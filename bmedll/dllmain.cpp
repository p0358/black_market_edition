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

extern FuncStaticWithType<void* (__cdecl*)()> get_cl;

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

typedef int (*GENERICINTCONSTCHARPTRVALISTFUNCTION) (const char* a1, ...);
GENERICINTCONSTCHARPTRVALISTFUNCTION sub_180022610_org;
int sub_180022610(const char* a1, ...) // or const char*
{
    va_list va; 
    va_start(va, a1);
    char buffer[256];
    vsnprintf(buffer, 256, a1, va);
    spdlog::get("logger")->debug("[netdebug] {}", buffer);
    va_end(va);
    return 0;
}

typedef bool(__fastcall* INetMessage_WriteToBuffer_type)(__int64 msg, __int64 buffer);
INetMessage_WriteToBuffer_type INetMessage_WriteToBuffer_org;
bool __fastcall INetMessage_WriteToBuffer(__int64 msg, __int64 buffer)
{
    auto msgid = (*(__int64(__fastcall**)(__int64))(*(_QWORD*)msg + 64i64))(msg);
    auto toString = (*(char*(__fastcall**)(__int64))(*(_QWORD*)msg + 64i64 + 32))(msg);
    spdlog::get("logger")->debug("[INetMessage::WriteToBuffer] [id:{}] {}", msgid, toString);
    return INetMessage_WriteToBuffer_org(msg, buffer);
}

typedef bool(__fastcall* ReadUBitLong_probably_for_netmsg_type_6bits__sub_1801F6C20_type)(int* a1, __int64 a2);
ReadUBitLong_probably_for_netmsg_type_6bits__sub_1801F6C20_type ReadUBitLong_probably_for_netmsg_type_6bits__sub_1801F6C20_org;
bool __fastcall ReadUBitLong_probably_for_netmsg_type_6bits__sub_1801F6C20(int* a1, __int64 a2)
{
    auto ret = ReadUBitLong_probably_for_netmsg_type_6bits__sub_1801F6C20_org(a1, a2);
    spdlog::get("logger")->debug("[reading net message] id:{} => {}", *a1, ret);
    return ret;
}

typedef bool(__fastcall* CBaseClientState_ConnectionCrashed_type)(__int64 a1, __int64 a2);
CBaseClientState_ConnectionCrashed_type CBaseClientState_ConnectionCrashed_org;
__int64 __fastcall CBaseClientState_ConnectionCrashed(__int64 a1, __int64 a2)
{
    spdlog::get("logger")->warn("[CBaseClientState::ConnectionCrashed] {}", (char*)a2);
    return CBaseClientState_ConnectionCrashed_org(a1, a2);
}

typedef void (*Con_NXPrintf_type)(__int64 a1, const char* fmt, ...);
Con_NXPrintf_type Con_NXPrintf_org;
void Con_NXPrintf(__int64 a1, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    spdlog::get("logger")->warn("[Con_NXPrintf] {}", Util::vformat(fmt, args));
    va_end(args);
    // no original call as it's nullsub
}

/*typedef char(__fastcall* CNetChan_ProcessMessages_type)(__int64* a1, __int64 a2);
CNetChan_ProcessMessages_type CNetChan_ProcessMessages_org;
char __fastcall CNetChan_ProcessMessages(__int64* a1, __int64 a2)
{
    auto ret = CNetChan_ProcessMessages_org(a1, a2);
    
    return ret;
}*/

