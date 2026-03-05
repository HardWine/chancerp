#if defined anticheat_system_included
	#endinput
#endif

#define anticheat_system_included

#include <anticheat/anticheat_header>
#include <anticheat/anticheat_api>

#include <YSI-Include\YSI\YSI\y_hooks>

hook OnDataBaseConnect() {
	mysql_pquery(database, "SELECT CONVERT(isPC, SIGNED) -1 AS isPC, CONVERT(isAndroid, SIGNED)-1 AS isAndroid, CONVERT(Action, SIGNED)-1 AS Action FROM `config_ac`", "@_LoadAnticheat");
}

@_LoadAnticheat();
@_LoadAnticheat() {
	new 
		rows = cache_get_row_count();

	for(new i = 0; i < rows; i++) {
		AC.Info[i][AC_Action] = cache_get_field_content_int(i, "Action");
		AC.Info[i][AC_ANDROID] = cache_get_field_content_int(i, "isAndroid");
		AC.Info[i][AC_PC] = cache_get_field_content_int(i, "isPC");
	}
}

CMD:anticheat(playerid, params[]) {
	return Dialog_ShowAnticheat(playerid, 0);
}

forward Dialog_ShowAnticheat(const playerid, const page);
public Dialog_ShowAnticheat(const playerid, const page) {
	huge_string = !"№\tНазвание\tСтатус\tДействие\n";

	new i, max_iter;

	if(page == 0) {
		i = 0; 
		max_iter = 30;
	} else {
		i = 30;
		max_iter = 53;
	}

	for(i = 0; i < max_iter; i++) {
		format(small_string, sizeof(small_string), 
			"%i\t(#0%i) %s\tPC = %s | Android = %s\t%s\n", 
				AC.Info[i][AC_ID], 
				AC.Info[i][AC_Value], 
				AC.Info[i][AC_Title],
				AC.PC[AC.Info[i][AC_PC]],
				AC.Android[AC.Info[i][AC_ANDROID]],
				AC.Action[AC.Info[i][AC_Action]]
		);
		strcat(huge_string, small_string);
	}

	if(page == 0) {
		strcat(huge_string, ""COLOR_ORANGE"След. страница");
	} else {
		strcat(huge_string, ""COLOR_ORANGE"Пред. страница");
	}
	return SPD(playerid, DIALOG_SHOW_ANTICHEAT, DIALOG_STYLE_TABLIST_HEADERS, ""COLOR_BLUE"Управление античитом", huge_string, "Далее", "Закрыть");
}

