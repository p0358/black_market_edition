#include "pch.h"
#include "Console.h"
#include "Util.h"

Console::Console()
    : m_winConsole(), m_conOut("CONOUT$", "w", stdout), m_conIn("CONIN$", "r", stdin)
{
    RemoveMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
    SetConsoleCtrlHandler(NULL, TRUE);
}

Console::~Console()
{
    SetConsoleCtrlHandler(NULL, FALSE);
}

FileStreamWrapper::FileStreamWrapper(const char* filename, const char* mode, FILE* oldStream) : m_file(nullptr)
{
    errno_t err = freopen_s(&m_file, filename, mode, oldStream);
    if (err != 0)
    {
        throw std::exception("Failed to reopen"); // TODO: better exception
    }
}

FileStreamWrapper::~FileStreamWrapper()
{
    if (m_file != nullptr)
    {
        fclose(m_file);
        m_file = nullptr;
    }
}

WindowsConsole::WindowsConsole()
{
    if (!AllocConsole())
    {
        if (!AttachConsole(GetCurrentProcessId())) {
            if (GetLastError() == 5) // this error means the console is already attached
                return;
            //throw std::exception("Failed to AllocConsole()"); // TODO: better exception
            std::stringstream e;
            e << "Failed to allocate console or attach to an existing console";
            e << " (";
            e << GetLastError();
            e << "): ";
            e << Util::GetLastErrorAsString();
            throw std::exception(e.str().c_str()); // TODO: better exception
        }
    }
}

WindowsConsole::~WindowsConsole()
{
    FreeConsole();
}