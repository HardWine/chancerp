#if defined utils_included
	#endinput
#endif

#define utils_included

forward GetPlayerIDFromAccID(const accID);
forward Player.GetPlayerAccID(const name[]);

/**
 * [GetPlayerIDFromAccID возвращает ID игрока по указанному ID аккаунта]
 * @param {int} const accID [ID аккаунта]
 */
public GetPlayerIDFromAccID(const accID) {
	new
		targetid = INVALID_PLAYER_ID;

	foreach(new i: Player) {
		if(PlayerInfo[i][pID] == accID) {
			targetid = i;
			break;
		}
	}
	return targetid;
}

public Player.GetPlayerAccID(const name[]) {
	mysql_format(database,
		small_string, sizeof(small_string),
		"SELECT `ID` FROM players WHERE `Name` = '%e' LIMIT 1",
			name
	);
	mysql_query(database, small_string, true);

	new
		rows = cache_get_row_count();

	if(rows == 0) {
		return INVALID_ACCOUNT_ID;
	} else {
		return cache_get_field_content_int(0, "ID");
	}
}