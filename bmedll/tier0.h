#pragma once

extern "C"
{
    IMemAlloc* CreateGlobalMemAlloc();
    __declspec(dllimport) extern IMemAlloc* g_pMemAllocSingleton;
    bool ThreadInMainThread();
}

/*HMODULE hTier0Module;
IMemAlloc** g_ppMemAllocSingleton;

void LoadTier0()
{
    if (GetModuleHandleA("tier0.dll")) return;

    printf("tier0 is not loaded yet\n");

    extern const std::wstring GetThisPathWide();
    std::wstring p = GetThisPathWide();
    p += L"\\bin\\x64_retail\\tier0.dll";
    LoadLibraryW(p.c_str());

    g_ppMemAllocSingleton = (IMemAlloc**)GetProcAddress(hTier0Module, "g_pMemAllocSingleton");
}

IMemAlloc* CreateGlobalMemAlloc()
{
    if (!hTier0Module)
        LoadTier0();
    static FARPROC Tier0_CreateGlobalMemAlloc;
    if (!Tier0_CreateGlobalMemAlloc)
        Tier0_CreateGlobalMemAlloc = GetProcAddress(hTier0Module, "CreateGlobalMemAlloc");
    return ((IMemAlloc*(*)())CreateGlobalMemAlloc)();
}*/

