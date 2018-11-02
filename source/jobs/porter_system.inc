#if defined _porter_system_included
	#endinput
#endif
#define _porter_system_included

#define	WEIGHT_MIN	1 // Минимальный вес ящика
#define WEIGHT_MAX	10 // Максимальный вес ящика
#define PORT_COUNTER 1 // Множитель
#define TO_GET_BOX_BOUNTY 15 // Кратность до премии
#define BOX_BOUNTY 50 // Размер премии

new porter_cloth;

new porter_cashbox;

new point_porter;
new unload_porter[4];
new porter_state[MAX_PLAYERS];
new total_porter_payday[MAX_PLAYERS];
new weight[MAX_PLAYERS];
new value_boxes[MAX_PLAYERS];

new pointer_string[90];

stock Porter_OnGameModeInit() {
	Create3DTextLabel(""COLOR_BLUE"Раздевалка", 0xFFFFFFFF, 1977.9124,-1970.7001,16.6941+1, 40, 0);
	porter_cloth = CreateDynamicPickup(1275, 1, 1977.9124,-1970.7001,16.6941);

	porter_cashbox = CreateDynamicPickup(1239, 1, 1976.0205,-1969.2917,16.6943);

	point_porter = CreateDynamicCP(2043.1221,-1966.9659,16.6941, 2.7, -1, -1, -1);
	unload_porter[0] = CreateDynamicCP(2012.3638,-1974.5287,16.9060, 1.2, -1, -1, -1);
	unload_porter[1] = CreateDynamicCP(2006.1279,-1971.9230,16.6941, 1.2, -1, -1, -1);
	unload_porter[2] = CreateDynamicCP(2001.4346,-1974.6238,16.9060, 1.2, -1, -1, -1);
	unload_porter[3] = CreateDynamicCP(1985.4435,-1974.4481,15.1404, 1.2, -1, -1, -1);
	return 1;
}

stock Porter_OnPlayerConnect(playerid) {
	porter_state[playerid] = 0;
	value_boxes[playerid] = 0;
	total_porter_payday[playerid] = 0;

	TogglePlayerDynamicCP(playerid, point_porter, false);
	for(new i = 0; i < sizeof(unload_porter); i++) {
		TogglePlayerDynamicCP(playerid, unload_porter[i], false);
	}
	Streamer_Update(playerid, STREAMER_TYPE_CP);
	return 1;
}
stock Porter_OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason

	TogglePlayerDynamicCP(playerid, point_porter, false);
	for(new i = 0; i < sizeof(unload_porter); i++) {
		TogglePlayerDynamicCP(playerid, unload_porter[i], false);
	}
	Streamer_Update(playerid, STREAMER_TYPE_CP);
	return 1;
}

stock Porter_OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(GetPVarInt(playerid, "tempjob") == 3 && porter_state[playerid] == 2) 
	{
		if(GetPVarInt(playerid,"DropBox") > gettime())	{ return false; }
    	if((newkeys & KEY_SPRINT && newkeys & KEY_JUMP)) {
			BoxFail(playerid);
        }
        if((newkeys & KEY_JUMP) && !(oldkeys & KEY_JUMP)) {
			BoxFail(playerid);
        }
        if(newkeys & KEY_SECONDARY_ATTACK || (newkeys & KEY_SUBMISSION && newkeys & KEY_SECONDARY_ATTACK)) {
			BoxFail(playerid);
        }
        if(newkeys & KEY_FIRE) {
			BoxFail(playerid);
        }
    }
    return 1;

}

/*hook OnPlayerUpdate(playerid) {
	if(GetPVarInt(playerid, "tempjob") == 3 && porter_state[playerid] == 2) {
		if(GetPVarInt(playerid,"DropBox") > gettime())	{ return false; }
	    new 
	        anim_index = GetPlayerAnimationIndex(playerid);

	    if(anim_index == 1132 || anim_index == 1136 || anim_index == 1141) {
				BoxFail(playerid);
	        }
    }
    return 1;
}*/

