#include "CommandManager.h"
#include "sampgdk.h"
#include "CommandUtil.h"

using namespace std;

static string ToLowerCase(string input);
static string ToLowerCase(string input)
{
	string output;
	// Transform commandInput to lowercase in command
	transform(input.cbegin(), input.cend(), back_inserter(output), tolower);
	return output;
}

bool CommandEmote(Player *player, string text, vector<string> params);
bool CommandEmote(Player *player, string text, vector<string> params)
{
	if (params.empty()) 
	{
		ChatManager::SystemMessage(player, "Usage: \"/me [emote]\"");
	}
	else
	{
		string emoteMessage = player->GetName() + " " + text;
		ChatManager::EmoteMessage(player, emoteMessage);
	}

	return true; 
}

bool CommandShout(Player *player, string text, vector<string> params);
bool CommandShout(Player *player, string text, vector<string> params)
{
	if (params.empty())
	{
		ChatManager::SystemMessage(player, "Usage: \"/shout [text]\"");
	}
	else
	{
		if (player->IsGagged())
		{
			ChatManager::GaggedMessage(player);
		}
		else
		{
			string shoutMessage = player->GetName() + " shouts: " + text;
			ChatManager::ShoutMessage(player, shoutMessage);
		}
	}

	return true;
}


bool CommandDo(Player *player, string text, vector<string> params);
bool CommandDo(Player *player, string text, vector<string> params)
{
	if (params.empty())
	{
		ChatManager::SystemMessage(player, "Usage: \"/do [action]\"");
	}
	else
	{
		string message = text + " (" + player->GetName() + ")";
		ChatManager::EmoteMessage(player, message);
	}

	return true;
}

bool CommandLocalOOC(Player *player, string text, vector<string> params);
bool CommandLocalOOC(Player *player, string text, vector<string> params)
{
	if (params.empty())
	{
		ChatManager::SystemMessage(player, "Usage: \"/b [text] (local OOC)\"");
	}
	else
	{
		string message = player->GetName() + ": (( " + text + " ))";
		ChatManager::LocalMessage(player, message);
	}

	return true;
}

bool CommandOOC(Player *player, string text, vector<string> params);
bool CommandOOC(Player *player, string text, vector<string> params)
{
	if (params.empty())
	{
		ChatManager::SystemMessage(player, "Usage: \"/o [text] (global OOC)\"");
	}
	else
	{
		string message = "(( " + player->GetName() + ": " + text + " ))";
		// TODO: Add Logging
		for (auto i = PlayerManager::BeginPlayer(); i != PlayerManager::EndPlayer(); i++)
		{
			Player *p = i->second;
			// TODO: Check if player has OOC enabled
			SendClientMessage(p->GetID(), COLOR_OOC, message.c_str());
		}
	}

	return true;
}

bool CommandGiveGun(Player *player, string text, vector<string> params);
bool CommandGiveGun(Player *player, string text, vector<string> params)
{
	if (params.size() == 2)
	{
		Player *otherPlayer = CommandManager::GetPlayerFromParams(player, params, 0);
		if (otherPlayer)
		{
			string weaponIDString = params[1];
			int weaponID = stoi(weaponIDString);

			otherPlayer->GiveWeapon(weaponID);
		}
	}
	else 
	{
		ChatManager::SystemMessage(player, "Usage: \"/givegun [PlayerID] [WeaponID]\"");
		ChatManager::SystemMessage(player, "IDs: 1 knuckles |2 club |3 baton |4 knife |5 bat |6 shovel |7 cue |8 sword |9 chainsaw |10 13 dildos |14 flowers |15 cane");
		ChatManager::SystemMessage(player, "		16 grenade |17 smoke |18 molotov |22 pistol |23 sdpistol |24 deagle |25 shotgun |26 sawnoff |27 spas |28 uzi |29 mp5");
		ChatManager::SystemMessage(player, "		30 AK |31 M4 |32 tec9 |33 rifle |34 sniper |35 rpg |36 rpg |37 flamethrower |38 minigun |41 paint |42 extinguisher");
		ChatManager::SystemMessage(player, "		43 camera |44/45 goggles |46 para");
	}
	
	return true;
}

