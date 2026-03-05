#if defined truck_system_included
	#endinput
#endif

#define truck_system_included

#define PROFIT_LS			50
#define PROFIT_SF			75
#define PROFIT_LV			25

#define TRAILER_1_PRICE		1000
#define TRAILER_1_PROFIT	6

#define TRAILER_2_PRICE		2500
#define TRAILER_2_PROFIT	5

#define TRAILER_3_PRICE		3000
#define TRAILER_3_PROFIT	5

#define TRAILER_4_PRICE		4000
#define TRAILER_4_PROFIT	5

#define TRAILER_5_PRICE		5500
#define TRAILER_5_PROFIT	4

new enter_office_area;
new office_pickup;
new office_area;
new trailer_spawnpoint;

new player_trailer[MAX_PLAYERS];

stock trucker_system_init() {

	enter_office_area = CreateDynamicCylinder(-49.8400, -269.3645, 6, 7, 1.5, 0, 0, -1);
	office_pickup = CreateDynamicPickup(1239, 2, 215.9068,1755.6349,3000.8308, -1, -1, -1, 15.0);
	office_area = CreateDynamicCylinder(215.9068,1755.6349,3000, 3001, 1.1, -1, -1, -1);
}

stock trucker_area(playerid, areaid) {
	if(areaid == enter_office_area) {
		SetPlayerScreenColour(playerid, 0x000000FF);
		SetPlayerPos(playerid,-49.8653,-267.3860,6.1832);
	}
	if(areaid == office_area) {
		Dialog_Show(playerid, Dialog:main_trucker);
	}	
}

stock trucker_pickup(playerid, pickupid) {
	if(pickupid == office_pickup) {
		return 0;
	}
	return 1;
}

stock trucker_offline(playerid) {
	if(IsValidVehicle(player_trailer[playerid])) DestroyVehicle(player_trailer[playerid]);
}

DialogCreate:main_trucker(playerid) {
	if(!GetPVarInt(playerid, "trucker")) {
		return Dialog_Open(playerid, Dialog:main_trucker, DIALOG_STYLE_MSGBOX,
		""COLOR_BLUE"Trucker & Co.",
		"{FFFFFF}Добро пожловать в офис грузоперевозочной компании,\n\
		Здесь вы можете начать работу на большегрузном автомобиле\n\
		и заработать неплохие деньги. Продолжить?",
		"Да", "Выход"
	);
	} else {
		//зп
	}
}

DialogResponse:main_trucker(playerid, response, listitem, inputtext[]) {
	if(!response) return 1;
	SetPVarInt(playerid, "trucker", 1);
	SendClientMessage(playerid, -1, ""COLOR_BLUE"Берите фуру и отправляйтесь в рейс");
	//SetPlayerAttachedObject(playerid, 1, 18961, 2, 0.12, 0.02, 0, 90, 90, 0, 1, 1, 1);	
	format(small_string, sizeof(small_string), "%s надел(а) кепку дальнобойщика", PlayerInfo[playerid][pName]);	
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
	return 1;
}

DialogCreate:trucker_get_way(playerid) {
	if(!GetPVarInt(playerid, "trucker")) return 1;
	
	return Dialog_Open(playerid, Dialog:trucker_get_way, DIALOG_STYLE_LIST,
	""COLOR_BLUE"Место назначения",
	"{FFFFFF}Склад Сан-Фиерро\n\
	Доки Лос-Сантос\n\
	Автобаза Лас-Вентурас",
	"Выбор", "Отмена"	
	);
}

DialogResponse:trucker_get_way(playerid, response, listitem, inputtext[]) {
	if(!response) return RemovePlayerFromVehicle(playerid);

	SetPVarInt(playerid, "way", listitem+1);

	if(listitem == 0) SendClientMessage(playerid, -1, ""COLOR_BLUE"Пункт назначения: {FFFFFF}Склад Сан-Фиерро определен");
	if(listitem == 1) SendClientMessage(playerid, -1, ""COLOR_BLUE"Пункт назначения: {FFFFFF}Доки Лос-Сантос определен");
	if(listitem == 2) SendClientMessage(playerid, -1, ""COLOR_BLUE"Пункт назначения: {FFFFFF}Автобаза Лас-Вентурас определен");

	Dialog_Show(playerid, Dialog:trucker_get_trailer);
	return 1;
}

