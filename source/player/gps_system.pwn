#if defined gps_system_included
	#endinput
#endif

#define gps_system_included

#define MAX_GPS_CATEGORY_TITLE 					(38)	
#define MAX_GPS_TITLE 							(51)
#define MAX_GPS_POINT_FOR_CATEGORY 				(12)

#if !defined INVALID_DYNAMIC_CP_ID
	#define INVALID_DYNAMIC_CP_ID 						(-1)
#endif

forward Gps_OnGameModeInit();
forward Gps_OnPlayerConnect(playerid);
forward Gps_OnPlayerDisconnect(playerid, reason);
forward GPS_OnPlayerDeath(playerid);
forward HideGpsForPlayer(playerid);
forward Gps_OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP checkpointid);

enum 
	gps_category__ {
		GC_ID,
		GC_Title[MAX_GPS_CATEGORY_TITLE]
	};

enum
	gps_info__ {
		GI_ID,
		GI_CategoryID,
		GI_Title[MAX_GPS_TITLE],
		Float: GI_X,
		Float: GI_Y,
		Float: GI_Z,
		GI_CheckpointID
	};

static const 
	GpsCategory[][gps_category__] = {
		{1, "Общественные места"},
		{2, "Работы"},
		{3, "Арена"},
		{4, "Государственные организации"},
		{5, "Магазины одежды"},
		{6, "Автосалоны"},
		{7, ""COLOR_BLUE"Частная авиация{FFFFFF}"},
		{8, ""COLOR_BLUE"Яхт-клуб{FFFFFF}"},
		{9, "Банды"},
		{10, "Мафии"},
		{11, "Другие места"},
		{12, ""COLOR_RED"(NEW!) Заправки"}
	},
	GPSInfo[][gps_info__] = {
		// Общественные места
		{1, 1, "Аэропорт - Зал прибытия", 1697.9700,-2326.7898,-2.6797, INVALID_DYNAMIC_CP_ID},
		{2, 1, "Мэрия", 1480.7307, -1724.2634, 13.5469, INVALID_DYNAMIC_CP_ID},
		{3, 1, "Банк", 1420.5402, -1701.6481, 13.5469, INVALID_DYNAMIC_CP_ID},
    	{4, 1, "Автошкола (San Fierro)", -2054.5476, -83.4346, 34.9195, INVALID_DYNAMIC_CP_ID},
   	 	{5, 1, "San News", 1653.9393,-1654.7565,22.5156, INVALID_DYNAMIC_CP_ID},
   	 	{6, 1, "Казино",1022.3159, -1131.8636, 23.8281, INVALID_DYNAMIC_CP_ID},
   	 	{7, 1, "Отель Rodeo", 325.8003, -1514.4475, 36.0325, INVALID_DYNAMIC_CP_ID},
   	 	{8, 1, "Церковь (Los Santos)", 1720.2915,-1739.1632,13.5469, INVALID_DYNAMIC_CP_ID},

   	 	// Работы
   	 	{5, 2, ""COLOR_RED"(NEW) Инкассатор", 1419.9252, -1694.4597, 13.5469, INVALID_DYNAMIC_CP_ID},
   	 	{5, 2, ""COLOR_RED"(NEW) Доставка пиццы", 2097.9111,-1806.4630,13.5540, INVALID_DYNAMIC_CP_ID},
   	 	{5, 2, "Уборщик пляжа", 153.9, -1943.0, 3.77, INVALID_DYNAMIC_CP_ID},
   	 	{5, 2, "Грузчик", 1977.6777, -1995.2330, 13.2810, INVALID_DYNAMIC_CP_ID},
	    {6, 2, "Ферма", -377.0727, -1428.1948, 25.4536, INVALID_DYNAMIC_CP_ID},
	    {7, 2, "Такси", 1778.7756, -1926.5769, 13.3884, INVALID_DYNAMIC_CP_ID},
	    {8, 2, "Водитель мусоровоза", 2210.3093, -1972.8179, 13.3088, INVALID_DYNAMIC_CP_ID},
	    {9, 2, "Водитель автобуса (LS)", 1052.9847, -1786.7516, 13.7352, INVALID_DYNAMIC_CP_ID},
	    {9, 2, "Водитель автобуса (SF)", -1982.5425, 98.7022, 27.6875, INVALID_DYNAMIC_CP_ID},
	    {9, 2, "Водитель автобуса (LV)", 2783.5583, 1279.6698, 10.7500, INVALID_DYNAMIC_CP_ID},
	    {10, 2, "Пилот", 1964.6069, -2174.6199, 13.4907, INVALID_DYNAMIC_CP_ID},
	    //{11, 2, "Дальнобойщик", -50.2242,-295.9560,5.4297, INVALID_DYNAMIC_CP_ID},
	    
	    // Арена
	    {11, 3, "Арена (Los Santos)", 2657.2292,-1672.1495,10.8809, INVALID_DYNAMIC_CP_ID},
	    {12, 3, "Арена (San Fierro)", -2127.3718,-444.1005,35.5344, INVALID_DYNAMIC_CP_ID},
	    {13, 3, "Арена (Las Venturas)", 1098.1600,1703.5334,10.8203, INVALID_DYNAMIC_CP_ID},

	    // Государственные организации
	    {11, 4, "Армия (Las Venturas)", 107.3761, 1928.9530, 18.5616, INVALID_DYNAMIC_CP_ID},
	    {12, 4, "LSPD", 1537.8695, -1689.6699, 13.5469, INVALID_DYNAMIC_CP_ID},
	    {13, 4, "FBI (San Fierro)", -2437.4724, 503.6610, 29.9404, INVALID_DYNAMIC_CP_ID},

	    // Магазины одежды
	    {14, 5, "Ganton Binco", 2245.4731, -1660.2493, 15.2867, INVALID_DYNAMIC_CP_ID},
	    {15, 5, "Victim", 451.9421, -1502.2311, 30.8728, INVALID_DYNAMIC_CP_ID},
	    {16, 5, "Pro Laps", 502.6359, -1353.8206, 16.1328, INVALID_DYNAMIC_CP_ID},
	    {17, 5, "Didier Sachs", 446.6231, -1480.7999, 30.6410, INVALID_DYNAMIC_CP_ID},

	    // Автосалоны
	    {18, 6, "Coutt and Schutz", 2140.4961, -1114.7876, 25.2607, INVALID_DYNAMIC_CP_ID},
	    {19, 6, "Grotti", 558.4465, -1274.4016, 17.2422, INVALID_DYNAMIC_CP_ID},
	    {20, 6, "Wang Cars (San Fierro)", -1977.0460, 292.0228, 35.1719, INVALID_DYNAMIC_CP_ID},
	    {21, 6, "Otto's Autos (San Fierro)", -1634.3658, 1201.8593, 7.1797, INVALID_DYNAMIC_CP_ID},

	    // Avia
		{22, 7, ""COLOR_BLUE"Покупка вертолета"COLOR_WHITE"", 1909.1882, -2638.3318, 13.5469, INVALID_DYNAMIC_CP_ID},
		{23, 7, "Спавн вертолета \"Аэропорт LS\"", 1903.1882, -2638.3318, 13.5469, INVALID_DYNAMIC_CP_ID},
		{24, 7, "Спавн вертолета \"Аэропорт SF\"", -1214.4943,15.7326,14.14849, INVALID_DYNAMIC_CP_ID},
		{25, 7, "Спавн вертолета \"Аэропорт LV\"", 1717.1376,1616.0215,10.0548, INVALID_DYNAMIC_CP_ID},
		{26, 7, "Спавн вертолета \"Центр LS\"", 1544.9669, -1353.2726, 329.7122, INVALID_DYNAMIC_CP_ID},
		{27, 7, "Спавн вертолета \"Маркет LS\"", 1153.8792,-1180.8655,32.8187, INVALID_DYNAMIC_CP_ID},


		// Water
		{28, 8, ""COLOR_BLUE"Покупка водного транспорта"COLOR_WHITE"", 2288.3254, 539.4296, 1.7944, INVALID_DYNAMIC_CP_ID},
		{29, 8, "Спавн водного транспорта \"Порт LV\"", 2288.3438, 536.9011, 1.7944, INVALID_DYNAMIC_CP_ID},

	    // Банды
	 	{30, 9, "Grove Street", 2491.7542, -1668.9608, 13.3359, INVALID_DYNAMIC_CP_ID},
	    {31, 9, "Ballas Gang", 2000.0699,-1114.0537,27.1250, INVALID_DYNAMIC_CP_ID},
	    {32, 9, "Rifa Gang", 2181.5093, -1798.2538, 13.3640, INVALID_DYNAMIC_CP_ID},
	    {33, 9, "Vagos Gang", 2778.6067, -1612.1714, 10.9219, INVALID_DYNAMIC_CP_ID},
	    {34, 9, "Aztecas Gang", 1688.9403, -2112.7820, 13.4849, INVALID_DYNAMIC_CP_ID},

	    // Мафии
	    {35, 10, "Triads Mafia (San Fierro)", -2120.7532,724.2069,69.5625, INVALID_DYNAMIC_CP_ID},
	    {36, 10, "Da Nang Boys (San Fierro)", -1696.5476, 1328.3705, 7.1778, INVALID_DYNAMIC_CP_ID},
	    {37, 10, "Russian Mafia (San Fierro)", -2520.58, 1216.18, 37.43, INVALID_DYNAMIC_CP_ID},

	    // Другие места
	    {38, 11, "Призывной пункт", 1168.6567,1364.5856,10.8125, INVALID_DYNAMIC_CP_ID},
	    {39, 11, "СТО", 993.5794, -1444.8092, 13.5469, INVALID_DYNAMIC_CP_ID},
    	{40, 11, "Автомойка", 1911.2762,-1774.6147,13.3828, INVALID_DYNAMIC_CP_ID},
    	{41, 11, "Притон", 2185.4124, -1667.5599, 14.6993, INVALID_DYNAMIC_CP_ID},
    	{42, 11, "Притон (San Fierro)", -2623.6533, 1409.0173, 7.1016, INVALID_DYNAMIC_CP_ID},
   		{43, 11, "Продажа грибов", 1081.24, -1696.78, 13.55, INVALID_DYNAMIC_CP_ID},
		{44, 11, "Полигон", 324.9771,2534.2307,16.8079, INVALID_DYNAMIC_CP_ID},
		{45, 11, "Метеостанция (Для San News)", -2521.1042,-624.9525,132.7841, INVALID_DYNAMIC_CP_ID},

		{46, 12, "Заправка №1", 1941.64, -1776.31, 13.6406, INVALID_DYNAMIC_CP_ID},
		{47, 12, "Заправка №2", 1003.27, -937.224, 42.3281, INVALID_DYNAMIC_CP_ID},
		{48, 12, "Заправка №3", -90.8843, -1168.76, 2.42273, INVALID_DYNAMIC_CP_ID},
		{49, 12, "Заправка №4", -2025.46, 156.715, 28.8359, INVALID_DYNAMIC_CP_ID},
		{50, 12, "Заправка №5", -1675.87, 412.918, 7.17969, INVALID_DYNAMIC_CP_ID},
		{51, 12, "Заправка №6", -2410.79, 977.138, 45.4609, INVALID_DYNAMIC_CP_ID},
		{52, 12, "Заправка №7", -1471.55, 1863.85, 32.6328, INVALID_DYNAMIC_CP_ID},
		{53, 12, "Заправка №8", 615.2, 1689.6, 6.99219, INVALID_DYNAMIC_CP_ID},
		{54, 12, "Заправка №9", 1595.52, 2199.22, 10.8203, INVALID_DYNAMIC_CP_ID}

	};

