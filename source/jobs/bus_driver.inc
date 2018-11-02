#if defined bus_driver_ls_included
	#endinput
#endif

#define bus_driver_ls_included

#if !defined MAX_BUS_LS_POINT
	#error "Not default value defined for MAX_BUS_LS_POINT (bus_driver.inc)"
#endif

#if !defined MAX_BUS_SF_POINT
	#error "Not default value defined for MAX_BUS_SF_POINT (bus_driver.inc)"
#endif

#if !defined MAX_BUS_LV_POINT
	#error "Not default value defined for MAX_BUS_LV_POINT (bus_driver.inc)"
#endif

#if !defined STREAMER_TYPE_BUS_DRIVER
	#error "Not default value defined for STREAMER_TYPE_BUS_DRIVER (bus_driver.inc)"
#endif

#if !defined BUS_RACECP_SIZE
	#define BUS_RACECP_SIZE 							(5.0000) // Размер меток на работе 					
#endif

forward BusDriver_OnGameModeInit();
forward BusDriver_OnPlayerConnect(playerid);
forward BusDriver_OnPlayerDisconnect(playerid);
forward OnPlayerEnterBus(playerid, bus);
forward BusDriver_OP_EnterDynamicRaceCP(playerid, checkpointid);
forward PlayerBusDriverStop(playerid);
forward OnPlayerExitVehicleBus(playerid);
forward BusDriver_OnPlayerLeaveJob(playerid);

new player_route_bus_driver[MAX_PLAYERS char];

new 
	player_bus_ls_stop[MAX_PLAYERS char],
	player_bus_driver_timer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};

enum busdriver__ {
	BLI_CheckpointID, 										// ID чекпоинта
	BLI_CheckpointType, 									// Тип гоночного чекпоинта
	bool: BLI_IsStop, 										// Остановка? (true - да | false - нет)
	Float: BLI_X, 											// Координата X
	Float: BLI_Y, 											// Координата Y
	Float: BLI_Z, 											// Координата Z
	Float: BLI_NextX, 										// Следующая оордината X
	Float: BLI_NextY, 										// Следующая оордината Y
	Float: BLI_NextZ 										// Следующая оордината Z
};

