#if defined casino_system_included
	#endinput
#endif

#define casino_system_included

#if !defined INVALID_DYNAMIC_AREA_ID
	#define INVALID_DYNAMIC_AREA_ID 						(-1)
#endif

#if !defined INVALID_PICKUP_ID
	#define INVALID_PICKUP_ID 								(-1)
#endif

#if !defined MAX_TABLE_CASINO
	#define MAX_TABLE_CASINO 								(2) // Максимальное число игровых столиков в казино
#endif

#if !defined TABLE_SIZE
	#define TABLE_SIZE 										(2.00) // Радиус стола
#endif

#if !defined OFFSET_Z
	#define OFFSET_Z 										(0.90)
#endif

#if !defined MAX_DRAWN_DISTANCE 	
	#define MAX_DRAWN_DISTANCE 								(18.00)
#endif

#if !defined STREAMER_TYPE_CASINO_CROUPIER
	#define STREAMER_TYPE_CASINO_CROUPIER 					(7843)
#endif

#if !defined STREAMER_TYPE_CASINO_PLAYER 
	#define STREAMER_TYPE_CASINO_PLAYER 					(7845)
#endif

#if !defined CASION_CROUPIER_AREA_SIZE 	
	#define CASION_CROUPIER_AREA_SIZE 						(1.00)
#endif

#if !defined CASION_CROUPIER_AREA_SIZE
	#define CASION_CROUPIER_AREA_SIZE 						(1.00)
#endif

enum 
	casino_info {
		CI_Table_ID, 										// Номер столика
		CI_Table_AreaID, 									// ID динамичной зоны для столика
		Text3D: CI_Table_Label,								// 3D Text над столиком
		Float: CI_Table_X, 									// Координата столика (X)
		Float: CI_Table_Y, 									// Координата столика (Y)
		Float: CI_Table_Z, 									// Координата столика (Z)
		CI_Table_Inter,  									// Интерьер столика
		CI_Table_World, 									// Виртуальный мир столика
		CI_Table_Sum, 										// Ставка стола
		CI_Table_Timer, 									// ID таймера для стола

		CI_CroupierID, 										// ID Крупье у стола
		Float: CI_Croupier_X, 								// Координата крупье (X)
		Float: CI_Croupier_Y, 								// Координата крупье (Y)
		Float: CI_Croupier_Z, 								// Координата крупье (Z)
		CI_Croupier_Pickup, 								// ID пикапа для крупье
		CI_Croupier_Area, 									// ID динамической зоны для крупье
		Text3D: CI_Croupier_Label, 							// ID 3D текста для крупье

		CI_Player1, 										// ID игрока, играющего (первый)
		CI_Pickup1, 										// ID пикапа для игрока (первый)
		Text3D: CI_Label1,									// ID 3D текста (первый)
		CI_Area1, 											// ID Динамичной зоны для игрока (первый)
		Float: CI_X1, 										// Координата пикапа и зоны X (первая)
		Float: CI_Y1, 										// Координата пикапа и зоны Y (первая)
		Float: CI_Z1, 										// Координата пикапа и зоны Z (первая)

		CI_Player2, 										// ID игрока, играющего (второй)
		CI_Pickup2, 										// ID пикапа для игрока (второй)
		Text3D: CI_Label2,									// ID 3D текста (второй)
		CI_Area2, 											// ID Динамичной зоны для игрока (второй)
		Float: CI_X2, 										// Координата пикапа и зоны X (вторая)
		Float: CI_Y2, 										// Координата пикапа и зоны Y (вторая)
		Float: CI_Z2 										// Координата пикапа и зоны Z (вторая)
	};
 
