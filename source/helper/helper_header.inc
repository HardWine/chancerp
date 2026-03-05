#if defined helper_header_included
	#endinput
#endif

#define helper_header_included

#include <YSI_Coding\y_hooks>

new 
	Player.HelperLevel[MAX_PLAYERS char];

hook OnPlayerConnect(playerid) {
	Player.HelperLevel{playerid} = 0;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	Player.HelperLevel{playerid} = 0;
	return Y_HOOKS_CONTINUE_RETURN_1;
}