#if defined job_collector_included
	#endinput
#endif

#define job_collector_included

#define MAX_PLAYER_COLLECTORS_LOADED_MONEY 			(9)

#include <YSI_Coding\y_hooks>

enum 
	E_COORDINATES_ATM {
		Float: E_X,
		Float: E_Y,
		Float: E_Z
	};

new 
	CollectionVehicles[13];

new 
	CoordinatesAtm[][E_COORDINATES_ATM] = {
		{1464.44180, -1749.2397, 15.4453},
		{1094.96780, -1803.0066, 13.6040},
		{-382.31020, -1433.5862, 25.7266},
		{562.332700, -1293.2828, 17.2482},
		{1049.99430, -1131.7157, 23.8281},
		{1752.20130, -1898.7198, 13.5575},
		{460.876600, -1511.9993, 30.9612},
		{-1981.2650, 121.810400, 27.6875},
		{-2243.0112, 116.319200, 35.3203},
		{-2035.2722, -101.37100, 35.1641},
		{-1828.0797, 3.96960000, 15.1172},
		{-1692.5946, 414.807900, 7.17970},
		{-1641.5057, 1208.08840, 7.17970},
		{-2629.3960, 1404.44800, 7.09380},
		{-855.83220, 1529.52230, 22.5870},
		{-300.26240, 1045.58560, 19.5831},
		{54.3784000, 1211.02800, 18.8838},
		{2089.87080, 1459.73630, 10.8203},
		{2086.32100, 2059.58810, 11.0579},
		{1629.11190, 1811.45590, 10.8203},
		{1715.85020, 1533.07420, 10.7629},
		{1718.52150, 1312.88330, 10.8052},
		{2271.15750, 82.7118000, 26.4844},
		{-2444.5059, 512.888600, 29.9181},
		{-1968.6960, 458.502300, 35.1719},
		{2019.96670, 1014.09700, 10.8203},
		{2107.34060, 897.430600, 11.1797},
		{2499.60740, 926.687100, 11.0234},
		{2646.25420, 1129.01810, 11.1797},
		{2848.74370, 1294.39430, 11.3906},
		{2637.94070, 1675.59810, 11.0234},
		{2638.00320, 1852.87220, 11.0234},
		{2466.83940, 2031.96770, 11.0625},
		{2565.09810, 2064.73140, 11.0995},
		{2366.41060, 2084.51370, 10.8203},
		{2086.34550, 2083.12890, 11.0579},
		{2173.23460, 1411.76050, 11.0625},
		{2281.92970, 2431.74580, 10.8203},
		{2188.36060, 2478.76370, 11.2422},
		{1697.15170, 2208.44380, 11.0692},
		{1590.91520, 2217.34670, 11.0692},
		{1163.66720, 2075.28340, 11.0625},
		{1665.29880, 1412.98140, 10.7907},
		{1665.72940, 1483.01280, 10.7757},
		{1697.61610, -2334.7483, -2.6797},
		{1690.80620, -2238.1514, -2.7142},
		{1690.90690, -2238.1672, 13.5396},
		{1680.38930, -2334.7571, 13.5469}
	};

new 
	PlayerCollectorsLoadingCP[MAX_PLAYERS] = {INVALID_STREAMER_ID, ...},
	PlayerCollectorsUnloadingCP[MAX_PLAYERS] = {INVALID_STREAMER_ID, ...},
	PlayerCollectorsLoadingTimer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...},
	PlayerCollectorsUnloadingTimer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...},
	PlayerCollectorsCheckVehicle[MAX_PLAYERS] = {INVALID_TIMER_ID, ...},
	bool: PlayerJobCollectors[MAX_PLAYERS] = {false, ...},
	PlayerCollectorsLoadedMoney[MAX_PLAYERS] = {0, ...};

new 
	CollectorsStartArea;

new 
	area_ls,
	area_sf,
	area_lv;

new
 	PlayerText:td_cash[MAX_PLAYERS][2];

