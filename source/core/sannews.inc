#if defined news_features_included
	#endinput
#endif

#define news_features_included



CMD:onair(playerid, params[]) {

	if(GetPlayerFraction(playerid) != FRACTION_NEWS) return 1;
	if(GetPlayerJobDayStatus(playerid) == false)
	{
		return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
	}
	if(PlayerInfo[playerid][pRank] < 4) return SendClientMessage(playerid, -1, "Вести прямые эфиры можно с 4 ранга");
	if(onair == 1) {
		if(GetPVarInt(playerid, "onair_master")) {
			DeletePVar(playerid, "onair_master");
			onair = 0;
			SendFamilyMessage(FRACTION_NEWS, -1, ""COLOR_ORANGE"Ведущий прервал прямой эфир");
		}
		foreach(new i: Player) {
			DeletePVar(playerid, "onair");
		}
		return 1;
	}
	if(onair != 1) {
		if(!IsPlayerInRangeOfPoint(playerid, 40, 1175.2021,-1180.5349,87.0787)) {
			if(!IsPlayerInRangeOfPoint(playerid, 40, 927.6644,-1677.8931,1349.5969)) {
				new vehicle_owner;
				for(new i = 0; i < sizeof(VehicleInfo); i++) {
				if(VehicleInfo[i][VI_VehicleID] == GetPlayerVehicleID(playerid)) {
				vehicle_owner = VehicleInfo[i][VI_Owner];
				}
				}
				if(vehicle_owner != VO_FRACTION_NEWS) {
				return SendClientMessage(playerid, -1, "Необходимо находится в офисе San News или в фракционном транспорте");
				}
			}
		}	
		printf("[Эфир] Участник : %s", PlayerInfo[playerid][pName]);
		SPD(playerid, dKickMessage,  DIALOG_STYLE_MSGBOX, ""COLOR_RED"Вы в эфире!",
		""COLOR_RED"Вы вышли в прямой эфир, все что вы отправите в чат увидят все игроки\nЧтобы покинуть эфир, покиньте офис/транспорт San News и напишите в чат","Ок", "");			
		if(!sscanf(params, "d", params[0])) {
			printf("[Эфир] Участник : %s", PlayerInfo[params[0]][pName]);
			if(PlayerLogged{params[0]} == false || !IsPlayerConnected(params[0])) return SendClientMessage(playerid, -1, "Указанный игрок не авторизован");
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"Ведущий {FFFFFF}%s"COLOR_ORANGE" начал эфир с гостем {FFFFFF}%s", PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName]);
			if(!IsPlayerInRangeOfPoint(params[0], 40, 1175.2021,-1180.5349,87.0787)) {
				if(!IsPlayerInRangeOfPoint(params[0], 40, 927.6644,-1677.8931,1349.5969)) {
					new vehicle_owner;
					for(new i = 0; i < sizeof(VehicleInfo); i++) {
					if(VehicleInfo[i][VI_VehicleID] == GetPlayerVehicleID(params[0])) {
					vehicle_owner = VehicleInfo[i][VI_Owner];
					}
					}
					if(vehicle_owner != VO_FRACTION_NEWS) {
					return SendClientMessage(playerid, -1, "Участник эфира должен быть в офисе San News или в фракционном транспорте");
					}
				}
			}	
			SetPVarInt(params[0], "onair", 1);
			SPD(params[0], dKickMessage,  DIALOG_STYLE_MSGBOX, ""COLOR_RED"Вы в эфире!",
			""COLOR_RED"Вы вышли в прямой эфир, все что вы отправите в чат увидят все игроки\nЧтобы покинуть эфир, покиньте офис/транспорт San News и напишите в чат","Ок", "");			
		} else {
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"Ведущий {FFFFFF}%s"COLOR_ORANGE" начал прямой эфир", PlayerInfo[playerid][pName]);
		}
		SendFamilyMessage(FRACTION_NEWS, -1, small_string);
		
		onair = 1;
		SetPVarInt(playerid, "onair", 1);
		SetPVarInt(playerid, "onair_master", 1);
	}
	return 1;
}

