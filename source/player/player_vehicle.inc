#if defined player_vehicle_included
	#endinput
#endif

#define player_vehicle_included

#define MAX_PLAYERS_CAR 			(2)
#define INVALID_CAR_ID 				(-1)

#include <YSI-Include\YSI\YSI\y_hooks>

hook OnPlayerAuthorization(playerid) {
	Player.GetPlayerCar(playerid, 0);
	Player.GetPlayerCar(playerid, 1);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

new 
	Player.CarID[MAX_PLAYERS][MAX_PLAYERS_CAR],
	Player.CarModelID[MAX_PLAYERS][MAX_PLAYERS_CAR],
	Player.CarVehicleID[MAX_PLAYERS][MAX_PLAYERS_CAR],
	Player.CarMileage[MAX_PLAYERS][MAX_PLAYERS_CAR],
	Player.CarColor_1[MAX_PLAYERS][MAX_PLAYERS_CAR],
	Player.CarColor_2[MAX_PLAYERS][MAX_PLAYERS_CAR];

hook OnPlayerConnect(playerid) {
	for(new i = 0; i < MAX_PLAYERS_CAR; i++) {
		Player.CarID[playerid][i] = INVALID_CAR_ID;
		Player.CarModelID[playerid][i] = INVALID_VEHICLE_ID;
		Player.CarVehicleID[playerid][i] = INVALID_VEHICLE_ID;
		Player.CarColor_1[playerid][i] = 0;
		Player.CarColor_2[playerid][i] = 0;
		Player.CarMileage[playerid][i] = 0;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	Player.DeletePlayerCar(playerid, 0);
	Player.DeletePlayerCar(playerid, 1);
	for(new i = 0; i < MAX_PLAYERS_CAR; i++) {
		Player.CarID[playerid][i] = INVALID_CAR_ID;
		Player.CarModelID[playerid][i] = INVALID_VEHICLE_ID;
		Player.CarVehicleID[playerid][i] = INVALID_VEHICLE_ID;
		Player.CarColor_1[playerid][i] = 0;
		Player.CarColor_2[playerid][i] = 0;
		Player.CarMileage[playerid][i] = 0;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

forward bool:Player.GetPlayerCar(const playerid, const slot);
public bool:Player.GetPlayerCar(const playerid, const slot) {
	format(small_string, sizeof(small_string), "CALL `Player.GetPlayerCar` (%i , %i);", GetPlayerAccountID(playerid), slot);
	printf(small_string);
	mysql_pquery(database, small_string, "@_LoadPlayerCar", "ii", playerid, slot);
	return true;
}

forward bool:Player.DeletePlayerCar(const playerid, const slot);
public bool:Player.DeletePlayerCar(const playerid, const slot) {
	if(Player.CarVehicleID[playerid][slot] != INVALID_VEHICLE_ID) {
		DestroyVehicle(Player.CarVehicleID[playerid][slot]);
		Player.CarVehicleID[playerid][slot] = INVALID_VEHICLE_ID;
		return true;
	}
	return false;
}

@_LoadPlayerCar(const playerid, const slot);
@_LoadPlayerCar(const playerid, const slot) {
	new 
		rows = cache_get_row_count();
	
	if(rows == 0) {
		Player.CarID[playerid][slot] = INVALID_CAR_ID;
		Player.CarModelID[playerid][slot] = INVALID_VEHICLE_ID;
		Player.CarVehicleID[playerid][slot] = INVALID_VEHICLE_ID;
		Player.CarColor_1[playerid][slot] = 0;
		Player.CarColor_2[playerid][slot] = 0;
		return false;
	} else {
		Player.CarID[playerid][slot] = cache_get_field_content_int(0, "ID");
		Player.CarModelID[playerid][slot] = cache_get_field_content_int(0, "VehicleID") + 399;
		Player.CarColor_1[playerid][slot] = cache_get_field_content_int(0, "Color_1");
		Player.CarColor_2[playerid][slot] = cache_get_field_content_int(0, "Color_2");
		Player.CarMileage[playerid][slot] = cache_get_field_content_int(0, "Mileage");


		printf("ID = %i Model = %i Color = %i|%i", Player.CarID[playerid][slot], Player.CarModelID[playerid][slot], Player.CarColor_1[playerid][slot], Player.CarColor_2[playerid][slot]);
		Player.CarVehicleID[playerid][slot] = CreateVehicle(Player.CarModelID[playerid][slot], 
			0.00, 0.00, 5.00, 270.00, Player.CarColor_1[playerid][slot], Player.CarColor_2[playerid][slot], 600000
		);
		Vehicle.SetLock(playerid, Player.CarVehicleID[playerid][slot]);
	}
}

CMD:lock(playerid, params[]) {
	if(Player.CarID[playerid][0] == INVALID_CAR_ID && Player.CarID[playerid][1] == INVALID_CAR_ID) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"У вас нет домашней машины.");
	}
	new 
		slot_0 = Player.CarVehicleID[playerid][0],
		slot_1 = Player.CarVehicleID[playerid][1];

	new 
		Float: pos_x,
		Float: pos_y,
		Float: pos_z;

	if(slot_0 != INVALID_VEHICLE_ID) {
		GetVehiclePos(slot_0, pos_x, pos_y, pos_z);

		if(IsPlayerInRangeOfPoint(playerid, 4, pos_x, pos_y, pos_z)) {
			PlayerPlaySound(playerid, 24600, 0, 0, 0);
			if(VehicleParameters[slot_0][1] == 1) {
				SetVehicleParamsForPlayerEx(slot_0,playerid,0,0);
				format(small_string, 100, "%s открыл(а) замок", PlayerInfo[playerid][pName]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				return GameTextForPlayer(playerid, "~g~Unlocked", 2500, 4);
			}
			if(VehicleParameters[slot_0][1] == 0) {
				SetVehicleParamsForPlayerEx(slot_0,playerid,0,1); 	
				format(small_string, 100, "%s закрыл(а) замок", PlayerInfo[playerid][pName]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				return GameTextForPlayer(playerid, "~r~Locked", 2500, 4);
			}
		}
	} 
	if(slot_1 != INVALID_VEHICLE_ID) {
		GetVehiclePos(slot_1, pos_x, pos_y, pos_z);

		if(IsPlayerInRangeOfPoint(playerid, 4, pos_x, pos_y, pos_z)) {
			PlayerPlaySound(playerid, 24600, 0, 0, 0);
			if(VehicleParameters[slot_1][1] == 1) {
				SetVehicleParamsForPlayerEx(slot_1,playerid,0,0);
				format(small_string, 100, "%s открыл(а) замок", PlayerInfo[playerid][pName]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				return GameTextForPlayer(playerid, "~g~Unlocked", 2500, 4);
			}
			if(VehicleParameters[slot_1][1] == 0) {
				SetVehicleParamsForPlayerEx(slot_1,playerid,0,1); 	
				format(small_string, 100, "%s закрыл(а) замок", PlayerInfo[playerid][pName]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				return GameTextForPlayer(playerid, "~r~Locked", 2500, 4);
			}
		}
	}
	return 1;
}