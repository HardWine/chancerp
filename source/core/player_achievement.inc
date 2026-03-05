#if defined private_achievement_included
	#endinput
#endif

#define private_achievement_included

#include <YSI_Coding\y_hooks>

forward OnPlayerAchievementChange(const playerid, const title[], const E_ACHIEVEMENT:achievement, const old_value, const new_value);

// internal defines
#define Achievement:%0(%1) \
	forward ach_%0(%1); \
	public ach_%0(%1)


#define DEBUG_ACHIEVEMENT

#define ACHIEVEMENT_GIVE_MONEY_LEVEL_0 			1000 // Silver
#define ACHIEVEMENT_GIVE_MONEY_LEVEL_1 			(2000) // Bronze
#define ACHIEVEMENT_GIVE_MONEY_LEVEL_2 			(3000) // Gold
#define ACHIEVEMENT_GIVE_MONEY_LEVEL_3 			(4000) // Platinum
#define ACHIEVEMENT_GIVE_MONEY_LEVEL_4 			(5000) // Ruby

#define ACHIEVEMENT_BLOCKED_COLOR 				"{FFFFFF}"
#define ACHIEVEMENT_BRONZE_COLOR 				"{FFFFFF}"
#define ACHIEVEMENT_SILVER_COLOR 				"{FFFFFF}"
#define ACHIEVEMENT_GOLD_COLOR 					"{FFFFFF}"
#define ACHIEVEMENT_PLATINUM_COLOR 				"{FFFFFF}"
#define ACHIEVEMENT_RUBY_COLOR 					"{FFFFFF}"

new 
	PlayerFarming[MAX_PLAYERS] = {0, ...}, 				// «Фермерство»
	PlayerFirstClassPilot[MAX_PLAYERS] = {0, ...},		// «Первоклассный пилот» 
	PlayerHeavyLoad[MAX_PLAYERS] = {0, ...},			// «Тяжелый груз»
	PlayerCleanCity[MAX_PLAYERS] = {0, ...},			// «Чистый город» 
	PlayerTrifle[MAX_PLAYERS] = {0, ...},				// «Мелочь в пепельнице»
	PlayerLongWay[MAX_PLAYERS] = {0, ...},				// «Дальний путь»
	PlayerRPOurAll[MAX_PLAYERS] = {0, ...},				// «Ролевая игра»
	PlayerSoldierSleeping[MAX_PLAYERS] = {0, ...},		// «Солдат спит, служба идет»
	PlayerWeaponSupply[MAX_PLAYERS] = {0, ...};			// «Поставка оружия»

new
	PlayerDangerous[MAX_PLAYERS] = {0, ...},			// «Опасный груз»
	PlayerWillNot[MAX_PLAYERS] = {0, ...},				// «Не пройдешь!»
	PlayerTurnFlashers[MAX_PLAYERS] = {0, ...},			// «Включай мигалки!»
	PlayerCopsIn[MAX_PLAYERS] = {0, ...},				// «Копы в деле»
	PlayerBenchGangster[MAX_PLAYERS] = {0, ...},		// «На нары, бандит»
	PlayerSleepWell[MAX_PLAYERS] = {0, ...},			// «Спи штат спокойно»
	PlayerPocketsInside[MAX_PLAYERS] = {0, ...},		// «Карманы на изнанку»
	PlayerGiftWill[MAX_PLAYERS] = {0, ...},				// «Подарок - воля»
	PlayerMakeCitizenship[MAX_PLAYERS] = {0, ...};		// «Оформляем гражданство»
	
new
	PlayerRealEditor[MAX_PLAYERS] = {0, ...},			// «Настоящий редактор»
	PlayerBattleSquares[MAX_PLAYERS] = {0, ...},		// «Война за территорию»
	PlayerDrugTrafficker[MAX_PLAYERS] = {0, ...},		// «Наркоторговец»
	PlayerCarRental[MAX_PLAYERS] = {0, ...},			// «Машинка напрокат»
	PlayerCenturyTheft[MAX_PLAYERS] = {0, ...},			// «Кража века»
	PlayerDeal[MAX_PLAYERS] = {0, ...};					// «Сделка? По рукам!»


enum E_ACHIEVEMENT {
	E_FARMING, 							// «Фермерство» +
	E_FIRST_CLASS_PILOT, 				// «Первоклассный пилот»  +
	E_HEAVY_LOAD, 						// «Тяжелый груз»  +
	E_CLEAN_CITY, 						// «Чистый город»  +
	E_TRIFLE, 							// «Мелочь в пепельнице» +
	E_LONG_WAY,							// «Дальний путь» +
	E_RP_OUR_ALL,						// «Ролевая игра»  +
	E_SOLDIER_SLEEPING,					// «Солдат спит, служба идет» +
	E_WEAPON_SUPPLY,					// «Поставка оружия» +
	E_DANGEROUS,						// «Опасный груз» +
	E_WILL_NOT,							// «Не пройдешь!» +
	E_TURN_FLASHERS,					// «Включай мигалки!» +
	E_COPS_IN,							// «Копы в деле» +
	E_BENCH_GANGSTER,					// «На нары, бандит» +
	E_SLEEP_WELL,						// «Спи штат спокойно» +
	E_POCKETS_INSIDER,					// «Карманы на изнанку» +
	E_GIFT_WILL,						// «Подарок - воля» +
	E_MAKE_CITIZENSHIP,					// «Оформляем гражданство» +
	E_REAL_EDITOR,						// «Настоящий редактор» +
	E_BATTLE_SQUARES,					// «Война за территорию» +
	E_DRUG_TRAFFICKET,					// «Наркоторговец» +
	E_CAR_RENTAL,						// «Машинка напрокат» +
	E_CENTURY_THEFT,					// «Кража века» +
	E_DEAL								// «Сделка? По рукам!» +
}

