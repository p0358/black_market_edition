#include "pch.h"
#include <windows.h>
#include <string>

HINSTANCE hLThis = 0;
//FARPROC p[180];
UINT64 p[180];
HINSTANCE hL = 0;

void loadOriginalLibrary() {
	WCHAR path[MAX_PATH];

	//std::wstringstream ss;
	//ss << 
	//RtlCopyMemory(path + GetSystemDirectoryW(path, MAX_PATH - 13), L"\\winmm.dll\0", 21);
	wmemcpy(path + GetSystemDirectoryW(path, MAX_PATH - 13), L"\\winmm.dll", 11);
	//RtlUnicodeStringCopy(path + GetSystemDirectoryW(path, MAX_PATH - 13), L"\\winmm.dll\0", 21);
	hL = LoadLibraryW(path);
	if (!hL)
	{
		MessageBoxA(0, "Cannot load original winmm.dll library", "Proxy", MB_ICONERROR);
		MessageBoxW(0, path, L"Proxy", MB_ICONERROR);
		ExitProcess(0);
	}

	p[0] = (UINT64)GetProcAddress(hL, "CloseDriver");
	p[1] = (UINT64)GetProcAddress(hL, "DefDriverProc");
	p[2] = (UINT64)GetProcAddress(hL, "DriverCallback");
	p[3] = (UINT64)GetProcAddress(hL, "DrvGetModuleHandle");
	p[4] = (UINT64)GetProcAddress(hL, "GetDriverModuleHandle");
	p[5] = (UINT64)GetProcAddress(hL, "OpenDriver");
	p[6] = (UINT64)GetProcAddress(hL, "PlaySound");
	p[7] = (UINT64)GetProcAddress(hL, "PlaySoundA");
	p[8] = (UINT64)GetProcAddress(hL, "PlaySoundW");
	p[9] = (UINT64)GetProcAddress(hL, "SendDriverMessage");
	p[10] = (UINT64)GetProcAddress(hL, "WOWAppExit");
	p[11] = (UINT64)GetProcAddress(hL, "auxGetDevCapsA");
	p[12] = (UINT64)GetProcAddress(hL, "auxGetDevCapsW");
	p[13] = (UINT64)GetProcAddress(hL, "auxGetNumDevs");
	p[14] = (UINT64)GetProcAddress(hL, "auxGetVolume");
	p[15] = (UINT64)GetProcAddress(hL, "auxOutMessage");
	p[16] = (UINT64)GetProcAddress(hL, "auxSetVolume");
	p[17] = (UINT64)GetProcAddress(hL, "joyConfigChanged");
	p[18] = (UINT64)GetProcAddress(hL, "joyGetDevCapsA");
	p[19] = (UINT64)GetProcAddress(hL, "joyGetDevCapsW");
	p[20] = (UINT64)GetProcAddress(hL, "joyGetNumDevs");
	p[21] = (UINT64)GetProcAddress(hL, "joyGetPos");
	p[22] = (UINT64)GetProcAddress(hL, "joyGetPosEx");
	p[23] = (UINT64)GetProcAddress(hL, "joyGetThreshold");
	p[24] = (UINT64)GetProcAddress(hL, "joyReleaseCapture");
	p[25] = (UINT64)GetProcAddress(hL, "joySetCapture");
	p[26] = (UINT64)GetProcAddress(hL, "joySetThreshold");
	p[27] = (UINT64)GetProcAddress(hL, "mciDriverNotify");
	p[28] = (UINT64)GetProcAddress(hL, "mciDriverYield");
	p[29] = (UINT64)GetProcAddress(hL, "mciExecute");
	p[30] = (UINT64)GetProcAddress(hL, "mciFreeCommandResource");
	p[31] = (UINT64)GetProcAddress(hL, "mciGetCreatorTask");
	p[32] = (UINT64)GetProcAddress(hL, "mciGetDeviceIDA");
	p[33] = (UINT64)GetProcAddress(hL, "mciGetDeviceIDFromElementIDA");
	p[34] = (UINT64)GetProcAddress(hL, "mciGetDeviceIDFromElementIDW");
	p[35] = (UINT64)GetProcAddress(hL, "mciGetDeviceIDW");
	p[36] = (UINT64)GetProcAddress(hL, "mciGetDriverData");
	p[37] = (UINT64)GetProcAddress(hL, "mciGetErrorStringA");
	p[38] = (UINT64)GetProcAddress(hL, "mciGetErrorStringW");
	p[39] = (UINT64)GetProcAddress(hL, "mciGetYieldProc");
	p[40] = (UINT64)GetProcAddress(hL, "mciLoadCommandResource");
	p[41] = (UINT64)GetProcAddress(hL, "mciSendCommandA");
	p[42] = (UINT64)GetProcAddress(hL, "mciSendCommandW");
	p[43] = (UINT64)GetProcAddress(hL, "mciSendStringA");
	p[44] = (UINT64)GetProcAddress(hL, "mciSendStringW");
	p[45] = (UINT64)GetProcAddress(hL, "mciSetDriverData");
	p[46] = (UINT64)GetProcAddress(hL, "mciSetYieldProc");
	p[47] = (UINT64)GetProcAddress(hL, "midiConnect");
	p[48] = (UINT64)GetProcAddress(hL, "midiDisconnect");
	p[49] = (UINT64)GetProcAddress(hL, "midiInAddBuffer");
	p[50] = (UINT64)GetProcAddress(hL, "midiInClose");
	p[51] = (UINT64)GetProcAddress(hL, "midiInGetDevCapsA");
	p[52] = (UINT64)GetProcAddress(hL, "midiInGetDevCapsW");
	p[53] = (UINT64)GetProcAddress(hL, "midiInGetErrorTextA");
	p[54] = (UINT64)GetProcAddress(hL, "midiInGetErrorTextW");
	p[55] = (UINT64)GetProcAddress(hL, "midiInGetID");
	p[56] = (UINT64)GetProcAddress(hL, "midiInGetNumDevs");
	p[57] = (UINT64)GetProcAddress(hL, "midiInMessage");
	p[58] = (UINT64)GetProcAddress(hL, "midiInOpen");
	p[59] = (UINT64)GetProcAddress(hL, "midiInPrepareHeader");
	p[60] = (UINT64)GetProcAddress(hL, "midiInReset");
	p[61] = (UINT64)GetProcAddress(hL, "midiInStart");
	p[62] = (UINT64)GetProcAddress(hL, "midiInStop");
	p[63] = (UINT64)GetProcAddress(hL, "midiInUnprepareHeader");
	p[64] = (UINT64)GetProcAddress(hL, "midiOutCacheDrumPatches");
	p[65] = (UINT64)GetProcAddress(hL, "midiOutCachePatches");
	p[66] = (UINT64)GetProcAddress(hL, "midiOutClose");
	p[67] = (UINT64)GetProcAddress(hL, "midiOutGetDevCapsA");
	p[68] = (UINT64)GetProcAddress(hL, "midiOutGetDevCapsW");
	p[69] = (UINT64)GetProcAddress(hL, "midiOutGetErrorTextA");
	p[70] = (UINT64)GetProcAddress(hL, "midiOutGetErrorTextW");
	p[71] = (UINT64)GetProcAddress(hL, "midiOutGetID");
	p[72] = (UINT64)GetProcAddress(hL, "midiOutGetNumDevs");
	p[73] = (UINT64)GetProcAddress(hL, "midiOutGetVolume");
	p[74] = (UINT64)GetProcAddress(hL, "midiOutLongMsg");
	p[75] = (UINT64)GetProcAddress(hL, "midiOutMessage");
	p[76] = (UINT64)GetProcAddress(hL, "midiOutOpen");
	p[77] = (UINT64)GetProcAddress(hL, "midiOutPrepareHeader");
	p[78] = (UINT64)GetProcAddress(hL, "midiOutReset");
	p[79] = (UINT64)GetProcAddress(hL, "midiOutSetVolume");
	p[80] = (UINT64)GetProcAddress(hL, "midiOutShortMsg");
	p[81] = (UINT64)GetProcAddress(hL, "midiOutUnprepareHeader");
	p[82] = (UINT64)GetProcAddress(hL, "midiStreamClose");
	p[83] = (UINT64)GetProcAddress(hL, "midiStreamOpen");
	p[84] = (UINT64)GetProcAddress(hL, "midiStreamOut");
	p[85] = (UINT64)GetProcAddress(hL, "midiStreamPause");
	p[86] = (UINT64)GetProcAddress(hL, "midiStreamPosition");
	p[87] = (UINT64)GetProcAddress(hL, "midiStreamProperty");
	p[88] = (UINT64)GetProcAddress(hL, "midiStreamRestart");
	p[89] = (UINT64)GetProcAddress(hL, "midiStreamStop");
	p[90] = (UINT64)GetProcAddress(hL, "mixerClose");
	p[91] = (UINT64)GetProcAddress(hL, "mixerGetControlDetailsA");
	p[92] = (UINT64)GetProcAddress(hL, "mixerGetControlDetailsW");
	p[93] = (UINT64)GetProcAddress(hL, "mixerGetDevCapsA");
	p[94] = (UINT64)GetProcAddress(hL, "mixerGetDevCapsW");
	p[95] = (UINT64)GetProcAddress(hL, "mixerGetID");
	p[96] = (UINT64)GetProcAddress(hL, "mixerGetLineControlsA");
	p[97] = (UINT64)GetProcAddress(hL, "mixerGetLineControlsW");
	p[98] = (UINT64)GetProcAddress(hL, "mixerGetLineInfoA");
	p[99] = (UINT64)GetProcAddress(hL, "mixerGetLineInfoW");
	p[100] = (UINT64)GetProcAddress(hL, "mixerGetNumDevs");
	p[101] = (UINT64)GetProcAddress(hL, "mixerMessage");
	p[102] = (UINT64)GetProcAddress(hL, "mixerOpen");
	p[103] = (UINT64)GetProcAddress(hL, "mixerSetControlDetails");
	p[104] = (UINT64)GetProcAddress(hL, "mmDrvInstall");
	p[105] = (UINT64)GetProcAddress(hL, "mmGetCurrentTask");
	p[106] = (UINT64)GetProcAddress(hL, "mmTaskBlock");
	p[107] = (UINT64)GetProcAddress(hL, "mmTaskCreate");
	p[108] = (UINT64)GetProcAddress(hL, "mmTaskSignal");
	p[109] = (UINT64)GetProcAddress(hL, "mmTaskYield");
	p[110] = (UINT64)GetProcAddress(hL, "mmioAdvance");
	p[111] = (UINT64)GetProcAddress(hL, "mmioAscend");
	p[112] = (UINT64)GetProcAddress(hL, "mmioClose");
	p[113] = (UINT64)GetProcAddress(hL, "mmioCreateChunk");
	p[114] = (UINT64)GetProcAddress(hL, "mmioDescend");
	p[115] = (UINT64)GetProcAddress(hL, "mmioFlush");
	p[116] = (UINT64)GetProcAddress(hL, "mmioGetInfo");
	p[117] = (UINT64)GetProcAddress(hL, "mmioInstallIOProcA");
	p[118] = (UINT64)GetProcAddress(hL, "mmioInstallIOProcW");
	p[119] = (UINT64)GetProcAddress(hL, "mmioOpenA");
	p[120] = (UINT64)GetProcAddress(hL, "mmioOpenW");
	p[121] = (UINT64)GetProcAddress(hL, "mmioRead");
	p[122] = (UINT64)GetProcAddress(hL, "mmioRenameA");
	p[123] = (UINT64)GetProcAddress(hL, "mmioRenameW");
	p[124] = (UINT64)GetProcAddress(hL, "mmioSeek");
	p[125] = (UINT64)GetProcAddress(hL, "mmioSendMessage");
	p[126] = (UINT64)GetProcAddress(hL, "mmioSetBuffer");
	p[127] = (UINT64)GetProcAddress(hL, "mmioSetInfo");
	p[128] = (UINT64)GetProcAddress(hL, "mmioStringToFOURCCA");
	p[129] = (UINT64)GetProcAddress(hL, "mmioStringToFOURCCW");
	p[130] = (UINT64)GetProcAddress(hL, "mmioWrite");
	p[131] = (UINT64)GetProcAddress(hL, "mmsystemGetVersion");
	p[132] = (UINT64)GetProcAddress(hL, "sndPlaySoundA");
	p[133] = (UINT64)GetProcAddress(hL, "sndPlaySoundW");
	p[134] = (UINT64)GetProcAddress(hL, "timeBeginPeriod");
	p[135] = (UINT64)GetProcAddress(hL, "timeEndPeriod");
	p[136] = (UINT64)GetProcAddress(hL, "timeGetDevCaps");
	p[137] = (UINT64)GetProcAddress(hL, "timeGetSystemTime");
	p[138] = (UINT64)GetProcAddress(hL, "timeGetTime");
	p[139] = (UINT64)GetProcAddress(hL, "timeKillEvent");
	p[140] = (UINT64)GetProcAddress(hL, "timeSetEvent");
	p[141] = (UINT64)GetProcAddress(hL, "waveInAddBuffer");
	p[142] = (UINT64)GetProcAddress(hL, "waveInClose");
	p[143] = (UINT64)GetProcAddress(hL, "waveInGetDevCapsA");
	p[144] = (UINT64)GetProcAddress(hL, "waveInGetDevCapsW");
	p[145] = (UINT64)GetProcAddress(hL, "waveInGetErrorTextA");
	p[146] = (UINT64)GetProcAddress(hL, "waveInGetErrorTextW");
	p[147] = (UINT64)GetProcAddress(hL, "waveInGetID");
	p[148] = (UINT64)GetProcAddress(hL, "waveInGetNumDevs");
	p[149] = (UINT64)GetProcAddress(hL, "waveInGetPosition");
	p[150] = (UINT64)GetProcAddress(hL, "waveInMessage");
	p[151] = (UINT64)GetProcAddress(hL, "waveInOpen");
	p[152] = (UINT64)GetProcAddress(hL, "waveInPrepareHeader");
	p[153] = (UINT64)GetProcAddress(hL, "waveInReset");
	p[154] = (UINT64)GetProcAddress(hL, "waveInStart");
	p[155] = (UINT64)GetProcAddress(hL, "waveInStop");
	p[156] = (UINT64)GetProcAddress(hL, "waveInUnprepareHeader");
	p[157] = (UINT64)GetProcAddress(hL, "waveOutBreakLoop");
	p[158] = (UINT64)GetProcAddress(hL, "waveOutClose");
	p[159] = (UINT64)GetProcAddress(hL, "waveOutGetDevCapsA");
	p[160] = (UINT64)GetProcAddress(hL, "waveOutGetDevCapsW");
	p[161] = (UINT64)GetProcAddress(hL, "waveOutGetErrorTextA");
	p[162] = (UINT64)GetProcAddress(hL, "waveOutGetErrorTextW");
	p[163] = (UINT64)GetProcAddress(hL, "waveOutGetID");
	p[164] = (UINT64)GetProcAddress(hL, "waveOutGetNumDevs");
	p[165] = (UINT64)GetProcAddress(hL, "waveOutGetPitch");
	p[166] = (UINT64)GetProcAddress(hL, "waveOutGetPlaybackRate");
	p[167] = (UINT64)GetProcAddress(hL, "waveOutGetPosition");
	p[168] = (UINT64)GetProcAddress(hL, "waveOutGetVolume");
	p[169] = (UINT64)GetProcAddress(hL, "waveOutMessage");
	p[170] = (UINT64)GetProcAddress(hL, "waveOutOpen");
	p[171] = (UINT64)GetProcAddress(hL, "waveOutPause");
	p[172] = (UINT64)GetProcAddress(hL, "waveOutPrepareHeader");
	p[173] = (UINT64)GetProcAddress(hL, "waveOutReset");
	p[174] = (UINT64)GetProcAddress(hL, "waveOutRestart");
	p[175] = (UINT64)GetProcAddress(hL, "waveOutSetPitch");
	p[176] = (UINT64)GetProcAddress(hL, "waveOutSetPlaybackRate");
	p[177] = (UINT64)GetProcAddress(hL, "waveOutSetVolume");
	p[178] = (UINT64)GetProcAddress(hL, "waveOutUnprepareHeader");
	p[179] = (UINT64)GetProcAddress(hL, "waveOutWrite");

	MessageBoxA(0, "Hi", "Proxy", MB_ICONERROR);
}

