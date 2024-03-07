#include "pch.h"
#include "TTFSDK.h"
#include "Updater.h"
#include "Console.h"
#include "SigScanning.h"
#include "Util.h"
#include "CrashReporting.h"
#include "BMEGUI.h"
#include "Discord.h"
#include "Presence.h"
#include "tier0.h"
#include "_version.h"

std::unique_ptr<Console> g_console;
std::unique_ptr<TTFSDK> g_SDK;
bool g_isSDKInitialized = false;
bool g_isShuttingDown = false;
HMODULE hDLLModule;
//bool isProcessTerminating = false;

TTFSDK& SDK()
{
    return *g_SDK;
}

bool IsSDKReady()
{
    return g_isSDKInitialized && g_SDK.get() != nullptr && !g_isShuttingDown;
}

#define WRAPPED_MEMBER(name) MemberWrapper<decltype(&TTFSDK::##name), &TTFSDK::##name, decltype(&SDK), &SDK>::Call

//HookedSigScanFunc<void, double, float> _Host_RunFrame("engine.dll", "\x48\x8B\xC4\x48\x89\x58\x00\xF3\x0F\x11\x48\x00\xF2\x0F\x11\x40\x00", "xxxxxx?xxxx?xxxx?");
////HookedSigScanFunc<void, double, float> _Host_RunFrame("engine.dll", "\x48\x8B\xC4\x48\x89\x58\x10\x48\x89\x68\x18\x48\x89\x70\x20\xF3\x0F\x11\x40\x08", "xxxxxxxxxxxxxxxxxxxx");
//HookedSigScanFunc<void, double, float> _Host_RunFrame("engine.dll", "\x48\x8B\xC4\x48\x89\x58\x10\x48\x89\x68\x18\x48\x89\x70\x20\xF3\x0F\x11\x40\x08", "xxxxxx??????????xxx?");
HookedFuncStatic<void __fastcall, __int64, double> CHostState_State_Run("engine.dll", 0x14B300);
HookedFuncStatic<void> CHostState_Shutdown("engine.dll", 0x58BD0); // was: 0x14B810
HookedFuncStatic<void __fastcall, double> getMotd("engine.dll", 0x1B340);

void test(const CCommand& args)
{
    //SDK().GetEngineClient()->ClientCmd_Unrestricted("disconnect \"test\"");
    //Updater::isUpdaterDownloadInProgress = true;
    throw std::exception();
}

void test_crash1(const CCommand& args)
{
    std::cout << "Oops:" << *((int*)0);
}

void test_crash2(const CCommand& args)
{
    throw std::runtime_error("Test");
}

void test_crash3(const CCommand& args)
{
    throw std::exception("Test");
}

void test_crash4(const CCommand& args)
{
    __try
    {
        printf("In __try, about to force exception\n");
        int x = 5;
        int y = 0;
        int* p = &y;
#pragma warning(suppress: 4723)
        *p = x / *p;
    }
    __finally
    {
        printf("In __finally\n");
    }
}

const std::string GetThisPath()
{
    fs::path path;
    WCHAR result[MAX_PATH];
    DWORD length = GetModuleFileNameW(NULL, result, MAX_PATH);
    path = Util::Narrow(result);
    path._Remove_filename_and_separator();
    return path.string();
}

const std::wstring GetThisPathWide()
{
    WCHAR result[MAX_PATH];
    DWORD length = GetModuleFileNameW(NULL, result, MAX_PATH);
    fs::path path{ result };
    path._Remove_filename_and_separator();
    return path.wstring();
}

const std::string GetBMEChannel()
{
    static std::string chan;
    if (!chan.empty()) return chan;
    fs::path path(GetThisPath());
    path = path / "bme" / "bme_channel.txt";
    std::ifstream stream(path.string().c_str(), std::ios::binary);
    if (stream.is_open())
    {
        std::ostringstream sstr;
        sstr << stream.rdbuf();
        chan = sstr.str();
    }
    else chan = std::string(BME_CHANNEL);
    return chan;
}

