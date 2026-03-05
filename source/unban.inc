// TODO Не забудь добавить команду в /ahelp
// TODO а также установить уровень с которого она будет работать

CMD:unban(playerid, params[])
{
    if(GetPlayerAdminLevel(playerid) < 4) {
        return false;
    }

    new
        target_name[MAX_PLAYER_NAME + 1],
        reason[48 + 1];

    if(sscanf(params, "s[24]s[48]", target_name, reason)) {
        SendClientMessage(playerid, -1, !"Используйте: /unban [Ник игрока] [Причина]");
        return false;
    }

    new
        target_accID = Player.GetPlayerAccID(target_name);

    if(target_accID == INVALID_ACCOUNT_ID) {
        format(small_string, sizeof(small_string), "Указанный Вами аккаунт "COLOR_ORANGE"%s"COLOR_WHITE" не существует", target_name);
        SendClientMessage(playerid, -1, small_string);
        return false;
    }
    if(Ban.IsAccBanned(target_accID) == -1) {
        format(small_string, sizeof(small_string), "Указанный Вами аккаунт "COLOR_ORANGE"%s"COLOR_WHITE" не заблокирован, либо уже вышел срок блокировки", target_name);
        SendClientMessage(playerid, -1, small_string);
        return false;
    }

    format(small_string, sizeof(small_string), ""COLOR_RED"[A] Администратор %s(%i) разблокировал игрока %s. Причина: %s", PlayerInfo[playerid][pName], playerid, target_name, reason);
    SendAdminMessage(-1, small_string);

    Ban.UnBanPlayer(target_accID, GetPlayerAccountID(playerid), reason);
    return true;
}