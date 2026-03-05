#if defined steal_car_system_included
	#endinput
#endif

#define steal_car_system_included

#include <YSI-Include\YSI\YSI\y_hooks>

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

/**
	В начале угона кидаешь это, с параметры ID машины (не модели)
	и ID игрока, который ее владелец 
*/
stock bool:AddNewSteelCar(const vehicleid, const owner_id) {
	for(new i = 0; i < MAX_STEEL_CAR; i++) {
		if(SteelCar[i][E_VEHICLE_ID] == INVALID_VEHICLE_ID) {
			SteelCar[e][E_VEHICLE_ID] = vehicleid;
			SteelCar[e][E_PLAYER_ID] = owner_id;
			return true;
		}
	}
	return false;
}

/**
	В паблике onplayerdisconnect вызываешь это,
	и если оно вернет true, то не удаляешь машину игрока
	при выходе
*/
stock bool:RemoveSteelCar(const vehicleid) {
	if(vehicleid == INVALID_VEHICLE_ID) {
		return false;
	} 
	for(new i = 0; i < MAX_STEEL_CAR; i++) {
		if(SteelCar[i][E_VEHICLE_ID] == vehicleid) {
			SteelCar[i][E_VEHICLE_ID] = INVALID_VEHICLE_ID;
			return true;
		}
	}
	return false;
} 

/**
	Это пока тебе не надо
**/
stock bool:IsSteelCar(const vehicleid) {
	for(new i = 0; i < MAX_STEEL_CAR; i++) {
		if(SteelCar[i][E_VEHICLE_ID] == vehicleid) {
			return true;
		}
	}
	return false;
}


/**
	В момент доставки, автомобиля, проверяй, онлайн ли игрок
	если вернет INVALID_PLAYER_ID - то удаляй машину
	иначе, перезагружай машину игрока loadplayercar че-то там
*/
stock IsSteelCarOwnerOnline(const vehicleid) {
	for(new i = 0; i < MAX_STEEL_CAR; i++) {
		if(SteelCar[i][E_VEHICLE_ID] == vehicleid) {
			return SteelCar[i][E_PLAYER_ID];
		}
	}
	return INVALID_PLAYER_ID;
}