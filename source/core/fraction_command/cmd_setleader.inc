#if defined cmd_setleader_included
	#endinput
#endif

#define cmd_setleader_included

CMD:setleader(playerid, params[]) {
	if(GetPlayerAdminLevel(playerid) < 4) {
		return 0;
	}

	new 
		targetid;

	if(sscanf(params, "u", targetid)) {
		return SendClientMessage(playerid, -1, "Используйте: /setleader [ID Игрока]");
	}
	if(IsPlayerConnected(targetid) == 0) {
		return SendClientMessage(playerid, -1, "Игрок не авторизован");
	}

	SetPVarInt(playerid, "targetid", targetid);
	return Dialog_Show(playerid, Dialog:DIALOG_CMD_SET_LEADER);

}

DialogCreate:DIALOG_CMD_SET_LEADER(playerid) {
	new 
		fraction_title[MAX_FRACTION_TITLE],
		count = 0;

	big_string = !"№\tНазвание организации\n";

	for(new i = 0; i < MAX_FRACTION; i++) {
		if(IsFractionLeader(i) == true) {
			continue;
		}

		GetFractionTitle(i, fraction_title);

		format(small_string, sizeof(small_string), "%i\t%s\n", i, fraction_title);
		strcat(big_string, small_string);
		count++;
	}

	if(count == 0) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"В данный момент все лидерки заняты. Назначение нового лидера не возможно.");
	}

	return Dialog_Open(playerid, Dialog:DIALOG_CMD_SET_LEADER, DIALOG_STYLE_TABLIST_HEADERS,
		""COLOR_BLUE"Выбор организации",
		big_string,
		"Выбрать", "Закрыть"
	);
}

DialogResponse:DIALOG_CMD_SET_LEADER(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return DeletePVar(playerid, "targetid");
	} else {
		new 
			arrayID = strval(inputtext),
			targetid = GetPVarInt(playerid, "targetid"),
			fraction_title[MAX_FRACTION_TITLE];

		printf("arrayID = %i targetid = %i", arrayID, targetid);

		SetFractionLeader(arrayID, targetid);
		printf("1121312311");
		GetFractionTitle(arrayID, fraction_title);
		printf("1111");
		format(small_string, sizeof(small_string), 
			""COLOR_GREEN"Администратор %s назначил Вас лидером организации %s", 
				PlayerInfo[playerid][pName], 
				fraction_title
		);
		SendClientMessage(targetid, -1, small_string);
		printf("1111s");
		format(small_string, sizeof(small_string), 
			""COLOR_RED"[A] Администратор %s нзначил игрока %s лидером организации %s", 
				PlayerInfo[playerid][pName],
				PlayerInfo[targetid][pName],
				fraction_title
		);
		SendAdminMessage(-1, small_string);
	}
	return 1;
}