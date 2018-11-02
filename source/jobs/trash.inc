#if defined trash_included
	#endinput
#endif

#define trash_included

#if !defined MAX_TRASH_CHECKPOINT
	#error "Not default value defined for MAX_TRASH_CHECKPOINT (trash.inc)"
#endif

#if !defined STREAMER_TYPE_TRASH
	#error "Not default value defined for STREAMER_TYPE_TRASH (trash.inc)"
#endif

forward Trash_OnGameModeInit();
forward Trash_OnPlayerConnect(playerid);
forward Trash_OnPlayerDisconnect(playerid);
forward Trash_OnPlayerSpawn(playerid);
forward Trash_OP_EnterDynamicRaceCP(playerid, checkpointid);
forward OnPlayerEnterTrash(playerid);
forward PlayerTrashStop(playerid);
forward OnPlayerExitVehicleTrash(playerid);
forward Trash_OnPlayerLeaveJob(playerid);

new 
	player_trash_driver_timer[MAX_PLAYERS],
	player_total_trash_point[MAX_PLAYERS char];

new 
	trash_unload_checkpointid;

enum 
	trash_info__ {
		TI_CheckpointID, 										// ID чекпоинта
		Float: TI_X, 											// Координата X
		Float: TI_Y, 											// Координата Y
		Float: TI_Z, 											// Координата Z
		Float: TI_NextX, 										// Следующая оордината X
		Float: TI_NextY, 										// Следующая оордината Y
		Float: TI_NextZ 										// Следующая оордината Z
	};

static 
	TrashInfo[MAX_TRASH_CHECKPOINT][trash_info__] = {
		{INVALID_DYNAMIC_CP, 1486.4631, -1844.8683, 13.1102, 1486.4631, -1844.8683, 13.1102},
		{INVALID_DYNAMIC_CP, 1426.2567, -1844.0217, 13.1119, 1426.2567, -1844.0217, 13.1119},
		{INVALID_DYNAMIC_CP, 1534.4121, -1448.5444, 13.3828, 1534.4121, -1448.5444, 13.3828},
		{INVALID_DYNAMIC_CP, 1933.9891, -2033.6768, 13.1146, 1933.9891, -2033.6768, 13.1146},
		{INVALID_DYNAMIC_CP, 2381.4141, -1937.1492, 13.1075, 2381.4141, -1937.1492, 13.1075},
		{INVALID_DYNAMIC_CP, 2447.9954, -1977.1823, 13.1186, 2447.9954, -1977.1823, 13.1186},
		{INVALID_DYNAMIC_CP, 2142.8647, -1342.6594, 23.5469, 2142.8647, -1342.6594, 23.5469},
		{INVALID_DYNAMIC_CP, 1653.6006, -1061.9578, 23.4628, 1653.6006, -1061.9578, 23.4628},
		{INVALID_DYNAMIC_CP, 1782.2749, -1114.2012, 23.6585, 1782.2749, -1114.2012, 23.6585},
		{INVALID_DYNAMIC_CP, 1823.9375, -1145.5192, 23.5316, 1823.9375, -1145.5192, 23.5316},
		{INVALID_DYNAMIC_CP, 1144.2090, -1355.0071, 13.2270, 1144.2090, -1355.0071, 13.2270},
		{INVALID_DYNAMIC_CP, 957.0651, -1332.2007, 13.0208, 957.0651, -1332.2007, 13.0208},
		{INVALID_DYNAMIC_CP, 859.3245, -1369.3916, 13.1188, 859.3245, -1369.3916, 13.1188},
		{INVALID_DYNAMIC_CP, 891.5518, -1359.4219, 13.3815, 891.5518, -1359.4219, 13.3815},
		{INVALID_DYNAMIC_CP, -60.3018, -1581.0995, 2.1778, -60.3018, -1581.0995, 2.1778},
		{INVALID_DYNAMIC_CP, 475.6409, -1741.1163, 8.9391, 475.6409, -1741.1163, 8.9391},
		{INVALID_DYNAMIC_CP, 1338.9060, -1828.2147, 13.1248, 1338.9060, -1828.2147, 13.1248},
		{INVALID_DYNAMIC_CP, 1341.1881, -1787.7170, 13.1063, 1341.1881, -1787.7170, 13.1063},
		{INVALID_DYNAMIC_CP, 2445.5261, -1892.5731, 13.1270, 2445.5261, -1892.5731, 13.1270},
		{INVALID_DYNAMIC_CP, 2447.2263, -1976.5076, 13.1194, 2447.2263, -1976.5076, 13.1194}
	};

public Trash_OnGameModeInit() {
	new 	
		streamer_data[2];

	streamer_data[0] = STREAMER_TYPE_TRASH;

	for(new i = 0; i < sizeof(TrashInfo); i++) {
		TrashInfo[i][TI_CheckpointID] = CreateDynamicRaceCP(1, 
			TrashInfo[i][TI_X], TrashInfo[i][TI_Y], TrashInfo[i][TI_Z], 
			TrashInfo[i][TI_NextX], TrashInfo[i][TI_NextY], TrashInfo[i][TI_NextZ], 
			BUS_RACECP_SIZE, .streamdistance = 9000.0000
		);

		streamer_data[1] = i;

		Streamer_SetArrayData(STREAMER_TYPE_RACE_CP, TrashInfo[i][TI_CheckpointID], E_STREAMER_EXTRA_ID, streamer_data, 2);
	}

	trash_unload_checkpointid = CreateDynamicRaceCP(1, 2199.5505, -2035.3813, 13.1105, 2199.5505, -2035.3813, 13.1105, BUS_RACECP_SIZE, .streamdistance = 9000.0000);
}

