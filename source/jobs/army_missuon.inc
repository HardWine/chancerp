#if defined army_missuon_included
	#endinput
#endif

#define army_missuon_included

forward AM_OnGameModeInit();
forward AM_OnPlayerConnect(playerid);
forward AM_OnPlayerDisconnect(playerid);
forward OnPlayerEnterArmyMissuon(playerid);
forward AM_OP_EnterDynamicRaceCP(playerid, checkpointid);
forward OnPlayerArmyMissuonLoad(playerid);

enum 
	army_missuon {
		AM_CheckpointID,
		Float: AM_X,
		Float: AM_Y,
		Float: AM_Z,
		Float: AM_NextX,
		Float: AM_NextY,
		Float: AM_NextZ,
		bool: AM_isFly,
		AM_Cash,
		AM_Title[MAX_ARMY_MISSUON_TITLE]
	};

new 
	ArmyMissuon[MAX_ARMY_MISSUON][army_missuon] = {
		{INVALID_DYNAMIC_CP, 1581.5845, -1627.6393, 13.3828, 1581.5845, -1627.6393, 13.3828, false, 1000, "LSPD"},
		{INVALID_DYNAMIC_CP, 1581.5845, -1627.6393, 13.3828, 1581.5845, -1627.6393, 13.3828, true, 1000, "LSPD"},
		{INVALID_DYNAMIC_CP, -2480.2007, 522.8958, 51.0638, -2480.2007, 522.8958, 51.0638, false, 1000, "FBI"},
		{INVALID_DYNAMIC_CP, -2480.2007, 522.8958, 51.0638, -2480.2007, 522.8958, 51.0638, true, 1000, "FBI"},
		{INVALID_DYNAMIC_CP, 1393.2424, -1278.1752, 33.4985, 1393.2424, -1278.1752, 33.4985, false, 1000, "аммунацию"},
		{INVALID_DYNAMIC_CP, 1393.2424, -1278.1752, 33.4985, 1393.2424, -1278.1752, 33.4985, true, 1000, "аммунацию"}
	};

new 
	army_missuon_fly_checkpoint,
	army_missuon_car_checkpoint;

new 
	player_army_missuon_timer[MAX_PLAYERS];

public AM_OnGameModeInit() {
	new 
		streamer_data[2];

	streamer_data[0] = STREAMER_TYPE_ARMY_MISSUON;

	for(new i = 0; i < sizeof(ArmyMissuon); i++) {
		if(ArmyMissuon[i][AM_isFly] == true) {
			ArmyMissuon[i][AM_CheckpointID] = CreateDynamicRaceCP(1, 
				ArmyMissuon[i][AM_X], ArmyMissuon[i][AM_Y], ArmyMissuon[i][AM_Z], 
				ArmyMissuon[i][AM_NextX], ArmyMissuon[i][AM_NextY], ArmyMissuon[i][AM_NextZ], 
				ARMY_MISSUON_FLY_RACECP_SIZE, -1, -1, -1, 4500.000
			);
		} else {
			ArmyMissuon[i][AM_CheckpointID] = CreateDynamicRaceCP(1, 
				ArmyMissuon[i][AM_X], ArmyMissuon[i][AM_Y], ArmyMissuon[i][AM_Z], 
				ArmyMissuon[i][AM_NextX], ArmyMissuon[i][AM_NextY], ArmyMissuon[i][AM_NextZ],
				ARMY_MISSUON_CAR_RACECP_SIZE, -1, -1, -1, 4500.000
			);
		}
		printf("Создали чекпоинт %i", ArmyMissuon[i][AM_CheckpointID]);
	}
	army_missuon_fly_checkpoint = CreateDynamicRaceCP(1, 
		352.7472, 1895.7017, 19.3464, 
		352.7472, 1895.7017, 19.3464, 
		ARMY_MISSUON_FLY_RACECP_SIZE, .streamdistance = 4000.0000
	);

	army_missuon_car_checkpoint = CreateDynamicRaceCP(1, 
		328.5100, 1963.1115, 17.6406, 
		328.5100, 1963.1115, 17.6406,
		ARMY_MISSUON_CAR_RACECP_SIZE, .streamdistance = 9000.0000
	);
}

public AM_OnPlayerConnect(playerid) {
	player_army_missuon_timer[playerid] = KillTimer(player_army_missuon_timer[playerid]);
	return HideAllAM_PointForPlayer(playerid);
}

