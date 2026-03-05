#if defined _race_included
	#endinput
#endif
#define _race_included

#define MAX_CHECKPOINT 10 // Значение 10 принимает, когда создает 10-ый чекпоинт, и блокирует создание новых
#define MAX_RACE_PLAYERS 4 // 5

new Float:pRaceCheckpoint[MAX_PLAYERS][MAX_CHECKPOINT][3];    //    Чекпоинты
new pCheckpointCounter[MAX_PLAYERS];    // Счетчик чекпоинтов
new pRaceInviteID[MAX_PLAYERS] = {INVALID_PLAYER_ID, ...};    //  ID создателя гонки
new bool:pOnRace[MAX_PLAYERS] = false;  // Проверяльщик
new pOnRaceCounter[MAX_PLAYERS]; // Счетчик собранных игроком чекпоинтов
new pRacePosition[MAX_PLAYERS]; // Счетчик позиции в гонке
new RacePlayers[MAX_PLAYERS];  // Счетчик игроков в гонке
new bool:pWatchRoad[MAX_PLAYERS] = false; // отвечает за /road
new IconsMass[MAX_PLAYERS][MAX_CHECKPOINT]; // Массив для ID иконок, для их "убийства"
new pTimerRace[MAX_PLAYERS] =  {INVALID_TIMER_ID, ...}; // Массив для хранения ID таймеров. На случай, если их придется "убить"(когда создатель гонки вводит /racestart)


stock race_Disconnect(playerid, reason)
{
	if(pRaceInviteID[playerid] != INVALID_PLAYER_ID)
	{
	    if(pRaceInviteID[playerid] == playerid && pOnRace[playerid] != true) // Если он создатель гонки и гонка не начата
	    {
	    	foreach(new i:Player)
	    	{
	    		if(pRaceInviteID[i]==playerid)
	    		{
	    			SendClientMessage(i,-1,""COLOR_RED"Создатель трассы вышел");
	    			pRaceInviteID[i] = INVALID_PLAYER_ID;
	    		}
	    	}
	    	for(new i = 0;i<=MAX_CHECKPOINT - 1;i++) // Чистка чекпоинтов
	    	{
	    		pRaceCheckpoint[playerid][i][0] = 0;
	    		pRaceCheckpoint[playerid][i][1] = 0;
	    		pRaceCheckpoint[playerid][i][2] = 0;
	    	}
	    	RacePlayers[playerid] = 0;
	    	pCheckpointCounter[playerid] = 0;
	    }
	    if(pRaceInviteID[playerid] == playerid && pOnRace[playerid] == true) // Если он создатель гонки и гонка начата
	    {
	    	foreach(new i:Player)
	    	{
	    		if(pRaceInviteID[i]==playerid)
	    		{
	    			SendClientMessage(i,-1,""COLOR_RED"Создатель трассы сдался");
	    		}
	    	}
	    	RacePlayers[playerid] -= 1;
	    }
	    if(pRaceInviteID[playerid] != INVALID_PLAYER_ID && pRaceInviteID[playerid] != playerid) // Если он участник гонки
	    {
	    	new name[24];
	    	new formated[255];
	    	GetPlayerName(playerid,name,sizeof(name));
	    	format(formated,sizeof(formated),""COLOR_RED"Игрок "COLOR_WHITE"%s [%d]"COLOR_RED" вышел",name,playerid);
	    	SendClientMessage(pRaceInviteID[playerid],-1,formated);
	    	RacePlayers[pRaceInviteID[playerid]] -= 1;
	    }
	    if(pWatchRoad[playerid] == true) 
	    {
	    	pTimerRace[playerid] = KillTimer(pTimerRace[playerid]); 
	    	@__IconsDelete(playerid);
	    	pWatchRoad[playerid] = false;
	    }
	    if(RacePlayers[pRaceInviteID[playerid]] == 0 && pOnRace[playerid] == true) // Если вышедший - последний из гонщиков
		{
			foreach(new i:Player)
			{
				if(pRaceInviteID[i] == pRaceInviteID[playerid]) 
				{
					SendClientMessage(i,-1,""COLOR_ORANGE"Гонка завершена!");
				    pRaceInviteID[i] = INVALID_PLAYER_ID;
				}
			}
		    for(new i = 0;i<=MAX_CHECKPOINT - 1;i++) // Чистка чекпоинтов
	        {
	        	pRaceCheckpoint[pRaceInviteID[playerid]][i][0] = 0;
	        	pRaceCheckpoint[pRaceInviteID[playerid]][i][1] = 0;
	        	pRaceCheckpoint[pRaceInviteID[playerid]][i][2] = 0;
	        }
	        pCheckpointCounter[playerid] = 0;
	    }
	    pRaceInviteID[playerid] = INVALID_PLAYER_ID;
	    pOnRace[playerid] = false;
	    DeletePVar(playerid,"racername"); // На всякий
	    pOnRaceCounter[playerid] = 0;
	}
	return 1;
}