hook OnGameModeInit() {
	area_ls = CreateDynamicCuboid(2926.2161, -2745.0596, -5000.1186, 56.7278, -382.4064, 5000.8638);
	area_sf = CreateDynamicCuboid(-2841.8604, -885.3775, -5000.2652, -1489.8456, 1552.7531, 5000.1493);
	area_lv = CreateDynamicCuboid(901.7102, 2907.3877, -5000.9711, 2908.2710, 586.7558, 5000.4937);

	CollectionVehicles[0] = AddStaticVehicleEx(428, 1423.9000, -1692.3000, 13.8000, 180.0000, 6, 14, 60);
	CollectionVehicles[1] = AddStaticVehicleEx(428, 1423.9000, -1684.3000, 13.8000, 180.0000, 6, 14, 60);
	CollectionVehicles[2] = AddStaticVehicleEx(428, 1423.9000, -1676.3000, 13.8000, 180.0000, 6, 14, 60);
	CollectionVehicles[3] = AddStaticVehicleEx(428, 1423.9000, -1668.3000, 13.8000, 180.0000, 6, 14, 60);
	CollectionVehicles[4] = AddStaticVehicleEx(428, 1423.9000, -1660.3000, 13.8000, 180.0000, 6, 14, 60);
	CollectionVehicles[5] = AddStaticVehicleEx(428, 1362.4889, -1661.3163, 13.5079, 270.0000, 6, 14, 60);
	CollectionVehicles[6] = AddStaticVehicleEx(428, 1362.4833, -1657.3116, 13.5080, 270.0000, 6, 14, 60);
	CollectionVehicles[7] = AddStaticVehicleEx(428, 1362.4833, -1653.3116, 13.5080, 270.0000, 6, 14, 60);
	CollectionVehicles[8] = AddStaticVehicleEx(428, 1362.4833, -1649.3116, 13.5080, 270.0000, 6, 14, 60);
	CollectionVehicles[9] = AddStaticVehicleEx(428, 1362.4833, -1645.3116, 13.5080, 270.0000, 6, 14, 60);
	CollectionVehicles[10] = AddStaticVehicleEx(428, 1362.4833, -1641.3116, 13.5080, 270.0000, 6, 14, 60);
	CollectionVehicles[11] = AddStaticVehicleEx(428, 1362.4833, -1637.3116, 13.5080, 270.0000, 6, 14, 60);
	CollectionVehicles[12] = AddStaticVehicleEx(428, 1363.4833, -1633.3116, 13.5074, 270.0000, 6, 14, 60);


	
	// Пикап трудоустройства
	new 
		Float: job_x = 1419.9252,
		Float: job_y = -1694.4597,
		Float: job_z = 13.5469;

	new 
		job_inter = 0,
		job_world = 0;

	CreateDynamicPickup(1275, 23, 
		job_x, job_y, job_z, 
		job_world, job_inter
	);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Работа инкаcсатора", -1, job_x, job_y, job_z + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, job_world, job_inter, -1, MAX_DISTANCE_VISIBLE
	);
	CollectorsStartArea = CreateDynamicSphere(job_x, job_y, job_z, 
		1.00, job_world, job_inter
	);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

stock GenerationPoint(const playerid) {
	new 
		total_point = PlayerCollectorsLoadedMoney[playerid],
		current_area = area_ls;

	format(small_string, sizeof(small_string), "Los_Santos");

	switch(total_point) {
		case 3, 4, 5: {
			format(small_string, sizeof(small_string), "San_Fierro");
			current_area = area_sf;
		}
		case 6, 7, 8: {
			format(small_string, sizeof(small_string), "Las_Venturas");
			current_area = area_lv;
		}
	}
	
	PlayerTextDrawSetString(playerid, td_cash[playerid][1], small_string);
	SetPVarInt(playerid, "td_cash", GetPVarInt(playerid, "td_cash") + RandomEx(7000, 1000000));

	format(small_string, sizeof(small_string), "%i$", GetPVarInt(playerid, "td_cash"));

	PlayerTextDrawSetString(playerid, td_cash[playerid][0], small_string);

	printf("%i %i", total_point, current_area);
	new 
		random_point;

	do {
		random_point = random(sizeof(CoordinatesAtm));
	} while(!IsPointInDynamicArea(current_area, 
		CoordinatesAtm[random_point][E_X], 
		CoordinatesAtm[random_point][E_Y], 
		CoordinatesAtm[random_point][E_Z])
	);
	
	return random_point;
}

