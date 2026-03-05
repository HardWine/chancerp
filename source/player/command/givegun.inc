#if defined cmd_givegun_system
	#endinput
#endif
#define cmd_givegun_system
/*
static const weapon_slot[47] =
{
    0, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    10, 10, 10, 10, 10, 10,
    8, 8, 8,
    0, 0, 0, //19-21
    2, 2, 2,
    3, 3, 3,
    4, 4,
    5, 5,
    4,
    6, 6,
    7, 7, 7, 7,
    8,
    12,
    9, 9, 9,
    11, 11, 11
};
*/
CMD:givegun(playerid, params[]) {

	Dialog_Show(playerid, Dialog:DIALOG_GIVEGUN_INITIAL);
	return 1;
}

DialogCreate:DIALOG_GIVEGUN_INITIAL(playerid) {

	new gun_id = GetPlayerWeapon(playerid);
	new slot_id = GetWeaponIDSlot(gun_id);
	new get_weapons, get_ammo;

	GetPlayerWeaponData(playerid, slot_id, get_weapons, get_ammo);

	SetPVarInt(playerid, "weapon_selected", get_weapons);
	SetPVarInt(playerid, "ammo_selected", get_ammo);

	if(slot_id == 0) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Сначала возьмите в руки оружие, разрешенное для передачи");

	format(small_string, sizeof(small_string), "Вы собираетесь передать "COLOR_BLUE"%s"COLOR_WHITE", введите ID игрока", weapon_names[gun_id]);

	return Dialog_Open(playerid, Dialog:DIALOG_GIVEGUN_INITIAL, DIALOG_STYLE_INPUT,
		"Передать оружие", small_string, "Далее", "Отмена"
	);	
}

DialogResponse:DIALOG_GIVEGUN_INITIAL(playerid, response, listitem, inputtext[]) {
	if(!response) return 1;

	new recipient = strval(inputtext);

	if(playerid == recipient) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Неверный ID!");
	if(recipient < 0 || recipient > 1000) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Неверный ID!");
	if(PlayerLogged{recipient} == false) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Неверный ID!");

	if(GetDistanceBetweenPlayerz(playerid, recipient, 5.00) != 1) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы слишком далеко от указанного игрока");
	SetPVarInt(playerid, "givegun", recipient);
	Dialog_Show(playerid, Dialog:DIALOG_GIVEGUN);
	return 1;
}

DialogCreate:DIALOG_GIVEGUN(playerid) {

	new current_weapon = GetPlayerWeapon(playerid);
	new recipient = GetPVarInt(playerid, "givegun");

	format(small_string, sizeof(small_string), "Вы собираетесь передать "COLOR_BLUE"%s"COLOR_WHITE" %s, укажите количество пт.",
		weapon_names[current_weapon],
		PlayerInfo[recipient][pName]
	);

	return Dialog_Open(playerid, Dialog:DIALOG_GIVEGUN, DIALOG_STYLE_INPUT,
		"Передать оружие", small_string, "Готово", "Отмена"
	);	
}

stock RemovePlayerWeapon(const playerid, const weaponid, const value) {
    new 
    	saveweapon[13], 
    	saveammo[13],
    	current_slot = -1;

    for(new slot = 0; slot < 13; slot++) {
 		GetPlayerWeaponData(playerid, slot, saveweapon[slot], saveammo[slot]);
 	}
 	ResetPlayerWeapons(playerid);
    
    for(new slot; slot < 13; slot++) {
    	if(saveammo[slot] == 0) {
    		continue;
    	}
    	
        if(saveweapon[slot] == weaponid) {
        	current_slot = slot;
            continue;
        }
 		GivePlayerWeapon(playerid, saveweapon[slot], saveammo[slot]);
    }

    if(current_slot != -1) {
	    new 
	    	last_patr_slot = saveammo[current_slot];

	    last_patr_slot = last_patr_slot - value;

	    if(last_patr_slot > 0) {
	    	GivePlayerWeapon(playerid, saveweapon[current_slot], last_patr_slot);
	    }
	}
}

