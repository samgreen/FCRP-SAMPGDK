#pragma once

#include <unordered_map>
#include <string>
#include "Point.h"

typedef enum {
	JobTypeNone,
	JobTypeWheelman,
	JobTypeDrugDealer,
	JobTypeArmsDealer,
	JobTypeMercenary,
	JobTypeLawyer,
} JobType;

class Player;

class JobManager
{
public:
	static JobType GetType(Player *player);
	static void SetType(Player *player, JobType type);

	static int GetContractTime(Player *player);

	static Point3D GetPoint(JobType type);
	static std::string GetName(JobType type);

private:
	JobManager();
	~JobManager();

	static std::unordered_map<int, JobType> playerJobTypeMap;
	static std::unordered_map<int, int> playerJobContractTimeMap;
};