hook OnPlayerDialogShowed(const playerid, const e_DIALOG_IDs:dialogid, const response, const listitem, const inputtext[]) {
	if(dialogid == DIALOG_SHOW_ANTICHEAT) {
		if(!response) {
			return 1;
		} else {
			if(strcmp(inputtext, "След. страница") == 0) {
				Dialog_ShowAnticheat(playerid, 1);
			} else if(strcmp(inputtext, "Пред. страница") == 0) {
				Dialog_ShowAnticheat(playerid, 0);
			} else {
				new 
					strval_inputtext = strval(inputtext);

				for(new i = 0; i < MAX_ANTICHEAT_CODE; i++) {
					if(AC.Info[i][AC_ID] == strval_inputtext) {
						return Dialog_EditAnticheat(playerid, i);
					}
				}
				return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Произошла ошибка.");
			}
		}
	} else if(dialogid == DIALOG_ANTICHEAT_SELECT) {
		if(!response) {
			Dialog_ShowAnticheat(playerid, 0);
		} else {
			new 
				arrayID = GetPVarInt(playerid, "anticheat_arrayid");

			switch(listitem) {
				case 0: {
					Dialog_EditAnticheatAndroid(playerid, arrayID);
				}
				case 1: {
					Dialog_EditAnticheatPC(playerid, arrayID);
				}
				case 2: {
					Dialog_EditAnticheatAction(playerid, arrayID);
				}
			}
		}
	} else if(dialogid == DIALOG_ANTICHEAT_EDIT_ACTION) {
		if(!response) {
			return Dialog_EditAnticheat(playerid, GetPVarInt(playerid, "anticheat_arrayid"));
		} else {
			new 
				arrayID = GetPVarInt(playerid, "anticheat_arrayid");

			AC.SetAction(arrayID, listitem);

			format(small_string, sizeof(small_string), ""COLOR_GREEN"Действие античита %s изменено на %s", AC.Info[arrayID][AC_Title], inputtext);
			return SendClientMessage(playerid, -1, small_string);
		}
	} else if(dialogid == DIALOG_ANTICHEAT_EDIT_PC) {
		if(!response) {
			return Dialog_EditAnticheat(playerid, GetPVarInt(playerid, "anticheat_arrayid"));
		} else {
			new 
				arrayID = GetPVarInt(playerid, "anticheat_arrayid");

			AC.SetStatusPC(arrayID, listitem);
				
			format(small_string, sizeof(small_string), ""COLOR_GREEN"Статус античита %s для ПК изменен на %s", AC.Info[arrayID][AC_Title], inputtext);
			return SendClientMessage(playerid, -1, small_string);	
		}
	} else if(dialogid == DIALOG_ANTICHEAT_EDIT_ANDROID) {
		if(!response) {
			return Dialog_EditAnticheat(playerid, GetPVarInt(playerid, "anticheat_arrayid"));
		} else {
			new 
				arrayID = GetPVarInt(playerid, "anticheat_arrayid");

			AC.SetStatusAndroid(arrayID, listitem);
				
			format(small_string, sizeof(small_string), ""COLOR_GREEN"Статус античита %s для Android изменен на %s", AC.Info[arrayID][AC_Title], inputtext);
			return SendClientMessage(playerid, -1, small_string);	
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

forward Dialog_EditAnticheat(const playerid, const arrayID);
public Dialog_EditAnticheat(const playerid, const arrayID) {
	format(small_string, sizeof(small_string), 
		"(#0%i) %s", 
			AC.Info[arrayID][AC_Value], 
			AC.Info[arrayID][AC_Title]
	);
	SetPVarInt(playerid, "anticheat_arrayid", arrayID);

	return SPD(playerid, 
		DIALOG_ANTICHEAT_SELECT, DIALOG_STYLE_LIST, small_string, 
		"Управление для Android\n\
			Управление для PC\n\
			Изменить действие антчита", 
		"Выбрать", "Назад"
	);
}

forward Dialog_EditAnticheatAction(const playerid, const arrayID);
public Dialog_EditAnticheatAction(const playerid, const arrayID) {
	big_string[0] = EOS;

	for(new i = 0; i < MAX_ANTICHEAT_ACTION; i++) {
		format(small_string, sizeof(small_string), "%s\n", AC.Action[i]);
		strcat(big_string, small_string);
	}

	format(small_string, sizeof(small_string), 
		"(#0%i) %s", 
			AC.Info[arrayID][AC_Value], 
			AC.Info[arrayID][AC_Title]
	);

	return SPD(playerid, 
		DIALOG_ANTICHEAT_EDIT_ACTION, DIALOG_STYLE_LIST, small_string, 
		big_string, 
		"Выбрать", "Назад"
	);
}

forward Dialog_EditAnticheatPC(const playerid, const arrayID);
public Dialog_EditAnticheatPC(const playerid, const arrayID) {
	big_string[0] = EOS;

	for(new i = 0; i < MAX_ANTICHEAT_PC; i++) {
		format(small_string, sizeof(small_string), "%s\n", AC.PC[i]);
		strcat(big_string, small_string);
	}

	format(small_string, sizeof(small_string), 
		"(#0%i) %s", 
			AC.Info[arrayID][AC_Value], 
			AC.Info[arrayID][AC_Title]
	);

	return SPD(playerid, 
		DIALOG_ANTICHEAT_EDIT_PC, DIALOG_STYLE_LIST, small_string, 
		big_string, 
		"Выбрать", "Назад"
	);
}

forward Dialog_EditAnticheatAndroid(const playerid, const arrayID);
public Dialog_EditAnticheatAndroid(const playerid, const arrayID) {
	big_string[0] = EOS;

	for(new i = 0; i < MAX_ANTICHEAT_ANDROID; i++) {
		format(small_string, sizeof(small_string), "%s\n", AC.Android[i]);
		strcat(big_string, small_string);
	}

	format(small_string, sizeof(small_string), 
		"(#0%i) %s", 
			AC.Info[arrayID][AC_Value], 
			AC.Info[arrayID][AC_Title]
	);

	return SPD(playerid, 
		DIALOG_ANTICHEAT_EDIT_ANDROID, DIALOG_STYLE_LIST, small_string, 
		big_string, 
		"Выбрать", "Назад"
	);
}

forward OnCheatDetected(const playerid, const ip_address[], const type, const code);
public OnCheatDetected(const playerid, const ip_address[], const type, const code)
{
	if(GetPlayerAdminLevel(playerid) > 0 || PlayerLogged{playerid} == false) return true;
	if(GetPVarInt(playerid, "ac_flood") > gettime()) {
		return 1;
	}
	SetPVarInt(playerid, "ac_flood", gettime() + 5);

	for(new i = 0; i < MAX_ANTICHEAT_CODE; i++) {
		if(AC.Info[i][AC_Value] == code) {
			if(AC.Info[i][AC_Action] == 0) {
				format(small_string, sizeof(small_string), ""COLOR_RED"Игрок %s(%i) код античита: {FFFFFF}%s", PlayerInfo[playerid][pName], playerid, AC.Info[code][AC_Title]);
				SendAdminMessage(-1, small_string);
				return 1;
			} else if(AC.Info[i][AC_Action] == 1) {
				format(small_string, sizeof(small_string), ""COLOR_RED"Вы были кикнуты по подозрению в читерстве. Код античита: {FFFFFF}%s", AC.Info[code][AC_Title]);
				SendClientMessage(playerid, -1, small_string);
				Kick(playerid);
				return 1;
			}
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerAuthorization(playerid) {

	if(Platform[playerid] == 1) {
		for(new i = 0; i < MAX_ANTICHEAT_CODE; i++) {
			EnableAntiCheatForPlayer(playerid, AC.Info[i][AC_Value], AC.Info[i][AC_PC]);
		}
	}

	if(Platform[playerid] == 0) {
		for(new i = 0; i < MAX_ANTICHEAT_CODE; i++) {
			EnableAntiCheatForPlayer(playerid, AC.Info[i][AC_Value], AC.Info[i][AC_ANDROID]);
		}
	}
}