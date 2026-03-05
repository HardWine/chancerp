#if defined job_puzza_included
    #endinput
#endif

#define job_puzza_included

#include <YSI_Coding\y_hooks>

#define PRICE_SKIN_PIZZA                        (400) // Стоимость формы курьера

enum 
    E_JOB_PIZZA_CAR {
        E_ID,
        Float: E_X,
        Float: E_Y,
        Float: E_Z,
        Float: E_ANGLE,
        E_VEHICLE_ID,
        E_PLAYER_ID
    }

new 
    JobPizzaCar[][E_JOB_PIZZA_CAR] = {
        {0, 2123.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID},
        {0, 2121.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID},
        {0, 2119.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID},
        {0, 2117.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID},
        {0, 2115.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID},
        {0, 2113.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID},
        {0, 2111.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID},
        {0, 2109.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID},
        {0, 2107.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID},
        {0, 2105.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID},
        {0, 2103.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID},
        {0, 2101.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID},
        {0, 2099.3623, -1785.0969, 12.9703, 0.0000, INVALID_VEHICLE_ID, INVALID_PLAYER_ID}
    };

new 
    AreaJob;

new 
    bool: PlayerJobPizza[MAX_PLAYERS] = {false, ...},
    PlayerPizzaHouseCP[MAX_PLAYERS][2],
    PlayerPizzaSkill[MAX_PLAYERS] = {0, ...};

new 
    Text: PizzaTD[2];
new 
    PlayerText: PlayerPizzaTD[MAX_PLAYERS];