hook OnPlayerConnect(playerid) {
	PlayerFarming[playerid] = 0;
	PlayerFirstClassPilot[playerid] = 0;
	PlayerHeavyLoad[playerid] = 0;
	PlayerCleanCity[playerid] = 0;
	PlayerTrifle[playerid] = 0;
	PlayerLongWay[playerid] = 0;
	PlayerRPOurAll[playerid] = 0;
	PlayerSoldierSleeping[playerid] = 0;
	PlayerWeaponSupply[playerid] = 0;
	PlayerDangerous[playerid] = 0;
	PlayerWillNot[playerid] = 0;
	PlayerTurnFlashers[playerid] = 0;
	PlayerCopsIn[playerid] = 0;
	PlayerBenchGangster[playerid] = 0;
	PlayerSleepWell[playerid] = 0;
	PlayerPocketsInside[playerid] = 0;
	PlayerGiftWill[playerid] = 0;
	PlayerMakeCitizenship[playerid] = 0;
	PlayerRealEditor[playerid] = 0;
	PlayerBattleSquares[playerid] = 0;
	PlayerDrugTrafficker[playerid] = 0;
	PlayerCarRental[playerid] = 0;
	PlayerCenturyTheft[playerid] = 0;
	PlayerDeal[playerid] = 0;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason

	PlayerFarming[playerid] = 0;
	PlayerFirstClassPilot[playerid] = 0;
	PlayerHeavyLoad[playerid] = 0;
	PlayerCleanCity[playerid] = 0;
	PlayerTrifle[playerid] = 0;
	PlayerLongWay[playerid] = 0;
	PlayerRPOurAll[playerid] = 0;
	PlayerSoldierSleeping[playerid] = 0;
	PlayerWeaponSupply[playerid] = 0;
	PlayerDangerous[playerid] = 0;
	PlayerWillNot[playerid] = 0;
	PlayerTurnFlashers[playerid] = 0;
	PlayerCopsIn[playerid] = 0;
	PlayerBenchGangster[playerid] = 0;
	PlayerSleepWell[playerid] = 0;
	PlayerPocketsInside[playerid] = 0;
	PlayerGiftWill[playerid] = 0;
	PlayerMakeCitizenship[playerid] = 0;
	PlayerRealEditor[playerid] = 0;
	PlayerBattleSquares[playerid] = 0;
	PlayerDrugTrafficker[playerid] = 0;
	PlayerCarRental[playerid] = 0;
	PlayerCenturyTheft[playerid] = 0;
	PlayerDeal[playerid] = 0;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

stock AddPlayerAchievement(const playerid, E_ACHIEVEMENT:achievement) {
	switch(_:achievement) {
		// «Фермерство»
		case E_FARMING: {
			new 
				old_value = PlayerFarming[playerid];

			PlayerFarming[playerid] = PlayerFarming[playerid] + 1;
			CallLocalFunction("ach_Farming", "ddd", playerid, PlayerFarming[playerid], old_value);
		}
		// «Первоклассный пилот»
		case E_FIRST_CLASS_PILOT: {
			new 
				old_value = PlayerFirstClassPilot[playerid];

			PlayerFirstClassPilot[playerid] = PlayerFirstClassPilot[playerid] + 1;
			CallLocalFunction("ach_FirstClassPilot", "ddd", playerid, PlayerFirstClassPilot[playerid], old_value);
		}
		// «Тяжелый груз»
		case E_HEAVY_LOAD: {
			new 
				old_value = PlayerHeavyLoad[playerid];

			PlayerHeavyLoad[playerid] = PlayerHeavyLoad[playerid] + 1;
			CallLocalFunction("ach_HeavyLoad", "ddd", playerid, PlayerHeavyLoad[playerid], old_value);
		}
		// «Чистый город»
		case E_CLEAN_CITY: {
			new 
				old_value = PlayerCleanCity[playerid];

			PlayerCleanCity[playerid] = PlayerCleanCity[playerid] + 1;
			CallLocalFunction("ach_CleanCity", "ddd", playerid, PlayerCleanCity[playerid], old_value);
		}
		// «Мелочь в пепельнице»
		case E_TRIFLE: {
			new 
				old_value = PlayerTrifle[playerid];

			PlayerTrifle[playerid] = PlayerTrifle[playerid] + 1;
			CallLocalFunction("ach_Trifle", "ddd", playerid, PlayerTrifle[playerid], old_value);
		}
		// «Дальний путь»
		case E_LONG_WAY: {
			new 
				old_value = PlayerLongWay[playerid];

			PlayerLongWay[playerid] = PlayerLongWay[playerid] + 1;
			CallLocalFunction("ach_LongWay", "ddd", playerid, PlayerLongWay[playerid], old_value);
		}
		// «Ролевая игра»
		case E_RP_OUR_ALL: {
			new 
				old_value = PlayerRPOurAll[playerid];

			PlayerRPOurAll[playerid] = PlayerRPOurAll[playerid] + 1;
			CallLocalFunction("ach_RPOurAll", "ddd", playerid, PlayerRPOurAll[playerid], old_value);
		}
		// «Солдат спит, служба идет» 
		case E_SOLDIER_SLEEPING: {
			new 
				old_value = PlayerSoldierSleeping[playerid];

			PlayerSoldierSleeping[playerid] = PlayerSoldierSleeping[playerid] + 1;
			CallLocalFunction("ach_SoldierSleeping", "ddd", playerid, PlayerSoldierSleeping[playerid], old_value);
		}
		// «Поставка оружия»
		case E_WEAPON_SUPPLY: {
			new 
				old_value = PlayerWeaponSupply[playerid];

			PlayerWeaponSupply[playerid] = PlayerWeaponSupply[playerid] + 1;
			CallLocalFunction("ach_WeaponSupply", "ddd", playerid, PlayerWeaponSupply[playerid], old_value);
		}
		// «Опасный груз»
		case E_DANGEROUS: {
			new 
				old_value = PlayerDangerous[playerid];

			PlayerDangerous[playerid] = PlayerDangerous[playerid] + 1;
			CallLocalFunction("ach_Dangerous", "ddd", playerid, PlayerDangerous[playerid], old_value);
		}
		// «Не пройдешь!»
		case E_WILL_NOT: {
			new 
				old_value = PlayerWillNot[playerid];

			PlayerWillNot[playerid] = PlayerWillNot[playerid] + 1;
			CallLocalFunction("ach_WillNot", "ddd", playerid, PlayerWillNot[playerid], old_value);
		}
		// «Включай мигалки!»
		case E_TURN_FLASHERS: {
			new 
				old_value = PlayerTurnFlashers[playerid];

			PlayerTurnFlashers[playerid] = PlayerTurnFlashers[playerid] + 1;
			CallLocalFunction("ach_TurnFlashers", "ddd", playerid, PlayerTurnFlashers[playerid], old_value);
		}
		// «Копы в деле»
		case E_COPS_IN: {
			new 
				old_value = PlayerCopsIn[playerid];

			PlayerCopsIn[playerid] = PlayerCopsIn[playerid] + 1;
			CallLocalFunction("ach_CopsIn", "ddd", playerid, PlayerCopsIn[playerid], old_value);
		}
		// «На нары, бандит»
		case E_BENCH_GANGSTER: {
			new 
				old_value = PlayerBenchGangster[playerid];

			PlayerBenchGangster[playerid] = PlayerBenchGangster[playerid] + 1;
			CallLocalFunction("ach_BenchGangster", "ddd", playerid, PlayerBenchGangster[playerid], old_value);
		}
		// «Спи штат спокойно»
		case E_SLEEP_WELL: {
			new 
				old_value = PlayerSleepWell[playerid];

			PlayerSleepWell[playerid] = PlayerSleepWell[playerid] + 1;
			CallLocalFunction("ach_SleepWell", "ddd", playerid, PlayerSleepWell[playerid], old_value);
		}
		// «Карманы на изнанку»
		case E_POCKETS_INSIDER: {
			new 
				old_value = PlayerPocketsInside[playerid];

			PlayerPocketsInside[playerid] = PlayerPocketsInside[playerid] + 1;
			CallLocalFunction("ach_PocketsInside", "ddd", playerid, PlayerPocketsInside[playerid], old_value);
		}
		// «Подарок - воля»
		case E_GIFT_WILL: {
			new 
				old_value = PlayerGiftWill[playerid];

			PlayerGiftWill[playerid] = PlayerGiftWill[playerid] + 1;
			CallLocalFunction("ach_GiftWill", "ddd", playerid, PlayerGiftWill[playerid], old_value);
		}
		// «Оформляем гражданство»
		case E_MAKE_CITIZENSHIP: {
			new 
				old_value = PlayerMakeCitizenship[playerid];

			PlayerMakeCitizenship[playerid] = PlayerMakeCitizenship[playerid] + 1;
			CallLocalFunction("ach_MakeCitizenship", "ddd", playerid, PlayerMakeCitizenship[playerid], old_value);
		}
		// «Настоящий редактор»
		case E_REAL_EDITOR: {
			new 
				old_value = PlayerRealEditor[playerid];

			PlayerRealEditor[playerid] = PlayerRealEditor[playerid] + 1;
			CallLocalFunction("ach_RealEditor", "ddd", playerid, PlayerRealEditor[playerid], old_value);
		}
		// «Война за территорию»
		case E_BATTLE_SQUARES: {
			new 
				old_value = PlayerBattleSquares[playerid];

			PlayerBattleSquares[playerid] = PlayerBattleSquares[playerid] + 1;
			CallLocalFunction("ach_BattleSquares", "ddd", playerid, PlayerBattleSquares[playerid], old_value);
		}
		// «Наркоторговец»
		case E_DRUG_TRAFFICKET: {
			new 
				old_value = PlayerDrugTrafficker[playerid];

			PlayerDrugTrafficker[playerid] = PlayerDrugTrafficker[playerid] + 1;
			CallLocalFunction("ach_DrugTrafficker", "ddd", playerid, PlayerDrugTrafficker[playerid], old_value);
		}
		// «Машинка напрокат»
		case E_CAR_RENTAL: {
			new 
				old_value = PlayerCarRental[playerid];

			PlayerCarRental[playerid] = PlayerCarRental[playerid] + 1;
			CallLocalFunction("ach_CarRental", "ddd", playerid, PlayerCarRental[playerid], old_value);
		}
		// «Кража века»
		case E_CENTURY_THEFT: {
			new 
				old_value = PlayerCenturyTheft[playerid];

			PlayerCenturyTheft[playerid] = PlayerCenturyTheft[playerid] + 1;
			CallLocalFunction("ach_CenturyTheft", "ddd", playerid, PlayerCenturyTheft[playerid], old_value);
		}
		// «Сделка? По рукам!»
		case E_DEAL: {
			new 
				old_value = PlayerDeal[playerid];

			PlayerDeal[playerid] = PlayerDeal[playerid] + 1;
			CallLocalFunction("ach_Deal", "ddd", playerid, PlayerDeal[playerid], old_value);
		}
	}
	return 1;
}

// «Фермерство»
Achievement:Farming(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:Farming %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Фермерство» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Фермерство», уровень Bronze");
		#endif 
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Фермерство» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Фермерство», уровень Silver");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Фермерство» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Фермерство», уровень Gold");
		#endif
	} else if(new_value == 1000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Фермерство» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Фермерство», уровень Platinum");
		#endif
	} else if(new_value == 2000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Фермерство» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Фермерство», уровень Ruby");
		#endif
	}
	new ach_query[144];
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `Farming` = `Farming` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Первоклассный пилот» 
Achievement:FirstClassPilot(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:FirstClassPilot %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Первоклассный пилот» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Первоклассный пилот», уровень Bronze");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Первоклассный пилот» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Первоклассный пилот», уровень Silver");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Первоклассный пилот» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Первоклассный пилот», уровень Gold");
		#endif
	} else if(new_value == 1000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Первоклассный пилот» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Первоклассный пилот», уровень Platinum");
		#endif
	} else if(new_value == 2000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Первоклассный пилот» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Первоклассный пилот», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `FirstClassPilot` = `FirstClassPilot` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);	
}

