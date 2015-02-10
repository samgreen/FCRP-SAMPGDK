#include "Player.h"
#include "sampgdk.h"
#include "Constants.h"

using namespace std;

Player::Player() : Player(-1) {}

Player::Player(int id) : id(id), level(1), adminLevel(0), money(500), bankMoney(1500), skin(170), isTied(false), isHandcuffed(false), cropDusterLevel(0), cropDusterCooldown(0.f), miningLevel(0), miningStat(0)
{
	SetPlayerSkin(id, skin);
	AddMoney(100000);
}


Player::~Player()
{

}

string Player::GetName()
{
	char nameChar[MAX_PLAYER_NAME];
	GetPlayerName(id, nameChar, sizeof(nameChar));
	name = string(nameChar);
	return name;
}
 
bool Player::HasValidName()
{
	string name = GetName();
	std::size_t found = name.find("_");
	return (found != std::string::npos);
}

int Player::GetID()
{
	return id;
}

int Player::GetAdminLevel()
{
	if (IsPlayerAdmin(id)) return 1337;
	return adminLevel;
}

int Player::AddExperience(int addedExperience)
{
	experience += addedExperience;
	return experience;
}

int Player::GetExperience()
{
	return experience;
}

void Player::StartWalkAnimation(int index)
{
	static const char *WALK_ANIMATIONS[] = 
	{
		"WALK_GANG1",
		"WALK_GANG2",
		"WALK_FAT",
		"WALK_FATOLD",
		"WALK_OLD",
		"WOMAN_WALKNORM",
		"WOMAN_WALKSEXY",
		"WALK_WUZI"
	};
	const int MAX_WALKS = ARRAY_SIZE(WALK_ANIMATIONS);

	if (index < MAX_WALKS)
	{
		StartAnimation("PED", WALK_ANIMATIONS[index], 4.1f, true, true, true, true, 1, true);
	}
}

void Player::StartAnimation(const char *animationLibrary, const char *animationName, float delta, bool loop, bool lockX, bool lockY, bool freeze, int time, bool forceSync)
{
	isLoopingAnimation = loop;
	ApplyAnimation(id, animationLibrary, animationName, delta, loop, lockX, lockY, freeze, time, forceSync);

	if (isLoopingAnimation)
	{
		GameTextForPlayer(id, "~p~Press the sprint key to stop the animation.", 3000, 1);
	}
}

void Player::StopAnimations()
{
	//ApplyAnimation(id, "CARRY", "crry_prtial", 4.f, false, false, false, false, false, true); // clears animations
	ClearAnimations(id, true);
}

bool Player::IsLoopingAnimation()
{
	return isLoopingAnimation;
}

void Player::SetHealth(int health)
{
	SetPlayerHealth(id, (float)health);
}

int Player::GetHealth()
{
	float health;
	GetPlayerHealth(id, &health);
	return (int)health;
}

void Player::SetArmor(int armor)
{
	SetPlayerArmour(id, (float)armor);
}

int Player::GetArmor()
{
	float armor;
	GetPlayerArmour(id, &armor);
	return (int)armor;
}

void Player::SetSkin(int skinID)
{
	SetPlayerSkin(id, skinID);
}

int Player::GetSkin()
{
	return GetPlayerSkin(id);
}

void Player::SetColor(int color)
{
	SetPlayerColor(id, color);
}

int Player::GetColor()
{
	return GetPlayerColor(id);
}

void Player::SetTeam(int team)
{
	SetPlayerTeam(id, team);
}

int Player::GetTeam()
{
	return GetPlayerTeam(id);
}

void Player::SetLevel(int level)
{
	level = level;

	SetPlayerScore(id, level); // Set their score to their current level so it will be shown in the tab screen
}

int Player::GetLevel()
{
	return level;
}

int Player::AddMoney(int addedMoney)
{
	GivePlayerMoney(id, addedMoney);

	money += addedMoney;
	return money;
}

int Player::SubtractMoney(int subtractedMoney)
{
	GivePlayerMoney(id, -subtractedMoney);

	money -= subtractedMoney;
	return money;
}