public AM_OnPlayerDisconnect(playerid) {
	player_army_missuon_timer[playerid] = KillTimer(player_army_missuon_timer[playerid]);
	return HideAllAM_PointForPlayer(playerid);
}

public OnPlayerEnterArmyMissuon(playerid) {
	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали задание по доставке боеприпасов");
	SendClientMessage(playerid, -1, ""COLOR_GREEN"Покинув транспорт, задание будет провалено");
	SendClientMessage(playerid, -1, ""COLOR_GREEN"Отправляйтесь на загрузку боеприпасов");

	SetPlayerJob(playerid, JOB_ARMY_MUSSION);

	if(GetVehicleType(GetPlayerVehicleID(playerid)) == VEHICLE_TYPE_HELICOPTER) {
		TogglePlayerDynamicRaceCP(playerid, army_missuon_fly_checkpoint, true);
	} else {
		TogglePlayerDynamicRaceCP(playerid, army_missuon_car_checkpoint, true);
	}
	return Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
}

public AM_OP_EnterDynamicRaceCP(playerid, checkpointid) {
	new 
		streamer_data[2];

	Streamer_GetArrayData(STREAMER_TYPE_RACE_CP, checkpointid, E_STREAMER_EXTRA_ID, streamer_data, 2);

	if(streamer_data[0] == STREAMER_TYPE_ARMY_MISSUON) {
		TogglePlayerDynamicRaceCP(playerid, checkpointid, false);
		return 1;
	} else if(checkpointid == army_missuon_car_checkpoint) {
		TogglePlayerDynamicRaceCP(playerid, checkpointid, false);
		SendClientMessage(playerid, -1, "Происходит загрузка боеприпасов в кузов автомобиля.");
		SetPVarInt(playerid, "MinusTime", 10);
		player_army_missuon_timer[playerid] = SetTimerEx("OnPlayerArmyMissuonLoad", 10_000, false, "i", playerid);
		return 1;
	} else if(checkpointid == army_missuon_fly_checkpoint) {
		TogglePlayerDynamicRaceCP(playerid, checkpointid, false);
		SendClientMessage(playerid, -1, "Происходит загрузка боеприпасов на борт вертолета.");
		SetPVarInt(playerid, "MinusTime", 10);
		player_army_missuon_timer[playerid] = SetTimerEx("OnPlayerArmyMissuonLoad", 10_000, false, "i", playerid);
		return 1;
	}
	return 0;
}


public OnPlayerArmyMissuonLoad(playerid) {
	new 
		random_iter = random(MAX_ARMY_MISSUON / 2),
		total_iter,
		bool: isFly = false;


	if(GetVehicleType(GetPlayerVehicleID(playerid)) == VEHICLE_CATEGORY_HELICOPTERS) {
		isFly = true;
	} 

	for(new i = 0; i < sizeof(ArmyMissuon); i++) {
		if(ArmyMissuon[i][AM_isFly] == isFly) {
			if(total_iter == random_iter) {
				format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы отправляетесь в %s с военным грузом", ArmyMissuon[i][AM_Title]);
				SendClientMessage(playerid, -1, small_string);

				TogglePlayerDynamicRaceCP(playerid, ArmyMissuon[i][AM_CheckpointID], true);
				break;
			} else {
				total_iter = total_iter + 1;
			}
		}
	}
	return Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
}

stock HideAllAM_PointForPlayer(playerid) {
	printf("sizeof army %i", sizeof(ArmyMissuon));
	for(new i = 0; i < sizeof(ArmyMissuon); i++) {
		if(IsValidDynamicRaceCP(ArmyMissuon[i][AM_CheckpointID])) {
			format(small_string, sizeof(small_string), "Скрываем чекпоинт %i", ArmyMissuon[i][AM_CheckpointID]);
			SendClientMessage(playerid, -1, small_string);
			TogglePlayerDynamicRaceCP(playerid, ArmyMissuon[i][AM_CheckpointID], false);
		}
	}

	if(IsValidDynamicRaceCP(army_missuon_car_checkpoint)) {
		SendClientMessage(playerid, -1, "Valid");
		TogglePlayerDynamicRaceCP(playerid, army_missuon_car_checkpoint, false);
	}
	if(IsValidDynamicRaceCP(army_missuon_fly_checkpoint)) {
		SendClientMessage(playerid, -1, "Valid");
		TogglePlayerDynamicRaceCP(playerid, army_missuon_fly_checkpoint, false);
	}
	return 1;
}

CMD:testcp(playerid, params[]) {
	TogglePlayerDynamicRaceCP(playerid, army_missuon_car_checkpoint, false);
}