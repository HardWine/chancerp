#if defined _tuning_system_included
	#endinput
#endif
#define _tuning_system_included

stock westcoastcustoms(playerid) {
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleID(playerid) == caridhouse[playerid]) {

		if(GetPlayerVehicleSeat(playerid) != 0) return 1;

		SetVehicleToRespawn(caridhouse[playerid]);

		// SetPlayerScreenColour(playerid, 0x000000FF);
		// FadePlayerScreenColour(playerid, 0x00000000, 5000, 50);
		//GameTextForPlayer(playerid, "~b~Los Santos Customs", 1000+GetPlayerPing(playerid), 2);

		//TogglePlayerControllable(playerid, 0);
		SetVehiclePos(caridhouse[playerid], -2667.8105,1417.7974,901.1921);
		LinkVehicleToInterior(caridhouse[playerid], 3);
		SetPlayerInterior(playerid, 3);
		SetVehicleVirtualWorld(caridhouse[playerid], 333+playerid);
		SetPlayerVirtualWorld(playerid, 333+playerid);
		

		//TogglePlayerSpectating(playerid, 1);

		WelcomeCustoms[playerid] = KillTimer(WelcomeCustoms[playerid]);
		WelcomeCustoms[playerid] = SetTimerEx("WelcomeCallback", 500+GetPlayerPing(playerid), 0, "i", playerid);

		//PutPlayerInVehicle(playerid, caridhouse[playerid], 0);
		
		//TogglePlayerSpectating(playerid, 1);

		//view_customs(playerid, 0);		

		SendClientMessage(playerid, -1, ""COLOR_BLUE"Добро пожаловать в Los Santos Customs!");	

	} else {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Въезд в тюнинг-ателье возможен только на личном транспорте");
	}
	return 1;
}

forward WelcomeCallback(playerid);
public WelcomeCallback(playerid) {
	//SetPlayerPos(playerid, -2667.3347,1416.2480,906.2734);
	SetPlayerPos(playerid, -2667.3347,1416.2480,906.2734);
	view_customs(playerid, 0);
	tuning_show(playerid);
	Dialog_Show(playerid, Dialog:tuning_menu);
	SetVehicleZAngle(caridhouse[playerid], 90.0);	
	return 1;
}

stock view_customs(playerid, vieww) {
	switch(vieww) {
		case 0: {
			// front view
			SetPVarInt(playerid, "view", 1);
			SetPlayerCameraPos(playerid, -2672.386474, 1422.012695, 901.880187);
			SetPlayerCameraLookAt(playerid, -2668.855957, 1418.511840, 901.351135);
		}
		case 1: {
			// from floor
			SetPVarInt(playerid, "view", 2);
			SetPlayerCameraPos(playerid, -2670.350341, 1409.066528, 901.073974);
			SetPlayerCameraLookAt(playerid, -2668.691162, 1413.783081, 901.042724);
		}
		case 2: {
			// back view
			SetPVarInt(playerid, "view", 3);
			SetPlayerCameraPos(playerid, -2664.458740, 1411.531005, 902.437194);
			SetPlayerCameraLookAt(playerid, -2666.732421, 1415.939208, 901.80609);			
		}
	}
	return 1;
}

/*CMD:wcc(playerid) {
	westcoastcustoms(playerid);
	return 1;
}*/

DialogCreate:tuning_menu(playerid) {
		SetPVarInt(playerid, "dialog_tuning", 1);

		return Dialog_Open(playerid, Dialog:tuning_menu, DIALOG_STYLE_LIST,
		""COLOR_BLUE"Los Santos Customs",
		"Покраска\n\
		Винилы\n\
		Тюнинг\n\
		Радар-Детектор",
		"Выбрать", ""
	);
}

new cached_cat[MAX_PLAYERS][14];

new clear_cat_cache[14] = {
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1,
	-1
};

DialogCreate:elements(playerid) {
		SetPVarInt(playerid, "dialog_tuning", 2);

		new
		    compatible_types[ZVEH_MAX_COMPONENT_TYPES],
		    compatible_types_count;

		GetVehicleCompatibleTypes(GetVehicleModel(caridhouse[playerid]), compatible_types, compatible_types_count);

		new elements_string[sizeof(big_string)];

		cached_cat[playerid] = clear_cat_cache;

		for (new i = 0; i < compatible_types_count; i++) {
			if(compatible_types[i] == CARMODTYPE_SPOILER) {
				format(small_string, sizeof(small_string), "Спойлер\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_SPOILER;
						break;
					}
				}
			}
		}
		for (new i = 0; i < compatible_types_count; i++) {
			if(compatible_types[i] == CARMODTYPE_HOOD) {
				format(small_string, sizeof(small_string), "Капот\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_HOOD;
						break;
					}
				}			
			}
		}
		for (new i = 0; i < compatible_types_count; i++) {	
			if(compatible_types[i] == CARMODTYPE_ROOF) {
				format(small_string, sizeof(small_string), "Крыша\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_ROOF;
						break;
					}
				}					
			}
		}
		for (new i = 0; i < compatible_types_count; i++) {		
			if(compatible_types[i] == CARMODTYPE_SIDESKIRT) {
				format(small_string, sizeof(small_string), "Боковые обтекатели\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_SIDESKIRT;
						break;
					}
				}
			}
		}
		for (new i = 0; i < compatible_types_count; i++) {
			if(compatible_types[i] == CARMODTYPE_LAMPS) {
				format(small_string, sizeof(small_string), "Фары\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_LAMPS;
						break;
					}
				}
			}
		}
		for (new i = 0; i < compatible_types_count; i++) {
			if(compatible_types[i] == CARMODTYPE_NITRO) {
				format(small_string, sizeof(small_string), "Закись азота\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_NITRO;
						break;
					}
				}
			}
		}		
		for (new i = 0; i < compatible_types_count; i++) {
			if(compatible_types[i] == CARMODTYPE_EXHAUST) {
				format(small_string, sizeof(small_string), "Выхлопная система\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_EXHAUST;
						break;
					}
				}
			}
		}
		for (new i = 0; i < compatible_types_count; i++) {	
			if(compatible_types[i] == CARMODTYPE_WHEELS) {
				format(small_string, sizeof(small_string), "Диски\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_WHEELS;
						break;
					}
				}
			}
		}
		for (new i = 0; i < compatible_types_count; i++) {
			if(compatible_types[i] == CARMODTYPE_STEREO) {
				format(small_string, sizeof(small_string), "Стереосистема\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_STEREO;
						break;
					}
				}
			}
		}
		for (new i = 0; i < compatible_types_count; i++) {	
			if(compatible_types[i] == CARMODTYPE_HYDRAULICS) {
				format(small_string, sizeof(small_string), "Гидравлика\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_HYDRAULICS;
						break;
					}
				}
			}
		}
		for (new i = 0; i < compatible_types_count; i++) {
			if(compatible_types[i] == CARMODTYPE_FRONT_BUMPER) {
				format(small_string, sizeof(small_string), "Передний бампер\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_FRONT_BUMPER;
						break;
					}
				}
			}
		}
		for (new i = 0; i < compatible_types_count; i++) {	
			if(compatible_types[i] == CARMODTYPE_REAR_BUMPER) {
				format(small_string, sizeof(small_string), "Задний бампер\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_REAR_BUMPER;
						break;
					}
				}
			}
		}
		for (new i = 0; i < compatible_types_count; i++) {	
			if(compatible_types[i] == CARMODTYPE_VENT_RIGHT) {
				format(small_string, sizeof(small_string), "Воздухозаборники\n");
				strcat(elements_string, small_string);
				for(new x = 0; x < 14; x++) {
					if(cached_cat[playerid][x] == -1) {
						cached_cat[playerid][x] = CARMODTYPE_VENT_RIGHT;
						break;
					}
				}
			}	
		}

		return Dialog_Open(playerid, Dialog:elements, DIALOG_STYLE_LIST,
		""COLOR_BLUE"Los Santos Customs",
		elements_string,
		"Выбрать", "Назад"
	);
}


