#if defined refill_system_included
	#endinput
#endif

#define refill_system_included

#include <YSI_Coding\y_hooks>

#if !defined PRICE_ONE_LITER_GASOLINE_VALUE
	#define PRICE_ONE_LITER_GASOLINE_VALUE 			2	// Цена за один три бензина
#endif

#if !defined COST_CANISTER
	#define COST_CANISTER 							200
#endif

#if !defined AMOUNT_FUEL_IN_CANISTER
	#define AMOUNT_FUEL_IN_CANISTER 				20
#endif

enum 
	E_REFILL {
		Float: E_X,
		Float: E_Y,
		Float: E_Z,
		E_AREA
	};

new
	Float: PumpData[][E_REFILL] = {
		{1941.70420, -1776.3087, 13.6406},
		{1003.26970, -937.22360, 42.3281},
		{-90.884300, -1168.7615, 2.4227},
		{-2025.4590, 156.715000, 28.8359},
		{-1675.8706, 412.917900, 7.1797},
		{-2410.8535, 977.137900, 45.4609},
		{-1471.5488, 1863.84720, 32.6328},
		{615.200000, 1689.60010, 6.9922},
		{2202.48540, 2475.38130, 10.8203},
		{1381.80360, 459.153700, 20.3452},
		{-1606.2146, -2714.0313, 48.5335},
		{-2244.1936, -2561.0613, 31.9219},
		{655.816600, -565.23220, 16.3359},
		{2640.60180, 1106.42070, 10.8203},
		{2147.76680, 2748.41060, 10.8203},
		{-1328.2766, 2677.5486, 49.7650},
		{1595.99000, 2199.51000, 10.3900}
	};

enum 
	E_FUEL_STATION {
		Float: E_X,
		Float: E_Y,
		Float: E_Z
	};

new 
	FuelStation[][E_FUEL_STATION] = {
		{1941.640, -1776.31, 13.6406},
		{1003.270, -937.224, 42.3281},
		{-90.8843, -1168.76, 2.42273},
		{-2025.46, 156.7150, 28.8359},
		{-1675.87, 412.9180, 7.17969},
		{-2410.79, 977.1380, 45.4609},
		{-1471.55, 1863.850, 32.6328},
		{615.2000, 1689.600, 6.99219},
		{1595.520, 2199.220, 10.8203},
		{2116.460, 920.3420, 10.8203},
		{-1328.54, 2677.510, 50.0625},
		{2202.500, 2475.850, 10.8203},
		{1381.800, 459.1540, 20.3452},
		{-1606.21, -2714.03, 48.5335},
		{-2244.19, -2561.06, 31.9219},
		{655.8170, -565.232, 16.3359},
		{2640.600, 1106.420, 10.8203},
		{2147.770, 2748.410, 10.8203}
	};

hook OnGameModeInit() {
	for(new i = 0; i < sizeof(PumpData); i++){
	     PumpData[i][E_AREA] = CreateDynamicSphere(PumpData[i][E_X], PumpData[i][E_Y], PumpData[i][E_Z], 15.00);
	}

	for(new i = 0; i < sizeof(FuelStation); i++) {
		printf("%f", FuelStation[i][E_Y]);
		CreateDynamicMapIcon(FuelStation[i][E_X], FuelStation[i][E_Y], FuelStation[i][E_Z], 47, -1);
		CreateDynamic3DTextLabel(""COLOR_GREEN"Автозаправочная станция\n\n"COLOR_WHITE"Подъезжайте для начала "COLOR_GREEN"заправки\n\n"COLOR_GREEN"/buycanister"COLOR_WHITE" - для покупки канистры "COLOR_GREEN"(" #COST_CANISTER " EXP - " #AMOUNT_FUEL_IN_CANISTER " литров)", -1, FuelStation[i][E_X], FuelStation[i][E_Y], FuelStation[i][E_Z] + 3.00, MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
	}

	CreateDynamic3DTextLabel(""COLOR_BLUE"Станция технического обслужинивая\n\n"COLOR_GREEN"/afuel"COLOR_WHITE" - заправить самолет/вертолет (бесплатно)\n"COLOR_GREEN"/arepair"COLOR_WHITE" - починить самолет (бесплатно)", -1, 1922.69400, -2248.7434, 13.5469 + 5.00, 100.00);
	CreateDynamicMapIcon(1922.69400, -2248.7434, 13.5469, 47, -1);
	CreateDynamic3DTextLabel(""COLOR_BLUE"Станция технического обслужинивая\n\n"COLOR_GREEN"/afuel"COLOR_WHITE" - заправить самолет/вертолет (бесплатно)\n"COLOR_GREEN"/arepair"COLOR_WHITE" - починить самолет (бесплатно)", -1, -1246.1857, -95.792600, 14.1484 + 5.00, 100.00);
	CreateDynamicMapIcon(-1246.1857, -95.792600, 14.1484, 47, -1);
	CreateDynamic3DTextLabel(""COLOR_BLUE"Станция технического обслужинивая\n\n"COLOR_GREEN"/afuel"COLOR_WHITE" - заправить самолет/вертолет (бесплатно)\n"COLOR_GREEN"/arepair"COLOR_WHITE" - починить самолет (бесплатно)", -1, 1608.30190, 1632.04710, 10.8203 + 5.00, 100.00);
	CreateDynamicMapIcon(1608.30190, 1632.04710, 10.8203, 47, -1);
}

hook OnVehicleSpawn(vehicleid) {
	SetVehicleFuel(vehicleid, 20);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

CMD:getfuel(playerid, params[]) {
	new 
		vehicleid = GetPlayerVehicleID(playerid);

	foreach(new i: Vehicle) {
		if(VehicleFuel[i][E_ID] == vehicleid) {
			format(small_string, sizeof(small_string), "%f", VehicleFuel[i][E_FUEL]);
			SendClientMessage(playerid, -1, small_string);
		}
	}
}

ptask CheckPlayerRefill[1000](playerid) {
	for(new i = 0; i < sizeof(PumpData); i++) {
		if(IsPlayerInDynamicArea(playerid, PumpData[i][E_AREA]) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			new 
				vehicleid = GetPlayerVehicleID(playerid);

			if(GetVehicleModel(vehicleid) == 481 || GetVehicleModel(vehicleid) == 509 || GetVehicleModel(vehicleid) == 510) return 1;
			if(GetVehicleFuel(vehicleid) > MAX_REFILL) return 1;
			if(CheckCash(playerid, PRICE_ONE_LITER_GASOLINE_VALUE) == false) return 1;
			RemovePlayerEXP(playerid, PRICE_ONE_LITER_GASOLINE_VALUE, "Заправка автомобиля");

			AddVehicleFuel(vehicleid, 1);

			format(small_string, sizeof(small_string), "~g~~h~~h~%i LITER OF GASOLINE~n~~r~~h~- %i EXP", GetVehicleFuel(vehicleid), PRICE_ONE_LITER_GASOLINE_VALUE);
			GameTextForPlayer(playerid, small_string, 1100, 3);
		} 
	}
	return 1;
}

CMD:afuel(playerid, params[]) {
	if(RouteAir2[playerid] || RouteAir[playerid]) {
		if(IsPlayerInAnyVehicle(playerid) == 0) {
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 30.00, 1608.3019,1632.0471,10.8203) || IsPlayerInRangeOfPoint(playerid, 30.00, -1246.1857,-95.7926,14.1484) || IsPlayerInRangeOfPoint(playerid, 30.00, 1922.6940,-2248.7434,13.5469)) {
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 553 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 519 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 592) {
				SetVehicleFuel(GetPlayerVehicleID(playerid), MAX_REFILL);
				return SendClientMessage(playerid, -1, ""COLOR_GREEN"Самолет успешно заправлен.");
			} else {
				return SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы должны находится в рабочем самолете.");
			}
		} else {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы должны находится на станции технического обслуживания в аэропорту.");
		}
	} else {
		new vehicleid = GetPlayerVehicleID(playerid);
		new modelid = GetVehicleModel(vehicleid);

		if(modelid == 447 || modelid == 469 || modelid == 487)
		{
			SetVehicleFuel(GetPlayerVehicleID(playerid), MAX_REFILL);
			return SendClientMessage(playerid, -1, ""COLOR_GREEN"Вертолет успешно заправлен.");
		}
	} 
	return 1;
}

