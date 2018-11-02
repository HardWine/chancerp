#if defined cmd_rang_included
	#endinput
#endif

#define cmd_rang_included

CMD:rang(playerid, params[]) {
	if(IsPlayerInFraction(playerid) == false) {
		return SendClientMessage(playerid, -1, "Вам недоступна данная команда.");
	}

	if(FractionRangInfo[PlayerFractionInfo[playerid][PFI_FractionRangArrayID]][FRI_isRang] == 0) {
		return SendClientMessage(playerid, -1, "Вам недоступна данная команда.");
	}

	new 
		targetid,
		sub[2];

	if(sscanf(params, "us[2]", targetid, sub)) {
		return SendClientMessage(playerid, -1, "Используйте: /rang [ID Игрока] [+ - повысить ранг; - - понизить ранг]");
	}

	if(IsPlayerConnected(targetid) == 0) {
		return SendClientMessage(playerid, -1, "Игрок не авторизован.");
	}

	if(PlayerFractionInfo[targetid][PFI_FractionRangArrayID] > PlayerFractionInfo[playerid][PFI_FractionRangArrayID]) {
		return SendClientMessage(playerid, -1, "Вы не можете изменить ранг игроку старше Вас по должности.");
	}
	if(FractionRangInfo[PlayerFractionInfo[targetid][PFI_FractionRangArrayID]][FRI_FractionID] != FractionRangInfo[PlayerFractionInfo[playerid][PFI_FractionRangArrayID]][FRI_FractionID]) {
		return SendClientMessage(playerid, -1, "Игрок не состоит в Вашей организации.");
	}
	if(targetid == playerid) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Вы указали свой ID");
	}
	if(GetDistanceBetweenPlayerz(playerid, targetid, 2.00) != 1) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Вы слишком далеко от указанного игрока");
	}

	new 
		active_player_rang = PlayerFractionInfo[targetid][PFI_FractionRangArrayID],
		rang_title[MAX_FRACTION_RANG];

	if(!strcmp(sub, "+")) {
		if(FractionRangInfo[active_player_rang + 1][FRI_LeaderRang] == 1) {
			return SendClientMessage(playerid, -1, "Игрок находится на максимальном ранге.");
		}

		if(PlayerFractionInfo[targetid][PFI_FractionRangArrayID]++ >= PlayerFractionInfo[playerid][PFI_FractionRangArrayID]) {
			return SendClientMessage(playerid, -1, "Вы не можете повысить игрока до вашей должности.");
		}
		PlayerFractionInfo[targetid][PFI_FractionRangArrayID] ++;

		GetFractionRangTitle(PlayerFractionInfo[targetid][PFI_FractionRangArrayID], rang_title);

		format(small_string, sizeof(small_string), 
			""COLOR_GREEN"%s(%i) повысил Вам ранг до %s", 
				PlayerInfo[playerid][pName], 
				playerid, 
				rang_title
		);
		SendClientMessage(targetid, -1, small_string);

		format(small_string, sizeof(small_string), 
			""COLOR_GREEN"Вы повысили ранг игроку %s(%i) до %s", 
				PlayerInfo[targetid][pName], 
				targetid, 
				rang_title
		);
		SendClientMessage(playerid, -1, small_string);

		mysql_format(database, small_string, sizeof(small_string), "CALL `ChangePlayerRang` (%i , 1);", PlayerInfo[targetid][pID]);
		mysql_query(database, small_string, false);
		return 1;

	} else if(!strcmp(sub, "-")) {
		if(FractionRangInfo[active_player_rang--][FRI_InviteRang] == 1) {
			return SendClientMessage(playerid, -1, "Игрок находится на минимальном ранге.");
		}
		PlayerFractionInfo[targetid][PFI_FractionRangArrayID] --;

		GetFractionRangTitle(PlayerFractionInfo[targetid][PFI_FractionRangArrayID], rang_title);

		format(small_string, sizeof(small_string), 
			""COLOR_ORANGE"%s(%i) понизил Вам ранг до %s", 
				PlayerInfo[playerid][pName], 
				playerid, 
				rang_title
		);
		SendClientMessage(targetid, -1, small_string);

		format(small_string, sizeof(small_string), 
			""COLOR_ORANGE"Вы понизили ранг игроку %s(%i) до %s", 
				PlayerInfo[targetid][pName], 
				targetid, 
				rang_title
		);
		SendClientMessage(playerid, -1, small_string);

		mysql_format(database, small_string, sizeof(small_string), "CALL `ChangePlayerRang` (%i , 0);", PlayerInfo[targetid][pID]);
		mysql_query(database, small_string, false);
		return 1;
	} else {
		return SendClientMessage(playerid, -1, "Используйте: /rang [ID Игрока] [+ - повысить ранг; - - понизить ранг]");
	}
	return 1;
}