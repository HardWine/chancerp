// Максимальное количество читеров на админ-панельке
#if !defined MAX_CHEATER_PANELS
	#define MAX_CHEATER_PANELS 				(12)
#endif

new Text:CheatShow[MAX_CHEATER_PANELS];
new CheaterID[MAX_CHEATER_PANELS] = {INVALID_PLAYER_ID, ...};
new total_cheater = 0;

stock CreateCheaterPanel()
{
	new Float:DrawPos = 26.000000;
	for(new i = 0; i < sizeof(CheatShow); i++)
	{
		if(i > 0) DrawPos = DrawPos + 24.000;
		CheatShow[i] = TextDrawCreate(DrawPos, 430.000000, "_");
		TextDrawColor(CheatShow[i], 0x6de64eFF);
		TextDrawFont(CheatShow[i], 1);
		TextDrawSetOutline(CheatShow[i], 1);
		TextDrawLetterSize(CheatShow[i],0.3500,1.270);
	}
}

stock ShowPlayerCheaterPanel(const playerid)
{
	for(new i = 0; i < sizeof(CheatShow); i++) 
	{
		TextDrawShowForPlayer(playerid, CheatShow[i]);
	}
}

stock HidePlayerCheaterPanel(const playerid)
{
	for(new i = 0; i < sizeof(CheatShow); i++) 
	{
		TextDrawHideForPlayer(playerid, CheatShow[i]);
	}
}
stock AddPlayerCheaterPanel(playerid)
{
	for(new i = 0; i < sizeof(CheaterID); i++) 
	{
		if(CheaterID[i] == playerid)
		{
			return 1;
		}
	}

	new arrayID = total_cheater;

	CheaterID[arrayID] = playerid;
	format(small_string, sizeof(small_string), "%d", CheaterID[arrayID]);
	TextDrawSetString(CheatShow[arrayID],small_string);
	total_cheater = total_cheater + 1;
	
	if(total_cheater >= sizeof(CheatShow))
	{
		total_cheater = 0;
	}
	return 1;
}

stock DeletePlayerCheaterPanel(playerid)
{
	for(new i = 0; i < sizeof(CheaterID); i++)
	{
		if(CheaterID[i] == playerid)
		{
			CheaterID[i] = INVALID_PLAYER_ID;
			TextDrawSetString(CheatShow[i], "_");
		}
	}
}

CMD:add(playerid, params[])
{
	if(GetPlayerAdminLevel(playerid) == 0) return 0;
	new targetid;
	if(sscanf(params, "i", targetid))
	{
		SendClientMessage(playerid, -1, "/add [ID]");
		return 0;
	}

	if(targetid == -1)
	{
		for(new i = 0; i < sizeof(CheatShow); i++) 
		{
			AddPlayerCheaterPanel(random(999));
		}
	}
	else 
	{
		AddPlayerCheaterPanel(targetid);
	}
	return 1;
}

CMD:del(playerid, params[])
{
	if(GetPlayerAdminLevel(playerid) == 0) return 0;

	new targetid;
	if(sscanf(params, "i", targetid))
	{
		SendClientMessage(playerid, -1, "/del [ID]");
		return 0;
	}
	if(targetid == -1)
	{
		for(new i = 0; i < sizeof(CheatShow); i++) 
		{
			DeletePlayerCheaterPanel(CheaterID[i]);
		}
	}
	else 
	{
		DeletePlayerCheaterPanel(targetid);
	}
	return 1;
}