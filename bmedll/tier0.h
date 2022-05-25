#pragma once

class IMemAlloc;

class ICommandLine
{
public:
	//struct VTable
	//{
	virtual void		CreateCmdLine(const char* commandline) = 0; // index 1
	virtual void		CreateCmdLine(int argc, char** argv) = 0; // index 0
	virtual void		ClearCmdLine(void) const = 0; // index 2
	virtual const char* GetCmdLine(void) const = 0; // index 3

	// Check whether a particular parameter exists
	virtual	const char* CheckParm(const char* psz, const char** ppszValue = 0) const = 0; // index 4
	virtual void		RemoveParm(const char* parm) = 0; // index 5
	virtual void		AppendParm(const char* pszParm, const char* pszValues) = 0; // index 6

	// Returns the argument after the one specified, or the default if not found
	virtual const char* ParmValue(const char* psz, const char* pDefaultVal = 0) const = 0; // index 9
	virtual int			ParmValue(const char* psz, int nDefaultVal) const = 0; // index 8
	virtual float		ParmValue(const char* psz, float flDefaultVal) const = 0; // index 7

	// Gets at particular parameters
	virtual int			ParmCount() const = 0; // index 10
	virtual int			FindParm(const char* psz) const = 0;	// Returns 0 if not found. // index 11
	virtual const char* GetParm(int nIndex) const = 0; // index 12

	virtual const char** GetParms() const = 0; // index 13

	// copies the string passed
	virtual void SetParm(int nIndex, char const* pNewParm) = 0; // index 14

	virtual void* Destructor(bool callFree = false) = 0; // index 15

//};

//VTable* m_vtable;
};

extern "C"
{
    IMemAlloc* CreateGlobalMemAlloc();
    __declspec(dllimport) extern IMemAlloc* g_pMemAllocSingleton;
    bool ThreadInMainThread();
	ICommandLine* CommandLine();
	__int64 Error(const char* psz, ...);
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

