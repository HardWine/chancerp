#if defined _hidden_system_included
	#endinput
#endif
#define _hidden_system_included

new hidden[50];

hook OnGameModeInit() {

hidden[0] = CreateDynamicPickup(954, 1, 1725.5928,-1540.1543,13.4943);
hidden[1] = CreateDynamicPickup(954, 1, 1847.1429,-1591.1763,28.4125);
hidden[2] = CreateDynamicPickup(954, 1, 1985.4734,-1780.5450,13.5477);
hidden[3] = CreateDynamicPickup(954, 1, 2244.1711,-2157.0100,13.5469);
hidden[4] = CreateDynamicPickup(954, 1, 2371.5930,-2114.9087,27.1797);
hidden[5] = CreateDynamicPickup(954, 1, 2682.1174,-2326.5420,3.0000);
hidden[6] = CreateDynamicPickup(954, 1, 2262.8630,-2538.4556,8.3810);
hidden[7] = CreateDynamicPickup(954, 1, 2765.4109,-2033.0110,13.5547);
hidden[8] = CreateDynamicPickup(954, 1, 2872.0647,-1589.9948,22.4450);
hidden[9] = CreateDynamicPickup(954, 1, 2805.0591,-1241.2314,45.6807);
hidden[10] = CreateDynamicPickup(954, 1, 2450.4729,-956.3770,80.0605);
hidden[11] = CreateDynamicPickup(954, 1, 2048.7363,-1035.0214,26.1530);
hidden[12] = CreateDynamicPickup(954, 1, 2017.9875,-1289.3706,26.2344);
hidden[13] = CreateDynamicPickup(954, 1, 2328.9031,-1244.9125,22.5000);
hidden[14] = CreateDynamicPickup(954, 1, 2582.3013,-1466.0835,24.0000);
hidden[15] = CreateDynamicPickup(954, 1, 2788.2300,-1417.7975,16.2500);
hidden[16] = CreateDynamicPickup(954, 1, 2441.1343,-1690.9528,13.8047);
hidden[17] = CreateDynamicPickup(954, 1, 2062.2786,-1967.5698,13.5469);
hidden[18] = CreateDynamicPickup(954, 1, 1862.6484,-1861.9427,13.5821);
hidden[19] = CreateDynamicPickup(954, 1, 1489.0806,-1720.2183,8.2363);
hidden[20] = CreateDynamicPickup(954, 1, 1480.9691,-1739.5433,13.5469);
hidden[21] = CreateDynamicPickup(954, 1, 1654.0009,-1655.6392,22.5156);
hidden[22] = CreateDynamicPickup(954, 1, 1521.1851,-1825.0923,13.5469);
hidden[23] = CreateDynamicPickup(954, 1, 1117.7574,-2037.0166,78.7500);
hidden[24] = CreateDynamicPickup(954, 1, 1000.3138,-1857.9939,12.8146);
hidden[25] = CreateDynamicPickup(954, 1, 674.0850,-1864.5764,5.4537);
hidden[26] = CreateDynamicPickup(954, 1, 245.1015,-1870.6257,3.3176);
hidden[27] = CreateDynamicPickup(954, 1, 310.6047,-1514.1572,24.9219);
hidden[28] = CreateDynamicPickup(954, 1, 726.1412,-1276.2968,13.6484);
hidden[29] = CreateDynamicPickup(954, 1, 811.1632,-1098.2327,25.9063);
hidden[30] = CreateDynamicPickup(954, 1, 1428.3469,-1081.6340,17.1184);
hidden[31] = CreateDynamicPickup(954, 1, 1616.2197,-992.2899,23.6356);
hidden[32] = CreateDynamicPickup(954, 1, 1954.4904,-1363.4832,18.5781);
hidden[33] = CreateDynamicPickup(954, 1, 1671.0460,-1903.1545,21.8828);
hidden[34] = CreateDynamicPickup(954, 1, 1691.3046,-1963.0009,7.8113);
hidden[35] = CreateDynamicPickup(954, 1, 1450.9689,-2287.0232,13.5469);
hidden[36] = CreateDynamicPickup(954, 1, 1799.1951,-2229.9268,13.1178);
hidden[37] = CreateDynamicPickup(954, 1, 1622.9513,-1780.0671,13.5394);
hidden[38] = CreateDynamicPickup(954, 1, 1689.9803,-2010.5363,14.1222);
hidden[39] = CreateDynamicPickup(954, 1, 1530.2960,-1658.0321,6.2188);
hidden[40] = CreateDynamicPickup(954, 1, 1606.4607,-1639.9484,13.7188);
hidden[41] = CreateDynamicPickup(954, 1, 1702.9731,-1471.1570,13.7188);
hidden[42] = CreateDynamicPickup(954, 1, 1777.3680,-1385.7478,15.5907);
hidden[43] = CreateDynamicPickup(954, 1, 2216.6833,-1179.7604,29.7971);
hidden[44] = CreateDynamicPickup(954, 1, 2700.3281,-1107.4226,69.5781);
hidden[45] = CreateDynamicPickup(954, 1, 2481.3230,-1331.9127,28.2493);
hidden[46] = CreateDynamicPickup(954, 1, 2890.4358,-1877.6783,12.0859);
hidden[47] = CreateDynamicPickup(954, 1, 2794.8945,-2409.3752,13.6319);
hidden[48] = CreateDynamicPickup(954, 1, 1175.5475,-1879.5305,13.5843);
hidden[49] = CreateDynamicPickup(954, 1, 723.1207,-1494.8510,1.9343);

}

