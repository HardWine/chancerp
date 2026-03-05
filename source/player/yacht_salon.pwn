#if defined yacht_salon_included
	#endinput
#endif

#define yacht_salon_included

#include <YSI_Coding\y_hooks>

#define INVALID_YACHT						(-1)

enum E_YACHT {
	E_MODEL_ID,
	E_VEHICLE_ID,
	Float: E_X,
	Float: E_Y,
	Float: E_Z,
	Float: E_ANGLE,
	E_PRICE,
	E_INFO[256] // Описание
}

new 
	YachtBuy[6][E_YACHT] = {
		{484, INVALID_VEHICLE_ID, 2251.1000, 536.40002, 0.0000, 180.0000, 400000, "Marquis - огромная яхта, медленно плавает, быстро идет ко дну.\nНа такую яхту точно влезут все Ваши друзья.\n\n"COLOR_GREEN"Максимальная скорость - 35 узлов в час"}, // 53
		{493, INVALID_VEHICLE_ID, 2258.1000, 539.40002, 0.0000, 180.0000, 250000, "Jetmax - модный дизайн, идеальное водное обтекание.\nСтатная лодка среднего класса\n\n"COLOR_GREEN"Максимальная скорость - 89 узлов в час"}, // 89
		{453, INVALID_VEHICLE_ID, 2265.1000, 537.70001, 0.0000, 180.0000, 350000, "Reefer - компактная яхта. Скажите друзьям что вы успешны.\nИ может быть они в это поверят. (но это не точно)\n\n"COLOR_GREEN"Максимальная скорость - 53 узла в час"}, // 35
		{454, INVALID_VEHICLE_ID, 2272.1000, 538.50000, 0.0000, 180.0000, 500000, "Tropic - шикарная яхта. Отлично подойдет для ценителей водных красот.\nС такой яхтой не страшно уйти в закат.\n\n"COLOR_GREEN"Максимальная скорость - 73 узла в час"}, // 73
		{452, INVALID_VEHICLE_ID, 2279.1000, 539.29999, 0.0000, 180.0000, 225000, "Speeder - бюджетный катер.\nСочитает в себе идеальную управляемость и оптимальную скорость.\n\n"COLOR_GREEN"Максимальная скорость - 83 узла в час"}, // 83
		{446, INVALID_VEHICLE_ID, 2286.1000, 539.29999, 0.0000, 180.0000, 295000, "Squalo - скоростная лодка \"премиум класса\"\nТы знаешь, у кого самая быстрая лодка на восточном побережье?\n\n"COLOR_GREEN"Максимальная скорость - 99 узлов в час"} // 99
	};

new 
	PC_YachtBuy,
	PC_YachtManager,
	PC_YachtSpawn[2];

new 
	Area_YachtBuy,
	Area_YachtManager,
	Area_YachtSpawn[2];

new 
	PlayerYachtModel[MAX_PLAYERS] = {INVALID_YACHT, ...},
	PlayerYachtVehicleID[MAX_PLAYERS] = {INVALID_VEHICLE_ID, ...},
	PlayerYachtColor[MAX_PLAYERS] = {1, ...},
	PlayerSellYachtTime[MAX_PLAYERS] = {-1, ...},
	PlayerCPSpawnYacht[MAX_PLAYERS] = -1;

hook OnGameModeInit() {

	// Los Santor Pier

	CreateObject(3406,135.5800000,-1861.2000000,-2.0000000,0.0000000,0.0000000,359.0000000); //object(cxref_woodjetty) (1)
	CreateObject(10245,138.3000000,-1862.3000000,-1.3360000,0.0000000,0.0000000,44.0000000); //object(ottos_ramp) (1)
	CreateObject(3406,135.5800000,-1863.2000000,-2.0000000,0.0000000,0.0000000,359.0000000); //object(cxref_woodjetty) (2)
	CreateObject(3406,126.8000000,-1863.0500000,-2.0000000,0.0000000,0.0000000,359.0000000); //object(cxref_woodjetty) (4)
	CreateObject(3406,126.8200000,-1861.1200000,-2.0000000,0.0000000,0.0000000,0.0000000); //object(cxref_woodjetty) (5)
	CreateObject(3406,138.4800000,-1855.3500000,-2.0000000,0.0000000,0.0000000,90.0000000); //object(cxref_woodjetty) (6)
	CreateObject(3406,130.7000000,-1855.3500000,-2.0000000,0.0000000,0.0000000,90.0000000); //object(cxref_woodjetty) (8)
	CreateObject(3406,122.8900000,-1855.3500000,-2.0000000,0.0000000,0.0000000,90.0000000); //object(cxref_woodjetty) (9)
	CreateObject(3406,122.8700000,-1868.9000000,-2.0000000,0.0000000,0.0000000,270.0000000); //object(cxref_woodjetty) (10)
	CreateObject(3406,129.6499900,-1868.9000000,-2.0000000,0.0000000,0.0000000,270.0000000); //object(cxref_woodjetty) (11)
	CreateObject(3406,131.6499900,-1868.9000000,-2.0000000,0.0000000,0.0000000,270.0000000); //object(cxref_woodjetty) (12)
	CreateObject(3406,138.4500000,-1868.9000000,-2.0000000,0.0000000,0.0000000,270.0000000); //object(cxref_woodjetty) (13)
	CreateObject(5153,149.4650000,-1862.8500000,2.3455000,0.0000000,0.0000000,180.0000000); //object(stuntramp7_las2) (1)
	CreateObject(5153,149.4600100,-1861.5900000,2.3500000,0.0000000,0.0000000,180.0000000); //object(stuntramp7_las2) (2)

	// 

	CreateDynamicMapIcon(2288.3254, 539.4296, 1.7944, 9, -1, 0, 0, -1, 100.0);

	for(new i = 0; i < sizeof(YachtBuy); i++) {
		new c1 = RandomEx(0,4);
		if(c1 == 4) c1 = 16;
		YachtBuy[i][E_VEHICLE_ID] = AddStaticVehicle(YachtBuy[i][E_MODEL_ID], YachtBuy[i][E_X], YachtBuy[i][E_Y], YachtBuy[i][E_Z], YachtBuy[i][E_ANGLE], c1, 1);
	}

	new actor = CreateActor(58, 2288.3254, 537.4296, 1.7944, 270.00);
	ApplyActorAnimation(actor, "COP_AMBIENT","coplook_loop",4.1, 1, 0, 0, 0, 0);
	
	PC_YachtBuy = CreateDynamicPickup(1239, 1, 2290.0000, 539.4296, 1.7944);
	Area_YachtBuy = CreateDynamicSphere(2290.0000, 539.4296, 1.7944, 1.00);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Покупка яхты", -1, 2290.0000, 539.4296, 1.7944 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	PC_YachtManager = CreateDynamicPickup(1276, 1, 2290.0000, 537.4296, 1.7944);
	Area_YachtManager = CreateDynamicSphere(2290.0000, 537.4296, 1.7944, 1.00);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Управление личным водным транспортом\n"COLOR_ORANGE"(покраска, продажа)", -1, 2290.0000, 537.4296, 1.7944 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	PC_YachtSpawn[0] = CreateDynamicPickup(1239, 1, 2290.0000, 535.4296, 1.7944);
	Area_YachtSpawn[0] = CreateDynamicSphere(2290.0000, 535.4296, 1.7944, 1.00);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Спавн личного водного транспорта", -1, 2290.0000, 535.4296, 1.7944 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	PC_YachtSpawn[1] = CreateDynamicPickup(1239, 1, 148.0847,-1864.7312,3.7734);
	Area_YachtSpawn[1] = CreateDynamicSphere(148.0847,-1864.7312,3.7734, 1.00);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Спавн личного водного транспорта", -1, 148.0847,-1864.7312,3.7734 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

}

