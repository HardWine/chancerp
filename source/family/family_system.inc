#if defined family_system_included
    #endinput
#endif

#define family_system_included

#include <family/family_header>
#include <family/family_api>

#include <YSI-Include\YSI\YSI\y_hooks>


hook OnPlayerConnect(playerid) {
    ResetPlayerFamily(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
    #pragma unused reason

    ResetPlayerFamily(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerAuthorization(playerid) {
    LoadPlayerFamily(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

CMD:getfamily(playerid, params[]) {
    new
        arrayID = GetPlayerFamily(playerid);

    if(arrayID == INVALID_FAMILY_ID) {
        return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы не состоите в семье");
    } else {
        // Общие количество игроков в семье
        mysql_format(database,
            big_string, sizeof(big_string),
            "SELECT COUNT(*) AS Total FROM `player_family` AS pf LEFT OUTER JOIN family AS f ON f.ID = pf.FamilyID WHERE f.ID = 1",
                Player.Family[playerid][E_FAMILY_ID]
        );
        mysql_query(database, big_string, true);

        new
            rows = cache_get_row_count(),
            total = 1,
            online,
            familyID = Player.Family[playerid][E_FAMILY_ID];

        if(!rows) {
            return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Произошла ошибка при попытке получить общие количество членов семьи");
        } else {
            total = cache_get_field_content_int(0, "Total");
        }

        // Игроки онлайн
        foreach(new i: Player) {
            if(Player.Family[i][E_FAMILY_ID] == familyID) {
                online++;
            }
        }

        big_string[0] = EOS;

        format(big_string, sizeof(big_string),
            ""COLOR_WHITE"Название семье: {%s}%s\n\
            "COLOR_WHITE"Ваша роль: {%s}%s\n\
            "COLOR_WHITE"Цвет семьи: {%s}%s\n\
            "COLOR_WHITE"Количество игроков (всего): {%s}%i\n\
            "COLOR_WHITE"Количество игроков "COLOR_GREEN"(ONLINE)"COLOR_WHITE": {%s}%i\n\n\
            "COLOR_ORANGE"Доступные действия:\n\
            "COLOR_RED"1. Покинуть семью",

                FamilyColor[Player.Family[playerid][E_COLOR]][E_HEX], Player.Family[playerid][E_TITLE],
                FamilyColor[Player.Family[playerid][E_COLOR]][E_HEX], FamilyRoly[Player.Family[playerid][E_ROLE]],
                FamilyColor[Player.Family[playerid][E_COLOR]][E_HEX], FamilyColor[Player.Family[playerid][E_COLOR]][E_TITLE],
                FamilyColor[Player.Family[playerid][E_COLOR]][E_HEX], total,
                FamilyColor[Player.Family[playerid][E_COLOR]][E_HEX], online
        );

        if(Player.Family[playerid][E_ROLE] >= 1) {
            strcat(big_string, "\n"COLOR_WHITE"2. Панель управления семьей"INPUT_NUMBER"");
        }
        ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_INPUT, "Информация о семье", big_string, "Закрыть", "");
        return 1;
    }
}

CMD:fam(playerid, params[]) {
    new
        arrayID = GetPlayerFamily(playerid);

    if(arrayID == INVALID_FAMILY_ID) {
        return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы не состоите в семье");
    } else {
        if(!params[0]) {
            return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Используйте: /fam [Сообщение]");
        }
        if(strlen(params) > 70) {
            return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Слишком длинное сообщение");
        }

        format(small_string, sizeof(small_string),
            "{%s}[FAM / %s] %s: %s",
                FamilyColor[Player.Family[playerid][E_COLOR]][E_HEX], Player.Family[playerid][E_TITLE],
                PlayerInfo[playerid][pName],
                params
        );
        SendFamMessage(playerid, small_string);
        return 1;
    }
}

