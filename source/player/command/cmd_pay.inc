#if defined cmd_pay_system
	#endinput
#endif
#define cmd_pay_system 

#include <YSI_Coding\y_hooks>

// Переменная отвечает за количесто денег 
// которые игрок передал другим игрокам
new PlayerAmountPassedMoney[MAX_PLAYERS] = {0, ...};

stock SetPlayerAmountPassedMoney(const playerid, const pay, bool:issave = true)
{
	// Игрок не авторизован 
	if(GetPlayerLoging(playerid) == false)
	{
		new name[MAX_PLAYER_NAME + 1];
		GetPlayerName(playerid, name, MAX_PLAYER_NAME);
		printf("Попытка установить лимит передачи денег неавторизованному игроку (playerid = %i; name = %s)", playerid, name);
		return false;
	}
	// если значение передачи денег меньше нуля
	if(pay < 0)
	{
		printf("Попытка установить лимит передачи денег < 0 (playerid = %i; name = %s)", playerid, PlayerInfo[playerid][pName]);
		return false;
	}
	// если превышен диапозон sellmax
	if(pay > cellmax)
	{
		printf("Попытка установить лимит передачи денег > %i (playerid = %i; name = %s)", cellmax, playerid, PlayerInfo[playerid][pName]);
		return false;
	}

	PlayerAmountPassedMoney[playerid] = pay;

	if(issave == true)
	{
		static const fmt_str_0[] = "UPDATE players SET `PassedMoney` = %i WHERE `ID` = %i LIMIT 1";

		goto skip_array_init;
		new string_0[sizeof(fmt_str_0) + 1
			+ (- 2 + 8)
			+ (- 2 + 8)
		];
		skip_array_init:

		mysql_format(database,
			string_0, sizeof(string_0),
			fmt_str_0,
				PlayerAmountPassedMoney[playerid],
				PlayerInfo[playerid][pID]
		);
		new result = mysql_pquery(database, string_0);
		if(!result)
		{
			printf("SetPlayerAmountPassedMoney: ошибка в запросе %s", string_0);
		}
	}
	return true;
}

stock GetPlayerAmountPassedMoney(const playerid)
{
	if(GetPlayerLoging(playerid) == false)
	{
		return 0;
	}

	new amount = PlayerAmountPassedMoney[playerid];
	if(amount < 0)
	{
		printf("Попытка получить лимит передачи денег < 0 (playerid = %i; name = %s)", playerid, PlayerInfo[playerid][pName]);
		amount = 0;
	}
	if(amount > cellmax)
	{
		printf("Попытка получить лимит передачи денег > %i (playerid = %i; name = %s)", cellmax, playerid, PlayerInfo[playerid][pName]);
		amount = cellmax;
	}

	return amount;
}

hook OnPlayerConnect(playerid) {
	PlayerAmountPassedMoney[playerid] = 0;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason 

	PlayerAmountPassedMoney[playerid] = 0;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnServerRestart()
{
	mysql_pquery(database, "UPDATE players SET PassedMoney = 0");
}

CMD:pay(playerid, params[]) {
	if(PlayerInfo[playerid][pHours] < 12) {
		SendClientMessage(playerid, -1, ""COLOR_RED"Для передачи денег нужно отыграть 12 часов!");
		return 0;
	}


	if(GetPVarInt(playerid, "pay_warning") != 1) {
		SetPVarInt(playerid, "pay_warning", 1);
		ShowPlayerDialog(playerid,
			DIALOG_INFO,
			DIALOG_STYLE_MSGBOX,
			""COLOR_BLUE"Предупреждение!",
			""COLOR_RED"Никогда не передавайте деньги игроку который предложит вам сделку с использованием команды /pay\nВ таком случае, вы будете обмануты, нарушите правила и утратите ваши средства навсегда!\nМы не сможем вам помочь, поэтому мы предупреждаем о существующих положениях:\n\n"COLOR_WHITE"1.5 Запрещены любые попытки (в том числе ролевые) обмануть игроков на собственность их аккаунта\n1.6 Запрещена продажа/обмен/дарение собственности на аккаунте (искл.: /changecar и /changehouse)\n1.7 Запрещена доплата любыми способами в обход системы доплаты /changecar и /changehouse\n\n"COLOR_GREEN"Для сделок с другими игроками разрешено:\n{FFFFFF}1. Обмен и продажа дома, используйте: /changehouse [id игрока] [доплата в EXP]\n2. Обмен и продажа авто, используйте: /changecar [доплата в EXP]",
			"Закрыть", ""
		);
		return 0;
	}

	new targetid;
	new sum;

	if(sscanf(params, "ri", targetid, sum)) 
	{
		return SendClientMessage(playerid, -1, "Используйте: /pay [ID игрока] [Сумма]");
	} 
	if(GetPlayerLoging(targetid) == false || targetid == INVALID_PLAYER_ID) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок не найден");
	}
	if(sum <= 0 || sum >= cellmax) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Указанна неверная сумма");
	}
	// if(playerid == targetid) {
	// 	return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы указали свой ID");
	// } 
	if(GetDistanceBetweenPlayerz(playerid, targetid, 3.00) == 0) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Игрок слишком далеко");
	}

	new amount_passed_money = GetPlayerAmountPassedMoney(playerid);
	new all_limit = (IsPlayerPremiumAccount(playerid) == true) ? (15000) : (5000);

	if(amount_passed_money + sum > all_limit) {
		format(small_string, sizeof(small_string), ""COLOR_RED"Сегодня осталось передать не более{FFFFFF} %i EXP", all_limit - amount_passed_money);
		return SendClientMessage(playerid, -1, small_string);
	} 
	if(CheckCash(playerid, sum) == false) return 1;

	format(small_string, sizeof(small_string), "%s достал(а) кошелек и передал %i EXP игроку %s", PlayerInfo[playerid][pName], sum, PlayerInfo[targetid][pName]);
	ShowAction(playerid, small_string);
	
	AddPlayerEXP(targetid, sum, "Передача денег от игрока %s", PlayerInfo[playerid][pName]);
	RemovePlayerEXP(playerid, sum, "Передача денег игроку %s", PlayerInfo[targetid][pName]);

	SetPlayerAmountPassedMoney(playerid, amount_passed_money + sum);
	return 1;
}