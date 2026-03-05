#if defined admin_api_included
	#endinput
#endif

#define admin_api_included

forward Admin.GetPlayerLevel(const accID);
public Admin.GetPlayerLevel(const accID) {
	format(small_string, sizeof(small_string), "CALL `Admin.GetPlayerLevel` (%i);", accID);
	new Cache:result = mysql_query(database, small_string, true);

	new 
		rows = cache_get_row_count(),
		level = 0;

	if(rows) {
		level = cache_get_field_content_int(0, !"Level");
	}
	
	cache_delete(result);
	return level;
}

forward bool:Admin.UpCountMute(const accID);
public bool:Admin.UpCountMute(const accID) {
	format(small_string, sizeof(small_string), "CALL `Admin.UpCountMute` (%i);", accID);
	mysql_pquery(database, small_string);
	return true;
}

forward bool:Admin.UpCountPM(const accID);
public bool:Admin.UpCountPM(const accID) {
	format(small_string, sizeof(small_string), "CALL `Admin.UpCountPM` (%i);", accID);
	mysql_pquery(database, small_string);
	return true;
}

forward bool:Admin.UpCountKick(const accID);
public bool:Admin.UpCountKick(const accID) {
	format(small_string, sizeof(small_string), "CALL `Admin.UpCountKick` (%i);", accID);
	mysql_pquery(database, small_string);
	return true;
}

forward bool:Admin.UpCountBan(const accID);
public bool:Admin.UpCountBan(const accID) {
	format(small_string, sizeof(small_string), "CALL `Admin.UpCountBan` (%i);", accID);
	mysql_pquery(database, small_string);
	return true;
}

forward bool:Admin.UpCountJail(const accID);
public bool:Admin.UpCountJail(const accID) {
	format(small_string, sizeof(small_string), "CALL `Admin.UpCountJail` (%i);", accID);
	mysql_pquery(database, small_string);
	return true;
}