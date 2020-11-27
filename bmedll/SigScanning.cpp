#include "pch.h"
#include "SigScanning.h"
#include "Util.h"
#include "ModuleScan.h"

SigScanFuncRegistry& SigScanFuncRegistry::GetInstance()
{
    static SigScanFuncRegistry instance;
    return instance;
}

void SigScanFuncRegistry::AddSigScanFunc(BaseSigScanFunc& func, const char* moduleName, const char* signature, const char* mask)
{
    m_registrations[m_numRegistrations++] = {
        &func,
        moduleName,
        signature,
        mask
    };
}

void SigScanFuncRegistry::ResolveAll()
{
    auto logger = spdlog::get("logger");
    std::map<std::string, ModuleScan> moduleScanners;

    for (int i = 0; i < m_numRegistrations; i++)
    {
        RegistrationData& reg = m_registrations[i];
        std::string moduleName(reg.moduleName);

        // Check if the map contains a modulescan for the module
        // If not, try get a handle to the module with GetModuleHandle 
        // If no module handle available, resort to fancy loading callback stuff (TODO)
        if (moduleScanners.count(moduleName) == 0)
        {
            logger->debug("No ModuleScan found for {}", moduleName);

            // Create modulescan
            HMODULE m = GetModuleHandle(Util::Widen(moduleName).c_str());
            if (m == nullptr)
            {
                throw std::runtime_error(fmt::format("Failed to get handle for {}", moduleName));
            }
            logger->debug("Module {} already loaded, creating ModuleScan", moduleName);
            moduleScanners.emplace(moduleName, m);
        }

        ModuleScan& moduleScan = moduleScanners.at(moduleName);
        void* ptr = moduleScan.Scan(reg.signature, reg.mask);
        // Skip past any leading 0xCC bytes to get the real function pointer
        unsigned char* funcData = (unsigned char*)ptr;
        while (*funcData == 0xCC)
        {
            funcData++;
        }
        
        logger->debug("Signature {} in {} found at {} (+{})", Util::DataToHex(reg.signature, strlen(reg.mask)), moduleName, (void*)funcData, (void*)(moduleScan.m_moduleBase - funcData));
        reg.func->SetFuncPtr(funcData);
    }
}