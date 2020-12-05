#pragma once
#include "pch.h"
#include "SourceInterface.h"

class ConVar
{
public:

	void SetValueString(const char* szString)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char*);
		return getvfunc<OriginalFn>(this, 12)(this, szString);
	}
	const char* GetString()
	{
		return *(const char**)((size_t)this + 72);
	}
};

class ConVar2
{
	//unsigned char               unknown[0x60];
	unsigned char               unknown[0x90];
};
