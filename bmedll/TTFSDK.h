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

class TTFSDK
{
private:
    std::shared_ptr<spdlog::logger> m_logger;

    std::unique_ptr<FileSystemManager> m_fsManager;
    std::unique_ptr<ConCommandManager> m_conCommandManager;
    //std::unique_ptr<SquirrelManager> m_sqManager;
    //std::unique_ptr<PakManager> m_pakManager;
    //std::unique_ptr<ModManager> m_modManager;
    std::unique_ptr<UIManager> m_uiManager;
    std::unique_ptr<SourceConsole> m_sourceConsole;

    std::unique_ptr<BMEGUI> m_bmegui;
    std::unique_ptr<DiscordWrapper> m_discord;
    std::unique_ptr<Presence> m_presence;

    //std::unique_ptr<IcepickMenu> m_icepickMenu;

    //std::list<std::shared_ptr<IFrameTask>> m_frameTasks;
    //std::shared_ptr<DelayedFuncTask> m_delayedFuncTask;

    //SourceInterface<IVEngineServer> m_engineServer;
    SourceInterface<IVEngineClient> m_engineClient;
    SourceInterface<ICvar> m_vstdlibCvar;
    SourceInterface<IInputSystem> m_inputSystem;

    //ID3D11Device** m_ppD3D11Device;

public:
    TTFSDK();
    ~TTFSDK();

    TFOrigin* origin;

    FileSystemManager& GetFSManager();
    ConCommandManager& GetConCommandManager();
    //SquirrelManager& GetSQManager();
    //PakManager& GetPakManager();
    //ModManager& GetModManager();
    UIManager& GetUIManager();
    SourceConsole& GetSourceConsole();

    BMEGUI& GetBMEGUI();
    DiscordWrapper& GetDiscord();
    Presence& GetPresence();

    //ID3D11Device** GetD3D11DevicePtr();

    //IcepickMenu& GetIcepickMenu();

    //SourceInterface<IVEngineServer>& GetEngineServer();
    SourceInterface<IVEngineClient>& GetEngineClient();
    SourceInterface<ICvar>& GetVstdlibCvar();
    SourceInterface<IInputSystem>& GetInputSystem();

    void RunFrameHook(double absTime, float frameTime);
    bool runFrameHookCalled;

    //void AddFrameTask(std::shared_ptr<IFrameTask> task);
    //void AddDelayedFunc(std::function<void()> func, int frames);

    //SQInteger SQGetMouseDeltaX(HSQUIRRELVM v);
    //SQInteger SQGetMouseDeltaY(HSQUIRRELVM v);

    //void EnableNoclipCommand(const CCommand& args);
    //void DisableNoclipCommand(const CCommand& args);
};

TTFSDK& SDK();
bool SetupSDK();
void FreeSDK();
const std::string GetThisPath();
const std::string GetBMEChannel();
void HostState_Shutdown_Hook();
extern std::unique_ptr<Console> g_console;
extern HMODULE hDLLModule;
extern bool isProcessTerminating;