public Gps_OnGameModeInit() {
	for(new i = 0; i < sizeof(GPSInfo); i++) {
		GPSInfo[i][GI_CheckpointID] = CreateDynamicCP(GPSInfo[i][GI_X], GPSInfo[i][GI_Y], GPSInfo[i][GI_Z], 6.0, -1, -1, -1, 9000.00);
	}
}

public Gps_OnPlayerConnect(playerid) {
	return HideGpsForPlayer(playerid);
}

public Gps_OnPlayerDisconnect(playerid, reason) {
	return HideGpsForPlayer(playerid);
}

CMD:gps(playerid, params[]) {
	if(GetPVarInt(playerid, "Gps_Active") == 1) {
		SendClientMessage(playerid, -1, ""COLOR_RED"GPS Навигация отключена");
		HideGpsForPlayer(playerid);
	}
	return Dialog_Show(playerid, Dialog:DIALOG_GPS_SHOW_CATEGORY);
}

DialogCreate:DIALOG_GPS_SHOW_CATEGORY(playerid) {
	new 
		gps_string_all[(sizeof(GpsCategory) * MAX_GPS_CATEGORY_TITLE) + 50 / 4],
		gps_string[MAX_GPS_CATEGORY_TITLE + 100];

	gps_string_all = !"№\tНазвание\n";

	for(new i = 0; i < sizeof(GpsCategory); i++) {
		format(gps_string, sizeof(gps_string), "%i\t%s\n", GpsCategory[i][GC_ID], GpsCategory[i][GC_Title]);
		strcat(gps_string_all, gps_string);
	}

	return Dialog_Open(playerid, Dialog:DIALOG_GPS_SHOW_CATEGORY, DIALOG_STYLE_TABLIST_HEADERS,
		"GPS Навигация",
		gps_string_all,
		"Выбрать", "Закрыть"
	);
}

