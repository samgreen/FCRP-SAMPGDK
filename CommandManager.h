#pragma once
#include <string>

#include "Player.h"

class CommandManager
{
public:
	CommandManager();
	~CommandManager();

	bool OnPlayerCommandText(Player *player, string commandText);
	bool OnPlayerCommandText(int playerID, const char *commandText);
};

