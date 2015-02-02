#pragma once
#include <map>
#include <string>
#include "Player.h"

using namespace std;

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
	static void RemovePlayer(Player *player);

	static int GetDefaultSkin(PlayerFaction faction);
	static int GetSkin(PlayerFaction faction, int index);

	static PlayerFaction GetFaction(Player *player);

	static int GetRank(Player *player);

	static string GetName(PlayerFaction faction);
	static PlayerFactionType GetType(PlayerFaction faction);

private:
	FactionManager();
	~FactionManager();

	static map<int, PlayerFaction> playerFactionMap;
	static map<int, int> playerFactionRankMap;
};

