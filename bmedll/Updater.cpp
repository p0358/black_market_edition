#include "pch.h"
#include "_version.h"
#include "TTFSDK.h"
#include "Updater.h"

namespace Updater
{

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
        if (curl)
        {
            form = curl_mime_init(curl);

            field = curl_mime_addpart(form);
            curl_mime_name(field, "ver");
            curl_mime_data(field, BME_VERSION, CURL_ZERO_TERMINATED);

            field = curl_mime_addpart(form);
            curl_mime_name(field, "env");
            curl_mime_data(field, GetBMEChannel().c_str(), CURL_ZERO_TERMINATED);

            curl_easy_setopt(curl, CURLOPT_URL, "https://bme.titanfall.top/backend/update_check.php");
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "BME/" BME_VERSION);
            curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            res = curl_easy_perform(curl);

            if (!IsSDKReady())
            {
                spdlog::warn("Update check: failure, game is already shutting down or SDK not ready");
                curl_easy_cleanup(curl);
                return false;
            }

            if (res != CURLE_OK)
            {
                spdlog::error("Update check: curl_easy_perform() failed: {}", curl_easy_strerror(res));
                return false;
            }

            curl_easy_cleanup(curl);
            curl_mime_free(form);
        }

        if (readBuffer.empty())
        {
            spdlog::error("Update check: readBuffer empty");
            return false;
        }

        if (document->Parse(readBuffer.c_str()).HasParseError())
        {
            spdlog::error("Update check: failed parsing JSON");
            return false;
        }

        if (!document->IsObject() && document->IsBool())
        {
            // no updates!
            return false;
        }

        return true;
    }

    //////////////////

    double updaterNowDownloaded = 0;
    double updaterTotalToDownload = 1;
    bool isUpdaterDownloadInProgress = false;
    bool isUpdaterDownloadCancelled = false;
    double updaterDownloadProgress = 0.0f;
    std::string updater_url;
    std::string updater_url_final;
    std::wstring updater_path;
    std::string params;

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
        updaterDownloadProgress = 0.0;

        CURL* curl;
        FILE* fp;
        CURLcode res;

        wchar_t temp[MAX_PATH];
        if (!GetTempPathW(MAX_PATH - 16, temp)) return L""; //return NULL;
        std::wstring outfilename{ temp };
        outfilename += L"bme_updater.exe";

        spdlog::info("Gonna save update to: {}", Util::Narrow(outfilename));

        curl = curl_easy_init();
        if (curl)
        {
            fp = _wfopen(outfilename.c_str(), L"wb");
            if (!fp)
            {
                spdlog::error("Failed opening file for writing");
                curl_easy_cleanup(curl);
                return L"";
            }

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
            curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirects
            res = curl_easy_perform(curl);
            isUpdaterDownloadInProgress = false;

            auto size = ftell(fp);
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

            char* url = nullptr;
            curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
            if (url)
                updater_url_final = url;

            curl_easy_cleanup(curl);
            fclose(fp);

            if (res != CURLE_OK)
            {
                spdlog::error("Update download error, curl code is not CURLE_OK: {}", (int)res);
                return L"";
            }
            if (response_code != 200)
            {
                spdlog::error("Update download error, response status code is not 200: {}", response_code);
                return L"";
            }
            if (size == 0)
            {
                spdlog::error("Update download error, file size is 0");
                return L"";
            }
        }

        if (fs::exists(outfilename))
            return outfilename;

        spdlog::error("Update download error, file doesn't exist at the location: {}", Util::Narrow(outfilename));
        return L"";
    }

    bool pendingUpdateLaunch = false;
    bool pendingUpdateLaunchMotdChange = false;
    bool updateInProcess = false;
    bool updaterDownloadFailed = false;
    bool isUpdaterLaunching = false;
    bool drawModalWillUpdaterLaunchAfterGameClose = false;

    void LaunchUpdater()
    {
        isUpdaterLaunching = true; // TODO: in case UI drawing causes crash, move this to the bottom?

        auto logger = spdlog::get("logger");
        RegisterApplicationRestart(GetCommandLineW(), 0);

        STARTUPINFOW si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        std::wstring params2 = L"\"";
        params2 += updater_path;
        params2 += L"\" ";
        params2 += Util::Widen(params);

        logger->info("Firing up BME updater...");
        logger->info("Path: {}", Util::Narrow(updater_path));
        logger->info("Params: {}", params);

        if (!CreateProcessW(updater_path.c_str(), (LPWSTR)params2.c_str(), NULL, NULL, false, 0, NULL, NULL, &si, &pi))
        {
            auto error_code = GetLastError();
            auto error_msg = std::string("Failed to launch process, last error: [") + std::to_string(error_code) + "] " + std::system_category().message(error_code);
            MessageBoxA(nullptr, error_msg.c_str(), "BME Update Error", MB_ICONERROR);
            if (pi.hThread && pi.hThread != INVALID_HANDLE_VALUE) CloseHandle(pi.hThread);
            if (pi.hProcess && pi.hProcess != INVALID_HANDLE_VALUE) CloseHandle(pi.hProcess);
            return;
        }

        bool success = pi.hProcess && pi.hProcess != INVALID_HANDLE_VALUE;
        auto error_code = GetLastError();
        if (pi.hThread && pi.hThread != INVALID_HANDLE_VALUE) CloseHandle(pi.hThread);
        if (pi.hProcess && pi.hProcess != INVALID_HANDLE_VALUE) CloseHandle(pi.hProcess);

        if (!success)
        {
            auto error_msg = std::string("Failed to launch process, last error: [") + std::to_string(error_code) + "] " + std::system_category().message(error_code);
            MessageBoxA(nullptr, error_msg.c_str(), "BME Update Error", MB_ICONERROR);
        }

        /*if (&SDK() != nullptr)
            FreeSDK();

        if (g_console)
            g_console.reset();*/
    }

    DWORD WINAPI DownloadAndApplyUpdate(LPVOID lpThreadParameter)
    {
        Sleep(1);
        auto logger = spdlog::get("logger");
        logger->info("Checking for updates...");

        rapidjson::Document d;
        bool result = QueryServerForUpdates(&d);
        if (result == false || !d.IsObject())
        {
            logger->info("No updates found.");
            return 0;
        }

        updateInProcess = true;
        updater_url = { d["updater_url"].GetString(), d["updater_url"].GetStringLength() };
        logger->info("Found an update, downloading updater...");
        logger->info("Downloading from: {}", updater_url);

        updater_path = SaveUpdaterFile(updater_url);
        if (Updater::isUpdaterDownloadCancelled)
        {
            logger->error("Update cancelled by user.");
            return 0;
        }
        // TODO: poni¿sze jako MsgBox?
        if (updater_path.empty())
        {
            logger->error("Found BME update, but could not save the file to user's temp directory. Check in with your antivirus software and create a whitelist entry.");
            updaterDownloadFailed = true;
            pendingUpdateLaunchMotdChange = true;
            return 0;
        }

        logger->info("Updater saved to: {}", Util::Narrow(updater_path));

        params = std::string(d["updater_params"].GetString());
        params = std::regex_replace(params, std::regex("\\$dir"), GetThisPath());

        logger->info("Updater command line params: {}", params);

        logger->info("====");
        logger->info("BME updater will be fired up after you close your game.");
        logger->info("If you wish to skip this update, you can set cvar in console: bme_skip_update 1");
        logger->info("Alternatively, if you wish to never check for updates in the future, you can use the command line option: -bmenoupdates");
        logger->info("====");

        pendingUpdateLaunch = true; // change, we will always launch updater after game close...
        pendingUpdateLaunchMotdChange = true;
        if (&SDK() != nullptr && SDK().runFrameHookCalled)
        {
            //pendingUpdateLaunch = true;
            //logger->info("Game is already launched, delaying update until it's quit.");
        }
        else
        {
            //LaunchUpdater();
            drawModalWillUpdaterLaunchAfterGameClose = true;
        }
        return 0;
    }

    void InformAboutUpdates()
    {
        //SPDLOG_LOGGER_DEBUG(m_logger, "set updater motd");
        const char* motdcmd;
        if (Updater::updaterDownloadFailed)
            motdcmd = "motd \"^FF000000Found BME update, but could not save the file to user's temp directory. Check in with your antivirus software and create a whitelist entry. See console or bme.log for more details. Alternatively, download the latest version from GitHub.\"";
        else
            motdcmd = "motd \"^00FF0000Black Market Edition update is pending! It will be installed after you exit your game. More information available in console and bme.log. If the installer doesn't start automatically, download the latest version from GitHub.\"";
        SDK().GetEngineClient()->ClientCmd_Unrestricted(motdcmd);

        auto logger = spdlog::get("logger");

        if (!Updater::updaterDownloadFailed)
        {
            logger->info("");
            logger->info("");
            logger->info("==========================================================");
            logger->info("= BME updater will be fired up after you close your game.");
            logger->info("= If you wish to skip this update, you can set cvar in console: bme_skip_update 1");
            logger->info("= Alternatively, if you wish to never check for updates in the future, you can use the command line option: -bmenoupdates");
            logger->info("==========================================================");
            logger->info("");
            logger->info("");

            logger->info("Updater URL:");
            logger->info("{}", updater_url);
            logger->info("");
            if (updater_url_final.size() && updater_url_final != updater_url)
            {
                logger->info("Updater URL (effective):");
                logger->info("{}", updater_url_final);
                logger->info("");
            }
            logger->info("Updater saved location:");
            logger->info("{}", Util::Narrow(updater_path));
            logger->info("");
            logger->info("Updater command line params:");
            logger->info("{}", params);
            logger->info("");
        }
    }

    void CheckForUpdates()
    {
        CreateThread(NULL, 0, DownloadAndApplyUpdate, NULL, 0, NULL);
    }

}