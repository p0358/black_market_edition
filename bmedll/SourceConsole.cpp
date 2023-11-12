#include "pch.h"
#include "TTFSDK.h"
#include "ConCommandManager.h"
#include "SourceConsole.h"

SourceConsole& SourceCon()
{
    return SDK().GetSourceConsole();
}

#define WRAPPED_MEMBER(name) MemberWrapper<decltype(&SourceConsole::##name), &SourceConsole::##name, decltype(&SourceCon), &SourceCon>::Call

//
HookedFuncStatic<bool __fastcall, __int64> SVC_Print_Process("engine.dll", 0x23E20); // in SVC_Print's vtable
bool __fastcall SVC_Print_Process_Hook(__int64 a1) // processing of received SVC_Print message
{
    auto text = *(char**)(a1 + 32);
    static auto logger = spdlog::get("logger");

    char buf[2048];
    sprintf_s(buf, "%s", text);

    auto len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
        buf[len - 1] = '\0';

    SPDLOG_LOGGER_INFO(logger, "[svc_print] {}", buf);
    return SVC_Print_Process(a1);
}
//

//
// awkward place to hook this tbh
#define CMDSTR_ADD_EXECUTION_MARKER "[$&*,`]"
HookedFuncStatic<__int64 __fastcall, unsigned int, __int64, int, int> Cmd_ExecuteCommand("engine.dll", 0x105240);
__int64 __fastcall Cmd_ExecuteCommand_Hook(unsigned int a1, __int64 a2, int src, int nClientSlot)
{

    // okay so what we do here is
    // we let the original exec and check the result and some internal conditions
    // in order to detect if a command was supressed by FCVAR_SERVER_CAN_EXECUTE limitation.
    // If server command execution limitation is enabled, g_iFilterCommandsByServerCanExecute is gonna be > 0 for commands
    // that do come from server and don't have FCVAR_SERVER_CAN_EXECUTE flag.
    // Now the function checks if it's an engine ConCommand, if it's a script command it gets passed through (VERIFY BECAUSE MAYBE NOT XD after all ret=0!!!!!!).
    // Problem? Most cvars that server executes don't have that flag enabled, because it was never enforced in Respawn engine.
    // So we disable the limitation for now, but keep the logging function here just in case we decide to re-enable it; it works.
    // Now, if we wanna enable it, we should 

    // Current list of registered concommands that the server may try to execute (may not be complete, but seems to be...):
    // -remote_view
    // stop_transition_videos_fadeout
    // connectwithtoken

    // Also in CBaseClientState::InternalProcessStringCmd there's an exemption for "Connect" command with HLTV,
    // and there it adds the limitation execution marker otherwise. Seems to be the best place to add more command exceptions,
    // easier than trying to apply the flag to every concommand...
    // also, that `if (pCommand)` kind of check we do below, we should probably use it in there to check if
    // it's a script concommand (ie not registered in engine), and in this case let it through...

    auto ret = Cmd_ExecuteCommand(a1, a2, src, nClientSlot);
    if (ret == 0) {
        // just trying to rewind the logic from decompilation to see if command rejection reason was what we want to log

        if (!*(_DWORD*)a2)
            return ret;

        const char* v9 = "";
        if (*(int*)a2 > 0)
            v9 = *(const CHAR**)(a2 + 1040);

        static auto logger = spdlog::get("logger");
        static auto& cmd_source = *(int*)(Util::GetModuleBaseAddress("engine.dll") + 0x2EB6AC0);
        static auto& cmd_clientslot = *(int*)(Util::GetModuleBaseAddress("engine.dll") + 0x2EB6AC0);
        logger->debug("[aaa] v9:{}, a2:{}, strcmp:{}, b1:{}, b2:{}, b3:{}, g:{}, h:{}, p:{}", v9, a2, strcmp(v9, CMDSTR_ADD_EXECUTION_MARKER),
            cmd_source != src, cmd_clientslot != nClientSlot, cmd_source != src || cmd_clientslot != nClientSlot,
            *(int*)(Util::GetModuleBaseAddress("engine.dll") + 0x2EB6AC4),
            ((bool(*)())(Util::GetModuleBaseAddress("engine.dll") + 0x130400))(),
            (*(__int64(__fastcall**)(__int64, const CHAR*))(*(_QWORD*)(*(__int64*)(Util::GetModuleBaseAddress("engine.dll") + 0x318A638)) + 112i64))(*(__int64*)(Util::GetModuleBaseAddress("engine.dll") + 0x318A638), v9)
            //,!(*(unsigned __int8(__fastcall**)(__int64, __int64))(*(_QWORD*)((*(__int64(__fastcall**)(__int64, const CHAR*))(*(_QWORD*)(*(__int64*)(Util::GetModuleBaseAddress("engine.dll") + 0x318A638)) + 112i64))(*(__int64*)(Util::GetModuleBaseAddress("engine.dll") + 0x318A638), v9)) + 16i64))((*(__int64(__fastcall**)(__int64, const CHAR*))(*(_QWORD*)(*(__int64*)(Util::GetModuleBaseAddress("engine.dll") + 0x318A638)) + 112i64))(*(__int64*)(Util::GetModuleBaseAddress("engine.dll") + 0x318A638), v9), 0x10000000i64)
            );

        if (strcmp(v9, CMDSTR_ADD_EXECUTION_MARKER) == 0)
        {
            if (*(_DWORD*)a2 != 3)
                logger->warn("WARNING: INVALID EXECUTION MARKER.");
            return ret;
        }

        //static auto& cmd_source = *(int*)(Util::GetModuleBaseAddress("engine.dll") + 0x2EB6AC0);
        //static auto& cmd_clientslot = *(int*)(Util::GetModuleBaseAddress("engine.dll") + 0x2EB6AC0);
        if (cmd_source != src /* || cmd_clientslot != nClientSlot*/)
            return ret;

        //logger->warn("Cmd_ExecuteCommand failed executing command: {}", v9);
        static auto& g_pCVar = *(__int64*)(Util::GetModuleBaseAddress("engine.dll") + 0x318A638);
        auto pCommand = (*(__int64(__fastcall**)(__int64, const CHAR*))(*(_QWORD*)g_pCVar + 112i64))(g_pCVar, v9);// const ConCommandBase *pCommand = g_pCVar->FindCommandBase( command[ 0 ] );
        static auto& g_iFilterCommandsByServerCanExecute = *(int*)(Util::GetModuleBaseAddress("engine.dll") + 0x2EB6AC4);
        static auto Host_IsSinglePlayerGame = (bool(*)())(Util::GetModuleBaseAddress("engine.dll") + 0x130400);
        if (!Host_IsSinglePlayerGame() && g_iFilterCommandsByServerCanExecute > 0 && pCommand)
        {
            if (!(*(unsigned __int8(__fastcall**)(__int64, __int64))(*(_QWORD*)pCommand + 16i64))(pCommand, 0x10000000i64))// !pCommand->IsFlagSet( FCVAR_SERVER_CAN_EXECUTE )
                logger->warn("FCVAR_SERVER_CAN_EXECUTE prevented server running command: {} (src:{})", v9, src); // v9 is not pCommand->GetName, but maybe it'll do...
        }
    }
    return ret;
}
//