DialogResponse:tuning_menu(playerid, response, listitem, inputtext[]) {
	if(!response) {
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Чтобы покинуть сервис нажмите "COLOR_WHITE"EXIT");
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Чтобы вернуться к меню нажмите "COLOR_WHITE"MENU");
		SelectTextDraw(playerid, 0x2A3439FF);
		return 1;
	} else {
		switch(listitem) {
			case 0: {
				Dialog_Show(playerid, Dialog:paintjob);
			}			
			case 1: {
				Dialog_Show(playerid, Dialog:vynil);
			}
			case 2: {
				new
				    compatible_types[ZVEH_MAX_COMPONENT_TYPES],
				    compatible_types_count;

				GetVehicleCompatibleTypes(GetVehicleModel(caridhouse[playerid]), compatible_types, compatible_types_count);

				if(compatible_types_count == 0) {
					SendClientMessage(playerid, -1, ""COLOR_RED"К сожалению, на ваш транспорт деталей нет");
					return Dialog_Show(playerid, Dialog:tuning_menu);
				}

				Dialog_Show(playerid, Dialog:elements);
			}
			case 3: {
				Dialog_Show(playerid, Dialog:radar_buy);
			}
			case 4: {
				SendClientMessage(playerid, -1, "3");
			}
		}
	}
	return 1;
}

DialogResponse:elements(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return Dialog_Show(playerid, Dialog:tuning_menu);
	} else {
		//new modelid = GetVehicleModel(caridhouse[playerid]);
		new cats;

		for(new i = 0; i < 14; i++) {
			if(cached_cat[playerid][i] != -1) cats++;
			printf("TYPE: %d | LISTITEM (SLOT):%d", cached_cat[playerid][i], i);
		}
		if(cats == 0) return 1;
		if(listitem >= 0 && listitem <= cats) {
			printf("%d", cached_cat[playerid][listitem]);
			SetPVarInt(playerid, "element_type", cached_cat[playerid][listitem]);
			Dialog_Show(playerid, Dialog:elements_cat);
		}
	}
	return 1;
}

new cached_elements[MAX_PLAYERS][17];

new clear_elements_cache[17] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

