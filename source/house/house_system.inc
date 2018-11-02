#if defined house_system_included
	#endinput
#endif

#define house_system_included

#include <house/house_header>
#include <house/house_api>

#include <YSI-Include\YSI\YSI\y_hooks>


hook OnDataBaseConnect() {
	mysql_pquery(database, !"SELECT \
		h.ID, \
		h.X, \
		h.Y, \
		h.Z, \
		h.Price, \
		IFNULL(h.Owned, -1) AS Owned, \
		h.RentDay, \
		CONVERT(h.Class, SIGNED) AS ClassID, \
		h.CarX, \
		h.CarY, \
		h.CarZ, \
		h.CarAngle, \
		CONVERT(h.Closed, SIGNED) -1 AS Closed, \
		h.MedChest, \
		IFNULL(p.Name, \"Отсутсвует\") AS OwnedName \
	FROM \
		house AS h \
	LEFT OUTER JOIN \
		players AS p \
	ON \
		h.Owned = p.ID", "@_LoadHouse");

	new 
		data[2];

	for(new i = 0; i < sizeof(House.Class); i++) {
		House.Class[i][E_HOUSE_CLASS_PICKUPID] = CreateDynamicPickup(1318, 1, 
			House.Class[i][E_HOUSE_CLASS_X], House.Class[i][E_HOUSE_CLASS_Y], House.Class[i][E_HOUSE_CLASS_Z], -1, -1, -1
		);

		House.Class[i][E_HOUSE_CLASS_ZONEID] = CreateDynamicCircle(House.Class[i][E_HOUSE_CLASS_X], House.Class[i][E_HOUSE_CLASS_Y], 1.00, -1, -1, -1);

		data[0] = E_STREAMER_TYPE_HOUSE_CLASS;
		data[1] = i;
		Streamer_SetArrayData(STREAMER_TYPE_AREA, House.Class[i][E_HOUSE_CLASS_ZONEID], E_STREAMER_EXTRA_ID, data, 2);
	}
}

hook OnPlayerConnect(playerid) {
	Player.House[playerid] = INVALID_HOUSE_ID;
	Player.EnterHouse[playerid] = INVALID_HOUSE_ID;
	Player.LinkHouseID[playerid] = INVALID_HOUSE_ID;
	Player.ViemTime{playerid} = 0;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	Player.House[playerid] = INVALID_HOUSE_ID;
	Player.EnterHouse[playerid] = INVALID_HOUSE_ID;
	Player.LinkHouseID[playerid] = INVALID_HOUSE_ID;
	Player.ViemTime{playerid} = 0;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid) {
	new 
		data[2];

	Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, data, 2);

	if(data[0] == E_STREAMER_TYPE_HOUSE) {
		new 
			arrayID = data[1];

		Player.EnterHouse[playerid] = arrayID;
		va_SendClientMessage(playerid, -1, "arrayID = %i", arrayID);
		Dialog_BuyHouse(playerid, arrayID);
		return Y_HOOKS_BREAK_RETURN_1;
	} else if(data[0] == E_STREAMER_TYPE_HOUSE_CLASS) {
		House.UnLinkPlayer(playerid);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid) {
	new 
		data[2];

	Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, data, 2);

	if(data[0] == E_STREAMER_TYPE_HOUSE) {
		//new 
			//arrayID = data[1];

		Player.EnterHouse[playerid] = INVALID_HOUSE_ID;	
	}
}

