#if defined exp_system_included
	#endinput
#endif

#define exp_system_included

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
		player_score = PlayerInfo[playerid][pScore];

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