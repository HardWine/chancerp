CMD:getban(playerid, params[])
{
    if(GetPlayerAdminLevel(playerid) < 1) {
        return false;
    }

    new
        target_name[MAX_PLAYER_NAME + 1];

    if(sscanf(params, "s[24]", target_name)) {
        SendClientMessage(playerid, -1, !"Используйте: /getban [Ник игрока]");
        return false;
    }

    new
        target_accID = Player.GetPlayerAccID(target_name);

    if(target_accID == INVALID_ACCOUNT_ID) {
        format(small_string, sizeof(small_string), "Указанный Вами аккаунт "COLOR_ORANGE"%s"COLOR_WHITE" не существует", target_name);
        SendClientMessage(playerid, -1, small_string);
        return false;
    }

    mysql_format(database, big_string, sizeof(big_string),
        "SELECT IFNULL(p.Name, '-') as UnBannedName, b.Reason, b.BanTime, b.UnBanTime FROM player_banned AS b LEFT OUTER JOIN players AS p ON p.ID = b.AdminID WHERE PlayerID = %i ORDER BY b.ID DESC LIMIT 15",
        target_accID
    );
    mysql_query(database, big_string, true);

    new
        rows = cache_get_row_count();

    if(rows == 0) {
        format(small_string, sizeof(small_string), "Указанный Вами аккаунт "COLOR_ORANGE"%s"COLOR_WHITE" не имеел блокировок", target_name);
        SendClientMessage(playerid, -1, small_string);
        return false;
    } else {
        new
            bantime[20 + 1],
            unbantime[20 + 1],
            unbanadmin[MAX_PLAYER_NAME + 1],
            reason[48 + 1];

        if(Platform[playerid] != 0) {
            huge_string = !"Дата блокировки\tДата разблокировки\tПричина\tРазблокирован\n";
        } else {
           huge_string = !""COLOR_BLUE"Дата блокировки\tДата разблокировки\tПричина\tРазблокирован\n\n"COLOR_WHITE"";
        }
        for(new i = 0; i < rows; i++) {
            cache_get_field_content(i, "BanTime", bantime);
            cache_get_field_content(i, "UnBanTime", unbantime);
            cache_get_field_content(i, "Reason", reason);
            cache_get_field_content(i, "UnBannedName", unbanadmin);

            format(big_string, sizeof(big_string),
                "%s\t%s\t%s\t%s\n",
                    bantime,
                    unbantime,
                    reason,
                    unbanadmin
            );
            strcat(huge_string, big_string);
        }


        if(Platform[playerid] != 0) {
            format(small_string, sizeof(small_string), ""COLOR_BLUE"Информация о блокировках %s", target_name);
            ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_TABLIST_HEADERS, small_string, huge_string, "Закрыть", "");
        } else {
            format(small_string, sizeof(small_string), "Информация о блокировках %s", target_name);
            ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, small_string, huge_string, "Закрыть", "Закрыть");
        }
    }

    return true;
}
