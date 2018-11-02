// **********************************************
//
//  Система "Закладочка" exclusive for Chance RP
//
// ***************** v 0.1 **********************

#if defined _drugdeal_system_included
	#endinput
#endif
#define _drugdeal_system_included

#define	DRUG_BUY_PRICE	33 // Закупочная цена (за грамм)
#define DRUG_SELL_PRICE 50 // Цена при продаже (за грамм)
#define MAX_DRUGS       15 // Максимум грамм на руках


#define MAX_PLACE_SELL	41

new TOTAL_DRUGS;
new Text3D:totaldrug;
new drug_amount[MAX_PLAYERS];
new buydrugs_Timer[MAX_PLAYERS];
new point_sell[41];
new drug_string[90];
new drughouse;

enum placesell
	{
		Float: cor_X,
		Float: cor_Y,
		Float: cor_Z
	};


static const DrugSale[MAX_PLACE_SELL][placesell] =
	{
		{1762.4342,-2103.8435,13.5469},
		{1940.9829,-2115.9775,13.6953},
		{1898.9917,-2037.9490,13.5469},
		{1891.9006,-1915.8767,15.2568},
		{2269.2544,-1883.9917,13.9710},
		{2465.3118,-2019.9049,13.8623},
		{2753.1370,-1962.7870,13.5469},
		{2722.7786,-2033.6702,13.5472},
		{2851.6387,-1532.3898,11.0938},
		{2754.2668,-1400.5101,39.3718},
		{2784.7273,-1306.2128,38.5347},
		{2627.9460,-1098.6697,69.3668},
		{2553.5396,-958.0579,82.6568},
		{2329.9639,-1059.0751,52.3516},
		{2186.2781,-998.5817,66.4688},
		{2008.3966,-985.6874,33.9508},
		{2000.0732,-1115.5569,27.1318},
		{2153.7937,-1242.0958,25.2843},
		{2230.6873,-1159.8674,25.8221},
		{2334.5635,-1233.7919,27.9766},
		{2230.1807,-1282.2523,25.3672},
		{2362.7107,-1332.4088,24.0078},
		{2468.6108,-1295.5103,29.9303},
		{2551.0203,-1235.5168,49.0014},
		{2609.2612,-1211.7159,57.9375},
		{2263.9160,-1471.1222,23.4859},
		{2150.1404,-1446.3730,25.7746},
		{2028.2794,-1640.8656,13.5547},
		{2055.6665,-1732.5574,13.5469},
		{2158.2976,-1818.6460,16.1406},
		{2140.5837,-1708.3036,15.0859},
		{2328.7222,-1681.9225,14.7926},
		{2512.7195,-1651.5948,13.9586},
		{2470.6267,-1698.3690,13.5160},
		{2360.8613,-1795.7842,13.5469},
		{1990.1074,-1777.4989,17.3646},
		{1933.4595,-1863.9418,13.5619},
		{1909.9490,-1598.3728,14.3062},
		{2122.9133,-1185.6782,24.0310},
		{2190.0249,-1082.2185,43.0531},
        {1940.9829,-2115.9775,13.6953}
    };


stock get_drugs(playerid) {
	new 
	Fraction:fractionid = GetPlayerFraction(playerid);
	if(fractionid > FRACTION_LSPD && fractionid < FRACTION_RUSSIAN_MAFIA) 
	{
		if(TOTAL_DRUGS <= 0) TOTAL_DRUGS = 0;
		if(TOTAL_DRUGS < 15) return SendClientMessage(playerid, -1, ""COLOR_RED"В притоне недостаточно наркотиков");
		if(drug_amount[playerid] > 0) return SendClientMessage(playerid, -1, ""COLOR_RED"У Вас максимальное кол-во наркотиков");
		format(drug_string, sizeof(drug_string), ""COLOR_BLUE"Склад притона: {FFFFFF}%dгр.",TOTAL_DRUGS);
		SendClientMessage(playerid, -1, drug_string);
		drug_amount[playerid] = 0;
		format(drug_string, sizeof(drug_string), "Цена за 1 гр. наркотиков составляет %d EXP", DRUG_BUY_PRICE);
		SendClientMessage(playerid, -1, drug_string);

		if(CheckCash(playerid, DRUG_BUY_PRICE*MAX_DRUGS) == false) return 1;
		
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Через 10 секунд вы закупите партию из 15 гр. наркотиков");
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Чтобы отменить это действие - покиньте пикап");
		buydrugs_Timer[playerid] = SetTimerEx("get_drugs_accepted", 10000, false, "d", playerid);
	}
	return 1;
}