new CasinoInfo[MAX_TABLE_CASINO][casino_info] = {
	{1, INVALID_DYNAMIC_AREA_ID, INVALID_3DTEXT_ID, 1011.4888, -1195.6183, 30.6630, -1, -1, 500, INVALID_TIMER_ID,
		INVALID_PLAYER_ID, 1011.3844, -1196.9115, 29.6481, INVALID_PICKUP_ID, INVALID_DYNAMIC_AREA_ID, INVALID_3DTEXT_ID,
		INVALID_PLAYER_ID, INVALID_PICKUP_ID, INVALID_3DTEXT_ID, INVALID_DYNAMIC_AREA_ID, 1012.6677, -1194.2783, 29.6481,
		INVALID_PLAYER_ID, INVALID_PICKUP_ID, INVALID_3DTEXT_ID, INVALID_DYNAMIC_AREA_ID, 1010.1858, -1194.3226, 29.6481
	},
	{2, INVALID_DYNAMIC_AREA_ID, INVALID_3DTEXT_ID, 1016.9261, -1203.8380, 32.0430, -1, -1, 100, INVALID_TIMER_ID,
		INVALID_PLAYER_ID, 1016.6971, -1205.0391, 31.05351, INVALID_PICKUP_ID, INVALID_DYNAMIC_AREA_ID, INVALID_3DTEXT_ID,
		INVALID_PLAYER_ID, INVALID_PICKUP_ID, INVALID_3DTEXT_ID, INVALID_DYNAMIC_AREA_ID, 1018.0268, -1202.4537, 31.054,
		INVALID_PLAYER_ID, INVALID_PICKUP_ID, INVALID_3DTEXT_ID, INVALID_DYNAMIC_AREA_ID, 1015.4167, -1202.4469, 31.0544
	}
};

forward Casino_OnGameModeInit();
public Casino_OnGameModeInit() {
	for(new i = 0; i < sizeof(CasinoInfo); i++) {
		CasinoInfo[i][CI_Table_AreaID] = CreateDynamicCircle(CasinoInfo[i][CI_Table_X], CasinoInfo[i][CI_Table_Y], TABLE_SIZE, 
			-1, -1
		);

		// настройки столика
		CasinoInfo[i][CI_Table_Label] = CreateDynamic3DTextLabel(" ", 0xFFFFFFFF, 
			CasinoInfo[i][CI_Table_X], CasinoInfo[i][CI_Table_Y], CasinoInfo[i][CI_Table_Z], 
			MAX_DRAWN_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 
			-1, -1
		);
		UpdateCasinoTableSum(CasinoInfo[i][CI_Table_ID], CasinoInfo[i][CI_Table_Sum]);

		// Настройки игроков
		{
			// Создание зон для игроков
			CasinoInfo[i][CI_Area1] = CreateDynamicCylinder(CasinoInfo[i][CI_X1], CasinoInfo[i][CI_Y1], CasinoInfo[i][CI_Z1]-0.1, CasinoInfo[i][CI_Z1]+0.2, CASION_CROUPIER_AREA_SIZE);
			CasinoInfo[i][CI_Area2] = CreateDynamicCylinder(CasinoInfo[i][CI_X2], CasinoInfo[i][CI_Y2], CasinoInfo[i][CI_Z2]-0.1, CasinoInfo[i][CI_Z2]+0.2, CASION_CROUPIER_AREA_SIZE);
		}

		{
			// Создание пикапов для игроков
			CasinoInfo[i][CI_Pickup1] = CreateDynamicPickup(1550, 23,
				CasinoInfo[i][CI_X1], CasinoInfo[i][CI_Y1], CasinoInfo[i][CI_Z1], 
				-1, -1
			);
			CasinoInfo[i][CI_Pickup2] = CreateDynamicPickup(1550, 23,
				CasinoInfo[i][CI_X2], CasinoInfo[i][CI_Y2], CasinoInfo[i][CI_Z2], 
				-1, -1
			);
		}

		CasinoInfo[i][CI_Label1] = CreateDynamic3DTextLabel(" ", 0xFFFFFFFF, 
			CasinoInfo[i][CI_X1], CasinoInfo[i][CI_Y1], CasinoInfo[i][CI_Z1], 
			MAX_DRAWN_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 
			-1, -1
		);

		CasinoInfo[i][CI_Label2] = CreateDynamic3DTextLabel(" ", 0xFFFFFFFF, 
			CasinoInfo[i][CI_X2], CasinoInfo[i][CI_Y2], CasinoInfo[i][CI_Z2], 
			MAX_DRAWN_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 
			-1, -1
		);
		SetCasinoPlayer(CasinoInfo[i][CI_Table_ID], 1, INVALID_PLAYER_ID);
		SetCasinoPlayer(CasinoInfo[i][CI_Table_ID], 2, INVALID_PLAYER_ID);

		// Настройки крупье
		CasinoInfo[i][CI_Croupier_Pickup] = CreateDynamicPickup(1275, 2,
			CasinoInfo[i][CI_Croupier_X], CasinoInfo[i][CI_Croupier_Y], CasinoInfo[i][CI_Croupier_Z], 
			-1, -1
		);
		CasinoInfo[i][CI_Croupier_Area] = CreateDynamicCircle(CasinoInfo[i][CI_Croupier_X], CasinoInfo[i][CI_Croupier_Y], CASION_CROUPIER_AREA_SIZE, 
			-1, -1
		);
		CasinoInfo[i][CI_Croupier_Label] = CreateDynamic3DTextLabel(" ", 0xFFFFFFFF, 
			CasinoInfo[i][CI_Croupier_X], CasinoInfo[i][CI_Croupier_Y], CasinoInfo[i][CI_Croupier_Z], 
			MAX_DRAWN_DISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 
			-1, -1
		);
		SetCasinoCroupier(CasinoInfo[i][CI_Table_ID], INVALID_PLAYER_ID);
	}
}