stock Porter_OP_PickUpDynamicPickup(playerid, pickupid) {
	if(pickupid == porter_cashbox)
 	{
 		if(GetPVarInt(playerid,"AntiFloodZ") > gettime()){ return false; }
		SetPVarInt(playerid,"AntiFloodZ",gettime() + 5);
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Чтобы начать работу грузчика - переоденьтесь в спецодежду");
		return 1;
    }
	if(pickupid == porter_cloth)
 	{
 		if(GetPVarInt(playerid,"AntiFloodF") > gettime()){ return false; }
		SetPVarInt(playerid,"AntiFloodF",gettime() + 5);
 	    if(GetPVarInt(playerid, "tempjob") == 3) {
 	    	if(IsPlayerAttachedObjectSlotUsed(playerid, 0) == 1) {
                RemovePlayerAttachedObject(playerid, 0);
            }
        	TogglePlayerDynamicCP(playerid, point_porter, false);
            for(new i = 0; i < sizeof(unload_porter); i++) {
				TogglePlayerDynamicCP(playerid, unload_porter[i], false);
			}
			Streamer_Update(playerid, STREAMER_TYPE_CP);
            porter_state[playerid] = 0;
            value_boxes[playerid] = 0;

            Player.AddEXP(PlayerInfo[playerid][pID], total_porter_payday[playerid], E_JOB_PORTER, playerid);
			if(total_porter_payday[playerid] > 0 ) {
				format(pointer_string, sizeof(pointer_string), ""COLOR_GREEN"Работа завершена. Вы заработали: {FFFFFF}%d EXP", total_porter_payday[playerid]);
				SendClientMessage(playerid, -1, pointer_string);
			}	 	   
	 	    else SendClientMessage(playerid, -1, ""COLOR_RED"Работа завершена. Вы ничего не заработали");

	 	    format(pointer_string, 100, "%s сдал(а) спецодежду", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, pointer_string);

	 	    total_porter_payday[playerid] = 0;
	 	    SetPVarInt(playerid,"tempjob", 0);
			CBackSkin(playerid);
			return 1;
 	    }
		new 
		Fraction:fractionid = GetPlayerFraction(playerid);
 	    if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы состоите во фракции");

 	    porter_state[playerid] = 0;
		value_boxes[playerid] = 0;
		total_porter_payday[playerid] = 0;

		SetPVarInt(playerid,"Worker", 0);

		format(pointer_string, 100, "%s надел(а) спецодежду", PlayerInfo[playerid][pName]);
		ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, pointer_string);

 	    SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали работу грузчика");
 	    SendClientMessage(playerid, -1, ""COLOR_GREEN"Ваша задача переносить груз в указанное место");

 	    format(pointer_string, sizeof(pointer_string), ""COLOR_GREEN"Вы будете получать премию за каждый %d ящик в размере: {FFFFFF} %d EXP", TO_GET_BOX_BOUNTY, BOX_BOUNTY);
			
	 	SendClientMessage(playerid, -1, pointer_string);

 	    SetPVarInt(playerid,"tempjob", 3);
 	    switch(random(3)) {
 	    	case 0: SetPlayerSkin(playerid, 16);
 	    	case 1: SetPlayerSkin(playerid, 27);
 	    	case 2: SetPlayerSkin(playerid, 260);
 	    }
 	    for(new i = 0; i < sizeof(unload_porter); i++) {
			TogglePlayerDynamicCP(playerid, unload_porter[i], false);
		}
		TogglePlayerDynamicCP(playerid, point_porter, true);
 	    
 	    Streamer_Update(playerid, STREAMER_TYPE_CP);
		return 1;
	}
	return 0;
}

