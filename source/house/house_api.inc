#if defined house_api_included
	#endinput
#endif

#define house_api_included	

/**
 * [House.SetOwner устанавливает дому владельца]
 * @param {int} const houseID [ID ячейки дома]
 * @param {int} const accID   [Номер аккаунта игрока]
 * @param {string} const name   [Ник владельца]
 */	
forward bool: House.SetOwner(const arrayID, const accID, const name[]);
/**
 * [House.UpRentDay прибавляет 1 день к сроку аренды дома]
 * @param {int} const houseID [ID ячейки дома]
 */	
forward bool: House.UpRentDay(const arrayID);
/**
 * [House.SwitchClossed изменяет статус дверей]
 * @param {int} const houseID [ID ячейки дома]
 */	
forward bool: House.SwitchClossed(const arrayID);
/**
 * [House.SellHouse изменяет статус дверей]
 * @param {int} const houseID [ID ячейки дома]
 * @param {int} const percent [Процент который необходимо вернуть бывшему владельцу]
 */	
forward bool: House.SellHouse(const arrayID, const percent);
/**
 * [House.SetRentDay устанавливает кол-во оплаченных дней дому]
 * @param {int} const houseID [ID ячейки дома]
 * @param {int} const percent [Кол-во дней]
 */	
forward bool: House.SetRentDay(const arrayID, const day);
/**
 * [House.SetRentDay устанавливает кол-во оплаченных дней дому]
 * @param {int} const houseID [ID ячейки дома]
 * @param {int} const percent [Кол-во дней]
 */	
forward bool: House.DownRentDay(const arrayID);
/**
 * [House.SetClass устанавливает класс дому]
 * @param {int} const houseID [ID ячейки дома]
 * @param {int} const percent [Новый класс]
 */	
forward bool: House.SetClass(const arrayID, const class);

public bool:House.SetOwner(const arrayID, const accID, const name[]) {
	format(small_string, sizeof(small_string), "CALL `House.SetOwner` (%i , %i);", HouseInfo[arrayID][E_HOUSE_ID], accID);
	mysql_pquery(database, small_string);

	new 
		playerid = GetPlayerIDFromAccID(accID);

	strmid(HouseInfo[arrayID][E_HOUSE_OWNER_NAME], name, 0, strlen(name), MAX_PLAYER_NAME);
	HouseInfo[arrayID][E_HOUSE_OWNER] = accID;

	Streamer_SetIntData(STREAMER_TYPE_PICKUP, HouseInfo[arrayID][E_HOUSE_PICKUID], E_STREAMER_MODEL_ID, 1272);
	Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, HouseInfo[arrayID][E_HOUSE_MAPICON_ID], E_STREAMER_TYPE, 32);
	format(medium_string, sizeof(medium_string),
		"{11FF00}Владелец "COLOR_ORANGE"%s{FFFFFF}\n\
			Класс: {1C82E8}%s{FFFFFF}\n\
			Цена: {1C82E8}%d${FFFFFF}\n\
			Состояние дверей %s{FFFFFF}", 
				name,
				House.Class[HouseInfo[arrayID][E_HOUSE_CLASS] - 1][E_HOUSE_CLASS_TITLE], 
				HouseInfo[arrayID][E_HOUSE_PRICE],
				(HouseInfo[arrayID][E_HOUSE_CLOSSED] == 0) ? (""COLOR_GREEN"Открыты") : (""COLOR_RED"Закрыты")
	);
	UpdateDynamic3DTextLabelText(HouseInfo[arrayID][E_HOUSE_LABELID], 0xFFFFFFFF, medium_string);

	if(playerid == INVALID_PLAYER_ID) {
		return false;
	} else {
		CheckHouseRentDay(playerid);
		Player.House[playerid] = arrayID;
		return true;
	}
}

public bool: House.UpRentDay(const arrayID) {
	format(small_string, sizeof(small_string), "CALL `House.UpRentDay` (%i);", HouseInfo[arrayID][E_HOUSE_ID]);
	mysql_pquery(database, small_string);

	HouseInfo[arrayID][E_HOUSE_RENT_DAY]++;
	return true;
}

public bool: House.SetRentDay(const arrayID, const day) {
	format(small_string, sizeof(small_string), "CALL `House.SetRentDay` (%i);", HouseInfo[arrayID][E_HOUSE_ID], day);
	mysql_pquery(database, small_string);

	HouseInfo[arrayID][E_HOUSE_RENT_DAY] = day;
	return true;
}

