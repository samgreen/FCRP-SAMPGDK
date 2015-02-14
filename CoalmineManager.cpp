#include "CoalmineManager.h"
#include "ChatManager.h"
#include "VehicleManager.h"
#include "Player.h"
#include "Constants.h"
#include <string>

using namespace std;

static const float CHECKPOINT_RADIUS = 7.f;
static const float CHECKPOINT_POSITIONS[][3] = 
{
	{ 848.6245f, 859.3553f,  13.3516f },
	{ 789.3705f, 839.8206f,   6.0424f },
	{ 771.7532f, 879.8436f,  -1.2641f },
	{ 740.1155f, 927.3599f,  -7.4024f },
	{ 688.7795f, 976.1136f, -12.7266f },
	{ 714.7140f, 931.1240f, -18.6950f },
	{ 724.5949f, 883.0548f, -26.4531f },
	{ 694.3653f, 920.2028f, -30.3084f },
	{ 639.8461f, 945.1127f, -35.2742f },
	{ 622.7034f, 908.2230f, -44.2276f },
	{ 658.3267f, 902.0953f, -40.8106f },
	{ 625.4291f, 861.7248f, -42.9609f },
	{ 586.1722f, 844.6242f, -42.4941f },
	{ 500.2440f, 874.7889f, -32.6625f },
	{ 510.6912f, 905.1781f, -35.2572f },
	{ 578.9271f, 901.1987f, -43.5548f },
	{ 624.4080f, 912.1463f, -43.5663f },
	{ 682.2263f, 938.3443f, -30.2094f },
	{ 718.4686f, 885.8133f, -26.6751f },
	{ 713.8182f, 929.0585f, -18.6895f },
	{ 684.6675f, 975.9233f, -12.7242f },
	{ 746.6543f, 914.0416f,  -5.7938f }
};

static const int STAT_REQUIRED_FOR_LEVEL[] =
{
	50,
	100,
	200,
	400
};

static const int COOLDOWN_FOR_LEVEL[] =
{
	20,
	18,
	16,
	14,
	12
};
unordered_map<int, int> CoalmineManager::cooldownTime;
unordered_map<int, int> CoalmineManager::currentCheckPoint;

CoalmineManager::CoalmineManager()
{
}

CoalmineManager::~CoalmineManager()
{
}

void CoalmineManager::MinuteTimer()
{
	// Iterate over players
	for (auto i : cooldownTime)
	{
		int time = i.second;
		if (time > 0) {
			// Decrement mine cooldown time
			cooldownTime[i.first] = --time;
		}
		sampgdk_logprintf("Player %d has %d minutes left on coalmine.", i.first, i.second);
	}
}

bool CoalmineManager::IsMining(Player *player)
{
	return CheckTime(player);
}

void CoalmineManager::OnPlayerExitVehicle(Player *player)
{
	int currentCheckPointIndex = currentCheckPoint[player->GetID()];
	if (currentCheckPointIndex > 0)
	{
		currentCheckPoint[player->GetID()] = 0;

		SendClientMessage(player->GetID(), COLOR_RED, "You've exited your dumper ending your coal delivery!");
		DisablePlayerRaceCheckpoint(player->GetID());
	}
}

void CoalmineManager::OnPlayerEnterRaceCheckpoint(Player *player)
{
	int currentCheckPointIndex = currentCheckPoint[player->GetID()];
	if (currentCheckPointIndex > 0)
	{
		SetCheckpoint(player, ++currentCheckPointIndex);
	}

	// Last checkpoint, they're done
	if (currentCheckPointIndex == ARRAY_SIZE(CHECKPOINT_POSITIONS) + 1)
	{
		int level = player->GetCoalMiningLevel();

		player->IncrementCoalMiningStat();
		int stat = player->GetCoalMiningStat();

		// Check for level up
		for (int i = 0; i < ARRAY_SIZE(STAT_REQUIRED_FOR_LEVEL); i++)
		{
			if (stat == STAT_REQUIRED_FOR_LEVEL[i]) // level up
			{
				player->SetCoalMiningLevel(++level);
				ChatManager::SkillMessage(player, "Your coal mining skill is now level " + to_string(i) + ", you can mine again in " + to_string(COOLDOWN_FOR_LEVEL[level]) + " minutes.");
				break;
			}
		}
		cooldownTime[player->GetID()] = COOLDOWN_FOR_LEVEL[level];

		int cash = 35 * (1 + level) + rand() % 25;
		// TODO: Blacklung upgrade
		player->AddMoney(cash);

		string gameTextMessage = "~w~Coal delivered.~n~~w~You get $" + to_string(cash) + " for your shift's work.~n~~w~You can mine coal again in " + to_string(cooldownTime[player->GetID()]) + " minutes.";
		GameTextForPlayer(player->GetID(), gameTextMessage.c_str(), 5000, 3);

		DisablePlayerRaceCheckpoint(player->GetID());
	}
}

void CoalmineManager::Start(Player *player)
{
	if (CheckTime(player))
	{
		if (VehicleManager::IsDumpTruck(player->GetVehicleID()))
		{
			ChatManager::WhiteMessage(player, "Drive through the checkpoints and deliver the coal. Hurry up!");
			GameTextForPlayer(player->GetID(), "~y~Coal miner~n~~w~Drive through the checkpoints and deliver the ~r~coal.", 5000, 3);
			SetCheckpoint(player, 1);
		}
		else
		{
			ChatManager::SystemMessage(player, "You're not in a dumper! Pick one up at the Quarry.");
		}
	}
	else
	{
		ChatManager::SystemMessage(player, "You still have " + to_string(GetCooldownTime(player)) + " minutes remaining before you can mine coal again.");
	}
}

int CoalmineManager::GetCooldownTime(Player *player)
{
	return cooldownTime[player->GetID()];
}

bool CoalmineManager::CheckTime(Player *player)
{
	return (GetCooldownTime(player) <= 0);
}

void CoalmineManager::SetCheckpoint(Player *player, int index)
{
	int checkpointArrayIndex = index - 1;
	float currentX = CHECKPOINT_POSITIONS[checkpointArrayIndex][0], currentY = CHECKPOINT_POSITIONS[checkpointArrayIndex][1], currentZ = CHECKPOINT_POSITIONS[checkpointArrayIndex][2];

	
	float nextX = 0.f, nextY = 0.f, nextZ = 0.f;
	if (checkpointArrayIndex < ARRAY_SIZE(CHECKPOINT_POSITIONS))
	{
		nextX = CHECKPOINT_POSITIONS[checkpointArrayIndex + 1][0];
		nextY = CHECKPOINT_POSITIONS[checkpointArrayIndex + 1][1];
		nextZ = CHECKPOINT_POSITIONS[checkpointArrayIndex + 1][2];
	}
	
	bool lastCheckPoint = (index == ARRAY_SIZE(CHECKPOINT_POSITIONS));
	int checkPointType = (lastCheckPoint ? 1 : 0);
	SetPlayerRaceCheckpoint(player->GetID(), checkPointType, currentX, currentY, currentZ, nextX, nextY, nextZ, CHECKPOINT_RADIUS);

	currentCheckPoint[player->GetID()] = index;
}
