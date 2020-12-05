#include "pch.h"
#include "TTFSDK.h"
#include "Chat.h"

void Chat::showChatLineEasy(const char* str, unsigned int color)
{
    typedef char(__fastcall* TESTFN) (__int64 a1, const char* a2, int a3, int a41);
    //sub_1806CBB40(__int64 a1, const char *a2, int a3, int a4)

    static DWORD64 clientdllBaseAddress;
    if (!clientdllBaseAddress) clientdllBaseAddress = Util::GetModuleBaseAddress("client.dll");

    __int64 i;
    __int64 qword_180F808C8 = *(__int64*)(clientdllBaseAddress + 0xF808C8);

    TESTFN sub_1806CBB40 = (TESTFN)(clientdllBaseAddress + 0x6CBB40);

    for (i = qword_180F808C8; i; i = *(unsigned __int64*)(i + 752))
        sub_1806CBB40(*(unsigned __int64*)(i + 744), str, color, color);

}

void Chat::showChatLineAsPlayer(int playerSlot, const char* str, bool isTeam, double xmm0_8_0) {
    typedef __int64 (/*__usercall*/ *TEST2FN) (__int64 a1, const CHAR* text, unsigned int playerSlot, char isTeam, double xmm0_8_0, char isDead);
    //__int64 __usercall sub_18017D440@<rax>(__int64 a1@<rcx>, const CHAR *text@<rdx>, unsigned int playerSlot@<r8d>, char isTeam@<r9b>, double xmm0_8_0@<xmm0>, char isDead)
    
    static DWORD64 clientdllBaseAddress;
    if (!clientdllBaseAddress) clientdllBaseAddress = Util::GetModuleBaseAddress("client.dll");

    __int64 i;
    __int64 qword_180F808C8 = *(__int64*)(clientdllBaseAddress + 0xF808C8);

    TEST2FN sub_18017D440 = (TEST2FN)(clientdllBaseAddress + 0x17D440);

    for (i = qword_180F808C8; i; i = *(unsigned __int64*)(i + 752)) {
        //result = sub_18017D440(i, &szString, playerSlot, isTeam, a2, isDead); // dead is not visible at all
        //sub_18017D440(i, str, playerSlot, isTeam, 0.0, 0);
        sub_18017D440(i, str, playerSlot, isTeam, xmm0_8_0, 0);
    }
}
