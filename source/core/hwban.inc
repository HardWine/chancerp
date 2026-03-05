#if defined _hwban_included
	#endinput
#endif
#define _hwban_included

new hwid_banned[9][45];
new pc_disabled = 0;

CMD:options(playerid) {
	if(GetPlayerAdminLevel(playerid) < 5) return true;
	SendClientMessage(playerid, -1, (pc_disabled == 0) ? (""COLOR_GREEN"Вход ПК игрокам включен") : (""COLOR_RED"Вход ПК игрокам ограничен"));
	SendClientMessage(playerid, -1, (ATTACK_MODE == 0) ? (""COLOR_GREEN"Attack-Mode отключен") : (""COLOR_RED"Attack-Mode активирован"));
	return 1;
}

CMD:xmode(playerid) {
	if(GetPlayerAdminLevel(playerid) < 5) return true;
	if(pc_disabled == 0) {
		pc_disabled = 1;

		format(small_string, sizeof(small_string), ""COLOR_RED"Администратор {FFFFFF}%s"COLOR_RED" ограничил вход ПК-игрокам", PlayerInfo[playerid][pName]);
		SendAdminMessage(-1, small_string);

	} else {
		pc_disabled = 0;

		format(small_string, sizeof(small_string), ""COLOR_GREEN"Администратор {FFFFFF}%s"COLOR_GREEN" включил вход ПК-игрокам", PlayerInfo[playerid][pName]);
		SendAdminMessage(-1, small_string);		
	}
	return 1;
}

stock null_HWBans() {
	for(new i = 0; i < 8; i++) {
		format(hwid_banned[i], 45, "-1");
	}
}

stock checkHWBanned(playerid) {
	for(new i = 0; i < 8; i++) {
		if(!strcmp(Client[playerid], hwid_banned[i])) {
			format(small_string, sizeof(small_string), ""COLOR_RED"%s был отключен при входе {FFFFFF}(бан серийного адреса)",  PlayerInfo[playerid][pName]);
			SendAdminMessage(-1, small_string);			
			return 1;
		}
	}
	return 0;
}