@_LoadHouse();
@_LoadHouse() {
	new 
		rows = cache_get_row_count(),
		data[2];

	if(rows) {
		for(new i = 0; i < rows; i++) {
			HouseInfo[i][E_HOUSE_ID] = cache_get_field_content_int(i, "ID");
			HouseInfo[i][E_HOUSE_X] = cache_get_field_content_float(i, "X");
			HouseInfo[i][E_HOUSE_Y] = cache_get_field_content_float(i, "Y");
			HouseInfo[i][E_HOUSE_Z] = cache_get_field_content_float(i, "Z");

			HouseInfo[i][E_HOUSE_OWNER] = cache_get_field_content_int(i, "Owned");
			cache_get_field_content(i, "OwnedName", HouseInfo[i][E_HOUSE_OWNER_NAME]);

			HouseInfo[i][E_HOUSE_CLASS] = cache_get_field_content_int(i, "ClassID");
			HouseInfo[i][E_HOUSE_RENT_DAY] = cache_get_field_content_int(i, "RentDay");
			HouseInfo[i][E_HOUSE_CLOSSED] = cache_get_field_content_int(i, "Closed");
			HouseInfo[i][E_HOUSE_MED_CHEST] = cache_get_field_content_int(i, "MedChest");

			HouseInfo[i][E_HOUSE_ZONEID] = CreateDynamicCircle(HouseInfo[i][E_HOUSE_X], HouseInfo[i][E_HOUSE_Y], 1.00, 0, 0, -1);
			
			data[0] = E_STREAMER_TYPE_HOUSE;
			data[1] = i;

			Streamer_SetArrayData(STREAMER_TYPE_AREA, HouseInfo[i][E_HOUSE_ZONEID], E_STREAMER_EXTRA_ID, data, 2);
			
			HouseInfo[i][E_HOUSE_PICKUID] = CreateDynamicPickup((HouseInfo[i][E_HOUSE_OWNER] == INVALID_ACCOUNT_ID) ? (1273) : (1272), 23, 
				HouseInfo[i][E_HOUSE_X], HouseInfo[i][E_HOUSE_Y], HouseInfo[i][E_HOUSE_Z], 0, 0, -1
			);

			if(HouseInfo[i][E_HOUSE_OWNER] == INVALID_ACCOUNT_ID) {
				format(medium_string, sizeof(medium_string),
					"Дом свободен{FFFFFF}\n\
						Класс: {1C82E8}%s{FFFFFF}\n\
						Цена: {1C82E8}%d${FFFFFF}", 
							House.Class[HouseInfo[i][E_HOUSE_CLASS] - 1][E_HOUSE_CLASS_TITLE], 
							HouseInfo[i][E_HOUSE_PRICE]
				);
				HouseInfo[i][E_HOUSE_MAPICON_ID] = CreateDynamicMapIcon(HouseInfo[i][E_HOUSE_X], HouseInfo[i][E_HOUSE_Y], HouseInfo[i][E_HOUSE_Z], 31, -1);
			} else {
				format(medium_string, sizeof(medium_string),
					"Владелец "COLOR_ORANGE"%s{FFFFFF}\n\
						Класс: {1C82E8}%s{FFFFFF}\n\
						Цена: {1C82E8}%d${FFFFFF}\n\
						Состояние дверей %s{FFFFFF}", 
							HouseInfo[i][E_HOUSE_OWNER_NAME],
							House.Class[HouseInfo[i][E_HOUSE_CLASS] - 1][E_HOUSE_CLASS_TITLE], 
							HouseInfo[i][E_HOUSE_PRICE],
							(HouseInfo[i][E_HOUSE_CLOSSED] == 0) ? (""COLOR_GREEN"Открыты") : (""COLOR_RED"Закрыты")
				);
				HouseInfo[i][E_HOUSE_MAPICON_ID] = CreateDynamicMapIcon(HouseInfo[i][E_HOUSE_X], HouseInfo[i][E_HOUSE_Y], HouseInfo[i][E_HOUSE_Z], 32, -1);
			}
			HouseInfo[i][E_HOUSE_LABELID] = CreateDynamic3DTextLabel(medium_string, 0xFFFFFFFF, 
				HouseInfo[i][E_HOUSE_X], HouseInfo[i][E_HOUSE_Y], HouseInfo[i][E_HOUSE_Z], 
				MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
			);
		}
	}
}

