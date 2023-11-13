#include "pch.h"
#include "CrashReporting.h"
#include "SigScanning.h"

#ifdef NDEBUG
#include <ehdata.h>
#include <dbghelp.h>
#include "_version.h"
#include "TTFSDK.h"
#include "tier0.h"

// this sig may be wrong
SigScanFunc<void*, _se_translator_function> engine_set_se_translator(_("engine.dll"), "\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x00\x48\x8B\xF9\xE8\x00\x00\x00\x00\x48\x8B\x98\x00\x00\x00\x00", "xxxx?xxxx?xxxx????xxx????");
FuncStatic<void*, _se_translator_function> engine_set_se_translator2("engine.dll", 0x56BC04);

void TranslatorFunc(unsigned int, struct _EXCEPTION_POINTERS* exinfo)
{
    sentry_handle_exception(reinterpret_cast<const sentry_ucontext_t*>(exinfo));
}

LONG WINAPI VectoredExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo)
{
    const auto& exceptionCode = pExceptionInfo->ExceptionRecord->ExceptionCode;

    if (exceptionCode != EXCEPTION_ACCESS_VIOLATION && exceptionCode != EXCEPTION_ARRAY_BOUNDS_EXCEEDED &&
        exceptionCode != EXCEPTION_DATATYPE_MISALIGNMENT && exceptionCode != EXCEPTION_FLT_DENORMAL_OPERAND &&
        exceptionCode != EXCEPTION_FLT_DIVIDE_BY_ZERO && exceptionCode != EXCEPTION_FLT_INEXACT_RESULT &&
        exceptionCode != EXCEPTION_FLT_INVALID_OPERATION && exceptionCode != EXCEPTION_FLT_OVERFLOW &&
        exceptionCode != EXCEPTION_FLT_STACK_CHECK && exceptionCode != EXCEPTION_FLT_UNDERFLOW &&
        exceptionCode != EXCEPTION_ILLEGAL_INSTRUCTION && exceptionCode != EXCEPTION_IN_PAGE_ERROR &&
        exceptionCode != EXCEPTION_INT_DIVIDE_BY_ZERO && exceptionCode != EXCEPTION_INT_OVERFLOW &&
        exceptionCode != EXCEPTION_INVALID_DISPOSITION && exceptionCode != EXCEPTION_NONCONTINUABLE_EXCEPTION &&
        exceptionCode != EXCEPTION_PRIV_INSTRUCTION && exceptionCode != EXCEPTION_STACK_OVERFLOW)
        return EXCEPTION_CONTINUE_SEARCH;

    //sentry_ucontext_t ctx{ .exception_ptrs = *pExceptionInfo };
    //sentry_handle_exception(&ctx);
    sentry_handle_exception(reinterpret_cast<const sentry_ucontext_t*>(pExceptionInfo));
    return EXCEPTION_EXECUTE_HANDLER;

    //return EXCEPTION_CONTINUE_SEARCH;
}

LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* exception_pointers)
{
    sentry_handle_exception(reinterpret_cast<const sentry_ucontext_t*>(exception_pointers));
    return EXCEPTION_CONTINUE_SEARCH;
}

void sentry_logger_spdlog(sentry_level_t level, const char* message, va_list args, void* userdata)
{
    // process format
    char buf[1024]{};
    vsprintf(buf, message, args);

    auto* logger = (spdlog::logger*)userdata;

    // write to spdlog
    switch (level) {
    case SENTRY_LEVEL_DEBUG: logger->debug("[sentry] {}", buf); break;
    case SENTRY_LEVEL_INFO: logger->info("[sentry] {}", buf); break;
    case SENTRY_LEVEL_WARNING: logger->warn("[sentry] {}", buf); break;
    case SENTRY_LEVEL_ERROR: logger->error("[sentry] {}", buf); break;
    case SENTRY_LEVEL_FATAL: logger->critical("[sentry] {}", buf); break;
    default: break;
    }
}

