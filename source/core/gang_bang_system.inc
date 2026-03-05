#if defined gang_bang_system_included
	#endinput
#endif

#define gang_bang_system_included

#define EXPLOSION_DELAY 		15 // Время между взрывами
#define MIN_DELAY_TIME			1 // Минимально время до взрыва
#define MAX_DELAY_TIME			10 // Максимальное время до взрыва
#define DROP_DISTANCE			10 // Дистаниция для броска

#include <YSI_Coding\y_hooks>

new bang_object[MAX_PLAYERS]; // Объект для взрыва
new Text3D:bang_text[MAX_PLAYERS]; // 3d Text гранаты
new bang_timer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};


hook OnPlayerConnect(playerid) {
	bang_object[playerid] = INVALID_OBJECT_ID;
	bang_text[playerid] = INVALID_3DTEXT_ID;
	bang_timer[playerid] = INVALID_TIMER_ID;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason

	if(IsValidObject(bang_object[playerid])) {
		DestroyDynamicObject(bang_object[playerid]);
	}
	if(IsValidDynamic3DTextLabel(bang_text[playerid])) {
		DestroyDynamic3DTextLabel(bang_text[playerid]);
	}
	bang_object[playerid] = INVALID_OBJECT_ID;
	bang_text[playerid] = INVALID_3DTEXT_ID;

	bang_timer[playerid] = KillTimer(bang_timer[playerid]);
	return Y_HOOKS_CONTINUE_RETURN_1;
}

