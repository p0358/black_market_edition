#pragma once
#include "ConCommandManager.h"
#include "IFrameTask.h"
#include <discord_rpc.h>

class TTFSDK;

class CDiscordUser
{
public:
	std::string userId{};
	std::string username{};
	std::string discriminator{};
	std::string globalName{};
	std::string avatar{};

	static CDiscordUser FromDiscordUser(const DiscordUser* user)
	{
		CDiscordUser cuser;
		cuser.CopyFrom(user);
		return cuser;
	}

	void CopyFrom(const DiscordUser* user)
	{
		if (!user)
			return;
		if (user->userId) this->userId = user->userId;
		if (user->username) this->username = user->username;
		if (user->discriminator) this->discriminator = user->discriminator;
		if (user->globalName) this->globalName = user->globalName;
		if (user->avatar) this->avatar = user->avatar;
	}

	void CopyFrom(const CDiscordUser& p)
	{
		DiscordUser cp;
		p.CopyTo(&cp);
		this->CopyFrom(&cp);
	}

	CDiscordUser& operator=(const DiscordUser* p) { this->CopyFrom(p); return *this; }
	CDiscordUser& operator=(const CDiscordUser& p) { this->CopyFrom(p); return *this; }

	void CopyTo(DiscordUser* user) const
	{
		if (!user)
			return;
		user->userId = this->userId.c_str();
		user->username = this->username.c_str();
		user->discriminator = this->discriminator.c_str();
		user->globalName = this->globalName.c_str();
		user->avatar = this->avatar.c_str();
	}

	bool IsEqualTo(const DiscordUser* user) const
	{
		if (!user)
			return false;
		auto IsStrEqual = [](const std::string& a, const char* b) [[msvc::forceinline]] {
			return (!b && !a.length()) || (b && a == b);
			};
		return IsStrEqual(this->userId, user->userId)
			&& IsStrEqual(this->username, user->username)
			&& IsStrEqual(this->discriminator, user->discriminator)
			&& IsStrEqual(this->globalName, user->globalName)
			&& IsStrEqual(this->avatar, user->avatar);
	}

	bool IsEqualTo(const CDiscordUser& p) const // this is lazy implementation, hopefully compiler optimizes it out :)
	{
		DiscordUser tmp;
		p.CopyTo(&tmp);
		return this->IsEqualTo(&tmp);
	}

	bool operator==(const DiscordUser* p) const { return this->IsEqualTo(p); }
	bool operator==(const CDiscordUser& p) const { return this->IsEqualTo(p); }
	bool operator==(const CDiscordUser* p) const { return this->IsEqualTo(*p); }

	bool HasDiscriminator() const
	{
		return this->discriminator.length() && this->discriminator != "0";
	}
};

/*struct CDiscordButton
{
	std::string label;
	std::string url;
};*/

class CDiscordRichPresence
{
public:
	std::string state{};
	std::string details{};
	int64_t startTimestamp{ 0 };
	int64_t endTimestamp{ 0 };
	std::string largeImageKey{};
	std::string largeImageText{};
	std::string smallImageKey{};
	std::string smallImageText{};
	std::string partyId{};
	int partySize{ 0 };
	int partyMax{ 0 };
	int partyPrivacy{ 0 };
	std::string matchSecret{};
	std::string joinSecret{};
	std::string spectateSecret{};
	int8_t instance{ 0 };
	//std::vector<CDiscordButton> buttons{};

	static CDiscordRichPresence FromDiscordRichPresence(const DiscordRichPresence* p)
	{
		CDiscordRichPresence cp;
		cp.CopyFrom(p);
		return cp;
	}

	void CopyFrom(const DiscordRichPresence* p)
	{
		if (!p)
			return;
		if (p->state) this->state = p->state;
		if (p->details) this->details = p->details;
		this->startTimestamp = p->startTimestamp;
		this->endTimestamp = p->endTimestamp;
		if (p->largeImageKey) this->largeImageKey = p->largeImageKey;
		if (p->largeImageText) this->largeImageText = p->largeImageText;
		if (p->smallImageKey) this->smallImageKey = p->smallImageKey;
		if (p->smallImageText) this->smallImageText = p->smallImageText;
		if (p->partyId) this->partyId = p->partyId;
		this->partySize = p->partySize;
		this->partyMax = p->partyMax;
		this->partyPrivacy = p->partyPrivacy;
		if (p->matchSecret) this->matchSecret = p->matchSecret;
		if (p->joinSecret) this->joinSecret = p->joinSecret;
		if (p->spectateSecret) this->spectateSecret = p->spectateSecret;
		this->instance = p->instance;
		/*this->buttons.clear();
		if (p->buttons)
		{
			for (uint8_t i = 0; true; i++)
			{
				const DiscordButton& btn = p->buttons[i];
				if (!btn.label || !btn.label[0])
					break;
				this->buttons.push_back({ .label = btn.label, .url = btn.url });
			}
		}*/
	}

