#if defined private_aviation_included
	#endinput
#endif

#define private_aviation_included

#include <YSI_Coding\y_hooks>

#define INVALID_AVIATION 						(-1)

enum E_AVIATION {
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
	AviationBuy[3][E_AVIATION] = {
		{447, INVALID_VEHICLE_ID, 1939.8630, -2643.4524, 13.5379, 0.0031, 190000, "Seasparrow - двухместный вертолет. Из-за воздушных подушек\nв основании корпуса может садиться прямо на воду\n\n"COLOR_GREEN"Максимальная скорость - 74 км. в час"}, // 76
		{469, INVALID_VEHICLE_ID, 1951.1909, -2643.3025, 13.6290, 0.0025, 225000, "Sparrow - двухместный вертолет\nСочетает в себе идеальную управляемость и высокую скорость\n\n"COLOR_GREEN"Максимальная скорость - 76 км. в час"}, // 74
		{487, INVALID_VEHICLE_ID, 1963.3010, -2643.1892, 13.7970, 359.9941, 250000, "Maverick - четырехместный вертолет.\nИдеальная аэродинамика, высокая скорость - выбор настоящего ценителя небесных простор\nБольшая кабина позволяет вместить в себя 4 человека\n"COLOR_GREEN"Максимальная скорость - 99 км. в час"} // 99
	};

new 
	PC_AviationBuy,
	PC_AviationManager,
	PC_AviationSpawn,
	PC_CenterLS[6];

new 
	Area_AviationBuy,
	Area_AviationManager,
	Area_AviationSpawn;

new 
	PlayerAviationModel[MAX_PLAYERS] = {INVALID_AVIATION, ...},
	PlayerAviationVehicleID[MAX_PLAYERS] = {INVALID_VEHICLE_ID, ...},
	PlayerAviationColor[MAX_PLAYERS] = {1, ...},
	PlayerSellAviaTime[MAX_PLAYERS] = {-1, ...},
	PlayerCPSpawnAvia[MAX_PLAYERS] = -1;

hook OnGameModeInit() {
	CreateDynamicMapIcon(1909.1882, -2638.3318, 13.5469, 57, -1, 0, 0, -1, 100.0);
	CreateDynamicMapIcon(1570.4407, -1337.4558, 16.4844, 5, -1, 0, 0, -1, 100.0);

	for(new i = 0; i < sizeof(AviationBuy); i++) {
		new c1 = RandomEx(0,4);
		if(c1 == 4) c1 = 16;
		AviationBuy[i][E_VEHICLE_ID] = AddStaticVehicle(AviationBuy[i][E_MODEL_ID], AviationBuy[i][E_X], AviationBuy[i][E_Y], AviationBuy[i][E_Z], AviationBuy[i][E_ANGLE], c1, 1);
	}

	new actor = CreateActor(93, 1906.1882, -2640.3318, 13.5469, 0.00);
	ApplyActorAnimation(actor, "COP_AMBIENT","coplook_loop",4.1, 1, 0, 0, 0, 0);

	PC_AviationBuy = CreateDynamicPickup(1239, 1, 1909.1882, -2638.3318, 13.5469);
	Area_AviationBuy = CreateDynamicSphere(1909.1882, -2638.3318, 13.5469, 1.00);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Покупка вертолета", -1, 1909.1882, -2638.3318, 13.5469 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	PC_AviationManager = CreateDynamicPickup(1276, 1, 1906.1882, -2638.3318, 13.5469);
	Area_AviationManager = CreateDynamicSphere(1906.1882, -2638.3318, 13.5469, 1.00);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Управление личным вертолетом\n"COLOR_ORANGE"(покраска, продажа)", -1, 1906.1882, -2638.3318, 13.5469 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	PC_AviationSpawn = CreateDynamicPickup(1239, 1, 1903.1882, -2638.3318, 13.5469);
	Area_AviationSpawn = CreateDynamicSphere(1903.1882, -2638.3318, 13.5469, 1.00);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Спавн личного вертолета", -1, 1903.1882, -2638.3318, 13.5469 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);


	PC_CenterLS[0] = CreateDynamicPickup(1318, 1, 1570.4407, -1337.4558, 16.4844);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход на крышу", -1, 1570.4407, -1337.4558, 16.4844 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	PC_CenterLS[1] = CreateDynamicPickup(1318, 1, 1548.5475, -1363.7407, 326.2183);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Спуск с крыши", -1, 1548.5475, -1363.7407, 326.2183 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	PC_CenterLS[2] = CreateDynamicPickup(1239, 1, 1545.5713, -1362.8953, 329.4579);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Спавн личного вертолета", -1, 1545.5713, -1362.8953, 329.457 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	PC_CenterLS[3] = CreateDynamicPickup(1239, 1, -1214.4943,15.7326,14.1484);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Спавн личного вертолета", -1, -1214.4943,15.7326,14.1484 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	PC_CenterLS[4] = CreateDynamicPickup(1239, 1, 1717.1376,1616.0215,10.0548);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Спавн личного вертолета", -1, 1717.1376,1616.0215,10.0548 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	PC_CenterLS[5] = CreateDynamicPickup(1239, 1, 1153.8792,-1180.8655,32.8187);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Спавн личного вертолета", -1, 1153.8792,-1180.8655,32.8187 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);



