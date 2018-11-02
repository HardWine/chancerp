#if defined wanted_system_included
	#endinput
#endif

#define wanted_system_included

#include <../src/player/fraction_system.pwn>

// Standart
#include <YSI\y_iterate>
#include <YSI\y_timers>
#include <YSI\y_hooks>


#define STREAMER_EXTRA_ID_WANTED 				(1337)

new 
	player_wanted_zone[MAX_PLAYERS],
	player_arrest_id[MAX_PLAYERS],
	player_time_arrest[MAX_PLAYERS],
	Timer: player_arrest_timer[MAX_PLAYERS];

new 
	bool: degug_wanted[MAX_PLAYERS char];

CMD:debug(playerid, params[]) {
	return degug_wanted{playerid} = !degug_wanted{playerid};
}

stock AddPlayerToArestArea(playerid) {
	if(IsValidDynamicArea(player_wanted_zone[playerid]) == 0) {
		new 
			Float: player_pos_x,
			Float: player_pos_y,
			Float: player_pos_z;

		GetPlayerPos(playerid, player_pos_x, player_pos_y, player_pos_z);

		player_wanted_zone[playerid] = CreateDynamicCircle(player_pos_x, player_pos_y, 9.00, -1, -1, -1);
		AttachDynamicAreaToPlayer(player_wanted_zone[playerid], playerid);

		new
			data[2];

		data[0] = STREAMER_EXTRA_ID_WANTED;
		data[1] = playerid + 1;

		if(degug_wanted{playerid} == true) {
			SendClientMessage(playerid, -1, "AddPlayerToArestArea");
		}

		Streamer_SetArrayData(STREAMER_TYPE_AREA, player_wanted_zone[playerid], E_STREAMER_EXTRA_ID, data, 2);
	}
}

stock ResetPlayerFromArestArea(playerid) {
	if(IsValidDynamicArea(player_wanted_zone[playerid]) == 1) {
		DestroyDynamicArea(player_wanted_zone[playerid]);
	}
}

hook OnGameModeInit() {
	army_zone = CreateDynamicCube(-84.00, 1632, -30.00, 437, 2144, 60.00, 0, 0, -1);
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
	if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) {
		Streamer_Update(playerid, STREAMER_TYPE_AREA);
	}
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) {
		if(degug_wanted{playerid} == true) {
			SendClientMessage(playerid, -1, "OnPlayerStateChange - устанавливаем время ареста");
		}
		if(IsACop(playerid)) {
			player_time_arrest[playerid] = 10;
		} else {
			player_time_arrest[playerid] = 5;
		}
	}
}

hook OnPlayerConnect(playerid) {
	player_time_arrest[playerid] = 0;
	player_arrest_id[playerid] = INVALID_PLAYER_ID;
	return SetPlayerWanted(playerid, 0);
}

