#include <string>
#include <string.h>
#include <vector>
#include <sstream>

#include "sampgdk.h"

#include "Constants.h"
#include "CommandManager.h"
#include "ChatManager.h"
#include "PlayerManager.h"
#include "VehicleManager.h"
#include "FactionManager.h"
#include "JobManager.h"
#include "Player.h"

using namespace std;

typedef struct {
	bool success;
	string errorMessage;
} CommandResult;

static inline CommandResult CommandResultMake(bool success, string error)
{
	return CommandResult{ success, error };
}

static inline vector<string> split(string s)
{
	vector<string> tokens;
	if (s.size() == 0) return tokens;

	stringstream stringStream(s);
	std::copy(istream_iterator<string>(stringStream), istream_iterator<string>(), back_inserter(tokens));

	return tokens;
}

CommandManager::CommandManager() {}
CommandManager::~CommandManager() {}

bool CommandEmote(Player *player, string params)
{
	if (params.size() == 0) 
	{
		ChatManager::SystemMessage(player, "Usage: \"/me [emote]\"");
	}
	else
	{
		string emoteMessage = player->GetName() + params;
		ChatManager::EmoteMessage(player, emoteMessage);
	}

	return true; 
}

bool CommandDo(Player *player, string params)
{
	if (params.size() == 0)
	{
		ChatManager::SystemMessage(player, "Usage: \"/do [action]\"");
	}
	else
	{
		string message = params + " (" + player->GetName() + ")";
		ChatManager::EmoteMessage(player, message);
	}

	return true;
}

bool CommandLocalOOC(Player *player, string params)
{
	if (params.size() == 0)
	{
		ChatManager::SystemMessage(player, "Usage: \"/b [text] (local OOC)\"");
	}
	else
	{
		string message = player->GetName() + ": ((" + params + " ))";
		ChatManager::LocalMessage(player, message);
	}

	return true;
}

bool CommandOOC(Player *player, string params)
{
	if (params.size() == 0)
	{
		ChatManager::SystemMessage(player, "Usage: \"/o [text] (global OOC)\"");
	}
	else
	{
		string message = "(( " + player->GetName() + ":" + params + " ))";
		// TODO: Add Logging
		for (auto i = PlayerManager::BeginPlayer(); i != PlayerManager::EndPlayer(); i++)
		{
			Player *p = i->second;
			SendClientMessage(p->GetID(), COLOR_OOC, message.c_str());
		}
	}

	return true;
}

bool CommandGiveGun(Player *player, string params)
{
	vector<string> paramTokens = split(params);
	if (paramTokens.size() == 2 && params.size() > 0)
	{
		string playerIDString = paramTokens.at(0);
		string weaponIDString = paramTokens.at(1);

		int playerID = stoi(playerIDString);
		int weaponID = stoi(weaponIDString);

		GivePlayerWeapon(playerID, weaponID, MAX_AMMO);
	}
	else 
	{
		ChatManager::SystemMessage(player->GetID(), "Usage: \"/givegun [PlayerID] [WeaponID]\"");
		ChatManager::SystemMessage(player->GetID(), "IDs: 1 knuckles |2 club |3 baton |4 knife |5 bat |6 shovel |7 cue |8 sword |9 chainsaw |10 13 dildos |14 flowers |15 cane");
		ChatManager::SystemMessage(player->GetID(), "		16 grenade |17 smoke |18 molotov |22 pistol |23 sdpistol |24 deagle |25 shotgun |26 sawnoff |27 spas |28 uzi |29 mp5");
		ChatManager::SystemMessage(player->GetID(), "		30 AK |31 M4 |32 tec9 |33 rifle |34 sniper |35 rpg |36 rpg |37 flamethrower |38 minigun |41 paint |42 extinguisher");
		ChatManager::SystemMessage(player->GetID(), "		43 camera |44/45 goggles |46 para");
	}
	
	return true;
}

