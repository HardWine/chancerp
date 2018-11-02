#if defined vehicle_system_included
	#endinput
#endif

#define vehicle_system_included

#define TABLE_VEHICLE 				"vehicle"

forward LoadVehicle();
forward Vehicle_OnGameModeInit();
forward Vehicle_OnPlayerEnterVehicle(playerid, vehicleid);
forward Vehicle_OnPlayerExitVehicle(playerid, vehicleid);

enum {
	VO_FREE = 1, // Бесплатный
	VO_TAXI, // Такси
	VO_GIVE_LIC, // Сдача на права (наземный)
	VO_GIVE_LIC_AIR, // Сдача на права (воздушный)
	VO_JOB_TRASH, // Работа на мусоровозе
	VO_BUS_LS, // Автобус (ЛС)
	VO_BUS_SF, // Автобус (СФ)
	VO_BUS_LV, // Автобус (ЛВ)
	VO_AIR_LS, // Самолеты (ЛС)
	VO_AIR_LV, // Самолеты (ЛВ)
	VO_FARM, // Ферма
	VO_FRACTION_GROOVE, // Организаций - Grove Street
	VO_FRACTION_RUSSIAN_MAFIA, // Организаций - Русская Мафия
	VO_FRACTION_TRIADA, // Организаций - Triads
	VO_FRACTION_DN_BOYS, // Организаций - Da Nang Boys
	VO_FRACTION_BALLAS, // Организаций - Ballas Gang
	VO_FRACTION_AZTECAS, // Организаций - Aztecas Gang
	VO_FRACTION_VAGOS, // Организаций - Vagos Gang
	VO_FRACTION_RIFA, // Организаций - Rifa Gang
	VO_FRACTION_LSPD, // Организаций - LSPD
	VO_FRACTION_GOVERMENT, // Организаций - Правительство
	VO_FRACTION_FBI, // Организаций - FBI
	VO_FRACTION_ARMY // Организаций - Армия
};

enum 
	vehicle_info__ {
		VI_ID,
		VI_VehicleID,
		VI_ModelID,
		Float: VI_X,
		Float: VI_Y,
		Float: VI_Z,
		Float: VI_Angle,
		VI_Inter,
		VI_World,
		VI_Color1,
		VI_Color2,
		VI_RespawnTime,
		VI_Owner
	};

new 
	VehicleInfo[250][vehicle_info__];

public Vehicle_OnGameModeInit() {
	for(new i = 0; i < sizeof(VehicleInfo); i++) {
		VehicleInfo[i][VI_VehicleID] = INVALID_VEHICLE_ID;
	}

	return mysql_pquery(database, "SELECT `ID`, CONVERT(ModelID, SIGNED) as ModelID, `X`, `Y`, `Z`, `Angle`, `World`, `Inter`, `Color_1`, `Color_2`, `RespawnTime`, CONVERT(Own, SIGNED) as Own FROM "TABLE_VEHICLE"", "LoadVehicle");
}

public LoadVehicle() {
	new 
		rows = cache_get_row_count();

	if(rows) {
		for(new i = 0; i < rows; i++) {
			VehicleInfo[i][VI_ID] = cache_get_field_content_int(i, "ID");
			VehicleInfo[i][VI_ModelID] = cache_get_field_content_int(i, "ModelID");
			VehicleInfo[i][VI_Owner] = cache_get_field_content_int(i, "Own");
			VehicleInfo[i][VI_ModelID] = VehicleInfo[i][VI_ModelID] + 399;

			VehicleInfo[i][VI_X] = cache_get_field_content_float(i, "X");
			VehicleInfo[i][VI_Y] = cache_get_field_content_float(i, "Y");
			VehicleInfo[i][VI_Z] = cache_get_field_content_float(i, "Z");
			VehicleInfo[i][VI_Angle] = cache_get_field_content_float(i, "Angle");

			VehicleInfo[i][VI_World] = cache_get_field_content_int(i, "World");
			VehicleInfo[i][VI_Inter] = cache_get_field_content_int(i, "Inter");

			VehicleInfo[i][VI_Color1] = cache_get_field_content_int(i, "Color_1");
			VehicleInfo[i][VI_Color2] = cache_get_field_content_int(i, "Color_2");
			VehicleInfo[i][VI_RespawnTime] = cache_get_field_content_int(i, "RespawnTime");

			VehicleInfo[i][VI_VehicleID] = AddStaticVehicleEx(VehicleInfo[i][VI_ModelID], 
				VehicleInfo[i][VI_X], VehicleInfo[i][VI_Y], VehicleInfo[i][VI_Z], VehicleInfo[i][VI_Angle], 
				VehicleInfo[i][VI_Color1], VehicleInfo[i][VI_Color2], VehicleInfo[i][VI_RespawnTime]
			);
			LinkVehicleToInterior(VehicleInfo[i][VI_VehicleID], VehicleInfo[i][VI_Inter]);
			SetVehicleVirtualWorld(VehicleInfo[i][VI_VehicleID], VehicleInfo[i][VI_World]);
		}
	}
}

