#include <YSI_Coding\y_hooks>

// -----------------------------------------------------------------------------
#define AC_LOGO 				"[AC] "
#define AC_KICK_COLOR 			0xEB4949FF
#define AC_WARNING_COLOR 		0xFFEB4949

#define MAX_IP_CONS             5
#define MAX_TICK_WAIT           3850
#define MAX_VEHICLE_SPEED 		200

#define FREEZE_MAX_DIST     	2.5

new Float: SENSY_DIST_NO_SPEED = 3.25;
new Float: SENSY_DIST = 3.25;
new Float: SENSY_DIST_INCAR = 11.25;

// ---------------------------------- AC vars ----------------------------------
new AC_Timer[MAX_PLAYERS] 				= 0;
new m_bKickMessageSendsKick[MAX_PLAYERS] 	= false;
new m_bKickMessageSendsWarning[MAX_PLAYERS] 	= false;

new m_dwLegalTick[MAX_PLAYERS] 			= 0;
new AC_LegalMoment[MAX_PLAYERS] 		= 0;

new Float:fLastPointX[MAX_PLAYERS] 		= 0.0;
new Float:fLastPointY[MAX_PLAYERS] 		= 0.0;
new Float:fLastPointZ[MAX_PLAYERS] 		= 0.0;
new Float:fCurrentPointX[MAX_PLAYERS] 	= 0.0;
new Float:fCurrentPointY[MAX_PLAYERS] 	= 0.0;
new Float:fCurrentPointZ[MAX_PLAYERS] 	= 0.0;
new Float:fFreezePointX[MAX_PLAYERS] 	= 0.0;
new Float:fFreezePointY[MAX_PLAYERS] 	= 0.0;
new Float:fFreezePointZ[MAX_PLAYERS] 	= 0.0;

new m_bEnterVehicle[MAX_PLAYERS] = false;
new bAndroidPlayer[MAX_PLAYERS] = 0;

new pWeapon[MAX_PLAYERS][50];
new pFreeze[MAX_PLAYERS] = 0;

// ---------------------------------- forwards ---------------------------------
forward FindPedInZone(playerid, Float:x, Float:y, Float:z);
forward FindHimInPointAfter(playerid, Float:x, Float:y, Float:z, tick);
forward GetMaxWaitTick(playerid);
forward KickPlayerTimer(playerid);
forward KickPlayer(playerid, kickcode);

// ---------------------------------- AC forwards ------------------------------
forward AC_Reset(playerid);
forward AC_StartTimer(playerid);
forward AC_EndTimer(playerid);
forward AC_MainTimer(playerid);
forward AC_SetLegalMoment(playerid);
forward AC_UnsetLegalMoment(playerid);
forward AC_IsLegalMoment(playerid);
forward AC_ProcessCheckTeleport(playerid);
forward AC_SetLegalEnterVehicle(playerid);
forward AC_UnsetLegalEnterVehicle(playerid);
forward AC_IsLegalEnterVehicle(playerid);
forward AC_SetAndroidPlayer(playerid);
forward AC_SetPCPlayer(playerid);
forward AC_IsAndroidPlayer(playerid);
forward AC_CheckWeapon(playerid);
forward AC_ProcessInCarCheckTeleport(playerid);
forward AC_CheckAntiFreeze(playerid);
forward AC_SetFreezed(playerid);
forward AC_UnsetFreezed(playerid);
forward AC_CheckGodMode(playerid);

// ---------------------------------- special forwards -------------------------
forward PlayerDeviceCallback(playerid);
forward GetDistanceBetweenPoints( Float:x1, Float:y1, Float:x2, Float:y2);
forward AC_IsMoving(Float:x, Float:y);
forward AC_GetVehicleSpeed(vehicleid);
forward IsATrain(vehicleid);
forward IsAPlane(vehicleid);

// ---------------------------------- AC hook forwards -------------------------
forward TeleportTo(playerid, Float:x, Float:y, Float:z);
forward SetTextDrawSelecting(playerid, hovercolor);

// ---------------------------------- special add-on's -------------------------
public GetDistanceBetweenPoints( Float:x1, Float:y1, Float:x2, Float:y2)
{
    return floatround(floatsqroot( ( ( x1 - x2 ) * ( x1 - x2 ) ) + ( ( y1 - y2 ) * ( y1 - y2 ) ) ) );
}

