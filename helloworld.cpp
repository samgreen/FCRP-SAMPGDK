#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <string>
#include <vector>

#include "sampgdk.h"
#include "Constants.h"
#include "Player.h"
#include "ChatManager.h"
#include "CommandManager.h"
#include "VehicleManager.h"
#include "PickupManager.h"
#include "PlayerManager.h"
#include "JobManager.h"
#include "CoalmineManager.h"

using namespace std;

static CommandManager *commandManager = new CommandManager;
static PlayerManager *playerManager;
static VehicleManager *vehicleManager;
static CoalmineManager *coalManager;

void SAMPGDK_CALL GlobalMinuteTimer(int timerid, void *params) {
	JobManager::MinuteTimer();
	CoalmineManager::MinuteTimer();
}

void SAMPGDK_CALL GlobalSecondTimer(int timerid, void *params) {
	JobManager::SecondTimer();
}
 
PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
	sampgdk::logprintf("----------------------------------");
	sampgdk::logprintf(" Fort Carson: Roleplay");
	sampgdk::logprintf("----------------------------------");

	// Create the initial vehicles 
	VehicleManager::CreateStartingVehicles();

	UsePlayerPedAnims();
	AllowInteriorWeapons(true);
	SetNameTagDrawDistance(10);
	EnableStuntBonusForAll(false);
	DisableInteriorEnterExits();
	ShowPlayerMarkers(1);

	SetGameModeText("BC-RP v0.1 ALPHA");
	AddPlayerClass(0, 1958.3783f, 1343.1572f, 15.3746f, 269.1425f, 0, 0, 0, 0, 0, 0);

	// Add job manager timers
	SetTimer(SECOND_IN_MS, true, GlobalSecondTimer, 0);
	SetTimer(MINUTE_IN_MS, true, GlobalMinuteTimer, 0);

	return true;
}

// TODO: OnPlayerStateChange
// TODO: Abort coalmine / cropdust if they exit vehicle
 
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
	Player *player = new Player(playerid);
	PlayerManager::AddPlayer(player);

	string message = player->GetName() + " has joined the server.";
	SendClientMessageToAll(COLOR_GOLD, message.c_str());

	// DEBUG
	JobManager::SetType(player, JobTypeWheelman);
	player->SetGagged(true);

	SetPlayerInterior(playerid, 0);
	SetPlayerPos(playerid, 163.984863f, 1213.388305f, 21.501449f);
	SetPlayerFacingAngle(playerid, 221.263046f);
	SetPlayerCameraPos(playerid, 165.959655f, 1203.647216f, 19.609039f);
	SetPlayerCameraLookAt(playerid, 169.6875f, 1217.8063f, 22.1361f, 0);
	ApplyAnimation(playerid, "SMOKING", "M_smklean_loop", 4.0, true, false, false, false, 0, false); // Smoke

	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason) {
	Player *player = PlayerManager::GetPlayer(playerid);
	PlayerManager::SavePlayer(player);

	string message = player->GetName() + " has left the server.";
	SendClientMessageToAll(COLOR_GOLD, message.c_str());

	PlayerManager::RemovePlayer(player);

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid) {
	SetPlayerInterior(playerid, 0);
	SetPlayerPos(playerid, 163.984863f, 1213.388305f, 21.501449f);
	SetPlayerFacingAngle(playerid, 221.263046f);
	SetPlayerCameraPos(playerid, 165.959655f, 1203.647216f, 19.609039f);
	SetPlayerCameraLookAt(playerid, 169.6875f, 1217.8063f, 22.1361f, 0);
	ApplyAnimation(playerid, "SMOKING", "M_smklean_loop", 4.0, true, false, false, false, 0, false); // Smoke

	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid) {
	SetPlayerInterior(playerid, 0);

	sampgdk_logprintf("%s has spawned.", PlayerManager::GetPlayer(playerid)->GetName().c_str());
	
	//int randomSpawnIndex = rand() % sizeof(RANDOM_SPAWNS);
	//float *randomSpawn = RANDOM_ARRAY_ELEMENT(RANDOM_SPAWNS);
	//float x = RANDOM_SPAWNS[randomSpawnIndex][0];
	//float y = RANDOM_SPAWNS[randomSpawnIndex][1];
	//float z = RANDOM_SPAWNS[randomSpawnIndex][2];
	Point3D randomSpawnPoint = Point3D{ 26.1551f, 922.8038f, 23.6378f };
	PlayerManager::GetPlayer(playerid)->SetPosition(randomSpawnPoint);

	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char *cmdtext) {
	return commandManager->OnPlayerCommandText(PlayerManager::GetPlayer(playerid), string(cmdtext));
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newKeys, int oldKeys) {
	Player *player = PlayerManager::GetPlayer(playerid);

	//if (KEY_PRESSSED_ONCE(KEY_SPRINT, newKeys, oldKeys))
	//{
	//	if (player->IsLoopingAnimation())
	//	{
	//		player->StopAnimations();
	//	}
	//}

	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterRaceCheckpoint(int playerid) {
	Player *player = PlayerManager::GetPlayer(playerid);
	CoalmineManager::OnPlayerEnterRaceCheckpoint(player);
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int playerid, const char *text) {
	Player *player = PlayerManager::GetPlayer(playerid);
	string message = player->GetName() + " says: " + string(text);

	int vehicleID = player->GetVehicleID();
	bool windowsOpen = VehicleManager::IsWindowOpen(vehicleID);
	// TODO: Phones

	// Gagged
	if (player->IsGagged())
	{
		message = player->GetName() + " mumbles: " + RANDOM_ARRAY_ELEMENT(GAGGED_MESSAGES);
	}
	 
	if (vehicleID != 0)
	{
		if (windowsOpen)
		{
			ChatManager::LocalMessage(player, message);
		}
		else
		{
			ChatManager::VehicleMessage(player, message);
		} 
	}
	else
	{
		ChatManager::LocalMessage(player, message);
	} 

	// TODO: Bugs (the listening kind)

	return false;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
	return sampgdk::Supports() | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
	return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
	sampgdk::Unload();
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
	sampgdk::ProcessTick();
}
