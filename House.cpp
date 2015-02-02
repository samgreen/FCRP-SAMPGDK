#include "House.h"


House::House()
{
}


House::~House()
{
}

int House::GetID()
{
	return id;
}

int House::GetPickupID()
{
	return pickupID;
}

string House::GetDescription()
{
	return description;
}

void House::SetDescription(string desc)
{
	description = desc;
}

int House::GetType()
{
	return type;
}

int House::GetOwnerID()
{
	return owner;
}

int House::GetPrice()
{
	return price;
}

int House::GetInterior()
{
	return interior;
}

float House::GetExitHeading()
{
	return exitHeading;
}

int House::GetVehicleID()
{
	return vehicleID;
}

Point3D House::GetVehiclePosition()
{
	return vehiclePosition;
}

float House::GetVehicleHeading()
{
	return vehicleHeading;
}

int House::GetVehicleColor(int index)
{
	if (index == 0)
	{
		return vehicleColor1;
	}

	return vehicleColor2;
}

Point3D House::GetEntrancePosition()
{
	return entrancePosition;
}

Point3D House::GetInteriorEntrancePosition()
{
	return interiorEntrancePosition;
}
