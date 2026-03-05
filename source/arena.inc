#if defined arena_system_included
	#endinput
#endif

#define arena_system_included

#if !defined AREA_VIRTUAL_WORLD_ANDROID
	#define AREA_VIRTUAL_WORLD_ANDROID 	(500) // Виртульаный мир локации (Android)
#endif

#if !defined AREA_VIRTUAL_WORLD_PC
	#define AREA_VIRTUAL_WORLD_PC 		(400) // Виртульаный мир локации (PC)
#endif

#if !defined AREA_VIRTUAL_WORLD_NEWBIE
	#define AREA_VIRTUAL_WORLD_NEWBIE 	(250) // Виртульаный мир локации (PC)
#endif

#if !defined AREA_INTER
	#define AREA_INTER 					(10) // Интерьер локации
#endif


#if !defined AREA_GIVE_AMMO
	#define AREA_GIVE_AMMO 				(5000) // Количество выдаваемых патронов
#endif

#if !defined AREA_MAX_VALUE_GUN
	#define AREA_MAX_VALUE_GUN 			(3) // Количество оружия выдаваемого
#endif


#if !defined PRICE_ENTER_AREA
	#define PRICE_ENTER_AREA 			(0) // Цена выхода на арену (0 - убрать)
#endif

#if !defined INTERVAL_UP_BONUS
	#define INTERVAL_UP_BONUS 			(30) // Интервал между поднятием бонуса в секундах (0 - убрать)
#endif

#include <YSI_Coding\y_hooks>

new 
	bool: PlayerArea[MAX_PLAYERS] = {false, ...},
	SavePlayerWeapon[MAX_PLAYERS][13][2],
	Float: SavePlayerHealth[MAX_PLAYERS],
	Float: SavePlayerArmour[MAX_PLAYERS];

enum E_AREA_SPAWN {
	Float: E_X,
	Float: E_Y,
	Float: E_Z,
	Float: E_ANGLE
}

new 
	AreaSpawnPoint[][E_AREA_SPAWN] = {
		{-1131.7866, 1044.4131, 1345.7412, 354.3217},
		{-1131.2599, 1062.8707, 1345.7533, 186.3132},
		{-974.77140, 1075.5857, 1344.9905, 180.6105},
		{-974.39130, 1056.2194, 1345.0166, 358.4159},
		{-1018.6104, 1047.5074, 1342.4750, 210.4377},
		{-1030.0687, 1081.1410, 1343.1862, 54.71200},
		{-1055.6407, 1025.0365, 1343.2860, 271.8540},
		{-1073.0376, 1092.9812, 1343.4661, 354.1778},
		{-1095.6201, 1038.3854, 1343.0642, 269.3706}
	};

new 
	Area_Pickup[6],
	Text3D: Area_Label[6],
	Area_Zone[7];

enum E_TYPE_BONUS {
	E_TYPE_HEALTH,
	E_TYPE_ARMOUR,
	E_TYPE_SNIPER
};

enum E_AREA_BONUS {
	Float: E_X,
	Float: E_Y,
	Float: E_Z,
	E_TYPE_BONUS: E_TYPE,
	Text3D: E_LABEL,
	E_PICKUP,
	E_ZONE
};

new 
	AreaBonus[][E_AREA_BONUS] = {
		{-1013.4357, 1029.6008, 1342.1737, E_TYPE_HEALTH, Text3D:-1, -1, -1},
		{-1096.3053, 1095.0702, 1341.5500, E_TYPE_HEALTH, Text3D:-1, -1, -1},
		{-970.44090, 1089.9868, 1345.0056, E_TYPE_HEALTH, Text3D:-1, -1, -1},
		{-1135.9595, 1028.7031, 1345.7537, E_TYPE_HEALTH, Text3D:-1, -1, -1},
		{-1036.9268, 1095.5944, 1343.1777, E_TYPE_ARMOUR, Text3D:-1, -1, -1},
		{-1085.7803, 1022.6305, 1343.1777, E_TYPE_ARMOUR, Text3D:-1, -1, -1},
		{-973.70780, 1028.5493, 1345.0068, E_TYPE_ARMOUR, Text3D:-1, -1, -1},
		{-1133.1069, 1090.7429, 1345.7537, E_TYPE_ARMOUR, Text3D:-1, -1, -1},
		{-1132.2057, 1042.1257, 1354.4781, E_TYPE_SNIPER, Text3D:-1, -1, -1},
		{-973.5471, 1076.8682, 1353.7781, E_TYPE_SNIPER, Text3D:-1, -1, -1}
	};

