#include "RadioManager.h"
#include "ChatManager.h"
#include "Player.h"
#include "Constants.h"

using namespace std;

unordered_map<Player *, int> RadioManager::frequencyMap;
unordered_map<Player *, bool> RadioManager::enabledMap;
unordered_map<Player *, bool> RadioManager::ownedMap;

RadioManager::RadioManager()
{
}


RadioManager::~RadioManager()
{
}

void RadioManager::SendMessage(Player *player, string message)
{
	const int messageFrequency = frequencyMap[player];
	string name = player->GetName();

	for (auto otherPlayerIter : frequencyMap)
	{
		// Skip iterating over ourselves, so we don't have duplicate messages
		if (otherPlayerIter.first == player) continue;

		// Do the frequencies match?
		if (otherPlayerIter.second == messageFrequency)
		{
			// Is the other player's radio turned on?
			const bool otherRadioEnabled = enabledMap[otherPlayerIter.first];
			if (otherRadioEnabled)
			{
				string radioMessage = name + " transmits (" + to_string(messageFrequency) + "Hz): " + message;
				ChatManager::OrangeMessage(otherPlayerIter.first, radioMessage);
			}
		}
	}

	string proximityMessage = name + " says (radio): " + message;
	ChatManager::ProximityMessage(player, proximityMessage, 20.f, COLOR_WHITE);
}

void RadioManager::SetRadioFrequency(Player *player, int frequency)
{
	frequencyMap[player] = frequency;

	ChatManager::SystemMessage(player, "You have tuned your walkie talkie to " + to_string(frequency) + "Hz.");
	ChatManager::EmoteMessage(player, player->GetName() + " fiddles with their radio, adjusting the frequency.");
}

void RadioManager::SetEnabled(Player *player, bool enabled)
{
	enabledMap[player] = enabled;

	if (enabled) 
	{
		ChatManager::SystemMessage(player, "Your radio crackles as it comes to life.");
		ChatManager::EmoteMessage(player, "A faint crackle is heard as " + player->GetName() + " turns on their radio.");
	}
	else
	{
		ChatManager::SystemMessage(player, "Your radio goes silent as you turn the volume knob all the way down.");
		ChatManager::EmoteMessage(player, "Static is heard as " + player->GetName() + " turns off their radio.");
	}
	
}

bool RadioManager::IsEnabled(Player *player)
{
	if (enabledMap.find(player) != enabledMap.end())
	{
		return enabledMap[player];
	}
	return false;
}

bool RadioManager::IsOwned(Player *player)
{
	if (ownedMap.find(player) != ownedMap.end())
	{
		return ownedMap[player];
	}
	return false;
}

void RadioManager::SetOwned(Player *player, bool isOwned)
{
	ownedMap[player] = true;
}