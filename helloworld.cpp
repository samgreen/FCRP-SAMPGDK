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

using namespace std;

static CommandManager *commandManager = new CommandManager;
static PlayerManager *playerManager;
static VehicleManager *vehicleManager;

void SAMPGDK_CALL PrintTickCountTimer(int timerid, void *params) {
	//sampgdk::logprintf("Tick count: %d", GetTickCount());
}
 
PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
	sampgdk::logprintf("----------------------------------");
	sampgdk::logprintf(" Fort Carson: Roleplay");
	sampgdk::logprintf("----------------------------------");

	// Create the initial vehicles 
	VehicleManager::CreateStartingVehicles();

	UsePlayerPedAnims();
	AllowAdminTeleport(true);
	AllowInteriorWeapons(true);
	SetNameTagDrawDistance(10);
	EnableStuntBonusForAll(false);
	DisableInteriorEnterExits();
	ShowPlayerMarkers(1);

	SetGameModeText("BC-RP v0.1 ALPHA");
	AddPlayerClass(0, 1958.3783f, 1343.1572f, 15.3746f, 269.1425f, 0, 0, 0, 0, 0, 0);
	SetTimer(1000, true, PrintTickCountTimer, 0);

	return true;
}
 
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
	PlayerManager::AddPlayer(new Player(playerid));

	//if (!player.HasValidName()) 
	//{
	//	SendClientMessage(player.GetID(), COLOR_RED, "This is a roleplaying server. We require names in the FirstName_LastName format.");
	//	Kick(player.GetID());
	//	playerList.pop_back(); // Remove the player from our list
	//	return false; // Don't let any other code handle this callback
	//}

	SetPlayerInterior(playerid, 0);
	SetPlayerPos(playerid, 163.984863f, 1213.388305f, 21.501449f);
	SetPlayerFacingAngle(playerid, 221.263046f);
	SetPlayerCameraPos(playerid, 165.959655f, 1203.647216f, 19.609039f);
	SetPlayerCameraLookAt(playerid, 169.6875f, 1217.8063f, 22.1361f, 0);
	ApplyAnimation(playerid, "SMOKING", "M_smklean_loop", 4.0, true, false, false, false, 0, false); // Smoke

	return false;
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

	sampgdk_logprintf("OnPlayerSpawn with id: %d", playerid);
	
	//int randomSpawnIndex = rand() % sizeof(RANDOM_SPAWNS);
	//float x = RANDOM_SPAWNS[randomSpawnIndex][0];
	//float y = RANDOM_SPAWNS[randomSpawnIndex][1];
	//float z = RANDOM_SPAWNS[randomSpawnIndex][2];
	Point3D randomSpawnPoint = Point3D{ 26.1551, 922.8038, 23.6378 };
	PlayerManager::GetPlayer(playerid)->SetPosition(randomSpawnPoint);

	return false;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char *cmdtext) {
	return commandManager->OnPlayerCommandText(playerid, cmdtext);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int playerid, const char *text) {
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
