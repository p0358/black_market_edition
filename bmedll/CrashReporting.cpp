#include "pch.h"
#include "SigScanning.h"

#ifdef NDEBUG
#include "client/windows/handler/exception_handler.h"
#include "_version.h"
#include "TTFSDK.h"

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
        //MessageBox(NULL, L"TEST, on before crash upload", L"Error", MB_OK | MB_ICONERROR);
        bool upload_ok = false;
        CURLcode res;
        {
            std::wstringstream ss;
            ss << dump_path << '\\' << minidump_id << ".dmp";
            std::string filepath = Util::Narrow(ss.str());
            //MessageBoxA(NULL, filepath.c_str(), "AAA", MB_OK | MB_ICONERROR);

            CURL* curl;
            //CURLcode res;

            curl_mime* form = NULL;
            curl_mimepart* field = NULL;
            //struct curl_slist* headerlist = NULL;
            //static const char buf[] = "Expect:";

            //curl_global_init(CURL_GLOBAL_ALL);

            curl = curl_easy_init();
            if (curl) {
                form = curl_mime_init(curl);

                field = curl_mime_addpart(form);
                curl_mime_name(field, "upload_file_minidump");
                curl_mime_filedata(field, filepath.c_str());

                {
                    field = curl_mime_addpart(form);
                    curl_mime_name(field, "sentry[release]");
                    std::stringstream verss; verss << "bme-v" << BME_VERSION;
                    curl_mime_data(field, verss.str().c_str(), CURL_ZERO_TERMINATED);
                }

                field = curl_mime_addpart(form);
                curl_mime_name(field, "sentry[environment]"); // consider adding "dist", especially if you ever report dev reports
                curl_mime_data(field, GetBMEChannel().c_str(), CURL_ZERO_TERMINATED);

                if (IsSDKReady()) {
                    TFOrigin* origin = SDK().origin;
                    if (origin) {
                        if (origin->uid)
                        {
                            field = curl_mime_addpart(form);
                            curl_mime_name(field, "originid");
                            std::stringstream ss; ss << origin->uid;
                            curl_mime_data(field, ss.str().c_str(), CURL_ZERO_TERMINATED);
                        }

                        if (origin->playerName && *origin->playerName)
                        {
                            field = curl_mime_addpart(form);
                            curl_mime_name(field, "originname");
                            curl_mime_data(field, origin->playerName, CURL_ZERO_TERMINATED);
                        }
                    }
                }

                curl_easy_setopt(curl, CURLOPT_URL, "https://o487146.ingest.sentry.io/api/5545628/minidump/?sentry_key=45d18041edb24b1f8f25f144d121cff3");
                curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);

                res = curl_easy_perform(curl);

                //if (res != CURLE_OK)
                //    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                upload_ok = res == CURLE_OK;

                curl_easy_cleanup(curl);
                curl_mime_free(form);
            }
        }


        if (upload_ok)
        MessageBox(NULL, L"An error occurred and Titanfall needs to close. A crash dump has been written to the crash_dumps folder and uploaded.", L"Error", MB_OK | MB_ICONERROR);
        else
        {
            //MessageBox(NULL, L"An error occurred and Titanfall needs to close. A crash dump has been written to the crash_dumps folder.", L"Error", MB_OK | MB_ICONERROR);
            std::wstring cws{ L"An error occurred and Titanfall needs to close. A crash dump has been written to the crash_dumps folder.\n\nUploading it failed with message:\n" };
            cws += Util::Widen(curl_easy_strerror(res));
            MessageBox(NULL, cws.c_str(), L"Error", MB_OK | MB_ICONERROR);
        }
        //std::string cs{ curl_easy_strerror(res) };
        //std::wstring cws = Util::Widen(cs);
        //MessageBox(NULL, cws.c_str(), L"Error", MB_OK | MB_ICONERROR);
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

bool SetupBreakpad(std::string BasePath)
{
    fs::path basePath(BasePath);
    //fs::path basePath(".");
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

bool SetupBreakpad(std::string BasePath)
{
    return false;
}

void UpdateSETranslator()
{
    return;
}

#endif