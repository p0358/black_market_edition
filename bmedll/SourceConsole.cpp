#include "pch.h"
#include "TTFSDK.h"
#include "ConCommandManager.h"
#include "SourceConsole.h"

SourceConsole& SourceCon()
{
    return SDK().GetSourceConsole();
}

#define WRAPPED_MEMBER(name) MemberWrapper<decltype(&SourceConsole::##name), &SourceConsole::##name, decltype(&SourceCon), &SourceCon>::Call

SourceConsole::SourceConsole(ConCommandManager& conCommandManager, spdlog::level::level_enum level) :
    m_gameConsole(_("client.dll"), _("GameConsole004"))
{
    m_logger = spdlog::get(_("logger"));

    m_sink = std::make_shared<SourceConsoleSink>(this);
    m_sink->set_pattern(_("[%l] %v"));
    m_sink->set_level(level);
    m_logger->sinks().push_back(m_sink);

    conCommandManager.RegisterCommand(_("toggleconsole"), WRAPPED_MEMBER(ToggleConsoleCommand), _("Show/hide the console"), 0);
    conCommandManager.RegisterCommand(_("clear"), WRAPPED_MEMBER(ClearConsoleCommand), _("Clears the console"), 0);
}

void SourceConsole::InitialiseSource()
{
    m_gameConsole->Initialize();
    CConsoleDialog_OnCommandSubmitted.Hook(m_gameConsole->m_pConsole->m_vtable, WRAPPED_MEMBER(OnCommandSubmittedHook));
}

void SourceConsole::ToggleConsoleCommand(const CCommand& args)
{
    if (!m_gameConsole->m_bInitialized)
    {
        return;
    }

    if (!m_gameConsole->IsConsoleVisible())
    {
        m_gameConsole->Activate();
    }
    else
    {
        m_gameConsole->Hide();
    }
}

void SourceConsole::ClearConsoleCommand(const CCommand& args)
{
    if (!m_gameConsole->m_bInitialized)
    {
        return;
    }

    m_gameConsole->Clear();
}

void SourceConsole::OnCommandSubmittedHook(CConsoleDialog* consoleDialog, const char* pCommand)
{
    Print(_("] "));
    Print(pCommand);
    Print(_("\n"));

    CConsoleDialog_OnCommandSubmitted(consoleDialog, pCommand);
}

void SourceConsole::ColorPrint(const SourceColor& clr, const char* pMessage)
{
    if (!m_gameConsole->m_bInitialized)
    {
        return;
    }

    m_gameConsole->m_pConsole->m_pConsolePanel->ColorPrint(clr, pMessage);
}

void SourceConsole::Print(const char* pMessage)
{
    if (!m_gameConsole->m_bInitialized)
    {
        return;
    }

    m_gameConsole->m_pConsole->m_pConsolePanel->Print(pMessage);
}

void SourceConsole::DPrint(const char* pMessage)
{
    if (!m_gameConsole->m_bInitialized)
    {
        return;
    }

    m_gameConsole->m_pConsole->m_pConsolePanel->DPrint(pMessage);
}

SourceConsoleSink::SourceConsoleSink(SourceConsole* console)
{
    m_console = console;
    m_colours.emplace(spdlog::level::trace, SourceColor(0, 255, 255, 255));
    m_colours.emplace(spdlog::level::debug, SourceColor(0, 255, 255, 255));
    m_colours.emplace(spdlog::level::info, SourceColor(255, 255, 255, 255));
    m_colours.emplace(spdlog::level::warn, SourceColor(255, 255, 0, 255));
    m_colours.emplace(spdlog::level::err, SourceColor(255, 0, 0, 255));
    m_colours.emplace(spdlog::level::critical, SourceColor(255, 0, 0, 255));
    m_colours.emplace(spdlog::level::off, SourceColor(0, 0, 0, 0));
}

void SourceConsoleSink::sink_it_(const spdlog::details::log_msg& msg)
{
    //fmt::memory_buf_t formatted;
    /*spdlog::memory_buf_t formatted;
    base_sink::formatter_->format(msg, formatted);
    m_console->ColorPrint(m_colours[msg.level], fmt::to_string(formatted).c_str());*/
    spdlog::memory_buf_t formatted;
    base_sink<std::mutex>::formatter_->format(msg, formatted);
    m_console->ColorPrint(m_colours[msg.level], fmt::to_string(formatted).c_str());
}

void SourceConsoleSink::flush_()
{
    return;
}