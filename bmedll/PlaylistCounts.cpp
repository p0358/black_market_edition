#include "pch.h"
#include "TTFSDK.h"
#include "SquirrelManager.h"
#include "ConCommandManager.h"
#include "_version.h"

std::string g_playlistCounts_etag;
std::shared_ptr<rapidjson::Document> g_playlistCountsJson;
std::mutex g_playlistCountsJsonMutex;

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);

DWORD WINAPI loadPlaylistCounts(PVOID pThreadParameter)
{
    auto curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://titanfall.top/status/playlists.json");
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, ""); // automatically uses all built-in supported encodings
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        //curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 0L);

        if (g_playlistCounts_etag.size())
        {
            struct curl_slist* list = NULL;
            list = curl_slist_append(list, ("If-None-Match: " + g_playlistCounts_etag).c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
        }

        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "BME/" BME_VERSION);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        curl_easy_perform(curl);

        long response_code;
        //double elapsed;
        //char* url;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        //curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        //curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

        std::string content_type, etag;
        struct curl_header* header;
        curl_easy_header(curl, "Content-Type", 0, CURLH_HEADER, -1, &header);
        if (header && header->value && header->value[0])
            content_type.assign(header->value);
        curl_easy_header(curl, "Etag", 0, CURLH_HEADER, -1, &header);
        if (header && header->value && header->value[0])
            etag.assign(header->value);

        curl_easy_cleanup(curl);

        if (response_code == 200)
        {
            if (content_type != "application/json")
            {
                spdlog::error("Wrong content-type for playlists ({}) despite response code 200", content_type);
                return 0;
            }
            if (etag.size())
            {
                spdlog::info("Received new playlists with etag: `{}` (response length: {})", etag, response_string.size());
                g_playlistCounts_etag.assign(etag);
            }
            std::shared_ptr<rapidjson::Document> newJson = std::make_shared<rapidjson::Document>();
            if (!newJson->Parse(response_string).HasParseError())
            {
                {
                    std::scoped_lock _{ g_playlistCountsJsonMutex };
                    g_playlistCountsJson = newJson;
                }
                SDK().GetConCommandManager().ExecuteCommand("script_ui BME_PlaylistCountsUpdated()");
            }
            else
            {
                spdlog::error("Parse error for playlists JSON despite response code 200 and correct content-type. Contents: {}", response_string);
            }
        }
        else if (response_code == 304)
        {
            spdlog::info("Playlists did not change since last refresh (304 Not Modified)");
        }
        else
        {
            spdlog::error("Unexpected response code for playlists (expected 200 or 304): {}", response_code);
        }
    }

    return 0;
}

SQInteger Script_BME_RefreshPlaylistCounts(HSQUIRRELVM v)
{
    spdlog::info("Refreshing BME playlist counts...");
    CreateThread(0, 0, loadPlaylistCounts, 0, 0, NULL);
    return 0;
}

SQInteger Script_GetPlaylistCountDescForMonthly_BME(HSQUIRRELVM v)
{
    std::shared_ptr<rapidjson::Document> json;
    {
        std::scoped_lock _{ g_playlistCountsJsonMutex };
        if (!g_playlistCountsJson.get())
        {
            sq_pushstring(v, "", -1);
            return 1;
        }
        json = g_playlistCountsJson;
    }
    if (json->HasMember("total_monthly") && (*json)["total_monthly"].IsNumber())
    {
        sq_pushinteger(nullptr, v, (*json)["total_monthly"].GetInt());
        return 1;
    }
    return -1;
}

SQInteger Script_GetPlaylistCountDescForWorldTotal_BME(HSQUIRRELVM v)
{
    std::shared_ptr<rapidjson::Document> json;
    {
        std::scoped_lock _{ g_playlistCountsJsonMutex };
        if (!g_playlistCountsJson.get())
        {
            sq_pushstring(v, "", -1);
            return 1;
        }
        json = g_playlistCountsJson;
    }
    if (json->HasMember("total_world") && (*json)["total_world"].IsNumber())
    {
        sq_pushinteger(nullptr, v, (*json)["total_world"].GetInt());
        return 1;
    }
    return -1;
}

SQInteger Script_GetPlaylistCountDescForRegion_BME(HSQUIRRELVM v)
{
    const SQChar* str;
    sq_getstring(v, 2, &str);

    static ConVarRef match_myDatacenter{ "match_myDatacenter" };
    auto* match_myDatacenter_str = match_myDatacenter->GetString();

    std::shared_ptr<rapidjson::Document> json;
    {
        std::scoped_lock _{ g_playlistCountsJsonMutex };
        if (!g_playlistCountsJson.get())
        {
            sq_pushstring(v, "", -1);
            return 1;
        }
        json = g_playlistCountsJson;
    }
    if (json->HasMember("playlists") && (*json)["playlists"].IsObject())
    {
        auto& playlists = (*json)["playlists"];
        if (playlists.HasMember(str) && playlists[str].IsObject() && playlists[str].HasMember(match_myDatacenter_str) && playlists[str][match_myDatacenter_str].IsNumber())
            sq_pushinteger(nullptr, v, playlists[str][match_myDatacenter_str].GetInt());
        else
            sq_pushinteger(nullptr, v, 0);
        return 1;
    }
    return -1;
}

SQInteger Script_GetPlaylistCountDescForWorld_BME(HSQUIRRELVM v)
{
    const SQChar* str;
    sq_getstring(v, 2, &str);

    std::shared_ptr<rapidjson::Document> json;
    {
        std::scoped_lock _{ g_playlistCountsJsonMutex };
        if (!g_playlistCountsJson.get())
        {
            sq_pushstring(v, "", -1);
            return 1;
        }
        json = g_playlistCountsJson;
    }
    if (json->HasMember("playlists") && (*json)["playlists"].IsObject())
    {
        auto& playlists = (*json)["playlists"];
        if (playlists.HasMember(str) && playlists[str].IsObject() && playlists[str].HasMember("_world") && playlists[str]["_world"].IsNumber())
            sq_pushinteger(nullptr, v, playlists[str]["_world"].GetInt());
        else
            sq_pushinteger(nullptr, v, 0);
        return 1;
    }
    return -1;
}

void PlaylistCounts_Init()
{
	auto& sqMan = SDK().GetSQManager();
	sqMan.AddFuncRegistration(SCRIPT_CONTEXT_UI, "BME_RefreshPlaylistCounts", Script_BME_RefreshPlaylistCounts, ".", 0, "", "", "");
	sqMan.AddFuncRegistration(SCRIPT_CONTEXT_UI, "GetPlaylistCountDescForMonthly_BME", Script_GetPlaylistCountDescForMonthly_BME, ".", 0, "integer", "", "");
	sqMan.AddFuncRegistration(SCRIPT_CONTEXT_UI, "GetPlaylistCountDescForWorldTotal_BME", Script_GetPlaylistCountDescForWorldTotal_BME, ".", 0, "integer", "", "");
	sqMan.AddFuncRegistration(SCRIPT_CONTEXT_UI, "GetPlaylistCountDescForRegion_BME", Script_GetPlaylistCountDescForRegion_BME, ".s", 0, "integer", "string text", "");
	sqMan.AddFuncRegistration(SCRIPT_CONTEXT_UI, "GetPlaylistCountDescForWorld_BME", Script_GetPlaylistCountDescForWorld_BME, ".s", 0, "integer", "string text", "");
}