public AC_IsMoving(Float:x, Float:y)
{
    if(x > 0.0 || x < 0.0 || y > 0.0 || y < 0.0)
		return 1;

	return 0;
}

public AC_GetVehicleSpeed(vehicleid)
{
    new Float:x, Float:y, Float:z;
    GetVehicleVelocity(vehicleid, x, y, z);
    return floatround(floatsqroot(x*x+y*y+z*z)*100);
}

public IsATrain(vehicleid)
{
    switch(GetVehicleModel(vehicleid))
    {
        case 449, 537, 538, 569, 570, 590: return 1;
    }
    
    return 0;
}

public IsAPlane(vehicleid)
{
    switch(GetVehicleModel(vehicleid))
    {
        case 460, 464, 476, 511, 512, 513, 519, 520, 553, 577, 592, 593: return 1;
    }
    
    return 0;
}

// CALLBACK's
public PlayerDeviceCallback(playerid)
{
    if(GetPlayerAnimationIndex(playerid) == 0)
    	AC_SetAndroidPlayer(playerid);
	else
 		AC_SetPCPlayer(playerid);
}

// -------------------------------------------- ac start -----------------------

// ANDROID STUFF
public AC_SetAndroidPlayer(playerid)
{
    bAndroidPlayer[playerid] = 1;
}

public AC_SetPCPlayer(playerid)
{
    bAndroidPlayer[playerid] = 0;
}

public AC_IsAndroidPlayer(playerid)
{
	return bAndroidPlayer[playerid];
}

// ---------------------------------- TASK MANAGER -----------------------------
public AC_MainTimer(playerid)
{
	if(!AC_Timer[playerid]) return 0;
	PlayerDeviceCallback(playerid);
	// if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING || GetPlayerAdminLevel(playerid) >= 1 || AC_IsAndroidPlayer(playerid)) return 0;
	// if(IsPlayerInAnyVehicle(playerid) && (GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER))
	// {
	//     // incar
	//     if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
	// 		AC_ProcessInCarCheckTeleport(playerid);
	// }
	// else
	// {
	//     // onfoot
	//     if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
	//     	AC_ProcessCheckTeleport(playerid);
	    
	//     AC_CheckWeapon(playerid);
	// }
	
	// // --------------------------- ALL FRAMES ----------------------------------
	// AC_CheckAntiFreeze(playerid);
	// AC_CheckGodMode(playerid);

	return 1;
}

public AC_CheckGodMode(playerid)
{
    if(!IsPlayerInAnyVehicle(playerid))
    {
        new Float:ped_health;
        GetPlayerHealth(playerid, ped_health);
        
		if(ped_health > 176.0)
		{
			SetPlayerHealth(playerid, 100.0);
			
			return KickPlayer(playerid, 12);
		}
    }
    else
    {
    	new Float:veh_health;
    	GetVehicleHealth(GetPlayerVehicleID(playerid), veh_health);
    
        if(veh_health > 1076.0)
        {
            SetVehicleHealth(GetPlayerVehicleID(playerid), 1000.0);
            
			return KickPlayer(playerid, 13);
		}
	}
	
	return 1;
}

public AC_CheckAntiFreeze(playerid)
{
    new Float:velX = 0.0;
	new Float:velY = 0.0;
	new Float:velZ = 0.0;

	// save velocity
	if(!IsPlayerInAnyVehicle(playerid))
		GetPlayerVelocity(playerid, velX, velY, velZ);
	else
	    GetVehicleVelocity(GetPlayerVehicleID(playerid), velX, velY, velZ);

	if(	pFreeze[playerid] &&
		AC_IsMoving(velX, velY) &&
		GetDistanceBetweenPoints(fFreezePointX[playerid], fFreezePointY[playerid], fCurrentPointX[playerid], fCurrentPointY[playerid]) > FREEZE_MAX_DIST )
	{
	    // anti moving in freeze
	    TeleportTo(playerid, fFreezePointX[playerid], fFreezePointY[playerid], fCurrentPointZ[playerid]);
	}
	else if( pFreeze[playerid] &&
	 		 !AC_IsMoving(velX, velY) &&
			 GetDistanceBetweenPoints(fFreezePointX[playerid], fFreezePointY[playerid], fCurrentPointX[playerid], fCurrentPointY[playerid]) > FREEZE_MAX_DIST )
	{
	    // anti teleport in freeze
	    if(!AC_IsLegalMoment(playerid))
	    {
   			if(IsPlayerInAnyVehicle(playerid))
			    return KickPlayer(playerid, 6);
			else
   				return KickPlayer(playerid, 3);
		}
	}
	    
	return 1;
}

