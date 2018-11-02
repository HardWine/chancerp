#if defined npc_system_included
	#endinput
#endif
new Coach;
#define npc_system_included

forward NPC_OnGameModeInit();
public NPC_OnGameModeInit() {
	Coach =	AddStaticVehicle(437,1695.4336,-2316.7441,-2.7599,90.3345,75,59);
	ConnectNPC("Otto_Mann","starterbus");
}

forward NPC_OnPlayerSpawn(playerid);
public NPC_OnPlayerSpawn(playerid) {
	if(IsPlayerNPC(playerid)) {
		new playername[64];
		GetPlayerName(playerid,playername,64);
		SetPlayerColor(playerid, CIVIL_COLOR);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 0);
		if(!strcmp(playername,"Otto_Mann",true)) {
			PutPlayerInVehicle(playerid, Coach, 0);
			return 1;
		}
		new vehicleid = GetPlayerVehicleID(playerid);
		SetVehicleParamsForPlayerEx(vehicleid,playerid,0,1); 
		return 1;
	}
	return 1;
}

forward NPC_OnPlayerRequestClass(playerid, classid);
public NPC_OnPlayerRequestClass(playerid, classid) {
	if(IsPlayerNPC(playerid)) {
		new playername[64];
		GetPlayerName(playerid,playername,64);

		if(!strcmp(playername,"Otto_Mann",true)) {
			SetSpawnInfo(playerid,0,255,1705.2080,-2331.4373,-2.6797,4.0268, 0, 0, 0, 0, 0, 0);
		}
		return SpawnPlayer(playerid);
	}
	return 1;
}