bool CommandKill(Player *player, string text, vector<string> params);
bool CommandKill(Player *player, string text, vector<string> params)
{
	if (!player->IsHandCuffed() && !player->IsTied()) {
		player->Kill();

		string message = text;
		if (text.empty()) {
			message = player->GetName() + " " + RANDOM_ARRAY_ELEMENT(DEATH_MESSAGES); // TODO: Re-add random kill messagse
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

bool CommandDance(Player *player, string text, vector<string> params);
bool CommandDance(Player *player, string text, vector<string> params)
{
	if (player->IsHandCuffed()) 
	{
		ChatManager::SystemMessage(player, "You cannot do that while cuffed.");
	}
	else 
	{
		int danceID = -1;
		if (params.size() == 1)
		{
			danceID = stoi(params[0]);
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

bool CommandVeh(Player *player, string text, vector<string> params);
bool CommandVeh(Player *player, string text, vector<string> params)
{
	if (player->IsInVehicle())
	{
		ChatManager::SystemMessage(player, "Get out of your current vehicle first!");
	}
	else
	{
		//new car = ReturnVehicleModelID(tmp);
		//if (!car)
		//	return SystemMsg(playerid, "   Invalid vehicle model name/ID");
		//else
		//{
		if (params.size() == 3 && IsNumeric(params[0]) && IsNumeric(params[1]) && IsNumeric(params[2]))
		{
			string carIDString = params[0];
			string color1String = params[1];
			string color2String = params[2];

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

bool CommandRequestBackup(Player *player, string text, vector<string> params);
bool CommandRequestBackup(Player *player, string text, vector<string> params)
{
	PlayerFaction faction = FactionManager::GetFaction(player);
	if (faction == PlayerFactionPolice)
	{
		string message = "Dispatch: Attention all units! " + player->GetName() + " is requesting immediate backup at their location.";
		for (auto iter = PlayerManager::BeginPlayer(); iter != PlayerManager::EndPlayer(); iter++)
		{
			Player *otherPlayer = iter->second;
			if (FactionManager::IsInSameFaction(player, otherPlayer))
			{
				SendClientMessage(otherPlayer->GetID(), COLOR_POLICE, message.c_str());
				SetPlayerMarkerForPlayer(otherPlayer->GetID(), player->GetID(), COLOR_POLICE);
			}
		}
	}
	else
	{
		ChatManager::SystemMessage(player, "This command is only available to police officers.");
	}

	return true;
}

bool CommandCancelRequestBackup(Player *player, string text, vector<string> params);
bool CommandCancelRequestBackup(Player *player, string text, vector<string> params)
{
	PlayerFaction faction = FactionManager::GetFaction(player);
	if (faction == PlayerFactionPolice)
	{
		string message = "Dispatch: Attention all units! " + player->GetName() + " is reporting a 10-22. Disregard the last assignment.";
		for (auto iter = PlayerManager::BeginPlayer(); iter != PlayerManager::EndPlayer(); iter++)
		{
			Player *otherPlayer = iter->second;
			if (FactionManager::IsInSameFaction(player, otherPlayer))
			{
				SendClientMessage(otherPlayer->GetID(), COLOR_POLICE, message.c_str());
				SetPlayerMarkerForPlayer(otherPlayer->GetID(), player->GetID(), COLOR_TRANSPARENT);
			}
		}
	}
	else
	{
		ChatManager::SystemMessage(player, "This command is only available to police officers.");
	}

	return true;
}

bool CommandCoalmine(Player *player, string text, vector<string> params);
bool CommandCoalmine(Player *player, string text, vector<string> params)
{
	CoalmineManager::Start(player);
	return true;
}

bool CommandCropdust(Player *player, string text, vector<string> params);
bool CommandCropdust(Player *player, string text, vector<string> params)
{
	if (player->GetCropDusterCooldown() > 0)
	{
		char message[MAX_CLIENT_MESSAGE];
		sprintf(message, "You still have %.0f minutes left before you can crop dust again.", player->GetCropDusterCooldown()); // TODO: add cropdust time to the player object
		ChatManager::SystemMessage(player, message);
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

bool CommandSetHealth(Player *player, string text, vector<string> params);
bool CommandSetHealth(Player *player, string text, vector<string> params)
{
	if (params.size() != 2)
	{
		ChatManager::SystemMessage(player, "Usage: \"/sethp [Part of name or PlayerID] [HP]\"");
	}
	else
	{
		Player *otherPlayer = CommandManager::GetPlayerFromParams(player, params, 0);
		if (otherPlayer)
		{
			int health = stoi(params.at(1));
			otherPlayer->SetHealth(health);
		}
		//ChatManager::AdminMessage();
	}

	return true;
}

bool CommandSetArmor(Player *player, string text, vector<string> params);
bool CommandSetArmor(Player *player, string text, vector<string> params)
{
	if (params.size() != 2)
	{
		ChatManager::SystemMessage(player, "Usage: \"/setarmor [Part of name or PlayerID] [Armor]\"");
	} 
	else
	{
		Player *otherPlayer = CommandManager::GetPlayerFromParams(player, params, 0);
		if (otherPlayer)
		{
			int armor = stoi(params[1]);
			otherPlayer->SetArmor(armor);
		}
	}

	return true;
}

bool CommandSetSkin(Player *player, string text, vector<string> params);
bool CommandSetSkin(Player *player, string text, vector<string> params)
{
	if (params.size() != 2)
	{
		ChatManager::SystemMessage(player, "Usage: \"/setskin [Part of name or PlayerID] [SkinID]\"");
	}
	else
	{
		Player *otherPlayer = CommandManager::GetPlayerFromParams(player, params, 0);
		if (otherPlayer)
		{
			int skinID = stoi(params[1]);
			otherPlayer->SetSkin(skinID);
		}
	}

	return true;
}

bool CommandGoto(Player *player, string text, vector<string> params);
bool CommandGoto(Player *player, string text, vector<string> params)
{
	if (params.size() != 1)
	{
		ChatManager::SystemMessage(player, "Usage: \"/goto [Part of name or PlayerID]\"");
		ChatManager::SystemMessage(player, "places: taxi corp1 corp2 pd lsair sfair lvair pier underwater boat mafjump skyscraper coalminer");
		ChatManager::SystemMessage(player, "chiliad drift wheelarch locolow transfender halfpipe bridgetop lombardstreet skatepark casino skydive");
		ChatManager::SystemMessage(player, "smokespot fc lb eq boneyard process cropdust trucker hotel1 hotel2 hotel3");
	}
	else
	{
		Player *otherPlayer = CommandManager::GetPlayerFromParams(player, params, 0);
		if (otherPlayer)
		{
			Point3D position = otherPlayer->GetPosition();
			position.x += 1; // Offset their position slightly

			player->SetPosition(position);
			player->SetInterior(otherPlayer->GetInterior());
			player->SetVirtualWorld(otherPlayer->GetVirtualWorld());
		}
		else if (!params.empty())
		{
			// Default to interior 0
			player->SetInterior(0);

			if (params[0].find("taxi") != string::npos) // /goto taxi
			{
				player->SetPosition(Point3DMake(-300.9337, 1322.2476, 54.2912));
			}
			else if (params[0].find("corp1") != string::npos) // /goto corp1
			{
				player->SetPosition(Point3DMake(641.5588, 1194.2560, 11.7188));
			}
			else if (params[0].find("corp2") != string::npos) // /goto corp2
			{
				player->SetPosition(Point3DMake(-702.7709, 954.3311, 12.3812));
			}
			else if (params[0].find("pd") != string::npos) // /goto pd
			{
				player->SetPosition(Point3DMake(213.9422, 1903.9194, 17.6406));
			}
			else if (params[0].find("lsair") != string::npos) // /goto lsair
			{
				player->SetPosition(Point3DMake(2006.3446, -2532.9819, 13.5469));
			}
			else if (params[0].find("sfair") != string::npos) // /goto sfair
			{
				player->SetPosition(Point3DMake(-1109.7617, 374.7649, 14.1484));
			}
			else if (params[0].find("lvair") != string::npos) // /goto lvair
			{
				player->SetPosition(Point3DMake(1435.2316, 1464.0927, 10.8203));
			}
			else if (params[0].find("pier") != string::npos) // /goto pier
			{
				player->SetPosition(Point3DMake(835.3309, -2055.8435, 12.8672));
			}
			else if (params[0].find("chiliad") != string::npos) // /goto chiliad
			{
				player->SetPosition(Point3DMake(-2317.3325, -1618.2611, 483.7491));
			}
			else if (params[0].find("drift") != string::npos) // /goto drift
			{
				player->SetPosition(Point3DMake(-2402.9199, -597.4742, 132.6484));
			}
			else if (params[0].find("wheelarch") != string::npos) // /goto wheelarch
			{
				player->SetPosition(Point3DMake(-2705.5552, 218.5947, 4.1797));
			}
			else if (params[0].find("locolow") != string::npos) // /goto locolow
			{
				player->SetPosition(Point3DMake(2646.9751, -2004.6864, 13.3828));
			}
			else if (params[0].find("transfender") != string::npos) // /goto transfender
			{
				player->SetPosition(Point3DMake(-1936.0275, 228.9241, 34.1563));
			}
			else if (params[0].find("coalminer") != string::npos) // /goto coalminer
			{
				player->SetPosition(Point3DMake(858.2095, 867.3469, 13.3516));
			}
			else if (params[0].find("skatepark") != string::npos) // /goto skatepark
			{
				player->SetPosition(Point3DMake(1882.3457, -1394.2074, 13.5703));
			}
			else if (params[0].find("skyscraper") != string::npos) // /goto skyscraper
			{
				player->SetPosition(Point3DMake(1543.8177, -1353.3562, 329.4742));
			}
			else if (params[0].find("mafjump") != string::npos) // /goto mafjump
			{
				player->SetPosition(Point3DMake(1311.2545, -1767.1433, 13.3828));
			}
			else if (params[0].find("lombardstreet") != string::npos) // /goto lombardstreet
			{
				player->SetPosition(Point3DMake(-2138.5032, 918.8997, 79.8516));
			}
			else if (params[0].find("boat") != string::npos) // /goto boat
			{
				player->SetPosition(Point3DMake(-2473.3965, 1541.1923, 36.8047));
			}
			else if (params[0].find("bridgetop") != string::npos) // /goto bridgetop
			{
				player->SetPosition(Point3DMake(-2678.0583, 1595.1338, 217.2739));
			}
			else if (params[0].find("halfpipe") != string::npos) // /goto halfpipe
			{
				player->SetPosition(Point3DMake(-1642.9333, 100.1801, -11.1626));
			}
			else if (params[0].find("underwater") != string::npos) // /goto underwater
			{
				player->SetPosition(Point3DMake(-1687.6527, 172.3593, -51.7813));
			}
			else if (params[0].find("casino") != string::npos) // /goto casino
			{
				player->SetPosition(Point3DMake(-524.9528, 2592.3601, 53.4141));
			}
			else if (params[0].find("skydive") != string::npos) // /goto skydive
			{
				player->SetPosition(Point3DMake(443.1121, 662.1830, 4755.9175));
			}
			else if (params[0].find("smokespot") != string::npos) // /goto smokespot
			{
				player->SetPosition(Point3DMake(770.8389, 3778.0808, 8.5173));
			}
			else if (params[0].find("fc") != string::npos) // /goto fc
			{
				player->SetPosition(Point3DMake(-191.8151, 1099.8364, 19.5938));
			}
			else if (params[0].find("lb") != string::npos) // /goto lb
			{
				player->SetPosition(Point3DMake(-844.7393, 1546.5504, 23.1495));
			}
			else if (params[0].find("eq") != string::npos) // /goto eq
			{
				player->SetPosition(Point3DMake(-1495.7999, 2603.5476, 55.6929));
			}
			else if (params[0].find("boneyard") != string::npos) // /goto boneyard
			{
				player->SetPosition(Point3DMake(339.1008, 2500.8767, 16.4844));
			}
			else if (params[0].find("process") != string::npos)
			{
				player->SetPosition(Point3DMake(-928.9985, 2022.5295, 60.9141));
			}
			else if (params[0].find("cropdust") != string::npos)
			{
				player->SetPosition(Point3DMake(-156.5437, 39.6247, 3.1172));
			}
			else if (params[0].find("trucker") != string::npos)
			{
				player->SetPosition(Point3DMake(607.6465, 1669.4261, 7.1712));
			}
			else if (params[0].find("hotel1") != string::npos)
			{
				player->SetPosition(Point3DMake(2251.85, -1138.16, 1050.63));
				player->SetInterior(9);
			}
			else if (params[0].find("hotel2") != string::npos)
			{
				player->SetPosition(Point3DMake(2259.5757, -1135.9651, 1050.6328));
				player->SetInterior(10);
			}
			else if (params[0].find("hotel3") != string::npos)
			{
				player->SetPosition(Point3DMake(444.646911, 508.239044, 1001.419494));
				player->SetInterior(12);
			}
			else if (params[0].find("ubermotors") != string::npos)
			{
				player->SetPosition(Point3DMake(1094.1666, 1599.0883, 12.5469));
			} 
		}
	}

	return true;
}

bool CommandGetHere(Player *player, string text, vector<string> params);
bool CommandGetHere(Player *player, string text, vector<string> params)
{
	if (params.size() != 1)
	{
		ChatManager::SystemMessage(player, "Usage: \"/gethere [Part of name or PlayerID]\"");
	}
	else
	{
		Player *otherPlayer = CommandManager::GetPlayerFromParams(player, params, 0);
		if (otherPlayer)
		{
			Point3D position = player->GetPosition();
			position.x += 1; // Offset their position slightly

			otherPlayer->SetPosition(position);
			otherPlayer->SetInterior(player->GetInterior());
			otherPlayer->SetVirtualWorld(player->GetVirtualWorld());

			ChatManager::SystemMessage(otherPlayer, "You've been teleported by an admin.");
		}
	}

	return true;
}

bool CommandRepairVehicle(Player *player, string text, vector<string> params);
bool CommandRepairVehicle(Player *player, string text, vector<string> params)
{
	//int vehicleID = player->GetVehicleID();
	//if (vehicleID == 0)
	//{
	//	ChatManager::SystemMessage(player, "You're not in a vehicle!");
	//}
	if (JobManager::GetType(player) == JobTypeWheelman || FactionManager::GetFaction(player) == PlayerFactionUber)
	{
		int repairTimeRemaining = JobManager::GetWheelmanRepairTime(player);
		if (repairTimeRemaining > 0)
		{
			ChatManager::SystemMessage(player, "You have " + to_string(repairTimeRemaining) + " minutes remaining before you can repair again!");
		}
		else
		{
			if (params.empty())
			{
				// Wheelman repairing their own vehicle
				static const int WHEELMAN_REPAIR_COST = 20; // Money
				static const int WHEELMAN_REPAIR_TIME = 4; // Seconds

				if (player->GetMoney() >= WHEELMAN_REPAIR_COST)
				{
					int vehicleID = player->GetVehicleID();
					if (vehicleID != 0)
					{
						SetVehicleHealth(vehicleID, 1000);

						// TODO: Add greasemonkey perk here
						JobManager::SetWheelmanRepairTime(player, WHEELMAN_REPAIR_TIME);

						ChatManager::SystemMessage(player, "Your vehicle was repaired for $" + to_string(WHEELMAN_REPAIR_COST));
						ChatManager::EmoteMessage(player, player->GetName() + " repairs the " + VehicleManager::GetVehicleName(vehicleID));

						player->SubtractMoney(WHEELMAN_REPAIR_COST);
					}
					else
					{
						ChatManager::SystemMessage(player, "You're not in a vehicle!");
					}
				}
				else
				{
					ChatManager::SystemMessage(player, "You need at least $" + to_string(WHEELMAN_REPAIR_COST) + " to repair your vehicle.");
				}
			}
			else
			{
				// Wheelman offering a repair to someone else
			}
		}
	}
	else
	{
		ChatManager::SystemMessage(player, "You're not a wheelman!");
	}

	return true;
}

bool CommandFactionList(Player *player, string text, vector<string> params);
bool CommandFactionList(Player *player, string text, vector<string> params)
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

bool CommandFactionListMembers(Player *player, string text, vector<string> params);
bool CommandFactionListMembers(Player *player, string text, vector<string> params)
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

bool CommandFactionGiveRank(Player *player, string text, vector<string> params);
bool CommandFactionGiveRank(Player *player, string text, vector<string> params)
{
	if (FactionManager::GetRank(player) < 6)
	{
		ChatManager::SystemMessage(player, "This command is only available to faction players at {FF0000FF}rank 6.");
	}
	else if (params.size() != 2)
	{
		ChatManager::SystemMessage(player, "Usage: \"/giverank [Part of name or PlayerID] [Rank 1-6]\"");
	}
	else
	{
		Player *otherPlayer = CommandManager::GetPlayerFromParams(player, params, 0);
		if (otherPlayer && FactionManager::GetFaction(player) == FactionManager::GetFaction(otherPlayer))
		{
			string rankString = params[1];
			int newRank = stoi(rankString);
			if (newRank < 1 || newRank > 6)
			{
				ChatManager::SystemMessage(player, "Valid ranks are from 1 to 6.");
			}
			else
			{
				int currentRank = FactionManager::GetRank(otherPlayer);

				string status = (currentRank < newRank ? "promoted" : "demoted");
				string factionName = FactionManager::GetName(FactionManager::GetFaction(player));
				string message = player->GetName() + " has " + status + " " + otherPlayer->GetName() + " to rank " + to_string(newRank) + " in " + factionName; // TODO: Add Rank names
				ChatManager::FactionMessage(otherPlayer, message);
				ChatManager::FactionMessage(player, "You gave " + otherPlayer->GetName() + " rank " + to_string(newRank) + " in " + factionName);

				FactionManager::SetRank(otherPlayer, newRank);
			}
		}
		else
		{
			ChatManager::SystemMessage(player, otherPlayer->GetName() + " is not in your faction!");
		}
	}
	return true;
}

bool CommandFactionInvite(Player *player, string text, vector<string> params);
bool CommandFactionInvite(Player *player, string text, vector<string> params)
{
	PlayerFaction playerFaction = FactionManager::GetFaction(player);
	if (playerFaction == PlayerFactionCivilian)
	{
		ChatManager::SystemMessage(player, "You're not in a faction.");
	}
	else if (FactionManager::GetRank(player) < 6)
	{
		ChatManager::SystemMessage(player, "You must be rank 6 to invite other players.");
	}
	else if (params.size() != 1)
	{
		ChatManager::SystemMessage(player, "Usage: \"/invite [Part of name or PlayerID]\"");
	}
	else
	{
		Player *otherPlayer = CommandManager::GetPlayerFromParams(player, params, 0);
		if (otherPlayer)
		{
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
	}
	return true;
}

bool CommandFactionUnInvite(Player *player, string text, vector<string> params);
bool CommandFactionUnInvite(Player *player, string text, vector<string> params)
{
	return true;
}

bool CommandFactionDeposit(Player *player, string text, vector<string> params);
bool CommandFactionDeposit(Player *player, string text, vector<string> params)
{
	return true;
}

bool CommandFactionWithdraw(Player *player, string text, vector<string> params);
bool CommandFactionWithdraw(Player *player, string text, vector<string> params)
{
	return true;
}

bool CommandFactionShowBalance(Player *player, string text, vector<string> params);
bool CommandFactionShowBalance(Player *player, string text, vector<string> params)
{
	return true;
}

bool CommandToggleVehicleWindows(Player *player, string text, vector<string> params);
bool CommandToggleVehicleWindows(Player *player, string text, vector<string> params)
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

bool CommandShowVehicleWindowState(Player *player, string text, vector<string> params);
bool CommandShowVehicleWindowState(Player *player, string text, vector<string> params)
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

bool CommandStartEvent(Player *player, string text, vector<string> params);
bool CommandStartEvent(Player *player, string text, vector<string> params)
{
	eventInProgress = true;
	eventPosition = player->GetPosition();

	SendClientMessage(player->GetID(), COLOR_LIGHTBLUE, "Event position saved. Don't for get to use /endevent to stop teleportations.");
	SendClientMessageToAll(COLOR_LIGHTBLUE, "** An admin has started an event. Use /joinevent to check it out!");

	return true;
}

bool CommandEndEvent(Player *player, string text, vector<string> params);
bool CommandEndEvent(Player *player, string text, vector<string> params)
{
	if (!eventInProgress)
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

bool CommandJoinEvent(Player *player, string text, vector<string> params);
bool CommandJoinEvent(Player *player, string text, vector<string> params)
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

bool CommandGetJob(Player *player, string text, vector<string> params);
bool CommandGetJob(Player *player, string text, vector<string> params)
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

bool CommandQuitJob(Player *player, string text, vector<string> params);
bool CommandQuitJob(Player *player, string text, vector<string> params)
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

bool CommandMakeLeader(Player *player, string text, vector<string> params);
bool CommandMakeLeader(Player *player, string text, vector<string> params)
{
	if (params.size() != 2)
	{
		ChatManager::SystemMessage(player, "Usage: \"/makeleader [Part of name or PlayerID] [Faction]\"");
	}
	else
	{
		Player *otherPlayer = CommandManager::GetPlayerFromParams(player, params, 0);
		if (otherPlayer) {
			string factionString = params[1];
			PlayerFaction faction = (PlayerFaction)stoi(factionString);

			FactionManager::AddLeader(otherPlayer, faction);
		}
		
	}

	return true;
}

bool CommandSetWalkStyle(Player *player, string text, vector<string> params);
bool CommandSetWalkStyle(Player *player, string text, vector<string> params)
{
	if (player->IsHandCuffed())
	{
		ChatManager::SystemMessage(player, "You cannot do that while cuffed!");
	}
	else
	{
		int style = -1;
		if (params.size() == 1 && IsNumeric(params[0]))
		{
			style = stoi(params[0]);
		}
		
		if (style > 0 && style < 9)
		{
			player->StartWalkAnimation(style);
		}
		else
		{
			ChatManager::SystemMessage(player, "USAGE: /walk [1-8]");
		}
	}

	return true;
}

bool CommandSetRunStyle(Player *player, string text, vector<string> params);
bool CommandSetRunStyle(Player *player, string text, vector<string> params)
{
	if (player->IsHandCuffed())
	{
		ChatManager::SystemMessage(player, "You cannot do that while cuffed!");
	}
	else
	{
		int style = -1;
		if (params.size() == 1 && IsNumeric(params[0]))
		{
			style = stoi(params[0]);
		}

		if (style > 0 && style < 8)
		{
			player->StartRunAnimation(style);
		}
		else
		{
			ChatManager::SystemMessage(player, "USAGE: /run [1-7]");
		}
	}

	return true;
}

bool CommandTurnOnRadio(Player *player, string text, vector<string> params);
bool CommandTurnOnRadio(Player *player, string text, vector<string> params)
{
	if (RadioManager::IsOwned(player))
	{
		if (RadioManager::IsEnabled(player))
		{
			ChatManager::SystemMessage(player, "Your walkie talkie is already on.");
		}
		else
		{
			RadioManager::SetEnabled(player, true);
		}
	}
	else
	{
		ChatManager::SystemMessage(player, "You don't have a walkie talkie, purchase one from the 24/7.");
	}
	return true;
}

bool CommandTurnOffRadio(Player *player, string text, vector<string> params);
bool CommandTurnOffRadio(Player *player, string text, vector<string> params)
{
	if (RadioManager::IsOwned(player))
	{
		if (!RadioManager::IsEnabled(player))
		{
			ChatManager::SystemMessage(player, "Your walkie talkie is already off.");
		}
		else
		{
			RadioManager::SetEnabled(player, false);
		}
	}
	else
	{
		ChatManager::SystemMessage(player, "You don't have a walkie talkie, purchase one from the 24/7.");
	}
	return true;
}

bool CommandRadioHelp(Player *player, string text, vector<string> params);
bool CommandRadioHelp(Player *player, string text, vector<string> params)
{
	if (RadioManager::IsOwned(player))
	{
		ChatManager::WhiteMessage(player, "/rOn - Turns on your radio.");
		ChatManager::WhiteMessage(player, "/rOff - Turns off your radio.");
		ChatManager::WhiteMessage(player, "/rTune [Frequency] - Tunes your radio to the specified sequence.");
		ChatManager::WhiteMessage(player, "/r [Text] - Transmits the specified message.");
	}
	else
	{
		ChatManager::SystemMessage(player, "You don't have a walkie talkie, purchase one from the 24/7.");
	}
	return true;
}

bool CommandTuneRadio(Player *player, string text, vector<string> params);
bool CommandTuneRadio(Player *player, string text, vector<string> params)
{
	if (RadioManager::IsOwned(player))
	{
		int frequency = -1;

		if (params.size() == 1)
		{
			if (IsNumeric(params[0]))
			{
				frequency = stoi(params[0]);
			}
		}

		if (frequency < 1000 || frequency > 10000)
		{
			ChatManager::SystemMessage(player, "You may only tune your walkie talkie from 1000Hz to 10000Hz");
		}
		else
		{
			PlayerFaction faction = FactionManager::GetFaction(player);
			if (frequency == 9111 && (faction != PlayerFactionPolice && faction != PlayerFactionEMT))
			{
				ChatManager::SystemMessage(player, "This frequency is reserved for emergency use only.");
			}
			else
			{
				RadioManager::SetRadioFrequency(player, frequency);
			}
		}
	}
	else
	{
		ChatManager::SystemMessage(player, "You don't have a walkie talkie, purchase one from the 24/7.");
	}
	return true;
}

bool CommandRadioChat(Player *player, string text, vector<string> params);
bool CommandRadioChat(Player *player, string text, vector<string> params)
{
	if (RadioManager::IsOwned(player))
	{
		if (RadioManager::IsEnabled(player))
		{
			RadioManager::SendMessage(player, text);
		}
		else
		{
			ChatManager::SystemMessage(player, "Your walkie talkie is disabled. Use /ron to turn it on.");
		}
	}
	else
	{
		ChatManager::SystemMessage(player, "You don't have a walkie talkie, purchase one from the 24/7.");
	}
	return true;
}

Player* CommandManager::GetPlayerFromParams(Player *player, vector<string> params, vector<string>::size_type index)
{
	Player *otherPlayer = CommandManager::GetPlayerFromParams(params, index);
	if (!otherPlayer)
	{
		ChatManager::ErrorMessageInvalidPlayer(player);
	}
	return otherPlayer;
}

Player* CommandManager::GetPlayerFromParams(vector<string> params, vector<string>::size_type index)
{
	Player *player = NULL;

	if (params.size() > index)
	{
		string playerString = params[index];
		//sampgdk_logprintf("Player string: %s", playerString.c_str());
		if (IsNumeric(playerString)) {
			int playerID = stoi(playerString);
			//sampgdk_logprintf("Checking for player id: %d", playerID);
			player = PlayerManager::GetPlayer(playerID);
			//sampgdk_logprintf("Player by id: %p", player);
		}
		else
		{
			// Transform the input to lower case so case insensitive match will work
			playerString = ToLowerCase(playerString);

			for (auto i = PlayerManager::BeginPlayer(); i != PlayerManager::EndPlayer(); i++)
			{
				string playerName = ToLowerCase(i->second->GetName());
				if (playerName.find(playerString) != string::npos) {
					player = i->second;
					break;
				}
			}
			//sampgdk_logprintf("Player by name: %p", player);
		}
	}
	 
	return player;
}

CommandFunction CommandManager::GetCommand(std::string commandInput)
{
	// Transform commandInput to lowercase in command
	string command = ToLowerCase(commandInput);

	//sampgdk_logprintf("Searching for command %s in map.", command.c_str());
	auto commandFunctionIter = commandMap.find(command);
	if (commandFunctionIter != commandMap.end()) {
		return commandFunctionIter->second;
	}
	return NULL;
}

bool CommandManager::OnPlayerCommandText(Player *player, string commandText)
{
	// TODO: Add spam time

	sampgdk_logprintf("Splitting params %s", commandText.c_str());
	vector<string> params = split(commandText);
	sampgdk_logprintf("Split in to %d params", params.size());

	if (params.size() > 0) 
	{
		sampgdk_logprintf("Parsing commandRemaing and Name");
		string commandRemainingText;
		string commandName = params[0].substr(1);
		if (params.size() > 1)
		{
			commandRemainingText = commandText.substr(params[0].size() + 1);
		}
		
		sampgdk_logprintf("Name %s - Remaining %s", commandName.c_str(), commandRemainingText.c_str());

		auto commandFunction = GetCommand(commandName);
		if (commandFunction)
		{
			sampgdk_logprintf("Found Command: %s", commandName.c_str());

			bool passedChecks = true;
			  
			auto adminLevelIter = commandAdminLevelMap.find(commandFunction);
			if (adminLevelIter != commandAdminLevelMap.cend()) {
				passedChecks = AdminLevelCheck(player, adminLevelIter->second);
				//if (!passedChecks)
				//{
				//	sampgdk_logprintf("Failed admin level check for command %s", commandName.c_str());
				//}
			}

			if (passedChecks) {
				// Erase the first element, which is the command itself
				params.erase(params.begin());
				commandFunction(player, commandRemainingText, params);
			}

			return true;
		}
	}

	return false;
}

#define COMMAND(name, commandFunction) commandMap[name] = &commandFunction;
#define ADMIN_COMMAND(name, commandFunction, adminLevel) COMMAND(name, commandFunction); commandAdminLevelMap[&commandFunction] = adminLevel;
CommandManager::CommandManager()
{
	//
	//		Admin
	//
	ADMIN_COMMAND("makeleader", CommandMakeLeader, 6);
	ADMIN_COMMAND("givegun", CommandGiveGun, 6);
	
	ADMIN_COMMAND("sethp", CommandSetHealth, 4);
	ADMIN_COMMAND("setarmor", CommandSetArmor, 4);
	ADMIN_COMMAND("setskin", CommandSetSkin, 4);

	ADMIN_COMMAND("v", CommandVeh, 2);
	ADMIN_COMMAND("veh", CommandVeh, 2);

	ADMIN_COMMAND("startevent", CommandStartEvent, 2);
	ADMIN_COMMAND("endevent", CommandEndEvent, 2);
	
	ADMIN_COMMAND("gethere", CommandGetHere, 2);
	ADMIN_COMMAND("goto", CommandGoto, 2);

	//ADMIN_COMMAND("slap", CommandGoto, 2);

	//ADMIN_COMMAND("freeze", CommandFreeze, 2);
	//ADMIN_COMMAND("unfreeze", CommandUnFreeze, 2);

	//
	//		Roleplay Chat & Emote
	//
	COMMAND("me", CommandEmote);
	COMMAND("b", CommandLocalOOC);
	COMMAND("o", CommandOOC);
	COMMAND("ooc", CommandOOC);
	COMMAND("do", CommandDo);
	//COMMAND("a", CommandAdminChat);
	COMMAND("s", CommandShout);
	//COMMAND("c", CommandCloseChat);
	//COMMAND("l", CommandLocalIC);
	//COMMAND("f", CommandFactionChat);
	//COMMAND("m", CommandMegaphone);
	//COMMAND("n", CommandNewbieChat);
	//COMMAND("ad", CommandAdvertise);
	//COMMAND("w", CommandWhisper);
	

	//
	//		Player
	//
	COMMAND("kill", CommandKill);
	COMMAND("dance", CommandDance);
	COMMAND("joinevent", CommandJoinEvent);
	COMMAND("walk", CommandSetWalkStyle);
	COMMAND("run", CommandSetRunStyle);

	//
	//		Radio
	//
	COMMAND("ron", CommandTurnOnRadio);
	COMMAND("roff", CommandTurnOffRadio);
	COMMAND("rhelp", CommandRadioHelp);
	COMMAND("rtune", CommandTuneRadio);
	COMMAND("r", CommandRadioChat);


	//
	//		Vehicle
	//
	COMMAND("rw", CommandToggleVehicleWindows);
	COMMAND("windows", CommandShowVehicleWindowState);

	//
	//		Faction
	//
	COMMAND("factions", CommandFactionList); COMMAND("families", CommandFactionList);
	COMMAND("invite", CommandFactionInvite);
	COMMAND("uninvite", CommandFactionUnInvite);
	COMMAND("fbalance", CommandFactionShowBalance);
	COMMAND("fwithdraw", CommandFactionWithdraw);
	COMMAND("fdeposit", CommandFactionDeposit);
	COMMAND("members", CommandFactionListMembers);
	COMMAND("giverank", CommandFactionGiveRank);

	//
	//		Job
	//
	COMMAND("cropdust", CommandCropdust);
	COMMAND("coalmine", CommandCoalmine);
	COMMAND("getjob", CommandGetJob);
	COMMAND("quitjob", CommandQuitJob);

	//
	//		Job - Wheelman
	//
	COMMAND("re", CommandRepairVehicle); COMMAND("repair", CommandRepairVehicle);

	//
	//		Police
	//
	//COMMAND("tazer", CommandTazer);
	//COMMAND("cuff", CommandCuff);
	//COMMAND("uncuff", CommandUncuff);
	//COMMAND("detain", CommandDetain);
	//COMMAND("arrest", CommandArrest);
	//COMMAND("gov", CommandGovernmentMessage);
	//COMMAND("su", CommandSuspect);
	//COMMAND("wanted", CommandWanted);
	//COMMAND("ticket", CommandTicket);
	//COMMAND("confiscate", CommandConfiscate);
	//COMMAND("clear", CommandClearWantedLevel);
	//COMMAND("rb", CommandCreateRoadBlock);
	COMMAND("bk", CommandRequestBackup); COMMAND("backup", CommandRequestBackup);
	COMMAND("bkcancel", CommandCancelRequestBackup); COMMAND("backupcancel", CommandCancelRequestBackup);
	//COMMAND("impound", CommandImpound);
	//COMMAND("residence", CommandShowResidence);

	//
	// EMT 
	//
	//COMMAND("heal", CommandHeal);

	//
	// Animations
	//

	// animation commands -----------------
	//dcmd(drunk, 5, cmdtext);
	//dcmd(bomb, 4, cmdtext);
	//dcmd(crossarms, 9, cmdtext);
	//dcmd(seat, 4, cmdtext);
	//dcmd(lay, 3, cmdtext);
	//dcmd(laugh, 5, cmdtext);
	//dcmd(robman, 6, cmdtext);
	//dcmd(getarrested, 11, cmdtext);
	//dcmd(fall, 4, cmdtext);
	//dcmd(wave, 4, cmdtext);
	//dcmd(crack, 5, cmdtext);
	//dcmd(chat, 4, cmdtext);g
	//dcmd(lookout, 7, cmdtext);
	//dcmd(deal, 4, cmdtext);
	//dcmd(taichi, 6, cmdtext);
	//dcmd(gro, 3, cmdtext);
	//dcmd(eatanim, 7, cmdtext);
	//dcmd(fucku, 5, cmdtext);
	//dcmd(smoke, 5, cmdtext);
	//dcmd(walk, 4, cmdtext);
	//dcmd(run, 3, cmdtext);
	//dcmd(hide, 4, cmdtext);
	//dcmd(rap, 3, cmdtext);
	//dcmd(handsup, 7, cmdtext);
	//dcmd(dance, 5, cmdtext);
	//dcmd(cellin, 6, cmdtext);
	//dcmd(cellout, 7, cmdtext);
	//dcmd(vomit, 5, cmdtext);
	//dcmd(lightcig, 8, cmdtext);
	//dcmd(slapass, 7, cmdtext);
	//dcmd(sideways, 8, cmdtext);
	//dcmd(stopani, 7, cmdtext);
	//dcmd(animlist, 8, cmdtext);
	//dcmd(piss, 4, cmdtext);
}

CommandManager::~CommandManager()
{

}