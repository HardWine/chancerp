#if defined farm_system_included
	#endinput
#endif

#define farm_system_included	

#include <YSI-Include\YSI\YSI\y_timers>
#include <YSI-Include\YSI\YSI\y_hooks>

#define MAX_FARM_COORD 			(5)

enum E_FARM_COORD {
	Float: E_FARM_X,
	Float: E_FARM_Y,
	Float: E_FARM_Z,
}

static const 
	Farm.Coord_0[MAX_FARM_COORD][E_FARM_COORD] = {
		{-244.0340, -1374.5000, 10.2968},
		{-244.5132, -1379.3893, 10.1628},
		{-241.7643, -1376.9087, 10.1990},
		{-241.9362, -1378.9124, 10.1594},
		{-243.1588, -1375.3256, 10.2700}
	},
	Farm.Coord_1[MAX_FARM_COORD][E_FARM_COORD] = {
		{-309.6248, -1350.7216, 8.6985},
		{-307.9674, -1350.7539, 8.5948},
		{-305.9592, -1350.8691, 8.4713},
		{-305.0207, -1348.0299, 8.3307},
		{-307.8632, -1350.9745, 8.5945}
	},
	Farm.Coord_2[MAX_FARM_COORD][E_FARM_COORD] = {
		{-288.2651, -1415.0011, 12.3010},
		{-288.8513, -1412.6829, 12.4116},
		{-289.2064, -1410.0813, 12.5129},
		{-290.9688, -1410.3022, 12.6391},
		{-290.4985, -1414.4073, 12.4860}
	},
	Farm.EndCoord[3][E_FARM_COORD] = {
		{-246.7454, -1376.7000, 10.2475},
		{-307.1583, -1347.2510, 8.44304},
		{-291.1464, -1412.6449, 12.5853}
	};

static 
	Player.FarmMoney[MAX_PLAYERS],
	Player.TotalBush[MAX_PLAYERS],
	bool: Player.FarmIsEnd[MAX_PLAYERS char],
	Player.ZoneType[MAX_PLAYERS char],
	Player.FarmTimer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...},
	Player.FarmCP[MAX_PLAYERS] = {INVALID_DYNAMIC_CP, ...},
	bool: Player.isJobFarm[MAX_PLAYERS char];

static 
	Pickup.Farm[4],
	Zone.Farm[4];

static const 
	Farm.Skin[4] = {132, 133, 202, 128};

enum E_FARM_INFO {
	E_VehicleID,
	E_Total,
	Text3D: E_LabelID
};

static 
	Farm.Info[3][E_FARM_INFO];

hook OnGameModeInit() {
	Pickup.Farm[0] = CreateDynamicPickup(1275, 1, -382.9781, -1426.2599, 26.3194, 0, 0, -1); // Устройство на работу
	Zone.Farm[0] = CreateDynamicCircle(-382.9781, -1426.2599, 1.00, 0, 0, -1);

	Zone.Farm[1] = CreateDynamicCircle(-244.0340, -1374.5000, 10.00, 0, 0, -1);
	Zone.Farm[2] = CreateDynamicCircle(-309.6248, -1350.7216, 10.00, 0, 0, -1);
	Zone.Farm[3] = CreateDynamicCircle(-288.2651, -1415.0011, 10.00, 0, 0, -1);

	Pickup.Farm[1] = CreateDynamicPickup(861, 1, -246.7454, -1376.7000, 10.2475, 0, 0, -1); // Сдача в машину 1
	Pickup.Farm[2] = CreateDynamicPickup(861, 1, -307.1583, -1347.2510, 8.44304, 0, 0, -1); // Сдача в машину 2
	Pickup.Farm[3] = CreateDynamicPickup(861, 1, -291.1464, -1412.6449, 12.5853, 0, 0, -1); // Сдача в машину 3

	Farm.Info[0][E_VehicleID] = AddStaticVehicle(478, -294.1775, -1412.4579, 12.8644, 86.0386, 3, 1);
	Farm.Info[0][E_LabelID] = CreateDynamic3DTextLabel(""COLOR_BLUE"Загружено:\n {FFFFFF}0/200", 0xFFFFFFFF, 
		-291.1464, -1412.6449, 13.5853, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);
	Farm.Info[0][E_Total] = 0;

	Farm.Info[1][E_VehicleID] = AddStaticVehicle(478, -306.8991, -1344.1766, 8.3550, 355.2137, 128, 1);
	Farm.Info[1][E_LabelID] = CreateDynamic3DTextLabel(""COLOR_BLUE"Загружено:\n {FFFFFF}0/200", 0xFFFFFFFF, 
		-307.1583, -1347.2510, 9.4434, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);
	Farm.Info[1][E_Total] = 0;

	Farm.Info[2][E_VehicleID] = AddStaticVehicle(478, -249.8366, -1376.5028, 10.2615, 86.0235, 6, 1);
	Farm.Info[2][E_LabelID] = CreateDynamic3DTextLabel(""COLOR_BLUE"Загружено:\n {FFFFFF}0/200", 0xFFFFFFFF, 
		-246.7454, -1376.7000, 11.2475, 
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1
	);
	Farm.Info[2][E_Total] = 0;
}

