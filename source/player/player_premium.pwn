#if defined player_premium_included
	#endinput
#endif

#define player_premium_included

#include <YSI_Coding\y_hooks>

new 
	bool: PlayerPremuimAccount[MAX_PLAYERS] = {false, ...};

stock IsPlayerPremiumAccount(const playerid) {
	return PlayerPremuimAccount[playerid];
}

hook OnPlayerConnect(playerid) {
	PlayerPremuimAccount[playerid] = false;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason 

	PlayerPremuimAccount[playerid] = false;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

forward ActivatePremium(playerid);
public ActivatePremium(playerid) {

	new days = GetPlayerNumberDaysPremium(playerid);

	if(days > 0) {
		format(big_string, sizeof(big_string), ""COLOR_WHITE"Вы авторизовались как игрок с "COLOR_GREEN"премиум аккаунтом"COLOR_WHITE".\n\
			До окончания действия премиум аккаунта осталось %i дней.\n\n\
			"COLOR_ORANGE"На момент действия премиум аккаунта, Вы получаете:"COLOR_WHITE"\n\
			\t- X2 зарплаты на всех гражданских работах\n\
			\t- X2 зарплаты во всех организациях\n\
			\t- X2 цена при продаже собранных грибов\n\
			\t- Иммунитет к штрафам за превышение скорости\n\
			\t- Ежедневный бонус в размере 499 EXP за вход\n\
			\t- Доступ к списку администрации в сети (/admins)\n\
			\t- Возможность перемещать транспорт к себе (/getcar)\n\
			\t- X3 Увеличенный лимит на передачу средств (/pay)\n\n\
			"COLOR_GREEN"Приятной игры на Chance RolePlay!",
			days
		);

		if(PlayerInfo[playerid][pGotBonus] == 0) {

			PlayerInfo[playerid][pGotBonus] = 1;
			SendClientMessage(playerid, -1, "(Premium) "COLOR_GREEN"Вы получили 499 EXP за вход в игру");
			AddPlayerEXP(playerid, 499, "Ежедневный бонус за премиум аккаунт");
			SetPlayerInt(playerid, "GotBonus", PlayerInfo[playerid][pGotBonus]);
		}	

		PlayerPremuimAccount[playerid] = true;
		Dialog_Message(playerid, "Премиум аккаунт", big_string, "Закрыть");
	} else {
		PlayerPremuimAccount[playerid] = false;
	}
	return 1;
}


stock GivePlayerPremiumAccount(const playerid, const dayz, updatenow) {

	if(updatenow != 1) updatenow = 0;

	mysql_format(database, 
		small_string, sizeof(small_string), 
		"INSERT INTO `player_premium`(`PlayerID`, `DateStart`, `DateStop`) VALUES (%i, CURRENT_TIMESTAMP(), CURRENT_TIMESTAMP() + INTERVAL %i DAY)", 
			PlayerInfo[playerid][pID], 
			dayz
	);
	if(mysql_pquery(database, small_string)) {
		if(updatenow == 1) SetTimerEx("ActivatePremium", 3000, 0, "i", playerid);
		return true;
	} else {
		return false;
	}
}

stock GetPlayerNumberDaysPremium(const playerid) {
	mysql_format(database,
		small_string, sizeof(small_string),
		"SELECT DATEDIFF(DateStop, DateStart) AS Day FROM `player_premium` WHERE `PlayerID` = %i AND `DateStop` > CURRENT_TIMESTAMP()",
			PlayerInfo[playerid][pID]
	);
	mysql_query(database, small_string, true);

	new
		rows = cache_get_row_count();

	if(rows == 0) {
		return false;
	} else {
		return cache_get_field_content_int(0, "Day");
	}
}

DialogCreate:DIALOG_FREE_PREMIUM(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_FREE_PREMIUM, DIALOG_STYLE_MSGBOX,
		""COLOR_BLUE"C Возвращением!", "{FFFFFF}Мы рады что вы снова с нами!\n\n\
		В честь этого хотим вручить вам "COLOR_GREEN"премиум аккаунт на 7 дней", "Забрать", ""
	);
}

DialogResponse:DIALOG_FREE_PREMIUM(playerid, response, listitem, inputtext[]) {
	ActivatePremium(playerid);
	return 1;
}

DialogCreate:DIALOG_GET_PREMIUM(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_GET_PREMIUM, DIALOG_STYLE_MSGBOX,
		""COLOR_BLUE"Премиум аккаунт", "{FFFFFF}На сервере появился премиум, покупая его вы получаете:\n\n\
		\t- X2 зарплаты на всех гражданских работах\n\
		\t- X2 зарплаты во всех организациях\n\
		\t- X2 цена при продаже собранных грибов\n\
		\t- Иммунитет к штрафам за превышение скорости\n\
		\t- Ежедневный бонус в размере 499 EXP за вход\n\
		\t- Доступ к списку администрации в сети (/admins)\n\
		\t- Возможность перемещать транспорт к себе (/getcar)\n\
		\t- Увеличенный лимит на передачу средств (/pay)\n\
		"COLOR_BLUE"Нажмите далее чтобы получить премиум-аккаунт", "Далее", "Закрыть"
	);
}