	CreateDynamicObject(2773, 1963.3000000, -2637.2000000, 13.1000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1951.2000000, -2637.2000000, 13.1000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1939.9000000, -2637.2000000, 13.1000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1961.4000000, -2637.2000000, 13.1000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1965.2000000, -2637.2000000, 13.1000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1949.3000000, -2637.2000000, 13.1000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1953.1000000, -2637.2000000, 13.1000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1938.0000000, -2637.2000000, 13.1000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1941.8000000, -2637.2000000, 13.1000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1966.1000000, -2638.1611000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1966.1000000, -2640.1001000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1966.1000000, -2642.0000000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1960.4000000, -2638.1611000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1960.4000000, -2640.1001000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1960.4000000, -2642.0000000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1948.3000000, -2638.1611000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1948.3000000, -2640.1001000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1948.3000000, -2642.0000000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1954.0000000, -2638.1611000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1954.0000000, -2640.1001000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1954.0000000, -2642.0000000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1942.7000000, -2638.1611000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1942.7000000, -2640.1001000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1942.7000000, -2642.0000000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1937.0000000, -2638.1611000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1937.0000000, -2640.1001000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1937.0000000, -2642.0000000, 13.1000000, 0.0000000, 0.0000000, 0.0000000);
}

hook OnPlayerConnect(playerid) {
	for(new i = 0; i < sizeof(AviationBuy); i++) {
		if(AviationBuy[i][E_VEHICLE_ID] != INVALID_VEHICLE_ID && IsValidVehicle(AviationBuy[i][E_VEHICLE_ID])) {
			SetVehicleParamsForPlayerEx(AviationBuy[i][E_VEHICLE_ID], playerid, 0, 1);
		}
	}

	PlayerAviationModel[playerid] = INVALID_AVIATION;
	PlayerAviationVehicleID[playerid] = INVALID_VEHICLE_ID;
	PlayerAviationColor[playerid] = 1;
	PlayerSellAviaTime[playerid] = -1;
	PlayerCPSpawnAvia[playerid] = -1;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason

	PlayerAviationModel[playerid] = INVALID_AVIATION;
	if(PlayerAviationVehicleID[playerid] != INVALID_VEHICLE_ID && IsValidVehicle(PlayerAviationVehicleID[playerid])) {
		DestroyVehicle(PlayerAviationVehicleID[playerid]);
	}
	PlayerAviationVehicleID[playerid] = INVALID_VEHICLE_ID;
	PlayerAviationColor[playerid] = 1;
	PlayerSellAviaTime[playerid] = -1;
	if(PlayerCPSpawnAvia[playerid] != -1) {
		DestroyDynamicCP(PlayerCPSpawnAvia[playerid]);
		Streamer_Update(playerid, STREAMER_TYPE_CP);
	}
	PlayerCPSpawnAvia[playerid] = -1;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
	for(new i = 0; i < sizeof(AviationBuy); i++) {
		if(vehicleid == AviationBuy[i][E_VEHICLE_ID] && AviationBuy[i][E_VEHICLE_ID] != INVALID_VEHICLE_ID) {
			// Kick(playerid);
			RemovePlayerFromVehicle(playerid);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid) {
	if(Dialog_IsOpen(playerid)) {
		return 0;
	}

	if(pickupid == PC_AviationBuy) {
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(pickupid == PC_AviationSpawn) {
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(pickupid == PC_AviationManager) {
		return Y_HOOKS_CONTINUE_RETURN_1;
	} else if(pickupid == PC_CenterLS[0]) {
		SetPlayerPos(playerid, 1547.3691, -1366.4625, 326.2109);
		SetPlayerFacingAngle(playerid, 90.00);
		SetCameraBehindPlayer(playerid);
	} else if(pickupid == PC_CenterLS[1]) {
		SetPlayerPos(playerid, 1576.1881, -1333.6328, 16.4844);
		SetPlayerFacingAngle(playerid, 325.00);
		SetCameraBehindPlayer(playerid);
	} else if(pickupid == PC_CenterLS[2]) {

		if(GetPVarInt(playerid,"CalledSpawnPickup") > gettime()) return 1;
		SetPVarInt(playerid,"CalledSpawnPickup",gettime() + 25);

		new 
			model = PlayerAviationModel[playerid];

		if(model == INVALID_AVIATION) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет личного вертолета");
		}
		if(PlayerAviationVehicleID[playerid] != INVALID_VEHICLE_ID) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вертолет уже заспавнен");
		}

		PlayerAviationVehicleID[playerid] = CreateVehicle(model, 1544.9669, -1353.2726, 329.7122, 90.00, 1, 1, 86400);

		ChangeVehicleColor(PlayerAviationVehicleID[playerid], PlayerAviationColor[playerid], 1);
		SetVehicleParamsForPlayerEx(PlayerAviationVehicleID[playerid], playerid, 0, 1);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Личный вертолет заспавнен");
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(pickupid == PC_CenterLS[3]) {

		if(GetPVarInt(playerid,"CalledSpawnPickup") > gettime()) return 1;
		SetPVarInt(playerid,"CalledSpawnPickup",gettime() + 25);

		new 
			model = PlayerAviationModel[playerid];

		if(model == INVALID_AVIATION) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет личного вертолета");
		}
		if(PlayerAviationVehicleID[playerid] != INVALID_VEHICLE_ID) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вертолет уже заспавнен");
		}

		new number_ran = RandomEx(1,2);
		if(number_ran == 1) {
			PlayerAviationVehicleID[playerid] = CreateVehicle(model, -1186.6260,24.9420,14.4166, 0.00, 1, 1, 86400);
		} else {
			PlayerAviationVehicleID[playerid] = CreateVehicle(model,-1224.0065,-11.4827,14.4520, 0.00, 1, 1, 86400);
		}

		ChangeVehicleColor(PlayerAviationVehicleID[playerid], PlayerAviationColor[playerid], 1);
		SetVehicleParamsForPlayerEx(PlayerAviationVehicleID[playerid], playerid, 0, 1);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Личный вертолет заспавнен");
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(pickupid == PC_CenterLS[4]) {

		if(GetPVarInt(playerid,"CalledSpawnPickup") > gettime()) return 1;
		SetPVarInt(playerid,"CalledSpawnPickup",gettime() + 25);

		new 
			model = PlayerAviationModel[playerid];

		if(model == INVALID_AVIATION) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет личного вертолета");
		}
		if(PlayerAviationVehicleID[playerid] != INVALID_VEHICLE_ID) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вертолет уже заспавнен");
		}

		new number_ran = RandomEx(1,2);
		if(number_ran == 1) {
			PlayerAviationVehicleID[playerid] = CreateVehicle(model, 1691.8905,1634.7445,10.9976, 170.00, 1, 1, 86400);
		} else {
			PlayerAviationVehicleID[playerid] = CreateVehicle(model, 1667.8677,1634.7445,11.1174, 170.00, 1, 1, 86400);
		}

		ChangeVehicleColor(PlayerAviationVehicleID[playerid], PlayerAviationColor[playerid], 1);
		SetVehicleParamsForPlayerEx(PlayerAviationVehicleID[playerid], playerid, 0, 1);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Личный вертолет заспавнен");
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(pickupid == PC_CenterLS[5]) {

		if(GetPVarInt(playerid,"CalledSpawnPickup") > gettime()) return 1;
		SetPVarInt(playerid,"CalledSpawnPickup",gettime() + 25);

		new 
			model = PlayerAviationModel[playerid];

		if(model == INVALID_AVIATION) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет личного вертолета");
		}
		if(PlayerAviationVehicleID[playerid] != INVALID_VEHICLE_ID) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вертолет уже заспавнен");
		}

		PlayerAviationVehicleID[playerid] = CreateVehicle(model, 1134.0824,-1169.4890,31.7048, 270.00, 1, 1, 86400);

		ChangeVehicleColor(PlayerAviationVehicleID[playerid], PlayerAviationColor[playerid], 1);
		SetVehicleParamsForPlayerEx(PlayerAviationVehicleID[playerid], playerid, 0, 1);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Личный вертолет заспавнен");
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == Area_AviationBuy) {
		if(PlayerAviationModel[playerid] != INVALID_AVIATION) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас уже есть личный вертолет");
		}
		SetPVarInt(playerid, "buy_mode", 1);
		TogglePlayerSpectating(playerid, true);
		ViewAviation(playerid);
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(areaid == Area_AviationSpawn) {
		new 
			model = PlayerAviationModel[playerid];

		if(model == INVALID_AVIATION) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет личного вертолета");
		}
		if(PlayerAviationVehicleID[playerid] != INVALID_VEHICLE_ID) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вертолет уже заспавнен");
		}

		switch(random(3)) {
			case 0: {
				PlayerCPSpawnAvia[playerid] = CreateDynamicCP(1928.8524, -2625.5837, 13.6325, 4.00, 0, 0, playerid);
				PlayerAviationVehicleID[playerid] = CreateVehicle(model, 1928.8524, -2625.5837, 13.6325, 0.00, 1, 1, 86400);
			}
			case 1: {
				PlayerCPSpawnAvia[playerid] = CreateDynamicCP(1940.8524, -2625.5837, 13.6325, 4.00, 0, 0, playerid);
				PlayerAviationVehicleID[playerid] = CreateVehicle(model, 1940.8524, -2625.5837, 13.6325, 0.00, 1, 1, 86400);
			}
			default: {
				PlayerCPSpawnAvia[playerid] = CreateDynamicCP(1962.8524, -2625.5837, 13.6325, 4.00, 0, 0, playerid);
				PlayerAviationVehicleID[playerid] = CreateVehicle(model, 1962.8524, -2625.5837, 13.6325, 0.00, 1, 1, 86400);
			}
		}
		Streamer_Update(playerid, STREAMER_TYPE_CP);
		ChangeVehicleColor(PlayerAviationVehicleID[playerid], PlayerAviationColor[playerid], 1);
		SetVehicleParamsForPlayerEx(PlayerAviationVehicleID[playerid], playerid, 0, 1);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Личный вертолет заспавнен");
		SetPVarInt(playerid, "avia_cam_mode", 1);
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(areaid == Area_AviationManager) {
		Dialog_Show(playerid, Dialog:DIALOG_MANAGER_AVIA);
		return Y_HOOKS_BREAK_RETURN_1;
	}

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == Area_AviationSpawn) {
		if(GetPVarInt(playerid, "avia_cam_mode") == 1) {
			InterpolateCameraPos(playerid, 1902.567871, -2633.641845, 14.701007, 1916.929687, -2609.195556, 18.131237, 2500);
			InterpolateCameraLookAt(playerid, 1907.494873, -2632.793457, 14.631479, 1921.257812, -2611.623535, 17.521818, 2500);
			DeletePVar(playerid, "avia_cam_mode");
			defer ReturnCameraHeli(playerid);
		}
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

timer ReturnCameraHeli[3000](playerid) {
	PutPlayerInVehicle(playerid, PlayerAviationVehicleID[playerid], 0);
	return SetCameraBehindPlayer(playerid);
}

hook OnVehicleDeath(vehicleid, killerid) {
	foreach(new i: Player) {
		if(PlayerAviationVehicleID[i] != INVALID_VEHICLE_ID && IsValidVehicle(PlayerAviationVehicleID[i]) && PlayerAviationVehicleID[i] == vehicleid) {
			DestroyVehicle(PlayerAviationVehicleID[i]);
			PlayerAviationVehicleID[i] = INVALID_VEHICLE_ID;
			SendClientMessage(i, -1, ""COLOR_ORANGE"Ваш вертолет был уничтожен. Отправляйтесь в аэропорт для повторного спавна вертолета");
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnVehicleSpawn(vehicleid) {
	foreach(new i: Player) {
		if(PlayerAviationVehicleID[i] != INVALID_VEHICLE_ID && IsValidVehicle(PlayerAviationVehicleID[i]) && PlayerAviationVehicleID[i] == vehicleid) {
			DestroyVehicle(PlayerAviationVehicleID[i]);
			PlayerAviationVehicleID[i] = INVALID_VEHICLE_ID;
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid) {
	if(checkpointid == PlayerCPSpawnAvia[playerid]) {
		DestroyDynamicCP(PlayerCPSpawnAvia[playerid]);
		PlayerCPSpawnAvia[playerid] = -1;
		Dialog_Message(playerid, 
			""COLOR_BLUE"Личный вертолет", 
			""COLOR_WHITE"Для того, чтобы предоставить/закрыть доступ другим игрокам к вертолету используйте: "COLOR_GREEN"/lock", 
			"Закрыть"
		);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDialogShowed(const playerid, const e_DIALOG_IDs:dialogid, const response, const listitem, const inputtext[]) {
	SetPVarInt(playerid, "player_uptime", gettime());
	if(dialogid == DIALOG_BUY_AVIATION) {
		new 
			activ_view = GetPVarInt(playerid, "aviation_view");
		
		if(!response) {
			switch(activ_view) {
				case 0: {
					SetPVarInt(playerid, "aviation_view", 2);
				}
				case 1: {
					SetPVarInt(playerid, "aviation_view", 0);
				}
				case 2: {
					SetPVarInt(playerid, "aviation_view", 1);
				}
			}
			ViewAviation(playerid);
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			switch(activ_view) {
				case 0: {
					SetPVarInt(playerid, "aviation_view", 1);
				}
				case 1: {
					SetPVarInt(playerid, "aviation_view", 2);
				}
				case 2: {
					SetPVarInt(playerid, "aviation_view", 0);
				}
			}
			ViewAviation(playerid);
			return Y_HOOKS_CONTINUE_RETURN_1;
		}
	} else if(dialogid == DIALOG_BUY_AVIATION_ACCEPT) {
		if(!response) {
			ViewAviation(playerid);
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			new 
				activ_view = GetPVarInt(playerid, "aviation_view");
				
			switch(activ_view) {
				case 0: {
					if(CheckCash(playerid, AviationBuy[0][E_PRICE]) == false) return ViewAviation(playerid);
					RemovePlayerEXP(playerid, AviationBuy[0][E_PRICE], "Покупка вертолета Sparrow");
					format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы купили вертолет "COLOR_GREEN"\"Sparrow\""COLOR_WHITE" за "COLOR_GREEN"%i EXP", AviationBuy[0][E_PRICE]);
					PlayerAviationModel[playerid] = 447;
					mysql_format(database, big_string, sizeof(big_string), "INSERT INTO `player_vehicle`(`PlayerID`, `Vehicle`, `Type`) VALUES (%i, '447 - Seasparrow', 'Вертолет')", PlayerInfo[playerid][pID]);
				}
				case 1: {
					if(CheckCash(playerid, AviationBuy[1][E_PRICE]) == false) return ViewAviation(playerid);
					RemovePlayerEXP(playerid, AviationBuy[1][E_PRICE], "Покупка вертолета Seasparrow");
					format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы купили вертолет "COLOR_GREEN"\"Seasparrow\""COLOR_WHITE" за "COLOR_GREEN"%i EXP", AviationBuy[1][E_PRICE]);
					PlayerAviationModel[playerid] = 469;
					mysql_format(database, big_string, sizeof(big_string), "INSERT INTO `player_vehicle`(`PlayerID`, `Vehicle`, `Type`) VALUES (%i, '469 - Sparrow', 'Вертолет')", PlayerInfo[playerid][pID]);
				}
				case 2: {
					if(CheckCash(playerid, AviationBuy[2][E_PRICE]) == false) return ViewAviation(playerid);
					RemovePlayerEXP(playerid, AviationBuy[2][E_PRICE], "Покупка вертолета Maverick");
					format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы купили вертолет "COLOR_GREEN"\"Maverick\""COLOR_WHITE" за "COLOR_GREEN"%i EXP", AviationBuy[2][E_PRICE]);
					PlayerAviationModel[playerid] = 487;
					mysql_format(database, big_string, sizeof(big_string), "INSERT INTO `player_vehicle`(`PlayerID`, `Vehicle`, `Type`) VALUES (%i, '487 - Maverick', 'Вертолет')", PlayerInfo[playerid][pID]);
				}
			}
			SendClientMessage(playerid, -1, small_string);
			mysql_pquery(database, big_string);
			callcmd::av_exit(playerid, "");
			return Y_HOOKS_CONTINUE_RETURN_1;
		}
	} 
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerAuthorization(playerid) {
	mysql_format(database, small_string, sizeof(small_string), "SELECT Color_1, CONVERT(Vehicle, SIGNED) AS Vehicle FROM `player_vehicle` WHERE `PlayerID` = %i AND `Type` = 'Вертолет'", PlayerInfo[playerid][pID]);
	mysql_query(database, small_string, true);

	new 
		rows = cache_get_row_count();

	if(!rows) {
		PlayerAviationModel[playerid] = INVALID_AVIATION;
	} else {
		new 
			value = cache_get_field_content_int(0, "Vehicle");

		PlayerAviationColor[playerid] = cache_get_field_content_int(0, "Color_1");

		switch(value) {
			case 1: {
				PlayerAviationModel[playerid] = 447;
			}
			case 2: {
				PlayerAviationModel[playerid] = 469;
			}
			case 3: {
				PlayerAviationModel[playerid] = 487;
			}
			default: {
				PlayerAviationModel[playerid] = INVALID_AVIATION;
			}
		}
	}
}

stock ViewAviation(const playerid) {
	new 
		activ_view = GetPVarInt(playerid, "aviation_view");

	TogglePlayerSpectating(playerid, true);
	format(big_string, sizeof(big_string), ""COLOR_WHITE"%s\n\n"COLOR_ORANGE"Для покупки вертолета используйте - /av_buy\n\
		Для выхода из режима покупки - /av_exit", 
			AviationBuy[activ_view][E_INFO]
	);

	SPD(playerid, DIALOG_BUY_AVIATION, DIALOG_STYLE_MSGBOX, "Покупка вертолета", big_string, "<<<", ">>>");
	switch(activ_view) {
		case 0: {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~Seasparrow~n~~w~190000 EXP", 15000, 6);
			InterpolateCameraPos(playerid, 1945.159179, -2636.312988, 14.468575, 1945.159179, -2636.312988, 14.468575, 864000);
			InterpolateCameraLookAt(playerid, 1941.442626, -2639.585937, 13.779627, 1941.442626, -2639.585937, 13.779627, 864000);
		}
		case 1: {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~Sparrow~n~~w~225000 EXP", 15000, 6);
			InterpolateCameraPos(playerid, 1956.250244, -2636.426757, 14.783007, 1956.250244, -2636.426757, 14.783007, 864000);
			InterpolateCameraLookAt(playerid, 1952.571533, -2639.666503, 13.797574, 1952.571533, -2639.666503, 13.797574, 864000);
		}
		case 2: {
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~Maverick~n~~w~250000 EXP", 15000, 6);
			InterpolateCameraPos(playerid, 1968.272216, -2636.318847, 14.358368, 1968.272216, -2636.318847, 14.358368, 864000);
			InterpolateCameraLookAt(playerid, 1964.588500, -2639.615722, 13.609889, 1964.588500, -2639.615722, 13.609889, 864000);
		}
	}
	return 1;
} 

CMD:av_exit(playerid, params[]) {
	if(GetPVarInt(playerid, "buy_mode") != 1) {
		return 1;
	} else {
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~g~Good luck", 1000, 6);
		ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, "Покупка вертолета", ""COLOR_WHITE"Вы покинули режим покупки", "Закрыть", "");
		TogglePlayerSpectating(playerid, false);
		DeletePVar(playerid, "aviation_view");
		return 1;
	}
}

CMD:av_buy(playerid, params[]) {
	if(GetPVarInt(playerid, "buy_mode") != 1) {
		return 1;
	} else {
		new 
			activ_view = GetPVarInt(playerid, "aviation_view");
			
		switch(activ_view) {
			case 0: {
				format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите купить вертолет "COLOR_GREEN"\"Seasparrow\""COLOR_WHITE" за "COLOR_GREEN"%i EXP?", AviationBuy[0][E_PRICE]);
			}
			case 1: {
				format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите купить вертолет "COLOR_GREEN"\"Sparrow\""COLOR_WHITE" за "COLOR_GREEN"%i EXP?", AviationBuy[1][E_PRICE]);
			}
			case 2: {
				format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите купить вертолет "COLOR_GREEN"\"Maverick\""COLOR_WHITE" за "COLOR_GREEN"%i EXP?", AviationBuy[2][E_PRICE]);
			}
		}
		ShowPlayerDialog(playerid, DIALOG_BUY_AVIATION_ACCEPT, DIALOG_STYLE_MSGBOX, "Покупка вертолета", big_string, "Да", "Нет");
	}
	return 1;
}

DialogCreate:DIALOG_CHANCE_AVIA_COLOR(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_CHANCE_AVIA_COLOR, DIALOG_STYLE_INPUT,
		""COLOR_BLUE"Перекраска личного вертолета",
		""COLOR_WHITE"1. Черный - "COLOR_GREEN"15000 EXP\n\
			"COLOR_WHITE"2. Белый - "COLOR_GREEN"12000 EXP\n\
			"COLOR_WHITE"3. Синий - "COLOR_GREEN"25000 EXP\n\
			"COLOR_WHITE"4. Зеленый - "COLOR_GREEN"27000 EXP\n\
			"COLOR_WHITE"5. Красный - "COLOR_GREEN"50000 EXP"INPUT_NUMBER"", 
		"Выбрать", "Назад"
	);
}

DialogResponse:DIALOG_CHANCE_AVIA_COLOR(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		switch(listitem) {
			case 0: {
				if(CheckCash(playerid, 15000) == false) return 1;
				RemovePlayerEXP(playerid, 15000, "Покраска вертолета в черный цвет");
				SendClientMessage(playerid, -1, "Вы покрасили Ваш личный вертолет в {000000}\"Черный\""COLOR_WHITE" цвет за "COLOR_GREEN"15000 EXP");
				mysql_format(database, small_string, sizeof(small_string), "UPDATE `player_vehicle` SET `Color_1` = 0 WHERE `PlayerID` = %i Type = 'Вертолет'", PlayerInfo[playerid][pID]);
				PlayerAviationColor[playerid] = 0;
				if(PlayerAviationVehicleID[playerid] != INVALID_VEHICLE_ID) {
					ChangeVehicleColor(PlayerAviationVehicleID[playerid], 0, 1);
				}
			}
			case 1: {
				if(CheckCash(playerid, 12000) == false) return 1;
				RemovePlayerEXP(playerid, 12000, "Покраска вертолета в белый цвет");
				SendClientMessage(playerid, -1, "Вы покрасили Ваш личный вертолет в {ffffff}\"Белый\""COLOR_WHITE" цвет за "COLOR_GREEN"12000 EXP");
				mysql_format(database, small_string, sizeof(small_string), "UPDATE `player_vehicle` SET `Color_1` = 1 WHERE `PlayerID` = %i AND Type = 'Вертолет'", PlayerInfo[playerid][pID]);
				PlayerAviationColor[playerid] = 1;
				if(PlayerAviationVehicleID[playerid] != INVALID_VEHICLE_ID) {
					ChangeVehicleColor(PlayerAviationVehicleID[playerid], 1, 1);
				}
			}
			case 2: {
				if(CheckCash(playerid, 25000) == false) return 1;
				RemovePlayerEXP(playerid, 25000, "Покраска вертолета в синий цвет");
				SendClientMessage(playerid, -1, "Вы покрасили Ваш личный вертолет в {2A77A1}\"Синий\""COLOR_WHITE" цвет за "COLOR_GREEN"25000 EXP");
				mysql_format(database, small_string, sizeof(small_string), "UPDATE `player_vehicle` SET `Color_1` = 2 WHERE `PlayerID` = %i AND Type = 'Вертолет'", PlayerInfo[playerid][pID]);
				PlayerAviationColor[playerid] = 2;
				if(PlayerAviationVehicleID[playerid] != INVALID_VEHICLE_ID) {
					ChangeVehicleColor(PlayerAviationVehicleID[playerid], 2, 1);
				}
			}
			case 3: {
				if(CheckCash(playerid, 27000) == false) return 1;
				RemovePlayerEXP(playerid, 27000, "Покраска вертолета в зеленый цвет");
				SendClientMessage(playerid, -1, "Вы покрасили Ваш личный вертолет в {335F3E}\"Зеленый\""COLOR_WHITE" цвет за "COLOR_GREEN"27000 EXP");
				mysql_format(database, small_string, sizeof(small_string), "UPDATE `player_vehicle` SET `Color_1` = 16 WHERE `PlayerID` = %i AND Type = 'Вертолет'", PlayerInfo[playerid][pID]);
				PlayerAviationColor[playerid] = 16;
				if(PlayerAviationVehicleID[playerid] != INVALID_VEHICLE_ID) {
					ChangeVehicleColor(PlayerAviationVehicleID[playerid], 16, 1);
				}
			}
			case 4: {
				if(CheckCash(playerid, 50000) == false) return 1;
				RemovePlayerEXP(playerid, 50000, "Покраска вертолета в красный цвет");
				SendClientMessage(playerid, -1, "Вы покрасили Ваш личный вертолет в "COLOR_RED"\"Красный\""COLOR_WHITE" цвет за "COLOR_GREEN"50000 EXP");
				mysql_format(database, small_string, sizeof(small_string), "UPDATE `player_vehicle` SET `Color_1` = 3 WHERE `PlayerID` = %i AND Type = 'Вертолет'", PlayerInfo[playerid][pID]);
				PlayerAviationColor[playerid] = 3;
				if(PlayerAviationVehicleID[playerid] != INVALID_VEHICLE_ID) {
					ChangeVehicleColor(PlayerAviationVehicleID[playerid], 3, 1);
				}
			}
		}
		mysql_pquery(database, small_string);
	}
	return 1;
}