//extern bool pendingUpdateLaunch;
//extern void LaunchUpdater();

//EXTERN_C IMAGE_DOS_HEADER __ImageBase;
void CHostState_Shutdown_Hook()
{
    spdlog::debug("CHostState::Shutdown Hook => Engine is going to shut down");
    //auto func = HostState_Shutdown.m_origFunc;
    //auto func = HostState_Shutdown.m_hookedFunc;
    //isProcessTerminating = true;
    g_isShuttingDown = true;

    extern HookedVTableFunc<decltype(&IFileSystem::VTable::MountVPK), &IFileSystem::VTable::MountVPK> IFileSystem_MountVPK;
    IFileSystem_MountVPK.Unhook();

    if (g_SDK)
    {
        g_SDK->GetSourceConsole().Deinitialize();
    }

    if (Updater::pendingUpdateLaunch)
        Updater::LaunchUpdater();
    //FreeLibraryAndExitThread(hDLLModule, 0);
    //CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, &__ImageBase, 0, NULL);
    ////FreeSDK();
    //CHostState_Shutdown.Unhook();
    //func();
    if (&g_SDK->GetDiscord() != nullptr)
        Discord_Shutdown();
    CHostState_Shutdown();
    //MH_Uninitialize();
    //TerminateProcess(GetCurrentProcess(), 0);
    FreeSDK();
    MH_DisableHook(MH_ALL_HOOKS);
#ifdef NDEBUG
    sentry_close();
#endif
}

void __fastcall getMotd_Hook(double a1)
{
    if (!IsSDKReady())
    {
        getMotd(a1);
        return;
    }
    static auto qword_18210FEA8 = *(uint64_t*)(Util::GetModuleBaseAddress("engine.dll") + 0x210FEA8);
    static auto& staticfile_hostname = *(const char**)(qword_18210FEA8 + 72);

    static std::string game_s3_url{ "bme.titanfall.top/backend/game_s3.php/ver=" BME_VERSION "/chan=" };
    static bool firstTimeCalled = true;
    if (firstTimeCalled)
    {
        game_s3_url += GetBMEChannel();
        game_s3_url += "/";
        firstTimeCalled = false;
    }

    auto staticfile_hostname_old = staticfile_hostname;
    staticfile_hostname = game_s3_url.c_str();
    getMotd(a1);
    staticfile_hostname = staticfile_hostname_old;
}

void GetCvarCC(const CCommand& args)
{
    if (args.ArgC() < 2)
    {
        spdlog::info("Usage: get_cvar <cvar_name>");
        return;
    }
    auto cvar = SDK().GetVstdlibCvar()->FindVar(args.Arg(1));
    if (!cvar)
    {
        spdlog::info("Cvar does not exist!");
        return;
    }
    spdlog::info("Cvar value: {}", cvar->GetString());
}

void SetCvarCC(const CCommand& args)
{
    if (args.ArgC() < 3)
    {
        spdlog::info("Usage: set_cvar <cvar_name> <cvar_value>");
        return;
    }
    auto cvar = SDK().GetVstdlibCvar()->FindVar(args.Arg(1));
    if (!cvar)
    {
        spdlog::info("Cvar does not exist!");
        return;
    }
    cvar->SetValueString(args.Arg(2));
    spdlog::info("Cvar value: {}", cvar->GetString());
}

extern void AntiEventCrash_Setup();

TTFSDK::TTFSDK() :
    //m_engineServer("engine.dll", "VEngineServer022"),
    m_engineClient("engine.dll", "VEngineClient013"),
    m_vstdlibCvar("vstdlib.dll", "VEngineCvar007"),
    m_inputSystem("inputsystem.dll", "InputSystemVersion001")
{
    m_logger = spdlog::get("logger");
}

