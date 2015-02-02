#pragma once

#include <map>
#include <string>
#include "Point.h"

using namespace std;

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
	static string GetName(JobType type);

private:
	JobManager();
	~JobManager();

	static map<int, JobType> playerJobTypeMap;
	static map<int, int> playerJobContractTimeMap;
};