DialogCreate:DIALOG_SELL_AVIA(playerid) {
	new 
		time = PlayerSellAviaTime[playerid];		

	new 
		model = PlayerAviationModel[playerid],
		cash = 0;

	switch(model) {
		case 447: {
			cash = AviationBuy[0][E_PRICE] / 2;
		}
		case 469: {
			cash = AviationBuy[1][E_PRICE] / 2;
		}
		case 487: {
			cash = AviationBuy[2][E_PRICE] / 2;
		}
	}

	if(time >= 0) {
		format(small_string, sizeof(small_string), "Да (%i)", time);
		format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите продать свой вертолет за "COLOR_GREEN"%i EXP?\n\n"COLOR_RED"Принять предложение продажи можно будет через 10 секунд.",  cash);
		return Dialog_Open(playerid, Dialog:DIALOG_SELL_AVIA, DIALOG_STYLE_MSGBOX,
			""COLOR_BLUE"Продажа личного вертолета",
			big_string, 
			small_string, "Нет"
		);
	} else {
		format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы уверены, что хотите продать свой вертолет за "COLOR_GREEN"%i EXP?", cash);
		return Dialog_Open(playerid, Dialog:DIALOG_SELL_AVIA, DIALOG_STYLE_MSGBOX,
			""COLOR_BLUE"Продажа личного вертолета",
			big_string, 
			"Да", "Нет"
		);
	}

}

