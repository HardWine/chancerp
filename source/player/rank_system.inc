#if defined rank_system_included
	#endinput
#endif

#define rank_system_included

new gFractionRankName_ENG[13][18][32] =
{
 /* LSPD */			{"","Officer","Sergeant","Detective","Lieutenant","Captain","Major","Lieutenant-Colonel","Colonel","Assistant Chief","Chief of Department","","","","","","",""},
 /* Grove Street */	{"","Playa","Hustla","Killa","Young G","Gangsta","O.G.","Mobsta","De King","Legend","Mad Dog","","","","","","",""},
 /* Ballas Gang */	{"","Blade","Buster","Cracker","Gun Bro","Bro","Gangster","Federal Block","Folks","Rich Nigga","Big Willy","","","","","","",""},
 /* Vagos Gang */	{"","Novato","Ordinario","Local","Verificado","Bandido","V.E.G","Assesino","V.E.G Lead","Padrino","Padre","","","","","","",""},
 /* Rifa Gang */ 	{"","Ladron","Novato","Amigo","Macho","Junior","Ermano","Bandido","Authoridead","Ajunto","Padre","","","","","","",""},
 /* Aztecas Gang */	{"","Perro","Tirador","Gettor","Las Gerras","Mirindo","Sabio","Invasor","Tesorero","Nestro","Padre","","","","","","",""},
 /* Russian Mafia */{"","Shoelace","Fledgling","Bull","Huckster","Criminal","Brother-in-law","Brother","Thief","Thief in the Law","Authority","","","","","","",""}, 
 /* Triads */		{"","49ers","Blue Lanterns","White Paper Fan","Red Pole","Straw Sandal","Vanguard","Deputy Mountain Master","Incense Master","Mountain Master","Dragon Head","","","","","","",""},
 /* Da Nang Boys */	{"","Kaikei","Shatei","Shingiin","Kyodai","Saiko-komon","So-kobunto","Shateigashira","Wakagashira","Kambu","Oyabun","","","","","","",""},
 /* ARMY */			{"","Recruit","Private","Corporal","Sergeant","Warrant Officer","Lieutenant","Capitan","Major","Colonel","Brigadier","","","","","","",""},
 /* FBI */			{"","Field Agent","Agent Trainee","Agent","Special Agent","Supervisory Agent","ASAC","SAC","Assistant Director","Deputy Director","Director","","","",""," ","",""},
 /* MAYOR */		{"","Guard", "Driver", "Bodyguard", "Secretary", "Head of Security", "Lawyer", "Minister", "Counselor","Vice-Governor", "Governor","","","","","","",""},
 /* NEWS */			{"","Intern","Journalist","Photographer","Reporter","Editor","Operator","Presenter","Creative Director","Vice-Director"," Director","","","","","","",""}
};
new gFractionRankName_RU[13][18][32] =
{
 /* LSPD */			{"","Офицер","Сержант","Детектив","Лейтенант","Капитан","Майор","Подполковник","Полковник","Помощник Шефа","Шеф департамента","","","","","","",""},
 /* Grove Street */	{"","Плайа","Хастла","Килла","Янг Джи","Гангста","О.Г.","Мобста","Де Кинг","Легенд","Мэд Дог","","","","","","",""},
 /* Ballas Gang */	{"","Блайд","Бастер","Крэкер","Ган бро","Бро","Гангстер","Федерал Блок","Фолкс","Райч нига","Биг вилли","","","","","","",""},
 /* Vagos Gang */	{"","Новато","Ординарио","Локал","Верификадо","Бандидо","V.E.G","Ассесино","Лидер V.E.G.","Падрино","Padrino","Padre","","","","","",""},
 /* Rifa Gang */ 	{"","Ладрон","Новато","Амиго","Мачо","Джуниор","Эрмано","Бандидо","Ауторидид","Аджунто","Падре","","","","","","",""},
 /* Aztecas Gang */	{"","Перро","Тирадор","Геттор","Лас Геррас","Мириндо","Сабио","Инвасор","Тесореро","Нестро","Падре","","","","","","",""},
 /* Russian Mafia */{"","Шнурок","Молодой","Бык","Барыга","Блатной","Свояк","Браток","Вор","Вор в Законе","Авторитет","","","","","","",""}, 
 /* Triads */		{"","49-ый", "Светлячок", "Белый веер", "Красный полюс", "Соломенный", "Авангард", "Скала", "Фимиам", "Горный мастер", "Голова дракона" , "", "", "", "", "", "", ""},
 /* Da Nang Boys */	{"","Кайкэй","Сятей","Сингин","Кё дай","Сайко комон","Со-хобунтё","Сятей-гасира","Вака-гасира","Камбу","Оябун","","","","","","",""},
 /* ARMY */			{"","Новобранец","Рядовой","Капрал","Сержант","Уоррент-Офицер","Лейтенант","Капитан","Майор","Полковник","Бригадир","","","","","","",""},
 /* FBI */			{"","Полевой Агент","Агент стажер","Агент","Специальный агент","Старший агент","ASAC","SAC","Помощник директора","Зам. директора","Директор","","","","","","",""},
 /* MAYOR */		{"","Охранник","Водитель","Телохранитель","Секретарь","Начальник охраны","Адвокат","Министр","Советник","Вице-губернатор","Губернатор","","","","","","",""},
 /* NEWS */			{"","Стажёр", "Журналист", "Фотограф", "Репортёр", "Редактор", "Оператор", "Ведущий", "Креативный директор","Исп. Директор", "Директор","","","","","","",""}
};

