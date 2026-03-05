#if defined cmd_gov_included
	#endinput
#endif

#define cmd_gov_included

#define MAX_VOTE_TIME_LIMIT 60 //Секунд  
#define MIN_POSITIVE_VOTES_PERCENTAGE 55.0

#define INVITE_ARMY_RANK 2
#define INVITE_LSPD_RANK 2
#define INVITE_GANG_RANK 2

new INVITATION_ARMY;

new gov_string_1[144];
new gov_string_2[144];
new gov_string_3[144];
new gov_string_4[144];
new gov_string_5[144];
new gov_string_6[144];

new
    uninviteFraction[12] = -1,
    uninviteTimer[12] = {INVALID_TIMER_ID, ...},
    uninviteTimerEnd = INVALID_TIMER_ID,
    uninvitePlayerID[12] = INVALID_PLAYER_ID;  



new gov_Status;
forward GOV_OnGameModeInit();
public GOV_OnGameModeInit() {
	gov_Status = 0;
	INVITATION_ARMY = 0;
	// тут лучше закрой глаза
	uninviteFraction[0] = -1;uninviteFraction[1] = -1;uninviteFraction[2] = -1;uninviteFraction[3] = -1;uninviteFraction[4] = -1;uninviteFraction[5] = -1;uninviteFraction[6] = -1;uninviteFraction[7] = -1;uninviteFraction[8] = -1;uninviteFraction[9] = -1;uninviteFraction[10] = -1;uninviteFraction[11] = -1;uninvitePlayerID[0] = INVALID_PLAYER_ID;uninvitePlayerID[1] = INVALID_PLAYER_ID;uninvitePlayerID[2] = INVALID_PLAYER_ID;uninvitePlayerID[3] = INVALID_PLAYER_ID;uninvitePlayerID[4] = INVALID_PLAYER_ID;uninvitePlayerID[5] = INVALID_PLAYER_ID;uninvitePlayerID[6] = INVALID_PLAYER_ID;uninvitePlayerID[7] = INVALID_PLAYER_ID;uninvitePlayerID[8] = INVALID_PLAYER_ID;uninvitePlayerID[9] = INVALID_PLAYER_ID;uninvitePlayerID[10] = INVALID_PLAYER_ID;uninvitePlayerID[11] = INVALID_PLAYER_ID;
}

