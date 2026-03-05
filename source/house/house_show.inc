#if defined house_show_included
	#endinput
#endif

#define house_show_included

#include <YSI-Include\YSI\YSI\y_hooks>

static 
	Player.PageHouse[MAX_PLAYERS char];

hook OnPlayerConnect(playerid) {
	Player.PageHouse{playerid} = 1;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	Player.PageHouse{playerid} = 1;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

stock House.ShowListForPlayer(const playerid, const start_point = 0, const limit = 30) {
	big_string[0] = EOS;
	big_string = !"Информация о домах\n\n";

	small_string[0] = EOS;

	new max_iter = start_point + limit;
	if(max_iter > MAX_HOUSE) {
		max_iter = MAX_HOUSE;
	}
	printf("start = %i max = %i", start_point, max_iter);
	for(new i = start_point; i < max_iter; i++) {
		format(small_string, sizeof(small_string), 
			"Дом %i. Цена %i Владелец %i\n", 
			HouseInfo[i][E_HOUSE_ID], 
			HouseInfo[i][E_HOUSE_PRICE], 
			HouseInfo[i][E_HOUSE_OWNER] 
		);
		strcat(big_string, small_string);
	}
	ShowPlayerDialog(playerid, DIALOG_SHOW_ALL_HOME, DIALOG_STYLE_MSGBOX, "Тест", big_string, "Вперед", "Назад");
	return 1;
}

CMD:test_show(playerid, params[]) {
	Player.PageHouse{playerid} = 1;
	return House.ShowListForPlayer(playerid, Player.PageHouse{playerid} * 30, 30);
}

hook OnPlayerDialogShowed(const playerid, const dialogid, const response, const listitem, const inputtext[]) {
	if(dialogid == DIALOG_SHOW_ALL_HOME) {
		if(!response) {
			if(Player.PageHouse{playerid} == 1) {
				House.ShowListForPlayer(playerid, 0, 30);
				return Y_HOOKS_BREAK_RETURN_1;
			}
			Player.PageHouse{playerid} --;
			House.ShowListForPlayer(playerid, Player.PageHouse{playerid} * 30, 30);
			return Y_HOOKS_BREAK_RETURN_1;
		} else {
			Player.PageHouse{playerid} ++;
			printf("page = %i", Player.PageHouse{playerid});
			House.ShowListForPlayer(playerid, Player.PageHouse{playerid} * 30, 30);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}