hook OnPlayerConnect(playerid) {

	// Los Santos Pier

	RemoveBuildingForPlayer(playerid, 1231, 154.66417, -1799.6652, 3.93898, 200.0); //StreetLamp on Pier
	RemoveBuildingForPlayer(playerid, 1231, 154.69829, -1839.199, 3.34166, 200.0); //StreetLamp on Pier
	RemoveBuildingForPlayer(playerid, 1231, 154.54057, -1887.2585, 3.97951, 200.0); //StreetLamp on Pier

	//




	for(new i = 0; i < sizeof(YachtBuy); i++) {
		if(YachtBuy[i][E_VEHICLE_ID] != INVALID_VEHICLE_ID && IsValidVehicle(YachtBuy[i][E_VEHICLE_ID])) {
			SetVehicleParamsForPlayerEx(YachtBuy[i][E_VEHICLE_ID], playerid, 0, 1);
		}
	}

	PlayerYachtModel[playerid] = INVALID_YACHT;
	PlayerYachtVehicleID[playerid] = INVALID_VEHICLE_ID;
	PlayerYachtColor[playerid] = 1;
	PlayerSellYachtTime[playerid] = -1;
	PlayerCPSpawnYacht[playerid] = -1;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason

	PlayerYachtModel[playerid] = INVALID_YACHT;
	if(PlayerYachtVehicleID[playerid] != INVALID_VEHICLE_ID && IsValidVehicle(PlayerYachtVehicleID[playerid])) {
		DestroyVehicle(PlayerYachtVehicleID[playerid]);
	}
	PlayerYachtVehicleID[playerid] = INVALID_VEHICLE_ID;
	PlayerYachtColor[playerid] = 1;
	PlayerSellYachtTime[playerid] = -1;

	if(PlayerCPSpawnYacht[playerid] != -1 && IsValidDynamicCP(PlayerCPSpawnYacht[playerid])) {
		DestroyDynamicCP(PlayerCPSpawnYacht[playerid]);
		PlayerCPSpawnYacht[playerid] = -1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
	for(new i = 0; i < sizeof(YachtBuy); i++) {
		if(vehicleid == YachtBuy[i][E_VEHICLE_ID] && YachtBuy[i][E_VEHICLE_ID] != INVALID_VEHICLE_ID) {
			// Kick(playerid);
			RemovePlayerFromVehicle(playerid);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid) {
	if(pickupid == PC_YachtBuy) {
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(pickupid == PC_YachtSpawn[0] || pickupid == PC_YachtSpawn[1]) {
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(pickupid == PC_YachtManager) {
		return Y_HOOKS_BREAK_RETURN_1;
	} 
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == Area_YachtBuy) {
		if(PlayerYachtModel[playerid] != INVALID_YACHT) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас уже есть личный водный транспорт");
		}
		SetPVarInt(playerid, "buy_mode_yacht", 1);
		TogglePlayerSpectating(playerid, true);

		SendClientMessage(playerid, -1, ""COLOR_GREEN"Владея водным транспортом, вы сможете вызвать его из любого места");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Необходимо лишь находиться в воде и ввести команду:{FFFFFF} /boat");

		ViewYacht(playerid);
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(areaid == Area_YachtSpawn[0]) {
		new 
			model = PlayerYachtModel[playerid];

		if(model == INVALID_YACHT) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет личного водного транспорта");
		}
		if(PlayerYachtVehicleID[playerid] != INVALID_VEHICLE_ID) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Ваш водный транспорт уже заспавнен");
		}

		switch(random(5)) {
			case 0: {
				PlayerCPSpawnYacht[playerid] = CreateDynamicCP(2306.8850, 538.2294, 0.000, 4.00, 0, 0, playerid);
				PlayerYachtVehicleID[playerid] = CreateVehicle(model, 2306.8850, 538.2294, 0.000, 180.00, 1, 1, 86400);
			}
			case 1: {
				PlayerCPSpawnYacht[playerid] = CreateDynamicCP(2316.8730, 538.0933, 0.000, 4.00, 0, 0, playerid);
				PlayerYachtVehicleID[playerid] = CreateVehicle(model, 2316.8730, 538.0933, 0.000, 180.00, 1, 1, 86400);
			}
			case 2: {
				PlayerCPSpawnYacht[playerid] = CreateDynamicCP(2327.7261, 537.8954, 0.000, 4.00, 0, 0, playerid);
				PlayerYachtVehicleID[playerid] = CreateVehicle(model, 2327.7261, 537.8954, 0.000, 180.00, 1, 1, 86400);
			}
			case 3: {
				PlayerCPSpawnYacht[playerid] = CreateDynamicCP(2335.8489, 537.7474, 0.000, 4.00, 0, 0, playerid);
				PlayerYachtVehicleID[playerid] = CreateVehicle(model, 2335.8489, 537.7474, 0.000, 180.00, 1, 1, 86400);
			}
			case 4: {
				PlayerCPSpawnYacht[playerid] = CreateDynamicCP(2344.6897, 537.5859, 0.000, 4.00, 0, 0, playerid);
				PlayerYachtVehicleID[playerid] = CreateVehicle(model, 2344.6897, 537.5859, 0.000, 180.00, 1, 1, 86400);
			}
		}
		Streamer_Update(playerid, STREAMER_TYPE_CP);
		ChangeVehicleColor(PlayerYachtVehicleID[playerid], PlayerYachtColor[playerid], 1);
		SetVehicleParamsForPlayerEx(PlayerYachtVehicleID[playerid], playerid, 0, 1);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Личный водный транспорт заспавнен");
		SetPVarInt(playerid, "yacht_cam_mode", 1);
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(areaid == Area_YachtSpawn[1]) {
		new 
			model = PlayerYachtModel[playerid];

		if(model == INVALID_YACHT) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет личного водного транспорта");
		}
		if(PlayerYachtVehicleID[playerid] != INVALID_VEHICLE_ID) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Ваш водный транспорт уже заспавнен");
		}

		switch(random(4)) {
			case 0: {
				PlayerCPSpawnYacht[playerid] = CreateDynamicCP(134.6499900,-1855.0000000,0.5000000, 4.00, 0, 0, playerid);
				PlayerYachtVehicleID[playerid] = CreateVehicle(model, 134.6499900,-1855.0000000,0.5000000,0.0000000, 1, 1, 86400);
			}
			case 1: {
				PlayerCPSpawnYacht[playerid] = CreateDynamicCP(135.1000100,-1869.0000000,0.0000000, 4.00, 0, 0, playerid);
				PlayerYachtVehicleID[playerid] = CreateVehicle(model, 135.1000100,-1869.0000000,0.0000000,180.0000000, 1, 1, 86400);
			}
			case 2: {
				PlayerCPSpawnYacht[playerid] = CreateDynamicCP(126.9000000,-1854.5000000,0.5000000, 4.00, 0, 0, playerid);
				PlayerYachtVehicleID[playerid] = CreateVehicle(model, 126.9000000,-1854.5000000,0.5000000, 0.00, 1, 1, 86400);
			}
			case 3: {
				PlayerCPSpawnYacht[playerid] = CreateDynamicCP(126.2500000,-1868.5000000,0.0000000, 4.00, 0, 0, playerid);
				PlayerYachtVehicleID[playerid] = CreateVehicle(model, 126.2500000,-1868.5000000,0.0000000, 180.00, 1, 1, 86400);
			}
		}
		Streamer_Update(playerid, STREAMER_TYPE_CP);
		ChangeVehicleColor(PlayerYachtVehicleID[playerid], PlayerYachtColor[playerid], 1);
		SetVehicleParamsForPlayerEx(PlayerYachtVehicleID[playerid], playerid, 0, 1);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Личный водный транспорт заспавнен");
		SetPVarInt(playerid, "yacht_cam_mode", 1);
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(areaid == Area_YachtManager) {
		Dialog_Show(playerid, Dialog:DIALOG_YACTH_MAHAGER);
		return Y_HOOKS_BREAK_RETURN_1;
	} 
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == Area_YachtSpawn[0]) {
		if(GetPVarInt(playerid, "yacht_cam_mode") == 1) {
			InterpolateCameraPos(playerid, 2295.376708, 530.971130, 2.401699, 2337.070068, 488.374359, 9.121240, 2500);
			InterpolateCameraLookAt(playerid, 2292.041259, 534.672363, 1.982717, 2335.990966, 493.197387, 8.363808, 2500);
			DeletePVar(playerid, "yacht_cam_mode");
			defer ReturnCamera(playerid);
		}
	} else if(areaid == Area_YachtSpawn[1]) {
		if(GetPVarInt(playerid, "yacht_cam_mode") == 1) {
			new 
                Float: pos_x,
                Float: pos_y,
                Float: pos_z;

            GetPlayerPos(playerid, pos_x, pos_y, pos_z);
            
            InterpolateCameraPos(playerid, pos_x, pos_y, pos_z, pos_x, pos_y, pos_z + 35.00, 2500);
            InterpolateCameraLookAt(playerid, pos_x, pos_y, pos_z, pos_x, pos_y, pos_z + 30.00, 2500);

			DeletePVar(playerid, "yacht_cam_mode");
			defer ReturnCamera(playerid);
		}		
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnVehicleDeath(vehicleid, killerid) {
	foreach(new i: Player) {
		if(PlayerYachtVehicleID[i] != INVALID_VEHICLE_ID && IsValidVehicle(PlayerYachtVehicleID[i]) && PlayerYachtVehicleID[i] == vehicleid) {
			DestroyVehicle(PlayerYachtVehicleID[i]);
			PlayerYachtVehicleID[i] = INVALID_VEHICLE_ID;
			SendClientMessage(i, -1, ""COLOR_ORANGE"Ваш водный транспорт был уничтожен. Отправляйтесь в порт для повторного спавна");
			SetPVarInt(i,"Destroyed",gettime() + 600);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnVehicleSpawn(vehicleid) {
	foreach(new i: Player) {
		if(PlayerYachtVehicleID[i] != INVALID_VEHICLE_ID && IsValidVehicle(PlayerYachtVehicleID[i]) && PlayerYachtVehicleID[i] == vehicleid) {
			DestroyVehicle(PlayerYachtVehicleID[i]);
			PlayerYachtVehicleID[i] = INVALID_VEHICLE_ID;
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid) {
	if(checkpointid == PlayerCPSpawnYacht[playerid]) {
		DestroyDynamicCP(PlayerCPSpawnYacht[playerid]);
		PlayerCPSpawnYacht[playerid] = -1;
		Dialog_Message(playerid, 
			""COLOR_BLUE"Водный транспорт", 
			""COLOR_WHITE"Для того, чтобы предоставить/закрыть доступ другим игрокам к судну используйте: "COLOR_GREEN"/lock", 
			"Закрыть"
		);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDialogShowed(const playerid, const e_DIALOG_IDs:dialogid, const response, const listitem, const inputtext[]) {
	SetPVarInt(playerid, "player_uptime", gettime());
	if(dialogid == DIALOG_BUY_YACHT) {
		new 
			activ_view = GetPVarInt(playerid, "yacht_view");

		if(response) {
			switch(activ_view) {
				case 0: {
					SetPVarInt(playerid, "yacht_view", 5);
				}
				case 1: {
					SetPVarInt(playerid, "yacht_view", 0);
				}
				case 2: {
					SetPVarInt(playerid, "yacht_view", 1);
				}
				case 3: {
					SetPVarInt(playerid, "yacht_view", 2);
				}
				case 4: {
					SetPVarInt(playerid, "yacht_view", 3);
				}
				case 5: {
					SetPVarInt(playerid, "yacht_view", 4);
				}
			}
			ViewYacht(playerid);
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			switch(activ_view) {
				case 0: {
					SetPVarInt(playerid, "yacht_view", 1);
				}
				case 1: {
					SetPVarInt(playerid, "yacht_view", 2);
				}
				case 2: {
					SetPVarInt(playerid, "yacht_view", 3);
				}
				case 3: {
					SetPVarInt(playerid, "yacht_view", 4);
				}
				case 4: {
					SetPVarInt(playerid, "yacht_view", 5);
				}
				case 5: {
					SetPVarInt(playerid, "yacht_view", 0);
				}
			}
			ViewYacht(playerid);
			return Y_HOOKS_CONTINUE_RETURN_1;
		}
	} else if(dialogid == DIALOG_BUY_YACHT_ACCEPT) {
		if(!response) {
			ViewYacht(playerid);
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			new 
				activ_view = GetPVarInt(playerid, "yacht_view");
				
			switch(activ_view) {
				case 0: {
					if(CheckCash(playerid, YachtBuy[0][E_PRICE]) == false) {
						ViewYacht(playerid);
						return 1;
					}
					RemovePlayerEXP(playerid, YachtBuy[0][E_PRICE], "Покупка яхты Marquis");

					format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы купили яхту "COLOR_GREEN"\"Marquis\""COLOR_WHITE" за "COLOR_GREEN"%i EXP", YachtBuy[0][E_PRICE]);
					PlayerYachtModel[playerid] = 484;
					mysql_format(database, big_string, sizeof(big_string), "INSERT INTO `player_vehicle`(`PlayerID`, `Vehicle`, `Type`) VALUES (%i, '484 - Marquis', 'Яхта')", PlayerInfo[playerid][pID]);
				}
				case 1: {
					if(CheckCash(playerid, YachtBuy[1][E_PRICE]) == false) {
						ViewYacht(playerid);
						return 1;
					}
					RemovePlayerEXP(playerid, YachtBuy[1][E_PRICE], "Покупка лодки Jetmax");

					format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы купили лодку "COLOR_GREEN"\"Jetmax\""COLOR_WHITE" за "COLOR_GREEN"%i EXP", YachtBuy[1][E_PRICE]);
					PlayerYachtModel[playerid] = 493;
					mysql_format(database, big_string, sizeof(big_string), "INSERT INTO `player_vehicle`(`PlayerID`, `Vehicle`, `Type`) VALUES (%i, '493 - Jetmax', 'Яхта')", PlayerInfo[playerid][pID]);
				}
				case 2: {
					if(CheckCash(playerid, YachtBuy[2][E_PRICE]) == false) {
						ViewYacht(playerid);
						return 1;
					}
					RemovePlayerEXP(playerid, YachtBuy[2][E_PRICE], "Покупка яхты Reefer");

					format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы купили яхту "COLOR_GREEN"\"Reefer\""COLOR_WHITE" за "COLOR_GREEN"%i EXP", YachtBuy[2][E_PRICE]);
					PlayerYachtModel[playerid] = 453;
					mysql_format(database, big_string, sizeof(big_string), "INSERT INTO `player_vehicle`(`PlayerID`, `Vehicle`, `Type`) VALUES (%i, '453 - Reefer', 'Яхта')", PlayerInfo[playerid][pID]);
				}
				case 3: {
					if(CheckCash(playerid, YachtBuy[3][E_PRICE]) == false) {
						ViewYacht(playerid);
						return 1;
					}
					RemovePlayerEXP(playerid, YachtBuy[3][E_PRICE], "Покупка яхты Tropic");

					format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы купили яхту "COLOR_GREEN"\"Tropic\""COLOR_WHITE" за "COLOR_GREEN"%i EXP", YachtBuy[3][E_PRICE]);
					PlayerYachtModel[playerid] = 454;
					mysql_format(database, big_string, sizeof(big_string), "INSERT INTO `player_vehicle`(`PlayerID`, `Vehicle`, `Type`) VALUES (%i, '454 - Tropic', 'Яхта')", PlayerInfo[playerid][pID]);
				}
				case 4: {
					if(CheckCash(playerid, YachtBuy[4][E_PRICE]) == false) {
						ViewYacht(playerid);
						return 1;
					}
					RemovePlayerEXP(playerid, YachtBuy[4][E_PRICE], "Покупка катера Speeder");

					format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы купили катер "COLOR_GREEN"\"Speeder\""COLOR_WHITE" за "COLOR_GREEN"%i EXP", YachtBuy[4][E_PRICE]);
					PlayerYachtModel[playerid] = 452;
					mysql_format(database, big_string, sizeof(big_string), "INSERT INTO `player_vehicle`(`PlayerID`, `Vehicle`, `Type`) VALUES (%i, '452 - Speeder', 'Яхта')", PlayerInfo[playerid][pID]);
				}
				case 5: {
					if(CheckCash(playerid, YachtBuy[5][E_PRICE]) == false) {
						ViewYacht(playerid);
						return 1;
					}
					RemovePlayerEXP(playerid, YachtBuy[5][E_PRICE], "Покупка лодки Squalo");

					format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы купили лодку "COLOR_GREEN"\"Squalo\""COLOR_WHITE" за "COLOR_GREEN"%i EXP", YachtBuy[5][E_PRICE]);
					PlayerYachtModel[playerid] = 446;
					mysql_format(database, big_string, sizeof(big_string), "INSERT INTO `player_vehicle`(`PlayerID`, `Vehicle`, `Type`) VALUES (%i, '446 - Squalo', 'Яхта')", PlayerInfo[playerid][pID]);
				}
			}
			SendClientMessage(playerid, -1, small_string);
			mysql_pquery(database, big_string);
			callcmd::ya_exit(playerid, "");
			return Y_HOOKS_CONTINUE_RETURN_1;
		}
	} 
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerAuthorization(playerid) {
	mysql_format(database, small_string, sizeof(small_string), "SELECT Color_1, CONVERT(Vehicle, SIGNED) AS Vehicle FROM `player_vehicle` WHERE `PlayerID` = %i AND `Type` = 'Яхта'", PlayerInfo[playerid][pID]);
	mysql_query(database, small_string, true);

	new 
		rows = cache_get_row_count();

	if(!rows) {
		PlayerYachtModel[playerid] = INVALID_YACHT;
	} else {
		new 
			value = cache_get_field_content_int(0, "Vehicle");

		PlayerYachtColor[playerid] = cache_get_field_content_int(0, "Color_1");

		switch(value) {
			case 4: {
				PlayerYachtModel[playerid] = 446;
			}
			case 5: {
				PlayerYachtModel[playerid] = 452;
			}
			case 6: {
				PlayerYachtModel[playerid] = 454;
			}
			case 7: {
				PlayerYachtModel[playerid] = 453;
			}
			case 8: {
				PlayerYachtModel[playerid] = 493;
			}
			case 9: {
				PlayerYachtModel[playerid] = 484;
			}
			default: {
				PlayerYachtModel[playerid] = INVALID_YACHT;
			}
		}
	}
}

stock ViewYacht(const playerid) {
	new 
		activ_view = GetPVarInt(playerid, "yacht_view");

	TogglePlayerSpectating(playerid, true);


	format(big_string, sizeof(big_string), ""COLOR_WHITE"%s\n\n"COLOR_ORANGE"Для покупки водного транспорта используйте - /ya_buy\n\
		Для выхода из режима покупки - /ya_exit", 
			YachtBuy[activ_view][E_INFO]
	);

	SPD(playerid, DIALOG_BUY_YACHT, DIALOG_STYLE_MSGBOX, "Покупка водного транспорта", big_string, "<<<", ">>>");
	switch(activ_view) {
		case 5: {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~Squalo~n~~w~295000 EXP", 15000, 6);
			InterpolateCameraPos(playerid, 2277.420898, 532.895385, 4.481897, 2277.420898, 532.895385, 4.481897, 864020);
			InterpolateCameraLookAt(playerid, 2281.615722, 534.733947, 2.476252, 2281.615722, 534.733947, 2.476252, 864020);
		}
		case 4: {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~Speeder~n~~w~225000 EXP", 15000, 6);
			InterpolateCameraPos(playerid, 2275.191162, 532.426696, 1.282389, 2275.191162, 532.426696, 1.282389, 864020);
			InterpolateCameraLookAt(playerid, 2279.016113, 535.608032, 0.783529, 2279.016113, 535.608032, 0.783529, 864020);
		}
		case 3: {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~Tropic~n~~w~500000 EXP", 15000, 6);
			InterpolateCameraPos(playerid, 2265.289550, 529.404052, 3.125607, 2265.289550, 529.404052, 3.125607, 864020);
			InterpolateCameraLookAt(playerid, 2269.069335, 532.625610, 2.547003, 2269.069335, 532.625610, 2.547003, 864020);
		}
		case 2: {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~Reefer~n~~w~350000 EXP", 15000, 6);
			InterpolateCameraPos(playerid, 2260.373779, 530.297180, 0.704556, 2260.373779, 530.297180, 0.704556, 864020);
			InterpolateCameraLookAt(playerid, 2264.058837, 533.675048, 0.806416, 2264.058837, 533.675048, 0.806416, 864020);
		}
		case 1 : {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~Jetmax~n~~w~250000 EXP", 15000, 6);
			InterpolateCameraPos(playerid, 2254.194091, 530.350463, 2.911164, 2254.194091, 530.350463, 2.911164, 864020);
			InterpolateCameraLookAt(playerid, 2257.430908, 533.862365, 1.431366, 2257.430908, 533.862365, 1.431366, 864020);
		}
		case 0 : {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~Marquis~n~~w~400000 EXP", 15000, 6);
			InterpolateCameraPos(playerid, 2243.063720, 523.325622, 3.758700, 2243.063720, 523.325622, 3.758700, 864020);
			InterpolateCameraLookAt(playerid, 2246.787109, 526.550964, 2.902323, 2246.787109, 526.550964, 2.902323, 864020);
		}
	}
} 

CMD:ya_exit(playerid, params[]) {
	if(GetPVarInt(playerid, "buy_mode_yacht") != 1) {
		return 1;
	} else {
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~g~Good luck", 1000, 6);
		ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, "Покупка водного транспорта", ""COLOR_WHITE"Вы покинули режим покупки", "Закрыть", "");
		TogglePlayerSpectating(playerid, false);
		DeletePVar(playerid, "yacht_view");
		return 1;
	}
}

CMD:ya_buy(playerid, params[]) {
	if(GetPVarInt(playerid, "buy_mode_yacht") != 1) {
		return 1;
	} else {
		new 
			activ_view = GetPVarInt(playerid, "yacht_view");
			
		switch(activ_view) {
			case 5: {
				format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите купить лодку "COLOR_GREEN"\"Squalo\""COLOR_WHITE" за "COLOR_GREEN"%i EXP?", YachtBuy[5][E_PRICE]);
			}
			case 4: {
				format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите купить катер "COLOR_GREEN"\"Speeder\""COLOR_WHITE" за "COLOR_GREEN"%i EXP?", YachtBuy[4][E_PRICE]);
			}
			case 3: {
				format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите купить яхту "COLOR_GREEN"\"Tropic\""COLOR_WHITE" за "COLOR_GREEN"%i EXP?", YachtBuy[3][E_PRICE]);
			}
			case 2: {
				format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите купить яхту "COLOR_GREEN"\"Reefer\""COLOR_WHITE" за "COLOR_GREEN"%i EXP?", YachtBuy[2][E_PRICE]);
			}
			case 1: {
				format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите купить лодку "COLOR_GREEN"\"Jetmax\""COLOR_WHITE" за "COLOR_GREEN"%i EXP?", YachtBuy[1][E_PRICE]);
			}
			case 0: {
				format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите купить яхту "COLOR_GREEN"\"Marquis\""COLOR_WHITE" за "COLOR_GREEN"%i EXP?", YachtBuy[0][E_PRICE]);
			}
		}
		ShowPlayerDialog(playerid, DIALOG_BUY_YACHT_ACCEPT, DIALOG_STYLE_MSGBOX, "Покупка", big_string, "Да", "Нет");
	}
	return 1;
}