CMD:gov(playerid,params[]) 
{
	new crutch = LeaderPlayerFraction(playerid);
	if(GetFractionLeader(crutch) == INVALID_ACCOUNT_ID) {
		if(PlayerInfo[playerid][pRank] < 9) return SendClientMessage(playerid, -1, ""COLOR_RED"Доступно только после достижения 9 ранга");
		if(gov_Status == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Сейчас происходит другое собеседованиеа");
		new Fraction: fractionid = GetPlayerFraction(playerid);
		
		if(fractionid == FRACTION_ARMY) { // Запуск призыва в Армию		
			
			if(!IsPlayerInRangeOfPoint(playerid, 30, 1168.6344,1363.5411,10.8203))
			if(GetPlayerJobDayStatus(playerid) == false)
			{
				return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
			} 
			return SendClientMessage(playerid, -1, !""COLOR_RED"Вы должны быть рядом с пунктом призыва {FFFFFF} (/gps - Другие места)");
			gov_Status = 1;
			SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Призыв", "{FFFFFF}Вы начали собеседование в вашу фракцию\nСоблюдайте РП во время всего процесса\n"COLOR_RED"Нарушение данных правил послужит причиной увольнения", "ОК", "Закрыть");
			format(gov_string_1, sizeof(gov_string_1), "{4ca136}%s %s: Уважаемые граждане штата San Andreas!", gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]], PlayerInfo[playerid][pName]);	
			SendClientMessageToAll(-1, gov_string_1);
			format(gov_string_2, sizeof(gov_string_2), "{4ca136}%s %s: В течение этого часа будет проходит призыв в ряды Армии 'Зона-51'", gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]], PlayerInfo[playerid][pName]);	
			SendClientMessageToAll(-1, gov_string_2);
			format(gov_string_3, sizeof(gov_string_3), "{4ca136}%s %s: Мы ждем всех желающих в призывном пункте Las Venturas{FFFFFF} (( /gps - Другие места ))", gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]], PlayerInfo[playerid][pName]);	
			SendClientMessageToAll(-1, gov_string_3);
			format(gov_string_4, sizeof(gov_string_4), "{4ca136}%s %s: Требования: Законопослушность и отсутствие вредных привычек", gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]], PlayerInfo[playerid][pName]);	
			SendClientMessageToAll(-1, gov_string_4);
			format(gov_string_5, sizeof(gov_string_5), "{4ca136}%s %s: Призыв в Армию 'Зона-51' был завершен", gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]], PlayerInfo[playerid][pName]);	
			format(gov_string_6, sizeof(gov_string_6), "{4ca136}%s %s: Призыв в Армию 'Зона-51' окончен. Руководство покинуло призывной пункт", gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]], PlayerInfo[playerid][pName]);	
			
			SetTimer("StopInvitation", 3600000, false);
			SetTimer("InviteAlert", 600000, false);
			SetSVarInt("alert_inv", -1);
			INVITATION_ARMY = 1;
	}
	}
	else {
	new Fraction: fractionid = GetPlayerFraction(playerid);	
	if(fractionid == FRACTION_LSPD || fractionid == FRACTION_ARMY || fractionid == FRACTION_FBI || fractionid == FRACTION_GOVERMENT) {
		if(PlayerInfo[playerid][pRank] < 9) return SendClientMessage(playerid, -1, ""COLOR_RED"Доступно только после достижения 9 ранга");
		if(GetPlayerJobDayStatus(playerid) == false)
		{
			return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
		}
	    if(!params[0]) return SendClientMessage(playerid, -1, !"Используйте: /gov [текст]");
	    if(strlen(params) > 80) {
	    	return SendClientMessage(playerid, -1, "Слишком длинное сообщение");
	    }
	    if(GetPVarInt(playerid,"AntiFloodGov") > gettime()){ SendClientMessage(playerid, -1, !""COLOR_RED"Пожалуйста не флудите"); return false; }
	   	SetPVarInt(playerid,"AntiFloodGov",gettime() + 5);
	    static string[32 + MAX_PLAYER_NAME + 1 + 80];

		format(string, sizeof(string), "[Гос. Новости] {2471A3}%s %s: %s", gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]],PlayerInfo[playerid][pName], params[0]);
		SendClientMessageToAll(-1, string);
	}
	}
	return 1;
}
CMD:invite(playerid,params[]) {
	new Fraction: fractionid = GetPlayerFraction(playerid);
	new crutch = LeaderPlayerFraction(playerid);
	if(GetFractionLeader(crutch) == INVALID_ACCOUNT_ID) {
		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid > FRACTION_LSPD) {
			if(GetPlayerJobDayStatus(playerid) == false)
			{
				return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
			}

			if(PlayerInfo[playerid][pRank] < 9) return SendClientMessage(playerid, -1, ""COLOR_RED"Доступно только после достижения 9 ранга");
			if(GetPVarInt(playerid,"InviteTime") > gettime()) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Подождите немного");
			if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Используйте: /invite [id игрока]");
			new Fraction: fractionid_invitation = GetPlayerFraction(params[0]);
			if(fractionid_invitation != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок уже во фракции");
			if(GetDistanceBetweenPlayerz(playerid, params[0], 6.00) != 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы слишком далеко от указанного игрока");

			PlayerInfo[params[0]][pRank] = INVITE_GANG_RANK; SetPlayerInt(params[0], "Rank", PlayerInfo[params[0]][pRank]);
			PlayerInfo[params[0]][pStatus] = 0; SetPlayerInt(params[0], "Status", PlayerInfo[params[0]][pStatus]);
			SPD(params[0], dKickMessage, DIALOG_STYLE_MSGBOX, "Банды", ""COLOR_BLUE"Данная справка по фракции доступна в любое время (/mm - Помощь - Фракции)\n\n"COLOR_ORANGE"Для вас открылись двери в криминальный мир.\nРанг за рангом вы испробуете на себе весь спектр криминальной деятельности.{FFFFFF}\n\n1 - 2 Ранг: Доставка наркотиков (/gps - Другие места - Притон)\n3 - 4 Ранг: Кража материалов с военной базы 'Зона-51'\n5 - 7 Ранг: Автоугон (/gps - Другие места - Автомойка)\n8 Ранг: Начало захвата территории (/capture)\n9 Ранг: Прием людей в банду\n10 Ранг: Запуск голосования за увольнение членов банды",
			"Закрыть","");
			SendClientMessage(params[0], -1, ""COLOR_GREEN"Вы были приняты в банду");
			SendClientMessage(params[0], -1, ""COLOR_GREEN"Для общения в чате банды используйте: {FFFFFF}/f и /fn");
			SetPlayerFraction(params[0], fractionid, true);
			SetColorName(params[0]);
			CBackSkin(params[0]);
			GivePlayerWeapon(params[0], 24, 150);
			GivePlayerWeapon(params[0], 31, 150);
			SetPlayerArmour(params[0], 100);
			UpdateSpawnInfo(params[0]);

			SetPVarInt(playerid,"InviteTime",gettime()+60);
			format(small_string, sizeof(small_string), "[F] {4ee6c7}%s %s: В нашей банде пополнение, %s", gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]], PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName]);
			SendFamilyMessage(fractionid, -1, small_string);		
		}
		if(fractionid == FRACTION_ARMY) {	
			if(PlayerInfo[playerid][pRank] < 9) return SendClientMessage(playerid, -1, ""COLOR_RED"Доступно только после достижения 9 ранга");
			if(GetPlayerJobDayStatus(playerid) == false)
			{
				return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
			}
			if(INVITATION_ARMY != 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Принимать игроков можно только во время призыва!");
			if(!IsPlayerInRangeOfPoint(playerid, 30, 1168.6344,1363.5411,10.8203)) 
			return SendClientMessage(playerid, -1, !""COLOR_RED"Вы должны быть в пункте призыва {FFFFFF} (/gps - Другие места)");
			if(GetPVarInt(playerid,"InviteTime") > gettime()) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Подождите немного");
			if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Используйте: /invite [id игрока]");
			new Fraction: fractionid_invitation = GetPlayerFraction(params[0]);
			if(fractionid_invitation != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок уже во фракции");
			if(GetDistanceBetweenPlayerz(playerid, params[0], 6.00) != 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы слишком далеко от указанного игрока");

			PlayerInfo[params[0]][pRank] = INVITE_ARMY_RANK; SetPlayerInt(params[0], "Rank", PlayerInfo[params[0]][pRank]);
			PlayerInfo[params[0]][pStatus] = 0; SetPlayerInt(params[0], "Status", PlayerInfo[params[0]][pStatus]);
			SPD(params[0], dKickMessage, DIALOG_STYLE_MSGBOX,"Армия",""COLOR_BLUE"Данная справка по фракции доступна в любое время (/mm - Помощь - Фракции){FFFFFF}\n\n1 - 2 Ранг: Вашей задачей будет патрулирование базы 'Зоны 51' (/patrol)\n3 - 5 Ранг: Для работы открывается оружейный завод (на территории Зоны)\n6 - 8 Ранг: Доставка военных грузов на  грузовике и вертолетах\n9 Ранг: Проведение официальных призывов (/gov и /invite)\n10 Ранг: Запуск голосования за увольнение служащих","Закрыть","");
			SendClientMessage(params[0], -1, ""COLOR_GREEN"Вы подписали контракт на срочную службу в армии");
			SendClientMessage(params[0], -1, ""COLOR_GREEN"Вам была выдана рация, используйте её для связи: {FFFFFF}/r и /rn");		
			SetPlayerFraction(params[0], FRACTION_ARMY, true);
			SetPlayerColor(params[0], ARMY_COLOR);
			CBackSkin(params[0]);
			GivePlayerWeapon(params[0], 24, 150);
			GivePlayerWeapon(params[0], 31, 150);
			SetPlayerArmour(params[0], 100);
			UpdateSpawnInfo(params[0]);
			SetPVarInt(playerid,"InviteTime",gettime()+60);
			SetPVarInt(playerid, "justinvited", 1);
			format(small_string, sizeof(small_string), "[R] {718aeb}%s %s: Принят новый рядовой %s", gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]], PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName]);
			SendFamilyMessage(fractionid, -1, small_string);		
			SendClientMessage(params[0], -1, ""COLOR_ORANGE"Ожидайте военный автобус. Он доставит вас в армию");	
			SetPlayerPos(params[0], 1164.7977,1341.9833,10.8125);
			SetCameraBehindPlayer(params[0]);
			SetPlayerFacingAngle(params[0], 180);	
		}
		if(fractionid == FRACTION_LSPD) {
			if(PlayerInfo[playerid][pRank] < 9) return SendClientMessage(playerid, -1, ""COLOR_RED"Доступно только после достижения 9 ранга");
			if(GetPlayerJobDayStatus(playerid) == false)
			{
				return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
			}
			if(!IsPlayerInRangeOfPoint(playerid, 30, 215.0767,76.3013,1005.0391)) 
			return SendClientMessage(playerid, -1, !""COLOR_RED"Вы должны быть в здании LSPD");
			if(GetPVarInt(playerid,"InviteTime") > gettime()) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Подождите немного");
			if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Используйте: /invite [id игрока]");
			new Fraction: fractionid_invitation = GetPlayerFraction(params[0]);
			if(fractionid_invitation == FRACTION_ARMY && PlayerInfo[params[0]][pRank] > 3) {
				if(GetDistanceBetweenPlayerz(playerid, params[0], 6.00) != 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы слишком далеко от указанного игрока");
				//if(fractionid_invitation != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок уже во фракции");
				PlayerInfo[params[0]][pRank] = INVITE_LSPD_RANK; SetPlayerInt(params[0], "Rank", PlayerInfo[params[0]][pRank]);
				PlayerInfo[params[0]][pStatus] = 0; SetPlayerInt(params[0], "Status", PlayerInfo[params[0]][pStatus]);
				SPD(params[0], dKickMessage, DIALOG_STYLE_MSGBOX,"Полиция",""COLOR_BLUE"Данная справка по фракции доступна в любое время (/mm - Помощь - Фракции)\n\n"COLOR_ORANGE"Став офицером полиции вашей задачей станет сохранение порядка в штате.\n\n{FFFFFF}1 - 2 Ранг: Патрулирование (/turnout) и проверка документов граждан\n3 - 4 Ранг: Арест\n\n"COLOR_RED"(функционал для 5-8 рангов в стадии разработки){FFFFFF}\n\n9 Ранг: Прием новых сотрудников (/invite)\n10 Ранг: Запуск голосования за увольнение","Закрыть","");
				SendClientMessage(params[0], -1, ""COLOR_GREEN"Вы устроились на работу в LSPD");
				SendClientMessage(params[0], -1, ""COLOR_GREEN"Вам была выдана рация, используйте её для связи: {FFFFFF}/r и /rn");		
				SetPlayerFraction(params[0], FRACTION_LSPD, true);
				SetPlayerColor(params[0], LSPD_COLOR);
				CBackSkin(params[0]);
				GivePlayerWeapon(params[0], 24, 150);
				GivePlayerWeapon(params[0], 31, 150);
				SetPlayerArmour(params[0], 100);
				UpdateSpawnInfo(params[0]);
				SetPVarInt(playerid,"InviteTime",gettime()+60);
				format(small_string, sizeof(small_string), "[R] {718aeb}%s %s: На службу был принят офицер %s", gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]], PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName]);
				SendFamilyMessage(fractionid, -1, small_string);		
			}
			else return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок должен быть служащим армии, минимум 4 ранга");
		}
	}
	else 
	{
		if(PlayerInfo[playerid][pRank] < 9) return SendClientMessage(playerid, -1, ""COLOR_RED"Доступно только после достижения 9 ранга");
		if(GetPlayerJobDayStatus(playerid) == false)
		{
			return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
		}
		if(GetPVarInt(playerid,"InviteTime") > gettime()) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Подождите немного");
		if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Используйте: /invite [id игрока]");
		new Fraction: fractionid_invitation = GetPlayerFraction(params[0]);
		if(fractionid_invitation != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок уже во фракции");
		if(GetDistanceBetweenPlayerz(playerid, params[0], 6.00) != 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы слишком далеко от указанного игрока");
		
		format(small_string, sizeof small_string, "{FFFFFF}%s приглашает вас вступить во фракцию %s", PlayerInfo[playerid][pName], GetFractionTitle(crutch));
		SPD(params[0], dInviteAnswer, DIALOG_STYLE_MSGBOX, "Приглашение во фракцию", small_string, "Принять", "Отклонить");
		SetPVarInt(params[0], "InviteID", crutch);

		SetPVarInt(playerid,"InviteTime",gettime()+60);
		format(small_string, sizeof small_string, ""COLOR_ORANGE"Вы предложили {FFFFFF}%s"COLOR_ORANGE" вступить в вашу фракцию", PlayerInfo[params[0]][pName]);
		SendClientMessage(playerid, -1, small_string);
	}
	return 1;
}
CMD:giverank(playerid, params[]) { 
	new fractionid = GetPlayerFractionInt(playerid);
	new crutch = LeaderPlayerFraction(playerid);
    if(fractionid == 0) return 1; 
    if(GetPlayerJobDayStatus(playerid) == false)
    {
    	return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
    }
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Используйте: /giverank [id игрока]");
    if(PlayerInfo[playerid][pRank] < 9) return SendClientMessage(playerid, -1, ""COLOR_RED"Функция доступна с 9 ранга");
    if(GetFractionLeader(crutch) == INVALID_ACCOUNT_ID) {
    	if(PlayerInfo[playerid][pUpRank] <= 0) return SendClientMessage(playerid, -1, ""COLOR_RED"Лимит повышений/понижений на сегодня превышен");
	}	
	if(PlayerInfo[playerid][pRank] < PlayerInfo[params[0]][pRank]) return 1;
	if(params[0] == playerid) return 1;
	if(GetPlayerFraction(params[0]) != GetPlayerFraction(playerid)) return 1;	

    if(GetFractionLeader(crutch) == INVALID_ACCOUNT_ID) {
    	if(PlayerInfo[params[0]][pRankGot] != 0) return SendClientMessage(playerid, -1, ""COLOR_RED"Данный игрок сегодня уже получал повышение");
    }
	
	new max_rank = PlayerInfo[playerid][pRank];
	max_rank --;
	if(PlayerInfo[params[0]][pRank] >= max_rank) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете дать ранг выше");

    PlayerInfo[params[0]][pRank] += 1; SetPlayerInt(params[0], "Rank", PlayerInfo[params[0]][pRank]);
    PlayerInfo[params[0]][pStatus] = 0; SetPlayerInt(params[0], "Status", PlayerInfo[params[0]][pStatus]);

    if(GetFractionLeader(crutch) == INVALID_ACCOUNT_ID) {

    	PlayerInfo[params[0]][pRankGot] = 1; SetPlayerInt(params[0], "RankGot", PlayerInfo[params[0]][pRankGot]);
    	PlayerInfo[playerid][pUpRank] -= 1; SetPlayerInt(params[0], "UpRank", PlayerInfo[playerid][pUpRank]);

		format(small_string, sizeof small_string, ""COLOR_GREEN"Вы повысили {FFFFFF}%s"COLOR_GREEN" до %d ранга. Осталось повышений/понижений: {FFFFFF}%d", PlayerInfo[params[0]][pName],PlayerInfo[params[0]][pRank],PlayerInfo[playerid][pUpRank]);    
    }
   	else format(small_string, sizeof small_string, ""COLOR_GREEN"Вы повысили {FFFFFF}%s"COLOR_GREEN" до %d ранга", PlayerInfo[params[0]][pName],PlayerInfo[params[0]][pRank]);
    SendClientMessage(playerid, -1, small_string);
    format(small_string, sizeof small_string, "{FFFFFF}%s"COLOR_GREEN" повысил вас до %d ранга, поздравляем!", PlayerInfo[playerid][pName],PlayerInfo[params[0]][pRank]);
    SendClientMessage(params[0], -1, small_string);
    CBackSkin(params[0]);
    return 1;
}
CMD:gunlock(playerid, params[]) { 
	new Fraction:fractionid = GetPlayerFraction(playerid);
	
	if(!IsACrime(playerid)) return 1;
	if(GetPlayerJobDayStatus(playerid) == false)
	{
		return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
	}
	new crutch = LeaderPlayerFraction(playerid);
	if(GetFractionLeader(crutch) == INVALID_ACCOUNT_ID) return 1;
    if(PlayerInfo[playerid][pRank] < 9) return SendClientMessage(playerid, -1, ""COLOR_RED"Функция доступна с 9 ранга");
    if(WStatus[_:fractionid] == 0) {
    	WStatus[_:fractionid] = 1;
    	SetWareInt(fractionid, "status", 1); 
		format(small_string, sizeof(small_string), ""COLOR_GREEN"%s %s открыл склад банды",gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]], PlayerInfo[playerid][pName]);
		SendFamilyMessage(fractionid, -1, small_string);
		UpdateGangEmblem(_:fractionid);
    }
    else {
    	WStatus[_:fractionid] = 0;
		SetWareInt(fractionid, "status", 0);

		format(small_string, sizeof(small_string), ""COLOR_RED"%s %s закрыл склад банды",gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]], PlayerInfo[playerid][pName]);
		SendFamilyMessage(fractionid, -1, small_string);
		UpdateGangEmblem(_:fractionid);
    }
    return 1;
}
CMD:warehouse(playerid, params[]) { 
	new Fraction:fractionid = GetPlayerFraction(playerid);
	
	if(!IsAGang(playerid)) return 1;
	if(GetPlayerJobDayStatus(playerid) == false)
	{
		return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
	}
	format(small_string, sizeof(small_string), ""COLOR_BLUE"Материалов на складе банды: {FFFFFF}%d ",Warehouse[_:fractionid]);
	SendClientMessage(playerid, -1, small_string);
    return 1;
}/*
CMD:gmap(playerid, params[]) { 
	new fractionid = GetPlayerFractionInt(playerid);
	
	if(!IsAGang(playerid)) return 1;
	new ownlands;
	for(new i = 0;i<=TOTALGZ;i++)
	{
		if(GZInfo[i][gFrak] == fractionid) ownlands++;
	}
	format(small_string, sizeof(small_string), ""COLOR_BLUE"Территорий под контролем: {FFFFFF}%d ",ownlands);
	SendClientMessage(playerid, -1, small_string);
    return 1;
}*/
CMD:takerank(playerid, params[]) { 
	new fractionid = GetPlayerFractionInt(playerid);
	new crutch = LeaderPlayerFraction(playerid);
    if(fractionid == 0) return 1; 
    if(GetPlayerJobDayStatus(playerid) == false)
    {
    	return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
    }
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Используйте: /takerank [id игрока]");
    if(PlayerInfo[playerid][pRank] < 9) return SendClientMessage(playerid, -1, ""COLOR_RED"Функция доступна с 9 ранга");
    if(GetFractionLeader(crutch) == INVALID_ACCOUNT_ID) {
    	if(PlayerInfo[playerid][pUpRank] <= 0) return SendClientMessage(playerid, -1, ""COLOR_RED"Лимит повышений/понижений на сегодня превышен");
	}

	if(PlayerInfo[playerid][pRank] < PlayerInfo[params[0]][pRank]) return 1;
	if(params[0] == playerid) return 1;
	if(GetPlayerFraction(params[0]) != GetPlayerFraction(playerid)) return 1;		


    if(GetFractionLeader(crutch) == INVALID_ACCOUNT_ID) {
    	if(PlayerInfo[params[0]][pRankGot] != 0) return SendClientMessage(playerid, -1, ""COLOR_RED"Данный игрок сегодня уже получал повышение");
    }

    if(PlayerInfo[params[0]][pRank] < 2) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете дать ранг ниже первого");
    PlayerInfo[params[0]][pRank] -= 1; SetPlayerInt(params[0], "Rank", PlayerInfo[params[0]][pRank]);
    PlayerInfo[params[0]][pStatus] = 0; SetPlayerInt(params[0], "Status", PlayerInfo[params[0]][pStatus]);

    if(GetFractionLeader(crutch) == INVALID_ACCOUNT_ID) {

       	PlayerInfo[params[0]][pRankGot] = 1; SetPlayerInt(params[0], "RankGot", PlayerInfo[params[0]][pRankGot]);
    	PlayerInfo[playerid][pUpRank] -= 1; SetPlayerInt(params[0], "UpRank", PlayerInfo[playerid][pUpRank]);

		format(small_string, sizeof small_string, ""COLOR_RED"Вы понизили {FFFFFF}%s"COLOR_RED" до %d ранга. Осталось повышений/понижений: {FFFFFF}%d", PlayerInfo[params[0]][pName],PlayerInfo[params[0]][pRank],PlayerInfo[playerid][pUpRank]);    
    }
   	else format(small_string, sizeof small_string, ""COLOR_RED"Вы понизили {FFFFFF}%s"COLOR_RED" до %d ранга", PlayerInfo[params[0]][pName],PlayerInfo[params[0]][pRank]);
    SendClientMessage(playerid, -1, small_string);
    format(small_string, sizeof small_string, "{FFFFFF}%s"COLOR_RED" понизил вас до %d ранга", PlayerInfo[playerid][pName],PlayerInfo[params[0]][pRank]);
    SendClientMessage(params[0], -1, small_string);
    CBackSkin(params[0]);
    return 1;
}
CMD:find(playerid) { 
	new Fraction: fractionid = GetPlayerFraction(playerid);
    if(fractionid == FRACTION_NONE) return 1; 
    new full; 
    huge_string[0] = EOS;
    huge_string = !"Никнейм (ID)\tРанг\tСтатус AFK\tРабочий день\n";
    foreach(new i : Player) { 
        if(!PlayerLogged{i}|| GetPlayerFraction(i) != fractionid) continue; 
        if(pl_afk_time[i] > 10) {
            format(small_string, sizeof(small_string), ""COLOR_GREEN"%s(%i)\t(%i) %s\t"COLOR_ORANGE"В AFK (%s)\t%s\n", PlayerInfo[i][pName], i, PlayerInfo[i][pRank], gFractionRankName_RU[_:fractionid-1][PlayerInfo[i][pRank]], Convert(pl_afk_time[i]), (GetPlayerJobDayStatus(i) == true) ? (""COLOR_GREEN"Начат") : (""COLOR_ORANGE"Окончен")); 
        	strcat(huge_string, small_string);
        } 
        else { 
            format(small_string, sizeof(small_string), ""COLOR_GREEN"%s(%i)\t(%i) %s\t"COLOR_GREEN"Не в AFK\t%s\n", PlayerInfo[i][pName], i, PlayerInfo[i][pRank], gFractionRankName_RU[_:fractionid-1][PlayerInfo[i][pRank]], (GetPlayerJobDayStatus(i) == true) ? (""COLOR_GREEN"Начат") : (""COLOR_ORANGE"Окончен")); 
       		strcat(huge_string, small_string);
        } 
        full++; 
    }  
	format(small_string,sizeof(small_string),""COLOR_BLUE"Онлайн фракции: "COLOR_ORANGE"%i человек\n",full);
	SPD(playerid, dKickMessage, DIALOG_STYLE_TABLIST_HEADERS, small_string, huge_string, "Закрыть", ""); 
  	return 1; 
}  