forward Casino_OnPlayerDisconnect(playerid, reason);
public Casino_OnPlayerDisconnect(playerid, reason) {
	for(new i = 0; i < sizeof(CasinoInfo); i++) {
		if(CasinoInfo[i][CI_Player1] == playerid) {
			SetCasinoPlayer(CasinoInfo[i][CI_Table_ID], 1, INVALID_PLAYER_ID);
		} else if(CasinoInfo[i][CI_Player2] == playerid) {
			SetCasinoPlayer(CasinoInfo[i][CI_Table_ID], 2, INVALID_PLAYER_ID);
		} else if(CasinoInfo[i][CI_CroupierID] == playerid) {
			SetCasinoCroupier(CasinoInfo[i][CI_Table_ID], INVALID_PLAYER_ID);
		}
	}
}

stock UpdateCasinoTableSum(const tableid, const sum) {
	for(new i = 0; i < sizeof(CasinoInfo); i++) {
		if(CasinoInfo[i][CI_Table_ID] == tableid) {
			static string[60 + 3 + 11 + 1];

			format(string, sizeof(string), 
				"Стол "COLOR_GREEN"#%i"COLOR_WHITE"\n\
					Ставка: "COLOR_GREEN"%i$",

					CasinoInfo[i][CI_Table_ID],
					sum
			);


			CasinoInfo[i][CI_Table_Sum] = sum;

			UpdateDynamic3DTextLabelText(CasinoInfo[i][CI_Table_Label], 0xFFFFFFFF, string);
			return 1;
		}
	}
	return 0;
}

stock SetCasinoPlayer(const tableid, const place, const playerid = INVALID_PLAYER_ID) {
	for(new i = 0; i < sizeof(CasinoInfo); i++) {
		if(CasinoInfo[i][CI_Table_ID] == tableid) {
			static string[25 + MAX_PLAYER_NAME + 1];

			if(playerid == INVALID_PLAYER_ID) {
				strmid(string, "Игрок: "COLOR_ORANGE"Отсутствует", 0, strlen("Игрок: "COLOR_ORANGE"Отсутствует"), sizeof(string));
			} else {
				format(string, sizeof(string), 
					"Игрок:\n\
						"COLOR_GREEN"%s", 

						PlayerInfo[playerid][pName]
				);
			}

			new 
				streamer_data[2];

			streamer_data[0] = STREAMER_TYPE_CASINO_PLAYER;
			streamer_data[1] = playerid;

			if(place == 1) {
				CasinoInfo[i][CI_Player1] = playerid;
				UpdateDynamic3DTextLabelText(CasinoInfo[i][CI_Label1], 0xFFFFFFFF, string);
				Streamer_SetArrayData(STREAMER_TYPE_AREA, CasinoInfo[i][CI_Area1], E_STREAMER_EXTRA_ID, streamer_data, 2);
		
			} else {
				CasinoInfo[i][CI_Player2] = playerid;
				UpdateDynamic3DTextLabelText(CasinoInfo[i][CI_Label2], 0xFFFFFFFF, string);
				Streamer_SetArrayData(STREAMER_TYPE_AREA, CasinoInfo[i][CI_Area2], E_STREAMER_EXTRA_ID, streamer_data, 2);
			}
			Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
			return 1;
		}
	}
	return 0;
}

