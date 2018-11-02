#if defined army_tp_included
	#endinput
#endif

#define army_tp_included

forward AT_OnGameModeInit();
AT_OnPlayerEnterDynArea(playerid, areaid);

new 
	army_tp_pickup[4],
	army_tp_zone[4],
	army_fix_enter;

public AT_OnGameModeInit() {
	army_tp_pickup[0] = CreateDynamicPickup(1239, 23, 270.9149, 1821.2976, 17.7465);
	army_tp_pickup[1] = CreateDynamicPickup(1239, 23, 298.6202, 1821.9934, 17.7462);
	army_tp_pickup[2] = CreateDynamicPickup(1239, 23, 279.1905, 1833.1390, 18.0874);
	army_tp_pickup[3] = CreateDynamicPickup(1239, 23, 291.7455, 1833.7161, 18.1027);

	army_tp_zone[0] = CreateDynamicSphere(270.9149, 1821.2976, 17.7465, 3.00);
	army_tp_zone[1] = CreateDynamicSphere(298.6202, 1821.9934, 17.7462, 3.00);
	army_tp_zone[2] = CreateDynamicSphere(279.1905, 1833.1390, 18.0874, 2.00);
	army_tp_zone[3] = CreateDynamicSphere(291.7455, 1833.7161, 18.1027, 2.00);

	army_fix_enter = CreateDynamicCube(222.3844, 1874.9106, 11.1352, 237.7152, 1869.5443, 15.4699);

	CreateObject(14408,358.2763672,2035.5468750,-7.5504284,0.0000000,0.0000000,0.0000000); //object(carter-floors04) (1)
	CreateObject(14437,358.2001953,2027.6093750,-14.8990135,0.0000000,0.0000000,0.0000000); 

	// AddStaticVehicleEx(548,217.8000000,2016.5000000,21.7000000,270.0000000,245,245,15); //Cargobob
	// AddStaticVehicleEx(548,217.8000000,1973.0000000,21.7000000,270.0000000,245,245,15); //Cargobob

	// AddStaticVehicleEx(455,299.7000100,2047.7000000,18.2000000,180.0000000,132,148,15); //Flatbed
	// AddStaticVehicleEx(455,308.0000000,2047.8000000,18.2000000,180.0000000,132,148,15); //Flatbed
	// AddStaticVehicleEx(455,317.2000100,2047.7000000,18.2000000,180.0000000,132,148,15); //Flatbed
	CreateObject(3268,308.2000100,2048.8999000,16.6000000,0.0000000,0.0000000,90.0000000); //object(mil_hangar1_) (1)
	CreateObject(9241,218.8000000,1973.1000000,18.3000000,0.0000000,0.0000000,0.0000000); //object(copbits_sfn) (1)
	CreateObject(9241,218.8000000,2016.5000000,18.3000000,0.0000000,0.0000000,0.0000000); //object(copbits_sfn) (2)

}

public AT_OnPlayerEnterDynArea(playerid, areaid) {
	if(areaid == army_tp_zone[0]) {
		if(IsPlayerInAnyVehicle(playerid)) {
			SetVehiclePos(GetPlayerVehicleID(playerid), 308.6202, 1821.9934, 17.7462);
			SetVehicleZAngle(GetPlayerVehicleID(playerid), 270.00);
		} else {
			SetPlayerPos(playerid, 308.6202, 1821.9934, 17.7462);
			SetPlayerFacingAngle(playerid, 270.00);
		}
		SetCameraBehindPlayer(playerid);
		return 1;
	} else if(areaid == army_tp_zone[1]) {
		if(IsPlayerInAnyVehicle(playerid)) {
			SetVehiclePos(GetPlayerVehicleID(playerid), 260.9149, 1821.2976, 17.7465);
			SetVehicleZAngle(GetPlayerVehicleID(playerid), 90.00);
		} else {
			SetPlayerPos(playerid, 260.9149, 1821.2976, 17.7465);
			SetPlayerFacingAngle(playerid, 90.00);
		}
		SetCameraBehindPlayer(playerid);
		return 1;
	} else if(areaid == army_tp_zone[2]) {
		if(IsPlayerInAnyVehicle(playerid) != 0) {
			return 1;
		}

		SetPlayerPos(playerid, 291.7455, 1836.7161, 18.1027);
		SetPlayerFacingAngle(playerid, 0.00);
		SetCameraBehindPlayer(playerid);
		return 1;
	} else if(areaid == army_tp_zone[3]) {
		if(IsPlayerInAnyVehicle(playerid) != 0) {
			return 1;
		}

		//SetPlayerPos(playerid, 279.1905, 1836.1390, 18.0874);
		SetPlayerPos(playerid, 279.1545, 1836.8062, 17.6481);
		SetPlayerFacingAngle(playerid, 0.00);
		SetCameraBehindPlayer(playerid);
		return 1;
	} else if(areaid == army_fix_enter) {
		if(IsPlayerInAnyVehicle(playerid)) {
			SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		}
		return 1;
	}
	return 0;
}