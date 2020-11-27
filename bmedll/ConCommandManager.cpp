#include "pch.h"
#include "TTFSDK.h"
#include "SigScanning.h"
#include "ConCommandManager.h"

SigScanFunc<void, ConCommand*, const char*, void(*)(const CCommand&), const char*, int, void*> ConCommand_ConCommand("engine.dll", "\x40\x53\x48\x83\xEC\x00\x48\x8B\xD9\x45\x33\xD2", "xxxxx?xxxxxx");

ConCommandManager::ConCommandManager() noexcept
    : m_cvar("vstdlib.dll", "VEngineCvar007")
{
    m_logger = spdlog::get("logger");
}

void ConCommandManager::RegisterCommand(const char* name, void(*callback)(const CCommand&), const char* helpString, int flags)
{
    m_logger->info(_("Adding console command: {}"), name);
    m_commands.emplace_back();
    ConCommand* newCommand = &m_commands.back();
    ConCommand_ConCommand(newCommand, name, callback, helpString, flags, nullptr);
}

void ConCommandManager::ExecuteCommand(const std::string& commandStr)
{
    auto& engineClient = SDK().GetEngineClient();
    //engineClient->m_vtable->ClientCmd_Unrestricted(engineClient, commandStr.c_str());
    engineClient->ClientCmd_Unrestricted(commandStr.c_str());
}

void ConCommandManager::UnregisterCommand(ConCommand& command)
{
    m_logger->info(_("Removing console command: {}"), command.GetName());
    m_cvar->m_vtable->UnregisterConCommand(m_cvar, &command);
}

void ConCommandManager::UnregisterAllCommands()
{
    // NOTE: It's tricky to do this in the destructor of ConCommand because
    // it would need to call SDK() which gets tricky when we're unloading.

    for (auto& command : m_commands)
    {
        UnregisterCommand(command);
    }

    m_commands.clear();
}

ConCommandManager::~ConCommandManager()
{
    //UnregisterAllCommands();
}