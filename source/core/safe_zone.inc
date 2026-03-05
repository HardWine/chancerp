#if defined greenzone_system_included
	#endinput
#endif

#define greenzone_system_included

stock IsPlayerInSafeZone(playerid) {
	if(IsPlayerInDynamicArea(playerid, safe_zone[0]) || IsPlayerInDynamicArea(playerid, safe_zone[1]) ||
	IsPlayerInDynamicArea(playerid, safe_zone[2]) || IsPlayerInDynamicArea(playerid, safe_zone[3]) ||
	IsPlayerInDynamicArea(playerid, safe_zone[4]) || IsPlayerInDynamicArea(playerid, safe_zone[5]) ||
	IsPlayerInDynamicArea(playerid, safe_zone[6]) || IsPlayerInDynamicArea(playerid, safe_zone[7]) ||
	IsPlayerInDynamicArea(playerid, safe_zone[8]) || IsPlayerInDynamicArea(playerid, safe_zone[9])) {
		return 1;
	}
	return 0;
}

stock Safe_OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if((newkeys & KEY_FIRE) || ((newkeys & KEY_HANDBRAKE) && (oldkeys & KEY_HANDBRAKE) && (newkeys & KEY_SECONDARY_ATTACK)))
	{
		if(IsPlayerInAnyVehicle(playerid)) return 1;
		if(GetPlayerAdminLevel(playerid) != 0) return 1;
		if(IsPlayerInSafeZone(playerid) == 1) {
			new try = GetPVarInt(playerid, "safe_no");
			try++;
			if(try > 5) { Kick(playerid); }
			SetPVarInt(playerid, "safe_no", try);
			if(try < 3) return 1;
			SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Безопасная зона",
			 "{FFFFFF}В данной игровой зоне запрещено наносить урон другим игрокам.\n"COLOR_RED"Повторные попытки приведут к отключению от сервера!"
			 , "ОК", "Закрыть");
			return 1;
		}
	}
    return 1;

}