#pragma once
#include "pch.h"
#include "SourceInterface.h"
#include "ICvar.h"
#include "IVEngineClient.h"
#include "ConCommandManager.h"
#include "SourceConsole.h"
#include "Console.h"
#include "BMEGUI.h"
#include "Discord.h"
#include "Presence.h"
#include "Origin.h"
#include "FileSystemManager.h"
#include "UIManager.h"
#include "IInputSystem.h"
#include "SquirrelManager.h"
#include "DelayedFunc.h"

class TTFSDK
{
private:
    std::shared_ptr<spdlog::logger> m_logger;

    std::unique_ptr<FileSystemManager> m_fsManager;
    std::unique_ptr<ConCommandManager> m_conCommandManager;
    std::unique_ptr<SquirrelManager> m_sqManager;
    //std::unique_ptr<ModManager> m_modManager;
    std::unique_ptr<UIManager> m_uiManager;
    std::unique_ptr<SourceConsole> m_sourceConsole;

    std::unique_ptr<BMEGUI> m_bmegui;
    std::unique_ptr<DiscordWrapper> m_discord;
    std::unique_ptr<Presence> m_presence;

    std::list<std::shared_ptr<IFrameTask>> m_frameTasks;
    std::recursive_mutex m_frameTasksLock;
    std::shared_ptr<DelayedFuncTask> m_delayedFuncTask;

    //SourceInterface<IVEngineServer> m_engineServer;
    SourceInterface<IVEngineClient> m_engineClient;
    SourceInterface<ICvar> m_vstdlibCvar;
    SourceInterface<IInputSystem> m_inputSystem;

    //ID3D11Device** m_ppD3D11Device;

public:
    TTFSDK();
    ~TTFSDK();
    void Init();

    TFOrigin* origin;

    FileSystemManager& GetFSManager();
    ConCommandManager& GetConCommandManager();
    SquirrelManager& GetSQManager();
    //ModManager& GetModManager();
    UIManager& GetUIManager();
    SourceConsole& GetSourceConsole();

    BMEGUI& GetBMEGUI();
    DiscordWrapper& GetDiscord();
    Presence& GetPresence();

    //ID3D11Device** GetD3D11DevicePtr();

    //SourceInterface<IVEngineServer>& GetEngineServer();
    SourceInterface<IVEngineClient>& GetEngineClient();
    SourceInterface<ICvar>& GetVstdlibCvar();
    SourceInterface<IInputSystem>& GetInputSystem();

    //void RunFrameHook(double absTime, float frameTime);
    void RunFrameHook(__int64 a1, double frameTime);
    bool runFrameHookCalled = false;

    void AddFrameTask(std::shared_ptr<IFrameTask> task);
    void AddDelayedFunc(std::function<void()> func, int frames = 0);

    void ReinitDiscord();
};

TTFSDK& SDK();
bool IsSDKReady();
bool SetupLogger();
bool SetupSDK();
void FreeSDK();
const std::string GetThisPath();
const std::wstring GetThisPathWide();
const std::string GetBMEChannel();
void HostState_Shutdown_Hook();
extern std::unique_ptr<Console> g_console;
extern HMODULE hDLLModule;
//extern bool isProcessTerminating;
extern bool g_isShuttingDown;
extern bool g_isDedicated;

#define IsDedi() (false)
#define IsClient() (true)
