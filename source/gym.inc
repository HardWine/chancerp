#if defined fight_system_included
	#endinput
#endif

#define fight_system_included

#define STYLE_PRICE_BOXING			"5000"

#define GYM_CLOTHES_ICON_ID			1275

#define GYM_LS_WORLD				200
#define GYM_LS_INTERIOR				5

new gympickup;
new gymarea;

stock GYM() {

	gymarea = CreateDynamicRectangle(774.7201, -5.2578, 755.4206, 16.0327,
		GYM_LS_WORLD, GYM_LS_INTERIOR, INVALID_PLAYER_ID
	);
	gympickup = CreateDynamicPickup(GYM_CLOTHES_ICON_ID, 2, 756.4730,8.7694,1000.7007, 
		GYM_LS_WORLD, GYM_LS_INTERIOR, INVALID_PLAYER_ID, MAX_DISTANCE_VISIBLE
	);
	CreateDynamic3DTextLabel(!"Раздевалка", 0x00F5FFFF, 756.4730,8.7694,1000.7007 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GYM_LS_WORLD, GYM_LS_INTERIOR, -1, MAX_DISTANCE_VISIBLE
	);
}


DialogCreate:fight_box(playerid) {

		if(PlayerInfo[playerid][pFightMaster] > 0 && PlayerInfo[playerid][pFightStyle] == 0) {
			return StartTraining(playerid);
		}


		if(PlayerInfo[playerid][pFightMaster] == 0 && PlayerInfo[playerid][pFightStyle] == 0) {
			return Dialog_Open(playerid, Dialog:fight_box, DIALOG_STYLE_MSGBOX,
			""COLOR_BLUE"Спортзал Los Santos",
			""COLOR_WHITE"Привет, ты наверняка пришел сюда чтобы обучиться единоборствам?\n\
			Здесь мы учим самым базовым техникам и культуре Боксинга\n\
			После освоения Бокса ты сможешь обучиться Кик-Боксу в спортзале Лас-Вентурас",
			"Далее", "Закрыть");
		}
}

DialogResponse:fight_box(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 1;
	} else {
		Dialog_Show(playerid, Dialog:fight_box_2);
		return 1;
	}
}

DialogCreate:fight_box_2(playerid) {

		return Dialog_Open(playerid, Dialog:fight_box_2, DIALOG_STYLE_MSGBOX,
		""COLOR_BLUE"Спортзал Los Santos",
		""COLOR_WHITE"Курс обучения в нашем спортзале стоит "COLOR_GREEN""STYLE_PRICE_BOXING""COLOR_WHITE"\n\
		Платишь один раз а потом приходишь в любое время дня и ночи\n\
		Формой и перчатками мы обеспечиваем бесплатно. Ты согласен?",
		"Да" "Подумаю"
	);
}

DialogResponse:fight_box_2(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 1;
	} else {
		new price = strval(STYLE_PRICE_BOXING);
		if(CheckCash(playerid, ) == false) return 1;
		RemovePlayerEXP(playerid, price, "Обучение боксу");
		SendClientMessage(playerid, -1, ""COLOR_BLUE"Вы начали обучение боксу в спортзале "COLOR_WHITE"Лос-Сантос");
		StartTraining(playerid);
		PlayerInfo[playerid][pFightMaster] = 1;
		SetPlayerInt(playerid, "FightMaster", PlayerInfo[playerid][pFightMaster]);		
		return 1;
	}
}

stock StartTraining(playerid) {
		if(PlayerInfo[playerid][pSex] != 0) {
			SetPlayerSkin(playerid, 90);
		} else {
			new male_random = RandomEx(0,1);
			SetPlayerSkin(playerid, 80+male_random);
		}
		format(small_string, sizeof(small_string), "%s надел(а) форму и перчатки", PlayerInfo[playerid][pName]);
		ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);	
		return 1;
}

