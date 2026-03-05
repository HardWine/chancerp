#if defined family_api_included
    #endinput
#endif

#define family_api_included

stock ResetPlayerFamily(playerid) {
    Player.Family[playerid] = NULL_PlayerFamily;
    return 1;
}

stock GetPlayerFamily(playerid) {
    return Player.Family[playerid][E_ID];
}

stock LoadPlayerFamily(playerid) {
    mysql_format(database,
        big_string, sizeof(big_string),
        "SELECT pf.ID, f.Title, CONVERT(f.Color, SIGNED) -1 as Color, pf.FamilyID, CONVERT(pf.Role, SIGNED) -1 as Role FROM player_family AS pf LEFT OUTER JOIN family AS f ON pf.FamilyID = f.ID WHERE pf.PlayerID = %i LIMIT 1",
            GetPlayerAccountID(playerid)
    );
    mysql_query(database, big_string, true);

    new
        rows = cache_get_row_count();

    if(rows) {
        Player.Family[playerid][E_ID] = cache_get_field_content_int(0, "ID");
        Player.Family[playerid][E_FAMILY_ID] = cache_get_field_content_int(0, "FamilyID");
        cache_get_field_content(0, "Title", Player.Family[playerid][E_TITLE]);
        Player.Family[playerid][E_COLOR] = cache_get_field_content_int(0, "Color");
        Player.Family[playerid][E_ROLE] = cache_get_field_content_int(0, "Role");
        return 1;
    } else {
        ResetPlayerFamily(playerid);
        return 0;
    }
}

stock SendFamMessage(const senderid, const text[]) {
    new
        familyID = Player.Family[senderid][E_FAMILY_ID];

    if(familyID == INVALID_FAMILY_ID) {
        return 0;
    } else {
        foreach(new i: Player) {
            if(Player.Family[i][E_FAMILY_ID] == familyID) {
                SendClientMessage(i, -1, text);
            }
        }
    }
    return 1;
}