DialogCreate:DIALOG_YACTH_MAHAGER(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_YACTH_MAHAGER, DIALOG_STYLE_LIST,
		""COLOR_BLUE"Управление",
		""COLOR_WHITE"1. Перекраска водного транспорта\n"COLOR_RED"2. Продажа государству", 
		"Выбрать", "Закрыть"
	);
}

DialogResponse:DIALOG_YACTH_MAHAGER(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		if(PlayerYachtModel[playerid] == INVALID_YACHT) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет личного водного транспорта");
		}

		switch(listitem) {
			// Перекраска
			case 0: {
				return Dialog_Show(playerid, Dialog:DIALOG_CHANCE_YACHT_COLOR);
			}
			// Продажа
			case 1: {
				PlayerSellYachtTime[playerid] = 10;
				Dialog_Show(playerid, Dialog:DIALOG_SELL_YACHT);
				defer SellYacht(playerid);
				return 1;
			}
			default: {
				return Dialog_Show(playerid, Dialog:DIALOG_YACTH_MAHAGER);
			}
		}
	}
	return 1;
}

DialogCreate:DIALOG_CHANCE_YACHT_COLOR(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_CHANCE_YACHT_COLOR, DIALOG_STYLE_LIST,
		""COLOR_BLUE"Покраска",
		""COLOR_WHITE"1. Черный - "COLOR_GREEN"15000 EXP\n\
			"COLOR_WHITE"2. Белый - "COLOR_GREEN"12000 EXP\n\
			"COLOR_WHITE"3. Синий - "COLOR_GREEN"25000 EXP\n\
			"COLOR_WHITE"4. Зеленый - "COLOR_GREEN"27000 EXP\n\
			"COLOR_WHITE"5. Красный - "COLOR_GREEN"50000 EXP"INPUT_NUMBER"", 
		"Выбрать", "Назад"
	);
}

