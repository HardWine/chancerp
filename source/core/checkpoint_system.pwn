#if defined checkpoint_system_included
	#endinput
#endif

#define checkpoint_system_included

#include <YSI_Coding\y_hooks>

forward CreatePlayerCP(playerid, Float:x, Float:y, Float:z, function[], world = 0, interiorid = 0, bool:destroyed = true, size = sizeof(function));
/*
	# Описание
	Создание новый, кастомный чекпоинт для игрока

	# Параметры
	- playerid: ID игрока
	- x, y, z: Координаты
	- function: Функция, которая будет вызвана при поднятии чекпоинта
	- world: Номер виртуального мира
	- interiorid: Номер интерьера
	- destroyed: Будет-ли удален чекпоинт при первом же поднятии

	# Возвращает
	- INVALID_STREAMER_ID: Функция была выполнена с ошибкой
	- Порядковый номер чекпоинта: Чекпоинт успешно создан
*/

forward SetPlayerCPGlobal(playerid, checkpointid, bool:isglobal);
/*
	# Описание
	Делает зону стрима мап-иконки чекпоинта на всю карту

	# Параметры
	- playerid: ID игрока
	- checkpointid: Порядковый номер чекпоинта
	- isglobal: Переключатель зоны видимости; false - в зоне стрима; true - на всю карту

	# Возвращает
	- false: Указан неверный порядковый номер чекпоинта
	- true: Функция выполнена успешно
*/

forward OnPlayerEnterPlayerCP(playerid, checkpointid);
#if !defined CUSTOM_CP_MAX
	#define CUSTOM_CP_MAX							(10)
#endif

#if !defined CUSTOM_PLAYER_CP_STREAMER
	#define CUSTOM_PLAYER_CP_STREAMER				(859)
#endif

#if !defined CUSTOM_PLAYER_CP_STREAM_DIS
	#define CUSTOM_PLAYER_CP_STREAM_DIS				(16000.00)
#endif

enum 
	E_CUSTOM_CHECKPOINT {
		E_ID,
		E_OBJECT_ID,
		E_AREA_ID,
		E_MAP_ICON,
		bool: E_DESTROY,
		E_FUNCTION[32]
	};

new 
	PlayerCustomCP[MAX_PLAYERS][CUSTOM_CP_MAX][E_CUSTOM_CHECKPOINT];

new 
	total_count_player_cp = 0;

hook OnPlayerConnect(playerid) {
	for(new i = 0; i < sizeof(PlayerCustomCP[]); i++) {
		PlayerCustomCP[playerid][i][E_ID] = INVALID_STREAMER_ID;
		PlayerCustomCP[playerid][i][E_OBJECT_ID] = INVALID_STREAMER_ID;
		PlayerCustomCP[playerid][i][E_AREA_ID] = INVALID_STREAMER_ID;
		PlayerCustomCP[playerid][i][E_MAP_ICON] = INVALID_STREAMER_ID;
	}
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason 

	for(new i = 0; i < sizeof(PlayerCustomCP[]); i++) {
		if(PlayerCustomCP[playerid][i][E_AREA_ID] != INVALID_STREAMER_ID) {
			DestroyDynamicArea(PlayerCustomCP[playerid][i][E_AREA_ID]);
		}
		PlayerCustomCP[playerid][i][E_AREA_ID] = INVALID_STREAMER_ID;

		if(PlayerCustomCP[playerid][i][E_OBJECT_ID] != INVALID_STREAMER_ID) {
			DestroyDynamicObject(PlayerCustomCP[playerid][i][E_OBJECT_ID]);
		}
		PlayerCustomCP[playerid][i][E_OBJECT_ID] = INVALID_STREAMER_ID;

		if(PlayerCustomCP[playerid][i][E_MAP_ICON] != INVALID_STREAMER_ID) {
			DestroyDynamicMapIcon(PlayerCustomCP[playerid][i][E_MAP_ICON]);
		}
		PlayerCustomCP[playerid][i][E_MAP_ICON] = INVALID_STREAMER_ID;

		PlayerCustomCP[playerid][i][E_ID] = INVALID_STREAMER_ID;
	}

	return Y_HOOKS_CONTINUE_RETURN_1;
}

