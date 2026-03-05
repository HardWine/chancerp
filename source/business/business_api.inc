#if defined business_api_included
	#endinput
#endif

#define business_api_included

stock bool:Business.PrintArray(const arrayID) {
	Log(businesslog, DEBUG, "Business.PrintArray(%i)", arrayID);
	if(BusinessInfo[arrayID][E_BUSINESS_ID] == INVALID_BUSINESS_ID) {
		Log(businesslog, ERROR, "Обращение к неициализированному бизнесу. Business.PrintArray(%i)", arrayID);
		return false;
	}

	Log(businesslog, DEBUG, "E_BUSINESS_ID = %i\n\
		E_BUSINESS_ENTER_X = %f E_BUSINESS_ENTER_Y = %f E_BUSINESS_ENTER_Z = %f\n\
		E_BUSINESS_EXIT_X = %f E_BUSINESS_EXIT_Y = %f E_BUSINESS_EXIT_z = %f E_BUSINESS_EXIT_ANGLE = %f\n\
		E_BUSINESS_TYPE = %i E_BUSINESS_PRICE = %i E_BUSINESS_OWNER_ID = %i E_BUSINESS_OWNER_NAME = %s\n\
		E_BUSINESS_PROD = %i, E_BUSINESS_MAX_PROD = %i E_BUSINESS_CASH = %i E_BUSINESS_RENT_PRICE = %i\n\
		E_BUSINESS_RENT_DAY = %i\n",
			BusinessInfo[arrayID][E_BUSINESS_ID],
			BusinessInfo[arrayID][E_BUSINESS_ENTER_X], BusinessInfo[arrayID][E_BUSINESS_ENTER_Y], BusinessInfo[arrayID][E_BUSINESS_ENTER_Z],
			BusinessInfo[arrayID][E_BUSINESS_EXIT_X], BusinessInfo[arrayID][E_BUSINESS_EXIT_Y], BusinessInfo[arrayID][E_BUSINESS_EXIT_Z], BusinessInfo[arrayID][E_BUSINESS_EXIT_ANGLE],
			BusinessInfo[arrayID][E_BUSINESS_TYPE], BusinessInfo[arrayID][E_BUSINESS_PRICE], BusinessInfo[arrayID][E_BUSINESS_OWNER_ID], BusinessInfo[arrayID][E_BUSINESS_OWNER_NAME],
			BusinessInfo[arrayID][E_BUSINESS_PROD], BusinessInfo[arrayID][E_BUSINESS_MAX_PROD], BusinessInfo[arrayID][E_BUSINESS_CASH], BusinessInfo[arrayID][E_BUSINESS_RENT_PRICE],
			BusinessInfo[arrayID][E_BUSINESS_RENT_DAY]
	);

	return true;
}

