#if defined kick_system_included
	#endinput
#endif

#define kick_system_included

#include <YSI-Include\YSI\YSI\y_hooks>

new 
	Player.KickTimer[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
	Player.KickTimer[playerid] = INVALID_TIMER_ID;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	if(Player.KickTimer[playerid] != INVALID_TIMER_ID) {
		KillTimer(Player.KickTimer[playerid]);
	}
	Player.KickTimer[playerid] = INVALID_TIMER_ID;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

public bool:Player.Kick(const playerid, const reason[MAX_KICK_REASON], const adminid) {
	mysql_format(database, 
		small_string, sizeof(small_string), 
		"CALL `Player.Kick` (@p0 , @p1 , @p2);", 
			GetPlayerAccountID(playerid), 
			GetPlayerAccountID(adminid), 
			reason
	);
	mysql_pquery(database, small_string);

	if(Player.KickTimer[playerid] == INVALID_TIMER_ID) {
		Player.KickTimer[playerid] = SetTimerEx("@__KickPlayer", GetPlayerPing(playerid) + 100, false, "i", playerid);
	}
	return true;
}

@__KickPlayer(playerid);
@__KickPlayer(playerid) {
	return Kick(playerid);
}