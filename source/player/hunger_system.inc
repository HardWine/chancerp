#if defined hunder_system_included
    #endinput
#endif

#define hunder_system_included

#include <YSI-Include\YSI\YSI\y_hooks>

new
    Player.Hunger[MAX_PLAYERS] = {100, ...};

hook OnPlayerConnect(playerid) {
    SetPlayerHunger(playerid, 100);

    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
    #pragma unused reason
    SetPlayerHunger(playerid, 100);

    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerAuthorization(playerid) {
    callcmd::hun(playerid, "\0");
}

#if defined ARMY_FREE_EAT
    new free_eat[5];
#endif

hook OnGameModeInit() {
    #if defined ARMY_FREE_EAT
        CreateDynamicObject(18236, 177.89999, 1927.2, 17.1, 0.00, 0.00, 90.00);
        CreateDynamicMapIcon(171.5427, 1924.5529, 18.8578, 10, -1);

        free_eat[0] = CreateDynamicPickup(1318, 1, 171.5427, 1924.5529, 18.8578);
        CreateDynamic3DTextLabel(!""COLOR_BLUE"Армейская столовая", -1, 171.5427, 1924.5529, 18.8578 + 1.0,
            MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
        );

        free_eat[1] = CreateDynamicPickup(1318, 1, 460.5561, -88.6037, 999.5547);
        CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход", -1, 460.5561, -88.6037, 999.5547 + 1.0,
            MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, MAX_DISTANCE_VISIBLE
        );

        free_eat[2] = CreateDynamicCP(450.7047, -83.8509, 999.5547, 1.00);
        CreateDynamic3DTextLabel(!""COLOR_GREEN"Cух паек", -1, 450.7047, -83.8509, 999.5547 + 1.0,
            MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, MAX_DISTANCE_VISIBLE
        );

        free_eat[3] = CreateDynamicPickup(2768, 1, 257.1321, 83.3535, 1002.4453);
        CreateDynamic3DTextLabel(!""COLOR_GREEN"Пончик с кофе", -1, 257.1321, 83.3535, 1002.4453 + 1.0,
            MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, MAX_DISTANCE_VISIBLE
        );
        free_eat[4] = CreateDynamicPickup(2768, 1, -2504.8999, 530.0089, 432.6819);
        CreateDynamic3DTextLabel(!""COLOR_GREEN"Пончик с кофе", -1, -2504.8999, 530.0089, 432.6819 + 1.0,
            MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, MAX_DISTANCE_VISIBLE
        );
    #endif
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP checkpointid) {
    #if defined ARMY_FREE_EAT
        if(checkpointid == free_eat[2]) {
            if(GetPlayerFraction(playerid) != FRACTION_ARMY) {
                return SendClientMessage(playerid, -1, ""COLOR_RED"Вы не военный.");
            }

            if(GetPVarInt(playerid, "army_eat") > gettime()) {
                SendClientMessage(playerid, -1, !""COLOR_WHITE"Cух паек можно брать раз в "COLOR_ORANGE"три минуты");
                return Y_HOOKS_BREAK_RETURN_1;
            }
            SetPVarInt(playerid, "army_eat", gettime() + 180);

            new hourss, action[32];
            gettime(hourss);
            switch(hourss)
            {
                case 7..12: strcat(action, "завтракает");
                case 13..17: strcat(action, "обедает");
                case 18..23: strcat(action, "ужинает");
                default: strcat(action, "ест");
            }

            SetPlayerHunger(playerid, GetPlayerHunger(playerid) + 15 + random(30));
            callcmd::hun(playerid, "\0");
            ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1,0,1,1,1,1);
            format(small_string, sizeof(small_string), "%s: %s", PlayerInfo[playerid][pName], action);
            ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
            SetPlayerChatBubble(playerid, action, C_PURPLE, MAX_DISTANCE_VISIBLE, 10000);
        }
    #endif
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerPickUpDynPickup(playerid, STREAMER_TAG_PICKUP pickupid) {
    #if defined ARMY_FREE_EAT
        if(pickupid == free_eat[0]) {
            SetPlayerPos(playerid, 457.7031, -88.4847, 999.5547);
            SetPlayerFacingAngle(playerid, 90.00);
            SetPlayerInterior(playerid, 4);
            SetPlayerVirtualWorld(playerid, 1);
            SetCameraBehindPlayer(playerid);
            return Y_HOOKS_BREAK_RETURN_1;
        }
        if(pickupid == free_eat[1]) {
            SetPlayerPos(playerid, 174.6705, 1923.9873, 18.1524);
            SetPlayerFacingAngle(playerid, 270.00);
            SetPlayerInterior(playerid, 0);
            SetPlayerVirtualWorld(playerid, 0);
            SetCameraBehindPlayer(playerid);
            return Y_HOOKS_BREAK_RETURN_1;
        }
        if(pickupid == free_eat[3]) {
            if(GetPlayerFraction(playerid) != FRACTION_LSPD) {
                return SendClientMessage(playerid, -1, ""COLOR_RED"Вы не сотрудник LSPD.");
            }

            if(GetPVarInt(playerid, "army_eat") > gettime()) {
                SendClientMessage(playerid, -1, !""COLOR_WHITE"Cух паек можно брать раз в "COLOR_ORANGE"три минуты");
                return Y_HOOKS_BREAK_RETURN_1;
            }
            SetPVarInt(playerid, "army_eat", gettime() + 180);

            new hourss, action[32];
            gettime(hourss);
            switch(hourss)
            {
                case 7..12: strcat(action, "завтракает");
                case 13..17: strcat(action, "обедает");
                case 18..23: strcat(action, "ужинает");
                default: strcat(action, "ест");
            }

            SetPlayerHunger(playerid, GetPlayerHunger(playerid) + 15 + random(30));
            callcmd::hun(playerid, "\0");
            ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1,0,1,1,1,1);
            format(small_string, sizeof(small_string), "%s: %s", PlayerInfo[playerid][pName], action);
            ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
            SetPlayerChatBubble(playerid, action, C_PURPLE, MAX_DISTANCE_VISIBLE, 10000);
        }
        if(pickupid == free_eat[4]) {
            if(GetPlayerFraction(playerid) != FRACTION_FBI) {
                return SendClientMessage(playerid, -1, ""COLOR_RED"Вы не сотрудник FBI.");
            }

            if(GetPVarInt(playerid, "army_eat") > gettime()) {
                SendClientMessage(playerid, -1, !""COLOR_WHITE"Cух паек можно брать раз в "COLOR_ORANGE"три минуты");
                return Y_HOOKS_BREAK_RETURN_1;
            }
            SetPVarInt(playerid, "army_eat", gettime() + 180);

            new hourss, action[32];
            gettime(hourss);
            switch(hourss)
            {
                case 7..12: strcat(action, "завтракает");
                case 13..17: strcat(action, "обедает");
                case 18..23: strcat(action, "ужинает");
                default: strcat(action, "ест");
            }

            SetPlayerHunger(playerid, GetPlayerHunger(playerid) + 15 + random(30));
            callcmd::hun(playerid, "\0");
            ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1,0,1,1,1,1);
            format(small_string, sizeof(small_string), "%s: %s", PlayerInfo[playerid][pName], action);
            ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
            SetPlayerChatBubble(playerid, action, C_PURPLE, MAX_DISTANCE_VISIBLE, 10000);
        }
    #endif
    return Y_HOOKS_CONTINUE_RETURN_1;
}

