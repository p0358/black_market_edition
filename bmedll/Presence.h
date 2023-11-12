#pragma once
#include "ConCommandManager.h"

enum eGameState	// These must stay in order from beginning of a match till the end
{
    WaitingForCustomStart, // mainly for e3
    WaitingForPlayers,
    PickLoadout,
    Prematch, // this gets triggered after round ends
    Playing,
    SuddenDeath,
    SwitchingSides,
    WinnerDetermined,
    Epilogue,
    Postmatch,

    _count_
};

struct ourInGameJoinData {
    bool ok;
    std::string serverIPAndPort;
    std::string encryptionKeyBase64;
    unsigned long long uid;
};

class Presence
{
private:
    std::shared_ptr<spdlog::logger> m_logger;
    std::mutex updateRichPresenceMutex;
public:
    const char* emptyString = "";
    char presenceBuffer[1024];
    __int64 textchat_last_a1 = 1;
    char richPresenceBuffer[1024];
    char* richPresenceBufferInGame;
    char* serverIPAndPortBufferInGame;
    char lastMap[32];

    const char* match_playlist;
    int* isConnectedAndInLobby; // 2 = training, 1 = lobby (EVEN IF it=0), 0 = game?
    int* teamNum;
    const char* map; // alt, faster (from cl_showfps???)
    const char* map_old;
    const char* joinSecretInGame;
    int* maxplayers;
    bool* isPrivateLobby;
    float* serverClock;

    __int64 updatePresence2LastInput;
    bool didOriginOfflineKickAlready;
    int trainingStage;
    int playerCount;
    int64_t gameStartTime;
    int64_t gameEndTime;
    int64_t gameEndTime2;
    int gameState;
    bool switchedSides;
    bool isSwitchSidesBased;
    bool isRoundBased;
    int roundNumber;
    int maxRounds;
    bool isDiscordJoinable;

    static const char* getDisplayMapName(const char* map);
    static const char* getDisplayPlaylistName(const char* map);
    const char* getDisplayNameForTrainingResumeChoice(int choice);
    const char* getDisplayCampaignMissionNameForMapName(const char* map);

    void updateRichPresenceLoading(bool requestOriginUpdateImmediately);
    void updateRichPresenceLoadingWithMap(const char* map, bool requestOriginUpdateImmediately);
    void updateRichPresence(bool requestOriginUpdateImmediately);
    void updateRichPresenceCCommand(const CCommand& args);

    __int16* isPresenceUpdatePending;
    inline void requestOriginPresenceUpdate();
    inline void wipeOriginRichPresenceString();
    inline void wipeOriginJoinSecret();
    std::string getJoinSecret();
    bool joinGameWithOriginJoinSecret(const char* str, unsigned long long uid);
    bool joinGameWithDiscordJoinSecret(const char* str);

    void SetTrainingResumeChoice(const CCommand& args);
    void updatePlayerCountCCommand(const CCommand& args);
    void updatePlayerCountGrabCCommand(const CCommand& args);
    void updateGameEndTimeCCommand(const CCommand& args);
    void updateGameEndTime2CCommand(const CCommand& args);
    void updateGameStateCCommand(const CCommand& args);
    void updateIsRoundBasedCCommand(const CCommand& args);
    void updateIsSwitchBasedCCommand(const CCommand& args);
    void updateRoundsPlayedCCommand(const CCommand& args);
    void updateRoundsTotalCCommand(const CCommand& args);

    void __fastcall Hook_updatePresence2(__int64 a1);
    char Hook_sub_180473500(char* a1, signed __int64 a2, const char* a3, char* a4, char* a5);
    __int64 __fastcall Hook_sub_180022CA0(__int64 a1);
    int64_t __fastcall Hook_originEventCallback(int64_t eventID, void* a2, uint64_t* a3, void* a4);

    Presence();
    ~Presence();
};