CMD:arepair(playerid, params[]) {
	if(RouteAir2[playerid] || RouteAir[playerid]) {
		if(IsPlayerInAnyVehicle(playerid) == 0) {
			return 1;
		}
		if(IsPlayerInRangeOfPoint(playerid, 30.00, 1608.3019,1632.0471,10.8203) || IsPlayerInRangeOfPoint(playerid, 30.00, -1246.1857,-95.7926,14.1484) || IsPlayerInRangeOfPoint(playerid, 30.00, 1922.6940,-2248.7434,13.5469)) {
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 553 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 519 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 592) {
				SetVehicleHealth(GetPlayerVehicleID(playerid), 1000.00);
				RepairVehicle(GetPlayerVehicleID(playerid));
				return SendClientMessage(playerid, -1, ""COLOR_GREEN"Самолет успешно отремонтирован.");
			} else {
				return SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы должны находится в рабочем самолете.");
			}
		} else {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы должны находится на станции технического обслуживания в аэропорту.");
		}
	} else {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Команда доступна только пилотам");
	}
}

CMD:buycanister(playerid, params[]) 
{
	for(new i = 0; i < sizeof(PumpData); i++) 
	{
		if(IsPlayerInDynamicArea(playerid, PumpData[i][E_AREA])) 
		{
			if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
			{
				return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Выйдите из машины.");
			}
			if(PlayerInfo[playerid][pCanister] == 1)
			{
				return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У Вас уже есть канистра с топливом.");
			}
			if(CheckCash(playerid, COST_CANISTER) == false) return 1;
			RemovePlayerEXP(playerid, COST_CANISTER, "Покупка канистры с топливом");
			PlayerInfo[playerid][pCanister] = 1;
	 		SetPlayerInt(playerid, "Canister", PlayerInfo[playerid][pCanister]);
	 		ShowAction(playerid, "купил(а) канистру");
	 		return SendClientMessage(playerid, -1, ""COLOR_WHITE"Вы купили канистру с топливом. Для заправки транспорта используйте "COLOR_GREEN"/canister");
		}
	}
	return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы должны находиться на АЗС.");
}

CMD:canister(playerid, params[])
{
	if(!IsPlayerInAnyVehicle(playerid)) 
	{
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы должны находиться в машине.");
	}
	if(PlayerInfo[playerid][pCanister] == 0)
	{
		return SendClientMessage(playerid, -1, ""COLOR_WHITE"У Вас уже нет канистры с топливом, Вы можете приобрести ее на АЗС "COLOR_GREEN"(/gps).");
	}
	new vehicleid = GetPlayerVehicleID(playerid);
	PlayerInfo[playerid][pCanister] -= 1;
	SetPlayerInt(playerid, "Canister", PlayerInfo[playerid][pCanister]);

	AddVehicleFuel(vehicleid, AMOUNT_FUEL_IN_CANISTER);
	SendClientMessage(playerid, -1, ""COLOR_WHITE"Автомобиль успешно заправлен.");
	ShowAction(playerid, "использовал(а) канистру");

	return true;
}