bool g_droppedPacketFlag = false;
typedef void netpacket_t;
typedef void netadr_t;
typedef __int64(__fastcall* CNetChan_ProcessPacketHeader_type)(_DWORD* thisptr, netpacket_t* packet);
CNetChan_ProcessPacketHeader_type CNetChan_ProcessPacketHeader_org;
__int64 __fastcall CNetChan_ProcessPacketHeader(_DWORD* thisptr, netpacket_t* packet)
{
    static auto& net_showdrop = SDK().GetVstdlibCvar()->FindVar("net_showdrop")->GetIntRef();
    auto& m_nInSequenceNr = thisptr[4];
    auto m_nInSequenceNr_before = m_nInSequenceNr;
    auto ret = CNetChan_ProcessPacketHeader_org(thisptr, packet);
    if (net_showdrop)
    {
        auto* remote_address = (netadr_t*)(((__int64)thisptr) + 228);
        static auto netadr_t_ToString = (char*(__fastcall*)(netadr_t* thisptr, bool baseOnly))(Util::GetModuleBaseAddress("engine.dll") + 0x4885B0);
        if (ret == 0xFFFFFFFFi64) [[unlikely]]
        {
            // actually gotta read sequence nr from raw packet, since sequence number won't be set in object if the func returned early with -1
            //auto sequence = *(int*)(packet->data);
            //auto sequence = *(int*)((size_t)packet + 0x28); // offset should be correct, but raw packet data is probably encrypted......
            // ^ too lazy to wrap bf_read for now...
            // it can also earlier return -1 due to back checksum, but packet checksumming enablement is hardcoded to 0
            //spdlog::info("ret = -1, m_nInSequenceNr={}, m_nInSequenceNr_before={}, sequence={}", m_nInSequenceNr, m_nInSequenceNr_before, sequence);
            /*if (sequence <= m_nInSequenceNr_before)
            {
                spdlog::info("{}:{} packet {} at {}", netadr_t_ToString(remote_address, 0),
                    sequence == m_nInSequenceNr_before ? "duplicate" : "out of order",
                    sequence, m_nInSequenceNr_before);
            }*/
            spdlog::info("{}:duplicate or out of order packet after {}", netadr_t_ToString(remote_address, 0), m_nInSequenceNr_before);
        }
        else
        {
            auto sequence = m_nInSequenceNr; // read it from current object, since it was set at the end of the func to the value read from packet
            auto& m_PacketDrop = thisptr[4009]; // m_PacketDrop = sequence - (m_nInSequenceNr_before + nChoked + 1);
            if (m_PacketDrop > 0) [[unlikely]]
            {
                spdlog::info("{}:Dropped {} packets at {}", netadr_t_ToString(remote_address, 0), m_PacketDrop, sequence);
            }
        }
    }
    auto& m_PacketDrop = thisptr[4009];
    if (ret == 0xFFFFFFFFi64 || m_PacketDrop > 0) [[unlikely]]
        g_droppedPacketFlag = true;
    return ret;
}

typedef _QWORD*(__fastcall* sub_18017E140_type)(_QWORD*, __int64, char*);
sub_18017E140_type sub_18017E140_org;
_QWORD* __fastcall sub_18017E140(_QWORD* a1, __int64 a2, char* a3)
{
    auto ret = sub_18017E140_org(a1, a2, a3);
    *(bool*)(a1[77] + 1011) = true; // enable Unicode input in CBaseHudChatEntry
    return ret;
}

typedef void(__fastcall* CL_Move_type)(size_t, bool);
CL_Move_type CL_Move_org;
void __fastcall CL_Move(size_t unk, bool bFinalTick)
{
    CL_Move_org(unk, bFinalTick);

    auto cl = get_cl();
    unsigned int& baseLocalClient__m_nSignonState = *((_DWORD*)cl + 29);
    double& cl_m_dblNextCmdTime = *((double*)cl + 15);
    static double& net_time = *(double*)(Util::GetModuleBaseAddress("engine.dll") + 0x30EF1C0);
    static auto& move_one_cmd_per_client_frame = SDK().GetVstdlibCvar()->FindVar("move_one_cmd_per_client_frame")->GetIntRef();
    static auto& cl_nocmdrate = SDK().GetVstdlibCvar()->FindVar("cl_nocmdrate")->GetIntRef();

    bool cl_isActive = baseLocalClient__m_nSignonState == 8;
    if (cl_isActive && move_one_cmd_per_client_frame && cl_nocmdrate)
        cl_m_dblNextCmdTime = net_time - DBL_EPSILON;
}