DialogResponse:DIALOG_GET_PREMIUM(playerid, response, listitem, inputtext[]) {
	if(!response) return 1;

	Dialog_Show(playerid, Dialog:DIALOG_LIST_PREMIUM);
	return 1;
}

DialogCreate:DIALOG_LIST_PREMIUM(playerid) {
	return Dialog_Open(playerid, Dialog:DIALOG_LIST_PREMIUM, DIALOG_STYLE_TABLIST_HEADERS,
		"Премиум аккаунт", "кол-во дней\tцена\n\
		1 дн.\t49р.\n\
		3 дн.\t129р. "COLOR_GRAY"(экономия 12 процентов)\n\
		7 дн.\t279р. "COLOR_GRAY"(экономия 20 процентов)\n\
		14 дн.\t489р. "COLOR_ORANGE"(экономия 30 процентов)\n\
		30 дн.\t799р. "COLOR_RED"(экономия 55 процентов)", "Купить", "Закрыть"
	);	
}

DialogResponse:DIALOG_LIST_PREMIUM(playerid, response, listitem, inputtext[]) {
	if(!response) return 1;

	new days = GetPlayerNumberDaysPremium(playerid);

	switch(listitem) {
		case 0: {
			if(PlayerInfo[playerid][pDonate] >= 49) {
			if(days > 0) {
				return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Нельзя приобрести премиум если он уже активен, дождитесь окончания подписки!");
			}		
			PlayerInfo[playerid][pDonate] -= 49;
			SetPlayerInt(playerid, "Donate", PlayerInfo[playerid][pDonate]);	
			GivePlayerPremiumAccount(playerid, 1, 1);	
			} else {
				Dialog_Show(playerid, Dialog:DIALOG_LIST_PREMIUM);
				return SendClientMessage(playerid, -1, "Цена услуги составляет 49 рублей. Для продолжения пополните счет: ChanceRp.Ru/donate");
			}
		}
		case 1: {
			if(PlayerInfo[playerid][pDonate] >= 129) {
			if(days > 0) {
				return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Нельзя приобрести премиум если он уже активен, дождитесь окончания подписки!");
			}				
			PlayerInfo[playerid][pDonate] -= 129;
			SetPlayerInt(playerid, "Donate", PlayerInfo[playerid][pDonate]);	
			GivePlayerPremiumAccount(playerid, 3, 1);	
			} else {
				Dialog_Show(playerid, Dialog:DIALOG_LIST_PREMIUM);
				return SendClientMessage(playerid, -1, "Цена услуги составляет 129 рублей. Для продолжения пополните счет: ChanceRp.Ru/donate");
				
			}
		}
		case 2: {
			if(PlayerInfo[playerid][pDonate] >= 279) {
			if(days > 0) {
				return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Нельзя приобрести премиум если он уже активен, дождитесь окончания подписки!");
			}				
			PlayerInfo[playerid][pDonate] -= 279;
			SetPlayerInt(playerid, "Donate", PlayerInfo[playerid][pDonate]);	
			GivePlayerPremiumAccount(playerid, 7, 1);	
			} else {
				Dialog_Show(playerid, Dialog:DIALOG_LIST_PREMIUM);
				return SendClientMessage(playerid, -1, "Цена услуги составляет 279 рублей. Для продолжения пополните счет: ChanceRp.Ru/donate");
			}
		}		
		case 3: {
			if(PlayerInfo[playerid][pDonate] >= 489) {
			if(days > 0) {
				return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Нельзя приобрести премиум если он уже активен, дождитесь окончания подписки!");
			}				
			PlayerInfo[playerid][pDonate] -= 489;
			SetPlayerInt(playerid, "Donate", PlayerInfo[playerid][pDonate]);	
			GivePlayerPremiumAccount(playerid, 14, 1);	
			} else {
				Dialog_Show(playerid, Dialog:DIALOG_LIST_PREMIUM);
				return SendClientMessage(playerid, -1, "Цена услуги составляет 489 рублей. Для продолжения пополните счет: ChanceRp.Ru/donate");
			}
		}
		case 4: {
			if(PlayerInfo[playerid][pDonate] >= 799) {
			if(days > 0) {
				return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Нельзя приобрести премиум если он уже активен, дождитесь окончания подписки!");
			}				
			PlayerInfo[playerid][pDonate] -= 799;
			SetPlayerInt(playerid, "Donate", PlayerInfo[playerid][pDonate]);	
			GivePlayerPremiumAccount(playerid, 30, 1);	
			} else {
				Dialog_Show(playerid, Dialog:DIALOG_LIST_PREMIUM);
				return SendClientMessage(playerid, -1, "Цена услуги составляет 799 рублей. Для продолжения пополните счет: ChanceRp.Ru/donate");
			}
		}					
	}
	return 1;
}

CMD:premium(playerid) {
	Dialog_Show(playerid, Dialog:DIALOG_GET_PREMIUM);
	return 1;
}