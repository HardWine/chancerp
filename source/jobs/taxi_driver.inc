#if defined _taxi_system_included
	#endinput
#endif
#define _taxi_system_included

#define TAXI_MULTIPLIER 15

new cabAvailible[MAX_PLAYERS] = 1; // По умолчанию 1 - такси от данного игрока недоступно. 2 - игрок за рулем такси и он свободен для заказов
new cabClient[MAX_PLAYERS] = INVALID_PLAYER_ID; // Переменная для ID клиента
new destinationMark[MAX_PLAYERS] = {INVALID_DYNAMIC_CP, ...};
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
		if(fractionid != FRACTION_NONE && GetPlayerJobDayStatus(playerid) == true) {
		SendClientMessage(playerid, -1, ""COLOR_RED"Вы состоите во фракции");
		return RemovePlayerFromVehicle(playerid);
		}
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали работу на таксопарк. Ваша задача перевозить пассажиров");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"За каждого пассажира вы получите зарплату в начале следующего часа");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Чтобы высадить неадекватного пассажира используйте:{FFFFFF} /eject");
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
	if(driverId == playerid) return 1; 
	if(driverId == INVALID_PLAYER_ID) return 1; 
	SendClientMessage(playerid, -1, ""COLOR_YELLOW"Вас приветствутет городское такси Downtown Cab Co.");
	if(cabAvailible[driverId] == 1 && cabClient[driverId] != INVALID_PLAYER_ID) return SendClientMessage(playerid, -1, ""COLOR_RED"Такси в данный момент едет по навигатору");
	// Если водителя нет или заказ уже сделан возвращаем 1
	SetPVarInt(playerid, "setDestination", 1); // Данный PVar будет проверкой перед выставлением метки на карте
	SetPVarInt(playerid, "cabdriverid", driverId); // Записываем ID водителя в PVar для дальнейшего выставления метки на карте
	
	if(GetPVarInt(playerid,"AntiFloodСallT") > gettime()) return 1;
	SetPVarInt(playerid,"AntiFloodCallT",gettime() + 3);
	SendClientMessage(playerid, -1, ""COLOR_YELLOW"Мы рады приветствовать Вас в нашем такси. Стоимость проезда: {FFFFFF}Бесплатно");
	SendClientMessage(playerid, -1, ""COLOR_YELLOW"Чтобы обозначить пункт назначения поставьте метку на карте");
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
		    		if(fractionid != FRACTION_NONE && GetPlayerJobDayStatus(playerid) == true) return 1;
		    		DeletePVar(playerid, "taxijob");
					cabAvailible[playerid] = 1; // Водитель вышел из такси - удаляем переменную для получения заказа
					if(cabClient[playerid] != INVALID_PLAYER_ID) {
						SendClientMessage(cabClient[playerid], -1, ""COLOR_RED"Водитель покинул такси. Заказ отменен");
						cabClient[playerid] = INVALID_PLAYER_ID;
					}
					if(destinationMark[playerid] != INVALID_DYNAMIC_CP) {
						DestroyDynamicCP(destinationMark[playerid]);
						destinationMark[playerid] = INVALID_DYNAMIC_CP;
					}
					return SendClientMessage(playerid, -1, ""COLOR_RED"Вы покинули такси и больше не можете принимать заказы");
				}
				else {
					new driverId = GetVehicleDriver(vehicleid);
					DeletePVar(playerid, "setDestination");
					DeletePVar(playerid, "cabdriverid");
					if(cabClient[driverId] == playerid) {
					cabClient[driverId] = INVALID_PLAYER_ID;
					SendClientMessage(driverId, -1, ""COLOR_RED"Пассажир покинул такси. Заказ отменен");
					if(destinationMark[driverId] != INVALID_DYNAMIC_CP) {
						DestroyDynamicCP(destinationMark[driverId]);
						destinationMark[driverId] = INVALID_DYNAMIC_CP;
					}
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
		new
	    Float: fZZ;
		GetPointZPos(Float:fX, Float:fY, fZZ);		

		// Если водителя нет или заказ уже сделан возвращаем SCM
		cabAvailible[playerid] = 1; // Делаем таксиста недоступным для новых заказов
		cabClient[driverId] = playerid; // В переменную для водителя такси записываем ID заказчика

		destinationMark[driverId] = CreateDynamicCP(Float:fX, Float:fY, Float:fZZ, 25.00, 0, 0, driverId, 60000.000, .priority = 1);
		Streamer_Update(driverId, STREAMER_TYPE_CP);
			

		new Float: hmuch = GetPlayerDistanceFromPoint(playerid, Float:fX, Float:fY, Float:fZ);
		// Записываем в PVar водителя расстояния до точки назначения
		SetPVarFloat(driverId, "DistanceToDestination", Float: hmuch);
		SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Downtown Cab Co.", ""COLOR_GREEN"Cпасибо за ваш заказ. Приятной поездки!", "ОК", "Закрыть");
		//SendClientMessage(playerid, -1, ""COLOR_GREEN"Спасибо за Ваш заказ. Приятной поездки!");
		SendClientMessage(driverId, -1, ""COLOR_YELLOW"Начинайте движение. Место назначения на карте, доставьте пассажира");
		//SendClientMessage(driverId, -1, ""COLOR_YELLOW"Место назначения на карте. Доставьте пассажира");
	}
	return 1;
}
stock Taxi_OnPlayerEnterDynamicCP(playerid, checkpointid) {
	if(checkpointid == destinationMark[playerid])
 	{
 		if(!IsPlayerInAnyVehicle(playerid)) {
 			DeletePVar(playerid, "taxijob");
			cabAvailible[playerid] = 1; // Водитель вышел из такси - удаляем переменную для получения заказа
			if(cabClient[playerid] != INVALID_PLAYER_ID) {
				SendClientMessage(cabClient[playerid], -1, ""COLOR_RED"Водитель покинул такси. Заказ отменен");
				cabClient[playerid] = INVALID_PLAYER_ID;
			}
			if(destinationMark[playerid] != INVALID_DYNAMIC_CP) {
				DestroyDynamicCP(destinationMark[playerid]);
				destinationMark[playerid] = INVALID_DYNAMIC_CP;
			}
			return 1;
 		}
	 	if(cabClient[playerid] != INVALID_PLAYER_ID) { // Если у водителя есть клиент в переменной
			if(destinationMark[playerid] != INVALID_DYNAMIC_CP) {
				DestroyDynamicCP(destinationMark[playerid]);
				destinationMark[playerid] = INVALID_DYNAMIC_CP;
			}
			AddPlayerAchievement(playerid, E_TRIFLE);	
			GameTextForPlayer(cabClient[playerid], "~y~Good Luck!", 3500, 0); // Желаем удачи клиенту
			cabClient[playerid] = INVALID_PLAYER_ID; // Удаляем ID клиента из переменной таксиста
			SendClientMessage(playerid, -1, ""COLOR_YELLOW"Вы достигли пункта назначения. Происходит расчет стоимости поездки...");
			taxiPayment[playerid] = SetTimerEx("getPayment",4999, false,"d",playerid);
			PlayerPlaySound(playerid, 3400, 0.0, 0.0, 10.0);
			return 1;
		}	
 	}
 	return 0;
}
forward getPayment(playerid);
public getPayment(playerid) {
	PlayerPlaySound(playerid, 40405, 0.0, 0.0, 10.0);
	new distanceRan = floatround(GetPVarFloat(playerid, "DistanceToDestination")); // Округляем Float расстояния до пункта назначения
	distanceRan = (distanceRan/TAXI_MULTIPLIER); // Делим на множитель
	if(distanceRan < 2) return SendClientMessage(playerid, -1, ""COLOR_RED"Сумма за поездку не начислена. Слишком короткое расстояние");
	PlayerInfo[playerid][pTaxiTotal] += distanceRan;
    SetPlayerInt(playerid, "TaxiTotal", PlayerInfo[playerid][pTaxiTotal]);
    // Прибавляем к ежечасной ЗП таксиста
	format(small_string, sizeof(small_string), "~g~+%d EXP", distanceRan);
	SendClientMessage(playerid, -1, ""COLOR_GREEN"Сумма за поездку была прибавлена к вашей зарплате");
	GameTextForPlayer(playerid, small_string, 3500, 0);
	AddPlayerEXP(playerid, distanceRan, "Работа таксистом");
	return 1;
}