stock bool:House.LinkPlayer(const playerid, const arrayID) {
	Player.LinkHouseID[playerid] = arrayID;

	new 
		class = HouseInfo[arrayID][E_HOUSE_CLASS] - 1;
	
	SetPlayerPos(playerid, House.Class[class][E_HOUSE_CLASS_TP_X], House.Class[class][E_HOUSE_CLASS_TP_Y], House.Class[class][E_HOUSE_CLASS_TP_Z]);
	SetPlayerFacingAngle(playerid, House.Class[class][E_HOUSE_CLASS_TP_ANGLE]);
	SetPlayerInterior(playerid, House.Class[class][E_HOUSE_CLASS_INTER]);
	SetPlayerVirtualWorld(playerid, HouseInfo[arrayID][E_HOUSE_ID]);
	SetCameraBehindPlayer(playerid);
	return true;
}

stock House.UnLinkPlayer(const playerid) {
	new 
		arrayID = Player.LinkHouseID[playerid];

	if(arrayID == INVALID_HOUSE_ID) {
		return false;
	}

	if(Player.ViemTime{playerid} > 0) {
		Player.ViemTime{playerid} = 0;
	}

	SetPlayerPos(playerid, HouseInfo[arrayID][E_HOUSE_X], HouseInfo[arrayID][E_HOUSE_Y], HouseInfo[arrayID][E_HOUSE_Z]);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);

	Player.LinkHouseID[playerid] = INVALID_HOUSE_ID;
	return true;
}

timer ViewInteriourHouse[1000](playerid) {
	new 
		time = Player.ViemTime{playerid};
	format(small_string, sizeof(small_string), "VIEW INTERIOR HOUSE ~g~~h~%i", time);
	GameTextForPlayer(playerid, small_string, 1200, 5);

	Player.ViemTime{playerid}--;
	if(time > 0) {
		defer ViewInteriourHouse(playerid);
		return 1;
	} else {
		House.UnLinkPlayer(playerid);
		return 0;
	}
}

hook OnPlayerAuthorization(playerid) {
	new 
		player_id = GetPlayerAccountID(playerid);

	for(new i = 0; i < MAX_HOUSE; i++) {
		if(HouseInfo[i][E_HOUSE_OWNER] == player_id) {
			Player.House[playerid] = i;
			CheckHouseRentDay(playerid);
			break;
		}
	}
}

stock CheckHouseRentDay(playerid) {
	new 
		player_house = Player.House[playerid];

	if(player_house == INVALID_HOUSE_ID) {
		return false;
	}

	new 
		rent_day = HouseInfo[player_house][E_HOUSE_RENT_DAY];

	if(rent_day <= 3) {
		format(small_string, sizeof(small_string), 
			""COLOR_RED"У вашего дома, осталось мало оплаченных дней (%i дн.)", 
				rent_day
		);
	} else {
		format(small_string, sizeof(small_string), 
			""COLOR_ORANGE"У вашего дома, осталось %i оплаченных дней.", 
					rent_day
		);
	}
	SendClientMessage(playerid, -1, small_string);
	SendClientMessage(playerid, -1, ""COLOR_RED"Оплатите дом в банке, во избежание дальнейшей продажи дома государству.");
	return true;
}

stock bool:IsPlayerInHouse(const playerid) {
	return (Player.House[playerid] == INVALID_HOUSE_ID) ? false : true;
}

stock GetPlayerHouse(const playerid) {
	return Player.House[playerid];
}

forward Dialog_BuyHouse(const playerid, const arrayID);
public Dialog_BuyHouse(const playerid, const arrayID) {
	format(big_string, sizeof(big_string), 
		""COLOR_WHITE"Номер дома: "COLOR_GREEN"%i"COLOR_WHITE"\n\
			Владелец: %s%s"COLOR_WHITE"\n\
			Цена: "COLOR_GREEN"%i$"COLOR_WHITE"\n\
			Класс: "COLOR_GREEN"%s"COLOR_WHITE"\n\n\
			"COLOR_ORANGE"1. Для покупки дома, введите цифру 1\n\
			2. Для просмотра интерьера дома, введите цифру 2", 
		HouseInfo[arrayID][E_HOUSE_ID],
		(HouseInfo[arrayID][E_HOUSE_OWNER] == INVALID_ACCOUNT_ID) ? (""COLOR_GREEN"") : (""COLOR_ORANGE""),
		HouseInfo[arrayID][E_HOUSE_OWNER_NAME],
		HouseInfo[arrayID][E_HOUSE_PRICE],
		House.Class[HouseInfo[arrayID][E_HOUSE_CLASS] - 1]
	);
	return ShowPlayerDialog(playerid, 
		DIALOG_BUY_HOUSE, DIALOG_STYLE_INPUT, 
		!""COLOR_BLUE"Информация о доме",
		big_string,
		!"Далее", !"Закрыть"
	);
}

