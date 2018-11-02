#if defined cmd_auninvite_included
	#endinput
#endif

#define cmd_auninvite_included

CMD:auninvite(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 4) {
		return 1;
	}

	new 
		targetid;

	if(sscanf(params, "u", targetid)) {
		return SendClientMessage(playerid, -1, "Используйте: /auninvite [ID Игрока]");
	}

	if(IsPlayerConnected(targetid) == 0) {
		return SendClientMessage(playerid, -1, "Игрок не авторизован");
	} 

	if(IsPlayerInFraction(targetid) == false) {
		return SendClientMessage(playerid, -1, "Игрок не состоит в организации");
	}

	new 
		rang_array = PlayerFractionInfo[targetid][PFI_FractionRangArrayID];

	if(FractionRangInfo[rang_array][FRI_LeaderRang] == 1) {
		if(PlayerInfo[playerid][pAdmin] < 5) {
			return SendClientMessage(playerid, -1, "Вы не можете снять лидера организации.");
		}
	}

	UnInvitePlayerFromOrganization(PlayerInfo[targetid][pID], true);

	format(small_string, sizeof(small_string), 
		""COLOR_ORANGE"[A] Администратор %s(%i) уволили игрока %s(%i) из фракции",
			PlayerInfo[playerid][pName],
			playerid,
			PlayerInfo[targetid][pName],
			targetid
	);
	SendAdminMessage(-1, small_string);

	format(small_string, sizeof(small_string), 
		""COLOR_ORANGE"Администратор %s уволил вас из фракции",
			PlayerInfo[playerid][pName]
	);
	return SendClientMessage(targetid, -1, small_string);
}