CMD:taxi(playerid, params[]) {
	if(GetPVarInt(playerid,"AntiTLocal") > gettime()) { SendClientMessage(playerid, -1, ""COLOR_RED"Нельзя использовать так часто"); return false; }
	//if(PlayerInfo[playerid][pDevice] == 0) return SendClientMessage(playerid, -1, ""COLOR_RED"Вам нужен пейджер или телефон. Купите его в магазине");
	if(sscanf(params,"s",params[0])) return SendClientMessage(playerid, -1, "Используйте: /taxi [место, куда вам нужно]");

	if(GetPVarInt(playerid, "taxijob")) return 1;
	if(GetPVarInt(playerid, "taxi_called")) return 1;

	if(GetPlayerInterior(playerid) != 0 && GetPlayerVirtualWorld(playerid) != 0) return 1;

	SendClientMessage(playerid, -1, ""COLOR_YELLOW"Вас приветствутет Downtown Cab Co., мы приняли ваш заказ...");
	SendClientMessage(playerid, -1, ""COLOR_YELLOW"и отправили его всем таксистам в нашем городе. Ожидайте");
	callcmd::cabs(playerid,"\0");
	SendTaxiMessage(params,playerid);
	SetPVarInt(playerid,"AntiTLocal",gettime() + 120);
	SetPVarInt(playerid, "taxi_called", 90);
	return 1;
}
CMD:pick(playerid, params[]) {
	new orderid;
	if(sscanf(params,"d",orderid)) return SendClientMessage(playerid, -1, ""COLOR_RED"Используйте: /pick [ID заказчика]");
	if(orderid == playerid) return 1;
	if(GetPVarInt(orderid, "taxi_called")) {
		format(small_string, sizeof(small_string), ""COLOR_GREEN"Водитель {FFFFFF}%s[%d]"COLOR_GREEN" принял ваш заказ", PlayerInfo[playerid][pName],playerid);
		SendClientMessage(orderid, -1, small_string);
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы приняли заказ, местоположение клиента отмечено на карте красной меткой");
		cabAvailible[playerid] = 1;
		new 
			Float: pos_x,
			Float: pos_y,
			Float: pos_z;

		GetPlayerPos(orderid, pos_x, pos_y, pos_z);
		SetPlayerRaceCheckpoint(playerid, 1, pos_x, pos_y, pos_z, pos_x, pos_y, pos_z, 5);
		SetPVarInt(playerid, "taxi_order", 300);
		DeletePVar(orderid, "taxi_called");
	}
	return 1;
}
CMD:cabs(playerid, params[]) {
	if(GetPVarInt(playerid,"AntiTaLocal") > gettime()){ SendClientMessage(playerid, -1, ""COLOR_RED"Нельзя использовать так часто"); return false; }
	SetPVarInt(playerid,"AntiTaLocal",gettime() + 60);
	new c = CountCabs();

	format(small_string, sizeof(small_string), ""COLOR_ORANGE"На текущую минуту {FFFFFF}%d"COLOR_ORANGE" такси свободно", c);
	SendClientMessage(playerid, -1, small_string);
	return 1;
}