stock race_Death(playerid, killerid, reason)
{
	if(pRaceInviteID[playerid] != INVALID_PLAYER_ID)
	{
		if(pOnRace[playerid] == true) DisablePlayerRaceCheckpoint(playerid);
		if(pRaceInviteID[playerid] == playerid && pOnRace[playerid] != true) // Если он создатель гонки и гонка не начата
	    {
	    	foreach(new i:Player)
	    	{
	    		if(pRaceInviteID[i]==playerid)
	    		{
	    			SendClientMessage(i,-1,""COLOR_RED"Создатель трассы погиб");
	    			pRaceInviteID[i] = INVALID_PLAYER_ID;
	    		}
	    	}
	    	for(new i = 0;i<=MAX_CHECKPOINT - 1;i++) // Чистка чекпоинтов
	    	{
	    		pRaceCheckpoint[playerid][i][0] = 0;
	    		pRaceCheckpoint[playerid][i][1] = 0;
	    		pRaceCheckpoint[playerid][i][2] = 0;
	    	}
	    	RacePlayers[playerid] = 0;
	    	pCheckpointCounter[playerid] = 0;
	    }
	    if(pRaceInviteID[playerid] == playerid && pOnRace[playerid] == true) // Если он создатель гонки и гонка начата
	    {
	    	foreach(new i:Player)
	    	{
	    		if(pRaceInviteID[i]==playerid)
	    		{
	    			SendClientMessage(i,-1,""COLOR_RED"Создатель трассы выбыл!");
	    		}
	    	}
	    	RacePlayers[playerid] -= 1;
	    }
	    if(pRaceInviteID[playerid] != INVALID_PLAYER_ID && pRaceInviteID[playerid] != playerid) // Если он участник гонки
	    {
	    	new name[24];
	    	new formated[255];
	    	GetPlayerName(playerid,name,sizeof(name));
	    	format(formated,sizeof(formated),""COLOR_ORANGE"Игрок "COLOR_WHITE"%s [%d]"COLOR_ORANGE" выбыл!",name,playerid);
	    	SendClientMessage(pRaceInviteID[playerid],-1,formated);
	    	RacePlayers[pRaceInviteID[playerid]] -= 1;
	    }
	    if(RacePlayers[pRaceInviteID[playerid]] == 0 && pOnRace[playerid] == true) // Если умерший - последний из гонщиков
		{
			foreach(new i:Player)
			{
				if(pRaceInviteID[i] == pRaceInviteID[playerid]) 
				{
					SendClientMessage(i,-1,""COLOR_ORANGE"Гонка завершена!");
				    pRaceInviteID[i] = INVALID_PLAYER_ID;
				}
			}
		    for(new i = 0;i<=MAX_CHECKPOINT - 1;i++) // Чистка чекпоинтов
	        {
	        	pRaceCheckpoint[pRaceInviteID[playerid]][i][0] = 0;
	        	pRaceCheckpoint[pRaceInviteID[playerid]][i][1] = 0;
	        	pRaceCheckpoint[pRaceInviteID[playerid]][i][2] = 0;
	        }
	        pCheckpointCounter[playerid] = 0;
	    }
	    SendClientMessage(playerid,-1,""COLOR_ORANGE"Вы более не участник гонки");
	    pRaceInviteID[playerid] = INVALID_PLAYER_ID;
	    pOnRace[playerid] = false;
	    DeletePVar(playerid,"racername"); // На всякий
	    pOnRaceCounter[playerid] = 0;
	}
	return 1;
}

