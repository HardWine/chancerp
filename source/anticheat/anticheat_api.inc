#if defined anticheat_api_included
	#endinput
#endif

#define anticheat_api_included

forward bool:AC.SetAction(const arrayID, const action);
public bool:AC.SetAction(const arrayID, const action) {
	format(small_string, sizeof(small_string), "CALL `Anticheat.SetAction` (%i , %i);", AC.Info[arrayID][AC_ID], action);
	mysql_pquery(database, small_string);
	
	AC.Info[arrayID][AC_Action] = action;
	return true;
}

forward bool:AC.SetStatusPC(const arrayID, const status);
public bool:AC.SetStatusPC(const arrayID, const status) {
	format(small_string, sizeof(small_string), "CALL `Anticheat.SetStatusPC` (%i , %i);", AC.Info[arrayID][AC_ID], status);
	mysql_pquery(database, small_string);
	
	AC.Info[arrayID][AC_PC] = status;

	foreach(new i: Player) {
		if(Platform[i] == 1 && Iter_Contains(Admin, i) == 0) {
			EnableAntiCheatForPlayer(i, AC.Info[arrayID][AC_Value], status);
		}
	}
	return true;
}

forward bool:AC.SetStatusAndroid(const arrayID, const status);
public bool:AC.SetStatusAndroid(const arrayID, const status) {
	format(small_string, sizeof(small_string), "CALL `Anticheat.SetStatusAndroid` (%i , %i);", AC.Info[arrayID][AC_ID], status);
	mysql_pquery(database, small_string);
	
	AC.Info[arrayID][AC_ANDROID] = status;

	foreach(new i: Player) {
		if(Platform[i] == 0 && Iter_Contains(Admin, i) == 0) {
			EnableAntiCheatForPlayer(i, AC.Info[arrayID][AC_Value], status);
		}
	}
	return true;
}
