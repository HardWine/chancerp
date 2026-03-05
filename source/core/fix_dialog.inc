#if defined fix_dialog_included
	#endinput
#endif

#define fix_dialog_included

#include <YSI_Coding\y_hooks>

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	return Y_HOOKS_CONTINUE_RETURN_1;
}

stock ALS_ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[])
{
	printf("вызван ShowPlayerDialog");
	return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}
#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif

#define ShowPlayerDialog ALS_ShowPlayerDialog