#if defined binder_system_included
	#endinput
#endif

#define binder_system_included

#define MAX_REDUCTION_LENGTH 			(24)
#define MAX_BINDER_LIST_COMMAND			(15)

new 
	PlayerBinderPage[MAX_PLAYERS] = {0, ...};

CMD:binder(playerid, params[]) {
	PlayerBinderPage[playerid] = 0;
	return ShowPlayerBinder(playerid);
}

CMD:bindercreate(playerid, params[]) {
	new 
		reduction_command[MAX_REDUCTION_LENGTH + 1],
		full_command[100];

	format(small_string, sizeof(small_string), "s[%i]s[100]", MAX_REDUCTION_LENGTH);
	if(sscanf(params, small_string, reduction_command, full_command)) return SendClientMessage(playerid, -1, "Используйте: /bindercreate [Сокращение] [Полная команда]");

	mysql_format(database, small_string, sizeof(small_string), "INSERT INTO `binder`(`PlayerID`, `Reduction`, `FullCommand`) VALUES (%i, '%e', '%e')", PlayerInfo[playerid][pID], reduction_command, full_command);
	mysql_pquery(database, small_string);

	format(small_string, sizeof(small_string), ""COLOR_WHITE"Биндер с сокращением "COLOR_GREEN"%s"COLOR_WHITE" успешно "COLOR_GREEN"создан ", reduction_command);
	return SendClientMessage(playerid, -1, small_string);
}

stock ShowPlayerBinder(const playerid) {
	new 
		current_page = PlayerBinderPage[playerid];

	mysql_format(database, big_string, sizeof(big_string), "SELECT `Reduction`, `FullCommand` FROM `binder` WHERE `PlayerID` = %i LIMIT %i OFFSET %i", PlayerInfo[playerid][pID], MAX_BINDER_LIST_COMMAND + 1, MAX_BINDER_LIST_COMMAND * current_page);
	return mysql_pquery(database, big_string, "@_ShowPlayerBinder", "i", playerid);
}

@_ShowPlayerBinder(const playerid);
@_ShowPlayerBinder(const playerid) {
	new 
		rows = cache_get_row_count();

	if(!rows) {
		if(PlayerBinderPage[playerid] == 0) {
			return SendClientMessage(playerid, -1, ""COLOR_WHITE"У вас отсутвуют биндеры.");
		}
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Произошла ошибка");
	} else {

		big_string[0] = EOS;
		huge_string[0] = EOS; 
		huge_string = !"Сокращение\tПолная команда\n";

		new 
			reduction[MAX_REDUCTION_LENGTH + 1],
			full_command[100];

		for(new i = 0; i < rows; i++) {
			cache_get_field_content(i, "Reduction", reduction);
			cache_get_field_content(i, "FullCommand", full_command);

			format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\t%s\n", reduction, full_command);	
			strcat(huge_string, big_string);

			if(i > MAX_BINDER_LIST_COMMAND - 1) {
				strcat(big_string, ""COLOR_GREEN"+ Следующая страница\n");
				break;
			}
		}

		if(PlayerBinderPage[playerid] >= 1) {
			strcat(big_string, ""COLOR_ORANGE"- Предыдущая страница\n");
		}
		return Dialog_Open(playerid, Dialog:DIALOG_SHOW_PLAYER_BINDER, DIALOG_STYLE_TABLIST_HEADERS,
			""COLOR_BLUE"Биндер: "COLOR_ORANGE"Список всех команд",
			huge_string,
			"Назад", "Закрыть"
		);
	}
}

DialogResponse:DIALOG_SHOW_PLAYER_BINDER(playerid, response, listitem, inputtext[]) {
	if(!response) {
		if(PlayerBinderPage[playerid] != 0) {
			return ShowPlayerBinder(playerid);
		}
		return 1;
	} else {
		if(strcmp(inputtext, "+ Следующая страница", false) == 0) {
			PlayerBinderPage[playerid] = PlayerBinderPage[playerid] + 1;
			return ShowPlayerBinder(playerid);
		} else if(strcmp(inputtext, "- Предыдущая страница", false) == 0) {
			PlayerBinderPage[playerid] = PlayerBinderPage[playerid] - 1;
			return ShowPlayerBinder(playerid);
		} else {
			new 
				reduction[MAX_REDUCTION_LENGTH + 1],
				full_command[100];

			mysql_format(database, big_string, sizeof(big_string), "SELECT `ID`, `Reduction`, `FullCommand` FROM `binder` WHERE `Reduction` = '%e' AND `PlayerID` = %i LIMIT 1", inputtext, PlayerInfo[playerid][pID]);
			mysql_query(database, big_string, true);

			cache_get_field_content(0, "Reduction", reduction);
			cache_get_field_content(0, "FullCommand", full_command);
			SetPVarString(playerid, "full_command", full_command);

			SetPVarInt(playerid, "binder_id", cache_get_field_content_int(0, "ID"));

			format(small_string, sizeof(small_string), ""COLOR_BLUE"Биндек: "COLOR_ORANGE"Команда %s", reduction);
			format(big_string, sizeof(big_string), ""COLOR_WHITE"Сокращение: "COLOR_GREEN"%s\n\
				"COLOR_WHITE"Полная команда: "COLOR_GREEN"%s\n\
				"COLOR_GREEN"Редактировать сокращение\n\
				"COLOR_GREEN"Выполнить команду\n\
				"COLOR_RED"Удалить сокращение\n\
				", 
					reduction, 
					full_command
			);

			return Dialog_Open(playerid, Dialog:DIALOG_SHOW_BINDER_ACTION, DIALOG_STYLE_LIST,
				small_string,
				big_string,
				"Назад", "Закрыть"
			);	
		}
	}
}

