#if defined _gangwar_included
	#endinput
#endif
#define _gangwar_included

enum gz_vars__ {
        Float:min_x,
        Float:min_y,
        Float:max_x,
        Float:max_y,

    };

static const gz_ls[][gz_vars__] = {
	{1643.0, -2163.0, 1768.0, -2038.0},
	{1768.0, -2163.0, 1893.0, -2038.0},
	{1893.0, -2163.0, 2018.0, -2038.0},
	{2018.0, -2163.0, 2143.0, -2038.0},
	{2143.0, -2163.0, 2268.0, -2038.0},
	{2268.0, -2163.0, 2393.0, -2038.0},
	{2393.0, -2163.0, 2518.0, -2038.0},
	{2518.0, -2163.0, 2643.0, -2038.0},
	{2643.0, -2163.0, 2768.0, -2038.0},
	{2768.0, -2163.0, 2893.0, -2038.0},
	{2768.0, -2038.0, 2893.0, -1913.0},
	{2768.0, -1913.0, 2893.0, -1788.0},
	{2768.0, -1788.0, 2893.0, -1663.0},
	{2768.0, -1663.0, 2893.0, -1538.0},
	{2768.0, -1538.0, 2893.0, -1413.0},
	{2768.0, -1413.0, 2893.0, -1288.0},
	{2768.0, -1288.0, 2893.0, -1163.0},
	{2768.0, -1163.0, 2893.0, -1038.0},
	{2768.0, -1038.0, 2893.0, -913.0},
	{2643.0, -1038.0, 2768.0, -913.0},
	{2518.0, -1038.0, 2643.0, -913.0},
	{2393.0, -1038.0, 2518.0, -913.0},
	{2268.0, -1038.0, 2393.0, -913.0},
	{2143.0, -1038.0, 2268.0, -913.0},
	{2018.0, -1038.0, 2143.0, -913.0},
	{1893.0, -1038.0, 2018.0, -913.0},
	{1768.0, -1038.0, 1893.0, -913.0},
	{1643.0, -1038.0, 1768.0, -913.0},
	{1643.0, -1163.0, 1768.0, -1038.0},
	{1643.0, -1288.0, 1768.0, -1163.0},
	{1643.0, -1413.0, 1768.0, -1288.0},
	{1643.0, -1538.0, 1768.0, -1413.0},
	{1643.0, -1663.0, 1768.0, -1538.0},
	{1643.0, -1788.0, 1768.0, -1663.0},
	{1643.0, -1913.0, 1768.0, -1788.0},
	{1643.0, -2038.0, 1768.0, -1913.0},
	{1768.0, -2038.0, 1893.0, -1913.0},
	{1893.0, -2038.0, 2018.0, -1913.0},
	{2018.0, -2038.0, 2143.0, -1913.0},
	{2143.0, -2038.0, 2268.0, -1913.0},
	{2268.0, -2038.0, 2393.0, -1913.0},
	{2393.0, -2038.0, 2518.0, -1913.0},
	{2518.0, -2038.0, 2643.0, -1913.0},
	{2643.0, -2038.0, 2768.0, -1913.0},
	{2643.0, -1913.0, 2768.0, -1788.0},
	{2518.0, -1913.0, 2643.0, -1788.0},
	{2393.0, -1913.0, 2518.0, -1788.0},
	{2268.0, -1913.0, 2393.0, -1788.0},
	{2143.0, -1913.0, 2268.0, -1788.0},
	{2018.0, -1913.0, 2143.0, -1788.0},
	{1893.0, -1913.0, 2018.0, -1788.0},
	{1768.0, -1913.0, 1893.0, -1788.0},
	{1768.0, -1788.0, 1893.0, -1663.0},
	{1893.0, -1788.0, 2018.0, -1663.0},
	{2018.0, -1788.0, 2143.0, -1663.0},
	{2143.0, -1788.0, 2268.0, -1663.0},
	{2268.0, -1788.0, 2393.0, -1663.0},
	{2393.0, -1788.0, 2518.0, -1663.0},
	{2518.0, -1788.0, 2643.0, -1663.0},
	{2643.0, -1788.0, 2768.0, -1663.0},
	{2643.0, -1663.0, 2768.0, -1538.0},
	{2518.0, -1663.0, 2643.0, -1538.0},
	{2393.0, -1663.0, 2518.0, -1538.0},
	{2268.0, -1663.0, 2393.0, -1538.0},
	{2143.0, -1663.0, 2268.0, -1538.0},
	{2018.0, -1663.0, 2143.0, -1538.0},
	{1893.0, -1663.0, 2018.0, -1538.0},
	{1768.0, -1663.0, 1893.0, -1538.0},
	{1768.0, -1538.0, 1893.0, -1413.0},
	{1893.0, -1538.0, 2018.0, -1413.0},
	{2018.0, -1538.0, 2143.0, -1413.0},
	{2143.0, -1538.0, 2268.0, -1413.0},
	{2268.0, -1538.0, 2393.0, -1413.0},
	{2393.0, -1538.0, 2518.0, -1413.0},
	{2518.0, -1538.0, 2643.0, -1413.0},
	{2643.0, -1538.0, 2768.0, -1413.0},
	{2643.0, -1413.0, 2768.0, -1288.0},
	{2643.0, -1288.0, 2768.0, -1163.0},
	{2643.0, -1163.0, 2768.0, -1038.0},
	{2518.0, -1163.0, 2643.0, -1038.0},
	{2518.0, -1288.0, 2643.0, -1163.0},
	{2518.0, -1413.0, 2643.0, -1288.0},
	{2393.0, -1413.0, 2518.0, -1288.0},
	{2393.0, -1288.0, 2518.0, -1163.0},
	{2393.0, -1163.0, 2518.0, -1038.0},
	{2268.0, -1163.0, 2393.0, -1038.0},
	{2268.0, -1288.0, 2393.0, -1163.0},
	{2268.0, -1413.0, 2393.0, -1288.0},
	{2143.0, -1413.0, 2268.0, -1288.0},
	{2143.0, -1288.0, 2268.0, -1163.0},
	{2143.0, -1163.0, 2268.0, -1038.0},
	{2018.0, -1163.0, 2143.0, -1038.0},
	{2018.0, -1288.0, 2143.0, -1163.0},
	{2018.0, -1413.0, 2143.0, -1288.0},
	{1893.0, -1413.0, 2018.0, -1288.0},
	{1893.0, -1288.0, 2018.0, -1163.0},
	{1893.0, -1163.0, 2018.0, -1038.0},
	{1768.0, -1163.0, 1893.0, -1038.0},
	{1768.0, -1288.0, 1893.0, -1163.0},
	{1768.0, -1413.0, 1893.0, -1288.0}
}

