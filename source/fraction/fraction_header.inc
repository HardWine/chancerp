#if defined G_fraction_header_included
    #endinput
#endif

#define G_fraction_header_included

#define Fraction.                           Fraction__
#define INVALID_FRACTION_ID                 (-1)        // Неверный ID фракции (AUTOINCREMENT)
#define INVALID_FRACTION_NUMBER             (-1)        // Неверный ID фракции

#define GetFractionTitle(%0)                FractionTitle[%0]
#define GetPlayerLeader(%0)                  Player.Leader[%0]
#define GetFractionLeader(%0)               Fraction[%0][E_FRACTION_LEADER_ID]

enum
    E_FRACTION_INFO {
        E_FRACTION_ID,                                  /* ID фракции (AUTOINCREMENT из базы данных) */
        E_FRACTION_NUMBER,                              /* Номер фракции */
        E_FRACTION_LEADER_ID,                           /* ID аккаунта лидера; INVALID_ACCOUNT_ID в случае отсутсвия */
        E_FRACTION_LEADER_NAME[MAX_PLAYER_NAME],        /* Ник лидера; "Отсутсвует" в случае если нет лидера */
        E_FRACTION_AUTO_INVITE,                         /* Система автоинвайта (0 - выключена, 1 - включена) */
        E_FRACTION_AUTO_RANG,                           /* Система автоповышения (0 - выключена, 1 - включена) */
        E_FRACTION_DATE_DESTINATION[20],                /* Дата назначения лидера */
    };

new
    const NULL_FRACTION_INFO[E_FRACTION_INFO] = {
        INVALID_FRACTION_ID,                            /* E_FRACTION_ID */
        INVALID_FRACTION_NUMBER,                        /* E_FRACTION_NUMBER */
        INVALID_ACCOUNT_ID,                             /* E_FRACTION_LEADER_ID */
        "Отсутсвует",                                   /* E_FRACTION_LEADER_NAME */
        1,                                              /* E_FRACTION_AUTO_INVITE */
        1,                                              /* E_FRACTION_AUTO_RANG */
        "-"                                             /* E_FRACTION_DATE_DESTINATION */
    };

new
    Fraction[MAX_FRACTION+1][E_FRACTION_INFO],
    //Logger: fractionlog,
    Player.Leader[MAX_PLAYERS] = {INVALID_FRACTION_ID, ...};