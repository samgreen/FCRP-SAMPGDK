#include "JobManager.h"
#include "sampgdk.h"
#include "Player.h"

using namespace std;

static const int DEFAULT_CONTRACT_TIME = 60; // Minutes

unordered_map<int, int>		JobManager::playerJobContractTimeMap;
unordered_map<int, JobType> JobManager::playerJobTypeMap;
unordered_map<int, int>		JobManager::playerWheelmanRepairTimeMap;

void JobManager::SecondTimer()
{

}

void JobManager::MinuteTimer()
{
	for (auto i : playerJobContractTimeMap)
	{
		int time = i.second;
		if (time > 0) {
			playerJobContractTimeMap[i.first] = --time;
		}
		//sampgdk_logprintf("Player %d has %d minutes left on job contract", i.first, i.second);
	}

	for (auto i : playerWheelmanRepairTimeMap)
	{
		int time = i.second;
		if (time > 0) {
			playerWheelmanRepairTimeMap[i.first] = --time;
		}
		//sampgdk_logprintf("Player %d has %d minutes left on wheelman repair", i.first, i.second);
	}
}

JobType JobManager::GetType(Player *player)
{
	auto i = playerJobTypeMap.find(player->GetID());
	if (i != playerJobTypeMap.cend())
	{
		return i->second;
	}
	return JobTypeNone;
}

void JobManager::SetType(Player *player, JobType type)
{
	playerJobTypeMap[player->GetID()] = type;
	playerJobContractTimeMap[player->GetID()] = DEFAULT_CONTRACT_TIME;
}

string JobManager::GetName(JobType type)
{
	switch (type)
	{
	case JobTypeNone: return "None";
	case JobTypeWheelman: return "Wheelman";
	case JobTypeDrugDealer: return "Drug Dealer";
	case JobTypeArmsDealer: return "Arms Dealer";
	case JobTypeMercenary: return "Mercenary";
	case JobTypeLawyer: return "Lawyer";
	default:
		break;
	}
	return "Unknown Job";
}

Point3D JobManager::GetPoint(JobType type)
{
	switch (type)
	{
	case JobTypeWheelman: return Point3DMake(-90.6001f, 1118.4298f, 20.7860f);
	case JobTypeDrugDealer: return Point3DMake(-713.4171f, 681.8257f, 3.8607f);
	case JobTypeArmsDealer: return Point3DMake(-329.3828f, 835.5164f, 14.2422f);
	case JobTypeMercenary: return Point3DMake(-1483.4847f, 2614.4500f, 58.7879f);
	default: return Point3DZero;
	}
}

int JobManager::GetContractTime(Player *player)
{
	return playerJobContractTimeMap[player->GetID()];
}

int JobManager::GetWheelmanRepairTime(Player *player)
{
	return playerWheelmanRepairTimeMap[player->GetID()];
}

void JobManager::SetWheelmanRepairTime(Player *player, int time)
{
	playerWheelmanRepairTimeMap[player->GetID()] = time;
}
