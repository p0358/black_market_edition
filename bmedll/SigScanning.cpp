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
        std::string(moduleName),
        std::string(signature, strlen(mask)),
        std::string(mask, strlen(mask))
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
            SPDLOG_LOGGER_DEBUG(logger, "No ModuleScan found for {}", moduleName);

            // Create modulescan
            HMODULE m = GetModuleHandle(Util::Widen(moduleName).c_str());
            if (m == nullptr)
            {
                throw std::runtime_error(fmt::format("Failed to get handle for {}", moduleName));
            }
            SPDLOG_LOGGER_DEBUG(logger, "Module {} already loaded, creating ModuleScan", moduleName);
            moduleScanners.emplace(moduleName, m);
        }

        ModuleScan& moduleScan = moduleScanners.at(moduleName);
        void* ptr = moduleScan.Scan(reg.signature.c_str(), reg.mask.c_str());
        // Skip past any leading 0xCC bytes to get the real function pointer
        unsigned char* funcData = (unsigned char*)ptr;
        while (*funcData == 0xCC)
        {
            funcData++;
        }
        
        //SPDLOG_LOGGER_DEBUG(logger, "Signature {} in {} found at {} (+{})", Util::DataToHex(reg.signature, strlen(reg.mask)), moduleName, (void*)funcData, (void*)(funcData - moduleScan.m_moduleBase));
        SPDLOG_LOGGER_DEBUG(logger, "Signature {} in {} found at {} (+{})", Util::DataToHex(reg.signature.c_str(), reg.mask.length()), moduleName, (void*)funcData, (void*)(funcData - moduleScan.m_moduleBase));
        reg.func->SetFuncPtr(funcData);
    }
}