#if defined fraction_system_included
	#endinput
#endif

#define fraction_system_included

forward bool:InvitePlayerFromOrganization(const playerid, const fractionid, const bool:isLeader);
forward  UnInvitePlayerFromOrganization(const accID, const bool:isLoad);

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
	
	PlayerFractionInfo[playerid][PFI_FractionArrayID] = INVALID_FRACTION_ID;
	PlayerFractionInfo[playerid][PFI_FractionRangArrayID] = INVALID_RANG_ID;
	
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



// Release 1.00
forward Fraction_LoadPlayerAccounts(playerid);
forward GetPlayerFractionInfo(const accID, &fractionid, &rangid);
forward ReturnFractionInfo(&fractionid, &rangid);

public Fraction_LoadPlayerAccounts(playerid) {
	new 
		fraction,
		rang;

	GetPlayerFractionInfo(PlayerInfo[playerid][pID], fraction, rang);
	
	PlayerFractionInfo[playerid][PFI_FractionArrayID] = fraction;
	PlayerFractionInfo[playerid][PFI_FractionRangArrayID] = rang;

	/*format(small_string, sizeof(small_string), "GetPlayerFraction -- %i %i", fraction, rang);
	SendClientMessage(playerid, -1, small_string);*/
	if(fraction != INVALID_FRACTION_ID) {
		SetPlayerFraction(playerid, Fraction:fraction + Fraction:1);

		if(PlayerInfo[playerid][pSex] == 0) {
			SetPlayerSkin(playerid, FractionRangInfo[rang][FRI_SkinMale]);
		} else {
			SetPlayerSkin(playerid, FractionRangInfo[rang][FRI_SkinFemale]);
		}

		switch(fraction + 1) {
			case FRACTION_LSPD: SetPlayerColor(playerid, LSPD_COLOR);
			case FRACTION_GROOVE: SetPlayerColor(playerid, GROVE_COLOR);
			case FRACTION_BALLAS: SetPlayerColor(playerid, BALLAS_COLOR);
			case FRACTION_VAGOS: SetPlayerColor(playerid, VAGOS_COLOR);
			case FRACTION_RIFA: SetPlayerColor(playerid, RIFA_COLOR);
			case FRACTION_AZTECAS: SetPlayerColor(playerid, AZTEC_COLOR);
			case FRACTION_RUSSIAN_MAFIA: SetPlayerColor(playerid, RUSSIA_COLOR);
			case FRACTION_TRIADA: SetPlayerColor(playerid, TRIAD_COLOR);
			case FRACTION_DN_BOYS: SetPlayerColor(playerid, DANANG_COLOR);
			case FRACTION_ARMY: SetPlayerColor(playerid, ARMY_COLOR);
			case FRACTION_FBI: SetPlayerColor(playerid, FBI_COLOR);
			case FRACTION_GOVERMENT: SetPlayerColor(playerid, MAYOR_COLOR);
		}
	} else {
		SetPlayerColor(playerid, CIVIL_COLOR);
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	}
	return 0;
}

public GetPlayerFractionInfo(const accID, &fractionid, &rangid) {
	mysql_format(database, 
		small_string, sizeof(small_string), 
		"SELECT CONVERT(Fraction, SIGNED) as Fr, CONVERT(Rang, SIGNED) as Rg FROM "TABLE_PLAYER_FRACTION" WHERE PlayerID=%i LIMIT 1", 
			accID
	);
	mysql_query(database, small_string, true);

	new 
		rows = cache_get_row_count();

	if(rows == 0) {
		fractionid = INVALID_FRACTION_ID;
		rangid = INVALID_RANG_ID;
		return 0;
	} else {
		fractionid = cache_get_field_content_int(0, "Fr");
		rangid = cache_get_field_content_int(0, "Rg");

		for(new i = 0; i < MAX_FRACTION; i++) {
			if(FractionInfo[i][FI_FractionID] == fractionid) {
				fractionid = i;
				break;
			}
		}
		for(new i = 0; i < MAX_FRACTION_RANG; i++) {
			if(FractionRangInfo[i][FRI_RangID] == rangid) {
				rangid = i;
				break;
			}
		}
		return 1;
	}
}

public bool:InvitePlayerFromOrganization(const playerid, const fractionid, const bool:isLeader) {
	for(new i = 0; i < MAX_FRACTION_RANG; i++) {
		if(FractionRangInfo[i][FRI_FractionID] == fractionid) {

			mysql_format(database, 
				small_string, sizeof(small_string), 
				"CALL `InvitePlayerInFraction` (%i , %i , %i);", 
					PlayerInfo[playerid][pID],
					FractionRangInfo[i][FRI_FractionID],
					isLeader
			);
			printf(small_string);
			mysql_query(database, small_string, false);	
			Fraction_LoadPlayerAccounts(playerid);
			return true;
		}
	}
	printf("Произошла ошибка при принятии игрока во фракцию. fraction = %i", fractionid);
	return false;
}

public UnInvitePlayerFromOrganization(const accID, const bool:isLoad) {
	mysql_format(database, 
		small_string, sizeof(small_string), 
		"CALL `UnInvitePlayer`(%i);", 
			accID
	);
	mysql_query(database, small_string, false);

	new 
		targetid = GetPlayerIDFromAccID(accID);

	if(targetid != INVALID_PLAYER_ID) {
		RemovePlayerFraction(targetid);
		if(isLoad == true) {
			ResetPlayerWeapons(targetid);
			Fraction_LoadPlayerAccounts(targetid);
		}
	}

	for(new i = 0; i < MAX_FRACTION; i++) {
		if(FractionInfo[i][FI_LeaderID] == accID) {
			FractionInfo[i][FI_LeaderID] = INVALID_ACCOUNT_ID;
		}
	}
	return 1;
}