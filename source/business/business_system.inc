#if defined business_system_included
	#endinput
#endif

#define business_system_included

#include <source/business/business_header>
#include <source/business/business_api>

#include <YSI-Include\YSI\YSI\y_hooks>

hook OnGameModeInit() {
	new
		local_year,
		local_mouth,
		local_day,
		local_hour,
		local_munite,
		local_second;

	getdate(local_year, local_mouth, local_day);
	gettime(local_hour, local_munite, local_second);

	format(small_string, sizeof(small_string), "business/%i-%02i-%02i %02i-%02i-%02i", local_year, local_mouth, local_day, local_hour, local_munite, local_second);
	printf(small_string);
	businesslog = CreateLog(small_string, DEBUG | INFO | WARNING | ERROR);

	for(new i = 0; i < MAX_BUSINESS; i++) {
		BusinessInfo[i] = NULL_BusinessInfo;
	}
	for(new i = 0; i < MAX_BUSINESS_TYPE; i++) {
		if(i != 2) {
			// Выход из бизнеса
			BusinessType[i][E_BUSINESS_TYPE_EXIT_PICKUP] = CreateDynamicPickup(1318, 23,
				BusinessType[i][E_BUSINESS_TYPE_EXIT_X], BusinessType[i][E_BUSINESS_TYPE_EXIT_Y], BusinessType[i][E_BUSINESS_TYPE_EXIT_Z]
			);
			CreateDynamic3DTextLabel(""COLOR_BLUE"Выход", 0xFFFFFFFF,
				BusinessType[i][E_BUSINESS_TYPE_EXIT_X], BusinessType[i][E_BUSINESS_TYPE_EXIT_Y], BusinessType[i][E_BUSINESS_TYPE_EXIT_Z] + 1.00,
				MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
			);
		}

		// Основное меню бизнеса
		BusinessAction[i][E_BUSINESS_ACTION_PICKUP] = CreateDynamicPickup(BusinessAction[i][E_BUSINESS_ACTION_PICKUP_TYPE], 23,
			BusinessAction[i][E_BUSINESS_ACTION_X], BusinessAction[i][E_BUSINESS_ACTION_Y], BusinessAction[i][E_BUSINESS_ACTION_Z]
		);
		CreateDynamic3DTextLabel(BusinessAction[i][E_BUSINESS_ACTION_TITLE], 0x4eb9e6FF,
			BusinessAction[i][E_BUSINESS_ACTION_X], BusinessAction[i][E_BUSINESS_ACTION_Y], BusinessAction[i][E_BUSINESS_ACTION_Z] + 1.00,
			MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
		);
	}

	// Создание мопедов для закусочных
	for(new i = 0; i < MAX_BUSINESS_TYPE_FOOD * MAX_BUSINESS_FOOD_CAR; i++) {
		BusinessFoodCar[i][E_FOOD_CAR_VEHICLE_ID] = CreateVehicle(448,
			BusinessFoodCar[i][E_FOOD_CAR_X], BusinessFoodCar[i][E_FOOD_CAR_Y], BusinessFoodCar[i][E_FOOD_CAR_Z],
			BusinessFoodCar[i][E_FOOD_CAR_ANGLE],
			42, 0, 25
		);
	}

	// Развозчик пиццы
	BusinessFoodCP = CreateDynamicCP(367.9807, -119.6159, 1001.4922, 1.00);
	BusinessFoodLabel = CreateDynamic3DTextLabel("Работа: "COLOR_ORANGE"доставщик пиццы", 0x4EB9E6FF,
		367.9807, -119.6159, 1001.4922 + 1,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);

	// Покупка продуктов
	CreateDynamicPickup(1239, 23, 2745.1650, -2449.7195, 13.6484);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Закуп продуктов"COLOR_ORANGE"\n(для владельцев бизнесов)", -1,
		2745.1650, -2449.7195, 13.6484 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);
	Business.ZoneBuyProd = CreateDynamicSphere(2745.1650, -2449.7195, 13.6484, 1.00);
	CreateDynamicMapIcon(2745.1650, -2449.7195, 13.6484, 51, -1, 0, 0, -1, 400.0);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnGameModeExit() {
	DestroyLog(businesslog);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnDataBaseConnect() {
	mysql_pquery(database, "SELECT \
		biz.ID, \
		biz.Enter_X, \
		biz.Enter_Y, \
		biz.Enter_Z, \
		biz.Exit_X, \
		biz.Exit_Y, \
		biz.Exit_Z, \
		biz.Exit_Angle, \
		CONVERT(biz.Type, SIGNED) -1 AS Type, \
		biz.Price, \
		IFNULL(biz.OwnerID, -1) AS OwnerID, \
		IFNULL(players.Name, 'Отсутсвует') AS OwnerName, \
		biz.Prod, \
		biz.Upd, \
		biz.MaxProd, \
		biz.Cash, \
		biz.RentPrice, \
		biz.RentDay \
	FROM \
		biz \
	LEFT OUTER JOIN \
		players \
	ON \
		biz.OwnerID = players.ID", "@_LoadBusiness");
}

@_LoadBusiness();
@_LoadBusiness() {
	new
		rows = cache_get_row_count();

	if(rows == 0) {
		Log(businesslog, ERROR, "Отсутсвуют бизнесы для загрузки");
		return;
	} else {
		new
			time = GetTickCount();

		if(rows > MAX_BUSINESS) {
			rows = MAX_BUSINESS;
			Log(businesslog, ERROR, "Отсутсвуют бизнесы для загрузки");
		}
		for(new i = 0; i < rows; i++) {
			BusinessInfo[i][E_BUSINESS_ID] = cache_get_field_content_int(i, "ID");

			BusinessInfo[i][E_BUSINESS_ENTER_X] = cache_get_field_content_float(i, "Enter_X");
			BusinessInfo[i][E_BUSINESS_ENTER_Y] = cache_get_field_content_float(i, "Enter_Y");
			BusinessInfo[i][E_BUSINESS_ENTER_Z] = cache_get_field_content_float(i, "Enter_Z");

			BusinessInfo[i][E_BUSINESS_EXIT_X] = cache_get_field_content_float(i, "Exit_X");
			BusinessInfo[i][E_BUSINESS_EXIT_Y] = cache_get_field_content_float(i, "Exit_Y");
			BusinessInfo[i][E_BUSINESS_EXIT_Z] = cache_get_field_content_float(i, "Exit_Z");
			BusinessInfo[i][E_BUSINESS_EXIT_ANGLE] = cache_get_field_content_float(i, "Exit_Angle");

			BusinessInfo[i][E_BUSINESS_TYPE] = cache_get_field_content_int(i, "Type");
			BusinessInfo[i][E_BUSINESS_PRICE] = cache_get_field_content_int(i, "Price");
			BusinessInfo[i][E_BUSINESS_OWNER_ID] = cache_get_field_content_int(i, "OwnerID");
			cache_get_field_content(i, "OwnerName", BusinessInfo[i][E_BUSINESS_OWNER_NAME]);

			BusinessInfo[i][E_BUSINESS_PROD] = cache_get_field_content_int(i, "Prod");
			BusinessInfo[i][E_BUSINESS_UPDATE] = cache_get_field_content_int(i, "Upd");
			BusinessInfo[i][E_BUSINESS_MAX_PROD] = cache_get_field_content_int(i, "MaxProd");
			BusinessInfo[i][E_BUSINESS_CASH] = cache_get_field_content_int(i, "Cash");
			BusinessInfo[i][E_BUSINESS_RENT_PRICE] = cache_get_field_content_int(i, "RentPrice");
			BusinessInfo[i][E_BUSINESS_RENT_DAY] = cache_get_field_content_int(i, "RentDay");

			BusinessInfo[i][E_BUSINESS_LABEL_ENTER] = CreateDynamic3DTextLabel(" ", 0xFFFFFFFF,
				BusinessInfo[i][E_BUSINESS_ENTER_X], BusinessInfo[i][E_BUSINESS_ENTER_Y], BusinessInfo[i][E_BUSINESS_ENTER_Z] + 1,
				MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
			);
			if(BusinessInfo[i][E_BUSINESS_TYPE] == 2) {
				BusinessInfo[i][E_BUSINESS_PICKUP_ENTER] = CreateDynamicPickup(1239, 23, BusinessInfo[i][E_BUSINESS_ENTER_X], BusinessInfo[i][E_BUSINESS_ENTER_Y], BusinessInfo[i][E_BUSINESS_ENTER_Z]);
			} else {
				BusinessInfo[i][E_BUSINESS_PICKUP_ENTER] = CreateDynamicPickup(1318, 23, BusinessInfo[i][E_BUSINESS_ENTER_X], BusinessInfo[i][E_BUSINESS_ENTER_Y], BusinessInfo[i][E_BUSINESS_ENTER_Z]);
			}
			BusinessInfo[i][E_BUSINESS_MAPICON_ENTER] = CreateDynamicMapIcon(BusinessInfo[i][E_BUSINESS_ENTER_X], BusinessInfo[i][E_BUSINESS_ENTER_Y], BusinessInfo[i][E_BUSINESS_ENTER_Z],
				BusinessType[BusinessInfo[i][E_BUSINESS_TYPE]][E_BUSINESS_TYPE_MAPICON_ID], -1
			);


			Business.PrintArray(i);
			Business.CreateHealth(i);
			Business.CreateLabel(i);
		}
		Log(businesslog, INFO, "Загружено %i бизнесов за %i м.с.", rows, GetTickCount() - time);
	}
}

hook OnPlayerConnect(playerid) {
	Player.Business[playerid] = INVALID_BUSINESS_ID;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason

	Player.Business[playerid] = INVALID_BUSINESS_ID;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerAuthorization(playerid) {
	new
		accID = GetPlayerAccountID(playerid);

	for(new i = 0; i < MAX_BUSINESS; i++) {
		if(BusinessInfo[i][E_BUSINESS_ID] == INVALID_BUSINESS_ID) {
			continue;
		}

		if(BusinessInfo[i][E_BUSINESS_OWNER_ID] == accID) {
			Player.Business[playerid] = i;
			break;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == Business.ZoneBuyProd) {
		if(Player.Business[playerid] == INVALID_BUSINESS_ID) {
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет бизнеса");
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			Dialog_BusinessBuyProd(playerid);
			return Y_HOOKS_CONTINUE_RETURN_1;
		}
	} else {
		for(new i = 0; i < MAX_BUSINESS; i++) {
			if(IsValidDynamicArea(BusinessInfo[i][E_BUSINESS_HEALH_ZONE]) && areaid == BusinessInfo[i][E_BUSINESS_HEALH_ZONE]) {
				if(BusinessInfo[i][E_BUSINESS_OWNER_ID] != INVALID_ACCOUNT_ID && BusinessInfo[i][E_BUSINESS_PROD] < 1) {
		    		SendClientMessage(playerid, -1, ""COLOR_RED"В этом бизнесе недостаточно товара");
		    		return Y_HOOKS_CONTINUE_RETURN_1;
		        }
		        if(CheckCash(playerid, 25) == false) {
		        	return Y_HOOKS_CONTINUE_RETURN_1;
		        }
		        RemovePlayerEXP(playerid, 25);

				Business.SetProd(i, BusinessInfo[i][E_BUSINESS_PROD] - 1);
				// Business.AddCash(i, 25);
				SetPlayerHealth(playerid, 100.00);

				GameTextForPlayer(playerid, "~g~~h~100 HP", 5000, 5);
				return Y_HOOKS_CONTINUE_RETURN_1;
			}
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}
hook OnPlayerPickUpDynPickup(playerid, STREAMER_TAG_PICKUP pickupid) {
	// Вход в бизнесы
	for(new i = 0; i < MAX_BUSINESS; i++) {
		if(BusinessInfo[i][E_BUSINESS_ID] == INVALID_BUSINESS_ID) {
			continue;
		}

		if(BusinessInfo[i][E_BUSINESS_PICKUP_ENTER] == pickupid) {
			if(BusinessInfo[i][E_BUSINESS_OWNER_ID] == INVALID_ACCOUNT_ID) {
				SetPVarInt(playerid, "business__", i);
				SPD(playerid,
					DIALOG_SELECT_BUY_OR_LINK, DIALOG_STYLE_INPUT,
					"Выберите действие",
					""COLOR_WHITE"1. Войти в бизнес\n2. Купить бизнес"INPUT_NUMBER"",
				 	"Далее", "Закрыть"
				);
			} else {
				Business.LinkPlayer(playerid, i);
			}
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}

	// Выход из бизнеса
	for(new i = 0; i < MAX_BUSINESS_TYPE; i++) {
		if(BusinessType[i][E_BUSINESS_TYPE_EXIT_PICKUP] == pickupid) {
			new
				arrayID = INVALID_BUSINESS_ID,
				world = GetPlayerVirtualWorld(playerid);

			for(new b = 0; b < MAX_BUSINESS; b++) {
				if(BusinessInfo[b][E_BUSINESS_ID] == world) {
					arrayID = b;
					break;
				}
			}

			if(arrayID == INVALID_BUSINESS_ID) {
				SendClientMessage(playerid, -1, ""COLOR_RED"Произошла техническая ошибка. Пожалуйста, попросите администрацию помочь Вам выбраться");
				SendClientMessage(playerid, -1, ""COLOR_RED"Отчет об ошибке отправлен разработчикам...");

				Log(businesslog, ERROR, "Ошибка при выходе из бизнеса World = %i", world);
				return Y_HOOKS_BREAK_RETURN_1;
			}

			if(GetPVarInt(playerid, "pizza_job_stoynka") == 1) {
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Стоянка мопедов отмечена "COLOR_RED"красным маркером");
				CreateParkingCP(playerid);
				DeletePVar(playerid, "pizza_job_stoynka");
			}

			SetPlayerPos(playerid, BusinessInfo[arrayID][E_BUSINESS_EXIT_X], BusinessInfo[arrayID][E_BUSINESS_EXIT_Y], BusinessInfo[arrayID][E_BUSINESS_EXIT_Z]);
			SetPlayerFacingAngle(playerid, BusinessInfo[arrayID][E_BUSINESS_EXIT_ANGLE]);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
			SetCameraBehindPlayer(playerid);
			Streamer_Update(playerid);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}

	for(new i = 0; i < MAX_BUSINESS_TYPE; i++) {
		if(BusinessAction[i][E_BUSINESS_ACTION_PICKUP] == pickupid) {
			new
				arrayID = INVALID_BUSINESS_ID,
				world = GetPlayerVirtualWorld(playerid);

			if(i != 2) {
				for(new b = 0; b < MAX_BUSINESS; b++) {
					if(BusinessInfo[b][E_BUSINESS_ID] == world) {
						arrayID = b;
						break;
					}
				}

				if(arrayID == INVALID_BUSINESS_ID) {
					SendClientMessage(playerid, -1, ""COLOR_RED"Произошла техническая ошибка.");
					SendClientMessage(playerid, -1, ""COLOR_RED"Отчет об ошибке отправлен разработчикам...");

					Log(businesslog, ERROR, "Ошибка при открытие основного меню бизнеса World = %i", world);
					return Y_HOOKS_BREAK_RETURN_1;
				}

				new
					type = BusinessInfo[arrayID][E_BUSINESS_TYPE];
			} else {
				for(new b = 0; b < MAX_BUSINESS; b++) {
					if(BusinessInfo[b][E_BUSINESS_TYPE] == 2) {
						arrayID = b;
						break;
					}
				}
			}


			new
				type = BusinessInfo[arrayID][E_BUSINESS_TYPE];

			ShowActionDialog(playerid, type);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP checkpointid) {
	if(checkpointid == BusinessFoodCP) {
		Dialog_JobPizza(playerid);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDialogShowed(const playerid, const e_DIALOG_IDs:dialogid, const response, const listitem, const inputtext[]) {
	if(dialogid == dShop) {
		if(!response) {
			return Y_HOOKS_BREAK_RETURN_1;
		}
		if(response) {

			new value;

			if(Platform[playerid] == 0) {
				value = strval(inputtext) - 1;
			} else {
				value = listitem;
			}

			new
				arrayID = INVALID_BUSINESS_ID,
				world = GetPlayerVirtualWorld(playerid);

			for(new b = 0; b < MAX_BUSINESS; b++) {
				if(BusinessInfo[b][E_BUSINESS_ID] == world) {
					arrayID = b;
					break;
				}
			}

			if(arrayID == INVALID_BUSINESS_ID) {
				SendClientMessage(playerid, -1, ""COLOR_RED"Произошла техническая ошибка.");
				SendClientMessage(playerid, -1, ""COLOR_RED"Отчет об ошибке отправлен разработчикам...");

				Log(businesslog, ERROR, "Ошибка при открытие основного меню бизнеса (dialogid) World = %i", world);
				return Y_HOOKS_BREAK_RETURN_1;
			}

			new
				type = BusinessInfo[arrayID][E_BUSINESS_TYPE];

			if(value < 0 || value > sizeof(BusinessProd_0)) {
				ShowActionDialog(playerid, type);
				return Y_HOOKS_BREAK_RETURN_1;
			}

			if(BusinessInfo[arrayID][E_BUSINESS_PROD] < BusinessProd_0[value][E_BUSINESS_PROD_DOWN]) {
				Log(businesslog, DEBUG, "BusinessInfo[arrayID][E_BUSINESS_PROD] < BusinessProd_0[value][E_BUSINESS_PROD_DOWN] %i %i", BusinessInfo[arrayID][E_BUSINESS_PROD], BusinessProd_0[value][E_BUSINESS_PROD_DOWN]);
				SendClientMessage(playerid, -1, ""COLOR_ORANGE"В бизнесе недостаточно товара.");
				ShowActionDialog(playerid, type);
				return Y_HOOKS_BREAK_RETURN_1;
			}

			switch(value)
			{
				case 0: {
			    	if(PlayerInfo[playerid][pDevice] == 1) {
			    		SendClientMessage(playerid, -1, ""COLOR_RED"У Вас уже есть пейджер");
			    		ShowActionDialog(playerid, type);
			    		return Y_HOOKS_BREAK_RETURN_1;
			    	}
			        if(CheckCash(playerid, 250) == false) {
			        	ShowActionDialog(playerid, type);
			        	return Y_HOOKS_BREAK_RETURN_1;
			        }
			        RemovePlayerEXP(playerid, 250);
			        SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы купили пейджер. Возпользоваться: {FFFFFF}/sms [id]");
			        PlayerInfo[playerid][pDevice] = 1;
					SetPlayerInt(playerid, "Device", PlayerInfo[playerid][pDevice]);
					ShowActionDialog(playerid, type);
			    }
			    case 1: {
			    	if(PlayerInfo[playerid][pDevice] == 2) {
			    		SendClientMessage(playerid, -1, ""COLOR_RED"У Вас уже есть телефон");
			    		ShowActionDialog(playerid, type);
			    		return Y_HOOKS_BREAK_RETURN_1;
			    	}
			        if(CheckCash(playerid, 2000) == false) {
			        	ShowActionDialog(playerid, type);
			        	return Y_HOOKS_BREAK_RETURN_1;
			        }
			        RemovePlayerEXP(playerid, 2000);
			       	SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы купили телефон. Возпользоваться: {FFFFFF}/sms [id]");
			        PlayerInfo[playerid][pDevice] = 2;
					SetPlayerInt(playerid, "Device", PlayerInfo[playerid][pDevice]);
					ShowActionDialog(playerid, type);
			    }
			    case 2: {
			 	    if(GetPVarInt(playerid,"Mask") > 0) {
			 	    	SendClientMessage(playerid, -1, ""COLOR_RED"На вас уже надета маска");
			 	    	ShowActionDialog(playerid, type);
			  			return Y_HOOKS_BREAK_RETURN_1;
			 	    }
			  		if(CheckCash(playerid, 100) == false) {
			  			ShowActionDialog(playerid, type);
			  			return Y_HOOKS_BREAK_RETURN_1;
			  		}
					RemovePlayerEXP(playerid, 100);
					SetPlayerChatBubble(playerid, "надевает маску", C_PURPLE, 10.0, 2000);
					ApplyAnimation(playerid,"SHOP","ROB_shifty",4.1,0,0,0,0,0,1);
					SetPlayerColor(playerid, 0x7a766700);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили и надели маску. Местоположение скрыто");
					SetPVarInt(playerid,"Mask", 1);
					ShowActionDialog(playerid, type);
				}
				case 3: {
			    	if(PlayerInfo[playerid][pScrew] == 1) {
			    		SendClientMessage(playerid, -1, ""COLOR_RED"У Вас уже есть отвертка");
			    		ShowActionDialog(playerid, type);
			    		return Y_HOOKS_BREAK_RETURN_1;
			    	}
			        if(CheckCash(playerid, 15) == false) {
			        	ShowActionDialog(playerid, type);
			        	return Y_HOOKS_BREAK_RETURN_1;
			        }
			        RemovePlayerEXP(playerid, 15);
			        SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы купили отвертку. Возпользоваться: {FFFFFF}/carjack");
			        PlayerInfo[playerid][pScrew] += 1;
					SetPlayerInt(playerid, "Screw", PlayerInfo[playerid][pScrew]);
					ShowActionDialog(playerid, type);
			    }
			}
			// Снимем продукты
			Business.SetProd(arrayID, BusinessInfo[arrayID][E_BUSINESS_PROD] - BusinessProd_0[value][E_BUSINESS_PROD_DOWN]);
			// Добавим денег
			Business.SetCash(arrayID, BusinessInfo[arrayID][E_BUSINESS_CASH] + BusinessProd_0[value][E_BUSINESS_PROD_CASH]);
		}
		return Y_HOOKS_BREAK_RETURN_1;
	}
	if(dialogid == DIALOG_JOB_PIZZA) {
		if(!response) {
			return Y_HOOKS_BREAK_RETURN_1;
		} else {
			new
				value = strval(inputtext);

			switch(value) {
				case 1: {
					new
						world = GetPlayerVirtualWorld(playerid),
						bizID = INVALID_BUSINESS_ID;

					for(new i = 0; i < MAX_BUSINESS; i++) {
						if(world == BusinessInfo[i][E_BUSINESS_ID]) {
							bizID = i;
						}
					}

					if(bizID == INVALID_BUSINESS_ID) {
						SendClientMessage(playerid, -1, ""COLOR_ORANGE"Произошла техническая ошибка #1. Продолжение невозможно");
						return Y_HOOKS_BREAK_RETURN_1;
					}
					if(BusinessInfo[bizID][E_BUSINESS_TYPE] != 1) {
						SendClientMessage(playerid, -1, ""COLOR_ORANGE"Произошла техническая ошибка #2. Продолжение невозможно");
						return Y_HOOKS_BREAK_RETURN_1;
					}

					new
						arrayID = 0;

					switch(bizID) {
						case 8: {
							arrayID = 0;
						}
						case 9: {
							arrayID = 1;
						}
						case 10: {
							arrayID = 2;
						}
						default: {
							SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вакансия не актуальна.");
							return Y_HOOKS_BREAK_RETURN_1;
						}
					}
					switch(InvitePlayerPizzaJob(playerid, arrayID)) {
						case -1: {
							SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже работаете доставщиком пиццы.");
							return Y_HOOKS_BREAK_RETURN_1;
						}
						case 0: {
							return Y_HOOKS_BREAK_RETURN_1;
						}
						case 1: {
							SetPVarInt(playerid, "pizza_job_stoynka", 1);
							SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы устроились доставщиком пиццы.");
							SendClientMessage(playerid, -1, ""COLOR_GREEN"Выйдите из ресторана, и найдите стоянку мопедов.");
							SendClientMessage(playerid, -1, ""COLOR_GREEN"После чего, займите один из свободных мопедов.");
							return Y_HOOKS_BREAK_RETURN_1;
						}
					}
					return Y_HOOKS_BREAK_RETURN_1;
				}
				case 2: {
					if(GetPlayerSkin(playerid) == 155) {
						SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже арендовали форму курьера.");
						return Y_HOOKS_BREAK_RETURN_1;
					}
					if(CheckCash(playerid, PRICE_SKIN_PIZZA) == false) return 1;
	  				RemovePlayerEXP(playerid, PRICE_SKIN_PIZZA);
	  				SetPlayerSkin(playerid, 155);
	  				return Y_HOOKS_BREAK_RETURN_1;
				}
				default: {
					SendClientMessage(playerid, -1, ""COLOR_ORANGE"Указано неверное действие.");
					Dialog_JobPizza(playerid);
					return Y_HOOKS_BREAK_RETURN_1;
				}
			}
		}
	} else if(dialogid == dSnack) {
		if(!response) {
			return Y_HOOKS_BREAK_RETURN_1;
		} else {
			new value;

			if(Platform[playerid] == 0) {
				value = strval(inputtext) - 1;
			} else {
				value = listitem;
			}

			if(CheckCash(playerid, BusinessFood[value][E_FOOD_PRICE]) == false) return 1;
			RemovePlayerEXP(playerid, PRICE_SKIN_PIZZA);

			format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы купили "COLOR_GREEN"%s"COLOR_WHITE" за "COLOR_GREEN"%i EXP", BusinessFood[value][E_FOOD_TITLE], BusinessFood[value][E_FOOD_PRICE]);
			SendClientMessage(playerid, -1, small_string);

			SetPlayerHunger(playerid, GetPlayerHunger(playerid) + BusinessFood[value][E_FOOD_SATIETY]);
            callcmd::hun(playerid, "\0");

            ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1,0,1,1,1,1);

            new hourss, action[32];
            gettime(hourss);
            switch(hourss)
            {
                case 7..12: strcat(action, "завтракает");
                case 13..17: strcat(action, "обедает");
                case 18..23: strcat(action, "ужинает");
                default: strcat(action, "ест");
            }

            format(small_string, sizeof(small_string), "%s: %s", PlayerInfo[playerid][pName], action);
            ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
            SetPlayerChatBubble(playerid, action, C_PURPLE, MAX_DISTANCE_VISIBLE, 10000);

		}
	} else if(dialogid == DIALOG_SELECT_CAR_COLOR) {
		if(!response) {
			return Y_HOOKS_BREAK_RETURN_1;
		} else {
			if(GetPVarInt(playerid, "color__") == 0) {
				SetPVarInt(playerid, "color__", 1);
				ShowActionDialog(playerid, 2);
				return Y_HOOKS_BREAK_RETURN_1;
			} else {
				new value;

				if(value < 0 || value > MAX_BUSINESS_COLOR) {
					ShowActionDialog(playerid, 2);
					SendClientMessage(playerid, -1, ""COLOR_ORANGE"Указан некорректный номер цвета");
					return Y_HOOKS_BREAK_RETURN_1;
				}

				if(CheckCash(playerid, 1000) == false) return 1;
				RemovePlayerEXP(playerid, 1000);

				PlayerPlaySound(playerid, 1098 , 0.0, 0.0, 0.0);
				PlayerInfo[playerid][pCarCol] = BusinessColor[value][E_BUSINESS_COLOR_NUMBER];
				SetPVarInt(playerid, "CarCol", BusinessColor[value][E_BUSINESS_COLOR_NUMBER]);

				ChangeVehicleColor(caridhouse[playerid], PlayerInfo[playerid][pCarCol], PlayerInfo[playerid][pCarCol2]);
				DeletePVar(playerid, "color__");
				return Y_HOOKS_BREAK_RETURN_1;
			}
		}
	}
	if(dialogid == DIALOG_SELECT_BUY_OR_LINK) {
		if(!response) {
			return Y_HOOKS_BREAK_RETURN_1;
		} else {
			new
				value = strval(inputtext);

			if(value != 1 && value != 2) {
				return Y_HOOKS_BREAK_RETURN_1;
			}

			new
				arrayID = GetPVarInt(playerid, "business__");

			DeletePVar(playerid, "business__");

			switch(value) {
				case 1: {
					Business.LinkPlayer(playerid, arrayID);
					return Y_HOOKS_BREAK_RETURN_1;
				}
				case 2: {
					switch(Business.BuyBusiness(arrayID, playerid)) {
						case -1: {
							SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас уже есть бизнес.");
						}
						case -2: {
							SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас недостаточно денег для покупки этого бизнеса.");
						}
						case -3: {
							SendClientMessage(playerid, -1, ""COLOR_ORANGE"Бизнес уже куплен.");
						}
						case 1: {
							SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы успешно приобрели бизнес.");
						}
						default: {
							SendClientMessage(playerid, -1, ""COLOR_ORANGE"Произошла какая-то там ошибка.");
						}
					}
					return Y_HOOKS_CONTINUE_RETURN_1;
				}
			}
		}
	}
	if(dialogid == DIALOG_SELL_BUSINESS) {
		if(!response) {
			return Y_HOOKS_BREAK_RETURN_1;
		} else {
			new
				arrayID = Player.Business[playerid];

			if(arrayID == INVALID_BUSINESS_ID) {
				SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет бизнеса");
				return Y_HOOKS_CONTINUE_RETURN_1;
			}

			new
				price = BusinessInfo[arrayID][E_BUSINESS_PRICE] / 2;

			format(small_string, sizeof(small_string),
				""COLOR_WHITE"Вы продали свой бизнес "COLOR_GREEN"%s"COLOR_WHITE" за "COLOR_GREEN"%i EXP",
				BusinessType[BusinessInfo[arrayID][E_BUSINESS_TYPE]],
				price
			);
			SendClientMessage(playerid, -1, small_string);

			AddPlayerEXP(playerid, price);

			Player.Business[playerid] = INVALID_BUSINESS_ID;

			Business.SellBusiness(arrayID);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	} else if(dialogid == DIALOG_CMD_BUSINESS) {
		if(!response) {
			callcmd::business(playerid, "");
			return Y_HOOKS_BREAK_RETURN_1;
		} else {
			new
				value = strval(inputtext);

			switch(value) {
				case 1: {
					return SPD(playerid,
						DIALOG_INFO, DIALOG_STYLE_MSGBOX,
						"Закупка продуктов",
						""COLOR_WHITE"Для покупки продуктов, отправляетесь в порт\n\
						"COLOR_ORANGE"(/gps 8. Другие места -> 5. Покупка продуктов (для бизнесменов))"COLOR_WHITE"\n\
						Цена за одну единицу продукции составляет "COLOR_GREEN""BUSINESS_PRICE_BUY_PROD_TEXT" EXP"COLOR_WHITE"\n\n\
						"COLOR_GREEN"После оплаты Ващего заказа, продукция на склад\nбизнеса будет доставленна мгновенно.",
						"Закрыть", ""
					);
				}
				case 2: {
					Dialog_BusinessUpdate(playerid);
				}
				default: {
					Dialog_CMD_Business(playerid);
				}
			}
			return Y_HOOKS_BREAK_RETURN_1;
		}
	} else if(dialogid == DIALOG_BUSINESS_UPDATE) {
		if(!response) {
			callcmd::business(playerid, "");
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			new
				value = strval(inputtext);

			switch(value) {
				case 1: {
					SPD(playerid,
						DIALOG_BUSINESS_UPDATE_1, DIALOG_STYLE_MSGBOX,
						!"Улучшение: Аптечка",
						!""COLOR_WHITE"Добавляет в Ваш бизнес аптечку. Встав на нее, игрок\n\
						получает 100 HP. Расходует при этом 1 продукт со\n\
						склада бизнеса. Доход - 25 EXP за использование",
						!"Купить", !"Назад"
					);
				}
				case 2: {
					SPD(playerid,
						DIALOG_BUSINESS_UPDATE_2, DIALOG_STYLE_MSGBOX,
						!"Улучшение: Расширение склада",
						!""COLOR_WHITE"Расширяет склад Вашего бизнеса ровно в два раза",
						!"Купить", !"Назад"
					);
					return Y_HOOKS_CONTINUE_RETURN_1;
				}
				default: {
					Dialog_BusinessUpdate(playerid);
				}
			}
		}
	} else if(dialogid == DIALOG_BUSINESS_UPDATE_1) {
		if(!response) {
			callcmd::business(playerid, "");
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			new
				arrayID = Player.Business[playerid];

			if(arrayID == INVALID_BUSINESS_ID) {
				return -1;
			} else {
				if(BusinessInfo[arrayID][E_BUSINESS_UPDATE] >= 1) {
					SendClientMessage(playerid, -1, "У вас уже куплено данное улучшение.");
					Dialog_BusinessUpdate(playerid);
					return Y_HOOKS_CONTINUE_RETURN_1;
				}
				if(CheckCash(playerid, BUSINESS_CONST_UPDATE_LEVEL_1) == false) {
					Dialog_BusinessUpdate(playerid);
					return Y_HOOKS_CONTINUE_RETURN_1;
				}
	  			RemovePlayerEXP(playerid, BUSINESS_CONST_UPDATE_LEVEL_1);

	  			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили улучшение \"Аптечка\" для вашего бизнеса");

				Business.UpBusinessUpdate(arrayID);
				Business.CreateHealth(arrayID);
				return Y_HOOKS_CONTINUE_RETURN_1;
			}
		}
	} else if(dialogid == DIALOG_BUSINESS_UPDATE_2) {
		if(!response) {
			callcmd::business(playerid, "");
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			new
				arrayID = Player.Business[playerid];

			if(arrayID == INVALID_BUSINESS_ID) {
				return -1;
			} else {
				if(BusinessInfo[arrayID][E_BUSINESS_TYPE] == 2) {
					SendClientMessage(playerid, -1, "Вам недоступно данное улучшение");
					Dialog_BusinessUpdate(playerid);
					return Y_HOOKS_CONTINUE_RETURN_1;
				}
				if(BusinessInfo[arrayID][E_BUSINESS_UPDATE] >= 2) {
					SendClientMessage(playerid, -1, "У вас уже куплено данное улучшение.");
					Dialog_BusinessUpdate(playerid);
					return Y_HOOKS_CONTINUE_RETURN_1;
				}
				if(CheckCash(playerid, BUSINESS_CONST_UPDATE_LEVEL_2) == false) {
					Dialog_BusinessUpdate(playerid);
					return Y_HOOKS_CONTINUE_RETURN_1;
				}
	  			RemovePlayerEXP(playerid, BUSINESS_CONST_UPDATE_LEVEL_2);

	  			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили улучшение \"Расширение склада\" для вашего бизнеса");

				Business.UpBusinessUpdate(arrayID);
				return Y_HOOKS_CONTINUE_RETURN_1;
			}
		}
	} else if(dialogid == DIALOG_BUY_BUSINESS_PROD) {
		if(!response) {
			return Y_HOOKS_CONTINUE_RETURN_1;
		} else {
			new
				arrayID = Player.Business[playerid];

			if(arrayID == INVALID_BUSINESS_ID) {
				return Y_HOOKS_CONTINUE_RETURN_1;
			} else {
				new
					strval_inputtext = strval(inputtext);

				if(strval_inputtext <= 0 || strval_inputtext >= 9999) {
					SendClientMessage(playerid, -1, ""COLOR_WHITE"Значение должно быть в диапозоне от "COLOR_ORANGE"1"COLOR_WHITE" до "COLOR_GREEN"9999");
					Dialog_BusinessBuyProd(playerid);
					return Y_HOOKS_CONTINUE_RETURN_1;
				}
				if(CheckCash(playerid, strval_inputtext * BUSINESS_PRICE_BUY_PROD) == false) {
					Dialog_BusinessBuyProd(playerid);
					return Y_HOOKS_CONTINUE_RETURN_1;
				}

				RemovePlayerEXP(playerid, strval_inputtext * BUSINESS_PRICE_BUY_PROD);

				new
					prod = BusinessInfo[arrayID][E_BUSINESS_PROD],
					max_prod = BusinessInfo[arrayID][E_BUSINESS_MAX_PROD];

				if(BusinessInfo[arrayID][E_BUSINESS_UPDATE] >= 2) {
					max_prod = max_prod * 2;
				}
				if(prod + strval_inputtext > max_prod) {
					SendClientMessage(playerid, -1, ""COLOR_ORANGE"В склад Вашего бизнеса не влезет столько продуктов.");
					format(small_string, sizeof(small_string), ""COLOR_ORANGE"Рекомендуемое значение для покупки - "COLOR_GREEN"%i"COLOR_ORANGE" продуктов", max_prod - prod);
					SendClientMessage(playerid, -1, small_string);
					Dialog_BusinessBuyProd(playerid);
					return Y_HOOKS_CONTINUE_RETURN_1;
				}

				format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы купили %i продуктов для вашего бизнеса.", strval_inputtext);
				SendClientMessage(playerid, -1, small_string);
				Business.SetProd(arrayID, prod + strval_inputtext);
				return Y_HOOKS_CONTINUE_RETURN_1;
			}
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

stock ShowActionDialog(const playerid, const type) {
	switch(type) {
		case 0: {
			if(Platform[playerid] == 0) {
				return SPD(playerid, dShop, DIALOG_STYLE_INPUT, "Магазин 24/7", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP\n4. Отвертка - 15 EXP\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Купить", "Выход");
			} else {
				return SPD(playerid, dShop, DIALOG_STYLE_LIST, "Магазин 24/7", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP\n4. Отвертка - 15 EXP", "Купить", "Выход");
			}
		}
		case 1: {
			big_string[0] = EOS;

			big_string = !"Блюдо\tЦена\n";

			for(new i = 0; i < MAX_BUSINESS_FOOD; i++) {
				format(small_string, sizeof(small_string), ""COLOR_WHITE"%s\t"COLOR_GREEN"%i EXP\n", BusinessFood[i][E_FOOD_TITLE], BusinessFood[i][E_FOOD_PRICE]);
				strcat(big_string, small_string);
			}

			if(Platform[playerid] == 0) {
				return SPD(playerid, dSnack, DIALOG_STYLE_INPUT, "Закусочная", big_string, "Купить", "Выход");
			} else {
				return SPD(playerid, dSnack, DIALOG_STYLE_TABLIST_HEADERS, "Закусочная", big_string, "Купить", "Выход");
			}
		}
		case 2: {
			big_string[0] = EOS;

			for(new i = 0; i < MAX_BUSINESS_COLOR; i++) {
				format(small_string, sizeof(small_string), ""COLOR_WHITE"%i. {%s}%s\n", i, BusinessColor[i][E_BUSINESS_COLOR_HEX], BusinessColor[i][E_BUSINESS_COLOR_TITLE]);
				strcat(big_string, small_string);
			}

			strcat(big_string, INPUT_NUMBER);

			if(GetPVarInt(playerid, "color__") == 0) {
				SPD(playerid, DIALOG_SELECT_CAR_COLOR, DIALOG_STYLE_INPUT, "Выбор первого цвета", big_string, "Далее", "Закрыть");
			} else {
				SPD(playerid, DIALOG_SELECT_CAR_COLOR, DIALOG_STYLE_INPUT, "Выбор второго цвета", big_string, "Далее", "Закрыть");
			}
			return 1;
		}
	}
	return false;
}

stock Dialog_JobPizza(const playerid) {
	return SPD(playerid,
		DIALOG_JOB_PIZZA, DIALOG_STYLE_INPUT,
		(GetPlayerPlatform(playerid) == PLATFORM_ANDROID) ? "Работа: доставщик пиццы" : (""COLOR_BLUE"Работа: "COLOR_ORANGE"доставщик пиццы"),
		""COLOR_WHITE"Привет дружище. В последнее время, жители нашего штата\n\
		прям как с ума посходили. Всем подавай горяченькую пиццу с\n\
		доставкой на дом. У меня не хватает курьеров. Не хочешь\n\
		помочь мне с доставкой заказов?\n\n\
		"COLOR_ORANGE"Информация о работе:"COLOR_WHITE"\n\
		- Тебе необходимо брать пиццу в закусочной и доставлять по\n\
		указанному адресу "COLOR_RED"(красная метка на мини карте)"COLOR_WHITE"\n\
		- Заказ нужно доставить пока пицца не остыла\n\
		- От скорости доставки зависят твои чаевые. Чем быстрее\n\
		привезешь пиццу - тем больше получишь. \n\
		- Клиенты любят опрятный внешний вид курьеров. Если курьер\n\
		будет неопрятно выглядеть то его чаевые будут мизерными.\n\
		Но не беспокойся, мой друг детства владеет швейной\n\
		фабрикой в городе San Fierrro. Он мне поставляет форму\n\
		курьера. Тебе я ее готов отдать по себестоимости\n\n\
		"COLOR_GREEN"Профессиональные навыки:"COLOR_WHITE"\n\
		- Выполнив 25 заказов, отсек под пиццу твоего мопеда будет\n\
		увеличен. Ты сможете брать две пиццы у закусочной за один\n\
		раз.\n\
		- Выполнив 50 заказов, твои чаевые будут увеличены на 15\%\n\
		- Выполнив 100 заказов, стоимость одежды курьера будет\n\
		снижена на 50\%\n\
		- Выполнив 150 заказов, твои чаевые будут увеличены на 30\%\n\
		- Выполнив более 200 заказов, ты сможете брать одежду\n\
		курьера бесплатно. Твои чаевые будут увеличены на 50\%\n\n\
		"COLOR_ORANGE"Доступные действия:"COLOR_WHITE"\n\
		1. Устроиться на работу\n\
		2. Арендовать форму курьера",
		!"Далее", !"Закрыть"
	);
}

CMD:sellbusiness(playerid, params[]) {
	new
		arrayID = Player.Business[playerid];

	if(arrayID == INVALID_BUSINESS_ID) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет бизнеса");
	}

	format(big_string, sizeof(big_string),
		""COLOR_WHITE"Вы уверены, что хотите продать свой бизнес "COLOR_GREEN"%s"COLOR_WHITE"\n\
			за "COLOR_GREEN"%i EXP",
				BusinessType[BusinessInfo[arrayID][E_BUSINESS_TYPE]],
				BusinessInfo[arrayID][E_BUSINESS_PRICE] / 2
	);

	return SPD(playerid,
		DIALOG_SELL_BUSINESS, DIALOG_STYLE_MSGBOX,
		"Продажа бизнеса",
		big_string,
		"Нет", "Да"
	);
}

CMD:business(playerid, params[]) {
	if(Dialog_CMD_Business(playerid) == -1) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет бизнеса.");
	}
	return 1;
}

stock Dialog_CMD_Business(const playerid) {
	if(Player.Business[playerid] == INVALID_BUSINESS_ID) {
		return -1;
	} else {
		new
			arrayID = Player.Business[playerid];

		format(huge_string, sizeof(huge_string),
			""COLOR_WHITE"Тип бизнеса\t\t\t"COLOR_GREEN"%s\n\
			"COLOR_WHITE"Арендован на\t\t\t"COLOR_GREEN"%i дн.\n\
			"COLOR_WHITE"Цена аренды за 1 день\t"COLOR_GREEN"%i EXP.\n\
			"COLOR_WHITE"На счету бизнеса\t\t"COLOR_GREEN"%i EXP.\n\
			"COLOR_WHITE"Продуктов в складе\t\t"COLOR_GREEN"%i шт. из %i шт.\n\
			\t\t\n\
			"COLOR_ORANGE"1. Закупка продуктов\t\n\
			"COLOR_ORANGE"2. Улучшения бизнеса\t"INPUT_NUMBER"",
			BusinessType[BusinessInfo[arrayID][E_BUSINESS_TYPE]],
			BusinessInfo[arrayID][E_BUSINESS_RENT_DAY],
			BusinessInfo[arrayID][E_BUSINESS_RENT_PRICE],
			BusinessInfo[arrayID][E_BUSINESS_CASH],
			BusinessInfo[arrayID][E_BUSINESS_PROD],
			(BusinessInfo[arrayID][E_BUSINESS_UPDATE] >= 2) ? BusinessInfo[arrayID][E_BUSINESS_MAX_PROD] * 2 : BusinessInfo[arrayID][E_BUSINESS_MAX_PROD]
		);

		SPD(playerid,
			DIALOG_CMD_BUSINESS, DIALOG_STYLE_INPUT,
			!"Информация о бизнесе",
			huge_string,
			!"Далее", !"Закрыть"
		);
	}
	return 1;
}

stock Dialog_BusinessUpdate(const playerid) {
	new
		arrayID = Player.Business[playerid];

	if(arrayID == INVALID_BUSINESS_ID) {
		return -1;
	} else {
		return SPD(playerid,
			DIALOG_BUSINESS_UPDATE, DIALOG_STYLE_INPUT,
			""COLOR_BLUE"Улучшения бизнеса",
			""COLOR_WHITE"1\tАптечка\t\t\t"COLOR_GREEN""BUSINESS_CONST_UPDATE_LEVEL_1_TEXT"\n\
			"COLOR_WHITE"2\tРасширение склада\t\t"COLOR_GREEN""BUSINESS_CONST_UPDATE_LEVEL_2_TEXT""INPUT_NUMBER"",
			"Выбрать", "Назад"
		);
	}
}

stock Dialog_BusinessBuyProd(const playerid) {
	new
		arrayID = Player.Business[playerid];

	if(arrayID == INVALID_BUSINESS_ID) {
		return false;
	} else {
		new
			max_prod = BusinessInfo[arrayID][E_BUSINESS_MAX_PROD];

		if(BusinessInfo[arrayID][E_BUSINESS_UPDATE] >= 2) {
			max_prod = max_prod * 2;
		}
		if(BusinessInfo[arrayID][E_BUSINESS_PROD] == max_prod) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"В Вашем бизнесе находится максимальное число продуктов.");
		}

		format(big_string, sizeof(big_string), ""COLOR_WHITE"Введите количество продуктов, которое вы хотите купить для Вашего бизнеса\n\n\
			"COLOR_GREEN"Всего продуктов в вашем бизнесе: %i шт.\n\
			Склад Вашего бизнеса вмещает %i продуктов\n\
			Рекомендуемое значение для покупки - %i",
				BusinessInfo[arrayID][E_BUSINESS_PROD],
				max_prod,
				max_prod - BusinessInfo[arrayID][E_BUSINESS_PROD]
		);
		return SPD(playerid,
			DIALOG_BUY_BUSINESS_PROD, DIALOG_STYLE_INPUT,
			"Покупка продуктов",
			big_string,
			"Купить", "Закрыть"
		);
	}
}