stock SetPlayerHunger(playerid, value) {
    Player.Hunger[playerid] = value;

    if(Player.Hunger[playerid] > 100) {
        Player.Hunger[playerid] = 100;
    }
    if(Player.Hunger[playerid] < 0) {
        Player.Hunger[playerid] = 1;
    }
}

stock GetPlayerHunger(playerid) {
    return Player.Hunger[playerid];
}

ptask DownHunger[15000](playerid) {
    if(PlayerLogged{playerid} == true) {
        new
            active_hunger = GetPlayerHunger(playerid);

        SetPlayerHunger(playerid, active_hunger - 1);

        if(active_hunger < 50 && active_hunger > 20) {
            if(active_hunger % 10 == 0) {
                SendClientMessage(playerid, -1, ""COLOR_ORANGE"Ваш персонаж начинает голодать. Посети закусочную в ближайшие время");
            }
        } else if(active_hunger < 20 && active_hunger > 10) {
            if(active_hunger % 5 == 0) {
                SendClientMessage(playerid, -1, ""COLOR_ORANGE"Ваш персонаж голоден. Посети закусочную в ближайшие время");
            }
        }
        if(active_hunger < 10) {
            SetPlayerDrunkLevel(playerid, 0);
            switch(random(10)) {
                case 3: {
                    ApplyAnimation(playerid, !"SWEET", !"Sweet_injuredloop" ,4.1,1,0,0,0,0,0);
                    defer ClearAnim(playerid);
                    SendClientMessage(playerid, -1, ""COLOR_ORANGE"Ваш персонаж голоден. Посети закусочную в ближайшие время");
                }
                case 2: {
                    SetPlayerDrunkLevel(playerid, 5000);
                    SendClientMessage(playerid, -1, ""COLOR_ORANGE"Ваш персонаж голоден. Посети закусочную в ближайшие время");
                }
            }
        }
    }
}

CMD:hun(playerid, params[]) {
    new
        active_hunger = GetPlayerHunger(playerid);

    if(active_hunger > 60) {
        format(small_string, sizeof(small_string), "Ваш уровень сытости: "COLOR_GREEN"отличный"COLOR_WHITE" (%i единиц)", active_hunger);
    } else if(active_hunger >= 60 && active_hunger < 30) {
        format(small_string, sizeof(small_string), "Ваш уровень сытости: "COLOR_ORANGE"в норме"COLOR_WHITE" (%i единиц)", active_hunger);
    } else if(active_hunger >= 30 && active_hunger < 20) {
        format(small_string, sizeof(small_string), "Ваш уровень сытости: "COLOR_ORANGE"персонаж голоден"COLOR_WHITE" (%i единиц)", active_hunger);
    } else {
        format(small_string, sizeof(small_string), "Ваш уровень сытости: "COLOR_RED"персонаж сильно голоден"COLOR_WHITE" (%i единиц)", active_hunger);
    }
    SendClientMessage(playerid, -1, small_string);
    return 1;
}

timer ClearAnim[4000](playerid) {
    ClearAnimations(playerid, 1);
}