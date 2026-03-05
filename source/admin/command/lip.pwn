#if defined cmd_lip_included
	#endinput
#endif

#define cmd_lip_included


#define MAX_ACCOUNTS_COMAMND_LIP 				(15) // Максимальное кол-во аккаунтов выводимое через /lip

CMD:lip(playerid, params[]) {
	if(GetPlayerAdminLevel(playerid) < 4) {
		return 0;
	} 
	
	if(params[0] == EOS) {
		return SendClientMessage(playerid, -1, !"Используйте: /lip [IP Адрес/ID Игрока]");
	}	
	
	new 
		bool: isSuccess = false,
		ip_address[MAX_LENGTH_IP];

	if(IsValidIP(params) == 0) {
		new 
			strval_params = strval(params);
		
		if(strval_params >= 0 && strval_params < MAX_PLAYERS) {
			if(GetPlayerLoging(strval_params) == false) {
				return SendClientMessage(playerid, -1, !"Игрок не авторизован.");
			}
			
			strmid(ip_address, PlayerInfo[strval_params][pIP], 0, strlen(PlayerInfo[strval_params][pIP]), MAX_LENGTH_IP);
			isSuccess = true;
		}
	} else {
		strmid(ip_address, params, 0, strlen(params), MAX_LENGTH_IP);
		isSuccess = true;
	}

	if(isSuccess == false) {
		return SendClientMessage(playerid, -1, !"Используйте: /lip [IP Адрес/ID Игрока]");
	}
	
	static 
		string[150 + (MAX_LENGTH_IP * 3) + 2 + 1];

	mysql_format(database, 
		string, sizeof(string), 
		"SELECT Name, LastDate FROM players WHERE IP = '%e' OR LastIP = '%e' OR RegIP = '%e' GROUP BY Name LIMIT %i;", 
			ip_address, 
			ip_address,
			ip_address,
			MAX_ACCOUNTS_COMAMND_LIP
	);
	return mysql_pquery(database, string, "@_ReturnCommandLIP", "is", playerid, ip_address);
}

@_ReturnCommandLIP(playerid, ip[]);
@_ReturnCommandLIP(playerid, ip[]) {
	new rows = cache_get_row_count();

	if(!rows) {
		return SendClientMessage(playerid, -1, !"Аккауны по указанному IP адресу не найдены."); 
	} else {
		static max_string[(MAX_ACCOUNTS_COMAMND_LIP * (MAX_PLAYER_NAME + 20) + 50) / 4],
			name[MAX_PLAYER_NAME],
			last_date[20 + 1],
			format_string[MAX_PLAYER_NAME + 20 + 1];

		max_string = !"Ник\tДата последнего входа\n"COLOR_WHITE"";

		for(new i = 0; i < rows; i++) {
			cache_get_field_content(i, "Name", name);
			cache_get_field_content(i, "LastDate", last_date);

			format(format_string, sizeof(format_string), "%s\t%s\n", name, last_date);
			strcat(max_string, format_string);
		}

		static 
			dialog_header[30 + MAX_LENGTH_IP + 1];

		format(dialog_header, sizeof(dialog_header), ""COLOR_BLUE"Поиск по IP %s (%i)", ip, rows);
		return ShowPlayerDialog(playerid, 4785, DIALOG_STYLE_TABLIST_HEADERS, dialog_header, max_string, "Закрыть", "");
	}
}

//SELECT * FROM `players` WHERE IP = '195.246.106.29' OR LastIP = '195.246.106.29' OR RegIP = '195.246.106.29'