public Vehicle_OnPlayerEnterVehicle(playerid, vehicleid) {
	new 
		Fraction: fractionid = GetPlayerFraction(playerid),
		vehicle_owner;

	for(new i = 0; i < sizeof(VehicleInfo); i++) {
		if(VehicleInfo[i][VI_VehicleID] == vehicleid) {
			vehicle_owner = VehicleInfo[i][VI_Owner];

			if(vehicle_owner == VO_FREE) {
				// if(PlayerInfo[playerid][pLicense] == 0)
				// {
				//     SendClientMessage(playerid, -1, ""COLOR_RED"У Вас нет водительских прав");
				//     SendClientMessage(playerid, -1, ""COLOR_RED"Получить лицензию можно в Автошколе Сан-Фиерро");
				//     return 0;
				// }
				return 1;
			} else if(vehicle_owner == VO_TAXI) {
				if(GetPVarInt(playerid, "tempjob") > 0) {
					SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
	    		if(fractionid != FRACTION_NONE) {
	    			SendClientMessage(playerid, -1, ""COLOR_RED"Вы состоите во фракции");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали работу водителем такси. Ваша задача перевозить пассажиров");
				SendClientMessage(playerid, -1, ""COLOR_GREEN"За каждого пассажира вы получите зарплату в начале следующего часа");
				return 1;
			} else if(vehicle_owner == VO_GIVE_LIC) {
				if(GetPVarInt(playerid,"GetLic") == 1)
				{
					SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали сдавать на права. Соблюдайте правила дорожного движения!");
					SetPlayerRaceCheckpoint(playerid, 0, -2047.4313,-83.9501,34.9071, -2004.1478,-46.2495,34.9080, 5);
					RouteLic[playerid] = 1;
					RouteTrash[playerid] = -1;
					RouteFarm[playerid] = -1;
					UnloadFarm[playerid] = -1;
					RouteLicAir[playerid] = -1;
					RouteAir[playerid] = -1;
					RouteAir2[playerid] = -1;
				 	Route2[playerid] = -1;
				 	Route3[playerid] = -1;
				 	Route[playerid] = -1;
				 	ArmyMission[playerid] = -1;
				 	return 5;
				} else {
					return 0;
				}
			} else if(vehicle_owner == VO_GIVE_LIC_AIR) {
				if(GetPVarInt(playerid,"GetLicAir") == 1)
				{
					SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали сдавать экзамен. Не повредите самолет!");
					SetPlayerRaceCheckpoint(playerid, 3, -2052.0408,-187.2903,35.3203, -2059.2136,-295.8495,134.9901, 20);
					RouteLicAir[playerid] = 1;
					RouteTrash[playerid] = -1;
					RouteFarm[playerid] = -1;
					UnloadFarm[playerid] = -1;
					RouteLic[playerid] = -1;
					RouteAir[playerid] = -1;
					RouteAir2[playerid] = -1;
				 	Route2[playerid] = -1;
				 	Route3[playerid] = -1;
				 	Route[playerid] = -1;
				 	ArmyMission[playerid] = -1;
				 	return 5;
				} else {
					return 0;
				}
			} else if(vehicle_owner == VO_JOB_TRASH) {
				if(fractionid != FRACTION_NONE) {
	    			SendClientMessage(playerid, -1, ""COLOR_RED"Вы состоите во фракции");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				if(GetPVarInt(playerid, "tempjob") != 2) {
					SendClientMessage(playerid, -1, "Необходимо начать рабочий день");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				SetPVarInt(playerid,"tempjob", 2);
				SelectBin(playerid);
				ArmyMission[playerid] = -1;
				RouteTrash[playerid] = 1;
				RouteFarm[playerid] = -1;
				UnloadFarm[playerid] = -1;
			 	Route2[playerid] = -1;
			 	Route3[playerid] = -1;
			 	Route[playerid] = -1;
			 	RouteLic[playerid] = -1;
			 	RouteLicAir[playerid] = -1;
			 	RouteAir[playerid] = -1;
			 	RouteAir2[playerid] = -1;
				SendClientMessage(playerid, -1, ""COLOR_ORANGE"Отправляйтесь в указанное на карте место");
			 	return 1;
			} else if(vehicle_owner == VO_BUS_LS) {
				if(fractionid != FRACTION_NONE) {
	    			SendClientMessage(playerid, -1, ""COLOR_RED"Вы состоите во фракции!");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				if(GetPVarInt(playerid, "tempjob") > 0) {
					SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали работу водителем автобуса");
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Увеличивая скилл водителя вы получите больше EXP!");
				SendClientMessage(playerid, -1, ""COLOR_RED"Покинув автобус вы потеряете навык водителя");
			 	SetPlayerRaceCheckpoint(playerid, 0, 1130.6526,-1743.5892,13.1755, 1172.6687,-1770.6853,13.1796, 5); //
			 	Route[playerid] = 1;
			 	RouteTrash[playerid] = -1;
			 	RouteFarm[playerid] = -1;
			 	UnloadFarm[playerid] = -1;
			 	ArmyMission[playerid] = -1;
			 	Route2[playerid] = -1;
			 	Route3[playerid] = -1;
			 	RouteLic[playerid] = -1;
			 	RouteLicAir[playerid] = -1;
			 	RouteAir[playerid] = -1;
			 	RouteAir2[playerid] = -1;
			 	return 1;
			} else if(vehicle_owner == VO_BUS_LV) {
				if(fractionid != FRACTION_NONE) {
	    			SendClientMessage(playerid, -1, ""COLOR_RED"Вы состоите во фракции!");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				if(GetPVarInt(playerid, "tempjob") > 0) {
					SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
		 		RouteAir2[playerid] = -1;
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали работу водителем автобуса");
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Увеличивая скилл водителя вы получите больше EXP!");
				SendClientMessage(playerid, -1, ""COLOR_RED"Покинув автобус вы потеряете навык водителя");
			 	SetPlayerRaceCheckpoint(playerid, 0, 1130.6526,-1743.5892,13.1755, 1172.6687,-1770.6853,13.1796, 5); //
			 	Route[playerid] = 1;
			 	RouteTrash[playerid] = -1;
			 	RouteFarm[playerid] = -1;
			 	UnloadFarm[playerid] = -1;
			 	ArmyMission[playerid] = -1;
			 	Route2[playerid] = -1;
			 	Route3[playerid] = -1;
			 	RouteLic[playerid] = -1;
			 	RouteLicAir[playerid] = -1;
			 	RouteAir[playerid] = -1;
			 	RouteAir2[playerid] = -1;
			 	return 1;
			} else if(vehicle_owner == VO_BUS_SF) {
				if(fractionid != FRACTION_NONE) {
	    			SendClientMessage(playerid, -1, ""COLOR_RED"Вы состоите во фракции!");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				if(GetPVarInt(playerid, "tempjob") > 0) {
					SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
		 		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали работу водителем автобуса");
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Увеличивая скилл водителя вы получите больше EXP!");
				SendClientMessage(playerid, -1, ""COLOR_RED"Покинув автобус вы потеряете навык водителя");
			 	SetPlayerRaceCheckpoint(playerid, 1,-1988.6450,138.3930,27.2461,-1988.6450,138.3930,27.2461, 5);

			 	Route3[playerid] = 1;
			 	RouteTrash[playerid] = -1;
			 	RouteFarm[playerid] = -1;
			 	UnloadFarm[playerid] = -1;
			 	ArmyMission[playerid] = -1;
			 	Route2[playerid] = -1;
			 	Route[playerid] = -1;
			 	RouteLic[playerid] = -1;
			 	RouteLicAir[playerid] = -1;
			 	RouteAir[playerid] = -1;
			 	RouteAir2[playerid] = -1;
			 	return 1;
			}
			else if(vehicle_owner == VO_FRACTION_GROOVE) {
				if(fractionid != FRACTION_GROOVE) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"Вы не состоите в Grove Street");
					RemovePlayerFromVehicle(playerid);	
					return 0;
				}
				return 1;
			} else if(vehicle_owner == VO_FRACTION_RUSSIAN_MAFIA) {
				if(fractionid != FRACTION_RUSSIAN_MAFIA) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"Вы не состоите в Russian Mafia");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				return 1;
			} else if(vehicle_owner == VO_FRACTION_TRIADA) {
				if(fractionid != FRACTION_TRIADA) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"Вы не состоите в Triads");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				return 1;
			} else if(vehicle_owner == VO_FRACTION_DN_BOYS) {
				if(fractionid != FRACTION_DN_BOYS) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"Вы не состоите в Da Nang Boys");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				return 1;
			} else if(vehicle_owner == VO_FRACTION_BALLAS) {
				if(fractionid != FRACTION_BALLAS) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"Вы не состоите в Ballas Gang");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				return 1;
			} else if(vehicle_owner == VO_FRACTION_AZTECAS) {
				if(fractionid != FRACTION_AZTECAS) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"Вы не состоите в Aztecas");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				return 1;
			} else if(vehicle_owner == VO_FRACTION_VAGOS) {
				if(fractionid != FRACTION_VAGOS) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"Вы не состоите в Vagos Gang");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				return 1;
			} else if(vehicle_owner == VO_FRACTION_RIFA) {
				if(fractionid != FRACTION_RIFA) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"Вы не состоите в Rifa Gang");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				return 1;
			} else if(vehicle_owner == VO_FRACTION_LSPD) {
				if(fractionid != FRACTION_LSPD) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"Вы не полицейский");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				return 1;
			} else if(vehicle_owner == VO_FRACTION_GOVERMENT) {
				if(fractionid != FRACTION_GOVERMENT) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"Вы не работаете в Мэрии");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				return 1;
			} else if(vehicle_owner == VO_FRACTION_FBI) {
				if(fractionid != FRACTION_FBI) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"Вы не агент FBI");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				return 1;
			} else if(vehicle_owner == VO_FRACTION_ARMY) {
				if(fractionid != FRACTION_ARMY) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"Вы не военный");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}

				if(GetVehicleModel(vehicleid) == 433 || GetVehicleModel(vehicleid) == 548) {
					ArmyMission[playerid] = 1;
					RouteTrash[playerid] = -1;
					RouteFarm[playerid] = -1;
					UnloadFarm[playerid] = -1;
				 	Route2[playerid] = -1;
				 	Route3[playerid] = -1;
				 	Route[playerid] = -1;
				 	RouteLic[playerid] = -1;
				 	RouteLicAir[playerid] = -1;
				 	RouteAir[playerid] = -1;
				 	RouteAir2[playerid] = -1;
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали задание по доставке боеприпасов");
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Покинув транспорт, задание будет провалено");
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Отправляйтесь на загрузку боеприпасов");
					DisablePlayerRaceCheckpoint(playerid);
					SetPlayerRaceCheckpoint(playerid, 1, 328.5100,1963.1115,17.6406, 328.5100,1963.1115,17.6406, 5);
					return 1;
				}
				return 1;
			} else if(vehicle_owner == VO_FARM) {
				if(GetVehicleModel(vehicleid) == 532) {
					if(GetPVarInt(playerid, "tempjob") != 1) {
						SetVehicleToRespawn(vehicleid);
						return 0;
					}
				    if(PlayerInfo[playerid][pFarmSkill] < 500) {
				     	SetVehicleToRespawn(vehicleid);
				    	SendClientMessage(playerid, -1, ""COLOR_RED"Доступно с 500 навыка фермера");
				    	return 0;
				   	}
		  			if(HarvestAmount > 0) {
		  			 	SendClientMessage(playerid, -1, ""COLOR_RED"На поле достаточно урожая");
		  				SetVehicleToRespawn(vehicleid);
		  				return 0;
		  			}
					
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали посев поля");
		  			RouteFarm[playerid] = 1;
		  			UnloadFarm[playerid] = -1;
					RouteLic[playerid] = -1;
					RouteTrash[playerid] = -1;
					RouteLicAir[playerid] = -1;
					RouteAir[playerid] = -1;
					RouteAir2[playerid] = -1;
				 	Route2[playerid] = -1;
				 	Route3[playerid] = -1;
				 	Route[playerid] = -1;
				 	ArmyMission[playerid] = -1;
				 	DisablePlayerRaceCheckpoint(playerid);
		  			SetPlayerRaceCheckpoint(playerid, 0,-322.7826,-1426.0459,14.4216,-275.9756,-1416.3439,10.9044,10); // combine
					return 1;
				} else {
					return 0;
				}
			} else if(vehicle_owner == VO_AIR_LV) {
				if(PlayerInfo[playerid][pLicenseAir] == 0) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"У Вас нет лицензии пилота");
				    SendClientMessage(playerid, -1, ""COLOR_RED"Получить лицензию можно в Автошколе Сан-Фиерро");
				    RemovePlayerFromVehicle(playerid);
				    return 0;
				}
				if(fractionid != FRACTION_NONE) {
	   				SendClientMessage(playerid, -1, ""COLOR_RED"Вы состоите во фракции!");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				if(GetPVarInt(playerid, "tempjob") > 0) {
					SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				if(Runway[0] > 0) {
					SendClientMessage(playerid, -1, ""COLOR_RED"Подождите. В данный момент другой пилот занимает место посадки");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
    			if(GetVehicleModel(vehicleid) == 553) {
    				if((0 <= PlayerInfo[playerid][pAirSkill] <= 99 || PlayerInfo[playerid][pAirSkill] >= 500)) {
    				
    				} else { 
    					SendClientMessage(playerid, -1, ""COLOR_GREEN"С вашим опытом пилота, данный самолет недоступен"); 
    					RemovePlayerFromVehicle(playerid); 
    					return 0;
    				}
    			} else if(GetVehicleModel(vehicleid) == 519) {
    				if((100 <= PlayerInfo[playerid][pAirSkill] <= 499  || PlayerInfo[playerid][pAirSkill] >= 500)) {
		    		
		    		} else { 
    					SendClientMessage(playerid, -1, ""COLOR_GREEN"С вашим опытом пилота, данный самолет недоступен"); 
    					RemovePlayerFromVehicle(playerid); 
    					return 0;
    				}
    			} else if(GetVehicleModel(vehicleid) == 592) {
    				if(PlayerInfo[playerid][pAirSkill] < 499) { 
    					SendClientMessage(playerid, -1, ""COLOR_GREEN"С вашим опытом пилота, данный самолет недоступен"); 
    					RemovePlayerFromVehicle(playerid); 
    					return 0;
    				}
    			}

    			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали работу пилота");
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Увеличивая скилл пилота вы получите больше EXP!");
				SendClientMessage(playerid, -1, ""COLOR_GREEN"В конце рейса вы получите зарплату. Покинув самолет вы прекратите работу");
			 	SetPlayerRaceCheckpoint(playerid, 2, 1507.5469,1463.4788,10.4105, 1477.3033,1497.8701,10.3932, 20);
				RouteAir[playerid] = 1;
			 	Route2[playerid] = -1;
			 	Route3[playerid] = -1;
			 	ArmyMission[playerid] = -1;
			 	Route[playerid] = -1;
			 	RouteLic[playerid] = -1;
			 	RouteLicAir[playerid] = -1;
			 	return 1;
			} else if(vehicle_owner == VO_AIR_LS) {
				if(PlayerInfo[playerid][pLicenseAir] == 0) {
				    SendClientMessage(playerid, -1, ""COLOR_RED"У Вас нет лицензии пилота");
				    SendClientMessage(playerid, -1, ""COLOR_RED"Получить лицензию можно в Автошколе Сан-Фиерро");
				    RemovePlayerFromVehicle(playerid);
				    return 0;
				}
				if(fractionid != FRACTION_NONE) {
	   				SendClientMessage(playerid, -1, ""COLOR_RED"Вы состоите во фракции!");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				if(GetPVarInt(playerid, "tempjob") > 0) {
					SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
				if(Runway[0] > 0) {
					SendClientMessage(playerid, -1, ""COLOR_RED"Подождите. В данный момент другой пилот занимает место посадки");
					RemovePlayerFromVehicle(playerid);
					return 0;
				}
    			if(GetVehicleModel(vehicleid) == 553) {
    				if((0 <= PlayerInfo[playerid][pAirSkill] <= 99 || PlayerInfo[playerid][pAirSkill] >= 500)) {
    				
    				} else { 
    					SendClientMessage(playerid, -1, ""COLOR_GREEN"С вашим опытом пилота, данный самолет недоступен"); 
    					RemovePlayerFromVehicle(playerid); 
    					return 0;
    				}
    			} else if(GetVehicleModel(vehicleid) == 519) {
    				if((100 <= PlayerInfo[playerid][pAirSkill] <= 499  || PlayerInfo[playerid][pAirSkill] >= 500)) {
		    		
		    		} else { 
    					SendClientMessage(playerid, -1, ""COLOR_GREEN"С вашим опытом пилота, данный самолет недоступен"); 
    					RemovePlayerFromVehicle(playerid); 
    					return 0;
    				}
    			} else if(GetVehicleModel(vehicleid) == 592) {
    				if(PlayerInfo[playerid][pAirSkill] < 499) { 
    					SendClientMessage(playerid, -1, ""COLOR_GREEN"С вашим опытом пилота, данный самолет недоступен"); 
    					RemovePlayerFromVehicle(playerid); 
    					return 0;
    				}
    			}
				SetPlayerRaceCheckpoint(playerid, 1, 1914.4653,-2328.6389,13.1067, 1914.4653,-2328.6389,13.1067, 20);
				RouteAir2[playerid] = 1;
				RouteTrash[playerid] = -1;
				RouteFarm[playerid] = -1;
				UnloadFarm[playerid] = -1;
				RouteAir[playerid] = -1;
			 	Route2[playerid] = -1;
			 	Route3[playerid] = -1;
			 	ArmyMission[playerid] = -1;
			 	Route[playerid] = -1;
			 	RouteLic[playerid] = -1;
			 	RouteLicAir[playerid] = -1;
			 	return 1;
			}
		}
	}
	return 2;
}

public Vehicle_OnPlayerExitVehicle(playerid, vehicleid) {
	if(vehicleid != gonecar[playerid]) {
		return -1;
	}

	new 
		vehicle_owner;

	for(new i = 0; i < sizeof(VehicleInfo); i++) {
		if(VehicleInfo[i][VI_VehicleID] == vehicleid) {
			vehicle_owner = VehicleInfo[i][VI_Owner];

			if(vehicle_owner == VO_TAXI || vehicle_owner == VO_GIVE_LIC || vehicle_owner == VO_GIVE_LIC_AIR || vehicle_owner == VO_JOB_TRASH ||
				vehicle_owner == VO_BUS_LS || vehicle_owner == VO_BUS_SF || vehicle_owner == VO_BUS_LV || vehicle_owner == VO_AIR_LS ||
				vehicle_owner == VO_AIR_LV || vehicle_owner == VO_FARM || vehicle_owner == VO_FRACTION_ARMY) {

				if(vehicle_owner == VO_FARM) {
					if(GetVehicleModel(vehicleid) != 532) {
						return 0;
					}
				}

				onfootverify(playerid);
				return 1;
			}
		}
	}
	return 0;
}

stock IsTaxiCar(vehicleid)
{
   	for(new i = 0; i < sizeof(VehicleInfo); i++) {
        if(VehicleInfo[i][VI_VehicleID] == vehicleid) {
        	if(VehicleInfo[i][VI_Owner] == VO_TAXI) {
        		return 1;
        	}
        }
    }
    return 0;
}

stock IsWarehouseCar(vehicleid)
{
	if(GetVehicleModel(vehicleid) != 433 && GetVehicleModel(vehicleid) != 548) {
		return 0;
	}

   	for(new i = 0; i < sizeof(VehicleInfo); i++) {
        if(VehicleInfo[i][VI_VehicleID] == vehicleid) {
        	if(VehicleInfo[i][VI_Owner] == VO_FRACTION_ARMY) {
        		return 1;
        	}
        }
    }
    return 0;
}

CMD:reloadcar(playerid, params[]) {
	for(new i = 0; i < sizeof(VehicleInfo); i++) {
		if(VehicleInfo[i][VI_VehicleID] != INVALID_VEHICLE_ID) {
			DestroyVehicle(VehicleInfo[i][VI_VehicleID]);
		}
		VehicleInfo[i][VI_VehicleID] = INVALID_VEHICLE_ID;
	}

	return Vehicle_OnGameModeInit();
}