new 
	BusLSInfo[MAX_BUS_LS_POINT][busdriver__] = {
		{INVALID_DYNAMIC_CP, 0, false, 1130.6526, -1743.5892, 13.1755, 1172.6687, -1770.6853, 13.1796},
		{INVALID_DYNAMIC_CP, 0, false, 1172.6687, -1770.6853, 13.1796, 1194.7738, -1854.8091, 13.1752},
		{INVALID_DYNAMIC_CP, 0, false, 1194.7738, -1854.8091, 13.1752, 1314.9088, -1817.0076, 13.1639},
		{INVALID_DYNAMIC_CP, 0, false, 1314.9088, -1817.0076, 13.1639, 1315.0186, -1748.1293, 13.1611},
		{INVALID_DYNAMIC_CP, 0, false, 1315.0186, -1748.1293, 13.1611, 1373.8833, -1735.1019, 13.1635},
		{INVALID_DYNAMIC_CP, 0, false, 1373.8833, -1735.1019, 13.1635, 1445.9802, -1735.4197, 13.1608},
		{INVALID_DYNAMIC_CP, 0, false, 1445.9802, -1735.4197, 13.1608, 1475.4797, -1735.5637, 13.1633},
		{INVALID_DYNAMIC_CP, 1, true, 1475.4797, -1735.5637, 13.1633, 1673.6885, -1735.4968, 13.1609},
		{INVALID_DYNAMIC_CP, 0, false, 1475.4797, -1735.5637, 13.1633, 1673.6885, -1735.4968, 13.1609},
		{INVALID_DYNAMIC_CP, 0, false, 1673.6885, -1735.4968, 13.1609, 1817.8293, -1735.1664, 13.1596},
		{INVALID_DYNAMIC_CP, 0, false, 1817.8293, -1735.1664, 13.1596, 1819.3456, -1813.4141, 13.1844},
		{INVALID_DYNAMIC_CP, 0, false, 1819.3456, -1813.4141, 13.1844, 1819.2897, -1870.4648, 13.1913},
		{INVALID_DYNAMIC_CP, 0, false, 1819.2897, -1870.4648, 13.1913, 1818.7710, -1907.1416, 13.1731},
		{INVALID_DYNAMIC_CP, 1, true, 1818.7710, -1907.1416, 13.1731, 876.8849, -1934.8877, 13.1628},
		{INVALID_DYNAMIC_CP, 0, false, 1818.7710, -1907.1416, 13.1731, 876.8849, -1934.8877, 13.1628},
		{INVALID_DYNAMIC_CP, 0, false, 1876.8849, -1934.8877, 13.1628, 1959.1816, -1969.8948, 13.2184},
		{INVALID_DYNAMIC_CP, 0, false, 1959.1816, -1969.8948, 13.2184, 1958.9706, -2092.0698, 13.1676},
		{INVALID_DYNAMIC_CP, 0, false, 1958.9706, -2092.0698, 13.1676, 1983.7018, -2112.4702, 13.1222},
		{INVALID_DYNAMIC_CP, 0, false, 1983.7018, -2112.4702, 13.1222, 2089.8477, -2112.7598, 13.1037},
		{INVALID_DYNAMIC_CP, 0, false, 2089.8477, -2112.7598, 13.1037, 2179.9163, -2149.9106, 13.1542},
		{INVALID_DYNAMIC_CP, 0, false, 2179.9163, -2149.9106, 13.1542, 2265.0615, -2235.2913, 13.2845},
		{INVALID_DYNAMIC_CP, 0, false, 2265.0615, -2235.2913, 13.2845, 2341.8574, -2236.5745, 13.1521},
		{INVALID_DYNAMIC_CP, 0, false, 2341.8574, -2236.5745, 13.1521, 2545.7178, -2172.6692, 13.0248},
		{INVALID_DYNAMIC_CP, 0, false, 2545.7178, -2172.6692, 13.0248, 2825.4358, -2112.7910, 10.7079},
		{INVALID_DYNAMIC_CP, 0, false, 2825.4358, -2112.7910, 10.7079, 2840.8699, -1941.5917, 10.7159},
		{INVALID_DYNAMIC_CP, 0, false, 2840.8699, -1941.5917, 10.7159, 2801.8223, -1654.7633, 10.4728},
		{INVALID_DYNAMIC_CP, 1, true, 2801.8223, -1654.7633, 10.4728, 2667.0901, -1654.5537, 10.4752},
		{INVALID_DYNAMIC_CP, 0, false, 2801.8223, -1654.7633, 10.4728, 2667.0901, -1654.5537, 10.4752},
		{INVALID_DYNAMIC_CP, 0, false, 2607.9146, -1729.6914, 12.0120, 2532.1121, -1729.4828, 13.1628,},
		{INVALID_DYNAMIC_CP, 0, false, 2532.1121, -1729.4828, 13.1628, 2450.9299, -1729.6489, 13.2863},
		{INVALID_DYNAMIC_CP, 1, true, 2450.9299, -1729.6489, 13.2863, 2276.6689, -1730.1351, 13.1628},
		{INVALID_DYNAMIC_CP, 0, false, 2450.9299, -1729.6489, 13.2863, 2276.6689, -1730.1351, 13.1628},
		{INVALID_DYNAMIC_CP, 0, false, 2276.6689, -1730.1351, 13.1628, 2162.4392, -1748.8833, 13.1573},
		{INVALID_DYNAMIC_CP, 0, false, 2162.4392, -1748.8833, 13.1573, 1960.0845, -1750.0604, 13.1629},
		{INVALID_DYNAMIC_CP, 0, false, 1960.0845, -1750.0604, 13.1629, 1833.9393, -1749.2125, 13.1628},
		{INVALID_DYNAMIC_CP, 0, false, 1833.9393, -1749.2125, 13.1628, 1708.6572, -1729.8389, 13.1629},
		{INVALID_DYNAMIC_CP, 0, false, 1708.6572, -1729.8389, 13.1629, 1692.1533, -1690.3262, 13.1627},
		{INVALID_DYNAMIC_CP, 0, false, 1692.1533, -1690.3262, 13.1627, 1658.2278, -1590.1727, 13.1702},
		{INVALID_DYNAMIC_CP, 0, false, 1658.2278, -1590.1727, 13.1702, 1548.3784, -1589.8077, 13.1627},
		{INVALID_DYNAMIC_CP, 0, false, 1548.3784, -1589.8077, 13.1627, 1526.6211, -1672.0090, 13.1611},
		{INVALID_DYNAMIC_CP, 1, true, 1526.6211, -1672.0090, 13.1611, 1504.3635, -1729.6943, 13.1603},
		{INVALID_DYNAMIC_CP, 0, false, 1526.6211, -1672.0090, 13.1611, 1504.3635, -1729.6943, 13.1603},
		{INVALID_DYNAMIC_CP, 0, false, 1504.3635, -1729.6943, 13.1603, 1386.4618, -1756.3813, 13.1617},
		{INVALID_DYNAMIC_CP, 0, false, 1386.4618, -1756.3813, 13.1617, 1386.9150, -1862.8605, 13.1614},
		{INVALID_DYNAMIC_CP, 0, false, 1386.9150, -1862.8605, 13.1614, 1337.7184, -1853.0475, 13.1675},
		{INVALID_DYNAMIC_CP, 0, false, 1337.7184, -1853.0475, 13.1675, 1281.9629, -1850.2169, 13.1684},
		{INVALID_DYNAMIC_CP, 0, false, 1281.9629, -1850.2169, 13.1684, 1245.3251, -1828.3600, 13.1830},
		{INVALID_DYNAMIC_CP, 1, false, 1245.3251, -1828.3600, 13.1830, 1245.3251, -1828.3600, 13.1830}
	},
	BusSFInfo[MAX_BUS_SF_POINT][busdriver__] = {
		{INVALID_DYNAMIC_CP, 1, true, -1988.6450, 138.3930, 27.2461, -2009.7799, 190.0612, 27.2468},
		{INVALID_DYNAMIC_CP, 0, false, -1988.6450, 138.3930, 27.2461, -2009.7799, 190.0612, 27.2468},
		{INVALID_DYNAMIC_CP, 0, false, -2009.7799, 190.0612, 27.2468, -2009.7573, 50.9689, 30.7395},
		{INVALID_DYNAMIC_CP, 0, false, -2009.7573, 50.9689, 30.7395, -2048.8228, 33.5824, 34.8789},
		{INVALID_DYNAMIC_CP, 0, false, -2048.8228, 33.5824, 34.8789, -2089.9421, -10.6358, 34.8776},
		{INVALID_DYNAMIC_CP, 0, false, -2089.9421, -10.6358, 34.8776, -2077.2681, -72.8924, 34.8781},
		{INVALID_DYNAMIC_CP, 0, false, -2077.2681, -72.8924, 34.8781, -2029.1040, -77.7470, 35.0282},
		{INVALID_DYNAMIC_CP, 1, true, -2029.1040, -77.7470, 35.0282, -1854.7101, -118.7683, 5.9268},
		{INVALID_DYNAMIC_CP, 0, false, -2029.1040, -77.7470, 35.0282, -1854.7101, -118.7683, 5.9268},
		{INVALID_DYNAMIC_CP, 0, false, -1854.7101, -118.7683, 5.9268, -1854.7101, -118.7683, 5.9268},
		{INVALID_DYNAMIC_CP, 0, false, -1854.7101, -118.7683, 5.9268, -1801.4520, -130.5810, 5.4300},
		{INVALID_DYNAMIC_CP, 0, false, -1801.4520, -130.5810, 5.4300, -1801.6399, -256.0707, 18.8793},
		{INVALID_DYNAMIC_CP, 0, false, -1801.6399, -256.0707, 18.8793, -1815.6925, -400.7422, 15.9548},
		{INVALID_DYNAMIC_CP, 0, false, -1815.6925, -400.7422, 15.9548, -1821.7493, -552.6250, 15.7331},
		{INVALID_DYNAMIC_CP, 0, false, -1821.7493, -552.6250, 15.7331, -1787.4788, -584.2288, 16.0414},
		{INVALID_DYNAMIC_CP, 0, false, -1787.4788, -584.2288, 16.0414, -1762.4775, -692.0914, 25.1931},
		{INVALID_DYNAMIC_CP, 0, false, -1762.4775, -692.0914, 25.1931, -1631.5165, -790.1624, 45.4642},
		{INVALID_DYNAMIC_CP, 0, false, -1631.5165, -790.1624, 45.4642, -1491.4242, -823.0391, 64.2672},
		{INVALID_DYNAMIC_CP, 0, false, -1491.4242, -823.0391, 64.2672, -1224.3580, -777.6037, 63.6083},
		{INVALID_DYNAMIC_CP, 0, false, -1224.3580, -777.6037, 63.6083, -1103.4009, -902.4699, 76.1163},
		{INVALID_DYNAMIC_CP, 0, false, -1103.4009, -902.4699, 76.1163, -1008.6852, -999.5681, 92.6091},
		{INVALID_DYNAMIC_CP, 0, false, -1008.6852, -999.5681, 92.6091, -878.1254, -1110.8273, 98.3178},
		{INVALID_DYNAMIC_CP, 0, false, -878.1254, -1110.8273, 98.3178, -758.8220, -1008.7773, 77.1448},
		{INVALID_DYNAMIC_CP, 0, false, -758.8220, -1008.7773, 77.1448, -646.9244, -1001.3293, 68.1421},
		{INVALID_DYNAMIC_CP, 0, false, -646.9244, -1001.3293, 68.1421, -386.4313, -837.4401, 46.9065},
		{INVALID_DYNAMIC_CP, 0, false, -386.4313, -837.4401, 46.9065, -157.5044, -961.7455, 28.8297},
		{INVALID_DYNAMIC_CP, 0, false, -157.5044, -961.7455, 28.8297, -98.5346, -1125.1733, 0.7931},
		{INVALID_DYNAMIC_CP, 0, false, -98.5346, -1125.1733, 0.7931, -159.5574, -1377.3635, 2.5837},
		{INVALID_DYNAMIC_CP, 0, false, -159.5574, -1377.3635, 2.5837, 54.4676, -1541.8804, 4.8500},
		{INVALID_DYNAMIC_CP, 0, false, 54.4676, -1541.8804, 4.8500, 388.5890, -1719.2759, 7.5602},
		{INVALID_DYNAMIC_CP, 0, false, 388.5890, -1719.2759, 7.5602, 823.0443, -1786.6195, 13.4243},
		{INVALID_DYNAMIC_CP, 0, false, 823.0443, -1786.6195, 13.4243, 1036.6509, -1828.0513, 13.3161},
		{INVALID_DYNAMIC_CP, 0, false, 1036.6509, -1828.0513, 13.3161, 1040.4053, -1869.4093, 13.1565},
		{INVALID_DYNAMIC_CP, 1, false, 1040.4053, -1869.4093, 13.1565, 1040.4053, -1869.4093, 13.1565}
	},
	BusLVInfo[MAX_BUS_LV_POINT][busdriver__] = {
		{INVALID_DYNAMIC_CP, 1, true, 2809.6353, 1302.1759, 10.4570, 2769.1545, 1475.4580, 10.9587},
		{INVALID_DYNAMIC_CP, 0, false, 2809.6353, 1302.1759, 10.4570, 2769.1545, 1475.4580, 10.9587},
		{INVALID_DYNAMIC_CP, 0, false, 2769.1545, 1475.4580, 10.9587, 2639.4485, 1448.1586, 10.3407},
		{INVALID_DYNAMIC_CP, 0, false, 2639.4485, 1448.1586, 10.3407, 2706.0308, 1281.7927, 6.4420},
		{INVALID_DYNAMIC_CP, 0, false, 2706.0308, 1281.7927, 6.4420, 2621.4075, 928.5538, 6.4469},
		{INVALID_DYNAMIC_CP, 0, false, 2621.4075, 928.5538, 6.4469, 2365.2959, 854.7721, 6.4395},
		{INVALID_DYNAMIC_CP, 0, false, 2365.2959, 854.7721, 6.4395, 1992.2372, 855.0261, 6.4418},
		{INVALID_DYNAMIC_CP, 0, false, 1992.2372, 855.0261, 6.4418, 1785.0820, 801.9041, 10.8147},
		{INVALID_DYNAMIC_CP, 0, false, 1785.0820, 801.9041, 10.8147, 1745.0541, 579.1783, 24.0793},
		{INVALID_DYNAMIC_CP, 0, false, 1745.0541, 579.1783, 24.0793, 1654.9573, 312.5692, 29.9793},
		{INVALID_DYNAMIC_CP, 0, false, 1654.9573, 312.5692, 29.9793, 1622.7864, -4.6736, 36.44399},
		{INVALID_DYNAMIC_CP, 0, false, 1622.7864, -4.6736, 36.4439, 1677.5072, -420.4447, 33.4097},
		{INVALID_DYNAMIC_CP, 0, false, 1677.5072, -420.4447, 33.4097, 1692.0481, -706.8760, 47.2514},
		{INVALID_DYNAMIC_CP, 0, false, 1692.0481, -706.8760, 47.2514, 1636.7799, -839.8529, 58.2235},
		{INVALID_DYNAMIC_CP, 0, false, 1636.7799, -839.8529, 58.2235, 1469.9343, -939.3515, 35.9429},
		{INVALID_DYNAMIC_CP, 0, false, 1469.9343, -939.3515, 35.9429, 1356.0643, -977.9618, 30.8393},
		{INVALID_DYNAMIC_CP, 0, false, 1356.0643, -977.9618, 30.8393, 1340.2274, -1148.3407, 23.3682},
		{INVALID_DYNAMIC_CP, 0, false, 1340.2274, -1148.3407, 23.3682, 1315.2666, -1503.5526, 13.0947},
		{INVALID_DYNAMIC_CP, 0, false, 1315.2666, -1503.5526, 13.0947, 1295.0389, -1644.3304, 13.0902},
		{INVALID_DYNAMIC_CP, 0, false, 1295.0389, -1644.3304, 13.0902, 1261.3240, -1709.7252, 13.0890},
		{INVALID_DYNAMIC_CP, 0, false, 1261.3240, -1709.7252, 13.0890, 1173.4429, -1732.9390, 13.2154},
		{INVALID_DYNAMIC_CP, 0, false, 1173.4429, -1732.9390, 13.2154, 1124.2900, -1738.3217, 13.2075},
		{INVALID_DYNAMIC_CP, 0, false, 1124.2900, -1738.3217, 13.2075, 1094.3568, -1738.1898, 13.2466},
		{INVALID_DYNAMIC_CP, 1, false, 1094.3568, -1738.1898, 13.2466, 1094.3568, -1738.1898, 13.2466}
	};

