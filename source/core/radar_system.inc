#if defined radar_system_included
	#endinput
#endif

#define radar_system_included

#include <YSI_Coding\y_hooks>

#define RADAR_SIDES						35				
#define RADAR_RADIUS					50
#define MAX_RADAR						70
#define ALERT_RADAR_DIST				300

new RadarArea[MAX_RADAR];
new RadarIcon[MAX_PLAYERS][MAX_RADAR] = {INVALID_STREAMER_ID, ...};

enum RadarCoords__ {
	Float:rX,
	Float:rY,
	Float:rZ,
	rLimit,
};

new
    Radar[MAX_RADAR][RadarCoords__] = {
		{2350.8970,2143.4517,10.8982,60},
		{2062.8462,1713.9580,10.6797,60},
		{2427.2581,1193.2682,11.0981,60},
		{1727.9363,2273.2898,11.0849,60},
		{1716.2911,1713.3650,11.0733,60},
		{1012.7124,1373.5575,10.8601,60},
		{1021.5964,-1144.9004,23.6563,60},
		{1201.1367,-1324.0936,13.3984,60},
		{1350.1019,-1280.2524,13.3828,60},
		{2282.5332,-2079.5164,13.3675,60},
		{1037.5775,-1712.2899,13.3906,60},
		{-115.6690,1197.7577,19.5938,60},
		{1480.3025,-1732.4054,13.3828,60},
		{1821.4618,-1612.3136,13.3820,60},
		{1961.8231,-1932.1466,13.3828,60},
		{1520.5634,-2286.5391,13.3828,60},
		{2201.0344,-1733.3529,13.3634,60},
		{2431.0393,-1444.4786,23.8352,60},
		{2215.7302,-1126.8253,25.6328,60},
		{2164.1399,-1009.8840,62.7973,60},
		{1364.2615,-1036.4612,26.1926,60},
		{797.6650,-1143.5155,24.0446,60},
		{371.7875,-1709.7809,7.2904,60},
		{-23.7166,-1517.5397,1.8203,60},
		{369.9255,-1786.5106,9.1084,60},
		{796.8324,-887.5429,57.4501,60},
		{1160.1095,-948.2413,43.0588,60},
		{1372.0502,-939.8141,34.1875,60},
		{917.5084,-1400.9762,13.2696,60},
		{-2209.1177,1066.1566,58.4425,60},
		{-2261.0596,808.3485,49.2969,60},
		{-2004.1578,608.2605,35.0156,60},
		{-2006.4453,154.7697,28.1381,60},
		{-2007.2972,-69.6369,35.1654,60},
		{-2371.8369,-70.3903,35.1719,60},
		{-2809.0044,157.7929,7.0313,60},
		{-2605.7581,565.7458,14.4609,60},
		{-2606.5903,909.1035,64.8281,60},
		{-1715.4479,845.4559,24.7344,60},
		{-2505.1777,2420.8176,16.5982,60},
		{1710.5686,-625.5118,40.3217,90},
		{1731.9253,503.4306,29.8536,90},
		{1567.4044,843.4695,12.1219,90},
		{2147.4436,843.3051,12.1219,90},
		{2717.4607,1313.5903,12.1219,90},
		{819.8365,2632.7427,13.0359,90},
		{1813.8308,2496.2402,9.9443,90},
		{1797.2208,1711.6361,7.8187,90},
		{846.3568,698.9073,13.0313,90},
		{316.7456,765.1559,9.1835,90},
		{-1264.6248,968.6276,45.2363,90},
		{-1566.7076,650.2264,43.7727,90},
		{-1419.7283,1740.7405,16.9931,90},
		{-2130.9785,2646.4360,57.8715,90},
		{-2681.6152,1689.9346,67.7047,90},
		{-2681.8179,1275.2809,55.1984,90},
		{-1899.8909,-575.3098,38.2422,90},
		{-2426.5808,-333.8674,35.6526,90},
		{-2865.6067,-830.9280,7.0502,90},
		{-2592.5012,-2104.3904,37.4289,90},
		{-1630.2800,-2736.8818,48.3028,90},
		{-415.4980,-2798.4348,60.9455,90},
		{-282.6947,-1678.6443,15.1060,90},
		{349.9501,-1146.1663,30.6621,90},
		{-92.1266,-1029.7854,24.1085,90},
		{-249.0211,-265.7036,1.3039,90},
		{-417.6194,-630.9830,11.2107,90},
		{-1072.1406,-930.4507,81.1883,90},
		{-1818.2899,-580.1108,16.3434,90},
		{-847.4471,1490.7898,18.1029,90}
};

