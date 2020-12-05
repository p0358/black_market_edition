#pragma once

class Chat
{
public:
    static void showChatLineEasy(const char* str, unsigned int color); // first two bytes of color are opacity, FF = visible fully
    static void showChatLineAsPlayer(int playerSlot, const char* str, bool isTeam, double xmm0_8_0);

    Chat();
    ~Chat();
};