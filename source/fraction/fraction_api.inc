#if defined G_fraction_api_included
    #endinput
#endif

#define G_fraction_api_included

stock bool: Fraction.PrintArray(const arrayID) {
    //Log(fractionlog, DEBUG, "Fraction.PrintArray(%i)", arrayID);

    if(Fraction[arrayID][E_FRACTION_ID] == INVALID_FRACTION_ID) {
        //Log(fractionlog, WARNING, "Попытка обращения к неисцилизированному массиву. Fraction.PrintArray(%i)", arrayID);
        return false;
    }

    /*Log(fractionlog, INFO,
        "E_FRACTION_ID = %i, E_FRACTION_NUMBER = %i TITLE = %s\n\
        E_FRACTION_LEADER_ID = %i E_FRACTION_LEADER_NAME = %s E_FRACTION_DATE_DESTINATION = %s\n\
        E_FRACTION_AUTO_INVITE = %i E_FRACTION_AUTO_RANG = %i",
            Fraction[arrayID][E_FRACTION_ID], Fraction[arrayID][E_FRACTION_NUMBER], FractionTitle[Fraction[arrayID][E_FRACTION_NUMBER]],
            Fraction[arrayID][E_FRACTION_LEADER_ID], Fraction[arrayID][E_FRACTION_LEADER_NAME], Fraction[arrayID][E_FRACTION_DATE_DESTINATION],
            Fraction[arrayID][E_FRACTION_AUTO_INVITE], Fraction[arrayID][E_FRACTION_AUTO_RANG]
    );*/
    return true;
}

stock Fraction.SetLeader(const arrayID, const targetid) {
    //Log(fractionlog, DEBUG, "Fraction.SetLeader(%i, %i)", arrayID, targetid);

    if(Fraction[arrayID][E_FRACTION_ID] == INVALID_FRACTION_ID) {
       // Log(fractionlog, WARNING, "Попытка обращения к неисцилизированному массиву. Fraction.SetLeader(%i, %i)", arrayID, targetid);
        return 0;
    }

    if(Fraction[arrayID][E_FRACTION_LEADER_ID] != INVALID_ACCOUNT_ID) {
       // Log(fractionlog, WARNING, "Попытка установить нового лидера организации (%s), без снятия старого (%s). Fraction.SetLeader(%i, %i)", PlayerInfo[targetid][pName], Fraction[arrayID][E_FRACTION_LEADER_NAME], arrayID, targetid);
        return -1;
    }
    if(GetPlayerAccountID(targetid) == 0) {
       // Log(fractionlog, WARNING, "Попытка установить нового лидера организации c accID = 0. Fraction.SetLeader(%i, %i)", arrayID, targetid);
        return -2;
    }

    strmid(Fraction[arrayID][E_FRACTION_LEADER_NAME], PlayerInfo[targetid][pName], 0, strlen(PlayerInfo[targetid][pName]), MAX_PLAYER_NAME);
    Fraction[arrayID][E_FRACTION_LEADER_ID] = GetPlayerAccountID(targetid);
    Player.Leader[targetid] = arrayID;

    new
        local_year,
        local_mouth,
        local_day,
        local_hour,
        local_munite,
        local_second;

    getdate(local_year, local_mouth, local_day);
    gettime(local_hour, local_munite, local_second);

    format(small_string, sizeof(small_string), "%i-%02i-%02i %02i:%02i:%02i", local_year, local_mouth, local_day, local_hour, local_munite, local_second);
    strmid(Fraction[arrayID][E_FRACTION_DATE_DESTINATION], small_string, 0, strlen(small_string), 20);

    mysql_format(database, small_string, sizeof(small_string), "CALL `Fraction.SetLeader` (%i , %i);", Fraction[arrayID][E_FRACTION_ID], GetPlayerAccountID(targetid));
    mysql_pquery(database, small_string);
    return 1;
}

stock Fraction.ResetLeader(const arrayID) {
    //Log(fractionlog, DEBUG, "Fraction.ResetLeader(%i)", arrayID);

    if(Fraction[arrayID][E_FRACTION_ID] == INVALID_FRACTION_ID) {
        //Log(fractionlog, WARNING, "Попытка обращения к неисцилизированному массиву. Fraction.ResetLeader(%i)", arrayID);
        return 0;
    }

    if(Fraction[arrayID][E_FRACTION_LEADER_ID] == INVALID_ACCOUNT_ID) {
        //Log(fractionlog, WARNING, "Попытка снять лидеру у организации без лидера. Fraction.ResetLeader(%i)", arrayID);
        return -1;
    }

    new
        oldFractionLeader = Fraction[arrayID][E_FRACTION_LEADER_ID];

    foreach(new i: Player) {
        if(GetPlayerAccountID(i) == 0) {
            continue;
        }

        if(GetPlayerAccountID(i) == oldFractionLeader) {
            Player.Leader[i] = INVALID_FRACTION_ID;
            Leave(i);
        }
    }
    Fraction[arrayID][E_FRACTION_AUTO_INVITE] = 1;
    Fraction[arrayID][E_FRACTION_AUTO_RANG] = 1;
    Fraction.SetField(arrayID+1, "AutoInvite", 1);
    Fraction.SetField(arrayID+1, "AutoRang", 1);

    strmid(Fraction[arrayID][E_FRACTION_LEADER_NAME], "Отсутсвует", 0, strlen("Отсутсвует"), MAX_PLAYER_NAME);
    Fraction[arrayID][E_FRACTION_LEADER_ID] = INVALID_ACCOUNT_ID;
    strmid(Fraction[arrayID][E_FRACTION_DATE_DESTINATION], "-", 0, strlen("-"), 20);

    mysql_format(database, small_string, sizeof(small_string), "CALL `Fraction.SetLeader` (%i , %i);", Fraction[arrayID][E_FRACTION_ID], INVALID_ACCOUNT_ID);
    mysql_pquery(database, small_string);

    return 1;
}
stock Fraction.SetField(fracid, field[], value) {
    static const fmt_str[] =
        "UPDATE fraction SET  `%e`='%i' WHERE ID=%i LIMIT 1";
    goto skip_array_init;
    new string[sizeof(fmt_str) + 1
        + (- 2 + 32)
        + (- 2 + 64)
        + (- 2 + MAX_LENGTH_ACCOUNT_ID)
    ];
    skip_array_init:

    mysql_format(database,
        string, sizeof(string),
        fmt_str,
            field,
            value,
            fracid
    );
    new result = mysql_pquery(database, string);
    printf("Произошла ошибка при отправке запроса - \"%s\"", string);
    if(result == 0) {
        return printf("Произошла ошибка при отправке запроса - \"%s\"", string);
    } else {
        return 1;
    }
}