DialogResponse:DIALOG_GPS_SHOW_CATEGORY(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		new 
			strval_inputtext = listitem + 1;

		if(strval_inputtext < 0 && strval_inputtext > sizeof(GpsCategory)) {
			SendClientMessage(playerid, -1, ""COLOR_RED"Указано неверное значение");
			return Dialog_Show(playerid, Dialog:DIALOG_GPS_SHOW_CATEGORY);
		}
		SetPVarInt(playerid, "GPS_Category", strval_inputtext);
		return Dialog_Show(playerid, Dialog:DIALOG_GPS_SHOW_POINT);
	}
}

DialogCreate:DIALOG_GPS_SHOW_POINT(playerid) {
	new 
		gps_string_all[(MAX_GPS_TITLE * MAX_GPS_POINT_FOR_CATEGORY) + 50 / 2],
		gps_string[MAX_GPS_TITLE + 100],
		gps_categoryid = GetPVarInt(playerid, "GPS_Category");
	
	gps_string_all = !""COLOR_BLUE"№\t"COLOR_BLUE"Название\t"COLOR_BLUE"Расстояние\n"COLOR_WHITE"";

	new 
		total_iterator,
		Float: distance;

	for(new i = 0; i < sizeof(GPSInfo); i++) {
		if(GPSInfo[i][GI_CategoryID] == gps_categoryid) {
			total_iterator = total_iterator + 1;

			distance = GetPlayerDistanceFromPoint(playerid, GPSInfo[i][GI_X], GPSInfo[i][GI_Y], GPSInfo[i][GI_Z]);

			format(gps_string, sizeof(gps_string), "%i\t%s\t"COLOR_GREEN"%0.2f m."COLOR_WHITE"\n", total_iterator, GPSInfo[i][GI_Title], distance);
			strcat(gps_string_all, gps_string);
		}
	}

	return Dialog_Open(playerid, Dialog:DIALOG_GPS_SHOW_POINT, DIALOG_STYLE_TABLIST_HEADERS,
		"GPS Навигация",
		gps_string_all,
		"Выбрать", "Назад"
	);
}