hook OnPlayerConnect(playerid) {
	Player.FarmCP[playerid] = INVALID_DYNAMIC_CP;

	Player.FarmTimer[playerid] = INVALID_TIMER_ID;
	Player.ZoneType{playerid} = 0;
	Player.FarmMoney[playerid] = 0;
	Player.TotalBush[playerid] = 0;
	Player.FarmIsEnd{playerid} = false;
	Player.isJobFarm{playerid} = false;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
	if(Player.FarmCP[playerid] != INVALID_DYNAMIC_CP) {
		DestroyDynamicCP(Player.FarmCP[playerid]);
	}

	if(Player.FarmTimer[playerid] != INVALID_TIMER_ID) {
		stop Player.FarmTimer[playerid];
	}

	Player.FarmCP[playerid] = INVALID_DYNAMIC_CP;
	Player.FarmTimer[playerid] = INVALID_TIMER_ID;

	Player.ZoneType{playerid} = 0;
	Player.FarmMoney[playerid] = 0;
	Player.TotalBush[playerid] = 0;
	Player.FarmIsEnd{playerid} = false;
	Player.isJobFarm{playerid} = false;
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == Zone.Farm[0]) { // Устройство на работу 
		if(Player.isJobFarm{playerid} == true) {
			SendClientMessage(playerid, -1, ""COLOR_RED"Вы уволились с работы фермера");
			CBackSkin(playerid);

			return Player.isJobFarm{playerid} = false;
		} else {
			if(IsPlayerInFraction(playerid) == true) {
				return SendClientMessage(playerid, -1, "Вы состоите в организации.");
			}
			Player.isJobFarm{playerid} = true;

			if(PlayerInfo[playerid][pFarmSkill] < 200) {
				if(PlayerInfo[playerid][pSex] == 1) {
					SetPlayerSkin(playerid, 131);
				} else {
					new RandomF = random(sizeof(Farm.Skin));
					SetPlayerSkin(playerid, Farm.Skin[RandomF]);
				}
			}
			if(PlayerInfo[playerid][pFarmSkill] >= 200) {
				if(PlayerInfo[playerid][pSex] == 1) {
					SetPlayerSkin(playerid, 201);
				} else {
					SetPlayerSkin(playerid, 161);
				}
			}
			if(PlayerInfo[playerid][pFarmSkill] > 500) {
				if(PlayerInfo[playerid][pSex] == 1) {
					SetPlayerSkin(playerid, 198);
				} else {
					SetPlayerSkin(playerid, 34);
				}
			}

			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали работу фермера. Отправляйтесь в поле");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Увеличивая скилл фермера вы получите больше EXP!");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Подойдите к одной из машин на поле, а после встаньте на красную метку.");
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	if(Player.isJobFarm{playerid} == true) {
		if(areaid == Zone.Farm[1]) {
			if(Player.FarmCP[playerid] == INVALID_DYNAMIC_CP) {
				Player.ZoneType{playerid} = 0;
				new 
					random_value = random(MAX_FARM_COORD);
				Player.FarmCP[playerid] = CreateDynamicCP(Farm.Coord_0[random_value][E_FARM_X], Farm.Coord_0[random_value][E_FARM_Y], Farm.Coord_0[random_value][E_FARM_Z], 
					1.50, 0, 0, playerid
				);
			}
			return Y_HOOKS_BREAK_RETURN_1;
		}

		if(areaid == Zone.Farm[2]) {
			if(Player.FarmCP[playerid] == INVALID_DYNAMIC_CP) {
				Player.ZoneType{playerid} = 1;
				new 
					random_value = random(MAX_FARM_COORD);
				Player.FarmCP[playerid] = CreateDynamicCP(Farm.Coord_1[random_value][E_FARM_X], Farm.Coord_1[random_value][E_FARM_Y], Farm.Coord_1[random_value][E_FARM_Z], 
					1.50, 0, 0, playerid
				);
			}
			return Y_HOOKS_BREAK_RETURN_1;
		}

		if(areaid == Zone.Farm[3]) {
			if(Player.FarmCP[playerid] == INVALID_DYNAMIC_CP) {
				Player.ZoneType{playerid} = 2;
				new 
					random_value = random(MAX_FARM_COORD);
				Player.FarmCP[playerid] = CreateDynamicCP(Farm.Coord_2[random_value][E_FARM_X], Farm.Coord_2[random_value][E_FARM_Y], Farm.Coord_2[random_value][E_FARM_Z], 
					1.50, 0, 0, playerid
				);
			}
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}	
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid) {
	if(areaid == Zone.Farm[0]) { // Устройство на работу 
		return Y_HOOKS_BREAK_RETURN_1;
	}
	if(Player.isJobFarm{playerid} == true) {
		if(areaid == Zone.Farm[1]) {
			if(Player.FarmCP[playerid] != INVALID_DYNAMIC_CP) {
				Player.ZoneType{playerid} = 0;
				DestroyDynamicCP(Player.FarmCP[playerid]);
				Player.FarmCP[playerid] = INVALID_DYNAMIC_CP;
			}
			return Y_HOOKS_BREAK_RETURN_1;
		}

		if(areaid == Zone.Farm[2]) {
			if(Player.FarmCP[playerid] != INVALID_DYNAMIC_CP) {
				Player.ZoneType{playerid} = 0;
				DestroyDynamicCP(Player.FarmCP[playerid]);
				Player.FarmCP[playerid] = INVALID_DYNAMIC_CP;
			}
			return Y_HOOKS_BREAK_RETURN_1;
		}

		if(areaid == Zone.Farm[3]) {
			if(Player.FarmCP[playerid] != INVALID_DYNAMIC_CP) {
				Player.ZoneType{playerid} = 0;
				DestroyDynamicCP(Player.FarmCP[playerid]);
				Player.FarmCP[playerid] = INVALID_DYNAMIC_CP;
			}
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}	
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerPickUpDynPickup(playerid, STREAMER_TAG_PICKUP pickupid) {
	if(pickupid == Pickup.Farm[1]) {
		if(Player.FarmIsEnd{playerid} == true) {
			if(Farm.Info[0][E_Total] + 1 >= 200) {
				return SendClientMessage(playerid, -1, ""COLOR_RED"Автомобиль переполнен");
			}
			Farm.Info[0][E_Total]++;
			format(small_string, sizeof(small_string), ""COLOR_BLUE"Загружено:\n {FFFFFF}%i/200", Farm.Info[0][E_Total]);
			UpdateDynamic3DTextLabelText(Farm.Info[0][E_LabelID], 0xFFFFFFFF, small_string);

			Player.FarmIsEnd{playerid} = false;

			new 
	  			hmc,
	   			FarmSkill = PlayerInfo[playerid][pFarmSkill];

    		if((0 <= FarmSkill <= 49)) {
				hmc = 1;
				format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/50", hmc, PlayerInfo[playerid][pFarmSkill]);
    		} else if(FarmSkill == 50) {
	 			hmc = 2;
	 			format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/100", hmc, PlayerInfo[playerid][pFarmSkill]);
	 			SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
		 	} else if((51 <= FarmSkill <= 99)) {
				hmc = 2;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/100", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 100) {
		 	    hmc = 3;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/250", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((101 <= FarmSkill <= 249)) {
		 	    hmc = 3;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/250", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 250) {
		 	    hmc = 4;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/500", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((251 <= FarmSkill <= 499)) {
		 		hmc = 4;
		 		format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/500", hmc, PlayerInfo[playerid][pFarmSkill]);
		 	} else if(FarmSkill == 500) {
		 	    hmc = 5;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/750", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((501 <= FarmSkill <= 749)) {
		 	    hmc = 5;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/750", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 750) {
			 	hmc = 6;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/900", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((751 <= FarmSkill <= 899)) {
			 	hmc = 6;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/900", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 900) {
				hmc = 7;
				format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1000", hmc, PlayerInfo[playerid][pFarmSkill]);
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((901 <= FarmSkill <= 999)) {
			 	hmc = 7;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1000", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 1000) {
			 	hmc = 8;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1250", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((1001 <= FarmSkill <= 1249)) {
			 	hmc = 8;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1250", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 1250) {
		 	    hmc = 9;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1500", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((1251 <= FarmSkill <= 1499)) {
			 	hmc = 9;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1500", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 1500) {
			 	hmc = 10;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы достигли максимального уровня фермера. Поздравляем!");
			} else {
				hmc = 10;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: ~b~~h~FULL", hmc);
			}
			GameTextForPlayer(playerid, small_string, 5000, 5);
			Player.AddEXP(PlayerInfo[playerid][pID], hmc, E_JOB_BUS_DRIVER, playerid);
			PlayerInfo[playerid][pFarmSkill] += 1;
			SetPlayerInt(playerid, "FarmSkill", PlayerInfo[playerid][pFarmSkill]);

			new 
				random_value = random(MAX_FARM_COORD);
			Player.ZoneType{playerid} = 0;
			Player.FarmCP[playerid] = CreateDynamicCP(Farm.Coord_0[random_value][E_FARM_X], Farm.Coord_0[random_value][E_FARM_Y], Farm.Coord_0[random_value][E_FARM_Z], 
				1.50, 0, 0, playerid
			);
		}
	}
	if(pickupid == Pickup.Farm[2]) {
		if(Player.FarmIsEnd{playerid} == true) {
			if(Farm.Info[1][E_Total] + 1 >= 200) {
				return SendClientMessage(playerid, -1, ""COLOR_RED"Автомобиль переполнен");
			}
			Farm.Info[1][E_Total]++;
			format(small_string, sizeof(small_string), ""COLOR_BLUE"Загружено:\n {FFFFFF}%i/200", Farm.Info[1][E_Total]);
			UpdateDynamic3DTextLabelText(Farm.Info[1][E_LabelID], 0xFFFFFFFF, small_string);

			Player.FarmIsEnd{playerid} = false;

			new 
	  			hmc,
	   			FarmSkill = PlayerInfo[playerid][pFarmSkill];

    		if((0 <= FarmSkill <= 49)) {
				hmc = 1;
				format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/50", hmc, PlayerInfo[playerid][pFarmSkill]);
    		} else if(FarmSkill == 50) {
	 			hmc = 2;
	 			format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/100", hmc, PlayerInfo[playerid][pFarmSkill]);
	 			SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
		 	} else if((51 <= FarmSkill <= 99)) {
				hmc = 2;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/100", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 100) {
		 	    hmc = 3;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/250", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((101 <= FarmSkill <= 249)) {
		 	    hmc = 3;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/250", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 250) {
		 	    hmc = 4;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/500", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((251 <= FarmSkill <= 499)) {
		 		hmc = 4;
		 		format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/500", hmc, PlayerInfo[playerid][pFarmSkill]);
		 	} else if(FarmSkill == 500) {
		 	    hmc = 5;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/750", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((501 <= FarmSkill <= 749)) {
		 	    hmc = 5;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/750", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 750) {
			 	hmc = 6;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/900", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((751 <= FarmSkill <= 899)) {
			 	hmc = 6;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/900", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 900) {
				hmc = 7;
				format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1000", hmc, PlayerInfo[playerid][pFarmSkill]);
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((901 <= FarmSkill <= 999)) {
			 	hmc = 7;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1000", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 1000) {
			 	hmc = 8;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1250", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((1001 <= FarmSkill <= 1249)) {
			 	hmc = 8;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1250", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 1250) {
		 	    hmc = 9;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1500", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((1251 <= FarmSkill <= 1499)) {
			 	hmc = 9;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1500", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 1500) {
			 	hmc = 10;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы достигли максимального уровня фермера. Поздравляем!");
			} else {
				hmc = 10;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: ~b~~h~FULL", hmc);
			}
			GameTextForPlayer(playerid, small_string, 5000, 5);
			Player.AddEXP(PlayerInfo[playerid][pID], hmc, E_JOB_BUS_DRIVER, playerid);
			PlayerInfo[playerid][pFarmSkill] += 1;
			SetPlayerInt(playerid, "FarmSkill", PlayerInfo[playerid][pFarmSkill]);

			new 
				random_value = random(MAX_FARM_COORD);
			Player.ZoneType{playerid} = 1;
			Player.FarmCP[playerid] = CreateDynamicCP(Farm.Coord_1[random_value][E_FARM_X], Farm.Coord_1[random_value][E_FARM_Y], Farm.Coord_1[random_value][E_FARM_Z], 
				1.50, 0, 0, playerid
			);
		}
	}
	if(pickupid == Pickup.Farm[1]) {
		if(Player.FarmIsEnd{playerid} == true) {
			if(Farm.Info[2][E_Total] + 1 >= 200) {
				return SendClientMessage(playerid, -1, ""COLOR_RED"Автомобиль переполнен");
			}
			Farm.Info[2][E_Total]++;
			format(small_string, sizeof(small_string), ""COLOR_BLUE"Загружено:\n {FFFFFF}%i/200", Farm.Info[2][E_Total]);
			UpdateDynamic3DTextLabelText(Farm.Info[2][E_LabelID], 0xFFFFFFFF, small_string);

			Player.FarmIsEnd{playerid} = false;

			new 
	  			hmc,
	   			FarmSkill = PlayerInfo[playerid][pFarmSkill];

    		if((0 <= FarmSkill <= 49)) {
				hmc = 1;
				format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/50", hmc, PlayerInfo[playerid][pFarmSkill]);
    		} else if(FarmSkill == 50) {
	 			hmc = 2;
	 			format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/100", hmc, PlayerInfo[playerid][pFarmSkill]);
	 			SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
		 	} else if((51 <= FarmSkill <= 99)) {
				hmc = 2;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/100", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 100) {
		 	    hmc = 3;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/250", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((101 <= FarmSkill <= 249)) {
		 	    hmc = 3;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/250", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 250) {
		 	    hmc = 4;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/500", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((251 <= FarmSkill <= 499)) {
		 		hmc = 4;
		 		format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/500", hmc, PlayerInfo[playerid][pFarmSkill]);
		 	} else if(FarmSkill == 500) {
		 	    hmc = 5;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/750", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((501 <= FarmSkill <= 749)) {
		 	    hmc = 5;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/750", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 750) {
			 	hmc = 6;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/900", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((751 <= FarmSkill <= 899)) {
			 	hmc = 6;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/900", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 900) {
				hmc = 7;
				format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1000", hmc, PlayerInfo[playerid][pFarmSkill]);
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((901 <= FarmSkill <= 999)) {
			 	hmc = 7;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1000", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 1000) {
			 	hmc = 8;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1250", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((1001 <= FarmSkill <= 1249)) {
			 	hmc = 8;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1250", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 1250) {
		 	    hmc = 9;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1500", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			} else if((1251 <= FarmSkill <= 1499)) {
			 	hmc = 9;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1500", hmc, PlayerInfo[playerid][pFarmSkill]);
			} else if(FarmSkill == 1500) {
			 	hmc = 10;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы достигли максимального уровня фермера. Поздравляем!");
			} else {
				hmc = 10;
			 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: ~b~~h~FULL", hmc);
			}
			GameTextForPlayer(playerid, small_string, 5000, 5);
			Player.AddEXP(PlayerInfo[playerid][pID], hmc, E_JOB_BUS_DRIVER, playerid);
			PlayerInfo[playerid][pFarmSkill] += 1;
			SetPlayerInt(playerid, "FarmSkill", PlayerInfo[playerid][pFarmSkill]);

			new 
				random_value = random(MAX_FARM_COORD);
			Player.ZoneType{playerid} = 2;
			Player.FarmCP[playerid] = CreateDynamicCP(Farm.Coord_2[random_value][E_FARM_X], Farm.Coord_2[random_value][E_FARM_Y], Farm.Coord_2[random_value][E_FARM_Z], 
				1.50, 0, 0, playerid
			);
		}
	}
	return Y_HOOKS_BREAK_RETURN_1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP checkpointid) {
	if(checkpointid == Player.FarmCP[playerid]) {
		ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,1,1,1,1,0);
	    SendClientMessage(playerid, -1, "Подождите 10 секунд...");
	    SetPVarInt(playerid, "MinusTime", 10);
	    DestroyDynamicCP(Player.FarmCP[playerid]);
		Player.FarmTimer[playerid] = defer Farm.End(playerid);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

timer Farm.End[10_000](playerid) {
	if(Player.isJobFarm{playerid} == false) {
		return 1;
	}

	Player.FarmIsEnd{playerid} = true;
	ClearAnimations(playerid);
    SendClientMessage(playerid, -1, ""COLOR_ORANGE"Доставьте урожай в автомобиль");


    return Player.FarmTimer[playerid] = INVALID_TIMER_ID;
}