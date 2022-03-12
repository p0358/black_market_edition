#include "pch.h"
#include "CrashReporting.h"
#include "SigScanning.h"

#ifdef NDEBUG
#include "_version.h"
#include "TTFSDK.h"

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
    case SENTRY_LEVEL_DEBUG:
        logger->debug("[sentry] {}", buf);
        break;
    case SENTRY_LEVEL_INFO:
        logger->info("[sentry] {}", buf);
        break;
    case SENTRY_LEVEL_WARNING:
        logger->warn("[sentry] {}", buf);
        break;
    case SENTRY_LEVEL_ERROR:
        logger->error("[sentry] {}", buf);
        break;
    case SENTRY_LEVEL_FATAL:
        logger->critical("[sentry] {}", buf);
        break;
    default:
        break;
    }
}

bool SetupCrashHandler(std::wstring BasePath)
{
    sentry_options_t* options = sentry_options_new();
    sentry_options_set_logger(options, sentry_logger_spdlog, spdlog::get("logger").get());
    
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

    if (strstr(GetCommandLineA(), "-crashhandlernoupload"))
    {
        sentry_options_set_sample_rate(options, 0.0);
        sentry_options_set_traces_sample_rate(options, 0.0);
    }
    else
        sentry_options_set_dsn(options, "https://45d18041edb24b1f8f25f144d121cff3@o487146.ingest.sentry.io/5545628");

    sentry_init(options);

    AddVectoredExceptionHandler(1, &::VectoredExceptionHandler);

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