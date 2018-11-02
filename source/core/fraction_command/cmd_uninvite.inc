#if defined cmd_uninvite_included
	#endinput
#endif

#define cmd_uninvite_included

CMD:uninvite(playerid, params[]) {
	if(IsPlayerInFraction(playerid) == false) {
		return SendClientMessage(playerid, -1, "Вам недоступна данная команда.");
	}

	if(FractionRangInfo[PlayerFractionInfo[playerid][PFI_FractionRangArrayID]][FRI_isUninvite] == 0) {
		return SendClientMessage(playerid, -1, "Вам недоступна данная команда.");
	}

	new 
		targetid,
		reason[MAX_UNINVITE_REASON];

	if(sscanf(params, "us[32]", targetid, reason)) {
		return SendClientMessage(playerid, -1, "Используйте: /uninvite [ID Игрока] [Причина]");
	}

	if(IsPlayerConnected(targetid) == 0) {
		return SendClientMessage(playerid, -1, "Игрок не авторизован.");
	}

	if(PlayerFractionInfo[targetid][PFI_FractionRangArrayID] > PlayerFractionInfo[playerid][PFI_FractionRangArrayID]) {
		return SendClientMessage(playerid, -1, "Вы не можете уволить игрока старше Вас по должности.");
	}
	if(FractionRangInfo[PlayerFractionInfo[targetid][PFI_FractionRangArrayID]][FRI_FractionID] != FractionRangInfo[PlayerFractionInfo[playerid][PFI_FractionRangArrayID]][FRI_FractionID]) {
		return SendClientMessage(playerid, -1, "Игрок не состоит в Вашей организации.");
	}
	if(targetid == playerid) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Вы указали свой ID");
	}
	new 
		rang_title[MAX_RANG_TITLE];

	GetFractionRangTitle(PlayerFractionInfo[playerid][PFI_FractionRangArrayID], rang_title);

	format(small_string, sizeof(small_string), 
		"%s %s(%i) уволил игрока %s. Причина: %s", 
			rang_title, 
			PlayerInfo[playerid][pName], 
			playerid, 
			PlayerInfo[targetid][pName], 
			reason
	);

	PlayerFractionInfo[targetid][PFI_FractionArrayID] = INVALID_FRACTION_ID;
	PlayerFractionInfo[targetid][PFI_FractionRangArrayID] = INVALID_RANG_ID;
	RemovePlayerFraction(targetid);

	SendFamilyMessage(GetPlayerFraction(playerid), 0x8D8DFF00, small_string);
	return UnInvitePlayerFromOrganization(PlayerInfo[targetid][pID], true);
}