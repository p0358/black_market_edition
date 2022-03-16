#include "pch.h"
#include <iostream>
#include "TTFSDK.h"
#include "Presence.h"
#include "Chat.h"
#include "ConVar.h"
#include "_version.h"

short presenceUpdatePendingDebounceThresholdMs = 1500;

DiscordWrapper& DiscordWrap()
{
    return SDK().GetDiscord();
}

#define WRAPPED_MEMBER(name) MemberWrapper<decltype(&DiscordWrapper::##name), &DiscordWrapper::##name, decltype(&DiscordWrap), &DiscordWrap>::Call

std::once_flag flag_discord1, flag_discord2;

void bme_discord_reinit(const CCommand& args)
{
    if (!IsSDKReady()) return;
    try {
        SDK().ReinitDiscord();
    }
    catch (std::exception& ex) {
        spdlog::get("logger")->error("Failed reinitializing Discord: {}", ex.what());
    }
}

DiscordWrapper::DiscordWrapper(ConCommandManager& conCommandManager)
{
    auto startTime = std::chrono::system_clock::now();
    m_logger = spdlog::get("logger");
    m_logger->info("Discord init start");

    //this->isDiscordInitialized = false;
    this->isDiscordReady = false;
    this->presenceUpdatePendingDebounceThresholdMs = 1500;

    memset(&user, 0, sizeof(user));
    memset(&lastPresence, 0, sizeof(lastPresence));

    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = WRAPPED_MEMBER(handleDiscordReady);
    handlers.disconnected = WRAPPED_MEMBER(handleDiscordDisconnected);
    handlers.errored = WRAPPED_MEMBER(handleDiscordError);
    handlers.joinGame = WRAPPED_MEMBER(handleDiscordJoin);
    handlers.spectateGame = WRAPPED_MEMBER(handleDiscordSpectate);
    handlers.joinRequest = WRAPPED_MEMBER(handleDiscordJoinRequest);
    Discord_Initialize("444356071880917002", &handlers, 1, NULL);

    std::call_once(flag_discord1, [&conCommandManager]() {
        // TODO: not ideal, cause reinitialization won't modify the below cvar
        conCommandManager.RegisterConVar("bme_is_discord_initialized", /*!core ? "0" :*/ "1", FCVAR_DONTRECORD | FCVAR_SERVER_CANNOT_QUERY, "Is updated with whether Discord was successfully initialized");
        conCommandManager.RegisterCommand("bme_discord_reinit", bme_discord_reinit, "Reinit Discord (deinitialize and reinitialize again)", 0);

        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));
        discordPresence.details = "Launching game...";
        discordPresence.state = BME_VERSION_LONG;
        discordPresence.largeImageKey = "titanfall_101";
        discordPresence.largeImageText = "Titanfall";
        discordPresence.smallImageKey = "";
        discordPresence.smallImageText = "";
        discordPresence.instance = 0;
        Discord_UpdatePresence(&discordPresence);
    });

    /*core->ActivityManager().OnActivityJoin.Connect([this](const char* secret) {
        if (!IsSDKReady()) return;
        bool suc = SDK().GetPresence().joinGameWithDiscordJoinSecret((char*)secret);
        spdlog::get("logger")->info("[discord] OnActivityJoin secret:{} isSuccess:{}", secret, suc);
        /*ourInGameJoinData data = SDK().GetPresence().parseJoinSecret((char*)secret);
        if (data.ok)
        {
            std::stringstream cmd;
            cmd << "connectwithinvite";
            cmd << ' ' << '"' << data.serverIPAndPort << '"';
            cmd << ' ' << '"' << data.encryptionKeyBase64 << '"';
            cmd << ' ' << data.uid;
            spdlog::get("logger")->info("[discord] Joining game of origin user ID: {}", data.uid);
            SDK().GetEngineClient()->ClientCmd_Unrestricted(cmd.str().c_str());
        }* /
    });*/

    /*core->ActivityManager().OnActivityJoinRequest.Connect([this](const discord::User& user) {
        if (!IsSDKReady()) return;
        // Fires when a user asks to join the current user's game.
        spdlog::get("logger")->info("[discord] OnActivityJoinRequest {}{} {}", user.GetUsername(), user.GetDiscriminator(), user.GetId());
        {
            const char* map = SDK().GetPresence().map;
            if (map && *map && std::strcmp(map, "mp_lobby") == 0)
            {
                Chat::showChatLineEasy(_("\n[Discord] "), 0xFF7289DA);
                Chat::showChatLineEasy(user.GetUsername(), 0xFFDDDDDD);
                Chat::showChatLineEasy(_(" asked to join your game. You can accept this request in Discord."), 0xFFFFFFFF);
            }
        }
    });*/

    // TODO TODO TODO:
    // TODO TODO TODO: THIS NOT SUPPORTED BY DISCORD-RPC??????????
    // TODO TODO TODO:
    /*core->ActivityManager().OnActivityInvite.Connect([this](discord::ActivityActionType actionType, const discord::User& user, const discord::Activity& activity) {
        if (!IsSDKReady()) return;
        // Fires when the user receives a join or spectate invite.
        spdlog::get("logger")->info("[discord] OnActivityInvite type:{} {}{} {}", actionType, user.GetUsername(), user.GetDiscriminator(), user.GetId());
        {
            const char* map = SDK().GetPresence().map;
            if (map && *map && std::strcmp(map, "mp_lobby") == 0)
            {
                Chat::showChatLineEasy(_("\n[Discord] "), 0x7289DAFF);
                Chat::showChatLineEasy(user.GetUsername(), 0xDDDDDDFF);
                Chat::showChatLineEasy(_(" invited you to join their game. You can accept this invite in Discord."), 0xFFFFFFFF);
            }
        }
    });*/


    SPDLOG_LOGGER_DEBUG(m_logger, _("Discord on before first RunCallbacks"));
    Discord_RunCallbacks();

    std::call_once(flag_discord2, [&conCommandManager]() {
        conCommandManager.RegisterCommand("bme_discord_guild_invite_open", WRAPPED_MEMBER(OpenDiscordGuildInvite), "Open Discord invite to Harmony", FCVAR_DONTRECORD);
        conCommandManager.RegisterCommand("bme_discord_friends_invite_open", WRAPPED_MEMBER(OpenDiscordFriendsInvite), "Open Discord invite friends dialog", FCVAR_DONTRECORD);
    });

    presenceUpdatePendingSince = std::chrono::system_clock::now();
    presenceUpdatePending = false;
    
    m_logger->info(_("Discord init end - {} ms"), std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime).count());
}