public Trash_OnPlayerConnect(playerid) {
	player_trash_driver_timer[playerid] = KillTimer(player_trash_driver_timer[playerid]);
	ResetPlayerTrashCount(playerid);
	return HideAllTrashPointForPlayer(playerid);
}

public Trash_OnPlayerDisconnect(playerid) {
	player_trash_driver_timer[playerid] = KillTimer(player_trash_driver_timer[playerid]);
	ResetPlayerTrashCount(playerid);
	return HideAllTrashPointForPlayer(playerid);
}

public Trash_OnPlayerSpawn(playerid) {
	player_trash_driver_timer[playerid] = KillTimer(player_trash_driver_timer[playerid]);
	ResetPlayerTrashCount(playerid);
	return HideAllTrashPointForPlayer(playerid);
}

public OnPlayerEnterTrash(playerid) {
	SetPlayerJob(playerid, JOB_TRASH);
	TogglePlayerDynamicRaceCP(playerid, TrashInfo[random(MAX_TRASH_CHECKPOINT)][TI_CheckpointID], true);
	return Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
}


public Trash_OP_EnterDynamicRaceCP(playerid, checkpointid) {
	new 
		streamer_data[2];

	Streamer_GetArrayData(STREAMER_TYPE_RACE_CP, checkpointid, E_STREAMER_EXTRA_ID, streamer_data, 2);

	if(streamer_data[0] == STREAMER_TYPE_TRASH) {
		TogglePlayerDynamicRaceCP(playerid, checkpointid, false);
		Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);

		TogglePlayerControllable(playerid, false);
		SendClientMessage(playerid, -1, ""COLOR_RED"Происходит загрузка мусора в кузов автомобиля. Подождите 10 секунд");
		SetPVarInt(playerid, "MinusTime", 10);
		player_trash_driver_timer[playerid] = SetTimerEx("PlayerTrashStop", 10_000, false, !"i", playerid);	
		return 1;
	} else if(checkpointid == trash_unload_checkpointid) {
		TogglePlayerDynamicRaceCP(playerid, trash_unload_checkpointid, false);
		Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);

		if(GetPlayerTrashCount(playerid) >= 5) {
			new pay = RandomEx(80, 115);
		  	AddPlayerEXP(playerid, pay);
		  	Player.AddEXP(PlayerInfo[playerid][pID], pay, E_JOB_DRIVER_TRASH, playerid);
		  	SendClientMessage(playerid, -1, ""COLOR_BLUE"Мусоровоз разгружен.");
		  	va_SendClientMessage(playerid, -1, ""COLOR_GREEN"Рабочий день завершен. Ваша зарплата: {FFFFFF}+%d EXP", pay);
			
			SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			ResetPlayerTrashCount(playerid);
			ResetPlayerJob(playerid);
			return 1;
		} else {
			TogglePlayerDynamicRaceCP(playerid, TrashInfo[random(MAX_TRASH_CHECKPOINT)][TI_CheckpointID], true);
			Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
			return 1;
		}
	}
	return 0;
}

public PlayerTrashStop(playerid) {
	HideAllTrashPointForPlayer(playerid);

	new 
		total_trash_count = AddPlayerTrashCount(playerid);

	if(GetPlayerTrashCount(playerid) >= 5) {
		TogglePlayerDynamicRaceCP(playerid, trash_unload_checkpointid, true);
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Кузов автомобиля полон. Отправляйтесь на разгрузку");
	} else {
		TogglePlayerDynamicRaceCP(playerid, TrashInfo[random(MAX_TRASH_CHECKPOINT)][TI_CheckpointID], true);
		va_SendClientMessage(playerid, -1, ""COLOR_ORANGE"Загружено: %i/5. Отправляйтесь на следующее место", total_trash_count);
	}
	TogglePlayerControllable(playerid, true);
	return Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
}

public OnPlayerExitVehicleTrash(playerid) {
	HideAllTrashPointForPlayer(playerid);
	return Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
}

public Trash_OnPlayerLeaveJob(playerid) {
	ResetPlayerTrashCount(playerid);
	HideAllTrashPointForPlayer(playerid);
	player_trash_driver_timer[playerid] = KillTimer(player_trash_driver_timer[playerid]);
}
/**
 * [HideAllTrashPointForPlayer скрывает все чекпоинты для игрока]
 * @param {int} playerid [ID Игрока]
 */
stock HideAllTrashPointForPlayer(playerid) {
	for(new i = 0; i < sizeof(TrashInfo); i++) {
		if(IsValidDynamicRaceCP(TrashInfo[i][TI_CheckpointID])) {
			TogglePlayerDynamicRaceCP(playerid, TrashInfo[i][TI_CheckpointID], false);
		}
	}

	if(IsValidDynamicRaceCP(trash_unload_checkpointid)) {
		TogglePlayerDynamicRaceCP(playerid, trash_unload_checkpointid, false);
	}
	return Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
}

stock AddPlayerTrashCount(playerid) {
	return player_total_trash_point{playerid} = player_total_trash_point{playerid} + 1;
}

stock GetPlayerTrashCount(playerid) {
	return player_total_trash_point{playerid};
}

stock ResetPlayerTrashCount(playerid) {
	return player_total_trash_point{playerid} = 0;
}