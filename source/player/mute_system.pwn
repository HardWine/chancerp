#if defined myte_system_included
	#endinput
#endif

#define myte_system_included

stock PlayerMuteCount[MAX_PLAYERS] = {0, ...};
stock PlayerMuteTimer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};

stock Mute_OnPlayerConnect(playerid)
{
	AddPlayerMute(playerid);
}

stock Mute_OnPlayerAuthorization(const playerid)
{
	mysql_format(database, small_string, sizeof(small_string), "SELECT SUM(`MiteCount`) AS Count FROM player_mute WHERE PlayerID = %i AND Status = 'Активен'", GetPlayerAccountID(playerid));
	mysql_pquery(database, small_string, "@_LoadPlayerMute", "i", playerid);

	PlayerMuteTimer[playerid] = SetTimerEx("@_PlayerMuteTimer", 1000, 0, "i", playerid);
}

@_LoadPlayerMute(const playerid);
@_LoadPlayerMute(const playerid) {
	new rows = cache_get_row_count();

	if(rows)
	{
		PlayerMuteCount[playerid] = cache_get_field_content_int(0, "Count");
	}
}

@_PlayerMuteTimer(const playerid);
@_PlayerMuteTimer(const playerid) {
	PlayerMuteTimer[playerid] = PlayerMuteTimer[playerid] - 1;

	if(PlayerMuteTimer[playerid] == 0)
	{
		SendClientMessage(playerid, -1, "Доступ в чат восстановлен")
	}
}

stock AddPlayerMute(const playerid, const adminid = 1616, const secound = (60 * 15), const reason[] = "Нарушение правил сервера")
{
	printf("%i %i %i %s", playerid, adminid, secound, reason);

	mysql_format(database, small_string, sizeof(small_string), 
		"INSERT INTO `player_mute`(`PlayerID`, `AdminID`, `Reason`, `MiteCount`) VALUES (%i, %i, '%e', %i)", 
			GetPlayerAccountID(playerid),
			GetPlayerAccountID(adminid),
			reason,
			secound
	);
	mysql_pquery(database, small_string);

	SendClientMessage(playerid, -1, ""COLOR_WHITE"Доступ в чат ограничен");
}

CMD:muteinfo(playerid, params[])
{

}