typedef __int64(__fastcall* COM_ExplainDisconnection_TYPE)(bool a1, const char* fmt, ...);
COM_ExplainDisconnection_TYPE COM_ExplainDisconnection_org;
__int64 __fastcall COM_ExplainDisconnection(bool a1, const char* fmt, ...)
{
    std::stringstream ss;
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsprintf_s(buffer, fmt, args);
    va_end(args);

    ss << "COM_ExplainDisconnection: " << (char*)buffer;
    spdlog::info(ss.str().c_str());
    return COM_ExplainDisconnection_org(a1, buffer);
}

typedef void(__fastcall* Tier0_ThreadSetDebugName_type)(HANDLE, const char*);
Tier0_ThreadSetDebugName_type Tier0_ThreadSetDebugName_org = nullptr;
void __fastcall Tier0_ThreadSetDebugName(HANDLE threadHandle, const char* name)
{
    if (!name) return;
    std::string newName{ "[R1] " };
    newName += name;

    // below might block as it will wait for internal Source's map!
    static auto LookupThreadIDFromHandle = reinterpret_cast<unsigned int(__fastcall*)(HANDLE)>(Util::GetModuleBaseAddress("tier0.dll") + 0x12520);

    auto currentThread = GetCurrentThread();

    if (threadHandle == 0 || threadHandle == currentThread)
        spdlog::info("Thread: {}", newName);
    else
    {
        uint64_t threadID = LookupThreadIDFromHandle(threadHandle);
        spdlog::info("Thread {}: {}", threadID, newName);
    }

    if (Tier0_ThreadSetDebugName_org) // we call this func to name the main thread before this hook is ready
        Tier0_ThreadSetDebugName_org(threadHandle, newName.c_str()); // original sets name only for debugger, if it's attached

    extern HRESULT _SetThreadDescription(HANDLE hThread, PCWSTR lpThreadDescription);
    _SetThreadDescription(threadHandle == 0 ? currentThread : threadHandle, Util::Widen(newName).c_str());
}

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
    CreateMiscHook(enginedllBaseAddress, 0x22610, &sub_180022610, reinterpret_cast<LPVOID*>(&sub_180022610_org));
    ////CreateMiscHook(enginedllBaseAddress, 0x1F6B90, &INetMessage_WriteToBuffer, reinterpret_cast<LPVOID*>(&INetMessage_WriteToBuffer_org));
    ////CreateMiscHook(enginedllBaseAddress, 0x1F6C20, &ReadUBitLong_probably_for_netmsg_type_6bits__sub_1801F6C20, reinterpret_cast<LPVOID*>(&ReadUBitLong_probably_for_netmsg_type_6bits__sub_1801F6C20_org));
    CreateMiscHook(enginedllBaseAddress, 0x22C70, &CBaseClientState_ConnectionCrashed, reinterpret_cast<LPVOID*>(&CBaseClientState_ConnectionCrashed_org));
    CreateMiscHook(enginedllBaseAddress, 0x34390, &Con_NXPrintf, reinterpret_cast<LPVOID*>(&Con_NXPrintf_org));
    CreateMiscHook(enginedllBaseAddress, 0x1E73C0, &CNetChan_ProcessPacketHeader, reinterpret_cast<LPVOID*>(&CNetChan_ProcessPacketHeader_org));
    CreateMiscHook(clientdllBaseAddress, 0x17E140, &sub_18017E140, reinterpret_cast<LPVOID*>(&sub_18017E140_org));
    CreateMiscHook(enginedllBaseAddress, 0x59DE0, &CL_Move, reinterpret_cast<LPVOID*>(&CL_Move_org));
    CreateMiscHook(enginedllBaseAddress, 0x117240, &COM_ExplainDisconnection, reinterpret_cast<LPVOID*>(&COM_ExplainDisconnection_org));
    CreateMiscHookNamed("tier0", "ThreadSetDebugName", &Tier0_ThreadSetDebugName, reinterpret_cast<LPVOID*>(&Tier0_ThreadSetDebugName_org));
}

