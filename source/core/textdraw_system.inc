#if defined _textdraw_system_included
	#endinput
#endif
#define _textdraw_system_included

#define TD_COLOR_DEFAULT 0xff353cFF
#define TD_COLOR_GREEN 0x67da41FF
#define TD_COLOR_BLACK 0x4eb9e6FF
#define TD_COLOR_ORANGE 0xFFAF00FF

new PlayerText:server_logo_0[MAX_PLAYERS];
new PlayerText:server_logo_1[MAX_PLAYERS];
new PlayerText:server_logo_2[MAX_PLAYERS];
new PlayerText:server_logo_3[MAX_PLAYERS];

new PlayerText:speedo_TD_0[MAX_PLAYERS];
new PlayerText:speedo_TD_1[MAX_PLAYERS];
new PlayerText:speedo_TD_2[MAX_PLAYERS];
new PlayerText:speedo_TD_3[MAX_PLAYERS];


stock TD_OnPlayerDisconnect(playerid) {
	if(Platform[playerid] == 1) {
	destroy_logo_textdraws(playerid);
	destroy_speedo_textdraws(playerid);
	}
	return 1;
}

CMD:selectcolor(playerid, params[])
{
	return SPD(playerid, dSelectColor, DIALOG_STYLE_LIST, ""COLOR_BLUE"Выберите цвет оформления", "1. Красный\n2. Зеленый\n3. Синий\n4. Оранжевый", "Выбрать", "Отмена");
}

forward TD_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
public TD_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
    case dSelectColor: {
	if(!response) return 1;
	if(response) {
		if(GetPVarInt(playerid,"AntiFloodTD") > gettime())	{ SendClientMessage(playerid, -1, !""COLOR_RED"Повторите через несколько секунд"); return false; }
		switch(listitem) {
			case 0: {
				if(PlayerInfo[playerid][pColor] == 0) callcmd::selectcolor(playerid,"\0"); SendClientMessage(playerid, -1, !""COLOR_YELLOW"Цвет установлен");
				PlayerInfo[playerid][pColor] = 0;
				SetPlayerInt(playerid, "Color", PlayerInfo[playerid][pColor]);
				update_logo_textdraw_color(playerid);
				SetPVarInt(playerid,"AntiFloodTD",gettime() + 10);
			}
			case 1: {
				if(PlayerInfo[playerid][pColor] == 1) callcmd::selectcolor(playerid,"\0"); SendClientMessage(playerid, -1, !""COLOR_YELLOW"Цвет установлен");
				PlayerInfo[playerid][pColor] = 1;
				SetPlayerInt(playerid, "Color", PlayerInfo[playerid][pColor]);
				update_logo_textdraw_color(playerid);
				SetPVarInt(playerid,"AntiFloodTD",gettime() + 10);
			}
			case 2: {
				if(PlayerInfo[playerid][pColor] == 2) callcmd::selectcolor(playerid,"\0"); SendClientMessage(playerid, -1, !""COLOR_YELLOW"Цвет установлен");
				PlayerInfo[playerid][pColor] = 2;
				SetPlayerInt(playerid, "Color", PlayerInfo[playerid][pColor]);
				update_logo_textdraw_color(playerid);
				SetPVarInt(playerid,"AntiFloodTD",gettime() + 10);
			}
			case 3: {
				if(PlayerInfo[playerid][pColor] == 3) callcmd::selectcolor(playerid,"\0"); SendClientMessage(playerid, -1, !""COLOR_YELLOW"Цвет установлен");
				PlayerInfo[playerid][pColor] = 3;
				SetPlayerInt(playerid, "Color", PlayerInfo[playerid][pColor]);
				update_logo_textdraw_color(playerid);
				SetPVarInt(playerid,"AntiFloodTD",gettime() + 10);
			}
    	}
	}
	return 1;
	}
	}
	return 1;
}

