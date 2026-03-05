#if defined phone_book_system_included
	#endinput
#endif

#define phone_book_system_included

#define MAX_PHONE_BOOK_LIST_CONTACT		(20)

new 
	PlayerPhoneBookPage[MAX_PLAYERS] = {0, ...};

// Добавление контакта в телефонную книжку
CMD:addcontact(playerid, params[]) {
	if(PlayerInfo[playerid][pDevice] == 0) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Вам нужен пейджер или телефон. Купите его в магазине");
	}
	if(GetPVarInt(playerid, "togphone") == 1) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Ваш телефон выключен");
	}
	return Dialog_Show(playerid, Dialog:DIALOG_CMD_ACCCONTACT);
}

DialogCreate:DIALOG_CMD_ACCCONTACT(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_CMD_ACCCONTACT, DIALOG_STYLE_INPUT,
		""COLOR_BLUE"Телефонная книжка: "COLOR_ORANGE"Добавление контакта",
		""COLOR_WHITE"Введите номер контакта, для добавления его в записную\n\
		книжку",
		"Далее", "Закрыть"
	);
}

DialogResponse:DIALOG_CMD_ACCCONTACT(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return true;
	} else {
		new 
			phone_number = strval(inputtext);

		mysql_format(database, small_string, sizeof(small_string), "SELECT `Name` FROM `players` WHERE `SIMCard` = %i LIMIT 1", phone_number);
		return mysql_pquery(database, small_string, "@_AddPlayerContactPhoneBook", "ii", playerid, phone_number);
	}
}

@_AddPlayerContactPhoneBook(const playerid, const phone_number);
@_AddPlayerContactPhoneBook(const playerid, const phone_number) {
	new 
		rows = cache_get_row_count();

	if(!rows) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Данный номер не зарегистирован");
	} else {
		new 
			phone_number_name[MAX_PLAYER_NAME + 1];

		cache_get_field_content(0, "Name", phone_number_name);

		mysql_format(database, small_string, sizeof(small_string), "INSERT INTO `phone_book`(`PlayerID`, `Number`) VALUES (%i, %i)", PlayerInfo[playerid][pID], phone_number);
		if(mysql_pquery(database, small_string)) {
			format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы добавили в свою записную книжку игрока "COLOR_GREEN"%s"COLOR_WHITE" с номером "COLOR_GREEN"%i", phone_number_name, phone_number);
			SendClientMessage(playerid, -1, small_string);
		}
	}
	return 1;
}

// Отображение контактов

CMD:showcontact(playerid, params[]) {
	if(PlayerInfo[playerid][pDevice] == 0) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Вам нужен пейджер или телефон. Купите его в магазине");
	}
	if(GetPVarInt(playerid, "togphone") == 1) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Ваш телефон выключен");
	}

	PlayerPhoneBookPage[playerid] = 0;
	return ShowPlayerContactPhoneBook(playerid);
}

stock ShowPlayerContactPhoneBook(const playerid) {
	new 
		current_page = PlayerPhoneBookPage[playerid];

	mysql_format(database, big_string, sizeof(big_string), "SELECT phone_book.Number, players.Name FROM phone_book RIGHT OUTER JOIN players ON players.SIMcard = phone_book.Number WHERE phone_book.PlayerID = %i LIMIT %i OFFSET %i", PlayerInfo[playerid][pID], MAX_PHONE_BOOK_LIST_CONTACT + 1, MAX_PHONE_BOOK_LIST_CONTACT * current_page);
	return mysql_pquery(database, big_string, "@_ShowPlayerPhoneBookContact", "i", playerid);
}

