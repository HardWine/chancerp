#if defined gps_system_included
	#endinput
#endif

#define gps_system_included

#define MAX_GPS_CATEGORY 						(8)
#define MAX_GPS 								(33)
#define MAX_GPS_CATEGORY_TITLE 					(32)	
#define MAX_GPS_TITLE 							(32)
#define MAX_GPS_POINT_FOR_CATEGORY 				(8)

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
	GpsCategory[MAX_GPS_CATEGORY][gps_category__] = {
		{1, "Общественные места"},
		{2, "Работы"},
		{3, "Государственные организации"},
		{4, "Магазины одежды"},
		{5, "Автосалоны"},
		{6, "Банды"},
		{7, "Мафии"},
		{8, "Другие места"}
	},
	GPSInfo[MAX_GPS][gps_info__] = {
		// Общественные места
		{1, 1, "Мэрия", 1480.7307, -1724.2634, 13.5469, INVALID_DYNAMIC_CP_ID},
		{2, 1, "Банк", 1420.5402, -1701.6481, 13.5469, INVALID_DYNAMIC_CP_ID},
    	{3, 1, "Автошкола (San Fierro)", -2054.5476, -83.4346, 34.9195, INVALID_DYNAMIC_CP_ID},
   	 	{4, 1, "Казино",1022.3159, -1131.8636, 23.8281, INVALID_DYNAMIC_CP_ID},

   	 	// Работы
   	 	{5, 2, "Грузчик", 1977.6777, -1995.2330, 13.2810, INVALID_DYNAMIC_CP_ID},
	    {6, 2, "Ферма", -377.0727, -1428.1948, 25.4536, INVALID_DYNAMIC_CP_ID},
	    {7, 2, "Такси", 1778.7756, -1926.5769, 13.3884, INVALID_DYNAMIC_CP_ID},
	    {8, 2, "Водитель мусоровоза", 2210.3093, -1972.8179, 13.3088, INVALID_DYNAMIC_CP_ID},
	    {9, 2, "Водитель автобуса (LS)", 1052.9847, -1786.7516, 13.7352, INVALID_DYNAMIC_CP_ID},
	    {9, 2, "Водитель автобуса (SF)", -1982.5425, 98.7022, 27.6875, INVALID_DYNAMIC_CP_ID},
	    {9, 2, "Водитель автобуса (LV)", 2783.5583, 1279.6698, 10.7500, INVALID_DYNAMIC_CP_ID},
	    {10, 2, "Пилот", 1964.6069, -2174.6199, 13.4907, INVALID_DYNAMIC_CP_ID},

	    // Государственные организации
	    {11, 3, "Армия (Las Venturas)", 107.3761, 1928.9530, 18.5616, INVALID_DYNAMIC_CP_ID},
	    {12, 3, "LSPD", 1537.8695, -1689.6699, 13.5469, INVALID_DYNAMIC_CP_ID},
	    {13, 3, "FBI (San Fierro)", -2437.4724, 503.6610, 29.9404, INVALID_DYNAMIC_CP_ID},

	    // Магазины одежды
	    {14, 4, "Ganton Binco", 2245.4731, -1660.2493, 15.2867, INVALID_DYNAMIC_CP_ID},
	    {15, 4, "Victim", 451.9421, -1502.2311, 30.8728, INVALID_DYNAMIC_CP_ID},
	    {16, 4, "Pro Laps", 502.6359, -1353.8206, 16.1328, INVALID_DYNAMIC_CP_ID},
	    {17, 4, "Didier Sachs", 446.6231, -1480.7999, 30.6410, INVALID_DYNAMIC_CP_ID},

	    // Автосалоны
	    {18, 5, "Coutt and Schutz", 2140.4961, -1114.7876, 25.2607, INVALID_DYNAMIC_CP_ID},
	    {19, 5, "Grotti", 558.4465, -1274.4016, 17.2422, INVALID_DYNAMIC_CP_ID},
	    {20, 5, "Wang Cars (San Fierro)", -1977.0460, 292.0228, 35.1719, INVALID_DYNAMIC_CP_ID},
	    {21, 5, "Otto's Autos (San Fierro)", -1634.3658, 1201.8593, 7.1797, INVALID_DYNAMIC_CP_ID},

	    // Банды
	 	{22, 6, "Grove Street", 2491.7542, -1668.9608, 13.3359, INVALID_DYNAMIC_CP_ID},
	    {23, 6, "Ballas Gang", 2647.6831, -2003.8358, 13.3828, INVALID_DYNAMIC_CP_ID},
	    {24, 6, "Rifa Gang", 2181.5093, -1798.2538, 13.3640, INVALID_DYNAMIC_CP_ID},
	    {25, 6, "Vagos Gang", 2778.6067, -1612.1714, 10.9219, INVALID_DYNAMIC_CP_ID},
	    {26, 6, "Aztecas Gang", 1688.9403, -2112.7820, 13.4849, INVALID_DYNAMIC_CP_ID},

	    // Мафии
	    {27, 7, "Triads Mafia (San Fierro)", -2244.6636, 576.0410, 35.1719, INVALID_DYNAMIC_CP_ID},
	    {28, 7, "Da Nang Boys (San Fierro)", -1696.5476, 1328.3705, 7.1778, INVALID_DYNAMIC_CP_ID},
	    {29, 7, "Russian Mafia (Las Venturas)", 944.2119, 1733.2594, 8.8516, INVALID_DYNAMIC_CP_ID},

	    // Другие места
	    {30, 8, "Притон", 2185.4124, -1667.5599, 14.6993, INVALID_DYNAMIC_CP_ID},
    	{31, 8, "СТО", 993.5794, -1444.8092, 13.5469, INVALID_DYNAMIC_CP_ID}
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
	if(Platform[playerid] == 0) return SendClientMessage(playerid, -1, !"Мобильная версия навигатора в разработке");
	if(GetPVarInt(playerid, "Gps_Active") == 1) {
		SendClientMessage(playerid, -1, ""COLOR_RED"GPS Навигация отключена.");
		HideGpsForPlayer(playerid);
	}
	return Dialog_Show(playerid, Dialog:DIALOG_GPS_SHOW_CATEGORY);
}

