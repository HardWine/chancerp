#if defined cmd_pass_included
	#endinput
#endif

#define cmd_pass_included

CMD:pass(playerid, params[]) {
	new 
		targetid;

	if(sscanf(params, "u", targetid)) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Используйте: /pass [ID Игрока]");
	} else {
		if(GetPlayerLoging(targetid) == false) {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Игрок не найден");
		}
		if(playerid == targetid) {
			callcmd::me(playerid, "достал свои документы и рассматривает их");
			return Dialog_ShowPass(playerid, targetid);
		} else {
			if(GetDistanceBetweenPlayerz(playerid, targetid, 3.00) == 0) {
				return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Игрок слишком далеко");
			} else {
				format(small_string, sizeof(small_string), 
					"достал свои документы и передал их игроку %s", 
						PlayerInfo[targetid][pName]
				);
				callcmd::me(playerid, small_string);

				return Dialog_ShowPass(playerid, targetid);
			}
		}
	}
}

Dialog_ShowPass(const playerid, const targetid) {
	new 
		Fraction:fractionid = GetPlayerFraction(targetid);

	format(big_string, sizeof(big_string), 
		""COLOR_WHITE"Имя:\t\t\t\t"COLOR_ORANGE"%s\n\
		"COLOR_WHITE"Пол:\t\t\t\t"COLOR_ORANGE"%s\n\
		"COLOR_WHITE"Законопослушность:\t\t"COLOR_ORANGE"%d\n\
		"COLOR_WHITE"Уровень розыска:\t\t"COLOR_ORANGE"%i\n\
		"COLOR_WHITE"Проживание:\t\t\t"COLOR_ORANGE"%s\n\
		"COLOR_WHITE"Фракция:\t\t\t"COLOR_ORANGE"%s",
			PlayerInfo[targetid][pName],
			(PlayerInfo[targetid][pSex] == 0) ? ("Мужской") : ("Женский"),
			PlayerInfo[targetid][pKarma],
			GetPlayerWanted(targetid),
			(GetPlayerHouse(targetid)) ? ("Дом") : ("Бездомный"),
			(fractionid == FRACTION_NONE) ? ("Отсутствует") : FractionTitle[fractionid - 1]
	);
	if(playerid == targetid) {
		small_string[0] = EOS;
		small_string = "Ваш паспорт";
	} else {
		format(small_string, sizeof(small_string), "Паспорт игрока %s", PlayerInfo[targetid][pName]);
	}
	return SPD(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, small_string, big_string, "Закрыть", "");
}