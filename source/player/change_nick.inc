#if defined change_nick_system
	#endinput
#endif

#define change_nick_system

#include <YSI_Coding\y_hooks>

forward bool: Player.RemoveChangeNick(const playerid);

enum 
	E_CHANGE_NICK_TYPE {
		E_FREE = 1,
		E_SELL
	};

forward Player.IsUsedName(const name[]);
public Player.IsUsedName(const name[]) {
	mysql_format(database, 
		small_string, sizeof(small_string), 
		"SELECT `ID` FROM `players` WHERE `Name` = '%e' LIMIT 1", 
			name
	);
	mysql_query(database, small_string, true);

	if(cache_get_row_count()) {
		return 1;
	} else {
		mysql_format(database_forum, 
			small_string, sizeof(small_string), 
			"SELECT `member_id` FROM `core_members` WHERE `name` = '%e' LIMIT 1", 
				name
		);
		mysql_query(database_forum, small_string, true);

		if(cache_get_row_count()) {
			return -1;
		}
	}
	return 0;
}

stock bool:Player.ChangeNick(const playerid, const new_name[], const E_CHANGE_NICK_TYPE:type = E_FREE, const admin_id = INVALID_PLAYER_ID) {
	mysql_format(database, 
		small_string, sizeof(small_string), 
		"UPDATE `players` SET `Name` = '%e' WHERE `Name` = '%e' AND ID = %i LIMIT 1", 
			new_name,
			PlayerInfo[playerid][pName],
			GetPlayerAccountID(playerid)
	);
	printf(small_string);
	mysql_query(database, small_string, false);

	new mysql_errno_code = mysql_errno(database);
	
	printf("%i", mysql_errno_code);

	if(mysql_errno_code == 0) {

		/*mysql_format(database_forum, 
			small_string, sizeof(small_string), 
				"UPDATE `core_members` SET `name` = '%e' WHERE `name` = '%e' LIMIT 1", 
					new_name,
					PlayerInfo[playerid][pName]
		);
		printf(small_string);
		mysql_query(database_forum, small_string, false);
		printf("%i", mysql_errno(database_forum));
		if(mysql_errno(database_forum) == 0) {*/
		if(admin_id == INVALID_PLAYER_ID) {
			mysql_format(database, 
				big_string, sizeof(big_string), 
				"INSERT INTO `log_name` (`PlayerID`, `OldName`, `NewName`, `Type`, `AdminID`) VALUES (%i, '%e', '%e', %i, NULL)", 
					GetPlayerAccountID(playerid),
					PlayerInfo[playerid][pName],
					new_name,
					_:type
			);
		} else {
			mysql_format(database, 
				big_string, sizeof(big_string), 
				"INSERT INTO `log_name` (`PlayerID`, `OldName`, `NewName`, `Type`, `AdminID`) VALUES (%i, '%e', '%e', %i, %i)", 
					GetPlayerAccountID(playerid),
					PlayerInfo[playerid][pName],
					new_name,
					_:type,
					GetPlayerAccountID(admin_id)
			);
		}
		printf(big_string);
		mysql_pquery(database, big_string);

		mysql_format(database, 
			small_string, sizeof(small_string), 
			"UPDATE `roulet` SET `name`= '%e' WHERE `name` = '%e'", 
				new_name,
				PlayerInfo[playerid][pName]
		);
		mysql_pquery(database, small_string);
		/*new player_house = GetPlayerHouseID(playerid);
		if(player_house != 0 ) {
			new MySQL[110], text[156];
			mysql_format(database, MySQL, sizeof(MySQL), "UPDATE `apartment` SET Owner = '%e' WHERE ID = '%d' LIMIT 1",PlayerInfo[playerid][pName],player_house);
			mysql_pquery(database, MySQL, "", "");
			HouseInfo[player_house][hOwner] = PlayerInfo[playerid][pName];
			new klass[20];
			switch(HouseInfo[player_house][hClass])
			{
				case 0: klass = "Эконом";
				case 1: klass = "Доступный";
				case 2: klass = "Средний";
				case 3: klass = "Элитный";
				case 4: klass = "Премиум";
				case 5: klass = "Люкс";
			}
			format(text, sizeof(text),"Дом №%d {FF6347}(куплен){FFFFFF}\nВладелец: {7CFC00}%s{FFFFFF}\nКласс: {7CFC00}%s{FFFFFF}", player_house, HouseInfo[player_house][hOwner],klass);
			UpdateDynamic3DTextLabelText(HouseInfo[player_house][hText], -1, text);
		}
		for(new i = 0; i < MAX_HOTEL_ROOM; i++) {
			if(Hotel.Room[i][E_HOTEL_ROOM_OWNER_ID] == GetPlayerAccountID(playerid)) {
				strmid(Hotel.Room[i][E_HOTEL_ROOM_OWNER_NAME], new_name, 0, strlen(new_name), 255);
			}
		}*/
		format(small_string, sizeof(small_string), ""COLOR_YELLOW"%s сменил ник на %s", PlayerInfo[playerid][pName], new_name);
		SendClientMessageToAll(-1, small_string);
			
		SetPlayerName(playerid, new_name);
		strmid(PlayerInfo[playerid][pName], new_name, 0, strlen(new_name), MAX_PLAYER_NAME);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Перезайдите в игру под новым ником");
		Kick(playerid);

		return true;
		//}
	}
	return false;
}