@_ShowPlayerPhoneBookContact(const playerid);
@_ShowPlayerPhoneBookContact(const playerid) {
	new 
		rows = cache_get_row_count();

	if(!rows) {
		if(PlayerPhoneBookPage[playerid] == 0) {
			return SendClientMessage(playerid, -1, ""COLOR_WHITE"В вашей записной книжке отсутсвуют контакты. Добавьте свой первый контакт "COLOR_GREEN"командой /addcontact");
		}
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Произошла ошибка");
	} else {

		small_string[0] = EOS;
		huge_string[0] = EOS;

		huge_string = "Контакт\tНомер\n";

		new 
			contact_name[MAX_PLAYER_NAME + 1];

		for(new i = 0; i < rows; i++) {
			cache_get_field_content(i, "Name", contact_name);

			format(small_string, sizeof(small_string), ""COLOR_WHITE"%s\t"COLOR_GREEN"%i\n", contact_name, cache_get_field_content_int(i, "Number"));	
			strcat(huge_string, small_string);

			if(i > MAX_PHONE_BOOK_LIST_CONTACT - 1) {
				strcat(huge_string, ""COLOR_GREEN"Следующая страница\n");
				break;
			}
		}

		if(PlayerPhoneBookPage[playerid] >= 1) {
			strcat(huge_string, ""COLOR_ORANGE"Предыдущая страница\n");
		}
		return Dialog_Open(playerid, Dialog:DIALOG_SHOW_PLAYER_CONTACT, DIALOG_STYLE_TABLIST_HEADERS,
			""COLOR_BLUE"Телефонная книжка: "COLOR_ORANGE"Список контактов",
			huge_string,
			"Назад", "Закрыть"
		);
	}
}

DialogResponse:DIALOG_SHOW_PLAYER_CONTACT(playerid, response, listitem, inputtext[]) {
	if(!response) {
		if(PlayerPhoneBookPage[playerid] != 0) {
			return ShowPlayerContactPhoneBook(playerid);
		}
		return 1;
	} else {
		if(strcmp(inputtext, "Следующая страница", false) == 0) {
			PlayerPhoneBookPage[playerid] = PlayerPhoneBookPage[playerid] + 1;
			return ShowPlayerContactPhoneBook(playerid);
		} else if(strcmp(inputtext, "Предыдущая страница", false) == 0) {
			PlayerPhoneBookPage[playerid] = PlayerPhoneBookPage[playerid] - 1;
			return ShowPlayerContactPhoneBook(playerid);
		} else {
			new 
				contact_name[MAX_PLAYER_NAME + 1],
				contact_number;

			mysql_format(database, big_string, sizeof(big_string), "SELECT phone_book.Number, players.Name FROM phone_book LEFT OUTER JOIN players ON players.SIMcard = phone_book.Number WHERE players.Name = '%e' LIMIT 1", inputtext);
			mysql_query(database, big_string, true);

			contact_number = cache_get_field_content_int(0, "Number");
			cache_get_field_content(0, "Name", contact_name);
			
			SetPVarInt(playerid, "contact_phone_number", contact_number);

			format(small_string, sizeof(small_string), ""COLOR_BLUE"Телефонная книжка: "COLOR_ORANGE"Контакт %s", contact_name);
			format(big_string, sizeof(big_string), ""COLOR_WHITE"Контакт: "COLOR_GREEN"%s\n\
				"COLOR_WHITE"Номер: "COLOR_GREEN"%i\n\
				"COLOR_RED"Удалить контакт", 
					contact_name, 
					contact_number
			);

			return Dialog_Open(playerid, Dialog:DIALOG_SHOW_CONTACT_ACTION, DIALOG_STYLE_LIST,
				small_string,
				big_string,
				"Назад", "Закрыть"
			);	
		}
	}
}


DialogResponse:DIALOG_SHOW_CONTACT_ACTION(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 1;
	} else {
		new 
			phone_number = GetPVarInt(playerid, "contact_phone_number");

		printf("contact_phone_number = %i ", phone_number);

		switch(listitem) {
			case 0: {

			} 
			case 1: {

			}
			case 2: {
				mysql_format(database, small_string, sizeof(small_string), "DELETE FROM `phone_book` WHERE `PlayerID` = %i AND `Number` = %i LIMIT 1", PlayerInfo[playerid][pID], phone_number);
				printf("%i", small_string);
				mysql_pquery(database, small_string);

				format(small_string, sizeof(small_string), ""COLOR_WHITE"Контакт с номером "COLOR_GREEN"%i"COLOR_WHITE" удален из Вашей записной книжки", phone_number);
				SendClientMessage(playerid, -1, small_string);
			}
		}
	}
	return 1;
}