static const 
	BusLSStopTitle[5][24] = {
		{"Мэрия штата"},
		{"Таксопарк"},
		{"Восточный пляж"},
		{"Grove Street"},
		{"Полицейский Департамент"}
	},
	BusSFStopTitle[2][22] = {
		{"Автовокзал Сан-Фиерро"},
		{"Автошкола"}
	},
	BusLVStopTitle[1][24] = {
		{"Автовокзал Лас-Вентурас"}
	};

public BusDriver_OnGameModeInit() {
	new 
		streamer_data[2];

	streamer_data[0] = STREAMER_TYPE_BUS_DRIVER;

	for(new i = 0; i < sizeof(BusLSInfo); i++) {
		BusLSInfo[i][BLI_CheckpointID] = CreateDynamicRaceCP(BusLSInfo[i][BLI_CheckpointType], 
			BusLSInfo[i][BLI_X], BusLSInfo[i][BLI_Y], BusLSInfo[i][BLI_Z], 
			BusLSInfo[i][BLI_NextX], BusLSInfo[i][BLI_NextY], BusLSInfo[i][BLI_NextZ], 
			BUS_RACECP_SIZE, .streamdistance = 9000.0000
		);

		streamer_data[1] = i;

		Streamer_SetArrayData(STREAMER_TYPE_RACE_CP, BusLSInfo[i][BLI_CheckpointID], E_STREAMER_EXTRA_ID, streamer_data, 2);
	}

	for(new i = 0; i < sizeof(BusSFInfo); i++) {
		BusSFInfo[i][BLI_CheckpointID] = CreateDynamicRaceCP(BusSFInfo[i][BLI_CheckpointType], 
			BusSFInfo[i][BLI_X], BusSFInfo[i][BLI_Y], BusSFInfo[i][BLI_Z], 
			BusSFInfo[i][BLI_NextX], BusSFInfo[i][BLI_NextY], BusSFInfo[i][BLI_NextZ], 
			BUS_RACECP_SIZE, .streamdistance = 9000.0000
		);

		streamer_data[1] = i;

		Streamer_SetArrayData(STREAMER_TYPE_RACE_CP, BusSFInfo[i][BLI_CheckpointID], E_STREAMER_EXTRA_ID, streamer_data, 2);
	}

	for(new i = 0; i < sizeof(BusLVInfo); i++) {
		BusLVInfo[i][BLI_CheckpointID] = CreateDynamicRaceCP(BusLVInfo[i][BLI_CheckpointType], 
			BusLVInfo[i][BLI_X], BusLVInfo[i][BLI_Y], BusLVInfo[i][BLI_Z], 
			BusLVInfo[i][BLI_NextX], BusLVInfo[i][BLI_NextY], BusLVInfo[i][BLI_NextZ], 
			BUS_RACECP_SIZE, .streamdistance = 9000.0000
		);

		streamer_data[1] = i;

		Streamer_SetArrayData(STREAMER_TYPE_RACE_CP, BusLVInfo[i][BLI_CheckpointID], E_STREAMER_EXTRA_ID, streamer_data, 2);
	}
}