stock Business.CreateLabel(const arrayID) {
	Log(businesslog, DEBUG, "Business.CreateLabel(%i)", arrayID);
	if(BusinessInfo[arrayID][E_BUSINESS_ID] == INVALID_BUSINESS_ID) {
		Log(businesslog, ERROR, "Обращение к неициализированному бизнесу. Business.CreateLabel(%i)", arrayID);
		return false;
	}

	if(BusinessInfo[arrayID][E_BUSINESS_OWNER_ID] == INVALID_ACCOUNT_ID) {
		format(big_string, sizeof(big_string),
			""COLOR_GREEN"%s"COLOR_WHITE"\n\
			Владелец: "COLOR_GREEN"Отсутствует"COLOR_WHITE"\n\
			Цена бизнеса: "COLOR_GREEN"%i EXP"COLOR_WHITE"\n\
			Арендная плата: "COLOR_GREEN"%i EXP"COLOR_WHITE"",
				BusinessType[BusinessInfo[arrayID][E_BUSINESS_TYPE]][E_BUSINESS_TYPE_TITLE],
				BusinessInfo[arrayID][E_BUSINESS_PRICE],
				BusinessInfo[arrayID][E_BUSINESS_RENT_PRICE]
		);
	} else {
		format(big_string, sizeof(big_string),
			""COLOR_GREEN"%s"COLOR_WHITE"\n\
			Владелец: "COLOR_ORANGE"%s"COLOR_WHITE"\n\
			Цена бизнеса: "COLOR_GREEN"%i EXP"COLOR_WHITE"\n\
			Арендная плата: "COLOR_GREEN"%i EXP"COLOR_WHITE"",
				BusinessType[BusinessInfo[arrayID][E_BUSINESS_TYPE]][E_BUSINESS_TYPE_TITLE],
				BusinessInfo[arrayID][E_BUSINESS_OWNER_NAME],
				BusinessInfo[arrayID][E_BUSINESS_PRICE],
				BusinessInfo[arrayID][E_BUSINESS_RENT_PRICE]
		);
	}
	Log(businesslog, DEBUG, big_string);
	UpdateDynamic3DTextLabelText(BusinessInfo[arrayID][E_BUSINESS_LABEL_ENTER], 0xFFFFFFFF, big_string);
	return true;
}

stock bool: Business.SetProd(const arrayID, const prod) {
	Log(businesslog, DEBUG, "Business.SetProd(%i, %i)", arrayID, prod);
	if(BusinessInfo[arrayID][E_BUSINESS_ID] == INVALID_BUSINESS_ID) {
		Log(businesslog, ERROR, "Обращение к неициализированному бизнесу. Business.SetProd(%i, %i)", arrayID, prod);
		return false;
	}

	BusinessInfo[arrayID][E_BUSINESS_PROD] = prod;

	if(BusinessInfo[arrayID][E_BUSINESS_PROD] < 0) {
		Log(businesslog, WARNING, "Продуктов в бизнесе останется меньше нуля. Business.SetProd(%i, %i)", arrayID, prod);
		BusinessInfo[arrayID][E_BUSINESS_PROD] = 0;
	}
	if(BusinessInfo[arrayID][E_BUSINESS_PROD] > BusinessInfo[arrayID][E_BUSINESS_MAX_PROD]) {
		Log(businesslog, WARNING, "Продуктов в бизнесе стало больше MAX_BUSINESS_PROD. Business.SetProd(%i, %i)", arrayID, prod);
		BusinessInfo[arrayID][E_BUSINESS_PROD] = BusinessInfo[arrayID][E_BUSINESS_MAX_PROD];
	}

	format(small_string, sizeof(small_string),
		"UPDATE `biz` SET `Prod`=%i WHERE ID = %i LIMIT 1",
			BusinessInfo[arrayID][E_BUSINESS_PROD],
			BusinessInfo[arrayID][E_BUSINESS_ID]
	);
	mysql_pquery(database, small_string);
	Log(businesslog, DEBUG, small_string);
	return true;
}

stock bool: Business.SetCash(const arrayID, const cash) {
	Log(businesslog, DEBUG, "Business.SetCash(%i, %i)", arrayID, cash);
	if(BusinessInfo[arrayID][E_BUSINESS_ID] == INVALID_BUSINESS_ID) {
		Log(businesslog, ERROR, "Обращение к неициализированному бизнесу. Business.SetCash(%i, %i)", arrayID, cash);
		return false;
	}

	BusinessInfo[arrayID][E_BUSINESS_CASH] = cash;

	format(small_string, sizeof(small_string),
		"UPDATE `biz` SET `Cash`=%i WHERE ID = %i LIMIT 1",
			BusinessInfo[arrayID][E_BUSINESS_CASH],
			BusinessInfo[arrayID][E_BUSINESS_ID]
	);
	mysql_pquery(database, small_string);
	Log(businesslog, DEBUG, small_string);
	return true;
}

