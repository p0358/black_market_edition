#pragma once

typedef struct player_info_s {
	char    _0x0000[0x0008];    // 0x0000
	char    szName[32];            // 0x0008
	char    _0x0028[0x0228];    // 0x0028
} player_info_t;

class IVEngineClient
{
public:
    struct VTable
    {
        void* unknown[279];
        //void(*ClientCmd_Unrestricted) (IVEngineClient* engineClient, const char* szCmdString);
    };

    VTable* m_vtable;

	void GetScreenSize(int& wide, int& tall)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int&, int&);
		return getvfunc<OriginalFn>(this, 12)(this, wide, tall);
	}
	bool GetPlayerInfo(int ent_num, player_info_t* pinfo)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, int, player_info_t*);
		return getvfunc<OriginalFn>(this, 16)(this, ent_num, pinfo);
	}
	int GetLocalPlayer(void)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 23)(this);
	}
	void ClientCmd_Unrestricted(const char* command)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char*);
		//void(*)(IVEngineClient*, const char*)
		return getvfunc<OriginalFn>(this, /*106*/199)(this, command);
	}
	bool IsInGame(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 117)(this);
	}
	void ServerCmd(const char* szCmdString, bool bReliable = true)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char*, bool);
		return getvfunc<OriginalFn>(this, 14)(this, szCmdString, bReliable);
	}
	void ClientCmd(const char* szCmdString)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char*);
		return getvfunc<OriginalFn>(this, 15)(this, szCmdString);
	}
};