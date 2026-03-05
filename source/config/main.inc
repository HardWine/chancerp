#if defined _main_cfg_included
	#endinput
#endif

#define _main_cfg_included
#define SERVER_RCON_PASSWORD	 "HX4a7faw3vas541ASFn5qqsfaq"

#define SERVER_HOSTNAME			 "Обновление клиента (Подробнее: vk.com/ChanceRp)"
#define SERVER_HOSTNAME_A1		 "Chance RP | Рестарт через 5 минут"
#define SERVER_HOSTNAME_A2		 "Chance RP | Производится рестарт..."
#define TEST_SERVER_HOSTNAME	 "Chance RP | Тестовый сервер"

#define GAMEMODE_TEXT			 "2.1.0 ver."

#define TEST_SERVER_PASSWORD	 "201820192020"

#define MAX_LENGTH_IP 			 (19 + 1)

#define GLOBAL_SERVER_IP 		 "176.32.36.4"

new bool: test_server = false,
	FIX_AUTH_TIME = 180000,
	server_ip[MAX_LENGTH_IP + 1];

stock GameModeConfig() {


	// EnableAntiCheat(40, false);
	// EnableAntiCheat(2, false);

	SendRconCommand("ackslimit 5000");
	SendRconCommand("sleep 5");
	SendRconCommand("password ServerLoadingWait");
	SendRconCommand("rcon_password "SERVER_RCON_PASSWORD"");
	SendRconCommand("hostname "SERVER_HOSTNAME"");	

	AddPlayerClass(0, 1176.9836,-1324.4713,14.0483, 270, 0, 0, 0, 0, 0, 0);
	
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_STREAMED);
	SetNameTagDrawDistance(25.0);
	LimitPlayerMarkerRadius(35.0);	
	EnableStuntBonusForAll(0);
	SetGameModeText(""GAMEMODE_TEXT"");

	DisableInteriorEnterExits();
	ManualVehicleEngineAndLights();

	GetConsoleVarAsString("bind", server_ip, sizeof(server_ip));

}

stock GamemodeLoaded() {
	FIX_AUTH_TIME = 60000;

	SetTimer("int_op", 250, false);
	SetTimer("InfoMessage", (60 * 1000) * 10, true);
	SetTimer("UpdateTimers", 1000, false);
	SetTimer("AutoAttack", 60000, false);
	SetTimer("SendADList",15*1000,0);	

	if(strcmp(server_ip, GLOBAL_SERVER_IP, false) == 0) {
		test_server = false;
		SendRconCommand("password 0");
	} else {
		test_server = true;
		SendRconCommand("password "TEST_SERVER_PASSWORD"");
	}

	gettime(hour);
	SetWorldTime(hour);

	weather = RandomEx(0,8);
	newweather = RandomEx(0,20);
	if(weather == 8) {
		weather = RandomEx(10,12);
	}
}