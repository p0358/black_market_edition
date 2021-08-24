#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include <string>
//#include <sstream>
#include <system_error>

//#include <filesystem>
//#include <codecvt>
////#include <PathCch.h>
//namespace fs = std::filesystem;

HMODULE hLauncherModule;
HMODULE hHookModule;

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


#if 0
// You can define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING or _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS to acknowledge that you have received this warning.	
// TODO: Fix this?
namespace Util
{
    // Taken from https://stackoverflow.com/a/18597384
    std::wstring Widen(const std::string& input)
    {
        using convert_typeX = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typeX, wchar_t> converterX;
        return converterX.from_bytes(input);
        /*std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(input);

        /*std::string str{ input };
        if (str.empty()) return std::wstring();

        size_t len = input.length() + 1;
        std::wstring ret = std::wstring(len, 0);
        int size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, &str[0], str.size(), &ret[0], len);
        ret.resize(size);
        return ret;*/
    }

    // Taken from https://stackoverflow.com/a/18597384
    std::string Narrow(const std::wstring& input)
    {
        using convert_typeX = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typeX, wchar_t> converterX;
        return converterX.to_bytes(input);
        /*std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.to_bytes(input);*/

        /*std::wstring wstr{ input };
        if (wstr.empty()) return std::string();

        int size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, &wstr[0], wstr.size(), NULL, 0, NULL, NULL);
        std::string ret = std::string(size, 0);
        WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, &wstr[0], wstr.size(), &ret[0], size, NULL, NULL);
        return ret;*/
    }
}

const std::string GetExePath()
{
    WCHAR result[MAX_PATH];
    const DWORD length = GetModuleFileNameW(NULL, result, MAX_PATH);
    if (!length)
    {
        MessageBoxA(GetForegroundWindow(), "Failed calling GetModuleFileNameW.\nThe game cannot continue and has to exit.", "Launcher Error", 0);
        std::exit(1);
    }
    fs::path path{ Util::Narrow(result) };
    path._Remove_filename_and_separator();
    return path.string();
}

const std::wstring GetExePathWide()
{
    WCHAR result[MAX_PATH];
    const DWORD length = GetModuleFileNameW(NULL, result, MAX_PATH);
    if (!length)
    {
        MessageBoxA(GetForegroundWindow(), "Failed calling GetModuleFileNameW.\nThe game cannot continue and has to exit.", "Launcher Error", 0);
        std::exit(1);
    }
    fs::path path{ result };
    path._Remove_filename_and_separator();
    return path.wstring();
}
#endif

FARPROC GetLauncherMain()
{
    static FARPROC Launcher_LauncherMain;
    if (!Launcher_LauncherMain)
        Launcher_LauncherMain = GetProcAddress(hLauncherModule, "LauncherMain");
    return Launcher_LauncherMain;
}

/*void LibraryLoadError(DWORD dwMessageId, const wchar_t* libName, const wchar_t* location)
{
    char text[2048];
    std::string message = std::system_category().message(dwMessageId);
    sprintf_s(text, "Failed to load the %ls at \"%ls\" (%lu):\n\n%hs", libName, location, dwMessageId, message.c_str());
    MessageBoxA(GetForegroundWindow(), text, "Launcher Error", 0);
}*/

