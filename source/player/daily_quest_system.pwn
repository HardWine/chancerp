#include <YSI_Coding\y_hooks>

enum 
{
	E_MUSHROOM,
	E_GARBAGE_CAN,
	E_GARBAGE_LOADER,
	E_CLEANING,
	E_TIME,
	E_TRASH_DRIVER,
	E_FLY,
	E_BUS,
	E_DRUGS,
	E_ARENAS,
	E_ARENA_BONUS,
	E_BUY_WEAPON,
	E_BUY_MASK,
	E_GAME_CASINO,
	E_CASINO_CROUP,
	E_GAME_MACHINE,
	E_JOB_COLLECTORS,
	E_JOB_FARMING
}

enum 
	E_DAILY_QUEST {
		E_TYPE,
		Fraction:E_FRACTION,
		E_TEXT[144],
		E_COUNT,
		E_AWARD
	};

enum 
	E_PLAYER_DAILY_QUEST {
		E_QUEST,
		E_PROGRESS
	};

new 
	DailyQuest[][E_DAILY_QUEST] = {
		{E_MUSHROOM, FRACTION_NONE, "Собрать грибы не менее 5 раз", 5, 300},
		{E_MUSHROOM, FRACTION_NONE, "Собрать грибы не менее 25 раз", 25, 900},
		{E_MUSHROOM, FRACTION_NONE, "Собрать грибы не менее 50 раз", 50, 2000},
		{E_GARBAGE_CAN, FRACTION_NONE, "Обыскать мусорные баки не менее 5 раз", 5, 300},
		{E_GARBAGE_CAN, FRACTION_NONE, "Обыскать мусорные баки не менее 10 раз", 10, 600},
		{E_GARBAGE_CAN, FRACTION_NONE, "Обыскать мусорные баки не менее 25 раз", 25, 1200},
		{E_GARBAGE_LOADER, FRACTION_NONE, "Отнести 5 ящиков на работу грузчика", 5, 250},
		{E_GARBAGE_LOADER, FRACTION_NONE, "Отнести 10 ящиков на работу грузчика", 10, 500},
		{E_GARBAGE_LOADER, FRACTION_NONE, "Отнести 25 ящиков на работу грузчика", 25, 1250},
		{E_CLEANING, FRACTION_NONE, "Сдать 1 мусорный пакет на работе уборщика пляжа", 1, 200},
		{E_CLEANING, FRACTION_NONE, "Сдать 2 мусорный пакет на работе уборщика пляжа", 2, 400},
		{E_CLEANING, FRACTION_NONE, "Сдать 3 мусорный пакет на работе уборщика пляжа", 3, 600},
		{E_TIME, FRACTION_NONE, "Отыграть 1 час", 1, 500},
		{E_TIME, FRACTION_NONE, "Отыграть 2 часа", 2, 1000},
		{E_TIME, FRACTION_NONE, "Отыграть 3 часа", 3, 1500},
		{E_TIME, FRACTION_NONE, "Отыграть 4 часа", 4, 2000},
		{E_TIME, FRACTION_NONE, "Отыграть 6 часа", 6, 3000},
		{E_TRASH_DRIVER, FRACTION_NONE, "Завершить 1 рейс на работе водителя мусоровоза", 1, 250},
		{E_TRASH_DRIVER, FRACTION_NONE, "Завершить 3 рейс на работе водителя мусоровоза", 3, 500},
		{E_TRASH_DRIVER, FRACTION_NONE, "Завершить 5 рейс на работе водителя мусоровоза", 5, 900},
		{E_FLY, FRACTION_NONE, "Завершить 1 рейс на работе пилота", 1, 250},
		{E_FLY, FRACTION_NONE, "Завершить 5 рейс на работе пилота", 5, 900},
		{E_FLY, FRACTION_NONE, "Завершить 10 рейс на работе пилота", 10, 1500},
		{E_BUS, FRACTION_NONE, "Завершить 1 рейс на работе водителя автобуса", 1, 250},
		{E_BUS, FRACTION_NONE, "Завершить 3 рейс на работе водителя автобуса", 3, 500},
		{E_BUS, FRACTION_NONE, "Завершить 5 рейс на работе водителя автобуса", 5, 1000},
		{E_DRUGS, FRACTION_NONE, "Употребить наркотики не менее 3 раз", 3, 200},
		{E_DRUGS, FRACTION_NONE, "Употребить наркотики не менее 5 раз", 5, 300},
		{E_DRUGS, FRACTION_NONE, "Употребить наркотики не менее 10 раз", 10, 500},
		{E_ARENAS, FRACTION_NONE, "Убить 5 игроков на арене", 5, 200},
		{E_ARENAS, FRACTION_NONE, "Убить 10 игроков на арене", 10, 500},
		{E_ARENAS, FRACTION_NONE, "Убить 25 игроков на арене", 25, 1000},
		{E_ARENA_BONUS, FRACTION_NONE, "Собрать 1 бонус на арене", 1, 200},
		{E_ARENA_BONUS, FRACTION_NONE, "Собрать 3 бонуса на арене", 3, 300},
		{E_ARENA_BONUS, FRACTION_NONE, "Собрать 5 бонусов на арене", 5, 500},
		{E_BUY_WEAPON, FRACTION_NONE, "Купить любое оружие в оруженом магазине", 1, 300},
		{E_BUY_MASK, FRACTION_NONE, "Купить маску в магазине 24/7", 1, 300},
		{E_GAME_CASINO, FRACTION_NONE, "Сыграть в казино не менее 3 раз", 3, 250},
		{E_GAME_CASINO, FRACTION_NONE, "Сыграть в казино не менее 5 раз", 5, 500},
		{E_GAME_CASINO, FRACTION_NONE, "Сыграть в казино не менее 10 раз", 10, 1000},
		{E_CASINO_CROUP, FRACTION_NONE, "Заработать чаевые в казино с 1 ставки", 1, 250},
		{E_CASINO_CROUP, FRACTION_NONE, "Заработать чаевые в казино с 3 ставок", 3, 500},
		{E_CASINO_CROUP, FRACTION_NONE, "Заработать чаевые в казино с 5 ставок", 5, 1000},
		{E_GAME_MACHINE, FRACTION_NONE, "Прокрутить игровые автоматы не менее 5 раз", 5, 250},
		{E_GAME_MACHINE, FRACTION_NONE, "Прокрутить игровые автоматы не менее 10 раз", 10, 500},
		{E_GAME_MACHINE, FRACTION_NONE, "Прокрутить игровые автоматы не менее 25 раз", 25, 1000},
		{E_JOB_COLLECTORS, FRACTION_NONE, "Завершить 1 рейс на работу инкасатора", 1, 250},
		{E_JOB_COLLECTORS, FRACTION_NONE, "Завершить 3 рейса на работу инкасатора", 3, 500},
		{E_JOB_COLLECTORS, FRACTION_NONE, "Завершить 5 рейсов на работу инкасатора", 5, 1250},
		{E_JOB_FARMING, FRACTION_NONE, "Собрать 5 кустов на работе фермера", 5, 250},
		{E_JOB_FARMING, FRACTION_NONE, "Собрать 10 кустов на работе фермера", 10, 500},
		{E_JOB_FARMING, FRACTION_NONE, "Собрать 25 кустов на работе фермера", 25, 1000}
	};