stock Hidden_OP_PickUpDynamicPickup(playerid, pickupid) {
	if(pickupid == hidden[0]) {
		if(GetPVarInt(playerid, "h0") == 1) return 1;
		SetPVarInt(playerid, "h0", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[1]) {
		if(GetPVarInt(playerid, "h1") == 1) return 1;
		SetPVarInt(playerid, "h1", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[2]) {
		if(GetPVarInt(playerid, "h2") == 1) return 1;
		SetPVarInt(playerid, "h2", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[3]) {
		if(GetPVarInt(playerid, "h3") == 1) return 1;
		SetPVarInt(playerid, "h3", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[4]) {
		if(GetPVarInt(playerid, "h4") == 1) return 1;
		SetPVarInt(playerid, "h4", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[5]) {
		if(GetPVarInt(playerid, "h5") == 1) return 1;
		SetPVarInt(playerid, "h5", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[6]) {
		if(GetPVarInt(playerid, "h6") == 1) return 1;
		SetPVarInt(playerid, "h6", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[7]) {
		if(GetPVarInt(playerid, "h7") == 1) return 1;
		SetPVarInt(playerid, "h7", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[8]) {
		if(GetPVarInt(playerid, "h8") == 1) return 1;
		SetPVarInt(playerid, "h8", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[9]) {
		if(GetPVarInt(playerid, "h9") == 1) return 1;
		SetPVarInt(playerid, "h9", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[10]) {
		if(GetPVarInt(playerid, "h10") == 1) return 1;
		SetPVarInt(playerid, "h10", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[11]) {
		if(GetPVarInt(playerid, "h11") == 1) return 1;
		SetPVarInt(playerid, "h11", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[12]) {
		if(GetPVarInt(playerid, "h12") == 1) return 1;
		SetPVarInt(playerid, "h12", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[13]) {
		if(GetPVarInt(playerid, "h13") == 1) return 1;
		SetPVarInt(playerid, "h13", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[14]) {
		if(GetPVarInt(playerid, "h14") == 1) return 1;
		SetPVarInt(playerid, "h14", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[15]) {
		if(GetPVarInt(playerid, "h15") == 1) return 1;
		SetPVarInt(playerid, "h15", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[16]) {
		if(GetPVarInt(playerid, "h16") == 1) return 1;
		SetPVarInt(playerid, "h16", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[17]) {
		if(GetPVarInt(playerid, "h17") == 1) return 1;
		SetPVarInt(playerid, "h17", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[18]) {
		if(GetPVarInt(playerid, "h18") == 1) return 1;
		SetPVarInt(playerid, "h18", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[19]) {
		if(GetPVarInt(playerid, "h19") == 1) return 1;
		SetPVarInt(playerid, "h19", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[20]) {
		if(GetPVarInt(playerid, "h20") == 1) return 1;
		SetPVarInt(playerid, "h20", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[21]) {
		if(GetPVarInt(playerid, "h21") == 1) return 1;
		SetPVarInt(playerid, "h21", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[22]) {
		if(GetPVarInt(playerid, "h22") == 1) return 1;
		SetPVarInt(playerid, "h22", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[23]) {
		if(GetPVarInt(playerid, "h23") == 1) return 1;
		SetPVarInt(playerid, "h23", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[24]) {
		if(GetPVarInt(playerid, "h24") == 1) return 1;
		SetPVarInt(playerid, "h24", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[25]) {
		if(GetPVarInt(playerid, "h25") == 1) return 1;
		SetPVarInt(playerid, "h25", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[26]) {
		if(GetPVarInt(playerid, "h26") == 1) return 1;
		SetPVarInt(playerid, "h26", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[27]) {
		if(GetPVarInt(playerid, "h27") == 1) return 1;
		SetPVarInt(playerid, "h27", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[28]) {
		if(GetPVarInt(playerid, "h28") == 1) return 1;
		SetPVarInt(playerid, "h28", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[29]) {
		if(GetPVarInt(playerid, "h29") == 1) return 1;
		SetPVarInt(playerid, "h29", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[30]) {
		if(GetPVarInt(playerid, "h30") == 1) return 1;
		SetPVarInt(playerid, "h30", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[31]) {
		if(GetPVarInt(playerid, "h31") == 1) return 1;
		SetPVarInt(playerid, "h31", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[32]) {
		if(GetPVarInt(playerid, "h32") == 1) return 1;
		SetPVarInt(playerid, "h32", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[33]) {
		if(GetPVarInt(playerid, "h33") == 1) return 1;
		SetPVarInt(playerid, "h33", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[34]) {
		if(GetPVarInt(playerid, "h34") == 1) return 1;
		SetPVarInt(playerid, "h34", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[35]) {
		if(GetPVarInt(playerid, "h35") == 1) return 1;
		SetPVarInt(playerid, "h35", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[36]) {
		if(GetPVarInt(playerid, "h36") == 1) return 1;
		SetPVarInt(playerid, "h36", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[37]) {
		if(GetPVarInt(playerid, "h37") == 1) return 1;
		SetPVarInt(playerid, "h37", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[38]) {
		if(GetPVarInt(playerid, "h38") == 1) return 1;
		SetPVarInt(playerid, "h38", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[39]) {
		if(GetPVarInt(playerid, "h39") == 1) return 1;
		SetPVarInt(playerid, "h39", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[40]) {
		if(GetPVarInt(playerid, "h40") == 1) return 1;
		SetPVarInt(playerid, "h40", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[41]) {
		if(GetPVarInt(playerid, "h41") == 1) return 1;
		SetPVarInt(playerid, "h41", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[42]) {
		if(GetPVarInt(playerid, "h42") == 1) return 1;
		SetPVarInt(playerid, "h42", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[43]) {
		if(GetPVarInt(playerid, "h43") == 1) return 1;
		SetPVarInt(playerid, "h43", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[44]) {
		if(GetPVarInt(playerid, "h44") == 1) return 1;
		SetPVarInt(playerid, "h44", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[45]) {
		if(GetPVarInt(playerid, "h45") == 1) return 1;
		SetPVarInt(playerid, "h45", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[46]) {
		if(GetPVarInt(playerid, "h46") == 1) return 1;
		SetPVarInt(playerid, "h46", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[47]) {
		if(GetPVarInt(playerid, "h47") == 1) return 1;
		SetPVarInt(playerid, "h47", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[48]) {
		if(GetPVarInt(playerid, "h48") == 1) return 1;
		SetPVarInt(playerid, "h48", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	if(pickupid == hidden[49]) {
		if(GetPVarInt(playerid, "h49") == 1) return 1;
		SetPVarInt(playerid, "h49", 1);
		new nowpackets = GetPVarInt(playerid, "Packets"); if(nowpackets == 0) SendClientMessage(playerid, -1, ""COLOR_GREEN"Найдите все подковы и получите 50р. на донат счет");
		nowpackets++;
		SetPVarInt(playerid, "Packets", nowpackets);
		format(small_string, sizeof(small_string), "~g~Hidden packet %d/50", nowpackets);
		GameTextForPlayer(playerid, small_string, 5000, 4);
		if(GetPVarInt(playerid, "Packets") == 50) win(playerid);
		return 1;
	}
	return 1;
}
stock win(playerid) {
	if(GetPVarInt(playerid, "h49") != 1) return 1;
	if(GetPVarInt(playerid, "h48") != 1) return 1;
	if(GetPVarInt(playerid, "h47") != 1) return 1;
	if(GetPVarInt(playerid, "h46") != 1) return 1;
	if(GetPVarInt(playerid, "h45") != 1) return 1;
	if(GetPVarInt(playerid, "h44") != 1) return 1;
	if(GetPVarInt(playerid, "h43") != 1) return 1;
	if(GetPVarInt(playerid, "h42") != 1) return 1;
	if(GetPVarInt(playerid, "h41") != 1) return 1;
	if(GetPVarInt(playerid, "h40") != 1) return 1;
	if(GetPVarInt(playerid, "h39") != 1) return 1;
	if(GetPVarInt(playerid, "h38") != 1) return 1;
	if(GetPVarInt(playerid, "h37") != 1) return 1;
	if(GetPVarInt(playerid, "h36") != 1) return 1;
	if(GetPVarInt(playerid, "h35") != 1) return 1;
	if(GetPVarInt(playerid, "h34") != 1) return 1;
	if(GetPVarInt(playerid, "h33") != 1) return 1;
	if(GetPVarInt(playerid, "h32") != 1) return 1;
	if(GetPVarInt(playerid, "h31") != 1) return 1;
	if(GetPVarInt(playerid, "h30") != 1) return 1;
	if(GetPVarInt(playerid, "h29") != 1) return 1;
	if(GetPVarInt(playerid, "h28") != 1) return 1;
	if(GetPVarInt(playerid, "h27") != 1) return 1;
	if(GetPVarInt(playerid, "h26") != 1) return 1;
	if(GetPVarInt(playerid, "h25") != 1) return 1;
	if(GetPVarInt(playerid, "h24") != 1) return 1;
	if(GetPVarInt(playerid, "h23") != 1) return 1;
	if(GetPVarInt(playerid, "h22") != 1) return 1;
	if(GetPVarInt(playerid, "h21") != 1) return 1;
	if(GetPVarInt(playerid, "h20") != 1) return 1;
	if(GetPVarInt(playerid, "h19") != 1) return 1;
	if(GetPVarInt(playerid, "h18") != 1) return 1;
	if(GetPVarInt(playerid, "h17") != 1) return 1;
	if(GetPVarInt(playerid, "h16") != 1) return 1;
	if(GetPVarInt(playerid, "h15") != 1) return 1;
	if(GetPVarInt(playerid, "h14") != 1) return 1;
	if(GetPVarInt(playerid, "h13") != 1) return 1;
	if(GetPVarInt(playerid, "h12") != 1) return 1;
	if(GetPVarInt(playerid, "h11") != 1) return 1;
	if(GetPVarInt(playerid, "h10") != 1) return 1;
	if(GetPVarInt(playerid, "h9") != 1) return 1;
	if(GetPVarInt(playerid, "h8") != 1) return 1;
	if(GetPVarInt(playerid, "h7") != 1) return 1;
	if(GetPVarInt(playerid, "h6") != 1) return 1;
	if(GetPVarInt(playerid, "h5") != 1) return 1;
	if(GetPVarInt(playerid, "h4") != 1) return 1;
	if(GetPVarInt(playerid, "h3") != 1) return 1;
	if(GetPVarInt(playerid, "h2") != 1) return 1;
	if(GetPVarInt(playerid, "h1") != 1) return 1;
	if(GetPVarInt(playerid, "h0") != 1) return 1;
	if(GetPVarInt(playerid, "Packets") == 50) {

		if(PlayerInfo[playerid][pFreshPrice] == 3) return SendClientMessage(playerid, -1, ""COLOR_GREEN"Молодец!");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем!");
		PlayerInfo[playerid][pDonate] += 50;
		SetPlayerInt(playerid, "Donate", PlayerInfo[playerid][pDonate]);
		PlayerInfo[playerid][pFreshPrice] = 3;
		SetPlayerInt(playerid, "FreshPrice", PlayerInfo[playerid][pFreshPrice]);
		format(small_string, sizeof(small_string), ""COLOR_BLUE"%s нашел все подковы и выйграл 50 рублей!", PlayerInfo[playerid][pName]);
		SendClientMessageToAll(1, small_string);
		printf("нашел все подковы %s",PlayerInfo[playerid][pName]);
	}
	return 1;
}