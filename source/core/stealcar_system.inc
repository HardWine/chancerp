#if defined steal_car_system_included
	#endinput
#endif

#define steal_car_system_included

#include <YSI_Coding\y_hooks>

#define MAX_STEEL_CAR 				(100)

enum 
	E_STEEL_CAR {
		E_VEHICLE_ID,
		E_PLAYER_ID
	};

new 
	SteelCar[MAX_STEEL_CAR][E_STEEL_CAR];

hook OnGameModeInit() {
	for(new i = 0; i < MAX_STEEL_CAR; i++) {
		SteelCar[i][E_VEHICLE_ID] = INVALID_VEHICLE_ID;
		SteelCar[i][E_PLAYER_ID] = INVALID_PLAYER_ID;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

stock bool:AddNewSteelCar(const vehicleid) {
	for(new i = 0; i < MAX_STEEL_CAR; i++) {
		if(SteelCar[i][E_VEHICLE_ID] == INVALID_VEHICLE_ID) {
			SteelCar[i][E_VEHICLE_ID] = vehicleid;
			return true;
		}
	}
	return false;
}
