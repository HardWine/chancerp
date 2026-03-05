#if defined fish_system_included
	#endinput
#endif

#define fish_system_included

enum FISH_STRUCTURE {
	ID,
	Name[36],
	Habit,
}

new TotalFish[MAX_PLAYERS];
new Float:TotalFishWeight[MAX_PLAYERS];

stock LoadPlayerFish(playerid) {

		new query_string[144];

		format(query_string, sizeof(query_string), "SELECT * FROM fish WHERE PlayerID =", GetPlayerAccountID(playerid));

		mysql_query(database, query_string, true);

		new 
			rows = cache_get_row_count();


		for(new i = 0; i < rows; i++) {
			PlayerInfo[playerid][pRadarDetect1] = 2;
		}
}


new FishBase[][FISH_STRUCTURE] {

	{1, "Радужная Форель", 0},
	{2, "Карп", 0},
	{3, "Голец", 0},
	{4, "Тилапия", 0},
	{5, "Осетр", 0},
	{6, "Форель ручьевая", 0},
	{7, "Сом", 0},
	{8, "Амур", 0},
	{9, "Щука", 0},
	{10, "Линь", 0},
	{11, "Толстолобик", 0},
	{12, "Карась", 0},
	{13, "Кумжа", 0},
	{14, "Судак", 0},
	{15, "Язь", 0},
	{16, "Окунь", 0},
	{17, "Угорь", 0},
	{18, "Плотва", 0},
	{19, "Лещ", 0},
	{20, "Лосось", 0},	
	{21, "Рак", 0},	
	{22, "Гловаль", 0}

};