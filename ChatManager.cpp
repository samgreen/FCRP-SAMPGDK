#include "ChatManager.h"
#include "PlayerManager.h"
#include "VehicleManager.h"
#include "Player.h"
#include "Constants.h"

using namespace std;

static const float MESSAGE_DISTANCE = 20.f;
static const float EMOTE_DISTANCE = MESSAGE_DISTANCE - 2.f;

 void ChatManager::AdminMessage(string message)
{
	for (auto i = PlayerManager::BeginPlayer(); i != PlayerManager::EndPlayer(); i++)
	{
		Player *p = i->second;
		if (p->GetAdminLevel() > 0) {
			SendClientMessage(p->GetID(), COLOR_YELLOW, message.c_str());
		}
	}
}

 void ChatManager::SystemMessage(Player *player, string message)
{
	SendClientMessage(player->GetID(), COLOR_GRAD1, message.c_str());
}

 void ChatManager::VehicleMessage(Player *player, std::string message)
 {
	 int vehicleID = player->GetVehicleID();
	 for (auto i = PlayerManager::BeginPlayer(); i != PlayerManager::EndPlayer(); i++)
	 {
		 Player *p = i->second;
		 if (p->GetVehicleID() == vehicleID) {
			 SendClientMessage(p->GetID(), COLOR_FADE1, message.c_str());
		 }
	 }
 }

void ChatManager::ErrorMessageInvalidPlayer(Player *player)
 {
	 ChatManager::SystemMessage(player, "Invalid {FFFFFF}player name or ID.");
 }

void ChatManager::EmoteMessage(Player *player, string message)
{
	ChatManager::ProximityMessage(player, message, EMOTE_DISTANCE, COLOR_EMOTE);
}

void ChatManager::LocalMessage(Player *player, string message)
{
	ChatManager::ProximityMessage(player, message, MESSAGE_DISTANCE, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
}

void ChatManager::WhiteMessage(Player *player, string message)
{
	SendClientMessage(player->GetID(), COLOR_WHITE, message.c_str());
}

void ChatManager::OrangeMessage(Player *player, string message)
{
	SendClientMessage(player->GetID(), COLOR_ORANGE, message.c_str());
}

void ChatManager::SkillMessage(Player *player, string message)
{
	YellowMessage(player, message);
}

void ChatManager::YellowMessage(Player *player, string message)
{
	SendClientMessage(player->GetID(), COLOR_YELLOW, message.c_str());
}

void ChatManager::FactionMessage(Player *player, string message)
{
	SendClientMessage(player->GetID(), COLOR_BLUE, message.c_str());
}

void ChatManager::ProximityMessage(Player *player, string message, float distance, int color)
{
	ProximityMessage(player, message, distance, color, color, color, color, color);
}

void ChatManager::ProximityMessage(Player *player, string message, float distance, int color1, int color2, int color3, int color4, int color5)
{
	Point3D position = player->GetPosition();
	bool inVehicle = player->IsInVehicle();
	for (auto i = PlayerManager::BeginPlayer(); i != PlayerManager::EndPlayer(); i++)
	{
		Player *otherPlayer = i->second;
		if (player->GetID() == otherPlayer->GetID())
		{
			SendClientMessage(player->GetID(), color1, message.c_str());
			continue;
		}

		int vehicleID = player->GetVehicleID();
		if (inVehicle && !VehicleManager::IsWindowOpen(vehicleID))
		{
			if (otherPlayer->IsInVehicleID(vehicleID))
			{
				SendClientMessage(otherPlayer->GetID(), color1, message.c_str());
			}
		}
		else if (player->GetVirtualWorld() == otherPlayer->GetVirtualWorld())
		{
			Point3D otherPlayerPosition = otherPlayer->GetPosition();
			if (Point3DDistance(position, otherPlayerPosition) < distance / 16)
			{
				SendClientMessage(otherPlayer->GetID(), color1, message.c_str());
			}
			else if (Point3DDistance(position, otherPlayerPosition) < distance / 8)
			{
				SendClientMessage(otherPlayer->GetID(), color2, message.c_str());
			}
			else if (Point3DDistance(position, otherPlayerPosition) < distance / 4)
			{
				SendClientMessage(otherPlayer->GetID(), color3, message.c_str());
			}
			else if (Point3DDistance(position, otherPlayerPosition) < distance / 2)
			{
				SendClientMessage(otherPlayer->GetID(), color4, message.c_str());
			}
			else if (Point3DDistance(position, otherPlayerPosition) < distance)
			{
				SendClientMessage(otherPlayer->GetID(), color5, message.c_str());
			}
		}
	}
}
