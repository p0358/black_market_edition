// dllmain.cpp : Definiuje punkt wejścia dla aplikacji DLL.
#include "pch.h"
#include <iostream>
#include <functional>
#include <string>
#include "tier0.h"
#include "Memory.h"
#include "TTFSDK.h"
#include "CrashReporting.h"

HANDLE threadHandle;
std::chrono::system_clock::time_point g_startTime;

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

typedef __int64(__fastcall* sub_1802C4220_type)(int a1);
sub_1802C4220_type sub_1802C4220_org;
__int64 __fastcall sub_1802C4220(int a1)
{
 
    static auto sub_1800E8E80 = (__int64(__fastcall*)(int))(Util::GetModuleBaseAddress("client.dll") + 0xE8E80);
    __int64 v1 = sub_1800E8E80(a1);
    if (!v1) return 0; // lack of this check was crashing in original game!!!
    return (*(__int64(__fastcall**)(__int64))(*(_QWORD*)v1 + 1664i64))(v1);
}

typedef bool(__fastcall* Base_CmdKeyValues_ReadFromBuffer_type)(__int64, __int64);
Base_CmdKeyValues_ReadFromBuffer_type Base_CmdKeyValues_ReadFromBuffer_org;
bool __fastcall Base_CmdKeyValues_ReadFromBuffer(__int64 a1, __int64 a2)
{
    // what's wrong with CLC_CmdKeyValues and SVC_CmdKeyValues?
    // - unchecked bounds
    // - "OnPlayerAward" gets forwarded to everyone
    // - this is a Portal leftover that doesn't seem to ever get used by Titanfall
    auto logger = spdlog::get("logger");
    if (logger) logger->warn("Base_CmdKeyValues::ReadFromBuffer was called. This network message should never be used.");
    return false; // always block this message and drop the packet by returning false
}

// in theory the below should work, in practice it causes some language field to be empty somewhere and cause "file corruption" error message...
/*typedef char* (__fastcall* filterLanguage_type)(const char*, char*, size_t);
filterLanguage_type filterLanguage_engine_org;
filterLanguage_type filterLanguage_client_org;
char* __fastcall filterLanguage_engine(const char* Src, char* Dst, size_t Size) { strncpy_s(Dst, 64, Src, Size); return Dst; }
char* __fastcall filterLanguage_client(const char* Src, char* Dst, size_t Size) { strncpy_s(Dst, 64, Src, Size); return Dst; }*/

void DoMiscHooks()
{
    DWORD64 launcherdllBaseAddress = Util::GetModuleBaseAddress("launcher.org.dll");
    if (!launcherdllBaseAddress) launcherdllBaseAddress = Util::GetModuleBaseAddress("launcher.dll");
    DWORD64 clientdllBaseAddress = Util::GetModuleBaseAddress("client.dll");
    DWORD64 enginedllBaseAddress = Util::GetModuleBaseAddress("engine.dll");
    CreateMiscHook(launcherdllBaseAddress, 0x6B8E0, &CSourceAppSystemGroup_PreInit, reinterpret_cast<LPVOID*>(&CSourceAppSystemGroup_PreInit_org));
    CreateMiscHook(clientdllBaseAddress, 0x2C4220, &sub_1802C4220, reinterpret_cast<LPVOID*>(&sub_1802C4220_org));
    CreateMiscHook(enginedllBaseAddress, 0x203250, &Base_CmdKeyValues_ReadFromBuffer, reinterpret_cast<LPVOID*>(&Base_CmdKeyValues_ReadFromBuffer_org));
    //CreateMiscHook(enginedllBaseAddress, 0x489050, &filterLanguage_engine, reinterpret_cast<LPVOID*>(&filterLanguage_engine_org));
    //CreateMiscHook(clientdllBaseAddress, 0x67D6D0, &filterLanguage_client, reinterpret_cast<LPVOID*>(&filterLanguage_client_org));
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

    { // isMMDev
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("engine.dll")) + 0x229155A);
        TempReadWrite rw(ptr);
        *((bool*)ptr) = true;
    }
    { // retn here so we don't break the above accidentally
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("engine.dll")) + 0x57740);
        TempReadWrite rw(ptr);
        *((unsigned char*)ptr) = 0xC3;
    }

    // disabled for now, see comment in SourceConsole.cpp in Cmd_ExecuteCommand_Hook
    /*if (!strstr(GetCommandLineA(), "-norestrictservercommands"))
    {
        // default is m_bRestrictServerCommands=true, don't let it be set to false
        // this is the easiest way that at the same time allows m_bRestrictClientCommands to be false
        void* ptr = (void*)(Util::GetModuleBaseAddress(_("engine.dll")) + 0x19C516);
        TempReadWrite rw(ptr);
        memset(ptr, 0x90, 0x19C523 - 0x19C516);
    }*/
    // engine.dll+797070+193C4 = restrict server commands bool
    // engine.dll+797070+193C5 = restrict client commands bool
}

void CreateTier0MemAlloc()
{
    if (g_pMemAllocSingleton)
        return; // seems it's already created

    g_pMemAllocSingleton = CreateGlobalMemAlloc();
}


void main()
{
    g_startTime = std::chrono::system_clock::now();
    CreateTier0MemAlloc();
    //if (IsClient()) ShowConsole(); // TODO: disable in production?
    //std::cout << "bme.dll main" << std::endl;
    SetupLogger();
    auto logger = spdlog::get(_("logger"));

    if (strstr(GetCommandLineA(), _("-nocrashhandler"))) // CommandLine() not yet ready probably
        logger->info(_("Sentry not starting due to -nocrashhandler"));
    else
    {
        auto wasCrashHandlerStarted = SetupCrashHandler(GetThisPathWide());
        logger->info(_("Sentry was{}started"), wasCrashHandlerStarted ? " " : " not ");
    }

    curl_global_init_mem(CURL_GLOBAL_DEFAULT, internal_malloc, internal_free, internal_realloc, internal_strdup, internal_calloc);

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