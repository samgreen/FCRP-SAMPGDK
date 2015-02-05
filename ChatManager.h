#pragma once
#pragma once

#include <string>
#include "sampgdk.h"

class Player;

class ChatManager
{
public:
	static void ChatManager::SystemMessage(Player *player, std::string message);
	static void ChatManager::AdminMessage(std::string message);
	static void ChatManager::EmoteMessage(Player *player, std::string message);
	static void ChatManager::LocalMessage(Player *player, std::string message);
	static void ChatManager::WhiteMessage(Player *player, std::string message);
	static void ChatManager::FactionMessage(Player *player, std::string message);

	static void ChatManager::ErrorMessageInvalidPlayer(Player *player);

	static void ChatManager::ProximityMessage(Player *player, std::string message, float distance, int color1, int color2, int color3, int color4, int color5);

private:
	ChatManager();
	~ChatManager();
};