stock IncreaseStatus(playerid, amount = 1) {
	new 
		Fraction: fractionid = GetPlayerFraction(playerid);

	new crutch = GetPlayerFractionInt(playerid);
	crutch--;

	if(Fraction[crutch][E_FRACTION_AUTO_RANG] == 0) return 1;	


	PlayerInfo[playerid][pStatus] += amount;

	if(PlayerInfo[playerid][pStatus] > 1000) {
		PlayerInfo[playerid][pStatus] = 1000;
		SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
	}
	else SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 

	new player_status = PlayerInfo[playerid][pStatus];
	if(fractionid >= FRACTION_GROOVE && fractionid <= FRACTION_AZTECAS) {

		if(PlayerInfo[playerid][pRank] == 1) {
			switch(player_status) {
				case 0..4: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 5..9: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 10..19: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 20..29: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 30..39: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 40..49: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 2
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 	
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 2 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/50~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 2) {
			switch(player_status) {
				case 0..12: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 13..25: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 26..38: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 39..51: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 52..64: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 65..74: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 3
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 3 ранга!");
					CBackSkin(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стала доступна кража материалов с военной базы 'Зона-51'");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/75~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 3) {
			switch(player_status) {
				case 0..21: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 22..43: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 44..65: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 66..87: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 88..109: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 110..124: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 4
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 4 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/125~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 4) {
			switch(player_status) {
				case 0..43: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 44..86: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 87..130: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 131..173: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 174..216: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 217..249: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 5 ранга!");
					CBackSkin(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стал доступен автоугон{FFFFFF}(/gps - Другие места - Автомойка)");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/250~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 5) {
			switch(player_status) {
				case 0..84: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 85..169: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 170..253: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 254..337: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 338..422: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 423..499: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 	
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 6 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/500~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status); 
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 6) {
			switch(player_status) {
				case 0..108: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 109..216: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 217..324: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 325..432: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 433..540: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 541..649: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 7 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/650~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 7) {
			switch(player_status) {
				case 0..125: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 126..251: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 252..377: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 378..502: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 503..628: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 629..749: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 8 ранга!");
					CBackSkin(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стал доступен захват вражеских территорий: {FFFFFF}/capture");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/750~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 8) {
			switch(player_status) {
				case 0..150: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 151..301: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 302..452: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 453..600: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 601..749: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 750..899: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					if(GetFractionLeader(crutch) != INVALID_ACCOUNT_ID) return 1;
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 9 ранга!");
					CBackSkin(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стало доступен прием людей в банду:{FFFFFF} /invite");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/900~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 9) {
			switch(player_status) {
				case 0..166: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 167..332: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 333..498: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 499..664: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 665..830: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 831..999: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					if(GetFractionLeader(crutch) != INVALID_ACCOUNT_ID) return 1;
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли максимального ранга!");
					CBackSkin(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стало доступна функция увольнения:{FFFFFF} /uninvite");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/900~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] >= 10) {
			if(GetFractionLeader(crutch) != INVALID_ACCOUNT_ID) return 1;
			format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
			return GameTextForPlayer(playerid, small_string, 4250, 3);	
		}
		GameTextForPlayer(playerid, small_string, 4250, 3);
	} 
	if(fractionid >= FRACTION_AZTECAS && fractionid <= FRACTION_DN_BOYS) {

		if(PlayerInfo[playerid][pRank] == 1) {
			switch(player_status) {
				case 0..4: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 5..9: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 10..19: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 20..29: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 30..39: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 40..49: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 2
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 	
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 2 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/50~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 2) {
			switch(player_status) {
				case 0..12: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 13..25: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 26..38: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 39..51: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 52..64: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 65..74: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 3
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 3 ранга!");
					CBackSkin(playerid);
					//SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стала доступна кража материалов с военной базы 'Зона-51'");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/75~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 3) {
			switch(player_status) {
				case 0..21: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 22..43: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 44..65: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 66..87: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 88..109: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 110..124: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 4
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 4 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/125~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 4) {
			switch(player_status) {
				case 0..43: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 44..86: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 87..130: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 131..173: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 174..216: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 217..249: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 5 ранга!");
					CBackSkin(playerid);
					//SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стал доступен автоугон{FFFFFF}(/gps - Другие места - Автомойка)");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/250~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 5) {
			switch(player_status) {
				case 0..84: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 85..169: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 170..253: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 254..337: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 338..422: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 423..499: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 	
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 6 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/500~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status); 
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 6) {
			switch(player_status) {
				case 0..108: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 109..216: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 217..324: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 325..432: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 433..540: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 541..649: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 7 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/650~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 7) {
			switch(player_status) {
				case 0..125: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 126..251: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 252..377: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 378..502: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 503..628: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 629..749: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 8 ранга!");
					CBackSkin(playerid);
					//SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стал доступен захват вражеских территорий: {FFFFFF}/capture");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/750~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 8) {
			switch(player_status) {
				case 0..150: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 151..301: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 302..452: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 453..600: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 601..749: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 750..899: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					if(GetFractionLeader(crutch) != INVALID_ACCOUNT_ID) return 1;
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 9 ранга!");
					CBackSkin(playerid);
					//SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стало доступен прием людей в банду:{FFFFFF} /invite");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/900~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 9) {
			switch(player_status) {
				case 0..166: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 167..332: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 333..498: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 499..664: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 665..830: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 831..999: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					if(GetFractionLeader(crutch) != INVALID_ACCOUNT_ID) return 1;
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли максимального ранга!");
					CBackSkin(playerid);
					//SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стало доступна функция увольнения:{FFFFFF} /uninvite");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/900~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] >= 10) {
			if(GetFractionLeader(crutch) != INVALID_ACCOUNT_ID) return 1;
			format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
			return GameTextForPlayer(playerid, small_string, 4250, 3);	
		}
		GameTextForPlayer(playerid, small_string, 4250, 3);
	} 



	if(fractionid == FRACTION_ARMY) {

		if(PlayerInfo[playerid][pRank] == 1) {
			switch(player_status) {
				case 0..4: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 5..9: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 10..19: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 20..29: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 30..39: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 40..49: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 2
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 2 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/50~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 2) {
			switch(player_status) {
				case 0..12: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 13..25: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 26..38: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 39..51: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 52..64: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 65..74: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 3
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 3 ранга!");
					CBackSkin(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стала доступна работа на заводе по сборке оружия");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/75~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 3) {
			switch(player_status) {
				case 0..21: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 22..43: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 44..65: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 66..87: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 88..109: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 110..124: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 4
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 4 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/125~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 4) {
			switch(player_status) {
				case 0..43: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 44..86: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 87..130: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 131..173: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 174..216: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 217..249: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 5 ранга!");
					CBackSkin(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стала доступна доставка военных грузов");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/250~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 5) {
			switch(player_status) {
				case 0..84: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 85..169: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 170..253: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 254..337: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 338..422: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 423..499: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 6 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/500~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 6) {
			switch(player_status) {
				case 0..108: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 109..216: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 217..324: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 325..432: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 433..540: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 541..649: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 7 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/650~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 7) {
			switch(player_status) {
				case 0..125: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 126..251: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 252..377: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 378..502: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 503..628: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 629..749: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 8 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/750~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 8) {
			switch(player_status) {
				case 0..150: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 151..301: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 302..452: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 453..600: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 601..749: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 750..899: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					if(GetFractionLeader(crutch) != INVALID_ACCOUNT_ID) return 1;
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 9 ранга!");
					CBackSkin(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стало доступно проведение призывов:{FFFFFF} /gov и /invite");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/900~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 9) {
			switch(player_status) {
				case 0..166: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 167..332: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 333..498: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 499..664: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 665..830: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 831..999: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					if(GetFractionLeader(crutch) != INVALID_ACCOUNT_ID) return 1;
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли максимального ранга!");
					CBackSkin(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стало доступна функция увольнения:{FFFFFF} /uninvite");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/900~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] >= 10) {
			format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
			return GameTextForPlayer(playerid, small_string, 4250, 3);	
		}
		GameTextForPlayer(playerid, small_string, 4250, 3);
	}

	if(fractionid == FRACTION_LSPD) {

		if(PlayerInfo[playerid][pRank] == 1) {
			switch(player_status) {
				case 0..4: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 5..9: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 10..19: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 20..29: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 30..39: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 40..49: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/50", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 2
				default: {

					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 2 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/50~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 2) {
			switch(player_status) {
				case 0..12: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 13..25: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 26..38: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 39..51: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 52..64: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 65..74: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/75", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 3
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 3 ранга!");
					CBackSkin(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стал доступен арест игроков (/taser /cuff /cput /arrest)");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/75~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 3) {
			switch(player_status) {
				case 0..21: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 22..43: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 44..65: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 66..87: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 88..109: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 110..124: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/125", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 4
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 4 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/125~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 4) {
			switch(player_status) {
				case 0..43: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 44..86: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 87..130: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 131..173: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 174..216: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 217..249: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/250", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 5 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/250~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 5) {
			switch(player_status) {
				case 0..84: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 85..169: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 170..253: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 254..337: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 338..422: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 423..499: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/500", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 6 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/500~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 6) {
			switch(player_status) {
				case 0..108: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 109..216: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 217..324: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 325..432: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 433..540: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 541..649: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/650", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 7 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/650~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 7) {
			switch(player_status) {
				case 0..125: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 126..251: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 252..377: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 378..502: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 503..628: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 629..749: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/750", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 8 ранга!");
					CBackSkin(playerid);
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/750~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 8) {
			switch(player_status) {
				case 0..150: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 151..301: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 302..452: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 453..600: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 601..749: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 750..899: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					if(GetFractionLeader(crutch) != INVALID_ACCOUNT_ID) return 1;
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли 9 ранга!");
					CBackSkin(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стало доступен прием новых сотрудников:{FFFFFF} /invite");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/900~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] == 9) {
			switch(player_status) {
				case 0..166: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~]]]]]]]]]~n~%d/900", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 167..332: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]~w~]]]]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 333..498: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]~w~]]]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 499..664: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]~w~]]]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 665..830: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]~w~]]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				case 831..999: format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~]~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
				// RANK 5
				default: {
					if(GetFractionLeader(crutch) != INVALID_ACCOUNT_ID) return 1;
					PlayerInfo[playerid][pStatus] = 0; SetPlayerInt(playerid, "Status", PlayerInfo[playerid][pStatus]); 
					PlayerInfo[playerid][pRank] += 1; SetPlayerInt(playerid, "Rank", PlayerInfo[playerid][pRank]); 
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы достигли максимального ранга!");
					CBackSkin(playerid);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Теперь вам стало доступна функция увольнения:{FFFFFF} /uninvite");
					format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~g~~h~~h~%s~n~~y~]]]]]]]]]~w~~n~%d/900~n~~w~Congratulations!", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
					return GameTextForPlayer(playerid, small_string, 4250, 3);
				}		
			}
		}
		else if(PlayerInfo[playerid][pRank] >= 10) {
			if(GetFractionLeader(crutch) != INVALID_ACCOUNT_ID) return 1;
			format(small_string, sizeof(small_string), "~n~~n~~n~~n~~n~~n~~n~~n~~w~%s~n~~y~]]]]]]]]~w~~n~%d/1000", gFractionRankName_ENG[_:fractionid-1][PlayerInfo[playerid][pRank]], player_status);
			return GameTextForPlayer(playerid, small_string, 4250, 3);	
		}
		GameTextForPlayer(playerid, small_string, 4250, 3);
	}
	return 1;
}