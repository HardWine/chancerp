#if defined helper_system_included
	#endinput
#endif

#define helper_system_included

#define Helper. 			Helper__

#include <helper/helper_header>
#include <helper/helper_api>

#include <YSI_Coding\y_hooks>

new Iterator:Helper<MAX_PLAYERS>;

hook OnPlayerAuthorization(playerid) {
	Player.HelperLevel{playerid} = Helper.GetPlayerLevel(GetPlayerAccountID(playerid));


	if(Player.HelperLevel{playerid} != 0) {
		Iter_Add(Helper, playerid);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы авторизовались как хелпер");

		format(small_string, sizeof(small_string), 
			""COLOR_RED"Support "COLOR_WHITE"%s"COLOR_RED" авторизовался", 
				PlayerInfo[playerid][pName]
		);
		SendHelperMessage(-1, small_string);
		SendAdminMessage(-1, small_string);
	}
}

hook OnPlayerDisconnect(playerid, reason) {
	if(Iter_Contains(Helper, playerid)) {
		Iter_Remove(Helper, playerid);
	}
}
