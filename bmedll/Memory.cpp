#include "pch.h"

//#if 0

HMODULE hTier0Module;
IMemAlloc** g_ppMemAllocSingleton;

/*void LoadTier0()
{
    if (GetModuleHandleA("tier0.dll")) return;

    printf("tier0 is not loaded yet\n");

    extern const std::wstring GetThisPathWide();
    std::wstring p = GetThisPathWide();
    p += L"\\bin\\x64_retail\\tier0.dll";
    LoadLibraryW(p.c_str());

    g_ppMemAllocSingleton = (IMemAlloc**)GetProcAddress(hTier0Module, "g_pMemAllocSingleton");
}*/

/*IMemAlloc* CreateGlobalMemAlloc()
{
    if (!hTier0Module)
        LoadTier0();
    static FARPROC Tier0_CreateGlobalMemAlloc;
    if (!Tier0_CreateGlobalMemAlloc)
        Tier0_CreateGlobalMemAlloc = GetProcAddress(hTier0Module, "CreateGlobalMemAlloc");
    return ((IMemAlloc * (*)())CreateGlobalMemAlloc)();
}*/

#pragma optimize("", off)
void* operator new(std::size_t n)
//void* operatornew(std::size_t n)
{
    if (!g_pMemAllocSingleton)
    {
        g_pMemAllocSingleton = CreateGlobalMemAlloc();
    }   
    
    
    
    
    /*if (!g_ppMemAllocSingleton || !*g_ppMemAllocSingleton)
    {
        LoadTier0();
        *g_ppMemAllocSingleton = CreateGlobalMemAlloc();
    }*/

    return g_pMemAllocSingleton->m_vtable->Alloc(g_pMemAllocSingleton, n);
    //return (*g_ppMemAllocSingleton)->m_vtable->Alloc(*g_ppMemAllocSingleton, n);
    //return malloc(n);
}

void operator delete(void* p) throw()
//void operatordelete(void* p) throw()
{
    if (!g_pMemAllocSingleton)
    {
        g_pMemAllocSingleton = CreateGlobalMemAlloc();
    }




    /*if (!g_ppMemAllocSingleton || !*g_ppMemAllocSingleton)
    {
        LoadTier0();
        *g_ppMemAllocSingleton = CreateGlobalMemAlloc();
    }*/

    g_pMemAllocSingleton->m_vtable->Free(g_pMemAllocSingleton, p);
    //(*g_ppMemAllocSingleton)->m_vtable->Free(*g_ppMemAllocSingleton, p);
    //free(p);
}
#pragma optimize("", on)

//#endif