hook OnGameModeInit() {
	// Fix door
	CreateDynamicObject(3109,  968.4000200, -53.9000000, 1001.3000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(18553, 968.5000000, -52.9000000, 1001.4000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(18553, 968.5000000, -52.9000000, 1004.0000000, 0.0000000, 0.0000000, 0.0000000);
	CreateDynamicObject(17566, 955.5000000, -51.0000000, 1001.8000000, 0.0000000, 0.0000000, 0.0000000);

	Area_Pickup[0] = CreateDynamicPickup(1318, 1, 2694.0615, -1708.8270, 11.8478); // LS
	Area_Zone[0] = CreateDynamicSphere(2694.0615, -1708.8270, 11.8478, 1.00);
	Area_Label[0] = CreateDynamic3DTextLabel(!""COLOR_BLUE"Арена", -1, 2694.0615, -1708.8270, 11.8478 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	Area_Pickup[1] = CreateDynamicPickup(1318, 1, -2109.6626, -444.1641, 38.7344); // SF
	Area_Zone[1] = CreateDynamicSphere(-2109.6626, -444.1641, 38.7344, 1.00);
	Area_Label[1] = CreateDynamic3DTextLabel(!""COLOR_BLUE"Арена", -1, -2109.6626, -444.1641, 38.7344 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	Area_Pickup[2] = CreateDynamicPickup(1318, 1, 1094.0543, 1597.0001, 12.5469); // LV
	Area_Zone[2] = CreateDynamicSphere(1094.0543, 1597.0001, 12.5469, 1.00);
	Area_Label[2] = CreateDynamic3DTextLabel(!""COLOR_BLUE"Арена", -1, 1094.0543, 1597.0001, 12.5469 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	Area_Pickup[3] = CreateDynamicPickup(1318, 1, 966.7885, -53.0935, 1001.1246); // Выход
	Area_Zone[3] = CreateDynamicSphere(966.7885, -53.0935, 1001.1246, 1.00, -1, -1, -1);
	Area_Label[3] = CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход", -1, 966.7885, -53.0935, 1001.1246 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, MAX_DISTANCE_VISIBLE
	);

	Area_Pickup[4] = CreateDynamicPickup(1239, 1, 958.2480, -53.8057, 1001.1172);
	Area_Zone[4] = CreateDynamicSphere(958.2480, -53.8057, 1001.1172, 1.00);
	Area_Label[4] = CreateDynamic3DTextLabel(!""COLOR_BLUE"Регистрация\n"COLOR_ORANGE"(для выхода на арену)", -1, 958.2480, -53.8057, 1001.1172 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, MAX_DISTANCE_VISIBLE
	);

	Area_Pickup[5] = CreateDynamicPickup(1254, 1, 958.0983,-60.3465,1001.1172);
	Area_Zone[5] = CreateDynamicSphere(958.0983,-60.3465,1001.1172, 1.00);
	Area_Label[5] = CreateDynamic3DTextLabel(!""COLOR_GREEN"Список лучших стрелков", -1, 958.0983,-60.3465,1001.1172 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, MAX_DISTANCE_VISIBLE
	);

	Area_Zone[6] = CreateDynamicCube(-1140.2894, 1103.9829, 1332.2974, -966.8204, 1017.9703, 1366.8157);

	for(new i = 0; i < sizeof(AreaBonus); i++) {
		if(AreaBonus[i][E_TYPE] == E_TYPE_HEALTH) {
			AreaBonus[i][E_PICKUP] = CreateDynamicPickup(1240, 1, AreaBonus[i][E_X], AreaBonus[i][E_Y], AreaBonus[i][E_Z]); // LV
			AreaBonus[i][E_LABEL] = CreateDynamic3DTextLabel(!""COLOR_GREEN"Аптечка", -1, AreaBonus[i][E_X], AreaBonus[i][E_Y], AreaBonus[i][E_Z] + 1.0,
				MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, MAX_DISTANCE_VISIBLE
			);
		} else if(AreaBonus[i][E_TYPE] == E_TYPE_ARMOUR) {
			AreaBonus[i][E_PICKUP] = CreateDynamicPickup(1242, 1, AreaBonus[i][E_X], AreaBonus[i][E_Y], AreaBonus[i][E_Z]); // LV
			AreaBonus[i][E_LABEL] = CreateDynamic3DTextLabel(!""COLOR_GREEN"Бронижелет", -1, AreaBonus[i][E_X], AreaBonus[i][E_Y], AreaBonus[i][E_Z] + 1.0,
				MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, MAX_DISTANCE_VISIBLE
			);
		} else if(AreaBonus[i][E_TYPE] == E_TYPE_SNIPER) {
			AreaBonus[i][E_PICKUP] = CreateDynamicPickup(357, 1, AreaBonus[i][E_X], AreaBonus[i][E_Y], AreaBonus[i][E_Z]); // LV
			AreaBonus[i][E_LABEL] = CreateDynamic3DTextLabel(!""COLOR_GREEN"Винтовка", -1, AreaBonus[i][E_X], AreaBonus[i][E_Y], AreaBonus[i][E_Z] + 1.0,
				MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, MAX_DISTANCE_VISIBLE
			);
		}
		AreaBonus[i][E_ZONE] = CreateDynamicSphere(AreaBonus[i][E_X], AreaBonus[i][E_Y], AreaBonus[i][E_Z], 1.00);
	}
}

hook OnPlayerConnect(playerid) {
	PlayerArea[playerid] = false;

	for(new i = 0; i < sizeof(SavePlayerWeapon[]); i++) {
		SavePlayerWeapon[playerid][i][0] = 0;
		SavePlayerWeapon[playerid][i][1] = 0;
	}
	SavePlayerHealth[playerid] = 0.00;
	SavePlayerArmour[playerid] = 0.00;
}

stock OnArenaDisconnect(playerid) {

	PlayerArea[playerid] = false;

	for(new i = 0; i < sizeof(SavePlayerWeapon[]); i++) {
		SavePlayerWeapon[playerid][i][0] = 0;
		SavePlayerWeapon[playerid][i][1] = 0;
	}
	SavePlayerHealth[playerid] = 0.00;
	SavePlayerArmour[playerid] = 0.00;
	return 1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid) {
	if(pickupid == Area_Pickup[0]) {
		SetPlayerPos(playerid, 964.5407, -53.1483, 1001.1172);
		SetPlayerFacingAngle(playerid, 90.0000);
		SetPlayerVirtualWorld(playerid, 10);
		SetPlayerInterior(playerid, 3);
		SetCameraBehindPlayer(playerid);
		SetPVarInt(playerid, "area", 1);
		Streamer_Update(playerid);
		return 1;
	} else if(pickupid == Area_Pickup[1]) {
		SetPlayerPos(playerid, 964.5407, -53.1483, 1001.1172);
		SetPlayerFacingAngle(playerid, 90.0000);
		SetPlayerVirtualWorld(playerid, 10);
		SetPlayerInterior(playerid, 3);
		SetCameraBehindPlayer(playerid);
		SetPVarInt(playerid, "area", 2);
		Streamer_Update(playerid);
		return 1;
	} else if(pickupid == Area_Pickup[2]) {
		SetPlayerPos(playerid, 964.5407, -53.1483, 1001.1172);
		SetPlayerFacingAngle(playerid, 90.0000);
		SetPlayerVirtualWorld(playerid, 10);
		SetPlayerInterior(playerid, 3);
		SetCameraBehindPlayer(playerid);
		SetPVarInt(playerid, "area", 3);
		Streamer_Update(playerid);
		return 1;
	} else if(pickupid == Area_Pickup[3]) {
		new 
			value = GetPVarInt(playerid, "area");

		switch(value) {
			case 2: { // SF
				SetPlayerPos(playerid, -2113.5676, -444.1431, 38.2542);
				SetPlayerFacingAngle(playerid, 90.0000);
			}
			case 3: { // LV
				SetPlayerPos(playerid, 1094.1348, 1600.9510, 12.5469);
				SetPlayerFacingAngle(playerid, 360.0000);
			}
			case 4: {
				SpawnPlayer(playerid);
			}
			default: { // LS
				SetPlayerPos(playerid, 2691.6917, -1706.1080, 11.7476);
				SetPlayerFacingAngle(playerid, 45.0000);
			}
		}
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 0);
		SetCameraBehindPlayer(playerid);
		DeletePVar(playerid, "area");
		Streamer_Update(playerid);
		return 1;
	}
	return 0;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == Area_Zone[4]) { // Регистрация

		#if PRICE_ENTER_AREA > 0
			if(CheckCash(playerid, PRICE_ENTER_AREA) == false) return 1;
			RemovePlayerEXP(playerid, PRICE_ENTER_AREA, "Оплата за выход на арену");
		#endif

		new 
			random_point = random(sizeof(AreaSpawnPoint));

		SetPlayerPos(playerid, AreaSpawnPoint[random_point][E_X], AreaSpawnPoint[random_point][E_Y], AreaSpawnPoint[random_point][E_Z]);
		SetPlayerFacingAngle(playerid, AreaSpawnPoint[random_point][E_ANGLE]);

		SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "mobile") ? (AREA_VIRTUAL_WORLD_ANDROID) : (AREA_VIRTUAL_WORLD_PC));
		SetPlayerInterior(playerid, AREA_INTER);

		if(PlayerInfo[playerid][pHours] < 3) {
			SetPlayerVirtualWorld(playerid, AREA_VIRTUAL_WORLD_NEWBIE);
			SendClientMessage(playerid, -1, ""COLOR_RED"Вы попали в локацию для новичков, так как отыграли менее 3 часов на сервере!");
		}

		SetCameraBehindPlayer(playerid);

		for (new i = 0; i < sizeof(SavePlayerWeapon[]); i++) {
		    GetPlayerWeaponData(playerid, i, SavePlayerWeapon[playerid][i][0], SavePlayerWeapon[playerid][i][1]);
		}
		ResetPlayerWeapons(playerid);
		GetPlayerHealth(playerid, SavePlayerHealth[playerid]);
		GetPlayerArmour(playerid, SavePlayerArmour[playerid]);

		GivePlayerWeapon(playerid, 24, AREA_GIVE_AMMO);
		GivePlayerWeapon(playerid, 25, AREA_GIVE_AMMO);
		GivePlayerWeapon(playerid, 31, AREA_GIVE_AMMO);

		SetPlayerArmour(playerid, 0.00);
		SetPlayerHealth(playerid, 100.00);

		PlayerArea[playerid] = true;

		Dialog_Message(playerid, 
			""COLOR_BLUE"Арена - общая информация", 
			""COLOR_WHITE"Ваша цель убивать других игроков\n\
			Для того, чтобы покинуть арену используйте команду: "COLOR_GREEN"/arena_exit", 
			"Закрыть"
		);

		return 1;
	} else if(areaid == Area_Zone[5]) { // Регистрация
		Dialog_Show(playerid, Dialog:DIALOG_SELECT_AREA_LIST_PLA);
		return 1;
	} else {
		for(new i = 0; i < sizeof(AreaBonus); i++) {
			if(areaid == AreaBonus[i][E_ZONE] && IsValidDynamicArea(AreaBonus[i][E_ZONE])) {
				#if INTERVAL_UP_BONUS > 0
					if(GetPVarInt(playerid, "area_up_bonus") > gettime()) {
						SendClientMessage(playerid, -1, ""COLOR_ORANGE"Пожалуйста подождите перед поднятием бонуса.");
						return 1;
					}
					SetPVarInt(playerid, "area_up_bonus", gettime() + INTERVAL_UP_BONUS);

					if(AreaBonus[i][E_TYPE] == E_TYPE_HEALTH) {
						SetPlayerHealth(playerid, 100.00);
						SetPlayerChatBubble(playerid, "+ 100 HP", C_GREEN, MAX_DISTANCE_VISIBLE, 5000);
					} else if(AreaBonus[i][E_TYPE] == E_TYPE_ARMOUR) {
						SetPlayerArmour(playerid, 100.00);
						SetPlayerChatBubble(playerid, "+ 100 DEF", C_GRAY, MAX_DISTANCE_VISIBLE, 5000);
					} else if(AreaBonus[i][E_TYPE] == E_TYPE_SNIPER) {
						GivePlayerWeapon(playerid, 33, 125);
					}
				#else 
					if(AreaBonus[i][E_TYPE] == E_TYPE_HEALTH) {
						SetPlayerHealth(playerid, 100.00);
						SetPlayerChatBubble(playerid, "+ 100 HP", C_GREEN, MAX_DISTANCE_VISIBLE, 5000);
					} else if(AreaBonus[i][E_TYPE] == E_TYPE_ARMOUR) {
						SetPlayerArmour(playerid, 100.00);
						SetPlayerChatBubble(playerid, "+ 100 DEF", C_GRAY, MAX_DISTANCE_VISIBLE, 5000);
					} else if(AreaBonus[i][E_TYPE] == E_TYPE_SNIPER) {
						GivePlayerWeapon(playerid, 33, 125);
					}
					return 1;
				#endif
				UpdatePlayerProgressQuest(playerid, E_ARENA_BONUS);
			}
		}
	}
	return 0;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(PlayerArea[playerid] == true && areaid == Area_Zone[6]) {
		//ResetPlayerWeapons(playerid);
	}
	return 0;
}