DialogResponse:DIALOG_CHANCE_YACHT_COLOR(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return Dialog_Show(playerid, Dialog:DIALOG_YACTH_MAHAGER);
	} else {
		if(PlayerYachtModel[playerid] == INVALID_YACHT) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет личного водного транспорта");
		}

		switch(listitem) {
			case 0: {
				if(CheckCash(playerid, 15000) == false) return 1;
				RemovePlayerEXP(playerid, 15000, "Покраска водного транспорта в черный цвет");
				SendClientMessage(playerid, -1, "Вы покрасили Ваш водный транспорт в {000000}\"Черный\""COLOR_WHITE" цвет за "COLOR_GREEN"15000 EXP");
				mysql_format(database, small_string, sizeof(small_string), "UPDATE `player_vehicle` SET `Color_1` = 0 WHERE `PlayerID` = %i AND `Type` = 'Яхта'", PlayerInfo[playerid][pID]);
				PlayerYachtColor[playerid] = 0;
				if(PlayerYachtVehicleID[playerid] != INVALID_VEHICLE_ID) {
					ChangeVehicleColor(PlayerYachtVehicleID[playerid], 0, 1);
				}
			}
			case 1: {
				if(CheckCash(playerid, 12000) == false) return 1;
				RemovePlayerEXP(playerid, 12000, "Покраска водного транспорта в белый цвет");
				SendClientMessage(playerid, -1, "Вы покрасили Ваш водный транспорт в {ffffff}\"Белый\""COLOR_WHITE" цвет за "COLOR_GREEN"12000 EXP");
				mysql_format(database, small_string, sizeof(small_string), "UPDATE `player_vehicle` SET `Color_1` = 1 WHERE `PlayerID` = %i AND `Type` = 'Яхта'", PlayerInfo[playerid][pID]);
				PlayerYachtColor[playerid] = 1;
				if(PlayerYachtVehicleID[playerid] != INVALID_VEHICLE_ID) {
					ChangeVehicleColor(PlayerYachtVehicleID[playerid], 1, 1);
				}
			}
			case 2: {
				if(CheckCash(playerid, 25000) == false) return 1;
				RemovePlayerEXP(playerid, 25000, "Покраска водного транспорта в синий цвет");
				SendClientMessage(playerid, -1, "Вы покрасили Ваш водный транспорт в {2A77A1}\"Синий\""COLOR_WHITE" цвет за "COLOR_GREEN"25000 EXP");
				mysql_format(database, small_string, sizeof(small_string), "UPDATE `player_vehicle` SET `Color_1` = 2 WHERE `PlayerID` = %i AND `Type` = 'Яхта'", PlayerInfo[playerid][pID]);
				PlayerYachtColor[playerid] = 2;
				if(PlayerYachtVehicleID[playerid] != INVALID_VEHICLE_ID) {
					ChangeVehicleColor(PlayerYachtVehicleID[playerid], 2, 1);
				}
			}
			case 3: {
				if(CheckCash(playerid, 27000) == false) return 1;
				RemovePlayerEXP(playerid, 27000, "Покраска водного транспорта в зеленый цвет");
				SendClientMessage(playerid, -1, "Вы покрасили Ваш водный транспорт в {335F3E}\"Зеленый\""COLOR_WHITE" цвет за "COLOR_GREEN"27000 EXP");
				mysql_format(database, small_string, sizeof(small_string), "UPDATE `player_vehicle` SET `Color_1` = 16 WHERE `PlayerID` = %i AND `Type` = 'Яхта'", PlayerInfo[playerid][pID]);
				PlayerYachtColor[playerid] = 16;
				if(PlayerYachtVehicleID[playerid] != INVALID_VEHICLE_ID) {
					ChangeVehicleColor(PlayerYachtVehicleID[playerid], 16, 1);
				}
			}
			case 4: {
				if(CheckCash(playerid, 27000) == false) return 1;
				RemovePlayerEXP(playerid, 27000, "Покраска водного транспорта в красный цвет");
				SendClientMessage(playerid, -1, "Вы покрасили Ваш водный транспорт в "COLOR_RED"\"Красный\""COLOR_WHITE" цвет за "COLOR_GREEN"50000 EXP");
				mysql_format(database, small_string, sizeof(small_string), "UPDATE `player_vehicle` SET `Color_1` = 3 WHERE `PlayerID` = %i AND `Type` = 'Яхта'", PlayerInfo[playerid][pID]);
				PlayerYachtColor[playerid] = 3;
				if(PlayerYachtVehicleID[playerid] != INVALID_VEHICLE_ID) {
					ChangeVehicleColor(PlayerYachtVehicleID[playerid], 3, 1);
				}
			}
			default: {
				return Dialog_Show(playerid, Dialog:DIALOG_CHANCE_YACHT_COLOR);
			}
		}
		mysql_pquery(database, small_string);
		Dialog_Show(playerid, Dialog:DIALOG_YACTH_MAHAGER);
	}
	return 1;
}


