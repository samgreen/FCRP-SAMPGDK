#pragma once

#include <unordered_map>
#include <string>

class Player;

class RadioManager
{
public:
	static void SendMessage(Player *player, std::string message);

	static void SetRadioFrequency(Player *player, int frequency);

	static bool IsEnabled(Player *player);
	static void SetEnabled(Player *player, bool enabled);

	static bool IsRadioOwned(Player *player);
	static void SetRadioOwned(Player *player, bool isOwned);
	

private:
	RadioManager();
	~RadioManager();

	static std::unordered_map<Player *, int> frequencyMap;
	static std::unordered_map<Player *, bool> enabledMap;
	static std::unordered_map<Player *, bool> ownedMap;
};

