#include "pch.h"
#include "TTFSDK.h"
#include "SigScanning.h"
#include "ConCommandManager.h"
#include "ConVar.h"

SigScanFunc<void, ConCommand*, const char*, void(*)(const CCommand&), const char*, int, void*> ConCommand_ConCommand("engine.dll", "\x40\x53\x48\x83\xEC\x00\x48\x8B\xD9\x45\x33\xD2", "xxxxx?xxxxxx");
SigScanFunc<void, ConVar2*, const char*, const char*, int, const char*> ConVar_ConVar("engine.dll", "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x48\x89\x7C\x24\x20\x41\x54\x48\x83\xEC\x50\x45\x33\xE4\x48\x8D\x05\x84\x5F\x21\x00", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx?");

ConCommandManager::ConCommandManager() noexcept
    : m_cvar("vstdlib.dll", "VEngineCvar007")
{
    m_logger = spdlog::get("logger");
}

void ConCommandManager::RegisterCommand(const char* name, void(*callback)(const CCommand&), const char* helpString, int flags)
{
    //m_logger->info(_("Adding console command: {}"), name);
    SPDLOG_LOGGER_DEBUG(m_logger, "Adding console command: {}", name);
    m_commands.emplace_back();
    ConCommand* newCommand = &m_commands.back();
    ConCommand_ConCommand(newCommand, name, callback, helpString, flags, nullptr);
}

void ConCommandManager::RegisterConVar(const char* name, const char* defaultValue, int flags, const char* helpString)
{
    //m_logger->info(_("Adding cvar: {}"), name);
    SPDLOG_LOGGER_DEBUG(m_logger, "Adding cvar: {}", name);
    m_cvars.emplace_back();
    ConVar2* newCvar = &m_cvars.back();
    ConVar_ConVar(newCvar, name, defaultValue, flags, helpString);
}

void ConCommandManager::ExecuteCommand(const std::string& commandStr)
{
    auto& engineClient = SDK().GetEngineClient();
    //engineClient->m_vtable->ClientCmd_Unrestricted(engineClient, commandStr.c_str());
    engineClient->ClientCmd_Unrestricted(commandStr.c_str());
}

void ConCommandManager::UnregisterCommand(ConCommand& command)
{
    if (!m_cvar || !m_cvar->m_vtable) return;
    m_logger->info(_("Removing console command: {}"), command.GetName());
    m_cvar->m_vtable->UnregisterConCommand(m_cvar, &command);
}

void ConCommandManager::UnregisterAllCommands()
{
    // NOTE: It's tricky to do this in the destructor of ConCommand because
    // it would need to call SDK() which gets tricky when we're unloading.
    SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "ConCommandManager::UnregisterAllCommands");

    for (auto& command : m_commands)
    {
        UnregisterCommand(command);
    }

    m_commands.clear();
}

ConCommandManager::~ConCommandManager()
{
    SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "ConCommandManager destructor");
    if (!isProcessTerminating)
        UnregisterAllCommands();
}