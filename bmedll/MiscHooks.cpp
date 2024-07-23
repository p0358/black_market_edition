#include "pch.h"
#include "Memory.h"
#include "MiscHooks.h"

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