static const gz_sf[][gz_vars__] = {
	{-1720.0, 1268.5, -1600.0, 1388.5},
	{-1840.0, 1268.5, -1720.0, 1388.5},
	{-1960.0, 1268.5, -1840.0, 1388.5},
	{-2080.0, 1268.5, -1960.0, 1388.5},
	{-2200.0, 1268.5, -2080.0, 1388.5},
	{-2320.0, 1268.5, -2200.0, 1388.5},
	{-2440.0, 1268.5, -2320.0, 1388.5},
	{-2560.0, 1268.5, -2440.0, 1388.5},
	{-2680.0, 1268.5, -2560.0, 1388.5},
	{-2800.0, 1268.5, -2680.0, 1388.5},
	{-1720.0, 1268.5, -1600.0, 1388.5},
	{-1720.0, 1148.5, -1600.0, 1268.5},
	{-1720.0, 1028.5, -1600.0, 1148.5},
	{-1720.0, 908.5, -1600.0, 1028.5},
	{-1720.0, 788.5, -1600.0, 908.5},
	{-1720.0, 668.5, -1600.0, 788.5},
	{-1720.0, 548.5, -1600.0, 668.5},
	{-1720.0, 428.5, -1600.0, 548.5},
	{-1720.0, 308.5, -1600.0, 428.5},
	{-1720.0, 188.5, -1600.0, 308.5},
	{-1720.0, 68.5, -1600.0, 188.5},
	{-1720.0, -52.5, -1600.0, 68.5},
	{-1840.0, 1268.5, -1720.0, 1388.5},
	{-1840.0, 1148.5, -1720.0, 1268.5},
	{-1840.0, 1028.5, -1720.0, 1148.5},
	{-1840.0, 908.5, -1720.0, 1028.5},
	{-1840.0, 788.5, -1720.0, 908.5},
	{-1840.0, 668.5, -1720.0, 788.5},
	{-1840.0, 548.5, -1720.0, 668.5},
	{-1840.0, 428.5, -1720.0, 548.5},
	{-1840.0, 308.5, -1720.0, 428.5},
	{-1840.0, 188.5, -1720.0, 308.5},
	{-1840.0, 68.5, -1720.0, 188.5},
	{-1840.0, -52.5, -1720.0, 68.5},
	{-1960.0, 1268.5, -1840.0, 1388.5},
	{-1960.0, 1148.5, -1840.0, 1268.5},
	{-1960.0, 1028.5, -1840.0, 1148.5},
	{-1960.0, 908.5, -1840.0, 1028.5},
	{-1960.0, 788.5, -1840.0, 908.5},
	{-1960.0, 668.5, -1840.0, 788.5},
	{-1960.0, 548.5, -1840.0, 668.5},
	{-1960.0, 428.5, -1840.0, 548.5},
	{-1960.0, 308.5, -1840.0, 428.5},
	{-1960.0, 188.5, -1840.0, 308.5},
	{-1960.0, 68.5, -1840.0, 188.5},
	{-1960.0, -52.5, -1840.0, 68.5},
	{-2080.0, 1268.5, -1960.0, 1388.5},
	{-2080.0, 1148.5, -1960.0, 1268.5},
	{-2080.0, 1028.5, -1960.0, 1148.5},
	{-2080.0, 908.5, -1960.0, 1028.5},
	{-2080.0, 788.5, -1960.0, 908.5},
	{-2080.0, 668.5, -1960.0, 788.5},
	{-2080.0, 548.5, -1960.0, 668.5},
	{-2080.0, 428.5, -1960.0, 548.5},
	{-2080.0, 308.5, -1960.0, 428.5},
	{-2080.0, 188.5, -1960.0, 308.5},
	{-2080.0, 68.5, -1960.0, 188.5},
	{-2080.0, -52.5, -1960.0, 68.5},
	{-2200.0, 1268.5, -2080.0, 1388.5},
	{-2200.0, 1148.5, -2080.0, 1268.5},
	{-2200.0, 1028.5, -2080.0, 1148.5},
	{-2200.0, 908.5, -2080.0, 1028.5},
	{-2200.0, 788.5, -2080.0, 908.5},
	{-2200.0, 668.5, -2080.0, 788.5},
	{-2200.0, 548.5, -2080.0, 668.5},
	{-2200.0, 428.5, -2080.0, 548.5},
	{-2200.0, 308.5, -2080.0, 428.5},
	{-2200.0, 188.5, -2080.0, 308.5},
	{-2200.0, 68.5, -2080.0, 188.5},
	{-2200.0, -52.5, -2080.0, 68.5},
	{-2320.0, 1268.5, -2200.0, 1388.5},
	{-2320.0, 1148.5, -2200.0, 1268.5},
	{-2320.0, 1028.5, -2200.0, 1148.5},
	{-2320.0, 908.5, -2200.0, 1028.5},
	{-2320.0, 788.5, -2200.0, 908.5},
	{-2320.0, 668.5, -2200.0, 788.5},
	{-2320.0, 548.5, -2200.0, 668.5},
	{-2320.0, 428.5, -2200.0, 548.5},
	{-2320.0, 308.5, -2200.0, 428.5},
	{-2320.0, 188.5, -2200.0, 308.5},
	{-2320.0, 68.5, -2200.0, 188.5},
	{-2320.0, -52.5, -2200.0, 68.5},
	{-2440.0, 1268.5, -2320.0, 1388.5},
	{-2440.0, 1148.5, -2320.0, 1268.5},
	{-2440.0, 1028.5, -2320.0, 1148.5},
	{-2440.0, 908.5, -2320.0, 1028.5},
	{-2440.0, 788.5, -2320.0, 908.5},
	{-2440.0, 668.5, -2320.0, 788.5},
	{-2440.0, 548.5, -2320.0, 668.5},
	{-2440.0, 428.5, -2320.0, 548.5},
	{-2440.0, 308.5, -2320.0, 428.5},
	{-2440.0, 188.5, -2320.0, 308.5},
	{-2440.0, 68.5, -2320.0, 188.5},
	{-2440.0, -52.5, -2320.0, 68.5},
	{-2560.0, 1268.5, -2440.0, 1388.5},
	{-2560.0, 1148.5, -2440.0, 1268.5},
	{-2560.0, 1028.5, -2440.0, 1148.5},
	{-2560.0, 908.5, -2440.0, 1028.5},
	{-2560.0, 788.5, -2440.0, 908.5},
	{-2560.0, 668.5, -2440.0, 788.5},
	{-2560.0, 548.5, -2440.0, 668.5},
	{-2560.0, 428.5, -2440.0, 548.5},
	{-2560.0, 308.5, -2440.0, 428.5},
	{-2560.0, 188.5, -2440.0, 308.5},
	{-2560.0, 68.5, -2440.0, 188.5},
	{-2560.0, -52.5, -2440.0, 68.5},
	{-2680.0, 1268.5, -2560.0, 1388.5},
	{-2680.0, 1148.5, -2560.0, 1268.5},
	{-2680.0, 1028.5, -2560.0, 1148.5},
	{-2680.0, 908.5, -2560.0, 1028.5},
	{-2680.0, 788.5, -2560.0, 908.5},
	{-2680.0, 668.5, -2560.0, 788.5},
	{-2680.0, 548.5, -2560.0, 668.5},
	{-2680.0, 428.5, -2560.0, 548.5},
	{-2680.0, 308.5, -2560.0, 428.5},
	{-2680.0, 188.5, -2560.0, 308.5},
	{-2680.0, 68.5, -2560.0, 188.5},
	{-2680.0, -52.5, -2560.0, 68.5},
	{-2800.0, 1268.5, -2680.0, 1388.5},
	{-2800.0, 1148.5, -2680.0, 1268.5},
	{-2800.0, 1028.5, -2680.0, 1148.5},
	{-2800.0, 908.5, -2680.0, 1028.5},
	{-2800.0, 788.5, -2680.0, 908.5},
	{-2800.0, 668.5, -2680.0, 788.5},
	{-2800.0, 548.5, -2680.0, 668.5},
	{-2800.0, 428.5, -2680.0, 548.5},
	{-2800.0, 308.5, -2680.0, 428.5},
	{-2800.0, 188.5, -2680.0, 308.5},
	{-2800.0, 68.5, -2680.0, 188.5},
	{-2800.0, -52.5, -2680.0, 68.5}
}

