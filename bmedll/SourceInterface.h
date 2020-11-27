#pragma once
#include "Util.h"

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);

template<typename T>
class SourceInterface
{
    T* m_interface;

public:
    SourceInterface(const std::string& moduleName, const std::string& interfaceName)
    {
        baseAddress = Util::GetModuleBaseAddress(moduleName);
        CreateInterfaceFn createInterface = (CreateInterfaceFn)Util::ResolveLibraryExport(moduleName, "CreateInterface");
        m_interface = (T*)createInterface(interfaceName.c_str(), NULL);
        if (m_interface == nullptr)
        {
            throw std::runtime_error(fmt::sprintf("Failed to call CreateInterface for %s in %s", interfaceName, moduleName));
        }
    }

    DWORD64 baseAddress;

    T* operator->() const
    {
        return m_interface;
    }

    operator T* () const
    {
        return m_interface;
    }
};




inline void**& getvtable(void* inst, size_t offset = 0)
{
    return *reinterpret_cast<void***>((size_t)inst + offset);
}
inline const void** getvtable(const void* inst, size_t offset = 0)
{
    return *reinterpret_cast<const void***>((size_t)inst + offset);
}
template< typename Fn >
inline Fn getvfunc(const void* inst, size_t index, size_t offset = 0)
{
    return reinterpret_cast<Fn>(getvtable(inst, offset)[index]);
}