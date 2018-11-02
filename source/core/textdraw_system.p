#if defined _textdraw_system_included
	#endinput
#endif
#define _textdraw_system_included

#define TD_COLOR_DEFAULT 0xf3505aFF
#define TD_COLOR_GREEN 0x1dac6dFF
#define TD_COLOR_BLACK 0x000000FF


new PlayerText:server_logo_0[MAX_PLAYERS];
new PlayerText:server_logo_1[MAX_PLAYERS];
new PlayerText:server_logo_2[MAX_PLAYERS];
new PlayerText:server_logo_3[MAX_PLAYERS];

hook OnPlayerAuthorization(playerid) {

	create_logo_textdraws(playerid);

	return 1;
}

hook OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{

	CMD:selectcolor(playerid, params[])
	{
		return SPD(playerid, dSelectColor, DIALOG_STYLE_LIST, "Выберите цвет оформления", "1. Красный\n2. Зеленый\n3. Черный", "Выбрать", "Отмена")	
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(GetPVarInt(playerid,"DialogID") != dialogid) return 1;
	DeletePVar(playerid, "DialogID");
	switch(dialogid)
	{
    case dSelectColor: {
	if(!response) return callcmd::mn(playerid,"\0");
	if(response) {
		switch(listitem) {
			case 0: {
				if(PlayerInfo[playerid][pColor] == 0) callcmd::selectcolor(playerid,"\0");
				PlayerInfo[playerid][pColor] = 0;
				destroy_logo_textdraws(playerid);
				create_logo_textdraws(playerid);
			}
			case 1: {
				if(PlayerInfo[playerid][pColor] == 1) callcmd::selectcolor(playerid,"\0");
				PlayerInfo[playerid][pColor] = 1;
				destroy_logo_textdraws(playerid);
				create_logo_textdraws(playerid);
			}
			case 2: {
				if(PlayerInfo[playerid][pColor] == 2) callcmd::selectcolor(playerid,"\0");
				PlayerInfo[playerid][pColor] = 2;
				destroy_logo_textdraws(playerid);
				create_logo_textdraws(playerid);
			}
    	}
	}
	return 1;
}


hook OnPlayerDisconnect(playerid, reason) {

	destroy_logo_textdraws(playerid);

	return 1;
}

stock create_logo_textdraws(playerid) {

	new td_color[10];

	switch(PlayerInfo[playerid][pColor]) {
		case 0: td_color = TD_COLOR_DEFAULT;
		case 1: td_color = TD_COLOR_GREEN;
		case 2: td_color = TD_COLOR_BLACK;
	}

	server_logo_0[playerid] = CreatePlayerTextDraw(playerid, 541.666931, 5.599995, "CHANCE");
	PlayerTextDrawLetterSize(playerid, server_logo_0[playerid], 0.340333, 1.398398);
	PlayerTextDrawAlignment(playerid, server_logo_0[playerid], 1);
	PlayerTextDrawColor(playerid, server_logo_0[playerid], td_color);
	PlayerTextDrawSetShadow(playerid, server_logo_0[playerid], 0);
	PlayerTextDrawSetOutline(playerid, server_logo_0[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, server_logo_0[playerid], 51);
	PlayerTextDrawFont(playerid, server_logo_0[playerid], 1);
	PlayerTextDrawSetProportional(playerid, server_logo_0[playerid], 1);

	server_logo_1[playerid] = CreatePlayerTextDraw(playerid, 592.666870, 9.713334, "usebox");
	PlayerTextDrawLetterSize(playerid, server_logo_1[playerid], 0.000000, 0.642592);
	PlayerTextDrawTextSize(playerid, server_logo_1[playerid], 582.333374, 0.000000);
	PlayerTextDrawAlignment(playerid, server_logo_1[playerid], 1);
	//PlayerTextDrawColor(playerid, server_logo_1[playerid], -16763990);
	PlayerTextDrawUseBox(playerid, server_logo_1[playerid], true);
	PlayerTextDrawBoxColor(playerid, server_logo_1[playerid], td_color);
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

	TextDrawShowForPlayer(playerid, server_logo_1[playerid]);
	TextDrawShowForPlayer(playerid,	server_logo_2[playerid]);
	TextDrawShowForPlayer(playerid,	server_logo_3[playerid]);


	return 1;
}

stock destroy_logo_textdraws(playerid) {

	TextDrawHideForPlayer(playerid, server_logo_1[playerid]);
	TextDrawHideForPlayer(playerid,	server_logo_2[playerid]);
	TextDrawHideForPlayer(playerid,	server_logo_3[playerid]);

	PlayerTextDrawDestroy(playerid, server_logo_1[playerid]);
	PlayerTextDrawDestroy(playerid, server_logo_2[playerid]);
	PlayerTextDrawDestroy(playerid, server_logo_3[playerid]);

	return 1;
}