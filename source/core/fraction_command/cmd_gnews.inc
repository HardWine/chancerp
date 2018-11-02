#if defined cmd_gnews_included
	#endinput
#endif

#define cmd_gnews_included

CMD:gnews(playerid, params[]) {
	if(IsPlayerInFraction(playerid) == false) {
		return SendClientMessage(playerid, -1, "Вам недоступна данная команда.");
	}

	if(FractionRangInfo[PlayerFractionInfo[playerid][PFI_FractionRangArrayID]][FRI_isGnews] == 0) {
		return SendClientMessage(playerid, -1, "Вам недоступна данная команда.");
	}

	new 
		text[80];

	if(sscanf(params, "s[80]", text)) {
		return SendClientMessage(playerid, -1, "Используйте: /gnews [Текст]");
	}

	format(small_string, sizeof(small_string), 
		""COLOR_BLUE"[Гос волна] %s(%i): %s", 
			PlayerInfo[playerid][pName], 
			playerid, 
			text
	);
	return SendClientMessageToAll(-1, small_string);
}