bool CommandKill(Player *player, string params)
{
	if (!player->IsHandCuffed() && !player->IsTied()) {
		player->Kill();

		string message = params;
		if (params.size() == 0) {
			message = player->GetName() + string(" ") + string(RANDOM_ARRAY_ELEMENT(DEATH_MESSAGES));
		}
		ChatManager::EmoteMessage(player, message);
	}
	else 
	{
		player->SubtractRespect(5);
		ChatManager::SystemMessage(player, "Hey now, play nice. You've been docked five respect for not playing fair.");
	} 

	return true;
}

bool CommandDance(Player *player, string params)
{
	if (player->IsHandCuffed()) 
	{
		ChatManager::SystemMessage(player, "You cannot do that while cuffed.");
	}
	else 
	{
		int danceID = -1;
		if (params.size())
		{
			danceID = stoi(params);
		}

		switch (danceID)
		{
		case 1: SetPlayerSpecialAction(player->GetID(), SPECIAL_ACTION_DANCE1); break;
		case 2: SetPlayerSpecialAction(player->GetID(), SPECIAL_ACTION_DANCE2); break;
		case 3: SetPlayerSpecialAction(player->GetID(), SPECIAL_ACTION_DANCE3); break;
		case 4: SetPlayerSpecialAction(player->GetID(), SPECIAL_ACTION_DANCE4); break;
		default: SendClientMessage(player->GetID(), 0xEFEFF7AA, "USAGE: /dance [1-4]"); break;
		}
	}
	return true;
}

bool CommandVeh(Player *player, string params)
{
	if (player->IsInVehicle())
	{
		ChatManager::SystemMessage(player, "Get out of your current vehicle first!");
	}
	else if (player->GetAdminLevel() < 5)
	{
		ChatManager::SystemMessage(player, "You are not authorized to use this command.");
	}
	else
	{
		//new car = ReturnVehicleModelID(tmp);
		//if (!car)
		//	return SystemMsg(playerid, "   Invalid vehicle model name/ID");
		//else
		//{
		vector<string> paramTokens = split(params);
		if (paramTokens.size() == 3 && params.size() > 0)
		{
			string carIDString = paramTokens.at(0);
			string color1String = paramTokens.at(1);
			string color2String = paramTokens.at(2);

			int carID = stoi(carIDString);
			int color1 = stoi(color1String);
			int color2 = stoi(color2String);

			Point3D position = player->GetPosition();
			float angle = player->GetFacingAngle();
			int vehicleID = CreateVehicle(carID, position.x, position.y, position.z, angle, color1, color2, 600000);
			int interiorID = player->GetInterior();
			LinkVehicleToInterior(vehicleID, interiorID);

			//CreatedCars[CreatedCar] = carid;
			//CreatedCar++;
			PutPlayerInVehicle(player->GetID(), vehicleID, 0);
			//new carname[56], string[256];
			//carname = GetVehicleName(carid);
			//format(string, sizeof(string), "[AdmCmd] %s(ID: %d) spawned by %s.", VehicleName[GetVehicleModel(carid) - 400], carid, Name(playerid));
			//AdminBroadcast(COLOR_YELLOW, string);
		}
		else
		{
			ChatManager::SystemMessage(player, "Usage: \"/veh [Car ID] [Color 1] [Color 2]\"");
		}
	}
	return true;
}

