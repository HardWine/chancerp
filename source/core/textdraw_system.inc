#if defined _textdraw_system_included
	#endinput
#endif
#define _textdraw_system_included

#define ASPECT_RATIO_4_3 (Float:0x3FAAAAAB)
#define ASPECT_RATIO_16_9 (Float:0x3FE36364)

#define TD_COLOR_DEFAULT 0xff353cFF
#define TD_COLOR_GREEN 0x67da41FF
#define TD_COLOR_BLACK 0x4eb9e6FF
#define TD_COLOR_ORANGE 0xFFAF00FF
#define TD_COLOR_NULL 0x333333FF

new PlayerText: tuning_ui[MAX_PLAYERS][3];
new PlayerText: server_logo[MAX_PLAYERS][4];
new PlayerText: speedo_TD[MAX_PLAYERS][4];
new PlayerText: spec_PTD[MAX_PLAYERS][5];
new PlayerText: car_params_td[MAX_PLAYERS][6];

stock OnPlayerConnect_textdraw(playerid) {
	for(new i = 0; i < sizeof(server_logo[]); i++) {
		server_logo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}
	for(new i = 0; i < sizeof(speedo_TD[]); i++) {
		speedo_TD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}
	for(new i = 0; i < sizeof(tuning_ui[]); i++) {
		tuning_ui[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}	
	for(new i = 0; i < sizeof(spec_PTD[]); i++) {
		spec_PTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}	
	for(new i = 0; i < sizeof(car_params_td[]); i++) {
		car_params_td[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}		
	return 1;
}

stock OnPlayerDisconnect_textdraw(playerid) {

	hide_logo(playerid);
	hide_speedo(playerid);
	hide_spec(playerid);
	hide_tuning(playerid);

	destroy_logo_textdraws(playerid);
	destroy_speedo_textdraws(playerid);
	destroy_spec_textdraws(playerid);
	destroy_tuning_textdraws(playerid);

	for(new i = 0; i < sizeof(server_logo[]); i++) {
		server_logo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}
	for(new i = 0; i < sizeof(speedo_TD[]); i++) {
		speedo_TD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}
	for(new i = 0; i < sizeof(tuning_ui[]); i++) {
		tuning_ui[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}	
	return 1;
}

forward TD_OnPlayerAuthorization(playerid);
public TD_OnPlayerAuthorization(playerid) {

	if(GetPlayerAdminLevel(playerid) > 0) { // ТД слежки

	spec_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 556.4996, 114.7108, "_"); // пусто
	PlayerTextDrawLetterSize(playerid, spec_PTD[playerid][0], 0.0000, 20.0000);
	PlayerTextDrawTextSize(playerid, spec_PTD[playerid][0], 0.0000, 100.0000);
	PlayerTextDrawAlignment(playerid, spec_PTD[playerid][0], 2);
	PlayerTextDrawColor(playerid, spec_PTD[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, spec_PTD[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][0], -5308288);
	PlayerTextDrawBackgroundColor(playerid, spec_PTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, spec_PTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, spec_PTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, spec_PTD[playerid][0], 0);

	spec_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 556.6996, 133.1442, "~n~~n~Chance~n~RolePlay~n~Forever"); // пусто
	PlayerTextDrawLetterSize(playerid, spec_PTD[playerid][1], 0.2800, 1.5000);
	PlayerTextDrawAlignment(playerid, spec_PTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, spec_PTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, spec_PTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, spec_PTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, spec_PTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, spec_PTD[playerid][1], 0);

	spec_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 556.0000, 310.0000, "UPD"); // пусто
	PlayerTextDrawLetterSize(playerid, spec_PTD[playerid][2], 0.75, 3.0);
	PlayerTextDrawTextSize(playerid, spec_PTD[playerid][2], 30.0000, 80.0000);
	PlayerTextDrawAlignment(playerid, spec_PTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, spec_PTD[playerid][2], -1);
	PlayerTextDrawUseBox(playerid, spec_PTD[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][2], -5963521);
	PlayerTextDrawBackgroundColor(playerid, spec_PTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, spec_PTD[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, spec_PTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, spec_PTD[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, spec_PTD[playerid][2], true);

	spec_PTD[playerid][3] = CreatePlayerTextDraw(playerid, 556.0000, 345.0000, "STAT"); // пусто
	PlayerTextDrawLetterSize(playerid, spec_PTD[playerid][3], 0.75, 3.0);
	PlayerTextDrawTextSize(playerid, spec_PTD[playerid][3], 30.0000, 80.0000);
	PlayerTextDrawAlignment(playerid, spec_PTD[playerid][3], 2);
	PlayerTextDrawColor(playerid, spec_PTD[playerid][3], -1);
	PlayerTextDrawUseBox(playerid, spec_PTD[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][3], -5963521);
	PlayerTextDrawBackgroundColor(playerid, spec_PTD[playerid][3], 255);
	PlayerTextDrawFont(playerid, spec_PTD[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, spec_PTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, spec_PTD[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, spec_PTD[playerid][3], true);

	spec_PTD[playerid][4] = CreatePlayerTextDraw(playerid, 556.0000, 380.0000, "EXIT"); // пусто
	PlayerTextDrawLetterSize(playerid, spec_PTD[playerid][4], 0.75, 3.0);
	PlayerTextDrawTextSize(playerid, spec_PTD[playerid][4], 30.0000, 80.0000);
	PlayerTextDrawAlignment(playerid, spec_PTD[playerid][4], 2);
	PlayerTextDrawColor(playerid, spec_PTD[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, spec_PTD[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][4], -5963521);
	PlayerTextDrawBackgroundColor(playerid, spec_PTD[playerid][4], 255);
	PlayerTextDrawFont(playerid, spec_PTD[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, spec_PTD[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, spec_PTD[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, spec_PTD[playerid][4], true);
	}

	// ТД Тюнинг
	tuning_ui[playerid][0] = CreatePlayerTextDraw(playerid, 556.0000, 310.0000, "Menu"); // пусто
	PlayerTextDrawLetterSize(playerid, tuning_ui[playerid][0], 0.75, 3.0);
	PlayerTextDrawTextSize(playerid, tuning_ui[playerid][0], 30.0000, 80.0000);
	PlayerTextDrawAlignment(playerid, tuning_ui[playerid][0], 2);
	PlayerTextDrawColor(playerid, tuning_ui[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, tuning_ui[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][0], -5963521);
	PlayerTextDrawBackgroundColor(playerid, tuning_ui[playerid][0], 255);
	PlayerTextDrawFont(playerid, tuning_ui[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, tuning_ui[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, tuning_ui[playerid][0], 0);
	PlayerTextDrawSetSelectable(playerid, tuning_ui[playerid][0], true);

	tuning_ui[playerid][1] = CreatePlayerTextDraw(playerid, 556.0000, 345.0000, "View"); // пусто
	PlayerTextDrawLetterSize(playerid, tuning_ui[playerid][1], 0.75, 3.0);
	PlayerTextDrawTextSize(playerid, tuning_ui[playerid][1], 30.0000, 80.0000);
	PlayerTextDrawAlignment(playerid, tuning_ui[playerid][1], 2);
	PlayerTextDrawColor(playerid, tuning_ui[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, tuning_ui[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][1], -5963521);
	PlayerTextDrawBackgroundColor(playerid, tuning_ui[playerid][1], 255);
	PlayerTextDrawFont(playerid, tuning_ui[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, tuning_ui[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, tuning_ui[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, tuning_ui[playerid][1], true);

	tuning_ui[playerid][2] = CreatePlayerTextDraw(playerid, 556.0000, 380.0000, "Exit"); // пусто
	PlayerTextDrawLetterSize(playerid, tuning_ui[playerid][2], 0.75, 3.0);
	PlayerTextDrawTextSize(playerid, tuning_ui[playerid][2], 30.0000, 80.0000);
	PlayerTextDrawAlignment(playerid, tuning_ui[playerid][2], 2);
	PlayerTextDrawColor(playerid, tuning_ui[playerid][2], -1);
	PlayerTextDrawUseBox(playerid, tuning_ui[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][2], -5963521);
	PlayerTextDrawBackgroundColor(playerid, tuning_ui[playerid][2], 255);
	PlayerTextDrawFont(playerid, tuning_ui[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, tuning_ui[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, tuning_ui[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, tuning_ui[playerid][2], true);

	// ТД Логотип
	//if(GetPlayerCameraAspectRatio(playerid) <= 1.0 && GetPlayerCameraAspectRatio(playerid) <= 1.11) {
	if(GetPVarInt(playerid, "mobile")) {	
		
		server_logo[playerid][0] = CreatePlayerTextDraw(playerid, 45.0000, 415.0000, "CHANCE"); // пусто
		PlayerTextDrawLetterSize(playerid, server_logo[playerid][0], 0.4000, 2.2500);
		PlayerTextDrawAlignment(playerid, server_logo[playerid][0], 2);
		PlayerTextDrawColor(playerid, server_logo[playerid][0], -1);
		PlayerTextDrawBackgroundColor(playerid, server_logo[playerid][0], 255);
		PlayerTextDrawFont(playerid, server_logo[playerid][0], 1);
		PlayerTextDrawSetProportional(playerid, server_logo[playerid][0], 1);
		PlayerTextDrawSetShadow(playerid, server_logo[playerid][0], 0);

		server_logo[playerid][1] = CreatePlayerTextDraw(playerid, 81.0000, 422.0000, "usebox"); // пусто
		PlayerTextDrawLetterSize(playerid, server_logo[playerid][1], 0.0000, 1.0);
		PlayerTextDrawTextSize(playerid, server_logo[playerid][1], 0.0000, 10.0000);
		PlayerTextDrawAlignment(playerid, server_logo[playerid][1], 2);
		PlayerTextDrawColor(playerid, server_logo[playerid][1], -1);
		PlayerTextDrawUseBox(playerid, server_logo[playerid][1], 1);
		PlayerTextDrawBoxColor(playerid, server_logo[playerid][1], -1);
		PlayerTextDrawBackgroundColor(playerid, server_logo[playerid][1], 255);
		PlayerTextDrawFont(playerid, server_logo[playerid][1], 1);
		PlayerTextDrawSetProportional(playerid, server_logo[playerid][1], 1);
		PlayerTextDrawSetShadow(playerid, server_logo[playerid][1], 0);

		server_logo[playerid][2] = CreatePlayerTextDraw(playerid, 81.5000, 419.0000, "RP"); // пусто
		PlayerTextDrawLetterSize(playerid, server_logo[playerid][2], 0.2666, 1.5000);
		PlayerTextDrawAlignment(playerid, server_logo[playerid][2], 2);
		PlayerTextDrawColor(playerid, server_logo[playerid][2], -1);
		PlayerTextDrawBackgroundColor(playerid, server_logo[playerid][2], 255);
		PlayerTextDrawFont(playerid, server_logo[playerid][2], 1);
		PlayerTextDrawSetProportional(playerid, server_logo[playerid][2], 1);
		PlayerTextDrawSetShadow(playerid, server_logo[playerid][2], 0);

		server_logo[playerid][3] = CreatePlayerTextDraw(playerid, 68.0000, 410.0000, "chancerp.ru"); // пусто
		PlayerTextDrawLetterSize(playerid, server_logo[playerid][3], 0.2000, 1.0000);
		PlayerTextDrawAlignment(playerid, server_logo[playerid][3], 2);
		PlayerTextDrawColor(playerid, server_logo[playerid][3], -1);
		PlayerTextDrawBackgroundColor(playerid, server_logo[playerid][3], 255);
		PlayerTextDrawFont(playerid, server_logo[playerid][3], 1);
		PlayerTextDrawSetProportional(playerid, server_logo[playerid][3], 1);
		PlayerTextDrawSetShadow(playerid, server_logo[playerid][3], 0);

	} else {

		server_logo[playerid][0] = CreatePlayerTextDraw(playerid, 563.0000, 8.0000, "CHANCE"); // пусто
		PlayerTextDrawLetterSize(playerid, server_logo[playerid][0], 0.5000, 2);
		PlayerTextDrawAlignment(playerid, server_logo[playerid][0], 2);
		PlayerTextDrawColor(playerid, server_logo[playerid][0], -1);
		PlayerTextDrawBackgroundColor(playerid, server_logo[playerid][0], 255);
		PlayerTextDrawFont(playerid, server_logo[playerid][0], 1);
		PlayerTextDrawSetProportional(playerid, server_logo[playerid][0], 1);
		PlayerTextDrawSetShadow(playerid, server_logo[playerid][0], 0);

		server_logo[playerid][1] = CreatePlayerTextDraw(playerid, 600.0000, 14.0000, "usebox"); // пусто
		PlayerTextDrawLetterSize(playerid, server_logo[playerid][1], 0.0000, 0.8);
		PlayerTextDrawTextSize(playerid, server_logo[playerid][1], 0.0000, 8.0000);
		PlayerTextDrawAlignment(playerid, server_logo[playerid][1], 2);
		PlayerTextDrawColor(playerid, server_logo[playerid][1], -1);
		PlayerTextDrawUseBox(playerid, server_logo[playerid][1], 1);
		PlayerTextDrawBoxColor(playerid, server_logo[playerid][1], -1);
		PlayerTextDrawBackgroundColor(playerid, server_logo[playerid][1], 255);
		PlayerTextDrawFont(playerid, server_logo[playerid][1], 1);
		PlayerTextDrawSetProportional(playerid, server_logo[playerid][1], 1);
		PlayerTextDrawSetShadow(playerid, server_logo[playerid][1], 0);

		server_logo[playerid][2] = CreatePlayerTextDraw(playerid, 600.0000, 11.0000, "RP"); // пусто
		PlayerTextDrawLetterSize(playerid, server_logo[playerid][2], 0.2500, 1.3500);
		PlayerTextDrawAlignment(playerid, server_logo[playerid][2], 2);
		PlayerTextDrawColor(playerid, server_logo[playerid][2], -1);
		PlayerTextDrawBackgroundColor(playerid, server_logo[playerid][2], 255);
		PlayerTextDrawFont(playerid, server_logo[playerid][2], 1);
		PlayerTextDrawSetProportional(playerid, server_logo[playerid][2], 1);
		PlayerTextDrawSetShadow(playerid, server_logo[playerid][2], 0);

		server_logo[playerid][3] = CreatePlayerTextDraw(playerid, 588.0000, 2.0000, "chancerp.ru"); // пусто
		PlayerTextDrawLetterSize(playerid, server_logo[playerid][3], 0.2000, 1.0000);
		PlayerTextDrawAlignment(playerid, server_logo[playerid][3], 2);
		PlayerTextDrawColor(playerid, server_logo[playerid][3], -1);
		PlayerTextDrawBackgroundColor(playerid, server_logo[playerid][3], 255);
		PlayerTextDrawFont(playerid, server_logo[playerid][3], 1);
		PlayerTextDrawSetProportional(playerid, server_logo[playerid][3], 1);
		PlayerTextDrawSetShadow(playerid, server_logo[playerid][3], 0);
	}	
	// Показ лого (как раз после авторизации)
	update_logo_textdraw_color(playerid);
	show_logo(playerid);

	// ТД Спидометр
	speedo_TD[playerid][0] = CreatePlayerTextDraw(playerid, 357.000000, 397.233337, "usebox");
	PlayerTextDrawLetterSize(playerid, speedo_TD[playerid][0], 0.000000, 2.421109);
	PlayerTextDrawTextSize(playerid, speedo_TD[playerid][0], 280.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, speedo_TD[playerid][0], 1);
	PlayerTextDrawColor(playerid, speedo_TD[playerid][0], 0);
	PlayerTextDrawUseBox(playerid, speedo_TD[playerid][0], true);
	PlayerTextDrawBoxColor(playerid, speedo_TD[playerid][0], TD_COLOR_DEFAULT);
	PlayerTextDrawSetShadow(playerid, speedo_TD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, speedo_TD[playerid][0], 0);
	PlayerTextDrawFont(playerid, speedo_TD[playerid][0], 0);		

	speedo_TD[playerid][1] = CreatePlayerTextDraw(playerid, 284.333404, 392.373352, "");
	PlayerTextDrawLetterSize(playerid, speedo_TD[playerid][1], 0.449999, 1.600000);
	PlayerTextDrawAlignment(playerid, speedo_TD[playerid][1], 1);
	PlayerTextDrawColor(playerid, speedo_TD[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, speedo_TD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, speedo_TD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, speedo_TD[playerid][1], 51);
	PlayerTextDrawFont(playerid, speedo_TD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, speedo_TD[playerid][1], 1);

	// red box (-16776961) \ green box (16711935)

	car_params_td[playerid][0] = CreatePlayerTextDraw(playerid, 360.9999, 397.1997, "Box"); // пусто
	PlayerTextDrawLetterSize(playerid, car_params_td[playerid][0], 0.0000, 0.9998);
	PlayerTextDrawTextSize(playerid, car_params_td[playerid][0], 374.0000, 0.0000);
	PlayerTextDrawAlignment(playerid, car_params_td[playerid][0], 1);
	PlayerTextDrawColor(playerid, car_params_td[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, car_params_td[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, car_params_td[playerid][0], 0xDD90FFFF);
	PlayerTextDrawBackgroundColor(playerid, car_params_td[playerid][0], 255);
	PlayerTextDrawFont(playerid, car_params_td[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, car_params_td[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, car_params_td[playerid][0], 0);

	car_params_td[playerid][1] = CreatePlayerTextDraw(playerid, 264.9978, 397.1997, "Box"); // пусто
	PlayerTextDrawLetterSize(playerid, car_params_td[playerid][1], 0.0000, 0.9998);
	PlayerTextDrawTextSize(playerid, car_params_td[playerid][1], 277.9978, 0.0000);
	PlayerTextDrawAlignment(playerid, car_params_td[playerid][1], 1);
	PlayerTextDrawColor(playerid, car_params_td[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, car_params_td[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, car_params_td[playerid][1], 0xDD90FFFF);
	PlayerTextDrawBackgroundColor(playerid, car_params_td[playerid][1], 255);
	PlayerTextDrawFont(playerid, car_params_td[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, car_params_td[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, car_params_td[playerid][1], 0);

	car_params_td[playerid][2] = CreatePlayerTextDraw(playerid, 367.2391, 397.8533, "LOCK"); // пусто
	PlayerTextDrawLetterSize(playerid, car_params_td[playerid][2], 0.1817, 0.8047);
	PlayerTextDrawAlignment(playerid, car_params_td[playerid][2], 2);
	PlayerTextDrawColor(playerid, car_params_td[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, car_params_td[playerid][2], 255);
	PlayerTextDrawFont(playerid, car_params_td[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, car_params_td[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, car_params_td[playerid][2], 0);

	car_params_td[playerid][3] = CreatePlayerTextDraw(playerid, 271.6333, 397.8533, "ENG"); // пусто
	PlayerTextDrawLetterSize(playerid, car_params_td[playerid][3], 0.1817, 0.8047);
	PlayerTextDrawAlignment(playerid, car_params_td[playerid][3], 2);
	PlayerTextDrawColor(playerid, car_params_td[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, car_params_td[playerid][3], 255);
	PlayerTextDrawFont(playerid, car_params_td[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, car_params_td[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, car_params_td[playerid][3], 0);	

	car_params_td[playerid][4] = CreatePlayerTextDraw(playerid, 360.9999, 412.1997, "Box"); // пусто
	PlayerTextDrawLetterSize(playerid, car_params_td[playerid][4], 0.0000, 0.9998);
	PlayerTextDrawTextSize(playerid, car_params_td[playerid][4], 374.0000, 0.0000);
	PlayerTextDrawAlignment(playerid, car_params_td[playerid][4], 1);
	PlayerTextDrawColor(playerid, car_params_td[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, car_params_td[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, car_params_td[playerid][4], 0xDD90FFFF);
	PlayerTextDrawBackgroundColor(playerid, car_params_td[playerid][4], 255);
	PlayerTextDrawFont(playerid, car_params_td[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, car_params_td[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, car_params_td[playerid][4], 0);

	car_params_td[playerid][5] = CreatePlayerTextDraw(playerid, 367.2391, 413.8533, "0"); // пусто
	PlayerTextDrawLetterSize(playerid, car_params_td[playerid][5], 0.1817, 0.8047);
	PlayerTextDrawAlignment(playerid, car_params_td[playerid][5], 2);
	PlayerTextDrawColor(playerid, car_params_td[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, car_params_td[playerid][5], 255);
	PlayerTextDrawFont(playerid, car_params_td[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, car_params_td[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, car_params_td[playerid][5], 0);	


	if(GetPVarInt(playerid, "mobile")) {

		speedo_TD[playerid][2] = CreatePlayerTextDraw(playerid, 319, 422.239898, "000000000");
		PlayerTextDrawLetterSize(playerid, speedo_TD[playerid][2], 0.37, 1.6);
		PlayerTextDrawAlignment(playerid, speedo_TD[playerid][2], 2);
		PlayerTextDrawColor(playerid, speedo_TD[playerid][2], -1);
		PlayerTextDrawSetShadow(playerid, speedo_TD[playerid][2], 0);
		PlayerTextDrawSetOutline(playerid, speedo_TD[playerid][2], 1);
		PlayerTextDrawBackgroundColor(playerid, speedo_TD[playerid][2], 51);
		PlayerTextDrawFont(playerid, speedo_TD[playerid][2], 3);
		PlayerTextDrawSetProportional(playerid, speedo_TD[playerid][2], 1);

		speedo_TD[playerid][3] = CreatePlayerTextDraw(playerid, 319.000152, 406.186706, "{999999}IIIIIIIIIIIIIIIIII");
		PlayerTextDrawLetterSize(playerid, speedo_TD[playerid][3], 0.27, 1.6);
		PlayerTextDrawAlignment(playerid, speedo_TD[playerid][3], 2);
		PlayerTextDrawColor(playerid, speedo_TD[playerid][3], -1);
		PlayerTextDrawSetShadow(playerid, speedo_TD[playerid][3], 0);
		PlayerTextDrawSetOutline(playerid, speedo_TD[playerid][3], 0);
		PlayerTextDrawBackgroundColor(playerid, speedo_TD[playerid][3], 51);
		PlayerTextDrawFont(playerid, speedo_TD[playerid][3], 1);
		PlayerTextDrawSetProportional(playerid, speedo_TD[playerid][3], 1);

	} else {
	
		speedo_TD[playerid][2] = CreatePlayerTextDraw(playerid, 318.666687, 422.239898, "000000000");
		PlayerTextDrawLetterSize(playerid, speedo_TD[playerid][2], 0.412333, 1.510400);
		PlayerTextDrawAlignment(playerid, speedo_TD[playerid][2], 2);
		PlayerTextDrawColor(playerid, speedo_TD[playerid][2], -1);
		PlayerTextDrawSetShadow(playerid, speedo_TD[playerid][2], 0);
		PlayerTextDrawSetOutline(playerid, speedo_TD[playerid][2], 1);
		PlayerTextDrawBackgroundColor(playerid, speedo_TD[playerid][2], 51);
		PlayerTextDrawFont(playerid, speedo_TD[playerid][2], 3);
		PlayerTextDrawSetProportional(playerid, speedo_TD[playerid][2], 1);

		speedo_TD[playerid][3] = CreatePlayerTextDraw(playerid, 319.000152, 406.186706, "{999999}IIIIIIIIIIIIIIIIII");
		PlayerTextDrawLetterSize(playerid, speedo_TD[playerid][3], 0.292666, 1.327467);
		PlayerTextDrawAlignment(playerid, speedo_TD[playerid][3], 2);
		PlayerTextDrawColor(playerid, speedo_TD[playerid][3], -1);
		PlayerTextDrawSetShadow(playerid, speedo_TD[playerid][3], 0);
		PlayerTextDrawSetOutline(playerid, speedo_TD[playerid][3], 0);
		PlayerTextDrawBackgroundColor(playerid, speedo_TD[playerid][3], 51);
		PlayerTextDrawFont(playerid, speedo_TD[playerid][3], 1);
		PlayerTextDrawSetProportional(playerid, speedo_TD[playerid][3], 1);

	}
	return 1;
}

stock update_logo_textdraw_color(playerid) {
	PlayerTextDrawHide(playerid, 	server_logo[playerid][0]);
	PlayerTextDrawHide(playerid, 	server_logo[playerid][1]);

	switch(PlayerInfo[playerid][pColor]) {
		case 1: {
			PlayerTextDrawColor(playerid, server_logo[playerid][0], TD_COLOR_GREEN);
			PlayerTextDrawBoxColor(playerid, server_logo[playerid][1], TD_COLOR_GREEN);
		}
		case 2: {
			PlayerTextDrawColor(playerid, server_logo[playerid][0], TD_COLOR_BLACK);
			PlayerTextDrawBoxColor(playerid, server_logo[playerid][1], TD_COLOR_BLACK);
		}
		case 3: {
			PlayerTextDrawColor(playerid, server_logo[playerid][0], TD_COLOR_ORANGE);
			PlayerTextDrawBoxColor(playerid, server_logo[playerid][1], TD_COLOR_ORANGE);
		}
		case 4: {
			PlayerTextDrawColor(playerid, server_logo[playerid][0], TD_COLOR_NULL);
			PlayerTextDrawBoxColor(playerid, server_logo[playerid][1], TD_COLOR_NULL);
		}		
		default: {
			PlayerTextDrawColor(playerid, server_logo[playerid][0], TD_COLOR_DEFAULT);
			PlayerTextDrawBoxColor(playerid, server_logo[playerid][1], TD_COLOR_DEFAULT);
		}
	}

	PlayerTextDrawShow(playerid, 	server_logo[playerid][0]);
	PlayerTextDrawShow(playerid, 	server_logo[playerid][1]);

	if(IsPlayerInAnyVehicle(playerid)) {
		hide_speedo(playerid);
		show_speedo(playerid, GetVehicleModel(GetPlayerVehicleID(playerid)));
		return 1;
	}
	return 1;
}

stock destroy_logo_textdraws(playerid) {
	for(new i = 0; i < sizeof(server_logo[]); i++) {
		if(server_logo[playerid][i] == PlayerText:INVALID_TEXT_DRAW) {
			continue;
		}

		PlayerTextDrawHide(playerid, server_logo[playerid][i]);
		PlayerTextDrawDestroy(playerid, server_logo[playerid][i]);
	}
	return 1;
}
stock destroy_speedo_textdraws(playerid) {
	for(new i = 0; i < sizeof(speedo_TD[]); i++) {
		if(speedo_TD[playerid][i] == PlayerText:INVALID_TEXT_DRAW) {
			continue;
		}

		PlayerTextDrawHide(playerid, speedo_TD[playerid][i]);
		PlayerTextDrawDestroy(playerid, speedo_TD[playerid][i]);
	}
	return 1;
}

stock show_logo(playerid) {
	for(new i = 0; i < sizeof(server_logo[]); i++) {
		PlayerTextDrawShow(playerid, server_logo[playerid][i]);
	}
}

stock show_speedo(playerid, modelid) {
	if(modelid != 481 && modelid != 510 && modelid != 509) {

		switch(PlayerInfo[playerid][pColor]) {
			case 1: {
				PlayerTextDrawBoxColor(playerid, speedo_TD[playerid][0], TD_COLOR_GREEN);
			}
			case 2: {
				PlayerTextDrawBoxColor(playerid, speedo_TD[playerid][0], TD_COLOR_BLACK);
			}
			case 3: {
				PlayerTextDrawBoxColor(playerid, speedo_TD[playerid][0], TD_COLOR_ORANGE);
			}
			case 4: {
				PlayerTextDrawBoxColor(playerid, speedo_TD[playerid][0], TD_COLOR_NULL);
			}			
			default: {
				PlayerTextDrawBoxColor(playerid, speedo_TD[playerid][0], TD_COLOR_DEFAULT);
			}
		}

		PlayerTextDrawShow(playerid, speedo_TD[playerid][0]);
		PlayerTextDrawShow(playerid, speedo_TD[playerid][1]);


		for(new i = 0; i < sizeof(car_params_td[]); i++) {
			PlayerTextDrawShow(playerid, car_params_td[playerid][i]);
		}

		if(IsPlayerInVehicle(playerid, caridhouse[playerid])) {
			PlayerTextDrawShow(playerid, speedo_TD[playerid][2]);
		}
		PlayerTextDrawShow(playerid, speedo_TD[playerid][3]);
	}
	return 1;
}

stock hide_logo(playerid) {
	for(new i = 0; i < sizeof(server_logo[]); i++) {
		if(server_logo[playerid][i] == PlayerText:INVALID_TEXT_DRAW) {
			continue;
		}

		PlayerTextDrawHide(playerid, server_logo[playerid][i]);
	}
	return 1;
}

stock hide_speedo(playerid) {
	for(new i = 0; i < sizeof(speedo_TD[]); i++) {
		if(speedo_TD[playerid][i] == PlayerText:INVALID_TEXT_DRAW) {
			continue;
		}

		PlayerTextDrawHide(playerid, speedo_TD[playerid][i]);
	}

	for(new i = 0; i < sizeof(car_params_td[]); i++) {
		PlayerTextDrawHide(playerid, car_params_td[playerid][i]);
	}

	return 1;
}

stock update_speedo(playerid, speed) {
	if(0 <= speed <= 1) {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"");
    } else  if(2 <= speed <= 10) {
		PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"I");
    } else  if(11 <= speed <= 20) {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"II");
    } else  if(21 <= speed <= 30) {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"III");
    } else  if(31 <= speed <= 45) {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"IIII");
    } else  if(46 <= speed <= 47) {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"IIIII");
    } else  if(48 <= speed <= 59) {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"IIIIII");
    } else  if(60 <= speed <= 75) {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"IIIIIII");
    } else  if(76 <= speed <= 90) {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"IIIIIIII");
    } else  if(91 <= speed <= 100) {
		PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"IIIIIIIII");
    } else  if(101 <= speed <= 105) {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"IIIIIIIIII");
    } else  if(106 <= speed <= 110) {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"IIIIIIIIIII");
    } else  if(111 <= speed <= 115) {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"IIIIIIIIIIII");
    } else  if(116 <= speed <= 120) {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"IIIIIIIIIIIII");
    } else  {
    	PlayerTextDrawSetString(playerid,speedo_TD[playerid][1],"IIIIIIIIIIIIII");
    }
    UpdateIndicatorStatus(playerid);
	return 1;
}

stock update_spec_textdraw_color(playerid) {
	if(GetPlayerAdminLevel(playerid) < 1) return true;
	switch(PlayerInfo[playerid][pColor]) {
		case 1: {
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][0], TD_COLOR_GREEN);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][2], TD_COLOR_GREEN);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][3], TD_COLOR_GREEN);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][4], TD_COLOR_GREEN);
		}
		case 2: {
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][0], TD_COLOR_BLACK);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][2], TD_COLOR_BLACK);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][3], TD_COLOR_BLACK);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][4], TD_COLOR_BLACK);
		}
		case 3: {
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][0], TD_COLOR_ORANGE);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][2], TD_COLOR_ORANGE);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][3], TD_COLOR_ORANGE);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][4], TD_COLOR_ORANGE);
		}
		case 4: {
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][0], TD_COLOR_NULL);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][2], TD_COLOR_NULL);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][3], TD_COLOR_NULL);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][4], TD_COLOR_NULL);
		}		
		default: {
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][0], TD_COLOR_DEFAULT);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][2], TD_COLOR_DEFAULT);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][3], TD_COLOR_DEFAULT);
			PlayerTextDrawBoxColor(playerid, spec_PTD[playerid][4], TD_COLOR_DEFAULT);
		}
	}
	return 1;
}