// «Тяжелый груз» 
Achievement:HeavyLoad(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:HeavyLoad %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Тяжелый груз» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Тяжелый груз», уровень Bronze");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Тяжелый груз» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Тяжелый груз», уровень Silver");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Тяжелый груз» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Тяжелый груз», уровень Gold");
		#endif
	} else if(new_value == 1000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Тяжелый груз» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Тяжелый груз», уровень Platinum");
		#endif
	} else if(new_value == 2000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Тяжелый груз» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Тяжелый груз», уровень Platinum");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `HeavyLoad` = `HeavyLoad` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);		
}

// «Чистый город» 
Achievement:CleanCity(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:CleanCity %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 10) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Чистый город» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Чистый город», уровень Bronze");
		#endif
	} else if(new_value == 25) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Чистый город» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Чистый город», уровень Silver");
		#endif
	} else if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Чистый город» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Чистый город», уровень Gold");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Чистый город» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Чистый город», уровень Platinum");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Чистый город» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Чистый город», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `CleanCity` = `CleanCity` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);			
}

// «Мелочь в пепельнице» 
Achievement:Trifle(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:Trifle %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Мелочь в пепельнице» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Мелочь в пепельнице», уровень Bronze");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Мелочь в пепельнице» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Мелочь в пепельнице», уровень Silver");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Мелочь в пепельнице» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Мелочь в пепельнице», уровень Gold");
		#endif
	} else if(new_value == 1000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Мелочь в пепельнице» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Мелочь в пепельнице», уровень Platinum");
		#endif
	} else if(new_value == 2000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Мелочь в пепельнице» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Мелочь в пепельнице», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `Trifle` = `Trifle` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Дальний путь»
Achievement:LongWay(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:LongWay %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Дальний путь» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Дальний путь», уровень Bronze");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Дальний путь» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Дальний путь», уровень Silver");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Дальний путь» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Дальний путь», уровень Gold");
		#endif
	} else if(new_value == 1000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Дальний путь» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Дальний путь», уровень Platinum");
		#endif
	} else if(new_value == 2000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Дальний путь» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Дальний путь», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `LongWay` = `LongWay` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Ролевая игра» 
Achievement:RPOurAll(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:RPOurAll %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Ролевая игра» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Ролевая игра», уровень Bronze");
		#endif
	} else if(new_value == 1000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Ролевая игра» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Ролевая игра», уровень Silver");
		#endif
	} else if(new_value == 1500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Ролевая игра» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Ролевая игра», уровень Gold");
		#endif
	} else if(new_value == 2000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Ролевая игра» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Ролевая игра», уровень Platinum");
		#endif
	} else if(new_value == 2500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Ролевая игра» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Ролевая игра», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `RPOurAll` = `RPOurAll` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Солдат спит, служба идет»
Achievement:SoldierSleeping(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:SoldierSleeping %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Солдат спит, служба идет» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");
	
		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Солдат спит, служба идет», уровень Bronze");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Солдат спит, служба идет» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Солдат спит, служба идет», уровень Silver");
		#endif
	} else if(new_value == 200) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Солдат спит, служба идет» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Солдат спит, служба идет», уровень Gold");
		#endif
	} else if(new_value == 300) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Солдат спит, служба идет» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Солдат спит, служба идет», уровень Platinum");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Солдат спит, служба идет» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Солдат спит, служба идет», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `SoldierSleeping` = `SoldierSleeping` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Поставка оружия» 