CMD:uninvite(playerid, params[]) {
	new fractionid = GetPlayerFractionInt(playerid);
	new crutch = LeaderPlayerFraction(playerid);
	if(GetFractionLeader(crutch) == INVALID_ACCOUNT_ID) {
		
		if(PlayerInfo[playerid][pRank] < 10) return SendClientMessage(playerid, -1, ""COLOR_RED"Доступно только после достижения 10 ранга");
		if(GetPlayerJobDayStatus(playerid) == false)
		{
			return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
		}
		if(uninviteFraction[_:fractionid-1] == -1) {
			if(sscanf(params,"ds[32]", params[0],params[1])) return SendClientMessage(playerid, -1, !"Используйте: /uninvite [id игрока] [причина]");
			if(uninvitePlayerID[_:fractionid-1] != INVALID_PLAYER_ID) {
	            SendClientMessage(playerid, -1, ""COLOR_RED"Голосование на увольнение уже запущено!");
	            return SendClientMessage(playerid, -1, ""COLOR_PEACH"Введите {FFFFFF}'/uninvite +',"COLOR_PEACH" чтобы проголосовать 'за' и {FFFFFF}'/uninvite -'"COLOR_PEACH", чтобы проголосовать 'против'");
	        }
	        if(INVALID_PLAYER_ID == params[0] || PlayerLogged{params[0]} == false) return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок не найден!");
	        if(playerid == params[0]) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете применить это на себя!");
	        if(fractionid != GetPlayerFractionInt(params[0])) return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок не состоит в вашей фракции");
	      	uninviteFraction[_:fractionid-1] = 1;
	        uninvitePlayerID[_:fractionid-1] = params[0];
	        SetPVarInt(uninvitePlayerID[_:fractionid-1], "AgreeVotesCount", 1);
	        DeletePVar(uninvitePlayerID[_:fractionid-1], "DisagreeVotesCount");
	        SetPVarString(uninvitePlayerID[_:fractionid-1], "VoteReason", params[1]);
	        for(new i = GetPlayerPoolSize(); i != -1; --i) DeletePVar(i, "HasVoted");
	        new string[256];
	        format(string, sizeof string, ""COLOR_PEACH"%s {FFFFFF}%s"COLOR_PEACH" начал голосование за увольнение {FFFFFF}%s"COLOR_PEACH". Причина: {FFFFFF}%s",
	        	 gFractionRankName_RU[_:fractionid-1][PlayerInfo[playerid][pRank]], PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName], params[1]);
	        SendLeadMessage(Fraction:fractionid, params[0], string);
			SendLeadMessage(Fraction:fractionid, params[0], ""COLOR_PEACH"Введите {FFFFFF}'/uninvite +',"COLOR_PEACH" чтобы проголосовать 'за' и {FFFFFF}'/uninvite -'"COLOR_PEACH", чтобы проголосовать 'против'");
	        new t = _:fractionid-1;
	       	uninviteTimer[t] = SetTimerEx("VoteTimer", MAX_VOTE_TIME_LIMIT * 1000, 0, "d", t);
	        SetPVarInt(playerid, "HasVoted", 1);
	        SetPVarString(params[0], "name_origin", PlayerInfo[playerid][pName]);
		}
		else {
		if(sscanf(params,"s[4]", params[0])) return SendClientMessage(playerid, -1, !"Используйте: /uninvite [+/-]");
		if(!strcmp(params[0], "+", true)) {
	        if(uninviteFraction[_:fractionid-1] == -1) return SendClientMessage(playerid, -1, ""COLOR_RED"Голосование на увольнение не запущено!");
	        if(playerid == uninvitePlayerID[_:fractionid-1]) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете голосовать за самого себя!");
	        if(GetPVarInt(playerid, "HasVoted")) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы уже проголосовали!");
	        SetPVarInt(uninvitePlayerID[_:fractionid-1], "AgreeVotesCount", GetPVarInt(uninvitePlayerID[_:fractionid-1], "AgreeVotesCount") + 1);
	        new gName[MAX_PLAYER_NAME], string[145];
	        GetPlayerName(uninvitePlayerID[_:fractionid-1], gName, sizeof gName);
	        format(string, sizeof string, ""COLOR_GREEN"Вы проголосовали {FFFFFF}'за'"COLOR_GREEN" увольнение игрока{FFFFFF} %s[%d]"COLOR_GREEN" (%d 'за' и %d 'против')", gName, uninvitePlayerID[_:fractionid-1], GetPVarInt(uninvitePlayerID[_:fractionid-1], "AgreeVotesCount"), GetPVarInt(uninvitePlayerID[_:fractionid-1], "DisagreeVotesCount"));
	        SendClientMessage(playerid, -1, string);
	        SetPVarInt(playerid, "HasVoted", 1);
	    	} else if(!strcmp(params[0], "-", true)) {
	        if(uninviteFraction[_:fractionid-1] == -1) return SendClientMessage(playerid, -1, ""COLOR_RED"Голосование на увольнение не запущено!");
	        if(playerid == uninvitePlayerID[_:fractionid-1]) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете голосовать за самого себя!");
	        if(GetPVarInt(playerid, "HasVoted")) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы уже проголосовали!");
	        SetPVarInt(uninvitePlayerID[_:fractionid-1], "DisagreeVotesCount", GetPVarInt(uninvitePlayerID[_:fractionid-1], "DisagreeVotesCount") + 1);
	        new gName[MAX_PLAYER_NAME], string[145];
	        GetPlayerName(uninvitePlayerID[_:fractionid-1], gName, sizeof gName);
	        format(string, sizeof string, ""COLOR_GREEN"Вы проголосовали {FFFFFF}'против'"COLOR_GREEN" увольнения игрока{FFFFFF} %s[%d]"COLOR_GREEN" (%d 'за' и %d 'против')", gName, uninvitePlayerID[_:fractionid-1], GetPVarInt(uninvitePlayerID[_:fractionid-1], "AgreeVotesCount"), GetPVarInt(uninvitePlayerID[_:fractionid-1], "DisagreeVotesCount"));
	        SendClientMessage(playerid, -1, string);
	        SetPVarInt(playerid, "HasVoted", 1);
	    }
		}
	}
	else {
		if(PlayerInfo[playerid][pRank] < 9) return SendClientMessage(playerid, -1, ""COLOR_RED"Доступно только после достижения 9 ранга");

		if(sscanf(params,"ds[32]", params[0],params[1])) return SendClientMessage(playerid, -1, !"Используйте: /uninvite [id игрока] [причина]");
		if(GetPlayerJobDayStatus(playerid) == false)
		{
			return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
		}
		if(PlayerInfo[playerid][pRank] < PlayerInfo[params[0]][pRank]) return 1;
		if(params[0] == playerid) return 1;
		if(GetPlayerFraction(params[0]) != GetPlayerFraction(playerid)) return 1;		

		SetPlayerArmour(params[0], 0);
	 	ResetPlayerWeapons(params[0]);
	 	RemovePlayerFraction(params[0], true);

		if(GetPVarInt(playerid, "onair_master")) {
			DeletePVar(playerid, "onair_master");
			onair = 0;
			SendFamilyMessage(FRACTION_NEWS, -1, ""COLOR_ORANGE"Ведущий прервал прямой эфир (был уволен)");
		}

     	format(big_string, sizeof(big_string),
        "{FFFFFF}Вы были уволены по решению %s.\n\n"COLOR_RED"Причина: {FFFFFF}%s\n"COLOR_RED"Ваш ранг: {FFFFFF}%d\n\nЕсли вы считаете что были нарушены правила,\nсделайте скриншот данного диалога и разместите\nжалобу на форуме проекта: talk.chancerp.ru",
        PlayerInfo[playerid][pName],
        params[1],
        PlayerInfo[params[0]][pRank]);
        SPD(params[0], dKickMessage, DIALOG_STYLE_MSGBOX, "Информация", big_string, "Закрыть", "");
        new string[156];
        format(string, sizeof(string), ""COLOR_RED"%s был уволен по решению %s. Причина: %s", 
        	PlayerInfo[params[0]][pName], PlayerInfo[playerid][pName], params[1]);
        SendFamilyMessage(GetPlayerFraction(playerid), -1, string);

	 	PlayerInfo[params[0]][pStatus] = 0;
	 	SetPlayerInt(params[0], "Status", PlayerInfo[params[0]][pStatus]);
	 	PlayerInfo[params[0]][pRank] = 0;
	 	SetPlayerInt(params[0], "Rank", PlayerInfo[params[0]][pRank]);

	 	CBackSkin(params[0]);
	}
    return 1;
}  
stock SendLeadMessage(Fraction:family, id = INVALID_PLAYER_ID, string[])
{
	foreach(new i: Player)
	{
		if(GetPlayerFraction(i) == family && PlayerInfo[i][pRank] == 10 && i != id)
	    {
			SendClientMessage(i, -1, string);
		}
	}
}
forward VoteTimer(fractionid);
public VoteTimer(fractionid)
{
    new
        AverageVotesCount = GetPVarInt(uninvitePlayerID[fractionid], "AgreeVotesCount") + GetPVarInt(uninvitePlayerID[fractionid], "DisagreeVotesCount"),
        PositiveVotesPercent = (GetPVarInt(uninvitePlayerID[fractionid], "AgreeVotesCount") / AverageVotesCount) * 100,
        string[145];
    if(PositiveVotesPercent >= MIN_POSITIVE_VOTES_PERCENTAGE && GetPVarInt(uninvitePlayerID[fractionid], "AgreeVotesCount") >= 3)
    {
        new reason[128],
        	origin[MAX_PLAYER_NAME+1];
        GetPVarString(uninvitePlayerID[fractionid], "VoteReason", reason, sizeof reason);
        GetPVarString(uninvitePlayerID[fractionid], "name_origin", origin, sizeof origin);

        format(big_string, sizeof(big_string),
        "{FFFFFF}Вы были уволены по решению руководства фракции.\n\n"COLOR_RED"Инициатор: {FFFFFF}%s\n"COLOR_RED"Причина: {FFFFFF}%s\n"COLOR_RED"Ваш ранг: {FFFFFF}%d (%d)\n\nЕсли вы не согласны с причиной увольнения,\nсделайте скриншот данного диалога и разместите\nжалобу на форуме проекта: talk.chancerp.ru",
        origin,
        reason,
        PlayerInfo[uninvitePlayerID[fractionid]][pRank],
        PlayerInfo[uninvitePlayerID[fractionid]][pStatus]);
        SPD(uninvitePlayerID[fractionid], dKickMessage, DIALOG_STYLE_MSGBOX, "Информация", big_string, "Закрыть", "");
        format(string, sizeof(string), ""COLOR_PEACH"Игрок {FFFFFF}%s[%d]"COLOR_PEACH" был уволен по решению руководства фракции. Причина: {FFFFFF}%s", 
        	PlayerInfo[uninvitePlayerID[fractionid]][pName], uninvitePlayerID[fractionid], reason);

        SendFamilyMessage(GetPlayerFraction(uninvitePlayerID[fractionid]), -1, string);
	 	SetPlayerColor(uninvitePlayerID[fractionid], CIVIL_COLOR);
	 	SetPlayerArmour(uninvitePlayerID[fractionid], 0);
	 	ResetPlayerWeapons(uninvitePlayerID[fractionid]);
	 	RemovePlayerFraction(uninvitePlayerID[fractionid], true);

	 	PlayerInfo[uninvitePlayerID[fractionid]][pStatus] = 0;
	 	SetPlayerInt(uninvitePlayerID[fractionid], "Status", PlayerInfo[uninvitePlayerID[fractionid]][pStatus]);
	 	PlayerInfo[uninvitePlayerID[fractionid]][pRank] = 0;
	 	SetPlayerInt(uninvitePlayerID[fractionid], "Rank", PlayerInfo[uninvitePlayerID[fractionid]][pRank]);

	 	CBackSkin(uninvitePlayerID[fractionid]);
        uninviteFraction[fractionid] = -1;
   		uninvitePlayerID[fractionid] = INVALID_PLAYER_ID;
    }
    else
    {
        format(string, sizeof string, ""COLOR_PEACH"Игрок {FFFFFF}%s[%d]"COLOR_PEACH" не был уволен. Не набралось достаточное количество голосов", PlayerInfo[uninvitePlayerID[fractionid]][pName],
         uninvitePlayerID[fractionid]);
        SendLeadMessage(GetPlayerFraction(uninvitePlayerID[fractionid]), uninvitePlayerID[fractionid], string);
        uninviteFraction[fractionid] = -1;
   		uninvitePlayerID[fractionid] = INVALID_PLAYER_ID;
    }
    return 1;
}  
forward StopInvitation();
public StopInvitation() {
	KillTimer(uninviteTimerEnd);
	gov_Status = 0;
	INVITATION_ARMY = 0;
	SendClientMessageToAll(-1, gov_string_6);
	return 1;
}