// just log basic exception info directly into the log for informative purposes
// so that it's not always needed to fire up a debugger to analyse the dump
void log_exception_info(const EXCEPTION_POINTERS* exceptionInfo)
{
    if (!exceptionInfo)
        return;

    const auto* exceptionRecord = exceptionInfo->ExceptionRecord;
    const DWORD exceptionCode = exceptionRecord->ExceptionCode;

    const char* exceptionCause = nullptr;
    switch (exceptionCode)
    {
    case EXCEPTION_ACCESS_VIOLATION: exceptionCause = "Access Violation"; break;
    case EXCEPTION_IN_PAGE_ERROR: exceptionCause = "Access Violation (In-Page Error)"; break;
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: exceptionCause = "Array bounds exceeded"; break;
    case EXCEPTION_DATATYPE_MISALIGNMENT: exceptionCause = "Datatype misalignment"; break;
    case EXCEPTION_FLT_DENORMAL_OPERAND: exceptionCause = "Float denormal operand"; break;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO: exceptionCause = "Divide by zero (float)"; break;
    case EXCEPTION_INT_DIVIDE_BY_ZERO: exceptionCause = "Divide by zero (int)"; break;
    case EXCEPTION_FLT_INEXACT_RESULT: exceptionCause = "Float inexact result"; break;
    case EXCEPTION_FLT_INVALID_OPERATION: exceptionCause = "Float invalid operation"; break;
    case EXCEPTION_INT_OVERFLOW: exceptionCause = "Integer overflow"; break;
    case EXCEPTION_FLT_OVERFLOW: exceptionCause = "Float overflow"; break;
    case EXCEPTION_FLT_UNDERFLOW: exceptionCause = "Float underflow"; break;
    case EXCEPTION_FLT_STACK_CHECK: exceptionCause = "Float stack check"; break;
    case EXCEPTION_ILLEGAL_INSTRUCTION: exceptionCause = "Illegal instruction"; break;
    case EXCEPTION_INVALID_DISPOSITION: exceptionCause = "Invalid disposition"; break;
    case EXCEPTION_NONCONTINUABLE_EXCEPTION: exceptionCause = "Noncontinuable exception"; break;
    case EXCEPTION_PRIV_INSTRUCTION: exceptionCause = "Priviledged instruction"; break;
    case EXCEPTION_STACK_OVERFLOW:  exceptionCause = "Stack overflow"; break;
    case EXCEPTION_BREAKPOINT: exceptionCause = "Breakpoint"; break;
    case EH_EXCEPTION_NUMBER: exceptionCause = "C++ EH Exception"; break;
    case 0xE000000C: exceptionCause = "Tier0 Error"; break;
    default: exceptionCause = nullptr; break;
        break;
    }
    if (exceptionCause)
        spdlog::error("Cause: {}", exceptionCause);
    else
        spdlog::error("Cause: Unknown (0x{0:x})", exceptionCode);

    if (exceptionCode == EXCEPTION_ACCESS_VIOLATION || exceptionCode == EXCEPTION_IN_PAGE_ERROR)
    {
        auto exceptionInfo0 = exceptionRecord->ExceptionInformation[0];
        auto exceptionInfo1 = exceptionRecord->ExceptionInformation[1];

        if (!exceptionInfo0) spdlog::error("Attempted to read from: {}", (void*)exceptionInfo1);
        else if (exceptionInfo0 == 1) spdlog::error("Attempted to write to: {}", (void*)exceptionInfo1);
        else if (exceptionInfo0 == 8) spdlog::error("Data Execution Prevention (DEP) at: {}", (void*)exceptionInfo1);
        else spdlog::error("Unknown access violation at: {}", (void*)exceptionInfo1);

        if (exceptionCode == EXCEPTION_IN_PAGE_ERROR)
        {
            auto exceptionInfo2 = exceptionRecord->ExceptionInformation[2];
            spdlog::error("Underlying NTSTATUS code that resulted in the exception: {}", (void*)exceptionInfo2);
        }
    }
    else if (exceptionCode == EH_EXCEPTION_NUMBER)
    {
        // C++ EH exception
        // https://devblogs.microsoft.com/oldnewthing/20100730-00/?p=13273
        // https://devblogs.microsoft.com/oldnewthing/20200821-00/?p=104112
        // https://stackoverflow.com/a/37058499/4470653
        // https://stackoverflow.com/a/31424553/4470653
        auto* record = reinterpret_cast<const EHExceptionRecord*>(exceptionRecord);
        if (record->NumberParameters >= 4 && record->params.magicNumber == EH_MAGIC_NUMBER1
            && record->params.pExceptionObject && record->params.pThrowInfo && record->params.pThrowImageBase)
        {
            auto* pExceptionObject = record->params.pExceptionObject;
            auto* pThrowInfo = record->params.pThrowInfo;
            auto* pThrowImageBase = record->params.pThrowImageBase;

            auto* pCatchableTypeArray = reinterpret_cast<_s_CatchableTypeArray*>((size_t)pThrowImageBase + pThrowInfo->pCatchableTypeArray);
            auto pCatchableTypeArraySize = pCatchableTypeArray->nCatchableTypes;

            for (int i = 0; i < pCatchableTypeArraySize; i++)
            {
                auto* pCatchableType = reinterpret_cast<_s_CatchableType*>((size_t)pThrowImageBase + pCatchableTypeArray->arrayOfCatchableTypes[i]);
                auto* pCatchableTypeDescriptor = reinterpret_cast<TypeDescriptor*>((size_t)pThrowImageBase + pCatchableType->pType);
                auto* classname = pCatchableTypeDescriptor->name; // mangled

                if (i == 0)
                {
                    char classname_demangled_output[64]{ 0 };
                    if (!UnDecorateSymbolName(classname + 1, classname_demangled_output, 63, UNDNAME_COMPLETE)) [[unlikely]] // +1 because it's prepended with a dot for some reason
                        spdlog::error("UnDecorateSymbolName failed, GetLastError(): {}", GetLastError());
                    char* classname_demangled = classname_demangled_output;
                    while (classname_demangled[0] == ' ' || classname_demangled[0] == '?') // skip leading ' ?? '
                        classname_demangled++;
                    spdlog::error("Type: {} ({})", classname_demangled, classname);
                }

                // most C++ exceptions like std::runtime_error inherit from std::exception
                // pCatchableTypeArray has all the inheritance tree, so we will hit it here at the end
                // and then we can use its common ::what() function
                if (strcmp(classname, ".?AVexception@std@@") == 0)
                {
                    auto* exception = reinterpret_cast<std::exception*>(pExceptionObject);
                    spdlog::error("Message: {}", exception->what());
                    break;
                }
            }
        }
    }

    void* exceptionAddress = exceptionInfo->ExceptionRecord->ExceptionAddress;

    HMODULE crashedModuleHandle;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, static_cast<LPCSTR>(exceptionAddress), &crashedModuleHandle);

    MODULEINFO crashedModuleInfo;
    GetModuleInformation(GetCurrentProcess(), crashedModuleHandle, &crashedModuleInfo, sizeof(crashedModuleInfo));

    char crashedModuleFullName[MAX_PATH];
    GetModuleFileNameExA(GetCurrentProcess(), crashedModuleHandle, crashedModuleFullName, MAX_PATH);
    char* crashedModuleName = strrchr(crashedModuleFullName, '\\') + 1;

    DWORD64 crashedModuleOffset = ((DWORD64)exceptionAddress) - ((DWORD64)crashedModuleInfo.lpBaseOfDll);
    CONTEXT* exceptionContext = exceptionInfo->ContextRecord;

    //spdlog::error("At: {} + {}", crashedModuleName, (void*)crashedModuleOffset);

    PVOID framesToCapture[62];
    int frames = RtlCaptureStackBackTrace(0, 62, framesToCapture, NULL);
    for (int i = 0; i < frames; i++)
    {
        HMODULE backtraceModuleHandle;
        GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, static_cast<LPCSTR>(framesToCapture[i]), &backtraceModuleHandle);

        char backtraceModuleFullName[MAX_PATH];
        GetModuleFileNameExA(GetCurrentProcess(), backtraceModuleHandle, backtraceModuleFullName, MAX_PATH);
        char* backtraceModuleName = strrchr(backtraceModuleFullName, '\\') + 1;

        void* actualAddress = (void*)framesToCapture[i];
        void* relativeAddress = (void*)(uintptr_t(actualAddress) - uintptr_t(backtraceModuleHandle));

        spdlog::error("{}{} + {} ({}){}",
            actualAddress == exceptionAddress ? "==> " : "    ",
            backtraceModuleName, relativeAddress, actualAddress,
            actualAddress == exceptionAddress ? " <==" : "");
    }

    spdlog::error("RAX: 0x{0:x}", exceptionContext->Rax);
    spdlog::error("RBX: 0x{0:x}", exceptionContext->Rbx);
    spdlog::error("RCX: 0x{0:x}", exceptionContext->Rcx);
    spdlog::error("RDX: 0x{0:x}", exceptionContext->Rdx);
    spdlog::error("RSI: 0x{0:x}", exceptionContext->Rsi);
    spdlog::error("RDI: 0x{0:x}", exceptionContext->Rdi);
    spdlog::error("RBP: 0x{0:x}", exceptionContext->Rbp);
    spdlog::error("RSP: 0x{0:x}", exceptionContext->Rsp);
    spdlog::error("R8: 0x{0:x}", exceptionContext->R8);
    spdlog::error("R9: 0x{0:x}", exceptionContext->R9);
    spdlog::error("R10: 0x{0:x}", exceptionContext->R10);
    spdlog::error("R11: 0x{0:x}", exceptionContext->R11);
    spdlog::error("R12: 0x{0:x}", exceptionContext->R12);
    spdlog::error("R13: 0x{0:x}", exceptionContext->R13);
    spdlog::error("R14: 0x{0:x}", exceptionContext->R14);
    spdlog::error("R15: 0x{0:x}", exceptionContext->R15);
}

