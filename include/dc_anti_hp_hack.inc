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

new bool: check_hp = true;

stock CheckHp() {
	return check_hp = false;
}

public OnPlayerUpdate(playerid)
{
	if(check_hp == true)
	{
		new Float:health;
		GetPlayerHealth(playerid, health);
		if(_:ac_hp__health[playerid] != _:health)
		{
			if((ac_hp__health[playerid] > health)
			&& (GetTickCount() > ac_hp__ignore_tick[playerid]))
			{
				ac_hp__health[playerid] = health;
			}
			else if(ac_hp__health[playerid] < health)
			{
				SetPlayerHealth(playerid, ac_hp__health[playerid]);
			}
		}
	}
#if	defined	ac_hp__OnPlayerUpdate
	ac_hp__OnPlayerUpdate(playerid);
#endif
	return 1;
}
#if	defined	_ALS_OnPlayerUpdate
	#undef	OnPlayerUpdate
#else
	#define	_ALS_OnPlayerUpdate
#endif
#define	OnPlayerUpdate	ac_hp__OnPlayerUpdate
#if	defined	ac_hp__OnPlayerUpdate
forward ac_hp__OnPlayerUpdate(playerid);
#endif

public OnPlayerSpawn(playerid)
{
	ac_hp__ignore_tick[playerid] = GetTickCount()+AC_HP__IGNORE_TIME;
	ac_hp__health[playerid] = 100.0;
#if	defined	ac_hp__OnPlayerSpawn
	ac_hp__OnPlayerSpawn(playerid);
#endif
	return 1;
}
#if	defined	_ALS_OnPlayerSpawn
	#undef	OnPlayerSpawn
#else
	#define	_ALS_OnPlayerSpawn
#endif
#define	OnPlayerSpawn	ac_hp__OnPlayerSpawn
#if	defined	ac_hp__OnPlayerSpawn
forward ac_hp__OnPlayerSpawn(playerid);
#endif


stock ac_hp__SetPlayerHealth(playerid, Float:health)
{
	ac_hp__ignore_tick[playerid] = GetTickCount()+AC_HP__IGNORE_TIME;
	ac_hp__health[playerid] = health;
	return SetPlayerHealth(playerid, health);
}
#if	defined	_ALS_SetPlayerHealth
	#undef	SetPlayerHealth
#else
	#define	_ALS_SetPlayerHealth
#endif
#define SetPlayerHealth ac_hp__SetPlayerHealth

stock ac_hp__GetPlayerHealth(playerid, &Float:health)
{
	health = ac_hp__health[playerid];
	return 1;
}
#if	defined	_ALS_GetPlayerHealth
	#undef	GetPlayerHealth
#else
	#define	_ALS_GetPlayerHealth
#endif
#define GetPlayerHealth ac_hp__GetPlayerHealth