DialogCreate:DIALOG_SELECT_AREA_LIST_PLA(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_SELECT_AREA_LIST_PLA, DIALOG_STYLE_LIST,
		""COLOR_BLUE"Cписок лучших игроков", 
		"С мобильных устройств\n\
		С компьютера",
		"Выбрать", "Закрыть"
	);
}

DialogResponse:DIALOG_SELECT_AREA_LIST_PLA(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		switch(listitem) {
			case 0: {
				Dialog_Show(playerid, Dialog:DIALOG_SELECT_AREA_LIST_AND);
			}
			case 1: {
				Dialog_Show(playerid, Dialog:DIALOG_SELECT_AREA_LIST_PC);
			}
			default: {
				return Dialog_Show(playerid, Dialog:DIALOG_SELECT_AREA_LIST_PLA);
			}
		}
		return false;
	}
}

DialogCreate:DIALOG_SELECT_AREA_LIST_AND(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_SELECT_AREA_LIST_AND, DIALOG_STYLE_LIST,
		""COLOR_BLUE"Cписок лучших игроков", 
		"1. День\n\
		2. Неделя\n\
		3. Месяц\n\
		4. Все время",
		"Выбрать", "Назад"
	);
}

DialogResponse:DIALOG_SELECT_AREA_LIST_AND(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return Dialog_Show(playerid, Dialog:DIALOG_SELECT_AREA_LIST_PLA);
	} else {
		switch(listitem) {
			// Мобильные устройства
			case 0: {
				mysql_query(database, "SELECT p.Name, Count(d.Type) As `Kill` FROM dm_area AS d LEFT OUTER JOIN players AS p ON p.ID = d.PlayerID WHERE DATE(d.Time) = CURRENT_DATE() AND d.Type='Убийство другого игрока' AND d.Platform = 'Мобильное устройство' GROUP BY d.PlayerID ORDER BY `Kill` DESC LIMIT 10", true);
			}
			case 1: {
				mysql_query(database, "SELECT p.Name, Count(d.Type) As `Kill` FROM dm_area AS d LEFT OUTER JOIN players AS p ON p.ID = d.PlayerID WHERE DATE(d.Time) > CURRENT_DATE() - INTERVAL 7 DAY AND d.Type='Убийство другого игрока' AND d.Platform = 'Мобильное устройство' GROUP BY d.PlayerID ORDER BY `Kill` DESC LIMIT 10", true);
			}
			case 2: {
				mysql_query(database, "SELECT p.Name, Count(d.Type) As `Kill` FROM dm_area AS d LEFT OUTER JOIN players AS p ON p.ID = d.PlayerID WHERE DATE(d.Time) > CURRENT_DATE() - INTERVAL 30 DAY AND d.Type='Убийство другого игрока' AND d.Platform = 'Мобильное устройство' GROUP BY d.PlayerID ORDER BY `Kill` DESC LIMIT 10", true);
			}
			case 3: {
				mysql_query(database, "SELECT p.Name, Count(d.Type) As `Kill` FROM dm_area AS d LEFT OUTER JOIN players AS p ON p.ID = d.PlayerID WHERE d.Type='Убийство другого игрока' AND d.Platform = 'Мобильное устройство' GROUP BY d.PlayerID ORDER BY `Kill` DESC LIMIT 10", true);
			}
		}
		new 
			rows = cache_get_row_count();

		new 
			name[MAX_PLAYER_NAME],
			kill;

		big_string[0] = EOS;
		big_string = !"Игрок\tКоличество убийств\n";

		for(new i = 0; i < rows; i++) {
			cache_get_field_content(i, "Name", name);
			kill = cache_get_field_content_int(i, "Kill");
			
			if(i == 0 && strcmp(name, "NULL") == 0) {
				strcat(big_string, ""COLOR_ORANGE"Рейтинг игроков еще не сформирован");
				break;
			}
			format(small_string, sizeof(small_string), "%s\t"COLOR_GREEN"%i\n", name, kill);
			strcat(big_string, small_string);
		}
		return Dialog_Open(playerid, Dialog:DIALOG_RETURN_LIST_ANDROID, DIALOG_STYLE_TABLIST_HEADERS, ""COLOR_BLUE"Лучшие игроки", big_string, "Назад", "");
	}
}

