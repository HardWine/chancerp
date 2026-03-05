#if defined army_plant_included
	#endinput
#endif

#define army_plant_included

forward Army_OnGameModeInit();
forward Army_OnPlayerConnect(playerid);
forward Army_OnPlayerDisconnect(playerid, reason);
forward Army_OP_PickUpDynamicPickup(playerid, pickupid);
forward Army_OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid);
forward	JobPlant(playerid, tableid);

#if !defined INVALID_DYNAMIC_CP
	#define INVALID_DYNAMIC_CP 					(-1)
#endif

#define MAX_ARMY_PLANT 							(10)
#define STREAMER_TYPE_ARMY_PLANT 				(227)

new 
	army_pickup[4],
	army_warehouse,
	army_zone,
	PlayerArmyJonPlant[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};

enum 
	army_plant__ {
		AP_ID,
		Float: AP_Table_X,
		Float: AP_Table_Y,
		Float: AP_Table_Z,
		Float: AP_Table_Angle,
		AP_Table_World,
		AP_Table_Inter,
		AP_Table_PlayerID,
		AP_Table_Checkpoint,
		Float: AP_Gun_X,
		Float: AP_Gun_Y,
		Float: AP_Gun_Z,
		Float: AP_Gun_RX,
		Float: AP_Gun_RY,
		Float: AP_Gun_RZ,
		AP_Gun_ObjectID
	};

new 
	ArmyPlant[MAX_ARMY_PLANT][army_plant__] = {
		{0, 2541.9768, -1295.8505, 1044.1250, 0.0000, -1, 2, INVALID_PLAYER_ID, INVALID_DYNAMIC_CP,
			2541.8195, -1295.1600, 1044.1152, -90.0000, 0.0000, 0.0000, INVALID_OBJECT_ID
		},
		{1, 2544.3972, -1295.8499, 1044.1250, 0.0000, -1, 2, INVALID_PLAYER_ID, INVALID_DYNAMIC_CP,
			2544.1975, -1295.1600, 1044.1250, -90.0000, 0.0000, 0.0000, INVALID_OBJECT_ID
		},
		{2, 2553.8723, -1295.8511, 1044.1250, 0.0000, -1, 2, INVALID_PLAYER_ID, INVALID_DYNAMIC_CP,
			2553.6145, -1295.1600, 1044.1250, -90.0000, 0.0000, 0.0000, INVALID_OBJECT_ID
		},
		{3, 2556.1526, -1295.8514, 1044.1250, 0.0000, -1, 2, INVALID_PLAYER_ID, INVALID_DYNAMIC_CP,
			2555.9794, -1295.1600, 1044.1250, -90.0000, 0.0000, 0.0000, INVALID_OBJECT_ID
		},
		{4, 2558.5598, -1295.8497, 1044.1250, 0.0000, -1, 2, INVALID_PLAYER_ID, INVALID_DYNAMIC_CP,
			2558.3249, -1295.1600, 1044.1250, -90.0000, 0.0000, 0.0000, INVALID_OBJECT_ID
		},
		{5, 2558.5247, -1291.0040, 1044.1250, 180.0000, -1, 2, INVALID_PLAYER_ID, INVALID_DYNAMIC_CP,
			2558.3249, -1291.7012, 1044.1250, 90.0000, 0.0000, 0.0000, INVALID_OBJECT_ID
		},
		{6, 2556.1226, -1291.0050, 1044.1250, 180.0000,-1, 2, INVALID_PLAYER_ID, INVALID_DYNAMIC_CP,
			2555.9794, -1291.7012, 1044.1250, 90.0000, 0.0000, 0.0000, INVALID_OBJECT_ID
		},
		{7, 2553.7849, -1291.0031, 1044.1250, 180.0000,-1, 2, INVALID_PLAYER_ID, INVALID_DYNAMIC_CP,
			2553.6145, -1291.7012, 1044.1250, 90.0000, 0.0000, 0.0000, INVALID_OBJECT_ID
		},
		{8, 2544.3049, -1291.0031, 1044.1250, 180.0000,-1, 2, INVALID_PLAYER_ID, INVALID_DYNAMIC_CP,
			2544.1975, -1291.7012, 1044.1250, 90.0000, 0.0000, 0.0000, INVALID_OBJECT_ID
		},
		{9, 2541.9966, -1291.0057, 1044.1250, 180.0000,-1, 2, INVALID_PLAYER_ID, INVALID_DYNAMIC_CP,
			2541.8195, -1291.7012, 1044.1250, 90.0000, 0.0000, 0.0000, INVALID_OBJECT_ID
		}
	};