public AC_SetFreezed(playerid)
{
    if(playerid < 0 || playerid > MAX_PLAYERS)
	    return 0;
	    
    fFreezePointX[playerid] = fCurrentPointX[playerid];
	fFreezePointY[playerid] = fCurrentPointY[playerid];
	fFreezePointZ[playerid] = fCurrentPointZ[playerid];
	
	pFreeze[playerid] = 1;
	
	return 1;
}

public AC_UnsetFreezed(playerid)
{
    if(playerid < 0 || playerid > MAX_PLAYERS)
	    return 0;
	    
	pFreeze[playerid] = 0;
	
	return 1;
}

public AC_StartTimer(playerid)
{
	if(playerid < 0 || playerid > MAX_PLAYERS)
	    return 0;

	AC_Reset(playerid);
	AC_Timer[playerid] = SetTimerEx("AC_MainTimer", 0, 1, "%d", playerid);
	
	return 1;
}

public AC_EndTimer(playerid)
{
    if(playerid < 0 || playerid > MAX_PLAYERS)
	    return 0;

	KillTimer(AC_Timer[playerid]);
	AC_Timer[playerid] = 0;
	
	return 1;
}

// ---------------------------------- LEGALITY ---------------------------------
public AC_SetLegalMoment(playerid)
{
    m_dwLegalTick[playerid] = GetTickCount();
    AC_LegalMoment[playerid] = true;
}

public AC_UnsetLegalMoment(playerid)
{
    AC_LegalMoment[playerid] = false;
}

public AC_IsLegalMoment(playerid)
{
	return AC_LegalMoment[playerid];
}

// ---------------------------------- addvit func's ----------------------------
public GetMaxWaitTick(playerid)
{
	new x = ( (GetPlayerPing(playerid) * 10) - (1 / GetPlayerPing(playerid)) );
	
	return (MAX_TICK_WAIT + x);
}

public FindPedInZone(playerid, Float:x, Float:y, Float:z)
{
    if(!IsPlayerInRangeOfPoint(playerid, 30, x,y,z))
		return KickPlayer(playerid, 3);
		
	return 1;
}

// ---------------------------------- weapon process ---------------------------
public AC_CheckWeapon(playerid)
{
    if(GetTickCount() - m_dwLegalTick[playerid] < GetMaxWaitTick(playerid) && AC_LegalMoment[playerid])
	return 1;
	
	new iWeapon = GetPlayerWeapon(playerid);

	if(iWeapon > 0 && iWeapon <= 47)
	{
		if(pWeapon[playerid][iWeapon] == 0)
		return KickPlayer(playerid, 5);
	}

	return 1;
}

// ---------------------------------- hooks ------------------------------------
public TeleportTo(playerid, Float:x, Float:y, Float:z)
{
    if(playerid < 0 || playerid > MAX_PLAYERS)
	    return 0;
	    
	AC_SetLegalMoment(playerid);

	if(!IsPlayerInAnyVehicle(playerid))
		SetPlayerPos(playerid, x, y, z);
	else
	    SetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
	
    SetTimerEx("FindPedInZone", (1500 + (GetPlayerPing(playerid) * 10) - (1 / GetPlayerPing(playerid))), 0, "%d%f%f%f", playerid, x,y,z);
	
	return 1;
}

public SetTextDrawSelecting(playerid, hovercolor)
{
	SelectTextDraw(playerid, hovercolor);
	AC_SetFreezed(playerid);
	    
	return 1;
}

