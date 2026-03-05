#if defined player_last_date_included
	#endinput
#endif

#define player_last_date_included

#include <YSI_Coding\y_hooks>

hook OnPlayerAuthorization(playerid) {
	new 
		account_id = GetPlayerAccountID(playerid);

	if(account_id != 0) {
		mysql_format(database, 
			small_string, sizeof(small_string), 
			"UPDATE "TABLE_ACCOUNTS" SET `isOnline`= 1 WHERE ID = %i LIMIT 1", 
				GetPlayerAccountID(playerid)
		);
		mysql_pquery(database, small_string);
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason 

	new 
		account_id = GetPlayerAccountID(playerid);

	if(account_id != 0) {
		mysql_format(database, 
			small_string, sizeof(small_string), 
			"UPDATE "TABLE_ACCOUNTS" SET `LastDate` = CURRENT_TIMESTAMP(), `isOnline`= 0 WHERE ID = %i", 
				GetPlayerAccountID(playerid)
		);
		mysql_pquery(database, small_string);
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}