stock spec_show(playerid) {
	if(GetPlayerAdminLevel(playerid) < 1) return true;
	for(new i = 0; i < sizeof(spec_PTD[]); i++) {
		if(spec_PTD[playerid][i] == PlayerText:INVALID_TEXT_DRAW) {
			continue;
		}
		update_spec_textdraw_color(playerid);
		PlayerTextDrawShow(playerid, spec_PTD[playerid][i]);
		//SelectTextDraw(playerid, 0x2A3439FF);
	}
	return 1;
}
stock hide_spec(playerid) {
	if(GetPlayerAdminLevel(playerid) < 1) return true;
	for(new i = 0; i < sizeof(spec_PTD[]); i++) {
		if(spec_PTD[playerid][i] == PlayerText:INVALID_TEXT_DRAW) {
			continue;
		}

		PlayerTextDrawHide(playerid, spec_PTD[playerid][i]);
		CancelSelectTextDraw(playerid);
	}
	return 1;
}

stock destroy_spec_textdraws(playerid) {
	if(GetPlayerAdminLevel(playerid) < 1) return true;
	for(new i = 0; i < sizeof(spec_PTD[]); i++) {
		if(spec_PTD[playerid][i] == PlayerText:INVALID_TEXT_DRAW) {
			continue;
		}

		PlayerTextDrawDestroy(playerid, spec_PTD[playerid][i]);
	}	
	return 1;
}
 
