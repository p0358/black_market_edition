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
#include "_version.h"
#include <iostream>

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
HookedFuncStatic<void> HostState_Shutdown("engine.dll", 0x14B810);

void test(const CCommand& args)
{
    //SDK().GetEngineClient()->ClientCmd_Unrestricted("disconnect \"test\"");
    //Updater::isUpdaterDownloadInProgress = true;
    throw std::exception();
}

void test_crash(const CCommand& args)
{
    std::cout << "Oops:" << *((int*)0);
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
void HostState_Shutdown_Hook() {
    SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "HostState_Shutdown_Hook => Engine is going to shut down");
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
    //HostState_Shutdown.Unhook();
    //func();
    HostState_Shutdown();
    //MH_Uninitialize();
    //TerminateProcess(GetCurrentProcess(), 0);
    FreeSDK();
    MH_DisableHook(MH_ALL_HOOKS);
}

extern void AntiEventCrash_Setup();

TTFSDK::TTFSDK() :
    //m_engineServer("engine.dll", "VEngineServer022"),
    m_engineClient("engine.dll", "VEngineClient013"),
    m_vstdlibCvar("vstdlib.dll", "VEngineCvar007"),
    m_inputSystem("inputsystem.dll", "InputSystemVersion001")
{
    runFrameHookCalled = false;
    m_logger = spdlog::get(_("logger"));

    SigScanFuncRegistry::GetInstance().ResolveAll();

    /*if (MH_Initialize() != MH_OK)
    {
        throw std::exception(_("Failed to initialise MinHook"));
    }*/

    m_conCommandManager.reset(new ConCommandManager());
    m_sqManager.reset(new SquirrelManager(*m_conCommandManager));
    m_fsManager.reset(new FileSystemManager(GetThisPath(), *m_conCommandManager));
    //m_uiManager.reset(new UIManager(*m_conCommandManager, *m_fsManager));
    m_sourceConsole.reset(new SourceConsole(*m_conCommandManager, true ? spdlog::level::debug : spdlog::level::info));

    //m_bmegui.reset(new BMEGUI(*m_conCommandManager, *m_uiManager, *m_fsManager));
    m_discord.reset(new DiscordWrapper(*m_conCommandManager));
    m_presence.reset(new Presence(*m_conCommandManager));

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
    m_conCommandManager->RegisterCommand("test_crash", test_crash, "Crash the engine by throwing an exception", 0);
    m_conCommandManager->RegisterConVar("bme_version", BME_VERSION, FCVAR_UNLOGGED | FCVAR_DONTRECORD | FCVAR_SERVER_CANNOT_QUERY, "Current BME version");

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

    {
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
    }

    AntiEventCrash_Setup();
    HostState_Shutdown.Hook(HostState_Shutdown_Hook);
}


FileSystemManager& TTFSDK::GetFSManager()
{
    return *m_fsManager;
}

ConCommandManager& TTFSDK::GetConCommandManager()
{
    return *m_conCommandManager;
}

SquirrelManager& TTFSDK::GetSQManager()
{
    return *m_sqManager;
}

UIManager& TTFSDK::GetUIManager()
{
    return *m_uiManager;
}

SourceConsole& TTFSDK::GetSourceConsole()
{
    return *m_sourceConsole;
}

BMEGUI& TTFSDK::GetBMEGUI()
{
    return *m_bmegui;

}

DiscordWrapper& TTFSDK::GetDiscord()
{
    return *m_discord;
}

Presence& TTFSDK::GetPresence()
{
    return *m_presence;
}

SourceInterface<IVEngineClient>& TTFSDK::GetEngineClient()
{
    return m_engineClient;
}

SourceInterface<ICvar>& TTFSDK::GetVstdlibCvar()
{
    return m_vstdlibCvar;
}