bool CommandCropdust(Player *player, string params)
{
	if (player->GetCropDusterCooldown() > 0)
	{
		char message[MAX_CLIENT_MESSAGE];
		sprintf(message, "You still have %.0f minutes left before you can crop dust again.", player->GetCropDusterCooldown()); // TODO: add cropdust time to the player object
		ChatManager::SystemMessage(player->GetID(), message);
	}
	else if (!player->IsInVehicle() || !VehicleManager::IsCropduster(player->GetVehicleModelID()))
	{
		ChatManager::SystemMessage(player, "You're not in a cropduster! They're at the farm, stupid.");
	}
	else
	{
		SendClientMessage(player->GetID(), COLOR_WHITE, "These crops need dustin'! Fly through the checkpoints and land.");
		GameTextForPlayer(player->GetID(), "~y~Crop duster~n~~w~fly through the checkpoints to dust the ~g~crops", 5000, 3);
		SetPlayerRaceCheckpoint(player->GetID(), 0, -100.3056f, 55.1138f, 3.3968f, -111.7368f, 24.8819f, 4.5995f, 7.f);
		////CropDusterCheckpoint[playerid] = 1;

		static float CROP_DUSTER_COOLDOWN[] = {
			34.f,
			32.f,
			30.f,
			28.f,
			25.f
		};

		int cropDusterLevel = player->GetCropDusterLevel();
		player->SetCropDusterCooldown(CROP_DUSTER_COOLDOWN[cropDusterLevel]);
	}

	return true;
}

bool CommandSetHealth(Player *player, vector<string> params)
{
	if (params.size() != 2)
	{
		ChatManager::SystemMessage(player, "Usage: \"/sethp [Part of name or PlayerID] [HP]\"");
	}
	else
	{
		int otherPlayerID = stoi(params.at(0));
		int health = stoi(params.at(1));

		Player *otherPlayer = PlayerManager::GetPlayer(otherPlayerID);
		if (otherPlayer != NULL)
		{
			otherPlayer->SetHealth(health);
		}
		else
		{
			ChatManager::SystemMessage(player, "Invalid playerID");
		}

		//ChatManager::AdminMessage();
	}

	return true;
}

bool CommandSetArmor(Player *player, vector<string> params)
{
	if (params.size() != 2)
	{
		ChatManager::SystemMessage(player, "Usage: \"/setarmor [Part of name or PlayerID] [Armor]\"");
	} 
	else
	{
		int otherPlayerID = stoi(params.at(0));
		int armor = stoi(params.at(1));

		Player *otherPlayer = PlayerManager::GetPlayer(otherPlayerID);
		if (otherPlayer != NULL)
		{
			otherPlayer->SetArmor(armor);
		}
		else
		{
			ChatManager::SystemMessage(player, "Invalid playerID");
		}
	}

	return true;
}

bool CommandSetSkin(Player *player, vector<string> params)
{
	if (params.size() != 2)
	{
		ChatManager::SystemMessage(player, "Usage: \"/setskin [Part of name or PlayerID] [SkinID]\"");
	}
	else
	{
		int otherPlayerID = stoi(params.at(0));
		int skinID = stoi(params.at(1));

		Player *otherPlayer = PlayerManager::GetPlayer(otherPlayerID);
		if (otherPlayer != NULL)
		{
			otherPlayer->SetSkin(skinID);
		}
		else
		{
			ChatManager::SystemMessage(player, "Invalid playerID");
		}
	}

	return true;
}

bool CommandFactionList(Player *player, vector<string> params)
{
	for (int i = 0; i < PlayerFactionNumberOfFactions; i++)
	{
		PlayerFaction faction = (PlayerFaction)i;
		// Do not show our super secret faction, or civilian as a faction
		if (faction == PlayerFactionTen || faction == PlayerFactionCivilian) continue;

		PlayerFactionType factionType = FactionManager::GetType(faction);

		string message;
		switch (factionType)
		{
		case PlayerFactionTypeCorporation:
		{
			message = "Corporation";
			break;
		}
		case PlayerFactionTypeFaction:
		{
			message = "Faction";
			break;
		}
		case PlayerFactionTypeFamily:
		{
			message = "Family";
			break;
		}
		default: break;
		}

		string factionName = FactionManager::GetName(faction);
		message = message + " " + to_string(i) + ": " + factionName; 
		ChatManager::WhiteMessage(player, message);
	}

	return true;
}

