#include "pch.h"

#include <stdio.h>
#include <Shlwapi.h>

#include <string>
#include <system_error>

#define ERROR_MESSAGE_CAPTION "BME Launcher DLL Error"

HMODULE hLauncherModule;
HMODULE hHookModule;
FARPROC Launcher_LauncherMain;

using CreateInterfaceFn = void* (*)(const char* pName, int* pReturnCode);

// does not seem to be used
extern "C" _declspec(dllexport) void* __fastcall CreateInterface(const char* pName, int* pReturnCode)
{
    //AppSystemCreateInterfaceFn(pName, pReturnCode);
    printf("external CreateInterface: name: %s\n", pName);

    static CreateInterfaceFn launcher_CreateInterface = (CreateInterfaceFn)GetProcAddress(hLauncherModule, "CreateInterface");
    auto res = launcher_CreateInterface(pName, pReturnCode);

    printf("external CreateInterface: return code: %p\n", res);
    return res;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

FARPROC GetLauncherMain()
{
    static FARPROC Launcher_LauncherMain;
    if (!Launcher_LauncherMain)
        Launcher_LauncherMain = GetProcAddress(hLauncherModule, "LauncherMain");
    return Launcher_LauncherMain;
}

void LibraryLoadError(DWORD dwMessageId, const wchar_t* libName, const wchar_t* location)
{
    char text[2048];
    std::string message = std::system_category().message(dwMessageId);
    sprintf_s(text, "Failed to load the %ls at \"%ls\" (%lu):\n\n%hs", libName, location, dwMessageId, message.c_str());
    MessageBoxA(GetForegroundWindow(), text, ERROR_MESSAGE_CAPTION, 0);
}

bool GetExePathWide(wchar_t* dest, DWORD destSize)
{
    if (!dest) return NULL;
    if (destSize < MAX_PATH) return NULL;

    DWORD length = GetModuleFileNameW(NULL, dest, destSize);
    return length && PathRemoveFileSpecW(dest);
}

bool Load()
{
    wchar_t exePath[2048];
    wchar_t LibFullPath[2048];

    if (!GetExePathWide(exePath, 2048))
    {
        MessageBoxA(GetForegroundWindow(), "Failed getting game directory.\nThe game cannot continue and has to exit.", ERROR_MESSAGE_CAPTION, 0);
        return false;
    }

    if (_wchdir(exePath))
    {
        MessageBoxA(GetForegroundWindow(), "Failed changing current directory to game directory.\nThe game cannot continue and has to exit.", ERROR_MESSAGE_CAPTION, 0);
        return false;
    }

#define LOAD_LIBRARY(libname) swprintf_s(LibFullPath, L"%s\\" libname, exePath); if (!LoadLibraryExW(LibFullPath, 0, LOAD_WITH_ALTERED_SEARCH_PATH)) { LibraryLoadError(GetLastError(), L ## libname, LibFullPath); return false; }
    
    LOAD_LIBRARY("bin\\x64_retail\\tier0.dll");

    {
        swprintf_s(LibFullPath, L"%s\\bin\\x64_retail\\launcher.org.dll", exePath);
        hLauncherModule = LoadLibraryExW(LibFullPath, 0, LOAD_WITH_ALTERED_SEARCH_PATH);
        if (hLauncherModule) Launcher_LauncherMain = GetProcAddress(hLauncherModule, "LauncherMain");
        if (!hLauncherModule || Launcher_LauncherMain == nullptr)
        {
            LibraryLoadError(GetLastError(), L"launcher.org.dll", LibFullPath);
            return false;
        }
    }

    LOAD_LIBRARY("bin\\x64_retail\\engine.dll");
    LOAD_LIBRARY("r1\\bin\\x64_retail\\client.dll");
    LOAD_LIBRARY("bin\\x64_retail\\filesystem_stdio.dll");
    LOAD_LIBRARY("bin\\x64_retail\\materialsystem_dx11.dll");
    LOAD_LIBRARY("bin\\x64_retail\\vstdlib.dll");
    LOAD_LIBRARY("bin\\x64_retail\\vguimatsurface.dll");
    LOAD_LIBRARY("bin\\x64_retail\\inputsystem.dll");

    FARPROC Hook_Init = nullptr;
    {
        swprintf_s(LibFullPath, L"%s\\bme\\bme.dll", exePath);
        hHookModule = LoadLibraryExW(LibFullPath, 0, LOAD_WITH_ALTERED_SEARCH_PATH);
        if (hHookModule) Hook_Init = GetProcAddress(hHookModule, "Init");
        if (!hHookModule || Hook_Init == nullptr)
        {
            LibraryLoadError(GetLastError(), L"bme.dll", LibFullPath);
            return false;
        }
    }

    //printf("before hook init\n");
    ((void (*)()) Hook_Init)();
    return true;
}

//extern "C" _declspec(dllexport) void LauncherMain()
extern "C" __declspec(dllexport) int LauncherMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (!Load())
        return 1;

    //auto LauncherMain = GetLauncherMain();
    //auto result = ((__int64(__fastcall*)())LauncherMain)();
    //auto result = ((signed __int64(__fastcall*)(__int64))LauncherMain)(0i64);
    return ((int(*)(HINSTANCE, HINSTANCE, LPSTR, int))Launcher_LauncherMain)(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

// doubt that will help us here (in launcher.dll) though
extern "C" {
    __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