DialogResponse:DIALOG_RETURN_LIST_ANDROID(playerid, response, listitem, inputtext[]) {
	return Dialog_Show(playerid, Dialog:DIALOG_SELECT_AREA_LIST_AND);
}

DialogCreate:DIALOG_SELECT_AREA_LIST_PC(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_SELECT_AREA_LIST_PC, DIALOG_STYLE_LIST,
		""COLOR_BLUE"Cписок лучших игроков", 
		"1. День\n\
		2. Неделя\n\
		3. Месяц\n\
		4. Все время",
		"Выбрать", "Назад"
	);
}

DialogResponse:DIALOG_SELECT_AREA_LIST_PC(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return Dialog_Show(playerid, Dialog:DIALOG_SELECT_AREA_LIST_PLA);
	} else {
		switch(listitem) {
			case 0: {
				mysql_query(database, "SELECT p.Name, Count(d.Type) As `Kill` FROM dm_area AS d LEFT OUTER JOIN players AS p ON p.ID = d.PlayerID WHERE DATE(d.Time) = CURRENT_DATE() AND d.Type='Убийство другого игрока' AND d.Platform = 'Компьютер' GROUP BY d.PlayerID ORDER BY `Kill` DESC LIMIT 10", true);
			}
			case 1: {
				mysql_query(database, "SELECT p.Name, Count(d.Type) As `Kill` FROM dm_area AS d LEFT OUTER JOIN players AS p ON p.ID = d.PlayerID WHERE DATE(d.Time) > CURRENT_DATE() - INTERVAL 7 DAY AND d.Type='Убийство другого игрока' AND d.Platform = 'Компьютер' GROUP BY d.PlayerID ORDER BY `Kill` DESC LIMIT 10", true);
			}
			case 2: {
				mysql_query(database, "SELECT p.Name, Count(d.Type) As `Kill` FROM dm_area AS d LEFT OUTER JOIN players AS p ON p.ID = d.PlayerID WHERE DATE(d.Time) > CURRENT_DATE() - INTERVAL 30 DAY AND d.Type='Убийство другого игрока' AND d.Platform = 'Компьютер' GROUP BY d.PlayerID ORDER BY `Kill` DESC LIMIT 10", true);
			}
			case 3: {
				mysql_query(database, "SELECT p.Name, Count(d.Type) As `Kill` FROM dm_area AS d LEFT OUTER JOIN players AS p ON p.ID = d.PlayerID WHERE d.Type='Убийство другого игрока' AND d.Platform = 'Компьютер' GROUP BY d.PlayerID ORDER BY `Kill` DESC LIMIT 10", true);
			}
			default: {
				return Dialog_Show(playerid, Dialog:DIALOG_SELECT_AREA_LIST_PC);
			}
		}
		new 
			rows = cache_get_row_count();

		new 
			name[MAX_PLAYER_NAME],
			kill;

		big_string[0] = EOS;
		big_string = !"Игрок\tКоличество убийств\n";

		for(new i = 0; i < rows; i++) {
			cache_get_field_content(i, "Name", name);
			kill = cache_get_field_content_int(i, "Kill");
			
			if(i == 0 && strcmp(name, "NULL") == 0) {
				strcat(big_string, ""COLOR_ORANGE"Рейтинг игроков еще не сформирован");
				break;
			}
			format(small_string, sizeof(small_string), "%s\t"COLOR_GREEN"%i\n", name, kill);
			strcat(big_string, small_string);
		}
		return Dialog_Open(playerid, Dialog:DIALOG_RETURN_LIST_PC, DIALOG_STYLE_TABLIST_HEADERS, ""COLOR_BLUE"Лучшие игроки", big_string, "Назад", "");
	}
}