public BusDriver_OnPlayerConnect(playerid) {
	HideAllBusDriverPointForPlayer(playerid);
	player_bus_driver_timer[playerid] = KillTimer(player_bus_driver_timer[playerid]);
	return 1;
}

public BusDriver_OnPlayerDisconnect(playerid) {
	HideAllBusDriverPointForPlayer(playerid);
	player_bus_driver_timer[playerid] = KillTimer(player_bus_driver_timer[playerid]);
	return 1;
}


public OnPlayerEnterBus(playerid, bus) {
	if(bus == VO_BUS_LS) {
		SetPlayerJob(playerid, JOB_BUS_LS);
		TogglePlayerDynamicRaceCP(playerid, BusLSInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], true);
	} else if(bus == VO_BUS_SF) {
		SetPlayerJob(playerid, JOB_BUS_SF);
		TogglePlayerDynamicRaceCP(playerid, BusSFInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], true);
	} else if(bus == VO_BUS_LV) {
		SetPlayerJob(playerid, JOB_BUS_LV);
		TogglePlayerDynamicRaceCP(playerid, BusLVInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], true);
	}
	SetPVarInt(playerid, "job_time", gettime());
	return Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
}

public OnPlayerExitVehicleBus(playerid) {
	new 
		PlayerJob: local_player_job = GetPlayerJob(playerid);

	if(local_player_job == JOB_BUS_LS) {
		TogglePlayerDynamicRaceCP(playerid, BusLSInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], false);
	} else if(local_player_job == JOB_BUS_SF) {
		TogglePlayerDynamicRaceCP(playerid, BusSFInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], false);
	} else if(local_player_job == JOB_BUS_LV) {
		TogglePlayerDynamicRaceCP(playerid, BusLVInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], false);
	}
	return Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
}

