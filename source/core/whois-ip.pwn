#include <YSI_Coding\y_hooks>

// Максимальная длина названия континента
#if !defined MAX_LENGTH_CONTINENT
    #define MAX_LENGTH_CONTINENT                48
#endif

// Максимальная длина названия страны
#if !defined MAX_LENGTH_COUNTRY
    #define MAX_LENGTH_COUNTRY                  64
#endif

// Максимальная длина названия региона
#if !defined MAX_LENGTH_REGION_NAME
    #define MAX_LENGTH_REGION_NAME              48
#endif

// Максимальная длина названия города
#if !defined MAX_LENGTH_CITY
    #define MAX_LENGTH_CITY                     48
#endif

// Максимальная длина названия часового пояса
#if !defined MAX_LENGTH_TIMEZONE
    #define MAX_LENGTH_TIMEZONE                 48
#endif

// Максимальная длина названия ISP
#if !defined MAX_LENGTH_ISP
    #define MAX_LENGTH_ISP                      64
#endif

// Максимальная длина названия провайдера
#if !defined MAX_LENGTH_ORG
    #define MAX_LENGTH_ORG                      128
#endif

// Максимальная длина названия AS
#if !defined MAX_LENGTH_AS
    #define MAX_LENGTH_AS                       64
#endif

// Максимальная длина названия REVERSE
#if !defined MAX_LENGTH_REVERSE
    #define MAX_LENGTH_REVERSE                  64
#endif

// Максимальная длина IP адреса
#if !defined MAX_LENGTH_IP
    #define MAX_LENGTH_IP                       16
#endif

// Максимальная длина IP адреса
#if !defined INVALID_SESSION_ID
    #define INVALID_SESSION_ID                  -1
#endif

enum E_IP_INFO 
{
    E_SESSION_ID,
    E_IP[MAX_LENGTH_IP],
    E_CONTINENT[MAX_LENGTH_CONTINENT],
    E_COUNTRY[MAX_LENGTH_COUNTRY],
    E_REGION_NAME[MAX_LENGTH_REGION_NAME],
    E_CITY[MAX_LENGTH_CITY],
    Float: E_LAT,
    Float: E_LON,
    E_TIMEZONE[MAX_LENGTH_TIMEZONE],
    E_ISP[MAX_LENGTH_ISP],
    E_ORG[MAX_LENGTH_ORG],
    E_AS[MAX_LENGTH_AS],
    E_REVERSE[MAX_LENGTH_REVERSE],
    bool: E_IS_MOBILE,
    bool: E_IS_PROXY,
    bool: E_IS_STATUS
};

static const NULL_PlayerIPInfo[E_IP_INFO] =
{
    /* E_SESSION_ID */      INVALID_SESSION_ID,
    /* E_IP */              "0.0.0.0",
    /* E_CONTINENT */       "-",
    /* E_COUNTRY */         "-",
    /* E_REGION_NAME */     "-",
    /* E_CITY */            "-",
    /* E_LAT */             0.00,
    /* E_LON */             0.00,
    /* E_TIMEZONE */        "-",
    /* E_ISP */             "-",
    /* E_ORG */             "-",
    /* E_AS */              "-",
    /* E_REVERSE */         "-",
    /* E_IS_MOBILE */       false, 
    /* E_IS_PROXY */        false,
    /* E_IS_STATUS */       false
};

new PlayerIPInfo[MAX_PLAYERS][E_IP_INFO];