#define PER_GZ_PAYMENT	6

enum gz_info_vars__ {gz, gz_owner, dispute, invader};
new gz_info[][gz_info_vars__];

enum capture_info_vars__ {status, opponent, score}
new capture_info[][capture_info_vars__];

new fraction_zones[MAX_FRACTION+1],
	gang_profit[MAX_FRACTION+1],
	total_gangzones = 0,
	total_mafiazones = 0,
	gangwar_delay_gang = 0,
	gangwar_delay_mafia = 0;

new gangwar_mafia = {INVALID_TIMER_ID, ...};
new gangwar_gang = {INVALID_TIMER_ID, ...};

new mafia_counter, gang_counter;

forward load_gz();
public load_gz() {
	new rows = cache_get_row_count();
	new time = GetTickCount();
	if(rows)
	{
	for(new i = 0; i < rows; i++)
		{
			gz_info[i][gz_owner] = cache_get_field_content_int(he,"gz_owner");

			fraction_zones[gz_owner] += 1;

			if(i<= 99) gz_info[i][zone] = GangZoneCreate(gz_ls[i][min_x], gz_ls[i][min_y], gz_ls[i][max_x], gz_ls[i][max_y]), total_gangzones += 1;;
			if(i > 99) gz_info[i][zone] = GangZoneCreate(gz_sf[i][min_x], gz_sf[i][min_y], gz_sf[i][max_x], gz_sf[i][max_y]), total_mafiazones += 1;;

			gz_info[i][dispute] = 0;
		}
	}
	printf("Загружено: %d территорий за %d м.с", total_gangzones, GetTickCount() - time);

	GetCrimeSalary();

	for(new i = 1; i <= MAX_FRACTION+1; i++) {
		UpdateGangEmblem(i);
	}	
}