public BusDriver_OP_EnterDynamicRaceCP(playerid, checkpointid) {
	new 
		streamer_data[2];

	Streamer_GetArrayData(STREAMER_TYPE_RACE_CP, checkpointid, E_STREAMER_EXTRA_ID, streamer_data, 2);

	if(streamer_data[0] == STREAMER_TYPE_BUS_DRIVER) {
		new 
			arrayid = streamer_data[1],
			PlayerJob: local_player_job = GetPlayerJob(playerid);

		if(local_player_job == JOB_BUS_LS) {
			TogglePlayerDynamicRaceCP(playerid, BusLSInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], false);

			if(GetPlayerRouteBus(playerid) == MAX_BUS_LS_POINT - 1) { // Конечная остановка
				OnPlayerBusDriverFinish(playerid, JOB_BUS_LS);
				return 1;
			}

			if(BusLSInfo[arrayid][BLI_IsStop] == true) {
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Остановка. Подождите 10 секунд...");
				player_bus_driver_timer[playerid] = SetTimerEx("PlayerBusDriverStop", 10_000, false, !"i", playerid);
				SetPVarInt(playerid, "MinusTime", 10);
				
				format(small_string, 100, "Водитель %s: Остановка %s", PlayerInfo[playerid][pName], BusLSStopTitle[GetPlayerBusStopNumber(playerid)]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				return 1;
			} else {
				AddPlayerRouteBus(playerid);	
				TogglePlayerDynamicRaceCP(playerid, BusLSInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], true);
				Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
				return 1;
			}
		} else if(local_player_job == JOB_BUS_SF) {
			TogglePlayerDynamicRaceCP(playerid, BusSFInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], false);

			if(GetPlayerRouteBus(playerid) == MAX_BUS_SF_POINT - 1) { // Конечная остановка
				OnPlayerBusDriverFinish(playerid, JOB_BUS_SF);
				return 1;
			}

			if(BusSFInfo[arrayid][BLI_IsStop] == true) {
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Остановка. Подождите 10 секунд...");
				player_bus_driver_timer[playerid] = SetTimerEx("PlayerBusDriverStop", 10_000, false, !"i", playerid);
				SetPVarInt(playerid, "MinusTime", 10);
				
				format(small_string, 100, "Водитель %s: Остановка %s", PlayerInfo[playerid][pName], BusSFStopTitle[GetPlayerBusStopNumber(playerid)]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				return 1;
			} else {
				AddPlayerRouteBus(playerid);	
				TogglePlayerDynamicRaceCP(playerid, BusSFInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], true);
				Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
				return 1;
			}
		} else if(local_player_job == JOB_BUS_LV) {
			TogglePlayerDynamicRaceCP(playerid, BusLVInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], false);

			if(GetPlayerRouteBus(playerid) == MAX_BUS_LV_POINT - 1) { // Конечная остановка
				OnPlayerBusDriverFinish(playerid, JOB_BUS_LV);
				return 1;
			}

			if(BusLVInfo[arrayid][BLI_IsStop] == true) {
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Остановка. Подождите 10 секунд...");
				player_bus_driver_timer[playerid] = SetTimerEx("PlayerBusDriverStop", 10_000, false, !"i", playerid);
				SetPVarInt(playerid, "MinusTime", 10);
				
				format(small_string, 100, "Водитель %s: Остановка %s", PlayerInfo[playerid][pName], BusLVStopTitle[GetPlayerBusStopNumber(playerid)]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				return 1;
			} else {
				AddPlayerRouteBus(playerid);	
				TogglePlayerDynamicRaceCP(playerid, BusLVInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], true);
				Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
				return 1;
			}
		}
	}
	return 0;
}