forward TD_OnPlayerAuthorization(playerid);
public TD_OnPlayerAuthorization(playerid) {
	if(Platform[playerid] == 1) {
	server_logo_0[playerid] = CreatePlayerTextDraw(playerid, 541.666931, 5.599995, "CHANCE");
	PlayerTextDrawLetterSize(playerid, server_logo_0[playerid], 0.340333, 1.398398);
	PlayerTextDrawAlignment(playerid, server_logo_0[playerid], 1);
	PlayerTextDrawColor(playerid, server_logo_0[playerid], TD_COLOR_DEFAULT);
	PlayerTextDrawSetShadow(playerid, server_logo_0[playerid], 0);
	PlayerTextDrawSetOutline(playerid, server_logo_0[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, server_logo_0[playerid], 51);
	PlayerTextDrawFont(playerid, server_logo_0[playerid], 1);
	PlayerTextDrawSetProportional(playerid, server_logo_0[playerid], 1);

	server_logo_1[playerid] = CreatePlayerTextDraw(playerid, 592.666870, 9.713334, "usebox");
	PlayerTextDrawLetterSize(playerid, server_logo_1[playerid], 0.000000, 0.642592);
	PlayerTextDrawTextSize(playerid, server_logo_1[playerid], 582.333374, 0.000000);
	PlayerTextDrawAlignment(playerid, server_logo_1[playerid], 0);
	PlayerTextDrawUseBox(playerid, server_logo_1[playerid], true);
	PlayerTextDrawBoxColor(playerid, server_logo_1[playerid], TD_COLOR_DEFAULT);
	PlayerTextDrawSetShadow(playerid, server_logo_1[playerid], 0);
	PlayerTextDrawSetOutline(playerid, server_logo_1[playerid], 0);
	PlayerTextDrawFont(playerid, server_logo_1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, server_logo_1[playerid], 1);

	server_logo_2[playerid] = CreatePlayerTextDraw(playerid, 584.333435, 8.586679, "RP");
	PlayerTextDrawLetterSize(playerid, server_logo_2[playerid], 0.181333, 0.797333);
	PlayerTextDrawAlignment(playerid, server_logo_2[playerid], 1);
	PlayerTextDrawColor(playerid, server_logo_2[playerid], -1);
	PlayerTextDrawSetShadow(playerid, server_logo_2[playerid], 0);
	PlayerTextDrawSetOutline(playerid, server_logo_2[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, server_logo_2[playerid], 51);
	PlayerTextDrawFont(playerid, server_logo_2[playerid], 1);
	PlayerTextDrawSetProportional(playerid, server_logo_2[playerid], 1);

	server_logo_3[playerid] = CreatePlayerTextDraw(playerid, 563.000000, 16.800014, "chancerp.ru");
	PlayerTextDrawLetterSize(playerid, server_logo_3[playerid], 0.155999, 0.681599);
	PlayerTextDrawAlignment(playerid, server_logo_3[playerid], 1);
	PlayerTextDrawColor(playerid, server_logo_3[playerid], -1);
	PlayerTextDrawSetShadow(playerid, server_logo_3[playerid], 0);
	PlayerTextDrawSetOutline(playerid, server_logo_3[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, server_logo_3[playerid], 51);
	PlayerTextDrawFont(playerid, server_logo_3[playerid], 1);
	PlayerTextDrawSetProportional(playerid, server_logo_3[playerid], 1);

	update_logo_textdraw_color(playerid);

	speedo_TD_0[playerid] = CreatePlayerTextDraw(playerid, 357.000000, 397.233337, "usebox");
	PlayerTextDrawLetterSize(playerid, speedo_TD_0[playerid], 0.000000, 2.421109);
	PlayerTextDrawTextSize(playerid, speedo_TD_0[playerid], 280.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, speedo_TD_0[playerid], 1);
	PlayerTextDrawColor(playerid, speedo_TD_0[playerid], 0);
	PlayerTextDrawUseBox(playerid, speedo_TD_0[playerid], true);
	PlayerTextDrawBoxColor(playerid, speedo_TD_0[playerid], TD_COLOR_DEFAULT);
	PlayerTextDrawSetShadow(playerid, speedo_TD_0[playerid], 0);
	PlayerTextDrawSetOutline(playerid, speedo_TD_0[playerid], 0);
	PlayerTextDrawFont(playerid, speedo_TD_0[playerid], 0);

	speedo_TD_1[playerid] = CreatePlayerTextDraw(playerid, 284.333404, 392.373352, "");
	PlayerTextDrawLetterSize(playerid, speedo_TD_1[playerid], 0.449999, 1.600000);
	PlayerTextDrawAlignment(playerid, speedo_TD_1[playerid], 1);
	PlayerTextDrawColor(playerid, speedo_TD_1[playerid], -1);
	PlayerTextDrawSetShadow(playerid, speedo_TD_1[playerid], 0);
	PlayerTextDrawSetOutline(playerid, speedo_TD_1[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, speedo_TD_1[playerid], 51);
	PlayerTextDrawFont(playerid, speedo_TD_1[playerid], 1);
	PlayerTextDrawSetProportional(playerid, speedo_TD_1[playerid], 1);

	speedo_TD_2[playerid] = CreatePlayerTextDraw(playerid, 318.666687, 422.239898, "000000000");
	PlayerTextDrawLetterSize(playerid, speedo_TD_2[playerid], 0.412333, 1.510400);
	PlayerTextDrawAlignment(playerid, speedo_TD_2[playerid], 2);
	PlayerTextDrawColor(playerid, speedo_TD_2[playerid], -1);
	PlayerTextDrawSetShadow(playerid, speedo_TD_2[playerid], 0);
	PlayerTextDrawSetOutline(playerid, speedo_TD_2[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, speedo_TD_2[playerid], 51);
	PlayerTextDrawFont(playerid, speedo_TD_2[playerid], 3);
	PlayerTextDrawSetProportional(playerid, speedo_TD_2[playerid], 1);

	speedo_TD_3[playerid] = CreatePlayerTextDraw(playerid, 319.000152, 406.186706, "{999999}IIIIIIIIIIIIIIIIII");
	PlayerTextDrawLetterSize(playerid, speedo_TD_3[playerid], 0.292666, 1.327467);
	PlayerTextDrawAlignment(playerid, speedo_TD_3[playerid], 2);
	PlayerTextDrawColor(playerid, speedo_TD_3[playerid], -1);
	PlayerTextDrawSetShadow(playerid, speedo_TD_3[playerid], 0);
	PlayerTextDrawSetOutline(playerid, speedo_TD_3[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, speedo_TD_3[playerid], 51);
	PlayerTextDrawFont(playerid, speedo_TD_3[playerid], 1);
	PlayerTextDrawSetProportional(playerid, speedo_TD_3[playerid], 1);

	PlayerTextDrawShow(playerid, 	server_logo_0[playerid]);	
	PlayerTextDrawShow(playerid, 	server_logo_1[playerid]);
	PlayerTextDrawShow(playerid,	server_logo_2[playerid]);
	PlayerTextDrawShow(playerid,	server_logo_3[playerid]);
	}
	return 1;
}

stock update_logo_textdraw_color(playerid) {
	PlayerTextDrawHide(playerid, 	server_logo_0[playerid]);
	PlayerTextDrawHide(playerid, 	server_logo_1[playerid]);

	if(PlayerInfo[playerid][pColor] == 0) {
	PlayerTextDrawColor(playerid, server_logo_0[playerid], TD_COLOR_DEFAULT);
	PlayerTextDrawBoxColor(playerid, server_logo_1[playerid], TD_COLOR_DEFAULT);
	}
	if(PlayerInfo[playerid][pColor] == 1) {
	PlayerTextDrawColor(playerid, server_logo_0[playerid], TD_COLOR_GREEN);
	PlayerTextDrawBoxColor(playerid, server_logo_1[playerid], TD_COLOR_GREEN);
	}
	if(PlayerInfo[playerid][pColor] == 2) {
	PlayerTextDrawColor(playerid, server_logo_0[playerid], TD_COLOR_BLACK);
	PlayerTextDrawBoxColor(playerid, server_logo_1[playerid], TD_COLOR_BLACK);
	}
	if(PlayerInfo[playerid][pColor] == 3) {
	PlayerTextDrawColor(playerid, server_logo_0[playerid], TD_COLOR_ORANGE);
	PlayerTextDrawBoxColor(playerid, server_logo_1[playerid], TD_COLOR_ORANGE);
	}

	PlayerTextDrawShow(playerid, 	server_logo_0[playerid]);	
	PlayerTextDrawShow(playerid, 	server_logo_1[playerid]);

	if(IsPlayerInAnyVehicle(playerid)) {
		hide_speedo(playerid);
		show_speedo(playerid, GetVehicleModel(GetPlayerVehicleID(playerid)));
		return 1;		
	}
	return 1;
}

stock destroy_logo_textdraws(playerid) {
	PlayerTextDrawHide(playerid, 	server_logo_0[playerid]);
	PlayerTextDrawHide(playerid, 	server_logo_1[playerid]);
	PlayerTextDrawHide(playerid,	server_logo_2[playerid]);
	PlayerTextDrawHide(playerid,	server_logo_3[playerid]);

	PlayerTextDrawDestroy(playerid, server_logo_0[playerid]);
	PlayerTextDrawDestroy(playerid, server_logo_1[playerid]);
	PlayerTextDrawDestroy(playerid, server_logo_2[playerid]);
	PlayerTextDrawDestroy(playerid, server_logo_3[playerid]);
	return 1;
}
stock destroy_speedo_textdraws(playerid) {
	PlayerTextDrawHide(playerid, 	speedo_TD_0[playerid]);	
	PlayerTextDrawHide(playerid, 	speedo_TD_1[playerid]);
	PlayerTextDrawHide(playerid,	speedo_TD_2[playerid]);
	PlayerTextDrawHide(playerid,	speedo_TD_3[playerid]);	

	PlayerTextDrawDestroy(playerid, speedo_TD_0[playerid]);
	PlayerTextDrawDestroy(playerid, speedo_TD_1[playerid]);
	PlayerTextDrawDestroy(playerid, speedo_TD_2[playerid]);
	PlayerTextDrawDestroy(playerid, speedo_TD_3[playerid]);
	return 1;
}
stock show_speedo(playerid, modelid) {
	if(modelid != 481 && modelid != 510 && modelid != 509) { 

	if(PlayerInfo[playerid][pColor] == 0) {
	PlayerTextDrawBoxColor(playerid, speedo_TD_0[playerid], TD_COLOR_DEFAULT);
	}
	if(PlayerInfo[playerid][pColor] == 1) {
	PlayerTextDrawBoxColor(playerid, speedo_TD_0[playerid], TD_COLOR_GREEN);
	}
	if(PlayerInfo[playerid][pColor] == 2) {
	PlayerTextDrawBoxColor(playerid, speedo_TD_0[playerid], TD_COLOR_BLACK);
	}
	if(PlayerInfo[playerid][pColor] == 3) {
	PlayerTextDrawBoxColor(playerid, speedo_TD_0[playerid], TD_COLOR_ORANGE);
	}

	PlayerTextDrawShow(playerid, 	speedo_TD_0[playerid]);	
	PlayerTextDrawShow(playerid, 	speedo_TD_1[playerid]);
	if(IsPlayerInVehicle(playerid, caridhouse[playerid])) { PlayerTextDrawShow(playerid,	speedo_TD_2[playerid]); }
	PlayerTextDrawShow(playerid,	speedo_TD_3[playerid]);
	}
	return 1;
}

stock hide_speedo(playerid) {
	PlayerTextDrawHide(playerid, 	speedo_TD_0[playerid]);	
	PlayerTextDrawHide(playerid, 	speedo_TD_1[playerid]);
	PlayerTextDrawHide(playerid,	speedo_TD_2[playerid]);
	PlayerTextDrawHide(playerid,	speedo_TD_3[playerid]);	
	return 1;
}

stock update_speedo(playerid, speed) {
	if(0 <= speed <= 1) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"");
    } else  if(2 <= speed <= 10) {
		PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"I");
    } else  if(11 <= speed <= 20) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"II");
    } else  if(21 <= speed <= 30) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"III");
    } else  if(31 <= speed <= 45) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIII");
    } else  if(46 <= speed <= 47) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIIII");
    } else  if(48 <= speed <= 59) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIIIII");
    } else  if(60 <= speed <= 75) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIIIIII");
    } else  if(76 <= speed <= 90) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIIIIIII");
    } else  if(91 <= speed <= 100) {
		PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIIIIIIII");
    } else  if(101 <= speed <= 105) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIIIIIIIII");
    } else  if(106 <= speed <= 110) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIIIIIIIIII");
    } else  if(111 <= speed <= 115) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIIIIIIIIIII");
    } else  if(116 <= speed <= 120) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIIIIIIIIIIII");
    } else  if(121 <= speed <= 130) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIIIIIIIIIIIII");
    } else  if(131 <= speed <= 144) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIIIIIIIIIIIIII");
    } else  if(145 <= speed <= 155) {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid],"IIIIIIIIIIIIIIII");
    } else {
    	PlayerTextDrawSetString(playerid,speedo_TD_1[playerid], "IIIIIIIIIIIIIIIII");
	}
	return 1;
}