DialogCreate:DIALOG_SELL_YACHT(playerid) {
	new 
		time = PlayerSellYachtTime[playerid];

	new 
		model = PlayerYachtModel[playerid],
		cash = 0;

	switch(model) {
		case 484: {
			cash = YachtBuy[0][E_PRICE] / 2;
		}
		case 493: {
			cash = YachtBuy[1][E_PRICE] / 2;
		}
		case 453: {
			cash = YachtBuy[2][E_PRICE] / 2;
		}
		case 454: {
			cash = YachtBuy[3][E_PRICE] / 2;
		}
		case 452: {
			cash = YachtBuy[4][E_PRICE] / 2;
		}
		case 446: {
			cash = YachtBuy[5][E_PRICE] / 2;
		}
	}

	if(time >= 0) {
		format(small_string, sizeof(small_string), "Да (%i)", time);
		format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите продать свой водный транспорт за "COLOR_GREEN"%i EXP?\n\n"COLOR_RED"Принять предложение продажи можно будет через 10 секунд.", cash);
		return Dialog_Open(playerid, Dialog:DIALOG_SELL_YACHT, DIALOG_STYLE_MSGBOX,
			""COLOR_BLUE"Продажа",
			big_string, 
			small_string, "Нет"
		);
	} else {
		format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите продать свой водный транспорт за "COLOR_GREEN"%i EXP?", cash);
		return Dialog_Open(playerid, Dialog:DIALOG_SELL_YACHT, DIALOG_STYLE_MSGBOX,
			""COLOR_BLUE"Продажа",
			big_string, 
			"Да", "Нет"
		);
	}
}

