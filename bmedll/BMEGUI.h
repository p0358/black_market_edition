#pragma once
#include "ConCommandManager.h"
#include "UIManager.h"

class BMEGUI
{
public:
	BMEGUI(ConCommandManager& conCommandManager, UIManager& uiManager/*, SquirrelManager& sqManager*/, FileSystemManager& fsManager);
	~BMEGUI();

	void DrawUpdaterDownloadProgress();
	void DrawUpdaterLaunchingSplashScreen();
	/*void DrawPropsGui();
	void DrawSearchResults();
	void DrawModelsDirectory(struct ModelsDirectory* dir);
	void DrawDirectoryModels(struct ModelsDirectory* dir);
	void DrawModelButton(std::string& modelName, std::string& displayName, ImVec2 size);
	void DrawToolsGui(float ToolsPanelWidth);
	void DrawOptionsGui();
	void DrawPage(int idx);
	void DrawSaveAs();
	bool IsSaveInputNameValid();
	void RefreshSaveFilesList();
	void DrawCreateSpawnlist();

	void DrawCallback();*/

	//void ShowMenuCommand(const CCommand& args);
	//void HideMenuCommand(const CCommand& args);
	//SQInteger IsMenuShowing(HSQUIRRELVM v);

private:
	std::shared_ptr<spdlog::logger> m_logger;
	UIManager* m_uiManager;

	/*std::vector<Tool> m_Tools;
	Tool* m_ViewingTool = nullptr;

	int m_DisplayingPage = 0;
	std::vector<SpawnmenuPage> m_Pages;
	bool m_IcepickMenuOpen = false;
	bool m_EditModeEnabled = true;
	bool m_IsInvincibilityEnabled = false;

	bool m_SaveAsOpen = false;
	bool m_ShowInvalidSave = false;
	char m_SaveInput[SaveMaxChars] = "";
	std::vector<std::string> m_CachedSaveFileNames;
	bool m_ShowLoadingModal = false;

	bool m_CreateSpawnlistOpen = false;
	char m_SpawnlistInput[SaveMaxChars] = "";

	int m_SpawnmenuButtonSizes[7] = { 0, 32, 48, 64, 96, 128, 256 };
	int m_SpawnmenuButtonSize = 96;

	char m_SearchInput[SearchMaxChars] = "";
	int m_CachedSearchInputLength = 0;
	std::vector<std::string*> m_SearchResults;

	class ModelsList* m_ModelsList = nullptr;
	struct ModelsDirectory* m_ViewingDirectory = nullptr;
	SpawnlistDisplayMode m_SpawnlistDisplayMode = SpawnlistDisplayMode::Tree;
	ModelsDisplayMode m_ModelsDisplayMode = ModelsDisplayMode::List;

	std::vector<std::string> m_SaveBuffer;*/
};