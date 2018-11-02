#if defined newexp_system_included
	#endinput
#endif

#define newexp_system_included

#include <YSI-Include\YSI\YSI\y_hooks>

enum E_ADD_EXP_TYPE {
	// Прибавление
	E_SELL_CAR_GOVERMENT = 1, // Продажа транспорта (гос-ву)
	E_JOB_DRUGS, // Работа наркодилер
	E_JOB_PORTER, // Работа грузчика
	E_JOB_ARMY_PLANT, // Работа на военном заводе
	E_LEAVE_RETURN_CASINO_CASH, // Возврат ставки в казино
	E_WIN_CASINO, // Выигрыш в казино
	E_CASION_CROUPIER, // Чаевые (крупье в казино)
	E_RETURN_CASINO_CASH, // Чаевые (крупье в казино)
	E_ARREST, // Поимка преступника
	E_WIN_MPPRIZE, // Поимка преступника
	E_WIN_AWARD, // Активность с свободной группе
	E_WIN_CARPRIZE, // Победа в мероприятии (/carprize)
	E_JOB_FARM, // Работа на ферме
	E_JOB_THEFT_AUTO, // Работа автоугонщиком
	E_GOOD_DEAL, // Успешная сделка (мафия)
	E_FARM_PREMIUM, // Премия на ферме
	E_JOB_COMBAINE, // Работа на комбаине
	E_JOB_DRIVER_TRASH, // Работа на мусоровозе
	E_JOB_CAR_ARMY, // Доставка военного груза
	E_JOB_PILOT, // Работа пилота
	E_JOB_BUS_DRIVER, // Работа автобусника
	E_ADD_CASH_BANK, // Снятие денег с банкомата
	E_ROBBERY_BUSINESS, // Ограбление бизнеса
	E_SELL_HOUSE, // Продажа дома
	E_WIN_AZINO, // Выигрыш в игровых автоматы
	E_JOB_LAWYER, // Работа адвоката
	E_ARREST_ARMY, // Поимка преступника (армия)
	E_ARREST_COP, // Поимка преступника (полиция)
	// Убавление
	E_BUY_CAR, // Покупка транспорта
	E_BUY_DRUGS_JOB, // Покупка наркотиков (работа курьера)
	E_PLAYING_AZINO, // Игра в казино
	E_INVITE_LSPD, // Вступление в LSPD
	E_INVITE_ARMY, // Вступление в армию
	E_INVITE_AZTECAS, // Вступление в Aztecas
	E_INVITE_RIFA, // Вступление в Rifa
	E_INVITE_VAGOS, // Вступление в Vagos
	E_INVITE_BALLAS, // Вступление в Ballas
	E_INVITE_GROVE, // Вступление в Grove
	E_BUY_DRUGS, // Покупка наркотиков
	E_INVITE_DNBOYS, // Вступление в Da Nang Boys
	E_INVITE_TRIADS, // Вступление в Triads
	E_INVITE_PM, // Вступление в Русскую Мафию
	E_PLAYING_AZINO_MACHINE, // Ставка в игровых автоматах
	E_INVITE_FBI, // Вступление в FBI
	E_BUY_SLOTHES, // Покупка одежды
	E_RENTTIME_HOUSE, // Оплата жилья (Сутки)
	E_LEASE_CAR, // Сдача на права (Водительские)
	E_LEASE_FLY, // Сдача на права (Пилот)
	E_BUY_PAGER, // Покупка пейджера
	E_BUY_PHONE, // Покупка телефона
	E_BUY_MASK, // Покупка маски
	E_PUT_BANK, // Перевод на свой счет в банке
	E_BALANCE_PHONE, // Пополнение баланса телефона
	E_BUY_NEW_PASS, // Приобретение нового паспорта
	E_BUY_LAWYER, // Услуги адвоката
	E_BUY_DRINK, // Покупка спиртного
	E_BUY_HOUSE // Покупка дома
}

static 
	Player.EXP[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
	Player.EXP[playerid] = 0;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	Player.EXP[playerid] = 0;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerUpdate(playerid) {
	if(GetPlayerMoney(playerid) != Player.EXP[playerid]) {
		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, Player.EXP[playerid]);
	}
}

forward bool:Player.AddEXP(const accID, const value, const E_ADD_EXP_TYPE:type, const playerid);
public bool:Player.AddEXP(const accID, const value, const E_ADD_EXP_TYPE:type, const playerid) {
	mysql_format(database, small_string, sizeof(small_string), "CALL `Player.AddEXP` (%i , %i , %i);", accID, value, _:type);
	mysql_pquery(database, small_string);

	if(playerid != INVALID_PLAYER_ID) {
		if(PlayerLogged{playerid} == false || !IsPlayerConnected(playerid)) {
			return false;
		}

		Player.EXP[playerid] = Player.EXP[playerid] + value;
		return true;
	} else {
		return true;
	}
}

forward bool:Player.DownEXP(const accID, const value, const E_ADD_EXP_TYPE:type, const playerid);
public bool:Player.DownEXP(const accID, const value, const E_ADD_EXP_TYPE:type, const playerid) {
	mysql_format(database, small_string, sizeof(small_string), "CALL `Player.DownEXP` (%i , %i , %i);", accID, value, _:type);
	mysql_pquery(database, small_string);

	if(playerid != INVALID_PLAYER_ID) {
		if(PlayerLogged{playerid} == false || !IsPlayerConnected(playerid)) {
			return false;
		}
		Player.EXP[playerid] = Player.EXP[playerid] - value;
		return true;
	} else {
		return true;
	}
}

forward GetPlayerEXP(const playerid);
public GetPlayerEXP(const playerid) {
	return Player.EXP[playerid];
}

forward SetPlayerEXP(const playerid, const value);
public SetPlayerEXP(const playerid, const value) {
	return Player.EXP[playerid] = value;
}

/**
 * [CheckCash проверяет и снимает сумму (cash) с аккаунта.]
 * Возвращает:
 *  	false - если у игрока нет столько денег
 *  	true - если у игрока есть нужная сумма, и деньги сняты
 * @param {int} const playerid [ID Игрока]
 * @param {int} const cash     [Сумма]
 */
forward bool:CheckCash(const playerid, const cash);
public bool:CheckCash(const playerid, const cash) {
	new 
		player_score = GetPlayerEXP(playerid);

	if(player_score < cash) {
		new it = cash - player_score;
		
		format(small_string, sizeof(small_string),
			"~y~YOU NEED %d ~w~EXP", 
				it
		);
		GameTextForPlayer(playerid, small_string, 3000, 5);

		format(small_string, sizeof(small_string), 
			""COLOR_RED"Вам не хватает "COLOR_WHITE"%i EXP", 
				it
		);
		SendClientMessage(playerid, -1, small_string);
		return false;
	}
	return true;
}