DialogResponse:DIALOG_SELL_YACHT(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		if(PlayerSellYachtTime[playerid] != -1) {
			return Dialog_Show(playerid, Dialog:DIALOG_SELL_YACHT);
		}
		new 
			model = PlayerYachtModel[playerid],
			cash = 0;

		switch(model) {
			case 484: {
				cash = YachtBuy[0][E_PRICE] / 2;
			}
			case 493: {
				cash = YachtBuy[1][E_PRICE] / 2;
			}
			case 453: {
				cash = YachtBuy[2][E_PRICE] / 2;
			}
			case 454: {
				cash = YachtBuy[3][E_PRICE] / 2;
			}
			case 452: {
				cash = YachtBuy[4][E_PRICE] / 2;
			}
			case 446: {
				cash = YachtBuy[5][E_PRICE] / 2;
			}
		}

		AddPlayerEXP(playerid, cash, "Продажа частной яхты");
		if(PlayerYachtVehicleID[playerid] != INVALID_VEHICLE_ID && IsValidVehicle(PlayerYachtVehicleID[playerid])) {
			DestroyVehicle(PlayerYachtVehicleID[playerid]);
		}
		PlayerYachtVehicleID[playerid] = INVALID_VEHICLE_ID;
		PlayerYachtColor[playerid] = 1;
		PlayerYachtModel[playerid] = INVALID_YACHT;

		mysql_format(database, small_string, sizeof(small_string), "DELETE FROM `player_vehicle` WHERE `PlayerID` = %i AND `Type` = 'Яхта'", PlayerInfo[playerid][pID]);
		mysql_pquery(database, small_string);

		format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы продали свой водный транспорт за "COLOR_GREEN"%i EXP", cash);
		SendClientMessage(playerid, -1, small_string);

		if(PlayerCPSpawnYacht[playerid] != -1 && IsValidDynamicCP(PlayerCPSpawnYacht[playerid])) {
			DestroyDynamicCP(PlayerCPSpawnYacht[playerid]);
		}
	}
	return 1;
}