void TTFSDK::Init()
{
    SigScanFuncRegistry::GetInstance().ResolveAll();

    m_delayedFuncTask = std::make_shared<DelayedFuncTask>();
    AddFrameTask(m_delayedFuncTask);

    m_conCommandManager = std::make_unique<ConCommandManager>();
    m_sqManager = std::make_unique<SquirrelManager>();
    m_fsManager = std::make_unique<FileSystemManager>(GetThisPath());
    //m_uiManager = std::make_unique<UIManager>();
    m_sourceConsole = std::make_unique<SourceConsole>(true ? spdlog::level::debug : spdlog::level::info);

    //m_bmegui.reset(new BMEGUI(*m_conCommandManager, *m_uiManager, *m_fsManager));
    if (!CommandLine()->CheckParm("-nodiscord"))
        m_discord = std::make_unique<DiscordWrapper>();
    m_presence = std::make_unique<Presence>();

    /*{
        Updater::updaterNowDownloaded = 5.0 * 1024.0 * 1023.0;
        Updater::updaterTotalToDownload = 10.0 * 1024.0 * 1022.0;
        Updater::isUpdaterDownloadInProgress = true;
        Updater::isUpdaterDownloadCancelled = false;
        Updater::updaterDownloadProgress = (5.0 * 1024.0 * 1023.0) / (10.0 * 1024.0 * 1022.0);
     }*/

    //_Host_RunFrame.Hook(WRAPPED_MEMBER(RunFrameHook));
    CHostState_State_Run.Hook(WRAPPED_MEMBER(RunFrameHook));

    m_conCommandManager->RegisterCommand("testtt", test, "Tests", 0);
    m_conCommandManager->RegisterCommand("test_crash1", test_crash1, "Crash the engine by dereferencing a null pointer", 0);
    m_conCommandManager->RegisterCommand("test_crash2", test_crash2, "Crash the engine by throwing a runtime error", 0);
    m_conCommandManager->RegisterCommand("test_crash3", test_crash3, "Crash the engine by throwing an exception", 0);
    m_conCommandManager->RegisterCommand("test_crash4", test_crash4, "Crash the engine by throwing a SE exception", 0);
    m_conCommandManager->RegisterCommand("get_cvar", GetCvarCC, "Print cvar's value", 0);
    m_conCommandManager->RegisterCommand("set_cvar", SetCvarCC, "Set cvar to value", 0);
    m_conCommandManager->RegisterConVar("bme_version", BME_VERSION, FCVAR_UNLOGGED | FCVAR_DONTRECORD | FCVAR_SERVER_CANNOT_QUERY, "Current BME version");
    m_conCommandManager->RegisterConVar("cl_nocmdrate", "0", FCVAR_DONTRECORD, "Do not limit command packet rate by cl_cmdrate, instead allow dispatching one packet after every move command (so after every client frame)");
    m_conCommandManager->RegisterConVar("hudwarp_disable", "0", FCVAR_DONTRECORD, "Disable HUD warping entirely for hugely improved performance. Affects how the HUD is displayed visually and breaks its \"warp-in\" effect at the beginning of the match in turn.");

#if 0
    /*{ // patch the restriction "Can't send client command; not connected to a server" of ClientCommand in script
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("client.dll")) + 0x2DB33B);
        TempReadWrite rw(ptr);
        *((unsigned char*)ptr) = 0xEB;
    }*/

    /*{ // FOV range patch
        {
            void* ptr = (void*)(Util::GetModuleBaseAddress(_("engine.dll")) + 0x6C6D34);
            TempReadWrite rw(ptr);
            *((float*)ptr) = 2.5f; // will work only before cvar is registered
        }
        //*(float*)(enginedllBaseAddress + 0x6C6D34) = 2.5; 
        ConVar* fov = (ConVar*)m_vstdlibCvar->FindVar("cl_fovScale");
        *(float*)((DWORD64)fov + 108) = 2.5f; // max
        //*(float*)((DWORD64)fov + 100) = 0.5f; // min
    }*/
    { // FOV range patch 2
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("engine.dll")) + 0x31A1BE0 + 108);
        //void* ptr = (void*)(*((unsigned __int64*)(Util::GetModuleBaseAddress(_("engine.dll")) + 0x31A1BE0)) + 108);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 2.5f;
    }
