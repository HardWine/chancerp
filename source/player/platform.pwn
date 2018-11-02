#if defined player_platform_included
	#endinput
#endif

#define player_platform_included

forward Platform_OnPlayerConnect(playerid);
forward Platform_OnPlayerDisconnect(playerid, reason);

#define GPCI_ANDROID 					"42443231414852474A4953364736505754353538"

static const RakDroidGpci[7][41] = {
	"3952314F524834355456464955525858554F3353",
	"485149554757444F555856484E3139425A495345",
	"3343434B4D415A59474A505A50334A5048304D4B",
	"37584E55314659564E5050575758464A53513555",
	"37544E45315A4D565A3135344331564A5355484D",
	"3956314F52584735484A5A55554E314841305230",
	"42313745394255564239393838394A564F325432"
};

enum 
	Platfrom: {
		PLATFORM_NONE, // Отсутсвует 
		PLATFORM_ANDROID, // Android
		PLATFORM_RAKDROID, // RakDroid
		PLATFORM_PC // Компьютер
	};

new 
	Platfrom: player_platform[MAX_PLAYERS char];

public Platform_OnPlayerConnect(playerid) {
	new player_gpci[MAX_SIZE_GPCI + 1];

	gpci(playerid, player_gpci);

	if(strcmp(player_gpci, GPCI_ANDROID) == 0) {
		player_platform{playerid} = PLATFORM_ANDROID;
		return 1;
	} else {
		for(new i = 0; i < sizeof(RakDroidGpci); i++) {
			if(strcmp(Client[playerid], RakDroidGpci[i]) == 0) { 
				player_platform{playerid} = PLATFORM_RAKDROID;
				return 1;
			}
		}
	}
	player_platform{playerid} = PLATFORM_PC;
	return 1;
}

public Platform_OnPlayerDisconnect(playerid, reason) {
	player_platform{playerid} = PLATFORM_NONE;
	return 1;
}

stock Platfrom:SetPlayerPlatform(const playerid, const Platfrom: value) {
	return player_platform{playerid} = value;
}

stock Platfrom:GetPlayerPlatform(const playerid) {
	return player_platform{playerid};
}