DialogCreate:elements_cat(playerid) {
	SetPVarInt(playerid, "dialog_tuning", 3);

	new modelid = GetVehicleModel(caridhouse[playerid]),
		elements_string[sizeof(big_string)],
		type = GetPVarInt(playerid, "element_type");

	cached_elements[playerid] = clear_elements_cache;

	if(type == CARMODTYPE_SPOILER) {
		if(IsVehicleUpgradeCompatible(modelid, 1000)) {
			format(small_string, sizeof(small_string), "Спойлер 'Pro'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1000;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1001)) {
			format(small_string, sizeof(small_string), "Спойлер 'Win'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1001;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1002)) {
			format(small_string, sizeof(small_string), "Спойлер 'Drag'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1002;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1003)) {
			format(small_string, sizeof(small_string), "Спойлер 'Alpha'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1003;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1014)) {
			format(small_string, sizeof(small_string), "Спойлер 'Champ'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1014;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1015)) {
			format(small_string, sizeof(small_string), "Спойлер 'Race'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1015;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1016)) {
			format(small_string, sizeof(small_string), "Спойлер 'Worx'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1016;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1023)) {
			format(small_string, sizeof(small_string), "Спойлер 'Fury'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1023;
					break;
				}
			}
		}			
		if(IsVehicleUpgradeCompatible(modelid, 1049)) {
			format(small_string, sizeof(small_string), "Спойлер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1049;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1050)) {
			format(small_string, sizeof(small_string), "Спойлер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1050;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1058)) {
			format(small_string, sizeof(small_string), "Спойлер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1058;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1060)) {
			format(small_string, sizeof(small_string), "Спойлер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1060;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1138)) {
			format(small_string, sizeof(small_string), "Спойлер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1138;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1139)) {
			format(small_string, sizeof(small_string), "Спойлер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1139;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1146)) {
			format(small_string, sizeof(small_string), "Спойлер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1146;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1147)) {
			format(small_string, sizeof(small_string), "Спойлер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1147;
					break;
				}
			}
		}				
		if(IsVehicleUpgradeCompatible(modelid, 1158)) {
			format(small_string, sizeof(small_string), "Спойлер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1158;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1162)) {
			format(small_string, sizeof(small_string), "Спойлер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1162;
					break;
				}
			}
		}			
		if(IsVehicleUpgradeCompatible(modelid, 1163)) {
			format(small_string, sizeof(small_string), "Спойлер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1163;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1164)) {
			format(small_string, sizeof(small_string), "Спойлер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1164;
					break;
				}
			}
		}																			
	}
	if(type == CARMODTYPE_HOOD) {
		if(IsVehicleUpgradeCompatible(modelid, 1004)) {
			format(small_string, sizeof(small_string), "Капот 'Champ'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1004;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1005)) {
			format(small_string, sizeof(small_string), "Капот 'Fury'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1005;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1011)) {
			format(small_string, sizeof(small_string), "Капот 'Race'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1011;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1012)) {
			format(small_string, sizeof(small_string), "Капот 'Worx'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1012;
					break;
				}
			}
		}				
	}
	if(type == CARMODTYPE_ROOF) {
		if(IsVehicleUpgradeCompatible(modelid, 1006)) {
			format(small_string, sizeof(small_string), "Воздухозаборник\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1006;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1032)) {
			format(small_string, sizeof(small_string), "Воздухозаборник 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1032;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1033)) {
			format(small_string, sizeof(small_string), "Воздухозаборник 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1033;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1035)) {
			format(small_string, sizeof(small_string), "Воздухозаборник 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1035;
					break;
				}
			}
		}			
		if(IsVehicleUpgradeCompatible(modelid, 1038)) {
			format(small_string, sizeof(small_string), "Воздухозаборник 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1038;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1053)) {
			format(small_string, sizeof(small_string), "Воздухозаборник 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1053;
					break;
				}
			}
		}			
		if(IsVehicleUpgradeCompatible(modelid, 1054)) {
			format(small_string, sizeof(small_string), "Воздухозаборник 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1054;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1055)) {
			format(small_string, sizeof(small_string), "Воздухозаборник 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1055;
					break;
				}
			}
		}			
		if(IsVehicleUpgradeCompatible(modelid, 1061)) {
			format(small_string, sizeof(small_string), "Воздухозаборник 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1061;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1067)) {
			format(small_string, sizeof(small_string), "Воздухозаборник 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1067;
					break;
				}
			}
		}			
		if(IsVehicleUpgradeCompatible(modelid, 1068)) {
			format(small_string, sizeof(small_string), "Воздухозаборник 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1068;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1088)) {
			format(small_string, sizeof(small_string), "Воздухозаборник 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1088;
					break;
				}
			}
		}			
		if(IsVehicleUpgradeCompatible(modelid, 1091)) {
			format(small_string, sizeof(small_string), "Воздухозаборник 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1091;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1103)) {
			format(small_string, sizeof(small_string), "Складная крыша\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1103;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1128)) {
			format(small_string, sizeof(small_string), "Виниловый хард-топ\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1128;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1130)) {
			format(small_string, sizeof(small_string), "Хард-топ\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1130;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1131)) {
			format(small_string, sizeof(small_string), "Софт-топ\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1131;
					break;
				}
			}
		}																	
	}
	if(type == CARMODTYPE_SIDESKIRT) {
		if(IsVehicleUpgradeCompatible(modelid, 1007) && IsVehicleUpgradeCompatible(modelid, 1017)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1007);
					SetPVarInt(playerid, "dbl_two", 1017);
					break;
				}
			}			
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1026) && IsVehicleUpgradeCompatible(modelid, 1027)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1026);
					SetPVarInt(playerid, "dbl_two", 1027);
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1030) && IsVehicleUpgradeCompatible(modelid, 1031)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1030);
					SetPVarInt(playerid, "dbl_two", 1031);
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1036) && IsVehicleUpgradeCompatible(modelid, 1040)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1036);
					SetPVarInt(playerid, "dbl_two", 1040);
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1039) && IsVehicleUpgradeCompatible(modelid, 1041)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1039);
					SetPVarInt(playerid, "dbl_two", 1041);
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1042) && IsVehicleUpgradeCompatible(modelid, 1099)) {
			format(small_string, sizeof(small_string), "Хромированные накладки\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1042);
					SetPVarInt(playerid, "dbl_two", 1099);
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1047) && IsVehicleUpgradeCompatible(modelid, 1051)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1047);
					SetPVarInt(playerid, "dbl_two", 1051);
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1048) && IsVehicleUpgradeCompatible(modelid, 1052)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1048);
					SetPVarInt(playerid, "dbl_two", 1052);
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1056) && IsVehicleUpgradeCompatible(modelid, 1062)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1056);
					SetPVarInt(playerid, "dbl_two", 1062);
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1057) && IsVehicleUpgradeCompatible(modelid, 1063)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1057);
					SetPVarInt(playerid, "dbl_two", 1063);
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1069) && IsVehicleUpgradeCompatible(modelid, 1071)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1069);
					SetPVarInt(playerid, "dbl_two", 1071);
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1070) && IsVehicleUpgradeCompatible(modelid, 1072)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1070);
					SetPVarInt(playerid, "dbl_two", 1072);
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1095) && IsVehicleUpgradeCompatible(modelid, 1094)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1095);
					SetPVarInt(playerid, "dbl_two", 1094);
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1093) && IsVehicleUpgradeCompatible(modelid, 1095)) {
			format(small_string, sizeof(small_string), "Боковые обтекатели 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1093);
					SetPVarInt(playerid, "dbl_two", 1095);
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1101) && IsVehicleUpgradeCompatible(modelid, 1122)) {
			format(small_string, sizeof(small_string), "Хром. накладка 'Языки пламени'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1101);
					SetPVarInt(playerid, "dbl_two", 1122);
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1106) && IsVehicleUpgradeCompatible(modelid, 1124)) {
			format(small_string, sizeof(small_string), "Хром. накладка 'Стрелы'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1106);
					SetPVarInt(playerid, "dbl_two", 1124);
					break;
				}
			}
		}			
		if(IsVehicleUpgradeCompatible(modelid, 1102) && IsVehicleUpgradeCompatible(modelid, 1133)) {
			format(small_string, sizeof(small_string), "Хром. накладка 'Полоса'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1102);
					SetPVarInt(playerid, "dbl_two", 1133);
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1107) && IsVehicleUpgradeCompatible(modelid, 1108)) {
			format(small_string, sizeof(small_string), "Хром. накладка 'Полоса'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1107);
					SetPVarInt(playerid, "dbl_two", 1108);
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1118) && IsVehicleUpgradeCompatible(modelid, 1120)) {
			format(small_string, sizeof(small_string), "Отделка с хромированием\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1118);
					SetPVarInt(playerid, "dbl_two", 1120);
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1119) && IsVehicleUpgradeCompatible(modelid, 1121)) {
			format(small_string, sizeof(small_string), "Wheelcovers\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1119);
					SetPVarInt(playerid, "dbl_two", 1121);
					break;
				}
			}
		}			
		if(IsVehicleUpgradeCompatible(modelid, 1134) && IsVehicleUpgradeCompatible(modelid, 1137)) {
			format(small_string, sizeof(small_string), "Хром. накладка 'Полоса'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1134);
					SetPVarInt(playerid, "dbl_two", 1137);
					break;
				}
			}
		}									
	}
	if(type == CARMODTYPE_LAMPS) {
		if(IsVehicleUpgradeCompatible(modelid, 1013)) {
			format(small_string, sizeof(small_string), "Фары противотуманные (круглые)\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1013;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1024)) {
			format(small_string, sizeof(small_string), "Фары противотуманные (квадратные)\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1024;
					break;
				}
			}
		}		
	}
	if(type == CARMODTYPE_NITRO) {
		if(IsVehicleUpgradeCompatible(modelid, 1009)) {
			format(small_string, sizeof(small_string), "Закись азота (x2)\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1009;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1008)) {
			format(small_string, sizeof(small_string), "Закись азота (х5)\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1008;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1010)) {
			format(small_string, sizeof(small_string), "Закись азота (х10)\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1010;
					break;
				}
			}
		}				
	}
	if(type == CARMODTYPE_EXHAUST) {
		if(IsVehicleUpgradeCompatible(modelid, 1018)) {
			format(small_string, sizeof(small_string), "Вертикальная выхлопная система\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1018;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1019)) {
			format(small_string, sizeof(small_string), "Двойная выхлопная система\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1019;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1022)) {
			format(small_string, sizeof(small_string), "Малая выхлопная система\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1022;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1021)) {
			format(small_string, sizeof(small_string), "Средняя выхлопная система\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1021;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1020)) {
			format(small_string, sizeof(small_string), "Большая выхлопная система\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1020;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1028)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1028;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1029)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1029;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1034)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1034;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1037)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1037;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1046)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1046;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1045)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1045;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1064)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1064;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1059)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1059;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1065)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1065;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1066)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1066;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1092)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1092;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1089)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1089;
					break;
				}
			}
		}				
		if(IsVehicleUpgradeCompatible(modelid, 1043)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1043;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1044)) {
			format(small_string, sizeof(small_string), "Хром. выхлопная система\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1044;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1105)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1105;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1104)) {
			format(small_string, sizeof(small_string), "Хром. выхлопная система\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1104;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1114)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1114;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1113)) {
			format(small_string, sizeof(small_string), "Хром. выхлопная система\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1113;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1127)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1127;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1126)) {
			format(small_string, sizeof(small_string), "Хром. выхлопная система\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1126;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1132)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1132;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1129)) {
			format(small_string, sizeof(small_string), "Хром. выхлопная система\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1129;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1135)) {
			format(small_string, sizeof(small_string), "Выхлопная система 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1135;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1136)) {
			format(small_string, sizeof(small_string), "Хром. выхлопная система\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1136;
					break;
				}
			}
		}																								
	}
	if(type == CARMODTYPE_WHEELS) {
		if(IsVehicleUpgradeCompatible(modelid, 1025)) {
			format(small_string, sizeof(small_string), "Внедорожные\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1025;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1073)) {
			format(small_string, sizeof(small_string), "Литые диски 'Shadow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1073;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1074)) {
			format(small_string, sizeof(small_string), "Литые диски 'Mega'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1074;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1075)) {
			format(small_string, sizeof(small_string), "Литые диски 'Rimshine'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1075;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1076)) {
			format(small_string, sizeof(small_string), "Литые диски 'Wires'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1076;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1077)) {
			format(small_string, sizeof(small_string), "Литые диски 'Classic'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1077;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1078)) {
			format(small_string, sizeof(small_string), "Литые диски 'Twist'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1078;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1079)) {
			format(small_string, sizeof(small_string), "Литые диски 'Cutter'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1079;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1080)) {
			format(small_string, sizeof(small_string), "Литые диски 'Switch'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1080;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1081)) {
			format(small_string, sizeof(small_string), "Литые диски 'Grove'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1081;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1082)) {
			format(small_string, sizeof(small_string), "Литые диски 'Import'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1082;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1083)) {
			format(small_string, sizeof(small_string), "Литые диски 'Dollar'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1083;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1084)) {
			format(small_string, sizeof(small_string), "Литые диски 'Trance'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1084;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1085)) {
			format(small_string, sizeof(small_string), "Литые диски 'Atomic'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1085;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1096)) {
			format(small_string, sizeof(small_string), "Литые диски 'Ahab'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1096;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1097)) {
			format(small_string, sizeof(small_string), "Литые диски 'Virtual'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1097;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1098)) {
			format(small_string, sizeof(small_string), "Литые диски 'Access'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1098;
					break;
				}
			}
		}															
	}
	if(type == CARMODTYPE_STEREO) {
		if(IsVehicleUpgradeCompatible(modelid, 1086)) {
			format(small_string, sizeof(small_string), "Стереосистема (Bass Boost)\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1086;
					break;
				}
			}
		}	
	}
	if(type == CARMODTYPE_HYDRAULICS) {
		if(IsVehicleUpgradeCompatible(modelid, 1087)) {
			format(small_string, sizeof(small_string), "Гидравлическая подвеска\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1087;
					break;
				}
			}
		}	
	}
	if(type == CARMODTYPE_FRONT_BUMPER) {
		if(IsVehicleUpgradeCompatible(modelid, 1152)) {
			format(small_string, sizeof(small_string), "Передний бампер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1152;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1153)) {
			format(small_string, sizeof(small_string), "Передний бампер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1153;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1157)) {
			format(small_string, sizeof(small_string), "Передний бампер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1157;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1155)) {
			format(small_string, sizeof(small_string), "Передний бампер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1155;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1165)) {
			format(small_string, sizeof(small_string), "Передний бампер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1165;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1160)) {
			format(small_string, sizeof(small_string), "Передний бампер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1160;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1166)) {
			format(small_string, sizeof(small_string), "Передний бампер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1166;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1169)) {
			format(small_string, sizeof(small_string), "Передний бампер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1169;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1170)) {
			format(small_string, sizeof(small_string), "Передний бампер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1170;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1171)) {
			format(small_string, sizeof(small_string), "Передний бампер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1171;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1172)) {
			format(small_string, sizeof(small_string), "Передний бампер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1172;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1173)) {
			format(small_string, sizeof(small_string), "Передний бампер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1173;
					break;
				}
			}
		}											
		if(IsVehicleUpgradeCompatible(modelid, 1117)) {
			format(small_string, sizeof(small_string), "Хромированный передний бампер\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1117;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1191)) {
			format(small_string, sizeof(small_string), "Хромированный передний бампер\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1191;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1189)) {
			format(small_string, sizeof(small_string), "Хромированный передний бампер\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1189;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1182)) {
			format(small_string, sizeof(small_string), "Хромированный передний бампер\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1182;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1179)) {
			format(small_string, sizeof(small_string), "Хромированный передний бампер\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1179;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1174)) {
			format(small_string, sizeof(small_string), "Хромированный передний бампер\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1174;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1190)) {
			format(small_string, sizeof(small_string), "Передний бампер 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1190;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1188)) {
			format(small_string, sizeof(small_string), "Передний бампер 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1188;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1185)) {
			format(small_string, sizeof(small_string), "Передний бампер 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1185;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1181)) {
			format(small_string, sizeof(small_string), "Передний бампер 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1181;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1175)) {
			format(small_string, sizeof(small_string), "Передний бампер 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1175;
					break;
				}
			}
		}												
	}
	if(type == CARMODTYPE_REAR_BUMPER) {
		if(IsVehicleUpgradeCompatible(modelid, 1140)) {
			format(small_string, sizeof(small_string), "Задний бампер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1140;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1141)) {
			format(small_string, sizeof(small_string), "Задний бампер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1141;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1148)) {
			format(small_string, sizeof(small_string), "Задний бампер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1148;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1149)) {
			format(small_string, sizeof(small_string), "Задний бампер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1149;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1150)) {
			format(small_string, sizeof(small_string), "Задний бампер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1150;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1151)) {
			format(small_string, sizeof(small_string), "Задний бампер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1151;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1154)) {
			format(small_string, sizeof(small_string), "Задний бампер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1154;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1159)) {
			format(small_string, sizeof(small_string), "Задний бампер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1159;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1156)) {
			format(small_string, sizeof(small_string), "Задний бампер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1156;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1168)) {
			format(small_string, sizeof(small_string), "Задний бампер 'Alien'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1168;
					break;
				}
			}
		}		
		if(IsVehicleUpgradeCompatible(modelid, 1161)) {
			format(small_string, sizeof(small_string), "Задний бампер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1161;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1167)) {
			format(small_string, sizeof(small_string), "Задний бампер 'X-Flow'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1167;
					break;
				}
			}
		}											
		if(IsVehicleUpgradeCompatible(modelid, 1192)) {
			format(small_string, sizeof(small_string), "Хромированный задний бампер\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1192;
					break;
				}
			}
		}	
		if(IsVehicleUpgradeCompatible(modelid, 1187)) {
			format(small_string, sizeof(small_string), "Хромированный задний бампер\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1187;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1184)) {
			format(small_string, sizeof(small_string), "Хромированный задний бампер\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1184;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1180)) {
			format(small_string, sizeof(small_string), "Хромированный задний бампер\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1180;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1176)) {
			format(small_string, sizeof(small_string), "Хромированный задний бампер\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1176;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1177)) {
			format(small_string, sizeof(small_string), "Задний бампер 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1177;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1178)) {
			format(small_string, sizeof(small_string), "Задний бампер 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1178;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1183)) {
			format(small_string, sizeof(small_string), "Задний бампер 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1183;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1186)) {
			format(small_string, sizeof(small_string), "Задний бампер 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1186;
					break;
				}
			}
		}
		if(IsVehicleUpgradeCompatible(modelid, 1193)) {
			format(small_string, sizeof(small_string), "Задний бампер 'Slamin'\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					cached_elements[playerid][i] = 1193;
					break;
				}
			}
		}												
	}	
	if(type == CARMODTYPE_VENT_RIGHT) {
		if(IsVehicleUpgradeCompatible(modelid, 1142) && IsVehicleUpgradeCompatible(modelid, 1143)) {
			format(small_string, sizeof(small_string), "Круглые воздухозаборники\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1142);
					SetPVarInt(playerid, "dbl_two", 1143);
					break;
				}
			}			
		}
		if(IsVehicleUpgradeCompatible(modelid, 1144) && IsVehicleUpgradeCompatible(modelid, 1145)) {
			format(small_string, sizeof(small_string), "Квадратные воздухозаборники\n");
			strcat(elements_string, small_string);
			for(new i = 0; i < 17; i++) {
				if(cached_elements[playerid][i] == 0) {
					SetPVarInt(playerid, "dbl_one", 1144);
					SetPVarInt(playerid, "dbl_two", 1145);
					break;
				}
			}			
		}	
	}	
	return Dialog_Open(playerid, Dialog:elements_cat, DIALOG_STYLE_LIST,
	""COLOR_BLUE"Los Santos Customs",
	elements_string,
	"Выбрать", "Назад");
}

DialogResponse:elements_cat(playerid, response, listitem, inputtext[]) {
	if(!response) {
		RemoveVehicleComponent(caridhouse[playerid], cached_elements[playerid][GetPVarInt(playerid, "element_listitem")]);
		return Dialog_Show(playerid, Dialog:elements);
	} else {
		new type = GetPVarInt(playerid, "element_type");
		SetPVarInt(playerid, "element_listitem", listitem);

		if(type == CARMODTYPE_SIDESKIRT || type == CARMODTYPE_VENT_RIGHT) {

			AddVehicleComponent(caridhouse[playerid], GetPVarInt(playerid, "dbl_one"));
			AddVehicleComponent(caridhouse[playerid], GetPVarInt(playerid, "dbl_two"));

		} else {
			AddVehicleComponent(caridhouse[playerid], cached_elements[playerid][listitem]);
		}
		Dialog_Show(playerid, Dialog:element_buy);
	}
	return 1;
}

DialogCreate:element_buy(playerid) {
    SetPVarInt(playerid, "dialog_tuning", 4);
	new cost;
	new slot = PlayerInfo[playerid][pSelectedSlot];
	new modelid = -1;
	new component = cached_elements[playerid][GetPVarInt(playerid, "element_listitem")];

	if(slot == 1) modelid = PlayerInfo[playerid][pCar];
	if(slot == 2) modelid = PlayerInfo[playerid][pCar2];

    for(new i = 0; i < MAX_CAR_AUTOSALEE; i++) {
        if(AutoSalee[i][AS_ModelID] == modelid) {
            cost = AutoSalee[i][AS_Score]/3;	
        }
    }

    if(cost <= 0) cost = 300000;

	switch(component) {
		case 1008: cost = 5000;
		case 1009: cost = 2000;
		case 1010: cost = 10000;
		case 1025: cost = 2500;
		case 1073..1085: cost = cost*2;
		case 1096..1098: cost = cost*2;
		case 1086: cost = cost/2;
		case 1087: cost = cost*2;
		default: {
		    if(cost < 1500) cost = 1500;
		    if(cost > 10000) cost = 10000;			
		}
	}

    SetPVarInt(playerid, "element_cost", cost);

	format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы хотите приобрести элемент #%d за %d EXP?\n\
		"COLOR_BLUE"Подсказка:"COLOR_WHITE" Чтобы осмотреть автомобиль нажмите клавишу MENU", component, cost);

	PlayerPlaySound(playerid, 1133, 0, 0, 0);

	return Dialog_Open(playerid, Dialog:element_buy, DIALOG_STYLE_MSGBOX,
		""COLOR_BLUE"Покупка",
		small_string,
		"Купить", "Назад"
	);
}

DialogResponse:element_buy(playerid, response, listitem, inputtext[]) {
	new vehicleid;
	new cost = GetPVarInt(playerid, "element_cost");

	if(PlayerInfo[playerid][pSelectedSlot] == 1) vehicleid = PlayerInfo[playerid][pCar];
	if(PlayerInfo[playerid][pSelectedSlot] == 2) vehicleid = PlayerInfo[playerid][pCar2];


	if(!response) {
		//new type = GetPVarInt(playerid, "element_type");
		RemoveVehicleComponent(vehicleid, cached_elements[playerid][GetPVarInt(playerid, "element_listitem")]);
		return Dialog_Show(playerid, Dialog:elements_cat);
	} else {
		if(CheckCash(playerid, cost) == false) {
			SendClientMessage(playerid, -1, ""COLOR_RED"Вам не хватает средств!");
			RemoveVehicleComponent(vehicleid, cached_elements[playerid][GetPVarInt(playerid, "element_listitem")]);
			return Dialog_Show(playerid, Dialog:elements_cat);	
		}
		RemovePlayerEXP(playerid, cost, "Покупка тюнинг-детали");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили тюнинг-деталь на свой транспорт");
		save_elements(playerid);
		Dialog_Show(playerid, Dialog:elements);	
	}
	return 1;
}


stock save_elements(playerid) {
	new cat = GetPVarInt(playerid, "element_type");
	new cached_element = cached_elements[playerid][GetPVarInt(playerid, "element_listitem")];

	switch(cat) {
		case CARMODTYPE_SPOILER: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Spoiler_1] = cached_element;
				SetPlayerInt(playerid, "Spoiler_1", PlayerInfo[playerid][Spoiler_1]);
			} else {
				PlayerInfo[playerid][Spoiler_2] = cached_element;
				SetPlayerInt(playerid, "Spoiler_2", PlayerInfo[playerid][Spoiler_2]);		
			}			
		}
		case CARMODTYPE_HOOD: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Hood_1] = cached_element;
				SetPlayerInt(playerid, "Hood_1", PlayerInfo[playerid][Hood_1]);
			} else {
				PlayerInfo[playerid][Hood_2] = cached_element;
				SetPlayerInt(playerid, "Hood_2", PlayerInfo[playerid][Hood_2]);		
			}			
		}
		case CARMODTYPE_ROOF: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Roof_1] = cached_element;
				SetPlayerInt(playerid, "Roof_1", PlayerInfo[playerid][Roof_1]);
			} else {
				PlayerInfo[playerid][Roof_2] = cached_element;
				SetPlayerInt(playerid, "Roof_2", PlayerInfo[playerid][Roof_2]);		
			}			
		}
		case CARMODTYPE_SIDESKIRT: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Sideskirt_1] = GetPVarInt(playerid, "dbl_one");
				PlayerInfo[playerid][Sideskirt1_1] = GetPVarInt(playerid, "dbl_two");
				SetPlayerInt(playerid, "Sideskirt_1", PlayerInfo[playerid][Sideskirt_1]);
				SetPlayerInt(playerid, "Sideskirt1_1", PlayerInfo[playerid][Sideskirt1_1]);
			} else {
				PlayerInfo[playerid][Sideskirt_2] = GetPVarInt(playerid, "dbl_one");
				PlayerInfo[playerid][Sideskirt2_2] = GetPVarInt(playerid, "dbl_two");
				SetPlayerInt(playerid, "Sideskirt_2", PlayerInfo[playerid][Sideskirt_2]);
				SetPlayerInt(playerid, "Sideskirt2_2", PlayerInfo[playerid][Sideskirt2_2]);	
			}			
		}
		case CARMODTYPE_LAMPS: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Lamps_1] = cached_element;
				SetPlayerInt(playerid, "Lamps_1", PlayerInfo[playerid][Lamps_1]);
			} else {
				PlayerInfo[playerid][Lamps_2] = cached_element;
				SetPlayerInt(playerid, "Lamps_2", PlayerInfo[playerid][Lamps_2]);		
			}			
		}
		case CARMODTYPE_NITRO: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Nitro_1] = cached_element;
				SetPlayerInt(playerid, "Nitro_1", PlayerInfo[playerid][Nitro_1]);
			} else {
				PlayerInfo[playerid][Nitro_2] = cached_element;
				SetPlayerInt(playerid, "Nitro_2", PlayerInfo[playerid][Nitro_2]);		
			}			
		}
		case CARMODTYPE_EXHAUST: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Exhaust_1] = cached_element;
				SetPlayerInt(playerid, "Exhaust_1", PlayerInfo[playerid][Exhaust_1]);
			} else {
				PlayerInfo[playerid][Exhaust_2] = cached_element;
				SetPlayerInt(playerid, "Exhaust_2", PlayerInfo[playerid][Exhaust_2]);		
			}			
		}
		case CARMODTYPE_WHEELS: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Wheels_1] = cached_element;
				SetPlayerInt(playerid, "Wheels_1", PlayerInfo[playerid][Wheels_1]);
			} else {
				PlayerInfo[playerid][Wheels_2] = cached_element;
				SetPlayerInt(playerid, "Wheels_2", PlayerInfo[playerid][Wheels_2]);		
			}			
		}
		case CARMODTYPE_STEREO: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Stereo_1] = cached_element;
				SetPlayerInt(playerid, "Stereo_1", PlayerInfo[playerid][Stereo_1]);
			} else {
				PlayerInfo[playerid][Stereo_2] = cached_element;
				SetPlayerInt(playerid, "Stereo_2", PlayerInfo[playerid][Stereo_2]);		
			}			
		}
		case CARMODTYPE_HYDRAULICS: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Hydraulics_1] = cached_element;
				SetPlayerInt(playerid, "Hydraulics_1", PlayerInfo[playerid][Hydraulics_1]);
			} else {
				PlayerInfo[playerid][Hydraulics_2] = cached_element;
				SetPlayerInt(playerid, "Hydraulics_2", PlayerInfo[playerid][Hydraulics_2]);		
			}			
		}
		case CARMODTYPE_FRONT_BUMPER: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Front_Bumper_1] = cached_element;
				SetPlayerInt(playerid, "Front_Bumper_1", PlayerInfo[playerid][Front_Bumper_1]);
			} else {
				PlayerInfo[playerid][Front_Bumper_2] = cached_element;
				SetPlayerInt(playerid, "Front_Bumper_2", PlayerInfo[playerid][Front_Bumper_2]);		
			}			
		}
		case CARMODTYPE_REAR_BUMPER: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Rear_Bumper_1] = cached_element;
				SetPlayerInt(playerid, "Rear_Bumper_1", PlayerInfo[playerid][Rear_Bumper_1]);
			} else {
				PlayerInfo[playerid][Rear_Bumper_2] = cached_element;
				SetPlayerInt(playerid, "Rear_Bumper_2", PlayerInfo[playerid][Rear_Bumper_2]);		
			}			
		}
		case CARMODTYPE_VENT_RIGHT: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Vent_Right_1] = GetPVarInt(playerid, "dbl_one");
				PlayerInfo[playerid][Vent_Left_1] = GetPVarInt(playerid, "dbl_two");
				SetPlayerInt(playerid, "Vent_Right_1", PlayerInfo[playerid][Vent_Right_1]);
				SetPlayerInt(playerid, "Vent_Left_1", PlayerInfo[playerid][Vent_Left_1]);
			} else {
				PlayerInfo[playerid][Vent_Right_2] = GetPVarInt(playerid, "dbl_one");
				PlayerInfo[playerid][Vent_Left_2] = GetPVarInt(playerid, "dbl_two");
				SetPlayerInt(playerid, "Vent_Right_2", PlayerInfo[playerid][Vent_Right_2]);
				SetPlayerInt(playerid, "Vent_Left_2", PlayerInfo[playerid][Vent_Left_2]);
			}			
		}
		/*case CARMODTYPE_VENT_LEFT: {
			if(PlayerInfo[playerid][pSelectedSlot] == 1) {
				PlayerInfo[playerid][Vent_Left_1] = cached_element;
				SetPlayerInt(playerid, "Vent_Left_1", PlayerInfo[playerid][Vent_Left_1]);
			} else {
				PlayerInfo[playerid][Vent_Left_2] = cached_element;
				SetPlayerInt(playerid, "Vent_Left_2", PlayerInfo[playerid][Vent_Left_2]);		
			}			
		}*/
	}
	return 1;
}

DialogCreate:vynil(playerid) {
    SetPVarInt(playerid, "dialog_tuning", 5);

	return Dialog_Open(playerid, Dialog:vynil, DIALOG_STYLE_LIST,
		""COLOR_BLUE"Винилы",
		"Винил 1\nВинил 2\nВинил 3",
		"Купить", "Назад"
	);
}

DialogResponse:vynil(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return Dialog_Show(playerid, Dialog:tuning_menu);
	}	
	if(listitem == 0) {
		SetPVarInt(playerid, "pjob", 1);
		ChangeVehiclePaintjob(caridhouse[playerid], 0);		
	}
	if(listitem == 1) {
		SetPVarInt(playerid, "pjob", 2);
		ChangeVehiclePaintjob(caridhouse[playerid], 1);		
	}
	if(listitem == 2) {
		SetPVarInt(playerid, "pjob", 3);
		ChangeVehiclePaintjob(caridhouse[playerid], 2);		
	}	
	Dialog_Show(playerid, Dialog:vynil_buy);
	return 1;
}

DialogCreate:vynil_buy(playerid) {
    SetPVarInt(playerid, "dialog_tuning", 6);
	new cost = 50000;
	//new slot = PlayerInfo[playerid][pSelectedSlot];
	//new modelid = -1;

	//if(slot == 1) modelid = PlayerInfo[playerid][pCar];
	//if(slot == 2) modelid = PlayerInfo[playerid][pCar2];

	format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы хотите приобрести установленный винил за %d EXP?\n\
		"COLOR_RED"Внимание:"COLOR_WHITE" Если винил не отображается, значит он не поддерживается!", cost);

	PlayerPlaySound(playerid, 1134, 0, 0, 0);

	return Dialog_Open(playerid, Dialog:vynil_buy, DIALOG_STYLE_MSGBOX,
		""COLOR_BLUE"Покупка",
		small_string,
		"Купить", "Назад"
	);
}

DialogResponse:vynil_buy(playerid, response, listitem, inputtext[]) {
	new vehicleid;

	if(PlayerInfo[playerid][pSelectedSlot] == 1) vehicleid = PlayerInfo[playerid][pCar];
	if(PlayerInfo[playerid][pSelectedSlot] == 2) vehicleid = PlayerInfo[playerid][pCar2];


	if(!response) {
		ChangeVehiclePaintjob(vehicleid, 3);
		return Dialog_Show(playerid, Dialog:vynil);
	}

	if(CheckCash(playerid, 50000) == false) {
		SendClientMessage(playerid, -1, ""COLOR_RED"Вам не хватает средств!");
		RemoveVehicleComponent(vehicleid, cached_elements[playerid][GetPVarInt(playerid, "element_listitem")]);
		return Dialog_Show(playerid, Dialog:elements_cat);	
	}

	RemovePlayerEXP(playerid, 50000, "Покупка винил");
	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили винил на свой транспорт");
	
	if(PlayerInfo[playerid][pSelectedSlot] == 1) {
		PlayerInfo[playerid][Vynil_1] = GetPVarInt(playerid, "pjob");
		SetPlayerInt(playerid, "Vynil_1", PlayerInfo[playerid][Vynil_1]);
	}
	if(PlayerInfo[playerid][pSelectedSlot] == 2) {
		PlayerInfo[playerid][Vynil_2] = GetPVarInt(playerid, "pjob");
		SetPlayerInt(playerid, "Vynil_2", PlayerInfo[playerid][Vynil_2]);	
	}

	Dialog_Show(playerid, Dialog:tuning_menu);	

	return 1;
}

stock wear_elements(playerid) {

	if(PlayerInfo[playerid][pSelectedSlot] == 1) {

		ChangeVehiclePaintjob(caridhouse[playerid], PlayerInfo[playerid][Vynil_1]-1);
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Spoiler_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Spoiler_1]);
		}
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Hood_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Hood_1]);
		}	
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Roof_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Roof_1]);
		}
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Lamps_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Lamps_1]);
		}		
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Nitro_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Nitro_1]);
		}
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Exhaust_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Exhaust_1]);
		}	
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Wheels_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Wheels_1]);
		}		
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Stereo_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Stereo_1]);
		}	
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Hydraulics_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Hydraulics_1]);
		}	
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Front_Bumper_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Front_Bumper_1]);
		}		
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Rear_Bumper_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Rear_Bumper_1]);
		}

		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Vent_Right_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Vent_Right_1]);
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Vent_Left_1]);
		}
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar], PlayerInfo[playerid][Sideskirt_1])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Sideskirt_1]);
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Sideskirt1_1]);
		}	

	} else {

		ChangeVehiclePaintjob(caridhouse[playerid], PlayerInfo[playerid][Vynil_2]-1);
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Spoiler_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Spoiler_2]);
		}
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Hood_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Hood_2]);
		}	
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Roof_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Roof_2]);
		}	
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Lamps_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Lamps_2]);
		}		
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Nitro_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Nitro_2]);
		}
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Exhaust_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Exhaust_2]);
		}	
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Wheels_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Wheels_2]);
		}		
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Stereo_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Stereo_2]);
		}	
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Hydraulics_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Hydraulics_2]);
		}	
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Front_Bumper_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Front_Bumper_2]);
		}		
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Rear_Bumper_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Rear_Bumper_2]);
		}	
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Vent_Right_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Vent_Right_2]);
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Vent_Left_2]);
		}
		if(IsVehicleUpgradeCompatible(PlayerInfo[playerid][pCar2], PlayerInfo[playerid][Sideskirt_2])) {
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Sideskirt_2]);
			AddVehicleComponent(caridhouse[playerid], PlayerInfo[playerid][Sideskirt2_2]);
		}			
	}
	return 1;
}