hook OnPlayerConnect(const playerid)
{
    PlayerIPInfo[playerid] = NULL_PlayerIPInfo;
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerAuthorization(const playerid)
{
    // GetPlayerIPInfo(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerGameQuit(const playerid)
{
    // Если у игрока сохранен insert_id сессии
    if(PlayerIPInfo[playerid][E_SESSION_ID] == INVALID_SESSION_ID)
    {
        new name[MAX_PLAYER_NAME + 1];
        GetPlayerName(playerid, name, MAX_PLAYER_NAME);
        printf("Попытка сохранения невалидной сессии %i", PlayerIPInfo[playerid][E_SESSION_ID], playerid, name);
        return Y_HOOKS_CONTINUE_RETURN_1;
    }

    // Устанавливаем дату окончания сессии на текущие время
    mysql_format(database, small_string, sizeof(small_string), "UPDATE `player_log.session` SET `TimeEnd` = CURRENT_TIMESTAMP() WHERE ID = %i LIMIT 1", PlayerIPInfo[playerid][E_SESSION_ID]);
    mysql_pquery(database, small_string);

    PlayerIPInfo[playerid] = NULL_PlayerIPInfo;
    return Y_HOOKS_CONTINUE_RETURN_1;
}

forward GetPlayerIPInfo(const playerid);
public GetPlayerIPInfo(const playerid) {
    GetPlayerIp(playerid, PlayerIPInfo[playerid][E_IP], MAX_LENGTH_IP);

    if(strcmp(PlayerIPInfo[playerid][E_IP], "127.0.0.1", false) == 0)
    {
        new name[MAX_PLAYER_NAME + 1];
        GetPlayerName(playerid, name, MAX_PLAYER_NAME);
        printf("Попытка получения информации о локальном IP (name = %s; playerid = %i)", name, playerid);
        
        strmid(PlayerIPInfo[playerid][E_IP], "2.132.85.95", 0, strlen("2.132.85.95"));
    }


    format(big_string, sizeof(big_string), "www.ip-api.com/csv/%s?fields=status,continent,country,regionName,city,lat,lon,timezone,isp,org,as,reverse,mobile,proxy&lang=ru/", PlayerIPInfo[playerid][E_IP]);
    
    HTTP(playerid, HTTP_GET, big_string, "", "OnGetIPWhois");
    return 1;
}

forward OnGetIPWhois(index, response_code, data[]); 
public OnGetIPWhois(index, response_code, data[])
{
    // 200 код означает, что запрос выполнен 
    if(response_code == 200)
    {
        // временные переменные, необходимы для обработки возвращаемых данных
        // и дальнейшей их конвертации, так например запрос возвращает false строкой 
        // вместо нуля, запись в interger уже не пройде. Нужна резервная строка
        // которая примет bool значение как string и в дальнейшем его уже конвертировать

        new status_query[16];
        new temp_bool_proxy[7];
        new temp_bool_mobile[7];

        if(sscanf(data, "p<,>s[32]s[" #MAX_LENGTH_CONTINENT "]s[" #MAX_LENGTH_COUNTRY "]s[" #MAX_LENGTH_REGION_NAME "]s[" #MAX_LENGTH_CITY "]ffs[" #MAX_LENGTH_TIMEZONE "]s[" #MAX_LENGTH_ISP "]s[" #MAX_LENGTH_ORG "]s[" #MAX_LENGTH_AS "]s[" #MAX_LENGTH_REVERSE "]s[7]s[7]",
            status_query,
            PlayerIPInfo[index][E_CONTINENT],
            PlayerIPInfo[index][E_COUNTRY],
            PlayerIPInfo[index][E_REGION_NAME],
            PlayerIPInfo[index][E_CITY],
            PlayerIPInfo[index][E_LAT],
            PlayerIPInfo[index][E_LON],
            PlayerIPInfo[index][E_TIMEZONE],
            PlayerIPInfo[index][E_ISP],
            PlayerIPInfo[index][E_ORG],
            PlayerIPInfo[index][E_AS],
            PlayerIPInfo[index][E_REVERSE],
            temp_bool_mobile,
            temp_bool_proxy
        )) {
            print("[OnGetIPWhois] Ошибка в обработке запроса");
            return 1;
        }

        // В status_query должно записаться значение success если запрос выполнен успешно
        if(strcmp(status_query, "success", false) == 0)
        {
            // Проверка и конверацтия мобильного телефона
            if(strcmp(temp_bool_mobile, "false", false, strlen("false")) == 0)
            {
                PlayerIPInfo[index][E_IS_MOBILE] = false;
            }
            else
            {
                PlayerIPInfo[index][E_IS_MOBILE] = true;
            }
            
            // Проверка и конверацтия использования прокси
            if(strcmp(temp_bool_proxy, "false", false, strlen("false")) == 0)
            {
                PlayerIPInfo[index][E_IS_PROXY] = false;
            }
            else
            {
                PlayerIPInfo[index][E_IS_PROXY] = true;

                format(small_string, sizeof(small_string), ""COLOR_WHITE"[A] Внимание. Игрок "COLOR_GREEN"%s(%i)"COLOR_WHITE" использует подключение к серверу через прокси", PlayerInfo[index][pName], index);
                SendAdminMessage(-1, small_string);
            }
            
            // E_IS_STATUS в true говорит о полной иницализации данными массив
            PlayerIPInfo[index][E_IS_STATUS] = true;

            // Формирования отправки запроса в логирование сессий
            mysql_format(database, 
                huge_string, sizeof(huge_string), 
                "INSERT INTO `player_log.session`(`PlayerID`, `IP`, `Continent`, `Country`, `Region`, `City`, `Lat`, `Lon`, `Timezone`, `ISP`, `Org`, `AS`, `Reverse`, `Mobile`, `Proxy`, `TimeStart`) VALUES (%i, '%e', '%e', '%e', '%e', '%e', %f, %f, '%e', '%e', '%e', '%e', '%e', %i, %i, CURRENT_TIMESTAMP())", 
                    GetPlayerAccountID(index),
                    PlayerIPInfo[index][E_IP],
                    PlayerIPInfo[index][E_CONTINENT],
                    PlayerIPInfo[index][E_COUNTRY],
                    PlayerIPInfo[index][E_REGION_NAME],
                    PlayerIPInfo[index][E_CITY],
                    PlayerIPInfo[index][E_LAT],
                    PlayerIPInfo[index][E_LON],
                    PlayerIPInfo[index][E_TIMEZONE],
                    PlayerIPInfo[index][E_ISP],
                    PlayerIPInfo[index][E_ORG],
                    PlayerIPInfo[index][E_AS],
                    PlayerIPInfo[index][E_REVERSE],
                    PlayerIPInfo[index][E_IS_MOBILE],
                    PlayerIPInfo[index][E_IS_PROXY]
            );
            mysql_pquery(database, huge_string, "@_CreatePlayerSession", "i", index);
        }
    }
    else
    {
        printf("OnGetIPWhois response_code = %i, data = %s",  response_code, data);
    }
    return 1;
} 

CMD:whois(playerid, params[])
{
    if(GetPlayerAdminLevel(playerid) >= 5)
    {
        new targetid;
        if(sscanf(params, "r", targetid))
        {
            SendClientMessage(playerid, -1, "Используйте: /whois [ID Игрока]");
            return 0;
        }

        if(targetid == INVALID_PLAYER_ID)
        {
            SendClientMessage(playerid, -1, "Указан неверный ID игрока");
            return 0;
        }

        if(PlayerIPInfo[targetid][E_IS_STATUS] != true)
        {
            SendClientMessage(playerid, -1, "В данный момент данные о IP адресе игрока недоступны. Выполняется попытка их получения");
            SendClientMessage(playerid, -1, "Введите эту команду еще раз, через несколько секунд");
            GetPlayerIPInfo(targetid);
            return 0;
        }

        format(huge_string, sizeof(huge_string), 
            "Параметр\tЗначение\n\
                IP\t"COLOR_GREEN"%s\n\
                Cтрана\t"COLOR_GREEN"%s\n\
                Континент\t"COLOR_GREEN"%s\n\
                Регион\t"COLOR_GREEN"%s\n\
                Город\t"COLOR_GREEN"%s\n\
                Долгота\t"COLOR_GREEN"%f\n\
                Широта\t"COLOR_GREEN"%f\n\
                Временная зона\t"COLOR_GREEN"%s\n\
                ISP\t"COLOR_GREEN"%s\n\
                Организация\t"COLOR_GREEN"%s\n\
                AS\t"COLOR_GREEN"%s\n\
                Reverse\t"COLOR_GREEN"%s\n\
                Мобильный IP\t%s\n\
                Использование прокси\t%s",

                PlayerIPInfo[targetid][E_IP],
                PlayerIPInfo[targetid][E_CONTINENT],
                PlayerIPInfo[targetid][E_COUNTRY],
                PlayerIPInfo[targetid][E_REGION_NAME],
                PlayerIPInfo[targetid][E_CITY],
                PlayerIPInfo[targetid][E_LON],
                PlayerIPInfo[targetid][E_LAT],
                PlayerIPInfo[targetid][E_TIMEZONE],
                PlayerIPInfo[targetid][E_ISP],
                PlayerIPInfo[targetid][E_ORG],
                PlayerIPInfo[targetid][E_AS],
                PlayerIPInfo[targetid][E_REVERSE],
                (PlayerIPInfo[targetid][E_IS_MOBILE] == true) ? (""COLOR_GREEN"Да") : (""COLOR_ORANGE"Нет"),
                (PlayerIPInfo[targetid][E_IS_PROXY] == true) ? (""COLOR_ORANGE"Используется") : (""COLOR_GREEN"Не используется")
        );
        format(small_string, sizeof(small_string), ""COLOR_BLUE"Информация об IP: "COLOR_ORANGE"%s (%s)", PlayerIPInfo[targetid][E_IP], PlayerInfo[playerid][pName]);
        ShowPlayerDialog(playerid, DIALOG_INFO, DIALOG_STYLE_TABLIST_HEADERS, small_string, huge_string, "Закрыть", "");
        return 1;
    }
    return 0;
}

@_CreatePlayerSession(const playerid);
@_CreatePlayerSession(const playerid) {
    // Получаем id только, что созданной сессии
    PlayerIPInfo[playerid][E_SESSION_ID] = cache_insert_id();
}