stock SaveGZ(zoneid)
{
	new query[90];
	mysql_format(database, query, sizeof(query), "UPDATE gz SET fraction = %i WHERE id = %i LIMIT 1", gz_info[zoneid][owner], zoneid);
	mysql_pquery(database, query, "", "");
	return true;
}

stock GangZoneColor(zoneid) {
	new color_code;
	switch(gz_info[zoneid][gz_owner]) {
		case 3: color_code = 0xd200ff99;
		case 4: color_code = 0xcfbe0899;
		case 2: color_code = 0x06b50699;
		case 6: color_code = 0x03c3b899;
		case 5: color_code = 0x007fffAA;
		default: color_code = 0xFEFEFEAA;
	}
	return color_code;
}

stock ShowZones(playerid) {
	for(new i = 0; i <= total_gangzones; i++) GangZoneShowForPlayer(playerid, gz_info[i][zone], GangZoneColor(i));
}

stock GetCrimeSalary() {
	for(new i = 1; i <= MAX_FRACTION+1; i++) {
		gang_profit[i] = 0;
	}
	for(new x = 0; x <= total_gangzones; x++)
	{
		gang_profit[gz_info[x][gz_owner]] += PER_GZ_PAYMENT;
	}
	return 1;
}

stock UpdateGangEmblem(gangid) {
	new ownlands;
	for(new i = 0; i <= total_gangzones; i++) {
		if(gz_info[i][gz_owner] == gangid) ownlands++;
	}
	switch(gangid) {
		case 2: format(big_string, sizeof big_string, ""GROVE_C"%s %s\nМатериалов на складе: %d\nТерриторий под контролем: %d\n\nСобрать оружие: /makegun",GetGangName(gangid),(WStatus[gangid] == 1) ? ("{FFFFFF}("COLOR_GREEN"открыт{FFFFFF})") : ("{FFFFFF}("COLOR_RED"закрыт{FFFFFF})"), Warehouse[gangid], ownlands);
		case 3: format(big_string, sizeof big_string, ""BALLAS_C"%s %s\nМатериалов на складе: %d\nТерриторий под контролем: %d\n\nСобрать оружие: /makegun",GetGangName(gangid),(WStatus[gangid] == 1) ? ("{FFFFFF}("COLOR_GREEN"открыт{FFFFFF})") : ("{FFFFFF}("COLOR_RED"закрыт{FFFFFF})"), Warehouse[gangid], ownlands);
		case 4: format(big_string, sizeof big_string, ""VAGOS_C"%s %s\nМатериалов на складе: %d\nТерриторий под контролем: %d\n\nСобрать оружие: /makegun",GetGangName(gangid),(WStatus[gangid] == 1) ? ("{FFFFFF}("COLOR_GREEN"открыт{FFFFFF})") : ("{FFFFFF}("COLOR_RED"закрыт{FFFFFF})"), Warehouse[gangid], ownlands);
		case 5: format(big_string, sizeof big_string, ""RIFA_C"%s %s\nМатериалов на складе: %d\nТерриторий под контролем: %d\n\nСобрать оружие: /makegun",GetGangName(gangid),(WStatus[gangid] == 1) ? ("{FFFFFF}("COLOR_GREEN"открыт{FFFFFF})") : ("{FFFFFF}("COLOR_RED"закрыт{FFFFFF})"), Warehouse[gangid], ownlands);
		case 6: format(big_string, sizeof big_string, ""AZTEC_C"%s %s\nМатериалов на складе: %d\nТерриторий под контролем: %d\n\nСобрать оружие: /makegun",GetGangName(gangid),(WStatus[gangid] == 1) ? ("{FFFFFF}("COLOR_GREEN"открыт{FFFFFF})") : ("{FFFFFF}("COLOR_RED"закрыт{FFFFFF})"), Warehouse[gangid], ownlands);
		case 7: format(big_string, sizeof big_string, ""RUSSIA_C"%s %s\nМатериалов на складе: %d\nТерриторий под контролем: %d\n\nСобрать оружие: /makegun",GetGangName(gangid),(WStatus[gangid] == 1) ? ("{FFFFFF}("COLOR_GREEN"открыт{FFFFFF})") : ("{FFFFFF}("COLOR_RED"закрыт{FFFFFF})"), Warehouse[gangid], ownlands);
		case 8: format(big_string, sizeof big_string, ""TRIAD_C"%s %s\nМатериалов на складе: %d\nТерриторий под контролем: %d\n\nСобрать оружие: /makegun",GetGangName(gangid),(WStatus[gangid] == 1) ? ("{FFFFFF}("COLOR_GREEN"открыт{FFFFFF})") : ("{FFFFFF}("COLOR_RED"закрыт{FFFFFF})"), Warehouse[gangid], ownlands);
		case 9: format(big_string, sizeof big_string, ""DANANG_C"%s %s\nМатериалов на складе: %d\nТерриторий под контролем: %d\n\nСобрать оружие: /makegun",GetGangName(gangid),(WStatus[gangid] == 1) ? ("{FFFFFF}("COLOR_GREEN"открыт{FFFFFF})") : ("{FFFFFF}("COLOR_RED"закрыт{FFFFFF})"), Warehouse[gangid], ownlands);
		default: return 1;
	}
	UpdateDynamic3DTextLabelText(gang_invite_text[gangid-2], -1, big_string);
}

