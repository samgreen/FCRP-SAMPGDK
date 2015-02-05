#pragma once

#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

#include "Player.h"
#include "ChatManager.h"

static bool IsNumeric(const std::string &s)
{
	return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;
}

static std::vector<std::string> split(std::string s)
{
	std::vector<std::string> tokens;
	if (s.size() == 0) return tokens;

	std::stringstream stringStream(s);
	std::copy(std::istream_iterator<std::string>(stringStream), std::istream_iterator<std::string>(), std::back_inserter(tokens));

	return tokens;
}

static bool AdminLevelCheck(Player *player, int level)
{
	sampgdk_logprintf("Checking %s admin level. Show %d - Need %d", player->GetName().c_str(), player->GetAdminLevel(), level);

	bool authorized = (player->GetAdminLevel() >= level);
	if (!authorized) {
		ChatManager::SystemMessage(player, "You are not authorized to use this command.");
	}
	return authorized;
}