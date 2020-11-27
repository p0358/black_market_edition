#include "pch.h"
#include "ModuleScan.h"
#include "Util.h"

// Based off CSigScan from https://wiki.alliedmods.net/Signature_Scanning

ModuleScan::ModuleScan(const std::string& moduleName) : ModuleScan(GetModuleHandle(Util::Widen(moduleName).c_str()))
{

}

ModuleScan::ModuleScan(HMODULE _module)
{
    m_moduleHandle = _module;
    if (m_moduleHandle == nullptr)
    {
        throw SigScanException(fmt::sprintf("GetModuleHandle returned NULL (Win32 Error = %d)", GetLastError()));
    }

    MEMORY_BASIC_INFORMATION mem;
    if (!VirtualQuery(m_moduleHandle, &mem, sizeof(mem)))
    {
        throw SigScanException(fmt::sprintf("VirtualQuery returned NULL (Win32 Error = %d)", GetLastError()));
    }

    m_moduleBase = (unsigned char*)mem.AllocationBase;
    if (m_moduleBase == nullptr)
    {
        throw SigScanException("mem.AllocationBase was NULL");
    }

    IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)mem.AllocationBase;
    IMAGE_NT_HEADERS* pe = (IMAGE_NT_HEADERS*)((unsigned char*)dos + dos->e_lfanew);

    if (pe->Signature != IMAGE_NT_SIGNATURE)
    {
        throw SigScanException("PE signature is not a valid NT signature");
    }

    m_moduleLen = pe->OptionalHeader.SizeOfImage;
}

void* ModuleScan::Scan(const char* sig, const char* mask)
{
    size_t sigLength = strlen(mask);
    return Scan(sig, mask, sigLength);
}

void* ModuleScan::Scan(const char* sig, const char* mask, size_t sigLength)
{
    char* pData = (char*)m_moduleBase;
    char* pEnd = (char*)m_moduleBase + m_moduleLen;

    while (pData < (pEnd - sigLength))
    {
        int i;
        for (i = 0; i < sigLength; i++)
        {
            if (mask[i] != '?' && sig[i] != pData[i])
                break;
        }

        // The for loop finished on its own accord
        if (i == sigLength)
        {
            return (void*)pData;
        }

        pData++;
    }

    throw SigScanException(fmt::sprintf("Signature could not be resolved - %s", Util::DataToHex(sig, sigLength).c_str()));
}