stock CreatePlayerCP(playerid, Float:x, Float:y, Float:z, function[], world = 0, interiorid = 0, bool:destroyed = true, size = sizeof(function)) {
	new arrayid = INVALID_STREAMER_ID;

	for(new i = 0; i < sizeof(PlayerCustomCP[]); i++) {
		if(PlayerCustomCP[playerid][i][E_OBJECT_ID] == INVALID_STREAMER_ID && 
			PlayerCustomCP[playerid][i][E_AREA_ID] == INVALID_STREAMER_ID && 
			PlayerCustomCP[playerid][i][E_MAP_ICON] == INVALID_STREAMER_ID) {

			arrayid = i;
		}
	}

	if(arrayid == INVALID_STREAMER_ID) {
		return INVALID_STREAMER_ID;
	}

	new 
		objectid = CreateDynamicObject(1317, x, y, z - 1.0, 0.00, 0.00, 0.00, world, interiorid, playerid),
		areaid = CreateDynamicSphere(x, y, z, 1.00, world, interiorid, playerid),
		mapiconid = CreateDynamicMapIcon(x, y, z, 0, 0xff353cFF, world, interiorid, playerid);

	SetDynamicObjectMaterial(objectid, 0, 18646, "matcolours", "orange", 0x99FF8000);
	
	total_count_player_cp = total_count_player_cp + 1;

	PlayerCustomCP[playerid][arrayid][E_OBJECT_ID] = objectid;
	PlayerCustomCP[playerid][arrayid][E_AREA_ID] = areaid;
	PlayerCustomCP[playerid][arrayid][E_MAP_ICON] = mapiconid;
	PlayerCustomCP[playerid][arrayid][E_DESTROY] = destroyed;
	PlayerCustomCP[playerid][arrayid][E_ID] = total_count_player_cp;
	strmid(PlayerCustomCP[playerid][arrayid][E_FUNCTION], function, 0, size, 32);

	new data[2];

	data[0] = CUSTOM_PLAYER_CP_STREAMER;
	data[1] = arrayid;

	Streamer_SetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, data, 2);
	return total_count_player_cp;
}

stock SetPlayerCPGlobal(playerid, checkpointid, bool:isglobal) {
	new arrayid = INVALID_STREAMER_ID;

	for(new i = 0; i < sizeof(PlayerCustomCP[]); i++) {
		if(PlayerCustomCP[playerid][i][E_ID] == checkpointid) {
			arrayid = i;
		}
	}

	if(arrayid == INVALID_STREAMER_ID) {
		return false;
	}

	if(isglobal == true) {
		Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON, PlayerCustomCP[playerid][arrayid][E_MAP_ICON], E_STREAMER_STREAM_DISTANCE, CUSTOM_PLAYER_CP_STREAM_DIS);
	} else {
		Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON, PlayerCustomCP[playerid][arrayid][E_MAP_ICON], E_STREAMER_STREAM_DISTANCE, STREAMER_MAP_ICON_SD);
	}

	Streamer_Update(playerid, STREAMER_TYPE_MAP_ICON);
	return true;
}

stock EnabledPlayerCPDestoy(playerid, checkpointid, bool:destroyed) {
	new arrayid = INVALID_STREAMER_ID;

	for(new i = 0; i < sizeof(PlayerCustomCP[]); i++) {
		if(PlayerCustomCP[playerid][i][E_ID] == checkpointid) {
			arrayid = i;
		}
	}

	if(arrayid == INVALID_STREAMER_ID) {
		return false;
	}

	PlayerCustomCP[playerid][arrayid][E_DESTROY] = destroyed;
	return true;
}

stock DestroyPlayerCP(playerid, checkpointid) {
	new arrayid = INVALID_STREAMER_ID;

	for(new i = 0; i < sizeof(PlayerCustomCP[]); i++) {
		if(PlayerCustomCP[playerid][i][E_ID] == checkpointid) {
			arrayid = i;
		}
	}

	if(arrayid == INVALID_STREAMER_ID) {
		return false;
	}

	PlayerCustomCP[playerid][arrayid][E_ID] = INVALID_STREAMER_ID;

	if(PlayerCustomCP[playerid][arrayid][E_AREA_ID] != INVALID_STREAMER_ID) {
		DestroyDynamicArea(PlayerCustomCP[playerid][arrayid][E_AREA_ID]);
	}
	PlayerCustomCP[playerid][arrayid][E_AREA_ID] = INVALID_STREAMER_ID;

	if(PlayerCustomCP[playerid][arrayid][E_OBJECT_ID] != INVALID_STREAMER_ID) {
		DestroyDynamicObject(PlayerCustomCP[playerid][arrayid][E_OBJECT_ID]);
	}
	PlayerCustomCP[playerid][arrayid][E_OBJECT_ID] = INVALID_STREAMER_ID;

	if(PlayerCustomCP[playerid][arrayid][E_MAP_ICON] != INVALID_STREAMER_ID) {
		DestroyDynamicMapIcon(PlayerCustomCP[playerid][arrayid][E_MAP_ICON]);
	}
	PlayerCustomCP[playerid][arrayid][E_MAP_ICON] = INVALID_STREAMER_ID;
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid) {

	new 
		data[2];

	Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, data, 2);

	if(data[0] == CUSTOM_PLAYER_CP_STREAMER) { 
		new 
			arrayid = data[1];

		if(funcidx(PlayerCustomCP[playerid][arrayid][E_FUNCTION])) {
			print("+++");
			printf("%s", PlayerCustomCP[playerid][arrayid][E_FUNCTION]);
			CallLocalFunction(PlayerCustomCP[playerid][arrayid][E_FUNCTION], "i", playerid);
		}
		//SendClientMessage(playerid, -1, "Привет OnPlayerEnterPlayerCP");

		if(PlayerCustomCP[playerid][arrayid][E_DESTROY] == true) {
			DestroyPlayerCP(playerid, PlayerCustomCP[playerid][arrayid][E_ID]);
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}