// ---------------------------------- teleport process (on foot) ---------------
public AC_ProcessCheckTeleport(playerid)
{
    // update device
	PlayerDeviceCallback(playerid);
	
	new Float:velX;
	new Float:velY;
	new Float:velZ;
	
	// save velocity
	GetPlayerVelocity(playerid, velX, velY, velZ);
	
	// legal tick's
	if(GetTickCount() - m_dwLegalTick[playerid] < GetMaxWaitTick(playerid) && AC_LegalMoment[playerid])
		return 1;
	
	// check max speed on foot
	if( velX > 0.55 || velY > 0.55 ||
		velX < -0.95 || velY < -0.95)
	{
	    return KickPlayer(playerid, 1);
	}
	
	// save current position
	GetPlayerPos(playerid, fCurrentPointX[playerid], fCurrentPointY[playerid], fCurrentPointZ[playerid]);

	// check TP without speed
	if(!AC_IsMoving(velX, velY) && !AC_LegalMoment[playerid])
	{
	    // MAX distance
	    if(GetDistanceBetweenPoints(fCurrentPointX[playerid], fCurrentPointY[playerid], fLastPointX[playerid], fLastPointY[playerid]) > SENSY_DIST_NO_SPEED)
	    	return KickPlayer(playerid, 2);
	}
	
	// check TP with speed
	if(	AC_IsMoving(velX, velY) &&
		GetDistanceBetweenPoints(fCurrentPointX[playerid], fCurrentPointY[playerid], fLastPointX[playerid], fLastPointY[playerid]) > SENSY_DIST &&
		(!AC_LegalMoment[playerid] && GetTickCount() - m_dwLegalTick[playerid] > GetMaxWaitTick(playerid)))
	{
		return KickPlayer(playerid, 3);
	}

	// save last data
 	fLastPointX[playerid] = fCurrentPointX[playerid];
  	fLastPointY[playerid] = fCurrentPointY[playerid];
   	fLastPointZ[playerid] = fCurrentPointZ[playerid];
	AC_UnsetLegalMoment(playerid);
	
	return 1;
}

// ---------------------------------- teleport (in car) ------------------------
public AC_ProcessInCarCheckTeleport(playerid)
{
	new Float:velX;
	new Float:velY;
	new Float:velZ;

    new VehicleID = 65535;
	VehicleID = GetPlayerVehicleID(playerid);
	
	if(VehicleID <= 0 || VehicleID > MAX_VEHICLES)
		return KickPlayer(playerid, 9);

	// check speedhack
	if(AC_GetVehicleSpeed(VehicleID) >= MAX_VEHICLE_SPEED && !IsATrain(VehicleID) && !IsAPlane(VehicleID))
		return KickPlayer(playerid, 7);
	
	// save velocity
	GetVehicleVelocity(VehicleID, velX, velY, velZ);
	
	// legal tick's
	if(GetTickCount() - m_dwLegalTick[playerid] < GetMaxWaitTick(playerid) && AC_LegalMoment[playerid])
 		return 1;

	// save current position
	GetVehiclePos(VehicleID, fCurrentPointX[playerid], fCurrentPointY[playerid], fCurrentPointZ[playerid]);

	// check TP without speed
	if( !AC_IsMoving(velX, velY) && !AC_LegalMoment[playerid] && !IsATrain(VehicleID))
	{
	    // MAX distance
	    if(GetDistanceBetweenPoints(fCurrentPointX[playerid], fCurrentPointY[playerid], fLastPointX[playerid], fLastPointY[playerid]) > SENSY_DIST_NO_SPEED)
	    	return KickPlayer(playerid, 6);
	}

    // check TP with speed
	if(AC_IsMoving(velX, velY) && !AC_LegalMoment[playerid] && !IsATrain(VehicleID))
	{
	    if(GetDistanceBetweenPoints(fCurrentPointX[playerid], fCurrentPointY[playerid], fLastPointX[playerid], fLastPointY[playerid]) > SENSY_DIST_INCAR)
	        return KickPlayer(playerid, 6);
	}

	fLastPointX[playerid] = fCurrentPointX[playerid];
 	fLastPointY[playerid] = fCurrentPointY[playerid];
 	fLastPointZ[playerid] = fCurrentPointZ[playerid];
	AC_UnsetLegalMoment(playerid);

	return 1;
}

public AC_SetLegalEnterVehicle(playerid)
{
    m_bEnterVehicle[playerid] = true;
}

public AC_UnsetLegalEnterVehicle(playerid)
{
    m_bEnterVehicle[playerid] = false;
}

public AC_IsLegalEnterVehicle(playerid)
{
    return m_bEnterVehicle[playerid];
}