DialogResponse:DIALOG_RETURN_LIST_PC(playerid, response, listitem, inputtext[]) {
	return Dialog_Show(playerid, Dialog:DIALOG_SELECT_AREA_LIST_PC);
}


CMD:arena_exit(playerid, params[]) {
	if(PlayerArea[playerid] == true) {
		PlayerArea[playerid] = false;
		SetPlayerPos(playerid, 960.5510, -48.5531, 1001.1172);
		SetPlayerFacingAngle(playerid, 180.00);
		SetPlayerVirtualWorld(playerid, 10);
		SetPlayerInterior(playerid, 3);
		ResetPlayerWeapons(playerid);
		for (new i = 0; i < sizeof(SavePlayerWeapon[]); i++) {
		    GivePlayerWeapon(playerid, SavePlayerWeapon[playerid][i][0], SavePlayerWeapon[playerid][i][1]);
		}

		for(new i = 0; i < sizeof(SavePlayerWeapon[]); i++) {
			SavePlayerWeapon[playerid][i][0] = 0;
			SavePlayerWeapon[playerid][i][1] = 0;
		}
		
		SetPlayerHealth(playerid, SavePlayerHealth[playerid]);
		SetPlayerArmour(playerid, SavePlayerArmour[playerid]);

		return SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы покинули арену");
	}
	return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы должны находиться на арене");
}