DWORD WINAPI Start(LPVOID lpParam)
{
	loadOriginalLibrary();
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH: {
			hLThis = hModule;
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Start, 0, 0, 0);
            return TRUE;
        }
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH: {
            FreeLibrary(hL);
            return TRUE;
        }
        break;
    }
    return TRUE;
}

extern "C"
{
	UINT64 PA = NULL;
	int RunASM();

	void PROXY_CloseDriver() {
		PA = p[0];
		RunASM();
	}
	void PROXY_DefDriverProc() {
		PA = p[1];
		RunASM();
	}
	void PROXY_DriverCallback() {
		PA = p[2];
		RunASM();
	}
	void PROXY_DrvGetModuleHandle() {
		PA = p[3];
		RunASM();
	}
	void PROXY_GetDriverModuleHandle() {
		PA = p[4];
		RunASM();
	}
	void PROXY_OpenDriver() {
		PA = p[5];
		RunASM();
	}
	void PROXY_PlaySound() {
		PA = p[6];
		RunASM();
	}
	void PROXY_PlaySoundA() {
		PA = p[7];
		RunASM();
	}
	void PROXY_PlaySoundW() {
		PA = p[8];
		RunASM();
	}
	void PROXY_SendDriverMessage() {
		PA = p[9];
		RunASM();
	}
	void PROXY_WOWAppExit() {
		PA = p[10];
		RunASM();
	}
	void PROXY_auxGetDevCapsA() {
		PA = p[11];
		RunASM();
	}
	void PROXY_auxGetDevCapsW() {
		PA = p[12];
		RunASM();
	}
	void PROXY_auxGetNumDevs() {
		PA = p[13];
		RunASM();
	}
	void PROXY_auxGetVolume() {
		PA = p[14];
		RunASM();
	}
	void PROXY_auxOutMessage() {
		PA = p[15];
		RunASM();
	}
	void PROXY_auxSetVolume() {
		PA = p[16];
		RunASM();
	}
	void PROXY_joyConfigChanged() {
		PA = p[17];
		RunASM();
	}
	void PROXY_joyGetDevCapsA() {
		PA = p[18];
		RunASM();
	}
	void PROXY_joyGetDevCapsW() {
		PA = p[19];
		RunASM();
	}
	void PROXY_joyGetNumDevs() {
		PA = p[20];
		RunASM();
	}
	void PROXY_joyGetPos() {
		PA = p[21];
		RunASM();
	}
	void PROXY_joyGetPosEx() {
		PA = p[22];
		RunASM();
	}
	void PROXY_joyGetThreshold() {
		PA = p[23];
		RunASM();
	}
	void PROXY_joyReleaseCapture() {
		PA = p[24];
		RunASM();
	}
	void PROXY_joySetCapture() {
		PA = p[25];
		RunASM();
	}
	void PROXY_joySetThreshold() {
		PA = p[26];
		RunASM();
	}
	void PROXY_mciDriverNotify() {
		PA = p[27];
		RunASM();
	}
	void PROXY_mciDriverYield() {
		PA = p[28];
		RunASM();
	}
	void PROXY_mciExecute() {
		PA = p[29];
		RunASM();
	}
	void PROXY_mciFreeCommandResource() {
		PA = p[30];
		RunASM();
	}
	void PROXY_mciGetCreatorTask() {
		PA = p[31];
		RunASM();
	}
	void PROXY_mciGetDeviceIDA() {
		PA = p[32];
		RunASM();
	}
	void PROXY_mciGetDeviceIDFromElementIDA() {
		PA = p[33];
		RunASM();
	}
	void PROXY_mciGetDeviceIDFromElementIDW() {
		PA = p[34];
		RunASM();
	}
	void PROXY_mciGetDeviceIDW() {
		PA = p[35];
		RunASM();
	}
	void PROXY_mciGetDriverData() {
		PA = p[36];
		RunASM();
	}
	void PROXY_mciGetErrorStringA() {
		PA = p[37];
		RunASM();
	}
	void PROXY_mciGetErrorStringW() {
		PA = p[38];
		RunASM();
	}
	void PROXY_mciGetYieldProc() {
		PA = p[39];
		RunASM();
	}
	void PROXY_mciLoadCommandResource() {
		PA = p[40];
		RunASM();
	}
	void PROXY_mciSendCommandA() {
		PA = p[41];
		RunASM();
	}
	void PROXY_mciSendCommandW() {
		PA = p[42];
		RunASM();
	}
	void PROXY_mciSendStringA() {
		PA = p[43];
		RunASM();
	}
	void PROXY_mciSendStringW() {
		PA = p[44];
		RunASM();
	}
	void PROXY_mciSetDriverData() {
		PA = p[45];
		RunASM();
	}
	void PROXY_mciSetYieldProc() {
		PA = p[46];
		RunASM();
	}
	void PROXY_midiConnect() {
		PA = p[47];
		RunASM();
	}
	void PROXY_midiDisconnect() {
		PA = p[48];
		RunASM();
	}
	void PROXY_midiInAddBuffer() {
		PA = p[49];
		RunASM();
	}
	void PROXY_midiInClose() {
		PA = p[50];
		RunASM();
	}
	void PROXY_midiInGetDevCapsA() {
		PA = p[51];
		RunASM();
	}
	void PROXY_midiInGetDevCapsW() {
		PA = p[52];
		RunASM();
	}
	void PROXY_midiInGetErrorTextA() {
		PA = p[53];
		RunASM();
	}
	void PROXY_midiInGetErrorTextW() {
		PA = p[54];
		RunASM();
	}
	void PROXY_midiInGetID() {
		PA = p[55];
		RunASM();
	}
	void PROXY_midiInGetNumDevs() {
		PA = p[56];
		RunASM();
	}
	void PROXY_midiInMessage() {
		PA = p[57];
		RunASM();
	}
	void PROXY_midiInOpen() {
		PA = p[58];
		RunASM();
	}
	void PROXY_midiInPrepareHeader() {
		PA = p[59];
		RunASM();
	}
	void PROXY_midiInReset() {
		PA = p[60];
		RunASM();
	}
	void PROXY_midiInStart() {
		PA = p[61];
		RunASM();
	}
	void PROXY_midiInStop() {
		PA = p[62];
		RunASM();
	}
	void PROXY_midiInUnprepareHeader() {
		PA = p[63];
		RunASM();
	}
	void PROXY_midiOutCacheDrumPatches() {
		PA = p[64];
		RunASM();
	}
	void PROXY_midiOutCachePatches() {
		PA = p[65];
		RunASM();
	}
	void PROXY_midiOutClose() {
		PA = p[66];
		RunASM();
	}
	void PROXY_midiOutGetDevCapsA() {
		PA = p[67];
		RunASM();
	}
	void PROXY_midiOutGetDevCapsW() {
		PA = p[68];
		RunASM();
	}
	void PROXY_midiOutGetErrorTextA() {
		PA = p[69];
		RunASM();
	}
	void PROXY_midiOutGetErrorTextW() {
		PA = p[70];
		RunASM();
	}
	void PROXY_midiOutGetID() {
		PA = p[71];
		RunASM();
	}
	void PROXY_midiOutGetNumDevs() {
		PA = p[72];
		RunASM();
	}
	void PROXY_midiOutGetVolume() {
		PA = p[73];
		RunASM();
	}
	void PROXY_midiOutLongMsg() {
		PA = p[74];
		RunASM();
	}
	void PROXY_midiOutMessage() {
		PA = p[75];
		RunASM();
	}
	void PROXY_midiOutOpen() {
		PA = p[76];
		RunASM();
	}
	void PROXY_midiOutPrepareHeader() {
		PA = p[77];
		RunASM();
	}
	void PROXY_midiOutReset() {
		PA = p[78];
		RunASM();
	}
	void PROXY_midiOutSetVolume() {
		PA = p[79];
		RunASM();
	}
	void PROXY_midiOutShortMsg() {
		PA = p[80];
		RunASM();
	}
	void PROXY_midiOutUnprepareHeader() {
		PA = p[81];
		RunASM();
	}
	void PROXY_midiStreamClose() {
		PA = p[82];
		RunASM();
	}
	void PROXY_midiStreamOpen() {
		PA = p[83];
		RunASM();
	}
	void PROXY_midiStreamOut() {
		PA = p[84];
		RunASM();
	}
	void PROXY_midiStreamPause() {
		PA = p[85];
		RunASM();
	}
	void PROXY_midiStreamPosition() {
		PA = p[86];
		RunASM();
	}
	void PROXY_midiStreamProperty() {
		PA = p[87];
		RunASM();
	}
	void PROXY_midiStreamRestart() {
		PA = p[88];
		RunASM();
	}
	void PROXY_midiStreamStop() {
		PA = p[89];
		RunASM();
	}
	void PROXY_mixerClose() {
		PA = p[90];
		RunASM();
	}
	void PROXY_mixerGetControlDetailsA() {
		PA = p[91];
		RunASM();
	}
	void PROXY_mixerGetControlDetailsW() {
		PA = p[92];
		RunASM();
	}
	void PROXY_mixerGetDevCapsA() {
		PA = p[93];
		RunASM();
	}
	void PROXY_mixerGetDevCapsW() {
		PA = p[94];
		RunASM();
	}
	void PROXY_mixerGetID() {
		PA = p[95];
		RunASM();
	}
	void PROXY_mixerGetLineControlsA() {
		PA = p[96];
		RunASM();
	}
	void PROXY_mixerGetLineControlsW() {
		PA = p[97];
		RunASM();
	}
	void PROXY_mixerGetLineInfoA() {
		PA = p[98];
		RunASM();
	}
	void PROXY_mixerGetLineInfoW() {
		PA = p[99];
		RunASM();
	}
	void PROXY_mixerGetNumDevs() {
		PA = p[100];
		RunASM();
	}
	void PROXY_mixerMessage() {
		PA = p[101];
		RunASM();
	}
	void PROXY_mixerOpen() {
		PA = p[102];
		RunASM();
	}
	void PROXY_mixerSetControlDetails() {
		PA = p[103];
		RunASM();
	}
	void PROXY_mmDrvInstall() {
		PA = p[104];
		RunASM();
	}
	void PROXY_mmGetCurrentTask() {
		PA = p[105];
		RunASM();
	}
	void PROXY_mmTaskBlock() {
		PA = p[106];
		RunASM();
	}
	void PROXY_mmTaskCreate() {
		PA = p[107];
		RunASM();
	}
	void PROXY_mmTaskSignal() {
		PA = p[108];
		RunASM();
	}
	void PROXY_mmTaskYield() {
		PA = p[109];
		RunASM();
	}
	void PROXY_mmioAdvance() {
		PA = p[110];
		RunASM();
	}
	void PROXY_mmioAscend() {
		PA = p[111];
		RunASM();
	}
	void PROXY_mmioClose() {
		PA = p[112];
		RunASM();
	}
	void PROXY_mmioCreateChunk() {
		PA = p[113];
		RunASM();
	}
	void PROXY_mmioDescend() {
		PA = p[114];
		RunASM();
	}
	void PROXY_mmioFlush() {
		PA = p[115];
		RunASM();
	}
	void PROXY_mmioGetInfo() {
		PA = p[116];
		RunASM();
	}
	void PROXY_mmioInstallIOProcA() {
		PA = p[117];
		RunASM();
	}
	void PROXY_mmioInstallIOProcW() {
		PA = p[118];
		RunASM();
	}
	void PROXY_mmioOpenA() {
		PA = p[119];
		RunASM();
	}
	void PROXY_mmioOpenW() {
		PA = p[120];
		RunASM();
	}
	void PROXY_mmioRead() {
		PA = p[121];
		RunASM();
	}
	void PROXY_mmioRenameA() {
		PA = p[122];
		RunASM();
	}
	void PROXY_mmioRenameW() {
		PA = p[123];
		RunASM();
	}
	void PROXY_mmioSeek() {
		PA = p[124];
		RunASM();
	}
	void PROXY_mmioSendMessage() {
		PA = p[125];
		RunASM();
	}
	void PROXY_mmioSetBuffer() {
		PA = p[126];
		RunASM();
	}
	void PROXY_mmioSetInfo() {
		PA = p[127];
		RunASM();
	}
	void PROXY_mmioStringToFOURCCA() {
		PA = p[128];
		RunASM();
	}
	void PROXY_mmioStringToFOURCCW() {
		PA = p[129];
		RunASM();
	}
	void PROXY_mmioWrite() {
		PA = p[130];
		RunASM();
	}
	void PROXY_mmsystemGetVersion() {
		PA = p[131];
		RunASM();
	}
	void PROXY_sndPlaySoundA() {
		PA = p[132];
		RunASM();
	}
	void PROXY_sndPlaySoundW() {
		PA = p[133];
		RunASM();
	}
	void PROXY_timeBeginPeriod() {
		PA = p[134];
		RunASM();
	}
	void PROXY_timeEndPeriod() {
		PA = p[135];
		RunASM();
	}
	void PROXY_timeGetDevCaps() {
		PA = p[136];
		RunASM();
	}
	void PROXY_timeGetSystemTime() {
		PA = p[137];
		RunASM();
	}
	void PROXY_timeGetTime() {
		PA = p[138];
		RunASM();
	}
	void PROXY_timeKillEvent() {
		PA = p[139];
		RunASM();
	}
	void PROXY_timeSetEvent() {
		PA = p[140];
		RunASM();
	}
	void PROXY_waveInAddBuffer() {
		PA = p[141];
		RunASM();
	}
	void PROXY_waveInClose() {
		PA = p[142];
		RunASM();
	}
	void PROXY_waveInGetDevCapsA() {
		PA = p[143];
		RunASM();
	}
	void PROXY_waveInGetDevCapsW() {
		PA = p[144];
		RunASM();
	}
	void PROXY_waveInGetErrorTextA() {
		PA = p[145];
		RunASM();
	}
	void PROXY_waveInGetErrorTextW() {
		PA = p[146];
		RunASM();
	}
	void PROXY_waveInGetID() {
		PA = p[147];
		RunASM();
	}
	void PROXY_waveInGetNumDevs() {
		PA = p[148];
		RunASM();
	}
	void PROXY_waveInGetPosition() {
		PA = p[149];
		RunASM();
	}
	void PROXY_waveInMessage() {
		PA = p[150];
		RunASM();
	}
	void PROXY_waveInOpen() {
		PA = p[151];
		RunASM();
	}
	void PROXY_waveInPrepareHeader() {
		PA = p[152];
		RunASM();
	}
	void PROXY_waveInReset() {
		PA = p[153];
		RunASM();
	}
	void PROXY_waveInStart() {
		PA = p[154];
		RunASM();
	}
	void PROXY_waveInStop() {
		PA = p[155];
		RunASM();
	}
	void PROXY_waveInUnprepareHeader() {
		PA = p[156];
		RunASM();
	}
	void PROXY_waveOutBreakLoop() {
		PA = p[157];
		RunASM();
	}
	void PROXY_waveOutClose() {
		PA = p[158];
		RunASM();
	}
	void PROXY_waveOutGetDevCapsA() {
		PA = p[159];
		RunASM();
	}
	void PROXY_waveOutGetDevCapsW() {
		PA = p[160];
		RunASM();
	}
	void PROXY_waveOutGetErrorTextA() {
		PA = p[161];
		RunASM();
	}
	void PROXY_waveOutGetErrorTextW() {
		PA = p[162];
		RunASM();
	}
	void PROXY_waveOutGetID() {
		PA = p[163];
		RunASM();
	}
	void PROXY_waveOutGetNumDevs() {
		PA = p[164];
		RunASM();
	}
	void PROXY_waveOutGetPitch() {
		PA = p[165];
		RunASM();
	}
	void PROXY_waveOutGetPlaybackRate() {
		PA = p[166];
		RunASM();
	}
	void PROXY_waveOutGetPosition() {
		PA = p[167];
		RunASM();
	}
	void PROXY_waveOutGetVolume() {
		PA = p[168];
		RunASM();
	}
	void PROXY_waveOutMessage() {
		PA = p[169];
		RunASM();
	}
	void PROXY_waveOutOpen() {
		PA = p[170];
		RunASM();
	}
	void PROXY_waveOutPause() {
		PA = p[171];
		RunASM();
	}
	void PROXY_waveOutPrepareHeader() {
		PA = p[172];
		RunASM();
	}
	void PROXY_waveOutReset() {
		PA = p[173];
		RunASM();
	}
	void PROXY_waveOutRestart() {
		PA = p[174];
		RunASM();
	}
	void PROXY_waveOutSetPitch() {
		PA = p[175];
		RunASM();
	}
	void PROXY_waveOutSetPlaybackRate() {
		PA = p[176];
		RunASM();
	}
	void PROXY_waveOutSetVolume() {
		PA = p[177];
		RunASM();
	}
	void PROXY_waveOutUnprepareHeader() {
		PA = p[178];
		RunASM();
	}
	void PROXY_waveOutWrite() {
		PA = p[179];
		RunASM();
	}
}
