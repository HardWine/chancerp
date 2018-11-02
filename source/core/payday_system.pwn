#if defined payday_system_included
	#endinput
#endif

#define payday_system_included

// Standart
#include <YSI\y_hooks>
#include <YSI\y_timers>

hook OnGameModeInit() {
	new 
		payday_minute;

	gettime(_, payday_minute, _);

	new 
		time_to_payday = (60 - payday_minute) * 60;

	defer PayDay[time_to_payday * 1_000]();
}

timer PayDay[(60 * 60) * 1_000]() {
	printf("New_PayDay");

	SetWeather(RandomEx(0,7));

	defer GetPayDay();

    startcapture = 0;
	GameTextForAll("~y~PayDay", 5000, 0);
	format(small_string, sizeof(small_string), ""COLOR_ORANGE"Текущее время: {FFFFFF}%d:00", hour);
	SendClientMessageToAll(-1, ""COLOR_ORANGE"Внимание. Теперь зарплата будет приходить только когда вы отыграете целый час");
    SendClientMessageToAll(-1, small_string);
   	SetWorldTime(hour);
    switch(GetVehiclePoolSize()) {
	    case 0..69: orders = RandomEx(5,9);
	    case 70..99: orders = RandomEx(8,15);
	    default: orders = RandomEx(10,25);
	}

	defer PayDay();
	return 1;
}

timer GetPayDay[30 * 1_000]() {
	paydaybonus[1] = 0;
    paydaybonus[2] = 0;
    paydaybonus[3] = 0;
    paydaybonus[4] = 0;
    paydaybonus[5] = 0;
    paydaybonus[6] = 0;
	/*foreach(new i: Player)
	{
	    PlayerInfo[i][pOnline] = 0;
	}*/
	mysql_pquery(database, "UPDATE players SET Online = 0");
	if(invite_type == 0) {
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} В Мэрии штата началось собеседование в Армию");
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} Требования: Законопослушность не ниже -50");
		return invite_type = 1;
	} if(invite_type == 1) {
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} В Мэрии штата началось собеседование в LSPD");
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} Требования: Законопослушность не ниже 100");
		return invite_type = 2;
	} if(invite_type == 2) {
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} В Мэрии штата началось собеседование в FBI");
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} Требования: Законопослушность не ниже 250");
		return invite_type = 3;
	} if(invite_type == 3) {
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} В Мэрии штата началось собеседование в Мэрию");
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} Требования: Законопослушность не ниже 500");
		return invite_type = 0;
	}
	return 1;
}