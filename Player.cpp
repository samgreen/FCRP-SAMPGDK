#include "Player.h"
#include "sampgdk.h"
#include "Constants.h"

using namespace std;

Player::Player() : Player(-1) {}

Player::Player(int id) : id(id), level(1), adminLevel(0), money(500), bankMoney(1500), skin(170), isTied(false), isHandcuffed(false), cropDusterLevel(0), cropDusterCooldown(0.f)
{
	SetPlayerSkin(id, skin);
}


Player::~Player()
{

}

string Player::GetName()
{
	char name[MAX_PLAYER_NAME];
	GetPlayerName(id, name, sizeof(name));
	return string(name);
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
	money += addedMoney;
	return money;
}

int Player::SubtractMoney(int subtractedMoney)
{
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