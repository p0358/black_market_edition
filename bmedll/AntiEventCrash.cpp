#include "pch.h"
#include "SigScanning.h"
#include "TTFSDK.h"
#include "Chat.h"

/*class AntiEventCrash {

};*/

HookedFuncStatic<char __fastcall, __int64, __int64, __int64, __int64> ProcessMessages("engine.dll", 0x1E51D0);
HookedFuncStatic<__int64 __fastcall, __int64> GameEvent_Process("engine.dll", 0x25080);
SigScanFunc<__int64 __fastcall, __int64, __int64> buf_seektobit("engine.dll", "\x48\x89\x5C\x24\x00\x4C\x8B\xD2", "xxxx?xxx"); // 48 89 5C 24 ? 4C 8B D2
//typedef __int64 (__cdecl* __fastcall _buf_seektobit_function)(__int64, __int64);
//typedef __int64 (__fastcall *_buf_seektobit_function)(__int64, __int64);
//SigScanFunc<__int64 __fastcall, _buf_seektobit_function> buf_seektobit("engine.dll", "\x48\x89\x5C\x24\x00\x4C\x8B\xD2", "xxxx?xxx"); // 48 89 5C 24 ? 4C 8B D2

__int64 global_msg_buf;

__int64 __fastcall GameEvent_Process_Hook(__int64 thisptr) {
    //auto orig = reinterpret_cast<decltype(&gameevent_process_detour)>(gameevent_process_func);
    //auto ret = orig(thisptr);
    auto ret = GameEvent_Process(thisptr);

    // CHECKS n FIXES
    //auto datain = /*(BitBuf*)*/(thisptr + 0x28);
    //auto datain_written = datain->get_bits_written();

    auto v3 = (*(DWORD*)(thisptr + 64) & 3) + 4i64 * ((*(unsigned __int64*)(thisptr + 80) - *(unsigned __int64*)(thisptr + 96)) >> 2);
    auto v4 = *(unsigned int*)(thisptr + 76);
    auto datain_written = 8 * v3 - v4;

    auto chanbuf = /*(BitBuf*)*/global_msg_buf;
    //auto chanbuf_written = chanbuf->get_bits_written();
    auto chanbuf_written = 8
        * ((*(DWORD*)(chanbuf + 24i64) & 3)
            + 4i64 * ((*(unsigned __int64*)(chanbuf + 40i64) - *(unsigned __int64*)(chanbuf + 56i64)) >> 2))
        - *(unsigned int*)(chanbuf + 36i64);


    if (datain_written != chanbuf_written) {
        //static auto buf_seektobit = (buf_seektobit_t)signature::find_pattern("engine", "48 89 5C 24 ? 4C 8B D2");
        buf_seektobit(chanbuf, datain_written);// FIXING YAY!!!

        // TODO: check if this doesn't get shown multiple times
        if (*SDK().GetPresence().isConnectedAndInLobby == 1)
        {
            Chat::showChatLineEasy("\n[BME] ", 0xFFFF00FF);
            Chat::showChatLineEasy("A crash was prevented.", 0xFFFFFFFF);
        }
        else if (*SDK().GetPresence().presenceBuffer)
        {
            // TODO: obituary print
        }
    }

    return ret;
}

char __fastcall ProcessMessages_Hook(__int64 thisptr, __int64 buf, __int64 a3, __int64 a4) {
    //auto orig = reinterpret_cast<decltype(&process_messages_detour)>(process_messages_func);

    global_msg_buf = buf;

    return ProcessMessages(thisptr, buf, a3, a4);
}

void AntiEventCrash_Setup()
{
    ProcessMessages.Hook(ProcessMessages_Hook);
    GameEvent_Process.Hook(GameEvent_Process_Hook);
}
