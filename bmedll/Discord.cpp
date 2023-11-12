#include "pch.h"
#include "TTFSDK.h"
#include "Discord.h"
#include "Presence.h"
#include "Chat.h"
#include "ConVar.h"
#include "_version.h"

#define DISCORD_APP_ID "444356071880917002"
#define DISCORD_GUILD_INVITE "VsYvaQ4UcZ"

DiscordWrapper& DiscordWrap()
{
	return SDK().GetDiscord();
}

#define WRAPPED_MEMBER(name) MemberWrapper<decltype(&DiscordWrapper::##name), &DiscordWrapper::##name, decltype(&DiscordWrap), &DiscordWrap>::Call

void bme_discord_reinit(const CCommand& args)
{
	if (!IsSDKReady()) return;
	try
	{
		SDK().ReinitDiscord();
	}
	catch (std::exception& ex)
	{
		spdlog::error("Failed reinitializing Discord: {}", ex.what());
	}
}

DiscordWrapper::DiscordWrapper()
{
	auto startTime = std::chrono::system_clock::now();
	m_logger = spdlog::get("logger");

	this->isDiscordReady = false;

	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.ready = WRAPPED_MEMBER(handleDiscordReady);
	handlers.disconnected = WRAPPED_MEMBER(handleDiscordDisconnected);
	handlers.errored = WRAPPED_MEMBER(handleDiscordError);
	handlers.joinGame = WRAPPED_MEMBER(handleDiscordJoin);
	handlers.spectateGame = WRAPPED_MEMBER(handleDiscordSpectate);
	handlers.joinRequest = WRAPPED_MEMBER(handleDiscordJoinRequest);
	Discord_Initialize(DISCORD_APP_ID, &handlers, 1, NULL);

	static std::once_flag flag;
	std::call_once(flag, []() {
		auto& conCommandManager = SDK().GetConCommandManager();
		conCommandManager.RegisterConVar("bme_is_discord_ready", "0", FCVAR_DONTRECORD | FCVAR_SERVER_CANNOT_QUERY, "Is updated with whether Discord was successfully initialized and connected to a user");
		conCommandManager.RegisterConVar("bme_is_discord_joinable", "0", FCVAR_DONTRECORD | FCVAR_SERVER_CANNOT_QUERY, "Is updated with whether user is joinable (is on a non-full game server)");
		conCommandManager.RegisterConVar("bme_discord_ipc_debug", "0", FCVAR_DONTRECORD | FCVAR_SERVER_CANNOT_QUERY, "Dump IPC JSON messages exchanged between the Discord library and the Discord client");
		conCommandManager.RegisterCommand("bme_discord_reinit", bme_discord_reinit, "Reinit Discord (deinitialize and reinitialize again)", FCVAR_DONTRECORD);
		conCommandManager.RegisterCommand("bme_discord_guild_invite_open", WRAPPED_MEMBER(OpenDiscordGuildInvite), "Open Discord invite to Harmony", FCVAR_DONTRECORD);
		conCommandManager.RegisterCommand("bme_discord_friends_invite_open", WRAPPED_MEMBER(OpenDiscordFriendsInvite), "Open Discord invite friends dialog", FCVAR_DONTRECORD);

		SDK().AddFrameTask(std::make_shared<DiscordFrameTask>());

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

		SDK().AddDelayedFunc([] {
			DiscordRichPresence discordPresence;
			memset(&discordPresence, 0, sizeof(discordPresence));
			discordPresence.details = "Main Menu";
			discordPresence.state = BME_VERSION_LONG;
			discordPresence.largeImageKey = "titanfall_101";
			discordPresence.largeImageText = "Titanfall";
			discordPresence.smallImageKey = "";
			discordPresence.smallImageText = "";
			const auto n = std::chrono::system_clock::now();
			const auto t = std::chrono::duration_cast<std::chrono::seconds>(n.time_since_epoch()).count();
			discordPresence.startTimestamp = t;
			SDK().GetDiscord().UpdatePresence(&discordPresence);
		});
	});

	Discord_RunCallbacks();

	m_presenceUpdatePendingSince = std::chrono::system_clock::now();
	m_presenceUpdatePending = false;
	
	m_logger->info("Discord init - {} ms", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime).count());
}

void DiscordWrapper::handleDiscordReady(const DiscordUser* connectedUser)
{
	this->isDiscordReady = true;
	m_user.CopyFrom(connectedUser);
	if (m_user.HasDiscriminator())
		m_logger->info("[discord] Connected to user: {}#{} ({})", m_user.username, m_user.discriminator, m_user.globalName);
	else
		m_logger->info("[discord] Connected to user: @{} ({})", m_user.username, m_user.globalName);

	static ConVar* bme_is_discord_ready = SDK().GetVstdlibCvar()->FindVar("bme_is_discord_ready");
	if (bme_is_discord_ready)
		bme_is_discord_ready->SetValueInt(true);
}