stock update_drug_text() {

 	format(drug_string, sizeof(drug_string), ""COLOR_BLUE"Склад: {FFFFFF}%dгр.", TOTAL_DRUGS);
	Update3DTextLabelText(totaldrug, 0xFFFFFFFF, drug_string);
}

stock get_drugs_delivred(playerid)	{
	PlayerInfo[playerid][pWanted] += 90;
	SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
	Player.AddEXP(PlayerInfo[playerid][pID], DRUG_SELL_PRICE, E_JOB_DRUGS, playerid);
	drug_amount[playerid]--;
    if(drug_amount[playerid] <= 0) {
    drug_amount[playerid] = 0;
	
	DecreaseKarma(playerid);

	switch(random(10)) {
		case 0: SendClientMessage(playerid, C_CHAT, "- Покупатель: Отличный стафф, чувак. Удачи тебе");
		case 1: SendClientMessage(playerid, C_CHAT, "- Покупатель: Заезжай еще, ниггер");
		case 2: SendClientMessage(playerid, C_CHAT, "- Покупатель: Мог бы и побыстрей, барыга");
		case 3: SendClientMessage(playerid, C_CHAT, "- Покупатель: Классная петрушка, а теперь вали отсюда!");
		case 4: SendClientMessage(playerid, C_CHAT, "- Покупатель: Пахнет волшебством, спасибо мэн");
		case 5: SendClientMessage(playerid, C_CHAT, "- Покупатель: Нигга, мы тебя уже заждались");
		case 6: SendClientMessage(playerid, C_CHAT, "- Покупатель: Надеюсь не будет как в прошлый раз...");
		case 7: SendClientMessage(playerid, C_CHAT, "- Покупатель: Ради этого я продал мамино обручальное кольцо");
		case 8: SendClientMessage(playerid, C_CHAT, "- Покупатель: Ух, щас полетаем");
		case 9: SendClientMessage(playerid, C_CHAT, "- Покупатель: Надеюсь это не мука!");
	}

    SendClientMessage(playerid, -1, ""COLOR_GREEN"Ты доставил все наркотики");
	for(new i = 0; i < MAX_PLACE_SELL; i++)
	{
		if(IsValidDynamicCP(point_sell[i])) {
			TogglePlayerDynamicCP(playerid, point_sell[i], false);
		}
	}

	format(drug_string, sizeof(drug_string), ""COLOR_BLUE"Получено с продаж: "COLOR_WHITE"%d EXP", DRUG_SELL_PRICE*MAX_DRUGS);
	SendClientMessage(playerid, -1, drug_string);
	return 1;
    }

	format(drug_string, sizeof(drug_string), ""COLOR_BLUE"Получено: "COLOR_WHITE"%d EXP", DRUG_SELL_PRICE);
	SendClientMessage(playerid, -1, drug_string);
	format(drug_string, sizeof(drug_string), ""COLOR_BLUE"Осталось доставить: {FFFFFF}%d грамм", drug_amount[playerid]);
	SendClientMessage(playerid, -1, drug_string);
	return 1;
}

	forward get_drugs_accepted(playerid);
	public get_drugs_accepted(playerid) {
	if(IsValidTimer(buydrugs_Timer[playerid]))
	{
		KillTimer(buydrugs_Timer[playerid]);
		buydrugs_Timer[playerid] = 0;
	}
	if(TOTAL_DRUGS < 15) return SendClientMessage(playerid, -1, ""COLOR_RED"В притоне недостаточно наркотиков");
 	if(!IsPlayerInRangeOfPoint(playerid, 2.2, 2178.9387,-1660.8270,14.9413)) return 1;
	if(drug_amount[playerid] >= MAX_DRUGS) return SendClientMessage(playerid, -1, ""COLOR_RED"У Вас максимальное кол-во наркотиков");

	if(CheckCash(playerid, DRUG_BUY_PRICE*MAX_DRUGS) == false) return 1;
	Player.DownEXP(PlayerInfo[playerid][pID], DRUG_BUY_PRICE*MAX_DRUGS, E_BUY_DRUGS_JOB, playerid);
	TOTAL_DRUGS -= 15;

	update_drug_text();

	drug_amount[playerid] += MAX_DRUGS;

	format(drug_string, sizeof(drug_string), ""COLOR_BLUE"Вы закупили 15 гр. наркотиков за %d EXP", DRUG_BUY_PRICE*MAX_DRUGS);
	SendClientMessage(playerid, -1, drug_string);
	SendClientMessage(playerid, -1, ""COLOR_BLUE"Ваша задача: "COLOR_WHITE"Развозить наркотики по гетто");

	for(new i = 0; i < MAX_PLACE_SELL; i++) {
		if(IsValidDynamicCP(point_sell[i])) {
			TogglePlayerDynamicCP(playerid, point_sell[i], true);
		}
	}
	return 1;
}

