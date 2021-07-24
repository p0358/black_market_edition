#include "pch.h"
#include "TTFSDK.h"
#include "BMEGUI.h"
#include "Updater.h"

BMEGUI& GUI()
{
    return SDK().GetBMEGUI();
}

#define WRAPPED_MEMBER(name) MemberWrapper<decltype(&BMEGUI::##name), &BMEGUI::##name, decltype(&GUI), &GUI>::Call

BMEGUI::BMEGUI(ConCommandManager& conCommandManager, UIManager& uiManager/*, SquirrelManager& sqManager*/, FileSystemManager& fsManager)
{
    m_logger = spdlog::get("logger");
    m_uiManager = &uiManager;
    //uiManager.AddDrawCallback("UpdaterDownloadProgress", &Updater::isUpdaterDownloadInProgress, std::bind(&BMEGUI::DrawUpdaterDownloadProgress, this));
    uiManager.AddDrawCallback("UpdaterDownloadProgress", &Updater::isUpdaterDownloadInProgress, WRAPPED_MEMBER(DrawUpdaterDownloadProgress));
    uiManager.AddDrawCallback("DrawUpdaterLaunchingSplashScreen", &Updater::isUpdaterLaunching, WRAPPED_MEMBER(DrawUpdaterLaunchingSplashScreen));
    uiManager.AddDrawCallback("DrawUpdaterAfterGameClose", &Updater::drawModalWillUpdaterLaunchAfterGameClose, WRAPPED_MEMBER(DrawUpdaterAfterGameClose));
}

BMEGUI::~BMEGUI()
{
    SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "BMEGUI destructor");
    m_uiManager->RemoveDrawCallback("UpdaterDownloadProgress");
    m_uiManager->RemoveDrawCallback("DrawUpdaterLaunchingSplashScreen");
}

void BMEGUI::DrawUpdaterDownloadProgress()
{
    if (!Updater::isUpdaterDownloadInProgress) return;
    if (SDK().runFrameHookCalled) return; // only display this until the client launches
    //SPDLOG_LOGGER_TRACE(m_logger, "BMEGUI::DrawUpdaterDownloadProgress");

    //return;
    ImGui::OpenPopup("Black Market Edition Updater"); // UpdaterDownloadProgress

    // Always center this window when appearing
    ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    //SPDLOG_LOGGER_TRACE(m_logger, "BMEGUI::DrawUpdaterDownloadProgress: before popup modal");
    if (ImGui::BeginPopupModal("Black Market Edition Updater", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        //SPDLOG_LOGGER_TRACE(m_logger, "BMEGUI::DrawUpdaterDownloadProgress: before text");
        //std::stringstream ss;
        //ss << "Downloading update..." << " (" << (Updater::updaterNowDownloaded / 1024 / 1024) << "MB/" << (Updater::updaterTotalToDownload / 1024 / 1024) << "MB)";
        ImGui::Text("Downloading update... (%.1fMB/%.1fMB)", Updater::updaterNowDownloaded / 1024 / 1024, Updater::updaterTotalToDownload / 1024 / 1024);
        //ImGui::Text("Downloading update...");

        //ImGui::Separator();


        //static int unused_i = 0;
        //ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

        /*static bool dont_ask_me_next_time = false;
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
        ImGui::PopStyleVar();*/

        //ImGui::ProgressBar(0.6f, ImVec2(0.0f, 0.0f));
        ImGui::ProgressBar(Updater::updaterDownloadProgress, ImVec2(300.0f, 0.0f));

        //ImGui::AlignTextToFramePadding
        //if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        //ImGui::SetItemDefaultFocus();
        //SPDLOG_LOGGER_TRACE(m_logger, "BMEGUI::DrawUpdaterDownloadProgress: before button");
        if (!Updater::isUpdaterDownloadCancelled)
        {
            ImGui::NewLine();
            ImGui::SameLine((ImGui::GetWindowWidth() / 2) - (50 / 2));
            if (ImGui::Button("Cancel", ImVec2(50, 0))) {
                Updater::isUpdaterDownloadCancelled = true;
                Updater::isUpdaterDownloadInProgress = false; // TEMP!!
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::EndPopup();
    }
    //SPDLOG_LOGGER_TRACE(m_logger, "BMEGUI::DrawUpdaterDownloadProgress: end");
}

void BMEGUI::DrawUpdaterLaunchingSplashScreen()
{
    if (!Updater::isUpdaterLaunching) return;
    if (Updater::isUpdaterDownloadInProgress) return; // only one of the two at once!
    //if (Updater::pendingUpdateLaunch) return; // we only want to display it if the game will be closed as a result
    //if (SDK().runFrameHookCalled) return; // TODO: think about this
    //SPDLOG_LOGGER_TRACE(m_logger, "BMEGUI::DrawUpdaterLaunchingSplashScreen");

    //return;
    ImGui::OpenPopup("Black Market Edition Updater");

    // Always center this window when appearing
    ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    //SPDLOG_LOGGER_TRACE(m_logger, "BMEGUI::DrawUpdaterLaunchingSplashScreen: before popup modal");
    if (ImGui::BeginPopupModal("Black Market Edition Updater", &Updater::isUpdaterLaunching, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Launching updater...");
        ImGui::EndPopup();
    }
    //SPDLOG_LOGGER_TRACE(m_logger, "BMEGUI::DrawUpdaterLaunchingSplashScreen: end");
}

void BMEGUI::DrawUpdaterAfterGameClose()
{
    if (Updater::isUpdaterLaunching) return;
    if (Updater::isUpdaterDownloadInProgress) return;
    if (!Updater::drawModalWillUpdaterLaunchAfterGameClose) return;
    //SPDLOG_LOGGER_TRACE(m_logger, "BMEGUI::DrawUpdaterAfterGameClose");

    //return;
    ImGui::OpenPopup("Black Market Edition Updater");

    // Always center this window when appearing
    ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    //SPDLOG_LOGGER_TRACE(m_logger, "BMEGUI::DrawUpdaterLaunchingSplashScreen: before popup modal");
    if (ImGui::BeginPopupModal("Black Market Edition Updater", &Updater::isUpdaterLaunching, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Update has been downloaded and its installer will be launched after you close your game.");

        ImGui::NewLine();
        ImGui::SameLine((ImGui::GetWindowWidth() / 2) - (50 / 2));
        if (ImGui::Button("OK", ImVec2(50, 0))) {
            Updater::drawModalWillUpdaterLaunchAfterGameClose = false; // stop drawing
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
    //SPDLOG_LOGGER_TRACE(m_logger, "BMEGUI::DrawUpdaterLaunchingSplashScreen: end");
}