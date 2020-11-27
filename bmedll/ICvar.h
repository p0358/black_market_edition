#pragma once

class ConCommand;
class ConVar;

class ICvar
{
public:
	struct VTable
	{
		void* unknown[10];
		void(*UnregisterConCommand) (ICvar* cvar, ConCommand* pCommandBase);
	};

	VTable* m_vtable;

	ConVar* FindVar(const char* var_name)
	{
		typedef ConVar* (__thiscall* OriginalFn)(PVOID, const char*);
		return getvfunc<OriginalFn>(this, 13)(this, var_name);
	}
};