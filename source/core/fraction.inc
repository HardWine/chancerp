#if defined fraction_included
	#endinput
#endif

#define fraction_included


forward Fraction_OnGameModeInit();
forward LoadFraction();

forward GetFractionLeader(const arrayID, name[]);
forward SetFractionLeader(const arrayID, playerid);
forward GetFractionTitle(const arrayID, title[]);
forward GetFractionID(const arrayID);
forward bool:IsFractionLeader(const arrayID);

enum fraction_info__ {
	FI_ID,
	FI_FractionTitle[MAX_FRACTION_TITLE],
	FI_FractionID,
	FI_Leader[MAX_PLAYER_NAME],
	FI_LeaderID,
	FI_Color
};
new 
	FractionInfo[MAX_FRACTION][fraction_info__];

new const FractionColor[MAX_FRACTION][7] = {
	{"2641FE"},
	{"00D900"},
	{"D900D3"},
	{"FFC801"},
	{"01FCFF"},
	{"6666ff"},
	{"4d4d4d"},
	{"660000"},
	{"cc6600"},
	{"336600"},
	{"1a1a1a"},
	{"336699"}
};

public Fraction_OnGameModeInit() {
	mysql_pquery(database, 
		"SELECT \
			`ID`, \
			`Fraction`, \
			CONVERT(`Fraction`, SIGNED) as FractionID, \
			`Leader`, \
			IF(ISNULL(`Leader`), \"-1\", `Leader`) as LeaderID \
		FROM \
			"TABLE_FRACTION"", "LoadFraction");
}

public LoadFraction() {
	new 
		rows = cache_get_row_count();

	for(new i = 0; i < rows; i++) {
		FractionInfo[i][FI_ID] = cache_get_field_content_int(i, "ID");
		cache_get_field_content(i, "Fraction", FractionInfo[i][FI_FractionTitle]);
		FractionInfo[i][FI_FractionID] = cache_get_field_content_int(i, "FractionID");
		cache_get_field_content(i, "Leader", FractionInfo[i][FI_Leader]);
		FractionInfo[i][FI_LeaderID] = cache_get_field_content_int(i, "LeaderID");

		printf("Итерация %i ID = %i Fraction %s (%i) Leader %s LeaderID %i Color = %i", i, FractionInfo[i][FI_ID], FractionInfo[i][FI_FractionTitle], FractionInfo[i][FI_FractionID], FractionInfo[i][FI_Leader], FractionInfo[i][FI_LeaderID], FractionInfo[i][FI_Color]);
	}
}

public GetFractionLeader(const arrayID, name[]) {
	name[0] = EOS;

	if(arrayID >= 0 && arrayID < MAX_FRACTION) {
		if(FractionInfo[arrayID][FI_LeaderID] == INVALID_ACCOUNT_ID) {
			strcat(name, "Отсутсвует", MAX_PLAYER_NAME);
			return 0;
		} else {
			strcat(name, FractionInfo[arrayID][FI_Leader], MAX_PLAYER_NAME);
			return 1;
		}
	}
	return -1;
}

public SetFractionLeader(const arrayID, playerid) {
	if(arrayID >= 0 && arrayID < MAX_FRACTION) {
		UnInvitePlayerFromOrganization(PlayerInfo[playerid][pID]);
		
		strmid(FractionInfo[arrayID][FI_Leader], PlayerInfo[playerid][pName], 0, strlen(PlayerInfo[playerid][pName]), MAX_PLAYER_NAME);
		FractionInfo[arrayID][FI_LeaderID] = PlayerInfo[playerid][pID];
		
		return InvitePlayerFromOrganization(playerid, FractionInfo[arrayID][FI_FractionID], true);
	}
	return -1;
}

public bool:IsFractionLeader(const arrayID) {
	if(arrayID >= 0 && arrayID < MAX_FRACTION) {
		return (FractionInfo[arrayID][FI_LeaderID] == INVALID_ACCOUNT_ID) ? false : true;
	}
	return false;
}

public GetFractionTitle(const arrayID, title[]) {
	title[0] = EOS;

	if(arrayID >= 0 && arrayID < MAX_FRACTION) {
		strcat(title, FractionInfo[arrayID][FI_FractionTitle], MAX_FRACTION_TITLE);
		return 1;
	}
	return -1;
}

public GetFractionID(const arrayID) {
	if(arrayID >= 0 && arrayID < MAX_FRACTION) {
		return FractionInfo[arrayID][FI_ID];
	}
	return -1;
}