#define MAX_CHANGE_NICK 		(20)

enum 
	E_CHANGE_NICK {
		E_PLAYER_ID,
		E_NEW_NAME[MAX_PLAYER_NAME + 1]
	};
new 
	ChangeNick[MAX_CHANGE_NICK][E_CHANGE_NICK];

hook OnGameModeInit() {
	for(new i = 0; i < MAX_CHANGE_NICK; i++) {
		ChangeNick[i][E_PLAYER_ID] = INVALID_PLAYER_ID;
	}
}

hook OnPlayerDisconnect(playerid, reason) {
	Player.RemoveChangeNick(playerid);
}

stock bool: Player.AddChangeNick(const playerid, const new_name[]) {
	for(new i = 0; i < MAX_CHANGE_NICK; i++) {
		if(ChangeNick[i][E_PLAYER_ID] == INVALID_PLAYER_ID) {
			strmid(ChangeNick[i][E_NEW_NAME], new_name, 0, strlen(new_name), MAX_PLAYER_NAME);
			ChangeNick[i][E_PLAYER_ID] = playerid;

			format(big_string, sizeof(big_string), 
				""COLOR_RED"[A] Игрок %s(%i) хочет изменить свой никнейм на %s\n/cn %i + (для обобрения)\n/cn %i - (для отклонения)", 
					PlayerInfo[playerid][pName], 
					playerid, 
					new_name,
					playerid,
					playerid
			);
			SendAdminMessage(-1, big_string);
			return true;
		}
	}
	return false;
}

stock Player.IsChangeNick(const playerid) {
	for(new i = 0; i < MAX_CHANGE_NICK; i++) {
		if(ChangeNick[i][E_PLAYER_ID] == playerid) {
			return i;
		}
	}
	return -1;
}

CMD:cn(playerid, params[]) {
	if(GetPlayerAdminLevel(playerid) < 5) {
		return false;
	}

	new 
		targetid,
		arguments[2];

	if(sscanf(params, "us[2]", targetid, arguments) != 1) {
		new 
			arrayID = Player.IsChangeNick(targetid);

		if(arrayID == -1) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Игрок не отправлял заявку на смену имени");
		}
		if(strcmp(arguments, "+", false) == 0) {
			format(small_string, sizeof(small_string), 
				""COLOR_GREEN"Администратор %s(%i) одобрил игроку смену ника с %s(%i) на %s", 
					PlayerInfo[playerid][pName], 
					playerid, 
					PlayerInfo[targetid][pName],
					targetid,
					ChangeNick[arrayID][E_NEW_NAME]
			);
			SendAdminMessage(-1, small_string);

			format(small_string, sizeof(small_string), 
				""COLOR_GREEN"Ваша заявка на смену никнейма была одобрена администратором %s", 
					PlayerInfo[playerid][pName]
			);
			SendClientMessage(targetid, -1, small_string);

			Player.ChangeNick(targetid, ChangeNick[arrayID][E_NEW_NAME], E_FREE, playerid); 
			return Player.RemoveChangeNick(targetid);
		} else if(strcmp(arguments, "-", false) == 0) {
			format(small_string, sizeof(small_string), 
				""COLOR_RED"Администратор %s(%i) отклонил игроку смену ника с %s(%i) на %s", 
					PlayerInfo[playerid][pName], 
					playerid, 
					PlayerInfo[targetid][pName],
					targetid,
					ChangeNick[arrayID][E_NEW_NAME]
			);
			SendAdminMessage(-1, small_string);

			format(small_string, sizeof(small_string), 
				""COLOR_RED"Ваша заявка на смену никнейма была отклонена администратором %s", 
					PlayerInfo[playerid][pName]
			);
			SendClientMessage(targetid, -1, small_string);
			return Player.RemoveChangeNick(targetid);
		} else {
			return SendClientMessage(playerid, -1, "Используйте: /cn [ID Игрока] [+(для одобрения)/-(для отклонения)");
		}
	} else {
		return SendClientMessage(playerid, -1, "Используйте: /cn [ID Игрока] [+(для одобрения)/-(для отклонения)");
	}
}

public bool: Player.RemoveChangeNick(const playerid) {
	for(new i = 0; i < MAX_CHANGE_NICK; i++) {
		if(ChangeNick[i][E_PLAYER_ID] == playerid) {
			ChangeNick[i][E_NEW_NAME][0] = EOS;
			ChangeNick[i][E_PLAYER_ID] = INVALID_PLAYER_ID;
			return true;
		}
	}
	return false;
}