// dllmain.cpp : Definiuje punkt wejścia dla aplikacji DLL.
#include "pch.h"
#include "tier0.h"
#include "Memory.h"
#include "TTFSDK.h"
#include "CrashReporting.h"
#include "Updater.h"
#include "Chat.h"

HANDLE threadHandle;
std::chrono::system_clock::time_point g_startTime;

extern FuncStaticWithType<void* (__cdecl*)()> get_cl;

extern "C"
{
	uintptr_t g_CNetChan__ProcessSubChannelData_gadget_ret0 = 0;
	uintptr_t g_CNetChan__ProcessSubChannelData_AsmConductBufferSizeCheck_continue = 0;
	extern uintptr_t CNetChan__ProcessSubChannelData_AsmConductBufferSizeCheck;
}

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
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsprintf_s(buffer, fmt, args);
    va_end(args);

    spdlog::info("COM_ExplainDisconnection: {}", buffer);
    return COM_ExplainDisconnection_org(a1, buffer);
}

typedef __int64(__fastcall* Host_Disconnect_TYPE)(bool bShowMainMenu);
Host_Disconnect_TYPE Host_Disconnect_org;
__int64 __fastcall Host_Disconnect(bool bShowMainMenu)
{
    if (bShowMainMenu) Updater::CheckForUpdates();
    return Host_Disconnect_org(bShowMainMenu);
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

typedef void(__fastcall* sub_18000BAC0_type)(float*, __int64, __int64);
sub_18000BAC0_type sub_18000BAC0_org = nullptr;
void __fastcall sub_18000BAC0(float* a1, __int64 a2, __int64 a3)
{
    static auto& hudwarp_disable = SDK().GetVstdlibCvar()->FindVar("hudwarp_disable")->GetIntRef();
    if (hudwarp_disable)
        return;
    sub_18000BAC0_org(a1, a2, a3);
}

typedef void(__fastcall* SQInstance_Finalize_type)(uintptr_t);
SQInstance_Finalize_type SQInstance_Finalize_org = nullptr;
void SQInstance_Finalize(uintptr_t thisptr)
{
    if (*(uintptr_t*)(thisptr + 56) == 0)
    {
        // Kinda weird that this ever happened, but it sometimes caused crashes at the end of the game.
        // Looks like normally SQInstance destructor would check for if(_class) first before calling this,
        // however ->Finalize() may be called on objects during shared state destruction or garbage collection
        // without that check conducted.
        spdlog::warn("Called SQInstance::Finalize, but _class was null! Returning to prevent game crash.");
        return;
    }
    SQInstance_Finalize_org(thisptr);
}

inline bool IsMemoryReadable(void* ptr, size_t size, DWORD protect_required_flags_oneof)
{
    static SYSTEM_INFO sysInfo;
    if (!sysInfo.dwPageSize)
        GetSystemInfo(&sysInfo);

    MEMORY_BASIC_INFORMATION memInfo;

    if (!VirtualQuery(ptr, &memInfo, sizeof(memInfo)))
        return false;

    if (memInfo.RegionSize < size)
        return false;

    return (memInfo.State & MEM_COMMIT) && !(memInfo.Protect & PAGE_NOACCESS) && (memInfo.Protect & protect_required_flags_oneof) != 0;
}

typedef void(__fastcall* sub_180100880_type)(uintptr_t);
sub_180100880_type sub_180100880_org = nullptr;
void __fastcall sub_180100880(uintptr_t a1) // we fix seldom crash in vphysics on level shutdown (but most frequent crash to be reported)
{
    auto cl = get_cl();
    unsigned int& baseLocalClient__m_nSignonState = *((_DWORD*)cl + 29);
    bool cl_isActive = baseLocalClient__m_nSignonState == 8;

    // We just rebuild the function
    static auto* sub_1800FFB50 = reinterpret_cast<__int64(*)(uintptr_t)>(Util::GetModuleBaseAddress("vphysics.dll") + 0xFFB50);
    static auto* sub_1800FF010 = reinterpret_cast<__int64(*)(uintptr_t)>(Util::GetModuleBaseAddress("vphysics.dll") + 0xFF010);
    static auto* sub_1800CA0B0 = reinterpret_cast<__int64(*)(uintptr_t)>(Util::GetModuleBaseAddress("vphysics.dll") + 0xCA0B0);
    bool do_check = !cl_isActive; // it only seems to happen during level shutdown, so conduct checks only then (but this seems redundant since this func doesn't seem to be called at other times)

    void(__fastcall * **v2)(_QWORD, __int64); // rcx
    __int64 v3; // rcx

    spdlog::debug("[sub_180100880] Before func");
    sub_1800FFB50(a1);
    sub_1800FF010(a1);
    spdlog::debug("[sub_180100880] Before problematic loop");
    int i = 0;
    while (*(__int16*)(a1 + 1310866)) // apparently the loop usually doesn't run at all????? (is there a chance it's always to crash if ran?)
    {
        i++;
        v2 = **(void(__fastcall*****)(_QWORD, __int64))(a1 + 1310872);
        if (v2)
        {
            if (*v2 && **v2) // should always be true by practice, but **v2 may already be freed
            {
                if (do_check)
                {
                    if (!IsMemoryReadable(**v2, 8, PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY))
                    {
                        spdlog::warn("[sub_180100880] Trying to prevent vphysics crash by breaking out of the loop now, possible side effects unknown!");
                        Chat::showChatLineEasy("\n[BME] ", 0xFFFF00FF);
                        Chat::showChatLineEasy("Trying to prevent vphysics crash. Go poke p0358 if the game still crashes on next map load and send the log file!", 0xFFFFFFFF);
                        break;
                    }
                    else spdlog::debug("[sub_180100880] All good");
                }
                else spdlog::debug("[sub_180100880] Not doing the check???");
                (**v2)((_QWORD)v2, 1i64); // this call likes to crash :)
            }
        }
    }
    spdlog::debug("[sub_180100880] After problematic loop, ran it {} times", i);
    v3 = *(_QWORD*)(a1 + 1310872);
    if (v3 != a1 + 1310880)
    {
        if (v3)
            sub_1800CA0B0(v3);
        *(_QWORD*)(a1 + 1310872) = 0i64;
        *(__int16*)(a1 + 1310864) = 0;
    }
    *(__int16*)(a1 + 1310866) = 0;
    DeleteCriticalSection((LPCRITICAL_SECTION)(a1 + 8));
    spdlog::debug("[sub_180100880] After func");
}

typedef void*(__fastcall* CEngineAPI__Run_type)(void*);
CEngineAPI__Run_type CEngineAPI__Run_org = nullptr;
void* __fastcall CEngineAPI__Run(void* a1)
{
    // try-catch block is commented out, since while it would catch the exception with message
    // successfully, it wouldn't preserve the stack trace; instead, we'll simply let
    // the unhandled exception handler handle it instead
    //try
    //{
        auto* CEngineAPI__RunListenServer = reinterpret_cast<void*(__fastcall*)(void*)>(Util::GetModuleBaseAddress("engine.dll") + 0x1A0DE0);
        return CEngineAPI__RunListenServer(a1);
    //}
    //catch (...)
    //{
    //    spdlog::info("oy vey");
    //    throw;
    //}
}

void DoMiscHooks()
{
    DWORD64 launcherdllBaseAddress = Util::GetModuleBaseAddress("launcher.org.dll");
    if (!launcherdllBaseAddress) launcherdllBaseAddress = Util::GetModuleBaseAddress("launcher.dll");
    DWORD64 clientdllBaseAddress = Util::GetModuleBaseAddress("client.dll");
    DWORD64 enginedllBaseAddress = Util::GetModuleBaseAddress("engine.dll");
    DWORD64 vguimatsurfacedllBaseAddress = Util::GetModuleBaseAddress("vguimatsurface.dll");
    DWORD64 vphysicsdllBaseAddress = Util::GetModuleBaseAddress("vphysics.dll");
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
    CreateMiscHook(enginedllBaseAddress, 0x137160, &Host_Disconnect, reinterpret_cast<LPVOID*>(&Host_Disconnect_org));
    CreateMiscHookNamed("tier0", "ThreadSetDebugName", &Tier0_ThreadSetDebugName, reinterpret_cast<LPVOID*>(&Tier0_ThreadSetDebugName_org));
    CreateMiscHook(vguimatsurfacedllBaseAddress, 0xBAC0, &sub_18000BAC0, reinterpret_cast<LPVOID*>(&sub_18000BAC0_org));
    CreateMiscHook(launcherdllBaseAddress, 0x4D6D0, &SQInstance_Finalize, reinterpret_cast<LPVOID*>(&SQInstance_Finalize_org));
    CreateMiscHook(vphysicsdllBaseAddress, 0x100880, &sub_180100880, reinterpret_cast<LPVOID*>(&sub_180100880_org));
    CreateMiscHook(enginedllBaseAddress, 0x1A0F70, &CEngineAPI__Run, reinterpret_cast<LPVOID*>(&CEngineAPI__Run_org));
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
        //void* ptr = (void*)(*((unsigned __int64*)(Util::GetModuleBaseAddress("engine.dll") + 0x31A1BE0)) + 108);
        TempReadWrite rw(ptr);
        *((float*)ptr) = 3.85f;
    }
    { // FOV range patch
        void* ptr = (void*)(Util::GetModuleBaseAddress("client.dll") + 0x9CDB74);
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
    { // hudwarp_chopsize set minimum value to 120 (partially mitigates a huge performance issue of this game)
        // to mitigate if fully, use the new BME cvar hudwarp_disable 1
        char* ptr = (char*)(Util::GetModuleBaseAddress("vguimatsurface.dll") + 0x1EDF30);
        TempReadWrite rw(ptr);
        *((float*)(ptr + 100)) = 120.0f; // min (but doesn't seem to work?!)
        *((uint32_t*)(ptr + 40)) &= ~FCVAR_CHEAT; // flags
        ((ConVar*)ptr)->SetValueInt(120);
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
        void* ptr = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x19C516);
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
    { // SecurityPatch: ret in mat_crosshair_edit_command_callback // https://hackerone.com/reports/544096
        void* ptr = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x9D5B0);
        TempReadWrite rw(ptr);
        *((unsigned char*)ptr) = 0xC3;
    }
    { // SecurityPatch: do not use default XInput 1.3 due to no ASLR
        void* ptr = (void*)(Util::GetModuleBaseAddress("inputsystem.dll") + 0x41F50);
        TempReadWrite rw(ptr);
        strcpy_s((char*)ptr, 16, "XInput9_1_0.dll");
    }
    { // SecurityPatch: have net_writeStatsFile always write to net_stats.txt instead of arbitrary file
        void* ptr = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x130843);
        TempReadWrite rw(ptr);
        *((unsigned char*)ptr) = 0x90;
        *(unsigned char*)((uint64_t)ptr + 1) = 0x90;
    }
    { // SecurityPatch: stack smash in CNetChan::ProcessSubChannelData (possible RCE)
        // This fixes a stack smash in `CNetChan::ProcessSubChannelData` caused by the last fragment
        // of a reliable subchannel transmission, which could exceed the stack allocated buffer size of 592 bytes.
        // Reference: https://github.com/Mauler125/r5sdk/commit/94ae3e58ce980cc426f7e08a6da1cb366bcd79b6
        // Reference: https://github.com/TFORevive/tforevive_cpp/commit/c91d7c336d2a0b2ffe72642c3c959adb9eb956c5
        g_CNetChan__ProcessSubChannelData_gadget_ret0 = (uintptr_t)(Util::GetModuleBaseAddress("engine.dll") + 0x1E8F26); // responsible for returning 0 from func
        g_CNetChan__ProcessSubChannelData_AsmConductBufferSizeCheck_continue = (uintptr_t)(Util::GetModuleBaseAddress("engine.dll") + 0x1E8DDA); // where normal execution continues if buffer size is ok
        void* algn = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x1EA961); // Some align after CNetChan::ProcessSubChannelData, size 15
        // Above call to `bf_read::ReadBytes` there's a call to nullsub_87, which we replace to a jump to code align after the function.
        // In the code align we perform a long jump to our helper assembly function `CNetChan__ProcessSubChannelData_AsmConductBufferSizeCheck`,
        // which conducts the buffer size check. If it passes, we jump back to the old place to continue execution from the call to `bf_read::ReadBytes`,
        // otherwise we jump to the place which makes the function return 0 instead, indicating read failure.

        // Turn `call nullsub_87` into a jmp to our algn (both original call and our jmp patch have the exact same byte length)
        auto* jmp_pos = (void*)(Util::GetModuleBaseAddress("engine.dll") + 0x1E8DD5); // `call nullsub_87` offset
        // 0xE9, 0x87, 0x1B, 0x00, 0x00 // jmp 0x1b8c (algn_1801EA961)  (0x1EA961 - 0x1E8DD5)
        TempReadWrite rw(jmp_pos);
        *((unsigned char*)jmp_pos) = 0xE9;
        *(unsigned char*)((uint64_t)jmp_pos + 1) = 0x87;
        *(unsigned char*)((uint64_t)jmp_pos + 2) = 0x1B;
        *(unsigned char*)((uint64_t)jmp_pos + 3) = 0x00;
        *(unsigned char*)((uint64_t)jmp_pos + 4) = 0x00;

        //algn.Patch({ 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00 }); // this instruction does far jump to rip+0, which means the 8 bytes placed exactly after this instruction
        //algn.Offset(6).Patch<uintptr_t>((uintptr_t)&CNetChan__ProcessSubChannelData_AsmConductBufferSizeCheck); // address to be used by the above, disassemblers may be confused about these bytes, but it does not matter
        *((unsigned char*)algn) = 0xFF;
        *(unsigned char*)((uint64_t)algn + 1) = 0x25;
        *(unsigned char*)((uint64_t)algn + 2) = 0x00;
        *(unsigned char*)((uint64_t)algn + 3) = 0x00;
        *(unsigned char*)((uint64_t)algn + 4) = 0x00;
        *(unsigned char*)((uint64_t)algn + 5) = 0x00;
        *(uintptr_t**)((uint64_t)algn + 6) = &CNetChan__ProcessSubChannelData_AsmConductBufferSizeCheck;
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

        extern void Setup_MMNotificationClient();
        Setup_MMNotificationClient();

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
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" _declspec(dllexport) void Init()
{
    main();
}