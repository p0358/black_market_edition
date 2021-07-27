// dllmain.cpp : Definiuje punkt wejścia dla aplikacji DLL.
#include "pch.h"
#include <iostream>
#include <functional>
#include <string>
#include "TTFSDK.h"
#include "CrashReporting.h"

HANDLE threadHandle;

// old
DWORD WINAPI OnAttach(LPVOID lpThreadParameter)
{
    curl_global_init(CURL_GLOBAL_ALL);

    // Setup the SDK or unload the DLL if we can't
    if (!SetupSDK())
    {
        TerminateProcess(GetCurrentProcess(), 100);
        return 0;
    }

    auto logger = spdlog::get(_("logger"));
    logger->info(_("Titanfall Black Market Edition loaded"));

    if (g_console)
    {
        // Process console input
        std::string input;
        while (std::getline(std::cin, input) && g_console && IsSDKReady())
        {
            //if (&SDK() != nullptr)
            SDK().GetConCommandManager().ExecuteCommand(input);
            //SDK().GetDiscord().core->RunCallbacks();
        }
    }

    return 0;
}

////////

//bool isConsoleEnabled = false;

HANDLE consoleInputThread;
DWORD WINAPI ConsoleInputThread(PVOID pThreadParameter)
{
    //if (!isConsoleEnabled) return 0;
    while (!g_console || !IsSDKReady())
        Sleep(1000);

    {
        std::cout << "this thread will now listen for commands in console" << std::endl;
        // Process console input
        std::string input;
        while (std::getline(std::cin, input) && g_console && IsSDKReady())
        {
            input += "\n";
            SDK().GetConCommandManager().ExecuteCommand(input);
        }
    }
    return 0;
}

/////////////////////

void CreateMiscHook_Error(const std::string& err)
{
    std::cout << std::endl << "/////////// Error in CreateMiscHook:" << std::endl << err << std::endl << "///////////" << std::endl;
    MessageBoxA(NULL, err.c_str(), "Error in CreateMiscHook", 0);
}

//MH_STATUS WINAPI CreateMiscHook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal)
MH_STATUS WINAPI CreateMiscHook(DWORD64 baseAddress, unsigned int offset, LPVOID pDetour, LPVOID* ppOriginal)
{
    static unsigned int counter = 0;
    counter++;
    LPVOID pTarget = (LPVOID)(baseAddress + offset);
    auto ret = MH_CreateHook(pTarget, pDetour, ppOriginal);
    if (ret != MH_OK)
    {
        CreateMiscHook_Error(fmt::sprintf("Error hooking function with index number %i at module's offset of 0x%X", counter, offset));
    }
    return ret;
}

MH_STATUS WINAPI CreateMiscHookNamed(const char* moduleName, const char* procName, LPVOID pDetour, LPVOID* ppOriginal)
{
    HMODULE hModule = GetModuleHandleA(moduleName);
    if (!hModule)
    {
        CreateMiscHook_Error(fmt::sprintf("GetModuleHandle failed for %s (Error = 0x%X)", moduleName, GetLastError()));
        return MH_ERROR_MODULE_NOT_FOUND;
    }

    void* exportPtr = GetProcAddress(hModule, procName);
    if (!exportPtr)
    {
        CreateMiscHook_Error(fmt::sprintf("GetProcAddress failed for %s (ModuleName = %s, Error = 0x%X)", procName, moduleName, GetLastError()));
        return MH_ERROR_FUNCTION_NOT_FOUND;
    }

    LPVOID pTarget = exportPtr;
    auto ret = MH_CreateHook(pTarget, pDetour, ppOriginal);
    if (ret != MH_OK)
    {
        CreateMiscHook_Error(fmt::sprintf("Error hooking function %s (0x%X) in %s", procName, exportPtr, moduleName));
    }
    return ret;
}

typedef char(__fastcall *CSourceAppSystemGroup_PreInit_type)(__int64 a1);
CSourceAppSystemGroup_PreInit_type CSourceAppSystemGroup_PreInit_org;
char __fastcall CSourceAppSystemGroup_PreInit(__int64 a1) // 
{
    auto res = CSourceAppSystemGroup_PreInit_org(a1);
    SetupSDK();
    return res;
}

void DoMiscHooks()
{
    DWORD64 launcherdllBaseAddress = Util::GetModuleBaseAddress("launcher.org.dll");
    CreateMiscHook(launcherdllBaseAddress, 0x6B8E0, &CSourceAppSystemGroup_PreInit, reinterpret_cast<LPVOID*>(&CSourceAppSystemGroup_PreInit_org));
}

void DoBinaryPatches()
{
    { // patch the restriction "Can't send client command; not connected to a server" of ClientCommand in script
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("client.dll")) + 0x2DB33B);
        TempReadWrite rw(ptr);
        *((unsigned char*)ptr) = 0xEB;
    }

//#if 0
    { // FOV range patch
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("engine.dll")) + 0x6C6D34);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f; // will work only before cvar is registered
    }
    { // FOV range patch 2
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("engine.dll")) + 0x31A1BE0 + 108);
        //void* ptr = (void*)(*((unsigned __int64*)(Util::GetModuleBaseAddress(_("engine.dll")) + 0x31A1BE0)) + 108);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f;
    }
    { // FOV range patch
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("client.dll")) + 0x9CDB74);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f; // will work only before cvar is registered
    }
    { // FOV range patch 2
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("client.dll")) + 0x38774C0 + 108);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f;
    }
    { // FOV range patch
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("materialsystem_dx11.dll")) + 0x191734);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f; // will work only before cvar is registered
    }
    { // FOV range patch 2
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("materialsystem_dx11.dll")) + 0x3B9560 + 108);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f;
    }
    { // FOV range patch in client.dll
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("client.dll")) + 0x7F9844);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f;
    }
//#endif
}


void main()
{
    //if (IsClient()) ShowConsole(); // TODO: disable in production?
    //std::cout << "bme.dll main" << std::endl;
    SetupLogger();
    auto logger = spdlog::get(_("logger"));

    if (strstr(GetCommandLineA(), _("-nocrashhandler"))) // CommandLine() not yet ready probably
        logger->info(_("Breakpad not starting due to -nocrashhandler"));
    else
    {
        auto wasBreakpadStarted = SetupBreakpad(GetThisPath());
        logger->info(_("Breakpad was{}started"), wasBreakpadStarted ? " " : " not ");
    }

    curl_global_init(CURL_GLOBAL_ALL);

    SPDLOG_LOGGER_DEBUG(logger, _("DoBinaryPatches"));
    DoBinaryPatches();

    {
        SPDLOG_LOGGER_DEBUG(logger, _("MH_Initialize")); 
        if (MH_Initialize() != MH_OK)
        {
            logger->error(_("MH_Initialize error"));
            return;
        }

        SPDLOG_LOGGER_DEBUG(logger, _("DoMiscHooks"));
        DoMiscHooks();

        if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        {
            logger->error(_("MH_EnableHook error"));
            return;
        }

    }

    SPDLOG_LOGGER_DEBUG(logger, _("Preinit code end"));

    consoleInputThread = CreateThread(0, 0, ConsoleInputThread, 0, 0, NULL);
}

////////

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    DisableThreadLibraryCalls(hModule);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        hDLLModule = hModule;

        //threadHandle = CreateThread(NULL, 0, OnAttach, NULL, 0, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        //TerminateThread(threadHandle, 0);
        /*FreeSDK();
        if (g_console)
            g_console.reset();*/
        break;
    }
    return TRUE;
}

extern "C" _declspec(dllexport) void Init()
{
    //printf("hello in init\n");
    main();
}