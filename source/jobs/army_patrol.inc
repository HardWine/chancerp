#if defined army_patrol_included
	#endinput
#endif

#define army_patrol_included

new Player.PatrolCP[MAX_PLAYERS] = {INVALID_DYNAMIC_CP, ...};
forward Patrol_OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid);
new PATROL_TOWER[9];
new PatrolZone[9];
new player_Patrol[MAX_PLAYERS] = -1;

new PatrolTimer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...}; 

forward Patrol_OnGameModeInit();
public Patrol_OnGameModeInit() {
	PatrolZone[0] = CreateDynamicCylinder(162.3296, 1932.9833, 25, 35, 15);
	PatrolZone[1] = CreateDynamicCylinder(103.9078, 1900.6954, 25, 35, 15);
	PatrolZone[2] = CreateDynamicCylinder(113.3552, 1814.4213, 25, 35, 15);
	PatrolZone[3] = CreateDynamicCylinder(166.0648, 1849.855, 25, 35, 15);
	PatrolZone[4] = CreateDynamicCylinder(262.2686, 1807.1348, 25, 35, 15);
	PatrolZone[5] = CreateDynamicCylinder(267.1777, 1895.3052, 25, 35, 15);
	PatrolZone[6] = CreateDynamicCylinder(233.6904, 1935.3856, 25, 35, 15);
	PatrolZone[7] = CreateDynamicCylinder(96.8001, 1920.4340, 15, 25, 30);
	PatrolZone[8] = CreateDynamicCylinder(341.6616, 1804.3160, 15, 25, 30);
}

forward OnPlayerEnterPatrolCP(playerid, STREAMER_TAG_CP checkpointid);
public OnPlayerEnterPatrolCP(playerid, STREAMER_TAG_CP checkpointid) {

	if(Player.PatrolCP[playerid] == checkpointid && IsPlayerInAnyVehicle(playerid) == 0) { 
		// 1 МАРШРУТ (1-4)
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 165.4972,1932.1563,33.4981)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 1);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 162.2766,1931.2283,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 2);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 160.3832,1932.9899,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 3);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 162.1092,1935.2637,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 4);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		// 2 МАРШРУТ (5-8)
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 107.4883,1900.2822,33.4988)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 5);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 104.2140,1899.2179,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 6);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 102.2472,1900.9285,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 7);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 104.0126,1902.7732,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 8);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}	
		// 3 МАРШРУТ (9-12)
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 116.8958,1813.7156,33.4993)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 9);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 113.7116,1812.5693,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 10);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 111.6113,1814.2487,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 11);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 113.3675,1816.2024,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 12);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}	
		// 4 МАРШРУТ (13-16)
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 169.5328,1849.1542,33.4987)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 13);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 166.0950,1848.0941,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 14);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 164.2539,1849.7903,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 15);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 165.9684,1851.6871,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 16);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}	
		// 5 МАРШРУТ (17-20)
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 265.6458,1806.8669,33.4989)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 17);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 262.3283,1805.7856,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 18);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 260.3836,1807.2378,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 19);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 262.0783,1809.3845,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 20);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}	
		// 6 МАРШРУТ (21-24)
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 270.6409,1894.4889,33.4989)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 21);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 267.3655,1893.4131,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 22);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 265.3108,1895.1185,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 23);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 267.0774,1896.9723,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 24);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		// 7 МАРШРУТ (25-28)
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 237.0311,1934.0801,33.4992)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 25);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 233.8169,1932.9153,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 26);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 231.7041,1934.7461,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 27);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.1, 233.2229,1936.5203,33.8984)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 28);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		// 8 МАРШРУТ (29-32)
		if(IsPlayerInRangeOfPoint(playerid, 3.1, 103.3832,1913.4237,18.4054)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 29);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.1, 92.5536,1916.6945,17.9983)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 30);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.1, 103.9860,1929.7076,18.4321)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 31);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.1, 93.1961,1924.8977,18.0405)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 32);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}	
		// 9 МАРШРУТ (33-36)
		if(IsPlayerInRangeOfPoint(playerid, 3.1, 347.6863,1815.4681,18.1154)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 33);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.1, 338.1339,1796.4677,18.0828)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 34);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.1, 328.7558,1801.5684,17.8348)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 35);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.1, 349.4514,1803.4324,18.5533)) {
			DeletePatrolCP(playerid);
			SetPVarInt(playerid, "patrol", 36);
			SetPVarInt(playerid, "MinusTime", 30);
			PatrolTimer[playerid] = SetTimerEx("PatrolAwait", 30000, 0, "i", playerid);
			return 1;
		}		
	}
	return 0;
}