void log_crash_diagnostic_info(const EXCEPTION_POINTERS* exceptionInfo)
{
    spdlog::error("=====================================================");
    spdlog::error("=====================================================");
    spdlog::error("             A CRASH HAS BEEN CAPTURED!              ");
    spdlog::error("     Diagnostic information will now be printed.     ");
    spdlog::error("=====================================================");
    spdlog::error("=====================================================");

    HMODULE KernelBase = GetModuleHandleA("KernelBase.dll");
    typedef HRESULT(WINAPI* GetThreadDescription_t)(HANDLE, PWSTR*);
    GetThreadDescription_t GetThreadDescription;
    wchar_t* threadDesc = nullptr;
    if (KernelBase)
    {
        bool gotThreadDesc = false;
        GetThreadDescription = (GetThreadDescription_t)GetProcAddress(KernelBase, "GetThreadDescription");
        if (GetThreadDescription)
        {
            GetThreadDescription(GetCurrentThread(), &threadDesc);
            if (threadDesc && wcslen(threadDesc) > 0)
            {
                gotThreadDesc = true;
                spdlog::error("Thread: {} ({})", GetCurrentThreadId(), Util::Narrow(threadDesc));
            }
        }
        if (!gotThreadDesc)
            spdlog::error("Thread: {}", GetCurrentThreadId());
    }
    //if (!KernelBase || !GetThreadDescription || !threadDesc) // thread id itself is already logged by spdlog anyways...
    //	spdlog::error("Thread: {}", GetCurrentThreadId());

    if (exceptionInfo)
    {
        log_exception_info(exceptionInfo);
        spdlog::error("=====================================================");
    }

    if (IsClient())
    {
        auto engineaddr = Util::GetModuleBaseAddress("engine.dll");
        auto CL_SetSteamCrashComment = (void(__fastcall*)())(engineaddr + 0x57060);
        auto materials = *reinterpret_cast<size_t*>(engineaddr + 0x318A688);
        auto videomode = *reinterpret_cast<size_t*>(engineaddr + 0x30EC298);
        extern FuncStaticWithType<void* (__cdecl*)()> get_cl;
        auto cl = get_cl();
        if (materials && videomode && cl)
        {
            spdlog::error("CRASH COMMENT:");
            CL_SetSteamCrashComment();
            auto* g_minidumpinfo = (char*)(engineaddr + 0x2291560);
            spdlog::info("{}", g_minidumpinfo);
            auto dword_182292564 = *(DWORD*)(engineaddr + 0x2292564);
            auto dword_182292560 = *(DWORD*)(engineaddr + 0x2292560);
            if (dword_182292560 || dword_182292564)
                spdlog::info("PP PAGES: used {}, free {}", dword_182292560, dword_182292564);
            //spdlog::error("=====================================================");
        }
    }

#if 0
    if (IsSDKReady())
    {
        auto sqmg = SDK().GetSQManager();
        auto sqstd_aux_printerror = (__int64(__fastcall*)(HSQUIRRELVM))(Util::GetModuleBaseAddress("launcher.dll") + 0x3A5E0); // offset updated for r1
        // you can test those with for example `script_ui TestCrash()`
        if (sqmg.m_pLastServerSQVM != nullptr)
        {
            auto v = sqmg.m_pLastServerSQVM;
            if (v->_top - v->_stackbase >= 1 && v->_callsstacksize > 1)
            {
                spdlog::error("=== SERVER SCRIPT STATE ===");
                sqstd_aux_printerror(v);
            }
        }
        if (sqmg.m_pLastClientSQVM != nullptr)
        {
            auto v = sqmg.m_pLastClientSQVM;
            if (v->_top - v->_stackbase >= 1 && v->_callsstacksize > 1)
            {
                spdlog::error("=== CLIENT SCRIPT STATE ===");
                sqstd_aux_printerror(v);
            }
        }
        if (sqmg.m_pLastUISQVM != nullptr)
        {
            auto v = sqmg.m_pLastUISQVM;
            if (v->_top - v->_stackbase >= 1 && v->_callsstacksize > 1)
            {
                spdlog::error("=== UI SCRIPT STATE ===");
                sqstd_aux_printerror(v);
            }
        }
    }
#endif

    spdlog::error("=====================================================");
    spdlog::error("=====================================================");
    spdlog::error("         END OF CRASH DIAGNOSTIC INFORMATION         ");
    spdlog::error("=====================================================");
    spdlog::error("=====================================================");
}