Achievement:WeaponSupply(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:WeaponSupply %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Поставка оружия» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Поставка оружия», уровень Bronze");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Поставка оружия» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Поставка оружия», уровень Silver");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Поставка оружия» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Поставка оружия», уровень Gold");
		#endif
	} else if(new_value == 1000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Поставка оружия» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Поставка оружия», уровень Platinum");
		#endif
	} else if(new_value == 2000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Поставка оружия» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Поставка оружия», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `WeaponSupply` = `WeaponSupply` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Опасный груз» 
Achievement:Dangerous(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:Dangerous %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 10) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Опасный груз» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Опасный груз», уровень Bronze");
		#endif
	} else if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Опасный груз» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Опасный груз», уровень Silver");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Опасный груз» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Опасный груз», уровень Gold");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Опасный груз» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Опасный груз», уровень Platinum");
		#endif
	} else if(new_value == 1000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Опасный груз» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Опасный груз», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `DangerousСargo` = `DangerousСargo` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Не пройдешь!»
Achievement:WillNot(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:WillNot %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 10) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Не пройдешь!» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Не пройдешь!», уровень Bronze");
		#endif
	} else if(new_value == 25) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Не пройдешь!» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Не пройдешь!», уровень Silver");
		#endif
	} else if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Не пройдешь!» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Не пройдешь!», уровень Gold");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Не пройдешь!» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Не пройдешь!», уровень Platinum");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Не пройдешь!» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Не пройдешь!», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `WillNot` = `WillNot` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Включай мигалки!»
