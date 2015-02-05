#include "FactionManager.h"
#include "Player.h"
#include "sampgdk.h"

using namespace std;

unordered_map<int, PlayerFaction> FactionManager::playerFactionMap;
unordered_map<int, int> FactionManager::playerFactionRankMap;

void FactionManager::AddLeader(Player *player, PlayerFaction faction)
{
	AddPlayer(player, faction);
	SetRank(player, 6); // Set to leader rank
}

 void FactionManager::AddPlayer(Player *player, PlayerFaction faction)
{
	playerFactionMap[player->GetID()] = faction;
	playerFactionRankMap[player->GetID()] = 0; // Set rank to 0 upon invite

	// Set the player's team to this faction
	player->SetTeam(faction);
	// Set the other player's skin to the default skin
	player->SetSkin(GetDefaultSkin(faction));
}

 void FactionManager::RemovePlayer(Player *player)
{
	playerFactionMap.erase(player->GetID());
}

 int FactionManager::GetDefaultSkin(PlayerFaction faction)
{
	return GetSkin(faction, 0);
}

 int FactionManager::GetSkin(PlayerFaction faction, int index)
{
	switch (faction)
	{
	case PlayerFactionCivilian:		return 10;
	case PlayerFactionKaito:		return 147;
	case PlayerFactionFinalBuild:	return 187;
	case PlayerFactionTaxi:			return 253;
	case PlayerFactionEMT:			return 274;
	case PlayerFactionPolice:		return 283;
	case PlayerFactionDemons:		return 248;
	case PlayerFactionErretat:		return 58;
	case PlayerFactionDisciples:	return 271;
	case PlayerFactionCholos:		return 114;
	case PlayerFactionTen:			return 1;
	case PlayerFactionUber:			return 43;
	}
	return 1;
}

 PlayerFaction FactionManager::GetFaction(Player *player)
{
	auto index = playerFactionMap.find(player->GetID());
	if (index != playerFactionMap.end()) {
		return index->second;
	}
	return PlayerFactionCivilian;
}

int FactionManager::GetRank(Player *player)
{
	auto index = playerFactionRankMap.find(player->GetID());
	if (index != playerFactionRankMap.end()) {
		return index->second;
	}
	return -1;
}

void FactionManager::SetRank(Player *player, int rank)
{
	playerFactionRankMap[player->GetID()] = rank;
}

 string FactionManager::GetName(PlayerFaction faction)
{
	switch (faction)
	{
	case PlayerFactionCivilian:		return "";
	case PlayerFactionKaito:		return "Kaito";
	case PlayerFactionFinalBuild:	return "Final Build Corporation";
	case PlayerFactionTaxi:			return "Taxi";
	case PlayerFactionEMT:			return "EMT";
	case PlayerFactionPolice:		return "BCSD";
	case PlayerFactionDemons:		return "Mojave Demons";
	case PlayerFactionErretat:		return "Erretat Tribe";
	case PlayerFactionDisciples:	return "Disciples";
	case PlayerFactionCholos:		return "Cholos";
	case PlayerFactionTen:			return "CIA";
	case PlayerFactionUber:			return "Uber Drivers";
	}
	return "Unknown faction";
}

 PlayerFactionType FactionManager::GetType(PlayerFaction faction)
{
	switch (faction)
	{
	case PlayerFactionCivilian:		return PlayerFactionTypeUnknown;
	case PlayerFactionKaito:		return PlayerFactionTypeCorporation;
	case PlayerFactionFinalBuild:	return PlayerFactionTypeCorporation;
	case PlayerFactionTaxi:			return PlayerFactionTypeFaction;
	case PlayerFactionEMT:			return PlayerFactionTypeFaction;
	case PlayerFactionPolice:		return PlayerFactionTypeFaction;
	case PlayerFactionDemons:		return PlayerFactionTypeFamily;
	case PlayerFactionErretat:		return PlayerFactionTypeFamily;
	case PlayerFactionDisciples:	return PlayerFactionTypeFamily;
	case PlayerFactionCholos:		return PlayerFactionTypeFamily;
	case PlayerFactionUber:			return PlayerFactionTypeFamily;
	case PlayerFactionTen:			return PlayerFactionTypeUnknown;
	}
	return PlayerFactionTypeUnknown;
}