SourceInterface<IInputSystem>& TTFSDK::GetInputSystem()
{
    return m_inputSystem;
}

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

    for (const auto& frameTask : m_frameTasks)
    {
        frameTask->RunFrame();
    }

    m_frameTasks.erase(std::remove_if(m_frameTasks.begin(), m_frameTasks.end(), [](const std::shared_ptr<IFrameTask>& t)
        {
            return t->IsFinished();
        }), m_frameTasks.end());

    static bool called = false;
    if (!called)
    {
        runFrameHookCalled = true;
        m_logger->info(_("RunFrame called for the first time"));
        called = true;
        Updater::drawModalWillUpdaterLaunchAfterGameClose = false;
        m_sourceConsole->InitializeSource();

        {
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
            if (!Updater::pendingUpdateLaunch)
                m_engineClient->ClientCmd_Unrestricted("getmotd");
            else
                m_engineClient->ClientCmd_Unrestricted("motd \"Black Market Edition update is pending! The installer will be run after you exit your game.\"");
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

        {
            extern void StartPreloading();
            StartPreloading();
        }

        {
            discord::Activity activity{};
            activity.SetDetails(_("Main Menu"));
            activity.SetState(_(BME_VERSION_LONG));
            activity.GetAssets().SetSmallImage("");
            activity.GetAssets().SetSmallText("");
            activity.GetAssets().SetLargeImage(_("titanfall_101"));
            activity.GetAssets().SetLargeText(_("Titanfall"));
            activity.SetType(discord::ActivityType::Playing);
            const auto p1 = std::chrono::system_clock::now();
            const auto p2 = std::chrono::duration_cast<std::chrono::seconds>(
                p1.time_since_epoch()).count();
            activity.GetTimestamps().SetStart(p2);
            m_discord->UpdateActivity(activity);
        }

    }

    if (Updater::pendingUpdateLaunchMotdChange)
    {
        static uint8_t callCount = 0;
        callCount++;
        if (callCount >= 95)
        {
            //SPDLOG_LOGGER_DEBUG(m_logger, "set updater motd");
            m_engineClient->ClientCmd_Unrestricted("motd \"^00FF0000Black Market Edition update is pending! It will be installed after you exit your game.\"");
            callCount = 0;
            Updater::pendingUpdateLaunchMotdChange = false;
        }
    }

    static uint8_t callCount = 0;
    callCount++;
    if (callCount >= 5)
    {
        callCount = 0;
        if (m_discord->core)
            m_discord->core->RunCallbacks();

    }

    //m_uiManager->DrawTest();

    //return _Host_RunFrame(absTime, frameTime);
}

void TTFSDK::AddFrameTask(std::shared_ptr<IFrameTask> task)
{
    m_frameTasks.push_back(std::move(task));
}

void TTFSDK::AddDelayedFunc(std::function<void()> func, int frames)
{
    m_delayedFuncTask->AddFunc(func, frames);
}

void TTFSDK::ReinitDiscord()
{
    m_discord.reset();
    m_discord.reset(new DiscordWrapper(*m_conCommandManager));
}

TTFSDK::~TTFSDK()
{
    SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "TTFSDK destructor");
    // TODO: Reorder these
    //m_sqManager.reset();
    m_presence.reset();
    m_discord.reset();
    /////m_bmegui.reset();
    m_sourceConsole.reset();
    /////m_uiManager.reset();
    m_fsManager.reset();
    m_conCommandManager.reset();
    //m_pakManager.reset();
    //m_modManager.reset();
    // TODO: Add anything i've missed here
    SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "TTFSDK destructor finishing");
    //_Host_RunFrame.Unhook();
    CHostState_State_Run.Unhook();

    //MH_Uninitialize();

    curl_global_cleanup();
    SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "TTFSDK destructor finished");
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

void SetupLoggerInternal(const std::string& filename, bool enableWindowsConsole)
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
        sinks.push_back(std::make_shared<flushed_file_sink_mt>(filename, true));
    }
    catch (spdlog::spdlog_ex& ex)
    {
        fileError = std::make_unique<std::string>(ex.what());
    }

    // Create logger from sinks
    auto logger = std::make_shared<spdlog::logger>("logger", begin(sinks), end(sinks));
    logger->set_pattern(_("[%T] [thread %t] [%l] %^%v%$"));