stock Porter_OnPlayerEnterDynamicCP(playerid, checkpointid) {
	if(IsPlayerInAnyVehicle(playerid)) {
		return 1;
	}
	
	if(checkpointid == point_porter)
	{
		if(GetPVarInt(playerid,"DropBox") > gettime()){ GameTextForPlayer(playerid, "~r~WAIT...", 7250, 5);	return false; }


		TogglePlayerDynamicCP(playerid, point_porter, false);
		deliver_goods(playerid);
		Streamer_Update(playerid, STREAMER_TYPE_CP);
		if(GetPVarInt(playerid, "Worker") == 0) {
			SetPVarInt(playerid,"Worker", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы взяли груз, доставьте его в указанное место");
		}

		ClearAnimations(playerid);
    	ApplyAnimation(playerid, !"CARRY", !"crry_prtial", 4.0, 1, 0, 0, 1, 1, 1);
    	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    	weight[playerid] = RandomEx(WEIGHT_MIN, WEIGHT_MAX);

    	format(pointer_string, sizeof(pointer_string), "%d ~g~KG", weight[playerid]);
		GameTextForPlayer(playerid, pointer_string, 2000, 5);


		SetPVarInt(playerid,"TakenBox",gettime() + 3);

		SetPlayerAttachedObject(playerid, 0, 1271, 17, -0.030999, 0.492000, 0.000000, 0.000000, 0.000000, 0.000000, 0.503000, 0.569000, 1.000000);
		switch(random(5)){
			case 0: {		
			switch(random(5)){		
				case 0: format(pointer_string, 100, "- %s[%d]: Фух, утомился я", PlayerInfo[playerid][pName], playerid);
				case 1: format(pointer_string, 100, "- %s[%d]: Тяжелый, сука...", PlayerInfo[playerid][pName], playerid);
				case 2: format(pointer_string, 100, "- %s[%d]: Там что, кирпичи", PlayerInfo[playerid][pName], playerid);
				case 3: format(pointer_string, 100, "- %s[%d]: Хух, потащили", PlayerInfo[playerid][pName], playerid);
				case 4: format(pointer_string, 100, "- %s[%d]: Тяжелый труд", PlayerInfo[playerid][pName], playerid);
			}
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_CHAT, pointer_string);
			}
			case 1: return 1;
			case 2: return 1;
			case 3: return 1;
			case 4: return 1;
		}	
		return 1;					
    }
    if(checkpointid >= unload_porter[0] && checkpointid <= unload_porter[3]) {
		for(new i = 0; i < sizeof(unload_porter); i++) {
			TogglePlayerDynamicCP(playerid, unload_porter[i], false);
		}
		get_goods(playerid);
		Streamer_Update(playerid, STREAMER_TYPE_CP);
		ClearPlayerAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		if(GetPVarInt(playerid,"TakenBox") > gettime()){ return Kick(playerid); }

		if(GetPVarInt(playerid, "Worker") == 1) {
			SetPVarInt(playerid,"Worker", 2);
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы доставили груз. Для получения зарплаты - переоденьтесь");
		}				

		value_boxes[playerid]++;

		if (value_boxes[playerid] % TO_GET_BOX_BOUNTY == 0) {
			format(pointer_string, sizeof(pointer_string), ""COLOR_BLUE"Вы получили премию в размере: {FFFFFF}%d EXP", BOX_BOUNTY);
			SendClientMessage(playerid, -1, pointer_string);

			total_porter_payday[playerid] += BOX_BOUNTY;
		}

		new sum = weight[playerid]*PORT_COUNTER;

		total_porter_payday[playerid] += sum;

		format(pointer_string, sizeof(pointer_string), "~g~+%d EXP~n~~b~TOTAL: ~w~%d", sum, total_porter_payday[playerid]);
		GameTextForPlayer(playerid, pointer_string, 5000, 5);			

        if(IsPlayerAttachedObjectSlotUsed(playerid, 0) == 1) {
            RemovePlayerAttachedObject(playerid, 0);
        }

        switch(random(5)){
			case 0: {		
				switch(random(3)){		
					case 0: format(pointer_string, 100, "%s вытер(ла) пот со лба", PlayerInfo[playerid][pName]);
					case 1: format(pointer_string, 100, "%s тяжело вздохнул(а)", PlayerInfo[playerid][pName]);
					case 2: format(pointer_string, 100, "%s отдышался", PlayerInfo[playerid][pName]);
				}
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, pointer_string);
			}
		}
		return 1;
	}
	return 0;
}

stock get_goods(playerid) {
	TogglePlayerDynamicCP(playerid, point_porter, true);
}

stock deliver_goods(playerid) {
	return TogglePlayerDynamicCP(playerid, unload_porter[random(4)], true);
}

stock ClearPlayerAnim(playerid) {
	ApplyAnimation(playerid, !"ped", !"facsurp", 4.0, 1, 0, 0, 1, 1, 1);
	ApplyAnimation(playerid, !"ped", !"facsurp", 4.0, 1, 0, 0, 1, 1, 1);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	return true;
}

stock BoxFail(playerid) {
	if(GetPVarInt(playerid,"DropBox") > gettime())	{ return false; }
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	SendClientMessage(playerid, -1, ""COLOR_RED"Вы уронили ящик");
	TogglePlayerDynamicCP(playerid, point_porter, false);
	get_goods(playerid);
	Streamer_Update(playerid, STREAMER_TYPE_CP);
	if(IsPlayerAttachedObjectSlotUsed(playerid, 0) == 1) {
		RemovePlayerAttachedObject(playerid, 0);
	}
	ClearAnimations(playerid);
	ApplyAnimation(playerid,"PED","IDLE_tired",4.1,0,1,1,0,1);
	
	SetPVarInt(playerid,"DropBox",gettime() + 2);
	SetPVarInt(playerid,"DroppedBox",gettime() + 8);

	switch(random(5)){
		case 0: {		
		switch(random(4)){		
			case 0: format(pointer_string, 100, "- %s[%d]: Ебта, прям на ногу", PlayerInfo[playerid][pName], playerid);
			case 1: format(pointer_string, 100, "- %s[%d]: Ах, что же так тяжело", PlayerInfo[playerid][pName], playerid);
			case 2: format(pointer_string, 100, "- %s[%d]: Там кирпичи?", PlayerInfo[playerid][pName], playerid);
			case 3: format(pointer_string, 100, "- %s[%d]: Сука!", PlayerInfo[playerid][pName], playerid);
		}
		ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_CHAT, pointer_string);
		}
		case 1: return 1;
		case 2: return 1;
		case 3: return 1;
		case 4: return 1;
	}	
	return 1;
}
