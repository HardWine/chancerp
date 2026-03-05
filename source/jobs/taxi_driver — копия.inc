#if defined _taxi_system_included
	#endinput
#endif
#define _taxi_system_included

#define TAXI_MULTIPLIER 15

new cabAvailible[MAX_PLAYERS] = 1; // По умолчанию 1 - такси от данного игрока недоступно. 2 - игрок за рулем такси и он свободен для заказов
new cabClient[MAX_PLAYERS] = INVALID_PLAYER_ID; // Переменная для ID клиента
new destinationArea[MAX_PLAYERS] = {INVALID_DYNAMIC_AREA, ...};
new destinationMark[MAX_PLAYERS] = {INVALID_DYNAMIC_MARK, ...};
new taxiPayment[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};

stock GetVehicleDriver(vehicleid) { // Функция чтобы узнать водителя т.с.
	foreach(new i: Player) {
		if(IsPlayerInVehicle(i, vehicleid) == 1) {
		if(GetPlayerVehicleSeat(i) == 0) return i;
		}
	}
	return INVALID_PLAYER_ID;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	new 
	Fraction: fractionid = GetPlayerFraction(playerid),
	vehicle_owner,
	vehicleid = GetPlayerVehicleID(playerid);

	for(new i = 0; i < sizeof(VehicleInfo); i++) {
	if(VehicleInfo[i][VI_VehicleID] == vehicleid) {
	vehicle_owner = VehicleInfo[i][VI_Owner];
	if(vehicle_owner == VO_TAXI) {

    if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER) {
		if(PlayerInfo[playerid][pLicense] == 0) return 1;
		if(GetPVarInt(playerid, "tempjob") > 0) {
		SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
		return RemovePlayerFromVehicle(playerid);
		}
		if(fractionid != FRACTION_NONE) {
		SendClientMessage(playerid, -1, ""COLOR_RED"Вы состоите во фракции");
		return RemovePlayerFromVehicle(playerid);
		}
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали работу на таксопарк. Ваша задача перевозить пассажиров");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"За каждого пассажира вы получите зарплату в начале следующего часа");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Чтобы высадить неадедекватного пассажира используйте:{FFFFFF} /eject");
		SetPVarInt(playerid, "taxijob", 1);
		return cabAvailible[playerid] = 2; // Водитель сел в такси - машина свободна для заказов
	}
	}
	}
	}	
   	return 1;
}
hook OnPlayerEnterVehicle(playerid, vehicleid, ispassanger) {
	if(ispassanger == 1) {
	new vehicle_owner;
	for(new i = 0; i < sizeof(VehicleInfo); i++) {
	if(VehicleInfo[i][VI_VehicleID] == vehicleid) {
	vehicle_owner = VehicleInfo[i][VI_Owner];
	if(vehicle_owner == VO_TAXI) {
	new driverId = GetVehicleDriver(vehicleid);
	if(driverId == INVALID_PLAYER_ID) return 1; 
	SendClientMessage(playerid, -1, ""COLOR_YELLOW"Вас приветствутет городское такси Downtown Cab Co.");
	if(cabAvailible[driverId] == 1 && cabClient[driverId] != INVALID_PLAYER_ID) return SendClientMessage(playerid, -1, ""COLOR_RED"Такси в данный момент едет по навигатору");
	// Если водителя нет или заказ уже сделан возвращаем 1
	SetPVarInt(playerid, "setDestination", 1); // Данный PVar будет проверкой перед выставлением метки на карте
	SetPVarInt(playerid, "cabdriverid", driverId); // Записываем ID водителя в PVar для дальнейшего выставления метки на карте
	
	if(GetPVarInt(playerid,"AntiFloodСallT") > gettime()) return 1;
	SetPVarInt(playerid,"AntiFloodCallT",gettime() + 3);
	SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Downtown Cab Co.", ""COLOR_YELLOW"Мы рады приветствовать Вас в нашем такси. Стоимость проезда: {FFFFFF}Бесплатно\n"COLOR_YELLOW"Чтобы обозначить пункт назначения поставьте метку на карте", "Закрыть", " ");
	}
	}
	}
	}
	return 1;
}
hook OnPlayerExitVehicle(playerid, vehicleid, ispassanger) {
	new 
	Fraction: fractionid = GetPlayerFraction(playerid),
	vehicle_owner;

	for(new i = 0; i < sizeof(VehicleInfo); i++) {
		if(VehicleInfo[i][VI_VehicleID] == vehicleid) {
			vehicle_owner = VehicleInfo[i][VI_Owner];
			if(vehicle_owner == VO_TAXI) {
				if(GetPlayerVehicleSeat(playerid) == 0) {
					if(PlayerInfo[playerid][pLicense] == 0) return 1;
					if(GetPVarInt(playerid, "tempjob") > 0) return 1;
		    		if(fractionid != FRACTION_NONE) return 1;
		    		DeletePVar(playerid, "taxijob");
					cabAvailible[playerid] = 1; // Водитель вышел из такси - удаляем переменную для получения заказа
					if(cabClient[playerid] != INVALID_PLAYER_ID) {
						SendClientMessage(cabClient[playerid], -1, ""COLOR_RED"Водитель покинул такси. Заказ отменен");
						cabClient[playerid] = INVALID_PLAYER_ID;
					}
					if(destinationArea[playerid] != INVALID_DYNAMIC_AREA) DestroyDynamicArea(destinationArea[playerid]);
					if(destinationMark[playerid] != INVALID_DYNAMIC_MARK) DestroyDynamicMapIcon(destinationMark[playerid]);
					return SendClientMessage(playerid, -1, ""COLOR_RED"Вы покинули такси и больше не можете принимать заказы");
				}
				else {
					new driverId = GetVehicleDriver(vehicleid);
					DeletePVar(playerid, "setDestination");
					DeletePVar(playerid, "cabdriverid");
					if(cabClient[driverId] == playerid) {
					cabClient[driverId] = INVALID_PLAYER_ID;
					SendClientMessage(driverId, -1, ""COLOR_RED"Пассажир покинул такси. Заказ отменен");
					if(destinationArea[driverId] != INVALID_DYNAMIC_AREA) DestroyDynamicArea(destinationArea[driverId]);
					if(destinationMark[driverId] != INVALID_DYNAMIC_MARK) DestroyDynamicMapIcon(destinationMark[driverId]);
					cabAvailible[driverId] = 1;
					}
					// Если заказ уже сделан и метка установлена - отменяем и снимаем метку с карты водителя
					// Удаляем PVar
				}
			}
		}
	}
	return 1;
}

