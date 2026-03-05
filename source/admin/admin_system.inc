#if defined admin_system_included
	#endinput
#endif

#define admin_system_included

#include <admin/admin_header>
#include <admin/admin_api>
#include <admin/cheater-panel.pwn>

stock LoadPlayerAdminLevel(playerid)
{
	new 
		admin_level = Admin.GetPlayerLevel(GetPlayerAccountID(playerid));

	Player.AdminLevel{playerid} = admin_level;
	if(admin_level != 0) {
		Iter_Add(Admin, playerid);
		if(admin_level > 2) {
			TextDrawShowForPlayer(playerid, welcomeText);
		}
		format(small_string, sizeof(small_string), 
			""COLOR_GREEN"Вы авторизовались как %s", 
				Admin.Level[admin_level][E_ADMIN_LEVEL_TITLE]
		);
		SendClientMessage(playerid, -1, small_string);

		format(small_string, sizeof(small_string), 
			""COLOR_RED"Администратор (%s) "COLOR_WHITE"%s"COLOR_RED" авторизовался", 
				Admin.Level[admin_level][E_ADMIN_LEVEL_TITLE],
				PlayerInfo[playerid][pName]
		);

		SendAdminMessage(-1, small_string);
	
	}
}