#pragma once

#include <string>
#include <unordered_map>

#include "sampgdk.h"

class VehicleManager
{
public:
	static void CreateStartingVehicles(); // Create the initial starting vehicles on the server

	static std::string GetVehicleName(int vehicleID);

	static bool IsCropduster(int vehicleID);
	static bool IsSemiTruck(int vehicleID);
	static bool IsBoat(int vehicleID);
	static bool IsBike(int vehicleID);

	static bool IsClassDVehicle(int vehicleID);		// standard cars
	static bool IsClassCVehicle(int vehicleID);		// heavy duty
	static bool IsClassBVehicle(int vehicleID);		// bikes 
	static bool IsClassB2Vehicle(int vehicleID); 	// sports bikes
	static bool IsClassPVehicle(int vehicleID);		// airplanes
	static bool IsClassRVehicle(int vehicleID);		// whirlybirds
	static bool IsClassM2Vehicle(int vehicleID);	// military

	// Windows
	static bool IsWindowOpen(int vehicleID);
	static void SetWindowState(int vehicleID, bool isOpen);

private:
	VehicleManager();
	~VehicleManager();

	static std::unordered_map<int, bool> vehicleWindowMap;
};