bool CommandFactionListMembers(Player *player, vector<string> params)
{
	PlayerFaction playerFaction = FactionManager::GetFaction(player);
	if (playerFaction == PlayerFactionCivilian)
	{
		ChatManager::SystemMessage(player, "This command is only available to families and corporations. Go to the library to learn more.");
	}
	else
	{
		// Iterate over all the players
		for (auto i = PlayerManager::BeginPlayer(); i != PlayerManager::EndPlayer(); i++)
		{
			Player *otherPlayer = i->second;
			// If the other player is in the same faction as the player sending the command
			if (playerFaction == FactionManager::GetFaction(otherPlayer))
			{
				ChatManager::WhiteMessage(player, "Rank " + to_string(FactionManager::GetRank(otherPlayer)) + " | " + otherPlayer->GetName());
			}
		}
	}

	return true;
}

bool CommandFactionGiveRank(Player *player, vector<string> params)
{
	return true;
}

bool CommandFactionInvite(Player *player, vector<string> params)
{
	PlayerFaction playerFaction = FactionManager::GetFaction(player);
	int playerFactionRank = FactionManager::GetRank(player);
	if (playerFaction == PlayerFactionCivilian)
	{
		ChatManager::SystemMessage(player, "You're not in a faction.");
	}
	else if (playerFactionRank < 6)
	{
		ChatManager::SystemMessage(player, "You must be rank 6 to invite other players.");
	}
	else if (params.size() != 1)
	{
		ChatManager::SystemMessage(player, "Usage: \"/invite [Part of name or PlayerID]\"");
	}
	else
	{
		int otherPlayerID = stoi(params.at(0));
		Player *otherPlayer = PlayerManager::GetPlayer(otherPlayerID);
		PlayerFaction otherPlayerFaction = FactionManager::GetFaction(otherPlayer);
		if (otherPlayerFaction != PlayerFactionCivilian)
		{
			ChatManager::SystemMessage(player, "That player is in another faction.");
		}
		else
		{
			// Set the other player's faction to the current player's faction
			FactionManager::AddPlayer(otherPlayer, FactionManager::GetFaction(player));

			// Send faction messages to the invitee and inviter
			ChatManager::FactionMessage(otherPlayer, player->GetName() + " invited you to join their faction.");
			ChatManager::FactionMessage(player, "You invited " + otherPlayer->GetName() + " join your faction.");
		}
	}
	return true;
}

bool CommandFactionUnInvite(Player *player, vector<string> params)
{
	return true;
}

bool CommandFactionDeposit(Player *player, vector<string> params)
{
	return true;
}

bool CommandFactionWithdraw(Player *player, vector<string> params)
{
	return true;
}

bool CommandFactionShowBalance(Player *player, vector<string> params)
{
	return true;
}

bool CommandToggleVehicleWindows(Player *player, vector<string> params)
{
	int vehicleID = player->GetVehicleID();
	if (vehicleID == 0)
	{
		ChatManager::SystemMessage(player, "You must be in a vehicle to roll the windows up or down.");
	}
	else if (VehicleManager::IsBike(vehicleID) || VehicleManager::IsBoat(vehicleID))
	{
		ChatManager::SystemMessage(player, "There are no windows on this vehicle.");
	}
	else
	{
		bool windowsOpen = VehicleManager::IsWindowOpen(vehicleID);
		if (windowsOpen)
		{
			ChatManager::EmoteMessage(player, player->GetName() + " rolls the windows up.");
		}
		else
		{
			ChatManager::EmoteMessage(player, player->GetName() + " rolls the windows down.");
		}

		// Toggle the window state
		VehicleManager::SetWindowState(vehicleID, !windowsOpen);
	}

	return true;
}

bool CommandShowVehicleWindowState(Player *player, vector<string> params)
{
	int vehicleID = player->GetVehicleID();
	if (vehicleID == 0)
	{
		ChatManager::SystemMessage(player, "You must be in a vehicle to check the state of the windows.");
	}
	else if (VehicleManager::IsBike(vehicleID) || VehicleManager::IsBoat(vehicleID))
	{
		ChatManager::SystemMessage(player, "There are no windows on this vehicle.");
	}
	else
	{
		bool windowOpen = VehicleManager::IsWindowOpen(vehicleID);
		string message = (windowOpen ? "Windows are down." : "Windows are up.");
		ChatManager::SystemMessage(player, message);
	}

	return true;
}

