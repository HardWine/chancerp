#if defined ban_system_included
	#endinput
#endif

#define ban_system_included

forward bool:BanPlayer.BanPlayer(const accID, const adminID, const reason[], const days);
public bool:BanPlayer.BanPlayer(const accID, const adminID, const reason[], const days) {
	if(accID == 0) {
		return false;
	}

	mysql_format(database,
		small_string, sizeof(small_string),
			"CALL `Ban.BanPlayer` (%i , %i , '%e' , %i);",
				accID, adminID, reason, days
	);
	mysql_pquery(database, small_string);

	new
		targetid = GetPlayerIDFromAccID(accID);

	if(targetid != INVALID_PLAYER_ID) {
		Kick(targetid);
		return true;
	} else {
		return false;
	}
}

forward bool:BanPlayer.UnBanPlayer(const accID, const adminID, const reason[]);
public bool:BanPlayer.UnBanPlayer(const accID, const adminID, const reason[]) {
	mysql_format(database, small_string, sizeof(small_string), "CALL `Ban.UnBanPlayer` (%i , %i, '%s');", accID, adminID, reason);
	mysql_pquery(database, small_string);
	return true;
}

forward BanPlayer.IsAccBanned(const accID);
public BanPlayer.IsAccBanned(const accID) {
	mysql_format(database,
		big_string, sizeof(big_string),
		"SELECT timestampdiff(DAY, NOW(), `UnBanTime`) AS Day FROM `player_banned` WHERE `PlayerID` = %i AND UnBanTime > NOW() AND Status = 1 ORDER BY ID DESC LIMIT 1",
			accID
	);
	mysql_query(database, big_string, true);

	new
		rows = cache_get_row_count();

	if(rows == 0) {
		return -1;
	} else {
		return cache_get_field_content_int(0, "Day");
	}
}

stock CheckBan(playerid, id) 
{
	printf("CheckBan %i %i", playerid, id);
	if(id > 0) {
		mysql_format(database,
			big_string, sizeof(big_string),
			"SELECT \
				datediff(b.UnBanTime, CURRENT_TIMESTAMP()) AS Day, \
				b.Reason, \
				b.BanTime, \
				b.UnBanTime, \
				p.Name \
			FROM \
				player_banned as b \
			LEFT OUTER JOIN \
				players as p \
			ON \
				b.AdminID = p.ID \
			WHERE \
				b.PlayerID=%i \
			AND \
				b.Status = 1 \
			AND \
				b.UnBanTime > CURRENT_TIMESTAMP() \
			ORDER BY \
				b.ID DESC \
			LIMIT \
				1",
				id
		);
		mysql_query(database, big_string, true);

		new
			rows = cache_get_row_count();

		if(rows != 0) {

			// SetPlayerScreenColour(playerid, 0x000000FF);
			// FadePlayerScreenColour(playerid, 0x00000000, 60000, 25);

			new
				bandate[20],
				unbandate[20],
				admin[MAX_PLAYER_NAME],
				reason[49];

			new
				days;

			cache_get_field_content(0, "Reason", reason);
			cache_get_field_content(0, "BanTime", bandate);
			cache_get_field_content(0, "UnBanTime", unbandate);
			cache_get_field_content(0, "Name", admin);
			days = cache_get_field_content_int(0, "Day");

			format(huge_string, sizeof(huge_string), ""COLOR_WHITE"Ваш аккаунт "COLOR_BLUE"%s"COLOR_WHITE" заблокирован за нарушение правил проекта. \n\
				Если вы не согласны с блокировкой, то Вы можете подать жалобу на форум \n\
				"COLOR_BLUE"(talk.chancerp.ru -> Жалобы - > Жалобы на команду проекта)"COLOR_WHITE"\n\n\
				"COLOR_ORANGE"Информация о блокировки:"COLOR_WHITE"\n\
				\t - Дата блокировки: "COLOR_GREEN"%s"COLOR_WHITE"\n\
				\t - Дата разблокировки: "COLOR_GREEN"%s"COLOR_WHITE"\n\
				\t - Осталось дней: "COLOR_GREEN"%i"COLOR_WHITE"\n\
				\t - Заблокирован администратором: "COLOR_GREEN"%s"COLOR_WHITE"\n\
				\t - Причина блокировки: "COLOR_GREEN"%s"COLOR_WHITE"",
					PlayerInfo[playerid][pName],
					bandate,
					unbandate,
					days,
					admin,
					reason
			);
			ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, "Блокировка аккаунта", huge_string, "Закрыть", "");
			Kick(playerid);
			return 1;
		}
	} 
	return 0;
}