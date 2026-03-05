#if defined _secure_included
	#endinput
#endif
#define _secure_included
//
//
// Реализация защиты аккаунтов от Boulevard_Picard с помощью TOTP.inc 1.0.1 (GamesDV)
// https://github.com/GamesDV/TOTP/releases
//
//
new gacode[MAX_PLAYERS][17];
new secure[MAX_PLAYERS];

CMD:secretcode(playerid)
{
	if(PlayerInfo[playerid][pSecured] != 0) return SPD(playerid, dSecureDisable, DIALOG_STYLE_MSGBOX, "Двухфакторная авторизация | Включено", "{FFFFFF}Ваш аккаунт защищен от взлома по средствам {495488}Google Authentificator\n{FFFFFF}Вы уверены что хотите отключить двухфакторную авторизацию?", "Да", "Отмена");
	new base_encoding[32][] =
	{
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y","Z","2", "3", "4", "5", "6", "7"
	};
	for(new i; i < 17; i++) strcat(gacode[playerid], base_encoding[random(sizeof(base_encoding))]);
	SendClientMessage(playerid, -1, "Введите код, который сейчас появится на экране в приложение Google Authenticator");
	SendClientMessage(playerid, -1, "А затем введите в поле для ввода код, которое вам выдало приложение");
	static const fmt_str[] = "{FFFFFF}Двухфакторная авторизация защитит вас от взлома аккаунта\nДля её использования необходимо установить на смартфон {495488}Google Authentificator\n{FFFFFF}Код, который необходимо добавить в приложение Google Authenticator: {FF9100}%s\n{FFFFFF}После этого введите выданный в приложении код введите здесь:\n\n{FF0000}Внимание: Чтобы код в приложении отображался верно необходимо сделать коррекцию времени\nдля кодов в самом приложении (Настройки > Коррекция времени для кодов > Синхронизировать)";
	new str[sizeof(fmt_str)+ (-2+sizeof(base_encoding))];
	format(str, sizeof(str), fmt_str, gacode[playerid]);
	SPD(playerid, dSecureSetting, DIALOG_STYLE_INPUT, "Двухфакторная авторизация | Настройка", str, "Ввести", "Отмена");
	return true;
}