void DiscordWrapper::handleDiscordDisconnected(int errcode, const char* message)
{
	this->isDiscordReady = false;
	m_logger->warn("[discord] disconnected {}: {}", errcode, message);
	static ConVar* bme_is_discord_ready = SDK().GetVstdlibCvar()->FindVar("bme_is_discord_ready");
	if (bme_is_discord_ready)
		bme_is_discord_ready->SetValueInt(false);
}

void DiscordWrapper::handleDiscordError(int errcode, const char* message)
{
	m_logger->error("[discord] {}: {}", errcode, message);
}

void DiscordWrapper::handleDiscordDebug(char isOut, const char* opcodeName, const char* message, uint32_t messageLength)
{
	static ConVar* bme_discord_ipc_debug = SDK().GetVstdlibCvar()->FindVar("bme_discord_ipc_debug");
	if (bme_discord_ipc_debug && bme_discord_ipc_debug->GetInt())
	{
		auto* direction = isOut ? "send" : "receive";
		if (messageLength && message && message[0])
		{
			std::string_view msg{ message, messageLength };
			m_logger->debug("[discord ipc] [{}] [{}] {}", direction, opcodeName, msg);
		}
		else
			m_logger->debug("[discord ipc] [{}] [{}] <empty>", direction, opcodeName);
	}
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
	if (m_user.HasDiscriminator())
		m_logger->warn("[discord] OnActivityJoinRequest from: {}#{} ({})", m_user.username, m_user.discriminator, m_user.globalName);
	else
		m_logger->warn("[discord] OnActivityJoinRequest from: @{} ({})", m_user.username, m_user.globalName);

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

void DiscordWrapper::handleDiscordInvited(/* DISCORD_ACTIVITY_ACTION_TYPE_ */ int8_t type,
	const DiscordUser* user,
	const DiscordRichPresence* activity,
	const char* sessionId,
	const char* channelId,
	const char* messageId)
{
	if (m_user.HasDiscriminator())
		m_logger->warn("[discord] OnActivityJoinRequest from: {}#{} ({})", m_user.username, m_user.discriminator, m_user.globalName);
	else
		m_logger->warn("[discord] OnActivityInvite from: @{} ({})", m_user.username, m_user.globalName);

	{
		const char* map = SDK().GetPresence().map;
		if (map && *map && std::strcmp(map, "mp_lobby") == 0)
		{
			Chat::showChatLineEasy(_("\n[Discord] "), 0x7289DAFF);
			Chat::showChatLineEasy(user->username, 0xDDDDDDFF);
			Chat::showChatLineEasy(_(" invited you to join their game. You can accept this invite in Discord."), 0xFFFFFFFF);
		}
	}
	//Discord_AcceptInvite(user->userId, type, sessionId, channelId, messageId);
}

void DiscordWrapper::OpenDiscordGuildInvite(const CCommand& args)
{
	if (!isDiscordReady) return;
	Discord_OpenGuildInvite(DISCORD_GUILD_INVITE);
}

void DiscordWrapper::OpenDiscordFriendsInvite(const CCommand& args)
{
	if (!isDiscordReady) return;
	Discord_OpenActivityInvite(DISCORD_ACTIVITY_ACTION_TYPE_JOIN);
}

bool DiscordWrapper::UpdatePresence(const CDiscordRichPresence& presence, bool now)
{
	DiscordRichPresence p;
	presence.CopyTo(&p);
	return UpdatePresence(&p, now);
}

bool DiscordWrapper::UpdatePresence(const DiscordRichPresence* presence, bool now)
{
	std::lock_guard<std::mutex> guard(m_updatePresenceMutex);

	bool isChanged = !m_lastPresence.IsEqualTo(presence);

	if (!isChanged)
	{
		SPDLOG_LOGGER_DEBUG(m_logger, "[discord] Did not update presence, because it was identical to the last one");
		return false;
	}

	m_lastPresence = presence;

	// let's debounce the update
	m_presenceUpdatePendingSince = std::chrono::system_clock::now();
	m_presenceUpdatePending = true;
	if (now)
		m_presenceUpdatePendingForceImmediate = true;

	return true;
}

void DiscordWrapper::UpdateDebouncedPresenceTick()
{
	if (m_presenceUpdatePending
		&& std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_presenceUpdatePendingSince).count()
			> this->presenceUpdatePendingDebounceThresholdMs)
	{
		std::lock_guard<std::mutex> guard(m_updatePresenceMutex);
		m_presenceUpdatePending = false;

		DiscordRichPresence discordPresence;
		m_lastPresence.CopyTo(&discordPresence);
		Discord_UpdatePresence(&discordPresence);

		bool isDiscordJoinable = discordPresence.joinSecret && discordPresence.joinSecret[0];
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
	SPDLOG_LOGGER_DEBUG(m_logger, "DiscordWrapper destructor");
	Discord_Shutdown();
}

void DiscordFrameTask::RunFrame()
{
	if (IsClient() && IsSDKReady())
	{
		auto& discord = DiscordWrap();
		if (&discord != nullptr)
		{
			discord.UpdateDebouncedPresenceTick();
			m_callCount++;
			if (m_callCount >= 5) [[unlikely]]
				{
					m_callCount = 0;
					discord.RunCallbacks();
				}
		}
	}
}
