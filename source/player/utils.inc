#if defined utils_included
	#endinput
#endif

#define utils_included

forward GetPlayerIDFromAccID(const accID);
forward Player.GetAccIDFromName(const name[]);
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

/**
 * [GetAccIDFromName возвращает ID аккаунта по нику игрока]
 * @param {text} const name[] [Ник игрока]
 */
public Player.GetAccIDFromName(const name[]) {
	mysql_format(database, small_string, sizeof(small_string), "CALL `Player.GetAccIDFromName` ('%e');", name);
	mysql_query(database, small_string, true);

	new 
		rows = cache_get_row_count();

	if(rows) {
		return cache_get_field_content_int(0, "ID", database);
	} else {
		return false;
	}
}