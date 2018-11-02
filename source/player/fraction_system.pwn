#if defined fraction_system_included
	#endinput
#endif

#define fraction_system_included

forward bool:InvitePlayerFromOrganization(const playerid, const fractionid, const bool:isLeader);
forward  UnInvitePlayerFromOrganization(const accID, const bool:isLoad);

#define MAX_FRACTION 		12
#define MAX_FRACTION_TITLE 	32
enum 
	Fraction: {
		FRACTION_NONE = 0,
		FRACTION_LSPD, // 1
		FRACTION_GROOVE, // 2
		FRACTION_BALLAS, // 3
		FRACTION_VAGOS, // 4
		FRACTION_RIFA, // 5
		FRACTION_AZTECAS,  // 6
		FRACTION_RUSSIAN_MAFIA, // 7
		FRACTION_TRIADA, // 8
		FRACTION_DN_BOYS,  // 9
		FRACTION_ARMY, // 10
		FRACTION_FBI, // 11
		FRACTION_GOVERMENT // 12
	};

new const 
	FractionTitle[MAX_FRACTION][MAX_FRACTION_TITLE] = {
		"LSPD", // 1
		"Grove Street", // 2
		"Ballas Gang", // 3
		"Vagos Gang", // 4
		"Rifa Gang", // 5
		"Aztecas Gang", // 6
		"Русская Мафия", // 7
		"Triads", // 8
		"Da Nang Boys", // 9
		"Армия", // 10
		"FBI", // 11
		"Правительство" // 12
	};



new 
	Fraction: player_fraction[MAX_PLAYERS char];

forward Fraction_OnPlayerConnect(playerid);
public Fraction_OnPlayerConnect(playerid) {
	return RemovePlayerFraction(playerid);
}

forward Fraction_OnPlayerDisconnect(playerid, reason);
public Fraction_OnPlayerDisconnect(playerid, reason) {
	return RemovePlayerFraction(playerid);
}

stock SetPlayerFraction(playerid, Fraction:sfractionid, bool:isSave = false) {
	player_fraction{playerid} = sfractionid;

	if(isSave == true) {
		static string[55 + 2 + MAX_LENGTH_ACCOUNT_ID + 1];

		mysql_format(database,
			string, sizeof(string),
			"UPDATE players SET `Job` = '%i' WHERE `ID` = %i LIMIT 1",
				_:sfractionid,
				GetPlayerAccountID(playerid)
		);
		mysql_pquery(database, string);
	}
	return 1;
}

stock Fraction:GetPlayerFraction(playerid) {
	return player_fraction{playerid};
}

stock RemovePlayerFraction(playerid, bool:isSave = false) {
	// new 
	// 	Fraction: fractionid = GetPlayerFraction(playerid);

	// if(fractionid >= FRACTION_GROOVE && fractionid <= FRACTION_AZTECAS) {
	// 	TogglePlayerDynamicArea(playerid, army_zone, false);
	// }
	
	//PlayerFractionInfo[playerid][PFI_FractionArrayID] = INVALID_FRACTION_ID;
	//PlayerFractionInfo[playerid][PFI_FractionRangArrayID] = INVALID_RANG_ID;
	
	if(GetPlayerFraction(playerid) != FRACTION_NONE) {
		SetPlayerFraction(playerid, FRACTION_NONE, isSave);
		return true;
	} else {
		return false;
	}
}

stock bool:IsPlayerInFraction(playerid) {
	return (player_fraction{playerid} != FRACTION_NONE) ? (true) : (false);
}


