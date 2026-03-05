#if defined family_header_included
    #endinput
#endif

#define family_header_included

#include <YSI-Include\YSI\YSI\y_hooks>

#define INVALID_FAMILY_ID               (-1)
#define INVALID_FAMILY_ROLE             (-1)
#define INVALID_FAMILY_COLOR             (-1)
#define MAX_FAMILY_TITLE                (32 + 1)
#define MAX_FAMILY_ROLE                 (3)
#define MAX_FAMILY_ROLE_TITLE           (17)
#define MAX_FAMILY_COLOR                (9)

enum
    E_PLAYER_FAMILY {
        E_ID,
        E_FAMILY_ID,
        E_TITLE[MAX_FAMILY_TITLE],
        E_COLOR,
        E_ROLE
    };

new NULL_PlayerFamily[E_PLAYER_FAMILY] = {
    /* E_ID */              INVALID_FAMILY_ID,
    /* E_FAMILY_ID */       INVALID_FAMILY_ID,
    /* E_TITLE */           "-",
    /* E_COLOR */           INVALID_FAMILY_COLOR,
    /* E_ROLE */            INVALID_FAMILY_ROLE
};

new
    Player.Family[MAX_PLAYERS][E_PLAYER_FAMILY];

new const
    FamilyRoly[MAX_FAMILY_ROLE][MAX_FAMILY_ROLE_TITLE] = {
        {"Член семьи"},
        {"Зам. главы семьи"},
        {"Глава семьи"}
    };

enum
    E_FAMILY_COLOR {
        E_TITLE[12],
        E_HEX[7]
    };

new
    const FamilyColor[MAX_FAMILY_COLOR][E_FAMILY_COLOR] = {
        {"Белый", "FFFFFF"},
        {"Синий", "4eb9e6"},
        {"Фиолетовый", "DD90FF"},
        {"Желтый", "F3FF02"},
        {"Зеленый", "6de64e"},
        {"Оранжевый", "FFAF00"},
        {"Розовый", "8FE47F"},
        {"Розовый", "8FE47F"},
        {"Персиковый", "e67b4e"}
    };