DialogResponse:DIALOG_SELL_AVIA(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		if(GetPVarInt(playerid, "sell_avia") > gettime()) {
			return Dialog_Show(playerid, Dialog:DIALOG_SELL_AVIA);
		}

		new 
			model = PlayerAviationModel[playerid],
			cash = 0;

		switch(model) {
			case 447: {
				cash = AviationBuy[0][E_PRICE] / 2;
			}
			case 469: {
				cash = AviationBuy[1][E_PRICE] / 2;
			}
			case 487: {
				cash = AviationBuy[2][E_PRICE] / 2;
			}
		}

		AddPlayerEXP(playerid, cash, "Продажа частного вертолета");
		if(PlayerAviationVehicleID[playerid] != INVALID_VEHICLE_ID && IsValidVehicle(PlayerAviationVehicleID[playerid])) {
			DestroyVehicle(PlayerAviationVehicleID[playerid]);
		}
		PlayerAviationVehicleID[playerid] = INVALID_VEHICLE_ID;
		PlayerAviationColor[playerid] = 0;
		PlayerAviationModel[playerid] = INVALID_AVIATION;
		
		mysql_format(database, small_string, sizeof(small_string), "DELETE FROM `player_vehicle` WHERE `PlayerID` = %i AND Type = 'Вертолет'", PlayerInfo[playerid][pID]);
		mysql_pquery(database, small_string);

		format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы продали свой личный вертолет за "COLOR_GREEN"%i EXP", cash);
		SendClientMessage(playerid, -1, small_string);

		if(PlayerCPSpawnAvia[playerid] != -1 && IsValidDynamicCP(PlayerCPSpawnAvia[playerid])) {
			DestroyDynamicCP(PlayerCPSpawnAvia[playerid]);
		}
	}
	return 1;
}