void LibraryLoadError(DWORD dwMessageId, const wchar_t* libName)
{
    char text[2048];
    std::string message = std::system_category().message(dwMessageId);
    sprintf_s(text, "Failed to load the %ls (%lu):\n\n%hs", libName, dwMessageId, message.c_str());
    MessageBoxA(GetForegroundWindow(), text, "Launcher Error", 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
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

//wchar_t newPathEnv[65565];

extern "C" _declspec(dllexport) void LauncherMain()
{
    {
        //printf("%s\n", "henlo from LauncherMain");

        /*auto exePath = GetExePathWide();
        if (!exePath.length())
        {
            MessageBoxA(GetForegroundWindow(), "Failed getting game directory.\nThe game cannot continue and has to exit.", "Launcher Error", 0);
            return;
        }*/

        /*WCHAR NPath[MAX_PATH];
        GetCurrentDirectoryW(MAX_PATH, NPath);

        if (false) {
            //std::wstringstream PathSS;
            wchar_t* pValue;
            size_t len;
            errno_t err = _wdupenv_s(&pValue, &len, L"PATH");
            if (!err)
            {
                //PathSS << L"PATH=" << exePath << L";" << exePath << L"\\bin\\x64_retail;" << exePath << L"\\r1\\bin\\x64_retail;" << pValue;
                //auto result = _wputenv(PathSS.str().c_str());
                //wsprintf(newPathEnv, L"PATH=%s;%s\\bin\\x64_retail;%s\\r1\\bin\\x64_retail;%s", exePath, exePath, exePath, pValue);
                wsprintf(newPathEnv, L"PATH=%s;%s\\bin\\x64_retail;%s\\r1\\bin\\x64_retail;%s", NPath, NPath, NPath, pValue);
                auto result = _wputenv(newPathEnv);
                if (result == -1)
                {
                    /*std::wstringstream errSS;
                    errSS << L"Warning: could not prepend the current directory to app's PATH environment variable. Something may break because of that.";
                    //errSS << "\n\n" << PathSS.str();
                    errSS << L"\n\n" << newPathEnv;
                    MessageBoxW(GetForegroundWindow(), errSS.str().c_str(), L"Launcher Warning", 0);* /
                    MessageBoxW(GetForegroundWindow(), L"eresdfsfsdfds", L"Launcher Warning", 0);
                }
                free(pValue);
            }
        }*/

        {
            //wchar_t LauncherLibFileName[1024];
            //swprintf_s(LauncherLibFileName, L"%s\\bin\\x64_retail\\launcher.org.dll", exePath.c_str());
            //swprintf_s(LauncherLibFileName, L"%s\\bin\\x64_retail\\launcher.org.dll", NPath);
            //swprintf_s(LauncherLibFileName, L".\\bin\\x64_retail\\launcher.org.dll");
            //hLauncherModule = LoadLibraryW(LauncherLibFileName);
            hLauncherModule = LoadLibraryExA("bin\\x64_retail\\launcher.org.dll", 0i64, 8u);
            if (!hLauncherModule)
            {
                //LibraryLoadError(GetLastError(), L"launcher.org.dll", LauncherLibFileName);
                LibraryLoadError(GetLastError(), L"launcher.org.dll");
                return;
            }
        }

        {
            //wchar_t LibFullPath[1024];
#define LOAD_LIBRARY(libname) if (!LoadLibraryExW(L ## libname, 0i64, 8u)) LibraryLoadError(GetLastError(), L ## libname)
//#define LOAD_LIBRARY(libname) swprintf_s(LibFullPath, L"%s\\" L ## libname, NPath); if (!LoadLibraryW(LibFullPath)) LibraryLoadError(GetLastError(), L ## libname, LibFullPath)
//#define LOAD_LIBRARY(libname) swprintf_s(LibFullPath, L"%s\\" L ## libname, exePath.c_str()); if (!LoadLibraryW(LibFullPath)) LibraryLoadError(GetLastError(), L ## libname, LibFullPath)
//#define LOAD_LIBRARY(libname) swprintf_s(LibFullPath, L"" libname); if (!LoadLibraryW(LibFullPath)) LibraryLoadError(GetLastError(), L ## libname, LibFullPath)
            LOAD_LIBRARY("bin\\x64_retail\\engine.dll");
            LOAD_LIBRARY("r1\\bin\\x64_retail\\client.dll");
            LOAD_LIBRARY("bin\\x64_retail\\tier0.dll");
            LOAD_LIBRARY("bin\\x64_retail\\filesystem_stdio.dll");
            LOAD_LIBRARY("bin\\x64_retail\\materialsystem_dx11.dll");
            LOAD_LIBRARY("bin\\x64_retail\\vstdlib.dll");
            LOAD_LIBRARY("bin\\x64_retail\\vguimatsurface.dll");
            LOAD_LIBRARY("bin\\x64_retail\\inputsystem.dll");
        }

        //printf("before hook load\n");
        FARPROC Hook_Init = nullptr;
        {
            //wchar_t HookLibFileName[1024];
            //swprintf_s(HookLibFileName, L"%s\\bme\\bme.dll", exePath.c_str());
            //swprintf_s(HookLibFileName, L"bme\\bme.asi");
            //hHookModule = LoadLibraryW(HookLibFileName);
            hHookModule = LoadLibraryExW(L"bme\\bme.dll", 0i64, 8u);
            if (hHookModule) Hook_Init = GetProcAddress(hHookModule, "Init");
            if (!hHookModule || Hook_Init == nullptr)
            {
                //LibraryLoadError(GetLastError(), L"bme.dll", HookLibFileName);
                LibraryLoadError(GetLastError(), L"bme.dll");
                return;
            }
        }

        //printf("before hook init\n");
        ((void (*)()) Hook_Init)();
        //printf("after hook init\n");
    }

    auto LauncherMain = GetLauncherMain();
    //auto result = ((__int64(__fastcall*)())LauncherMain)();
    auto result = ((signed __int64(__fastcall*)(__int64))LauncherMain)(0i64);
}

// doubt that will help us here (in launcher.dll) though
extern "C" {
    __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
