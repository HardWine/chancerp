#if defined _business_functions_included
	#endinput
#endif
#define _business_functions_included

#define BUSINESS_COST			10

#define ATM_CLICK_SOUND			43000
#define ATM_WITHDRAW_SOUND		20801
#define ATM_DEPOSIT_SOUND		6400

#define COST_PAGER				700
#define COST_MOBILE				2500		
#define COST_SCREW				35
#define COST_MASK				100
#define COST_SIM				500

#define COST_BUSTER				2
#define COST_2LUX				5
#define COST_RACK				10
#define COST_SALAD				10

#define COST_BEER				50
#define COST_SCOTCH				90
#define COST_GIN				100
#define COST_VODKA				120
#define COST_WINE				200
#define COST_CHAMPAGNE			500

#define COST_9MM				15
#define COST_SILENCED			25
#define COST_DE 				40
#define COST_SHOTGUN			45
#define COST_AK 				50
#define COST_SMG				40


new BusinessMenu[11];

stock SetBusinessInt(column[], value, id)
{
	printf("[bizz_debug] [bid:%d] ВЫПОЛНЕНИЕ ЗАПРОСА ДЛЯ БИЗНЕСА", id);
	id=id+1;
	new query[256];
	mysql_format(database, query, sizeof(query), "UPDATE `bizz` SET  %e = '%i' WHERE ID = '%i' LIMIT 1", column, value, id);
	
	print(query);

	if(mysql_pquery(database, query, "", "") == 1) {
		print("[bizz_debug] Запрос успешно прошел");
	} else {
		print("[bizz_debug] Запрос пошел по пизде");
	}
	return true;
}

stock BusinessCP() {

	// 24/7
	BusinessMenu[0] = CreateDynamicCP(-21.9947,-138.5611,1003.5469, 0.9, -1,
	 -1, -1, 20);
	BusinessMenu[1] = CreateDynamicCP(-23.3323,-55.5361,1003.5469, 0.9, -1,
	 -1, -1, 20);
	BusinessMenu[2] = CreateDynamicCP(-28.0853,-89.8599,1003.5469, 0.9, -1,
	 -1, -1, 20);

	// Pizza Stack
	BusinessMenu[3] = CreateDynamicCP(373.7096,-119.1796,1001.4922, 0.9, -1,
	 -1, -1, 20);
	// Cluckin Bell
	BusinessMenu[4] = CreateDynamicCP(369.4851,-6.1764,1001.8589, 0.9, -1,
	 -1, -1, 20);
	// Burger Shot
	BusinessMenu[5] = CreateDynamicCP(377.4861,-67.6131,1001.5078, 0.9, -1,
	 -1, -1, 20);

	// Bar
	BusinessMenu[6] = CreateDynamicCP(499.8165,-20.7264,1000.6797, 0.9, -1,
	 -1, -1, 20);
	BusinessMenu[7] = CreateDynamicCP(1215.3322,-13.2969,1000.9219, 0.9, -1,
	 -1, -1, 20);
	BusinessMenu[8] = CreateDynamicCP(495.6079,-75.9203,998.7578, 0.9, -1,
	 -1, -1, 20);

	// Ammu-Nation
	BusinessMenu[9] = CreateDynamicCP(295.2127,-38.3023,1001.5156, 0.9, -1,
	 -1, -1, 20);
	BusinessMenu[10] = CreateDynamicCP(290.1922,-109.5344,1001.5156, 0.9, -1,
	 -1, -1, 20);


	// Tattoo Parlor CP coords (if you got ideas what he can do) -201.9385,-42.2514,1002.2734
	// Barbershop CP coords (same shit but 2 types of int) 421.3306,-76.9431,1001.8047 + 414.1440,-17.9516,1001.8047

}


stock OpenBusinessMenu(playerid, checkpointid) {
	
	if(checkpointid >= BusinessMenu[0] && checkpointid <= BusinessMenu[10]) {
		if(IsPlayerInAnyVehicle(playerid)) return 1;
		new 
			player_world = GetPlayerVirtualWorld(playerid),
			menuid = player_world-DOOR_VW_ADDENDUM,
			shop_type;

		if(Properties[menuid][ICost] != -1 && BusinessInfo[menuid][OwnerID] == -1) SendClientMessage(playerid, -1, ""COLOR_ORANGE"Бизнес продается. Подробности: {FFFFFF}/buy");

		if(checkpointid >= BusinessMenu[0] && checkpointid <= BusinessMenu[2]) shop_type = 0;
		if(checkpointid == BusinessMenu[3]) shop_type = 1;
		if(checkpointid == BusinessMenu[4]) shop_type = 2;
		if(checkpointid == BusinessMenu[5]) shop_type = 3;
		if(checkpointid >= BusinessMenu[6] && checkpointid <= BusinessMenu[8]) shop_type = 4;
		if(checkpointid >= BusinessMenu[9] && checkpointid <= BusinessMenu[10]) shop_type = 5;

		SetPVarInt(playerid, "b_menu_id", menuid);
		SetPVarInt(playerid, "shop_type", shop_type);
		Dialog_Show(playerid, Dialog:BusinessMenu);
		return 1;
	}
	return 0;
}	

stock BuyBusiness_agreed(playerid) {

		new menuid = GetPVarInt(playerid, "b_id_buy");

		if(CheckCash(playerid, Properties[menuid][ICost]) == false) return 1;

		RemovePlayerEXP(playerid, Properties[menuid][ICost], "Приобретение бизнеса");
		BusinessInfo[menuid][OwnerID] = PlayerInfo[playerid][pID];

		SetBusinessInt("OwnerID", BusinessInfo[menuid][OwnerID], menuid);

		BusinessInfo[menuid][Income] = 0;
		SetBusinessInt( "Income", BusinessInfo[menuid][Income], menuid);		

		BusinessInfo[menuid][Taxes] = 1;
		SetBusinessInt( "Taxes", BusinessInfo[menuid][Taxes], menuid);			



		format(small_string, sizeof small_string, "Бизнес #%i\n\
			%s\n\
			Владелец: %s\n", 
			BusinessInfo[menuid][ID],
			Properties[menuid][IName],
			PlayerInfo[playerid][pName]
			);

		UpdateDynamic3DTextLabelText(BusinessInfo[menuid][textlbl], -1, small_string);

		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы приобрели бизнес!");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Список ваших бизнесов: {FFFFFF}/business");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Снять прибыль: {FFFFFF}/income");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Не забудьте оплатить аренду в банке штата!");
		return 1;
}


stock SellBusiness_agreed(playerid) {

		new menuid = GetPVarInt(playerid, "b_id_buy");

		AddPlayerEXP(playerid, Properties[menuid][ICost]/2, "Продажа бизнеса");
		BusinessInfo[menuid][OwnerID] = INVALID_ACCOUNT_ID;
		SetBusinessInt("OwnerID", BusinessInfo[menuid][OwnerID], menuid);

		BusinessInfo[menuid][Income] = 0;
		SetBusinessInt( "Income", BusinessInfo[menuid][Income], menuid);		

		BusinessInfo[menuid][Taxes] = 0;
		SetBusinessInt( "Taxes", BusinessInfo[menuid][Taxes], menuid);	

		format(small_string, sizeof small_string, "Бизнес #%i\n\
			%s\n\
			Владелец: отсутствует\n", 
			BusinessInfo[menuid][ID],
			Properties[menuid][IName]
			);

		UpdateDynamic3DTextLabelText(BusinessInfo[menuid][textlbl], -1, small_string);

		GameTextForPlayer(playerid, "Sold", 2500, 1);
		SendClientMessage(playerid, -1, ""COLOR_RED"Вы продали бизнес!");
		return 1;
}

