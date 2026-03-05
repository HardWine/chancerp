#if defined mp_functions_included
	#endinput
#endif

#define mp_functions_included

new
	Iterator:PlayersMP<MAX_PLAYERS>;

new 
	Float: MP_Pos_X,
	Float: MP_Pos_Y,
	Float: MP_Pos_Z,
	Float: MP_Pos_Angle;

new 
	MP_Pos_Inter,
	MP_Pos_World;

new 
	bool: Mp_Enable = false;

CMD:tpmp(playerid, params[]) {
	if(Iter_Contains(PlayersMP, playerid)) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже телепортировались на текущее мероприятие");
	} else {
		if(Mp_Enable == true) {
			Iter_Add(PlayersMP, playerid);
			new 
				Float: MpPos[4];

			MpPos[0] = MP_Pos_X;
			MpPos[1] = MP_Pos_Y;
			MpPos[2] = MP_Pos_Angle;

			MpPos[0] = MpPos[0] + (5.0 * floatsin(-MpPos[2], degrees));
			MpPos[1] = MpPos[1] + (5.0 * floatcos(-MpPos[2], degrees));

			SetPlayerPos(playerid, MpPos[0], MpPos[1], MP_Pos_Z);
			SetPlayerFacingAngle(playerid, MP_Pos_Angle);
			SetPlayerInterior(playerid, MP_Pos_Inter);
			SetPlayerVirtualWorld(playerid, MP_Pos_World);

			Dialog_Message(playerid, 
				""COLOR_BLUE"Мероприятие", 
				""COLOR_WHITE"Вы телепортировались к месту проведения мероприятия\n\
				Соблюдайте пожалуйста правила сервера и не создавайте помех\n\
				"COLOR_BLUE"Ждите дальнейших указаний от администраторов!", 
				"Закрыть"
			);
		} else {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"В данный момент телепорт на мероприятие закрыт");
		}
	}
	return 1;
}
CMD:mp(playerid, params[]) {
	if(GetPlayerAdminLevel(playerid) >= 3) {
		return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP);
	} else return 1;
}

DialogCreate:DIALOG_CMD_MP(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_CMD_MP, DIALOG_STYLE_LIST,
		""COLOR_BLUE"Панель МП", 
		""COLOR_WHITE"1. Открыть телепорт на мероприятие\n\
		2. Закрыть телепорт на мероприятие\n\
		3. Раздать оружие\n\
		4. Раздать жизни\n\
		5. Раздать бронижелеты\n\
		6. Забрать бронижелеты\n\
		7. Забрать оружие\n\
		8. Разделить на команды",
		"Выбрать", "Закрыть"
	);
}

DialogResponse:DIALOG_CMD_MP(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		switch(listitem) {
			case 0: {
				if(Mp_Enable == true) {
					SendClientMessage(playerid, -1, ""COLOR_ORANGE"Телепорт на мероприятие уже открыт");
					return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP);
				} else {
					foreach(new i:PlayersMP) {
						Iter_Remove(PlayersMP, i);
					}
					Mp_Enable = true;
					GetPlayerPos(playerid, MP_Pos_X, MP_Pos_Y, MP_Pos_Z);
					GetPlayerFacingAngle(playerid, MP_Pos_Angle);
					MP_Pos_Inter = GetPlayerInterior(playerid);
					MP_Pos_World = GetPlayerVirtualWorld(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Точка телепортации игроков создана");
					SendClientMessage(playerid, -1, "Телепорт на мероприятие "COLOR_GREEN"открыт"COLOR_WHITE". Оповестите об этом игроков.");
					SendClientMessage(playerid, -1, "Команда для телепортации на мероприятие для игроков - /tpmp");
					return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP);
				}
			}
			case 1: {
				if(Mp_Enable == false) {
					SendClientMessage(playerid, -1, ""COLOR_ORANGE"Телепорт на мероприятие не был открыт");
					return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP);
				} else {
		
					Mp_Enable = false;
					SendClientMessage(playerid, -1, ""COLOR_RED"Телепорт на мероприятие закрыт");

					foreach(new i:PlayersMP) {
						Iter_SafeRemove(PlayersMP, i, i);
					}						
					return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP);
				}
			}
			case 2: {
				return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP_GIVE_GIN);
			}
			case 3: {
				foreach(new i:PlayersMP) {
					SetPlayerHealth(i, 100.00);
					SendClientMessage(i, -1, ""COLOR_GREEN"Администратор востановил Вам здоровье");
				}
			}
			case 4: {
				foreach(new i:PlayersMP) {
					SetPlayerArmour(i, 100.00);
					SendClientMessage(i, -1, ""COLOR_GREEN"Администратор выдал Вам бронижелет");
				}
			}
			case 5: {
				foreach(new i:PlayersMP) {
					SetPlayerArmour(i, 0.00);
					SendClientMessage(i, -1, ""COLOR_GREEN"Администратор забрал у Вас бронижелет");
				}
			}
			case 6: {
				foreach(new i:PlayersMP) {
					ResetPlayerWeapons(i);
					SendClientMessage(i, -1, ""COLOR_GREEN"Администратор забрал у Вас оружие");
				}
			}
			case 7: {
				return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP_SET_SKIN);
			}
			default: {
				return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP);
			}
		}
	}
	return 1;
}

DialogCreate:DIALOG_CMD_MP_GIVE_GIN(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_CMD_MP_GIVE_GIN, DIALOG_STYLE_INPUT,
		"Выдача оружия", 
		""COLOR_WHITE"Укажите через запятую ID оружия и количество патронов\n\
		Пример: 31, 500",
		"Далее", "Назад"
	);
}

DialogResponse:DIALOG_CMD_MP_GIVE_GIN(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP);
	} else {
		new 
			weapon,
			ammo;

		if(sscanf(inputtext, "p<,>dd", weapon, ammo)) {
			return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP_GIVE_GIN);
		}

		foreach(new i:PlayersMP) {
			GivePlayerWeapon(i, weapon, ammo);
			SendClientMessage(i, -1, ""COLOR_GREEN"Администратор выдал Вам оружие");
		}
		return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP);
	}
}

DialogCreate:DIALOG_CMD_MP_SET_SKIN(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_CMD_MP_SET_SKIN, DIALOG_STYLE_INPUT,
		"Команды", 
		""COLOR_WHITE"Укажите через запятую ID двух скинов\n\
		Пример: 100, 255",
		"Далее", "Назад"
	);
}

DialogResponse:DIALOG_CMD_MP_SET_SKIN(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP);
	} else {
		new 
			skin_1,
			skin_2;

		if(sscanf(inputtext, "p<,>dd", skin_1, skin_2)) {
			return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP_SET_SKIN);
		}

		new 
			value = 0;

		foreach(new i:PlayersMP) {
			if(value == 0) {
				value = 1;
				SetPlayerSkin(i, skin_1);
				SetPlayerColor(i, TRIAD_COLOR);
			} else if(value == 1) {
				value = 0;
				SetPlayerSkin(i, skin_2);
				SetPlayerColor(i, LSPD_COLOR);
			}
			SendClientMessage(i, -1, ""COLOR_GREEN"Администратор выдал Вам временную одежду");
		}
		return Dialog_Show(playerid, Dialog:DIALOG_CMD_MP);
	}
}