stock bool: Business.LinkPlayer(const playerid, const arrayID) {
	if(arrayID < 0 || arrayID > MAX_BUSINESS || BusinessInfo[arrayID][E_BUSINESS_ID] == INVALID_BUSINESS_ID) {
		return false;
	}

	new
		type = BusinessInfo[arrayID][E_BUSINESS_TYPE];

	switch(type) {
		case 0: {
			SetPlayerPos(playerid, BusinessType[type][E_BUSINESS_TYPE_ENTER_X], BusinessType[type][E_BUSINESS_TYPE_ENTER_Y], BusinessType[type][E_BUSINESS_TYPE_ENTER_Z]);
			SetPlayerFacingAngle(playerid, BusinessType[type][E_BUSINESS_TYPE_ENTER_ANGLE]);
			SetPlayerInterior(playerid, BusinessType[type][E_BUSINESS_TYPE_ENTER_INTER]);
			SetPlayerVirtualWorld(playerid, BusinessInfo[arrayID][E_BUSINESS_ID]);
			SetCameraBehindPlayer(playerid);
			Streamer_Update(playerid);
		}
		case 1: {
			SetPlayerPos(playerid, BusinessType[type][E_BUSINESS_TYPE_ENTER_X], BusinessType[type][E_BUSINESS_TYPE_ENTER_Y], BusinessType[type][E_BUSINESS_TYPE_ENTER_Z]);
			SetPlayerFacingAngle(playerid, BusinessType[type][E_BUSINESS_TYPE_ENTER_ANGLE]);
			SetPlayerInterior(playerid, BusinessType[type][E_BUSINESS_TYPE_ENTER_INTER]);
			SetPlayerVirtualWorld(playerid, BusinessInfo[arrayID][E_BUSINESS_ID]);
			SetCameraBehindPlayer(playerid);
			Streamer_Update(playerid);
		}
		case 3: {
			SetPlayerPos(playerid, BusinessType[type][E_BUSINESS_TYPE_ENTER_X], BusinessType[type][E_BUSINESS_TYPE_ENTER_Y], BusinessType[type][E_BUSINESS_TYPE_ENTER_Z]);
			SetPlayerFacingAngle(playerid, BusinessType[type][E_BUSINESS_TYPE_ENTER_ANGLE]);
			SetPlayerInterior(playerid, 15);
			SetPlayerVirtualWorld(playerid, 20);
			SetCameraBehindPlayer(playerid);
			Streamer_Update(playerid);
		}
		case 4,5,6: {
			SetPlayerPos(playerid, BusinessType[type][E_BUSINESS_TYPE_ENTER_X], BusinessType[type][E_BUSINESS_TYPE_ENTER_Y], BusinessType[type][E_BUSINESS_TYPE_ENTER_Z]);
			SetPlayerFacingAngle(playerid, BusinessType[type][E_BUSINESS_TYPE_ENTER_ANGLE]);
			SetPlayerInterior(playerid, BusinessType[type][E_BUSINESS_TYPE_ENTER_INTER]);
			SetPlayerVirtualWorld(playerid, BusinessInfo[arrayID][E_BUSINESS_ID]);
			SetCameraBehindPlayer(playerid);
			Streamer_Update(playerid);
		}
	}
	return true;
}