//
HookedFuncStatic<bool __fastcall, __int64, __int64, bool> CBaseClientState_InternalProcessStringCmd("engine.dll", 0x22DD0);
bool __fastcall CBaseClientState__InternalProcessStringCmd_Hook(__int64 thisptr, __int64 msg, bool bIsHLTV) {
    //signed int v10[260];
    //unsigned __int8* v11 = nullptr;

    auto ret = CBaseClientState_InternalProcessStringCmd(thisptr, msg, bIsHLTV);

    /*static auto& g_pCVar = *(__int64*)(Util::GetModuleBaseAddress("engine.dll") + 0x318A638);
    static auto& m_State_dword_182966168 = *(int*)(Util::GetModuleBaseAddress("engine.dll") + 0x2966168);
    if (m_State_dword_182966168 >= 2) return true; // ignore for listenserver

    static auto CCommand_constructor = (__int64(__fastcall *)(__int64))(Util::GetModuleBaseAddress("engine.dll") + 0x4806B0);
    static auto CCommand_Tokenize = (char(__fastcall *)(signed int*, const void*))(Util::GetModuleBaseAddress("engine.dll") + 0x4812D0);
    CCommand_constructor((__int64)v10);
    CCommand_Tokenize(v10, *(const void**)(msg + 32));
    auto argc = v10[0];*/

    auto fullStr = *(const char**)(msg + 32);
    /*auto pCommand = (*(__int64(__fastcall**)(__int64, const CHAR*))(*(_QWORD*)g_pCVar + 112i64))(g_pCVar, (const char*)v11);
    auto isRestricted = pCommand && !(*(unsigned __int8(__fastcall**)(__int64, __int64))(*(_QWORD*)pCommand + 16i64))(pCommand, 0x10000000i64);*/
    static auto logger = spdlog::get("logger");

    /*if (isRestricted)
        logger->warn("[StringCmd] {} (no FCVAR_SERVER_CAN_EXECUTE)", fullStr);
    else*/
        logger->info("[StringCmd] {}", fullStr);
    

    return ret;
}
//