public AC_Reset(playerid)
{
    fLastPointX[playerid] = 0.0;
    fLastPointY[playerid] = 0.0;
    fLastPointZ[playerid] = 0.0;
    fCurrentPointX[playerid] = 0.0;
    fCurrentPointY[playerid] = 0.0;
    fCurrentPointZ[playerid] = 0.0;
    fFreezePointX[playerid] = 0.0;
    fFreezePointY[playerid] = 0.0;
   	fFreezePointZ[playerid] = 0.0;
    
    AC_UnsetLegalEnterVehicle(playerid);
    AC_UnsetFreezed(playerid);
    
    AC_LegalMoment[playerid] = false;
    m_dwLegalTick[playerid] = GetTickCount();
    
    if(AC_Timer[playerid])
   		AC_EndTimer(AC_Timer[playerid]);
}

public KickPlayerTimer(playerid)
{
    m_bKickMessageSendsWarning[playerid] = false;
}

new KickPlayerT[MAX_PLAYERS][14];

public KickPlayer(playerid, kickcode)
{
    AC_UnsetLegalMoment(playerid);
    
    if(KickPlayerT[playerid][kickcode] > gettime()) return 1;
    KickPlayerT[playerid][kickcode] = gettime() + 10;
    if(kickcode == 1 || kickcode == 4 || kickcode == 5 || kickcode == 10 || kickcode == 11 || kickcode == 12 || kickcode == 13)
    {
	    if(!m_bKickMessageSendsKick[playerid])
	    {
	        if(kickcode == 1)
	        {
	            SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #1 > OnFoot: Fly / Surf / Slapper)");
	            format(small_string, sizeof(small_string), "[A] %s(%i) был кикнут. (code #1 > OnFoot: Fly / Surf / Slapper)", PlayerInfo[playerid][pName], playerid);
	        }

	        if(kickcode == 4)
	        {
	            SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #4 > OnFoot: Teleport in car)");
	            format(small_string, sizeof(small_string), "[A] %s(%i) был кикнут. (code #4 > OnFoot: Teleport in car)", PlayerInfo[playerid][pName], playerid);
	        }
	            
	        if(kickcode == 5)
	        {
	            SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #5 > OnFoot: Weapon Hack)");
	            format(small_string, sizeof(small_string), "[A] %s(%i) был кикнут. (code #5 > OnFoot: Weapon Hack)", PlayerInfo[playerid][pName], playerid);
	        }
	            
			if(kickcode == 10)
			{
	            SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #10 > AntiFreeze)");
	            format(small_string, sizeof(small_string), "[A] %s(%i) был кикнут. (code #10 > AntiFreeze)", PlayerInfo[playerid][pName], playerid);
			}
	            
	        if(kickcode == 11)
	        {
	            SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #11 > Damager)");
	            format(small_string, sizeof(small_string), "[A] %s(%i) был кикнут. (code #11 > Damager)", PlayerInfo[playerid][pName], playerid);
	        }
	            
	        if(kickcode == 12)
	        {
	            SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #12 > OnFoot: Health Hack)");
	            format(small_string, sizeof(small_string), "[A] %s(%i) был кикнут. (code #12 > OnFoot: Health Hack)", PlayerInfo[playerid][pName], playerid);
	        }
	            
	        if(kickcode == 13)
	        {
	            SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #13 > InCar: Health Hack)");
	            format(small_string, sizeof(small_string), "[A] %s(%i) был кикнут. (code #13 > InCar: Health Hack)", PlayerInfo[playerid][pName], playerid);
	        }
	        Kick(playerid);
	   		SetPlayerVirtualWorld(playerid, random(784));
	    	m_bKickMessageSendsKick[playerid] = true;
	    	SendAdminMessageAC(-1, small_string);
	    }
	    return 1;
    }
    else 
    {
	    if(!m_bKickMessageSendsWarning[playerid])
	    {
	       	if(kickcode == 2)
	       	{
	       		AddPlayerCheaterPanel(playerid);
	            // SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #2 > OnFoot: Teleport / AirBreak)");
	            // format(small_string, sizeof(small_string), "[A] %s(%i) (code #2 > OnFoot: Teleport / AirBreak)", PlayerInfo[playerid][pName], playerid);
	       	}
	          
	        if(kickcode == 3)
	        {
	        	AddPlayerCheaterPanel(playerid);
	            // SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #3 > OnFoot: Teleport / AirBreak)");
	            // format(small_string, sizeof(small_string), "[A] %s(%i) (code #3 > OnFoot: Teleport / AirBreak)", PlayerInfo[playerid][pName], playerid);
	        }
	            
	        if(kickcode == 6)
	        {
	        	AddPlayerCheaterPanel(playerid);
	            // SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #6 > InCar: Teleport / AirBreak)");
	            // format(small_string, sizeof(small_string), "[A] %s(%i) (code #6 > InCar: Teleport / AirBreak)", PlayerInfo[playerid][pName], playerid);
	        }
	            
	  		if(kickcode == 7)
	  		{
	  			AddPlayerCheaterPanel(playerid);
	            // SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #7 > InCar: SpeedHack / CarShot)");
	            // format(small_string, sizeof(small_string), "[A] %s(%i) (code #7 > InCar: SpeedHack / CarShot)", PlayerInfo[playerid][pName], playerid);
	  		}
	            
	        if(kickcode == 8)
	        {
	        	AddPlayerCheaterPanel(playerid);
	            // SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #8 > Bot flood)");
	            // format(small_string, sizeof(small_string), "[A] %s(%i) (code #8 > Bot flood)", PlayerInfo[playerid][pName], playerid);
	        }
	            
	        if(kickcode == 9)
	        {
	        	AddPlayerCheaterPanel(playerid);
	            // SendClientMessage(playerid, AC_KICK_COLOR, AC_LOGO "¬ы были кикнуты по подозрению в читерстве! (code #9 > Invisible)");
	            // format(small_string, sizeof(small_string), "[A] %s(%i) (code #9 > Invisible)", PlayerInfo[playerid][pName], playerid);
	        }
	        // SendAdminMessageAC(-1, small_string);   
	    	m_bKickMessageSendsWarning[playerid] = true;
	    }
	   	return SetTimerEx("KickPlayerTimer", 10_000, 0, "%d", playerid);
    }
}