Achievement:TurnFlashers(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:TurnFlashers %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 10) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Включай мигалки!» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Включай мигалки!», уровень Bronze");
		#endif
	} else if(new_value == 25) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Включай мигалки!» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Включай мигалки!», уровень Silver");
		#endif
	} else if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Включай мигалки!» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Включай мигалки!», уровень Gold");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Включай мигалки!» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Включай мигалки!», уровень Platinum");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Включай мигалки!» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Включай мигалки!», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `TurnFlashers` = `TurnFlashers` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// ЖЕНЯ БЛЯТЬ
// «Копы в деле»
Achievement:CopsIn(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:CopsIn %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 25) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Копы в деле» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Копы в деле», уровень Bronze");
		#endif
	} else if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Копы в деле» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Копы в деле», уровень Silver");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Копы в деле» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Копы в деле», уровень Gold");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Копы в деле» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Копы в деле», уровень Platinum");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Копы в деле» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Копы в деле», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `CopsIn` = `CopsIn` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «На нары, бандит»
Achievement:BenchGangster(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:BenchGangster %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 15) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «На нары, бандит» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «На нары, бандит», уровень Bronze");
		#endif
	} else if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «На нары, бандит» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «На нары, бандит», уровень Silver");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «На нары, бандит» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «На нары, бандит», уровень Gold");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «На нары, бандит» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «На нары, бандит», уровень Platinum");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «На нары, бандит» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «На нары, бандит», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `BenchGangster` = `BenchGangster` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Спи штат спокойно»
Achievement:SleepWell(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:SleepWell %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 15) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Спи штат спокойно» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Спи штат спокойно», уровень Bronze");
		#endif
	} else if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Спи штат спокойно» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Спи штат спокойно», уровень Silver");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Спи штат спокойно» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Спи штат спокойно», уровень Gold");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Спи штат спокойно» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Спи штат спокойно», уровень Platinum");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Спи штат спокойно» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Спи штат спокойно», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `SleepWell` = `SleepWell` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Карманы на изнанку»
Achievement:PocketsInside(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:PocketsInside %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 25) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Карманы на изнанку» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Карманы на изнанку», уровень Bronze");
		#endif
	} else if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Карманы на изнанку» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Карманы на изнанку», уровень Silver");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Карманы на изнанку» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Карманы на изнанку», уровень Gold");
		#endif
	} else if(new_value == 150) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Карманы на изнанку» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Карманы на изнанку», уровень Platinum");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Карманы на изнанку» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Карманы на изнанку», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `PocketsInside` = `PocketsInside` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Подарок - воля»
Achievement:GiftWill(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:GiftWill %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Подарок - воля» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Подарок - воля», уровень Bronze");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Подарок - воля» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Подарок - воля», уровень Silver");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Подарок - воля» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Подарок - воля», уровень Gold");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Подарок - воля» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Подарок - воля», уровень Platinum");
		#endif
	} else if(new_value == 1000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Подарок - воля» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Подарок - воля», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `GiftWill` = `GiftWill` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Оформляем гражданство»
Achievement:MakeCitizenship(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:MakeCitizenship %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Оформляем гражданство» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Оформляем гражданство», уровень Bronze");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Оформляем гражданство» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Оформляем гражданство», уровень Silver");
		#endif
	} else if(new_value == 200) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Оформляем гражданство» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Оформляем гражданство», уровень Gold");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Оформляем гражданство» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Оформляем гражданство», уровень Platinum");
		#endif
	} else if(new_value == 700) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Оформляем гражданство» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Оформляем гражданство», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `MakeCitizenship` = `MakeCitizenship` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Настоящий редактор»
Achievement:RealEditor(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:RealEditor %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Настоящий редактор» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Настоящий редактор», уровень Bronze");
		#endif
	} else if(new_value == 200) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Настоящий редактор» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Настоящий редактор», уровень Silver");
		#endif
	} else if(new_value == 300) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Настоящий редактор» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Настоящий редактор», уровень Gold");
		#endif
	} else if(new_value == 600) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Настоящий редактор» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Настоящий редактор», уровень Platinum");
		#endif
	} else if(new_value == 1000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Настоящий редактор» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Настоящий редактор», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `RealEditor` = `RealEditor` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Война за территорию»
Achievement:BattleSquares(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:BattleSquares %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 30) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Война за территорию» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Война за территорию», уровень Bronze");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Война за территорию» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Война за территорию», уровень Silver");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Война за территорию» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Война за территорию», уровень Gold");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Война за территорию» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Война за территорию», уровень Platinum");
		#endif
	} else if(new_value == 1000) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Война за территорию» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Война за территорию», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `BattleSquares` = `BattleSquares` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Наркоторговец»