hook OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
	if(GetPVarInt(playerid, "setDestination")) { // Если игроку разрешено ставить метку, принимаем её значение и отправляем водителю
		new vehicleid = GetPlayerVehicleID(playerid); // Узнаем ID машины в которой игрок
		new driverId = GetVehicleDriver(vehicleid);
		new driverIdBefore = GetPVarInt(playerid, "cabdriverid");


		DeletePVar(playerid, "setDestination"); // Удаляем VPar игрока для разрешения выставления метки
		DeletePVar(playerid, "cabdriverid"); // ID водителя игроку также больше не пригодится

		if(driverId != driverIdBefore) return SendClientMessage(playerid, -1, ""COLOR_RED"Водитель к которому вы сели покинул такси");


		if(driverId == INVALID_PLAYER_ID || cabClient[driverId] != INVALID_PLAYER_ID || cabClient[driverId] == playerid) return SendClientMessage(playerid, -1, ""COLOR_RED"Водителя нет или такси уже приняло заказ");
		// Если водителя нет или заказ уже сделан возвращаем SCM
		cabAvailible[playerid] = 1; // Делаем таксиста недоступным для новых заказов
		cabClient[driverId] = playerid; // В переменную для водителя такси записываем ID заказчика

		destinationArea[driverId] = CreateDynamicCylinder(Float:fX, Float:fY, -25, 550, 25, -1, -1, driverId);

		destinationMark[driverId] = CreateDynamicMapIcon(Float:fX, Float:fY, 0.0, 19, -1, -1, -1, driverId, -1, MAPICON_GLOBAL, -1, .priority = 1);

		//SetPlayerRaceCheckpoint(driverId, 1 ,Float:fX, Float:fY, Float:fZ, Float:fX, Float:fY, Float:fZ, 20); // Ставим метку водителю

		new Float: hmuch = GetPlayerDistanceFromPoint(playerid, Float:fX, Float:fY, Float:fZ);
		// Записываем в PVar водителя расстояния до точки назначения
		SetPVarFloat(driverId, "DistanceToDestination", Float: hmuch);
		SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Downtown Cab Co.", ""COLOR_GREEN"Cпасибо за ваш заказ. Приятной поездки!", "ОК", "Закрыть");
		//SendClientMessage(playerid, -1, ""COLOR_GREEN"Спасибо за Ваш заказ. Приятной поездки!");
		SPD(driverId, dKickMessage, DIALOG_STYLE_MSGBOX, "Downtown Cab Co.", ""COLOR_YELLOW"Начинайте движение. Место назначения на карте, доставьте пассажира", "ОК", "Закрыть");
		//SendClientMessage(driverId, -1, ""COLOR_YELLOW"Место назначения на карте. Доставьте пассажира");
	}
	return 1;
}
forward OnPlayerEnterDynamicAreaTaxi(playerid, STREAMER_TAG_AREA areaid);
public OnPlayerEnterDynamicAreaTaxi(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == destinationArea[playerid])
 	{
	 	if(cabClient[playerid] != INVALID_PLAYER_ID) { // Если у водителя есть клиент в переменной
			if(destinationArea[playerid] != INVALID_DYNAMIC_AREA) DestroyDynamicArea(destinationArea[playerid]);
			if(destinationMark[playerid] != INVALID_DYNAMIC_MARK) DestroyDynamicMapIcon(destinationMark[playerid]);
			GameTextForPlayer(cabClient[playerid], "~y~Good Luck!", 3500, 0); // Желаем удачи клиенту
			cabClient[playerid] = INVALID_PLAYER_ID; // Удаляем ID клиента из переменной таксиста
			SendClientMessage(playerid, -1, ""COLOR_YELLOW"Вы достигли пункта назначения. Происходит расчет стоимости поездки...");
			taxiPayment[playerid] = SetTimerEx("getPayment",4999, false,"d",playerid);
			PlayerPlaySound(playerid, 3400, 0.0, 0.0, 10.0);
		}	
 	}
 	return 1;
}
forward getPayment(playerid);
public getPayment(playerid) {
	PlayerPlaySound(playerid, 40405, 0.0, 0.0, 10.0);
	new distanceRan = floatround(GetPVarFloat(playerid, "DistanceToDestination")); // Округляем Float расстояния до пункта назначения
	distanceRan = distanceRan/TAXI_MULTIPLIER; // Делим на множитель
	if(distanceRan < 2) return SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Downtown Cab Co.", ""COLOR_RED"Сумма за поездку не начислена. Слишком короткое расстояние", "ОК", "Закрыть");
	PlayerInfo[playerid][pTaxiTotal] += distanceRan;
    SetPlayerInt(playerid, "TaxiTotal", PlayerInfo[playerid][pTaxiTotal]);
    // Прибавляем к ежечасной ЗП таксиста
	format(small_string, sizeof(small_string), "~g~+%d EXP", distanceRan);
	SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Downtown Cab Co.", ""COLOR_GREEN"Сумма за поездку была прибавлена к вашей зарплате", "ОК", "Закрыть");
	GameTextForPlayer(playerid, small_string, 3500, 0);
	return 1;
}