stock race_Checkpoint(playerid)
{
	if(pOnRace[playerid] == true)
	{
		pOnRaceCounter[playerid] += 1;
		DisablePlayerRaceCheckpoint(playerid);
		if(pOnRaceCounter[playerid] == pCheckpointCounter[pRaceInviteID[playerid]] + 1) // Участник финишировал
		{
			new formated[250];
			RacePlayers[pRaceInviteID[playerid]] -= 1;
			pRacePosition[pRaceInviteID[playerid]] += 1;
			if(pRacePosition[pRaceInviteID[playerid]] == 1) // Первое место
			{
				new name[25];
				GetPlayerName(playerid,name,sizeof(name));
				format(formated,sizeof(formated),""COLOR_GREEN"Игрок "COLOR_WHITE"%s [%d] "COLOR_GREEN"занял первое место в гонке!",name,playerid);
				foreach(new i:Player)
				{
					if(pRaceInviteID[i] == pRaceInviteID[playerid]) SendClientMessage(i,-1,formated);
				}
			}
			if(pRacePosition[pRaceInviteID[playerid]] == 2) // Второе место
			{
				new name[25];
				GetPlayerName(playerid,name,sizeof(name));
				format(formated,sizeof(formated),""COLOR_GREEN"Игрок "COLOR_WHITE"%s [%d] "COLOR_GREEN"занял второе место в гонке!",name,playerid);
				foreach(new i:Player)
				{
					if(pRaceInviteID[i] == pRaceInviteID[playerid]) SendClientMessage(i,-1,formated);
				}
			}
			if(pRacePosition[pRaceInviteID[playerid]] == 3) // Третье место
			{
				new name[25];
				GetPlayerName(playerid,name,sizeof(name));
				format(formated,sizeof(formated),""COLOR_GREEN"Игрок "COLOR_WHITE"%s [%d] "COLOR_GREEN"занял третье место в гонке!",name,playerid);
				foreach(new i:Player)
				{
					if(pRaceInviteID[i] == pRaceInviteID[playerid]) SendClientMessage(i,-1,formated);
				}
			}
			if(RacePlayers[pRaceInviteID[playerid]] == 0) // Все участники финиширвоали
			{
				foreach(new i:Player)
				{
					if(pRaceInviteID[i] == pRaceInviteID[playerid]) 
					{
						SendClientMessage(i,-1,""COLOR_ORANGE"Гонка завершена!");
					    pRaceInviteID[i] = INVALID_PLAYER_ID;
					}
				}
			    for(new i = 0;i<=MAX_CHECKPOINT - 1;i++) // Чистка чекпоинтов
	    	    {
	    	    	pRaceCheckpoint[pRaceInviteID[playerid]][i][0] = 0;
	    	    	pRaceCheckpoint[pRaceInviteID[playerid]][i][1] = 0;
	    	    	pRaceCheckpoint[pRaceInviteID[playerid]][i][2] = 0;
	    	    }
			}
			pOnRace[playerid] = false;
			pOnRaceCounter[playerid] = 0;
		}
		if(pOnRaceCounter[playerid] == pCheckpointCounter[pRaceInviteID[playerid]]) // Следующий чекпоинт - финиш
		{
			SetPlayerRaceCheckpoint(playerid, 1,pRaceCheckpoint[pRaceInviteID[playerid]][pOnRaceCounter[playerid]][0], 
    	                                        pRaceCheckpoint[pRaceInviteID[playerid]][pOnRaceCounter[playerid]][1], 
    	                                        pRaceCheckpoint[pRaceInviteID[playerid]][pOnRaceCounter[playerid]][2], 
    	                                        0,
    	                                        0,
    	                                        0,
    	                                        5.0);
		}
		if(pOnRaceCounter[playerid] < pCheckpointCounter[pRaceInviteID[playerid]]) // Ни тот, ни другой случай
		{
			SetPlayerRaceCheckpoint(playerid, 0,pRaceCheckpoint[pRaceInviteID[playerid]][pOnRaceCounter[playerid]][0], 
    	                                        pRaceCheckpoint[pRaceInviteID[playerid]][pOnRaceCounter[playerid]][1], 
    	                                        pRaceCheckpoint[pRaceInviteID[playerid]][pOnRaceCounter[playerid]][2], 
    	                                        pRaceCheckpoint[pRaceInviteID[playerid]][pOnRaceCounter[playerid]+1][0],
    	                                        pRaceCheckpoint[pRaceInviteID[playerid]][pOnRaceCounter[playerid]+1][1],
    	                                        pRaceCheckpoint[pRaceInviteID[playerid]][pOnRaceCounter[playerid]+1][2],
    	                                        5.0);
		}
	}	
	return 1;
}

