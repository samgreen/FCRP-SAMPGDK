#pragma once
#include <string>
#include "Point.h"

class House
{
public:
	House();
	~House();

	int GetID();
	int GetPickupID();

	std::string GetDescription();
	void SetDescription(std::string desc);

	int GetType();
	int GetOwnerID();
	int GetPrice();
	int GetInterior();
	float GetExitHeading();

	int GetVehicleID();
	Point3D GetVehiclePosition();
	float GetVehicleHeading();
	int GetVehicleColor(int index);

	Point3D GetEntrancePosition();
	Point3D GetInteriorEntrancePosition();

private:
	int id;
	int pickupID;

	std::string description;
		
	int type;
	int owner;
	int price;
	int interior;
	float exitHeading;

	int vehicleID;
	Point3D vehiclePosition;
	float vehicleHeading;
	int vehicleColor1;
	int vehicleColor2;

	Point3D entrancePosition;
	Point3D interiorEntrancePosition;
};

