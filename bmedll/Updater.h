#pragma once
#include <rapidjson/document.h>

namespace Updater {
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	bool QueryServerForUpdates(rapidjson::Document* document);
	size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream);
	int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded);
	std::wstring SaveUpdaterFile(std::string url);

	extern bool pendingUpdateLaunch;
	extern bool pendingUpdateLaunchMotdChange;
	extern bool updateInProcess;
	extern std::wstring updater_path;
	extern std::string params;

	extern bool isUpdaterDownloadInProgress;
	extern bool isUpdaterDownloadCancelled;
	extern double updaterDownloadProgress;
	extern double updaterNowDownloaded;
	extern double updaterTotalToDownload;
	extern bool isUpdaterLaunching;
	extern bool drawModalWillUpdaterLaunchAfterGameClose;

	void LaunchUpdater();
	DWORD WINAPI DownloadAndApplyUpdate(LPVOID lpThreadParameter);
	void CheckForUpdates();
}