DialogCreate:race(playerid)
{
    Dialog_Open(playerid, Dialog:race, DIALOG_STYLE_INPUT,
                "Создание гонки",
                ""COLOR_ORANGE"1."#DIALOG_COLOR"Сбросить старый маршрут и создать старт\n\
                 "COLOR_ORANGE"2."#DIALOG_COLOR"Создать следующий чекпоинт\n\
                 "COLOR_ORANGE"3."#DIALOG_COLOR"Сбросить всех участников\n\
                 "COLOR_ORANGE"4."#DIALOG_COLOR"Информация и команды\n\
                 \n\
                 \\c"COLOR_ORANGE"Выберите пункт",
                 "Выбрать","Отмена");
}

DialogResponse:race(playerid, response, listitem, inputtext[])
{
	if (strval(inputtext) == 1) 
	{
		foreach(new i:Player)
	    {
	    	if(pRaceInviteID[i]==playerid)
	    	{
	    		SendClientMessage(i,-1,""COLOR_RED"Создатель трассы стер данные");
	    		pRaceInviteID[i] = INVALID_PLAYER_ID;
	    	}
	    }
	    for(new i = 0;i<=MAX_CHECKPOINT - 1;i++) // Чистка чекпоинтов
	    {
	    	pRaceCheckpoint[playerid][i][0] = 0;
	    	pRaceCheckpoint[playerid][i][1] = 0;
	    	pRaceCheckpoint[playerid][i][2] = 0;
	    }
		pCheckpointCounter[playerid] = 0;
		RacePlayers[playerid] = 1;
		pRaceInviteID[playerid] = playerid;
		GetPlayerPos(playerid
			,pRaceCheckpoint[playerid][0][0]
			,pRaceCheckpoint[playerid][0][1]
		    ,pRaceCheckpoint[playerid][0][2]);
		SendClientMessage(playerid,-1,""COLOR_GREEN"Старт создан."COLOR_LIGHTBLUE" Прежние данные стерты");
		return 1;
	}
	if (strval(inputtext) == 2) 
	{
		if(pRaceCheckpoint[playerid][0][0] == 0) return SendClientMessage(playerid,-1,""COLOR_RED"Создайте старт");
		if(IsPlayerInRangeOfPoint(playerid,35.0,pRaceCheckpoint[playerid][pCheckpointCounter[playerid]][0] 
			                                  ,pRaceCheckpoint[playerid][pCheckpointCounter[playerid]][1]
			                                  ,pRaceCheckpoint[playerid][pCheckpointCounter[playerid]][2])) return SendClientMessage(playerid,-1,""COLOR_RED"Расстояние между чекпоинтами должно быть больше");
		if(pCheckpointCounter[playerid] <9)
		{
		    new formatedtext[200];
		    GetPlayerPos(playerid
		        ,pRaceCheckpoint[playerid][pCheckpointCounter[playerid]+ 1][0]
	        	,pRaceCheckpoint[playerid][pCheckpointCounter[playerid]+ 1][1]
	            ,pRaceCheckpoint[playerid][pCheckpointCounter[playerid]+ 1][2]);
		    pCheckpointCounter[playerid] += 1;
		    format(formatedtext, sizeof(formatedtext),""COLOR_GREEN"Следующий чекпоинт создан."COLOR_WHITE"[%d]",pCheckpointCounter[playerid]+1);
	        SendClientMessage(playerid,-1,formatedtext);
	        return 1;
	    }
	    else
	    {
	    	return SendClientMessage(playerid,-1,""COLOR_RED"Создано максимальное количество чекпоинтов: "COLOR_ORANGE"10");
	    }
	}
	if (strval(inputtext) == 3) 
	{
		if (pRaceInviteID[playerid] != playerid) return SendClientMessage(playerid,-1,""COLOR_RED"Вы не создавали трассу");
		foreach(new i:Player)
		{	
			if(pRaceInviteID[i] == playerid)
			{
				SendClientMessage(i,-1,""COLOR_RED"Создатель трассы удалил всех участников");
				pRaceInviteID[i] = INVALID_PLAYER_ID;
			}
		}
		RacePlayers[playerid]=0;
	    SendClientMessage(playerid,-1,""COLOR_ORANGE"Вы успешно стерли всех участников");
	    pRaceInviteID[playerid]=playerid;
	    return 1;
	}
	if(strval(inputtext) == 4) 
	{
		return Dialog_Show(playerid, Dialog:raceinfo);
	}
	return 1;
}