stock Business.BuyBusiness(const arrayID, const playerid) {
	if(arrayID < 0 || arrayID > MAX_BUSINESS || BusinessInfo[arrayID][E_BUSINESS_ID] == INVALID_BUSINESS_ID) {
		// Если указан неверный ID бизнеса
		return 0;
	}

	if(Player.Business[playerid] != INVALID_BUSINESS_ID) {
		// Если у игрока уже есть бизнес
		return -1;
	} else {
		if(CheckCash(playerid, BusinessInfo[arrayID][E_BUSINESS_PRICE]) == false) {
			// Если у игрока недостаточно денег
			return -2;
		}
		if(BusinessInfo[arrayID][E_BUSINESS_OWNER_ID] != INVALID_ACCOUNT_ID) {
			// Бизнес уже куплен
			return -3;
		}
		RemovePlayerEXP(playerid, BusinessInfo[arrayID][E_BUSINESS_PRICE]);

		BusinessInfo[arrayID][E_BUSINESS_OWNER_ID] = GetPlayerAccountID(playerid);
		BusinessInfo[arrayID][E_BUSINESS_RENT_DAY] = 3;
		BusinessInfo[arrayID][E_BUSINESS_PROD] = 3000;
		BusinessInfo[arrayID][E_BUSINESS_CASH] = 0;
		strmid(BusinessInfo[arrayID][E_BUSINESS_OWNER_NAME], PlayerInfo[playerid][pName], 0, strlen(PlayerInfo[playerid][pName]), MAX_PLAYER_NAME);
		Player.Business[playerid] = arrayID;
		printf("BusinessInfo[arrayID][E_OWNER_NAME] = %s", BusinessInfo[arrayID][E_BUSINESS_OWNER_NAME]);
		Business.CreateLabel(arrayID);

		format(small_string, sizeof(small_string), "UPDATE `biz` SET `OwnerID`=%i, `RentDay` = 3, Prod=2000, Cash=0 WHERE `ID` = %i LIMIT 1", GetPlayerAccountID(playerid), BusinessInfo[arrayID][E_BUSINESS_ID]);
		mysql_pquery(database, small_string);
		// Купили бизнес
		return 1;
	}
}

stock Business.SellBusiness(const arrayID, const playerid = INVALID_PLAYER_ID) {
	if(arrayID < 0 || arrayID > MAX_BUSINESS || BusinessInfo[arrayID][E_BUSINESS_ID] == INVALID_BUSINESS_ID) {
		// Если указан неверный ID бизнеса
		return 0;
	} else {
		if(playerid == INVALID_PLAYER_ID) {

		}

		format(small_string, sizeof(small_string), "UPDATE `biz` SET `OwnerID`=NULL, `RentDay` = 3, Prod=2000, Cash=0 WHERE `ID` = %i LIMIT 1", BusinessInfo[arrayID][E_BUSINESS_ID]);
		mysql_pquery(database, small_string);

		BusinessInfo[arrayID][E_BUSINESS_RENT_DAY] = 3;
		BusinessInfo[arrayID][E_BUSINESS_PROD] = 3000;
		BusinessInfo[arrayID][E_BUSINESS_CASH] = 0;
		BusinessInfo[arrayID][E_BUSINESS_OWNER_ID] = INVALID_ACCOUNT_ID;
		strmid(BusinessInfo[arrayID][E_BUSINESS_OWNER_NAME], "Отсутствует", 0, strlen("Отсутствует"), strlen("Отсутствует"));

		Business.CreateLabel(arrayID);
		return true;
	}
}

stock bool: Business.UpBusinessUpdate(const arrayID) {
	if(arrayID < 0 || arrayID > MAX_BUSINESS || BusinessInfo[arrayID][E_BUSINESS_ID] == INVALID_BUSINESS_ID) {
		return false;
	}

	BusinessInfo[arrayID][E_BUSINESS_UPDATE]++;

	format(small_string, sizeof(small_string), "UPDATE `biz` SET `Upd`=`Upd`+1 WHERE `ID` = %i LIMIT 1", BusinessInfo[arrayID][E_BUSINESS_ID]);
	mysql_pquery(database, small_string);
	return true;
}