static bool eventInProgress = false;
static Point3D eventPosition;

bool CommandStartEvent(Player *player, vector<string> params)
{
	if (player->GetAdminLevel() >= 5)
	{
		eventInProgress = true;
		eventPosition = player->GetPosition();

		SendClientMessage(player->GetID(), COLOR_LIGHTBLUE, "Event position saved. Don't for get to use /endevent to stop teleportations.");
		SendClientMessageToAll(COLOR_LIGHTBLUE, "** An admin has started an event. Use /joinevent to check it out!");
	}
	else
	{
		ChatManager::SystemMessage(player, "You are not authorized to use this command.");
	}

	return true;
}

bool CommandEndEvent(Player *player, vector<string> params)
{
	if (player->GetAdminLevel() < 5)
	{
		ChatManager::SystemMessage(player, "You are not authorized to use this command,");
	}
	else if (!eventInProgress)
	{
		ChatManager::SystemMessage(player, "There is no event currently in progress.");
	}
	else
	{
		eventInProgress = false;

		SendClientMessageToAll(COLOR_LIGHTBLUE, "** An admin has closed the event.");
	}

	return true;
}

bool CommandJoinEvent(Player *player, vector<string> params)
{
	if (!eventInProgress)
	{
		ChatManager::SystemMessage(player, "There is no event currently in progress.");
	}
	else if (player->IsInVehicle())
	{
		ChatManager::SystemMessage(player, "Please exit your vehicle to join the event.");
	}
	else
	{
		player->SetPosition(eventPosition);
	}

	return true;
}

bool CommandGetJob(Player *player, vector<string> params)
{
	if (JobManager::GetType(player) != JobTypeNone)
	{
		ChatManager::SystemMessage(player, "You already have a job. Use /quitjob first.");
	}
	else if (JobManager::GetContractTime(player) > 0)
	{
		ChatManager::SystemMessage(player, "You have " + to_string(JobManager::GetContractTime(player)) + " minutes left in your contract!");
	}
	else
	{
		if (player->GetDistanceFromPoint(JobManager::GetPoint(JobTypeDrugDealer)) < 4.f)
		{
			JobManager::SetType(player, JobTypeDrugDealer);
			ChatManager::WhiteMessage(player, "You're now a drug dealin' chemist! Learn how to make your favorite poisons at your local library!");
		}
		else if (player->GetDistanceFromPoint(JobManager::GetPoint(JobTypeArmsDealer)) < 4.f)
		{
			JobManager::SetType(player, JobTypeArmsDealer);
			ChatManager::WhiteMessage(player, "You're now an arms dealer! Learn more about what you can do with /help and the library!");
		}
		else if (player->GetDistanceFromPoint(JobManager::GetPoint(JobTypeWheelman)) < 4.f)
		{
			JobManager::SetType(player, JobTypeWheelman);
			ChatManager::WhiteMessage(player, "You're now a wheelman! Learn more about what you can do with /help and the library!");
		}
		else if (player->GetDistanceFromPoint(JobManager::GetPoint(JobTypeMercenary)) < 4.f)
		{
			JobManager::SetType(player, JobTypeMercenary);
			ChatManager::WhiteMessage(player, "You're now a mercenary! Learn more about what you can do with /help and the library!");
		}
	}
	return true;
}

bool CommandQuitJob(Player *player, vector<string> params)
{
	if (JobManager::GetContractTime(player) > 0)
	{
		ChatManager::SystemMessage(player, "You have " + to_string(JobManager::GetContractTime(player)) + " minutes left in your contract!");
	}
	else
	{
		string message;
		switch (JobManager::GetType(player))
		{
		case JobTypeNone: message = "You are currently unemployed."; break;
		case JobTypeWheelman: message = "You quit being a wheelman. Have fun being slow!"; break;
		case JobTypeArmsDealer: message = "You quit being an arms dealer, what will your friends think?"; break;
		case JobTypeDrugDealer: message = "You quit being a drug dealer, mad scientist guy!"; break;
		case JobTypeMercenary: message = "You quit being a mercenary. Have fun controlling your anger!"; break;
		}
		ChatManager::SystemMessage(player, message);

		JobManager::SetType(player, JobTypeNone);
	}
	return true;
}