DialogCreate:raceinfo(playerid)
{
	Dialog_Open(playerid, Dialog:raceinfo, DIALOG_STYLE_MSGBOX,
		        "Информация и команды",
		         "\\c"COLOR_ORANGE"Информация\n\
		          "#DIALOG_COLOR"Макс. количество чекпоинтов:"COLOR_WHITE"10\n\
		          "#DIALOG_COLOR"Макс. количество участников:"COLOR_WHITE"5\n\
		          \\c"COLOR_ORANGE"Команды\n\
		          "#DIALOG_COLOR"Пригласить игрока:"COLOR_WHITE"/inviterace <id>\n\
		          "#DIALOG_COLOR"Исключить игрока:"COLOR_WHITE"/uninviterace <id>\n\
		          "#DIALOG_COLOR"Покинуть гонку:"COLOR_WHITE"/leaverace\n\
		          "#DIALOG_COLOR"Просмотреть маршрут:"COLOR_WHITE"/road\n\
		          "#DIALOG_COLOR"Начать гонку:"COLOR_WHITE"/startrace",
		          "Назад","Выйти");
}

DialogResponse:raceinfo(playerid,response)
{
	if(response)
	{
	    return Dialog_Show(playerid, Dialog:race);
	}
    return 1;
}

DialogCreate:raceinvite(playerid)
{
	new formated[255];
	new name[24];
	GetPVarString(playerid,"racername",name,sizeof(name));
	format(formated,sizeof(formated),""COLOR_LIGHTBLUE"Игрок "COLOR_WHITE"%s "#DIALOG_COLOR"пригласил вас принять участие в гонке.", name);
	Dialog_Open(playerid,Dialog:raceinvite,DIALOG_STYLE_MSGBOX,
		"Приглашение в гонку",
		 formated,
		 "Принять","Отказать");
}

DialogResponse:raceinvite(playerid,response)
{
	if(response)
	{
		new invitedname[24];
		new formated01[255];
		pRaceInviteID[playerid] -= MAX_PLAYERS;
		RacePlayers[pRaceInviteID[playerid]] += 1;
		GetPlayerName(playerid,invitedname,sizeof(invitedname));
		format(formated01,sizeof(formated01),""COLOR_WHITE"%s [%d] "COLOR_LIGHTBLUE"принял ваше приглашение в гонку.",invitedname,playerid);
		SendClientMessage(pRaceInviteID[playerid],-1,formated01);
		SendClientMessage(playerid,-1,""COLOR_LIGHTBLUE"Вы приняли участие в гонке. Для просмотра маршрута введите: "COLOR_GREEN"/road");
		DeletePVar(playerid,"racername");
		RemovePlayerFromVehicle(playerid); // Чтобы игрок успел првоерить /road прежде чем создатель начнет гонку
		return 1;
	}
	new formated[255];
	new name[24];
	pRaceInviteID[playerid] -= MAX_PLAYERS;
	GetPlayerName(playerid,name,sizeof(name));
	format(formated,sizeof(formated),""COLOR_RED"Игрок "COLOR_WHITE"%s [%d] "COLOR_RED"отклонил приглашение в гонку",name,playerid);
    SendClientMessage(playerid,-1,""COLOR_RED"Приглашение отклонено");
    SendClientMessage(pRaceInviteID[playerid],-1,formated);
	DeletePVar(playerid,"racername");
	pRaceInviteID[playerid] = INVALID_PLAYER_ID;
    return 1;
}

CMD:race(playerid)
{ // Стоит добавить проверку на деморган и сидит ли игрок в тюрьме
	if(pRaceInviteID[playerid] != INVALID_PLAYER_ID)
    {	
		SendClientMessage(playerid,-1,""COLOR_RED"Вы уже являетесь участником гонки");
		SendClientMessage(playerid,-1,""COLOR_ORANGE"Выход из гонки:"COLOR_WHITE"/leaverace");
		return 1;
	}
	if(pOnRace[playerid] == true) return SendClientMessage(playerid,-1,""COLOR_RED"Гонка уже началась");

	Dialog_Show(playerid, Dialog:race);
    return 1;
}

CMD:inviterace(playerid,params[])
{
    if(sscanf(params,"d", params[0]))return SendClientMessage(playerid, -1, ""COLOR_RED"Используйте: "COLOR_ORANGE"/inviterace [id]");
    if(!IsPlayerConnected(strval(params[0]))) return SendClientMessage(playerid,-1,""COLOR_RED"Игрок не найден.");
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid,x,y,z);
    if(!IsPlayerInRangeOfPoint(strval(params[0]),5.0,x,y,z)) return SendClientMessage(playerid,-1,""COLOR_RED"Игрок слишком далеко.");
    if(RacePlayers[playerid] == 5) return SendClientMessage(playerid, -1, ""COLOR_RED"Максимальное кол-во участников: "COLOR_ORANGE"5");
    if(pRaceInviteID[strval(params[0])] != INVALID_PLAYER_ID)
    {	
    	SendClientMessage(playerid,-1,""COLOR_RED"Игрок уже является участником гонки"); 
        SendClientMessage(playerid,-1,""COLOR_ORANGE"Попросите его выйти из гонки командой:"COLOR_WHITE"/leaverace");
        return 1;
    }
    if(playerid == strval(params[0])) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете пригласить себя");
    if(pOnRace[playerid] == true) return SendClientMessage(playerid,-1, ""COLOR_RED"Гонка уже началась!");
   
    new racername[24];
    GetPlayerName(playerid,racername,sizeof(racername));
    SendClientMessage(playerid,-1,""COLOR_ORANGE"Приглашение отправлено");
    pRaceInviteID[strval(params[0])] = MAX_PLAYERS + playerid;
    SetPVarString(strval(params[0]),"racername",racername);
    Dialog_Show(strval(params[0]), Dialog:raceinvite);
    return 1;
}