DialogCreate:radar_buy(playerid) {

	return Dialog_Open(playerid, Dialog:radar_buy, DIALOG_STYLE_MSGBOX,
		""COLOR_BLUE"Покупка",
		""COLOR_WHITE"Вы хотите приобрести Радар-Детектор 'AC#11-AB' за 9000 EXP?\n\
		"COLOR_GREEN"Инфо:"COLOR_WHITE"Радар-Детектор позволяет видеть на карте все места, где расположены радары",
		"Купить", "Назад"
	);
}

DialogResponse:radar_buy(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return Dialog_Show(playerid, Dialog:tuning_menu);
	}
	if(CheckCash(playerid, 9000) == false) {
		SendClientMessage(playerid, -1, ""COLOR_RED"Недостаточно средств!");
		return Dialog_Show(playerid, Dialog:tuning_menu);
	}
	RemovePlayerEXP(playerid, 9000, "Покупка радар-детектора");
	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили Радар-Детектор");
	Dialog_Show(playerid, Dialog:tuning_menu);

	if(PlayerInfo[playerid][pSelectedSlot] == 1) {
		PlayerInfo[playerid][pRadarDetect1] = 1;
		SetPlayerInt(playerid, "RadarDetect1", PlayerInfo[playerid][pRadarDetect1]);
	} else {
		PlayerInfo[playerid][pRadarDetect2] = 1;
		SetPlayerInt(playerid, "RadarDetect2", PlayerInfo[playerid][pRadarDetect2]);		
	}	
	return 1;
}