public Army_OnGameModeInit() {
	//new 
		//data[2];

	//data[0] = STREAMER_TYPE_ARMY_PLANT;

	for(new i = 0; i < sizeof(ArmyPlant); i++) {
		ArmyPlant[i][AP_Table_Checkpoint] = CreateDynamicPickup(2061, 23, 
			ArmyPlant[i][AP_Table_X], ArmyPlant[i][AP_Table_Y], ArmyPlant[i][AP_Table_Z]);

		//data[1] = i;
		//Streamer_SetArrayData(STREAMER_TYPE_PICKUP, ArmyPlant[i][AP_Table_Checkpoint], E_STREAMER_EXTRA_ID, data, 2);

		ArmyPlant[i][AP_Gun_ObjectID] = CreateDynamicObject(1654, 
			ArmyPlant[i][AP_Gun_X], ArmyPlant[i][AP_Gun_Y], ArmyPlant[i][AP_Gun_Z] - 10.00, 
			ArmyPlant[i][AP_Gun_RX], ArmyPlant[i][AP_Gun_RY], ArmyPlant[i][AP_Gun_RZ], 
			ArmyPlant[i][AP_Table_World], ArmyPlant[i][AP_Table_Inter]
		);
	}

	CreateDynamicMapIcon(340.5771, 1949.2246, 22.0171, 
		6, -1, 
		0, 0
	);
	
	army_warehouse = CreateDynamicPickup(1279, 1, 2564.1118, -1292.9135, 1044.1250);
	army_zone = CreateDynamicCuboid(2530.1396, -1309.6229, 1042.4398, 
		2571.2827, -1279.7139, 1053.7505, -1, 2
	);

	army_pickup[0] = CreateDynamicPickup(1318, 1, 340.5771, 1949.2246, 22.0171);
	CreateDynamic3DTextLabel(""COLOR_BLUE"Производственный цех", -1, 
		340.5771, 1949.2246, 22.0171 + 0.9, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);

	army_pickup[1] = CreateDynamicPickup(1318, 1, 2531.3218, -1281.9708, 1048.2891);
	CreateDynamic3DTextLabel(""COLOR_BLUE"Выход", -1, 
		2531.3218, -1281.9708, 1048.2891 + 0.9, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 2
	);

	army_pickup[2] = CreateDynamicPickup(1239, 1, 2538.3184, -1293.5227, 1044.1250);
	CreateDynamic3DTextLabel(""COLOR_BLUE"Информация о работе", -1, 
		2538.3184, -1293.5227, 1044.1250 + 0.9, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 2
	);

	army_pickup[3] = CreateDynamicPickup(1275, 1, 2532.7905, -1305.8507, 1044.1250);
	CreateDynamic3DTextLabel(""COLOR_BLUE"Раздевалка", -1, 
		2532.7905, -1305.8507, 1044.1250 + 0.9, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 2
	);

	// Завод
	CreateDynamicObject(13028, 2571.173828, -1301.873291, 1044.321655, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(13028, 2530.964599, -1305.700317, 1049.406616, 0.000000, 0.000000, -179.300094, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3066, 2569.875000, -1299.706176, 1044.215332, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(14792, 2528.531738, -1296.824462, 1044.494628, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3016, 2558.885498, -1286.539306, 1044.225097, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(2359, 2559.252441, -1301.512329, 1044.286132, 0.000000, 0.000000, -178.400070, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(2359, 2559.458984, -1285.998779, 1044.295654, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(2359, 2543.488525, -1286.009521, 1044.295654, 0.000000, 0.000000, -14.799994, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3016, 2550.862548, -1286.539306, 1044.225097, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3016, 2551.333007, -1286.539306, 1044.225097, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3016, 2551.112792, -1300.959350, 1044.225097, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3016, 2559.087158, -1300.959350, 1044.225097, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3016, 2543.228515, -1300.959350, 1044.225097, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3016, 2542.858154, -1300.959350, 1044.225097, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3016, 2542.917480, -1286.459228, 1044.225097, 0.000000, 0.000000, 3.299998, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(370, 2526.696289, -1289.299560, 1048.444702, 0.000000, 0.000000, 145.800003, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3014, 2565.642089, -1292.629394, 1044.342163, -91.799995, 0.000000, 107.500015, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1583, 2553.227294, -1293.347534, 1045.224487, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1242, 2565.459228, -1293.692626, 1044.285156, -7.699976, -0.300007, -0.199999, -1, -1, -1, 300.00, 300.00); 
}

public Army_OnPlayerConnect(playerid) {
	PlayerArmyJonPlant[playerid] = INVALID_TIMER_ID;
}

public Army_OnPlayerDisconnect(playerid, reason) {
	for(new i = 0; i < sizeof(ArmyPlant); i++) {
		if(ArmyPlant[i][AP_Table_PlayerID] == playerid) {
			ArmyPlant[i][AP_Table_PlayerID] = INVALID_PLAYER_ID;

			if(IsValidDynamicObject(ArmyPlant[i][AP_Gun_ObjectID])) {
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, ArmyPlant[i][AP_Gun_ObjectID], E_STREAMER_Z, 1034.1250);
			}
			break;
		}
	}
	PlayerArmyJonPlant[playerid] = KillTimer(PlayerArmyJonPlant[playerid]);
}

public Army_OP_PickUpDynamicPickup(playerid, pickupid) {
	// new 
	// 	streamer_data[2];

	// Streamer_GetArrayData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_EXTRA_ID, streamer_data, 2);

	// format(small_string, sizeof(small_string), "%i %i", streamer_data[0], streamer_data[1]);
	// SendClientMessage(playerid, -1, small_string);
	
	// if(streamer_data[0] == STREAMER_TYPE_ARMY_PLANT) {
	// 	new 
	// 		arrayid = streamer_data[1];

	// 	if(ArmyPlant[arrayid][AP_Table_PlayerID] != INVALID_PLAYER_ID) {
	// 		return SendClientMessage(playerid, -1, ""COLOR_RED"Этот столик занят другим игроком.");
	// 	}

	// 	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, ArmyPlant[arrayid][AP_Gun_ObjectID], E_STREAMER_Z, 1044.1250);

	// 	ArmyPlant[arrayid][AP_Table_PlayerID] = playerid;

	// 	SetPlayerPos(playerid, ArmyPlant[arrayid][AP_Table_X], ArmyPlant[arrayid][AP_Table_Y], ArmyPlant[arrayid][AP_Table_Z]);
	// 	SetPlayerFacingAngle(playerid, ArmyPlant[arrayid][AP_Table_Angle]);
	// 	SetCameraBehindPlayer(playerid);

	// 	TogglePlayerControllable(playerid, false);
	// 	ApplyAnimation(playerid, "OTB", "BETSLP_LOOP", 10.1, 1, 1, 1, 1, 0);

	// 	PlayerArmyJonPlant[playerid] = SetTimerEx("JobPlant", 10_000, false, "ii", playerid, arrayid);
	// 	GameTextForPlayer(playerid, "~g~~h~WAITING", 10_250, 4);
	// 	return 1;
	// } 

	if(pickupid == army_pickup[0]) {
		SetPlayerPos(playerid, 2533.0698, -1284.5824, 1048.2891);
		SetPlayerFacingAngle(playerid, 180.000);
		SetPlayerInterior(playerid, 2);
		SetCameraBehindPlayer(playerid);
		return 1;
	} else if(pickupid == army_pickup[1]) {
		SetPlayerPos(playerid, 338.3293, 1949.1570, 22.0173);
		SetPlayerFacingAngle(playerid, 90.000);
		SetPlayerInterior(playerid, 0);
		SetCameraBehindPlayer(playerid);
		return 1;
	} else if(pickupid == army_pickup[2]) {
		if(Platform[playerid] == 1) {
			Dialog_Show(playerid, Dialog:DIALOG_ARMY_PLANT_INFO);
			return 1;
		} else {
			SendClientMessage(playerid, -1, ""COLOR_WHITE"На данной работе вам предстоит собирать оружие для военных сил армии штата San Andreas.");
			SendClientMessage(playerid, -1, ""COLOR_WHITE"Вы будете повышать свою законопослушность за каждые 25 перенесенных ящиков");
			return 1;
		}

	} else if(pickupid == army_pickup[3]) {
		if(GetPlayerFraction(playerid) != FRACTION_ARMY) {
			SendClientMessage(playerid, -1, ""COLOR_RED"Подработка доступна только для военных");
			return 1;
		}
		if(PlayerInfo[playerid][pRank] < 3) return SendClientMessage(playerid, -1, ""COLOR_RED"Работа доступна только после достижения 3 ранга");
		if(GetPlayerJobDayStatus(playerid) == false)
		{
			return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
		}
		
		if(GetPVarInt(playerid, "job_army_plant") == 1) {
			if(IsPlayerAttachedObjectSlotUsed(playerid, 3)) {
				RemovePlayerAttachedObject(playerid, 3);
			}
			ClearPlayerAnimation(playerid);
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Рабочий день завершен");
			SetPlayerChatBubble(playerid, 
				(PlayerInfo[playerid][pSex] == 0) ? ("закончил работу") : ("закончила работу"), 
				0x000000AA, MAX_DISTANCE_VISIBLE, 2000
			);
			DeletePVar(playerid, "fix_plant");
			DeletePVar(playerid, "job_army_plant");
			CBackSkin(playerid);
			return 1;
		}
		if(PlayerInfo[playerid][pSex] == 0) {
			switch(random(2)) {
				case 0: SetPlayerSkin(playerid, 73);
				default: SetPlayerSkin(playerid, 179);
			}
		} else {
			SetPlayerSkin(playerid, 191);
		}
		SetPVarInt(playerid, "job_army_plant", 1);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали подработку на военном заводе. Для начала работы, отправляетесь к свободному столу");
		SetPlayerChatBubble(playerid, 
			(PlayerInfo[playerid][pSex] == 0) ? ("начал работу") : ("начала работу"), 
			0x000000AA, MAX_DISTANCE_VISIBLE, 2000
		);
		return 1;
	} else {
		if(GetPVarInt(playerid, "job_army_plant") == 1 && GetPVarInt(playerid, "fix_plant") == 0) {
			for(new i = 0; i < sizeof(ArmyPlant); i++) {
				if(pickupid == ArmyPlant[i][AP_Table_Checkpoint]) {
					new 
						arrayid = i;

					if(ArmyPlant[arrayid][AP_Table_PlayerID] != INVALID_PLAYER_ID) {
						return SendClientMessage(playerid, -1, ""COLOR_RED"Этот столик занят другим игроком");
					}

					Streamer_SetFloatData(STREAMER_TYPE_OBJECT, ArmyPlant[arrayid][AP_Gun_ObjectID], E_STREAMER_Z, 1044.1250);

					ArmyPlant[arrayid][AP_Table_PlayerID] = playerid;

					SetPlayerPos(playerid, ArmyPlant[arrayid][AP_Table_X], ArmyPlant[arrayid][AP_Table_Y], ArmyPlant[arrayid][AP_Table_Z]);
					SetPlayerFacingAngle(playerid, ArmyPlant[arrayid][AP_Table_Angle]);
					SetCameraBehindPlayer(playerid);

					//TogglePlayerControllable(playerid, false);
					ApplyAnimation(playerid, "OTB", "BETSLP_LOOP", 10.1, 1, 1, 1, 1, 0);
					SetPVarInt(playerid, "fix_plant", 1);
					SetPVarInt(playerid, "MinusTime", 10);
					PlayerArmyJonPlant[playerid] = SetTimerEx("JobPlant", 10_000, false, "ii", playerid, arrayid);
					GameTextForPlayer(playerid, "~g~~h~WAITING", 10_250, 4);
					return 1;
				}
			}
		}
		if(GetPVarInt(playerid, "fix_plant") == 2) {
			if(pickupid == army_warehouse) {
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы отнесли готовый продукт на склад");

				AddPlayerAchievement(playerid, E_WEAPON_SUPPLY);
				
				if(IsPlayerAttachedObjectSlotUsed(playerid, 3)) {
					RemovePlayerAttachedObject(playerid, 3);
				}
				ClearPlayerAnimation(playerid);

				new sum = random(3) + 2;
	
				new active_box = GetPVarInt(playerid, "box_army_plant");

				active_box = active_box + 1;

				if(active_box == 25) {
					IncreaseKarma(playerid);
					active_box = 0;
				}
				SetPVarInt(playerid, "box_army_plant", active_box);

				format(small_string, sizeof(small_string), "~g~~h~+%d EXP", sum);
				GameTextForPlayer(playerid, small_string, 1_250, 4);
				DeletePVar(playerid, "fix_plant");
				AddPlayerEXP(playerid, sum, "Работа на военном заводе");

				mysql_format(database, 
					small_string, sizeof(small_string), 
					"UPDATE players SET `ArmyBox`= `ArmyBox` + 1 WHERE ID=%i LIMIT 1", 
						GetPlayerAccountID(playerid)
				);
				mysql_pquery(database, small_string);
				switch(random(3)) {
					case 0: IncreaseStatus(playerid, 1);
					case 1: return 1;
					case 2: return 1;
				}
				return 1;
			}
		}
	}
	return 0;
}

public Army_OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == army_zone) {
		if(GetPVarInt(playerid, "job_army_plant") == 1) {
			if(IsPlayerAttachedObjectSlotUsed(playerid, 3)) {
				RemovePlayerAttachedObject(playerid, 3);
			}
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Рабочий день завершен");
			SetPlayerChatBubble(playerid, 
				(PlayerInfo[playerid][pSex] == 0) ? ("закончил работу") : ("закончила работу"), 
				0x000000AA, MAX_DISTANCE_VISIBLE, 2000
			);
			DeletePVar(playerid, "job_army_plant");
			DeletePVar(playerid, "fix_plant");
			ClearPlayerAnimation(playerid);
			CBackSkin(playerid);
			return 1;
		}
	}
	return 0;
}

DialogCreate:DIALOG_ARMY_PLANT_INFO(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_ARMY_PLANT_INFO, DIALOG_STYLE_MSGBOX,
		!""COLOR_BLUE"Подработка для солдат",
		!""COLOR_WHITE"На данной работе вам предстоит собирать оружие для\nвоенных сил армии штата San Andreas. Вы будете повышать\nсвою законопослушность "COLOR_GREEN"за каждые 25 перенесенных ящиков",
		!"Закрыть", ""
	);
}

public JobPlant(playerid, tableid) {
	if(GetPVarInt(playerid, "job_army_plant") == 0) {
		return 0;
	}
	// plugins crashdetect.so mysql.so pawncmd.so sscanf.so regex.so streamer.so
	if(IsValidDynamicObject(ArmyPlant[tableid][AP_Gun_ObjectID])) {
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, ArmyPlant[tableid][AP_Gun_ObjectID], E_STREAMER_Z, 1034.1250);
	}

	if(ArmyPlant[tableid][AP_Table_PlayerID] != playerid) {
		return 0;
	}

	ArmyPlant[tableid][AP_Table_PlayerID] = INVALID_PLAYER_ID;

	ClearPlayerAnimation(playerid);
	TogglePlayerControllable(playerid, true);

	SendClientMessage(playerid, -1, ""COLOR_GREEN"Отнесите готовый продукт на склад");

	SetPVarInt(playerid, "fix_plant", 2);

	if(!IsPlayerAttachedObjectSlotUsed(playerid, 3)) {
		SetPlayerAttachedObject(playerid, 3, 2969, 1, 0.075578, 0.407083, 0.000000, 1.248928, 97.393852, 359.645050, 1.000000, 1.000000, 1.000000);
	}
	//ApplyAnimation(playerid, !"CARRY", !"crry_prtial", 4.0, 1, 0, 0, 1, 1, 1);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY); 
	return 1;
}