stock spec_update(playerid) {
	if(GetPlayerAdminLevel(playerid) < 1) return true;
	new targetid = spectating[playerid];
	if(!IsPlayerConnected(targetid)) return 1;
	new Float:hppp, Float:armour, Float:health;
	new playersip[20];


	GetPlayerIp(spectating[playerid],playersip,sizeof(playersip));

	GetPlayerArmour(spectating[playerid],armour);
	GetPlayerHealth(spectating[playerid],hppp);
	GetVehicleHealth(GetPlayerVehicleID(spectating[playerid]),health);

	new spectate_string[512];

	format(spectate_string, sizeof(spectate_string),
		"%s(%d)~n~\
		Health: %.2f~n~\
		Armour: %.2f~n~\
		Speed: %dkm/h~n~~n~\
		IP: %s~n~\
		Ping: %d~n~~n~\
		%s",
		PlayerInfo[targetid][pName],
		targetid,
		(IsPlayerInAnyVehicle(targetid) == 1) ? (health) : (hppp),
		armour,
		(IsPlayerInAnyVehicle(targetid) == 1) ? (floatround(GetVehicleSpeed(GetPlayerVehicleID(targetid)))) : (PlayerSpeed(targetid)),
		ipsget[targetid],
		GetPlayerPing(targetid),
		(GetPVarInt(targetid, "mobile")) ? ("Android") : ("PC")
	);
	PlayerTextDrawSetString(playerid, spec_PTD[playerid][1], spectate_string);
	return 1;
}

