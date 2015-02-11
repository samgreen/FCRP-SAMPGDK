#pragma once

#include <string>

#include "Point.h"

#include <cereal/archives/json.hpp>

class Player
{
public:
	template <class Archive>
	void save(Archive &archive) const
	{
		archive(level, experience, money, skin, adminLevel, wantedLevel, cropDusterLevel, cropDusterCooldown);
	}

	template <class Archive>
	void load(Archive &archive)
	{
		archive(level, experience, money, skin, adminLevel, wantedLevel, cropDusterLevel, cropDusterCooldown);
	}

	Player();
	Player(int id);
	~Player();

	std::string GetName();
	bool HasValidName();

	int GetID();

	int GetAdminLevel();

	int AddExperience(int addedExperience);
	int GetExperience();

	void SetHealth(int health);
	int GetHealth();

	void SetArmor(int armor);
	int GetArmor();

	void SetSkin(int skinID);
	int GetSkin();

	void SetColor(int color);
	int GetColor();

	void SetTeam(int team);
	int GetTeam();

	void SetLevel(int level);
	int GetLevel();

	int AddMoney(int addedMoney);
	int SubtractMoney(int subtractedMoney);
	int GetMoney();

	int AddRespect(int addedRespect);
	int SubtractRespect(int subtractedRespect);

	int AddSpamTime(int addedTime);

	bool IsHandCuffed();
	void SetHandCuffed(bool cuffed);

	bool IsTied();
	void SetTied(bool tied);

	bool IsGagged();
	void SetGagged(bool gagged);

	void SetWantedLevel(int level);
	int GetWantedLevel();

	void GiveWeapon(int weaponID);
	void GiveWeapon(int weaponID, int ammo);

	void Kill();

	Point3D GetPosition();
	void SetPosition(Point3D position);

	bool IsInRangeOfPlayer(float range, Player *player);
	bool IsInRangeOfPoint(float range, Point3D point);
	float GetDistanceFromPoint(Point3D point);

	float GetFacingAngle();
	void SetFacingAngle(float angle);

	bool IsInVehicle();
	bool IsInVehicleID(int vehicleID);
	int GetVehicleID();
	int GetVehicleModelID();

	int GetVirtualWorld();
	void SetVirtualWorld(int virtualWorldID);

	int GetInterior();
	void SetInterior(int interiorID);

	int GetCropDusterLevel();
	int SetCropDusterLevel(int level);

	void SetCropDusterCooldown(float cooldown);
	float GetCropDusterCooldown();

	int Player::IncrementCoalMiningStat();
	int Player::GetCoalMiningStat();

	void SetCoalMiningLevel(int level);
	int GetCoalMiningLevel();

	void StartAnimation(const char *animationLibrary, const char *animationName, float delta, bool loop, bool lockX, bool lockY, bool freeze, int time, bool forceSync);

	void StartWalkAnimation(int index);
	void StartRunAnimation(int index);
	void StopAnimations();
	bool IsLoopingAnimation();

protected:
	int id;
	std::string name;
	int level;
	int adminLevel;
	int skin;
	int phoneNumber;

	int experience;
	int money;
	int bankMoney;
	int respect;
	int wantedLevel;

	int spamTime;

	int cropDusterLevel;
	float cropDusterCooldown;

	int miningStat;
	int miningLevel;

	int truckingLevel;
	float truckingTime;

	float connectedTime;

	bool isHandcuffed;
	bool isTied;
	bool isGagged;
	bool isLoopingAnimation;
};

