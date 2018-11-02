#if defined player_last_date_included
	#endinput
#endif

#define player_last_date_included

forward LD_OnPlayerAuthorization(playerid);
public LD_OnPlayerAuthorization(playerid) {
	static string[56 + MAX_LENGTH_ACCOUNT_ID + 1];

	mysql_format(database, 
		string, sizeof(string), 
		"UPDATE `players` SET `isOnline`= 1 WHERE ID = %i LIMIT 1", 
			GetPlayerAccountID(playerid)
	);
	return mysql_pquery(database, string);
}

forward LD_OnPlayerDisconnect(playerid, reason);
public LD_OnPlayerDisconnect(playerid, reason) {
	if(GetPlayerLoging(playerid) == true) {
		static string[85 + MAX_PLAYER_NAME + 1];

		mysql_format(database, 
			string, sizeof(string), 
			"UPDATE "TABLE_ACCOUNTS" SET `LastDate` = CURRENT_TIMESTAMP(), `isOnline`= 0 WHERE Name = '%e';", 
				PlayerInfo[playerid][pName]
		);
		return mysql_pquery(database, string);
	}
	return 1;
}