#if defined fraction_system_included
	#endinput
#endif

#define fraction_system_included

#include <YSI_Coding\y_hooks>

#define MSG_START_JOB_DAY 	""COLOR_WHITE"Необходимо начать рабочий день на "COLOR_GREEN"базе организации"

//#include <../src/player/wanted_system.pwn>


#define MAX_FRACTION 						(13) // Максимальное кол-во организаций
#define MAX_FRACTION_TITLE 					(14) // Максимальная длина названия организации

enum 
	Fraction: {
		FRACTION_NONE = 0,
		FRACTION_LSPD, // 1
		FRACTION_GROOVE, // 2
		FRACTION_BALLAS, // 3
		FRACTION_VAGOS, // 4
		FRACTION_RIFA, // 5
		FRACTION_AZTECAS,  // 6
		FRACTION_RUSSIAN_MAFIA, // 7
		FRACTION_TRIADA, // 8
		FRACTION_DN_BOYS,  // 9
		FRACTION_ARMY, // 10
		FRACTION_FBI, // 11
		FRACTION_GOVERMENT, // 12
		FRACTION_NEWS // 12
	};

new const 
	FractionTitle[MAX_FRACTION][MAX_FRACTION_TITLE] = {
		"LSPD", // 1
		"Grove Street", // 2
		"Ballas Gang", // 3
		"Vagos Gang", // 4
		"Rifa Gang", // 5
		"Aztecas Gang", // 6
		"Русская Мафия", // 7
		"Triads", // 8
		"Da Nang Boys", // 9
		"Армия", // 10
		"FBI", // 11
		"Правительство", // 12
		"San News" // 12
	};

new FractionColor[][9] =
{
	"{E6E6E6}", // FRACTION_NONE
	"{2641FE}", // FRACTION_LSPD
	"{00D900}", // FRACTION_GROOVE
	"{D900D3}", // FRACTION_BALLAS
	"{FFC801}", // FRACTION_VAGOS
	"{6666ff}", // FRACTION_RIFA
	"{01FCFF}", // FRACTION_AZTECAS
	"{4d4d4d}", // FRACTION_RUSSIAN_MAFIA
	"{660000}", // FRACTION_TRIADA
	"{FFCC33}", // FRACTION_DN_BOYS
	"{336600}", // FRACTION_ARMY
	"{1a1a1a}", // FRACTION_FBI
	"{336699}", // FRACTION_GOVERMENT
	"{FFAF00}" // FRACTION_NEWS
};

new 
	Fraction: player_fraction[MAX_PLAYERS char];

forward Fraction_OnPlayerConnect(playerid);
public Fraction_OnPlayerConnect(playerid) {
	return RemovePlayerFraction(playerid);
}

forward Fraction_OnPlayerDisconnect(playerid, reason);
public Fraction_OnPlayerDisconnect(playerid, reason) {
	return RemovePlayerFraction(playerid);
}

stock SetPlayerFraction(playerid, Fraction:sfractionid, bool:isSave = false) {
	player_fraction{playerid} = sfractionid;

	// if(fractionid >= FRACTION_GROOVE && fractionid <= FRACTION_AZTECAS) {
	// 	TogglePlayerDynamicArea(playerid, army_zone, true);
	// }
	StartPlayerJobDay(playerid, false);
	if(isSave == true) {
		static string[55 + 2 + MAX_LENGTH_ACCOUNT_ID + 1];
		
		mysql_format(database,
			string, sizeof(string),
			"UPDATE players SET `Job` = '%i' WHERE `ID` = %i LIMIT 1",
				_:sfractionid,
				GetPlayerAccountID(playerid)
		);
		mysql_pquery(database, string);
	}
	return 1;
}

stock Fraction:GetPlayerFraction(playerid) {
	return player_fraction{playerid};
}

stock LeaderPlayerFraction(playerid) {
	new crutch = _:player_fraction{playerid};
	crutch--;
	return crutch;
}

stock GetPlayerFractionInt(playerid) { 
	return _:player_fraction{playerid}; 
}


stock RemovePlayerFraction(playerid, bool:isSave = false) {
	// new 
	// 	Fraction: fractionid = GetPlayerFraction(playerid);

	// if(fractionid >= FRACTION_GROOVE && fractionid <= FRACTION_AZTECAS) {
	// 	TogglePlayerDynamicArea(playerid, army_zone, false);
	// }

	if(GetPlayerFraction(playerid) != FRACTION_NONE) {
		SetPlayerFraction(playerid, FRACTION_NONE, isSave);
		return true;
	} else {
		return false;
	}
}

