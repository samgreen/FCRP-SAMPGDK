#include "PlayerManager.h"
#include "Player.h"

#include <fstream>
#include <cereal/archives/json.hpp>

using namespace std;

unordered_map<int, Player *> PlayerManager::playerMap;
unordered_map<string, Player*> PlayerManager::playerNameMap;

void PlayerManager::SavePlayer(Player *player)
{
	string savePath = "data/" + player->GetName() + ".json";
	std::ofstream os(savePath);
	cereal::JSONOutputArchive archive(os); 
	archive(*player);
}

Player* PlayerManager::GetPlayer(int playerID)
{
	auto index = playerMap.find(playerID);
	if (index != playerMap.end()) {
		return index->second;
	}
	return NULL;
}

Player* PlayerManager::GetPlayerByName(string name)
{
	auto index = playerNameMap.find(name);
	if (index != playerNameMap.end()) {
		return index->second;
	}
	return NULL;
}

const unordered_map<int, Player *>::const_iterator PlayerManager::BeginPlayer()
{
	return playerMap.cbegin();
}

const unordered_map<int, Player *>::const_iterator PlayerManager::EndPlayer()
{
	return playerMap.cend();
}

void PlayerManager::AddPlayer(Player *player)
{
	playerMap[player->GetID()] = player;
	playerNameMap[player->GetName()] = player;
}

void PlayerManager::RemovePlayer(Player *player)
{
	playerMap.erase(player->GetID());
}

string PlayerManager::GetName(int playerID)
{
	char name[MAX_PLAYER_NAME];
	GetPlayerName(playerID, name, sizeof(name));
	return string(name);
}

int PlayerManager::GetNumPlayers()
{
	return playerMap.size();
}