// Данная функция от Y_Less, она позволит определить коордиаты перед игроком 
stock GetXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance)
{
    new Float:a;

    GetPlayerPos(playerid, x, y, a);
    GetPlayerFacingAngle(playerid, a);

    x += (distance * floatsin(-a, degrees));
    y += (distance * floatcos(-a, degrees));
}
CMD:bang(playerid, params[])
{
	if(IsPlayerInDynamicArea(playerid, safe_zone[0]) || IsPlayerInDynamicArea(playerid, safe_zone[1]) ||
	IsPlayerInDynamicArea(playerid, safe_zone[2]) || IsPlayerInDynamicArea(playerid, safe_zone[3]) ||
	IsPlayerInDynamicArea(playerid, safe_zone[4]) || IsPlayerInDynamicArea(playerid, safe_zone[5]) ||
	IsPlayerInDynamicArea(playerid, safe_zone[6]) || IsPlayerInDynamicArea(playerid, safe_zone[7]) ||
	IsPlayerInDynamicArea(playerid, safe_zone[8]) || IsPlayerInDynamicArea(playerid, safe_zone[9])) {
	return SendClientMessage(playerid, -1, ""COLOR_RED"Использование взрывных устройств в безопасной зоне запрещен");
	}
	if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Использование взрывных устройств в помещениях невозможно");
 
	}

	new bomb_id, dist;
	if(sscanf(params, "dd", bomb_id, dist)) return SendClientMessage(playerid, -1, !"Используйте: /bang [id устройства] [дистанция]");
	if(GetPVarInt(playerid,"bomb_dropped") > gettime()) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Подождите немного");
	}
	if(IsPlayerInAnyVehicle(playerid)) {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Использование данной команды в транспорте невозможно");
	}
	if(bomb_id > 3 || bomb_id < 1) return SendClientMessage(playerid, -1, "(( id 1 - петарда, id 2 - граната, id 3 - динамит ))");

	if(dist > 10 || dist < 2) return SendClientMessage(playerid, -1, ""COLOR_RED"Дистанция должна быть от 2 до 10 метров");
	new delay = MAX_DELAY_TIME;
	// Проверка задержки перед взрывом
	/*if(delay > MAX_DELAY_TIME || delay < MIN_DELAY_TIME) {
		format(small_string, sizeof small_string, 
		""COLOR_ORANGE"Задержка должна быть от %i до %i секунд", 
		MIN_DELAY_TIME, MAX_DELAY_TIME);
		return SendClientMessage(playerid, -1, small_string);
	}*/
	// Запишем в PVar задержку перед взрывом
	SetPVarInt(playerid, "delay_bomb", delay);
	// Задержка между бросками
	SetPVarInt(playerid,"bomb_dropped",gettime()+EXPLOSION_DELAY);
	// Получаем координаты игрока
	new Float:bpos_x, Float:bpos_y, Float:bpos_z;
	GetPlayerPos(playerid, bpos_x, bpos_y, bpos_z);
	//

	GetXYInFrontOfPlayer(playerid, bpos_x, bpos_y, dist);


	switch(bomb_id) {
		case 1: {
			if(PlayerInfo[playerid][pPetard] < 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Недостаточно петард");
			PlayerInfo[playerid][pPetard] -= 1;
			SetPlayerInt(playerid, "Petard", PlayerInfo[playerid][pPetard]);
			format(small_string, sizeof small_string, ""COLOR_ORANGE"Осталось петард: {FFFFFF}%d", PlayerInfo[playerid][pPetard]);
			SendClientMessage(playerid, -1, small_string);		
			SetPlayerChatBubble(playerid, "бросает петарду", C_PURPLE, 15.0, 5000);
			format(small_string, 100, "%s бросает петарду", PlayerInfo[playerid][pName]);
			// Создаем объект
			bang_object[playerid] = CreateDynamicObject(327, bpos_x, bpos_y, bpos_z, 0, 0, bpos_z, -1, -1, -1, 25, 25);

		}
		case 2: {
			if(PlayerInfo[playerid][pGrenade] < 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Недостаточно гранат");
			PlayerInfo[playerid][pGrenade] -= 1;
			SetPlayerInt(playerid, "Grenade", PlayerInfo[playerid][pGrenade]);
			format(small_string, sizeof small_string, ""COLOR_ORANGE"Осталось гранат: {FFFFFF}%d", PlayerInfo[playerid][pGrenade]);
			SendClientMessage(playerid, -1, small_string);		
			SetPlayerChatBubble(playerid, "бросает гранату", C_PURPLE, 15.0, 5000);
			format(small_string, 100, "%s бросает гранату", PlayerInfo[playerid][pName]);
			// Создаем объект
			bang_object[playerid] = CreateDynamicObject(343, bpos_x, bpos_y, bpos_z, 0, 0, bpos_z, -1, -1, -1, 25, 25);

		}
		case 3: {
			if(PlayerInfo[playerid][pDynamite] < 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Недостаточно динамита");
			PlayerInfo[playerid][pDynamite] -= 1;
			SetPlayerInt(playerid, "Dynamite", PlayerInfo[playerid][pDynamite]);
			format(small_string, sizeof small_string, ""COLOR_ORANGE"Осталось динамита: {FFFFFF}%d", PlayerInfo[playerid][pDynamite]);
			SendClientMessage(playerid, -1, small_string);		
			SetPlayerChatBubble(playerid, "бросает динамит", C_PURPLE, 15.0, 5000);
			format(small_string, 100, "%s бросает динамит", PlayerInfo[playerid][pName]);
			// Создаем объект
			bang_object[playerid] = CreateDynamicObject(1654, bpos_x, bpos_y, bpos_z-0.27, 0, 0, bpos_z, -1, -1, -1, 25, 25);

		}
		default: return SendClientMessage(playerid, -1, "(( id 1 - петарда, id 2 - граната, id 3 - динамит ))");
	}

	SetPVarInt(playerid, "bomb_id_used", bomb_id);
	SetPVarInt(playerid, "dist_used", dist);

	// Создаем текст
	bang_text[playerid] = CreateDynamic3DTextLabel(" ", 0xFFFFFFFF,  bpos_x, bpos_y, bpos_z+0.15, 20, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 25.0);

	// Создаем таймер
	bang_timer[playerid] = KillTimer(bang_timer[playerid]);
	bang_timer[playerid] = SetTimerEx("CreateBang", 1000, 0, "i", playerid);
	ApplyAnimation(playerid, !"ped", !"facsurp", 4.0, 1, 0, 0, 1, 1, 1);
	ApplyAnimation(playerid, !"ped", !"facsurp", 4.0, 1, 0, 0, 1, 1, 1);
	ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, 1, 1, 1, 1, 1);
	SetTimerEx("StopThrow", 350, 0, "i", playerid);

	ProxDetector(playerid, 15, C_PURPLE, small_string);
	return 1;
}
forward CreateBang(playerid);
public CreateBang(playerid) {
	new delay = GetPVarInt(playerid, "delay_bomb");
	delay -= 1;
	SetPVarInt(playerid, "delay_bomb", delay);
	switch(delay) {
		case 1..3: {
			// Обновляем 3d текст
			format(small_string, sizeof small_string, ""COLOR_RED"До взрыва: {FFFFFF}%d сек.", delay);
			UpdateDynamic3DTextLabelText(bang_text[playerid], 0xFFFFFFFF, small_string);
			goto counter;
		}
		case 4..6: {
			// Обновляем 3d текст
			format(small_string, sizeof small_string, ""COLOR_ORANGE"До взрыва: {FFFFFF}%d сек.", delay);
			UpdateDynamic3DTextLabelText(bang_text[playerid], 0xFFFFFFFF, small_string);
			goto counter;
		}
		case 7..10: {
			// Обновляем 3d текст
			format(small_string, sizeof small_string, ""COLOR_GREEN"До взрыва: {FFFFFF}%d сек.", delay);
			UpdateDynamic3DTextLabelText(bang_text[playerid], 0xFFFFFFFF, small_string);
			goto counter;
		}
		default: {
			// Удаляем текст
			if(IsValidDynamic3DTextLabel(bang_text[playerid])) {
				DestroyDynamic3DTextLabel(bang_text[playerid]);
			}
			// Получаем координаты объекта для взрыва
			new Float:bpos_x, Float:bpos_y, Float:bpos_z;
			GetDynamicObjectPos(bang_object[playerid], bpos_x, bpos_y, bpos_z);
			// Удаляем объект
			if(IsValidDynamicObject(bang_object[playerid])) {
				DestroyDynamicObject(bang_object[playerid]);
			}

			new bomb_id = GetPVarInt(playerid, "bomb_id_used");
			//new dist = GetPVarInt(playerid, "dist_used");
			DeletePVar(playerid, "delay_bomb");

			switch(random(10)) {
				case 0..8: goto bang;
				case 9: return CreateExplosion(bpos_x, bpos_y, bpos_z, 13, 2), SendClientMessage(playerid, -1, ""COLOR_RED"Заряд оказался бракованным");
			}

			bang:
			switch(bomb_id) {
				case 1: CreateExplosion(bpos_x, bpos_y, bpos_z, 12, 5);
				case 2: CreateExplosion(bpos_x, bpos_y, bpos_z, 11, RandomEx(6,12));
				case 3: CreateExplosion(bpos_x, bpos_y, bpos_z, 1, RandomEx(13,17));
			}
			// Взрываем
			
			//
			bang_timer[playerid] = INVALID_TIMER_ID;
			bang_object[playerid] = INVALID_OBJECT_ID;
			bang_text[playerid] = INVALID_3DTEXT_ID;	
			return 1;
		}
	}
	counter:

	bang_timer[playerid] = KillTimer(bang_timer[playerid]);
	return bang_timer[playerid] = SetTimerEx("CreateBang", 1000, 0, "i", playerid);
}
forward StopThrow(playerid);
public StopThrow(playerid) {
	ApplyAnimation(playerid, !"ped", !"facsurp", 4.0, 1, 0, 0, 1, 1, 1);
	ApplyAnimation(playerid, !"ped", !"facsurp", 4.0, 1, 0, 0, 1, 1, 1);
	return 1;
}