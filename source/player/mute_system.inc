#if defined mute_system_included
    #endinput
#endif

#define mute_system_included

#include <YSI-Include\YSI\YSI\y_hooks>

new
    Player.MuteTime[MAX_PLAYERS] = {0, ...};

hook OnPlayerConnect(playerid) {
    Player.MuteTime[playerid] = 0;
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
    Player.MuteTime[playerid] = 0;
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerText(playerid, text[]) {
    if(Player.MuteTime[playerid] >= 1) {
        return SendClientMessage(playerid, -1, ""COLOR_RED"У вас бан чата");
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerAuthorization(playerid) {
    mysql_format(database, small_string, sizeof(small_string),
        "SELECT `MiteCount` FROM `player_mute` WHERE `PlayerID` = %i AND `Status` = 1 ORDER BY ID DESC LIMIT 1",
            PlayerInfo[playerid][pID]
    );
    mysql_query(database, small_string, true);

    new
        rows = cache_get_row_count();

    if(rows == 0) {
        Player.MuteTime[playerid] = 0;
    } else {
        Player.MuteTime[playerid] = cache_get_field_content_int(0, "MiteCount");
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

ptask PlayerMute[1000](playerid)  {
    if(Player.MuteTime[playerid] >= 1) {
        Player.MuteTime[playerid] = Player.MuteTime[playerid] - 1;

        if(Player.MuteTime[playerid] % 60 == 0) {
            mysql_format(database,
                small_string, sizeof(small_string),
                "UPDATE `player_mute` SET `MiteTime`=%i WHERE PlayerID = %i AND Status = 1 ORDER BY ID DESC",
                    Player.MuteTime[playerid], PlayerInfo[playerid][pID]
            );
            mysql_pquery(database, small_string);
        }
        if(Player.MuteTime[playerid] == 0) {
            mysql_format(database,
                small_string, sizeof(small_string),
                "UPDATE `player_mute` SET `MiteTime`=0, `Status` = 2 WHERE PlayerID = %i AND Status = 1 ORDER BY ID DESC",
                    PlayerInfo[playerid][pID]
            );
            mysql_pquery(database, small_string);
        }
    }
}

CMD:muteinfo(playerid, params[]) {
    if(Player.MuteTime[playerid] == 0) {
        return SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас нет активных блокировок чата");
    } else {
        mysql_format(database, big_string, sizeof(big_string),
            "SELECT p.Name, m.MiteTime, m.Reason FROM player_mute AS m LEFT OUTER JOIN players AS p ON p.ID = m.AdminID WHERE m.PlayerID = %i ORDER BY m.ID DESC",
                PlayerInfo[playerid][pID]
        );
        mysql_query(database, big_string, true);
        new
            rows = cache_get_row_count();

        if(rows == 0) {
            return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Произошла ошибка при выполнение запроса.");
        } else {
            new
                adminName[MAX_PLAYER_NAME],
                reason[48],
                date[20];

            cache_get_field_content(0, "Name", adminName);
            cache_get_field_content(0, "MiteTime", date);
            cache_get_field_content(0, "Reason", reason);

            format(big_string, sizeof(big_string), ""COLOR_WHITE"Заблокировал: "COLOR_ORANGE"%s"COLOR_WHITE"\nПричина: "COLOR_ORANGE"%s"COLOR_WHITE"\nДата выдачи: "COLOR_ORANGE"%s"COLOR_WHITE"\nВремени до разблокирвки: "COLOR_GREEN"%s мин.", adminName, reason, date, Convert(Player.MuteTime[playerid]));
            ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, "Информация о блокировке чата", big_string, "Закрыть", !"");
        }

        return 1;
    }
}