Achievement:DrugTrafficker(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:DrugTrafficker %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 75) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Наркоторговец» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Наркоторговец», уровень Bronze");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Наркоторговец» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Наркоторговец», уровень Silver");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Наркоторговец» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Наркоторговец», уровень Gold");
		#endif
	} else if(new_value == 700) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Наркоторговец» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Наркоторговец», уровень Platinum");
		#endif
	} else if(new_value == 1250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Наркоторговец» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Наркоторговец», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `DrugTrafficker` = `DrugTrafficker` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Машинка напрокат»
Achievement:CarRental(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:CarRental %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 5) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Машинка напрокат» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Машинка напрокат», уровень Bronze");
		#endif
	} else if(new_value == 15) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Машинка напрокат» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Машинка напрокат», уровень Silver");
		#endif
	} else if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Машинка напрокат» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Машинка напрокат», уровень Gold");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Машинка напрокат» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Машинка напрокат», уровень Platinum");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Машинка напрокат» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Машинка напрокат», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `CarRental` = `CarRental` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Кража века»
Achievement:CenturyTheft(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:CenturyTheft %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 10) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Кража века» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Кража века», уровень Bronze");
		#endif
	} else if(new_value == 50) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Кража века» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Кража века», уровень Silver");
		#endif
	} else if(new_value == 100) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Кража века» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Кража века», уровень Gold");
		#endif
	} else if(new_value == 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Кража века» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Кража века», уровень Platinum");
		#endif
	} else if(new_value == 500) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Кража века» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Кража века», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `CenturyTheft` = `CenturyTheft` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

// «Сделка? По рукам!»
Achievement:Deal(const playerid, const new_value, const old_value) {
	#if defined DEBUG_ACHIEVEMENT
		printf("Achievement:Deal %i %i %i", playerid, new_value, old_value);
	#endif

	if(new_value == 5) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Сделка? По рукам!» - "ACHIEVEMENT_BRONZE_COLOR"уровень повышен до Bronze");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_0 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_0, "Выполнение достижения «Сделка? По рукам!», уровень Bronze");
		#endif
	} else if(new_value == 10) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Сделка? По рукам!» - "ACHIEVEMENT_SILVER_COLOR"уровень повышен до Silver");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_1 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_1, "Выполнение достижения «Сделка? По рукам!», уровень Silver");
		#endif
	} else if(new_value == 20) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Сделка? По рукам!» - "ACHIEVEMENT_GOLD_COLOR"уровень повышен до Gold");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_2 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_2, "Выполнение достижения «Сделка? По рукам!», уровень Gold");
		#endif
	} else if(new_value == 40) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Сделка? По рукам!» - "ACHIEVEMENT_PLATINUM_COLOR"уровень повышен до Platinum");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_3 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_3, "Выполнение достижения «Сделка? По рукам!», уровень Platinum");
		#endif
	} else if(new_value == 60) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Достижение «Сделка? По рукам!» - "ACHIEVEMENT_RUBY_COLOR"уровень повышен до Ruby");

		#if ACHIEVEMENT_GIVE_MONEY_LEVEL_4 > 0
			AddPlayerEXP(playerid, ACHIEVEMENT_GIVE_MONEY_LEVEL_4, "Выполнение достижения «Сделка? По рукам!», уровень Ruby");
		#endif
	}
	new ach_query[144];	
	format(ach_query, sizeof(ach_query), "UPDATE `players` SET `Deal` = `Deal` + 1 WHERE ID = %i LIMIT 1;", PlayerInfo[playerid][pID]);
	mysql_pquery(database, ach_query);
}

alias:achievement("ach");
CMD:achievement(playerid, params[]) {
	Dialog_Show(playerid, Dialog:DIALOG_ACHIEVEMENT);
}

DialogCreate:DIALOG_ACHIEVEMENT(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_ACHIEVEMENT, DIALOG_STYLE_LIST,
		""COLOR_BLUE"Достижения",
		""COLOR_WHITE"«Война за территорию»\n\
			«Включай мигалки»\n\
			«Дальний путь»\n\
			«Карманы на изнанку»\n\
			«Копы в деле»\n\
			«Машинка напрокат»\n\
			«Мелочь в пепельнице»\n\
			«На нары, бандит»\n\
			«Наркоторговец»\n\
			«Настоящий редактор»\n\
			«Не пройдешь»\n\
			«Опасный груз»\n\
			«Оформляем гражданство»\n\
			«Первоклассный пилот»\n\
			«Подарок - воля»\n\
			«Поставка оружия»\n\
			«Солдат спит, служба идет»\n\
			«Спи штат спокойно»\n\
			«Тяжелый груз»\n\
			«Фермерство»\n\
			«Чистый город»\n\
			«Кража века»\n\
			«Ролевая игра»",
		"Выбрать", "Закрыть"
	);
}