timer SellYacht[1000](playerid) {
	if(!Dialog_IsOpen(playerid)) {
		return 0;
	}

	new 
		time = PlayerSellYachtTime[playerid];

	if(time >= 0) {
		PlayerSellYachtTime[playerid] = time - 1;
		Dialog_Show(playerid, Dialog:DIALOG_SELL_YACHT);
	
		defer SellYacht(playerid);
	} else {
		PlayerSellYachtTime[playerid] = -1;
	}
	return 1;
}

timer ReturnCamera[3000](playerid) {
	PutPlayerInVehicle(playerid, PlayerYachtVehicleID[playerid], 0);
	return SetCameraBehindPlayer(playerid);
}

stock IsPlayerSwimming(playerid)
{
    new animlib[32];
    new animname[32];
    GetAnimationName(GetPlayerAnimationIndex(playerid),animlib,32,animname,32);
    if(!strcmp(animlib, "SWIM")) return 1;
    return 0;
}

CMD:boat(playerid) {
	new 
		model = PlayerYachtModel[playerid];

	if(IsPlayerInAnyVehicle(playerid) == 1) return 1;
	if(GetPlayerVirtualWorld(playerid) != 0) return 1;
	if(GetPlayerInterior(playerid) != 0) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;

	if(GetPVarInt(playerid,"Destroyed") > gettime()) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваш водный транспорт недавно был уничтожен, заберите его в порту");

	if(model == INVALID_YACHT) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет личного водного транспорта");
	}
	if(PlayerYachtVehicleID[playerid] != INVALID_VEHICLE_ID) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Ваш водный транспорт уже заспавнен");
	}

	if(IsPlayerSwimming(playerid) == 0) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Необходимо находиться в воде");
	
	new
		Float: player_pos_x,
		Float: player_pos_y,
		Float: player_pos_z,
		Float: player_angle;	

	GetPlayerPos(playerid, player_pos_x, player_pos_y, player_pos_z);
	GetPlayerFacingAngle(playerid, player_angle);		

	PlayerYachtVehicleID[playerid] = CreateVehicle(model, player_pos_x,player_pos_y,player_pos_z+3,player_angle, 1, 1, 86400);
	PutPlayerInVehicle(playerid, PlayerYachtVehicleID[playerid], 0);

	Streamer_Update(playerid, STREAMER_TYPE_CP);
	ChangeVehicleColor(PlayerYachtVehicleID[playerid], PlayerYachtColor[playerid], 1);
	SetVehicleParamsForPlayerEx(PlayerYachtVehicleID[playerid], playerid, 0, 1);
	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы успешно вызвали и переместились в личный водный транспорт");

	return 1;
}