stock IsEnoughPlayersToWar(zoneid, playerid) {

		new gonline[2],
			Fraction:fractionid = GetPlayerFraction(playerid),
			Fraction:target_fractionid;

		if(_:gz_info[zoneid][gz_owner] == _:fractionid) return { 
			SendClientMessage(playerid, -1, ""COLOR_RED"Данная территория уже под контролем вашей фракции");
			return 0;
		}	

		foreach(new i: Player) {
			if(_:target_fractionid == _:fractionid) gonline[0]++;
			if(_:target_fractionid == _:gz_info[zoneid][gz_owner]) gonline[1]++;
		}

		if(gonline[0] < 5) { 
			SendClientMessage(playerid, -1, ""COLOR_RED"В вашей банде недостаточно людей для нападения. Необходимо: 5");
			return 0;
		}
		if(gonline[1] < 5) {
			SendClientMessage(playerid, -1, ""COLOR_RED"В банде противника недостаточно людей для участия. Необходимо: 5");
			return 0;
		}
		return 1;
}

CMD:capture(playerid) {
	if(!IsACrime(playerid)) return 1;
	if(GetPlayerJobDayStatus(playerid) == false)
	{
		return SendClientMessage(playerid, -1, MSG_START_JOB_DAY);
	}
	if(PlayerInfo[playerid][pRank] < 8) return SendClientMessage(playerid, -1, ""COLOR_RED"Доступно только после достижения 8 ранга");


	if(PlayerInGangZone(playerid, -3000, -727.5, -1228, 1588.5)) {
		if(IsAMafia(playerid) == 0) return 1;
		if(gangwar_delay_mafia = 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Война за территорию уже идет/проходила в этом часу");
		for(new i = 0; i <= total_mafiazones; i++) {
			if(PlayerInGangZone(playerid, gz_sf[i][min_x], gz_sf[i][min_y], gz_sf[i][max_x], gz_sf[i][max_y]) {
				if(IsEnoughPlayersToWar(i, playerid) == 0) return 1;
				if(gangwar_delay_mafia = 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Война за территорию уже идет/проходила в этом часу");
				gangwar_delay_mafia = 1;
				mafia_counter = 900;

				new zoneid = i,
					owner = gz_info[zoneid][gz_owner],		
					invader = GetPlayerFractionInt(playerid)
					type = 0;						

				gangwar_mafia = KillTimer(gangwar_mafia);
				gangwar_mafia = SetTimerEx("GangWar", 1000, false, "dddd", type, zoneid, owner, invader);

			} else {
				return 1;
			}
		}
	}
	if(PlayerInGangZone(playerid, 1460, -2788, 3000, -872)) {
		if(IsAGang(playerid) == 0) return 1;
		if(gangwar_delay_gang = 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Война за территорию уже идет/проходила в этом часу");
		for(new i = 0; i <= total_gangzones; i++) {
			if(PlayerInGangZone(playerid, gz_ls[i][min_x], gz_ls[i][min_y], gz_ls[i][max_x], gz_ls[i][max_y]) {
				if(IsEnoughPlayersToWar(i, playerid) == 0) return 1;
				if(gangwar_delay_gang = 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Война за территорию уже идет/проходила в этом часу");
				gangwar_delay_gang = 1;
				gang_counter = 600;

				new zoneid = i,
					owner = gz_info[zoneid][gz_owner],		
					invader = GetPlayerFractionInt(playerid),
					type = 1;			

				gangwar_gang = KillTimer(gangwar_gang);
				gangwar_gang = SetTimerEx("GangWar", 1000, false, "dddd", type, zoneid, owner, invader);

			} else {
				return 1;
			}
		}
	}

	new Fraction:fractionid = GetPlayerFraction(playerid);

	format(small_string, sizeof(small_string), ""COLOR_BLUE"На вашу территорию напали "COLOR_WHITE"%s", GetGangName(gz_info[zoneid][invader]));
	SendFamilyMessage(Fraction:gz_info[zoneid][gz_owner], -1, small_string);
	SendFamilyMessage(Fraction:gz_info[zoneid][gz_owner], -1, ""COLOR_BLUE"Эта зона будет мигать на карте 10 минут");
	SendFamilyMessage(Fraction:gz_info[zoneid][gz_owner], -1, ""COLOR_BLUE"Территория достанется банде которая сделает больше убийств");
	
	format(small_string, sizeof(small_string), "%s"COLOR_BLUE" начал захват зоны под влиянием "COLOR_WHITE"%s", PlayerInfo[playerid][pName],GetGangName(gz_info[zoneid][gz_owner]));
	SendFamilyMessage(fractionid, -1, small_string);
	SendFamilyMessage(fractionid, -1, ""COLOR_BLUE"Эта зона будет мигать на карте 10 минут");
	SendFamilyMessage(fractionid, -1, ""COLOR_BLUE"Территория достанется стороне которая сделает больше убийств");

	foreach(new y: Admin) {
		GameTextForPlayer(y, "GangWar", 2500, 4);
	}
	return 1;
}

forward GangWar(type, zoneid, owner, invader);
public GangWar(type, zoneid, owner, invader) {

	if(gang_counter <= 0 || mafia_counter <= 0) {
		new string[144];
		GangZoneStopFlashForAll(gz_info[zoneid][zone]);
		GangZoneHideForAll(gz_info[zoneid][zone]);	
		if(capture_info[invader][score] == capture_info[owner][score]) {
			format(string, 144, ""COLOR_ORANGE"Счет в войне за территорию равен");
			SendFamilyMessage(Fraction:owner, -1, string);
			SendFamilyMessage(Fraction:invader, -1, string);
			SendAdminMessage(-1, string);
		}		
		if(capture_info[invader][score] > capture_info[owner][score]) {
			format(string, 144,"%s"COLOR_BLUE" побеждает в войне за территорию", GetGangName(invader));
			SendFamilyMessage(Fraction:owner, -1, string);
			SendFamilyMessage(Fraction:invader ,-1, string);
			SendAdminMessage(-1, string);			
			gz_info[zoneid][owner] = invader;
			SaveGZ(zoneid);

			UpdateGangEmblem(invader);
			UpdateGangEmblem(owner);			
		}
		if(capture_info[invader][score] < capture_info[owner][score]) {
			format(string, 144,"%s"COLOR_BLUE" отстояли свои права на территорию", GetGangName(owner));
			SendFamilyMessage(Fraction:owner, -1, string);
			SendFamilyMessage(Fraction:invader ,-1, string);
			SendAdminMessage(-1, string);			
		}		
		GangZoneShowForAll(gz_info[zoneid][zone], GetGangZoneColor(gz_info[zoneid][owner]));	

		if(type == 0) gangwar_mafia = KillTimer(gangwar_mafia);
		if(type == 1) gangwar_gang = KillTimer(gangwar_gang);
		return 1;
	}

	if(type = 0) {
		mafia_counter--;
		gangwar_mafia = KillTimer(gangwar_mafia);
		gangwar_mafia = SetTimerEx("GangWar", 1000, false, "dddd", type, zoneid, owner, invader);
	}
	if(type = 1) {
		gang_counter--;
		gangwar_gang = KillTimer(gangwar_gang);
		gangwar_gang = SetTimerEx("GangWar", 1000, false, "dddd", type, zoneid, owner, invader);		
	}

	GangZoneFlashForAll(gz_info[zoneid][zone], GangZoneColor(invader));

	foreach(new i: Player) {
		if(GetPlayerFractionInt(i) == owner || GetPlayerFractionInt(i) == invader) {

			format(small_string, sizeof(small_string), "~w~%d : %d~n~~b~~h~TIME: ~w~%s", capture_info[invader][score], capture_info[owner][score], Convert(mafia_counter));
			GameTextForPlayer(i, small_string, 1500, 4);			

			if(PlayerInGangZone(playerid, gz_sf[zoneid][min_x], gz_sf[zoneid][min_y], gz_sf[zoneid][max_x], gz_sf[zoneid][max_y] && type = 0) {
				SetPVarInt(i, "oncapture", 1);
			} else {
				DeletePVar(i, "oncapture");
			}
			
			if(PlayerInGangZone(playerid, gz_ls[zoneid][min_x], gz_ls[zoneid][min_y], gz_ls[zoneid][max_x], gz_ls[zoneid][max_y] && type = 1) {
				SetPVarInt(i, "oncapture", 1);
			} else {
				DeletePVar(i, "oncapture");
			}			
		}
	}
	return 1;
}