void DiscordWrapper::handleDiscordReady(const DiscordUser* connectedUser)
{
    isDiscordReady = true;
    m_logger->info("[discord] Connected to user: {}#{}", connectedUser->username, connectedUser->discriminator);
    strcpy_s(user.userId, connectedUser->userId);
    strcpy_s(user.username, connectedUser->username);
    strcpy_s(user.discriminator, connectedUser->discriminator);
    strcpy_s(user.avatar, connectedUser->avatar);
}

void DiscordWrapper::handleDiscordDisconnected(int errcode, const char* message)
{
    isDiscordReady = false;
    m_logger->warn("[discord] disconnected {}: {}", errcode, message);
}

void DiscordWrapper::handleDiscordError(int errcode, const char* message)
{
    m_logger->error("[discord] {}: {}", errcode, message);
}

void DiscordWrapper::handleDiscordJoin(const char* secret)
{
    m_logger->info("[discord] before join = secret:{}", secret);
    bool suc = SDK().GetPresence().joinGameWithDiscordJoinSecret((char*)secret);
    m_logger->info("[discord] join = secret:{} isSuccess:{}", secret, suc); // OnActivityJoin
}

void DiscordWrapper::handleDiscordSpectate(const char* secret)
{
    m_logger->warn("[discord] spectate (not implemented): {}", secret);
}

void DiscordWrapper::handleDiscordJoinRequest(const DiscordUser* request)
{
    // Fires when a user asks to join the current user's game.
    m_logger->info("[discord] OnActivityJoinRequest {}#{} ({})", request->username, request->discriminator, request->userId);
    {
        const char* map = SDK().GetPresence().map;
        if (map && *map && std::strcmp(map, "mp_lobby") == 0)
        {
            Chat::showChatLineEasy(_("\n[Discord] "), 0xFF7289DA);
            Chat::showChatLineEasy(request->username, 0xFFDDDDDD);
            Chat::showChatLineEasy(_(" asked to join your game. You can accept this request in Discord."), 0xFFFFFFFF);
        }
    }
    //Discord_Respond(request->userId, response); // response = DISCORD_REPLY_YES / _NO
}

void DiscordWrapper::OpenDiscordGuildInvite(const CCommand& args)
{
    if (!isDiscordReady) return;
    Discord_OpenGuildInvite("VsYvaQ4UcZ");
}

void DiscordWrapper::OpenDiscordFriendsInvite(const CCommand& args)
{
    if (!isDiscordReady) return;
    Discord_OpenActivityInvite(DISCORD_ACTIVITY_ACTION_TYPE_JOIN);
}