// Арена
// Подобрать бонусы на арене
// Покупка оружия в амунации
// Покупка маски в 24/7
// Ставка в казино
// Чаевые со ставки в казино
// Игровые автоматы
// Работа инкасатором
// Работа на ферме

// Добавить аптечки в 24/7

hook OnGameModeInit()
{
	for(new i = 0; i < sizeof(DailyQuest); i++)
	{
		printf("%i. %s", i + 1, DailyQuest[i][E_TEXT]);
	}
}
new 
	PlayerDailyQuest[MAX_PLAYERS][3][E_PLAYER_DAILY_QUEST];

hook OnPlayerAuthorization(const playerid) {
	mysql_format(database, 
		small_string, sizeof(small_string), 
		"SELECT * FROM player_daily_quest WHERE PlayerID = 1616 AND DATE(`Date`) = CURRENT_DATE()",
			PlayerInfo[playerid][pID]
	);
	mysql_pquery(database, small_string, "@_LoadPlayerDailyQuest", "i", playerid);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

@_LoadPlayerDailyQuest(const playerid);
@_LoadPlayerDailyQuest(const playerid) {
	new 
		rows = cache_get_row_count();

	if(rows) {
		for(new i = 0; i < rows; i++) {
			PlayerDailyQuest[playerid][i][E_QUEST] = cache_get_field_content_int(i, "Quest");
			PlayerDailyQuest[playerid][i][E_PROGRESS] = cache_get_field_content_int(i, "Progress");
 		}
	} else {
		GeneratePlayerQuest(playerid);
	}
}

CMD:quest(playerid, params[]) {
	new arrayid;

	huge_string[0] = EOS;
	huge_string = "Задание\tПрогресс\tНаграда\tСтатус\n";

	for(new i = 0; i < sizeof(PlayerDailyQuest[]); i++) {
		arrayid = PlayerDailyQuest[playerid][i][E_QUEST];

		format(big_string, sizeof(big_string), 
			"%s\t"COLOR_GREEN"%i\t"COLOR_GREEN"%i EXP\t%s\n",
				DailyQuest[arrayid][E_TEXT], PlayerDailyQuest[playerid][i][E_PROGRESS], DailyQuest[arrayid][E_AWARD], (PlayerDailyQuest[playerid][i][E_PROGRESS] >= DailyQuest[PlayerDailyQuest[playerid][i][E_QUEST]][E_COUNT]) ? (""COLOR_GREEN"Выполнено") : (""COLOR_ORANGE"Не выполнено")
		);
		strcat(huge_string, big_string);
	}
	strcat(huge_string, ""COLOR_WHITE"Сменить задание "COLOR_GREEN"№1"COLOR_WHITE"\t-\t-\tСтоимость "COLOR_ORANGE"50 EXP"COLOR_WHITE"\n"COLOR_WHITE"Сменить задание "COLOR_GREEN"№2"COLOR_WHITE"\t-\t-\tСтоимость "COLOR_ORANGE"50 EXP"COLOR_WHITE"\n"COLOR_WHITE"Сменить задание "COLOR_GREEN"№3"COLOR_WHITE"\t-\t-\tСтоимость "COLOR_ORANGE"50 EXP"COLOR_WHITE"\n");
	return ShowPlayerDialog(playerid, DIALOG_CMD_ACH, DIALOG_STYLE_TABLIST_HEADERS, ""COLOR_BLUE"Ежедневные задания", huge_string, "Закрыть", "");
}

stock GeneratePlayerQuest(const playerid) {
	new Fraction:fraction = GetPlayerFraction(playerid);

	for(new i = 0; i < sizeof(PlayerDailyQuest[]); i++) {
		regeneration:
		PlayerDailyQuest[playerid][i][E_QUEST] = random(sizeof(DailyQuest));
		printf("%i %i", DailyQuest[PlayerDailyQuest[playerid][i][E_QUEST]][E_FRACTION], fraction);
		// if(DailyQuest[PlayerDailyQuest[playerid][i][E_QUEST]][E_FRACTION] != fraction) 
		// {
		// 	goto regeneration;
		// }
		printf("Задание %s", DailyQuest[PlayerDailyQuest[0][i][E_QUEST]][E_TEXT]);
		
		if(i != 0) {
			for(new k = 0; k < i; k++) {
				if(PlayerDailyQuest[playerid][k][E_QUEST] == PlayerDailyQuest[playerid][i][E_QUEST]) {
					printf("%s", PlayerDailyQuest[playerid][k][E_QUEST]);
					printf("задание повторилось надо новое");
					goto regeneration;
				}
			}
		}
	}

	for(new i = 0; i < sizeof(PlayerDailyQuest[]); i++) {
		mysql_format(database, 
			big_string, sizeof(big_string), 
			"INSERT INTO `player_daily_quest` (`PlayerID`, `Quest`, `Date`) VALUES (%i, %i, CURRENT_DATE());", 
				PlayerInfo[playerid][pID],
				PlayerDailyQuest[playerid][i][E_QUEST]
		);
		mysql_pquery(database, big_string);
	}
}

stock RegeneratePlayerQuest(const playerid, const arrayid) {
	new Fraction:fraction = GetPlayerFraction(playerid);
	new i = arrayid;
	new old_quest = PlayerDailyQuest[playerid][i][E_QUEST];

	regeneration:
	PlayerDailyQuest[playerid][i][E_QUEST] = random(sizeof(DailyQuest));
	printf("%i %i", DailyQuest[PlayerDailyQuest[playerid][i][E_QUEST]][E_FRACTION], fraction);
	// if(DailyQuest[PlayerDailyQuest[playerid][i][E_QUEST]][E_FRACTION] != fraction) 
	// {
	// 	goto regeneration;
	// }
	printf("Задание %s", DailyQuest[PlayerDailyQuest[0][i][E_QUEST]][E_TEXT]);
	
	for(new k = 0; k < i; k++) {
		if(PlayerDailyQuest[playerid][k][E_QUEST] == PlayerDailyQuest[playerid][i][E_QUEST]) {
			printf("%s", PlayerDailyQuest[playerid][k][E_QUEST]);
			printf("задание повторилось надо новое");
			goto regeneration;
		}
	}

	PlayerDailyQuest[playerid][i][E_PROGRESS] = 0;

	mysql_format(database, 
		big_string, sizeof(big_string), 
		"UPDATE `player_daily_quest` SET `Quest` = %i, `Progress` = 0 WHERE `Quest` = %i AND PlayerID = %i AND Date = CURRENT_DATE()", 
			PlayerDailyQuest[playerid][i][E_QUEST],
			old_quest,
			PlayerInfo[playerid][pID]
	);
	mysql_pquery(database, big_string);
}

stock UpdatePlayerProgressQuest(const playerid, const type)
{
	for(new i = 0; i < sizeof(PlayerDailyQuest[]); i++) {
		if(DailyQuest[PlayerDailyQuest[playerid][i][E_QUEST]][E_TYPE] == type) {
			PlayerDailyQuest[playerid][i][E_PROGRESS] ++;

			mysql_format(database, 
				small_string, sizeof(small_string), 
					"UPDATE `player_daily_quest` SET `Progress` = `Progress` + 1 WHERE PlayerID = %i AND Quest = %i AND Date = CURRENT_DATE() LIMIT 1", 
						PlayerInfo[playerid][pID],
						PlayerDailyQuest[playerid][i][E_QUEST]
			);
			printf(small_string);
			mysql_pquery(database, small_string);

			if(DailyQuest[PlayerDailyQuest[playerid][i][E_QUEST]][E_COUNT] == PlayerDailyQuest[playerid][i][E_PROGRESS])
			{
				format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы выполнили ежедневное задание: "COLOR_GREEN"%s", DailyQuest[PlayerDailyQuest[playerid][i][E_QUEST]][E_TEXT]);
				SendClientMessage(playerid, -1, small_string);

				format(small_string, sizeof(small_string), ""COLOR_WHITE"Награда в виде "COLOR_GREEN"%i EXP"COLOR_WHITE" зачислена на Ваш аккаунт", DailyQuest[PlayerDailyQuest[playerid][i][E_QUEST]][E_AWARD]);
				SendClientMessage(playerid, -1, small_string);
				AddPlayerEXP(playerid, DailyQuest[PlayerDailyQuest[playerid][i][E_QUEST]][E_AWARD], "Выполнение ежедневного задания %s", DailyQuest[PlayerDailyQuest[playerid][i][E_QUEST]][E_TEXT]);
			}
		}
	}
}

CMD:addquest(playerid, params[]) {
	new 
		value;

	if(sscanf(params, "i", value)) {
		return 1;
	}

	UpdatePlayerProgressQuest(playerid, E_JOB_FARMING);
	return true;
}

CMD:reg(playerid, params[])
{
	new 
		value;

	if(sscanf(params, "i", value)) {
		return 1;
	}

	RegeneratePlayerQuest(playerid, value);
}