DialogResponse:DIALOG_GPS_SHOW_POINT(playerid, response, listitem, inputtext[]) {
	if(!response) {
		DeletePVar(playerid, "GPS_Category");
		return Dialog_Show(playerid, Dialog:DIALOG_GPS_SHOW_CATEGORY);
	} else {
		new 
			gps_id = listitem + 1,
			gps_categoryid = GetPVarInt(playerid, "GPS_Category"),
			total_iterator;

		for(new i = 0; i < sizeof(GPSInfo); i++) {
			if(GPSInfo[i][GI_CategoryID] == gps_categoryid) {
				total_iterator = total_iterator + 1;

				if(total_iterator == gps_id) {
					if(GetPlayerAdminLevel(playerid) > 2) {
						if(IsPlayerInAnyVehicle(playerid) == 0) {
							SetPlayerPos(playerid, GPSInfo[i][GI_X], GPSInfo[i][GI_Y], GPSInfo[i][GI_Z]);
							SetPlayerInterior(playerid, 0);
							SetPlayerVirtualWorld(playerid, 0);
							return SetCameraBehindPlayer(playerid);
						} else {
							new vehicleid = GetPlayerVehicleID(playerid);

							SetVehiclePos(vehicleid, GPSInfo[i][GI_X], GPSInfo[i][GI_Y], GPSInfo[i][GI_Z]);
							SetVehicleVirtualWorld(vehicleid, 0);
							LinkVehicleToInterior(vehicleid, 0);
							return SetCameraBehindPlayer(playerid);
						}
					}
					TogglePlayerDynamicCP(playerid, GPSInfo[i][GI_CheckpointID], true);
					Streamer_Update(playerid, STREAMER_TYPE_CP);

					SetPVarInt(playerid, "Gps_Active", 1);

					static string[37 + MAX_GPS_TITLE + 1];
					format(string, sizeof(string), "GPS Навигатор активен: "COLOR_GREEN"%s", GPSInfo[i][GI_Title]);
					return SendClientMessage(playerid, -1, string);
				}
			}
		}
		SendClientMessage(playerid, -1, ""COLOR_RED"Указано неверное значение");
		return Dialog_Show(playerid, Dialog:DIALOG_GPS_SHOW_POINT);
	}
}