stock update_tune_textdraw_color(playerid) {
	switch(PlayerInfo[playerid][pColor]) {
		case 1: {
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][0], TD_COLOR_GREEN);
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][1], TD_COLOR_GREEN);
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][2], TD_COLOR_GREEN);
		}
		case 2: {
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][0], TD_COLOR_BLACK);
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][1], TD_COLOR_BLACK);
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][2], TD_COLOR_BLACK);
		}
		case 3: {
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][0], TD_COLOR_ORANGE);
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][1], TD_COLOR_ORANGE);
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][2], TD_COLOR_ORANGE);
		}
		case 4: {
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][0], TD_COLOR_NULL);
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][1], TD_COLOR_NULL);
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][2], TD_COLOR_NULL);
		}		
		default: {
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][0], TD_COLOR_DEFAULT);
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][1], TD_COLOR_DEFAULT);
			PlayerTextDrawBoxColor(playerid, tuning_ui[playerid][2], TD_COLOR_DEFAULT);
		}
	}
	return 1;
}

stock tuning_show(playerid) {

	for(new i = 0; i < sizeof(tuning_ui[]); i++) {
		if(tuning_ui[playerid][i] == PlayerText:INVALID_TEXT_DRAW) {
			continue;
		}
		update_tune_textdraw_color(playerid);
		PlayerTextDrawShow(playerid, tuning_ui[playerid][i]);
		SelectTextDraw(playerid, 0x2A3439FF);
	}
	return 1;
}
stock hide_tuning(playerid) {

	for(new i = 0; i < sizeof(tuning_ui[]); i++) {
		if(tuning_ui[playerid][i] == PlayerText:INVALID_TEXT_DRAW) {
			continue;
		}

		PlayerTextDrawHide(playerid, tuning_ui[playerid][i]);
		CancelSelectTextDraw(playerid);
	}
	return 1;
}