DialogCreate:paintjob(playerid) {
    SetPVarInt(playerid, "dialog_tuning", 7);

	return Dialog_Open(playerid, Dialog:paintjob, DIALOG_STYLE_MSGBOX,
		""COLOR_BLUE"Покраска",
		""COLOR_WHITE"Выберите цвет который вы хотите изменить\n"COLOR_RED"Внимание: "COLOR_WHITE"Не все виды транспорта поддерживают второй цвет",
		"> 1 <", "> 2 <"
	);
}

DialogResponse:paintjob(playerid, response, listitem, inputtext[]) {

	if(response) {
		SetPVarInt(playerid, "selecting_colnumber", 1);
	
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Для примерки выбран цвет "COLOR_WHITE"#1");
	} else {
		SetPVarInt(playerid, "selecting_colnumber", 2);

		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Для примерки выбран цвет "COLOR_WHITE"#2");
	}
	Dialog_Show(playerid, Dialog:paintjob_list);
	return 1;
}

DialogCreate:paintjob_list(playerid) {
	SetPVarInt(playerid, "dialog_tuning", 8);

	//new pass_string[3256];

	return Dialog_Open(playerid, Dialog:paintjob_list, DIALOG_STYLE_INPUT,
		""COLOR_BLUE"Покраска",
		"({000000}0{FFFFFF}) ({f4f6f4}1{FFFFFF}) ({2c77a2}2{FFFFFF}) ({840510}3{FFFFFF}) ({26373a}4{FFFFFF}) ({864570}5{FFFFFF}) ({d68e10}6{FFFFFF}) ({4a75b5}7{FFFFFF}) ({bebfc6}8{FFFFFF}) ({5d7070}9{FFFFFF}) ({4a597b}10{FFFFFF})\n  ({656a78}11{FFFFFF}) ({5d7f8f}12{FFFFFF}) ({58595b}13{FFFFFF}) ({d6dbd6}14{FFFFFF}) ({9da2a5}15{FFFFFF}) ({9da2a5}16{FFFFFF}) ({730f18}17{FFFFFF}) ({7c092c}18{FFFFFF}) ({9f9e94}19{FFFFFF}) ({3c4e78}20{FFFFFF})  \n({732f3c}21{FFFFFF}) ({681d39}22{FFFFFF}) ({97928f}23{FFFFFF}) ({525558}24{FFFFFF}) ({3f3e44}25{FFFFFF}) ({a5a9a7}26{FFFFFF}) ({655d5b}27{FFFFFF}) ({655d5b}28{FFFFFF}) ({979691}29{FFFFFF}) ({422021}30{FFFFFF})  \n({60272c}31{FFFFFF}) ({8495aa}32{FFFFFF}) ({767c7c}33{FFFFFF}) ({656565}34{FFFFFF}) ({5b5852}35{FFFFFF}) ({262526}36{FFFFFF}) ({2e3a36}37{FFFFFF}) ({94a397}38{FFFFFF}) ({6b7984}39{FFFFFF}) ({231919}40{FFFFFF})  \n({706660}41{FFFFFF}) ({7c1c2c}42{FFFFFF}) ({600b15}43{FFFFFF}) ({193926}44{FFFFFF}) ({5d1b1e}45{FFFFFF}) ({9d9973}46{FFFFFF}) ({797560}47{FFFFFF}) ({999686}48{FFFFFF}) ({adb1b2}49{FFFFFF}) ({848886}50{FFFFFF})  \n({315144}51{FFFFFF}) ({4d6168}52{FFFFFF}) ({162347}53{FFFFFF}) ({292f4d}54{FFFFFF}) ({7e6457}55{FFFFFF}) ({9da5ad}56{FFFFFF}) ({9d8e70}57{FFFFFF}) ({6e1823}58{FFFFFF}) ({4f6881}59{FFFFFF}) ({9d9e99}60{FFFFFF})  \n({917447}61{FFFFFF}) ({651c26}62{FFFFFF}) ({949e9f}63{FFFFFF}) ({a5a7a7}64{FFFFFF}) ({8f8c47}65{FFFFFF}) ({34191e}66{FFFFFF}) ({6b7a8c}67{FFFFFF}) ({aaad8f}68{FFFFFF}) ({aa9a8f}69{FFFFFF}) ({841f2c}70{FFFFFF})  \n({708299}71{FFFFFF}) ({575952}72{FFFFFF}) ({99a791}73{FFFFFF}) ({601b23}74{FFFFFF}) ({21202c}75{FFFFFF}) ({a5a194}76{FFFFFF}) ({aa9e84}77{FFFFFF}) ({78232c}78{FFFFFF}) ({0d306e}79{FFFFFF}) ({732b3f}80{FFFFFF})  \n({7c7160}81{FFFFFF}) ({731c29}82{FFFFFF}) ({1e2f34}83{FFFFFF}) ({4f332e}84{FFFFFF}) ({7c1b44}85{FFFFFF}) ({2e5c21}86{FFFFFF}) ({3a5a84}87{FFFFFF}) ({632839}88{FFFFFF}) ({a7a28f}89{FFFFFF}) ({b0b1b0}90{FFFFFF})  \n({364155}91{FFFFFF}) ({6e6d70}92{FFFFFF}) ({106a89}93{FFFFFF}) ({214b6b}94{FFFFFF}) ({2c3e57}95{FFFFFF}) ({9a9f9f}96{FFFFFF}) ({6e8497}97{FFFFFF}) ({4d8494}98{FFFFFF}) ({b09a7e}99{FFFFFF}) ({3f6c8f}100{FFFFFF})  \n({1e253c}101{FFFFFF}) ({aa9276}102{FFFFFF}) ({134573}103{FFFFFF}) ({97826e}104{FFFFFF}) ({65686b}105{FFFFFF}) ({105184}106{FFFFFF}) ({a29a84}107{FFFFFF}) ({375694}108{FFFFFF}) ({525660}109{FFFFFF}) ({7b6657}110{FFFFFF})  \n({8c929a}111{FFFFFF}) ({5a7087}112{FFFFFF}) ({473531}113{FFFFFF}) ({44624f}114{FFFFFF}) ({730b29}115{FFFFFF}) ({233458}116{FFFFFF}) ({650f1b}117{FFFFFF}) ({a2adc6}118{FFFFFF}) ({6b5955}119{FFFFFF}) ({9d8b81}120{FFFFFF})  \n({630b1b}121{FFFFFF}) ({5d5d60}122{FFFFFF}) ({614529}123{FFFFFF}) ({731826}124{FFFFFF}) ({1b376e}125{FFFFFF}) ({ec6ab2}126{FFFFFF}) {FFFFFF}\nnВведите номер цвета для примерки",
		"Далее", "Назад"
	);

	/*
	format(small_string, sizeof(small_string), ""COLOR_WHITE"Список цветов:\n\n");strcat(pass_string,small_string);

	for(new i = 0; i < 127; i++) {
		format(small_string, sizeof(small_string), "(%s%d"COLOR_WHITE") ",VehColorHex[i][colorhex], i);strcat(pass_string,small_string);
		if((i % 10) == 0 && i != 0) {
			format(small_string, sizeof(small_string), " \n");
			strcat(pass_string,small_string);
		}
	}

	format(small_string, sizeof(small_string), ""COLOR_WHITE"\n\nВведите номер цвета чтобы примерить его");strcat(pass_string,small_string);

	print(pass_string);

	return Dialog_Open(playerid, Dialog:paintjob_list, DIALOG_STYLE_INPUT,
		""COLOR_BLUE"Покраска",
		pass_string,
		"Далее", "Назад"
	);
	*/
}

