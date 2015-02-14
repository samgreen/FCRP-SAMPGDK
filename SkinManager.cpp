#include "SkinManager.h"
#include "Player.h"
#include "Constants.h"

std::unordered_map<Player *, int> SkinManager::skinMap;

SkinManager::SkinManager()
{
}

SkinManager::~SkinManager()
{
}

void SkinManager::NextSkin(Player *player)
{
	if (skinMap.find(player) == skinMap.end()) {
		skinMap[player] = CIVILIAN_SKINS[0];
	}
	else
	{
		skinMap[player] = skinMap[player]++;
		if (skinMap[player] > ARRAY_SIZE(CIVILIAN_SKINS))
		{
			skinMap[player] = 0;
		}
	}
	player->SetSkin(GetSkin(player));
}

void SkinManager::PreviousSkin(Player *player)
{
	if (skinMap.find(player) == skinMap.end()) {
		skinMap[player] = CIVILIAN_SKINS[0];
	}
	else
	{
		skinMap[player] = skinMap[player]--;
		if (skinMap[player] < 0)
		{
			skinMap[player] = ARRAY_SIZE(CIVILIAN_SKINS);
		}
	}
	player->SetSkin(GetSkin(player));
}

int SkinManager::GetSkin(Player *player)
{
	return CIVILIAN_SKINS[skinMap[player]];
}
