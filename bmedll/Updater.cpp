#include "pch.h"
#include "_version.h"
#include "TTFSDK.h"
#include "Updater.h"

//#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
//#include <rapidjson/schema.h>
//#include <rapidjson/filereadstream.h>

namespace Updater {

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    bool QueryServerForUpdates(rapidjson::Document* document)
    {
        CURL* curl;
        CURLcode res;

        curl_mime* form = NULL;
        curl_mimepart* field = NULL;

        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            form = curl_mime_init(curl);

            field = curl_mime_addpart(form);
            curl_mime_name(field, "ver");
            curl_mime_data(field, BME_VERSION, CURL_ZERO_TERMINATED);

            field = curl_mime_addpart(form);
            curl_mime_name(field, "env");
            curl_mime_data(field, GetBMEChannel().c_str(), CURL_ZERO_TERMINATED);

            /*{
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
            }*/

            curl_easy_setopt(curl, CURLOPT_URL, "https://bme.titanfall.top/backend/update_check.php");
            curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK)
                return false;
            //fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

            curl_easy_cleanup(curl);
            curl_mime_free(form);
        }

        if (readBuffer.empty()) return false;

        if (document->Parse(readBuffer.c_str()).HasParseError()) return false;

        if (!document->IsObject() && document->IsBool()) return false;
        return true;

    }

    //////////////////

    double updaterNowDownloaded = 0;
    double updaterTotalToDownload = 1;
    bool isUpdaterDownloadInProgress = false;
    bool isUpdaterDownloadCancelled = false;
    float updaterDownloadProgress = 0.0f;

    size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
        size_t written = fwrite(ptr, size, nmemb, stream);
        return written;
    }

    int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
    {
        if (Updater::isUpdaterDownloadCancelled)
            return 1;
        updaterDownloadProgress = NowDownloaded / TotalToDownload;
        updaterNowDownloaded = NowDownloaded;
        updaterTotalToDownload = TotalToDownload;
        return 0;
    }

    std::wstring Updater::SaveUpdaterFile(std::string url)
    {
        isUpdaterDownloadInProgress = true;
        isUpdaterDownloadCancelled = false;
        updaterDownloadProgress = 0.0f;

        CURL* curl;
        FILE* fp;
        CURLcode res;

        wchar_t temp[MAX_PATH];
        if (!GetTempPath(MAX_PATH - 16, temp)) return NULL;
        std::wstring outfilename{ temp };
        outfilename += L"bme_updater.exe";

        curl = curl_easy_init();
        if (curl) {
            fp = _wfopen(outfilename.c_str(), L"wb");
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
            curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);
            res = curl_easy_perform(curl);
            isUpdaterDownloadInProgress = false;

            if (res != CURLE_OK) return NULL;

            curl_easy_cleanup(curl);
            fclose(fp);
        }

        return outfilename;
    }

    bool pendingUpdateLaunch = false;
    bool updateInProcess = false;
    std::wstring updater_path;
    std::string params;
    bool isUpdaterLaunching = false;

    void LaunchUpdater()
    {
        isUpdaterLaunching = true; // TODO: in case UI drawing causes crash, move this to the bottom?

        auto logger = spdlog::get(_("logger"));
        RegisterApplicationRestart(GetCommandLine(), 0);

        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        std::wstring params2 = Util::Widen(params);

        logger->info(_("Firing up BME updater..."));
        SPDLOG_LOGGER_DEBUG(logger, _("Path: {}"), Util::Narrow(updater_path));
        SPDLOG_LOGGER_DEBUG(logger, _("Params: {}"), params);

        CreateProcessW(updater_path.c_str(), (LPWSTR)params2.c_str(), NULL, NULL, false, 0, NULL, NULL, &si, &pi);

        /*if (&SDK() != nullptr)
            FreeSDK();

        if (g_console)
            g_console.reset();*/
    }

    DWORD WINAPI DownloadAndApplyUpdate(LPVOID lpThreadParameter)
    {
        Sleep(1);
        auto logger = spdlog::get(_("logger"));
        logger->info(_("Checking for updates..."));

        rapidjson::Document d;
        bool result = QueryServerForUpdates(&d);
        if (result == false || !d.IsObject())
        {
            logger->info(_("No updates found."));
            return 0;
        }

        updateInProcess = true;
        logger->info(_("Found an update, downloading updater..."));

        updater_path = SaveUpdaterFile(d["updater_url"].GetString());
        // TODO: poni¿sze jako MsgBox?
        if (updater_path.empty())
        {
            logger->error(_("Found update, but could not save the file to user's temp directory. Check in with your antivirus software and create a whitelist entry."));
            return 0;
        }

        logger->info(_("Updater saved."));

        params = std::string(d["updater_params"].GetString());
        params = std::regex_replace(params, std::regex("\\$dir"), GetThisPath());

        if (&SDK() != nullptr && SDK().runFrameHookCalled)
        {
            pendingUpdateLaunch = true;
            logger->info(_("Game is already launched, delaying update until it's quit."));
        }
        else
        {
            LaunchUpdater();
        }
        return 0;
    }

    void CheckForUpdates()
    {
        CreateThread(NULL, 0, DownloadAndApplyUpdate, NULL, 0, NULL);
    }

}