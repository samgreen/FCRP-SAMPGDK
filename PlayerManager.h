#pragma once

#include <map>
#include <string>
#include "sampgdk.h"

class Player;

using namespace std;

class PlayerManager
{
public:	
	static Player* GetPlayer(int playerID);
	static string GetName(int playerID);

	static const map<int, Player *>::const_iterator BeginPlayer();
	static const map<int, Player *>::const_iterator EndPlayer();

	static int GetNumPlayers();
	//static Player* GetPlayerByName(string name);

	static void AddPlayer(Player *player);
	static void RemovePlayer(Player *player);	

private:
	PlayerManager();
	~PlayerManager();

	static map<int, Player *> playerMap;
};