forward SendTaxiMessage(string[],senderid);
public SendTaxiMessage(string[],senderid)
{
	new 
		Float: pos_x,
		Float: pos_y,
		Float: pos_z;

	GetPlayerPos(senderid, pos_x, pos_y, pos_z);	

	foreach(new i: Player)
	{
		if(cabAvailible[i] == 2)
		{
			new Float:dist = GetPlayerDistanceFromPoint(i, pos_x, pos_y, pos_z);
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"[Заказ] В %.2fм. от вас %s[%d]. Место назначения:", dist, PlayerInfo[senderid][pName],senderid);
			SendClientMessage(i, -1, small_string);
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"[Заказ] {FFFFFF}'%s'", string);
			SendClientMessage(i, -1, small_string);			
			SendClientMessage(i, -1, ""COLOR_ORANGE"[Заказ] Интересен заказ? Введите: "COLOR_WHITE"/pick [ID заказчика]");
		}
	}
}
forward SendTChatMessage(string[]);
public SendTChatMessage(string[])
{
	foreach(new i: Player)
	{
		if(GetPVarInt(i, "taxijob") == 1) SendClientMessage(i, -1, string);
	}
}

stock CountCabs() {
	new cabs = 0;
	foreach(new i: Player)
	{
		if(cabAvailible[i] == 2) cabs++;
	}
	return cabs;
}

CMD:tchat(playerid, params[]) {
	if(GetPVarInt(playerid, "taxijob") == 1)
		{
			SendClientMessage(playerid, -1, "Используйте: /tc [текст]");
		}
	return 1;
}
CMD:tc(playerid, params[]) {

	if(GetPVarInt(playerid, "taxijob") == 1) {
		if(!params[0]) return SendClientMessage(playerid, -1, "Используйте: /tc [текст]");
		if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У вас бан чата");
		new tstate;
		if(cabAvailible[playerid] == 2) tstate = 0;
		else tstate = 1;
		if(tstate == 1) format(small_string, sizeof(small_string),""COLOR_RED"[На заказе]{FFFFFF} %s: %s",PlayerInfo[playerid][pName],params[0]);
		else format(small_string, sizeof(small_string),""COLOR_GREEN"[Свободен]{FFFFFF} %s: %s",PlayerInfo[playerid][pName],params[0]);
		SendTChatMessage(small_string);
	}
	return 1;
}
CMD:tcn(playerid, params[]) {
	if(GetPVarInt(playerid, "taxijob") == 1) {
		if(!params[0]) return SendClientMessage(playerid, -1, "Используйте: /tcn [текст]");
		if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У вас бан чата");
		new tstate;
		if(cabAvailible[playerid] == 2) tstate = 0;
		else tstate = 1;
		if(tstate == 1) format(small_string, sizeof(small_string),""COLOR_RED"[На заказе]{FFFFFF} %s: (( %s ))",PlayerInfo[playerid][pName],params[0]);
		else format(small_string, sizeof(small_string),""COLOR_GREEN"[Свободен]{FFFFFF} %s: (( %s ))",PlayerInfo[playerid][pName],params[0]);
		SendTChatMessage(small_string);
	}
	return 1;
}