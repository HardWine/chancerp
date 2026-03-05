#if defined anticheat_header_included
	#endinput
#endif

#define anticheat_header_included
#define MAX_ANTICHEAT_PC 			(2)
#define MAX_ANTICHEAT_CODE 			(53)
#define MAX_ANTICHEAT_TITLE 			(52)
#define MAX_ANTICHEAT_ANDROID 			(2)
#define MAX_ANTICHEAT_ACTION 			(3)

enum AC_INFO__ {
	AC_ID,
	AC_Value,
	AC_Title[MAX_ANTICHEAT_TITLE],
	AC_PC,
	AC_ANDROID,
	AC_Action
};

new const AC.PC[MAX_ANTICHEAT_PC][30] = {
		{""COLOR_RED"Выкл."COLOR_WHITE""},
		{""COLOR_GREEN"Вкл."COLOR_WHITE""}
	},
	AC.Android[MAX_ANTICHEAT_ANDROID][30] = {
		{""COLOR_RED"Выкл."COLOR_WHITE""},
		{""COLOR_GREEN"Вкл."COLOR_WHITE""}
	},
	AC.Action[MAX_ANTICHEAT_ACTION][24] = {
		{"Cообщение администрации"},
		{"Кик"},
		{"Блокировка IP адреса"}
	};

new
	AC.Info[MAX_ANTICHEAT_CODE][AC_INFO__] = {
		{1, 0, "Anti-AirBreak (onfoot)", 0, 0, 0},
		{2, 1, "Anti-AirBreak (in vehicle)", 0, 0, 0},
		{3, 2, "Anti-teleport hack (onfoot)", 0, 0, 0},
		{4, 3, "Anti-teleport hack (in vehicle)", 0, 0, 0},
		{5, 4, "Anti-teleport hack (into/between vehicles)", 0, 0, 0},
		{6, 5, "Anti-teleport hack (vehicle to player)", 0, 0, 0},
		{7, 6, "Anti-teleport hack (pickups)", 0, 0, 0},
		{8, 7, "Anti-FlyHack (onfoot)", 0, 0, 0},
		{9, 8, "Anti-FlyHack (in vehicle)", 0, 0, 0},
		{10, 9, "Anti-SpeedHack (onfoot)", 0, 0, 0},
		{11, 10, "Anti-SpeedHack (in vehicle)", 0, 0, 0},
		{12, 11, "Anti-Health hack (in vehicle)", 0, 0, 0},
		{13, 12, "Anti-Health hack (onfoot)", 0, 0, 0},
		{14, 13, "Anti-Armour hack", 0, 0, 0},
		{15, 14, "Anti-Money hack", 0, 0, 0},
		{16, 15, "Anti-Weapon hack", 0, 0, 0},
		{17, 16, "Anti-Ammo hack (add)", 0, 0, 0},
		{18, 17, "Anti-Ammo hack (infinite)", 0, 0, 0},
		{19, 18, "Anti-Special actions hack", 0, 0, 0},
		{20, 19, "Anti-GodMode from bullets (onfoot)", 0, 0, 0},
		{21, 20, "Anti-GodMode from bullets (in vehicle)", 0, 0, 0},
		{22, 21, "Anti-Invisible hack", 0, 0, 0},
		{23, 22, "Anti-lagcomp-spoof", 0, 0, 0},
		{24, 23, "Anti-Tuning hack", 0, 0, 0},
		{25, 24, "Anti-Parkour mod", 0, 0, 0},
		{26, 25, "Anti-Quick turn", 0, 0, 0},
		{27, 26, "Anti-Rapid fire", 0, 0, 0},
		{28, 27, "Anti-FakeSpawn", 0, 0, 0},
		{29, 28, "Anti-FakeKill", 0, 0, 0},
		{30, 29, "Anti-Pro Aim", 0, 0, 0},
		{31, 30, "Anti-CJ run", 0, 0, 0},
		{32, 31, "Anti-CarShot", 0, 0, 0},
		{33, 32, "Anti-CarJack", 0, 0, 0},
		{34, 33, "Anti-UnFreeze", 0, 0, 0},
		{35, 34, "Anti-AFK Ghost", 0, 0, 0},
		{36, 35, "Anti-Full Aiming", 0, 0, 0},
		{37, 36, "Anti-Fake NPC", 0, 0, 0},
		{38, 37, "Anti-Reconnect", 0, 0, 0},
		{39, 38, "Anti-High ping", 0, 0, 0},
		{40, 39, "Anti-Dialog hack", 0, 0, 0},
		{41, 40, "Protection from the sandbox", 0, 0, 0},
		{42, 41, "Protection against an invalid version", 0, 0, 0},
		{43, 42, "Anti-Rcon hack", 0, 0, 0},
		{44, 43, "Anti-Tuning crasher", 0, 0, 0},
		{45, 44, "Anti-Invalid seat crasher", 0, 0, 0},
		{46, 45, "Anti-Dialog crasher", 0, 0, 0},
		{47, 46, "Anti-Attached object crasher", 0, 0, 0},
		{48, 47, "Anti-Weapon Crasher", 0, 0, 0},
		{49, 48, "Flood protection connects to one slot", 0, 0, 0},
		{50, 49, "Anti-flood callback functions", 0, 0, 0},
		{51, 50, "Anti-flood change seat", 0, 0, 0},
		{52, 51, "Anti-Ddos", 0, 0, 0},
		{53, 52, "Anti-NOP's", 0, 0, 0}
	};