CMD:stopair(playerid, params[]) {

	if(GetPlayerFraction(playerid) != FRACTION_NEWS) return 1;
	if(PlayerInfo[playerid][pRank] < 9) return SendClientMessage(playerid, -1, "Останавливать эфиры можно с 9 ранга");
	onair = 0;

	format(small_string, sizeof(small_string), ""COLOR_ORANGE"{FFFFFF}%s"COLOR_ORANGE" прервал эфир", PlayerInfo[playerid][pName]);
	SendFamilyMessage(FRACTION_NEWS, -1, small_string);	

	foreach(new i: Player) {
		DeletePVar(playerid, "onair");
		DeletePVar(playerid, "onair_master");
	}
	return 1;
}
CMD:mutefm(playerid) {
	if(GetPVarInt(playerid,"fmflood") > gettime()){ SendClientMessage(playerid, -1, ""COLOR_RED"Пожалуйста, не флудите!"); return false; }
	SetPVarInt(playerid,"fmflood",gettime() + 3);
	if(GetPlayerAdminLevel(playerid) > 0) return SendClientMessage(playerid, -1, ""COLOR_RED"А следить за тем что всем отправляется кто будет, А?");

	if(PlayerInfo[playerid][pParrot] == 0) return SendClientMessage(playerid, -1, ""COLOR_RED"У вас нет попугая");
	if(GetPVarInt(playerid, "fm")) {
		DeletePVar(playerid, "fm");
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы включили сообщения от {FFFFFF}San News");
		return 1;
	}
	SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы выключили сообщения от {FFFFFF}San News");

	SetPVarInt(playerid, "fm", 1);	
	return 1;
}
CMD:forecast(playerid) {
	if(IsPlayerInRangeOfPoint(playerid, 5.0, -2521.1042,-624.9525,132.7841)) {
		if(GetPlayerFraction(playerid) == FRACTION_NEWS) {
			if(forecast == -1) {
				if(GetPlayerJobDayStatus(playerid) == false)
				{
					return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
				}
				
				AddPlayerEXP(playerid, 250, "Прогнал погоды от San News");
				forecast = 1;
				new kek = RandomEx(15,35);
				new lel = RandomEx(1,15);
				new w_str_0[144];
				new w_str_1[144];
				ShowPlayerDialog(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, ""COLOR_GREEN"Прогноз погоды", "{FFFFFF}Вы получили прогоноз погоды и отправили его в студию", "Закрыть", "");
				switch(weather) {
					case 0..7: format(w_str_0, sizeof(w_str_0), "{FF3855}(Новости погоды){FFFFFF} Cейчас в San Andreas солнечно, +21. Местное время: %d:%02d", hour, minute);
					case 8: format(w_str_0, sizeof(w_str_0), "{FF3855}(Новости погоды){FFFFFF} Cейчас в San Andreas облачно, +15. Местное время: %d:%02d", hour, minute);
					case 9: format(w_str_0, sizeof(w_str_0), "{FF3855}(Новости погоды){FFFFFF} Cейчас в San Andreas туман, +19. Местное время: %d:%02d", hour, minute);
					case 10: format(w_str_0, sizeof(w_str_0), "{FF3855}(Новости погоды){FFFFFF} Cейчас в San Andreas ясно, +19. Местное время: %d:%02d", hour, minute);
					case 11: format(w_str_0, sizeof(w_str_0), "{FF3855}(Новости погоды){FFFFFF} Cейчас в San Andreas жарко, +26. Местное время: %d:%02d", hour, minute);
					case 12..15: format(w_str_0, sizeof(w_str_0), "{FF3855}(Новости погоды){FFFFFF} Cейчас в San Andreas обычная погода, +%d. Местное время: %d:%02d", hour, minute,kek);
					case 16..20: format(w_str_0, sizeof(w_str_0), "{FF3855}(Новости погоды){FFFFFF} Cейчас в San Andreas пасмурно, +%d. Местное время: %d:%02d", hour, minute,lel);
				}
				switch(newweather) {
					case 0..7: format(w_str_1, sizeof(w_str_1), "{FF3855}(Новости погоды){FFFFFF} В следующем часу ожидается солнечная погода, +21");
					case 8: format(w_str_1, sizeof(w_str_1), "{FF3855}(Новости погоды){FFFFFF} В следующем часу по нашим прогнозам погода будет облачной, +15");
					case 9: format(w_str_1, sizeof(w_str_1), "{FF3855}(Новости погоды){FFFFFF} В следующем часу будет небольшой туман, +19");
					case 10: format(w_str_1, sizeof(w_str_1), "{FF3855}(Новости погоды){FFFFFF} В следующем часу будет ясное небо, +19");
					case 11: format(w_str_1, sizeof(w_str_1), "{FF3855}(Новости погоды){FFFFFF} В следующем часу будет жарко, +26");
					case 12..15: format(w_str_1, sizeof(w_str_1), "{FF3855}(Новости погоды){FFFFFF} В следующем часу будет отличная погода, +%d", hour, minute,kek);
					case 16..20: format(w_str_1, sizeof(w_str_1), "{FF3855}(Новости погоды){FFFFFF} В следующем часу будет пасмурная погода, +%d", hour, minute,lel);
				}						
				foreach(new i: Player) {
					if(GetPVarInt(i, "fm")) continue;
					SendClientMessage(i, -1, w_str_0);
					SendClientMessage(i, -1, w_str_1);
				}					
			}
		}
	}
}

stock onair_offline(playerid) {
	if(GetPVarInt(playerid, "onair_master")) {
		format(small_string, sizeof(small_string), ""COLOR_ORANGE"Ведущий {FFFFFF}%s"COLOR_ORANGE" прервал прямой эфир (вышел из игры)", PlayerInfo[playerid][pName]);
		SendFamilyMessage(FRACTION_NEWS, -1, small_string);
		onair = -1;
	}
	return 1;
}