#endif

    this->origin = (TFOrigin*)(Util::GetModuleBaseAddress(_("engine.dll")) + 0x2ECB770);

    /*{
        std::string game_s3_url{ _("bme.titanfall.top/backend/game_s3.php/ver=") };
        game_s3_url += BME_VERSION;
        game_s3_url += _("/chan=");
        game_s3_url += GetBMEChannel();
        game_s3_url += "/";
        std::string cmd{ _("staticfile_hostname ") };
        cmd += game_s3_url;
        //ConVar* staticfile_hostname = m_vstdlibCvar->FindVar("staticfile_hostname");
        //staticfile_hostname->SetValueString(game_s3_url.c_str());
        m_engineClient->ClientCmd_Unrestricted(cmd.c_str());
    }*/
    if (!strstr(GetCommandLineA(), "-bmeoffline"))
    {
        getMotd.Hook(getMotd_Hook);
    }

    AntiEventCrash_Setup();
    CHostState_Shutdown.Hook(CHostState_Shutdown_Hook);
}


FileSystemManager& TTFSDK::GetFSManager() { return *m_fsManager; }
ConCommandManager& TTFSDK::GetConCommandManager() { return *m_conCommandManager; }
SquirrelManager& TTFSDK::GetSQManager() { return *m_sqManager; }
UIManager& TTFSDK::GetUIManager() { return *m_uiManager; }
SourceConsole& TTFSDK::GetSourceConsole() { return *m_sourceConsole; }
BMEGUI& TTFSDK::GetBMEGUI() { return *m_bmegui; }
DiscordWrapper& TTFSDK::GetDiscord() { return *m_discord; }
Presence& TTFSDK::GetPresence() {return *m_presence; }
SourceInterface<IVEngineClient>& TTFSDK::GetEngineClient() { return m_engineClient; }
SourceInterface<ICvar>& TTFSDK::GetVstdlibCvar() { return m_vstdlibCvar; }
SourceInterface<IInputSystem>& TTFSDK::GetInputSystem() { return m_inputSystem; }