CMD:uninviterace(playerid, params[0])
{
	if(sscanf(params,"d", params[0]))return SendClientMessage(playerid, -1, ""COLOR_RED"Используйте: "COLOR_ORANGE"/uninviterace [id]");
	if(!IsPlayerConnected(strval(params[0]))) return SendClientMessage(playerid,-1,""COLOR_RED"Игрок не найден");
	if(pRaceInviteID[playerid] != playerid) return SendClientMessage(playerid,-1,""COLOR_RED"Вы не создатель трассы");
	if(pRaceInviteID[(strval(params[0]))] != playerid) return SendClientMessage(playerid,-1,""COLOR_RED"Игрок не принимает участие в гонке");
	if(params[0] == pRaceInviteID[playerid]) return SendClientMessage(playerid,-1,""COLOR_RED"Вы не можете исключить себя");
	if(pOnRace[playerid] == true) return SendClientMessage(playerid,-1,""COLOR_RED"Гонка уже началась!");

	pRaceInviteID[strval(params[0])] = INVALID_PLAYER_ID;
	SendClientMessage(strval(params[0]),-1,""COLOR_RED"Вы были исключены из гонки");
	RacePlayers[playerid] -= 1;
	SendClientMessage(playerid,-1,""COLOR_ORANGE"Вы успешно исключили участника");
	return 1;
}