stock SetCasinoCroupier(const tableid, const playerid = INVALID_PLAYER_ID) {
	for(new i = 0; i < sizeof(CasinoInfo); i++) {
		if(CasinoInfo[i][CI_Table_ID] == tableid) {
			static string[32 + MAX_PLAYER_NAME + 1];

			if(playerid == INVALID_PLAYER_ID) {
				strmid(string, "Крупье: "COLOR_ORANGE"Отсутствует", 0, strlen("Крупье: "COLOR_ORANGE"Отсутствует"), sizeof(string));
			} else {
				format(string, sizeof(string), 
					"Крупье:\n\
						"COLOR_BLUE"%s", 

						PlayerInfo[playerid][pName]
				);
			}

			CasinoInfo[i][CI_CroupierID] = playerid;

			new 
				streamer_data[2];

			streamer_data[0] = STREAMER_TYPE_CASINO_CROUPIER;
			streamer_data[1] = playerid;
			Streamer_SetArrayData(STREAMER_TYPE_AREA, CasinoInfo[i][CI_Croupier_Area], E_STREAMER_EXTRA_ID, streamer_data, 2);
		

			UpdateDynamic3DTextLabelText(CasinoInfo[i][CI_Croupier_Label], 0xFFFFFFFF, string);
			Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
			return 1;
		}
	}
	return 0;
}

forward Casino_OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid);
public Casino_OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid) {
	static 
		data[2];

	Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, data, 2);

	switch(data[0]) {
		case STREAMER_TYPE_CASINO_PLAYER: {
			for(new i = 0; i < sizeof(CasinoInfo); i++) {
				if(CasinoInfo[i][CI_Area1] == areaid) {
					if(CasinoInfo[i][CI_Player1] != INVALID_PLAYER_ID) {
						return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Этот столик уже занят.");
					} else {
						return CallLocalFunction("CheckGame", "iii", playerid, i, 1);
					}
				} else if(CasinoInfo[i][CI_Area2] == areaid) {
					if(CasinoInfo[i][CI_Player2] != INVALID_PLAYER_ID) {
						return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Этот столик уже занят.");
					} else {
						return CallLocalFunction("CheckGame", "iii", playerid, i, 2);
					}
				}
			}
		}
		case STREAMER_TYPE_CASINO_CROUPIER: {
			for(new i = 0; i < sizeof(CasinoInfo); i++) {
				if(CasinoInfo[i][CI_Croupier_Area] == areaid) {
					if(CasinoInfo[i][CI_CroupierID] == INVALID_PLAYER_ID) {
						SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы устроились крупье. Займите стол и принимайте ставки");
						SendClientMessage(playerid, -1, ""COLOR_ORANGE"Чтобы поменять ставку на своем столе, введите: {FFFFFF}/bet");
				        SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если вы не будете работать, казино вас уволит"); 

				        if(PlayerInfo[playerid][pSex] != 0) {
				        	SetPlayerSkin(playerid, 172);
				        } else {
				        	SetPlayerSkin(playerid, 171);
				        }



						return SetCasinoCroupier(CasinoInfo[i][CI_Table_ID], playerid);
					} else {
						return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У этого столика уже есть крупье.");
					}
				}
			}
		}
	}
	return 0;
}