DialogCreate:DIALOG_MANAGER_AVIA(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_MANAGER_AVIA, DIALOG_STYLE_LIST,
		""COLOR_BLUE"Управление личным вертолетом",
		""COLOR_WHITE"1. Перекраска вертолета\n"COLOR_RED"2. Продажа государству", 
		"Далее", "Закрыть"
	);
}

DialogResponse:DIALOG_MANAGER_AVIA(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		if(PlayerAviationModel[playerid] == INVALID_AVIATION) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет личного вертолета");
		}

		switch(listitem) {
			// Перекраска
			case 0: {
				if(PlayerAviationModel[playerid] != 487) {
					SendClientMessage(playerid, -1, ""COLOR_ORANGE"Перекраска доступна только для вертолета марки \"Maverick\"");
					return Y_HOOKS_CONTINUE_RETURN_1;
				} else {
					return Dialog_Show(playerid, Dialog:DIALOG_CHANCE_AVIA_COLOR);
				}
			}
			// Продажа
			case 1: {
				PlayerSellAviaTime[playerid] = 10;
				Dialog_Show(playerid, Dialog:DIALOG_SELL_AVIA);
				defer SellAvia(playerid);
				return 1;
			}
			default: {
				return Dialog_Show(playerid, Dialog:DIALOG_MANAGER_AVIA);
			}
		}
	}
	return 1;
}

timer SellAvia[1000](playerid) {
	if(!Dialog_IsOpen(playerid)) {
		return 0;
	}

	new 
		time = PlayerSellAviaTime[playerid];

	if(time >= 0) {
		PlayerSellAviaTime[playerid] = time - 1;
		Dialog_Show(playerid, Dialog:DIALOG_SELL_AVIA);
	
		defer SellAvia(playerid);
	} else {
		PlayerSellAviaTime[playerid] = -1;
	}
	return 1;
}
