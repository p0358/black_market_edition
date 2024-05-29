#include "pch.h"
#include "SquirrelManager.h"
#include "SquirrelJSONConverter.h"
#include "FileSystemManager.h"
#include "TTFSDK.h"

ConVar* bme_cl_save_scoreboards;

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

    return 0;
}

void ScoreboardSave_Init(SquirrelManager& sqManager, ConCommandManager& ccManager)
{
    sqManager.AddFuncRegistrationAllContexts("SaveScoreboard", SaveScoreboard_Script, ".s.", 0, "string", "string filename, void input", "");
    ccManager.RegisterConVar("bme_cl_save_scoreboards", "0", FCVAR_DONTRECORD, "");
}