hook OnGameModeInit() {
    // Окно в пиццерии
    CreateDynamicObject(3034, 2123.70, -1805.20, 14.20, 0.00, 0.00, 90.00);

    for(new i = 0; i < sizeof(JobPizzaCar); i++) {
        JobPizzaCar[i][E_VEHICLE_ID] = AddStaticVehicle(448, 
            JobPizzaCar[i][E_X], JobPizzaCar[i][E_Y], JobPizzaCar[i][E_Z], JobPizzaCar[i][E_ANGLE], 
            3, random(120)
        );
    }
    CreateDynamicPickup(1275, 23, 368.0597, -119.6428, 1001.4922, 114, 5);
    AreaJob = CreateDynamicSphere(368.0597, -119.6428, 1001.4922, 1.00, 114, 5);
    CreateDynamic3DTextLabel(""COLOR_BLUE"Трудоустройство\n"COLOR_ORANGE"(доставщик пиццы)", -1, 
        368.0597, -119.6428, 1002.4922, 
        MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 114, 5, -1, MAX_DISTANCE_VISIBLE
    );

    PizzaTD[0] = TextDrawCreate(509.944549, 433.283447, "box");
    TextDrawLetterSize(PizzaTD[0], 0.000000, 1.332357);
    TextDrawTextSize(PizzaTD[0], 652.296508, 0.000000);
    TextDrawAlignment(PizzaTD[0], 1);
    TextDrawColor(PizzaTD[0], -1);
    TextDrawUseBox(PizzaTD[0], 1);
    TextDrawBoxColor(PizzaTD[0], 125);
    TextDrawSetShadow(PizzaTD[0], 0);
    TextDrawFont(PizzaTD[0], 1);
    TextDrawSetProportional(PizzaTD[0], 1);

    PizzaTD[1] = TextDrawCreate(511.539764, 433.433471, "box");
    TextDrawLetterSize(PizzaTD[1], 0.000000, 1.519767);
    TextDrawTextSize(PizzaTD[1], 506.399902, 0.000000);
    TextDrawAlignment(PizzaTD[1], 1);
    TextDrawColor(PizzaTD[1], -5963521);
    TextDrawUseBox(PizzaTD[1], 1);
    TextDrawBoxColor(PizzaTD[1], -5963521);
    TextDrawSetShadow(PizzaTD[1], 0);
    TextDrawBackgroundColor(PizzaTD[1], 255);
    TextDrawFont(PizzaTD[1], 1);
    TextDrawSetProportional(PizzaTD[1], 1);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerConnect(playerid) {
    PlayerJobPizza{playerid} = false;
    PlayerPizzaSkill[playerid] = 0;

    for(new i = 0; i < sizeof(PlayerPizzaHouseCP[]); i++) {
        PlayerPizzaHouseCP[playerid][i] = INVALID_STREAMER_ID;
    }
    PlayerPizzaTD[playerid] = CreatePlayerTextDraw(playerid, 516.902770, 435.350158, "~w~DISTANCE: ~g~~h~~h~1200.0");
    PlayerTextDrawLetterSize(playerid, PlayerPizzaTD[playerid], 0.338155, 0.981665);
    PlayerTextDrawTextSize(playerid, PlayerPizzaTD[playerid], 638.299682, 0.000000);
    PlayerTextDrawAlignment(playerid, PlayerPizzaTD[playerid], 1);
    PlayerTextDrawColor(playerid, PlayerPizzaTD[playerid], 16711935);
    PlayerTextDrawSetShadow(playerid, PlayerPizzaTD[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerPizzaTD[playerid], 255);
    PlayerTextDrawFont(playerid, PlayerPizzaTD[playerid], 2);
    PlayerTextDrawSetProportional(playerid, PlayerPizzaTD[playerid], 1);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason) {
    PlayerJobPizza{playerid} = false;  
    PlayerPizzaSkill[playerid] = 0;

    for(new i = 0; i < sizeof(PlayerPizzaHouseCP[]); i++) {
        PlayerPizzaHouseCP[playerid][i] = INVALID_STREAMER_ID;
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA areaid) {
    if(areaid == AreaJob) {
        return ShowPlayerDialog(playerid,
            DIALOG_JOB_PIZZA, DIALOG_STYLE_INPUT,
            ""COLOR_BLUE"Работа: "COLOR_ORANGE"доставщик пиццы",
            ""COLOR_GREEN"Профессиональные навыки:"COLOR_WHITE"\n\
            - Выполнив 25 заказов, отсек под пиццу твоего мопеда будет\n\
            увеличен. Ты сможете брать две пиццы у закусочной за один\n\
            раз.\n\
            - Выполнив 50 заказов, твои чаевые будут увеличены на 15\%\n\
            - Выполнив 100 заказов, стоимость одежды курьера будет\n\
            снижена на 50\%\n\
            - Выполнив 150 заказов, твои чаевые будут увеличены на 25\%\n\
            - Выполнив более 200 заказов, ты сможете брать одежду\n\
            курьера бесплатно. Твои чаевые будут увеличены на 40\%\n\n\
            "COLOR_ORANGE"Доступные действия:"COLOR_WHITE"\n\
            1. Начать/закончить работу\n\
            2. Арендовать форму курьера (400 EXP)",
            !"Далее", !"Закрыть"
        );
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA areaid) {
    
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDialogShowed(const playerid, const e_DIALOG_IDs:dialogid, const response, const listitem, const inputtext[]) {
    if(dialogid == DIALOG_JOB_PIZZA_AND_1) {
        return ShowPlayerDialog(playerid,
            DIALOG_JOB_PIZZA, DIALOG_STYLE_INPUT,
            ""COLOR_BLUE"Работа: "COLOR_ORANGE"доставщик пиццы",
            ""COLOR_GREEN"Профессиональные навыки:"COLOR_WHITE"\n\
            - Выполнив 25 заказов, отсек под пиццу твоего мопеда будет\n\
            увеличен. Ты сможете брать две пиццы у закусочной за один\n\
            раз.\n\
            - Выполнив 50 заказов, твои чаевые будут увеличены на 15\%\n\
            - Выполнив 100 заказов, стоимость одежды курьера будет\n\
            снижена на 50\%\n\
            - Выполнив 150 заказов, твои чаевые будут увеличены на 25\%\n\
            - Выполнив более 200 заказов, ты сможете брать одежду\n\
            курьера бесплатно. Твои чаевые будут увеличены на 40\%\n\n\
            "COLOR_ORANGE"Доступные действия:"COLOR_WHITE"\n\
            1. Начать/закончить работу\n\
            2. Арендовать форму курьера (400 EXP)",
            !"Далее", !"Закрыть"
        );
    }
    if(dialogid == DIALOG_JOB_PIZZA_AND_2 || dialogid == DIALOG_JOB_PIZZA) {
        new 
            strval_inputtext = strval(inputtext);

        if(strval_inputtext == 1) {
            if(PlayerJobPizza[playerid] == false) {
                PlayerJobPizza[playerid] = true;
                SetPVarInt(playerid, "pizza_job_stoynka", 1);
                DeletePVar(playerid, "show_pizza");
                SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы устроились доставщиком пиццы");
                SendClientMessage(playerid, -1, ""COLOR_GREEN"Выйдите из ресторана, и найдите стоянку мопедов");
                SendClientMessage(playerid, -1, ""COLOR_GREEN"После чего, займите один из свободных мопедов");
                return Y_HOOKS_BREAK_RETURN_1;
            } else {
                PlayerJobPizza[playerid] = false;
                for(new i = 0; i < sizeof(PizzaTD); i++) {
                    TextDrawHideForPlayer(playerid, PizzaTD[i]);
                }
                for(new i = 0; i < sizeof(PlayerPizzaHouseCP[]); i++) {
                    if(PlayerPizzaHouseCP[playerid][i] != INVALID_STREAMER_ID) {
                        DestroyPlayerCP(playerid, PlayerPizzaHouseCP[playerid][i]);
                    }
                    PlayerPizzaHouseCP[playerid][i] = INVALID_STREAMER_ID;
                }
                PlayerTextDrawHide(playerid, PlayerPizzaTD[playerid]);
                SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы уволились с работы доставщика пиццы");
                return Y_HOOKS_BREAK_RETURN_1;
            }
        } else if(strval_inputtext == 2) {
            if(GetPlayerSkin(playerid) == 155) {
                SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже арендовали форму курьера");
                return Y_HOOKS_BREAK_RETURN_1;
            }
            new 
                skill = PlayerPizzaSkill[playerid],
                cash = PRICE_SKIN_PIZZA;
                
            if(skill >= 100) {
                cash = PRICE_SKIN_PIZZA / 2;
            }
            if(skill >= 200) {
                cash = 0;
            }

            if(CheckCash(playerid, cash) == false) return 1;
            RemovePlayerEXP(playerid, cash, "Работа развозчика пиццы. Аренда формы");
            SetPlayerSkin(playerid, 155);
            return Y_HOOKS_BREAK_RETURN_1;
        } else {
            OnPlayerEnterDynamicArea(playerid, AreaJob);
            return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Введен неверный номер пункта");
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid) {
    if(newinteriorid == 0 && PlayerJobPizza[playerid] == true && GetPVarInt(playerid, "pizza_job_stoynka") == 1) {

        DeletePVar(playerid, "pizza_job_stoynka");

        ShowPlayerDialog(playerid, 
            DIALOG_INFO, DIALOG_STYLE_MSGBOX, 
            ""COLOR_BLUE"Работа: "COLOR_ORANGE"доставщик пиццы", 
            ""COLOR_WHITE"Отправляйтесь на стоянку, и займите "COLOR_GREEN"свободный"COLOR_WHITE" мопед", 
            "Закрыть", ""
        );
        InterpolateCameraPos(playerid, 2103.562255, -1806.837646, 13.899127, 2111.720947, -1763.511108, 16.715671, 2500);
        InterpolateCameraLookAt(playerid, 2098.650878, -1805.913818, 14.059257, 2111.631103, -1768.479980, 16.166004, 2500);
        defer ReturnCameraPizza(playerid);
        return Y_HOOKS_BREAK_RETURN_1;
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnVehicleSpawn(vehicleid) {
    for(new i = 0; i < sizeof(JobPizzaCar); i++) {
        if(JobPizzaCar[i][E_VEHICLE_ID] == vehicleid) {
            new 
                playerid = JobPizzaCar[i][E_PLAYER_ID];

            JobPizzaCar[i][E_PLAYER_ID] = INVALID_PLAYER_ID;

            if(IsPlayerConnected(playerid) && PlayerJobPizza[playerid] == true) {
                PlayerJobPizza[playerid] = false;
                SendClientMessage(playerid, -1, ""COLOR_WHITE"Работа "COLOR_GREEN"доставщика пиццы"COLOR_WHITE"завершена");
            }
        }
    }
}

hook OnVehicleDeath(vehicleid, killerid) {
    for(new i = 0; i < sizeof(JobPizzaCar); i++) {
        if(JobPizzaCar[i][E_VEHICLE_ID] == vehicleid) {
            new 
                playerid = JobPizzaCar[i][E_PLAYER_ID];

            JobPizzaCar[i][E_PLAYER_ID] = INVALID_PLAYER_ID;

            if(IsPlayerConnected(playerid) && PlayerJobPizza[playerid] == true) {
                PlayerJobPizza[playerid] = false;
                SendClientMessage(playerid, -1, ""COLOR_WHITE"Работа "COLOR_GREEN"доставщика пиццы"COLOR_WHITE"завершена");
            }
        }
    }
}

// найти "if(return_value != 5) {" и добавить перед CallLocalFunction("OnPlayerEnteredVehicle", "ii", playerid, vehicleid);
hook OnPlayerEnteredVehicle(playerid, vehicleid) {
    for(new i = 0; i < sizeof(JobPizzaCar); i++) {
        if(vehicleid == JobPizzaCar[i][E_VEHICLE_ID]) {
            if(PlayerJobPizza[playerid] == false) {
                SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы не устроились на работу доставщика пиццы");
                RemovePlayerFromVehicle(playerid);
                return Y_HOOKS_BREAK_RETURN_1;
            }

            if(GetPVarInt(playerid, "show_pizza") == 0) {
                ShowPlayerDialog(playerid, 
                    DIALOG_INFO, DIALOG_STYLE_MSGBOX, 
                    ""COLOR_BLUE"Работа: "COLOR_ORANGE"доставщик пиццы", 
                    ""COLOR_WHITE"Отправляйтесь к окошку пицерии, для загрузки "COLOR_RED"(красная метка)", 
                    "Закрыть", ""
                );
                
                InterpolateCameraPos(playerid, 2111.617919, -1765.338134, 18.301687, 2131.842041, -1802.610351, 14.486857, 2500);
                InterpolateCameraLookAt(playerid, 2111.570312, -1770.180908, 17.058639, 2127.001464, -1803.838500, 14.242450, 2500);
                defer ReturnCameraPizza(playerid);

                new checkpointid = CreatePlayerCP(playerid, 2125.2842, -1805.0114, 13.1270, "@_PlayerLoadPizza");
                SetPlayerCPGlobal(playerid, checkpointid, true);
                EnabledPlayerCPDestoy(playerid, checkpointid, true);

                SetPVarInt(playerid, "show_pizza", 1);
            }
            return Y_HOOKS_BREAK_RETURN_1;
        }
    }
    return Y_HOOKS_CONTINUE_RETURN_1;
}

@_PlayerLoadPizza(playerid);
@_PlayerLoadPizza(playerid) {
    InterpolateCameraPos(playerid, 2126.648925, -1805.442749, 14.196038, 2137.213134, -1805.861938, 15.650208, 2500);
    InterpolateCameraLookAt(playerid, 2121.700683, -1805.218994, 13.514715, 2132.263671, -1805.665283, 14.968885, 2500);
    
    SetVehiclePos(GetPlayerVehicleID(playerid), 2125.1418, -1805.1628, 13.1265);
    SetVehicleZAngle(GetPlayerVehicleID(playerid), 270.00);

    new 
        time = 10;
    
    SetPVarInt(playerid, "player_pizza", 1);

    if(PlayerPizzaSkill[playerid] >= 25) {
        time = 20;
        SetPVarInt(playerid, "player_pizza", 2);
    }

    SetPVarInt(playerid, "MinusTime", time);
    TogglePlayerControllable(playerid, false);    
    defer PizzaLoadgind[time * 1000](playerid);

    return ShowPlayerDialog(playerid, 
        DIALOG_INFO, DIALOG_STYLE_MSGBOX, 
        ""COLOR_BLUE"Работа: "COLOR_ORANGE"доставщик пиццы", 
        ""COLOR_WHITE"Ожидайте окончания загрузки пиццы", 
        "Закрыть", ""
    );
}

@_PlayerGivePizza(playerid);
@_PlayerGivePizza(playerid) {
    if(GetPVarInt(playerid,"pizza_ss") < gettime()) { return 1; }
    
    if(IsPlayerInAnyVehicle(playerid)) {
        return ShowPlayerDialog(playerid, 
            DIALOG_INFO, DIALOG_STYLE_MSGBOX, 
            ""COLOR_BLUE"Работа: "COLOR_ORANGE"доставщик пиццы", 
            ""COLOR_WHITE"Вы не должны находиться за рулем", 
            "Закрыть", ""
        );
    }
    
    new 
        Float: pos_x,
        Float: pos_y,
        Float: pos_z;

    GetPlayerPos(playerid, pos_x, pos_y, pos_z);
    
    InterpolateCameraPos(playerid, pos_x, pos_y, pos_z, pos_x, pos_y, pos_z + 35.00, 2500);
    InterpolateCameraLookAt(playerid, pos_x, pos_y, pos_z, pos_x, pos_y, pos_z + 30.00, 2500);
    
    format(small_string, sizeof(small_string), "~b~~h~DONE", random(40) + 40);
    GameTextForPlayer(playerid, small_string, 2500, 4);

    TogglePlayerControllable(playerid, false);
    defer DonePizzaJob(playerid);
    return true;
}

task CheckPizzaCar[1000]() 
{
    for(new i = 0; i < sizeof(JobPizzaCar); i++) {
        if(JobPizzaCar[i][E_PLAYER_ID] != INVALID_PLAYER_ID && PlayerJobPizza[JobPizzaCar[i][E_PLAYER_ID]] == false) {
            SetVehicleToRespawn(JobPizzaCar[i][E_VEHICLE_ID]);
            JobPizzaCar[i][E_PLAYER_ID] = INVALID_PLAYER_ID;
        }
    }
}

timer ReturnCameraPizza[3000](playerid) {
    TogglePlayerControllable(playerid, true);
    return SetCameraBehindPlayer(playerid);
}

timer PizzaLoadgind[20000](playerid) {
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, true);

    ShowPlayerDialog(playerid, 
        DIALOG_INFO, DIALOG_STYLE_MSGBOX, 
        ""COLOR_BLUE"Работа: "COLOR_ORANGE"доставщик пиццы", 
        ""COLOR_WHITE"Пицца загружена. Отправляйтесь к клиенту домой "COLOR_RED"(красная метка на миникарте)", 
        "Закрыть", ""
    );

    new random_street = RandomEx(1,11),
        random_house;

    if(random_street == 1) random_house = RandomEx(23,26);
    if(random_street == 2) random_house = RandomEx(42,57);
    if(random_street == 3) random_house = RandomEx(65,78);
    if(random_street == 4) random_house = RandomEx(79,85);
    if(random_street == 5) random_house = RandomEx(100,105);
    if(random_street == 6) random_house = RandomEx(117,128);
    if(random_street == 7) random_house = RandomEx(151,156);
    if(random_street == 8) random_house = RandomEx(178,173);
    if(random_street == 9) random_house = RandomEx(273,276);
    if(random_street == 10) random_house = RandomEx(317,322);
    if(random_street == 11) random_house = RandomEx(213,217);

    new checkpointid = CreatePlayerCP(playerid, HouseInfo[random_house][hEntrancex], HouseInfo[random_house][hEntrancey], HouseInfo[random_house][hEntrancez], "@_PlayerGivePizza");
    SetPlayerCPGlobal(playerid, checkpointid, true);
    EnabledPlayerCPDestoy(playerid, checkpointid, true);

    return SetPVarInt(playerid, "pizza_house", random_house);
}

timer DonePizzaJob[3000](playerid) {
    SetCameraBehindPlayer(playerid);
    TogglePlayerControllable(playerid, true);

    new default_min = 20;

    if(GetPlayerSkin(playerid) == 155) default_min = 35;   

    new 
        player_tip = random(50) + default_min,
        player_cash,
        bonus;

    new 
        skill = PlayerPizzaSkill[playerid];

    if (skill >= 30 && skill < 150) {
        bonus = (player_tip / 100) * 15;
    }
    if(skill >= 150 && skill < 200) {
        bonus = (player_tip / 100) * 25;
    }
    if(skill >= 500) {
        bonus = (player_tip / 100) * 40;
    }

    player_tip = player_tip + bonus;

    format(big_string, sizeof(big_string), ""COLOR_WHITE"Время выполнения заказа "COLOR_GREEN"%s"COLOR_WHITE"\n\
        Чаевые: "COLOR_GREEN"%i EXP"COLOR_WHITE"\n\
        Всего заработано: "COLOR_GREEN"%i EXP", 
            Convert(GetPVarInt(playerid, "pizza_total_time")), 
            player_tip, 
            player_cash + player_tip
    );



    AddPlayerEXP(playerid, (player_tip + player_cash), "Работа развозчик пиццы");

    PlayerPizzaSkill[playerid] = PlayerPizzaSkill[playerid]+1;
    SetPlayerInt(playerid, "PizzaSkill", PlayerPizzaSkill[playerid]);

    ShowPlayerDialog(playerid, 
        DIALOG_INFO, DIALOG_STYLE_MSGBOX, 
        ""COLOR_BLUE"Работа: "COLOR_ORANGE"доставщик пиццы", 
        big_string, 
        "Закрыть", ""
    );

    SetPVarInt(playerid, "player_pizza", GetPVarInt(playerid, "player_pizza") -1);
   
    if(GetPVarInt(playerid, "player_pizza") == 1) {
        new random_street = RandomEx(1,11),
            random_house;

        if(random_street == 1) random_house = RandomEx(23,26);
        if(random_street == 2) random_house = RandomEx(42,57);
        if(random_street == 3) random_house = RandomEx(65,78);
        if(random_street == 4) random_house = RandomEx(79,85);
        if(random_street == 5) random_house = RandomEx(100,105);
        if(random_street == 6) random_house = RandomEx(117,128);
        if(random_street == 7) random_house = RandomEx(151,156);
        if(random_street == 8) random_house = RandomEx(178,173);
        if(random_street == 9) random_house = RandomEx(273,276);
        if(random_street == 10) random_house = RandomEx(317,322);
        if(random_street == 11) random_house = RandomEx(213,217);

        new checkpointid = CreatePlayerCP(playerid, HouseInfo[random_house][hEntrancex], HouseInfo[random_house][hEntrancey], HouseInfo[random_house][hEntrancez], "@_PlayerGivePizza");
        SetPlayerCPGlobal(playerid, checkpointid, true);
        EnabledPlayerCPDestoy(playerid, checkpointid, true);

        Streamer_Update(playerid, STREAMER_TYPE_CP);
        SetPVarInt(playerid, "pizza_house", random_house);
        SendClientMessage(playerid, -1, ""COLOR_GREEN"Отправляйтесь к следующему клиенту "COLOR_RED"(красная метка на миникарте)");
    } else {
        DeletePVar(playerid, "pizza_house");
        new checkpointid = CreatePlayerCP(playerid, 2125.2842, -1805.0114, 13.1270, "@_PlayerLoadPizza");
        SetPlayerCPGlobal(playerid, checkpointid, true);
        EnabledPlayerCPDestoy(playerid, checkpointid, true);

        SendClientMessage(playerid, -1, ""COLOR_GREEN"Отправляйтесь за новой порцией пиццы "COLOR_RED"(красная метка на миникарте)");
    }
}

ptask CheckPizza[1000](playerid) 
{
    if(PlayerJobPizza{playerid} == true) {
        new 
            player_house = GetPVarInt(playerid, "pizza_house");

        new 
            Float: distance = GetPlayerDistanceFromPoint(playerid, HouseInfo[player_house][hEntrancex], HouseInfo[player_house][hEntrancey], HouseInfo[player_house][hEntrancez]);

        format(small_string, sizeof(small_string), "~w~DISTANCE: ~g~~h~~h~%.01f", distance);
        PlayerTextDrawSetString(playerid, PlayerPizzaTD[playerid], small_string);
        PlayerTextDrawShow(playerid, PlayerPizzaTD[playerid]);

        if(distance < 30 && GetPVarInt(playerid, "show_pizza_info") == 0) {
            SetPVarInt(playerid, "show_pizza_info", 1);
            ShowPlayerDialog(playerid, 
                DIALOG_INFO, DIALOG_STYLE_MSGBOX, 
                ""COLOR_BLUE"Работа: "COLOR_ORANGE"доставщик пиццы", 
                ""COLOR_WHITE"Припаркуйтесь как можно ближе к дому и встаньте на "COLOR_RED"красный маркер", 
                "Закрыть", ""
            );
        }

        for(new i = 0; i < sizeof(PizzaTD); i++) {
            TextDrawShowForPlayer(playerid, PizzaTD[i]);
        }
        SetPVarInt(playerid, "pizza_total_time", GetPVarInt(playerid, "pizza_total_time") + 1);
    } else {
        for(new i = 0; i < sizeof(PizzaTD); i++) {
            TextDrawHideForPlayer(playerid, PizzaTD[i]);
        }
        PlayerTextDrawHide(playerid, PlayerPizzaTD[playerid]);
        SetPVarInt(playerid, "hiden_td_pizza", 1);
    }
}