#pragma once
#include "pch.h"

class TempReadWrite
{
    DWORD m_origProtection;
    void* m_ptr;

public:
    TempReadWrite(void* ptr)
    {
        m_ptr = ptr;
        MEMORY_BASIC_INFORMATION mbi;
        VirtualQuery(m_ptr, &mbi, sizeof(mbi));
        VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);
        m_origProtection = mbi.Protect;
    }

    ~TempReadWrite()
    {
        MEMORY_BASIC_INFORMATION mbi;
        VirtualQuery(m_ptr, &mbi, sizeof(mbi));
        VirtualProtect(mbi.BaseAddress, mbi.RegionSize, m_origProtection, &mbi.Protect);
    }
};

template <typename TVTable, TVTable> class HookedVTableFunc;
template <typename TVTable, typename R, typename ...Args, R(*(TVTable::* mf))(Args...)>
class HookedVTableFunc<R(*(TVTable::*))(Args...), mf>
{
    bool m_hooked = false;
    TVTable* m_vtable = nullptr;
    R(*m_origFunc)(Args...) = nullptr;

public:
    void Hook(TVTable* vtablePtr, R(*hookFunc)(Args...))
    {
        if (m_hooked)
        {
            return;
        }

        m_vtable = vtablePtr;
        m_origFunc = *(m_vtable->*mf);

        TempReadWrite rw(m_vtable);
        (m_vtable->*mf) = hookFunc;

        m_hooked = true;
    }

    ~HookedVTableFunc()
    {
        if (m_hooked)
        {
            TempReadWrite rw(m_vtable);
            (m_vtable->*mf) = m_origFunc;
            m_hooked = false;
        }
    }

    R operator()(Args... args)
    {
        return m_origFunc(args...);
    }
};