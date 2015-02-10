#pragma once
class PickupManager
{
public:
	static void CreatePickups();

protected:
	static void AddDefaultPickup(int modelID, float x, float y, float z);

private:
	PickupManager();
	~PickupManager();
};

