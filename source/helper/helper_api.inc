#if defined helper_api_included
	#endinput
#endif

#define helper_api_included

forward Helper.GetPlayerLevel(const accID);
public Helper.GetPlayerLevel(const accID) {
	format(small_string, sizeof(small_string), "CALL `Helper.GetPlayerLevel` (%i);", accID);
	new Cache: result = mysql_query(database, small_string, true);

	new 
		rows = cache_get_row_count();

	cache_delete(result);
	
	if(rows == 0) {
		return 0;
	} else {
		return 1;
	}
}

forward bool:Helper.UpCountPM(const accID);
public bool:Helper.UpCountPM(const accID) {
	format(small_string, sizeof(small_string), "CALL `Helper.UpCountPM` (%i);", accID);
	mysql_pquery(database, small_string);
	return true;
}