SourceConsole::SourceConsole(spdlog::level::level_enum level) :
    //m_gameConsole(_("client.dll"), _("GameConsole004"))
    m_gameConsole("client.dll", "GameConsole004")
{
    m_logger = spdlog::get(_("logger"));

    m_sink = std::make_shared<SourceConsoleSink>(this);
    m_sink->set_pattern(_("%v")); // [%l] 
    m_sink->set_level(level);
    m_logger->sinks().push_back(m_sink);

    ConCommandManager& conCommandManager = SDK().GetConCommandManager();
    conCommandManager.RegisterCommand("toggleconsole", WRAPPED_MEMBER(ToggleConsoleCommand), "Show/hide the console", 0);
    conCommandManager.RegisterCommand("clear", WRAPPED_MEMBER(ClearConsoleCommand), "Clears the console", 0);

    SVC_Print_Process.Hook(SVC_Print_Process_Hook);
    //Cmd_ExecuteCommand.Hook(Cmd_ExecuteCommand_Hook); // disable for now
    CBaseClientState_InternalProcessStringCmd.Hook(CBaseClientState__InternalProcessStringCmd_Hook);
}

void SourceConsole::InitializeSource()
{
    m_gameConsole->Initialize();
    CConsoleDialog_OnCommandSubmitted.Hook(m_gameConsole->m_pConsole->m_vtable, WRAPPED_MEMBER(OnCommandSubmittedHook));
}

void SourceConsole::Deinitialize()
{
    auto& sinks = m_logger->sinks();
    sinks.erase(std::remove(sinks.begin(), sinks.end(), m_sink), sinks.end());
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
    if (!m_gameConsole->m_bInitialized || !IsSDKReady())
    {
        return;
    }

    m_gameConsole->m_pConsole->m_pConsolePanel->ColorPrint(clr, pMessage);
}

void SourceConsole::Print(const char* pMessage)
{
    if (!m_gameConsole->m_bInitialized || !IsSDKReady())
    {
        return;
    }

    m_gameConsole->m_pConsole->m_pConsolePanel->Print(pMessage);
}

void SourceConsole::DPrint(const char* pMessage)
{
    if (!m_gameConsole->m_bInitialized || !IsSDKReady())
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
    if (!IsSDKReady()) return;
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