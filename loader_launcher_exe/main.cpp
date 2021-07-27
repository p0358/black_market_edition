//#if 0
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
//#include <windows.h>

#include <wtypes.h>
#include <stdio.h>

HMODULE hLauncherModule;

FARPROC GetLauncherMain()
{
    static FARPROC Launcher_LauncherMain;
    if (!Launcher_LauncherMain)
        Launcher_LauncherMain = GetProcAddress(hLauncherModule, "LauncherMain");
    return Launcher_LauncherMain;
}

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
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
            //hLauncherModule = LoadLibraryExA("bin\\x64_retail\\launcher.org.dll", 0i64, 8u);
            hLauncherModule = LoadLibraryExA("bin\\x64_retail\\launcher.dll", 0i64, 8u);
            /*if (!hLauncherModule)
            {
                LibraryLoadError(GetLastError(), L"launcher.org.dll", LauncherLibFileName);
                return;
            }*/
        }

        {
            //wchar_t LibFullPath[1024];
#define LOAD_LIBRARY(libname) swprintf_s(LibFullPath, L"%s\\" L ## libname, NPath); if (!LoadLibraryW(LibFullPath)) LibraryLoadError(GetLastError(), L ## libname, LibFullPath)
//#define LOAD_LIBRARY(libname) swprintf_s(LibFullPath, L"%s\\" libname, exePath.c_str()); if (!LoadLibraryW(LibFullPath)) LibraryLoadError(GetLastError(), L ## libname, LibFullPath)
//#define LOAD_LIBRARY(libname) swprintf_s(LibFullPath, L"" libname); if (!LoadLibraryW(LibFullPath)) LibraryLoadError(GetLastError(), L ## libname, LibFullPath)
            /*LOAD_LIBRARY("bin\\x64_retail\\engine.dll");
            LOAD_LIBRARY("r1\\bin\\x64_retail\\client.dll");
            LOAD_LIBRARY("bin\\x64_retail\\tier0.dll");
            LOAD_LIBRARY("bin\\x64_retail\\filesystem_stdio.dll");
            LOAD_LIBRARY("bin\\x64_retail\\materialsystem_dx11.dll");
            LOAD_LIBRARY("bin\\x64_retail\\vstdlib.dll");
            LOAD_LIBRARY("bin\\x64_retail\\vguimatsurface.dll");
            LOAD_LIBRARY("bin\\x64_retail\\inputsystem.dll");*/
        }

        //printf("before hook load\n");
        /*FARPROC Hook_Init = nullptr;
        {
            wchar_t HookLibFileName[1024];
            swprintf_s(HookLibFileName, L"%s\\bme\\bme.dll", exePath.c_str());
            //swprintf_s(HookLibFileName, L"bme\\bme.asi");
            hHookModule = LoadLibraryW(HookLibFileName);
            if (hHookModule) Hook_Init = GetProcAddress(hHookModule, "Init");
            if (!hHookModule || Hook_Init == nullptr)
            {
                LibraryLoadError(GetLastError(), L"bme.dll", HookLibFileName);
                return;
            }
        }

        //printf("before hook init\n");
        ((void (*)()) Hook_Init)();*/
        //printf("after hook init\n");
    }

    auto LauncherMain = GetLauncherMain();
    //auto result = ((__int64(__fastcall*)())LauncherMain)();
    auto result = ((signed __int64(__fastcall*)(__int64))LauncherMain)(0i64);
    return result;
}

// doubt that will help us here though
extern "C" {
    __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
//#endif

#if 0
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <iterator>

// You can compile with: cl /EHsc /std:c++latest /F8000000 launchertest.cpp
// /HIGHENTROPYVA:NO -- was originally there due to old compiler, but not needed

extern "C" {
    __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

HINSTANCE hInst;

//signed __int64 __fastcall LauncherMain(__int64 a1)
//__declspec(dllimport) signed __int64 __fastcall LauncherMain(__int64 a1); // used for static binding

typedef signed __int64(__fastcall* GW)(__int64 a1);
//typedef signed __int64(__fastcall* GW)();
GW LauncherMain;
DWORD WINAPI LauncherThread(LPVOID lpThreadParameter)
{
    //LauncherMain((__int64)0i64);
    //LauncherMain(lpThreadParameter);
    return 0;
}

HMODULE hModule;

//int main(int argc, char* argv[])
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    //std::copy( argv+1, argv+argc, std::ostream_iterator<const char*>( std::cout, " " ) );

/***
__declspec(dllimport) bool GetWelcomeMessage(char *buf, int len); // used for static binding
 ***/
 //typedef bool (*GW)(char *buf, int len);
 //typedef signed __int64(__fastcall* GW)(__int64 a1);

 //HMODULE hModule = LoadLibrary(TEXT("./bin/x64_retail/launcher.dll"));
// HMODULE hModule = LoadLibraryExA("bin\\x64_retail\\launcher.dll", 0i64, 8u);
  hModule = LoadLibraryExA("bin\\x64_retail\\launcher.dll", 0i64, 8u);
    //HMODULE hModule = LoadLibraryExA("launcher.dll", 0i64, 8u);
    //HMODULE hModule = LoadLibraryExA("C:\\Program Files (x86)\\Origin Games\\Titanfall\\bin\\x64_retail\\launcher.dll", 0i64, 8u);
    //HMODULE hModule = LoadLibraryExA("C:\\Nexon\\TitanFallOnline\\Bin\\launcher.dll", 0i64, 8u);
    //HMODULE hModule = LoadLibraryExA("H:\\Downloads\\titanfall_beta\\Titanfall-Beta\\bin\\x64_retail\\launcher.dll", 0i64, 8u);
    //HMODULE hModule = LoadLibraryExA("H:\\Gry\\Origin\\Titanfall2\\bin\\x64_retail\\launcher.dll", 0i64, 8u);
    if (hModule) {
        std::cout << "Launcher loaded!" << std::endl;
    }
    if (!hModule) {
        std::cout << "Launcher not loaded, fail!" << std::endl;
        return 1;
    }
    std::cout << "Getting launcher function..." << std::endl;
    LauncherMain = (GW)GetProcAddress(hModule, "LauncherMain");
    std::cout << "Got: " << (void*)LauncherMain << ". Proceeding to launch the game..." << std::endl;

    /*char buf[128];
    if(GetWelcomeMessage(buf, 128) == true)
        std::cout << buf;
        return 0;*/
        LauncherMain((__int64)0i64);
        //LauncherMain();
    ////////CreateThread(NULL, 0, LauncherThread, NULL, 0, NULL);
    //CreateThread(NULL, 0, LauncherThread, lpCmdLine, 0, NULL);

    /////////while (true) {}

    return 0;
}
#endif