//void TTFSDK::RunFrameHook(double absTime, float frameTime)
void __fastcall TTFSDK::RunFrameHook(__int64 a1, double frameTime)
{
    CHostState_State_Run.m_origFunc(a1, frameTime);

    static bool translatorUpdated = false;
    if (!translatorUpdated)
    {
        UpdateSETranslator();
        translatorUpdated = true;
    }

    {
        std::lock_guard<std::recursive_mutex> l(m_frameTasksLock);

        for (const auto& frameTask : m_frameTasks)
        {
            frameTask->RunFrame();
        }

        auto isFinished = [](const std::shared_ptr<IFrameTask>& t) { return t->IsFinished(); };
        m_frameTasks.erase(std::remove_if(m_frameTasks.begin(), m_frameTasks.end(), isFinished), m_frameTasks.end());
    }

    static bool called = false;
    if (!called)
    {
        runFrameHookCalled = true;
        m_logger->info(_("RunFrame called for the first time"));
        called = true;
        Updater::drawModalWillUpdaterLaunchAfterGameClose = false;
        m_sourceConsole->InitializeSource();

        {
            /*std::string game_s3_url{_("bme.titanfall.top/backend/game_s3.php/ver=")};
            game_s3_url += BME_VERSION;
            game_s3_url += "/chan=";
            game_s3_url += GetBMEChannel();
            game_s3_url += "/";
            std::string cmd{ "staticfile_hostname " };
            cmd += game_s3_url;
            //ConVar* staticfile_hostname = m_vstdlibCvar->FindVar("staticfile_hostname");
            //staticfile_hostname->SetValueString(game_s3_url.c_str());
            m_engineClient->ClientCmd_Unrestricted(cmd.c_str());
            if (!Updater::pendingUpdateLaunch)
                m_engineClient->ClientCmd_Unrestricted("getmotd");
            else*/
            if (Updater::pendingUpdateLaunch)
                m_engineClient->ClientCmd_Unrestricted("motd \"Black Market Edition update is pending! The installer will be started after you exit your game.\"");
        }

#if 0
        { // FOV range patch
            ConVar* fov = (ConVar*)m_vstdlibCvar->FindVar("cl_fovScale");
            *(float*)((DWORD64)fov + 108) = 3.85f; // max
            //*(float*)((DWORD64)fov + 100) = 0.5f; // min
        }

        { // FOV range patch 2
            void* ptr = (void*)(Util::GetModuleBaseAddress(_("engine.dll")) + 0x31A1BE0 + 108);
            //void* ptr = (void*)(*((unsigned __int64*)(Util::GetModuleBaseAddress(_("engine.dll")) + 0x31A1BE0)) + 108);
            TempReadWrite rw(ptr);
            *((float*)ptr) = 2.5f;
        }
#endif
        auto* net_showdrop = SDK().GetVstdlibCvar()->FindVar("net_showdrop");
        *(int*)((uint64_t)net_showdrop + 40) &= ~FCVAR_DEVELOPMENTONLY;

        {
            extern void StartPreloading();
            StartPreloading();
        }
    }

#ifdef NDEBUG
    static bool did_set_origin_info_in_sentry = false;
    if (!did_set_origin_info_in_sentry && origin && origin->uid && origin->playerName && origin->playerName[0])
    {
        // because it seems playerName isn't populated instantly
        did_set_origin_info_in_sentry = true;
        sentry_value_t user = sentry_value_new_object();
        sentry_value_t origin_ctx = sentry_value_new_object();
        if (origin->uid)
        {
            auto origin_id_sentry_value = sentry_value_new_string(std::to_string(origin->uid).c_str());
            sentry_value_set_by_key(user, "id", origin_id_sentry_value);
            sentry_value_set_by_key(origin_ctx, "originid", origin_id_sentry_value);
        }

        if (origin->playerName && origin->playerName[0])
        {
            sentry_value_set_by_key(user, "username", sentry_value_new_string(origin->playerName));
            sentry_value_set_by_key(origin_ctx, "originname", sentry_value_new_string(origin->playerName));
        }

        if (origin->locale && origin->locale[0])
            sentry_value_set_by_key(origin_ctx, "originlocale", sentry_value_new_string(origin->locale));
        if (origin->environment && origin->environment[0])
            sentry_value_set_by_key(origin_ctx, "originenvironment", sentry_value_new_string(origin->environment));

        sentry_set_user(user);
        sentry_set_context("origin", origin_ctx);
    }
#endif

    if (Updater::pendingUpdateLaunchMotdChange)
    {
        static uint8_t callCount = 0;
        callCount++;
        if (callCount >= 125)
        {
            //SPDLOG_LOGGER_DEBUG(m_logger, "set updater motd");
            m_engineClient->ClientCmd_Unrestricted("motd \"^00FF0000Black Market Edition update is pending! It will be installed after you exit your game.\"");
            callCount = 0;
            Updater::pendingUpdateLaunchMotdChange = false;
        }
    }

    //return _Host_RunFrame(absTime, frameTime);
}

void TTFSDK::AddFrameTask(std::shared_ptr<IFrameTask> task)
{
    std::lock_guard<std::recursive_mutex> l(m_frameTasksLock);
    m_frameTasks.push_back(std::move(task));
}

void TTFSDK::AddDelayedFunc(std::function<void()> func, int frames)
{
    m_delayedFuncTask->AddFunc(func, frames);
}

void TTFSDK::ReinitDiscord()
{
    m_discord.reset();
    m_discord = std::make_unique<DiscordWrapper>();
}