CMD:racestart(playerid)
{
	if(pRaceInviteID[playerid] == INVALID_PLAYER_ID) return 1;
	if(playerid != pRaceInviteID[playerid]) return SendClientMessage(playerid,-1,""COLOR_RED"Вы не создатель трассы");
    if(RacePlayers[playerid] < 1) return SendClientMessage(playerid,-1,""COLOR_RED"Минимальное количество участников: 2");
    if(pOnRace[playerid] == true) return SendClientMessage(playerid,-1,""COLOR_RED"Гонка уже началась!");
    foreach(new i:Player)
    {
    	if(pRaceInviteID[i] == playerid) 
    	{	
    		if(!IsPlayerInAnyVehicle(i)) return SendClientMessage(playerid,-1,""COLOR_RED"Кто-то из участников не сидит в машине");
     	}	
    }

    foreach(new i:Player)
    {
    	if(pRaceInviteID[i] == playerid)
    	{
    		pOnRaceCounter[i] = 0;
    		if(pWatchRoad[i] == true)
    		{
    			pTimerRace[playerid] = KillTimer(pTimerRace[playerid]); 
    			@__IconsDelete(i);
    		}
    		SendClientMessage(i, -1, ""COLOR_GREEN"Гонка начинается! "COLOR_ORANGE"Отсчет пошел");
    		pOnRace[i]= true;
    		SetPlayerRaceCheckpoint(i, 0, 
    			pRaceCheckpoint[playerid][0][0], 
    			pRaceCheckpoint[playerid][0][1], 
    			pRaceCheckpoint[playerid][0][2], 
    			pRaceCheckpoint[playerid][1][0],
    			pRaceCheckpoint[playerid][1][1],
    			pRaceCheckpoint[playerid][1][2],
    			5.0);
    		TogglePlayerControllable(i,0);
    		SetTimerEx("@__UpdateRaceCountdown", 1000, false, "ii", playerid, 6);
    	}
    }
    pRacePosition[playerid] = 0;
	return 1;
}


CMD:leaverace(playerid)
{
	if(pRaceInviteID[playerid] == playerid && RacePlayers[playerid] > 0) return SendClientMessage(playerid,-1,""COLOR_RED"В вашей гонке еще остались участники");
	if(pRaceInviteID[playerid] == INVALID_PLAYER_ID) return SendClientMessage(playerid,-1,""COLOR_RED"Вы не учавствуете в гонке");

	if(pOnRace[playerid] == true && pRaceInviteID[playerid] != INVALID_PLAYER_ID) // Если игрок выходит, а гонка уже начата
	{
		new formated[255], name[25];
		pOnRace[playerid] = false;
		GetPlayerName(playerid,name,sizeof(name));
		format(formated,sizeof(formated),""COLOR_ORANGE"Игрок "COLOR_WHITE"%s [%d] "COLOR_ORANGE"сдался!",name,playerid);
		RacePlayers[pRaceInviteID[playerid]] -= 1;
		foreach(new i:Player)
		{
			if(pRaceInviteID[i] == pRaceInviteID[playerid]) SendClientMessage(i,-1,formated);
		}
		if(RacePlayers[pRaceInviteID[playerid]] == 0) // Если вышедший - последний из гонщиков
		{
			foreach(new i:Player)
			{
				if(pRaceInviteID[i] == pRaceInviteID[playerid]) 
				{
					SendClientMessage(i,-1,""COLOR_ORANGE"Гонка завершена!");
				    pRaceInviteID[i] = INVALID_PLAYER_ID;
				}
			}
		    for(new i = 0;i<=MAX_CHECKPOINT - 1;i++) // Чистка чекпоинтов
	        {
	        	pRaceCheckpoint[pRaceInviteID[playerid]][i][0] = 0;
	        	pRaceCheckpoint[pRaceInviteID[playerid]][i][1] = 0;
	        	pRaceCheckpoint[pRaceInviteID[playerid]][i][2] = 0;
	        }
	    }
		pRaceInviteID[playerid] = INVALID_PLAYER_ID;
	}

	if(pRaceInviteID[playerid] != INVALID_PLAYER_ID && pOnRace[playerid] == false) // Если игрок выходит, но гонка еще не начата
	{
		new formated[255], name[25];
		pOnRace[playerid] = false;
		GetPlayerName(playerid,name,sizeof(name));
		format(formated,sizeof(formated),""COLOR_ORANGE"Игрок "COLOR_WHITE"%s [%d] "COLOR_ORANGE"вышел из гонки",name,playerid);
		SendClientMessage(pRaceInviteID[playerid],-1,formated);
		RacePlayers[pRaceInviteID[playerid]] -= 1;
		pRaceInviteID[playerid] = INVALID_PLAYER_ID;
	}
	return 1;
}