int Player::GetMoney()
{
	return money;
}

int Player::AddRespect(int addedRespect)
{
	respect += addedRespect;
	return respect;
}

int Player::SubtractRespect(int subtractedRespect)
{
	respect -= subtractedRespect;
	return respect;
}

int Player::AddSpamTime(int addedTime)
{
	spamTime += addedTime;
	return spamTime;
}

bool Player::IsHandCuffed()
{
	return isHandcuffed;
}

void Player::SetHandCuffed(bool cuffed)
{
	isHandcuffed = cuffed;

	TogglePlayerControllable(id, isHandcuffed);

	// Add animations
	ClearAnimations(id, true);
	ApplyAnimation(id, "CRACK", "crckdeth2", 4.0, true, false, false, false, 0, true);
}

bool Player::IsTied()
{
	return isTied;
}

void Player::SetTied(bool tied)
{
	isTied = tied;
}

bool Player::IsGagged()
{
	return isGagged;
}

void Player::SetGagged(bool gagged)
{
	isGagged = gagged;
}

void Player::SetWantedLevel(int level)
{
	SetPlayerWantedLevel(id, level);
}

int Player::GetWantedLevel()
{
	return GetPlayerWantedLevel(id);
}

void Player::Kill()
{
	SetPlayerHealth(id, 0);
}

void Player::GiveWeapon(int weaponID)
{
	GiveWeapon(weaponID, MAX_AMMO);
}
void Player::GiveWeapon(int weaponID, int ammo)
{
	GivePlayerWeapon(id, weaponID, ammo);
}

Point3D Player::GetPosition()
{
	float x, y, z;
	GetPlayerPos(id, &x, &y, &z);
	return Point3D{ x, y, z };
}

void Player::SetPosition(Point3D position)
{
	SetPlayerPos(id, position.x, position.y, position.z);
}

bool Player::IsInRangeOfPlayer(float range, Player *player)
{
	return IsInRangeOfPoint(range, player->GetPosition());
}

bool Player::IsInRangeOfPoint(float range, Point3D point)
{
	return IsPlayerInRangeOfPoint(id, range, point.x, point.y, point.z);
}

float Player::GetDistanceFromPoint(Point3D point)
{
	return GetPlayerDistanceFromPoint(id, point.x, point.y, point.z);
}

float Player::GetFacingAngle()
{
	float angle;
	GetPlayerFacingAngle(id, &angle);
	return angle;
}

void Player::SetFacingAngle(float angle)
{
	SetPlayerFacingAngle(id, angle);
}

bool Player::IsInVehicle()
{
	return IsPlayerInAnyVehicle(id);
}

int Player::GetVehicleID()
{
	return GetPlayerVehicleID(id);
}

int Player::GetVehicleModelID()
{
	return GetVehicleModel(GetVehicleID());
}

bool Player::IsInVehicleID(int vehicleID)
{
	if (IsInVehicle()) {
		return (GetVehicleID() == vehicleID);
	}
	return false;
}

int Player::GetVirtualWorld()
{
	return GetPlayerVirtualWorld(id);
}

void Player::SetVirtualWorld(int virtualWorldID)
{
	SetPlayerVirtualWorld(id, virtualWorldID);
}

int Player::GetInterior()
{
	return GetPlayerInterior(id);
}

void Player::SetInterior(int interiorID)
{
	SetPlayerInterior(id, interiorID);
}

int Player::GetCropDusterLevel()
{
	return cropDusterLevel;
}

void Player::SetCropDusterCooldown(float cooldown)
{
	cropDusterCooldown = cooldown;
}

float Player::GetCropDusterCooldown()
{
	return cropDusterCooldown;
}

int Player::IncrementCoalMiningStat()
{
	return ++miningStat;
}

int Player::GetCoalMiningStat()
{
	return miningStat;
}

void Player::SetCoalMiningLevel(int level)
{
	miningLevel = level;
}

int Player::GetCoalMiningLevel()
{
	return miningLevel;
}