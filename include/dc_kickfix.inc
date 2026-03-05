/*==============================================================================
		Delayed Kick for SA:MP v1.3.1
			by Daniel_Cortez

This include replaces Kick, Ban and BanEx functions with its own versions
that call original functions with a 0.5-second delay.
You can set the delay time by defining DC_KICKFIX_INTERVAL macro
before the #include line.


Copyright (c) 2014-2017 Stanislav Gromov (Daniel_Cortez)

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the
use of this software.

Permission is granted to anyone to use this software for
any purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1.	The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software in
	a product, an acknowledgment in the product documentation would be
	appreciated but is not required.

2.	Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.

3.	This notice may not be removed or altered from any source distribution.
==============================================================================*/


#if defined DC__KICKFIX_INC
	#endinput
#endif
#define	DC__KICKFIX_INC


#include <a_samp>

#if	!defined	DC_KICKFIX_INTERVAL
	#define		DC_KICKFIX_INTERVAL	2000
#endif


// Define this string once, so there won't be multiple copies of it.
static const str__dc_kickfix__d[] = !"d";

// This string can't be constant because the "varname" parameter
// in SetPVarString is declared without the "const" qualifier.
// Blame Kalcor for that.
// Interestingly though, the "name" parameter in GetPlayerName
// is defined as "const name[]" for some ******g reason
// so the function can write data to constant arrays.
static str__dc_kickfix__reason[] = !"dc_kickfix__reason";


@__dc_kickfix_sysreq_Workaround();
@__dc_kickfix_sysreq_Workaround()
{
	#emit retn
	// The stock compiler crashes because of using sysreq.c on a native function
	// that was never used before (see dc_kickfix__BanEx) so let's use it here.
	SetPVarString(0, str__dc_kickfix__reason, str__dc_kickfix__reason);
	return 1;
}


// Delayed kick function for calling via SetTimerEx.
@__dc_kickfix__DoKick(const playerid);
@__dc_kickfix__DoKick(const playerid)
	return Kick(playerid);

// Reserve ImmediateKick for a normal kick without a delay.
native ImmediateKick(playerid) = Kick;

// Kick hook.
stock dc_kickfix__Kick(playerid)
{
	SetPVarInt(playerid, "kicked", 1);
	if(0 == IsPlayerConnected(playerid))
		return 0;
	SetTimerEx(
		!"@__dc_kickfix__DoKick", DC_KICKFIX_INTERVAL, false,
		str__dc_kickfix__d, playerid
	);
	return 1;
}
#if defined _ALS_Kick
	#undef Kick
#else
	#define _ALS_Kick
#endif
#define	Kick(%0)	dc_kickfix__Kick(%0)


// Delayed ban function for calling via SetTimerEx.
@__dc_kickfix__DoBan(const playerid);
@__dc_kickfix__DoBan(const playerid)
	return Ban(playerid);

// Reserve ImmediateBan for a normal ban without a delay.
native ImmediateBan(playerid) = Ban;

// Ban hook.
stock dc_kickfix__Ban(playerid)
{
	if(0 == IsPlayerConnected(playerid))
		return 0;
	SetTimerEx(
		!"@__dc_kickfix__DoBan", DC_KICKFIX_INTERVAL, false,
		str__dc_kickfix__d, playerid
	);
	return 1;
}
#if defined _ALS_Ban
	#undef Ban
#else
	#define _ALS_Ban
#endif
#define	Ban(%0)	dc_kickfix__Ban(%0)


// Delayed ban (extended) function for calling via SetTimerEx.
@__dc_kickfix__DoBanEx(const playerid);
@__dc_kickfix__DoBanEx(const playerid)
{
	goto skip_array_init;
	new reason[128];
skip_array_init:
	GetPVarString(playerid, str__dc_kickfix__reason, reason, sizeof(reason));
	DeletePVar(playerid, str__dc_kickfix__reason);
	// If a character code is more than 127, GetPVarString & GetSVarString
	// set bytes 1-3 to 0xFF, e.g. instead of 0x000000C0
	// (192, 'A' in cyrillic keyboard layout) these functions give 0xFFFFFFC0.
	// Some functions like BanEx and fwrite can't save such corrupted symbols
	// to a file properly, so we have to correct the text.
	static i; i = -1;
	do {} while((reason[++i] &= 0xFF) != '\0');
	return BanEx(playerid, reason);
}

// Reserve ImmediateKick for normal kick without a delay.
native ImmediateBanEx(playerid, const reason[]) = BanEx;

// BanEx hook.
stock dc_kickfix__BanEx(playerid, const reason[])
{
// The "reason" argument should be defined with a "const" qualifier,
// as in original native function definition, so it won't break the
// compatibility in some cases when you pass a constant array to it,
// but it can't be used in SetPVarString directly.
	if(0 == IsPlayerConnected(playerid))
		return 0;
	//SetPVarString(playerid, str__dc_kickfix__reason, reason);
	const ARGS_SIZE = (cellbits / charbits) * 3;
	const USED_STACK_SPACE = ARGS_SIZE + (cellbits / charbits) * 1;
	#emit	push.s		reason
	#emit	push.c		str__dc_kickfix__reason
	#emit	push.s		playerid
	#emit	push.c		ARGS_SIZE
	#emit	sysreq.c	SetPVarString
	#emit	stack		USED_STACK_SPACE
	SetTimerEx(
		!"@__dc_kickfix__DoBanEx", DC_KICKFIX_INTERVAL, false,
		str__dc_kickfix__d, playerid
	);
	return 1;
}
#if defined _ALS_BanEx
	#undef BanEx
#else
	#define _ALS_BanEx
#endif
#define	BanEx(%0)	dc_kickfix__BanEx(%0)
