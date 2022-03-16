#pragma once
#include "ConCommandManager.h"
#include <discord_rpc.h>

struct DiscordUserStored {
    // snowflake (64bit int), turned into a ascii decimal string, at most 20 chars +1 null
    // terminator = 21
    char userId[32];
    // 32 unicode glyphs is max name size => 4 bytes per glyph in the worst case, +1 for null
    // terminator = 129
    char username[344];
    // 4 decimal digits + 1 null terminator = 5
    char discriminator[8];
    // optional 'a_' + md5 hex digest (32 bytes) + null terminator = 35
    char avatar[128];
};

struct DiscordRichPresenceStored {
    char state[128];
    char details[128];
    int64_t startTimestamp;
    int64_t endTimestamp;
    char largeImageKey[32];
    char largeImageText[128];
    char smallImageKey[32];
    char smallImageText[128];
    char partyId[128];
    int partySize;
    int partyMax;
    int partyPrivacy;
    char matchSecret[128];
    char joinSecret[128];
    char spectateSecret[128];
    int8_t instance;
};

class DiscordWrapper
{
private:
    std::shared_ptr<spdlog::logger> m_logger;
    std::mutex UpdatePresenceMutex;
    DiscordUserStored user;
    DiscordRichPresenceStored lastPresence;
    bool presenceUpdatePending = false;
    std::chrono::system_clock::time_point presenceUpdatePendingSince;
public:
    //bool isDiscordInitialized;
    bool isDiscordReady;
    short presenceUpdatePendingDebounceThresholdMs;

    void handleDiscordReady(const DiscordUser* connectedUser);
    void handleDiscordDisconnected(int errcode, const char* message);
    void handleDiscordError(int errcode, const char* message);
    void handleDiscordJoin(const char* secret);
    void handleDiscordSpectate(const char* secret);
    void handleDiscordJoinRequest(const DiscordUser* request);

    void OpenDiscordGuildInvite(const CCommand& args);
    void OpenDiscordFriendsInvite(const CCommand& args);
    //void UpdateActivity(discord::Activity activity);
    bool UpdatePresence(const DiscordRichPresence* presence);

    void UpdateDebouncedPresenceTick();
    void RunCallbacks();

    DiscordWrapper(ConCommandManager& conCommandManager);
    ~DiscordWrapper();
};
