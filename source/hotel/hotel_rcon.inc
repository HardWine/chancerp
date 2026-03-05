#if defined hotel_rcon_included
	#endinput
#endif

#define hotel_rcon_included

#include <YSI_Coding\y_hooks>

hook OnRconCommand(cmd[]) {
	if(strcmp(cmd, "Hotel.Help", false) == 0) {
		printf("Hotel.BuyHolelPlayer(arrayID, accID, name[]) -- установить номеру в отели владельца");
		printf("Hotel.SetNullOwner(arrayID) -- сбросить номеру в отели владельца");
		printf("Hotel.UpRentDay -- увеличить количество дней аренды на 1");
		printf("Hotel.Show(arrayID) -- отобразить информацию отеля");
		return Y_HOOKS_CONTINUE_RETURN_1;
	}

	new 
		command[32],
		params[32];

	if(!sscanf(cmd, "s[32]s[32]", command, params)) {
		if(strcmp(command, "Hotel.BuyHolelPlayer", false) == 0) {
			new 
				accID,
				arrayID,
				name[MAX_PLAYER_NAME];

			if(sscanf(params, "iis[24]", arrayID, accID, name) == 0) {
				printf("Hotel.BuyHolelPlayer(%i, %i, %s) = %i", arrayID, accID, name, Hotel.BuyHolelPlayer(arrayID, accID, name));
				return Y_HOOKS_CONTINUE_RETURN_1;
			}
		} else if(strcmp(command, "Hotel.Show", false) == 0) {
			new 
				arrayID;

			if(sscanf(params, "i", arrayID) == 0) {
				printf("Hotel.Show(%i) = %i", arrayID, Hotel.Show(arrayID));
				return Y_HOOKS_CONTINUE_RETURN_1;
			}
		} else if(strcmp(command, "Hotel.SetNullOwner", false) == 0) {
			new 
				arrayID;

			if(sscanf(params, "i", arrayID) == 0) {
				printf("Hotel.SetNullOwner(%i) = %i", arrayID, Hotel.SetNullOwner(arrayID));
				return Y_HOOKS_CONTINUE_RETURN_1;
			}
		} else if(strcmp(command, "Hotel.UpRentDay", false) == 0) {
			new 
				arrayID;

			if(sscanf(params, "i", arrayID) == 0) {
				printf("Hotel.UpRentDay(%i) = %i", arrayID, Hotel.UpRentDay(arrayID));
				return Y_HOOKS_CONTINUE_RETURN_1;
			}
		} else if(strcmp(command, "Hotel.DownRentDay", false) == 0) {
			new 
				arrayID;

			if(sscanf(params, "i", arrayID) == 0) {
				printf("Hotel.DownRentDay(%i) = %i", arrayID, Hotel.DownRentDay(arrayID));
				return Y_HOOKS_CONTINUE_RETURN_1;
			}
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}