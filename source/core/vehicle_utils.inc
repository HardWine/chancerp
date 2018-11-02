#if defined vehicle_utils_included
	#endinput
#endif

#define vehicle_utils_included	

forward bool:Vehicle.SetLock(const playerid, const vehicleid);
forward bool:Vehicle.SetUnLock(const playerid, const vehicleid);

public bool:Vehicle.SetLock(const playerid, const vehicleid) {
	if(IsValidVehicle(vehicleid) == 0) {
		return false;
	}

	SetVehicleParamsForPlayer(vehicleid, playerid, 0, 1);
	return true;
}

public bool:Vehicle.SetUnLock(const playerid, const vehicleid) {
	if(IsValidVehicle(vehicleid) == 0) {
		return false;
	}

	SetVehicleParamsForPlayer(vehicleid, playerid, 0, 0);
	return true;
}