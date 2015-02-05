#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Player;

typedef bool(*CommandFunction)(Player *player, std::string text, std::vector<std::string> params);

class CommandManager
{
public:
	CommandManager();
	~CommandManager();

	bool OnPlayerCommandText(Player *player, std::string commandText);

	CommandFunction GetCommand(std::string command);

	static Player* GetPlayerFromParams(std::vector<std::string> params, std::vector<std::string>::size_type index = 0);
	static Player* GetPlayerFromParams(Player *player, std::vector<std::string> params, std::vector<std::string>::size_type index);

private:
	std::unordered_map<std::string, CommandFunction> commandMap;
	std::unordered_map<CommandFunction, int> commandAdminLevelMap;
};

