#pragma once
#include <unordered_map>

class Player;

class CoalmineManager
{
public:
	static void Start(Player *player);
	static void MinuteTimer();

	static bool IsMining(Player *player);
	static void OnPlayerEnterRaceCheckpoint(Player *player);
	static void OnPlayerEnterVehicle(Player *player);
	static void OnPlayerExitVehicle(Player *player);

private:
	CoalmineManager();
	~CoalmineManager();

	static int GetCooldownTime(Player *player);
	static bool CheckTime(Player *player);

	static void SetCheckpoint(Player *player, int index);

	static std::unordered_map<int, int> cooldownTime;
	static std::unordered_map<int, int> currentCheckPoint;
};