DialogResponse:paintjob_list(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return Dialog_Show(playerid, Dialog:tuning_menu);
	}
	new check_color = strval(inputtext);

	if(check_color < 0 || check_color > 127) {
		return Dialog_Show(playerid, Dialog:paintjob_list);
	} else {
		SetPVarInt(playerid, "color_buy", check_color);
	}

	new selected_color = GetPVarInt(playerid, "selecting_colnumber");
	new slot = PlayerInfo[playerid][pSelectedSlot];

	if(slot == 0) {
		return Dialog_Show(playerid, Dialog:paintjob_list);
	}

	ChangeVehiclePaintjob(caridhouse[playerid], 3);

	if(slot == 1) {
		if(selected_color == 1) {
			ChangeVehicleColor(caridhouse[playerid], check_color, PlayerInfo[playerid][pCarCol2]);
		}
		if(selected_color == 2) {
			ChangeVehicleColor(caridhouse[playerid], PlayerInfo[playerid][pCarCol], check_color);	
		}		
	}

	if(slot == 2) {
		if(selected_color == 1) {
			ChangeVehicleColor(caridhouse[playerid], check_color, PlayerInfo[playerid][pCar2Col2]);
		}
		if(selected_color == 2) {
			ChangeVehicleColor(caridhouse[playerid], PlayerInfo[playerid][pCar2Col], check_color);	
		}		
	}

	PlayerPlaySound(playerid, 1134, 0, 0, 0);

	Dialog_Show(playerid, Dialog:paintjob_buy);
	return 1;
}

