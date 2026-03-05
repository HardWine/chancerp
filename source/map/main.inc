#if defined _main_map_included
  #endinput
#endif
#define _main_map_included

#include <source/map/files/parking.inc>
#include <source/map/files/lspd_ext.inc>
#include <source/map/files/trucker_remobj.inc>
#include <source/map/files/lsspawn.inc>

stock LoadMapping() {
	create_object_parking();
	create_lspd_obj();
	create_truck_mapping();
	create_ls_spawn();

	

	return 1;
}

stock RemObject(playerid) {

	remove_building_parking(playerid);
	remove_lspd_obj(playerid);
	remove_trucker(playerid);
	remove_building_lsspawn(playerid);

	return 1;
}