#if defined fuel_system_included
	#endinput
#endif

#define fuel_system_included

#include <YSI_Coding\y_hooks>

#define DEFAULT_VEHICLE_FUEL 			(45.00)
#define MAX_REFILL		 				(150)

new fuel_consumption = 1;

enum 
	E_VEHICLE {
		E_ID,
		Float: E_FUEL,
	};

new 
	VehicleFuel[MAX_VEHICLES][E_VEHICLE];

new 
	Iterator:VehicleInfo<MAX_VEHICLES>;

stock FUEL_AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2)
{
	new 
		native_return_value = AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2);
	
	if(AddVehicleToIterator(native_return_value)) {
		return native_return_value;
	} else {
		return INVALID_VEHICLE_ID;
	}
}
#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif

#define AddStaticVehicle FUEL_AddStaticVehicle

stock FUEL_AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, addsiren=0)
{
	new 
		native_return_value = AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2, respawn_delay, addsiren);
	
	if(AddVehicleToIterator(native_return_value)) {
		return native_return_value;
	} else {
		return INVALID_VEHICLE_ID;
	}
}
#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif

#define AddStaticVehicleEx FUEL_AddStaticVehicleEx


stock FUEL_CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren=0)
{
	new 
		native_return_value = CreateVehicle(vehicletype, x, y, z, rotation, color1, color2, respawn_delay, addsiren);
	
	if(AddVehicleToIterator(native_return_value)) {
		return native_return_value;
	} else {
		return INVALID_VEHICLE_ID;
	}
}
#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif

#define CreateVehicle FUEL_CreateVehicle

stock FUEL_DestroyVehicle(vehicleid)
{
	if(Iter_Contains(VehicleInfo, vehicleid)) {
		Iter_Remove(VehicleInfo, vehicleid);
	}
	return DestroyVehicle(vehicleid);
}
#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif

#define DestroyVehicle FUEL_DestroyVehicle

stock AddVehicleToIterator(vehicleid) {
	new 
		iterarot_vehicleid = Iter_Free(VehicleInfo);

	if(iterarot_vehicleid == -1) {
		return -1;
	}

	VehicleFuel[iterarot_vehicleid][E_ID] = vehicleid;
	VehicleFuel[iterarot_vehicleid][E_FUEL] = DEFAULT_VEHICLE_FUEL;

	Iter_Add(VehicleInfo, iterarot_vehicleid);
	return iterarot_vehicleid;
}

stock GetVehicleFuel(const vehicleid) {
	foreach(new i: VehicleInfo) {
		if(VehicleFuel[i][E_ID] == vehicleid) {
			return floatround(VehicleFuel[i][E_FUEL]);	
		}
	}
	return 0;
}

stock SetVehicleFuel(const vehicleid, fuel) {
	foreach(new i: VehicleInfo) {
		if(VehicleFuel[i][E_ID] == vehicleid) {
			if(fuel > MAX_REFILL) {
				fuel = MAX_REFILL;
			}
			VehicleFuel[i][E_FUEL] = float(fuel);

			foreach(new p:Player)
			{
				if(IsValidVehicle(caridhouse[p]) && caridhouse[p] == vehicleid)
				{
					if(PlayerInfo[p][pSelectedSlot] == 1) {
						SetPlayerInt(p, "Fuel1", VehicleFuel[i][E_FUEL]);
					} else if(PlayerInfo[p][pSelectedSlot] == 2) {
						SetPlayerInt(p, "Fuel2", VehicleFuel[i][E_FUEL]);	
					}
				}
			}

			return 1;	
		}
	}
	return 0;
}

stock AddVehicleFuel(const vehicleid, const fuel) {
	foreach(new i: VehicleInfo) {
		if(VehicleFuel[i][E_ID] == vehicleid) {
			if(VehicleFuel[i][E_FUEL] + fuel > float(MAX_REFILL)) {
				VehicleFuel[i][E_FUEL] = float(MAX_REFILL);
			} else {
				VehicleFuel[i][E_FUEL] += float(fuel);
			}

			foreach(new p:Player)
			{
				if(IsValidVehicle(caridhouse[p]) && caridhouse[p] == vehicleid)
				{
					if(PlayerInfo[p][pSelectedSlot] == 1) {
						SetPlayerInt(p, "Fuel1", VehicleFuel[i][E_FUEL]);
					} else if(PlayerInfo[p][pSelectedSlot] == 2) {
						SetPlayerInt(p, "Fuel2", VehicleFuel[i][E_FUEL]);	
					}
				}
			}

			return 1;	
		}
	}
	return 0;
}

task VehicleFuelUpdate[45000]() 
{
	new engine, lights, alarm, doors, bonnet, boot, objective, vehicleid;

    foreach(new i: Vehicle)
    {
    	vehicleid = VehicleFuel[i][E_ID];
    	if(GetVehicleModel(vehicleid) == 481 || GetVehicleModel(vehicleid) == 509 || GetVehicleModel(vehicleid) == 510) continue;
        if(!IsValidVehicle(vehicleid)) continue;
        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
        if(engine != 1) continue;
		VehicleFuel[i][E_FUEL] -= float(fuel_consumption);
		if(VehicleFuel[i][E_FUEL] < 0.1) {
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(vehicleid, 0, 0, alarm, doors, bonnet, boot, objective);
		}

		foreach(new p:Player)
		{
			if(IsValidVehicle(caridhouse[p]) && caridhouse[p] == vehicleid)
			{
				if(PlayerInfo[p][pSelectedSlot] == 1) {
					SetPlayerInt(p, "Fuel1", VehicleFuel[i][E_FUEL]);
				} else if(PlayerInfo[p][pSelectedSlot] == 2) {
					SetPlayerInt(p, "Fuel2", VehicleFuel[i][E_FUEL]);	
				}
			}
		}
    }
}


stock UpdateIndicatorStatus(playerid) {
	new vehicleid = GetPlayerVehicleID(playerid);

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);	

	if(engine == 1) {
		PlayerTextDrawBoxColor(playerid, car_params_td[playerid][1], 16711935);
	} else {
		PlayerTextDrawBoxColor(playerid, car_params_td[playerid][1], -16776961);
	}

	if(doors == 1) {
		PlayerTextDrawBoxColor(playerid, car_params_td[playerid][0], -16776961);
	} else {
		PlayerTextDrawBoxColor(playerid, car_params_td[playerid][0], 16711935); 

	}

	format(small_string, sizeof(small_string), "%d", GetVehicleFuel(vehicleid));
	PlayerTextDrawSetString(playerid,car_params_td[playerid][5], small_string);

	hide_speedo(playerid);
	show_speedo(playerid, GetVehicleModel(vehicleid));
	return 1;
}