stock Business.CreateHealth(const arrayID) {
	if(arrayID < 0 || arrayID > MAX_BUSINESS || BusinessInfo[arrayID][E_BUSINESS_ID] == INVALID_BUSINESS_ID) {
		return 0;
	}

	if(BusinessInfo[arrayID][E_BUSINESS_UPDATE] < 1) {
		return -1;
	}

	if(IsValidDynamicPickup(BusinessInfo[arrayID][E_BUSINESS_HEALH_PICKUP])) {
		DestroyDynamicPickup(BusinessInfo[arrayID][E_BUSINESS_HEALH_PICKUP]);
	}

	if(IsValidDynamicArea(BusinessInfo[arrayID][E_BUSINESS_HEALH_ZONE])) {
		DestroyDynamicArea(BusinessInfo[arrayID][E_BUSINESS_HEALH_ZONE]);
	}

	if(IsValidDynamic3DTextLabel(BusinessInfo[arrayID][E_BUSINESS_HEALH_LABEL])) {
		DestroyDynamic3DTextLabel(BusinessInfo[arrayID][E_BUSINESS_HEALH_LABEL]);
	}

	new
		type = BusinessInfo[arrayID][E_BUSINESS_TYPE];

	if(type == 2) {
		return 0;
	}

	if(type == 3) {
		BusinessInfo[arrayID][E_BUSINESS_HEALH_PICKUP] = CreateDynamicPickup(1240, 23,
			BusinessType[type][E_BUSINESS_HEALTH_X], BusinessType[type][E_BUSINESS_HEALTH_Y], BusinessType[type][E_BUSINESS_HEALTH_Z],
			.interiorid = 15, .worldid = 20
		);
		BusinessInfo[arrayID][E_BUSINESS_HEALH_LABEL] = CreateDynamic3DTextLabel(!""COLOR_BLUE"Аптечка"COLOR_ORANGE"\n(Полностью восстанавливает здоровье)", -1,
			BusinessType[type][E_BUSINESS_HEALTH_X], BusinessType[type][E_BUSINESS_HEALTH_Y], BusinessType[type][E_BUSINESS_HEALTH_Z] + 1.0,
			MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1,
			.interiorid = 15, .worldid = 20
		);
		BusinessInfo[arrayID][E_BUSINESS_HEALH_ZONE] = CreateDynamicSphere(BusinessType[type][E_BUSINESS_HEALTH_X], BusinessType[type][E_BUSINESS_HEALTH_Y], BusinessType[type][E_BUSINESS_HEALTH_Z], 1.00,
			.interiorid = 15, .worldid = 20
		);
	} else {
		BusinessInfo[arrayID][E_BUSINESS_HEALH_PICKUP] = CreateDynamicPickup(1240, 23,
			BusinessType[type][E_BUSINESS_HEALTH_X], BusinessType[type][E_BUSINESS_HEALTH_Y], BusinessType[type][E_BUSINESS_HEALTH_Z],
			.interiorid = BusinessType[type][E_BUSINESS_TYPE_ENTER_INTER], .worldid = BusinessInfo[arrayID][E_BUSINESS_ID]
		);
		BusinessInfo[arrayID][E_BUSINESS_HEALH_LABEL] = CreateDynamic3DTextLabel(!""COLOR_BLUE"Аптечка"COLOR_ORANGE"\n(Полностью восстанавливает здоровье)", -1,
			BusinessType[type][E_BUSINESS_HEALTH_X], BusinessType[type][E_BUSINESS_HEALTH_Y], BusinessType[type][E_BUSINESS_HEALTH_Z] + 1.0,
			MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1,
			.interiorid = BusinessType[type][E_BUSINESS_TYPE_ENTER_INTER], .worldid = BusinessInfo[arrayID][E_BUSINESS_ID]
		);
		BusinessInfo[arrayID][E_BUSINESS_HEALH_ZONE] = CreateDynamicSphere(BusinessType[type][E_BUSINESS_HEALTH_X], BusinessType[type][E_BUSINESS_HEALTH_Y], BusinessType[type][E_BUSINESS_HEALTH_Z], 1.00,
			.interiorid = BusinessType[type][E_BUSINESS_TYPE_ENTER_INTER], .worldid = BusinessInfo[arrayID][E_BUSINESS_ID]
		);
	}
	return 1;
}