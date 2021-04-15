#include "pch.h"
#include "Discord.h"
#include "discord/discord.h"
#include <iostream>
#include "TTFSDK.h"
#include "Presence.h"
#include "Chat.h"
#include "ConVar.h"

DiscordWrapper& DiscordWrap()
{
    return SDK().GetDiscord();
}

#define WRAPPED_MEMBER(name) MemberWrapper<decltype(&DiscordWrapper::##name), &DiscordWrapper::##name, decltype(&DiscordWrap), &DiscordWrap>::Call

const std::string GetThisExecutablePath()
{
    WCHAR result[MAX_PATH];
    DWORD length = GetModuleFileNameW(NULL, result, MAX_PATH);
    return Util::Narrow(result);
}

DiscordWrapper::DiscordWrapper(ConCommandManager& conCommandManager)
{
    //DiscordState state{};
    //DiscordState state = state;
    auto logger = spdlog::get("logger");
    logger->info("Discord init start");
    std::cout << "a";

    discord::Core* core{};
    //this->core = core;
    auto result = discord::Core::Create(444356071880917002, DiscordCreateFlags_NoRequireDiscord, &core); std::cout << "b";

    this->core.reset(core);
    conCommandManager.RegisterConVar("bme_is_discord_initialized", !core ? "0" : "1", FCVAR_DONTRECORD | FCVAR_SERVER_CANNOT_QUERY, "Is updated with whether Discord was successfully initialized");
    if (!core) {
        logger->warn("Failed to instantiate discord core! (err {})", static_cast<int>(result));
        return;
    } std::cout << "c";

    isDiscordInitialized = result == discord::Result::Ok;

    core->SetLogHook(
        discord::LogLevel::Debug, [](discord::LogLevel level, const char* message) {
            //std::cerr << "Log(" << static_cast<uint32_t>(level) << "): " << message << "\n";
            spdlog::get("logger")->info("[discord] {}", message);
        }); std::cout << "d";


    //core->UserManager().OnCurrentUserUpdate.Connect([&state]() {
    core->UserManager().OnCurrentUserUpdate.Connect([this]() {
        this->isDiscordReady = true;
        //static discord::User user;
        //this->core->UserManager().GetCurrentUser(&user);
        //currentUser.reset(&user);
        this->core->UserManager().GetCurrentUser(&currentUser);
        //currentUser = std::make_shared<discord::User>(user);

        //std::cout << "Current user updated: " << state.currentUser.GetUsername() << "#"
        //    << state.currentUser.GetDiscriminator() << "\n";
        spdlog::get("logger")->info("[discord] Current user updated: {}#{}", currentUser.GetUsername(), currentUser.GetDiscriminator());

        /*state.core->UserManager().GetUser(130050050968518656,
            [](discord::Result result, discord::User const& user) {
                if (result == discord::Result::Ok) {
                    std::cout << "Get " << user.GetUsername() << "\n";
                }
                else {
                    std::cout << "Failed to get David!\n";
                }
        });*/

    }); std::cout << "e";

    //core->ActivityManager().RegisterSteam(1454890);
    core->ActivityManager().RegisterCommand(GetThisExecutablePath().c_str()); // TODO: check if that works
    std::cout << "f";

    /*discord::Activity activity{};
    activity.SetDetails("Fruit Tarts");
    activity.SetState("Pop Snacks");
    activity.GetAssets().SetSmallImage("the");
    activity.GetAssets().SetSmallText("i mage");
    activity.GetAssets().SetLargeImage("the");
    activity.GetAssets().SetLargeText("u mage");
    activity.SetType(discord::ActivityType::Playing);
    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
        std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed")
            << " updating activity!\n";
        });*/

    /*discord::Activity activity{};
    activity.SetDetails("Fruit Tarts");
    activity.SetState("Pop Snacks");
    activity.GetAssets().SetSmallImage("the");
    activity.GetAssets().SetSmallText("i mage");
    activity.GetAssets().SetLargeImage("the");
    activity.GetAssets().SetLargeText("u mage");
    activity.SetType(discord::ActivityType::Playing);
    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
        std::stringstream ss;
        ss << ((result == discord::Result::Ok) ? "Succeeded" : "Failed")
            << " updating activity!\n";
        spdlog::get("logger")->debug("[discord] {}", ss.str().c_str());
    });*/
    /*logger->debug(_("Discord on before first activity update"));

    discord::Activity activity{};
    activity.SetDetails("Launching game...");
    activity.SetState("Black Market Edition");
    activity.GetAssets().SetSmallImage("");
    activity.GetAssets().SetSmallText("");
    activity.GetAssets().SetLargeImage("titanfall_101");
    activity.GetAssets().SetLargeText("Titanfall");
    activity.SetType(discord::ActivityType::Playing);
    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
        std::stringstream ss;
        ss << ((result == discord::Result::Ok) ? "Succeeded" : "Failed")
            << " updating activity!\n";
        spdlog::get("logger")->debug("[discord] {}", ss.str().c_str());
    });*/

    core->ActivityManager().OnActivityJoin.Connect([this](const char* secret) {
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
        }*/
    });

    core->ActivityManager().OnActivityJoinRequest.Connect([this](const discord::User& user) {
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
    });

    core->ActivityManager().OnActivityInvite.Connect([this](discord::ActivityActionType actionType, const discord::User& user, const discord::Activity& activity) {
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
    });


    SPDLOG_LOGGER_DEBUG(logger, _("Discord on before first RunCallbacks"));
    core->RunCallbacks();

    conCommandManager.RegisterCommand("bme_discord_guild_invite_open", WRAPPED_MEMBER(OpenDiscordInvite), "Open Discord invite to TF Remnant Fleet", FCVAR_DONTRECORD);
    conCommandManager.RegisterCommand("bme_discord_friends_invite_open", WRAPPED_MEMBER(OpenDiscordFriendsInvite), "Open Discord invite friends dialog", FCVAR_DONTRECORD);

    logger->info(_("Discord init end"));
    
}

DWORD WINAPI DiscordWrapper::ThreadProc(LPVOID lpThreadParameter)
{
    return 0;
}

void DiscordWrapper::OpenDiscordInvite(const CCommand& args)
{
    if (!core) return;
    core->OverlayManager().OpenGuildInvite("Fw9bjMN", [](discord::Result result) {
        std::stringstream ss;
        ss << ((result == discord::Result::Ok) ? "Succeeded" : "Failed")
            << " opening invite!\n";
        SPDLOG_LOGGER_DEBUG(spdlog::get("logger"), "[discord] {}", ss.str().c_str());
    });
}

void DiscordWrapper::OpenDiscordFriendsInvite(const CCommand& args)
{
    if (!core) return;
    core->OverlayManager().OpenActivityInvite(discord::ActivityActionType::Join, [](discord::Result result) {
        std::stringstream ss;
        ss << ((result == discord::Result::Ok) ? "Succeeded" : "Failed")
            << " opening activity invite dialog!\n";
        SPDLOG_LOGGER_DEBUG(spdlog::get("logger"), "[discord] {}", ss.str().c_str());
    });
}

void DiscordWrapper::UpdateActivity(discord::Activity activity) {
    if (!core) return;
    core->ActivityManager().UpdateActivity(activity, [activity](discord::Result result) {
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
}

DiscordWrapper::~DiscordWrapper()
{
    SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "DiscordWrapper destructor");
    //currentUser.reset();
    core.reset();
}