forward PatrolAwait(playerid);
public PatrolAwait(playerid) {
	new patrol = GetPVarInt(playerid, "patrol");
	SetPVarInt(playerid, "inactive_patrol", 60);
	switch(patrol) {
		case 1: Player.PatrolCP[playerid] = CreateDynamicCP(162.2766,1931.2283,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 2:	Player.PatrolCP[playerid] = CreateDynamicCP(160.3832,1932.9899,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 3:	Player.PatrolCP[playerid] = CreateDynamicCP(162.1092,1935.2637,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 4: Player.PatrolCP[playerid] = CreateDynamicCP(165.4972,1932.1563,33.4981, 0.5, 0, 0, playerid, 60000.000, .priority = 2), IncreaseStatus(playerid,RandomEx(1,5)), AddPlayerAchievement(playerid, E_SOLDIER_SLEEPING);

		case 5: Player.PatrolCP[playerid] = CreateDynamicCP(104.2140,1899.2179,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 6:	Player.PatrolCP[playerid] = CreateDynamicCP(102.2472,1900.9285,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 7:	Player.PatrolCP[playerid] = CreateDynamicCP(104.0126,1902.7732,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 8: Player.PatrolCP[playerid] = CreateDynamicCP(107.4883,1900.2822,33.4988, 0.5, 0, 0, playerid, 60000.000, .priority = 2), IncreaseStatus(playerid,RandomEx(1,5)), AddPlayerAchievement(playerid, E_SOLDIER_SLEEPING);

		case 9: Player.PatrolCP[playerid] = CreateDynamicCP(113.7116,1812.5693,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 10:Player.PatrolCP[playerid] = CreateDynamicCP(111.6113,1814.2487,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 11:Player.PatrolCP[playerid] = CreateDynamicCP(113.3675,1816.2024,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 12:Player.PatrolCP[playerid] = CreateDynamicCP(116.8958,1813.7156,33.4993, 0.5, 0, 0, playerid, 60000.000, .priority = 2), IncreaseStatus(playerid,RandomEx(1,5)), AddPlayerAchievement(playerid, E_SOLDIER_SLEEPING);

		case 13:Player.PatrolCP[playerid] = CreateDynamicCP(166.0950,1848.0941,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 14:Player.PatrolCP[playerid] = CreateDynamicCP(164.2539,1849.7903,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 15:Player.PatrolCP[playerid] = CreateDynamicCP(165.9684,1851.6871,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 16:Player.PatrolCP[playerid] = CreateDynamicCP(169.5328,1849.1542,33.4987, 0.5, 0, 0, playerid, 60000.000, .priority = 2), IncreaseStatus(playerid,RandomEx(1,5)), AddPlayerAchievement(playerid, E_SOLDIER_SLEEPING);

		case 17:Player.PatrolCP[playerid] = CreateDynamicCP(262.3283,1805.7856,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 18:Player.PatrolCP[playerid] = CreateDynamicCP(260.3836,1807.2378,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 19:Player.PatrolCP[playerid] = CreateDynamicCP(262.0783,1809.3845,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 20:Player.PatrolCP[playerid] = CreateDynamicCP(265.6458,1806.8669,33.4989, 0.5, 0, 0, playerid, 60000.000, .priority = 2), IncreaseStatus(playerid,RandomEx(1,5)), AddPlayerAchievement(playerid, E_SOLDIER_SLEEPING);

		case 21:Player.PatrolCP[playerid] = CreateDynamicCP(267.3655,1893.4131,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 22:Player.PatrolCP[playerid] = CreateDynamicCP(265.3108,1895.1185,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 23:Player.PatrolCP[playerid] = CreateDynamicCP(267.0774,1896.9723,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 24:Player.PatrolCP[playerid] = CreateDynamicCP(270.6409,1894.4889,33.4989, 0.5, 0, 0, playerid, 60000.000, .priority = 2), IncreaseStatus(playerid,RandomEx(1,5)), AddPlayerAchievement(playerid, E_SOLDIER_SLEEPING);

		case 25:Player.PatrolCP[playerid] = CreateDynamicCP(233.8169,1932.9153,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 26:Player.PatrolCP[playerid] = CreateDynamicCP(231.7041,1934.7461,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 27:Player.PatrolCP[playerid] = CreateDynamicCP(233.2229,1936.5203,33.8984, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 28:Player.PatrolCP[playerid] = CreateDynamicCP(237.0311,1934.0801,33.4992, 0.5, 0, 0, playerid, 60000.000, .priority = 2), IncreaseStatus(playerid,RandomEx(1,5)), AddPlayerAchievement(playerid, E_SOLDIER_SLEEPING);

		case 29:Player.PatrolCP[playerid] = CreateDynamicCP(92.5536,1916.6945,17.9983, 1.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 30:Player.PatrolCP[playerid] = CreateDynamicCP(103.9860,1929.7076,18.4321, 1.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 31:Player.PatrolCP[playerid] = CreateDynamicCP(93.1961,1924.8977,18.0405, 1.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 32:Player.PatrolCP[playerid] = CreateDynamicCP(103.3832,1913.4237,18.4054, 1.5, 0, 0, playerid, 60000.000, .priority = 2), IncreaseStatus(playerid,RandomEx(1,5)), AddPlayerAchievement(playerid, E_SOLDIER_SLEEPING);

		case 33:Player.PatrolCP[playerid] = CreateDynamicCP(338.1339,1796.4677,18.0828, 1.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 34:Player.PatrolCP[playerid] = CreateDynamicCP(328.7558,1801.5684,17.8348, 1.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 35:Player.PatrolCP[playerid] = CreateDynamicCP(349.4514,1803.4324,18.5533, 1.5, 0, 0, playerid, 60000.000, .priority = 2);
		case 36:Player.PatrolCP[playerid] = CreateDynamicCP(347.6863,1815.4681,18.1154, 1.5, 0, 0, playerid, 60000.000, .priority = 2), IncreaseStatus(playerid,RandomEx(1,5)), AddPlayerAchievement(playerid, E_SOLDIER_SLEEPING);
	}
	Streamer_Update(playerid, STREAMER_TYPE_CP);
	return 1;
}

stock DeletePatrolCP(playerid) {
	if(Player.PatrolCP[playerid] != INVALID_DYNAMIC_CP) {
	DestroyDynamicCP(Player.PatrolCP[playerid]);
	Player.PatrolCP[playerid] = INVALID_DYNAMIC_CP;
	}
	return 1;
}
stock OnLeavePatrol(playerid, state_patrol = 0) {
	if(player_Patrol[playerid] != -1) {
		if(state_patrol == 1) {
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже на посту. Покиньте его чтобы выбрать другой");
		return 0;
		}
		if(player_Patrol[playerid] == 0) {
			PATROL_TOWER[0] = 0;
		}
		else if(player_Patrol[playerid] == 1) {
			PATROL_TOWER[1] = 0;
		}
		else if(player_Patrol[playerid] == 2) {
			PATROL_TOWER[2] = 0;
		}
		else if(player_Patrol[playerid] == 3) {
			PATROL_TOWER[3] = 0;
		}
		else if(player_Patrol[playerid] == 4) {
			PATROL_TOWER[4] = 0;
		}
		else if(player_Patrol[playerid] == 5) {
			PATROL_TOWER[5] = 0;
		}
		else if(player_Patrol[playerid] == 6) {
			PATROL_TOWER[6] = 0;
		}
		else if(player_Patrol[playerid] == 7) {
			PATROL_TOWER[7] -= 1;
		}
		else if(player_Patrol[playerid] == 8) {
			PATROL_TOWER[8] -= 1;
		}
		SetPVarInt(playerid, "MinusTime", 0);
		player_Patrol[playerid] = -1;
		PatrolTimer[playerid] = KillTimer(PatrolTimer[playerid]);
		DeletePatrolCP(playerid);
		DeletePVar(playerid, "inactive_patrol");
		if(state_patrol == 2) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Вы не начали патруль или уснули на посту. Задание завершено");
		}
		SendClientMessage(playerid, -1, ""COLOR_RED"Вы покинули ваш пост. Патрулирование завершено");
		return 1;
	}
	return 1;
}
CMD:patrol(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "Нельзя использовать в транспорте");
		
	new 
	Fraction:fractionid = GetPlayerFraction(playerid);

	if(fractionid != FRACTION_ARMY) return 1;
	if(GetPlayerJobDayStatus(playerid) == false)
	{
		return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
	}
	
	format(big_string, sizeof(big_string), "Пост\tСтатус\n\
		Вышка 1\t%s\n\
		Вышка 2\t%s\n\
		Вышка 3\t%s\n\
		Вышка 4\t%s\n\
		Вышка 5\t%s\n\
		Вышка 6\t%s\n\
		Вышка 7\t%s\n\
		КПП-1\t"COLOR_GREEN"%i чел.\n\
		КПП-2\t"COLOR_GREEN"%i чел.",
		 	(PATROL_TOWER[0] == 0) ? (""COLOR_GREEN"Свободен") : (""COLOR_RED"Занят"),
		  (PATROL_TOWER[1] == 0) ? (""COLOR_GREEN"Свободен") : (""COLOR_RED"Занят"),
		  (PATROL_TOWER[2] == 0) ? (""COLOR_GREEN"Свободен") : (""COLOR_RED"Занят"),
		  (PATROL_TOWER[3] == 0) ? (""COLOR_GREEN"Свободен") : (""COLOR_RED"Занят"),
		  (PATROL_TOWER[4] == 0) ? (""COLOR_GREEN"Свободен") : (""COLOR_RED"Занят"),
		  (PATROL_TOWER[5] == 0) ? (""COLOR_GREEN"Свободен") : (""COLOR_RED"Занят"),
		  (PATROL_TOWER[6] == 0) ? (""COLOR_GREEN"Свободен") : (""COLOR_RED"Занят"),
		  (PATROL_TOWER[7]),
		  (PATROL_TOWER[8]));

	return SPD(playerid, dTower, DIALOG_STYLE_TABLIST_HEADERS, ""COLOR_BLUE"Выход в патруль", big_string, "Выбор", "Отмена");
}

hook OnPlayerDialogPatrol(const playerid, const e_DIALOG_IDs:dialogid, const response, const listitem, const inputtext[]) {
    if(dialogid == dTower) 
    {
        if(!response)
        {
			return 1;
        }
        if(!strlen(inputtext)) return callcmd::patrol(playerid,"\0");
        else if(strlen(inputtext) < 1) return callcmd::patrol(playerid,"\0");
        else if(strlen(inputtext) > 9) return callcmd::patrol(playerid,"\0");
    	if(response) {
    		if(listitem == 0) {
    			if(OnLeavePatrol(playerid, 1) == 0) return 1;
    			if(PATROL_TOWER[0] > 0) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Пост занят. Выберите другой");
    			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали патруль. Отправляйтесь в место указанное на радаре");
    			SetPVarInt(playerid, "inactive_patrol", 120);
    			Player.PatrolCP[playerid] = CreateDynamicCP(165.4972,1932.1563,33.4981, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
    			Streamer_Update(playerid, STREAMER_TYPE_CP);
    			player_Patrol[playerid] = 0;
			    return PATROL_TOWER[0] = 1;
			}
	    	else if(listitem == 1) {
	    		if(OnLeavePatrol(playerid, 1) == 0) return 1;
	    		if(PATROL_TOWER[1] > 0) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Пост занят. Выберите другой");
    			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали патруль. Отправляйтесь в место указанное на радаре");
    			SetPVarInt(playerid, "inactive_patrol", 120);
    			Player.PatrolCP[playerid] = CreateDynamicCP(107.4883,1900.2822,33.4988, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
    			Streamer_Update(playerid, STREAMER_TYPE_CP);
    			player_Patrol[playerid] = 1;
	        	return PATROL_TOWER[1] = 1;
			}
			else if(listitem == 2) {
				if(OnLeavePatrol(playerid, 1) == 0) return 1;
				if(PATROL_TOWER[2] > 0) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Пост занят. Выберите другой");
    			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали патруль. Отправляйтесь в место указанное на радаре");
    			SetPVarInt(playerid, "inactive_patrol", 120);
    			Player.PatrolCP[playerid] = CreateDynamicCP(116.8958,1813.7156,33.4993, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
    			Streamer_Update(playerid, STREAMER_TYPE_CP);
    			player_Patrol[playerid] = 2;
	        	return PATROL_TOWER[2] = 1;
			}
			else if(listitem == 3) {
				if(OnLeavePatrol(playerid, 1) == 0) return 1;
				if(PATROL_TOWER[3] > 0) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Пост занят. Выберите другой");
    			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали патруль. Отправляйтесь в место указанное на радаре");
    			SetPVarInt(playerid, "inactive_patrol", 120);
    			Player.PatrolCP[playerid] = CreateDynamicCP(169.5328,1849.1542,33.4987, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
    			Streamer_Update(playerid, STREAMER_TYPE_CP);
    			player_Patrol[playerid] = 3;
	        	return PATROL_TOWER[3] = 1;
			}
			else if(listitem == 4) {
				if(OnLeavePatrol(playerid, 1) == 0) return 1;
				if(PATROL_TOWER[4] > 0) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Пост занят. Выберите другой");
    			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали патруль. Отправляйтесь в место указанное на радаре");
    			SetPVarInt(playerid, "inactive_patrol", 120);
    			Player.PatrolCP[playerid] = CreateDynamicCP(265.6458,1806.8669,33.4989, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
    			Streamer_Update(playerid, STREAMER_TYPE_CP);
    			player_Patrol[playerid] = 4;
	        	return PATROL_TOWER[4] = 1;
			}
			else if(listitem == 5) {
				if(OnLeavePatrol(playerid, 1) == 0) return 1;
				if(PATROL_TOWER[5] > 0) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Пост занят. Выберите другой");
    			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали патруль. Отправляйтесь в место указанное на радаре");
    			SetPVarInt(playerid, "inactive_patrol", 120);
    			Player.PatrolCP[playerid] = CreateDynamicCP(270.6409,1894.4889,33.4989, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
    			Streamer_Update(playerid, STREAMER_TYPE_CP);
    			player_Patrol[playerid] = 5;
	        	return PATROL_TOWER[5] = 1;
			}
			else if(listitem == 6) {
				if(OnLeavePatrol(playerid, 1) == 0) return 1;
				if(PATROL_TOWER[6] > 0) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Пост занят. Выберите другой");
    			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали патруль. Отправляйтесь в место указанное на радаре");
    			SetPVarInt(playerid, "inactive_patrol", 120);
    			Player.PatrolCP[playerid] = CreateDynamicCP(237.0311,1934.0801,33.4992, 0.5, 0, 0, playerid, 60000.000, .priority = 2);
    			Streamer_Update(playerid, STREAMER_TYPE_CP);
    			player_Patrol[playerid] = 6;
	        	return PATROL_TOWER[6] = 1;
			}
			else if(listitem == 7) {
				if(OnLeavePatrol(playerid, 1) == 0) return 1;
    			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали патруль. Отправляйтесь в место указанное на радаре");
    			SetPVarInt(playerid, "inactive_patrol", 120);
    			Player.PatrolCP[playerid] = CreateDynamicCP(103.3832,1913.4237,18.4054, 1.5, 0, 0, playerid, 60000.000, .priority = 2);
    			Streamer_Update(playerid, STREAMER_TYPE_CP);
    			player_Patrol[playerid] = 7;
	        	return PATROL_TOWER[7] += 1;
			}
			else if(listitem == 8) {
				if(OnLeavePatrol(playerid, 1) == 0) return 1;
    			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали патруль. Отправляйтесь в место указанное на радаре");
    			SetPVarInt(playerid, "inactive_patrol", 120);
    			Player.PatrolCP[playerid] = CreateDynamicCP(347.6863,1815.4681,18.1154, 1.5, 0, 0, playerid, 60000.000, .priority = 2);
    			Streamer_Update(playerid, STREAMER_TYPE_CP);
    			player_Patrol[playerid] = 8;
	        	return PATROL_TOWER[8] += 1;
			}
    	}
    	return 1;
    }
    return 1;
}
public Patrol_OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid >= PatrolZone[0] && areaid <= PatrolZone[8]) {
			OnLeavePatrol(playerid);
			return 1;
		}
	return 0;
}