DialogResponse:DIALOG_ACHIEVEMENT(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		new 
			level_1,
			level_2,
			level_3,
			level_4,
			level_5,
			count;

		new 
			level_text[128],
			level_title[48];

		switch(listitem) {
			case 0: { 
				level_1 = 30;
   				level_2 = 100;
   				level_3 = 250;
   				level_4 = 500;
   				level_5 = 1000;

   				strcat(level_text, "Для получения достижения необходимо участвовать в захвате территорий");
   				strcat(level_title, "«Война за территорию»");
   				count = PlayerBattleSquares[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i\n\n"COLOR_WHITE"Следующая награда: "COLOR_GREEN"%i EXP", level_text, count, level_1, ACHIEVEMENT_GIVE_MONEY_LEVEL_0); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i\n\n"COLOR_WHITE"Следующая награда: "COLOR_GREEN"%i EXP", level_text, count, level_2, ACHIEVEMENT_GIVE_MONEY_LEVEL_1); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i\n\n"COLOR_WHITE"Следующая награда: "COLOR_GREEN"%i EXP", level_text, count, level_3, ACHIEVEMENT_GIVE_MONEY_LEVEL_2); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i\n\n"COLOR_WHITE"Следующая награда: "COLOR_GREEN"%i EXP", level_text, count, level_4, ACHIEVEMENT_GIVE_MONEY_LEVEL_3); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i\n\n"COLOR_WHITE"Следующая награда: "COLOR_GREEN"%i EXP", level_text, count, level_5, ACHIEVEMENT_GIVE_MONEY_LEVEL_4); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Война за территорию»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 1: {
				level_1 = 10;
   				level_2 = 25;
   				level_3 = 50;
   				level_4 = 100;
   				level_5 = 250;

   				strcat(level_text, "Для получения достижения необходимо патрулировать территории");
   				strcat(level_title, "«Включай мигалки»");
   				count = PlayerTurnFlashers[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Включай мигалки»",
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 2: {
				level_1 = 50;
   				level_2 = 250;
   				level_3 = 500;
   				level_4 = 1000;
   				level_5 = 2000;

   				strcat(level_text, "Для получения достижения необходимо водить автобус");
   				strcat(level_title, "«Дальний путь»");
   				count = PlayerLongWay[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Дальний путь»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 3: {
				level_1 = 25;
   				level_2 = 50;
   				level_3 = 100;
   				level_4 = 150;
   				level_5 = 250;

   				strcat(level_text, "Для получения достижения необходимо обыскивать игроков");
   				strcat(level_title, "«Карманы на изнанку»");
   				count = PlayerPocketsInside[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Карманы на изнанку»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 4: {
				level_1 = 25;
   				level_2 = 50;
   				level_3 = 100;
   				level_4 = 250;
   				level_5 = 500;

   				strcat(level_text, "Для получения достижения необходимо проверять документы");
   				strcat(level_title, "«Копы в деле»");
   				count = PlayerCopsIn[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Копы в деле»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 5: {
				level_1 = 5;
   				level_2 = 15;
   				level_3 = 50;
   				level_4 = 100;
   				level_5 = 250;

   				strcat(level_text, "Для получения достижения необходимо заниматься автоугоном");
   				strcat(level_title, "«Машинка напрокат»");
   				count = PlayerCarRental[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Машинка напрокат»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 6: {
				level_1 = 50;
   				level_2 = 250;
   				level_3 = 500;
   				level_4 = 1000;
   				level_5 = 2000;

   				strcat(level_text, "Для получения достижения необходимо работать таксистом");
   				strcat(level_title, "«Мелочь в пепельнице»");
   				count = PlayerTrifle[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Мелочь в пепельнице»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 7: {
				level_1 = 15;
   				level_2 = 50;
   				level_3 = 100;
   				level_4 = 250;
   				level_5 = 500;

   				strcat(level_text, "Для получения достижения необходимо арестовывать преступников (Полиция)");
   				strcat(level_title, "«На нары, бандит»");
   				count = PlayerBenchGangster[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«На нары, бандит»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 8: {
				level_1 = 75;
   				level_2 = 250;
   				level_3 = 500;
   				level_4 = 700;
   				level_5 = 1250;

   				strcat(level_text, "Для получения достижения необходимо продавать наркотики");
   				strcat(level_title, "«Наркоторговец»");
   				count = PlayerDrugTrafficker[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Наркоторговец»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 9: {
				level_1 = 100;
   				level_2 = 200;
   				level_3 = 300;
   				level_4 = 600;
   				level_5 = 1000;

   				strcat(level_text, "Для получения достижения необходимо редактировать объявления");
   				strcat(level_title, "«Настоящий редактор»");
   				count = PlayerRealEditor[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Настоящий редактор»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 10: {
				level_1 = 10;
   				level_2 = 25;
   				level_3 = 50;
   				level_4 = 100;
   				level_5 = 250;

   				strcat(level_text, "Для получения достижения необходимо задерживать преступников на военной базе");
   				strcat(level_title, "«Не пройдешь»");
   				count = PlayerWillNot[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Не пройдешь»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 11: {
				level_1 = 10;
   				level_2 = 50;
   				level_3 = 100;
   				level_4 = 250;
   				level_5 = 1000;

   				strcat(level_text, "Для получения достижения необходимо доставлять фургоны с оружием");
   				strcat(level_title, "«Опасный груз»");
   				count = PlayerDangerous[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Опасный груз»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 12: {
				level_1 = 50;
   				level_2 = 100;
   				level_3 = 200;
   				level_4 = 500;
   				level_5 = 700;

   				strcat(level_text, "Для получения достижения необходимо выдавать паспорта игрокам");
   				strcat(level_title, "«Оформляем гражданство»");
   				count = PlayerMakeCitizenship[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Оформляем гражданство»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 13: {
				level_1 = 50;
   				level_2 = 250;
   				level_3 = 500;
   				level_4 = 1000;
   				level_5 = 2000;

   				strcat(level_text, "Для получения достижения необходимо работать пилотом самолета");
   				strcat(level_title, "«Первоклассный пилот»");
   				count = PlayerFirstClassPilot[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Первоклассный пилот»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 14: {
				level_1 = 50;
   				level_2 = 100;
   				level_3 = 250;
   				level_4 = 500;
   				level_5 = 1000;

   				strcat(level_text, "Для получения достижения необходимо работать адвокатом");
   				strcat(level_title, "«Подарок - воля»");
   				count = PlayerGiftWill[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Подарок - воля»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 15: {
				level_1 = 50;
   				level_2 = 250;
   				level_3 = 500;
   				level_4 = 1000;
   				level_5 = 2000;

   				strcat(level_text, "Для получения достижения необходимо работать на военном заводе");
   				strcat(level_title, "«Поставка оружия»");
   				count = PlayerWeaponSupply[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Поставка оружия»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 16: {
				level_1 = 50;
   				level_2 = 100;
   				level_3 = 200;
   				level_4 = 300;
   				level_5 = 500;

   				strcat(level_text, "Для получения достижения необходимо патрулировать территории (/patrol)");
   				strcat(level_title, "«Солдат спит, служба идет»");
   				count = PlayerSoldierSleeping[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Отсутствует\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Солдат спит, служба идет»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 17: {
				level_1 = 15;
   				level_2 = 50;
   				level_3 = 100;
   				level_4 = 250;
   				level_5 = 500;

   				strcat(level_text, "Для получения достижения необходимо арестовывать преступников (ФБР)");
   				strcat(level_title, "«Спи штат спокойно»");
   				count = PlayerSleepWell[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Спи штат спокойно»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 18: {
				level_1 = 50;
   				level_2 = 250;
   				level_3 = 500;
   				level_4 = 1000;
   				level_5 = 2000;

   				strcat(level_text, "Для получения достижения необходимо работать грузчиком");
   				strcat(level_title, "«Тяжелый груз»");
   				count = PlayerHeavyLoad[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Тяжелый груз»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 19: {
				level_1 = 50;
   				level_2 = 250;
   				level_3 = 500;
   				level_4 = 1000;
   				level_5 = 2000;

   				strcat(level_text, "Для получения достижения необходимо работать фермером");
   				strcat(level_title, "«Фермерство»");
   				count = PlayerFarming[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Фермерство»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			case 20: {
				level_1 = 10;
   				level_2 = 25;
   				level_3 = 50;
   				level_4 = 100;
   				level_5 = 250;

   				strcat(level_text, "Для получения достижения необходимо работать водителем мусоровоза");
   				strcat(level_title, "«Чистый город»");
   				count = PlayerCleanCity[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Чистый город»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}
			
			case 21: {
				level_1 = 10;
   				level_2 = 50;
   				level_3 = 100;
   				level_4 = 250;
   				level_5 = 500;

   				strcat(level_text, "Для получения достижения воровать материалы с базы Армии");
   				strcat(level_title, "«Кража века»");
   				count = PlayerCleanCity[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Кража века»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}						

			case 22: {
				level_1 = 500;
   				level_2 = 1000;
   				level_3 = 1500;
   				level_4 = 2000;
   				level_5 = 2500;

   				strcat(level_text, "Для получения достижения необходимо отыгрывать RP (/me, /do, /try)");
   				strcat(level_title, "«Ролевая игра»");
   				count = PlayerRPOurAll[playerid];
   				
				if(count < level_1) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BLOCKED_COLOR"Заблокировано\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_1); 
				} else if (count >= level_1 && count < level_2) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_BRONZE_COLOR"Bronze\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_2); 
				} else if (count >= level_2 && count < level_3) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_SILVER_COLOR"Silver\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_3); 
				} else if (count >= level_3 && count < level_4) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_GOLD_COLOR"Gold\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_4); 
				} else if (count >= level_4 && count < level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_PLATINUM_COLOR"Platinum\nТекущий прогрес "COLOR_GREEN"%i"COLOR_WHITE" из "COLOR_GREEN"%i", level_text, count, level_5); 
				} else if (count >= level_5) {
					format(big_string, sizeof(big_string), ""COLOR_GREEN"%s\n\n"COLOR_WHITE"Текущий уровень: "ACHIEVEMENT_RUBY_COLOR"Ruby\nТекущий прогрес "COLOR_GREEN"%i", level_text, count); 
				}

				Dialog_MessageEx(playerid, Dialog:DIALOG_ACHIEVEMENT_RETURN, 
					""COLOR_BLUE"«Ролевая игра»", 
					big_string, 
					"Назад", "Закрыть"
				);
			}

			default: {
				Dialog_Show(playerid, Dialog:DIALOG_ACHIEVEMENT);
			}
		}
	}
	return 1;
}

DialogResponse:DIALOG_ACHIEVEMENT_RETURN(playerid, response, listitem, inputtext[]) {
	if(!response) 
	{
		return Dialog_Show(playerid, Dialog:DIALOG_ACHIEVEMENT);
	}
}