TTFSDK::~TTFSDK()
{
    SPDLOG_DEBUG("TTFSDK destructor");
    // TODO: Reorder these
    //m_sqManager.reset();
    m_presence.reset();
    m_discord.reset();
    /////m_bmegui.reset();
    m_sourceConsole.reset();
    /////m_uiManager.reset();
    m_fsManager.reset();
    m_conCommandManager.reset();
    //m_modManager.reset();
    // TODO: Add anything i've missed here
    SPDLOG_DEBUG("TTFSDK destructor finishing");
    //_Host_RunFrame.Unhook();
    CHostState_State_Run.Unhook();

    //MH_Uninitialize();

    curl_global_cleanup();
    SPDLOG_DEBUG("TTFSDK destructor finished");
}

class flushed_file_sink_mt : public spdlog::sinks::sink
{
public:
    explicit flushed_file_sink_mt(const spdlog::filename_t& filename, bool truncate = false) : file_sink_(filename, truncate)
    {

    }

    void log(const spdlog::details::log_msg& msg) override
    {
        file_sink_.log(msg);
        flush();
    }

    void flush() override
    {
        file_sink_.flush();
    }

    void set_pattern(const std::string& pattern) override
    {
        file_sink_.set_pattern(pattern);
    }

    void set_formatter(std::unique_ptr<spdlog::formatter> sink_formatter) override
    {
        file_sink_.set_formatter(std::move(sink_formatter));
    }

private:
    spdlog::sinks::basic_file_sink_mt file_sink_;
};

void SetupLoggerInternal(const fs::path& filename, bool enableWindowsConsole)
{
    // Create sinks to file and console
    std::vector<spdlog::sink_ptr> sinks;

    if (enableWindowsConsole)
    {
        g_console = std::make_unique<Console>();
        sinks.push_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
    }

    // The file sink could fail so capture the error if so
    std::unique_ptr<std::string> fileError;
    try
    {
        sinks.push_back(std::make_shared<flushed_file_sink_mt>(filename.wstring(), true));
    }
    catch (spdlog::spdlog_ex& ex)
    {
        fileError = std::make_unique<std::string>(ex.what());
    }

    // Create logger from sinks
    auto logger = std::make_shared<spdlog::logger>("logger", begin(sinks), end(sinks));
    logger->set_pattern("[%T] [thread %t] [%l] %^%v%$");
#ifdef _DEBUG
    logger->set_level(spdlog::level::trace);
#else
    logger->set_level(spdlog::level::debug);
#endif

    if (fileError)
    {
        logger->warn("Failed to initialise file sink, log file will be unavailable ({})", *fileError);
    }

    spdlog::register_logger(logger);
    spdlog::set_default_logger(logger);
}