DialogCreate:paintjob_buy(playerid) {
    SetPVarInt(playerid, "dialog_tuning", 9);

    new selected_color = GetPVarInt(playerid, "color_buy");

    GetCarCost(playerid);

	new cost = GetPVarInt(playerid, "сcost");    

	format(small_string, sizeof(small_string), ""COLOR_WHITE"Оплатить покраску в цвет %s(%d) cтоимостью %d EXP?",
	 VehColorNames[selected_color][colorname], selected_color, cost);

	return Dialog_Open(playerid, Dialog:paintjob_buy, DIALOG_STYLE_MSGBOX,
		""COLOR_BLUE"Покупка",
		small_string,
		"Купить", "Назад"
	);
}

DialogResponse:paintjob_buy(playerid, response, listitem, inputtext[]) {

	new slot = PlayerInfo[playerid][pSelectedSlot];

	if(!response) {
		if(slot == 1) {
			ChangeVehicleColor(caridhouse[playerid], PlayerInfo[playerid][pCarCol], PlayerInfo[playerid][pCarCol2]);
		} else {
			ChangeVehicleColor(caridhouse[playerid], PlayerInfo[playerid][pCar2Col], PlayerInfo[playerid][pCar2Col2]);	
		}

		return Dialog_Show(playerid, Dialog:paintjob_list);
	}

	new selected, cnumber, cost;
	slot = PlayerInfo[playerid][pSelectedSlot];
	selected = GetPVarInt(playerid, "color_buy");
	cnumber = GetPVarInt(playerid, "selecting_colnumber");
	cost = GetPVarInt(playerid, "сcost");

	if(CheckCash(playerid, cost) == false) return Dialog_Show(playerid, Dialog:paintjob_list);

	RemovePlayerEXP(playerid, cost, "Оплата покрасочных работ");

	if(slot == 1) {
		if(cnumber == 1) {
			PlayerInfo[playerid][pCarCol] = selected;
			SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
		}
		if(cnumber == 2) {
			PlayerInfo[playerid][pCarCol2] = selected;
			SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);
		}
	}
	if(slot == 2) {
		if(cnumber == 1) {
			PlayerInfo[playerid][pCar2Col] = selected;
			SetPlayerInt(playerid, "Car2Col", PlayerInfo[playerid][pCar2Col]);
		}
		if(cnumber == 2) {
			PlayerInfo[playerid][pCar2Col2] = selected;
			SetPlayerInt(playerid, "Car2Col2", PlayerInfo[playerid][pCar2Col2]);
		}
	}

	if(slot == 1) {
		ChangeVehicleColor(caridhouse[playerid], PlayerInfo[playerid][pCarCol], PlayerInfo[playerid][pCarCol2]);
	} else {
		ChangeVehicleColor(caridhouse[playerid], PlayerInfo[playerid][pCar2Col], PlayerInfo[playerid][pCar2Col2]);	
	}

	DeletePVar(playerid, "col");
	DeletePVar(playerid, "col1");
	DeletePVar(playerid, "col2");
	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы оплатили покрасочные работы своего транспорта");
	Dialog_Show(playerid, Dialog:tuning_menu);	
	return 1;
}








