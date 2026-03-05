#if defined SIMcar_system_included
	#endinput
#endif

#define SIMcar_system_included

#define SIM_CARD_PRICE 						500 // Цена симкарты
#define INVALID_SIM_CARD_NUMBER 			(-1) // Цена симкарты
#define MAX_LENGTH_SMS_TEXT 				(48) // Цена симкарты

#include <YSI_Coding\y_hooks>

new 
	PlayerSIMCardNumber[MAX_PLAYERS] = {INVALID_SIM_CARD_NUMBER, ...};

hook OnPlayerConnect(playerid) {
	PlayerSIMCardNumber[playerid] = INVALID_SIM_CARD_NUMBER;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason 

	PlayerSIMCardNumber[playerid] = INVALID_SIM_CARD_NUMBER;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerAuthorization(playerid) {
	mysql_format(database, small_string, sizeof(small_string), 
		"SELECT COALESCE(SIMCard, %i) AS SIMCard FROM players WHERE ID = %i LIMIT 1;", 
		INVALID_SIM_CARD_NUMBER, 
		PlayerInfo[playerid][pID]
	);
	mysql_pquery(database, small_string, "@_LoadPlayerSIMCardNumber", "i", playerid);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

@_LoadPlayerSIMCardNumber(const playerid);
@_LoadPlayerSIMCardNumber(const playerid) {
	new 
		rows = cache_get_row_count();

	if(!rows) {
		PlayerSIMCardNumber[playerid] = INVALID_SIM_CARD_NUMBER;
	} else {
		PlayerSIMCardNumber[playerid] = cache_get_field_content_int(0, "SIMCard");

		if(PlayerSIMCardNumber[playerid] < 100000 && PlayerSIMCardNumber[playerid] != INVALID_SIM_CARD_NUMBER) {
			PlayerSIMCardNumber[playerid] = INVALID_SIM_CARD_NUMBER;

			SendClientMessage(playerid, -1, ""COLOR_GREEN"Ваша SIM-карта содержит неверный формат и больше не обслуживается.");
			AddPlayerEXP(playerid, SIM_CARD_PRICE, "Возврат денег за неверный формат SIMCard");

			mysql_format(database, 
				small_string, sizeof(small_string),
				"UPDATE `players` SET SIMCard = NULL WHERE ID = %i LIMIT 1", 
					PlayerInfo[playerid][pID]
			);
			mysql_pquery(database, small_string);

		}
	}
	return true;
}

DialogCreate:DIALOG_BUY_SIM_CARD(playerid) {
	format(big_string, sizeof(big_string), 
		""COLOR_GREEN"SIM-карта"COLOR_WHITE" – микроскопический чип, который дает\n\
		возможность общаться в мобильной сети с другими игроками.\n\n\
		Вы можете приобрести любой свободный номер в формате\n\
		XXXXXX. Пример: "COLOR_GREEN"777777, 666666, 123987, 456258, 222227"COLOR_WHITE"\n\
		В дальнейшем, вы также сможете изменить номер мобильного\n\
		телефона\n\
		Цена услуги за покупки или смену SIM-карты составляет "COLOR_GREEN"%i EXP"COLOR_WHITE"\n\n\
		"COLOR_ORANGE"Введите желаемый номер для продолжения:", 
			SIM_CARD_PRICE
	);

	return Dialog_Open(playerid, Dialog:DIALOG_BUY_SIM_CARD, DIALOG_STYLE_INPUT,
		""COLOR_BLUE"Покупка SIM-карты",
		big_string,
		"Купить", "Закрыть"
	);
}

DialogResponse:DIALOG_BUY_SIM_CARD(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return false;
	} else {
		new 
			input_number = strval(inputtext);

		printf("inputtext %i %i %i ", inputtext[0], strlen(inputtext), input_number);
		if(strlen(inputtext) != 6 || inputtext[0] == 0) {
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Указан неверный формат SIM-карты");
			Dialog_Show(playerid, Dialog:DIALOG_BUY_SIM_CARD);
			return false;
		}
		if(input_number < 100000 || input_number > 999999) {
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Указан неверный формат SIM-карты");
			Dialog_Show(playerid, Dialog:DIALOG_BUY_SIM_CARD);
			return false;
		}
		if(CheckCash(playerid, COST_SIM) == false) {
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас недостаточно денег для покупки SIM-карты");
			Dialog_Show(playerid, Dialog:DIALOG_BUY_SIM_CARD);
			return false;
		}

		mysql_format(database, 
			small_string, sizeof(small_string), 
			"SELECT ID FROM `players` WHERE SIMCard = %i LIMIT 1;", 
				input_number
		);
		mysql_pquery(database, small_string, "@_CheckFreeSIMCardNumber", "ii", playerid, input_number);
		return true;
	}
}

@_CheckFreeSIMCardNumber(const playerid, const number);
@_CheckFreeSIMCardNumber(const playerid, const number) {
	new 
		rows = cache_get_row_count();

	if(rows) {
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Введенный номер SIM-карты уже принадлежит другому игроку");
		Dialog_Show(playerid, Dialog:DIALOG_BUY_SIM_CARD);
		return false;
	} else {
		RemovePlayerEXP(playerid, COST_SIM, "Покупка SIMCard с номером %i", number);

		format(small_string, sizeof(small_string), ""COLOR_WHITE"Вы купили SIM-карту с номером "COLOR_GREEN"%i", number);
		SendClientMessage(playerid, -1, small_string);

		PlayerSIMCardNumber[playerid] = number;

		mysql_format(database, 
			small_string, sizeof(small_string),
			"UPDATE `players` SET SIMCard = %i WHERE ID = %i LIMIT 1", 
				number, 
				PlayerInfo[playerid][pID]
		);
		mysql_pquery(database, small_string);

		mysql_format(database, 
			small_string, sizeof(small_string),
			"INSERT INTO `log_buy_sim`(`PlayerID`, `Number`) VALUES (%i, %i)", 
				PlayerInfo[playerid][pID],
				number
		);
		mysql_pquery(database, small_string);
		return true;
	}
}

CMD:sms(playerid, params[])
{
	new 
		targetid = INVALID_PLAYER_ID,
		target_number;

	new 
		target_message[MAX_LENGTH_SMS_TEXT + 1];

	if(PlayerInfo[playerid][pDevice] == 0) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Вам нужен пейджер или телефон. Купите его в магазине");
	}
	if(PlayerSIMCardNumber[playerid] == INVALID_SIM_CARD_NUMBER) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"У вас нет SIM-карты");
	}

	format(small_string, sizeof(small_string), "is[%i]", MAX_LENGTH_SMS_TEXT);

	if(sscanf(params, small_string, target_number, target_message)) {
		return SendClientMessage(playerid, -1, "Используйте: /sms [Номер игрока] [Текст]");
	}

	foreach(new i: Player) {
		if(PlayerSIMCardNumber[i] == target_number) {
			targetid = i;
			break; 
		}
	}

	if(targetid == INVALID_PLAYER_ID) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Указан неверный номер, или игрок с таким номером не в сети");
	}
	if(PlayerInfo[targetid][pDevice] == 0) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"У указанного игрока нет ни одного девайса");
	}
	if(GetPVarInt(targetid, "togphone") == 1) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Абонент временно недоступен");
	}
	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У вас бан чата!");
	if(PlayerInfo[playerid][pBalance] < 5) return SendClientMessage(playerid, -1, ""COLOR_RED"Недостаточно средств. Пополните счет");
	if(PlayerInfo[playerid][pDevice] == 1) {
		format(small_string, sizeof(small_string), "%s достал(а) пейджер", PlayerInfo[playerid][pName]);
		ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
	}
	if(PlayerInfo[playerid][pDevice] == 2) {
		format(small_string, sizeof(small_string), "%s достал(а) телефон", PlayerInfo[playerid][pName]);
		ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
	}
	PlayerInfo[playerid][pBalance] -= 5;
	SetPlayerInt(playerid, "Balance", PlayerInfo[playerid][pBalance]);
	PlayerPlaySound(playerid, 1053, 0, 0, 0);

	format(small_string, sizeof(small_string), 
		""COLOR_WHITE"SMS: "COLOR_GREEN"%s."COLOR_WHITE" Получатель: "COLOR_GREEN"%s(%d)", 
			target_message, 
			PlayerInfo[targetid][pName], 
			targetid
	);
	SendClientMessage(playerid, -1, small_string);

	format(small_string, sizeof(small_string), 
		""COLOR_WHITE"SMS: "COLOR_GREEN"%s."COLOR_WHITE" Отправитель: "COLOR_GREEN"%s(%d)", 
		target_message,
		PlayerInfo[playerid][pName], 
		playerid
	);
	SendClientMessage(targetid, -1, small_string);

	foreach(new i: Admin) {
		if(GetPVarInt(i, "ears") == 1) {
			format(small_string, sizeof(small_string), 
				"[SPY~POWER] "COLOR_WHITE"%s(%d): "COLOR_GREEN"%s."COLOR_WHITE" => %s(%d)", 
				PlayerInfo[playerid][pName], playerid, 
				target_message, 
				PlayerInfo[targetid][pName], targetid
			);
			SendClientMessage(i, -1, small_string);
		}
	}

	mysql_format(database, big_string, sizeof(big_string), "INSERT INTO `log_sms`(`PlayerID`, `TargetID`, `Text`) VALUES (%i, %i, '%e')", PlayerInfo[playerid][pID], PlayerInfo[targetid][pID], target_message);
	mysql_pquery(database, big_string);	

	PlayerPlaySound(playerid, 1052,0,0,0);
	PlayerPlaySound(targetid, 20804,0,0,0);
	return 1;
}