hook OnPlayerConnect(playerid) {
	for(new i = 0; i < sizeof(RadarIcon[]); i++) {
		RadarIcon[playerid][i] = INVALID_STREAMER_ID;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason 

	for(new i = 0; i < sizeof(RadarIcon[]); i++) {
		RadarIcon[playerid][i] = INVALID_STREAMER_ID;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}
stock create_radar() {
	for(new i = 0; i < MAX_RADAR; i++) {
		RadarArea[i] = CreateDynamicCylinder(Radar[i][rX], Radar[i][rY], 0, 5000, RADAR_RADIUS, 0, 0, -1);
	}
}

stock turnon_detector(playerid) {
	if(GetPVarInt(playerid, "radar") == 0) {

		SetPVarInt(playerid, "radar", 1);
		for(new i = 0; i < MAX_RADAR; i++) {
			if(RadarIcon[playerid][i] != INVALID_STREAMER_ID) {
				DestroyDynamicMapIcon(RadarIcon[playerid][i]);
			}
			RadarIcon[playerid][i] = CreateDynamicMapIcon(Radar[i][rX], Radar[i][rY], Radar[i][rZ], (Radar[i][rLimit] == 60) ? (19) : (53), -1, 0, 0, playerid, RADAR_RADIUS+ALERT_RADAR_DIST);
		}
		Streamer_Update(playerid, STREAMER_TYPE_MAP_ICON);
	}
}


stock stop_detector(playerid) {
	if(GetPVarInt(playerid, "radar")) {

		DeletePVar(playerid, "radar");
		for(new i = 0; i < MAX_RADAR; i++) {
			if(RadarIcon[playerid][i] != INVALID_STREAMER_ID) {
				DestroyDynamicMapIcon(RadarIcon[playerid][i]);
				RadarIcon[playerid][i] = INVALID_STREAMER_ID;
			}
		}
		Streamer_Update(playerid, STREAMER_TYPE_MAP_ICON);
	}
}

stock get_radar(playerid) {
	if(IsPlayerInAnyVehicle(playerid)) {
		new vehicleid = GetPlayerVehicleID(playerid);
		foreach(new i: Player) {
			if(vehicleid == caridhouse[i]) {
				if(PlayerInfo[i][pSelectedSlot] == 1 && PlayerInfo[i][pRadarDetect1] == 1) return 1;
				if(PlayerInfo[i][pSelectedSlot] == 2 && PlayerInfo[i][pRadarDetect2] == 1) return 1;
			}
		}
	}
	return 0;
}

stock radar_shot(playerid, limit) {
	if(GetPlayerVehicleSeat(playerid) != 0) return 1;
	new v = GetPlayerVehicleID(playerid);
	if(!IsARadarDetectable(GetVehicleModel(v))) return 1;

	new 
		vehicle_owner;

	for(new i = 0; i < sizeof(VehicleInfo); i++) {
		if(VehicleInfo[i][VI_VehicleID] == v) {
			vehicle_owner = VehicleInfo[i][VI_Owner];
		}
	}

	if(vehicle_owner == VO_FRACTION_LSPD || vehicle_owner == VO_FRACTION_GOVERMENT || vehicle_owner == VO_FRACTION_FBI || vehicle_owner == VO_FRACTION_ARMY) return 1;

	new speed_vehicle = floatround(GetVehicleSpeed(v));
	new debt;

	if(speed_vehicle > limit) {
		// SetPlayerScreenColour(playerid, 0xFFFFFFFF);
		// FadePlayerScreenColour(playerid, 0xFFFFFF00, 1000, 15);

		PlayerPlaySound(playerid, 1132, 0, 0, 0);

		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Лимит скорости был превышен!");

		if(PlayerInfo[playerid][pHours] < 8) {
			return SendClientMessage(playerid, -1, "Первые 8 часов в штате у вас иммунитет и вы не получите штрафов");
		}

		if(PlayerInfo[playerid][pSelectedSlot] == 1 && PlayerInfo[playerid][pRadarDetect1] > 1) return 1;
		if(PlayerInfo[playerid][pSelectedSlot] == 2 && PlayerInfo[playerid][pRadarDetect2] > 1) return 1;

		/*
		if(limit == 60) {
			if(speed_vehicle >= 60 && speed_vehicle <=64) {
				debt = speed_vehicle*3;
			}
			if(speed_vehicle >= 65 && speed_vehicle <=74) {
				debt = speed_vehicle*6;
			}
			if(speed_vehicle >= 75) {
				debt = speed_vehicle*10;
			}						
		}
		if(limit == 90) {
			if(speed_vehicle >= 90  && speed_vehicle <= 99) {
				debt = speed_vehicle*12;
			}
			if(speed_vehicle >= 100 && speed_vehicle <= 119) {
				debt = speed_vehicle*14;
			}	
			if(speed_vehicle >= 120) {
				debt = speed_vehicle*16;
			}										
		}		
		*/

		if(limit == 80) {

			if(IsPlayerPremiumAccount(playerid) == true) {
				return SendClientMessage(playerid, -1, "(Premium) "COLOR_ORANGE"Иммунитет защитил вас от получения штрафа при движении по городу");
			}

			if(speed_vehicle >= 80 && speed_vehicle <=84) {
				debt = speed_vehicle*3;
			}
			if(speed_vehicle >= 85 && speed_vehicle <=94) {
				debt = speed_vehicle*6;
			}
			if(speed_vehicle >= 95) {
				debt = speed_vehicle*10;
			}						
		}
		if(limit == 120) {
			if(speed_vehicle >= 120  && speed_vehicle <= 129) {
				debt = speed_vehicle*12;
			}
			if(speed_vehicle >= 130 && speed_vehicle <= 149) {
				debt = speed_vehicle*14;
			}	
			if(speed_vehicle >= 150) {
				debt = speed_vehicle*16;
			}										
		}			

		debt = debt/2;
		

		format(small_string, sizeof(small_string), ""COLOR_ORANGE"Допустимая скорость на данном участке: "COLOR_WHITE"%dкм/ч."COLOR_ORANGE" Ваша скорость: "COLOR_WHITE"%dкм/ч", limit, speed_vehicle);
		SendClientMessage(playerid, -1, small_string);
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Некоторые финансовые операции будут недоступны, если не оплатить штрафы вовремя!");

		format(small_string, sizeof(small_string), "~r~Debt ~w~+%d EXP", debt);
		GameTextForPlayer(playerid, small_string, 2500, 3);

		PlayerInfo[playerid][pDebt] = PlayerInfo[playerid][pDebt]+debt;
		SetPlayerInt(playerid, "Debt", PlayerInfo[playerid][pDebt]);
	}
	return 1;
}
stock IsARadarDetectable(carid)
{
    if(carid==523||carid==596||carid==597||carid==601||carid==599||carid==427||carid==490||carid==588||carid==423||
    carid==400||carid==401||carid==402||carid==403||carid==404||carid==405||carid==406||carid==407||carid==408||
    carid==409||carid==410||carid==411||carid==412||carid==413||carid==414||carid==415||carid==416||carid==417||
    carid==418||carid==419||carid==420||carid==421||carid==422||carid==423||carid==424||carid==426||carid==427||
    carid==428||carid==429||carid==431||carid==432||carid==433||carid==434||carid==436||carid==437||carid==438||
    carid==439||carid==440||carid==441||carid==442||carid==443||carid==444||carid==445||carid==451||carid==455||
    carid==456||carid==457||carid==458||carid==459||carid==466||carid==467||carid==470||carid==474||carid==475||
    carid==477||carid==478||carid==479||carid==480||carid==482||carid==483||carid==485||carid==486||carid==489||
    carid==490||carid==491||carid==492||carid==494||carid==495||carid==496||carid==498||carid==499||carid==500||
    carid==502||carid==503||carid==504||carid==505||carid==506||carid==507||carid==508||carid==514||carid==515||
    carid==516||carid==517||carid==518||carid==524||carid==525||carid==526||carid==527||carid==528||carid==529||
    carid==530||carid==531||carid==532||carid==533||carid==534||carid==535||carid==536||carid==537||carid==538||
    carid==540||carid==541||carid==542||carid==543||carid==544||carid==545||carid==546||carid==547||carid==549||
    carid==550||carid==551||carid==552||carid==554||carid==555||carid==556||carid==557||carid==558||carid==559||
    carid==560||carid==561||carid==560||carid==562||carid==564||carid==565||carid==566||carid==567||carid==568||
    carid==570||carid==572||carid==573||carid==574||carid==575||carid==576||carid==578||carid==579||carid==580||
    carid==582||carid==583||carid==585||carid==587||carid==588||carid==589||carid==594||carid==596||carid==597||
    carid==598||carid==599||carid==600||carid==601||carid==602||carid==603||carid==604||carid==605||carid==609||
    carid==448||carid==463||carid==468||carid==471||carid==521||carid==522||carid==581||carid==586)
    {
        return 1;
    }
    return 0;
} 