DialogCreate:DIALOG_SELECT_SPAWN(playerid) {
	if(GetPVarInt(playerid, "is_setting_pos") == 1)
	{
		return Dialog_Open(playerid, Dialog:DIALOG_SELECT_SPAWN, DIALOG_STYLE_TABLIST_HEADERS,
			""COLOR_BLUE"Выбор место появления", 
			"Точка спавна\tОписание\n\
			"COLOR_GREEN"Обычный мир"COLOR_WHITE"\tПоявиться в обычном мире, для ролевой игры\n\
			"COLOR_GREEN"Арена"COLOR_WHITE"\tПереместиться в лобби арены для сражений\n\
			"COLOR_GREEN"Точка последнего выхода"COLOR_WHITE"\tПереместиться на последнию позицию Вашего персонажа",
			"Выбрать", ""
		);
	}
	else
	{
		return Dialog_Open(playerid, Dialog:DIALOG_SELECT_SPAWN, DIALOG_STYLE_TABLIST_HEADERS,
			""COLOR_BLUE"Выбор место появления", 
			"Точка спавна\tОписание\n\
			"COLOR_GREEN"Обычный мир"COLOR_WHITE"\tПоявиться в обычном мире, для ролевой игры\n\
			"COLOR_GREEN"Арена"COLOR_WHITE"\tПереместиться в лобби арены для сражений",
			"Выбрать", ""
		);
	}
}

