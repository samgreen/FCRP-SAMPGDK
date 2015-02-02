#include "PlayerManager.h"
#include "Player.h"

map<int, Player *> PlayerManager::playerMap;

Player* PlayerManager::GetPlayer(int playerID)
{
	auto index = playerMap.find(playerID);
	if (index != playerMap.end()) {
		return index->second;
	}
	return NULL;
}

const map<int, Player *>::const_iterator PlayerManager::BeginPlayer()
{
	return playerMap.cbegin();
}

const map<int, Player *>::const_iterator PlayerManager::EndPlayer()
{
	return playerMap.cend();
}

//static Player* GetPlayerByName(string name)
//{
//	for (auto i = playerMap.begin(); i < playerMap.end(); i++)
//	{
//		Player *p = i->second;
//		if (p->GetName() == name)
//		{
//			return p;
//		}
//	}
//	return NULL;
//}

void PlayerManager::AddPlayer(Player *player)
{
	playerMap[player->GetID()] = player;
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