DialogCreate:DIALOG_GPS_SHOW_CATEGORY(playerid) {
	new 
		gps_string_all[(MAX_GPS_CATEGORY * MAX_GPS_CATEGORY_TITLE) + 50 / 4],
		gps_string[MAX_GPS_CATEGORY_TITLE + 10];

	gps_string_all = !""COLOR_WHITE"№\t"COLOR_WHITE"Название\n"COLOR_WHITE"";

	for(new i = 0; i < sizeof(GpsCategory); i++) {
		format(gps_string, sizeof(gps_string), "%i\t%s\n", GpsCategory[i][GC_ID], GpsCategory[i][GC_Title]);
		strcat(gps_string_all, gps_string);
	}

	return Dialog_Open(playerid, Dialog:DIALOG_GPS_SHOW_CATEGORY, DIALOG_STYLE_TABLIST_HEADERS,
		""COLOR_BLUE"GPS Навигация",
		gps_string_all,
		"Выбрать", "Закрыть"
	);
}

DialogResponse:DIALOG_GPS_SHOW_CATEGORY(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		SetPVarInt(playerid, "GPS_Category", strval(inputtext));
		return Dialog_Show(playerid, Dialog:DIALOG_GPS_SHOW_POINT);
	}
}

DialogCreate:DIALOG_GPS_SHOW_POINT(playerid) {
	new 
		gps_string_all[(MAX_GPS_TITLE * MAX_GPS_POINT_FOR_CATEGORY) + 50 / 2],
		gps_string[MAX_GPS_TITLE + 30],
		gps_categoryid = GetPVarInt(playerid, "GPS_Category");
	
	gps_string_all = !""COLOR_WHITE"№\t"COLOR_WHITE"Название\t"COLOR_WHITE"Расстояние\n"COLOR_WHITE"";

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
		""COLOR_BLUE"GPS Навигация",
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
			gps_id = strval(inputtext),
			gps_categoryid = GetPVarInt(playerid, "GPS_Category"),
			total_iterator;

		for(new i = 0; i < sizeof(GPSInfo); i++) {
			if(GPSInfo[i][GI_CategoryID] == gps_categoryid) {
				total_iterator = total_iterator + 1;

				if(total_iterator == gps_id) {
					if(GetPlayerAdminLevel(playerid) > 3) {
						SetPlayerPos(playerid, GPSInfo[i][GI_X], GPSInfo[i][GI_Y], GPSInfo[i][GI_Z]);
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
						return SetCameraBehindPlayer(playerid);
					}
					TogglePlayerDynamicCP(playerid, GPSInfo[i][GI_CheckpointID], true);
					Streamer_Update(playerid, STREAMER_TYPE_CP);

					SetPVarInt(playerid, "Gps_Active", 1);

					static string[37 + MAX_GPS_TITLE + 1];
					format(string, sizeof(string), "GPS Навигатор автивен: "COLOR_GREEN"%s", GPSInfo[i][GI_Title]);
					return SendClientMessage(playerid, -1, string);
				}
			}
		}
	}
	return 1;
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
		SendClientMessage(playerid, -1, ""COLOR_RED"GPS Навигация отключена.");
		HideGpsForPlayer(playerid);
		DeletePVar(playerid, "Gps_Active");
	}
}