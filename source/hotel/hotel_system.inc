#if defined hotel_system_included
	#endinput
#endif

#define hotel_system_included

#include <source/hotel/hotel_header>
#include <source/hotel/hotel_api>
#include <source/hotel/hotel_rcon>
#include <YSI_Coding\y_hooks>

static 
	Hotel.Inter = 15,
	Hotel.World = 20;

static
	Hotel.Pickup[6],
	Text3D: Hotel.Label[7],
	Hotel.Zone[5];

static 
	Hotel.Floor[] = {
		20,
		21,
		22,
		23,
		24,
		25,
		26,
		27,
		28,
		29,
		30
	};

hook OnGameModeInit() {
	CreateObject(14590, 303.731201, -1532.073242, 40.392261, 0.000000, 0.000000, -24.399999, 300.00); 
	CreateDynamicObject(1566, 297.989349, -1551.985473, 36.306266, 0.000000, 0.000000, -23.699998); 
	CreateDynamicObject(1566, 314.899658, -1514.632446, 36.306266, 0.000000, 0.000000, -23.699998); 
	//CreateDynamicObject(2613, 303.182647, -1533.280761, 35.079761, 0.000000, 0.000000, 0.000000); 
	CreateObject(15033, 335.170928, -1492.662963, 35.039062, 0.000000, 0.000000, -135.900009, 300.000); 
	CreateDynamicObject(1569, 322.987457, -1498.284057, 35.046875, 0.000000, 0.000000, -45.899990); 
	CreateDynamicObject(1556, 326.442077, -1498.687255, 35.046875, 0.000000, 0.000000, 42.400005); 
	CreateDynamicObject(2575, 336.381439, -1491.014770, 35.446857, 0.000000, 0.000000, -135.699996); 
	CreateDynamicObject(1820, 332.175628, -1496.261962, 34.936885, 0.000000, 0.000000, -9.900000); 
	CreateDynamicObject(2576, 328.970062, -1491.103881, 35.046875, 0.000000, 0.000000, 44.400001); 
	CreateDynamicObject(2568, 331.550109, -1488.521606, 35.036876, 0.000000, 0.000000, 43.900012); 
	CreateDynamicObject(2572, 334.120513, -1494.766845, 35.046875, 0.000000, 0.000000, -174.500015); 
	CreateDynamicObject(1786, 330.369079, -1489.270507, 36.176876, 0.000000, 0.000000, 44.500003); 
	CreateDynamicObject(2593, 325.260986, -1494.344482, 35.896877, 0.000000, 0.000000, 0.000000); 
	CreateDynamicObject(2654, 325.962707, -1493.743652, 35.256870, 0.000000, 0.000000, -75.199989); 

	// Двери:
	CreateDynamicObject(1569, 316.899627, -1513.563354, 23.921875, 0.000000, 0.000000, 55.099983, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1569, 318.614257, -1511.104370, 23.921875, 0.000000, 0.000000, -125.199974, -1, -1, -1, 300.00, 300.00);
	
	Hotel.Pickup[0] = CreateDynamicPickup(1318, 23, 325.8003, -1514.4475, 36.0325);
	Hotel.Label[0] = CreateDynamic3DTextLabel(""COLOR_BLUE"Отель Rodeo", 0xFFFFFFFF, 
		325.8003, -1514.4475, 37.0325, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1,
		0, 0
	);
	CreateDynamicMapIcon(325.8003, -1514.4475, 36.0325, 35, -1, 0, 0);

	Hotel.Pickup[1] = CreateDynamicPickup(1318, 23, 315.4896, -1515.3247, 36.0923, 
		.worldid = Hotel.World, .interiorid = Hotel.Inter);
	Hotel.Label[1] = CreateDynamic3DTextLabel(""COLOR_BLUE"Выход", 0xFFFFFFFF, 
		315.4896, -1515.3247, 37.0923, 
		3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 
		.worldid = Hotel.World, .interiorid = Hotel.Inter
	);

	Hotel.Pickup[2] = CreateDynamicPickup(1318, 23, 303.5466, -1532.1730, 36.0798, 
		.interiorid = Hotel.Inter);
	Hotel.Label[2] = CreateDynamic3DTextLabel(""COLOR_BLUE"Лифт", 0xFFFFFFFF, 
		303.5466, -1532.1730, 37.0798,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 
		.interiorid = Hotel.Inter
	);
	Hotel.Zone[0] = CreateDynamicSphere(303.5466, -1532.1730, 36.0798, 1.00, 
		.interiorid = Hotel.Inter);

	Hotel.Pickup[3] = CreateDynamicPickup(1239, 23, 330.4706, -1494.8337, 36.0469);
	/*Hotel.Label[3] = CreateDynamic3DTextLabel(""COLOR_BLUE"Информация", 0xFFFFFFFF, 
		330.4706, -1494.8337, 37.0469,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);*/
	Hotel.Zone[3] = CreateDynamicSphere(330.4706, -1494.8337, 36.0469, 1.00);

	Hotel.Label[4] = CreateDynamic3DTextLabel(""COLOR_BLUE"Выход", 0xFFFFFFFF, 
		323.8458, -1498.5768, 37.0469,
		3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);

	Hotel.Pickup[4] = CreateDynamicPickup(1318, 23, 298.8803, -1551.9344, 36.0923, .worldid = Hotel.World, .interiorid = Hotel.Inter);
	Hotel.Label[5] = CreateDynamic3DTextLabel(""COLOR_BLUE"Выход на парковку\n"COLOR_ORANGE"(Личные автомобили)", 0xFFFFFFFF, 
		298.8803, -1551.9344, 37.0923,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1,
		.worldid = Hotel.World, .interiorid = Hotel.Inter
	);

	Hotel.Pickup[5] = CreateDynamicPickup(1318, 23, 317.4261, -1512.0807, 24.9219);
	Hotel.Label[6] = CreateDynamic3DTextLabel(""COLOR_BLUE"Вход в отель", 0xFFFFFFFF, 
		317.4261, -1512.0807, 25.9219,
		6.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1,
		0, 0
	);

	Hotel.Label[6] = CreateDynamic3DTextLabel(""COLOR_GREEN"Спавн личного автомобиля", 0xFFFFFFFF, 
		307.4381, -1519.0620, 25.9219,
		10, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1,
		0, 0
	);
	new 
		data[2];

	for(new i = 0; i < 88; i++) {

		/*format(small_string, sizeof(small_string), 
			"Комната "COLOR_GREEN"№%i"COLOR_WHITE"\nВладелец: %s", 
				Hotel.Room[i][E_HOTEL_ROOM_ID]
		);
		Hotel.Room[i][E_HOTEL_ROOM_LABEL] = CreateDynamic3DTextLabel(small_string, 0xFFFFFFFF, 
			Hotel.Room[i][E_HOTEL_ROOM_X], Hotel.Room[i][E_HOTEL_ROOM_Y], Hotel.Room[i][E_HOTEL_ROOM_Z] + 1,
			MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 
			.worldid = Hotel.Room[i][E_HOTEL_ROOM_INTER]
		);*/

		Hotel.Room[i][E_HOTEL_ROOM_PICKUP] = CreateDynamicPickup(19523, 23, 
			Hotel.Room[i][E_HOTEL_ROOM_X], Hotel.Room[i][E_HOTEL_ROOM_Y], Hotel.Room[i][E_HOTEL_ROOM_Z],
			.worldid = Hotel.Room[i][E_HOTEL_ROOM_INTER]
		);

		Hotel.Room[i][E_HOTEL_AREA] = CreateDynamicSphere(
			Hotel.Room[i][E_HOTEL_ROOM_X], Hotel.Room[i][E_HOTEL_ROOM_Y], Hotel.Room[i][E_HOTEL_ROOM_Z],
			0.50,
			.worldid = Hotel.Room[i][E_HOTEL_ROOM_INTER]
		);

		data[0] = STREAMER_TYPE_HOTEL_PICKUP;
		data[1] = i;
		Streamer_SetArrayData(STREAMER_TYPE_AREA, Hotel.Room[i][E_HOTEL_AREA], E_STREAMER_EXTRA_ID, data);
	}

	for(new i = 0; i < 88; i++) {
		Hotel.Room[i][E_HOTEL_PICKUP_EXIT] = CreateDynamicPickup(1318, 23, 
			323.8458, -1498.5768, 36.0469,
			.worldid = Hotel.Room[i][E_HOTEL_ROOM_WOLRD], .interiorid = Hotel.Room[i][E_HOTEL_ROOM_INTER]
		);

		data[0] = STREAMER_TYPE_HOTEL_PICKUP_EXIT;
		data[1] = i;
		Streamer_SetArrayData(STREAMER_TYPE_PICKUP, Hotel.Room[i][E_HOTEL_PICKUP_EXIT], E_STREAMER_EXTRA_ID, data);
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnDataBaseConnect() {
	mysql_tquery(database, "SELECT \
			ph.ID, \
			IFNULL(ph.PlayerID, -1) AS PlayerID, \
			ph.Day, \
			IFNULL(p.Name, \"Отсутствует\") as Name \
		FROM \
			player_hotel AS ph \
		LEFT OUTER JOIN \
			players AS p \
		ON \
			p.ID = ph.PlayerID", "@_LoadHotel");
}

@_LoadHotel();
@_LoadHotel() {
	new rows = cache_get_row_count();

	if(!rows) {
		printf("Отсутствуют отели для загрузки");
	} else {
		if(rows > MAX_HOTEL_ROOM) {
			rows = MAX_HOTEL_ROOM;
		}

		new 
			temp_int;
		
		for(new i = 0; i < rows; i++) {
			temp_int = cache_get_field_content_int(i, "ID");
			if(temp_int != Hotel.Room[i][E_HOTEL_ROOM_ID]) {
				printf("Ошибка при загрузки комнаты с ID = %i (%i)", temp_int, Hotel.Room[i][E_HOTEL_ROOM_ID]);
				continue;
			}

			Hotel.Room[i][E_HOTEL_ROOM_ID] = temp_int;
			Hotel.Room[i][E_HOTEL_ROOM_OWNER_ID] = cache_get_field_content_int(i, "PlayerID");
			Hotel.Room[i][E_HOTEL_ROOM_RENT_DAY] = cache_get_field_content_int(i, "Day");
			cache_get_field_content(i, "Name", Hotel.Room[i][E_HOTEL_ROOM_OWNER_NAME]);

			//Hotel.UpdateText(i);
		}

		printf("Загружено %i номеров отеля", rows);
	}
}

@_PlayerHotelSpawnCar(playerid);
@_PlayerHotelSpawnCar(playerid) {
	new 
		arrayID = Player.Hotel[playerid];

	if(arrayID == INVALID_HOTEL_ID) {
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы не проживаете в этом отеле.");
		return false;
	} else {
		Dialog_AcceptParkCar(playerid);
		return true;
	}
}

hook OnPlayerPickUpDynPickup(playerid, STREAMER_TAG_PICKUP pickupid) {
	if(pickupid == Hotel.Pickup[0]) {
		SetPlayerPos(playerid, 314.7547, -1516.7831, 36.0899);
		SetPlayerFacingAngle(playerid, 145.000);
		SetPlayerInterior(playerid, Hotel.Inter);
		SetPlayerVirtualWorld(playerid, Hotel.World);
		SetCameraBehindPlayer(playerid);
		return Y_HOOKS_CONTINUE_RETURN_1;
	}

	if(pickupid == Hotel.Pickup[1]) {
		SetPlayerPos(playerid, 327.7896, -1515.9894, 36.0391);
		SetPlayerFacingAngle(playerid, 235.000);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetCameraBehindPlayer(playerid);
		return Y_HOOKS_CONTINUE_RETURN_1;
	}
	if(pickupid == Hotel.Pickup[2] || pickupid == Hotel.Pickup[3]) {
		return Y_HOOKS_CONTINUE_RETURN_1;
	}
	if(pickupid == Hotel.Pickup[4]) {
		SetPlayerPos(playerid, 313.0134,-1511.6830,24.9219);
		SetPlayerFacingAngle(playerid, 55.000);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetCameraBehindPlayer(playerid);
		return Y_HOOKS_CONTINUE_RETURN_1;
	}
	if(pickupid == Hotel.Pickup[5]) {
		SetPlayerPos(playerid, 299.5829, -1550.2896, 36.0897);
		SetPlayerFacingAngle(playerid, 337.7017);
		SetPlayerInterior(playerid, Hotel.Inter);
		SetPlayerVirtualWorld(playerid, Hotel.World);
		SetCameraBehindPlayer(playerid);
		return Y_HOOKS_CONTINUE_RETURN_1;
	}


	new 
		data[2];

	Streamer_GetArrayData(STREAMER_TYPE_PICKUP, pickupid, E_STREAMER_EXTRA_ID, data);
	if(data[0] == STREAMER_TYPE_HOTEL_PICKUP_EXIT) {
		new 
			arrayID = data[1];

		SetPlayerPos(playerid, Hotel.Room[arrayID][E_HOTEL_ROOM_EXIT_X], Hotel.Room[arrayID][E_HOTEL_ROOM_EXIT_Y], Hotel.Room[arrayID][E_HOTEL_ROOM_EXIT_Z]);
		SetPlayerFacingAngle(playerid, Hotel.Room[arrayID][E_HOTEL_ROOM_EXIT_ANGLE]);
		SetPlayerInterior(playerid, Hotel.Inter);
		SetPlayerVirtualWorld(playerid, Hotel.Room[arrayID][E_HOTEL_ROOM_INTER]);
		return Y_HOOKS_CONTINUE_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}


hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == Hotel.Zone[0]) {
		Dialog_HotelSelectFloor(playerid);
		return Y_HOOKS_CONTINUE_RETURN_1;
	} else if(areaid == Hotel.Zone[3]) {
		Dialog_ShowHotelInfo(playerid);
		return Y_HOOKS_CONTINUE_RETURN_1;
	}

	new 
		data[2];

	Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, data);
	if(data[0] == STREAMER_TYPE_HOTEL_PICKUP) {
		new 
			arrayID = data[1];

		if(Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_ID] == INVALID_ACCOUNT_ID) {
			Dialog_RentHotelRoom(playerid, arrayID);
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			if(Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_ID] != GetPlayerAccountID(playerid)) {

				format(small_string, sizeof(small_string), 
					"Комната "COLOR_GREEN"№%i"COLOR_WHITE" | Владелец: %s", 
						Hotel.Room[arrayID][E_HOTEL_ROOM_ID],
						Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_NAME]
				);
				SendClientMessage(playerid, -1, small_string);
				return Y_HOOKS_CONTINUE_RETURN_1;
			} else {
				SetPlayerPos(playerid, 325.8442, -1496.4528, 36.0469);
				SetPlayerFacingAngle(playerid, 315.000);
				SetCameraBehindPlayer(playerid);
				SetPlayerInterior(playerid, Hotel.Room[arrayID][E_HOTEL_ROOM_INTER]);
				return SetPlayerVirtualWorld(playerid, Hotel.Room[arrayID][E_HOTEL_ROOM_WOLRD]);
			}
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