public PlayerBusDriverStop(playerid) {
	new 
		PlayerJob: local_player_job = GetPlayerJob(playerid);
	
	SendClientMessage(playerid, -1, ""COLOR_GREEN"Продолжайте движение по маршруту.");
	AddPlayerBusStop(playerid);
	AddPlayerRouteBus(playerid);

	if(local_player_job == JOB_BUS_LS) {
		TogglePlayerDynamicRaceCP(playerid, BusLSInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], true);
	} else if(local_player_job == JOB_BUS_SF) {
		TogglePlayerDynamicRaceCP(playerid, BusSFInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], true);
	} else if(local_player_job == JOB_BUS_LV) {
		TogglePlayerDynamicRaceCP(playerid, BusLVInfo[GetPlayerRouteBus(playerid)][BLI_CheckpointID], true);
	}

	Streamer_Update(playerid, STREAMER_TYPE_RACE_CP);
	return 1;
}

public BusDriver_OnPlayerLeaveJob(playerid) {
	GameTextForPlayer(playerid, "~r~-2 BUSSKILL", 3000, 5);
	PlayerInfo[playerid][pBusSkill] -= 2;
	SetPlayerInt(playerid, "BusSkill", PlayerInfo[playerid][pBusSkill]);
	
	ResetPlayerRouteBus(playerid);
	ResetPlayerBusStop(playerid);
	HideAllBusDriverPointForPlayer(playerid);
	player_bus_driver_timer[playerid] = KillTimer(player_bus_driver_timer[playerid]);
	DeletePVar(playerid, "job_time");
	return 1;
}