public bool: House.SetClass(const arrayID, const class) {
	format(small_string, sizeof(small_string), "CALL `House.SetClass` (%i);", HouseInfo[arrayID][E_HOUSE_ID], class);
	mysql_pquery(database, small_string);

	HouseInfo[arrayID][E_HOUSE_CLASS] = class;
	return true;
}

public bool: House.DownRentDay(const arrayID) {
	format(small_string, sizeof(small_string), "CALL `House.DownRentDay` (%i);", HouseInfo[arrayID][E_HOUSE_ID]);
	mysql_pquery(database, small_string);

	HouseInfo[arrayID][E_HOUSE_RENT_DAY]--;
	return true;
}

public bool: House.SwitchClossed(const arrayID) {
	format(small_string, sizeof(small_string), 
		"CALL `House.SwitchClossed` (%i);", 
			HouseInfo[arrayID][E_HOUSE_ID]
	);
	mysql_pquery(database, small_string);

	HouseInfo[arrayID][E_HOUSE_CLOSSED] = !HouseInfo[arrayID][E_HOUSE_CLOSSED];

	if(HouseInfo[arrayID][E_HOUSE_OWNER] == INVALID_ACCOUNT_ID) {
		format(medium_string, sizeof(medium_string),
			"Дом свободен{FFFFFF}\n\
				Класс: {1C82E8}%s{FFFFFF}\n\
				Цена: {1C82E8}%d${FFFFFF}", 
					House.Class[HouseInfo[arrayID][E_HOUSE_CLASS] - 1][E_HOUSE_CLASS_TITLE], 
					HouseInfo[arrayID][E_HOUSE_PRICE]
		);
	} else {
		format(medium_string, sizeof(medium_string),
			"Владелец "COLOR_ORANGE"%s{FFFFFF}\n\
				Класс: {1C82E8}%s{FFFFFF}\n\
				Цена: {1C82E8}%d${FFFFFF}\n\
				Состояние дверей %s{FFFFFF}", 
					HouseInfo[arrayID][E_HOUSE_OWNER_NAME],
					House.Class[HouseInfo[arrayID][E_HOUSE_CLASS] - 1][E_HOUSE_CLASS_TITLE], 
					HouseInfo[arrayID][E_HOUSE_PRICE],
					(HouseInfo[arrayID][E_HOUSE_CLOSSED] == 0) ? (""COLOR_GREEN"Открыты") : (""COLOR_RED"Закрыты")
		);
	}
	UpdateDynamic3DTextLabelText(HouseInfo[arrayID][E_HOUSE_LABELID], 0xFFFFFFFF, medium_string);
	return true;
}

public bool: House.SellHouse(const arrayID, const percent) {
	new 
		house_owner = HouseInfo[arrayID][E_HOUSE_PRICE],
		return_money = (HouseInfo[arrayID][E_HOUSE_PRICE] / 100) * percent,
		targetid = GetPlayerIDFromAccID(house_owner);

	strmid(HouseInfo[arrayID][E_HOUSE_OWNER_NAME], "Отсутсвует", 0, strlen("Отсутсвует"), MAX_PLAYER_NAME);

	HouseInfo[arrayID][E_HOUSE_OWNER] = INVALID_ACCOUNT_ID;

	Streamer_SetIntData(STREAMER_TYPE_PICKUP, HouseInfo[arrayID][E_HOUSE_PICKUID], E_STREAMER_MODEL_ID, 1273);
	Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, HouseInfo[arrayID][E_HOUSE_MAPICON_ID], E_STREAMER_TYPE, 31);
	format(medium_string, sizeof(medium_string),
		"Дом свободен{FFFFFF}\n\
			Класс: {1C82E8}%s{FFFFFF}\n\
			Цена: {1C82E8}%d${FFFFFF}", 
				House.Class[HouseInfo[arrayID][E_HOUSE_CLASS] - 1][E_HOUSE_CLASS_TITLE], 
				HouseInfo[arrayID][E_HOUSE_PRICE]
	);
	UpdateDynamic3DTextLabelText(HouseInfo[arrayID][E_HOUSE_LABELID], 0xFFFFFFFF, medium_string);

	if(return_money > 0) {
		Player.AddEXP(house_owner, return_money, E_SELL_HOUSE, targetid);
	}

	if(targetid != INVALID_PLAYER_ID) {
		Player.House[targetid] = INVALID_HOUSE_ID;
	}
	return true;
}