hook OnPlayerDisconnect(playerid, reason) {
	player_time_arrest[playerid] = 0;
	player_arrest_id[playerid] = INVALID_PLAYER_ID;
	return SetPlayerWanted(playerid, 0);
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(degug_wanted{playerid} == true) {
		SendClientMessage(playerid, -1, "OnPlayerEnterDynArea");
	}

	if(areaid == army_zone) {
		if(IsAGang(playerid)) {
			if(degug_wanted{playerid} == true) {
				SendClientMessage(playerid, -1, "AddPlayerToArestArea");
			}
			AddPlayerToArestArea(playerid);
		}
	}
	
	new 
		data[2];

	Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, data, 2);

	if(degug_wanted{playerid} == true) {
		format(small_string, sizeof(small_string), "data = %i|%i", data[0], data[1]);
		SendClientMessage(playerid, -1, small_string);
	}

	if(data[0] == STREAMER_EXTRA_ID_WANTED && data[1] != 0) {
		new targetid = data[1] - 1;
		player_arrest_id[playerid] = targetid;
		if(IsAnArmy(playerid)) {
			if(degug_wanted{playerid} == true) {
				format(small_string, sizeof(small_string), "IsValidDynamicArea = %i IsAGang = %i, IsPlayerInDynamicArea = %i", IsValidDynamicArea(player_wanted_zone[targetid]), IsAGang(targetid), IsPlayerInDynamicArea(targetid, army_zone));
				SendClientMessage(playerid, -1, small_string);
				SendClientMessage(playerid, -1, "IsAnArmy");
			}
			if(IsValidDynamicArea(player_wanted_zone[targetid]) == 1 && IsAGang(targetid) && IsPlayerInDynamicArea(targetid, army_zone)) {
				if(degug_wanted{playerid} == true) {
					SendClientMessage(playerid, -1, "IsValidDynamicArea IsAGang IsPlayerInDynamicArea");
				}
				player_time_arrest[playerid] = 5;
				SendClientMessage(playerid, -1, "Запуск таймера");
				stop player_arrest_timer[playerid];
				player_arrest_timer[playerid] = defer TimerArrestArmy(playerid, targetid);
				return Y_HOOKS_BREAK_RETURN_1;
			}
		}
		if(IsACop(playerid)) {
			if(degug_wanted{playerid} == true) {
				format(small_string, sizeof(small_string), "pl_afk_time = %i", pl_afk_time[targetid]);
				SendClientMessage(playerid, -1, small_string);
			}
			if(pl_afk_time[targetid] > 2) {
				return Y_HOOKS_BREAK_RETURN_1;
			}

			if(PlayerInfo[targetid][pWanted] > 10800 && GetPlayerFraction(playerid) != FRACTION_FBI) {
				SendClientMessage(playerid, -1, ""COLOR_RED"Преступник особо опасен, это дело для FBI");
				return Y_HOOKS_BREAK_RETURN_1;
			}

			if(IsPlayerInRangeOfPoint(playerid, 25, 2108.8223,-2403.1650,13.5847)) return 1;
			if(IsPlayerInRangeOfPoint(playerid, 25, 1691.0641,-2665.7048,13.5869)) return 1;
			if(IsPlayerInRangeOfPoint(playerid, 25, 1877.5209,-2673.4766,13.6030)) return 1;
			if(IsPlayerInRangeOfPoint(playerid, 25, 1826.4791,-2676.6099,13.6351)) return 1;

			if(degug_wanted{playerid} == true) {
				SendClientMessage(playerid, -1, "IsPlayerInRangeOfPoint + запус таймера");
			}

		    player_time_arrest[playerid] = 10;
            SetPVarInt(targetid, "OffArrest", gettime() + 5);

            stop player_arrest_timer[playerid];
			player_arrest_timer[playerid] = defer TimerArrestCop(playerid, targetid);
			return Y_HOOKS_BREAK_RETURN_1;
		}
		return Y_HOOKS_BREAK_RETURN_1;
	}

	return Y_HOOKS_CONTINUE_RETURN_0;
}


hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(degug_wanted{playerid} == true) {
		SendClientMessage(playerid, -1, "OnPlayerLeaveDynArea");
	}
	if(areaid == army_zone) {
		if(IsAGang(playerid)) {
			if(degug_wanted{playerid} == true) {
				SendClientMessage(playerid, -1, "ResetPlayerFromArestArea");
			}
			ResetPlayerFromArestArea(playerid);
		}
	}

	new 
		data[2];

	Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, data, 2);

	if(degug_wanted{playerid} == true) {
		format(small_string, sizeof(small_string), "data = %i|%i", data[0], data[1]);
		SendClientMessage(playerid, -1, small_string);
	}

	if(data[0] == STREAMER_EXTRA_ID_WANTED && data[1] != 0) {
		if(player_arrest_id[playerid] != INVALID_PLAYER_ID) {
			stop player_arrest_timer[playerid];

			player_time_arrest[playerid] = 0;
			player_arrest_id[playerid] = INVALID_PLAYER_ID;
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

timer TimerArrestArmy[1 * 1_000](playerid, targetid) {
	if(degug_wanted{playerid} == true) {
		format(small_string, sizeof(small_string), "time %i vehicle = %i, targetid = %i", player_time_arrest[playerid], IsPlayerInAnyVehicle(playerid), targetid);
		SendClientMessage(playerid, -1, small_string);
	}

	if(IsPlayerInAnyVehicle(playerid)) {
		player_arrest_timer[playerid] = defer TimerArrestArmy(playerid, targetid);
		return 1;
	}

	new time_arrest = player_time_arrest[playerid];

	new small_update_string[26 + 1 + 1];
	format(small_update_string, sizeof(small_update_string), "~w~BEFORE ARREST:~b~~h~ %d", time_arrest);
	GameTextForPlayer(playerid, small_update_string, 1100, 4);
	GameTextForPlayer(targetid, small_update_string, 1100, 4);

	switch(time_arrest) {
		case 5: {
			if(GetPVarInt(playerid,"AntiFloodArrest") > gettime()) { goto skip_arrest; }
			SetPVarInt(playerid,"AntiFloodArrest",gettime() + 60);
			format(small_string, 100, "- %s[%d]: Вы находитесь на запрещенной территории и будете задержаны", PlayerInfo[playerid][pName], playerid);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_CHAT, small_string);
		}
		case 3: {
			if(GetPVarInt(playerid,"AntiFloodArrest2") > gettime()) { goto skip_arrest; }
			SetPVarInt(playerid,"AntiFloodArrest",gettime() + 60);
			format(small_string, 100, "%s достал(а) наручники", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		}
		case 1: {
			format(small_string, 100, "%s надел(а) наручники на подозреваемого", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		}
		case 0: {
			format(small_string, 100, "- %s[%d]: Вы задержаны и отправляетесь в КПЗ", PlayerInfo[playerid][pName], playerid);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_CHAT, small_string);
			if(PlayerInfo[targetid][pWanted] <= 0)
			{
				PlayerInfo[targetid][pJailTime] = 300;
				PlayerInfo[targetid][pJailed] = 1;
				SetPlayerWanted(targetid, 0);
				SetPlayerInt(targetid, "Jailed", PlayerInfo[targetid][pJailed]);
				SetPlayerInt(targetid, "JailTime", PlayerInfo[targetid][pJailTime]);
			}
			else {
				PlayerInfo[targetid][pJailTime] = PlayerInfo[targetid][pWanted];
				PlayerInfo[targetid][pJailed] = 1;
				SetPlayerInt(targetid, "Jailed", PlayerInfo[targetid][pJailed]);
				SetPlayerInt(targetid, "JailTime", PlayerInfo[targetid][pJailTime]);
				PlayerInfo[targetid][pWanted] = 0;
				SetPlayerWanted(targetid, 0);
				SetPlayerInt(targetid, "Wanted", 0);
			}
			IncreaseKarma(playerid);
			

			new it = RandomEx(25, 75);
			new text[90];

			format(text,sizeof(text),"~g~+%d ~w~EXP", it);
			GameTextForPlayer(playerid, text, 3000, 5);

			AddPlayerEXP(playerid, it);

			if(IsPlayerInAnyVehicle(targetid) != 0) {
				RemovePlayerFromVehicle(targetid);
			}
	     	if(PlayerInfo[targetid][pWanted] > 0) {
				PlayerInfo[targetid][pWanted] = 0;
				SetPlayerWanted(targetid, 0);
				SetPlayerInt(targetid, "Wanted", 0);
			}
		}
	}
	skip_arrest:
	player_time_arrest[playerid] = time_arrest - 1;
	if(player_time_arrest[playerid] >= 0) {
		player_arrest_timer[playerid] = defer TimerArrestArmy(playerid, targetid);
	}
	return 1;
}

timer TimerArrestCop[1 * 1_000](playerid, targetid) {
	if(degug_wanted{playerid} == true) {
		format(small_string, sizeof(small_string), "time %i vehicle = %i, targetid = %i", player_time_arrest[playerid], IsPlayerInAnyVehicle(playerid), targetid);
		SendClientMessage(playerid, -1, small_string);
	}
	if(IsPlayerInAnyVehicle(playerid)) {
		player_arrest_timer[playerid] = defer TimerArrestCop(playerid, targetid);
		return 1;
	}

	new time_arrest = player_time_arrest[playerid];

	new small_update_string[26 + 1 + 1];
	format(small_update_string, sizeof(small_update_string), "~w~BEFORE ARREST:~b~~h~ %d", time_arrest);
	GameTextForPlayer(playerid, small_update_string, 1100, 4);
	GameTextForPlayer(targetid, small_update_string, 1100, 4);

	switch(time_arrest) {
		case 10: {
			if(GetPVarInt(playerid,"AntiFloodArrest") > gettime()) { goto skip_arrest; }
			SetPVarInt(playerid,"AntiFloodArrest",gettime() + 60);
			format(small_string, 100, "- %s[%d]: Подозреваемый %s, немедленно остановитесь!", PlayerInfo[playerid][pName], playerid, PlayerInfo[targetid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_CHAT, small_string);
		}
		case 9: {
			if(GetPVarInt(playerid,"AntiFloodArrest2") > gettime()) { goto skip_arrest; }
			SetPVarInt(playerid,"AntiFloodArrest",gettime() + 60);
 			format(small_string, 100, "- %s[%d]: Работает полиция, у Вас есть право хранить молчание", PlayerInfo[playerid][pName], playerid);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_CHAT, small_string);
		}
		case 7: {
			if(GetPVarInt(playerid,"AntiFloodArrest3") > gettime()) { goto skip_arrest; }
			SetPVarInt(playerid,"AntiFloodArrest",gettime() + 60);
			format(small_string, 100, "%s достал(а) наручники", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		}
		case 5: {
			if(GetPVarInt(playerid,"AntiFloodArrest4") > gettime()) { goto skip_arrest; }
			SetPVarInt(playerid,"AntiFloodArrest",gettime() + 60);
			format(small_string, 100, "- %s[%d]: Вы находитесь в федеральном розыске, и будете задержаны", PlayerInfo[playerid][pName], playerid);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_CHAT, small_string);
		}
		case 1: {
			format(small_string, 100, "%s надел(а) наручники на подозреваемого", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		}
		case 0: {
			format(small_string, 100, "- %s[%d]: Вы задержаны и отправляетесь в КПЗ", PlayerInfo[playerid][pName], playerid);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_CHAT, small_string);
			format(small_string, 100, ""COLOR_BLUE"Полицейский %s задержал преступника %s", PlayerInfo[playerid][pName], PlayerInfo[targetid][pName]);
        	SendPoliceAlert(-1, small_string);
			PlayerInfo[targetid][pJailTime] = PlayerInfo[targetid][pWanted];
			PlayerInfo[targetid][pJailed] = 1;
			SetPlayerInt(targetid, "Jailed", PlayerInfo[targetid][pJailed]);
			SetPlayerInt(targetid, "JailTime", PlayerInfo[targetid][pJailTime]);
	     	if(PlayerInfo[targetid][pWanted] > 0) {
			PlayerInfo[targetid][pWanted] = 0;
			SetPlayerWanted(targetid, 0);
			SetPlayerInt(targetid, "Wanted", 0);
			}
			IncreaseKarma(playerid);

			new it = RandomEx(25, 125);
			new text[90];

			format(text,sizeof(text),"~g~+%d ~w~EXP", it);
			GameTextForPlayer(playerid, text, 3000, 5);

			AddPlayerEXP(playerid, it);
		}
	}

	skip_arrest:
	player_time_arrest[playerid] = time_arrest - 1;
	if(player_time_arrest[playerid] >= 0) {
		player_arrest_timer[playerid] = defer TimerArrestCop(playerid, targetid);
	}
	return 1;
}