#pragma once

#include <unordered_map>

class Player;

class SkinManager
{
public:
	static void NextSkin(Player *player);
	static void PreviousSkin(Player *player);
	static int GetSkin(Player *player);

private:
	SkinManager();
	~SkinManager();

	static std::unordered_map<Player *, int> skinMap;
};