stock GetPlayerRouteBus(playerid) {
	return player_route_bus_driver{playerid};
}

stock AddPlayerRouteBus(playerid) {
	return player_route_bus_driver{playerid} ++;
}

stock ResetPlayerRouteBus(playerid) {
	return player_route_bus_driver{playerid} = 0;
}

stock AddPlayerBusStop(playerid) {
	return player_bus_ls_stop{playerid} ++;
}

stock GetPlayerBusStopNumber(playerid) {
	return player_bus_ls_stop{playerid};
}

stock ResetPlayerBusStop(playerid) {
	return player_bus_ls_stop{playerid} = 0;
}

stock HideAllBusDriverPointForPlayer(playerid) {
	for(new i = 0; i < sizeof(BusLSInfo); i++) {
		if(IsValidDynamicRaceCP(BusLSInfo[i][BLI_CheckpointID])) {
			TogglePlayerDynamicRaceCP(playerid, BusLSInfo[i][BLI_CheckpointID], false);
		}
	}

	for(new i = 0; i < sizeof(BusSFInfo); i++) {
		if(IsValidDynamicRaceCP(BusSFInfo[i][BLI_CheckpointID])) {
			TogglePlayerDynamicRaceCP(playerid, BusSFInfo[i][BLI_CheckpointID], false);
		}
	}

	for(new i = 0; i < sizeof(BusLVInfo); i++) {
		if(IsValidDynamicRaceCP(BusLVInfo[i][BLI_CheckpointID])) {
			TogglePlayerDynamicRaceCP(playerid, BusLVInfo[i][BLI_CheckpointID], false);
		}
	}
	return 1;
}