stock buy_shop_item(playerid, business_id, type_id, item_id) {

	printf("player %s called in shop #%d item #%d", PlayerInfo[playerid][pName], business_id, item_id);

	switch(type_id) {
		// 24/7
		case 0: {
			switch(item_id) {
				case 1: {
					if(CheckCash(playerid, COST_SCREW) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					if(PlayerInfo[playerid][pScrew] < 3) {
						RemovePlayerEXP(playerid, COST_SCREW, "Покупка отвертки");
						PlayerInfo[playerid][pScrew] += 1;
						SetPlayerInt(playerid, "Screw", PlayerInfo[playerid][pScrew]);
						SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы приобрели отвертку");
					} else { 
						SendClientMessage(playerid, -1, ""COLOR_RED"Вы уже приобрели максимально допустимое количество отверток");
						return Dialog_Show(playerid, Dialog:BusinessMenu);
					}
				}
				case 2: {
					if(CheckCash(playerid, COST_PAGER) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					if(PlayerInfo[playerid][pDevice] == 0) {
						RemovePlayerEXP(playerid, COST_PAGER, "Покупка пейджера");
						PlayerInfo[playerid][pDevice] = 1;
						SetPlayerInt(playerid, "Device", PlayerInfo[playerid][pDevice]);
						SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы приобрели пейджер. Использовать: "COLOR_WHITE"/sms [id] [текст]");
					} else {
						SendClientMessage(playerid, -1, ""COLOR_RED"У вас уже есть пейджер/мобильный телефон!");
						return Dialog_Show(playerid, Dialog:BusinessMenu);
					}
				}
				case 3: {
					if(CheckCash(playerid, COST_MOBILE) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					if(PlayerInfo[playerid][pDevice] < 2) {
						RemovePlayerEXP(playerid, COST_MOBILE, "Покупка мобильного телефона");
						PlayerInfo[playerid][pDevice] = 2;
						SetPlayerInt(playerid, "Device", PlayerInfo[playerid][pDevice]);
						SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы приобрели мобильный телефон. Использовать: "COLOR_WHITE"/sms [id] [текст]");
					} else { 
						SendClientMessage(playerid, -1, ""COLOR_RED"У вас уже есть мобильный телефон!");
						return Dialog_Show(playerid, Dialog:BusinessMenu);
					}
				}	
				case 4: {
					if(CheckCash(playerid, COST_MASK) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					if(PlayerInfo[playerid][pMask] == 0) {
						RemovePlayerEXP(playerid, COST_MASK, "Покупка маски");
						PlayerInfo[playerid][pMask] = 1;
						SetPlayerInt(playerid, "Mask", PlayerInfo[playerid][pMask]);
						SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы приобрели маску. Чтобы надеть используйте: "COLOR_WHITE"/mask");
						UpdatePlayerProgressQuest(playerid, E_BUY_MASK);
					} else {
						SendClientMessage(playerid, -1, ""COLOR_RED"У вас уже есть маска!");
						return Dialog_Show(playerid, Dialog:BusinessMenu);
					}					
				}
				case 5: {
					Dialog_Show(playerid, Dialog:DIALOG_BUY_SIM_CARD);
				}
				default: return Dialog_Show(playerid, Dialog:BusinessMenu);
			}
			SetPlayerChatBubble(playerid, "оплатил(а) покупку", C_PURPLE, 30.0, 5000);
			format(small_string, sizeof(small_string), "%s оплатил(а) покупку", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
			return 1;		
		}
		
		// Fast Food
		case 1..3: {
			if(PlayerInfo[playerid][pHunger] >= 100) SendClientMessage(playerid, -1, ""COLOR_RED"Ваш персонаж не хочет есть");
			switch(item_id) {
				
				case 1: {
					if(CheckCash(playerid, COST_BUSTER) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					RemovePlayerEXP(playerid, COST_BUSTER, "Восстановление сытости (+20)");
					PlayerInfo[playerid][pHunger] += 20;
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~+20 Satiety", 2000, 6);
					if(PlayerInfo[playerid][pHunger] > 100) PlayerInfo[playerid][pHunger] = 100;
				}
				case 2: {
					if(CheckCash(playerid, COST_2LUX) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					RemovePlayerEXP(playerid, COST_2LUX, "Восстановление сытости (+35)");
					PlayerInfo[playerid][pHunger] += 35;
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~+35 Satiety", 2000, 6);
					if(PlayerInfo[playerid][pHunger] > 100) PlayerInfo[playerid][pHunger] = 100;					
				}
				case 3: {
					if(CheckCash(playerid, COST_RACK) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					RemovePlayerEXP(playerid, COST_RACK, "Восстановление сытости (+50)");
					PlayerInfo[playerid][pHunger] += 50;
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~+50 Satiety", 2000, 6);
					if(PlayerInfo[playerid][pHunger] > 100) PlayerInfo[playerid][pHunger] = 100;						
				}
				case 4: {
					if(CheckCash(playerid, COST_SALAD) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					RemovePlayerEXP(playerid, COST_SALAD, "Восстановление сытости (+40)");
					PlayerInfo[playerid][pHunger] += 40;
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~w~+40 Satiety", 2000, 6);
					if(PlayerInfo[playerid][pHunger] > 100) PlayerInfo[playerid][pHunger] = 100;						
				}
				default: return Dialog_Show(playerid, Dialog:BusinessMenu);
			}		
			SetPlayerInt(playerid, "Hunger", PlayerInfo[playerid][pHunger]);

			ApplyAnimation(playerid,"FOOD","EAT_BURGER",4.1,0,1,1,1,1,1);
			SetPlayerChatBubble(playerid, "съел(а) свой заказ", C_PURPLE, 30.0, 5000);
			format(small_string, sizeof(small_string), "%s съел(а) свой заказ", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
			callcmd::hunger(playerid);
		}
		// Bar
		case 4: {
			if(GetPlayerDrunkLevel(playerid) >= 5000) SendClientMessage(playerid, -1, "- Бармен: Мне кажется, тебе пора домой");
			switch(item_id) {
				case 1: {
					if(CheckCash(playerid, COST_BEER) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					RemovePlayerEXP(playerid, COST_BEER, "Покупка напитков в баре");
					SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 250);
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_BEER);
				}
				case 2: {
					if(CheckCash(playerid, COST_SCOTCH) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					RemovePlayerEXP(playerid, COST_SCOTCH, "Покупка напитков в баре");
					SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 500);	
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_WINE);			
				}
				case 3: {
					if(CheckCash(playerid, COST_GIN) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					RemovePlayerEXP(playerid, COST_GIN, "Покупка напитков в баре");
					SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 300);
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_WINE);
				}
				case 4: {
					if(CheckCash(playerid, COST_VODKA) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					RemovePlayerEXP(playerid, COST_VODKA, "Покупка напитков в баре");
					SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 500);
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_WINE);
				}
				case 5: {
					if(CheckCash(playerid, COST_WINE) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					RemovePlayerEXP(playerid, COST_WINE, "Покупка напитков в баре");
					SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 300);
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_WINE);
				}
				case 6: {
					if(CheckCash(playerid, COST_CHAMPAGNE) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					RemovePlayerEXP(playerid, COST_CHAMPAGNE, "Покупка напитков в баре");
					SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 300);
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_WINE);
				}
				default: return Dialog_Show(playerid, Dialog:BusinessMenu);
			}		

			if(GetPlayerDrunkLevel(playerid) > 2000) ApplyAnimation(playerid, "PED", "WALK_DRUNK", 4.1, 1, 1, 1, 1, 1);

			SetPlayerChatBubble(playerid, "выпил(а)", C_PURPLE, 30.0, 5000);
			format(small_string, sizeof(small_string), "%s выпил(а)", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		}
		// Ammu
		case 5: {
			new ammo = GetPVarInt(playerid, "ammo_to_buy");
			switch(item_id) {
				case 1: {
					if(CheckCash(playerid, COST_9MM*ammo) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					if(PlayerInfo[playerid][slot_2_ammo] < 999) {
						RemovePlayerEXP(playerid, COST_9MM*ammo, "Покупка оружия (weaponid = 22; ammo = %i)", ammo);
						
						GivePlayerWeapon(playerid, 22, ammo);

						PlayerInfo[playerid][slot_2_gun] = 22;
						PlayerInfo[playerid][slot_2_ammo] = ammo;

						SetPlayerInt(playerid, "slot_2_gun", PlayerInfo[playerid][slot_2_gun]);
						SetPlayerInt(playerid, "slot_2_ammo", PlayerInfo[playerid][slot_2_ammo]);

						SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы оплатили и получили своё оружие");
						UpdatePlayerProgressQuest(playerid, E_BUY_WEAPON);
					} else {
						SendClientMessage(playerid, -1, ""COLOR_RED"Больше унести не получится");
						return Dialog_Show(playerid, Dialog:BusinessMenu);
					}
				}
				case 2: {
					if(CheckCash(playerid, COST_SILENCED*ammo) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					if(PlayerInfo[playerid][slot_2_ammo] < 999) {
						RemovePlayerEXP(playerid, COST_SILENCED*ammo, "Покупка оружия (weaponid = 23; ammo = %i)", ammo);
						
						GivePlayerWeapon(playerid, 23, ammo);

						PlayerInfo[playerid][slot_2_gun] = 23;
						PlayerInfo[playerid][slot_2_ammo] = ammo;

						SetPlayerInt(playerid, "slot_2_gun", PlayerInfo[playerid][slot_2_gun]);
						SetPlayerInt(playerid, "slot_2_ammo", PlayerInfo[playerid][slot_2_ammo]);

						SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы оплатили и получили своё оружие");
						UpdatePlayerProgressQuest(playerid, E_BUY_WEAPON);
					} else {
						SendClientMessage(playerid, -1, ""COLOR_RED"Больше унести не получится");
						return Dialog_Show(playerid, Dialog:BusinessMenu);
					}
				}
				case 3: {
					if(CheckCash(playerid, COST_DE*ammo) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					if(PlayerInfo[playerid][slot_2_ammo] < 999) {
						RemovePlayerEXP(playerid, COST_DE*ammo, "Покупка оружия (weaponid = 24; ammo = %i)", ammo);
						
						GivePlayerWeapon(playerid, 24, ammo);

						PlayerInfo[playerid][slot_2_gun] = 24;
						PlayerInfo[playerid][slot_2_ammo] = ammo;

						SetPlayerInt(playerid, "slot_2_gun", PlayerInfo[playerid][slot_2_gun]);
						SetPlayerInt(playerid, "slot_2_ammo", PlayerInfo[playerid][slot_2_ammo]);

						SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы оплатили и получили своё оружие");
						UpdatePlayerProgressQuest(playerid, E_BUY_WEAPON);
					} else {
						SendClientMessage(playerid, -1, ""COLOR_RED"Больше унести не получится");
						return Dialog_Show(playerid, Dialog:BusinessMenu);
					}
				}
				case 4: {
					if(CheckCash(playerid, COST_SHOTGUN*ammo) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					if(PlayerInfo[playerid][slot_3_ammo] < 999) {
						RemovePlayerEXP(playerid, COST_SHOTGUN*ammo, "Покупка оружия (weaponid = 25; ammo = %i)", ammo);
						
						GivePlayerWeapon(playerid, 25, ammo);

						PlayerInfo[playerid][slot_3_gun] = 25;
						PlayerInfo[playerid][slot_3_ammo] = ammo;

						SetPlayerInt(playerid, "slot_3_gun", PlayerInfo[playerid][slot_3_gun]);
						SetPlayerInt(playerid, "slot_3_ammo", PlayerInfo[playerid][slot_3_ammo]);

						SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы оплатили и получили своё оружие");
						UpdatePlayerProgressQuest(playerid, E_BUY_WEAPON);
					} else {
						SendClientMessage(playerid, -1, ""COLOR_RED"Больше унести не получится");
						return Dialog_Show(playerid, Dialog:BusinessMenu);
					}
				}
				case 5: {
					if(CheckCash(playerid, COST_AK*ammo) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					if(PlayerInfo[playerid][slot_5_ammo] < 999) {
						RemovePlayerEXP(playerid, COST_AK*ammo, "Покупка оружия (weaponid = 30; ammo = %i)", ammo);
						
						GivePlayerWeapon(playerid, 30, ammo);

						PlayerInfo[playerid][slot_5_gun] = 30;
						PlayerInfo[playerid][slot_5_ammo] = ammo;

						SetPlayerInt(playerid, "slot_5_gun", PlayerInfo[playerid][slot_5_gun]);
						SetPlayerInt(playerid, "slot_5_ammo", PlayerInfo[playerid][slot_5_ammo]);

						SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы оплатили и получили своё оружие");
						UpdatePlayerProgressQuest(playerid, E_BUY_WEAPON);
					} else {
						SendClientMessage(playerid, -1, ""COLOR_RED"Больше унести не получится");
						return Dialog_Show(playerid, Dialog:BusinessMenu);
					}
				}
				case 6: {
					if(CheckCash(playerid, COST_AK*ammo) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					if(PlayerInfo[playerid][slot_5_ammo] < 999) {
						RemovePlayerEXP(playerid, COST_AK*ammo, "Покупка оружия (weaponid = 31; ammo = %i)", ammo);
						
						GivePlayerWeapon(playerid, 31, ammo);

						PlayerInfo[playerid][slot_5_gun] = 31;
						PlayerInfo[playerid][slot_5_ammo] = ammo;

						SetPlayerInt(playerid, "slot_5_gun", PlayerInfo[playerid][slot_5_gun]);
						SetPlayerInt(playerid, "slot_5_ammo", PlayerInfo[playerid][slot_5_ammo]);

						SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы оплатили и получили своё оружие");
						UpdatePlayerProgressQuest(playerid, E_BUY_WEAPON);
					} else {
						SendClientMessage(playerid, -1, ""COLOR_RED"Больше унести не получится");
						return Dialog_Show(playerid, Dialog:BusinessMenu);
					}
				}	
				case 7: {
					if(CheckCash(playerid, COST_SMG*ammo) == false) return Dialog_Show(playerid, Dialog:BusinessMenu);
					if(PlayerInfo[playerid][slot_4_ammo] < 999) {
						RemovePlayerEXP(playerid, COST_SMG*ammo, "Покупка оружия (weaponid = 32; ammo = %i)", ammo);
						
						GivePlayerWeapon(playerid, 32, ammo);

						PlayerInfo[playerid][slot_4_gun] = 32;
						PlayerInfo[playerid][slot_4_ammo] = ammo;

						SetPlayerInt(playerid, "slot_4_gun", PlayerInfo[playerid][slot_4_gun]);
						SetPlayerInt(playerid, "slot_4_ammo", PlayerInfo[playerid][slot_4_ammo]);

						SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы оплатили и получили своё оружие");
						UpdatePlayerProgressQuest(playerid, E_BUY_WEAPON);
					} else {
						SendClientMessage(playerid, -1, ""COLOR_RED"Больше унести не получится");
						return Dialog_Show(playerid, Dialog:BusinessMenu);
					}
				}	
				default: return Dialog_Show(playerid, Dialog:BusinessMenu);
			}
			Dialog_Show(playerid, Dialog:BusinessMenu);
			SetPlayerChatBubble(playerid, "оплатил(а) покупку", C_PURPLE, 30.0, 5000);
			format(small_string, sizeof(small_string), "%s оплатил(а) покупку", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		}				
		
	}
	return 1;
}

DialogCreate:BusinessManage(playerid) {

    new business_string[256],
    	total_b = 0;
    strcat(business_string, "Название\tПрибыль\tАренда\n"); 

	for(new i = 0; i < MAX_BUSINESS; i++) {

		if(total_b == 0) SetPVarInt(playerid, "business_n_1", i);
		if(total_b == 1) SetPVarInt(playerid, "business_n_2", i);
		if(total_b == 2) SetPVarInt(playerid, "business_n_3", i);

		if(BusinessInfo[i][OwnerID] != PlayerInfo[playerid][pID]) continue;
		total_b += 1;
    	format(business_string, sizeof(business_string),
    	"%s%s\t%i\t%d дн.\n",
		business_string,
		Properties[i][IName],
		BusinessInfo[i][Income],
		BusinessInfo[i][Taxes]); 
	}

	if(total_b == 0) return SendClientMessage(playerid, -1, "Вы не владеете бизнесами"); 

	Dialog_Open(playerid, Dialog:BusinessManage, DIALOG_STYLE_TABLIST_HEADERS,
        "Бизнесы",
        business_string,
        "OK", "Закрыть");
	return 1;
}

DialogCreate:BusinessMenu(playerid) {

	new menuid = GetPVarInt(playerid, "shop_type"),
		b_title_string[24] = EOS;

	huge_string[0] = EOS;
	huge_string = !"№\tТовар\tСтоимость\n";

	switch(menuid) {
		// 24/7
		case 0: {
			strcat(b_title_string, ""COLOR_BLUE"24/7"); 
			format(big_string, sizeof big_string,
				"1\tОтвертка\t"COLOR_GREEN"%d\n\
				2\tПейджер\t"COLOR_GREEN"%d\n\
				3\tТелефон\t"COLOR_GREEN"%d\n\
				4\tМаска\t"COLOR_GREEN"%d\n\
				5\tSIM-карта\t"COLOR_GREEN"%d",
				COST_SCREW,
				COST_PAGER,
				COST_MOBILE,
				COST_MASK,
				COST_SIM
			);
			strcat(huge_string, big_string);
		}
		// Pizza
		case 1: {
			strcat(b_title_string, ""COLOR_BLUE"Pizza Stack"); 
			format(big_string, sizeof big_string,
				"1\tБастер\t"COLOR_GREEN"%d\n\
				2\tДвойной люкс\t"COLOR_GREEN"%d\n\
				3\tГора Еды\t"COLOR_GREEN"%d\n\
				4\tСалат\t"COLOR_GREEN"%d",
				COST_BUSTER,
				COST_2LUX,
				COST_RACK,
				COST_SALAD
			);			
			strcat(huge_string, big_string);
		}		
		// Cluck
		case 2: {
			strcat(b_title_string, ""COLOR_BLUE"Cluckin' Bell"); 
			format(big_string, sizeof big_string,
				"1\tМини-комбо\t"COLOR_GREEN"%d\n\
				2\tБольшое комбо\t"COLOR_GREEN"%d\n\
				3\tОгромное комбо\t"COLOR_GREEN"%d\n\
				4\tСалат\t"COLOR_GREEN"%d",
				COST_BUSTER,
				COST_2LUX,
				COST_RACK,
				COST_SALAD
			);		
			strcat(huge_string, big_string);	
		}
		// Burger Shot
		case 3: {
			strcat(b_title_string, ""COLOR_BLUE"Burger Shot"); 
			format(big_string, sizeof big_string,
				"1\tДетский набор\t"COLOR_GREEN"%d\n\
				2\tBeef Tower\t"COLOR_GREEN"%d\n\
				3\tMeat Stack\t"COLOR_GREEN"%d\n\
				4\tСалат\t"COLOR_GREEN"%d",
				COST_BUSTER,
				COST_2LUX,
				COST_RACK,
				COST_SALAD
			);			
			strcat(huge_string, big_string);
		}
		// Бары
		case 4: {
			strcat(b_title_string, ""COLOR_BLUE"Bar"); 
			format(big_string, sizeof big_string,
				"1\tБокал пива\t"COLOR_GREEN"%d\n\
				2\tСкотч\t"COLOR_GREEN"%d\n\
				3\tДжин\t"COLOR_GREEN"%d\n\
				4\tВодка\t"COLOR_GREEN"%d\n\
				5\tВино\t"COLOR_GREEN"%d\n\
				6\tШампанское\t"COLOR_GREEN"%d",
				COST_BEER,
				COST_SCOTCH,
				COST_GIN,
				COST_VODKA,
				COST_WINE,
				COST_CHAMPAGNE
			);				
			strcat(huge_string, big_string);
		}
		// Аммунация
		case 5: {
			strcat(b_title_string, ""COLOR_BLUE"Ammu-Nation"); 
			format(big_string, sizeof big_string,
				"1\tПистолет 9mm\t"COLOR_GREEN"%d\n\
				2\tПистолет с глушителем\t"COLOR_GREEN"%d\n\
				3\tПустынный орел\t"COLOR_GREEN"%d\n\
				4\tДробовик\t"COLOR_GREEN"%d\n\
				5\tАК-47\t"COLOR_GREEN"%d\n\
				6\tМ4\t"COLOR_GREEN"%d\n\
				7\tTec-9\t"COLOR_GREEN"%d",
				COST_9MM,
				COST_SILENCED,
				COST_DE,
				COST_SHOTGUN,
				COST_AK,
				COST_AK,
				COST_SMG
			);
			strcat(huge_string, big_string);	
		}
	}

	Dialog_Open(playerid, Dialog:BusinessMenu, DIALOG_STYLE_TABLIST_HEADERS,
        b_title_string,
        huge_string,
        "Выбрать", "Закрыть"
    );		
	return 1;
}

DialogCreate:BusinessManageInput(playerid) {

    new business_string[256] = EOS,
    	total_b = 0;

    strcat(business_string, ""COLOR_WHITE""); 

	for(new i = 0; i < MAX_BUSINESS; i++) {
		if(BusinessInfo[i][OwnerID] != PlayerInfo[playerid][pID]) continue;
		total_b += 1;
    	format(business_string, sizeof(business_string),
    	"%s%d | %s\n",
		business_string,
		i+1,
		Properties[i][IName]); 
	}

	if(total_b == 0) return SendClientMessage(playerid, -1, "Вы не владеете бизнесами");
 
	strcat(business_string, "\n\n"COLOR_ORANGE"Введите номер выбранного бизнеса"); 

	Dialog_Open(playerid, Dialog:BusinessManageInput, DIALOG_STYLE_INPUT,
        "Ваши бизнесы",
        business_string,
        "Выбрать", "Закрыть");
	return 1;
}

DialogCreate:InputBusinessInfo(playerid) {

		new b_to_get_info = GetPVarInt(playerid, "b_info_get"),
			b_name_string[36];

		b_to_get_info -= 1;

    	format(small_string, sizeof(small_string),
    	""COLOR_ORANGE"Прибыль на балансе: {FFFFFF}%d\n\
    	"COLOR_ORANGE"Дней аренды: {FFFFFF}%d\n",
		BusinessInfo[b_to_get_info][Income],
		BusinessInfo[b_to_get_info][Taxes]); 

		format(b_name_string, sizeof(b_name_string),
			"%s", Properties[b_to_get_info][IName]);

		Dialog_Open(playerid, Dialog:InputBusinessInfo, DIALOG_STYLE_MSGBOX,
	        b_name_string,
	        small_string,
	        "Назад", "Закрыть");
}

DialogCreate:BusinessBuyAgreement(playerid) {
		new menuid = GetPVarInt(playerid, "b_id_buy");

		format(small_string, sizeof small_string, ""COLOR_WHITE"Вы действительно хотите приобрести данный бизнес за "COLOR_GREEN"%d?", 
		Properties[menuid][ICost]
		);

		Dialog_Open(playerid, Dialog:BusinessBuyAgreement, DIALOG_STYLE_MSGBOX,
	        "Внимание",
	        small_string,
	        "Да", "Нет");
}

DialogCreate:BusinessSellAgreement(playerid) {
		new menuid = GetPVarInt(playerid, "b_id_buy");

		format(small_string, sizeof small_string, ""COLOR_WHITE"Вы действительно хотите продать бизнес за "COLOR_GREEN"%d?", 
		Properties[menuid][ICost]/2
		);

		Dialog_Open(playerid, Dialog:BusinessSellAgreement, DIALOG_STYLE_MSGBOX,
	        "Внимание",
	        small_string,
	        "Да", "Нет");
}

DialogCreate:GunAmmo(playerid) {
		Dialog_Open(playerid, Dialog:GunAmmo, DIALOG_STYLE_INPUT,
	        "Покупка",
	        ""COLOR_WHITE"Введите количество патронов",
	        "Далее", "Назад");
}

DialogResponse:GunAmmo(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return Dialog_Show(playerid, Dialog:BusinessMenu);
	} else {
	new b_buy_id = GetPVarInt(playerid, "b_menu_id"),
		gun_id = GetPVarInt(playerid, "gun_id_buy"),
		strval_inputtext = strval(inputtext);		

	if(strval_inputtext < 0 || strval_inputtext > 999) return Dialog_Show(playerid, Dialog:BusinessMenu);

	SetPVarInt(playerid, "ammo_to_buy", strval_inputtext);

	buy_shop_item(playerid, b_buy_id, 5, gun_id);	
	}
	return 1;
}

DialogResponse:BusinessMenu(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
	new menuid = GetPVarInt(playerid, "shop_type"),
		b_buy_id = GetPVarInt(playerid, "b_menu_id"),
		item_buy;

	if(Platform[playerid] == 0) {
	item_buy = strval(inputtext);
	} else {
	item_buy = listitem+1;
	}

	if(menuid == 5) return Dialog_Show(playerid, Dialog:GunAmmo), SetPVarInt(playerid, "gun_id_buy", item_buy);
	
	buy_shop_item(playerid, b_buy_id, menuid, item_buy);	
	}
	return 1;
}

DialogResponse:InputBusinessInfo(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		callcmd::business(playerid);
	}
	return 1;
}

DialogResponse:BusinessManageInput(playerid, response, listitem, inputtext[]) {
	if(!response) {

		if(IsPlayerInRangeOfPoint(playerid, 5, 1401.232543, -1684.396850, 13.583753)) {
			return Dialog_Bank_Property(playerid);
		}

		return 0;
	} else {
		new 
			strval_inputtext = strval(inputtext);

		if(strval_inputtext < 0 || strval_inputtext > 99) return callcmd::business(playerid);
		if(BusinessInfo[strval_inputtext-1][OwnerID] == GetPlayerAccountID(playerid)) {		
		SetPVarInt(playerid, "b_info_get", strval_inputtext);

		SetPVarInt(playerid, "b_rent", strval_inputtext-1);

		if(IsPlayerInRangeOfPoint(playerid, 5, 1401.232543, -1684.396850, 13.583753)) {
			return Dialog_Show(playerid, Dialog:BusinessRentInput);
		}

		Dialog_Show(playerid, Dialog:InputBusinessInfo);

		} else {
			callcmd::business(playerid);
		}

	}
	return 1;
}


DialogResponse:BusinessManage(playerid, response, listitem, inputtext[]) {
	if(!response) {
		if(IsPlayerInRangeOfPoint(playerid, 5, 1401.232543, -1684.396850, 13.583753)) {
			return Dialog_Bank_Property(playerid);
		}
	} else {
		if(IsPlayerInRangeOfPoint(playerid, 5, 1401.232543, -1684.396850, 13.583753)) {

			new business_chosen;
			switch(listitem) {
				case 0: {
					business_chosen = GetPVarInt(playerid, "business_n_1");
				}
				case 1: {
					business_chosen = GetPVarInt(playerid, "business_n_2");
				}
				case 2: {
					business_chosen = GetPVarInt(playerid, "business_n_3");
				}
			}
			SetPVarInt(playerid, "b_rent", business_chosen);
			Dialog_Show(playerid, Dialog:BusinessRentInput);
		}
	}
	return 1;
}

DialogResponse:BusinessBuyAgreement(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		BuyBusiness_agreed(playerid);
	}
	return 1;
}

DialogResponse:BusinessSellAgreement(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return 0;
	} else {
		SellBusiness_agreed(playerid);
	}
	return 1;
}

DialogCreate:BusinessRentInput(playerid) {

	Dialog_Open(playerid, Dialog:BusinessRentInput, DIALOG_STYLE_INPUT,
        "Касса",
        ""COLOR_WHITE"Введите количество дней продлеваемой аренды",
        "Да", "Отмена");	

}

DialogResponse:BusinessRentInput(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return Dialog_Bank_Property(playerid);
	} else {
		new strval_inputtext = strval(inputtext);

		if(strval_inputtext <= 7 && strval_inputtext > 0) {
			SetPVarInt(playerid, "days_rent_b", strval_inputtext);
			Dialog_Show(playerid, Dialog:BusinessRent);
			return 1;
		} else {
			return Dialog_Show(playerid, Dialog:BusinessRentInput);
		}
	}
}

DialogCreate:BusinessRent(playerid) {

			
	new business_chosen = GetPVarInt(playerid, "b_rent"),
		days_rent = GetPVarInt(playerid, "days_rent_b"),
		rent_string[64],
		income_hourly = Properties[business_chosen][ICost]/60,
		just_business = income_hourly/2;		

	format(rent_string, sizeof(rent_string), "%s", Properties[business_chosen][IName]);
	format(small_string, sizeof(small_string), ""COLOR_WHITE"Оплатить %d EXP за %d дней аренды?", just_business*days_rent, days_rent);

	Dialog_Open(playerid, Dialog:BusinessRent, DIALOG_STYLE_MSGBOX,
        rent_string,
        small_string,
        "Да", "Отмена");	

}

DialogResponse:BusinessRent(playerid, response, listitem, inputtext[]) {
	if(!response) {
		return Dialog_Bank_Property(playerid);
	} else {
		new business_chosen = GetPVarInt(playerid, "b_rent"),
			days_rent = GetPVarInt(playerid, "days_rent_b"),
			income_hourly = Properties[business_chosen][ICost]/60,
			just_business = income_hourly/2;

		if(BusinessInfo[business_chosen][Taxes] >= 7) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Бизнес уже оплачен на максимальный срок"), Dialog_Bank_Property(playerid);
		}

		if(BusinessInfo[business_chosen][Taxes]+days_rent > 7) {
			format(small_string, sizeof(small_string), ""COLOR_RED"Бизнес оплачен на %d дней, вы собираетесь оплатить на %d дней", BusinessInfo[business_chosen][Taxes], days_rent);
			SendClientMessage(playerid, -1, small_string);	
			SendClientMessage(playerid, -1, ""COLOR_RED"Оплатить можно максимум на 7 дней!");
			Dialog_Show(playerid, Dialog:BusinessRentInput);
			return 1;
		}	

		if(CheckCash(playerid, just_business*days_rent) == false) return 1;
		RemovePlayerEXP(playerid, just_business*days_rent, "Оплата арендной платы бизнеса");	

		format(small_string, sizeof small_string, "~n~~n~~n~~n~~n~~r~-%d EXP~n~~g~+%d DAYS", just_business*days_rent, days_rent);
		GameTextForPlayer(playerid, small_string, 2000, 6);		

		BusinessInfo[business_chosen][Taxes] += days_rent;
		SetBusinessInt("Taxes", BusinessInfo[business_chosen][Taxes], business_chosen);	
		callcmd::me(playerid, "оплатил(а) арендную плату за бизнес");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы оплатили аренду вашего бизнеса");
		//callcmd::business(playerid);
	}
	return 1;
}

CMD:business(playerid) {
	if(Platform[playerid] == 0) {
		Dialog_Show(playerid, Dialog:BusinessManageInput);
		return 1;
	} else Dialog_Show(playerid, Dialog:BusinessManage);
	return 1;
}

CMD:income(playerid) {
	new 
		player_world = GetPlayerVirtualWorld(playerid);

	if(player_world < DOOR_VW_ADDENDUM) return SendClientMessage(playerid, -1, "Используйте эту функцию находясь внутри своего бизнеса");

	new menuid = player_world-DOOR_VW_ADDENDUM;

	if(BusinessInfo[menuid][OwnerID] == PlayerInfo[playerid][pID]) {
		new income = BusinessInfo[menuid][Income];
		if(income <= 0) return SendClientMessage(playerid, -1, "Прибыль отсутствует");
		printf("[bizz_debug] [bid:%d] Снимается прибыль, переменная была равна %d", menuid, BusinessInfo[menuid][Income]);
		BusinessInfo[menuid][Income] = 0;
		printf("[bizz_debug] [bid:%d] Снимается прибыль, переменная теперь равна %d", menuid, BusinessInfo[menuid][Income]);
		SetBusinessInt("Income", BusinessInfo[menuid][Income], menuid);

		AddPlayerEXP(playerid, income, "Снятие прибыли с бизнеса");
		PlayerPlaySound(playerid, ATM_WITHDRAW_SOUND, 0, 0, 0);	

		callcmd::me(playerid, "достал(а) наличные из кассы");

		format(small_string, sizeof small_string, "Ваша прибыль: %i$", income);
		SendClientMessage(playerid, -1, small_string);
	} else {
		return SendClientMessage(playerid, -1, "Вы должны быть в своем бизнесе");
	}
	return 1;
}

CMD:sell(playerid) {
	new 
		player_world = GetPlayerVirtualWorld(playerid);

	if(player_world < DOOR_VW_ADDENDUM) return SendClientMessage(playerid, -1, "Используйте эту функцию находясь внутри своего бизнеса");
	new menuid = player_world-DOOR_VW_ADDENDUM;

	if(BusinessInfo[menuid][OwnerID] == PlayerInfo[playerid][pID]) {

		SetPVarInt(playerid, "b_id_buy", menuid);
		SetPVarInt(playerid, "b_info_get", BUSINESS_COST);

		Dialog_Show(playerid, Dialog:BusinessSellAgreement);

	} else {
		return 1;
	}
	return 1;
}

CMD:buy(playerid) {
	new 
		player_world = GetPlayerVirtualWorld(playerid);


	if(player_world < DOOR_VW_ADDENDUM) return SendClientMessage(playerid, -1, "Используйте эту функцию находясь внутри бизнеса");
	new menuid = player_world-DOOR_VW_ADDENDUM;

	if(BusinessInfo[menuid][OwnerID] == INVALID_ACCOUNT_ID) {
	    new total_b = 0;

		for(new i = 0; i < MAX_BUSINESS; i++) {
			if(BusinessInfo[i][OwnerID] != PlayerInfo[playerid][pID]) continue;
			total_b += 1;
		}
		if(total_b >= 3) return SendClientMessage(playerid, -1, "Вы достигли максимально допустимое количество бизнесов");


		if(CheckCash(playerid, Properties[menuid][ICost]) == false) return 1;

		SetPVarInt(playerid, "b_id_buy", menuid);
		SetPVarInt(playerid, "b_info_get", BUSINESS_COST);

		Dialog_Show(playerid, Dialog:BusinessBuyAgreement);
	} else {
		return SendClientMessage(playerid, -1, ""COLOR_RED"Бизнес уже имеет владельца");
	}
	return 1;
}

stock BusinessIncome() {
		for(new i = 0; i < MAX_BUSINESS; i++) {
		if(BusinessInfo[i][OwnerID] == INVALID_ACCOUNT_ID) continue;
		printf("[bizz_debug] [bid:%d] Прибыль пришла нахуй было: %d", i, BusinessInfo[i][Income]);
		new income_hourly = Properties[i][ICost]/30;
		BusinessInfo[i][Income] += income_hourly/24;
		SetBusinessInt("Income", BusinessInfo[i][Income], i);
		printf("[bizz_debug] [bid:%d] Прибыль пришла нахуй стало: %d", i, BusinessInfo[i][Income]);
	}
}

DialogCreate:ClothesShop(playerid) {

		new cost;
		new shop_id = GetPVarInt(playerid, "ShopSkin");

		switch(shop_id) {
			case 1: cost = 5000;
			case 2: cost = 45000;
			case 3: cost = 10000;
			case 4: cost = 20000;
		}

		format(small_string, sizeof(small_string), ""COLOR_BLUE"Выбирайте одежду нажатием кнопки 'Далее'\n"COLOR_WHITE"Стоимость любого костюма в этом магазине: "COLOR_GREEN"%d EXP", cost);

		Dialog_Open(playerid, Dialog:ClothesShop, DIALOG_STYLE_MSGBOX,
	        "Магазин одежды",
	        small_string,
	        "Далее", "Закрыть");
}

DialogResponse:ClothesShop(playerid, response, listitem, inputtext[]) {
	if(!response) {
		//SetPVarInt(playerid, "SelSkin", 1);
		//CBackSkin(playerid);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Чтобы купить примеренный костюм пройдите на кассу");
		SendClientMessage(playerid, -1, "(( Временная примерка длится 25 секунд ))");
		return 1;
	} else {
		new shop_id = GetPVarInt(playerid, "ShopSkin");
		SetPVarInt(playerid,"SkinSel",gettime() + 25);

		if(IsValidTimer(bskin[playerid])) KillTimer(bskin[playerid]),bskin[playerid] = -1;
		bskin[playerid] = SetTimerEx("CBackSkin", 25000, false, "d", playerid);

		if(shop_id == 1) {
			if(PlayerInfo[playerid][pSex] == 0) {
				switch(GetPVarInt(playerid, "SelSkin"))
				{
					case 1: {
						SetPVarInt(playerid, "SelSkin", 2);
						SetPlayerSkin(playerid, 15);
					}
					case 2: {
						SetPVarInt(playerid, "SelSkin", 3);
						SetPlayerSkin(playerid, 21);
					}
					case 3: {
						SetPVarInt(playerid, "SelSkin", 4);
						SetPlayerSkin(playerid, 25);
					}
					case 4: {
						SetPVarInt(playerid, "SelSkin", 5);
						SetPlayerSkin(playerid, 26);
					}
					case 5: {
						SetPVarInt(playerid, "SelSkin", 6);
						SetPlayerSkin(playerid, 44);
					}
					case 6: {
						SetPVarInt(playerid, "SelSkin", 7);
						SetPlayerSkin(playerid, 50);
					}
					case 7: {
						SetPVarInt(playerid, "SelSkin", 8);
						SetPlayerSkin(playerid, 58);
					}
					case 8: {
						SetPVarInt(playerid, "SelSkin", 9);
						SetPlayerSkin(playerid, 30);
					}
					case 9: {
						SetPVarInt(playerid, "SelSkin", 10);
						SetPlayerSkin(playerid, 32);
					}
					case 10: {
						SetPVarInt(playerid, "SelSkin", 11);
						SetPlayerSkin(playerid, 35);
					}
					case 11: {
						SetPVarInt(playerid, "SelSkin", 12);
						SetPlayerSkin(playerid, 36);
					}
					case 12: {
						SetPVarInt(playerid, "SelSkin", 13);
						SetPlayerSkin(playerid, 37);
					}
					case 13: {
						SetPVarInt(playerid, "SelSkin", 14);
						SetPlayerSkin(playerid, 96);
					}
					case 14: {
						SetPVarInt(playerid, "SelSkin", 15);
						SetPlayerSkin(playerid, 95);
					}
					case 15: {
						SetPVarInt(playerid, "SelSkin", 16);
						SetPlayerSkin(playerid, 142);
					}
					case 16: {
						SetPVarInt(playerid, "SelSkin", 17);
						SetPlayerSkin(playerid, 183);
					}
					case 17: {
						SetPVarInt(playerid, "SelSkin", 0);
					}
					default: {
						SetPVarInt(playerid, "SelSkin", 1);
						SetPlayerSkin(playerid, 14);
					}
				}
			}
			if(PlayerInfo[playerid][pSex] == 1) {
				switch(GetPVarInt(playerid, "SelSkin"))
				{
					case 1: {
						SetPVarInt(playerid, "SelSkin", 2);
						SetPlayerSkin(playerid, 13);
					}
					case 2: {
						SetPVarInt(playerid, "SelSkin", 3);
						SetPlayerSkin(playerid, 41);
					}
					case 3: {
						SetPVarInt(playerid, "SelSkin", 4);
						SetPlayerSkin(playerid, 56);
					}
					case 4: {
						SetPVarInt(playerid, "SelSkin", 5);
						SetPlayerSkin(playerid, 193);
					}
					case 5: {
						SetPVarInt(playerid, "SelSkin", 6);
						SetPlayerSkin(playerid, 90);
					}
					case 6: {
						SetPVarInt(playerid, "SelSkin", 7);
						SetPlayerSkin(playerid, 226);
					}
					case 7: {
						SetPVarInt(playerid, "SelSkin", 8);
						SetPlayerSkin(playerid, 195);
					}
					case 8: {
						SetPVarInt(playerid, "SelSkin", 0);
					}
					default: {
						SetPVarInt(playerid, "SelSkin", 1);
						SetPlayerSkin(playerid, 193);
					}
				}
			}
		}
		if(shop_id == 2) {
			if(PlayerInfo[playerid][pSex] == 0) {
				switch(GetPVarInt(playerid, "SelSkin"))
				{
					case 1: {
						SetPVarInt(playerid, "SelSkin", 2);
						SetPlayerSkin(playerid, 264);
					}
					case 2: {
						SetPVarInt(playerid, "SelSkin", 3);
						SetPlayerSkin(playerid, 290);
					}
					case 3: {
						SetPVarInt(playerid, "SelSkin", 4);
						SetPlayerSkin(playerid, 291);
					}
					case 4: {
						SetPVarInt(playerid, "SelSkin", 5);
						SetPlayerSkin(playerid, 292);
					}
					case 5: {
						SetPVarInt(playerid, "SelSkin", 6);
						SetPlayerSkin(playerid, 293);
					}
					case 6: {
						SetPVarInt(playerid, "SelSkin", 7);
						SetPlayerSkin(playerid, 294);
					}
					case 7: {
						SetPVarInt(playerid, "SelSkin", 8);
						SetPlayerSkin(playerid, 46);
					}
					case 8: {
						SetPVarInt(playerid, "SelSkin", 9);
						SetPlayerSkin(playerid, 49);
					}
					case 9: {
						SetPVarInt(playerid, "SelSkin", 10);
						SetPlayerSkin(playerid, 59);
					}
					case 10: {
						SetPVarInt(playerid, "SelSkin", 11);
						SetPlayerSkin(playerid, 68);
					}
					case 11: {
						SetPVarInt(playerid, "SelSkin", 12);
						SetPlayerSkin(playerid, 82);
					}
					case 12: {
						SetPVarInt(playerid, "SelSkin", 13);
						SetPlayerSkin(playerid, 83);
					}
					case 13: {
						SetPVarInt(playerid, "SelSkin", 14);
						SetPlayerSkin(playerid, 84);
					}
					case 14: {
						SetPVarInt(playerid, "SelSkin", 15);
						SetPlayerSkin(playerid, 295);
					}
					case 15: {
						SetPVarInt(playerid, "SelSkin", 16);
						SetPlayerSkin(playerid, 296);
					}
					case 16: {
						SetPVarInt(playerid, "SelSkin", 17);
						SetPlayerSkin(playerid, 185);
					}
					case 17: {
						SetPVarInt(playerid, "SelSkin", 18);
						SetPlayerSkin(playerid, 186);
					}
					case 18: {
						SetPVarInt(playerid, "SelSkin", 19);
						SetPlayerSkin(playerid, 297);
					}
					case 19: {
						SetPVarInt(playerid, "SelSkin", 20);
						SetPlayerSkin(playerid, 119);
					}
					case 20: {
						SetPVarInt(playerid, "SelSkin", 21);
						SetPlayerSkin(playerid, 126);
					}
					case 21: {
						SetPVarInt(playerid, "SelSkin", 22);
						SetPlayerSkin(playerid, 167);
					}
					case 22: {
						SetPVarInt(playerid, "SelSkin", 23);
						SetPlayerSkin(playerid, 181);
					}
					case 23: {
						SetPVarInt(playerid, "SelSkin", 24);
						SetPlayerSkin(playerid, 203);
					}
					case 24: {
						SetPVarInt(playerid, "SelSkin", 25);
						SetPlayerSkin(playerid, 249);
					}
					case 25: {
						SetPVarInt(playerid, "SelSkin", 0);
					}
					default: {
						SetPVarInt(playerid, "SelSkin", 1);
						SetPlayerSkin(playerid, 299);
					}
				}
			}
			if(PlayerInfo[playerid][pSex] == 1) {
				switch(GetPVarInt(playerid, "SelSkin"))
				{
					case 1: {
						SetPVarInt(playerid, "SelSkin", 2);
						SetPlayerSkin(playerid, 91);
					}
					case 2: {
						SetPVarInt(playerid, "SelSkin", 3);
						SetPlayerSkin(playerid, 216);
					}
					case 3: {
						SetPVarInt(playerid, "SelSkin", 0);
					}
					default: {
						SetPVarInt(playerid, "SelSkin", 1);
						SetPlayerSkin(playerid, 214);
					}
				}
			}
		}
		if(shop_id == 3) {
			if(PlayerInfo[playerid][pSex] == 0) {
				switch(GetPVarInt(playerid, "SelSkin"))
				{
					case 1: {
						SetPVarInt(playerid, "SelSkin", 2);
						SetPlayerSkin(playerid, 19);
					}
					case 2: {
						SetPVarInt(playerid, "SelSkin", 3);
						SetPlayerSkin(playerid, 22);
					}
					case 3: {
						SetPVarInt(playerid, "SelSkin", 4);
						SetPlayerSkin(playerid, 28);
					}
					case 4: {
						SetPVarInt(playerid, "SelSkin", 5);
						SetPlayerSkin(playerid, 45);
					}
					case 5: {
						SetPVarInt(playerid, "SelSkin", 6);
						SetPlayerSkin(playerid, 73);
					}
					case 6: {
						SetPVarInt(playerid, "SelSkin", 7);
						SetPlayerSkin(playerid, 170);
					}
					case 7: {
						SetPVarInt(playerid, "SelSkin", 8);
						SetPlayerSkin(playerid, 143);
					}
					case 8: {
						SetPVarInt(playerid, "SelSkin", 9);
						SetPlayerSkin(playerid, 144);
					}
					case 9: {
						SetPVarInt(playerid, "SelSkin", 10);
						SetPlayerSkin(playerid, 258);
					}
					case 10: {
						SetPVarInt(playerid, "SelSkin", 11);
						SetPlayerSkin(playerid, 97);
					}
					case 11: {
						SetPVarInt(playerid, "SelSkin", 12);
						SetPlayerSkin(playerid, 184);
					}
					case 12: {
						SetPVarInt(playerid, "SelSkin", 13);
						SetPlayerSkin(playerid, 67);
					}
					case 13: {
						SetPVarInt(playerid, "SelSkin", 14);
						SetPlayerSkin(playerid, 180);
					}
					case 14: {
						SetPVarInt(playerid, "SelSkin", 15);
						SetPlayerSkin(playerid, 24);
					}
					case 15: {
						SetPVarInt(playerid, "SelSkin", 16);
						SetPlayerSkin(playerid, 177);
					}
					case 16: {
						SetPVarInt(playerid, "SelSkin", 17);
						SetPlayerSkin(playerid, 176);
					}
					case 17: {
						SetPVarInt(playerid, "SelSkin", 18);
						SetPlayerSkin(playerid, 18);
					}
					case 18: {
						SetPVarInt(playerid, "SelSkin", 19);
						SetPlayerSkin(playerid, 24);
					}
					case 19: {
						SetPVarInt(playerid, "SelSkin", 0);
					}
					default: {
						SetPVarInt(playerid, "SelSkin", 1);
						SetPlayerSkin(playerid, 7);
					}
				}
			}
			if(PlayerInfo[playerid][pSex] == 1) {
				switch(GetPVarInt(playerid, "SelSkin"))
				{
					case 1: {
						SetPVarInt(playerid, "SelSkin", 2);
						SetPlayerSkin(playerid, 55);
					}
					case 2: {
						SetPVarInt(playerid, "SelSkin", 3);
						SetPlayerSkin(playerid, 40);
					}
					case 3: {
						SetPVarInt(playerid, "SelSkin", 4);
						SetPlayerSkin(playerid, 192);
					}
					case 4: {
						SetPVarInt(playerid, "SelSkin", 0);
					}
					default: {
						SetPVarInt(playerid, "SelSkin", 1);
						SetPlayerSkin(playerid, 69);
					}
				}
			}			
		}
		if(shop_id == 4) {
			if(PlayerInfo[playerid][pSex] == 0) {
				switch(GetPVarInt(playerid, "SelSkin"))
				{
					case 1: {
						SetPVarInt(playerid, "SelSkin", 2);
						SetPlayerSkin(playerid, 17);
					}
					case 2: {
						SetPVarInt(playerid, "SelSkin", 3);
						SetPlayerSkin(playerid, 20);
					}
					case 3: {
						SetPVarInt(playerid, "SelSkin", 4);
						SetPlayerSkin(playerid, 156);
					}
					case 4: {
						SetPVarInt(playerid, "SelSkin", 5);
						SetPlayerSkin(playerid, 23);
					}
					case 5: {
						SetPVarInt(playerid, "SelSkin", 6);
						SetPlayerSkin(playerid, 29);
					}
					case 6: {
						SetPVarInt(playerid, "SelSkin", 7);
						SetPlayerSkin(playerid, 33);
					}
					case 7: {
						SetPVarInt(playerid, "SelSkin", 8);
						SetPlayerSkin(playerid, 47);
					}
					case 8: {
						SetPVarInt(playerid, "SelSkin", 9);
						SetPlayerSkin(playerid, 48);
					}
					case 9: {
						SetPVarInt(playerid, "SelSkin", 10);
						SetPlayerSkin(playerid, 60);
					}
					case 10: {
						SetPVarInt(playerid, "SelSkin", 11);
						SetPlayerSkin(playerid, 101);
					}
					case 11: {
						SetPVarInt(playerid, "SelSkin", 12);
						SetPlayerSkin(playerid, 241);
					}
					case 12: {
						SetPVarInt(playerid, "SelSkin", 13);
						SetPlayerSkin(playerid, 242);
					}
					case 13: {
						SetPVarInt(playerid, "SelSkin", 0);
					}
					default: {
						SetPVarInt(playerid, "SelSkin", 1);
						SetPlayerSkin(playerid, 250);
					}
				}
			}
			if(PlayerInfo[playerid][pSex] == 1) {
				switch(GetPVarInt(playerid, "SelSkin"))
				{
					case 1: {
						SetPVarInt(playerid, "SelSkin", 2);
						SetPlayerSkin(playerid, 12);
					}
					case 2: {
						SetPVarInt(playerid, "SelSkin", 3);
						SetPlayerSkin(playerid, 93);
					}
					case 3: {
						SetPVarInt(playerid, "SelSkin", 4);
						SetPlayerSkin(playerid, 233);
					}
					case 4: {
						SetPVarInt(playerid, "SelSkin", 0);
					}
					default: {
						SetPVarInt(playerid, "SelSkin", 1);
						SetPlayerSkin(playerid, 190);
					}
				}
			}			
		}
	}
	Dialog_Show(playerid, Dialog:ClothesShop);	
	return 1;
}