#ifdef _DEBUG
    logger->set_level(spdlog::level::trace);
#else
    logger->set_level(spdlog::level::debug);
#endif

    if (fileError)
    {
        logger->warn(_("Failed to initialise file sink, log file will be unavailable ({})"), *fileError);
    }

    spdlog::register_logger(logger);
}

bool SetupLogger()
{
    try
    {
        //fs::path basePath(settings.BasePath);
        //fs::path basePath(".");
        fs::path basePath(GetThisPath());
        //SetupLogger((basePath / _("TTFSDK.log")).string(), true);
#ifdef _DEBUG
#define ENABLE_WINDOWS_CONSOLE true
#else
#ifdef STAGING
#define ENABLE_WINDOWS_CONSOLE true
#else
#define ENABLE_WINDOWS_CONSOLE false
#endif
#endif
        //SetupLoggerInternal((basePath / _("bme") / _("bme.log")).string(), ENABLE_WINDOWS_CONSOLE);
        SetupLoggerInternal((basePath / _("bme") / _("bme.log")).string(), strstr(GetCommandLineA(), _("-winconsole")));
        spdlog::get(_("logger"))->info("Logger has been initialized.");
        return true;
    }
    catch (std::exception& ex)
    {
        std::string message = fmt::format("Failed to initialise Black Market Edition logger: {}", ex.what());
        MessageBox(NULL, Util::Widen(message).c_str(), L"Error", MB_OK | MB_ICONERROR);
        return false;
    }
}

//extern void CheckForUpdates();
//extern bool updateInProcess;

bool SetupSDK()
{
    if (IsSDKReady()) { spdlog::get(_("logger"))->error(_("SDK IS ALREADY SET UP!!! WTF DID CALL THIS FUNC???")); return false; }

    // Separate try catch because these are required for logging to work
    //if (!SetupLogger()) return false;

    Updater::CheckForUpdates();

    try
    {
        /*bool breakpadSuccess = SetupBreakpad(GetThisPath());
        if (breakpadSuccess)
        {
            spdlog::get(_("logger"))->info(_("Breakpad initialized"));
        }
        else
        {
            spdlog::get(_("logger"))->info(_("Breakpad was not initialized"));
        }*/

        SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), _("Waiting for game DLLs..."));
        // TODO: Make this smarter (automatically pull DLL we need to load from somewhere)
        Util::WaitForModuleHandle(_("engine.dll"));
        Util::WaitForModuleHandle(_("client.dll"));
        Util::WaitForModuleHandle(_("vstdlib.dll"));
        Util::WaitForModuleHandle(_("filesystem_stdio.dll"));
        Util::WaitForModuleHandle(_("materialsystem_dx11.dll"));
        Util::WaitForModuleHandle(_("vguimatsurface.dll"));

        //SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), _("Suspending threads..."));
        //Util::ThreadSuspender suspender;
        //SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), _("Threads suspended. Initializing"));

        /*if (Updater::updateInProcess)
        {
            spdlog::get(_("logger"))->info(_("Update in progress, SDK will NOT be initialized. The updater should close the game now."));
            return true;
        }*/

        SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), _("Before actual SDK init."));
        g_SDK = std::make_unique<TTFSDK>();
        g_isSDKInitialized = true;
        SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), _("After actual SDK init."));

        //SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "Will unsuspend threads after this message.");
        return true;
    }
    catch (std::exception& ex)
    {
        std::string message = fmt::format("Failed to initialise Black Market Edition: {}", ex.what());
        spdlog::get(_("logger"))->critical(message);
        MessageBox(NULL, Util::Widen(message).c_str(), L"Error", MB_OK | MB_ICONERROR);
        return false;
    }
}

void FreeSDK()
{
    g_SDK.reset();
    if (g_console)
        g_console.reset();
}