hook OnPlayerConnect(playerid) {
	PlayerCollectorsLoadingCP[playerid] = INVALID_STREAMER_ID;
	PlayerCollectorsUnloadingCP[playerid] = INVALID_STREAMER_ID;
	PlayerCollectorsLoadedMoney[playerid] = 0;
	PlayerJobCollectors[playerid] = false;

	PlayerCollectorsLoadingTimer[playerid] = INVALID_TIMER_ID;
	PlayerCollectorsUnloadingTimer[playerid] = INVALID_TIMER_ID;
	PlayerCollectorsCheckVehicle[playerid] = INVALID_TIMER_ID;

	td_cash[playerid][0] = CreatePlayerTextDraw(playerid, 84.0000, 184.3999, "0$"); // от 0 до 9999999
	PlayerTextDrawLetterSize(playerid, td_cash[playerid][0], 0.6490, 2.7255);
	PlayerTextDrawTextSize(playerid, td_cash[playerid][0], 0.0000, 106.0000);
	PlayerTextDrawAlignment(playerid, td_cash[playerid][0], 2);
	PlayerTextDrawColor(playerid, td_cash[playerid][0], 8388863);
	PlayerTextDrawUseBox(playerid, td_cash[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, td_cash[playerid][0], 128);
	PlayerTextDrawSetOutline(playerid, td_cash[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, td_cash[playerid][0], 255);
	PlayerTextDrawFont(playerid, td_cash[playerid][0], 3);
	PlayerTextDrawSetProportional(playerid, td_cash[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, td_cash[playerid][0], 0);

	td_cash[playerid][1] = CreatePlayerTextDraw(playerid, 72.5000, 164.2399, "Las_Venturas"); // пусто
	PlayerTextDrawLetterSize(playerid, td_cash[playerid][1], 0.5884, 2.2943);
	PlayerTextDrawTextSize(playerid, td_cash[playerid][1], 0.0000, -23.0000);
	PlayerTextDrawAlignment(playerid, td_cash[playerid][1], 2);
	PlayerTextDrawColor(playerid, td_cash[playerid][1], -1);
	PlayerTextDrawSetOutline(playerid, td_cash[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, td_cash[playerid][1], 255);
	PlayerTextDrawFont(playerid, td_cash[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, td_cash[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, td_cash[playerid][1], 0);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason 

	PlayerJobCollectors[playerid] = false;

	if(PlayerCollectorsLoadingCP[playerid] != INVALID_STREAMER_ID) {
		DestroyDynamicCP(PlayerCollectorsLoadingCP[playerid]);
	}
	PlayerCollectorsLoadingCP[playerid] = INVALID_STREAMER_ID;

	if(PlayerCollectorsUnloadingCP[playerid] != INVALID_STREAMER_ID) {
		DestroyDynamicCP(PlayerCollectorsUnloadingCP[playerid]);
	}
	PlayerCollectorsUnloadingCP[playerid] = INVALID_STREAMER_ID;

	PlayerCollectorsLoadedMoney[playerid] = 0;

	if(PlayerCollectorsLoadingTimer[playerid] != INVALID_TIMER_ID) {
		KillTimer(PlayerCollectorsLoadingTimer[playerid]);
	}
	PlayerCollectorsLoadingTimer[playerid] = INVALID_TIMER_ID;

	if(PlayerCollectorsUnloadingTimer[playerid] != INVALID_TIMER_ID) {
		KillTimer(PlayerCollectorsUnloadingTimer[playerid]);
	}
	PlayerCollectorsUnloadingTimer[playerid] = INVALID_TIMER_ID;

	if(PlayerCollectorsCheckVehicle[playerid] != INVALID_TIMER_ID) {
		KillTimer(PlayerCollectorsCheckVehicle[playerid]);
	}
	PlayerCollectorsCheckVehicle[playerid] = INVALID_TIMER_ID;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == CollectorsStartArea) {
		Dialog_Show(playerid, Dialog:DIALOG_JOB_COLLECTORS);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) { 
	new 
		vehicleid = GetPlayerVehicleID(playerid);

	if(newstate == PLAYER_STATE_DRIVER) {
		for(new i = 0; i < sizeof(CollectionVehicles); i++) {
			if(IsValidVehicle(CollectionVehicles[i]) && vehicleid == CollectionVehicles[i]) {
				if(PlayerJobCollectors[playerid] == false) {
					RemovePlayerFromVehicle(playerid);
					SendClientMessage(playerid, -1, ""COLOR_WHITE"Вы не работаете "COLOR_GREEN"инкасcатором!");
					return Y_HOOKS_BREAK_RETURN_1;
				}

				if(PlayerCollectorsCheckVehicle[playerid] != INVALID_TIMER_ID) {
					KillTimer(PlayerCollectorsCheckVehicle[playerid]);
					PlayerCollectorsCheckVehicle[playerid] = INVALID_TIMER_ID;
					SetPVarInt(playerid, "MinusTime", 0);
				}

				if(PlayerCollectorsLoadingCP[playerid] == INVALID_STREAMER_ID) {
					for(new j = 0; j < sizeof(td_cash[]); j++) {
						PlayerTextDrawShow(playerid, td_cash[playerid][j]);
					}

					new 
						random_element_array = GenerationPoint(playerid);

	 				PlayerCollectorsLoadingCP[playerid] = CreateDynamicCP(
	 					CoordinatesAtm[random_element_array][E_X], CoordinatesAtm[random_element_array][E_Y], CoordinatesAtm[random_element_array][E_Z], 
	 					.size = 10.00, .playerid = playerid, .streamdistance = 16000.00, .priority = 202
	 				);
	 				Streamer_Update(playerid, STREAMER_TYPE_CP);
	 				SendClientMessage(playerid, -1, ""COLOR_ORANGE"Отправляйтесь к отмеченному "COLOR_WHITE"на миникарте"COLOR_ORANGE" банкомату");
				}
 				return Y_HOOKS_CONTINUE_RETURN_1;
			} 
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP checkpointid) {
	if(PlayerJobCollectors[playerid] == true) {

		@_PlayerCollectorsCheckVehicle(playerid);

		if(PlayerCollectorsLoadingCP[playerid] != INVALID_STREAMER_ID && checkpointid == PlayerCollectorsLoadingCP[playerid]) {
			DestroyDynamicCP(PlayerCollectorsLoadingCP[playerid]);
			PlayerCollectorsLoadingCP[playerid] = INVALID_STREAMER_ID;

			SendClientMessage(playerid, -1, ""COLOR_WHITE"Ожидайте окончания процесса "COLOR_GREEN"инкассации");

			TogglePlayerControllable(playerid, false);

			SetPVarInt(playerid, "MinusTime", 10);
			PlayerCollectorsLoadingTimer[playerid] = SetTimerEx("@_PlayerLoadingCollectorsMoney", 10 * 1000, false, "i", playerid);
			return Y_HOOKS_BREAK_RETURN_1;
		} else if(PlayerCollectorsUnloadingCP[playerid] != INVALID_STREAMER_ID && checkpointid == PlayerCollectorsUnloadingCP[playerid]) {
			DestroyDynamicCP(PlayerCollectorsUnloadingCP[playerid]);
			PlayerCollectorsUnloadingCP[playerid] = INVALID_STREAMER_ID;
			PlayerCollectorsLoadedMoney[playerid] = 0;

			SendClientMessage(playerid, -1, ""COLOR_WHITE"Ожидайте окончания процесса "COLOR_GREEN"инкассации");

			SetPVarInt(playerid, "MinusTime", 10);
			PlayerCollectorsUnloadingTimer[playerid] = SetTimerEx("@_PlayerUnloadingCollectorsMone", 10 * 1000, false, "i", playerid);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerExitVehicle(playerid, vehicleid) {
	new 
		modelid = GetVehicleModel(vehicleid);

	if(modelid == 428 && PlayerCollectorsCheckVehicle[playerid] == INVALID_TIMER_ID) {
		PlayerCollectorsCheckVehicle[playerid] = SetTimerEx("@_PlayerCollectorsCheckVehicle", 20 * 1000, false, "i", playerid);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

@_PlayerLoadingCollectorsMoney(const playerid);
@_PlayerLoadingCollectorsMoney(const playerid) {

	TogglePlayerControllable(playerid, true);

	@_PlayerCollectorsCheckVehicle(playerid);

	PlayerCollectorsLoadedMoney[playerid] = PlayerCollectorsLoadedMoney[playerid] + 1;

	format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы обслужили "COLOR_GREEN"%i"COLOR_WHITE" банкоматов из "COLOR_GREEN"%i"COLOR_WHITE" доступных", PlayerCollectorsLoadedMoney[playerid], MAX_PLAYER_COLLECTORS_LOADED_MONEY);
	SendClientMessage(playerid, -1, small_string);
	if(PlayerCollectorsLoadedMoney[playerid] == MAX_PLAYER_COLLECTORS_LOADED_MONEY) {
		PlayerCollectorsUnloadingCP[playerid] = CreateDynamicCP(
			1375.5109, -1659.0206, 13.5091, 
			.size = 15.00, .playerid = playerid, .streamdistance = 16000.00, .priority = 202
		);
		Streamer_Update(playerid, STREAMER_TYPE_CP);
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Отправляйтесь в "COLOR_WHITE"центральный банк Los Santos"COLOR_ORANGE" для разгрузки фургона");
		return true;
	} else {
		new 
			random_element_array = GenerationPoint(playerid);

		PlayerCollectorsLoadingCP[playerid] = CreateDynamicCP(
			CoordinatesAtm[random_element_array][E_X], CoordinatesAtm[random_element_array][E_Y], CoordinatesAtm[random_element_array][E_Z], 
			.size = 15.00, .playerid = playerid, .streamdistance = 16000.00, .priority = 202
		);
		Streamer_Update(playerid, STREAMER_TYPE_CP);
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Отправляйтесь к отмеченному "COLOR_WHITE"на миникарте"COLOR_ORANGE" банкомату");
		return true;
	}
}

@_PlayerUnloadingCollectorsMone(const playerid);
@_PlayerUnloadingCollectorsMone(const playerid) {

	TogglePlayerControllable(playerid, true);

	format(small_string, sizeof(small_string), "%i$", 0);

	PlayerTextDrawSetString(playerid, td_cash[playerid][0], small_string);
	SetPVarInt(playerid, "td_cash", 0);

	AddPlayerEXP(playerid, 500, "Работа инкаcсатором");
	SendClientMessage(playerid, -1, ""COLOR_BLUE"Вы получили 500 EXP за рабочий день");
	UpdatePlayerProgressQuest(playerid, E_JOB_COLLECTORS);
	TogglePlayerControllable(playerid, true);

	/*
	new 
		random_element_array = GenerationPoint(playerid);



	PlayerCollectorsLoadingCP[playerid] = CreateDynamicCP(
		CoordinatesAtm[random_element_array][E_X], CoordinatesAtm[random_element_array][E_Y], CoordinatesAtm[random_element_array][E_Z], 
		.size = 15.00, .playerid = playerid, .streamdistance = 16000.00, .priority = 202
	);
	Streamer_Update(playerid, STREAMER_TYPE_CP);
	SendClientMessage(playerid, -1, ""COLOR_ORANGE"Отправляйтесь к отмеченному "COLOR_WHITE"на миникарте"COLOR_ORANGE" банкомату");*/
	return true;
}

@_PlayerCollectorsCheckVehicle(const playerid);
@_PlayerCollectorsCheckVehicle(const playerid) {
	new 
		vehicleid = GetPlayerVehicleID(playerid),
		modelid = GetVehicleModel(vehicleid);

	if(modelid != 428) {
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Рабочий день инкаcсатора был завершен");

		PlayerJobCollectors[playerid] = false;
		PlayerCollectorsLoadedMoney[playerid] = 0;
		if(PlayerCollectorsLoadingTimer[playerid] != INVALID_TIMER_ID) {
			KillTimer(PlayerCollectorsLoadingTimer[playerid]);
		}
		PlayerCollectorsLoadingTimer[playerid] = INVALID_TIMER_ID;

		if(PlayerCollectorsUnloadingTimer[playerid] != INVALID_TIMER_ID) {
			KillTimer(PlayerCollectorsUnloadingTimer[playerid]);
		}
		PlayerCollectorsUnloadingTimer[playerid] = INVALID_TIMER_ID;

		if(PlayerCollectorsCheckVehicle[playerid] != INVALID_TIMER_ID) {
			KillTimer(PlayerCollectorsCheckVehicle[playerid]);
		}
		PlayerCollectorsCheckVehicle[playerid] = INVALID_TIMER_ID;

		if(PlayerCollectorsLoadingCP[playerid] != INVALID_STREAMER_ID) {
			DestroyDynamicCP(PlayerCollectorsLoadingCP[playerid]);
		}
		PlayerCollectorsLoadingCP[playerid] = INVALID_STREAMER_ID;

		if(PlayerCollectorsUnloadingCP[playerid] != INVALID_STREAMER_ID) {
			DestroyDynamicCP(PlayerCollectorsUnloadingCP[playerid]);
		}
		PlayerCollectorsUnloadingCP[playerid] = INVALID_STREAMER_ID;

		for(new i = 0; i < sizeof(td_cash[]); i++) {
			PlayerTextDrawHide(playerid, td_cash[playerid][i]);
		}
		return true;
	}

	PlayerCollectorsCheckVehicle[playerid] = INVALID_TIMER_ID;
	return false;
}

DialogCreate:DIALOG_JOB_COLLECTORS(playerid) {
	if(PlayerJobCollectors[playerid] == false) {
		return Dialog_Open(playerid, Dialog:DIALOG_JOB_COLLECTORS, DIALOG_STYLE_MSGBOX,
			""COLOR_BLUE"Работа инкаcсатора",
			""COLOR_WHITE"Инкассатор занимается инкассацией и доставкой денег из\n\
			банкоматов в банк, Профессия инкассатора сложная и\n\
			ответственная, требует определенных навыков и качеств от\n\
			исполнителя.\n\n\
			"COLOR_GREEN"Вы уверены, что хотите устроиться на работу?",
			"Да", "Нет"
		);
	} else {
		return Dialog_Open(playerid, Dialog:DIALOG_JOB_COLLECTORS, DIALOG_STYLE_MSGBOX,
			""COLOR_BLUE"Работа инкасcатора",
			""COLOR_WHITE"Инкассатор занимается инкассацией и доставкой денег из\n\
			банкоматов в банк, Профессия инкассатора сложная и\n\
			ответственная, требует определенных навыков и качеств от\n\
			исполнителя.\n\n\
			"COLOR_ORANGE"Вы уверены, что хотите закончить работу?",
			"Да", "Нет"
		);
	}
}

DialogResponse:DIALOG_JOB_COLLECTORS(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		if(PlayerJobCollectors[playerid] == false) {
			PlayerJobCollectors[playerid] = true;
			SendClientMessage(playerid, -1, ""COLOR_WHITE"Вы начали работу инкаcсатора. Отправляйтесь к стоянке, и сядьте в "COLOR_GREEN"бронированный фургон");
			return true;
		} else {
			PlayerJobCollectors[playerid] = false;

			PlayerCollectorsLoadedMoney[playerid] = 0;
			if(PlayerCollectorsLoadingTimer[playerid] != INVALID_TIMER_ID) {
				KillTimer(PlayerCollectorsLoadingTimer[playerid]);
			}
			PlayerCollectorsLoadingTimer[playerid] = INVALID_TIMER_ID;

			if(PlayerCollectorsUnloadingTimer[playerid] != INVALID_TIMER_ID) {
				KillTimer(PlayerCollectorsUnloadingTimer[playerid]);
			}
			PlayerCollectorsUnloadingTimer[playerid] = INVALID_TIMER_ID;

			if(PlayerCollectorsCheckVehicle[playerid] != INVALID_TIMER_ID) {
				KillTimer(PlayerCollectorsCheckVehicle[playerid]);
			}
			PlayerCollectorsCheckVehicle[playerid] = INVALID_TIMER_ID;

			if(PlayerCollectorsLoadingCP[playerid] != INVALID_STREAMER_ID) {
				DestroyDynamicCP(PlayerCollectorsLoadingCP[playerid]);
			}
			PlayerCollectorsLoadingCP[playerid] = INVALID_STREAMER_ID;

			if(PlayerCollectorsUnloadingCP[playerid] != INVALID_STREAMER_ID) {
				DestroyDynamicCP(PlayerCollectorsUnloadingCP[playerid]);
			}
			PlayerCollectorsUnloadingCP[playerid] = INVALID_STREAMER_ID;

			for(new i = 0; i < sizeof(td_cash[]); i++) {
				PlayerTextDrawHide(playerid, td_cash[playerid][i]);
			}

			SendClientMessage(playerid, -1, ""COLOR_WHITE"Вы завершили работу "COLOR_GREEN"инкассатора");
			return true;
		}
	}
}