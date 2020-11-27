// dllmain.cpp : Definiuje punkt wejścia dla aplikacji DLL.
#include "pch.h"
#include <iostream>
#include <functional>
#include <string>
#include "TTFSDK.h"

DWORD WINAPI OnAttach(LPVOID lpThreadParameter)
{
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
        while (std::getline(std::cin, input))
        {
            SDK().GetConCommandManager().ExecuteCommand(input);
            SDK().GetDiscord().core->RunCallbacks();
        }
    }

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        curl_global_init(CURL_GLOBAL_ALL);

        CreateThread(NULL, 0, OnAttach, NULL, 0, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