bool g_hasCrashed;
sentry_value_t sentry_on_crash(const sentry_ucontext_t* uctx, sentry_value_t event, void* closure)
{
    g_hasCrashed = true;

    log_crash_diagnostic_info(&uctx->exception_ptrs);

    if (CommandLine()->CheckParm("-crashdiscard"))
    {
        spdlog::error("Discarding the crash!");
        return sentry_value_new_null(); // will not save the .dmp file...
    }

    return event;
}

bool SetupCrashHandler(std::wstring BasePath)
{
    sentry_options_t* options = sentry_options_new();
    sentry_options_set_logger(options, sentry_logger_spdlog, spdlog::get("logger").get());
    sentry_options_set_on_crash(options, sentry_on_crash, NULL);
    
    sentry_options_set_release(options, "bme-v" BME_VERSION);
    sentry_options_set_environment(options, GetBMEChannel().c_str());

    fs::path basePath{ BasePath };
    fs::path handlerPath{ basePath / "bme" / "crashpad_handler.exe" };
    fs::path dbPath{ basePath / "bme" / "crashpad" };
    fs::create_directories(dbPath);
    sentry_options_set_handler_pathw(options, handlerPath.wstring().c_str());
    sentry_options_set_database_pathw(options, dbPath.wstring().c_str());

    fs::path logPath{ basePath / "bme" / "bme.log" };
    sentry_options_add_attachmentw(options, logPath.wstring().c_str());

#ifdef STAGING
    sentry_options_set_debug(options, 1);
#endif

    if (strstr(GetCommandLineA(), "-crashhandlernoupload") || strstr(GetCommandLineA(), "-bmeoffline"))
    {
        sentry_options_set_sample_rate(options, 0.0);
        sentry_options_set_traces_sample_rate(options, 0.0);
        sentry_options_set_dsn(options, "http://invalid@0.0.0.0/invalid");
    }
    else
        sentry_options_set_dsn(options, "https://45d18041edb24b1f8f25f144d121cff3@o487146.ingest.sentry.io/5545628");

    sentry_init(options);

    AddVectoredExceptionHandler(1, &::VectoredExceptionHandler);

    {
        // Add WINE version metadata if running under WINE
        HMODULE hntdll;
        typedef const char* (CDECL* wine_get_version_t)();
        typedef const char* (CDECL* wine_get_build_id_t)();
        typedef void (CDECL* wine_get_host_version_t)(const char** sysname, const char** release);
        wine_get_version_t wine_get_version;
        wine_get_build_id_t wine_get_build_id;
        wine_get_host_version_t wine_get_host_version;
        if ((hntdll = GetModuleHandleA("ntdll.dll")) && (wine_get_version = reinterpret_cast<wine_get_version_t>(GetProcAddress(hntdll, "wine_get_version"))))
        {
            sentry_value_t wine_ctx = sentry_value_new_object();

            sentry_value_set_by_key(wine_ctx, "version", sentry_value_new_string(wine_get_version())); // example: 7.11
            if (wine_get_build_id = reinterpret_cast<wine_get_build_id_t>(GetProcAddress(hntdll, "wine_get_build_id")))
                sentry_value_set_by_key(wine_ctx, "build", sentry_value_new_string(wine_get_build_id())); // example: wine-7.11
            if (wine_get_host_version = reinterpret_cast<wine_get_host_version_t>(GetProcAddress(hntdll, "wine_get_host_version")))
            {
                const char* sysname; // example: Linux
                const char* release; // example: 5.16.20-2-MANJARO
                wine_get_host_version(&sysname, &release);
                sentry_value_set_by_key(wine_ctx, "sysname", sentry_value_new_string(sysname));
                sentry_value_set_by_key(wine_ctx, "release", sentry_value_new_string(release));
            }

            sentry_set_context("wine", wine_ctx);
        }
    }

    return true;
}

void UpdateSETranslator()
{
    SetUnhandledExceptionFilter(&UnhandledExceptionHandler);
    engine_set_se_translator(TranslatorFunc);
    engine_set_se_translator2(TranslatorFunc);
}

#else

bool SetupCrashHandler(std::wstring BasePath)
{
    return false;
}

void UpdateSETranslator()
{
    return;
}

#endif