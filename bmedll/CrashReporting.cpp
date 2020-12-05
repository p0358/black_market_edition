#include "pch.h"
#include "SigScanning.h"

#ifdef NDEBUG
#include "client/windows/handler/exception_handler.h"

google_breakpad::ExceptionHandler* g_breakpadHandler;
LONG(*g_breakpadHandleException)(EXCEPTION_POINTERS* exinfo);

SigScanFunc<void*, _se_translator_function> engine_set_se_translator(_("engine.dll"), "\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x00\x48\x8B\xF9\xE8\x00\x00\x00\x00\x48\x8B\x98\x00\x00\x00\x00", "xxxx?xxxx?xxxx????xxx????");

bool DumpCompleted(const wchar_t* dump_path,
    const wchar_t* minidump_id,
    void* context,
    EXCEPTION_POINTERS* exinfo,
    MDRawAssertionInfo* assertion,
    bool succeeded)
{
    if (succeeded)
    {
        MessageBox(NULL, L"An error occurred and Titanfall needs to close. A crash dump has been written to the crash_dumps folder.", L"Error", MB_OK | MB_ICONERROR);
    }
    else
    {
        MessageBox(NULL, L"An error occurred and Titanfall needs to close.", L"Error", MB_OK | MB_ICONERROR);
    }

    return succeeded;
}

void TranslatorFunc(unsigned int, struct _EXCEPTION_POINTERS* exinfo)
{
    g_breakpadHandleException(exinfo);
    TerminateProcess(GetCurrentProcess(), 100);
}

bool SetupBreakpad()
{
    //fs::path basePath(settings.BasePath);
    fs::path basePath(".");
    fs::path crashDumpsPath(basePath / _("crash_dumps"));
    fs::create_directories(crashDumpsPath);

    g_breakpadHandler = new google_breakpad::ExceptionHandler(
        crashDumpsPath.wstring(),
        nullptr,
        DumpCompleted,
        nullptr,
        google_breakpad::ExceptionHandler::HANDLER_ALL
    );

    g_breakpadHandleException = SetUnhandledExceptionFilter(nullptr);
    SetUnhandledExceptionFilter(g_breakpadHandleException);

    return true;
}

void UpdateSETranslator()
{
    if (g_breakpadHandleException != nullptr)
    {
        engine_set_se_translator(TranslatorFunc);
    }
}

#else

bool SetupBreakpad()
{
    return false;
}

void UpdateSETranslator()
{
    return;
}

#endif