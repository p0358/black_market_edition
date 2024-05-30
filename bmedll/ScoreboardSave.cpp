#include "pch.h"
#include "SquirrelManager.h"
#include "SquirrelJSONConverter.h"
#include "FileSystemManager.h"
#include "TTFSDK.h"

ConVar* bme_cl_save_scoreboards;
ConVar* bme_cl_save_scoreboards_upload_url;

struct ScoreboardUploadInfo
{
    fs::path path;
};

DWORD WINAPI ScoreboardUploadThread(PVOID pThreadParameter)
{
    auto* infoPtr = reinterpret_cast<ScoreboardUploadInfo*>(pThreadParameter);
    ScoreboardUploadInfo info = *infoPtr;
    delete infoPtr;

    auto* url = bme_cl_save_scoreboards_upload_url->GetString();
    spdlog::info("[ScoreboardUploadThread] Will try to upload scoreboard");

    auto curl = curl_easy_init();
    if (!curl)
        return 1;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, ""); // automatically uses all built-in supported encodings
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    //curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 0L);

    FILE* fd = _wfopen(info.path.c_str(), L"rb");
    if (!fd)
    {
        spdlog::error("[ScoreboardUploadThread] Error opening file");
        return 1;
    }

    struct stat file_info;
    if (fstat(fileno(fd), &file_info) != 0)
    {
        spdlog::error("[ScoreboardUploadThread] Error opening file");
        curl_easy_cleanup(curl);
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_READDATA, fd);
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);

    TFOrigin* origin = SDK().origin;
    struct curl_slist* list = NULL;
    if (origin && origin->isInitialized && origin->isOnline && !origin->isLoggedOut && origin->uid)
    {
        list = curl_slist_append(list, ("X-Origin-Uid: " + std::to_string(origin->uid)).c_str());
        list = curl_slist_append(list, ("X-Origin-Name: " + std::string(origin->playerName)).c_str());
    }
    else
    {
        ConVar* platform_user_id = SDK().GetVstdlibCvar()->FindVar("platform_user_id");
        ConVar* name = SDK().GetVstdlibCvar()->FindVar("name");
        list = curl_slist_append(list, ("X-Origin-Uid: " + std::string(platform_user_id->GetString())).c_str());
        list = curl_slist_append(list, ("X-Origin-Name: " + std::string(name->GetString())).c_str());
    }
    list = curl_slist_append(list, ("X-File-Name: " + info.path.filename().string()).c_str());
    list = curl_slist_append(list, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        spdlog::error("[ScoreboardUploadThread] curl_easy_perform() failed: {}", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return 1;
    }

    long response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    if (response_code != 200)
    {
        spdlog::error("[ScoreboardUploadThread] upload failed, response code: {}", response_code);
        curl_easy_cleanup(curl);
        return 1;
    }

    curl_off_t speed_upload, total_time;
    curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD_T, &speed_upload);
    curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &total_time);

    spdlog::info("[ScoreboardUploadThread] Scoreboard uploaded, speed: {} bytes/sec during {} seconds",
        (unsigned long)speed_upload, (unsigned long)((double)total_time / 1000000.0));

    curl_easy_cleanup(curl);
    return 0;
}

SQRESULT SaveScoreboard_Script(HSQUIRRELVM v)
{
    if (sq_gettop(nullptr, v) != 3)
    {
        SQVM_Raise_Error(v, "wrong number of parameters");
        return SQ_ERROR;
    }

    const SQChar* str;
    sq_getstring(v, 2, &str);

    if (strchr(str, '.') || strchr(str, '/') || strchr(str, '\\') || strchr(str, '\r') || strchr(str, '\n') || strchr(str, '\t'))
    {
        SQVM_Raise_Error(v, "invalid filename");
        return SQ_ERROR;
    }

    rapidjson::Document document;
    SquirrelJSONConverter::PullSquirrelValue(v, -1, document, document.GetAllocator());

    rapidjson::StringBuffer buffer;
    buffer.Clear();
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    std::string out{ buffer.GetString(), buffer.GetLength() };

    fs::path saved_scoreboards_path = SDK().GetFSManager().GetBasePath() / "bme" / "saved_scoreboards";
    if (!fs::exists(saved_scoreboards_path))
        fs::create_directories(saved_scoreboards_path);

    char timestr[200];
    {
        time_t t;
        struct tm* tmp;
        const char* fmt = "%Y-%m-%d_%H_%M_%S";

        t = time(NULL);
        tmp = gmtime(&t);
        if (tmp == NULL)
        {
            throw std::runtime_error("gmtime error");
        }

        if (strftime(timestr, sizeof(timestr), fmt, tmp) == 0)
        {
            throw std::runtime_error("strftime returned 0");
        }
    }


    std::string filename{ timestr };
    filename += str;
    filename += ".json";

    spdlog::info("[ScoreboardSave] Saving scoreboard to {}...", filename);

    fs::path outpath = saved_scoreboards_path / filename;
    std::ofstream outfile{ outpath };
    outfile << out;
    outfile.close();

    if (strlen(bme_cl_save_scoreboards_upload_url->GetString()) > 0)
    {
        auto* info = new ScoreboardUploadInfo;
        info->path = outpath;
        CreateThread(0, 0, ScoreboardUploadThread, info, 0, NULL);
    }

    return 0;
}

void ScoreboardSave_Init(SquirrelManager& sqManager, ConCommandManager& ccManager)
{
    sqManager.AddFuncRegistrationAllContexts("SaveScoreboard", SaveScoreboard_Script, ".s.", 0, "string", "string filename, void input", "");
    bme_cl_save_scoreboards =
        ccManager.RegisterConVar("bme_cl_save_scoreboards", "0", FCVAR_DONTRECORD, "Whether to save scoreboards in JSON files");
    bme_cl_save_scoreboards_upload_url =
        ccManager.RegisterConVar("bme_cl_save_scoreboards_upload_url", "", FCVAR_DONTRECORD, "Optional URL to also upload the saved scoreboards to (must enable the feature with the other cvar too for this to work)");
}