void DoBinaryPatches()
{
    { // patch the restriction "Can't send client command; not connected to a server" of ClientCommand in script
        void* ptr = (void*)(Util::GetModuleBaseAddress("client.dll") + 0x2DB33B);
        TempReadWrite rw(ptr);
        *((unsigned char*)ptr) = 0xEB;
    }

//#if 0
    { // FOV range patch
        void* ptr = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x6C6D34);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f; // will work only before cvar is registered
    }
    { // FOV range patch 2
        void* ptr = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x31A1BE0 + 108);
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
        void* ptr = (void*)(Util::GetModuleBaseAddress("client.dll") + 0x38774C0 + 108);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f;
    }
    { // FOV range patch
        void* ptr = (void*)(Util::GetModuleBaseAddress("materialsystem_dx11.dll") + 0x191734);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f; // will work only before cvar is registered
    }
    { // FOV range patch 2
        void* ptr = (void*)(Util::GetModuleBaseAddress("materialsystem_dx11.dll") + 0x3B9560 + 108);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f;
    }
    { // FOV range patch in client.dll
        void* ptr = (void*)(Util::GetModuleBaseAddress("client.dll") + 0x7F9844);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f;
    }
    { // m_sensitivity range patch (remove minimal value)
        void* ptr = (void*)(Util::GetModuleBaseAddress("client.dll") + 0xF87E50 + 100);
        TempReadWrite rw(ptr);
        *((float*)ptr) = FLT_EPSILON;
    }
    { // fps_max non-devonly
        void* ptr = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x30EBF90 + 40);
        TempReadWrite rw(ptr);
        *((uint32_t*)ptr) &= ~FCVAR_DEVELOPMENTONLY;
    }
    {
        void* ptr = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x634CC0);
        TempReadWrite rw(ptr);
        *((double*)ptr) = 1000.0; // override max value of fps_max (default was 144.0)
    }
    {
        void* ptr = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x634CC8);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 1000.0f; // override max value of fps_max (default was 144.0)
    }
//#endif

    { // isMMDev
        void* ptr = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x229155A);
        TempReadWrite rw(ptr);
        *((bool*)ptr) = true;
    }
    { // retn here so we don't break the above accidentally
        void* ptr = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x57740);
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
    { // client received net message - use ToString rather than GetName
        void* ptr = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x1E559A);
        TempReadWrite rw(ptr);
        *(unsigned char*)ptr = 0x60;
    }
    { // SecurityPatch: prevent server plugin DLL loading
        void* ptr = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0xF3F40);
        TempReadWrite rw(ptr);
        *((unsigned char*)ptr) = 0x32;
        *(unsigned char*)((uint64_t)ptr + 1) = 0xC0;
        *(unsigned char*)((uint64_t)ptr + 2) = 0xC3;
    }
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
    Util::ThreadSetDebugName("MainThread");
    SetupLogger();

    if (strstr(GetCommandLineA(), "-nocrashhandler")) // CommandLine() not yet ready probably
        spdlog::info("Sentry not starting due to -nocrashhandler");
    else
    {
        auto wasCrashHandlerStarted = SetupCrashHandler(GetThisPathWide());
        spdlog::info("Sentry was{}started", wasCrashHandlerStarted ? " " : " not ");
    }

    curl_global_init_mem(CURL_GLOBAL_DEFAULT, internal_malloc, internal_free, internal_realloc, internal_strdup, internal_calloc);

    SPDLOG_DEBUG("DoBinaryPatches");
    DoBinaryPatches();

    {
        SPDLOG_DEBUG("MH_Initialize"); 
        if (MH_Initialize() != MH_OK)
        {
            spdlog::error("MH_Initialize error");
            return;
        }

        SPDLOG_DEBUG("DoMiscHooks");
        DoMiscHooks();

        if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        {
            spdlog::error("MH_EnableHook error");
            return;
        }

    }

    SPDLOG_DEBUG("Preinit code end");

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