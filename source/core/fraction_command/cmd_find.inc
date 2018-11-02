#if defined cmd_find_included
	#endinput
#endif

#define cmd_find_included

CMD:find(playerid, params[]) {
	if(IsPlayerInFraction(playerid) == false) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы не состоите в организации.");
	}
	return Dialog_Show(playerid, Dialog:DIALOG_CMD_FIND);
}

DialogCreate:DIALOG_CMD_FIND(playerid) {
	new 
		Fraction: local_player_fraction = GetPlayerFraction(playerid),
		fraction_title[MAX_FRACTION_TITLE],
		rang_title[MAX_RANG_TITLE],
		total_player;

	GetFractionTitle(PlayerFractionInfo[playerid][PFI_FractionArrayID], fraction_title);
			

	big_string = !"ID\tНик\tДолжность\tСтатус\n";

	foreach(new i: Player) {
		if(GetPlayerFraction(i) == local_player_fraction) {
			GetFractionRangTitle(PlayerFractionInfo[i][PFI_FractionRangArrayID], rang_title);

			format(small_string, sizeof(small_string), "%i\t%s\t%s\t%s\n",
				i,
				PlayerInfo[i][pName],
				rang_title,
				(pl_afk_time[i] >= 3) ? (""COLOR_RED"На паузе") : (""COLOR_GREEN"Активен")
			);
			strcat(big_string, small_string);
			total_player ++;
		}
	}

	if(total_player >= 1) {
		format(small_string, sizeof(small_string), 
			""COLOR_BLUE"Список сотрудников "COLOR_ORANGE"%s", 
				fraction_title
		);

		return Dialog_Open(playerid, Dialog:DIALOG_CMD_FIND, DIALOG_STYLE_TABLIST_HEADERS,
			small_string,
			big_string,
			"Закрыть", ""
		);
	} else {
		return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент, нет игроков в сети.");
	}
}