bool SetupLogger()
{
    try
    {
        fs::path basePath(GetThisPath());
#ifdef _DEBUG
#define ENABLE_WINDOWS_CONSOLE true
#else
#ifdef STAGING
#define ENABLE_WINDOWS_CONSOLE true
#else
#define ENABLE_WINDOWS_CONSOLE false
#endif
#endif
        SetupLoggerInternal(basePath / "bme" / "bme.log", strstr(GetCommandLineA(), "-winconsole"));

        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);

        spdlog::info("Logger has been initialized at {}.", strtok(std::ctime(&time), "\n"));
        spdlog::info("Raw command line: {}", GetCommandLineA());

        spdlog::info("CPU: {}", Util::GetProcessorNameString());
        bool ishdd = Util::DoesStorageDeviceIncurSeekPenaltyAtPath((basePath / L"vpk" / L"client_mp_common.bsp.pak000_000.vpk").wstring().c_str());
        spdlog::info("Does storage device incur seek penalty (is HDD): {}", ishdd);

        {
            // Log WINE version if running under WINE
            HMODULE hntdll;
            typedef const char* (CDECL* wine_get_version_t)();
            typedef const char* (CDECL* wine_get_build_id_t)();
            typedef void (CDECL* wine_get_host_version_t)(const char** sysname, const char** release);
            wine_get_version_t wine_get_version;
            wine_get_build_id_t wine_get_build_id;
            wine_get_host_version_t wine_get_host_version;
            if ((hntdll = GetModuleHandleA("ntdll.dll")) && (wine_get_version = reinterpret_cast<wine_get_version_t>(GetProcAddress(hntdll, "wine_get_version"))))
            {
                spdlog::info("WINE version: {}", wine_get_version()); // example: 7.11
                if (wine_get_build_id = reinterpret_cast<wine_get_build_id_t>(GetProcAddress(hntdll, "wine_get_build_id")))
                    spdlog::info("WINE build: {}", wine_get_build_id()); // example: wine-7.11
                if (wine_get_host_version = reinterpret_cast<wine_get_host_version_t>(GetProcAddress(hntdll, "wine_get_host_version")))
                {
                    const char* sysname; // example: Linux
                    const char* release; // example: 5.16.20-2-MANJARO
                    wine_get_host_version(&sysname, &release);
                    spdlog::info("WINE host system: {}", sysname);
                    spdlog::info("WINE host system release: {}", release);
                }
            }

            // STEAM_COMPAT_TOOL_PATHS is a colon separated lists of all compat tool paths used
            // The first one tends to be the Proton path itself
            // We extract the basename out of it to get the name used
            if (char* compatToolPtr = std::getenv("STEAM_COMPAT_TOOL_PATHS"))
            {
                std::string_view compatToolPath{ compatToolPtr };

                auto protonBasenameEnd = compatToolPath.find(":");
                if (protonBasenameEnd == std::string_view::npos)
                    protonBasenameEnd = 0;
                auto protonBasenameStart = compatToolPath.rfind("/", protonBasenameEnd) + 1;
                if (protonBasenameStart == std::string_view::npos)
                    protonBasenameStart = 0;

                spdlog::info("Proton build: {}", compatToolPath.substr(protonBasenameStart, protonBasenameEnd - protonBasenameStart));
            }
        }
        {
#ifdef _DEBUG
            spdlog::warn("Running a DEBUG build. Debug builds are untested and unsupported. Their usage may cause unforeseen random issues with the game, which you should not expect the TFORevive developers to look into.");
#endif
        }

        return true;
    }
    catch (std::exception& ex)
    {
        std::string message = fmt::format("Failed to initialise Black Market Edition logger: {}", ex.what());
        MessageBoxW(NULL, Util::Widen(message).c_str(), L"Error", MB_OK | MB_ICONERROR);
        return false;
    }
}

//extern void CheckForUpdates();
//extern bool updateInProcess;

bool SetupSDK()
{
    if (IsSDKReady()) { spdlog::error("SDK IS ALREADY SET UP!!! WTF DID CALL THIS FUNC???"); return false; }

    if (!strstr(GetCommandLineA(), "-bmenoupdates") && !strstr(GetCommandLineA(), "-bmeoffline"))
        Updater::CheckForUpdates();

    try
    {
        /*if (Updater::updateInProcess)
        {
            spdlog::info("Update in progress, SDK will NOT be initialized. The updater should close the game now.");
            return true;
        }*/

        SPDLOG_DEBUG("Before actual SDK init.");
        g_SDK = std::make_unique<TTFSDK>();
        g_SDK->Init();
        extern void HitchAlert_Setup(); HitchAlert_Setup();
        g_isSDKInitialized = true;
        SPDLOG_DEBUG("After actual SDK init.");
        return true;
    }
    catch (std::exception& ex)
    {
        std::string message = fmt::format("Failed to initialise Black Market Edition: {}", ex.what());
        MessageBoxA(NULL, message.c_str(), "Error", MB_OK | MB_ICONERROR);
        spdlog::critical(message);
        //MessageBox(NULL, Util::Widen(message).c_str(), L"Error", MB_OK | MB_ICONERROR);
        throw;
        return false;
    }
}

void FreeSDK()
{
    g_SDK.reset();
    if (g_console)
        g_console.reset();
}