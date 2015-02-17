#pragma once
#include <unordered_map>
#include <string>
#include "Player.h"

typedef enum {
	PlayerFactionCivilian,
	PlayerFactionKaito,
	PlayerFactionFinalBuild,
	PlayerFactionTaxi,
	PlayerFactionEMT,
	PlayerFactionPolice,
	PlayerFactionDemons,
	PlayerFactionErretat,
	PlayerFactionDisciples,
	PlayerFactionCholos,
	PlayerFactionTen, // TODO: Give these to froshy
	PlayerFactionUber,
	PlayerFactionNumberOfFactions,
} PlayerFaction;

typedef enum {
	PlayerFactionTypeUnknown,
	PlayerFactionTypeCorporation,
	PlayerFactionTypeFaction,
	PlayerFactionTypeFamily,
	PlayerFactionTypeNumberOfTypes,
} PlayerFactionType;

class FactionManager
{
public:
	static void AddPlayer(Player *player, PlayerFaction faction);
	static void AddLeader(Player *player, PlayerFaction faction);
	static void RemovePlayer(Player *player);

	static int GetDefaultSkin(PlayerFaction faction);
	static int GetSkin(PlayerFaction faction, int index);

	static PlayerFaction GetFaction(Player *player);
	static bool IsInSameFaction(Player *player, Player *otherPlayer);

	static int GetRank(Player *player);
	static void SetRank(Player *player, int rank);

	static std::string GetName(PlayerFaction faction);
	static PlayerFactionType GetType(PlayerFaction faction);

private:
	FactionManager();
	~FactionManager();

	static std::unordered_map<int, PlayerFaction> playerFactionMap;
	static std::unordered_map<int, int> playerFactionRankMap;
};

