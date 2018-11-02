#if defined house_header_included
	#endinput
#endif

#define house_header_included

#define MAX_HOUSE 									(690) // Максимальное кол-во домов
#define INVALID_HOUSE_ID							(-1) // Неверный ID дома
#define MAX_HOUSE_CLASS 							(6) // Максимальное кол-во классов дома
#define MAX_HOUSE_CLASS_TITLE 						(10) // Максимальная длина названия класса дома
#define E_STREAMER_TYPE_HOUSE 						(451) // Тип для дома
#define E_STREAMER_TYPE_HOUSE_CLASS 				(452) // Тип для класса дома
#define HOUSE_VIEW_TIME 							(10) // Время просмотра дома (секунды)


enum 
	E_HOUSE_INFO {
		E_HOUSE_ID,
		Float: E_HOUSE_X,
		Float: E_HOUSE_Y,
		Float: E_HOUSE_Z,
		E_HOUSE_PRICE,
		E_HOUSE_OWNER,
		E_HOUSE_OWNER_NAME[MAX_PLAYER_NAME],
		E_HOUSE_RENT_DAY,
		E_HOUSE_CLASS,
		Float: E_HOUSE_CAR_X,
		Float: E_HOUSE_CAR_Y,
		Float: E_HOUSE_CAR_Z,
		Float: E_HOUSE_CAR_ANGLE,
		E_HOUSE_CLOSSED,
		E_HOUSE_MED_CHEST,
		E_HOUSE_PICKUID,
		E_HOUSE_ZONEID,
		Text3D: E_HOUSE_LABELID,
		E_HOUSE_MAPICON_ID
	};

enum
	E_HOUSE_CLASS_INFO {
		E_HOUSE_CLASS_TITLE[MAX_HOUSE_CLASS_TITLE],
		E_HOUSE_CLASS_INTER,
		Float: E_HOUSE_CLASS_X,
		Float: E_HOUSE_CLASS_Y,
		Float: E_HOUSE_CLASS_Z,
		Float: E_HOUSE_CLASS_TP_X,
		Float: E_HOUSE_CLASS_TP_Y,
		Float: E_HOUSE_CLASS_TP_Z,
		Float: E_HOUSE_CLASS_TP_ANGLE,
		E_HOUSE_CLASS_PICKUPID,
		E_HOUSE_CLASS_ZONEID
	};

new 
	HouseInfo[MAX_HOUSE][E_HOUSE_INFO];

new
	Player.House[MAX_PLAYERS],
	Player.EnterHouse[MAX_PLAYERS],
	Player.LinkHouseID[MAX_PLAYERS],
	Player.ViemTime[MAX_PLAYERS char];

new 
	House.Class[MAX_HOUSE_CLASS][E_HOUSE_CLASS_INFO] = {
		{"Эконом", 2, 1691.0641, -2665.7048, 13.5869, 1689.2965, -2665.4661, 13.5869, 90.0000, INVALID_PICKUP_ID, INVALID_ZONE_ID},
		{"Доступный", 3, 1691.0641, -2665.7048, 13.5869, 1689.2965, -2665.4661, 13.5869, 90.0000, INVALID_PICKUP_ID, INVALID_ZONE_ID},
		{"Средний", 4, 2108.8228, -2403.1648, 13.5847, 2108.5801, -2400.9365, 13.5847, 360.0000, INVALID_PICKUP_ID, INVALID_ZONE_ID},
		{"Элитный", 5, 1826.4791, -2676.6099, 13.6351, 1826.5156, -2674.4048, 13.6318, 360.0000, INVALID_PICKUP_ID, INVALID_ZONE_ID},
		{"Премиум", 6, 1826.4791, -2676.6099, 13.6351, 1826.5156, -2674.4048, 13.6318, 360.0000, INVALID_PICKUP_ID, INVALID_ZONE_ID},
		{"Люкс", 7, 1877.5209, -2673.4766, 13.6030, 1877.5579, -2671.2019, 13.5931, 360.0000, INVALID_PICKUP_ID, INVALID_ZONE_ID}
	};