CMD:road(playerid)
{
	if(pRaceInviteID[playerid] == INVALID_PLAYER_ID) return 1;
	if(pOnRace[playerid] == true) return SendClientMessage(playerid,-1, ""COLOR_RED"Гонка уже началась");

    new formated[255], name[25];
	GetPlayerName(playerid,name,sizeof(name));
	format(formated,sizeof(formated),""COLOR_ORANGE"Игрок "COLOR_WHITE"%s [%d] "COLOR_ORANGE"начал просматривать маршрут",name,playerid);
	SendClientMessage(pRaceInviteID[playerid],-1,formated);
	pWatchRoad[playerid] = true;
	SendClientMessage(playerid,-1,""COLOR_LIGHTBLUE"Вы начали просматривать маршрут. Иконки исчезнут через "COLOR_ORANGE"20 "COLOR_LIGHTBLUE"секунд.");
	for(new i = 0; i<=pCheckpointCounter[pRaceInviteID[playerid]]; i++)
	{
	    IconsMass[pRaceInviteID[playerid]][i] = CreateDynamicMapIcon(pRaceCheckpoint[pRaceInviteID[playerid]][i][0],
	                                                                 pRaceCheckpoint[pRaceInviteID[playerid]][i][1],
	                                                                 pRaceCheckpoint[pRaceInviteID[playerid]][i][2], 56, 0, -1, -1, -1, 21000.0);
	}
	pTimerRace[playerid] = SetTimerEx("@__IconsDelete", 20000, false, "i", playerid);
	return 1;
}

@__IconsDelete(playerid); 
@__IconsDelete(playerid)
{
	pWatchRoad[playerid] = false;
	for(new i = 0; i<=pCheckpointCounter[pRaceInviteID[playerid]];i++)
	{
		DestroyDynamicMapIcon(IconsMass[pRaceInviteID[playerid]][i]);
	}
	SendClientMessage(playerid, -1, ""COLOR_ORANGE"Время закончилось, маршут стерт");
	return 1;
}

@__UpdateRaceCountdown(playerid, countdown);
@__UpdateRaceCountdown(playerid, countdown)
{
    if(--countdown <= 0)
    {
        foreach(new i:Player)
        {
            if(pRaceInviteID[i] == playerid)
            GameTextForPlayer(i, "GO!", 1000, 3);
            TogglePlayerControllable(i,1);
        }
        return 1;
    }
    else if(countdown <= 5)
    {
        new string[5];
        format(string, sizeof(string), "%d...", countdown);
        foreach(new i:Player)
        {
            if(pRaceInviteID[i] == playerid)
            GameTextForPlayer(i, string, 900, 3);
        }
    }
    SetTimerEx("@__UpdateRaceCountdown", 1000, false, "ii", playerid, countdown);
    return 1;
}