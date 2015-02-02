#pragma once
#pragma once

#include <string>
#include "sampgdk.h"

using namespace std;

class Player;

class ChatManager
{
public:
	static void ChatManager::AdminMessage(string message);

	static void ChatManager::SystemMessage(Player *player, string message);
	static void ChatManager::SystemMessage(int playerID, const char *message);

	static void ChatManager::EmoteMessage(Player *player, string message);
	static void ChatManager::EmoteMessage(int playerID, const char *message);

	static void ChatManager::LocalMessage(Player *player, string message);
	static void ChatManager::WhiteMessage(Player *player, string message);

	static void ChatManager::FactionMessage(Player *player, string message);

	static void ChatManager::ProximityMessage(int playerID, const char *message, float distance, int color1, int color2, int color3, int color4, int color5);
	static void ChatManager::ProximityMessage(Player *player, string message, float distance, int color1, int color2, int color3, int color4, int color5);

private:
	ChatManager();
	~ChatManager();
};