hook OnPlayerDialogShowed(const playerid, const dialogid, const response, const listitem, const inputtext[]) {
	if(dialogid == DIALOG_BUY_HOUSE) {
		if(!response) {
			return Y_HOOKS_BREAK_RETURN_1;
		} else {
			new
				strval_value = strval(inputtext),
				arrayID = Player.EnterHouse[playerid];
			
			if(arrayID == INVALID_HOUSE_ID) {
				return Y_HOOKS_BREAK_RETURN_1;
			}

			if(strval_value == 1) {
				if(Player.House[playerid] != INVALID_HOUSE_ID) {
					SendClientMessage(playerid, -1, "У вас уже есть дом.");
					return Y_HOOKS_BREAK_RETURN_1;
				}
				if(HouseInfo[arrayID][E_HOUSE_OWNER] != INVALID_ACCOUNT_ID) {
					SendClientMessage(playerid, -1, "Дом уже куплен другим игроком.");
					return Y_HOOKS_BREAK_RETURN_1;
				}
				if(CheckCash(playerid, HouseInfo[arrayID][E_HOUSE_PRICE]) == false) return Y_HOOKS_BREAK_RETURN_1;

				Player.DownEXP(GetPlayerAccountID(playerid), HouseInfo[arrayID][E_HOUSE_PRICE], E_BUY_HOUSE, playerid);
				House.SetOwner(arrayID, GetPlayerAccountID(playerid), PlayerInfo[playerid][pName]);
				House.LinkPlayer(playerid, arrayID);
				return Y_HOOKS_BREAK_RETURN_1;
			} else if(strval_value == 2) {
				Player.ViemTime{playerid} = HOUSE_VIEW_TIME;
				ViewInteriourHouse(playerid);
				House.LinkPlayer(playerid, arrayID);
				return Y_HOOKS_BREAK_RETURN_1;
			} else {
				Dialog_BuyHouse(playerid, arrayID);
				return Y_HOOKS_BREAK_RETURN_1;
			}
		}
	} else if(dialogid == DIALOG_CMD_HOUSE) {
		if(!response) {
			return Y_HOOKS_CONTINUE_RETURN_1;
		}

		new 
			strval_value = strval(inputtext),
			arrayID = Player.House[playerid];

		if(strval_value == 1) {
			House.SwitchClossed(arrayID);
			Dialog_CMD_House(playerid);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

CMD:home(playerid, params[]) {
	if(IsPlayerInHouse(playerid) == false) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"У вас нет дома");
	}

	new 
		houseID = GetPlayerHouse(playerid);

	Dialog_CMD_House(houseID);
	return 1;
}

forward Dialog_CMD_House(playerid);
public Dialog_CMD_House(playerid) {
	new 
		arrayID = Player.House[playerid];

	if(arrayID == INVALID_HOUSE_ID) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"У вас нет дома.");
	}

	format(small_string, sizeof(small_string), 
		""COLOR_WHITE"1. %s\n\
		"COLOR_WHITE"2. Использовать аптечку (%i шт.)", 
		(HouseInfo[arrayID][E_HOUSE_CLOSSED] == 0) ? (""COLOR_RED" Закрыть двери") : (""COLOR_GREEN"Открыть двери"),
		HouseInfo[arrayID][E_HOUSE_MED_CHEST]
	);
	return SPD(playerid, 
		DIALOG_CMD_HOUSE, DIALOG_STYLE_INPUT, 
		""COLOR_BLUE"Информация о доме", 
		small_string, 
		"Выбрать", "Закрыть"
	);
}