#if defined _saloons_included
	#endinput
#endif
#define _saloons_included

#define MAX_CAR_AUTOSALEE                   87

new Saloon[4];
new SALOON_CARS[2];
new SellCar;

enum
    autosalee__ {
        AS_ModelID,
        AS_Score,
        AS_Title[90]
    };

static const
    AutoSalee[MAX_CAR_AUTOSALEE][autosalee__] = {
        // Bikes
        {509, 350, "Такой был у каждого в детстве"},
        {481, 500, "Парни в скейтпарке на нем чудеса творят"},
        {510, 750, "Самый быстрый велосипед (но это не точно)"},
        {462, 1000, "На него даже права не нужны!"},
        {586, 5000, "Классический турестический мотоцикл"},
        {471, 6000, "Хотите выделиться? Купите Quad!"},
        {468, 12000, "Лучший байк для мотокросса, проедет везде"},
        {581, 25000, "По-своему уникален."},
        {521, 30000, "Очень мощный, но тормоза не очень..."},
        {461, 45000, "Эталон в дизайне и по скорости"},
        {463, 75000, "Легенда мотостроения"},
        {522, 125000, "Он однозначно того стоит (не забудьте  надеть шлем)"},
        // Saloons [Бюджет]
		{605, 1000, "Возраст автомобиля неизвестен"},
		{604, 2000, "Да, она заводится"},
        {410, 3000, "Двухдверный компакт или ящик на колесах"},
        {526, 3150, "Простой и не слишком стремный"},
        {527, 3300, "Отличный автомобиль для студента"},
        {401, 3500, "Неплохой вид, но ходовые качества.."},
        {436, 4000, "Внешне схож с Manana, но ездит нормально"},
        {474, 4300, "Основан на классике 40/50-х годов"},
        {491, 4450, "Двухместный купе 77 года выпуска"},
        {542, 4900, "Классический маслкар"},
        {419, 5000, "Тяжелое двухдверное купе"},
        {549, 5200, "Популярный среди подростков маслкар"},
        {466, 5750, "Седан, выполненый в стиле 60-х годов"},
        {467, 6000, "Остатки кокаина на приборке и кассеты из 80-х в подарок!"},
        {547, 6500, "Один из лучших седанов. Серьезно"},
        {492, 7000, "Гангстерский стиль и легкое управление"},
        {516, 7400, "Очень бойкий седан"},
        {585, 7500, "Прочное но не сильно выдающееся авто"},
		{517, 7600, "Почти лоурайд"},
		{518, 7750, "Выглядит круто, но звук у него.."},
		{546, 7800, "Отличный гражданский автомобиль"},
		{540, 8000, "Немецкое качество."},
		{551, 8500, "Представительский класс для начинающих"},
		{529, 9000, "Стильный бьюик прямо из 80-х!"},
		//Saloons [Средние]
		{426, 10000, "Автомобиль на все случаи жизни"},
		{507, 13500, "Быстрый и прочный (подойдет для перестрелок)"},
		{405, 14000, "Идеальный седан"},
		{550, 15000, "Выглядит слишком шикарно для своей цены"},
		{421, 16500, "На таком ездит сам мэр"},
		{445, 17000, "Качество на десятки лет"},
		{580, 20000, "Вас будут бояться."},
		//Convertibles [Кабриолеты]
		{439, 5500, "Доступный и достойный"},
		{533, 16000, "Для бойких парней"},
		{555, 18000, "Спортивная классика"},
		{480, 32000, "Легендарный дизайн"},
		//Lowriders [Лоурайды]
		{576, 5000, "Плавные изгибы и хвостовые плавники - Торнадо"},
		{575, 8200, "Классический атрибут сутенера"},
		{412, 8000, "Длинный и эффектный лоурайдер"},
		{536, 8900, "Классика так любимая месиканцами с El Corona"},
		{567, 9900, "Всеми любимая импала. Лоурайд - легенда."},
		{534, 12000, "Вас начнут замечать на дорогах"},
		{566, 13500, "Возьми с собой Tec-9 и корешей"},
		{535, 20000, "Увеличит уровень вашей сексуальности"},
		// Station Wagons [Универсалы]
		{404, 3500, "Универсал 60-х годов. У моего деда такой"},
		{479, 4200, "Типичный универсал 80-х годов"},
		{482, 7000, "Отличное решение для вашей семьи (или ОПГ)"},
		{458, 12000, "Семья будет в восторге!"},
		{561, 25000, "Спортивный универсал"},
		//Sport [Спортивные]
		{602, 20000, "Почувствуй мощь V6 в этой легкой крошке"},
		{589, 18500, "Отлтчный спортивный хэтчбэк"},
		{475, 14800, "Мощная классика"},
		{496, 16000, "Неизменный стиль"},
		{587, 21000, "Прямиком из Европы"},
		{603, 23000, "Действительно как феникс"},
		{477, 26000, "Вы только взгляните на его фары"},
		{429, 27000, "Любая девушка будет от нее без ума"},
		{565, 25000, "Небольшой суперкар с прекрасной подвеской"},
		{558, 28000, "Пусть ваши враги вдыхают урановую пыль!"},
		{560, 45000, "Здесь установлен мощный турбо-двигатель"},
		{562, 40000, "Дрифт - её стихия"},
		{559, 29900, "Переднеприводная ракета"},
		{506, 35000, "Мощный V8 не даст вам заскучать!"},
		{402, 50000, "Мощный американский маслкар"},
		{541, 75000, "Её форма напоминает пулю, а звук - выстрел"},
		{415, 85000, "Лучшая управляемость и спорт в одном флаконе"},
		{451, 90000, "Воплощение роскоши"},
		{411, 100000, "Адская скорость"},
		{502, 120000, "Для настоящих ценителей спортивных гонок"},
		{495, 145000, "Стань королем любой вершины"},
		//Off Road
		{400, 5000, "Четерехдверный внедорожник с полным приводом"},
		{500, 8000, "Прекрасный внедорожник для туриста"},
		{579, 18000, "Внедорожник премиум класса"},
		// Industrial
		{600, 4400, "Практичный индустриальный пикап"},
		{422, 3500, "Двудверный шустрый пикапчик"},
		{554, 10000, "Автомобиль для крепких мужчин"}
};
forward Salon_OnPlayerStateChange(playerid, newstate, oldstate);
public Salon_OnPlayerStateChange(playerid, newstate, oldstate)
{
    new
        vehicleid = GetPlayerVehicleID(playerid),
        modelid = GetVehicleModel(vehicleid);
    if(newstate == PLAYER_STATE_DRIVER) {
    	if(vehicleid >= SALOON_CARS[0] && vehicleid <= SALOON_CARS[1]) {
		    for(new i = 0; i < MAX_CAR_AUTOSALEE; i++) {
		        if(AutoSalee[i][AS_ModelID] == modelid) {
		            new price = AutoSalee[i][AS_Score];
		            new model_name[20];
		            model_name = GetVehicleText(modelid);
	                format(small_string, sizeof(small_string),
	                    ""COLOR_ORANGE"Транспортное средство: %s | Цена: %d",
							model_name,
							price
	                );
	                SendClientMessage(playerid, -1, small_string);
	                format(small_string, sizeof(small_string),
	                    ""COLOR_ORANGE"%s",
	                         AutoSalee[i][AS_Title]
	                );
	                SendClientMessage(playerid, -1, small_string);
	                RemovePlayerFromVehicle(playerid);
	                SetVehicleToRespawn(vehicleid);
	                SetPVarInt(playerid, "VehToBuy", modelid);
	                SetPVarInt(playerid, "PriceToBuy", price);
		        }
		    }
		}
		
	}
	return 1;
}
stock Saloon_OnGameModeInit() {

	SellCar = CreateDynamicCP(1027.9877,-1451.6542,13.3777,5,-1,-1,-1,25);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Продажа транспорта", -1, 1027.9877,-1451.6542,13.3777 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	Saloon[0] = CreateDynamicPickup(1274, 1, 2131.8633,-1151.2808,24.0653);
	CreateDynamicMapIcon(2131.8633,-1151.2808,24.0653, 55, -1, 0, -1, -1, 400.0);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Купить транспорт", -1, 2131.8633,-1151.2808,24.0653 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	Saloon[1] = CreateDynamicPickup(1274, 1, -1959.8765,304.1256,35.4739);
	CreateDynamicMapIcon(-1959.8765,304.1256,35.4739, 55, -1, 0, -1, -1, 400.0);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Купить транспорт", -1, -1959.8765,304.1256,35.4739 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	Saloon[2] = CreateDynamicPickup(1274, 1, -1657.5875,1210.2001,7.2500);
	CreateDynamicMapIcon(-1657.5875,1210.2001,7.2500, 55, -1, 0, -1, -1, 400.0);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Купить транспорт", -1, -1657.5875,1210.2001,7.2500 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	Saloon[3] = CreateDynamicPickup(1274, 1, 542.2120,-1293.9296,17.2422);
	CreateDynamicMapIcon(542.2120,-1293.9296,17.24220, 55, -1, 0, -1, -1, 400.0);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Купить транспорт", -1, 542.2120,-1293.9296,17.2422 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	new actor_wang;
	actor_wang = CreateActor(20, -1959.8492,305.9056,35.4739,180.2076);
	SetActorVirtualWorld(actor_wang, 0);

	new actor_otto;
	actor_otto = CreateActor(216, -1658.5497,1208.1904,7.2500,356.0861);
	SetActorVirtualWorld(actor_otto, 0);

	SALOON_CARS[0] = AddStaticVehicle(509, 2137.1001, -1143.4, 24.6, 60, -1, -1); //  (1)
	// Colt
	AddStaticVehicle(481, 2137, -1141.4, 24.8, 59.996, -1, -1); //  (2)
	AddStaticVehicle(510, 2137, -1139.5, 25, 59.996, -1, -1); //  (3)
	AddStaticVehicle(462, 2137, -1137.6, 25.2, 59.996, -1, -1); //  (4)
	AddStaticVehicle(586, 2137, -1135.6, 25.3, 59.996, -1, -1); //  (5)
	AddStaticVehicle(471, 2137, -1133.8, 25.3, 59.996, -1, -1); //  (6)
	AddStaticVehicle(468, 2137, -1132.2, 25.3, 59.996, -1, -1); //  (7)
	AddStaticVehicle(581, 2137, -1130.3, 25.3, 59.996, -1, -1); //  (8)
	AddStaticVehicle(463, -1956.1698,281.7359,40.5870,179.2479, -1, -1); //  (9)
	AddStaticVehicle(522, -1645.3682,1204.5085,13.2432,195.2122, -1, -1); //  (10)

	AddStaticVehicle(521, 2137, -1128.7, 25.2, 59.996, -1, -1); //  (12)
	AddStaticVehicle(461, 2137, -1127.2, 25.1, 59.996, -1, -1); //  (13)//461 521
	AddStaticVehicle(605, 2119.8999, -1154.8, 24, 314, -1, -1); //  (1)
	AddStaticVehicle(604, 2119.3999, -1148, 24.3, 313.995, -1, -1); //  (2)
	AddStaticVehicle(410, 2119.6001, -1139.9, 24.9, 313.995, -1, -1); //  (3)
	AddStaticVehicle(526, 2119.8, -1132.1, 25.3, 313.995, -1, -1); //  (4)
	AddStaticVehicle(527, 2120.2, -1125.3, 25.4, 313.995, -1, -1); //  (5)
	AddStaticVehicle(401, 2149.1001, -1138.3, 25.5, 270, -1, -1); //  (7)
	AddStaticVehicle(436, 2149, -1143.3, 24.9, 270, -1, -1); //  (8)
	AddStaticVehicle(474, 2148.8, -1148.3, 24.4, 270, -1, -1); //  (9)
	AddStaticVehicle(491, 2148.7, -1153, 23.8, 270, -1, -1); //  (10)
	AddStaticVehicle(542, 2148.7, -1157.3, 23.8, 270, -1, -1); //  (11)
	AddStaticVehicle(419, 2148.6001, -1161.69995, 23.8, 270, -1, -1); //  (12)
	AddStaticVehicle(549, 2148.6001, -1166.4, 23.8, 270, -1, -1); //  (13)
	AddStaticVehicle(466, 2148.5, -1171, 23.8, 270, -1, -1); //  (14)
	AddStaticVehicle(467, 2148.5, -1175.4, 23.8, 270, -1, -1); //  (15)
	AddStaticVehicle(547, 2148.5, -1180.2, 23.8, 270, -1, -1); //  (16)
	AddStaticVehicle(492, 2148.3, -1185, 23.8, 270, -1, -1); //  (17)
	AddStaticVehicle(516, 2148.3999, -1189.7, 23.8, 270, -1, -1); //  (18)
	AddStaticVehicle(585, 2148.3999, -1194.3, 23.8, 270, -1, -1); //  (20)
	AddStaticVehicle(517, 2148.4004, -1198.9004, 23.8, 270, -1, -1); //  (21)
	AddStaticVehicle(518, 2160.8999, -1197.2, 23.8, 90, -1, -1); //  (22)
	AddStaticVehicle(546, 2160.8999, -1192.1, 23.8, 90, -1, -1); //  (24)
	AddStaticVehicle(540, 2160.8999, -1187.3, 23.8, 90, -1, -1); //  (25)
	AddStaticVehicle(551, 2161, -1182.4, 23.8, 90, -1, -1); //  (26)
	AddStaticVehicle(529, 2161, -1177.6, 23.8, 90, -1, -1); //  (27)
	AddStaticVehicle(576, 2161, -1173, 23.8, 90, -1, -1); //  (28)
	AddStaticVehicle(575, 2161, -1168, 23.8, 90, -1, -1); //  (29)
	AddStaticVehicle(412, 2161, -1163.2, 23.8, 90, -1, -1); //  (30)
	AddStaticVehicle(536, 2161, -1158, 23.8, 90, -1, -1); //  (31)
	AddStaticVehicle(567, 2161.1001, -1153, 23.8, 90, -1, -1); //  (32)
	AddStaticVehicle(534, 2161.1001, -1148.4, 24.3, 90, -1, -1); //  (33)
	// Grotti
	AddStaticVehicle(426, 538.29999, -1289.9, 17.2, 328, -1, -1); //(1)
	AddStaticVehicle(507, 533.29999, -1289.7, 17.2, 327.997, -1, -1); //(2)
	AddStaticVehicle(405, 528.40002, -1289.5, 17.2, 327.997, -1, -1); //(3)
	AddStaticVehicle(550, 523.29999, -1290.1, 17.2, 327.997, -1, -1); //(4)
	AddStaticVehicle(482, 548.59998, -1290, 17.2, 31.997, -1, -1); //(5)
	AddStaticVehicle(445, 553.20001, -1289.5, 17.2, 31.992, -1, -1); //(6)
	AddStaticVehicle(439, 557.70001, -1289.5, 17.2, 31.992, -1, -1); //(7)
	AddStaticVehicle(535, 562, -1289.2, 17.2, 31.992, -1, -1); //(8)
	AddStaticVehicle(400, 552.79999, -1264.4, 17.2, 215.992, -1, -1); //(9)
	AddStaticVehicle(500, 549.09998, -1267.2, 17.2, 215.991, -1, -1); //(10)
	AddStaticVehicle(404, 544.90002, -1270.4, 17.2, 215.991, -1, -1); //(11)
	AddStaticVehicle(600, 540.5, -1273.9, 17.2, 215.991, -1, -1); //(12)
	AddStaticVehicle(479, 535.79999, -1277.5, 17.2, 215.991, -1, -1); //(13)
	AddStaticVehicle(554, 531.6271,-1280.3740,16.8148,211.5015, -1, -1); // (2)
	// Wang 
	AddStaticVehicle(579, -1956.8749,258.5778,35.3066,42.2316, -1, -1); // (1)
	AddStaticVehicle(458, -1947, 265.29999, 35.4, 90, -1, -1); // (3)
	AddStaticVehicle(561, -1947, 261.60001, 35.4, 90, -1, -1); // (4)
	AddStaticVehicle(580, -1955.9, 264.10001, 35.4, 42, -1, -1);//(Voodoo) (5)
	AddStaticVehicle(533, -1955.9, 272.20001, 35.4, 41.995, -1, -1);//(Voodoo) (6)
	AddStaticVehicle(480, -1955.9, 298.70001, 35.4, 127.995, -1, -1);//(Voodoo) (7)
	AddStaticVehicle(602, -1955.9, 292.70001, 35.4, 127.991, -1, -1);//(Voodoo) (8)
	AddStaticVehicle(589, -1955.9, 279.60001, 35.4, 41.995, -1, -1);//(Voodoo) (9)
	AddStaticVehicle(475, -1955.3, 301.5, 41, 142, -1, -1); //(Voodoo) (10)
	AddStaticVehicle(496, -1955.3, 295.20001, 41, 141.998, -1, -1); //(Voodoo) (11)
	AddStaticVehicle(421, -1955.3, 289.79999, 41, 141.998, -1, -1); //(Voodoo) (12)
	AddStaticVehicle(603, -1956.5, 258.10001, 41, 0, -1, -1); //(Voodoo) (13)
	AddStaticVehicle(477, -1952.6, 257.70001, 41, 0, -1, -1); //(Voodoo) (14)
	AddStaticVehicle(429, -1947.4, 261, 41, 50, -1, -1); //(Voodoo) (15)
	AddStaticVehicle(565, -1947.1, 274.39999, 41, 90, -1, -1); //(Voodoo) (16)
	AddStaticVehicle(558, -1947, 271, 41, 90, -1, -1); //(Voodoo) (17)
	AddStaticVehicle(587, -1946.9, 267.20001, 41, 90, -1, -1); //(Voodoo) (18)

	// OTTO
	AddStaticVehicle(495, -1666.3, 1209, 7.2, 316, -1, -1); //(Voodoo) (27)
	AddStaticVehicle(502, -1665.8, 1215.2, 7.2, 244, -1, -1); //(Voodoo) (28)
	AddStaticVehicle(411, -1652, 1212.3, 7.2, 229.995, -1, -1); //(Voodoo) (29)
	AddStaticVehicle(451, -1661.6, 1218.6, 13.6, 0,-1, -1); //(Voodoo) (30)
	AddStaticVehicle(415, -1657.8, 1215.5, 13.6, 0,-1, -1); //(Voodoo) (31)
	AddStaticVehicle(541, -1653.9, 1213.4, 13.6, 0,-1, -1); //(Voodoo) (32)
	AddStaticVehicle(402, -1669.9, 1204.5, 13.6, 268, -1, -1); //(33)
	AddStaticVehicle(506, -1673.3, 1207.9, 13.6, 267.995, -1, -1); //(34)
	AddStaticVehicle(559, -1663.8, 1220.7, 21.1, 0, -1, -1);//(Voodoo) (35)
	AddStaticVehicle(562, -1660.8, 1218.1, 21.1, 0, -1, -1);//(Voodoo) (36)
	AddStaticVehicle(560, -1657.9, 1215.7, 21.1, 0, -1, -1);//(Voodoo) (37)
	SALOON_CARS[1] = AddStaticVehicle(566, 2161.2, -1143.9, 24.8, 90, -1, -1); //  (34)

	// Wang Object

	CreateDynamicObject(2626, -1959.9, 305.10001, 35, 0, 0, 0); // object (CJ_URB_COUNTER) (1)

	// Grotti door

	CreateDynamicObject(1569, 540.682800, -1294.348754, 16.242187, 0.000000, 0.000000, 0.000000, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(1569, 543.683837, -1294.348754, 16.242187, 0.000000, 0.000000, 180.000000, -1, -1, -1, 100.00, 100.00);

}
stock Saloon_OP_PickUpDynamicPickup(playerid, pickupid) {
	if(pickupid >= Saloon[0] && pickupid <= Saloon[3]) {
		if(GetPVarInt(playerid,"AntiFloodF") > gettime())	{ return false; }
		SetPVarInt(playerid,"AntiFloodF",gettime() + 5);
		new selectedcar = GetPVarInt(playerid, "VehToBuy");
		if(!selectedcar) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Сначала необходимо сесть за руль понравившегося автомобиля");
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если у Вас уже имеется транспорт, он будет заменен");
		new vehprice = GetPVarInt(playerid, "PriceToBuy");
		DeletePVar(playerid, "VehToBuy");
		DeletePVar(playerid, "PriceToBuy");
		if(CheckCash(playerid, vehprice) == false) return 1;
		Player.DownEXP(PlayerInfo[playerid][pID], vehprice, E_BUY_CAR, playerid);
		format(small_string, sizeof(small_string), "~r~-%d ~w~EXP", vehprice);
		GameTextForPlayer(playerid, small_string, 3000, 5);
		PlayerInfo[playerid][pCar] = selectedcar;
		SetPlayerInt(playerid, "Car", PlayerInfo[playerid][pCar]);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы приобрели новый транспорт");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Он появится у Вашего дома");
		PlayerInfo[playerid][pFreshPrice] = 2;
		SetPlayerInt(playerid, "FreshPrice", PlayerInfo[playerid][pFreshPrice]);
		//PlayerInfo[playerid][pMileage] = 0;
		//SetPlayerInt(playerid, "Mileage", PlayerInfo[playerid][pMileage]);
		return 1;
	}
	return 0;
}
stock Saloon_OnPlayerEnterDynamicCP(playerid, checkpointid) {
	if(checkpointid == SellCar) {
		if(GetPVarInt(playerid,"AntiFloodSs") > gettime()){ return 1; }
		SetPVarInt(playerid,"AntiFloodSs",gettime() + 3);
		new
        vehicleid = GetPlayerVehicleID(playerid),
        modelid = GetVehicleModel(vehicleid);
		if(vehicleid != caridhouse[playerid]) {
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Здесь можно продать свой транспорт.");
			return 1;
		}
		if(modelid == 509) return 1;
		if(PlayerInfo[playerid][pFreshPrice] < 2) {
			SendClientMessage(playerid, -1, "Продать транспорт, купленный до обновления невозможно");
			return 1;
		}
		for(new i = 0; i < MAX_CAR_AUTOSALEE; i++) {
		if(AutoSalee[i][AS_ModelID] == modelid) {
		if(GetPVarInt(playerid,"AntiFloodF") > gettime()){ return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Чтобы продать транспорт, снова возьмите чекпоинт"); }
		if(GetPVarInt(playerid, "Await") != 1) {
			SetPVarInt(playerid,"AntiFloodF",gettime() + 10);
			SetPVarInt(playerid, "Await", 1);
			return 1;
		}
		// new vehprice = AutoSalee[i][AS_Score]/(2);
		// if(PlayerInfo[playerid][pMileage] > 1500000) vehprice = AutoSalee[i][AS_Score]/(3);
		// if(PlayerInfo[playerid][pMileage] > 2000000) vehprice = AutoSalee[i][AS_Score]/(4);
		// if(PlayerInfo[playerid][pMileage] > 3000000) vehprice = AutoSalee[i][AS_Score]/(5);
		// if(PlayerInfo[playerid][pMileage] > 4000000) vehprice = AutoSalee[i][AS_Score]/(6);
		// if(PlayerInfo[playerid][pMileage] > 5000000) vehprice = AutoSalee[i][AS_Score]/(7);
		// if(PlayerInfo[playerid][pMileage] > 6000000) vehprice = AutoSalee[i][AS_Score]/(8);
		// if(PlayerInfo[playerid][pMileage] > 7000000) vehprice = AutoSalee[i][AS_Score]/(9);
		// if(PlayerInfo[playerid][pMileage] > 8000000) vehprice = AutoSalee[i][AS_Score]/(10);
		// if(PlayerInfo[playerid][pMileage] > 98000000) vehprice = AutoSalee[i][AS_Score]/(25);
		// if(PlayerInfo[playerid][pMileage] > 10000000) vehprice = AutoSalee[i][AS_Score]/(50);
		// Player.AddEXP(PlayerInfo[playerid][pID], vehprice, E_SELL_CAR_GOVERMENT, playerid);
		// format(small_string, sizeof(small_string), "~g~+%d ~w~EXP", vehprice);	
		// GameTextForPlayer(playerid, small_string, 3000, 5);
		// PlayerInfo[playerid][pCar] = 509;
		// SetPlayerInt(playerid, "Car", PlayerInfo[playerid][pCar]);
		// LoadCarPlayerId(playerid);
		// PlayerInfo[playerid][pMileage] = 0;
		// SetPlayerInt(playerid, "Mileage", PlayerInfo[playerid][pMileage]);
		// SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы продали свой транспорт");
		// return 1;
		}
		}
		return 1;
	}
	return 0;
}

#define YSI_TESTS

TestInit:fsdf() {
	printf("test");
}