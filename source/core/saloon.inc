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

new
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
		{589, 18500, "Отличный спортивный хэтчбэк"},
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

	SALOON_CARS[0] = AddStaticVehicle(509, 2137.1001, -1143.4, 24.6, 60, rcol(), rcol()); //  (1)
	// Colt
	AddStaticVehicle(481, 2137, -1141.4, 24.8, 59.996, rcol(), rcol()); //  (2)
	AddStaticVehicle(510, 2137, -1139.5, 25, 59.996, rcol(), rcol()); //  (3)
	AddStaticVehicle(462, 2137, -1137.6, 25.2, 59.996, rcol(), rcol()); //  (4)
	AddStaticVehicle(586, 2137, -1135.6, 25.3, 59.996, rcol(), rcol()); //  (5)
	AddStaticVehicle(471, 2137, -1133.8, 25.3, 59.996, rcol(), rcol()); //  (6)
	AddStaticVehicle(468, 2137, -1132.2, 25.3, 59.996, rcol(), rcol()); //  (7)
	AddStaticVehicle(581, 2137, -1130.3, 25.3, 59.996, rcol(), rcol()); //  (8)
	AddStaticVehicle(463, -1956.1698,281.7359,40.5870,179.2479, rcol(), rcol()); //  (9)
	AddStaticVehicle(522, -1645.3682,1204.5085,13.2432,195.2122, rcol(), rcol()); //  (10)

	AddStaticVehicle(521, 2137, -1128.7, 25.2, 59.996, rcol(), rcol()); //  (12)
	AddStaticVehicle(461, 2137, -1127.2, 25.1, 59.996, rcol(), rcol()); //  (13)//461 521
	AddStaticVehicle(605, 2119.8999, -1154.8, 24, 314, rcol(), rcol()); //  (1)
	AddStaticVehicle(604, 2119.3999, -1148, 24.3, 313.995, rcol(), rcol()); //  (2)
	AddStaticVehicle(410, 2119.6001, -1139.9, 24.9, 313.995, rcol(), rcol()); //  (3)
	AddStaticVehicle(526, 2119.8, -1132.1, 25.3, 313.995, rcol(), rcol()); //  (4)
	AddStaticVehicle(527, 2120.2, -1125.3, 25.4, 313.995, rcol(), rcol()); //  (5)
	AddStaticVehicle(401, 2149.1001, -1138.3, 25.5, 270, rcol(), rcol()); //  (7)
	AddStaticVehicle(436, 2149, -1143.3, 24.9, 270, rcol(), rcol()); //  (8)
	AddStaticVehicle(474, 2148.8, -1148.3, 24.4, 270, rcol(), rcol()); //  (9)
	AddStaticVehicle(491, 2148.7, -1153, 23.8, 270, rcol(), rcol()); //  (10)
	AddStaticVehicle(542, 2148.7, -1157.3, 23.8, 270, rcol(), rcol()); //  (11)
	AddStaticVehicle(419, 2148.6001, -1161.69995, 23.8, 270, rcol(), rcol()); //  (12)
	AddStaticVehicle(549, 2148.6001, -1166.4, 23.8, 270, rcol(), rcol()); //  (13)
	AddStaticVehicle(466, 2148.5, -1171, 23.8, 270, rcol(), rcol()); //  (14)
	AddStaticVehicle(467, 2148.5, -1175.4, 23.8, 270, rcol(), rcol()); //  (15)
	AddStaticVehicle(547, 2148.5, -1180.2, 23.8, 270, rcol(), rcol()); //  (16)
	AddStaticVehicle(492, 2148.3, -1185, 23.8, 270, rcol(), rcol()); //  (17)
	AddStaticVehicle(516, 2148.3999, -1189.7, 23.8, 270, rcol(), rcol()); //  (18)
	AddStaticVehicle(585, 2148.3999, -1194.3, 23.8, 270, rcol(), rcol()); //  (20)
	AddStaticVehicle(517, 2148.4004, -1198.9004, 23.8, 270, rcol(), rcol()); //  (21)
	AddStaticVehicle(518, 2160.8999, -1197.2, 23.8, 90, rcol(), rcol()); //  (22)
	AddStaticVehicle(546, 2160.8999, -1192.1, 23.8, 90, rcol(), rcol()); //  (24)
	AddStaticVehicle(540, 2160.8999, -1187.3, 23.8, 90, rcol(), rcol()); //  (25)
	AddStaticVehicle(551, 2161, -1182.4, 23.8, 90, rcol(), rcol()); //  (26)
	AddStaticVehicle(529, 2161, -1177.6, 23.8, 90, rcol(), rcol()); //  (27)
	AddStaticVehicle(576, 2161, -1173, 23.8, 90, rcol(), rcol()); //  (28)
	AddStaticVehicle(575, 2161, -1168, 23.8, 90, rcol(), rcol()); //  (29)
	AddStaticVehicle(412, 2161, -1163.2, 23.8, 90, rcol(), rcol()); //  (30)
	AddStaticVehicle(536, 2161, -1158, 23.8, 90, rcol(), rcol()); //  (31)
	AddStaticVehicle(567, 2161.1001, -1153, 23.8, 90, rcol(), rcol()); //  (32)
	AddStaticVehicle(534, 2161.1001, -1148.4, 24.3, 90, rcol(), rcol()); //  (33)
	// Grotti
	AddStaticVehicle(426, 538.29999, -1289.9, 17.2, 328, rcol(), rcol()); //(1)
	AddStaticVehicle(507, 533.29999, -1289.7, 17.2, 327.997, rcol(), rcol()); //(2)
	AddStaticVehicle(405, 528.40002, -1289.5, 17.2, 327.997, rcol(), rcol()); //(3)
	AddStaticVehicle(550, 523.29999, -1290.1, 17.2, 327.997, rcol(), rcol()); //(4)
	AddStaticVehicle(482, 548.59998, -1290, 17.2, 31.997, rcol(), rcol()); //(5)
	AddStaticVehicle(445, 553.20001, -1289.5, 17.2, 31.992, rcol(), rcol()); //(6)
	AddStaticVehicle(439, 557.70001, -1289.5, 17.2, 31.992, rcol(), rcol()); //(7)
	AddStaticVehicle(535, 562, -1289.2, 17.2, 31.992, rcol(), rcol()); //(8)
	AddStaticVehicle(400, 552.79999, -1264.4, 17.2, 215.992, rcol(), rcol()); //(9)
	AddStaticVehicle(500, 549.09998, -1267.2, 17.2, 215.991, rcol(), rcol()); //(10)
	AddStaticVehicle(404, 544.90002, -1270.4, 17.2, 215.991, rcol(), rcol()); //(11)
	AddStaticVehicle(600, 540.5, -1273.9, 17.2, 215.991, rcol(), rcol()); //(12)
	AddStaticVehicle(479, 535.79999, -1277.5, 17.2, 215.991, rcol(), rcol()); //(13)
	AddStaticVehicle(554, 531.6271,-1280.3740,16.8148,211.5015, rcol(), rcol()); // (2)
	// Wang 
	AddStaticVehicle(579, -1956.8749,258.5778,35.3066,42.2316, rcol(), rcol()); // (1)
	AddStaticVehicle(458, -1947, 265.29999, 35.4, 90, rcol(), rcol()); // (3)
	AddStaticVehicle(561, -1947, 261.60001, 35.4, 90, rcol(), rcol()); // (4)
	AddStaticVehicle(580, -1955.9, 264.10001, 35.4, 42, rcol(), rcol());//(Voodoo) (5)
	AddStaticVehicle(533, -1955.9, 272.20001, 35.4, 41.995, rcol(), rcol());//(Voodoo) (6)
	AddStaticVehicle(480, -1955.9, 298.70001, 35.4, 127.995, rcol(), rcol());//(Voodoo) (7)
	AddStaticVehicle(602, -1955.9, 292.70001, 35.4, 127.991, rcol(), rcol());//(Voodoo) (8)
	AddStaticVehicle(589, -1955.9, 279.60001, 35.4, 41.995, rcol(), rcol());//(Voodoo) (9)
	AddStaticVehicle(475, -1955.3, 301.5, 41, 142, rcol(), rcol()); //(Voodoo) (10)
	AddStaticVehicle(496, -1955.3, 295.20001, 41, 141.998, rcol(), rcol()); //(Voodoo) (11)
	AddStaticVehicle(421, -1955.3, 289.79999, 41, 141.998, rcol(), rcol()); //(Voodoo) (12)
	AddStaticVehicle(603, -1956.5, 258.10001, 41, 0, rcol(), rcol()); //(Voodoo) (13)
	AddStaticVehicle(477, -1952.6, 257.70001, 41, 0, rcol(), rcol()); //(Voodoo) (14)
	AddStaticVehicle(429, -1947.4, 261, 41, 50, rcol(), rcol()); //(Voodoo) (15)
	AddStaticVehicle(565, -1947.1, 274.39999, 41, 90, rcol(), rcol()); //(Voodoo) (16)
	AddStaticVehicle(558, -1947, 271, 41, 90, rcol(), rcol()); //(Voodoo) (17)
	AddStaticVehicle(587, -1946.9, 267.20001, 41, 90, rcol(), rcol()); //(Voodoo) (18)

	// OTTO
	AddStaticVehicle(495, -1666.3, 1209, 7.2, 316, rcol(), rcol()); //(Voodoo) (27)
	AddStaticVehicle(502, -1665.8, 1215.2, 7.2, 244, rcol(), rcol()); //(Voodoo) (28)
	AddStaticVehicle(411, -1652, 1212.3, 7.2, 229.995, rcol(), rcol()); //(Voodoo) (29)
	AddStaticVehicle(451, -1661.6, 1218.6, 13.6, 0,rcol(), rcol()); //(Voodoo) (30)
	AddStaticVehicle(415, -1657.8, 1215.5, 13.6, 0,rcol(), rcol()); //(Voodoo) (31)
	AddStaticVehicle(541, -1653.9, 1213.4, 13.6, 0,rcol(), rcol()); //(Voodoo) (32)
	AddStaticVehicle(402, -1669.9, 1204.5, 13.6, 268, rcol(), rcol()); //(33)
	AddStaticVehicle(506, -1673.3, 1207.9, 13.6, 267.995, rcol(), rcol()); //(34)
	AddStaticVehicle(559, -1663.8, 1220.7, 21.1, 0, rcol(), rcol());//(Voodoo) (35)
	AddStaticVehicle(562, -1660.8, 1218.1, 21.1, 0, rcol(), rcol());//(Voodoo) (36)
	AddStaticVehicle(560, -1657.9, 1215.7, 21.1, 0, rcol(), rcol());//(Voodoo) (37)
	SALOON_CARS[1] = AddStaticVehicle(566, 2161.2, -1143.9, 24.8, 90, rcol(), rcol()); //  (34)

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
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если у Вас уже имеется транспорт, он будет заменен!");

		SPD(playerid, dBuyCar, DIALOG_STYLE_MSGBOX, "Покупка транспорта", "{FFFFFF}Вы действительно хотите купить транспорт?\n"COLOR_ORANGE"Транспорт паркуется у недвижимости, для его использования вам нужен дом!\nЕсли у вас уже есть транспорт - он будет заменен", "Купить", "Отмена");
	}
	return 1;
}
CMD:sellcar(playerid) {
	new
    vehicleid = GetPlayerVehicleID(playerid),
    modelid = GetVehicleModel(vehicleid);
	if(vehicleid != caridhouse[playerid]) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Необходимо находиться в своем транспорте");
	if(modelid == 509) return 1;
	for(new i = 0; i < MAX_CAR_AUTOSALEE; i++) {
	if(AutoSalee[i][AS_ModelID] == modelid) {
		new vehprice = AutoSalee[i][AS_Score]/(2);
		new mile = PlayerInfo[playerid][pMileage]/1000;
		if(mile > 1500) vehprice = AutoSalee[i][AS_Score]/(3);
		if(mile > 2000) vehprice = AutoSalee[i][AS_Score]/(4);
		if(mile > 3000) vehprice = AutoSalee[i][AS_Score]/(5);
		if(mile > 4000) vehprice = AutoSalee[i][AS_Score]/(6);
		if(mile > 5000) vehprice = AutoSalee[i][AS_Score]/(7);
		if(mile > 6000) vehprice = AutoSalee[i][AS_Score]/(8);
		if(mile > 7000) vehprice = AutoSalee[i][AS_Score]/(9);
		if(mile > 8000) vehprice = AutoSalee[i][AS_Score]/(10);
		if(mile > 98000) vehprice = AutoSalee[i][AS_Score]/(25);
		if(mile > 10000) vehprice = AutoSalee[i][AS_Score]/(50);
		format(small_string, sizeof small_string, "{FFFFFF}Вы собираетесь продать свой транспорт. Предлагаемая цена: %d "COLOR_GREEN"EXP", vehprice);
		return SPD(playerid, dSellCar, DIALOG_STYLE_MSGBOX, "Продать личный транспорт?", small_string, "Да", "Нет");

		}
	}
	return 1;
}
stock SellCar_Gov(playerid) {
	new
    vehicleid = GetPlayerVehicleID(playerid),
    modelid = GetVehicleModel(vehicleid);
	if(vehicleid != caridhouse[playerid]) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Необходимо находиться в своем транспорте");
	if(modelid == 509) return 1;
	for(new i = 0; i < MAX_CAR_AUTOSALEE; i++) {
	if(AutoSalee[i][AS_ModelID] == modelid) {

	new vehprice = AutoSalee[i][AS_Score]/(2);

	new mile = PlayerInfo[playerid][pMileage]/1000;

	if(mile > 1500) vehprice = AutoSalee[i][AS_Score]/(3);
	if(mile > 2000) vehprice = AutoSalee[i][AS_Score]/(4);
	if(mile > 3000) vehprice = AutoSalee[i][AS_Score]/(5);
	if(mile > 4000) vehprice = AutoSalee[i][AS_Score]/(6);
	if(mile > 5000) vehprice = AutoSalee[i][AS_Score]/(7);
	if(mile > 6000) vehprice = AutoSalee[i][AS_Score]/(8);
	if(mile > 7000) vehprice = AutoSalee[i][AS_Score]/(9);
	if(mile > 8000) vehprice = AutoSalee[i][AS_Score]/(10);
	if(mile > 98000) vehprice = AutoSalee[i][AS_Score]/(25);
	if(mile > 10000) vehprice = AutoSalee[i][AS_Score]/(50);

	if(vehprice > 0) AddPlayerEXP(playerid, vehprice, "Продажа автомобиля");
	format(small_string, sizeof(small_string), "~g~+%d ~w~EXP", vehprice);	
	GameTextForPlayer(playerid, small_string, 3000, 5);

	if(PlayerInfo[playerid][pSelectedSlot] == 1) {
		PlayerInfo[playerid][pCar] = 509;
		SetPlayerInt(playerid, "Car", PlayerInfo[playerid][pCar]);
		PlayerInfo[playerid][pMileage] = 0;
		SetPlayerInt(playerid, "Mileage", PlayerInfo[playerid][pMileage]);
		PlayerInfo[playerid][pCarRoulet1] = 0;
		SetPlayerInt(playerid, "CarRoulet1", PlayerInfo[playerid][pCarRoulet1]);
		PlayerInfo[playerid][pRadarDetect1] = 0;
		SetPlayerInt(playerid, "RadarDetect1", PlayerInfo[playerid][pRadarDetect1]);	

		PlayerInfo[playerid][Spoiler_1] = 0;
		PlayerInfo[playerid][Hood_1] = 0;
		PlayerInfo[playerid][Roof_1] = 0;
		PlayerInfo[playerid][Sideskirt_1] = 0;
		PlayerInfo[playerid][Lamps_1] = 0;
		PlayerInfo[playerid][Nitro_1] = 0;
		PlayerInfo[playerid][Exhaust_1] = 0;
		PlayerInfo[playerid][Wheels_1] = 0;
		PlayerInfo[playerid][Stereo_1] = 0;
		PlayerInfo[playerid][Hydraulics_1] = 0;
		PlayerInfo[playerid][Front_Bumper_1] = 0;
		PlayerInfo[playerid][Rear_Bumper_1] = 0;
		PlayerInfo[playerid][Vent_Right_1] = 0;
		PlayerInfo[playerid][Vent_Left_1] = 0;
		PlayerInfo[playerid][Vynil_1] = 0;

		SetPlayerInt(playerid, "Spoiler_1", PlayerInfo[playerid][Spoiler_1]);
		SetPlayerInt(playerid, "Hood_1", PlayerInfo[playerid][Hood_1]);
		SetPlayerInt(playerid, "Roof_1", PlayerInfo[playerid][Roof_1]);
		SetPlayerInt(playerid, "Sideskirt_1", PlayerInfo[playerid][Sideskirt_1]);
		SetPlayerInt(playerid, "Lamps_1", PlayerInfo[playerid][Lamps_1]);
		SetPlayerInt(playerid, "Nitro_1", PlayerInfo[playerid][Nitro_1]);
		SetPlayerInt(playerid, "Exhaust_1", PlayerInfo[playerid][Exhaust_1]);
		SetPlayerInt(playerid, "Wheels_1", PlayerInfo[playerid][Wheels_1]);
		SetPlayerInt(playerid, "Stereo_1", PlayerInfo[playerid][Stereo_1]);
		SetPlayerInt(playerid, "Hydraulics_1", PlayerInfo[playerid][Hydraulics_1]);
		SetPlayerInt(playerid, "Front_Bumper_1", PlayerInfo[playerid][Front_Bumper_1]);
		SetPlayerInt(playerid, "Rear_Bumper_1", PlayerInfo[playerid][Rear_Bumper_1]);
		SetPlayerInt(playerid, "Vent_Right_1", PlayerInfo[playerid][Vent_Right_1]);
		SetPlayerInt(playerid, "Vent_Left_1", PlayerInfo[playerid][Vent_Left_1]);
		SetPlayerInt(playerid, "Vynil_1", PlayerInfo[playerid][Vynil_1]);			

	} else {
		PlayerInfo[playerid][pCar2] = 509;
		SetPlayerInt(playerid, "Car2", PlayerInfo[playerid][pCar2]);
		PlayerInfo[playerid][pMileage2] = 0;
		SetPlayerInt(playerid, "Mileage2", PlayerInfo[playerid][pMileage2]);
		PlayerInfo[playerid][pCarRoulet2] = 0;
		SetPlayerInt(playerid, "CarRoulet2", PlayerInfo[playerid][pCarRoulet2]);
		PlayerInfo[playerid][pRadarDetect2] = 0;
		SetPlayerInt(playerid, "RadarDetect2", PlayerInfo[playerid][pRadarDetect2]);

		PlayerInfo[playerid][Spoiler_2] = 0;
		PlayerInfo[playerid][Hood_2] = 0;
		PlayerInfo[playerid][Roof_2] = 0;
		PlayerInfo[playerid][Sideskirt_2] = 0;
		PlayerInfo[playerid][Lamps_2] = 0;
		PlayerInfo[playerid][Nitro_2] = 0;
		PlayerInfo[playerid][Exhaust_2] = 0;
		PlayerInfo[playerid][Wheels_2] = 0;
		PlayerInfo[playerid][Stereo_2] = 0;
		PlayerInfo[playerid][Hydraulics_2] = 0;
		PlayerInfo[playerid][Front_Bumper_2] = 0;
		PlayerInfo[playerid][Rear_Bumper_2] = 0;
		PlayerInfo[playerid][Vent_Right_2] = 0;
		PlayerInfo[playerid][Vent_Left_2] = 0;
		PlayerInfo[playerid][Vynil_2] = 0;

		SetPlayerInt(playerid, "Spoiler_2", PlayerInfo[playerid][Spoiler_2]);
		SetPlayerInt(playerid, "Hood_2", PlayerInfo[playerid][Hood_2]);
		SetPlayerInt(playerid, "Roof_2", PlayerInfo[playerid][Roof_2]);
		SetPlayerInt(playerid, "Sideskirt_2", PlayerInfo[playerid][Sideskirt_2]);
		SetPlayerInt(playerid, "Lamps_2", PlayerInfo[playerid][Lamps_2]);
		SetPlayerInt(playerid, "Nitro_2", PlayerInfo[playerid][Nitro_2]);
		SetPlayerInt(playerid, "Exhaust_2", PlayerInfo[playerid][Exhaust_2]);
		SetPlayerInt(playerid, "Wheels_2", PlayerInfo[playerid][Wheels_2]);
		SetPlayerInt(playerid, "Stereo_2", PlayerInfo[playerid][Stereo_2]);
		SetPlayerInt(playerid, "Hydraulics_2", PlayerInfo[playerid][Hydraulics_2]);
		SetPlayerInt(playerid, "Front_Bumper_2", PlayerInfo[playerid][Front_Bumper_2]);
		SetPlayerInt(playerid, "Rear_Bumper_2", PlayerInfo[playerid][Rear_Bumper_2]);
		SetPlayerInt(playerid, "Vent_Right_2", PlayerInfo[playerid][Vent_Right_2]);
		SetPlayerInt(playerid, "Vent_Left_2", PlayerInfo[playerid][Vent_Left_2]);
		SetPlayerInt(playerid, "Vynil_2", PlayerInfo[playerid][Vynil_2]);

	}

	LoadCarPlayerId(playerid);

	return SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы продали свой транспорт");
	}
	}
	SendClientMessage(playerid, -1, ""COLOR_RED"Ваш транспорт исключителен. Продажа государству невозможна");
	return 1;
}
stock Saloon_OnPlayerEnterDynamicCP(playerid, checkpointid) {
	if(checkpointid == SellCar) {
		westcoastcustoms(playerid);
	}
	return 0;
}
hook OnPlayerDialogShowed(const playerid, const e_DIALOG_IDs:dialogid, const response, const listitem, const inputtext[]) {
    if(dialogid == dBuyCar) 
    {
    	if(response) {
    		BuyCar(playerid);
    	}
    	return 1;
    }
    return 1;
}
stock BuyCar(playerid) {
	new selectedcar = GetPVarInt(playerid, "VehToBuy");
	if(!selectedcar) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Сначала необходимо сесть за руль понравившегося автомобиля");
	new vehprice = GetPVarInt(playerid, "PriceToBuy");
	DeletePVar(playerid, "VehToBuy");
	DeletePVar(playerid, "PriceToBuy");
	if(CheckCash(playerid, vehprice) == false) return 1;
	RemovePlayerEXP(playerid, vehprice, "Приобретение автомобиля (modelid %i)", selectedcar);
	format(small_string, sizeof(small_string), "~r~-%d ~w~EXP", vehprice);
	GameTextForPlayer(playerid, small_string, 3000, 5);


	SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы приобрели новый транспорт");
	SendClientMessage(playerid, -1, ""COLOR_GREEN"Транспорт паркуется у недвижимости, для его использования вам нужен дом");
	SendClientMessage(playerid, -1, ""COLOR_BLUE"Дома от среднего класса позволяют иметь два авто {FFFFFF}(/cars)");

	if(PlayerInfo[playerid][pSelectedSlot] == 1) {
		PlayerInfo[playerid][pCar] = selectedcar;
		SetPlayerInt(playerid, "Car", PlayerInfo[playerid][pCar]);
		PlayerInfo[playerid][pMileage] = 0;
		SetPlayerInt(playerid, "Mileage", PlayerInfo[playerid][pMileage]);
		PlayerInfo[playerid][pCarRoulet1] = 0;
		SetPlayerInt(playerid, "CarRoulet1", PlayerInfo[playerid][pCarRoulet1]);
		PlayerInfo[playerid][pRadarDetect1] = 0;
		SetPlayerInt(playerid, "RadarDetect1", PlayerInfo[playerid][pRadarDetect1]);	
		PlayerInfo[playerid][pCarCol] = 0;
		SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
		PlayerInfo[playerid][pCarCol2] = 0;
		SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);

		PlayerInfo[playerid][Spoiler_1] = 0;
		PlayerInfo[playerid][Hood_1] = 0;
		PlayerInfo[playerid][Roof_1] = 0;
		PlayerInfo[playerid][Sideskirt_1] = 0;
		PlayerInfo[playerid][Lamps_1] = 0;
		PlayerInfo[playerid][Nitro_1] = 0;
		PlayerInfo[playerid][Exhaust_1] = 0;
		PlayerInfo[playerid][Wheels_1] = 0;
		PlayerInfo[playerid][Stereo_1] = 0;
		PlayerInfo[playerid][Hydraulics_1] = 0;
		PlayerInfo[playerid][Front_Bumper_1] = 0;
		PlayerInfo[playerid][Rear_Bumper_1] = 0;
		PlayerInfo[playerid][Vent_Right_1] = 0;
		PlayerInfo[playerid][Vent_Left_1] = 0;
		PlayerInfo[playerid][Vynil_1] = 0;

		SetPlayerInt(playerid, "Spoiler_1", PlayerInfo[playerid][Spoiler_1]);
		SetPlayerInt(playerid, "Hood_1", PlayerInfo[playerid][Hood_1]);
		SetPlayerInt(playerid, "Roof_1", PlayerInfo[playerid][Roof_1]);
		SetPlayerInt(playerid, "Sideskirt_1", PlayerInfo[playerid][Sideskirt_1]);
		SetPlayerInt(playerid, "Lamps_1", PlayerInfo[playerid][Lamps_1]);
		SetPlayerInt(playerid, "Nitro_1", PlayerInfo[playerid][Nitro_1]);
		SetPlayerInt(playerid, "Exhaust_1", PlayerInfo[playerid][Exhaust_1]);
		SetPlayerInt(playerid, "Wheels_1", PlayerInfo[playerid][Wheels_1]);
		SetPlayerInt(playerid, "Stereo_1", PlayerInfo[playerid][Stereo_1]);
		SetPlayerInt(playerid, "Hydraulics_1", PlayerInfo[playerid][Hydraulics_1]);
		SetPlayerInt(playerid, "Front_Bumper_1", PlayerInfo[playerid][Front_Bumper_1]);
		SetPlayerInt(playerid, "Rear_Bumper_1", PlayerInfo[playerid][Rear_Bumper_1]);
		SetPlayerInt(playerid, "Vent_Right_1", PlayerInfo[playerid][Vent_Right_1]);
		SetPlayerInt(playerid, "Vent_Left_1", PlayerInfo[playerid][Vent_Left_1]);
		SetPlayerInt(playerid, "Vynil_1", PlayerInfo[playerid][Vynil_1]);	


	} else {
		PlayerInfo[playerid][pCar2] = selectedcar;
		SetPlayerInt(playerid, "Car2", PlayerInfo[playerid][pCar2]);
		PlayerInfo[playerid][pMileage2] = 0;
		SetPlayerInt(playerid, "Mileage2", PlayerInfo[playerid][pMileage2]);		
		PlayerInfo[playerid][pCarRoulet2] = 0;
		SetPlayerInt(playerid, "CarRoulet2", PlayerInfo[playerid][pCarRoulet2]);
		PlayerInfo[playerid][pRadarDetect2] = 0;
		SetPlayerInt(playerid, "RadarDetect2", PlayerInfo[playerid][pRadarDetect2]);	
		PlayerInfo[playerid][pCar2Col] = 0;
		SetPlayerInt(playerid, "Car2Col", PlayerInfo[playerid][pCar2Col]);
		PlayerInfo[playerid][pCar2Col2] = 0;
		SetPlayerInt(playerid, "Car2Col2", PlayerInfo[playerid][pCar2Col2]);

		PlayerInfo[playerid][Spoiler_2] = 0;
		PlayerInfo[playerid][Hood_2] = 0;
		PlayerInfo[playerid][Roof_2] = 0;
		PlayerInfo[playerid][Sideskirt_2] = 0;
		PlayerInfo[playerid][Lamps_2] = 0;
		PlayerInfo[playerid][Nitro_2] = 0;
		PlayerInfo[playerid][Exhaust_2] = 0;
		PlayerInfo[playerid][Wheels_2] = 0;
		PlayerInfo[playerid][Stereo_2] = 0;
		PlayerInfo[playerid][Hydraulics_2] = 0;
		PlayerInfo[playerid][Front_Bumper_2] = 0;
		PlayerInfo[playerid][Rear_Bumper_2] = 0;
		PlayerInfo[playerid][Vent_Right_2] = 0;
		PlayerInfo[playerid][Vent_Left_2] = 0;
		PlayerInfo[playerid][Vynil_2] = 0;

		SetPlayerInt(playerid, "Spoiler_2", PlayerInfo[playerid][Spoiler_2]);
		SetPlayerInt(playerid, "Hood_2", PlayerInfo[playerid][Hood_2]);
		SetPlayerInt(playerid, "Roof_2", PlayerInfo[playerid][Roof_2]);
		SetPlayerInt(playerid, "Sideskirt_2", PlayerInfo[playerid][Sideskirt_2]);
		SetPlayerInt(playerid, "Lamps_2", PlayerInfo[playerid][Lamps_2]);
		SetPlayerInt(playerid, "Nitro_2", PlayerInfo[playerid][Nitro_2]);
		SetPlayerInt(playerid, "Exhaust_2", PlayerInfo[playerid][Exhaust_2]);
		SetPlayerInt(playerid, "Wheels_2", PlayerInfo[playerid][Wheels_2]);
		SetPlayerInt(playerid, "Stereo_2", PlayerInfo[playerid][Stereo_2]);
		SetPlayerInt(playerid, "Hydraulics_2", PlayerInfo[playerid][Hydraulics_2]);
		SetPlayerInt(playerid, "Front_Bumper_2", PlayerInfo[playerid][Front_Bumper_2]);
		SetPlayerInt(playerid, "Rear_Bumper_2", PlayerInfo[playerid][Rear_Bumper_2]);
		SetPlayerInt(playerid, "Vent_Right_2", PlayerInfo[playerid][Vent_Right_2]);
		SetPlayerInt(playerid, "Vent_Left_2", PlayerInfo[playerid][Vent_Left_2]);
		SetPlayerInt(playerid, "Vynil_2", PlayerInfo[playerid][Vynil_2]);

	}
	LoadCarPlayerId(playerid);
	return 1;
}
CMD:changecar(playerid, params[]) {

	if(GetPVarInt(playerid,"deal_created") > gettime()) return SendClientMessage(playerid, -1, ""COLOR_RED"Подождите немного");
	SetPVarInt(playerid,"deal_created",gettime()+30);
	if(!IsValidVehicle(caridhouse[playerid])) return 1;

	if(sscanf(params, "ii", params[0], params[1])) return SendClientMessage(playerid, -1, !"Используйте: /changecar [id игрока] [доплата покупателя]");
	if(PlayerLogged{params[0]} == false || !IsPlayerConnected(params[0])) return 0;
	if(GetDistanceBetweenPlayerz(playerid, params[0], 10.00) != 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы слишком далеко от указанного игрока");

	new price = 0;

	if(PlayerInfo[playerid][pTransferControl] == 2)
		return SendClientMessage(playerid, -1, ""COLOR_RED"Достигнут лимит сделок по транспорту на сегодня");
	if(PlayerInfo[params[0]][pTransferControl] == 2)
		return SendClientMessage(playerid, -1, ""COLOR_RED"Игроком достигнут лимит сделок по транспорту на сегодня");

	if(PlayerInfo[playerid][pDebt] > 1000) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваши штрафы превышают "COLOR_WHITE"1000 EXP"COLOR_RED", вы не можете совершать сделки");
	if(PlayerInfo[params[0]][pDebt] > 1000) return SendClientMessage(playerid, -1, ""COLOR_RED"Штрафы указанного игрока превышают "COLOR_WHITE"1000 EXP"COLOR_RED", вы не можете заключить с ним сделку");


	if(PlayerInfo[playerid][pSelectedSlot] == 1) {
		if(PlayerInfo[playerid][pCarRoulet1] == 1) {
			SendClientMessage(playerid, -1, ""COLOR_RED"Ваш транспорт был выйгран в рулетке");
			return 1;
		}
		if(PlayerInfo[params[0]][pCarRoulet1] == 1) {
			SendClientMessage(playerid, -1, ""COLOR_RED"Транспорт игрока выйгран в рулетке");
			return 1;
		}
	    for(new i = 0; i < MAX_CAR_AUTOSALEE; i++) {
	        if(AutoSalee[i][AS_ModelID] == PlayerInfo[playerid][pCar]) {
	            price = AutoSalee[i][AS_Score];
	        }
	    }
	} else {
		if(PlayerInfo[playerid][pCarRoulet2] == 1) {
			SendClientMessage(playerid, -1, ""COLOR_RED"Ваш транспорт был выйгран в рулетке");
			return 1;
		}
		if(PlayerInfo[params[0]][pCarRoulet2] == 1) {
			SendClientMessage(playerid, -1, ""COLOR_RED"Транспорт игрока выйгран в рулетке");
			return 1;
		}
	    for(new i = 0; i < MAX_CAR_AUTOSALEE; i++) {
	        if(AutoSalee[i][AS_ModelID] == PlayerInfo[playerid][pCar2]) {
	            price = AutoSalee[i][AS_Score]*2;
	        }
	    }
	}

    if(price == 0) return SendClientMessage(playerid, -1, !"Данное транспортное средство исключительно. Обмен невозможен");
	if(params[1] <= 0) return SendClientMessage(playerid, -1, ""COLOR_RED"Некорректная цена");
	if(params[1] > price) return SendClientMessage(playerid, -1, ""COLOR_RED"Доплата должна быть не выше двойной рыночной стоимости транспорта");
	if(params[0] == playerid || params[0] == INVALID_PLAYER_ID) return SendClientMessage(playerid, -1, "Неверный ID");
	if(caridhouse[params[0]] == INVALID_VEHICLE_ID) return SendClientMessage(playerid, -1, "У игрока нет дома для парковки транспорта");

	SetPVarInt(playerid, "buyer_house", params[0]);
	SetPVarInt(playerid, "price_house", params[1]);

	/* Диалог продавцу */
	if(PlayerInfo[params[0]][pSelectedSlot] == 1 && PlayerInfo[playerid][pSelectedSlot] == 1) {
	format(big_string, sizeof big_string, 
		"{FFFFFF}Вы предложили обмен транспорта %s\n"COLOR_RED"Вы отдаете: {FFFFFF}%s (%dкм.)\n"COLOR_GREEN"Вы получаете: {FFFFFF}%s (%dкм.), %d EXP\n\n"COLOR_ORANGE"Чтобы подтвердить сделку нажмите - Далее", 
		PlayerInfo[params[0]][pName], 
		GetVehicleText(PlayerInfo[playerid][pCar]), 
		PlayerInfo[playerid][pMileage]/1000,
		GetVehicleText(PlayerInfo[params[0]][pCar]), 
		PlayerInfo[params[0]][pMileage]/1000,
		params[1]);
	}
	if(PlayerInfo[params[0]][pSelectedSlot] == 1 && PlayerInfo[playerid][pSelectedSlot] == 2) {
	format(big_string, sizeof big_string, 
		"{FFFFFF}Вы предложили обмен транспорта %s\n"COLOR_RED"Вы отдаете: {FFFFFF}%s (%dкм.)\n"COLOR_GREEN"Вы получаете: {FFFFFF}%s (%dкм.), %d EXP\n\n"COLOR_ORANGE"Чтобы подтвердить сделку нажмите - Далее", 
		PlayerInfo[params[0]][pName], 
		GetVehicleText(PlayerInfo[playerid][pCar2]), 
		PlayerInfo[playerid][pMileage2]/1000,
		GetVehicleText(PlayerInfo[params[0]][pCar]), 
		PlayerInfo[params[0]][pMileage]/1000,
		params[1]);
	}
	if(PlayerInfo[params[0]][pSelectedSlot] == 2 && PlayerInfo[playerid][pSelectedSlot] == 1) {
	format(big_string, sizeof big_string, 
		"{FFFFFF}Вы предложили обмен транспорта %s\n"COLOR_RED"Вы отдаете: {FFFFFF}%s (%dкм.)\n"COLOR_GREEN"Вы получаете: {FFFFFF}%s (%dкм.), %d EXP\n\n"COLOR_ORANGE"Чтобы подтвердить сделку нажмите - Далее", 
		PlayerInfo[params[0]][pName], 
		GetVehicleText(PlayerInfo[playerid][pCar]), 
		PlayerInfo[playerid][pMileage]/1000,
		GetVehicleText(PlayerInfo[params[0]][pCar2]), 
		PlayerInfo[params[0]][pMileage2]/1000,
		params[1]);
	}
	if(PlayerInfo[params[0]][pSelectedSlot] == 2 && PlayerInfo[playerid][pSelectedSlot] == 2) {
	format(big_string, sizeof big_string, 
		"{FFFFFF}Вы предложили обмен транспорта %s\n"COLOR_RED"Вы отдаете: {FFFFFF}%s (%dкм.)\n"COLOR_GREEN"Вы получаете: {FFFFFF}%s (%dкм.), %d EXP\n\n"COLOR_ORANGE"Чтобы подтвердить сделку нажмите - Далее", 
		PlayerInfo[params[0]][pName], 
		GetVehicleText(PlayerInfo[playerid][pCar2]), 
		PlayerInfo[playerid][pMileage2]/1000,
		GetVehicleText(PlayerInfo[params[0]][pCar2]), 
		PlayerInfo[params[0]][pMileage2]/1000,
		params[1]);
	}
	SPD(playerid, dChangeCar, DIALOG_STYLE_MSGBOX, "Обмен транспорта",
	 big_string, "Далее", "Отмена");
	return 1;
}
stock GetCarCost(playerid) {
	new car, cost = -1;
	new slot = -1;
	if(PlayerInfo[playerid][pSelectedSlot] == 1) slot = 1;
	if(PlayerInfo[playerid][pSelectedSlot] == 2) slot = 2;

	if(slot == 1) {
	for(new i = 0; i < MAX_CAR_AUTOSALEE; i++) {
		if(PlayerInfo[playerid][pCar] == AutoSalee[i][AS_ModelID]) {
			car = AutoSalee[i][AS_Score];
		}
	}
	}
	if(slot == 2) {
	for(new i = 0; i < MAX_CAR_AUTOSALEE; i++) {
		if(PlayerInfo[playerid][pCar2] == AutoSalee[i][AS_ModelID]) {
			car = AutoSalee[i][AS_Score];
		}
	}
	}
	if(car >= 1 && car <= 5000) cost = 1000;
	if(car >= 5001 && car <= 10000) cost = 2500;
	if(car >= 10001 && car <= 25000) cost = 3500;
	if(car >= 25001 && car <= 50000) cost = 4500;
	if(car >= 50001 && car <= 75000) cost = 5500;
	if(car >= 75001 && car <= 100000) cost = 6500;
	if(cost == -1) cost = 9000;


	SetPVarInt(playerid, "сcost", cost);
	return 1;
}

stock rcol() {
	return RandomEx(0,126);
}