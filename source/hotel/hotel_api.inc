#if defined hotel_api_included
	#endinput
#endif

#define hotel_api_included

forward bool:Hotel.BuyHolelPlayer(const arrayID, const accID, const name[]); 
public bool:Hotel.BuyHolelPlayer(const arrayID, const accID, const name[]) {
	Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_ID] = accID;
	strmid(Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_NAME], name, 0, strlen(name), MAX_PLAYER_NAME);
	Hotel.Room[arrayID][E_HOTEL_ROOM_RENT_DAY] = HOTEL_START_RENT_DAY;

	//Hotel.UpdateText(arrayID);

	new 
		targetid = GetPlayerIDFromAccID(accID);

	if(targetid != INVALID_PLAYER_ID) {
		Player.Hotel[targetid] = arrayID;
	}

	format(small_string, sizeof(small_string), "CALL `Hotel.BuyHolelPlayer` (%i , %i);", accID, Hotel.Room[arrayID][E_HOTEL_ROOM_ID]);
	mysql_pquery(database, small_string);
	return true;
}

forward bool:Hotel.SetNullOwner(const arrayID); 
public bool:Hotel.SetNullOwner(const arrayID) {

	new 
		targetid = GetPlayerIDFromAccID(Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_ID]);

	if(targetid != INVALID_PLAYER_ID) {
		Player.Hotel[targetid] = INVALID_HOTEL_ID;
		if(caridhouse[targetid] != INVALID_VEHICLE_ID)
		{
			DestroyVehicle(caridhouse[targetid]);
			caridhouse[targetid] = INVALID_VEHICLE_ID;
		}
	}


	Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_ID] = INVALID_ACCOUNT_ID;
	strmid(Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_NAME], "Отсутствует", 0, strlen("Отсутствует"), MAX_PLAYER_NAME);

	//Hotel.UpdateText(arrayID);

	format(small_string, sizeof(small_string), "CALL `Hotel.SetNullOwner` (%i);", Hotel.Room[arrayID][E_HOTEL_ROOM_ID]);
	mysql_pquery(database, small_string);
	return true;
}

forward Hotel.UpRentDay(const arrayID);
public Hotel.UpRentDay(const arrayID) {
	Hotel.Room[arrayID][E_HOTEL_ROOM_RENT_DAY] ++;

	//Hotel.UpdateText(arrayID);

	format(small_string, sizeof(small_string), "CALL `Hotel.UpRentDay` (%i);", Hotel.Room[arrayID][E_HOTEL_ROOM_ID]);
	mysql_pquery(database, small_string);
	return true;
}


forward Hotel.DownRentDay(const arrayID);
public Hotel.DownRentDay(const arrayID) {
	Hotel.Room[arrayID][E_HOTEL_ROOM_RENT_DAY] --;
	if(Hotel.Room[arrayID][E_HOTEL_ROOM_RENT_DAY] <= 0) {
		Hotel.SetNullOwner(arrayID);
	} else {
		//Hotel.UpdateText(arrayID);

		format(small_string, sizeof(small_string), "CALL `Hotel.DownRentDay` (%i);", Hotel.Room[arrayID][E_HOTEL_ROOM_ID]);
		mysql_pquery(database, small_string);
	}
	return true;
}

forward Hotel.SetRentDay(const arrayID, const dayss);
public Hotel.SetRentDay(const arrayID, const dayss) { 
	Hotel.Room[arrayID][E_HOTEL_ROOM_RENT_DAY] = dayss; 

	format(small_string, sizeof(small_string), "CALL `Hotel.SetRentDay` (%i, %i);", Hotel.Room[arrayID][E_HOTEL_ROOM_ID], dayss); 
	mysql_pquery(database, small_string); 
	return true; 
}

forward bool:Hotel.Show(const arrayID);
public bool:Hotel.Show(const arrayID) {
	printf("ID = %i OwnerID = %i Name = %s Day = %i Inter = %i World = %i", 
		Hotel.Room[arrayID][E_HOTEL_ROOM_ID],
		Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_ID],
		Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_NAME],
		Hotel.Room[arrayID][E_HOTEL_ROOM_RENT_DAY],
		Hotel.Room[arrayID][E_HOTEL_ROOM_INTER],
		Hotel.Room[arrayID][E_HOTEL_ROOM_WOLRD]
	);
	return true;
}

/*stock Hotel.UpdateText(const arrayID) {
	if(Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_ID] == INVALID_ACCOUNT_ID) {
		format(small_string, sizeof(small_string), 
			"Комната "COLOR_GREEN"№%i"COLOR_WHITE"\n\
			Владелец: "COLOR_GREEN"%s"COLOR_WHITE"", 
				Hotel.Room[arrayID][E_HOTEL_ROOM_ID],
				Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_NAME]
		);
	} else {
		format(small_string, sizeof(small_string), 
			"Комната "COLOR_GREEN"№%i"COLOR_WHITE"\n\
			Владелец: "COLOR_ORANGE"%s"COLOR_WHITE"\n\
			Арендована на "COLOR_ORANGE"%i"COLOR_WHITE" дн.", 
				Hotel.Room[arrayID][E_HOTEL_ROOM_ID],
				Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_NAME],
				Hotel.Room[arrayID][E_HOTEL_ROOM_RENT_DAY]
		);
	}
	if(IsValidDynamic3DTextLabel(Hotel.Room[arrayID][E_HOTEL_ROOM_LABEL]) == 0) {
		Hotel.Room[arrayID][E_HOTEL_ROOM_LABEL] = CreateDynamic3DTextLabel(small_string, 0xFFFFFFFF, 
			Hotel.Room[arrayID][E_HOTEL_ROOM_X], Hotel.Room[arrayID][E_HOTEL_ROOM_Y], Hotel.Room[arrayID][E_HOTEL_ROOM_Z] + 1,
			MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 
			.worldid = Hotel.Room[arrayID][E_HOTEL_ROOM_INTER]
		);
	} else {
		UpdateDynamic3DTextLabelText(Hotel.Room[arrayID][E_HOTEL_ROOM_LABEL], 0xFFFFFFFF, small_string);
	}
}*/