/*void DiscordWrapper::UpdateActivity(discord::Activity activity) {
    if (!core) return;
    core->ActivityManager().UpdateActivity(activity, [activity](discord::Result result) {
        if (!IsSDKReady()) return;
        std::stringstream ss;
        ss << ((result == discord::Result::Ok) ? "Succeeded" : "Failed")
            << " updating activity!";
        SPDLOG_LOGGER_DEBUG(spdlog::get("logger"), "[discord] {}", ss.str().c_str());

        bool isDiscordJoinable = false;
        if (result == discord::Result::Ok)
        {
            const char* joinSecret = activity.GetSecrets().GetJoin();
            isDiscordJoinable = joinSecret && *joinSecret;
        }
        SDK().GetPresence().isDiscordJoinable = isDiscordJoinable;
        ConVar* bme_is_discord_joinable = SDK().GetVstdlibCvar()->FindVar("bme_is_discord_joinable");
        if (bme_is_discord_joinable)
            bme_is_discord_joinable->SetValueString(isDiscordJoinable ? "1" : "0");
    });
}*/

bool DiscordWrapper::UpdatePresence(const DiscordRichPresence* presence)
{
    std::lock_guard<std::mutex> guard(UpdatePresenceMutex);

    bool isChanged =
        (presence->state /*&& *lastPresence.state*/ && strcmp(presence->state, lastPresence.state) != 0)
        || (presence->details != nullptr /*&& *lastPresence.details*/ && strcmp(presence->details, lastPresence.details) != 0)
        || presence->startTimestamp != lastPresence.startTimestamp
        || presence->endTimestamp != lastPresence.endTimestamp
        || (presence->largeImageKey != nullptr && strcmp(presence->largeImageKey, lastPresence.largeImageKey) != 0)
        || (presence->largeImageText != nullptr && strcmp(presence->largeImageText, lastPresence.largeImageText) != 0)
        || (presence->smallImageKey != nullptr && strcmp(presence->smallImageKey, lastPresence.smallImageKey) != 0)
        || (presence->smallImageText != nullptr && strcmp(presence->smallImageText, lastPresence.smallImageText) != 0)
        || (presence->partyId != nullptr && strcmp(presence->partyId, lastPresence.partyId) != 0)
        || presence->partySize != lastPresence.partySize
        || presence->partyMax != lastPresence.partyMax
        || presence->partyPrivacy != lastPresence.partyPrivacy
        || (presence->matchSecret != nullptr && strcmp(presence->matchSecret, lastPresence.matchSecret) != 0)
        || (presence->joinSecret != nullptr && strcmp(presence->joinSecret, lastPresence.joinSecret) != 0)
        || (presence->spectateSecret != nullptr && strcmp(presence->spectateSecret, lastPresence.spectateSecret) != 0)
        || presence->instance != lastPresence.instance;


    if (!isChanged) { SPDLOG_LOGGER_DEBUG(m_logger, "[discord] Did not update presence, because it was identical to the last one"); return false; }



    if (presence->state != nullptr /*&& *presence->state*/)
        strcpy_s(lastPresence.state, presence->state);
    else
        memset(lastPresence.state, 0, 128);

    if (presence->details != nullptr)
        strcpy_s(lastPresence.details, presence->details);
    else
        memset(lastPresence.details, 0, 128);

    lastPresence.startTimestamp = presence->startTimestamp;

    lastPresence.endTimestamp = presence->endTimestamp;

    if (presence->largeImageKey != nullptr)
        strcpy_s(lastPresence.largeImageKey, presence->largeImageKey);
    else
        memset(lastPresence.largeImageKey, 0, 32);

    if (presence->largeImageText != nullptr)
        strcpy_s(lastPresence.largeImageText, presence->largeImageText);
    else
        memset(lastPresence.largeImageText, 0, 128);

    if (presence->smallImageKey != nullptr)
        strcpy_s(lastPresence.smallImageKey, presence->smallImageKey);
    else
        memset(lastPresence.smallImageKey, 0, 32);

    if (presence->smallImageText != nullptr)
        strcpy_s(lastPresence.smallImageText, presence->smallImageText);
    else
        memset(lastPresence.smallImageText, 0, 128);

    if (presence->partyId != nullptr)
        strcpy_s(lastPresence.partyId, presence->partyId);
    else
        memset(lastPresence.partyId, 0, 128);



    lastPresence.partySize = presence->partySize;
    lastPresence.partyMax = presence->partyMax;
    lastPresence.partyPrivacy = presence->partyPrivacy;
    if (presence->matchSecret != nullptr)
        strcpy_s(lastPresence.matchSecret, presence->matchSecret);
    else
        memset(lastPresence.matchSecret, 0, 128);
    if (presence->joinSecret != nullptr)
        strcpy_s(lastPresence.joinSecret, presence->joinSecret);
    else
        memset(lastPresence.joinSecret, 0, 128);
    if (presence->spectateSecret != nullptr)
        strcpy_s(lastPresence.spectateSecret, presence->spectateSecret);
    else
        memset(lastPresence.spectateSecret, 0, 128);

    // let's debounce the update
    presenceUpdatePendingSince = std::chrono::system_clock::now();
    presenceUpdatePending = true;

    /*DiscordRichPresence discordPresenceCopy;
    memset(&discordPresenceCopy, 0, sizeof(discordPresenceCopy));
    discordPresenceCopy.state = lastPresence.state;
    discordPresenceCopy.details = lastPresence.details;
    discordPresenceCopy.startTimestamp = lastPresence.startTimestamp;
    discordPresenceCopy.endTimestamp = lastPresence.endTimestamp;
    discordPresenceCopy.largeImageKey = lastPresence.largeImageKey;
    discordPresenceCopy.largeImageText = lastPresence.largeImageText;
    discordPresenceCopy.smallImageKey = lastPresence.smallImageKey;
    discordPresenceCopy.smallImageText = lastPresence.smallImageText;
    discordPresenceCopy.partyId = lastPresence.partyId;
    discordPresenceCopy.partySize = lastPresence.partySize;
    discordPresenceCopy.partyMax = lastPresence.partyMax;
    discordPresenceCopy.partyPrivacy = lastPresence.partyPrivacy;
    discordPresenceCopy.matchSecret = lastPresence.matchSecret;
    discordPresenceCopy.joinSecret = lastPresence.joinSecret;
    discordPresenceCopy.spectateSecret = lastPresence.spectateSecret;
    Discord_UpdatePresence(&discordPresenceCopy);*/

    return true;
}