// Начало/конец рабочего дня
enum E_PICKUP_START_JOB_DAY
{
	Float: E_X,
	Float: E_Y,
	Float: E_Z,
	E_PICKUP,
	E_AREA
};

new PickupStartJobDay[][E_PICKUP_START_JOB_DAY] = 
{
	{257.779400, 76.9935000, 1003.6406, INVALID_STREAMER_ID, INVALID_STREAMER_ID},
	{2493.04760, -1695.0397, 1014.7493, INVALID_STREAMER_ID, INVALID_STREAMER_ID},
	{2742.56540, -1777.9792, 25.503100, INVALID_STREAMER_ID, INVALID_STREAMER_ID},
	{2692.62790, -1570.5984, 20.039500, INVALID_STREAMER_ID, INVALID_STREAMER_ID},
	{2156.67650, -1776.2240, 13.786700, INVALID_STREAMER_ID, INVALID_STREAMER_ID},
	{1678.11880, -2058.7026, 14.214200, INVALID_STREAMER_ID, INVALID_STREAMER_ID},
	{1089.06340, 1559.81950, 5.9481000, INVALID_STREAMER_ID, INVALID_STREAMER_ID},
	{-2262.3445, 471.266600, 43.807600, INVALID_STREAMER_ID, INVALID_STREAMER_ID},
	{-1537.8932, 1141.65930, 7.2198000, INVALID_STREAMER_ID, INVALID_STREAMER_ID},
	{156.573300, 1447.89610, 10.614400, INVALID_STREAMER_ID, INVALID_STREAMER_ID},
	{-2461.9548, 539.538700, 432.67410, INVALID_STREAMER_ID, INVALID_STREAMER_ID},
	{1491.74980, -1772.5601, 485.08980, INVALID_STREAMER_ID, INVALID_STREAMER_ID},
	{922.735300, -1673.9144, 1349.5969, INVALID_STREAMER_ID, INVALID_STREAMER_ID}
};

new bool: IsPlayerStartJobDay[MAX_PLAYERS] = {true, ...};

hook OnDataBaseConnect()
{
	for(new i = 0; i < sizeof(PickupStartJobDay); i++)
	{
		PickupStartJobDay[i][E_PICKUP] = CreateDynamicPickup(1275, 23, PickupStartJobDay[i][E_X], PickupStartJobDay[i][E_Y], PickupStartJobDay[i][E_Z]);
		PickupStartJobDay[i][E_AREA] = CreateDynamicSphere(PickupStartJobDay[i][E_X], PickupStartJobDay[i][E_Y], PickupStartJobDay[i][E_Z], 1.00);

		CreateDynamic3DTextLabel(!""COLOR_WHITE"Гардероб\n("COLOR_GREEN"начало"COLOR_WHITE"/"COLOR_ORANGE"завершение"COLOR_WHITE" рабочего дня)", -1, PickupStartJobDay[i][E_X], PickupStartJobDay[i][E_Y], PickupStartJobDay[i][E_Z] + 1.00,
			MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, MAX_DISTANCE_VISIBLE
		);
	}
}

hook OnPlayerConnect(playerid)
{
	IsPlayerStartJobDay[playerid] = true;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason 

	IsPlayerStartJobDay[playerid] = true;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerPickUpDynPickup(playerid, pickupid)
{
	for(new i = 0; i < sizeof(PickupStartJobDay); i++)
	{
		if(PickupStartJobDay[i][E_PICKUP] == pickupid)
		{
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	for(new i = 0; i < sizeof(PickupStartJobDay); i++)
	{
		if(PickupStartJobDay[i][E_AREA] == areaid)
		{
			if(GetPlayerJobDayStatus(playerid) == true)
			{
				StopPlayerJobDay(playerid);
			}
			else
			{
				StartPlayerJobDay(playerid);
			}
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

stock StartPlayerJobDay(const playerid, const bool:show_message = true)
{
	IsPlayerStartJobDay[playerid] = true;
	if(show_message == true)
	{	
		SendClientMessage(playerid, -1, ""COLOR_WHITE"Вы успешно начали свой "COLOR_GREEN"рабочий день");
		ShowAction(playerid, "начал(а) рабочий день");
	}
	
	CBackSkin(playerid);
	SetColorName(playerid);
}

stock StopPlayerJobDay(const playerid)
{
	IsPlayerStartJobDay[playerid] = false;
	SendClientMessage(playerid, -1, ""COLOR_WHITE"Ваш рабочий день "COLOR_GREEN"окончен");

	CBackSkin(playerid);
	SetColorName(playerid);

	ShowAction(playerid, "закончил(а) рабочий день");
}

stock GetPlayerJobDayStatus(const playerid)
{
	return IsPlayerStartJobDay[playerid];
}