DialogCreate:trucker_get_trailer(playerid) {
	if(!GetPVarInt(playerid, "trucker")) return 1;
	new profit,
		way = GetPVarInt(playerid, "way");

	if(way == 1) profit = PROFIT_SF;
	if(way == 2) profit = PROFIT_LS;
	if(way == 3) profit = PROFIT_LV;

	format(big_string, sizeof(big_string), 
		"Трейлер\tЦена\tПрибыль\n\
		Щебень\t"COLOR_GREEN"%d\t%d\n\
		Продукты\t"COLOR_GREEN"%d\t%d\n\
		Одежда\t"COLOR_GREEN"%d\t%d\n\
		Техника\t"COLOR_GREEN"%d\t%d\n\
		Топливо\t"COLOR_GREEN"%d\t%d",
		TRAILER_1_PRICE,
		(TRAILER_1_PRICE/TRAILER_1_PROFIT)+profit,
		TRAILER_2_PRICE,
		(TRAILER_2_PRICE/TRAILER_2_PROFIT)+profit,
		TRAILER_3_PRICE,
		(TRAILER_3_PRICE/TRAILER_3_PROFIT)+profit,
		TRAILER_4_PRICE,
		(TRAILER_4_PRICE/TRAILER_4_PROFIT)+profit,
		TRAILER_5_PRICE,
		(TRAILER_5_PRICE/TRAILER_5_PROFIT)+profit);

	return Dialog_Open(playerid, Dialog:trucker_get_trailer, DIALOG_STYLE_TABLIST_HEADERS,
	""COLOR_BLUE"Купить трейлер",
	big_string,
	"Купить", "Отмена"	
	);
}

DialogResponse:trucker_get_trailer(playerid, response, listitem, inputtext[]) {
	if(!response) return Dialog_Show(playerid, Dialog:trucker_get_trailer);

	new trailer = listitem+1;
	new vehicleid = GetPlayerVehicleID(playerid);

	SetPVarInt(playerid, "trailer", trailer);

	new vehicletype = 450;

	if(trailer == 0) vehicletype = 450;
	if(trailer == 5) vehicletype = 584;

	switch(trailer_spawnpoint) {
		case 0: {
			SetVehiclePos(vehicleid, -117.8443,-336.5161,2.4535);
			trailer_spawnpoint = trailer_spawnpoint+1;
			SetVehicleZAngle(vehicleid, 180.0);
		}
		case 1: {
			SetVehiclePos(vehicleid, -131.1677,-335.9840,2.4570);
			trailer_spawnpoint = trailer_spawnpoint+1;
			SetVehicleZAngle(vehicleid, 180.0);
		}
		case 2: {
			SetVehiclePos(vehicleid, -144.9689,-335.4331,2.4569);
			trailer_spawnpoint = trailer_spawnpoint+1;
			SetVehicleZAngle(vehicleid, 180.0);
		}
		case 3: {
			SetVehiclePos(vehicleid, -187.4500,-288.6339,2.4482);
			trailer_spawnpoint = trailer_spawnpoint+1;
			SetVehicleZAngle(vehicleid, 90.0);
		}
		case 4: {
			SetVehiclePos(vehicleid, -187.2161,-274.8448,2.4481);
			trailer_spawnpoint = trailer_spawnpoint+1;
			SetVehicleZAngle(vehicleid, 90.0);
		}
		case 5: {
			SetVehiclePos(vehicleid, -186.9817,-261.0485,2.4525);
			trailer_spawnpoint = trailer_spawnpoint+1;
			SetVehicleZAngle(vehicleid, 90.0);
		}
		case 6: {
			SetVehiclePos(vehicleid, -23.6981,-297.7545,6.4522);
			trailer_spawnpoint = trailer_spawnpoint+1;
			SetVehicleZAngle(vehicleid, 180.0);
		}
		case 7: {
			SetVehiclePos(vehicleid, -15.3103,-297.9486,6.4559);
			trailer_spawnpoint = trailer_spawnpoint+1;
			SetVehicleZAngle(vehicleid, 180.0);
		}
		case 8: {
			SetVehiclePos(vehicleid, -14.7072,-225.4295,6.4476);
			SetVehicleZAngle(vehicleid, 270.0);
			trailer_spawnpoint = 0;
		}																		
	}

	if(IsValidVehicle(player_trailer[playerid])) DestroyVehicle(player_trailer[playerid]);

	new Float:truck_x,
		Float:truck_y,
		Float:truck_z;

	GetVehiclePos(vehicleid, truck_x, truck_y, truck_z);
	player_trailer[playerid] = CreateVehicle(vehicletype, truck_x, truck_y, truck_z, 0.0, RandomEx(0,79), RandomEx(0,79), 60000, 0);
	SetTimerEx("AttachTrailer", 1000, false, "iii", playerid, player_trailer[playerid], vehicleid);
	return 1;
}

forward AttachTrailer(playerid, trailerid, vehicleid);
public AttachTrailer(playerid, trailerid, vehicleid)
{
    AttachTrailerToVehicle(trailerid, vehicleid);
} 