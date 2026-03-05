#if defined verify_system_included
	#endinput
#endif

#define verify_system_included

#include <YSI-Include\YSI\YSI\y_hooks>

CMD:verify(playerid, params[]) {
	if(GetPlayerFraction(playerid) != FRACTION_LSPD) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вам недоступна данная команда.");
	} else {
		new 
			targetid;

		if(sscanf(params, "u", targetid)) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Используйте: /verify [ID Игрока]");
		}
		if(GetPlayerLoging(targetid) == false) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Игрок не найден.");
		}
		// if(GetPlayerFraction(targetid) == FRACTION_LSPD) {
		// 	return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У этого человека нельзя проверить документы.");
		// }
		format(small_string, sizeof(small_string), "Здравствуйте. Вас приветствутет сотрудник LSPD %s", PlayerInfo[playerid][pName]);
		OnPlayerText(playerid, small_string);

		format(small_string, sizeof(small_string), "Предъявил жетон сотрудника LSPD №%i", playerid);
		callcmd::me(playerid, small_string);

		SetPVarInt(playerid, "AntiFloodLocal", gettime() - 1);

		OnPlayerText(playerid, "Покажите пожалуйста, Ваши документы...");
		return Dialog_DoebalsyCop(targetid, playerid);
	}
}

Dialog_DoebalsyCop(const playerid, const targetid) {
	SetPVarInt(playerid, "cmd_verify", targetid);

	return SPD(playerid, 
		DIALOG_VERIFY_TARGETID, DIALOG_STYLE_MSGBOX, 
		"Проверка документов", ""COLOR_WHITE"Вы хотите преъявить "COLOR_GREEN"(Выбор пункта \"Да\")"COLOR_WHITE" свои документы\n\
		сотруднику правоохранительных органов?\n\n\
		"COLOR_ORANGE"Внимание! В случае отказа "COLOR_RED"(Выбор пункта \"Нет\")"COLOR_WHITE"\n\
		Вам будет выдан розыск за неподчинение", "Да", "Нет");
}


hook OnPlayerDialogShowed(const playerid, const e_DIALOG_IDs:dialogid, const response, const listitem, const inputtext[]) {
	if(dialogid == DIALOG_VERIFY_TARGETID) {
		new 
			targetid = GetPVarInt(playerid, "cmd_verify");

		DeletePVar(playerid, "cmd_verify");

		if(!response) {
			format(small_string, sizeof(small_string), 
				""COLOR_ORANGE"%s(%i) отказался от просьбы преъявить документы", 
					PlayerInfo[playerid][pName],
					playerid
			);
			SendClientMessage(targetid, -1, small_string);

			format(small_string, sizeof(small_string), 
				""COLOR_ORANGE"Вы отказалить от просьбы %s(%i) преъявить свои документы", 
					PlayerInfo[targetid][pName],
					targetid
			);
			SendClientMessage(playerid, -1, small_string);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Ваш уровень розыска был увеличен");

			PlayerInfo[playerid][pWanted] += 1200;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
			return Y_HOOKS_BREAK_RETURN_1;
		} else {

			format(small_string, sizeof(small_string), "%i", targetid);
			callcmd::pass(playerid, small_string);
			return Y_HOOKS_BREAK_RETURN_1;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}