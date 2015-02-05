#pragma once

#include <string>
#include "Point.h"

class Player
{
public:
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

	void SetWantedLevel(int level);
	int GetWantedLevel();

	void GiveWeapon(int weaponID);
	void GiveWeapon(int weaponID, int ammo);

	void Kill();

	Point3D GetPosition();
	void SetPosition(Point3D position);

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

protected:
	int id;
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

	int miningLevel;
	float miningTime;

	int truckingLevel;
	float truckingTime;

	float connectedTime;

	bool isHandcuffed;
	bool isTied;
};