DialogResponse:DIALOG_SELECT_SPAWN(playerid, response, listitem, inputtext[]) {
	switch(listitem)
	{
		case 0:
		{
			
		}
		case 1:
		{
			SetPVarInt(playerid, "first_spawn", 1);
		}
		case 2:
		{
			if(GetPVarInt(playerid, "is_setting_pos") == 1)
			{
				SetPVarInt(playerid, "is_setting_pos", 2);
			}
			else
			{
				return Dialog_Show(playerid, Dialog:DIALOG_SELECT_SPAWN);
			}
		}
		default:
		{
			return Dialog_Show(playerid, Dialog:DIALOG_SELECT_SPAWN);
		}
	}
	TogglePlayerSpectating(playerid, false);
	new DaysAgo = GetPlayerDaysWithoutActivity(GetPlayerAccountID(playerid));

	format(small_string, sizeof(small_string), ""COLOR_BLUE"Последний вход: "COLOR_WHITE"%d "COLOR_BLUE"дн. назад", DaysAgo);

	if(DaysAgo == 0) format(small_string, sizeof(small_string), ""COLOR_BLUE"Последний вход: "COLOR_WHITE"сегодня", DaysAgo);
	if(DaysAgo == 1) format(small_string, sizeof(small_string), ""COLOR_BLUE"Последний вход: "COLOR_WHITE"вчера", DaysAgo);
	if(DaysAgo == 2) format(small_string, sizeof(small_string), ""COLOR_BLUE"Последний вход: "COLOR_WHITE"позавчера", DaysAgo);

	
	SendClientMessage(playerid, -1, small_string);

	if(DaysAgo >= 30 && PlayerInfo[playerid][pHours] > 5) {
		GivePlayerPremiumAccount(playerid, 7, 0);
		Dialog_Show(playerid, Dialog:DIALOG_FREE_PREMIUM);
	} else {
		ActivatePremium(playerid);
	}

	CallLocalFunction("UpdateLastDay", "i", playerid);

	return 1;
}