/*=============================================================================
		Health Anticheat
			by Daniel_Cortez

		www.pro-pawn.ru

Copyright (c) 2014 Daniel_Cortez
This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the
use of this software. Permission is granted to anyone to use this software for
any purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:
    1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software in
		a product, an acknowledgment in the product documentation would be
		appreciated but is not required.
    2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.
=============================================================================*/


static Float:ac_hp__health[MAX_PLAYERS];
static ac_hp__ignore_tick[MAX_PLAYERS];

#if	!defined	AC_HP__IGNORE_TIME
	#define	AC_HP__IGNORE_TIME	1000
#endif


public OnPlayerUpdate(playerid)
{
	{
		new Float:health;
		GetPlayerArmour(playerid, health);
		if(_:ac_hp__health[playerid] != _:health)
		{
			if((ac_hp__health[playerid] > health)
			&& (GetTickCount() > ac_hp__ignore_tick[playerid]))
			{
				ac_hp__health[playerid] = health;
			}
			else if(ac_hp__health[playerid] < health)
			{
				SetPlayerArmour(playerid, ac_hp__health[playerid]);
			}
		}
	}
#if	defined	ac_ar__OnPlayerUpdate
	ac_ar__OnPlayerUpdate(playerid);
#endif
	return 1;
}
#if	defined	_ALS_OnPlayerUpdate
	#undef	OnPlayerUpdate
#else
	#define	_ALS_OnPlayerUpdate
#endif
#define	OnPlayerUpdate	ac_ar__OnPlayerUpdate
#if	defined	ac_ar__OnPlayerUpdate
forward ac_ar__OnPlayerUpdate(playerid);
#endif

public OnPlayerSpawn(playerid)
{
	ac_hp__ignore_tick[playerid] = GetTickCount()+AC_HP__IGNORE_TIME;
	ac_hp__health[playerid] = 100.0;
#if	defined	ac_ar__OnPlayerSpawn
	ac_ar__OnPlayerSpawn(playerid);
#endif
	return 1;
}
#if	defined	_ALS_OnPlayerSpawn
	#undef	OnPlayerSpawn
#else
	#define	_ALS_OnPlayerSpawn
#endif
#define	OnPlayerSpawn	ac_ar__OnPlayerSpawn
#if	defined	ac_ar__OnPlayerSpawn
forward ac_ar__OnPlayerSpawn(playerid);
#endif


stock ac_ar__SetPlayerArmour(playerid, Float:armour)
{
	ac_hp__ignore_tick[playerid] = GetTickCount()+AC_HP__IGNORE_TIME;
	ac_hp__health[playerid] = armour;
	return SetPlayerArmour(playerid, armour);
}
#if	defined	_ALS_SetPlayerArmour
	#undef	SetPlayerArmour
#else
	#define	_ALS_SetPlayerArmour
#endif
#define SetPlayerArmour ac_ar__SetPlayerArmour

stock ac_ar__GetPlayerArmour(playerid, &Float:armour)
{
	armour = ac_hp__health[playerid];
	return 1;
}
#if	defined	_ALS_GetPlayerArmour
	#undef	GetPlayerArmour
#else
	#define	_ALS_GetPlayerArmour
#endif
#define GetPlayerArmour ac_ar__GetPlayerArmour