stock OnPlayerBusDriverFinish(playerid, PlayerJob:route) {
	SetVehicleToRespawn(GetPlayerVehicleID(playerid));
	PlayerInfo[playerid][pBusSkill] = PlayerInfo[playerid][pBusSkill] + 2;
	SetPlayerInt(playerid, "BusSkill", PlayerInfo[playerid][pBusSkill]);
    new 
    	xmc,
    	BusSkill = PlayerInfo[playerid][pBusSkill];

    if((0 <= BusSkill <= 24)) {
		xmc = 50;
		format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/25", BusSkill);
	} else if((25 <= BusSkill <= 49)) {
    	xmc = 75;
		format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/50", BusSkill);
	} else if((50 <= BusSkill <= 99)) {
    	xmc = 100;
		format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/100", BusSkill);
	} else if((100 <= BusSkill <= 199)) {
    	xmc = 150;
		format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/200", BusSkill);
	} else if((200 <= BusSkill <= 499)) {
		xmc = 250;
		format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/500", BusSkill);
	} else {
		xmc = 350;
		format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} Максимум");
	}
    SendClientMessage(playerid, -1, small_string);
	format(small_string, sizeof(small_string), ""COLOR_ORANGE"Круг завершен. Зарплата: {FFFFFF}+%d EXP", xmc);
    SendClientMessage(playerid, -1, small_string);
    AddPlayerEXP(playerid, xmc);


    new bitid;

	if(route == JOB_BUS_LS) {
		bitid = 1;
	} else if(route == JOB_BUS_SF) {
		bitid = 2;
	} else if(route == JOB_BUS_LV) {
		bitid = 3;
	}

	mysql_format(database, 
		small_string, sizeof(small_string), 
		"INSERT INTO `bus_log`(`Name`, `Route`, `BusSkill`, `EXP`, `RouteTime`) VALUES ('%e', %i, %i, %i, %i)", 
			PlayerInfo[playerid][pName], 
			bitid, 
			BusSkill, 
			xmc, 
			gettime() - GetPVarInt(playerid, "job_time")
	);
	mysql_pquery(database, small_string);

    SetPlayerJob(playerid, JOB_NONE);
    ResetPlayerRouteBus(playerid);
    ResetPlayerBusStop(playerid);
    DeletePVar(playerid, "job_time");
    return 1;
}