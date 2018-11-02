#if defined cmd_car_included
	#endinput
#endif

#define cmd_car_included

#define MAX_ADMIN_CAR 						(15)

enum 
	admin_car__ {
		AC_ID,
		AC_VehicleID,
		AC_AdminName[MAX_PLAYER_NAME],
		AC_UnixTime
	};

new AdminCar[MAX_ADMIN_CAR][admin_car__];

CMD:car(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 5) {
    	return true;
    }

    new
		subcmd[20],
		subparams[32];

	if (sscanf(params, "s[20]S()[32]", subcmd, subparams)) {
		SendClientMessage(playerid, -1, "Синтаксис команды: ");
		SendClientMessage(playerid, -1, "/car add [ID модели] (Цвет 1) (Цвет 2) - создать машину.");
		SendClientMessage(playerid, -1, "/car remove [ID автомобиля] - удалить машину созданную администрацией.");
		SendClientMessage(playerid, -1, "/car remove all - удалить все машины созданные администрацией.");
		return SendClientMessage(playerid, -1, "/car show - отобразить информацию о созданных автомобилях.");
	}

	if(strcmp(subcmd, "add", true) == 0) {
		new 
	    	modelid,
	    	color1,
	    	color2;

	    if(sscanf(subparams, "iI(-1)I(-1)", modelid, color1, color2)) {
	    	return SendClientMessage(playerid, -1, "Используйте: /car add [ID Модели] (Цвет 1) (Цвет 2)");
		}

		new 
			Float: X,
			Float: Y,
			Float: Z;

		if(color1 == -1) {
			color1 = random(255);
		}
		if(color2 == -1) {
			color2 = random(255);
		}

		GetPlayerPos(playerid, X, Y, Z);
	   
	    new return_car = CreateVehicle(modelid, X + 2, Y, Z, 0.0, color1, color2, 9000);
		PutPlayerInVehicle(playerid, return_car, 0);

		return SendClientMessage(playerid, -1, !""COLOR_RED"Не злоупотребляйте данной функцией и убирайте за собой {FFFFFF}(/delcar)");
	} else if(strcmp(subcmd, "remove", true) == 0) {
		new vehicleid = GetPlayerVehicleID(playerid);
		return DestroyVehicle(vehicleid);
	}
}