static stock Dialog_HotelSelectFloor(playerid) {
	return SPD(playerid, 
		DIALOG_HOTEL_SELECT_FLOOR, DIALOG_STYLE_INPUT, 
		"Выбор этажа", 
		""COLOR_WHITE"1. 1 этаж\n\
		2. 2 этаж\n\
		3. 3 этаж\n\
		4. 4 этаж\n\
		5. 5 этаж\n\
		6. 6 этаж\n\
		7. 7 этаж\n\
		8. 8 этаж\n\
		9. 9 этаж\n\
		10. 10 этаж\n\
		11. 11 этаж\n\n\
		"COLOR_BLUE"Введите номер этажа для продолжения", 
		"Далее", "Закрыть"
	);
}


hook OnPlayerDialogShowed(const playerid, const e_DIALOG_IDs:dialogid, const response, const listitem, const inputtext[]) {
	if(dialogid == DIALOG_HOTEL_SELECT_FLOOR) {
		if(!response) {
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			new 
				strval_inputtext = strval(inputtext);
			//printf("strval_inputtext = %i", strval_inputtext);
			if(strval_inputtext <= 0 || strval_inputtext > 11) {
				SendClientMessage(playerid, -1, ""COLOR_ORANGE"Указан неверный номер этажа (1 - 11)");
				Dialog_HotelSelectFloor(playerid);
				return Y_HOOKS_CONTINUE_RETURN_1;
			} else {
				SetPlayerPos(playerid, 304.9746, -1532.7676, 36.0798);
				SetPlayerFacingAngle(playerid, 250.000);
				SetPlayerVirtualWorld(playerid, Hotel.Floor[strval_inputtext - 1]);
				return Y_HOOKS_CONTINUE_RETURN_1;
			}
		}

	} else if(dialogid == DIALOG_RENT_HOTEL) {
		if(!response) {
			DeletePVar(playerid, "hotel_arrayID");
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			new 
				arrayID = GetPVarInt(playerid, "hotel_arrayID");

			DeletePVar(playerid, "hotel_arrayID");	

			if(PlayerInfo[playerid][pScore] < HOTEL_RENT_PRICE) {
				SendClientMessage(playerid, -1, ""COLOR_RED"У вас недостаточно денег.");
				return Y_HOOKS_CONTINUE_RETURN_1;
			} else {
				if(Hotel.Room[arrayID][E_HOTEL_ROOM_OWNER_ID] != INVALID_ACCOUNT_ID) {
					SendClientMessage(playerid, -1, ""COLOR_ORANGE"Этот номер уже арендован другим игроком");
					return Y_HOOKS_CONTINUE_RETURN_1;
				}
				if(GetPlayerHouse(playerid) > 0) {
					SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас есть дом. Аренда номера в отеле невозможна.");
					return Y_HOOKS_CONTINUE_RETURN_1;
				}
				if(Player.Hotel[playerid] != INVALID_HOTEL_ID) {
					SendClientMessage(playerid, -1, ""COLOR_RED"У вас уже арендован номер в отеле.");
					return Y_HOOKS_CONTINUE_RETURN_1;
				}
				RemovePlayerEXP(playerid, HOTEL_RENT_PRICE, "Аренда номера в отеле");
				Hotel.BuyHolelPlayer(arrayID, GetPlayerAccountID(playerid), PlayerInfo[playerid][pName]);
				Dialog_ShowHotelInfoRentRoom(playerid, arrayID);
			}
			return Y_HOOKS_CONTINUE_RETURN_1;
		}
	} else if(dialogid == DIALOG_STYLE_PARK_CAR) {
		if(!response) {
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			new 
				car = caridhouse[playerid];
			foreach(new i: Player) {
				if(IsPlayerInVehicle(i, car)) {
					SendClientMessage(playerid, -1, ""COLOR_ORANGE"В данный момент нельзя совершить это действие. Поробуйте позжее");
					return Y_HOOKS_CONTINUE_RETURN_1;
				}
			}
			if(caridhouse[playerid] != INVALID_VEHICLE_ID) {
				if(PlayerInfo[playerid][pScore] < 50) {
					SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас недостаточно денег.");
					return Y_HOOKS_CONTINUE_RETURN_1;
				} else {
					RemovePlayerEXP(playerid, 50, "Парковка в отеле");
				}
			}
			LoadCarPlayerId(playerid);
			return Y_HOOKS_CONTINUE_RETURN_1;
		}
	} else if(dialogid == DIALOG_SELL_HOTEL) {
		if(!response) {
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			new 
				arrayID = Player.Hotel[playerid];

			if(arrayID == INVALID_HOTEL_ID) {
				SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы не проживаете в отеле.");
				return Y_HOOKS_CONTINUE_RETURN_1;
			} else {
				Hotel.SetRentDay(arrayID, 0);
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы будете выселены сегодня в 05:00 (МСК)");
				return Y_HOOKS_CONTINUE_RETURN_1;
			}
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerConnect(playerid) {
	new checkpoinid = CreatePlayerCP(playerid, 307.4381, -1519.0620, 24.9219, "@_PlayerHotelSpawnCar");
	EnabledPlayerCPDestoy(playerid, checkpoinid, false);

	Player.Hotel[playerid] = INVALID_HOTEL_ID;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	Player.Hotel[playerid] = INVALID_HOTEL_ID;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerAuthorization(playerid) {
	//printf("OnPlayerAuthorization");
	new 
		accID = GetPlayerAccountID(playerid);
	//printf("accID = %i", accID);
	for(new i = 0; i < MAX_HOTEL_ROOM; i++) {
		//printf("E_HOTEL_ROOM_OWNER_ID = %i", Hotel.Room[i][E_HOTEL_ROOM_OWNER_ID]);
		if(Hotel.Room[i][E_HOTEL_ROOM_OWNER_ID] == accID) {
			Player.Hotel[playerid] = i;
			//printf("arrayID = %i arrayID", i);
			break;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

CMD:exithotel(playerid, params[]) {
	if(Player.Hotel[playerid] == INVALID_HOTEL_ID) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы не проживаете в отеле.");
	} else {
		return Dialog_SellHotel(playerid);
	}
}

stock Dialog_SellHotel(const playerid) {
	if(Player.Hotel[playerid] == INVALID_HOTEL_ID) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы не проживаете в отеле.");
	} else {
		return SPD(playerid, DIALOG_SELL_HOTEL, DIALOG_STYLE_MSGBOX, "Выселение из отеля", ""COLOR_WHITE"Вы уверены, что хотите выселиться из отеля?\n\n\
			"COLOR_ORANGE"Внимание! Средства за оплаченные дни не будут возвращены\nВы будете выселены со следующим рестартом в 5:00 МСК", "Да", "Нет");
	} 
}
stock Dialog_RentHotelRoom(const playerid, const arrayID) {
	SetPVarInt(playerid, "hotel_arrayID", arrayID);

	format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы уверены, что хотите арендовать\n\
		комнату "COLOR_GREEN"№%i"COLOR_WHITE" за "COLOR_GREEN"%i EXP"COLOR_WHITE" в день", 
		Hotel.Room[arrayID][E_HOTEL_ROOM_ID],
		HOTEL_RENT_PRICE
	);
	return SPD(playerid, DIALOG_RENT_HOTEL, DIALOG_STYLE_MSGBOX, "Аренда комнаты", small_string, "Да", "Нет");
}

stock Dialog_ShowHotelInfoRentRoom(const playerid, const arrayID) {
	format(huge_string, sizeof(huge_string), ""COLOR_WHITE"Поздравляем! Вы арендовали комнату "COLOR_GREEN"№%i"COLOR_WHITE" в отелe \"Rodeo\"\n\
		Длительность аренды на текущий момент составляет "COLOR_GREEN"%i дн."COLOR_WHITE"\n\
		Для продления аренды, обратитесь в отделения банка "COLOR_ORANGE"\n\
		(/gps - Общественные места - Банк)\n\n\
		У вас появилась возможность пользоваться личным транспортом. \n\
		Для этого спуститесь на первый этаж\n\
		и встаньте на белую стрелочку с надписью \"Парковка\"", 

		Hotel.Room[arrayID][E_HOTEL_ROOM_ID],
		Hotel.Room[arrayID][E_HOTEL_ROOM_RENT_DAY]
	);
	return SPD(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, "Информация о аренде отеля", huge_string, "Закрыть", "");
}

stock Dialog_ShowHotelInfo(const playerid) {
	new 
		arrayID = Player.Hotel[playerid];

	if(arrayID == INVALID_HOTEL_ID) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы не проживаете в этом отеле");
	} else {
		format(huge_string, sizeof(huge_string), ""COLOR_WHITE"Вы арендуете комнату "COLOR_GREEN"№%i"COLOR_WHITE" в отелe \"Rodeo\"\n\
			Длительность аренды на текущий момент составляет "COLOR_GREEN"%i дн."COLOR_WHITE"\n\
			Для продления аренды, обратитесь в отделения банка "COLOR_ORANGE"\n\
			(/gps - Общественные места - Банк)\n\n\
			У вас есть возможность пользоваться личным транспортом. \n\
			Для этого спуститесь на первый этаж\n\
			и встаньте на белую стрелочку с надписью \"Парковка\"\n\n\
			Для выселения из отеля используйте команду: "COLOR_GREEN"/exithotel", 

			Hotel.Room[arrayID][E_HOTEL_ROOM_ID],
			Hotel.Room[arrayID][E_HOTEL_ROOM_RENT_DAY]
		);
		return SPD(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, "Информация о аренде отеля", huge_string, "Закрыть", "");
	}
}

stock Dialog_AcceptParkCar(const playerid) {
	if(PlayerInfo[playerid][pCar] == 509) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет автомобиля.");
	} else {
		if(caridhouse[playerid] != INVALID_VEHICLE_ID) {
			return SPD(playerid, DIALOG_STYLE_PARK_CAR, DIALOG_STYLE_MSGBOX, 
				"Парковка автомобиля", ""COLOR_WHITE"Вы уверены, что хотите подогнать\n\
				свой транспорт к отелю?\n\n\
				"COLOR_ORANGE"Цена услуги составляет: "COLOR_GREEN"50 EXP", "Да", "Нет"
			);
		} else {
			return SPD(playerid, DIALOG_STYLE_PARK_CAR, DIALOG_STYLE_MSGBOX, 
				"Парковка автомобиля", ""COLOR_WHITE"Вы уверены, что хотите подогнать\n\
				свой транспорт к отелю?\n\n\
				"COLOR_ORANGE"Цена услуги составляет: "COLOR_GREEN"0 EXP (Бесплатно)", "Да", "Нет"
			);
		}
	}
}