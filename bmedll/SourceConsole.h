#pragma once
#include "pch.h"
#include "VTableHooking.h"
#include "ConCommandManager.h"

class EditablePanel
{
public:
    virtual ~EditablePanel() = 0;
    unsigned char unknown[0x2A8];
};

struct SourceColor
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;

    SourceColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }

    SourceColor()
    {
        R = 0;
        G = 0;
        B = 0;
        A = 0;
    }
};

class IConsoleDisplayFunc
{
public:
    virtual void ColorPrint(const SourceColor& clr, const char* pMessage) = 0;
    virtual void Print(const char* pMessage) = 0;
    virtual void DPrint(const char* pMessage) = 0;
};

class CConsolePanel : public EditablePanel, public IConsoleDisplayFunc
{

};

class CConsoleDialog
{
public:
    struct VTable
    {
        void* unknown[298];
        void(*OnCommandSubmitted)(CConsoleDialog* consoleDialog, const char* pCommand);
    };

    VTable* m_vtable;
    //unsigned char unknown[0x398];
    unsigned char unknown[0x390];
    CConsolePanel* m_pConsolePanel;
};

class CGameConsole
{
public:
    virtual ~CGameConsole() = 0;

    // activates the console, makes it visible and brings it to the foreground
    virtual void Activate() = 0;

    virtual void Initialize() = 0;

    // hides the console
    virtual void Hide() = 0;

    // clears the console
    virtual void Clear() = 0;

    // return true if the console has focus
    virtual bool IsConsoleVisible() = 0;

    virtual void SetParent(int parent) = 0;

    bool m_bInitialized;
    CConsoleDialog* m_pConsole;
};

class SourceConsoleSink;

class SourceConsole
{
public:
    SourceConsole(ConCommandManager& conCommandManager, spdlog::level::level_enum level);
    void InitialiseSource();

    void ToggleConsoleCommand(const CCommand& args);
    void ClearConsoleCommand(const CCommand& args);

    void OnCommandSubmittedHook(CConsoleDialog* consoleDialog, const char* pCommand);

    void ColorPrint(const SourceColor& clr, const char* pMessage);
    void Print(const char* pMessage);
    void DPrint(const char* pMessage);

private:
    std::shared_ptr<spdlog::logger> m_logger;
    std::shared_ptr<SourceConsoleSink> m_sink;
    SourceInterface<CGameConsole> m_gameConsole;
    HookedVTableFunc<decltype(&CConsoleDialog::VTable::OnCommandSubmitted), &CConsoleDialog::VTable::OnCommandSubmitted> CConsoleDialog_OnCommandSubmitted;
};

class SourceConsoleSink : public spdlog::sinks::base_sink<std::mutex>
{
public:
    SourceConsoleSink(SourceConsole* console);

protected:
    void sink_it_(const spdlog::details::log_msg& msg) override;
    void flush_() override;

private:
    std::map<spdlog::level::level_enum, SourceColor> m_colours;
    SourceConsole* m_console;
};