// -------------------------------------------- ac end -------------------------
forward CheckMaxIpConnections(playerid);
public CheckMaxIpConnections(playerid)
{
   	new plrIP[16];
	new remplrIP[16];
    new i;
    new iMaxCons = 0;

    GetPlayerIp(playerid, plrIP, sizeof(plrIP));

    foreach(new i: Player)
    {
        GetPlayerIp(i, remplrIP, sizeof(remplrIP));

        if(strcmp(remplrIP, plrIP) == 0)
            iMaxCons++;
    }

    if(iMaxCons >= MAX_IP_CONS)
	{
        foreach(new i: Player)
    	{
  	 		GetPlayerIp(i, remplrIP, sizeof(remplrIP));

        	if(strcmp(remplrIP, plrIP) == 0)
        	    Ban(i);
    	}

    	Ban(playerid);
    }
}


hook OnPlayerRequestClass(playerid, classid)
{
	TogglePlayerControllable(playerid, true);
	ResetPlayerWeapons(playerid);
	return 1;
}

hook OnPlayerAuthorization(playerid)
{
    AC_StartTimer(playerid);
    
    // roflan
    // CheckMaxIpConnections(playerid);
    
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
   	AC_EndTimer(playerid);
    
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    TogglePlayerControllable(playerid, true);
	ResetPlayerWeapons(playerid);
	AC_SetLegalMoment(playerid);
	return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    AC_SetLegalEnterVehicle(playerid);
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_ONFOOT)
	    AC_SetLegalMoment(playerid); // it's not teleport, just ped leave car
	
	// check teleport from foot in car without RPC: EnterVehicle
	if(	 oldstate == PLAYER_STATE_ONFOOT &&
		(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER))
	{
	    if(AC_IsLegalEnterVehicle(playerid))
	    {
	        // all we okay
        	AC_UnsetLegalEnterVehicle(playerid);
		}
		else
		{
		    // not okay
		    KickPlayer(playerid, 4);
		}
	}
	
	    
	return 1;
}

hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(playerid < 0 || playerid > MAX_PLAYERS)
	    return 0;
	    
	if(weaponid >= 47 || weaponid < 22)
	    return 0;
	    
    if(!pWeapon[playerid][weaponid] && weaponid != GetPlayerWeapon(playerid))
	{
	    // anti-damager
		KickPlayer(playerid, 11);
		return 0;
	}

    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    AC_UnsetFreezed(playerid);
    
    // -------------------------------------------------------------------------
    // YOUR CODE HERE

	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	AC_UnsetFreezed(playerid);
	
	// ------------------------------------
	// YOUR CODE HERE!
}

// ALS FUNCTION
stock RM_GivePlayerWeapon(playerid, weaponid, ammo)
{
    if(playerid < 0 || playerid > MAX_PLAYERS)
	    return 0;
	    
    pWeapon[playerid][weaponid] = 1;
    AC_SetLegalMoment(playerid);
	return GivePlayerWeapon(playerid, weaponid, ammo);
}
#if defined _ALS_GivePlayerWeapon
	#undef GivePlayerWeapon
#else
	#define _ALS_GivePlayerWeapon
#endif

#define GivePlayerWeapon RM_GivePlayerWeapon


stock RM_PutPlayerInVehicle(playerid, vehicleid, seatid)
{
	AC_SetLegalEnterVehicle(playerid);
	return PutPlayerInVehicle(playerid, vehicleid, seatid);
}
#if defined _ALS_PutPlayerInVehicle
	#undef PutPlayerInVehicle
#else
	#define _ALS_PutPlayerInVehicle
#endif

#define PutPlayerInVehicle RM_PutPlayerInVehicle

stock RM_SetPlayerPos(playerid, Float: x, Float: y, Float: z)
{
    if(playerid < 0 || playerid > MAX_PLAYERS)
	    return 0;
	    
	AC_SetLegalMoment(playerid);

    SetTimerEx("FindPedInZone", (1500 + (GetPlayerPing(playerid) * 10) - (1 / GetPlayerPing(playerid))), 0, "%d%f%f%f", playerid, x,y,z);

	return SetPlayerPos(playerid, x, y, z);
}
#if defined _ALS_SetPlayerPos
	#undef SetPlayerPos
#else
	#define _ALS_SetPlayerPos
#endif

#define SetPlayerPos RM_SetPlayerPos

stock RM_TogglePlayerControllable(playerid, toggle)
{
    if(playerid < 0 || playerid > MAX_PLAYERS)
	    return 0;
	    
	if(!toggle)
		AC_SetFreezed(playerid);
	else
	    AC_UnsetFreezed(playerid);

	return TogglePlayerControllable(playerid, toggle);
}
#if defined _ALS_TogglePlayerControllable
	#undef TogglePlayerControllable
#else
	#define _ALS_TogglePlayerControllable
#endif

#define TogglePlayerControllable RM_TogglePlayerControllable

stock RM_ResetPlayerWeapons(playerid)
{
    if(playerid < 0 || playerid > MAX_PLAYERS)
	    return 0;
	    
	new i;
	for (i = 0; i < 50; i++)
	{
	    pWeapon[playerid][i] = 0;
	}
	AC_SetLegalMoment(playerid);
	return ResetPlayerWeapons(playerid);
}
#if defined _ALS_ResetPlayerWeapons
	#undef ResetPlayerWeapons
#else
	#define _ALS_ResetPlayerWeapons
#endif

#define ResetPlayerWeapons RM_ResetPlayerWeapons

stock RM_ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[])
{
	if(dialogid == -1 || dialogid == 65535)
		return AC_UnsetFreezed(playerid);
		
	if(playerid < 0 || playerid > MAX_PLAYERS)
	    return 0;
	    
	if(style < 0 || style > 5)
	    return 0;
	
	AC_SetFreezed(playerid);

	return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}
#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif

#define ShowPlayerDialog RM_ShowPlayerDialog


CMD:device(playerid, params[])
{
    if(sscanf(params,"d", params[0]))
    	return SendClientMessage(playerid, 0xCC0000FF, "/device <playerid>");
    	
	if(IsPlayerConnected(params[0]))
	{
	    if(AC_IsAndroidPlayer(params[0]))
	        return SendClientMessage(playerid, 0xCC0000FF, "Player device: Android");
		else
            return SendClientMessage(playerid, 0xCC0000FF, "Player device: PC");
	}
	
	SendClientMessage(playerid, 0xCC0000FF, "Player is not online!");
    	
	return 1;
}