stock destroy_tuning_textdraws(playerid) {
	for(new i = 0; i < sizeof(tuning_ui[]); i++) {
		if(tuning_ui[playerid][i] == PlayerText:INVALID_TEXT_DRAW) {
			continue;
		}

		PlayerTextDrawDestroy(playerid, tuning_ui[playerid][i]);
	}	
	return 1;
}

DialogCreate:selectcolor(playerid) {
		return Dialog_Open(playerid, Dialog:selectcolor, DIALOG_STYLE_LIST,
		""COLOR_BLUE"Выберите цвет оформления",
		"Красный\n\
		Зеленый\n\
		Синий\n\
		Оранжевый",
		"Выбрать", "Закрыть"
	);
}

DialogResponse:selectcolor(playerid, response, listitem, inputtext[]) {
	if(!response) return 1;
	switch(listitem) {
		case 0: {
			if(PlayerInfo[playerid][pColor] == 0) SendClientMessage(playerid, -1, !""COLOR_YELLOW"Цвет установлен");
			PlayerInfo[playerid][pColor] = 0;
			SetPlayerInt(playerid, "Color", PlayerInfo[playerid][pColor]);
			update_logo_textdraw_color(playerid);
			update_spec_textdraw_color(playerid);
			SetPVarInt(playerid,"AntiFloodTD",gettime() + 10);
		}
		case 1: {
			if(PlayerInfo[playerid][pColor] == 1) SendClientMessage(playerid, -1, !""COLOR_YELLOW"Цвет установлен");
			PlayerInfo[playerid][pColor] = 1;
			SetPlayerInt(playerid, "Color", PlayerInfo[playerid][pColor]);
			update_logo_textdraw_color(playerid);
			update_spec_textdraw_color(playerid);
			SetPVarInt(playerid,"AntiFloodTD",gettime() + 10);
		}
		case 2: {
			if(PlayerInfo[playerid][pColor] == 2) SendClientMessage(playerid, -1, !""COLOR_YELLOW"Цвет установлен");
			PlayerInfo[playerid][pColor] = 2;
			SetPlayerInt(playerid, "Color", PlayerInfo[playerid][pColor]);
			update_logo_textdraw_color(playerid);
			update_spec_textdraw_color(playerid);
			SetPVarInt(playerid,"AntiFloodTD",gettime() + 10);
		}
		case 3: {
			if(PlayerInfo[playerid][pColor] == 3) SendClientMessage(playerid, -1, !""COLOR_YELLOW"Цвет установлен");
			PlayerInfo[playerid][pColor] = 3;
			SetPlayerInt(playerid, "Color", PlayerInfo[playerid][pColor]);
			update_logo_textdraw_color(playerid);
			update_spec_textdraw_color(playerid);
			SetPVarInt(playerid,"AntiFloodTD",gettime() + 10);
		}
	}

	if(PlayerInfo[playerid][pColorSelected] == 0) {
		PlayerInfo[playerid][pColorSelected] = 1;
		SetPlayerInt(playerid, "ColorSelected", PlayerInfo[playerid][pColorSelected]);
	}

	if(GetPVarInt(playerid, "mobile")) ShowPlayerDialog(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, ""COLOR_ORANGE"Информация", ""COLOR_WHITE"Настоятельно рекомендуем в настройках графики "COLOR_ORANGE"отключить тени"COLOR_WHITE" - DYNAMIC SHADOWS\nИ установить "COLOR_ORANGE"английский язык"COLOR_WHITE" для правильной и стабильной работы игры!", "ОК", "");
	return 1;
}

CMD:selectcolor(playerid, params[])
{
	return Dialog_Show(playerid, Dialog:selectcolor);
}