stock Dealer_OnGameModeInit() {
	totaldrug = Create3DTextLabel("_", 0xFFFFFFFF, 2178.9387,-1660.8270,14.9413+1, 40, 0);
	TOTAL_DRUGS = 45;
	update_drug_text();
	drughouse = CreateDynamicPickup(1279, 2, 2178.9387,-1660.8270,14.9413);

	for(new i = 0; i < MAX_PLACE_SELL; i++) {
		point_sell[i] = CreateDynamicCP(DrugSale[i][cor_X], DrugSale[i][cor_Y], DrugSale[i][cor_Z], 1.5, -1, -1, -1, 60);
	}
	return 1;
}

stock Dealer_OnPlayerEnterDynamicCP(playerid, checkpointid) {
	for(new i = 0; i < MAX_PLACE_SELL; i++)
	{
		if(checkpointid == point_sell[i] && IsValidDynamicCP(checkpointid))
		{
		    get_drugs_delivred(playerid);
			TogglePlayerDynamicCP(playerid, point_sell[i], false);
			return 1;
		}
	}
	return 0;
}
stock Dealer_OP_PickUpDynamicPickup(playerid, pickupid) {
	if(pickupid == drughouse) {
		get_drugs(playerid);
		return 1;
	}
	return 0;
}

stock Dealer_OnPlayerConnect(playerid) {
	drug_amount[playerid] = 0;

	for(new i = 0; i < MAX_PLACE_SELL; i++) {
		if(IsValidDynamicCP(point_sell[i])) {
			TogglePlayerDynamicCP(playerid, point_sell[i], false);
		}
	}

	return 1;
}

stock Dealer_OnPlayerDisconnect(playerid, reason) {
	#pragma unused reason
    drug_amount[playerid] = 0;
	if(IsValidTimer(buydrugs_Timer[playerid]))
	{
		KillTimer(buydrugs_Timer[playerid]);
		buydrugs_Timer[playerid] = -1;
	}

	for(new i = 0; i < MAX_PLACE_SELL; i++) {
		if(IsValidDynamicCP(point_sell[i])) {
			TogglePlayerDynamicCP(playerid, point_sell[i], false);
		}
	}
	return 1;
}