DialogResponse:DIALOG_GIVEGUN(playerid, response, listitem, inputtext[]) {
	if(!response) return 1;

	new weapon_verify = GetPVarInt(playerid, "weapon_selected");
	new ammo_verify = GetPVarInt(playerid, "ammo_selected");

	new current_weapon = GetPlayerWeapon(playerid);
	new recipient = GetPVarInt(playerid, "givegun");
	new slot_weapon = GetWeaponIDSlot(current_weapon);

	if(GetDistanceBetweenPlayerz(playerid, recipient, 5.00) != 1) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы слишком далеко от указанного игрока");

	if(slot_weapon == 0) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Необходимо держать в руках оружие, разрешенное для передачи");

	new get_weapons, get_ammo;

	GetPlayerWeaponData(playerid, slot_weapon, get_weapons, get_ammo);

	if(weapon_verify != current_weapon) SendClientMessage(playerid, -1, "(1) Ошибка!");
	if(ammo_verify	 != get_ammo)  SendClientMessage(playerid, -1, "(2) Ошибка!");

	new value = strval(inputtext);

	if(get_ammo < value) return SendClientMessage(playerid, -1, ""COLOR_RED"У Вас нет столько пт.");
	if(value < 1 || value > 150) return SendClientMessage(playerid, -1, ""COLOR_RED"Укажите кол-во от 1 до 150");

	new pt = get_ammo-value;

	format(small_string, sizeof(small_string), "%d %d | %d %d | %d %d", weapon_verify, current_weapon, ammo_verify, get_ammo, pt, value);
	SendClientMessage(playerid, -1, small_string);	

	SetPlayerChatBubble(playerid, "передал(а) оружие", C_PURPLE, 30.0, 5000);
	format(small_string, sizeof(small_string), "%s передал(а) оружие", PlayerInfo[playerid][pName]);
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);

	SetPlayerChatBubble(recipient, "взял(а) оружие", C_PURPLE, 30.0, 5000);
	format(small_string, sizeof(small_string), "%s взял(а) оружие", PlayerInfo[recipient][pName]);
	ProxDetector(recipient, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);	

	GivePlayerWeapon(recipient, current_weapon, value);

	RemovePlayerWeapon(playerid, current_weapon, value);

	/*
	if(slot_weapon == 2) {
			if(PlayerInfo[playerid][slot_2_gun] != 0) GivePlayerWeapon(playerid, PlayerInfo[playerid][slot_2_gun], pt);
	}
	if(slot_weapon == 3) {
			if(PlayerInfo[playerid][slot_3_gun] != 0) GivePlayerWeapon(playerid, PlayerInfo[playerid][slot_3_gun], pt);
	}
	if(slot_weapon == 4) {
			if(PlayerInfo[playerid][slot_4_gun] != 0) GivePlayerWeapon(playerid, PlayerInfo[playerid][slot_4_gun], pt);
	}
	if(slot_weapon == 5) {
			if(PlayerInfo[playerid][slot_5_gun] != 0) GivePlayerWeapon(playerid, PlayerInfo[playerid][slot_5_gun], pt);
	}
	if(slot_weapon == 8) {
			if(PlayerInfo[playerid][slot_8_gun] != 0) GivePlayerWeapon(playerid, PlayerInfo[playerid][slot_8_gun], pt);
	}				
	*/
	GetPlayerWeaponData(playerid, 2, PlayerInfo[playerid][slot_2_gun], PlayerInfo[playerid][slot_2_ammo]);
	GetPlayerWeaponData(playerid, 3, PlayerInfo[playerid][slot_3_gun], PlayerInfo[playerid][slot_3_ammo]);
	GetPlayerWeaponData(playerid, 4, PlayerInfo[playerid][slot_4_gun], PlayerInfo[playerid][slot_4_ammo]);
	GetPlayerWeaponData(playerid, 5, PlayerInfo[playerid][slot_5_gun], PlayerInfo[playerid][slot_5_ammo]);
	GetPlayerWeaponData(playerid, 8, PlayerInfo[playerid][slot_8_gun], PlayerInfo[playerid][slot_8_ammo]);

	SetPlayerInt(playerid, "slot_2_gun", PlayerInfo[playerid][slot_2_gun]);
	SetPlayerInt(playerid, "slot_3_gun", PlayerInfo[playerid][slot_3_gun]);
	SetPlayerInt(playerid, "slot_4_gun", PlayerInfo[playerid][slot_4_gun]);
	SetPlayerInt(playerid, "slot_5_gun", PlayerInfo[playerid][slot_5_gun]);
	SetPlayerInt(playerid, "slot_8_gun", PlayerInfo[playerid][slot_8_gun]);

	SetPlayerInt(playerid, "slot_2_ammo", PlayerInfo[playerid][slot_2_ammo]);
	SetPlayerInt(playerid, "slot_3_ammo", PlayerInfo[playerid][slot_3_ammo]);
	SetPlayerInt(playerid, "slot_4_ammo", PlayerInfo[playerid][slot_4_ammo]);
	SetPlayerInt(playerid, "slot_5_ammo", PlayerInfo[playerid][slot_5_ammo]);
	SetPlayerInt(playerid, "slot_8_ammo", PlayerInfo[playerid][slot_8_ammo]);

	GetPlayerWeaponData(recipient, 2, PlayerInfo[recipient][slot_2_gun], PlayerInfo[recipient][slot_2_ammo]);
	GetPlayerWeaponData(recipient, 3, PlayerInfo[recipient][slot_3_gun], PlayerInfo[recipient][slot_3_ammo]);
	GetPlayerWeaponData(recipient, 4, PlayerInfo[recipient][slot_4_gun], PlayerInfo[recipient][slot_4_ammo]);
	GetPlayerWeaponData(recipient, 5, PlayerInfo[recipient][slot_5_gun], PlayerInfo[recipient][slot_5_ammo]);
	GetPlayerWeaponData(recipient, 8, PlayerInfo[recipient][slot_8_gun], PlayerInfo[recipient][slot_8_ammo]);

	SetPlayerInt(recipient, "slot_2_gun", PlayerInfo[recipient][slot_2_gun]);
	SetPlayerInt(recipient, "slot_3_gun", PlayerInfo[recipient][slot_3_gun]);
	SetPlayerInt(recipient, "slot_4_gun", PlayerInfo[recipient][slot_4_gun]);
	SetPlayerInt(recipient, "slot_5_gun", PlayerInfo[recipient][slot_5_gun]);
	SetPlayerInt(recipient, "slot_8_gun", PlayerInfo[recipient][slot_8_gun]);

	SetPlayerInt(recipient, "slot_2_ammo", PlayerInfo[recipient][slot_2_ammo]);
	SetPlayerInt(recipient, "slot_3_ammo", PlayerInfo[recipient][slot_3_ammo]);
	SetPlayerInt(recipient, "slot_4_ammo", PlayerInfo[recipient][slot_4_ammo]);
	SetPlayerInt(recipient, "slot_5_ammo", PlayerInfo[recipient][slot_5_ammo]);
	SetPlayerInt(recipient, "slot_8_ammo", PlayerInfo[recipient][slot_8_ammo]);	

	return 1;
}

stock GetWeaponIDSlot(weaponid) {
	if(weaponid == 22 || weaponid == 23 || weaponid == 24) {
		return 2;
	}
	if(weaponid == 25 || weaponid == 26 || weaponid == 27) {
		return 3;
	}	
	if(weaponid == 28 || weaponid == 29 || weaponid == 32) {
		return 4;
	}	
	if(weaponid == 30 || weaponid == 31 || weaponid == 32) {
		return 5;
	}		
	if(weaponid == 33 || weaponid == 34) {
		return 6;
	}		
	return 0;
}