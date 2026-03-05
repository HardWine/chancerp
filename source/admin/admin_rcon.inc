#if defined admin_rcon_included
	#endinput
#endif

#define admin_rcon_included

#include <YSI-Include\YSI\YSI\y_hooks>

hook OnRconCommand(cmd[]) {
	new 
		command[32],
		params[32];

	if(!sscanf(cmd, "s[32]s[32]", command, params)) {
		if(strcmp(command, "Admin.GetPlayerLevel", false) == 0) {
			new 
				accID;

			if(!sscanf(params, "i", accID)) {
				return printf("Admin.GetPlayerLevel (%i) = %i", accID, Admin.GetPlayerLevel(accID));
			}
		} else if(strcmp(command, "Admin.UpCountMute", false) == 0) {
			new 
				accID;

			if(!sscanf(params, "i", accID)) {
				return printf("Admin.UpCountMute (%i) = %i", accID, Admin.UpCountMute(accID));
			}
		} else if(strcmp(command, "Admin.OnPlayerConnect", false) == 0) {
			new 
				accID;

			if(!sscanf(params, "i", accID)) {
				return printf("OnPlayerConnect (%i) = %i", accID, OnPlayerConnect(accID));
			}
		}
	}
}