public HideGpsForPlayer(playerid) {
	for(new i = 0; i < sizeof(GPSInfo); i++) {
		TogglePlayerDynamicCP(playerid, GPSInfo[i][GI_CheckpointID], false);
	}
	return Streamer_Update(playerid, STREAMER_TYPE_CP);
}

public Gps_OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP checkpointid) {
	for(new i = 0; i < sizeof(GPSInfo); i++) {
		if(GPSInfo[i][GI_CheckpointID] == checkpointid) {
			static string[42 + MAX_GPS_TITLE + 1];
			TogglePlayerDynamicCP(playerid, GPSInfo[i][GI_CheckpointID], false);
			Streamer_Update(playerid, STREAMER_TYPE_CP);

			DeletePVar(playerid, "Gps_Active");

			format(string, sizeof(string), "Местоположение достигнуто: "COLOR_GREEN"%s", GPSInfo[i][GI_Title]);
			SendClientMessage(playerid, -1, string);
			return 1;
		}
	}
	return 0;
}

public GPS_OnPlayerDeath(playerid) {
	if(GetPVarInt(playerid, "Gps_Active") == 1) {
		SendClientMessage(playerid, -1, ""COLOR_RED"GPS Навигация отключена");
		HideGpsForPlayer(playerid);
		DeletePVar(playerid, "Gps_Active");
	}
}