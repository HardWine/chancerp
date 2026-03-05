#if defined xmas_system_included
	#endinput
#endif

#define xmas_system_included

new tree[46];
new xmas_tree;
new xmas_counter = 1137;
new Text3D:xmas_text;
new sphere;

stock xmas_obj() {
	/*
	tree[0] = CreateDynamicPickup(19059, 2, -741.6078,513.2751,1391.7451, 0, 0, -1, 300.0);
	tree[1] = CreateDynamicPickup(19059, 2, 1506.8998,-1747.8455,13.5469, 0, 0, -1, 300.0);
	tree[2] = CreateDynamicPickup(19059, 2, 1421.9594,-1607.1802,13.5469, 0, 0, -1, 300.0);
	tree[3] = CreateDynamicPickup(19059, 2, 1696.4995,-1670.6532,13.5469, 0, 0, -1, 300.0);
	tree[4] = CreateDynamicPickup(19059, 2, 1711.2214,-1797.5975,13.5469, 0, 0, -1, 300.0);
	tree[5] = CreateDynamicPickup(19060, 2, 1829.1169,-1880.0026,13.5469, 0, 0, -1, 300.0);
	tree[6] = CreateDynamicPickup(19060, 2, 1691.4999,-1945.3761,13.5469, 0, 0, -1, 300.0);
	tree[7] = CreateDynamicPickup(19060, 2, 1973.1761,-2158.2813,13.5469, 0, 0, -1, 300.0);
	tree[8] = CreateDynamicPickup(19060, 2, 2226.6482,-1847.7938,13.5469, 0, 0, -1, 300.0);
	tree[9] = CreateDynamicPickup(19060, 2, 2393.2327,-1669.2188,13.5469, 0, 0, -1, 300.0);
	tree[10] = CreateDynamicPickup(19060, 2, 2698.2231,-1617.2687,14.0102, 0, 0, -1, 300.0);
	tree[11] = CreateDynamicPickup(19061, 2, 2117.2522,-1162.0215,24.4420, 0, 0, -1, 300.0);
	tree[12] = CreateDynamicPickup(19061, 2, 819.0418,-1794.7556,13.8129, 0, 0, -1, 300.0);
	tree[13] = CreateDynamicPickup(19061, 2, 662.8833,-1423.1073,14.8700, 0, 0, -1, 300.0);
	tree[14] = CreateDynamicPickup(19061, 2, 864.7258,-979.0598,37.1875, 0, 0, -1, 300.0);
	tree[15] = CreateDynamicPickup(19061, 2, 1680.2303,-747.5192,51.8379, 0, 0, -1, 300.0);
	tree[16] = CreateDynamicPickup(19061, 2, 1972.7747,-1222.5430,20.0234, 0, 0, -1, 300.0);
	tree[17] = CreateDynamicPickup(19061, 2, 2210.7830,-1341.5504,23.9844, 0, 0, -1, 300.0);
	tree[18] = CreateDynamicPickup(19062, 2, 2316.2947,-1462.7675,21.1700, 0, 0, -1, 300.0);
	tree[19] = CreateDynamicPickup(19062, 2, 2489.6201,-1692.0096,14.7656, 0, 0, -1, 300.0);
	tree[20] = CreateDynamicPickup(19062, 2, 2103.6887,-1824.8953,13.5547, 0, 0, -1, 300.0);
	tree[21] = CreateDynamicPickup(19062, 2, 2014.8667,-1763.2500,17.3436, 0, 0, -1, 300.0);
	tree[22] = CreateDynamicPickup(19062, 2, 1921.8733,-1766.9553,17.9766, 0, 0, -1, 300.0);
	tree[23] = CreateDynamicPickup(19062, 2, 1794.2839,-1640.8302,14.8875, 0, 0, -1, 300.0);
	tree[24] = CreateDynamicPickup(19063, 2, 1692.2534,-1488.6554,13.5469, 0, 0, -1, 300.0);
	tree[25] = CreateDynamicPickup(19063, 2, 1641.1274,-1675.0991,19.1180, 0, 0, -1, 300.0);
	tree[26] = CreateDynamicPickup(19063, 2, 1144.0741,-1769.5657,16.5992, 0, 0, -1, 300.0);
	tree[27] = CreateDynamicPickup(19063, 2, 1485.0206,-1828.5912,13.5469, 0, 0, -1, 300.0);
	tree[28] = CreateDynamicPickup(19063, 2, 1673.1531,-2286.5281,-1.2251, 0, 0, -1, 300.0);
	tree[29] = CreateDynamicPickup(19063, 2, 1239.3474,-2040.3677,59.9034, 0, 0, -1, 300.0);
	tree[30] = CreateDynamicPickup(19059, 2, 1020.9404,-2186.3389,39.1406, 0, 0, -1, 300.0);
	tree[31] = CreateDynamicPickup(19059, 2, 827.2493,-2061.4211,12.8672, 0, 0, -1, 300.0);
	tree[32] = CreateDynamicPickup(19059, 2, 447.2057,-1872.6207,4.3723, 0, 0, -1, 300.0);
	tree[33] = CreateDynamicPickup(19059, 2, 289.1780,-1873.6211,6.4023, 0, 0, -1, 300.0);
	tree[34] = CreateDynamicPickup(19059, 2, 150.0331,-1946.5995,3.7734, 0, 0, -1, 300.0);
	tree[35] = CreateDynamicPickup(19060, 2, 1324.7046,-1121.6877,23.8420, 0, 0, -1, 300.0);
	tree[36] = CreateDynamicPickup(19060, 2, 1623.4624,-1042.8887,27.2013, 0, 0, -1, 300.0);
	tree[37] = CreateDynamicPickup(19060, 2, 1727.2885,-959.9899,41.6159, 0, 0, -1, 300.0);
	tree[38] = CreateDynamicPickup(19060, 2, 2237.3369,-1184.9443,33.5313, 0, 0, -1, 300.0);
	tree[39] = CreateDynamicPickup(19061, 2, 2325.3416,-1259.5745,22.5070, 0, 0, -1, 300.0);
	tree[40] = CreateDynamicPickup(19061, 2, 2472.4290,-1461.0649,24.0069, 0, 0, -1, 300.0);
	tree[41] = CreateDynamicPickup(19061, 2, 2954.8123,-1877.2599,5.3844, 0, 0, -1, 300.0);
	tree[42] = CreateDynamicPickup(19062, 2, 2073.6152,-2704.1519,13.5469, 0, 0, -1, 300.0);
	tree[43] = CreateDynamicPickup(19062, 2, 861.1125,-1510.6893,13.5498, 0, 0, -1, 300.0);
	tree[44] = CreateDynamicPickup(19062, 2, 734.9620,-1366.0032,25.6922, 0, 0, -1, 300.0);
	tree[45] = CreateDynamicPickup(19063, 2, 492.3423,-1508.4159,20.5731, 0, 0, -1, 300.0);
	*/
	sphere = CreateDynamicSphere(1480.15,-1707.77,13.5, 25);


	xmas_text = CreateDynamic3DTextLabel(""COLOR_GREEN"Новогодняя акция завершена\n"COLOR_WHITE"Спасибо за участие!", -1, 1481.096679, -1712.184204, 13.438006+1.5, 25, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 300.0);


	CreateDynamicObject(19129, 1480.15,-1707.77,13.1, 0, 0, 0, 0, 0, -1, 150, 150);

	xmas_tree = CreateDynamicObject(19076, 1481.096679, -1712.184204, 13.438006-0.5, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);



	//upd_xmas();
}
/*
stock got_tree(playerid,pickupid) {

	new xmas = GetPVarInt(playerid, "tree");
	xmas = xmas+1;
	SetPVarInt(playerid, "tree", xmas);

	format(small_string, sizeof(small_string), "%s поднял(а) шарик (собрано всего: %d)", PlayerInfo[playerid][pName], xmas);
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);	

	SPD(playerid, dKickMessage,  DIALOG_STYLE_MSGBOX, "Вы нашли новогдний предмет!",
	""COLOR_GREEN"Собирайте новогодние предметы и наряжайте елку у мэрии\n\n\
	{FFFFFF}Обратите внимание что если покинуть игру все собранные шарики разобьются!","Ок", "");

	AddPlayerEXP(playerid, 50);

	if(GetPVarInt(playerid, "xmasia") == 10) {
	SetPVarInt(playerid, "BallCollected10", pickupid);
	return SetPVarInt(playerid, "xmasia", 0);
	}
	if(GetPVarInt(playerid, "xmasia") == 9) {
	SetPVarInt(playerid, "BallCollected9", pickupid);
	return SetPVarInt(playerid, "xmasia", 10);
	}
	if(GetPVarInt(playerid, "xmasia") == 8) {
	SetPVarInt(playerid, "BallCollected8", pickupid);
	return SetPVarInt(playerid, "xmasia", 9);
	}
	if(GetPVarInt(playerid, "xmasia") == 7) {
	SetPVarInt(playerid, "BallCollected7", pickupid);
	return SetPVarInt(playerid, "xmasia", 8);
	}
	if(GetPVarInt(playerid, "xmasia") == 6) {
	SetPVarInt(playerid, "BallCollected6", pickupid);
	return SetPVarInt(playerid, "xmasia", 7);
	}
	if(GetPVarInt(playerid, "xmasia") == 5) {
	SetPVarInt(playerid, "BallCollected5", pickupid);
	return SetPVarInt(playerid, "xmasia", 6);
	}
	if(GetPVarInt(playerid, "xmasia") == 4) {
	SetPVarInt(playerid, "BallCollected4", pickupid);
	return SetPVarInt(playerid, "xmasia", 5);
	}
	if(GetPVarInt(playerid, "xmasia") == 3) {
	SetPVarInt(playerid, "BallCollected3", pickupid);
	return SetPVarInt(playerid, "xmasia", 4);
	}
	if(GetPVarInt(playerid, "xmasia") == 2) {
	SetPVarInt(playerid, "BallCollected2", pickupid);
	return SetPVarInt(playerid, "xmasia", 3);
	}
	if(GetPVarInt(playerid, "xmasia") == 1) {
	SetPVarInt(playerid, "BallCollected1", pickupid);
	return SetPVarInt(playerid, "xmasia", 2);
	}
	if(GetPVarInt(playerid, "xmasia") == 0) {
	SetPVarInt(playerid, "BallCollected", pickupid);
	return SetPVarInt(playerid, "xmasia", 1);
	}	
	return 1;
}
*/
CMD:tree(playerid) {

	if(GetPVarInt(playerid,"AntiFloodTree") > gettime()){ return false; }
	SetPVarInt(playerid,"AntiFloodTree",gettime() + 5);	
	
	if(!IsPlayerInRangeOfPoint(playerid, 5, 1481.096679, -1712.184204, 13.438006)) {
		return SendClientMessage(playerid, -1, "Необходимо быть у ёлки напротив мэрии!");
	}

	new xmas = GetPVarInt(playerid, "tree");
	if(xmas <= 0) return 1;
	printf("[2020] put %d", xmas);
	xmas_counter = xmas_counter+xmas;
	upd_xmas();

	SetPVarInt(playerid, "tree", 0);

	PlayerPlaySound(playerid, 1058, 0, 0, 0);

	format(small_string, sizeof(small_string), "%s выложил(а) %d шарик(ов)", PlayerInfo[playerid][pName], xmas);
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
	return 1;	
}

stock upd_xmas() {

	format(big_string, sizeof(big_string), ""COLOR_GREEN"Новогодняя акция завершена\n"COLOR_WHITE"Спасибо за участие!\n\nШариков на ёлке: %d", xmas_counter);
	UpdateDynamic3DTextLabelText(xmas_text, -1, big_string);
	
}