	void CopyFrom(const CDiscordRichPresence& p)
	{
		DiscordRichPresence cp;
		p.CopyTo(&cp);
		this->CopyFrom(&cp);
	}

	CDiscordRichPresence& operator=(const DiscordRichPresence* p) { this->CopyFrom(p); return *this; }
	CDiscordRichPresence& operator=(const CDiscordRichPresence& p) { this->CopyFrom(p); return *this; }

	void CopyTo(DiscordRichPresence* p) const
	{
		if (!p)
			return;
		p->state = this->state.c_str();
		p->details = this->details.c_str();
		p->startTimestamp = this->startTimestamp;
		p->endTimestamp = this->endTimestamp;
		p->largeImageKey = this->largeImageKey.c_str();
		p->largeImageText = this->largeImageText.c_str();
		p->smallImageKey = this->smallImageKey.c_str();
		p->smallImageText = this->smallImageText.c_str();
		p->partyId = this->partyId.c_str();
		p->partySize = this->partySize;
		p->partyMax = this->partyMax;
		p->partyPrivacy = this->partyPrivacy;
		p->matchSecret = this->matchSecret.c_str();
		p->joinSecret = this->joinSecret.c_str();
		p->spectateSecret = this->spectateSecret.c_str();
		p->instance = this->instance;
		p->buttons = nullptr;
	}

	bool IsEqualTo(const DiscordRichPresence* p) const
	{
		if (!p)
			return false;
		auto IsStrEqual = [](const std::string& a, const char* b) [[msvc::forceinline]] {
			return (!b && !a.length()) || (b && a == b);
			};
		return IsStrEqual(this->state, p->state)
			&& IsStrEqual(this->details, p->details)
			&& this->startTimestamp == p->startTimestamp
			&& this->endTimestamp == p->endTimestamp
			&& IsStrEqual(this->largeImageKey, p->largeImageKey)
			&& IsStrEqual(this->largeImageText, p->largeImageText)
			&& IsStrEqual(this->smallImageKey, p->smallImageKey)
			&& IsStrEqual(this->smallImageText, p->smallImageText)
			&& IsStrEqual(this->partyId, p->partyId)
			&& this->partySize == p->partySize
			&& this->partyMax == p->partyMax
			&& this->partyPrivacy == p->partyPrivacy
			&& IsStrEqual(this->matchSecret, p->matchSecret)
			&& IsStrEqual(this->joinSecret, p->joinSecret)
			&& IsStrEqual(this->spectateSecret, p->spectateSecret)
			&& this->instance == p->instance;
	}

	bool IsEqualTo(const CDiscordRichPresence& p) const // this is lazy implementation, hopefully compiler optimizes it out :)
	{
		DiscordRichPresence tmp;
		p.CopyTo(&tmp);
		return this->IsEqualTo(&tmp);
	}

	bool operator==(const DiscordRichPresence* p) const { return this->IsEqualTo(p); }
	bool operator==(const CDiscordRichPresence& p) const { return this->IsEqualTo(p); }
	bool operator==(const CDiscordRichPresence* p) const { return this->IsEqualTo(*p); }
};

class DiscordWrapper
{
private:
	std::shared_ptr<spdlog::logger> m_logger;
	std::mutex m_updatePresenceMutex;
	CDiscordUser m_user;
	CDiscordRichPresence m_lastPresence;
	bool m_presenceUpdatePending = false;
	bool m_presenceUpdatePendingForceImmediate = false;
	std::chrono::system_clock::time_point m_presenceUpdatePendingSince;
public:
	bool isDiscordReady = false;
	short presenceUpdatePendingDebounceThresholdMs = 1500;

	void handleDiscordReady(const DiscordUser* connectedUser);
	void handleDiscordDisconnected(int errcode, const char* message);
	void handleDiscordError(int errcode, const char* message);
	void handleDiscordDebug(char isOut, const char* opcodeName, const char* message, uint32_t messageLength);
	void handleDiscordJoin(const char* secret);
	void handleDiscordSpectate(const char* secret);
	void handleDiscordJoinRequest(const DiscordUser* request);
	void handleDiscordInvited(/* DISCORD_ACTIVITY_ACTION_TYPE_ */ int8_t type,
		const DiscordUser* user,
		const DiscordRichPresence* activity,
		const char* sessionId,
		const char* channelId,
		const char* messageId);

	void OpenDiscordGuildInvite(const CCommand& args);
	void OpenDiscordFriendsInvite(const CCommand& args);
	bool UpdatePresence(const CDiscordRichPresence& presence, bool now = false);
	bool UpdatePresence(const DiscordRichPresence* presence, bool now = false);

	void UpdateDebouncedPresenceTick();
	void RunCallbacks();

	DiscordWrapper();
	~DiscordWrapper();
};

class DiscordFrameTask : public IFrameTask
{
public:
	DiscordFrameTask() = default;
	virtual ~DiscordFrameTask() = default;
	virtual void RunFrame() override;
	virtual bool IsFinished() override { return false; };
private:
	int8_t m_callCount = 0;
};
