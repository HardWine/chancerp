#if defined call_system_included
	#endinput
#endif

#define call_system_included

#include <YSI_Coding\y_hooks>

enum 
	E_PLAYER_CALL {
		bool: E_PHONE_CALL,
		bool: E_CALL,
		E_CALLING_ID,
		bool: E_CALLING
	};

new 
	PlayerCall[MAX_PLAYERS][E_PLAYER_CALL];

new NULL_PlayerCall[E_PLAYER_CALL] = {
	/* E_CALLING */ 		false,
	/* E_CALLING */ 		false,
	/* E_CALLING_ID */ 		INVALID_PLAYER_ID,
	false
};

hook OnPlayerConnect(playerid) {
	PlayerCall[playerid] = NULL_PlayerCall;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason 
	callcmd::h(playerid, "");
	PlayerCall[playerid] = NULL_PlayerCall;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDeath(playerid, killerid, reason) {
	callcmd::h(playerid, "");
}

CMD:call(playerid, params[]) {
	new 
		targetid = INVALID_PLAYER_ID,
		target_number;

	if(PlayerInfo[playerid][pDevice] == 0) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Вам нужен пейджер или телефон. Купите его в магазине");
	}
	if(PlayerSIMCardNumber[playerid] == INVALID_SIM_CARD_NUMBER) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"У вас нет SIM-карты");
	}
	
	if(sscanf(params, "i", target_number)) {
		return SendClientMessage(playerid, -1, "Используйте: /call [Номер игрока]");
	}

	foreach(new i: Player) {
		if(PlayerSIMCardNumber[i] == target_number) {
			targetid = i;
			break; 
		}
	}

	if(targetid == INVALID_PLAYER_ID) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Указан неверный номер, или игрок с таким номером не в сети");
	}
	if(PlayerInfo[targetid][pDevice] == 0) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"У указанного игрока нет ни одного девайса");
	}
	if(GetPVarInt(targetid, "togphone") == 1) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Абонент временно недоступен");
	}
	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У вас бан чата!");
	if(PlayerInfo[playerid][pBalance] < 5) return SendClientMessage(playerid, -1, ""COLOR_RED"Недостаточно средств. Пополните счет");
	if(PlayerInfo[playerid][pDevice] == 1) {
		format(small_string, sizeof(small_string), "%s достал(а) пейджер", PlayerInfo[playerid][pName]);
		ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
	}
	if(PlayerInfo[playerid][pDevice] == 2) {
		format(small_string, sizeof(small_string), "%s достал(а) телефон", PlayerInfo[playerid][pName]);
		ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
	}

	PlayerCall[targetid][E_PHONE_CALL] = true;
	PlayerCall[playerid][E_CALLING] = true;
	PlayerCall[playerid][E_CALLING_ID] = targetid;
	PlayerCall[targetid][E_CALLING_ID] = playerid;

	format(small_string, sizeof(small_string), ""COLOR_WHITE"Исходящий звонок... | Абонент: "COLOR_GREEN"%s"COLOR_WHITE" | Номер: "COLOR_GREEN"%i", PlayerInfo[targetid][pName], target_number);
	SendClientMessage(playerid, -1 , small_string);
	format(small_string, sizeof(small_string), ""COLOR_WHITE"Входящий звонок от "COLOR_GREEN"%s"COLOR_WHITE" | Номер: %i", PlayerInfo[playerid][pName], PlayerSIMCardNumber[playerid]);
	SendClientMessage(targetid, -1, small_string);
	SendClientMessage(targetid, -1 , ""COLOR_WHITE"Используйте "COLOR_GREEN"/p"COLOR_WHITE" чтобы ответить на звонок или "COLOR_ORANGE"/h"COLOR_WHITE" чтобы отклонить звонок");
	
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
	SetPlayerAttachedObject(playerid, 0, 19513, 6);
	return PlayerPlaySound(targetid, 20600, 0.0, 0.0, 0.0);
}

CMD:p(playerid, params[]) {
	if(PlayerInfo[playerid][pDevice] == 0) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Вам нужен пейджер или телефон. Купите его в магазине");
	}
	else if(PlayerCall[playerid][E_PHONE_CALL] == false) {
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Нет входящих звонков.");
	} else if(PlayerCall[playerid][E_CALL] == true) {
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Для начала закончите текущий разговор.");
	} else if(PlayerInfo[playerid][pMuted] == 1) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"У вас бан чата!");
	} else {
		PlayerCall[playerid][E_PHONE_CALL] = true;
		PlayerCall[playerid][E_CALLING] = true;
		PlayerCall[playerid][E_CALL] = true;
		PlayerCall[PlayerCall[playerid][E_CALLING_ID]][E_CALL] = true;
		
		format(small_string, sizeof(small_string), ""COLOR_GREEN"%s"COLOR_WHITE" ответил(а) на Ваш звонок.", PlayerInfo[playerid][pName]);
		SendClientMessage(PlayerCall[playerid][E_CALLING_ID], -1, small_string);

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
		SetPlayerAttachedObject(playerid, 0, 19513, 6);
	}
	return 1;
}

CMD:h(playerid, params[]) {
	if(PlayerCall[playerid][E_CALLING] == true)
	{
		PlayerCall[playerid][E_PHONE_CALL] = false;
		PlayerCall[playerid][E_CALLING] = false;
		PlayerCall[playerid][E_CALL] = false;
		PlayerCall[PlayerCall[playerid][E_CALLING_ID]][E_PHONE_CALL] = false;
		PlayerCall[PlayerCall[playerid][E_CALLING_ID]][E_CALLING] = false;
		PlayerCall[PlayerCall[playerid][E_CALLING_ID]][E_CALL] = false;
		SendClientMessage(PlayerCall[playerid][E_CALLING_ID], -1 , ""COLOR_ORANGE"Звонок окончен.");
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Звонок окончен.");
		SetPlayerSpecialAction(PlayerCall[playerid][E_CALLING_ID],SPECIAL_ACTION_STOPUSECELLPHONE);
		SetTimerEx("ClearPhone",2000,false,"i",PlayerCall[playerid][E_CALLING_ID]);
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
		SetTimerEx("ClearPhone",2000,false,"i",playerid);
		PlayerPlaySound(playerid,0,0.0,0.0,0.0);
	}
	if(PlayerCall[playerid][E_PHONE_CALL] == true)
	{
		PlayerCall[playerid][E_PHONE_CALL] = false;
		PlayerCall[playerid][E_CALLING] = false;
		PlayerCall[playerid][E_CALL] = false;
		PlayerCall[PlayerCall[playerid][E_CALLING_ID]][E_PHONE_CALL] = false;
		PlayerCall[PlayerCall[playerid][E_CALLING_ID]][E_CALLING] = false;
		PlayerCall[PlayerCall[playerid][E_CALLING_ID]][E_CALL] = false;
		SendClientMessage(PlayerCall[playerid][E_CALLING_ID], -1, ""COLOR_ORANGE"Звонок окончен.");
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Звонок окончен.");
		SetPlayerSpecialAction(PlayerCall[playerid][E_CALLING_ID],SPECIAL_ACTION_STOPUSECELLPHONE);
		SetTimerEx("ClearPhone",2000,false,"i",PlayerCall[playerid][E_CALLING_ID]);
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
		SetTimerEx("ClearPhone",2000,false,"i",playerid);
		PlayerPlaySound(playerid,0,0.0,0.0,0.0);
	}
	return true;
}

forward ClearPhone(playerid);
public ClearPhone(playerid)
{
	RemovePlayerAttachedObject(playerid, 0);
}