bool CommandManager::OnPlayerCommandText(Player *player, string commandText)
{

	vector<string> params = split(commandText);
	// Does the command have additional parameters?
	if (params.size() > 1) {
		// Erase the first element, which is the command itself
		params.erase(params.begin());
	}

	// TODO: Add spam time

	if (commandText.find("/kill") == 0)
	{
		return CommandKill(player, commandText.substr(5, string::npos));
	}
	else if (commandText.find("/dance") == 0)
	{
		return CommandDance(player, commandText.substr(6, string::npos));
	}
	else if (commandText.find("/rw") == 0)
	{
		return CommandToggleVehicleWindows(player, params);
	}
	else if (commandText.find("/windows") == 0)
	{
		return CommandShowVehicleWindowState(player, params);
	}
	else if (commandText.find("/cropdust") == 0)
	{
		return CommandCropdust(player, commandText.substr(9, string::npos));
	}
	else if (commandText.find("/givegun") == 0)
	{
		return CommandGiveGun(player, commandText.substr(8, string::npos));
	}
	else if (commandText.find("/sethp") == 0)
	{
		return CommandSetHealth(player, params);
	}
	else if (commandText.find("/setarmor") == 0)
	{
		return CommandSetArmor(player, params);
	}
	else if (commandText.find("/setskin") == 0)
	{
		return CommandSetSkin(player, params);
	}
	else if (commandText.find("/factions") == 0 || commandText.find("/families") == 0)
	{
		return CommandFactionList(player, params);
	}
	else if (commandText.find("/invite") == 0)
	{
		return CommandFactionInvite(player, params);
	}
	else if (commandText.find("/uninvite") == 0)
	{
		return CommandFactionUnInvite(player, params);
	}
	else if (commandText.find("/fdeposit") == 0)
	{
		return CommandFactionDeposit(player, params);
	}
	else if (commandText.find("/fwithdraw") == 0)
	{
		return CommandFactionWithdraw(player, params);
	}
	else if (commandText.find("/fbalance") == 0)
	{
		return CommandFactionShowBalance(player, params);
	}
	else if (commandText.find("/members") == 0)
	{
		return CommandFactionListMembers(player, params);
	}
	else if (commandText.find("/startevent") == 0)
	{
		return CommandStartEvent(player, params);
	}
	else if (commandText.find("/endevent") == 0)
	{
		return CommandEndEvent(player, params);
	}
	else if (commandText.find("/joinevent") == 0)
	{
		return CommandJoinEvent(player, params);
	}
	else if (commandText.find("/v") == 0)
	{
		return CommandVeh(player, commandText.substr(2, string::npos));
	}
	else if (commandText.find("/o") == 0)
	{
		return CommandOOC(player, commandText.substr(2, string::npos));
	}
	else if (commandText.find("/b") == 0)
	{
		return CommandLocalOOC(player, commandText.substr(2, string::npos));
	}
	else if (commandText.find("/me") == 0)
	{
		return CommandEmote(player, commandText.substr(3, string::npos));
	}
	else if (commandText.find("/do") == 0)
	{
		return CommandDo(player, commandText.substr(3, string::npos));
	} 
	else if (commandText.find("/getjob") == 0)
	{
		return CommandDo(player, commandText.substr(3, string::npos));
	}
	else if (commandText.find("/quitjob") == 0)
	{
		return CommandDo(player, commandText.substr(3, string::npos));
	}

	return false;
}

bool CommandManager::OnPlayerCommandText(int playerID, const char *commandText)
{
	return CommandManager::OnPlayerCommandText(PlayerManager::GetPlayer(playerID), string(commandText));
}