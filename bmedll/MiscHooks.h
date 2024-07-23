#pragma once

MH_STATUS WINAPI CreateMiscHook(DWORD64 baseAddress, unsigned int offset, LPVOID pDetour, LPVOID* ppOriginal);
MH_STATUS WINAPI CreateMiscHookNamed(const char* moduleName, const char* procName, LPVOID pDetour, LPVOID* ppOriginal);