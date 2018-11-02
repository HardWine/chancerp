#if defined api_casino_log_included
	#endinput
#endif

#define api_casino_log_included

#define TABLE_CASINO_LOG 					"casino_log"

forward AddRowLogCasino(const player1, const player2, const sum);

/**
 * [AddRowLogCasino добавляет запись в таблицу логирования игры в казино]
 * @param {int} const player1 [ID Аккаунта игрока #1]
 * @param {int} const player2 [ID Аккаунта игрока #2]
 * @param {int} const sum     [Ставка]
 */
public AddRowLogCasino(const player1, const player2, const sum) {
	static string[71 + (11 * 2) + 9 + 1];

	mysql_format(database, 
		string, sizeof(string), 
		"INSERT INTO "TABLE_CASINO_LOG" (`Player1`, `Player2`, `Sum`) VALUES (%i, %i, %i)", 
			player1,
			player2,
			sum
	);
	return mysql_pquery(database, string);
}