forward InviteAlert();
public InviteAlert() {
	new alert = GetSVarInt("alert_inv");
	alert++;
	SetSVarInt("alert_inv", alert);
	// Если идет собеседование в Армию и Бригадиров нет на призыве - закрываем набор.
	new inviter = 0;
	foreach(new i: Player) { 
		if(IsPlayerInDynamicArea(i, army_area)) {
			if(PlayerInfo[i][pRank] >= 9 && GetPlayerFraction(i) == FRACTION_ARMY)
			//Streamer_Update(i, STREAMER_TYPE_OBJECT); 
			inviter += 1;
		}
	}
	if(inviter == 0) {
		return StopInvitation();
	}

	switch(alert) {
		case 0..4: {
			SendClientMessageToAll(-1, gov_string_1);
			SendClientMessageToAll(-1, gov_string_2);
			SendClientMessageToAll(-1, gov_string_3);
			SendClientMessageToAll(-1, gov_string_4);
			if(GetSVarInt("alert_inv") == 4) return 1;
			SetTimer("InviteAlert", 600000, false);
		}
		default: return 1;
	}

	return 1;
}
CMD:su(playerid, params[]) {
	if(GetPlayerFraction(playerid) != FRACTION_LSPD && GetPlayerFraction(playerid) != FRACTION_FBI) return 1;
	if(PlayerInfo[playerid][pRank] < 5) return SendClientMessage(playerid, -1, ""COLOR_RED"Выдача розыска доступна с 5 ранга");

	new crutch = GetPlayerFractionInt(playerid);
	crutch--;

	if(GetFractionLeader(crutch) == INVALID_ACCOUNT_ID) return 1;
	if(GetPlayerFraction(playerid) != FRACTION_LSPD && GetPlayerFraction(playerid) != FRACTION_FBI) return 1;
	if(GetPlayerJobDayStatus(playerid) == false)
	{
		return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
	}
	if(PlayerInfo[playerid][pRank] < 5) return SendClientMessage(playerid, -1, ""COLOR_RED"Выдача розыска доступна с 5 ранга");
	if(sscanf(params,"ds[32]", params[0], params[1])) return SendClientMessage(playerid, -1, !"Используйте: /su [id игрока] [причина]");

	new level = PlayerInfo[params[0]][pWanted];

	if(level > 10800) return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок уже имеет максимальный уровень розыска");
	
	if(7201 <= level <= 10800) SetPlayerWantedLevel(params[0], 6); PlayerInfo[params[0]][pWanted] = 10801;
	if(5401 <= level <= 7200) SetPlayerWantedLevel(params[0], 5); PlayerInfo[params[0]][pWanted] = 7201;
	if(3601 <= level <= 5400) SetPlayerWantedLevel(params[0], 4); PlayerInfo[params[0]][pWanted] = 5401;
	if(301 <= level <= 3600) SetPlayerWantedLevel(params[0], 3); PlayerInfo[params[0]][pWanted] = 3601;
	if(0 < level <= 300) SetPlayerWantedLevel(params[0], 2); PlayerInfo[params[0]][pWanted] = 1800;
	if(level <= 0) SetPlayerWantedLevel(params[0], 1); PlayerInfo[params[0]][pWanted] = 900;

	SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
	if(GetPlayerFraction(playerid) == FRACTION_LSPD) {
		format(small_string, sizeof small_string, ""COLOR_RED"Полицейский %s повысил розыск %s (%d [+1]). Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName], PlayerInfo[params[0]][pWanted], params[1]);
		SendPoliceAlert(-1, small_string);

		format(small_string, sizeof small_string, ""COLOR_RED"Полицейский %s повысил Вам уровень розыска (%d [+1]). Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[params[0]][pWanted], params[1]);
		SendClientMessage(params[0], -1, small_string);
	}
	if(GetPlayerFraction(playerid) == FRACTION_FBI) {
		format(small_string, sizeof small_string, ""COLOR_RED"Агент %s повысил розыск %s (%d [+1]). Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName], PlayerInfo[params[0]][pWanted], params[1]);
		SendFBIAlert(-1, small_string);

		format(small_string, sizeof small_string, ""COLOR_RED"Агент %s повысил Вам уровень розыска (%d [+1]). Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[params[0]][pWanted], params[1]);
		SendClientMessage(params[0], -1, small_string);
	}
	return 1;	
}
CMD:radio(playerid, params[]) {
	if(GetPlayerFraction(playerid) != FRACTION_LSPD) return 1;
	if(PlayerInfo[playerid][pRank] < 3) return 1;
	if(GetPVarInt(playerid, "GT_LSPD") == 0) {
		SetPVarInt(playerid, "GT_LSPD", 1); 
		GameTextForPlayer(playerid, "~g~LSPD Channel", 2500, 4);
	}

	if(GetPVarInt(playerid, "GT_LSPD") == 1) SetPVarInt(playerid, "GT_LSPD", 0); GameTextForPlayer(playerid, "~r~Radio Off", 2500, 4);
	return 1;
}
CMD:auninvite(playerid, params[]) {
	if(sscanf(params,"ds[32]", params[0],params[1])) return SendClientMessage(playerid, -1, !"Используйте: /auninvite [id игрока] [причина]");
	if(GetPlayerLeader(params[0]) != -1) return 1;
	if(GetPlayerFraction(params[0]) == FRACTION_NONE) return 1;
	if(GetPlayerAdminLevel(playerid) < 5) return 1;

	SetPlayerArmour(params[0], 0);
 	ResetPlayerWeapons(params[0]);
 	RemovePlayerFraction(params[0], true);

 	format(big_string, sizeof(big_string),
    "{FFFFFF}Вы были уволены администратором %s.\n\n"COLOR_RED"Причина: {FFFFFF}%s\n"COLOR_RED"Ваш ранг: {FFFFFF}%d\n\nЕсли вы считаете что были нарушены правила,\nсделайте скриншот данного диалога и разместите\nжалобу на форуме проекта: talk.chancerp.ru",
    PlayerInfo[playerid][pName],
    params[1],
    PlayerInfo[params[0]][pRank]);
    SPD(params[0], dKickMessage, DIALOG_STYLE_MSGBOX, "Информация", big_string, "Закрыть", "");
    new string[156];
    format(string, sizeof(string), ""COLOR_RED"%s был уволен %s. Причина: %s", 
    	PlayerInfo[params[0]][pName], PlayerInfo[playerid][pName], params[1]);
    SendAdminMessage(-1, string);

 	PlayerInfo[params[0]][pStatus] = 0;
 	SetPlayerInt(params[0], "Status", PlayerInfo[params[0]][pStatus]);
 	PlayerInfo[params[0]][pRank] = 0;
 	SetPlayerInt(params[0], "Rank", PlayerInfo[params[0]][pRank]);

 	CBackSkin(params[0]);
 	return 1;
}
CMD:frisk(playerid, params[]) {
	if(GetPlayerFraction(playerid) != FRACTION_FBI) return 1;
	if(PlayerInfo[playerid][pRank] < 3) return 1;
	if(sscanf(params,"d", params[0])) return SendClientMessage(playerid, -1, !"Используйте: /frisk [id игрока]");
	if(GetPlayerJobDayStatus(playerid) == false)
	{
		return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
	}
	if(GetPVarInt(playerid, "frisk_target") != 0 && GetPVarInt(playerid, "frisk_count") != 0) return 1;

	new Fraction:target_fraction = GetPlayerFraction(params[0]);
	new Fraction:playerfraction = GetPlayerFraction(playerid);

	if(GetDistanceBetweenPlayerz(playerid, params[0], 1.0) != 1)
		return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок слишком далеко от вас");

	if(params[0] == playerid) return 1;

	if(pl_afk_time[params[0]] > 4) return 1; 

	if(target_fraction == playerfraction) {
	if(PlayerInfo[playerid][pRank] < PlayerInfo[params[0]][pRank])
		return SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете обыскать сотрудника старше вас по рангу!");
	}
	
	SetPVarInt(playerid, "frisk_target", params[0]);
	SetPVarInt(playerid, "frisk_count", 10);

	FriskTimer[playerid] = KillTimer(FriskTimer[playerid]);
	FriskTimer[playerid] = SetTimerEx("StartFrisk", 1250, false, "d", playerid);

	format(small_string, sizeof small_string, "%s начал(а) обыскивать %s", PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName]);
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
	return 1;
}
forward StartFrisk(playerid);
public StartFrisk(playerid) {
	new targetid = GetPVarInt(playerid, "frisk_target");
	new counter = GetPVarInt(playerid, "frisk_count");

	new count_string[50];

	SetPVarInt(targetid,"OffFrisk",gettime() + 10);
	switch(counter) {
		case 10: strins(count_string,"~y~IIIIIIIIII", 0);
		case 9: strins(count_string, "I~y~IIIIIIIII", 0); 
		case 8: strins(count_string, "II~y~IIIIIIII", 0);
		case 7: strins(count_string, "III~y~IIIIIII", 0);
		case 6: strins(count_string, "IIII~y~IIIIII", 0);
		case 5: strins(count_string, "IIIII~y~IIIII", 0);
		case 4: strins(count_string, "IIIIII~y~IIII", 0);
		case 3: strins(count_string, "IIIIIII~y~III", 0);
		case 2: strins(count_string, "IIIIIIII~y~II", 0);
		case 1: strins(count_string, "IIIIIIIII~y~I", 0);
		default: strins(count_string, "~g~SUCCEED", 0);
	}

	counter -= 1;

	if(counter < 0) {

		DeletePVar(playerid, "frisk_target");
		DeletePVar(playerid, "frisk_count");
		FriskTimer[playerid] = KillTimer(FriskTimer[playerid]);
		return Frisk(playerid, targetid);
	}
	SetPVarInt(playerid, "frisk_count", counter);
	
	new small_update_string[256];
	format(small_update_string, sizeof(small_update_string), "~b~FRISK~n~~w~%s", count_string);
	
	if(GetDistanceBetweenPlayerz(playerid, targetid, 2) != 1) {
		SendClientMessage(playerid, -1, ""COLOR_RED"Игрок не рядом с вами. Обыск закончен!");
		GameTextForPlayer(playerid, "~b~FRISK~n~~r~FAILED", 1100, 4);
		DeletePVar(playerid, "frisk_target");
		DeletePVar(playerid, "frisk_count");
		FriskTimer[playerid] = KillTimer(FriskTimer[playerid]);
		return 1;
	}

	GameTextForPlayer(playerid, small_update_string, 1350, 4);
	GameTextForPlayer(targetid, small_update_string, 1350, 4);

	FriskTimer[playerid] = KillTimer(FriskTimer[playerid]);
	return FriskTimer[playerid] = SetTimerEx("StartFrisk", 1250, false, "d", playerid);
}
stock Frisk(playerid, targetid) {
	AddPlayerAchievement(playerid, E_POCKETS_INSIDER);
	new Fraction:target_fraction = GetPlayerFraction(targetid);
	new bangs = PlayerInfo[targetid][pPetard] + PlayerInfo[targetid][pGrenade] + PlayerInfo[targetid][pDynamite];
	new drug = PlayerInfo[targetid][pDrugs] + PlayerInfo[targetid][pDrugsSell];
	new stuff = PlayerInfo[targetid][pStuff];
	if(stuff == 0 && drug == 0 && bangs == 0) {
	format(small_string, sizeof small_string,
	""COLOR_ORANGE"Вы обыскали %s\n{FFFFFF}Не было найдено ничего незаконного",
	PlayerInfo[targetid][pName]);
	SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Обыск завершен", small_string, "Ок", "Закрыть");
	if(stuff == 0 && drug == 0 && bangs == 0) return 1;
	}
	else {
	format(big_string, sizeof big_string,
	""COLOR_ORANGE"Вы обыскали %s\n\n\
	{FFFFFF}Найдено:\n\
	%d взрывных устройств\n\
	%d грамм наркотиков\n\
	%d украденных материалов\n\n\
	"COLOR_RED"Наркотические вещества и материалы будут изъяты и уничтожены",
	PlayerInfo[targetid][pName],
	bangs,
	drug,
	PlayerInfo[targetid][pStuff]);
	SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Обыск завершен", big_string, "Ок", "Закрыть");
	if(stuff == 0 && drug == 0 && bangs == 0) return 1;
	}


	if(target_fraction != FRACTION_LSPD && target_fraction != FRACTION_FBI && target_fraction != FRACTION_GOVERMENT && target_fraction != FRACTION_ARMY) {
	PlayerInfo[targetid][pPetard] = 0;
	PlayerInfo[targetid][pGrenade] = 0;
	PlayerInfo[targetid][pDynamite] = 0;
	SetPlayerInt(targetid, "Petard", PlayerInfo[targetid][pPetard]);
	SetPlayerInt(targetid, "Grenade", PlayerInfo[targetid][pGrenade]);
	SetPlayerInt(targetid, "Dynamite", PlayerInfo[targetid][pDynamite]);
	PlayerInfo[targetid][pDrugs] = 0;
	PlayerInfo[targetid][pDrugsSell] = 0;
	PlayerInfo[targetid][pStuff] = 0;
	SetPlayerInt(targetid, "Drugs", PlayerInfo[targetid][pDrugs]);
	SetPlayerInt(targetid, "DrugsSell", PlayerInfo[targetid][pDrugsSell]);
	SetPlayerInt(targetid, "Stuff", PlayerInfo[targetid][pStuff]);
	ResetPlayerWeapons(targetid);
	return SendClientMessage(targetid, -1, ""COLOR_RED"У вас изъяли все незаконные предметы (оружие, материалы, наркотики)");
	}
	PlayerInfo[targetid][pDrugs] = 0;
	PlayerInfo[targetid][pDrugsSell] = 0;
	PlayerInfo[targetid][pStuff] = 0;
	SetPlayerInt(targetid, "Drugs", PlayerInfo[targetid][pDrugs]);
	SetPlayerInt(targetid, "DrugsSell", PlayerInfo[targetid][pDrugsSell]);
	SetPlayerInt(targetid, "Stuff", PlayerInfo[targetid][pStuff]);
	SendClientMessage(targetid, -1, ""COLOR_RED"У вас изъяли все незаконные предметы (наркотики, материалы)");

	if(drug > 250) {
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы получаете 500 EXP за изъятие крупной партии наркотиков!");
		AddPlayerEXP(playerid, 500, "Изъятие наркотиков у игрока %s", PlayerInfo[targetid][pName]);
	}
		
	IncreaseStatus(playerid,10);
	return 1;
}