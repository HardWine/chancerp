#if defined G_fraction_system_included
    #endinput
#endif

#define G_fraction_system_included

#include <source/fraction/fraction_header>
#include <source/fraction/fraction_api>

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
    // Сбрасываем значение всех организаций на стандартные
    for(new i = 0; i < MAX_FRACTION; i++) {
        Fraction[i] = NULL_FRACTION_INFO;
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

stock LoadFraction() {
    mysql_tquery(database, "CALL `ShowFractions`", "@_LoadFraction");
}


hook OnPlayerConnect(playerid) {
    Player.Leader[playerid] = INVALID_FRACTION_ID;
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
    #pragma unused reason
    Player.Leader[playerid] = INVALID_FRACTION_ID;
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerAuthorization(playerid) {
    new
        accID = GetPlayerAccountID(playerid);

    if(accID == 0) {
        //Log(fractionlog, ERROR, "Попытка проверить лидерство во фракции у игрока с ID 0 (%s)", PlayerInfo[playerid][pName]);
        return Y_HOOKS_CONTINUE_RETURN_1;
    }

    for(new i = 0; i < MAX_FRACTION; i++) {
        if(Fraction[i][E_FRACTION_ID] == INVALID_FRACTION_ID) {
            continue;
        }

        if(Fraction[i][E_FRACTION_LEADER_ID] == accID) {
            Player.Leader[playerid] = i;
            break;
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

@_LoadFraction();
@_LoadFraction() {
    new
        rows = cache_get_row_count();

    if(rows == 0) {
        //Log(fractionlog, ERROR, "Отсутсвуют организации для загрузки");
    } else {
        if(rows > MAX_FRACTION) {
            rows = MAX_FRACTION;
            //Log(fractionlog, ERROR, "Количество записей в базе даннных больше значения MAX_FRACTION. (rows = %i, MAX_FRACTION = %i)", rows, MAX_FRACTION);
        }

        for(new i = 0; i < rows; i++) {
            Fraction[i][E_FRACTION_ID] = cache_get_field_content_int(i, "ID");
            Fraction[i][E_FRACTION_NUMBER] = cache_get_field_content_int(i, "Fraction_ID");
            Fraction[i][E_FRACTION_LEADER_ID] = cache_get_field_content_int(i, "Leader_ID");
            Fraction[i][E_FRACTION_AUTO_INVITE] = cache_get_field_content_int(i, "AutoInvite");
            Fraction[i][E_FRACTION_AUTO_RANG] = cache_get_field_content_int(i, "AutoRang");
           
            cache_get_field_content(i, "Leader_Name", Fraction[i][E_FRACTION_LEADER_NAME]);
            cache_get_field_content(i, "Date_Destination", Fraction[i][E_FRACTION_DATE_DESTINATION]);

        }
    }
}

CMD:leaders(playerid) {
    huge_string[0] = EOS;
    huge_string = !"Организация\tЛидер\tДата назначения\n";

    for(new i = 0; i < MAX_FRACTION; i++) {
        if(Fraction[i][E_FRACTION_ID] == INVALID_FRACTION_ID) {
            continue;
        }
        if(GetFractionLeader(i) == INVALID_ACCOUNT_ID) {
            format(small_string, sizeof(small_string), "%s\t"COLOR_ORANGE"%s"COLOR_WHITE"\t-\n",
                GetFractionTitle(i),
                Fraction[i][E_FRACTION_LEADER_NAME]
            );
        } else {
            format(small_string, sizeof(small_string), "%s\t"COLOR_GREEN"%s"COLOR_WHITE"\t%10s\n",
                GetFractionTitle(i),
                Fraction[i][E_FRACTION_LEADER_NAME],
                Fraction[i][E_FRACTION_DATE_DESTINATION]
            );
        }
        strcat(huge_string, small_string);
    }
    return SPD(playerid, dLeaders, DIALOG_STYLE_TABLIST_HEADERS, ""COLOR_BLUE"Список лидеров", huge_string, "Выбрать", "Закрыть");
}
CMD:setleader(playerid, params[]) {
    if(GetPlayerAdminLevel(playerid) < 6) return true;
    new selectedid;
    if(sscanf(params, "d", selectedid)) return SendClientMessage(playerid, -1, !"Используйте: /setleader [id игрока]");
    if(!IsPlayerConnected(selectedid)) return 1;
    if(selectedid == INVALID_PLAYER_ID) return 1;
    if(GetPlayerLeader(selectedid) != -1) return SendClientMessage(playerid, -1, ""COLOR_RED"Данный игрок уже является лидером");

    SetPVarInt(playerid, "selected_leader", selectedid);

    format(small_string, sizeof small_string, ""COLOR_ORANGE"Назначение %s", PlayerInfo[selectedid][pName]);  

    if(Platform[playerid] == 1) {
    format(small_string, sizeof small_string, ""COLOR_ORANGE"Назначение %s", PlayerInfo[selectedid][pName]);  
    return SPD(playerid, dSetLeader, DIALOG_STYLE_LIST, small_string,
    "1. LSPD\n\
    2. Grove Street\n\
    3. Ballas Gang\n\
    4. Vagos Gang\n\
    5. Rifa Gang\n\
    6. Aztecas Gang\n\
    7. Русская Мафия\n\
    8. Triads\n\
    9. Da Nang Boys\n\
    10. Армия\n\
    11. FBI\n\
    12. Правительство\n\
    13. San News",
    "Далее", "Отмена");
    }
    else {
    format(small_string, sizeof small_string, ""COLOR_ORANGE"Назначение %s", PlayerInfo[selectedid][pName]);  
    return SPD(playerid, dSetLeaderAdaptive, DIALOG_STYLE_INPUT, small_string,
    "{FFFFFF}1. LSPD\n\
    2. Grove Street\n\
    3. Ballas Gang\n\
    4. Vagos Gang\n\
    5. Rifa Gang\n\
    6. Aztecas Gang\n\
    7. Русская Мафия\n\
    8. Triads\n\
    9. Da Nang Boys\n\
    10. Армия\n\
    11. FBI\n\
    12. Правительство\n\
    13. San News\n\n\
    "COLOR_ORANGE"Введите ID фракции для продолжения\n",
    "Далее", "Отмена");
    }
}
cmd:delleader(playerid) {
    if(GetPlayerAdminLevel(playerid) < 6) return true;
    if(Platform[playerid] == 1) return SPD(playerid, dDelLeader, DIALOG_STYLE_LIST, ""COLOR_RED"Снятие лидера",
    "1. LSPD\n\
    2. Grove Street\n\
    3. Ballas Gang\n\
    4. Vagos Gang\n\
    5. Rifa Gang\n\
    6. Aztecas Gang\n\
    7. Русская Мафия\n\
    8. Triads\n\
    9. Da Nang Boys\n\
    10. Армия\n\
    11. FBI\n\
    12. Правительство\n\
    13. San News",
    "Далее", "Отмена");
    else return SPD(playerid, dDelLeaderAdaptive, DIALOG_STYLE_INPUT, "Снятие лидера",
    "{FFFFFF}1. LSPD\n\
    2. Grove Street\n\
    3. Ballas Gang\n\
    4. Vagos Gang\n\
    5. Rifa Gang\n\
    6. Aztecas Gang\n\
    7. Русская Мафия\n\
    8. Triads\n\
    9. Da Nang Boys\n\
    10. Армия\n\
    11. FBI\n\
    12. Правительство\n\n\
    "COLOR_ORANGE"Введите ID фракции для продолжения\n",
    "Далее", "Отмена");    
}
cmd:lpanel(playerid) {

    if(Player.Leader[playerid] == INVALID_FRACTION_ID)
        return SendClientMessage(playerid, -1, "Вы не являетесь лидером фракции");
    new fractionid = Player.Leader[playerid];
    printf("%d %d %d",fractionid, Fraction[fractionid][E_FRACTION_AUTO_INVITE],Fraction[fractionid][E_FRACTION_AUTO_RANG]);
    new menu_string[156];

    

    if(Platform[playerid] == 1) {
    format(small_string, sizeof small_string, ""COLOR_BLUE"Настройки %s", GetFractionTitle(fractionid));
    format(menu_string, sizeof menu_string, "1. Прием за оплату\t%s\n\
     2. Прокачка ранга\t%s", 
     (Fraction[fractionid][E_FRACTION_AUTO_INVITE] == 1) ? (""COLOR_GREEN"Вкл.") : (""COLOR_RED"Выкл."),
     (Fraction[fractionid][E_FRACTION_AUTO_RANG] == 1) ? (""COLOR_GREEN"Вкл.") : (""COLOR_RED"Выкл."));
    return SPD(playerid, dLeaderPanel, DIALOG_STYLE_LIST, small_string,
    menu_string,
    "Далее",
    "Закрыть");
    }
    else {
    format(small_string, sizeof small_string, "Настройки %s", GetFractionTitle(fractionid));
    format(menu_string, sizeof menu_string, "1. Прием за оплату\t%s\n\
     {FFFFFF}2. Прокачка ранга\t%s\n\n\
     "COLOR_BLUE"Введите цифру выбранного пункта", 
     (Fraction[fractionid][E_FRACTION_AUTO_INVITE] == 1) ? (""COLOR_GREEN"Вкл.") : (""COLOR_RED"Выкл."),
     (Fraction[fractionid][E_FRACTION_AUTO_RANG] == 1) ? (""COLOR_GREEN"Вкл.") : (""COLOR_RED"Выкл."));
    return SPD(playerid, dLeaderPanelAdaptive, DIALOG_STYLE_INPUT, small_string,
    menu_string,
    "Далее",
    "Закрыть");
    }        
}