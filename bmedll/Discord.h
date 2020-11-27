#pragma once
#include "ConCommandManager.h"
#include "discord/discord.h"

/*struct DiscordState {
    discord::User currentUser;

    std::unique_ptr<discord::Core> core;
};*/

class DiscordWrapper
{
private:
    
public:
    //discord::Core* core;
    //std::unique_ptr<discord::Core> core;
    //DiscordState state;
    //discord::User currentUser;
    std::unique_ptr<discord::User> currentUser;
    std::unique_ptr<discord::Core> core;

    void OpenDiscordInvite(const CCommand& args);
    void UpdateActivity(discord::Activity activity);

    DWORD WINAPI ThreadProc(LPVOID lpThreadParameter);
    DiscordWrapper(ConCommandManager& conCommandManager);
    ~DiscordWrapper();
};
