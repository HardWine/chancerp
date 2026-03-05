#if defined admin_header_included
	#endinput
#endif

#define admin_header_included

#define MAX_ADMIN_LEVEL 				(10)
#define MAX_ADMIN_LEVEL_TITLE 			(36)
#define Admin. 							Admin__

enum 
	E_ADMIN_LEVEL__ {
		E_ADMIN_LEVEL,
		E_ADMIN_LEVEL_TITLE[MAX_ADMIN_LEVEL_TITLE]
	};

new const 
	Admin.Level[MAX_ADMIN_LEVEL][E_ADMIN_LEVEL__] = {
		{0, "-"},
		{1, "Первый уровень"},
		{2, "Второй уровень"},
		{3, "Третий уровень"},
		{4, "Четвертый уровень"},
		{5, "Пятый уровень"},
		{6, "Заместитель главного администратора"},
		{7, "Главный администратор"},
		{8, "Разработчик"},
		{9, "Santa"}
	};

new 
	Player.AdminLevel[MAX_PLAYERS char];

stock AD_OnPlayerConnect(playerid) 
{
	Player.AdminLevel{playerid} = 0;
}

public GetPlayerAdminLevel(playerid)
{
	return Player.AdminLevel{playerid};
}

stock AD_OnPlayerDisconnect(playerid, reason) 
{
	if(Player.AdminLevel{playerid} != 0) {
		format(small_string, sizeof(small_string), 
			""COLOR_RED"Администратор "COLOR_WHITE"%s"COLOR_RED" теперь оффлайн %s", 
				PlayerInfo[playerid][pName],
				(reason == 1) ? ("(выход из игры)") : ("(разрыв соединения)")
		);
		SendAdminMessage(-1, small_string);	
	}

	Player.AdminLevel{playerid} = 0;
	if(Iter_Contains(Admin, playerid)) {
		Iter_Remove(Admin, playerid);
	}
}