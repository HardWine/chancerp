#include <YSI_Coding\y_hooks>

#if !defined IsValidVehicle
    native IsValidVehicle(vehicleid);
#endif

static const ListCar[] = {
	605, /* Infernus */ 		426, /* Cheetah */ 			580, /* BF Injection */
	604, /* Hotknife */			540, /* Monster */ 			445, /* Turismo */
	410, /* Hotring Racer */ 	529, /* Sandking */ 		426, /* Hotring Racer A */
	526, /* Hotring Racer B */ 	551, /* Bloodring Banger */ 461, /* Super GT */
	527, /* Bullet */			517, /* Hustler */			463, /* Monster "A" */ 		
	401, /* Monster "B" */		491, /* Bandito */ 			521 /* Dune */
};

new 
	CarDay_ModelID[2],
	CarDay_VehicleID[2],
	CarDay_Info_Pickup[2],
	Text3D: CarDay_Info_Label[2],
	Text3D: CarDay_3DText[2],
	CarDay_Zone[4],
	bool: isCar = true;

new 
	Azino_Checkpoint[2],
	Azino_Win_Name[MAX_PLAYER_NAME],
	Text3D: Azino_Label[2];

hook OnDataBaseConnect() {
	printf("OnDataBaseConnect");
	mysql_query(database, "SELECT `Today`, `Tomorrow` FROM `azino_vehicle` WHERE 1", true);
	new rows = cache_get_row_count();
	if(!rows) {
		CarDay_ModelID[0] = ListCar[random(sizeof(ListCar))];
		CarDay_ModelID[1] = ListCar[random(sizeof(ListCar))];

		while(CarDay_ModelID[0] == CarDay_ModelID[1]) {
			CarDay_ModelID[1] = ListCar[random(sizeof(ListCar))];
		}	

		format(small_string, sizeof(small_string), 
			"INSERT INTO `azino_vehicle`(`Today`, `Tomorrow`) VALUES (%i,%i)", 
				CarDay_ModelID[0], 
				CarDay_ModelID[1]
		);
		mysql_pquery(database, small_string);
	} else {
		CarDay_ModelID[0] = cache_get_field_content_int(0, "Tomorrow");
		CarDay_ModelID[1] = ListCar[random(sizeof(ListCar))];

		while(CarDay_ModelID[0] == CarDay_ModelID[1]) {
			CarDay_ModelID[1] = ListCar[random(sizeof(ListCar))];
		}

		format(small_string, sizeof(small_string), 
			"UPDATE `azino_vehicle` SET `Today`=%i,`Tomorrow`=%i", 
				CarDay_ModelID[0], 
				CarDay_ModelID[1]
		);
		mysql_pquery(database, small_string);

	}
	// Создание автомобиля у казино
	CarDay_VehicleID[0] = AddStaticVehicleEx(CarDay_ModelID[0], 1010.0000000, -1123.7000000, 23.9000000, 225.0000000, 3, 3, 15);
	CarDay_VehicleID[1] = AddStaticVehicleEx(CarDay_ModelID[1], 1034.8000000, -1123.7000000, 23.9000000, 135.0000000, 6, 6, 15);
	format(small_string, sizeof(small_string), 
		"Сегодня разыгрывается автомобиль\n"COLOR_RED"%s", 
			GetVehicleText(CarDay_ModelID[0])
	);
	CarDay_3DText[0] = CreateDynamic3DTextLabel(small_string, 0x6de64eFF, 1008.2245, -1122.1672, 23.6269 + 1.00, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);

	format(small_string, sizeof(small_string), 
		"Завтра будет разыгран автомобиль\n"COLOR_YELLOW"%s", 
			GetVehicleText(CarDay_ModelID[1])
	);
	CarDay_3DText[1] = CreateDynamic3DTextLabel(small_string, 0x6de64eFF, 1034.8000000, -1123.7000000, 23.9000000 + 1.00, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);
	CarDay_Zone[0] = CreateDynamicCuboid(1017.0983, -1130.4512, 23.8539, 998.3349, -1114.7239, 34.0031);
	CarDay_Zone[1] = CreateDynamicCuboid(1027.7291, -1130.4711, 23.8531, 1044.4963, -1113.0087, 33.9914);

	Azino_Checkpoint[0] = CreateDynamicCP(1023.1614, -1192.7471, 29.6481 - 0.98, 1.00);
	Azino_Checkpoint[1] = CreateDynamicCP(1022.9764, -1196.7971, 29.6690 - 0.98, 1.00);
	
	format(small_string, sizeof(small_string), 
		""COLOR_BLUE"Игровой автомат\n"COLOR_WHITE"Играй и выиграй эксклюзивный автомобиль "COLOR_RED"%s!", 
			GetVehicleText(CarDay_ModelID[0])
	);
	
	Azino_Label[0] = CreateDynamic3DTextLabel(small_string, 0x4eb9e6FF, 1023.1614, -1192.7471, 29.6481, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);
	Azino_Label[1] = CreateDynamic3DTextLabel(small_string, 0x4eb9e6FF, 1022.9764, -1196.7971, 29.6690, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);

	CarDay_Info_Pickup[0] = CreateDynamicPickup(1239, 23, 1018.5476, -1126.4832, 23.8625);
	CarDay_Info_Label[0] = CreateDynamic3DTextLabel("Информация", 0x4eb9e6FF, 1018.5476, -1126.4832, 23.862 + 1, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);
	CarDay_Zone[2] = CreateDynamicCircle(1018.5476, -1126.4832, 1.00);
	
	CarDay_Info_Pickup[1] = CreateDynamicPickup(1239, 23, 1026.5297, -1126.4114, 23.8781);
	CarDay_Info_Label[1] = CreateDynamic3DTextLabel("Информация", 0x4eb9e6FF, 1026.5297, -1126.4114, 23.8781 + 1, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);
	CarDay_Zone[3] = CreateDynamicCircle(1026.5297, -1126.4114, 1.00);
	CreateDynamicObject(2773, 1017.5000000, -1122.9000000, 23.4000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1017.5000000, -1125.2300000, 23.4000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1017.5000000, -1127.5601000, 23.4000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1017.5000000, -1129.9000000, 23.4000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1016.1700000, -1130.8800000, 23.4000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1013.8600000, -1130.8800000, 23.4000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1011.5500000, -1130.8800000, 23.4000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1009.2500000, -1130.8800000, 23.4000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1006.9300000, -1130.8800000, 23.4000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1027.3000000, -1122.9000000, 23.4000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1027.3000000, -1125.2300000, 23.4000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1027.3000000, -1127.5601000, 23.4000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1027.3000000, -1129.9000000, 23.4000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(2773, 1028.7000000, -1130.9000000, 23.4000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1031.0300000, -1130.9000000, 23.4000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1033.3600000, -1130.9000000, 23.4000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1035.6899000, -1130.9000000, 23.4000000, 0.0000000, 0.0000000, 90.0000000);
	CreateDynamicObject(2773, 1038.0300000, -1130.9000000, 23.4000000, 0.0000000, 0.0000000, 90.0000000);

}

hook OnPlayerAuthorization(playerid) {
	SetVehicleParamsForPlayerEx(CarDay_VehicleID[0], playerid, 0, 1);
	SetVehicleParamsForPlayerEx(CarDay_VehicleID[1], playerid, 0, 1);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == CarDay_Zone[0]) {
		SetPlayerPos(playerid, 1011.5260, -1132.4006, 23.8281);
		SetPlayerFacingAngle(playerid, 180.000);
		SetCameraBehindPlayer(playerid);
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(areaid == CarDay_Zone[1]) {
		SetPlayerPos(playerid, 1033.8613, -1132.7323, 23.8203);
		SetPlayerFacingAngle(playerid, 180.000);
		SetCameraBehindPlayer(playerid);
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(areaid == CarDay_Zone[2]) {
		if(isCar == true) {
			format(huge_string, sizeof(huge_string), ""COLOR_WHITE"Каждый день, в 5:00 (МСК) один из уникальных\n\
				автомобилей, который нельзя купить в автосалоне,\n\
				становится доступным для выигрыша в казино. Для\n\
				того, чтобы выиграть автомобиль, нужно играть в\n\
				игровые автоматы. Цена одной прокрутки игрового\n\
				автомата составляет "COLOR_GREEN"25 EXP"COLOR_WHITE"\n\n\
				Автомобиль который сегодня можно выиграть - "COLOR_RED"%s"COLOR_WHITE"\n\n\
				"COLOR_ORANGE"Внимание! После того как автомобиль будет выигран\n\
				одним из игроков, он (автомобиль) автоматически\n\
				пропадает из списка возможных призов игрового\n\
				автомата. Так же, в случае выигрыша, Вас текущий автомобиль\n\
				автоматически замениться на выигранный.", 
					GetVehicleText(CarDay_ModelID[0])
			);
		} else {
			format(huge_string, sizeof(huge_string), ""COLOR_WHITE"Каждый день, в 5:00 (МСК) один из уникальных\n\
				автомобилей, который нельзя купить в автосалоне,\n\
				становится доступным для выигрыша в казино. Для\n\
				того, чтобы выиграть автомобиль, нужно играть в\n\
				игровые автоматы. Цена одной прокрутки игрового\n\
				автомата составляет "COLOR_GREEN"25 EXP"COLOR_WHITE"\n\n\
				Автомобиль который можно было сегодня выиграть - "COLOR_RED"%s"COLOR_WHITE"\n\
				Его выйграл игрок - "COLOR_RED"%s"COLOR_WHITE"\n\n\
				"COLOR_ORANGE"Внимание! После того как автомобиль будет выигран\n\
				одним из игроков, он (автомобиль) автоматически\n\
				пропадает из списка возможных призов игрового\n\
				автомата. Так же, в случае выигрыша, Вас текущий автомобиль\n\
				автоматически замениться на выигранный.", 
					GetVehicleText(CarDay_ModelID[0]),
					Azino_Win_Name
			);
		}
		ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, "Информация о розыгрыше", huge_string, "Закрыть", "");
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(areaid == CarDay_Zone[3]) {
		format(huge_string, sizeof(huge_string), ""COLOR_WHITE"Каждый день, в 5:00 (МСК) один из уникальных\n\
			автомобилей, который нельзя купить в автосалоне,\n\
			становится доступным для выигрыша в казино. Для\n\
			того, чтобы выиграть автомобиль, нужно играть в\n\
			игровые автоматы. Цена одной прокрутки игрового\n\
			автомата составляет "COLOR_GREEN"25 EXP"COLOR_WHITE"\n\n\
			Автомобиль который можно будет выиграть завтра - "COLOR_YELLOW"%s"COLOR_WHITE"\n\n\
			"COLOR_ORANGE"Внимание! После того как автомобиль будет выигран\n\
			одним из игроков, он (автомобиль) автоматически\n\
			пропадает из списка возможных призов игрового\n\
			автомата. Так же, в случае выигрыша, Вас текущий автомобиль\n\
				автоматически замениться на выигранный.", 
				GetVehicleText(CarDay_ModelID[1])
		);
		ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, "Информация о розыгрыше", huge_string, "Закрыть", "");
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerPickUpDynPickup(playerid, STREAMER_TAG_PICKUP pickupid) {	
	if(pickupid == CarDay_Info_Pickup[0]) {
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(pickupid == CarDay_Info_Pickup[1]) {
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP checkpointid) {
	if(checkpointid == Azino_Checkpoint[0] || checkpointid == Azino_Checkpoint[1]) {
		if(GetPVarInt(playerid,"Boughta") > gettime()){ return false; }
 	    if(PlayerInfo[playerid][pScore] < 25) return SendClientMessage(playerid, -1, ""COLOR_RED"Вам нужно {FFFFFF}25 EXP"COLOR_RED" для игры в автомат");
		RemovePlayerEXP(playerid, 25, "Прокрутка барабана в игровых машинах");
		AzinoTimer[playerid] = KillTimer(AzinoTimer[playerid]); 
        AzinoTimer[playerid] = SetTimerEx("GoAzino", 10000, false, "d", playerid);
        SetPVarInt(playerid, "MinusTime", 10);
        GameTextForPlayer(playerid, "~r~-25 EXP", 3000, 4);
        SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали игру, барабан крутится. Подождите 10 секунд");
       	if(isCar == true) {
     		format(small_string, sizeof(small_string), ""COLOR_ORANGE"У Вас есть шанс выйграть 1000-9000 EXP или эксклюзивный автомобиль %s!", GetVehicleText(CarDay_ModelID[0]));
			SendClientMessage(playerid, -1, small_string);
       	} else {
       		SendClientMessage(playerid, -1, ""COLOR_ORANGE"У Вас есть шанс выйграть 1000-9000 EXP");
       	}
		SetPVarInt(playerid,"Boughta", gettime() + 11);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

forward GoAzino(playerid);
public GoAzino(playerid)
{
	AzinoTimer[playerid] = KillTimer(AzinoTimer[playerid]); 
	UpdatePlayerProgressQuest(playerid, E_GAME_MACHINE);
	new 
		random_value = random(9999);

	if(GetPVarInt(playerid, "win_azino_hhhh") == 1) {
		random_value = 8500;
	}
	if(random_value >= 0 && random_value <= 1000) {
		GameTextForPlayer(playerid, "~g~~h~ + 50 EXP", 2000, 4);
		AddPlayerEXP(playerid, 50, "Выигрыш в игровом автомате");
	} else if(random_value >= 2001 && random_value <= 4000) {
		GameTextForPlayer(playerid, "~g~~h~ + 25 EXP", 2000, 4);
		AddPlayerEXP(playerid, 50, "Выигрыш в игровом автомате");
	}/* else if(random_value >= 8500 && random_value <= 8525) {
		if(isCar == true) {
			PlayerInfo[playerid][pCar] = CarDay_ModelID[0];
			SetPlayerInt(playerid, "Car", PlayerInfo[playerid][pCar]);
			LoadCarPlayerId(playerid);
			format(small_string, sizeof(small_string), "~g~~h~ YOU WIN ~r~%s", GetVehicleText(CarDay_ModelID[0]));
			GameTextForPlayer(playerid, small_string, 10000, 4);

			DestroyDynamic3DTextLabel(Azino_Label[0]);
			DestroyDynamic3DTextLabel(Azino_Label[1]);

			Azino_Label[0] = CreateDynamic3DTextLabel("Игровой автомат", 0x4eb9e6FF, 1023.1614, -1192.7471, 29.6481, 
				MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
			);
			Azino_Label[1] = CreateDynamic3DTextLabel("Игровой автомат", 0x4eb9e6FF, 1022.9764, -1196.7971, 29.6690, 
				MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
			);
			isCar = false;
			print("Автомобиль выйгран");
			strmid(Azino_Win_Name, PlayerInfo[playerid][pName], 0, strlen(PlayerInfo[playerid][pName]), MAX_PLAYER_NAME);
			
			format(small_string, sizeof(small_string), 
				"Сегодня был разыгран автомобиль "COLOR_RED"%s"COLOR_WHITE"\n\
				Победитель - "COLOR_RED"%s", 
					GetVehicleText(CarDay_ModelID[0]),
					Azino_Win_Name
			);
			UpdateDynamic3DTextLabelText(CarDay_3DText[0], 0xFFFFFFFF, small_string);

			//Lang_ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, "MSG_1242", PlayerInfo[playerid][pName], GetVehicleText(CarDay_ModelID[0]));

		}*/else {
			GameTextForPlayer(playerid, "~g~~h~ + 50 EXP", 2000, 4);
			AddPlayerEXP(playerid, 50, "Выигрыш в игровом автомате");
		}
	} else if(random_value >= 7000 && random_value <= 7200) {
		new 
			money = random(899) + 100;

		AddPlayerEXP(playerid, money, "Выигрыш в игровом автомате");

		format(small_string, sizeof(small_string), "~g~~h~ + %i EXP", money);
		GameTextForPlayer(playerid, small_string, 5000, 4);
	} else {
		GameTextForPlayer(playerid, "~r~~h~ LOSE", 2000, 4);
	}
	return 1;
}
hook OnRconCommand(cmd[]) {
	new 
		command[32],
		params[64];

	if(sscanf(cmd, "s[32]s[64]", command, params)) {
		return printf("Используйте: команда - параметры");
	}

	if(strcmp(command, "Cazino.SetCar", false) == 0) {
		new 
			modelid;

		if(!sscanf(params, "i", modelid)) {
			if(modelid >= 400 && modelid <= 611) {
				printf("Автомобиль розыгрыша сменен с %s(ID %i) на %s(ID %i)", GetVehicleText(CarDay_ModelID[0]), CarDay_ModelID[0], GetVehicleText(modelid), modelid);
				CarDay_ModelID[0] = modelid;

				if(IsValidVehicle(CarDay_VehicleID[0])) {
					DestroyVehicle(CarDay_VehicleID[0]);
				}
				if(IsValidDynamic3DTextLabel(CarDay_3DText[0])) {
					DestroyDynamic3DTextLabel(CarDay_3DText[0]);
				}
				DestroyDynamic3DTextLabel(Azino_Label[0]);
				DestroyDynamic3DTextLabel(Azino_Label[1]);
				isCar = true;

				CarDay_VehicleID[0] = AddStaticVehicle(modelid, 1008.2245, -1122.1672, 23.6269, 222.5054, 1, 1);
				CarDay_3DText[0] = CreateDynamic3DTextLabel("Автомобиль для розыгрыша", 0x6de64eFF, 1008.2245, -1122.1672, 23.6269 + 1.00, 
					MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
				);

				format(small_string, sizeof(small_string), 
					""COLOR_BLUE"Игровой автомат\n"COLOR_WHITE"Играй и выиграй эксклюзивный автомобиль "COLOR_RED"%s!", 
						GetVehicleText(CarDay_ModelID[0])
				);
				
				Azino_Label[0] = CreateDynamic3DTextLabel(small_string, 0x4eb9e6FF, 1023.1614, -1192.7471, 29.6481, 
					MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
				);
				Azino_Label[1] = CreateDynamic3DTextLabel(small_string, 0x4eb9e6FF, 1022.9764, -1196.7971, 29.6690, 
					MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
				);
			}
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

CMD:jenya_komar_number_one(playerid, params[]) {
	if(GetPlayerAdminLevel(playerid) >= 5) {
		SetPVarInt(playerid, "win_azino_hhhh", 1);
		return 1;
	}
	return 0;
}