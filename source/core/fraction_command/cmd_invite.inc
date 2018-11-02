#if defined cmd_invite_included
	#endinput
#endif

#define cmd_invite_included

CMD:invite(playerid, params[]) {
	if(IsPlayerInFraction(playerid) == false) {
		return SendClientMessage(playerid, -1, "Вам недоступна данная команда.");
	}

	if(FractionRangInfo[PlayerFractionInfo[playerid][PFI_FractionRangArrayID]][FRI_isInvite] == 0) {
		return SendClientMessage(playerid, -1, "Вам недоступна данная команда.");
	}

	new 
		targetid;

	if(sscanf(params, "u", targetid)) {
		return SendClientMessage(playerid, -1, "Используйте: /invite [ID Игрока]");
	}

	if(IsPlayerConnected(targetid) == 0) {
		return SendClientMessage(playerid, -1, "Игрок не авторизован.");
	}
	if(targetid == playerid) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Вы указали свой ID");
	}
	if(IsPlayerInFraction(targetid) == true) {
		return SendClientMessage(playerid, -1, "Игрок уже состоит в организации.");
	}
	if(GetDistanceBetweenPlayerz(playerid, targetid, 2.00) != 1) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Вы слишком далеко от указанного игрока");
	}
	
	new 
		fraction_title[MAX_FRACTION_TITLE],
		rang_title[MAX_RANG_TITLE];

	GetFractionTitle(PlayerFractionInfo[playerid][PFI_FractionArrayID], fraction_title);
	GetFractionRangTitle(PlayerFractionInfo[playerid][PFI_FractionRangArrayID], rang_title);

	format(small_string, sizeof(small_string), 
		""COLOR_GREEN"%s %s(%i) предлагает Вам вступить в организацию %s",
			rang_title,
			PlayerInfo[playerid][pName],
			playerid,
			fraction_title
	);
	SendClientMessage(targetid, -1, small_string);

	format(small_string, sizeof(small_string), 
		""COLOR_GREEN"Вы предложили игроку %s(%i) вступить к Вам, в организацию",
			PlayerInfo[targetid][pName],
			targetid
	);
	SendClientMessage(playerid, -1, small_string);

	SetPVarInt(targetid, "Invite_ID", playerid);
	return Dialog_Show(targetid, Dialog:DIALOG_CMD_INVITE);
}

DialogCreate:DIALOG_CMD_INVITE(playerid) {
	new 
		getInviteID = GetPVarInt(playerid, "Invite_ID");

	new 
		fraction_title[MAX_FRACTION_TITLE],
		rang_title[MAX_RANG_TITLE];

	GetFractionTitle(PlayerFractionInfo[getInviteID][PFI_FractionArrayID], fraction_title);
	GetFractionRangTitle(PlayerFractionInfo[getInviteID][PFI_FractionRangArrayID], rang_title);

	format(small_string, sizeof(small_string), 
		""COLOR_GREEN"%s %s"COLOR_WHITE" предлагает\nВам вступить в организацию "COLOR_GREEN"%s",
			rang_title,
			PlayerInfo[getInviteID][pName],
			fraction_title
	);

	return Dialog_Open(playerid, Dialog:DIALOG_CMD_INVITE, DIALOG_STYLE_MSGBOX,
		""COLOR_BLUE"Вступление в организацию",
		small_string,
		"Принять", "Отклонить"
	);
}

DialogResponse:DIALOG_CMD_INVITE(playerid, response, listitem, inputtext[]) {
	if(!response) {
		new 
			getInviteID = GetPVarInt(playerid, "Invite_ID");

		DeletePVar(playerid, "Invite_ID");

		format(small_string, sizeof(small_string), 
			""COLOR_ORANGE"Игрок %s(%i) отказался от предложение вступить к Вам в организацию.",
				PlayerInfo[playerid][pName],
				playerid
		);
		SendClientMessage(getInviteID, -1, small_string);

		format(small_string, sizeof(small_string), 
			""COLOR_ORANGE"Вы отказались от предложения %s(%i) на вступление в организацию.",
				PlayerInfo[getInviteID][pName],
				getInviteID
		);
		return SendClientMessage(playerid, -1, small_string);
	} else {
		new 
			getInviteID = GetPVarInt(playerid, "Invite_ID");

		DeletePVar(playerid, "Invite_ID");

		if(IsPlayerInFraction(getInviteID) == false) {
			return 0;
		}

		format(small_string, sizeof(small_string), 
			""COLOR_GREEN"%s(%i) принял Ваше предложение на вступление в организацию",
				PlayerInfo[playerid][pName],
				playerid
		);
		SendClientMessage(getInviteID, -1, small_string);

		format(small_string, sizeof(small_string), 
			""COLOR_GREEN"Вы приняли предложение игроку %s(%i) на вступление в организацию",
				PlayerInfo[getInviteID][pName],
				getInviteID
		);
		SendClientMessage(playerid, -1, small_string);

		new 
			fraction = PlayerFractionInfo[getInviteID][PFI_FractionRangArrayID];
		
		format(small_string, sizeof(small_string), "getInviteID %i fraction %i fractionid = %i", getInviteID, fraction, FractionRangInfo[fraction][FRI_FractionID]);
		SendClientMessage(playerid, -1, small_string);

		return InvitePlayerFromOrganization(playerid, FractionRangInfo[fraction][FRI_FractionID], false);
	}
}