void DiscordWrapper::UpdateDebouncedPresenceTick()
{
    if (presenceUpdatePending
        && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - presenceUpdatePendingSince).count()
            > presenceUpdatePendingDebounceThresholdMs)
    {
        std::lock_guard<std::mutex> guard(UpdatePresenceMutex);
        presenceUpdatePending = false;

        DiscordRichPresence discordPresenceCopy;
        memset(&discordPresenceCopy, 0, sizeof(discordPresenceCopy));
        discordPresenceCopy.state = lastPresence.state;
        discordPresenceCopy.details = lastPresence.details;
        discordPresenceCopy.startTimestamp = lastPresence.startTimestamp;
        discordPresenceCopy.endTimestamp = lastPresence.endTimestamp;
        discordPresenceCopy.largeImageKey = lastPresence.largeImageKey;
        discordPresenceCopy.largeImageText = lastPresence.largeImageText;
        discordPresenceCopy.smallImageKey = lastPresence.smallImageKey;
        discordPresenceCopy.smallImageText = lastPresence.smallImageText;
        discordPresenceCopy.partyId = lastPresence.partyId;
        discordPresenceCopy.partySize = lastPresence.partySize;
        discordPresenceCopy.partyMax = lastPresence.partyMax;
        discordPresenceCopy.partyPrivacy = lastPresence.partyPrivacy;
        discordPresenceCopy.matchSecret = lastPresence.matchSecret;
        discordPresenceCopy.joinSecret = lastPresence.joinSecret;
        discordPresenceCopy.spectateSecret = lastPresence.spectateSecret;
        Discord_UpdatePresence(&discordPresenceCopy);

        bool isDiscordJoinable = discordPresenceCopy.joinSecret && discordPresenceCopy.joinSecret[0];
        SDK().GetPresence().isDiscordJoinable = isDiscordJoinable;
        static ConVar* bme_is_discord_joinable = SDK().GetVstdlibCvar()->FindVar("bme_is_discord_joinable");
        if (bme_is_discord_joinable)
            bme_is_discord_joinable->SetValueString(isDiscordJoinable ? "1" : "0");

        m_logger->debug("[discord] Updated presence. Joinable: {}", isDiscordJoinable ? "yes" : "no");
    }
}

void DiscordWrapper::RunCallbacks()
{
    Discord_RunCallbacks();
}

DiscordWrapper::~DiscordWrapper()
{
    SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "DiscordWrapper destructor");
    Discord_Shutdown();
}