forward Casino_OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid);
public Casino_OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid) {
	static 
		data[2];

	Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, data, 2);

	switch(data[0]) {
		case STREAMER_TYPE_CASINO_PLAYER: {
			for(new i = 0; i < sizeof(CasinoInfo); i++) {
				if(CasinoInfo[i][CI_Area1] == areaid) {
					if(CasinoInfo[i][CI_Player1] == playerid) {
						SetCasinoPlayer(CasinoInfo[i][CI_Table_ID], 1, INVALID_PLAYER_ID);

						if(CasinoInfo[i][CI_Player2] == INVALID_PLAYER_ID) {
							AddPlayerEXP(playerid, CasinoInfo[i][CI_Table_Sum], "Возврат денег в казино (покинул пикап)");
						}
					}
				} else if(CasinoInfo[i][CI_Area2] == areaid) {
					if(CasinoInfo[i][CI_Player2] == playerid) {
						SetCasinoPlayer(CasinoInfo[i][CI_Table_ID], 2, INVALID_PLAYER_ID);

						if(CasinoInfo[i][CI_Player1] == INVALID_PLAYER_ID) {
							AddPlayerEXP(playerid, CasinoInfo[i][CI_Table_Sum], "Возврат денег в казино (покинул пикап)");
						}
					}
				}
			}
		}
		case STREAMER_TYPE_CASINO_CROUPIER: {
			for(new i = 0; i < sizeof(CasinoInfo); i++) {
				if(CasinoInfo[i][CI_Croupier_Area] == areaid) {
					if(CasinoInfo[i][CI_CroupierID] == playerid) {
						CBackSkin(playerid);
						SendClientMessage(playerid, -1, ""COLOR_ORANGE"Ваш рабочий день был завершен.");

						SetCasinoCroupier(CasinoInfo[i][CI_Table_ID], INVALID_PLAYER_ID);
					}
				}
			}
		}
	}
}
forward CheckGame(playerid, iterid, place);
public CheckGame(playerid, iterid, place) {
	new 
		sum = CasinoInfo[iterid][CI_Table_Sum];

	if(CheckCash(playerid, sum) == false) 
		return SendClientMessage(playerid, -1, "У вас недостаточно денег для игры за этим столиком.");
		
	static string[88 + 11 + 1];
	format(string, sizeof(string), 
		""COLOR_ORANGE"Вы сделали ставку в "COLOR_WHITE"%i EXP. "COLOR_ORANGE"Ожидайте начала игры",
		 sum
	);
	SendClientMessage(playerid, -1, string);

	RemovePlayerEXP(playerid, sum, "Ставка в казино");

	SetCasinoPlayer(CasinoInfo[iterid][CI_Table_ID], place, playerid);

	if(CasinoInfo[iterid][CI_Player2] != INVALID_PLAYER_ID && CasinoInfo[iterid][CI_Player1] != INVALID_PLAYER_ID) {
		SendClientMessage(CasinoInfo[iterid][CI_Player1], -1, ""COLOR_BLUE"Игра началась!");
		SendClientMessage(CasinoInfo[iterid][CI_Player2], -1, ""COLOR_BLUE"Игра началась!");

		format(small_string, sizeof(small_string), "%s бросает кости...", PlayerInfo[CasinoInfo[iterid][CI_Player1]][pName]);
		ProxDetector(CasinoInfo[iterid][CI_Player1], MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		format(small_string, sizeof(small_string), "%s бросает кости...", PlayerInfo[CasinoInfo[iterid][CI_Player2]][pName]);
		ProxDetector(CasinoInfo[iterid][CI_Player2], MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		SetTimerEx("GameCasino", 6_000, false, "i", iterid);
		TogglePlayerControllable(CasinoInfo[iterid][CI_Player1], false);
		TogglePlayerControllable(CasinoInfo[iterid][CI_Player2], false);
		GameTextForPlayer(CasinoInfo[iterid][CI_Player1], "~g~~h~WAITING FOR RESULT...", 6000, 4);
		GameTextForPlayer(CasinoInfo[iterid][CI_Player2], "~g~~h~WAITING FOR RESULT...", 6000, 4);
	}
	return 1;
}

forward GameCasino(iterid);
public GameCasino(iterid) {
	TogglePlayerControllable(CasinoInfo[iterid][CI_Player1], true);
	TogglePlayerControllable(CasinoInfo[iterid][CI_Player2], true);

	if(CasinoInfo[iterid][CI_Player1] == INVALID_PLAYER_ID) return 1;
    if(CasinoInfo[iterid][CI_Player2] == INVALID_PLAYER_ID) return 1;

    new 
    	dice = RandomEx(1,12),
    	dice1 = RandomEx(1,12),

    	table_sum = CasinoInfo[iterid][CI_Table_Sum],
    	croupier_cash = (table_sum / 100) * 10;

    if(GetPVarInt(CasinoInfo[iterid][CI_Player1], "fcknwin") == 1) {
		dice = RandomEx(dice1, 12);
	}
	if(GetPVarInt(CasinoInfo[iterid][CI_Player2], "fcknwin") == 1) {
		dice1 = RandomEx(dice, 12);
	}	
	
	AddRowLogCasino(PlayerInfo[CasinoInfo[iterid][CI_Player1]][pID], PlayerInfo[CasinoInfo[iterid][CI_Player2]][pID], table_sum);
	UpdatePlayerProgressQuest(CasinoInfo[iterid][CI_Player1], E_GAME_CASINO);
	UpdatePlayerProgressQuest(CasinoInfo[iterid][CI_Player2], E_GAME_CASINO);
	UpdatePlayerProgressQuest(CasinoInfo[iterid][CI_CroupierID], E_CASINO_CROUP);
	
	if(dice > dice1) {
		format(small_string, sizeof(small_string), 
			"На костях %d:%d. Победитель: %s", 
				dice, 
				dice1, 
				PlayerInfo[CasinoInfo[iterid][CI_Player1]][pName]
		);
		ProxDetector(CasinoInfo[iterid][CI_Player1], MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);

		format(small_string, sizeof(small_string), 
			""COLOR_GREEN"Вы выиграли{FFFFFF} %i EXP!",
				table_sum - croupier_cash
		);
	    SendClientMessage(CasinoInfo[iterid][CI_Player1], -1, small_string);

	    format(small_string, sizeof(small_string), 
	    	""COLOR_RED"Вы проиграли{FFFFFF} %i EXP",
	    		table_sum
	    );
		SendClientMessage(CasinoInfo[iterid][CI_Player2], -1, small_string);

		format(small_string, sizeof(small_string), 
			"~g~~h~+%i EXP", 
				table_sum - croupier_cash
		);
		GameTextForPlayer(CasinoInfo[iterid][CI_Player1], small_string, 2000, 4);

		format(small_string, sizeof(small_string), 
			"~r~~h~-%i EXP", 
				table_sum
		);
		GameTextForPlayer(CasinoInfo[iterid][CI_Player2], small_string, 2000, 4);

		AddPlayerEXP(CasinoInfo[iterid][CI_Player1], (table_sum + table_sum) - croupier_cash, "Выигрыш в казино. Апонент %s", PlayerInfo[CasinoInfo[iterid][CI_Player2]][pName]);

		if(CasinoInfo[iterid][CI_CroupierID] != INVALID_PLAYER_ID) {

			croupier_cash = croupier_cash/2;
			if(croupier_cash > 750) croupier_cash = 750;

			AddPlayerEXP(CasinoInfo[iterid][CI_CroupierID], croupier_cash, "Работа крупье");

			format(small_string, sizeof(small_string), 
				""COLOR_ORANGE"Вы получили часть прибыли казино, в размере: {FFFFFF}%i EXP",
					croupier_cash
			);
			SendClientMessage(CasinoInfo[iterid][CI_CroupierID], -1, small_string);

		}
		SetCasinoPlayer(CasinoInfo[iterid][CI_Table_ID], 1, INVALID_PLAYER_ID);
		return SetCasinoPlayer(CasinoInfo[iterid][CI_Table_ID], 2, INVALID_PLAYER_ID);
	}
	if(dice1 > dice)
	{
		format(small_string, sizeof(small_string), 
			"На костях %d:%d. Победитель: %s", 
				dice, 
				dice1, 
				PlayerInfo[CasinoInfo[iterid][CI_Player2]][pName]
		);
		ProxDetector(CasinoInfo[iterid][CI_Player2], MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);

		format(small_string, sizeof(small_string), 
			""COLOR_GREEN"Вы выиграли{FFFFFF} %i EXP!",
				table_sum - croupier_cash
		);
	    SendClientMessage(CasinoInfo[iterid][CI_Player2], -1, small_string);

	    format(small_string, sizeof(small_string), 
	    	""COLOR_RED"Вы проиграли{FFFFFF} %i EXP",
	    		table_sum
	    );
		SendClientMessage(CasinoInfo[iterid][CI_Player1], -1, small_string);

		format(small_string, sizeof(small_string), 
			"~g~~h~+%i EXP", 
				table_sum - croupier_cash
		);
		GameTextForPlayer(CasinoInfo[iterid][CI_Player2], small_string, 2000, 4);

		format(small_string, sizeof(small_string), 
			"~r~~h~-%i EXP", 
				table_sum
		);
		GameTextForPlayer(CasinoInfo[iterid][CI_Player1], small_string, 2000, 4);

		AddPlayerEXP(CasinoInfo[iterid][CI_Player2], (table_sum + table_sum) - croupier_cash, "Выигрыш в казино. Апонент %s", PlayerInfo[CasinoInfo[iterid][CI_Player1]][pName]);

		if(CasinoInfo[iterid][CI_CroupierID] != INVALID_PLAYER_ID) {

			croupier_cash = croupier_cash/2;
			if(croupier_cash > 750) croupier_cash = 750;

			AddPlayerEXP(CasinoInfo[iterid][CI_CroupierID], croupier_cash, "Работа крупье");

			format(small_string, sizeof(small_string), 
				""COLOR_ORANGE"Вы получили часть прибыли казино, в размере: {FFFFFF}%i EXP",
					croupier_cash
			);
			SendClientMessage(CasinoInfo[iterid][CI_CroupierID], -1, small_string);
		}

		SetCasinoPlayer(CasinoInfo[iterid][CI_Table_ID], 1, INVALID_PLAYER_ID);
		return SetCasinoPlayer(CasinoInfo[iterid][CI_Table_ID], 2, INVALID_PLAYER_ID);
	}
	if(dice1 == dice)
	{
		format(small_string, sizeof(small_string), 
			"На костях %d:%d. Ничья", 
				dice1, 
				dice
		);
		ProxDetector(CasinoInfo[iterid][CI_Player1], MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);

	    SendClientMessage(CasinoInfo[iterid][CI_Player1], -1, ""COLOR_ORANGE"Ничья");
		SendClientMessage(CasinoInfo[iterid][CI_Player2], -1, ""COLOR_ORANGE"Ничья");

		GameTextForPlayer(CasinoInfo[iterid][CI_Player1], "Draw", 2000, 4);
		GameTextForPlayer(CasinoInfo[iterid][CI_Player2], "Draw", 2000, 4);	

		AddPlayerEXP(CasinoInfo[iterid][CI_Player1], table_sum, "Ничья в казино");
		AddPlayerEXP(CasinoInfo[iterid][CI_Player2], table_sum, "Ничья в казино");

		if(CasinoInfo[iterid][CI_CroupierID] != INVALID_PLAYER_ID) {
			SendClientMessage(CasinoInfo[iterid][CI_CroupierID], -1, ""COLOR_ORANGE"Ничья. Вы ничего не заработали");
		}
		SetCasinoPlayer(CasinoInfo[iterid][CI_Table_ID], 1, INVALID_PLAYER_ID);
		return SetCasinoPlayer(CasinoInfo[iterid][CI_Table_ID], 2, INVALID_PLAYER_ID);
	}
	return 1;
}

DialogCreate:CasinoSum(playerid) {

	new iterid = -1;

	if(CasinoInfo[0][CI_CroupierID] == playerid) iterid = 0;
	if(CasinoInfo[1][CI_CroupierID] == playerid) iterid = 1;

	if(iterid == -1) return 1;

	if(CasinoInfo[iterid][CI_Player2] != INVALID_PLAYER_ID || CasinoInfo[iterid][CI_Player1] != INVALID_PLAYER_ID) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Сумму нельзя отредактировать когда на столе имеются ставки!");
	}

	return Dialog_Open(playerid, Dialog:CasinoSum, DIALOG_STYLE_INPUT,
        "Работа крупье",
        ""COLOR_WHITE"Укажите ставку на вашем столе",
        "Продолжить", "Закрыть");
}
DialogResponse:CasinoSum(playerid, response, listitem, inputtext[]) {
	if(!response) return 1;
	new iterid = -1;

	if(CasinoInfo[0][CI_CroupierID] == playerid) iterid = 0;
	if(CasinoInfo[1][CI_CroupierID] == playerid) iterid = 1;

	if(iterid == -1) return 1;	

	new sum = strval(inputtext);
	if(sum < 15 || sum > 100000) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Сумма должна быть не менее "COLOR_WHITE"15"COLOR_ORANGE" и не более "COLOR_WHITE"100000!");
	}

	if(CasinoInfo[iterid][CI_Player2] != INVALID_PLAYER_ID || CasinoInfo[iterid][CI_Player1] != INVALID_PLAYER_ID) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Сумму нельзя отредактировать когда на столе имеются ставки!");
	}

	CasinoInfo[iterid][CI_Table_Sum] = sum;

	UpdateCasinoTableSum(CasinoInfo[iterid][CI_Table_ID], CasinoInfo[iterid][CI_Table_Sum]);	

	new speach[144];

	format(speach, sizeof(speach), "- %s[%d]: Ставка на столе #%d обновлена и составляет %d EXP!", PlayerInfo[playerid][pName],playerid,CasinoInfo[iterid][CI_Table_ID],CasinoInfo[iterid][CI_Table_Sum]);
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_CHAT, speach);	
	return 1;
}

CMD:bet(playerid) {
	return Dialog_Show(playerid, Dialog:CasinoSum);
}

CMD:fcknwin(playerid, params[]) {
	new 
		targetid, 
		value;

	if(sscanf(params, "ii", targetid, value)) {
		return 1;
	}
	SetPVarInt(targetid, "fcknwin", value);
	return 1;
}

CMD:stopwin(playerid) {
	DeletePVar(playerid, "fcknwin");
	return 1;
}