DialogResponse:DIALOG_SHOW_BINDER_ACTION(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 1;
	} else {
		new 
			binder_id = GetPVarInt(playerid, "binder_id");

		printf("binder_id = %i ", binder_id);

		switch(listitem) {
			case 2: {
				return Dialog_Open(playerid, Dialog:DIALOG_BINDER_ACTION_EDIT, DIALOG_STYLE_INPUT,
					""COLOR_BLUE"Биндек: "COLOR_ORANGE"Редактирование",
					""COLOR_WHITE"Введите новую команду со всеми параметрами которую будет\n\
					выполнять выбранный Вами биндер",
					"Назад", "Закрыть"
				);	
			}
			case 3: {
				new full_command[100];
				GetPVarString(playerid, "full_command", full_command, 100);
				PC_EmulateCommand(playerid, full_command);
			}
			case 4: {
				mysql_format(database, small_string, sizeof(small_string), "DELETE FROM `binder` WHERE `PlayerID` = %i AND ID = %i LIMIT 1", PlayerInfo[playerid][pID], binder_id);
				printf("%i", small_string);
				mysql_pquery(database, small_string);

				SendClientMessage(playerid, -1, ""COLOR_WHITE"Выбранный биндер удален из списка всех Ваших биндеров");
			}
		}
	}
	return 1;
}

DialogResponse:DIALOG_BINDER_ACTION_EDIT(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 1;
	} else {
		new 
			binder_id = GetPVarInt(playerid, "binder_id");

		printf("binder_id = %i ", binder_id);

		mysql_format(database, small_string, sizeof(small_string), "UPDATE `binder` SET `FullCommand` = '%e' WHERE `PlayerID` = %i AND `ID` = %i LIMIT 1", inputtext, PlayerInfo[playerid][pID], binder_id);
		mysql_pquery(database, small_string);

		SendClientMessage(playerid, -1, ""COLOR_WHITE"Выбранный биндер успешно обновлен");
	}
	return 1;
}

CMD:b(playerid, params[]) {
	new 
		reduction_command[MAX_REDUCTION_LENGTH + 1];

	format(small_string, sizeof(small_string), "s[%i]", MAX_REDUCTION_LENGTH);

	if(sscanf(params, small_string, reduction_command)) {
		return SendClientMessage(playerid, -1, "Используйте: /b [Сокращение]");
	}

	mysql_format(database, 
		small_string, sizeof(small_string), 
		"SELECT `FullCommand` FROM `binder` WHERE `PlayerID` = %i AND `Reduction` = '%e' LIMIT 1;", 
			PlayerInfo[playerid][pID],
			reduction_command
	);
	mysql_query(database, small_string, true);

	new 
		rows = cache_get_row_count();

	if(!rows) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Указанно неверное сокращение команды");
	} else {
		new 
			full_command[100];

		cache_get_field_content(0, "FullCommand", full_command);
		SetPVarString(playerid, "full_commands", full_command);
		SetPVarInt(playerid, "is_binder", 1);
		return true;
	}
}

@_ExucutePlayerBinder(const playerid);
@_ExucutePlayerBinder(const playerid) {
	new 
		rows = cache_get_row_count();

	if(rows) {
		new 
			full_command[100];

		cache_get_field_content(0, "FullCommand", full_command);
		PC_EmulateCommand(playerid, full_command);
		printf("full_command full_command = %s", full_command);
		new cmd_1[100],
		cmd_2[100];

		sscanf(full_command, "s[24]s[100]", cmd_1, cmd_2);
		printf("cmd_1 = %s cmd_2 = %s", cmd_1, cmd_2);
		format(small_string, sizeof(small_string), "pc_cmd_%s", "sis", cmd_1);
		CallLocalFunction("pc_cmd_%s(%i, %s)", "sis", cmd_1, playerid, cmd_2);
		return true;
	}
}