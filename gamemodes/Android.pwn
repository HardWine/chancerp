#include <a_samp>

#if defined MAX_PLAYERS
    #undef MAX_PLAYERS
#endif

#define MAX_PLAYERS 			250

#if defined MAX_VEHICLES
    #undef MAX_VEHICLES 
#endif
#define MAX_VEHICLES 			1200

#include <foreach>
#include <streamer>
#include <sscanf2>
#include <a_mysql>
#include <Pawn.CMD>
#include <a_actor>
#include <regex>
#include <dc_kickfix>
#include <mdialog>
#include <crashdetect>
#define YSI_NO_HEAP_MALLOC
new Platform[MAX_PLAYERS];
#define MYSQL_HOSTNAME "triniti.ru-hoster.com"
#define MYSQL_USERNAME "chancobK" 
#define MYSQL_PASSWORD "OXop51sk82" 
#define MYSQL_DATABASE "chancobK"
#define GLOBAL_SERVER_IP "176.32.36.4"

#if !defined MAX_WEAPON_NAME
    #define MAX_WEAPON_NAME (19)
#endif

#if !defined WEAPON_FIST
    #define WEAPON_FIST (0)
#endif

#if !defined MAX_WEAPON_SLOTS
    #define MAX_WEAPON_SLOTS (12)
#endif

#define TABLE_ACCOUNTS "players"
#define SERVER_RCON_PASSWORD "HX4a7faw3vas541ASFn5qqsfa"

#define INVALID_ACCOUNT_ID 									(-1) // Неверный ID аккаунта
#define MAX_LENGTH_ACCOUNT_ID 								(6) // Максимальная длина (кол-во цифр) в ID аккаунта игрока

#define GetPlayerAdminLevel(%0) PlayerInfo[%0][pAdmin] 			// Быстрый и простой доступ к уровню админки
#define GetPlayerLoging(%0) PlayerLogged{%0} 					// Быстрый и простой доступ к статусу авторизации (false - не авторизован | true - авторизован)
#define GetPlayerAccountID(%0) PlayerInfo[%0][pID] 				// Быстрый и простой доступ к ID аккаунта игрока

forward OnPlayerAuthorization(playerid); 						// Игрок авторизовался (вошел в аккаунт)
forward OnPlayerGameQuit(playerid); 							// Авторизованный игрок вышел из игры
forward OnPlayerDialogShowed(const playerid, const dialogid, const response, const listitem, const inputtext[]);

//DEFINE
#define SMALL_STRING_SIZE 									(144)
new small_string 											[SMALL_STRING_SIZE];
#define MEDUIM_STRING_SIZE 									(256)
new medium_string 											[MEDUIM_STRING_SIZE];
#define BIG_STRING_SIZE 									(512)
new big_string 												[BIG_STRING_SIZE];
#define GBIG_STRING_SIZE 									(1024)
//new huge_string                                             [GBIG_STRING_SIZE];

#define MAX_DISTANCE_VISIBLE 								(20.00) // Максимальная зона видимости ников, пикапов, 3D текстов
#define publics:%0(%1)										forward %0(%1); public %0(%1)
#define MAX_LENGTH_IP 										(16 + 1)
//#define GetPlayerMember(%0) PlayerInfo[%0][pJob]
#define INVALID_TIMER_ID    (-1)

#define    BUG_REPORT_FILE_NAME        "BugLog.txt"
#define    SUGGESTION_FILE_NAME        "SugLog.txt"

#define Pickup. Pickup_
#define Farm. Farm_
#define House. House_
#define Zone. Zone_
#define Player. 		Player__
#define Vehicle.		Vehicle__

#define MAX_KICK_REASON 					(32 + 1) // Максимальная причина кика
native IsValidVehicle(vehicleid);
stock ALS_KillTimer(timerid) {
    if(timerid != INVALID_TIMER_ID) {
        KillTimer(timerid);
    }
    return INVALID_TIMER_ID;
}
#if defined _ALS_KillTimer
    #undef KillTimer
#else
    #define _ALS_KillTimer
#endif
 
#define KillTimer ALS_KillTimer

stock IsValidTimer(timerid) {
	if(timerid != INVALID_TIMER_ID) return true;
	return false;
}


#define MAX_ADMIN_CAR 			30

new
    pPickup_AntiFlood[MAX_PLAYERS],
    Float:pPickup_Pos[MAX_PLAYERS][3],
    bool:pPickup_Status[MAX_PLAYERS char]
;  

new 
	AdminCar[MAX_ADMIN_CAR] = {INVALID_VEHICLE_ID, ...};

new 
	Iterator:PlayerWanted<MAX_PLAYERS>;

new VehicleParameters[MAX_VEHICLES][2]; 

new busstop;

#define COLOR_WHITE "{FFFFFF}"//белый
#define COLOR_BLACK "{0E0101}" //черный
#define COLOR_GRAY "{C3C3C3}"//серый
#define COLOR_GREEN "{6de64e}"//зеленый
#define COLOR_RED "{ff353c}"//красный
#define COLOR_YELLOW "{F3FF02}"//желтый
#define COLOR_ORANGE "{FFAF00}"//оранжевый
#define COLOR_LIME "{B7FF00}"//светло зеленый
#define COLOR_LIGHTBLUE "{00C0FF}"//голубой
#define COLOR_BLUE "{4eb9e6}"//синий
#define COLOR_PINK "{8FE47F}"//розовый
#define COLOR_PURPLE "{DD90FF}"//фиолетовый

#define C_PURPLE	0xDD90FFFF
#define C_YELLOW	0xFFFF00AA
#define C_ORANGE	0xFF9900AA
#define C_CHAT      0xE6E6E6E6

#define CIVIL_COLOR 0xFFFFFF70
#define LSPD_COLOR 0x2641FEAA
#define GROVE_COLOR 0x00D900C8
#define BALLAS_COLOR 0xD900D3C8
#define VAGOS_COLOR 0xFFC801C8
#define AZTEC_COLOR 0x01FCFFC8
#define RIFA_COLOR 0x6666ffff
#define RUSSIA_COLOR 0x4d4d4dFF
#define TRIAD_COLOR 0x660000AA
#define DANANG_COLOR 0xcc6600FF
#define ARMY_COLOR 0x336600AA
#define FBI_COLOR 0x1a1a1aFF
#define MAYOR_COLOR 0x336699FF
#define INVALID_ZONE_ID                         (-1)

#if !defined gpci
	native gpci(playerid, buffer[], size = sizeof(buffer));
#endif

// commit 
#define Gpci047 "42443231414852474A4953364736505754353538"

#define Gpci069 "5A4D574253415337304A5A593654444A32584A30"

static const RakDroidGpci[7][41] = {
	"3952314F524834355456464955525858554F3353",
	"485149554757444F555856484E3139425A495345",
	"3343434B4D415A59474A505A50334A5048304D4B",
	"37584E55314659564E5050575758464A53513555",
	"37544E45315A4D565A3135344331564A5355484D",
	"3956314F52584735484A5A55554E314841305230",
	"42313745394255564239393838394A564F325432"
};

new 
	bool: AutoHouseSell = true,
	bool: test_server = false;

// ENUMS
enum 
{
    dKickMessage,//Автоматически займёт ID 0
    dRegister,
    dEmail,
    dSex,
    dLogin,
    dName,
    dBank,
    dBankRecieve,
    dBankPut,
    dBankPayPhone,
    dShop,
    dShopAdaptive,
    dLicense,
	dLicenseAdaptive,
    dNavigate,
    dTeleport,
    dInviting,
    dAnim,
    dMenu,
    dStats,
    dSupport,
    dSupportAdaptive,
    dNullKarma,
    dCommandList,
    dCommandList2,
    dCommandList3,
    dMenuAdaptive,
    dMenuSettings,
    dMenuFeedback,
    dMenuFeedbackAdaptive,
    dMenuReport,
    dMenuBug,
    dMenuSug,
    dRules,
    dSelectColor,
    DIALOG_BUY_HOUSE,
    DIALOG_CMD_HOUSE
};

enum Ganginfa {capture, score, captureid};
enum GzoneInfo {gid, pic, Float:gCoords[7], gFrak, gNapad};
enum pInfo
{
	pID,
	pName[MAX_PLAYER_NAME],
	pPassword[30],
	pEmail[30],
	pDonate,
	pBanned,
	pAdmin,
	pHours,
	pColor,
	pLicense,
	pLicenseAir,
	pBank,
	pDevice,
	pBalance,
	pJob,
	pSkin,
	pSex,
	pKarma,
	pWanted,
	pFarmSkill,
	pBusSkill,
	pAirSkill,
	pCar,
	pCarCol,
	pCarCol2,
	pTaxiTotal,
	pOnline,
	pIP[MAX_LENGTH_IP],
	pJailed,
	pJailTime,
	pMuted,
	pMuteTime,
	pFreshPrice
};

enum hInfo
{
	hID,
	Float:hEntrancex,
	Float:hEntrancey,
	Float:hEntrancez,
	Float:hExitx,
	Float:hExity,
	Float:hExitz,
	Float:hCarx,
	Float:hCary,
	Float:hCarz,
	Float:hCarc,
	hOwner[MAX_PLAYER_NAME],
	hOwned,
	hInt,
	hPrice,
	hTakings,
	hPickup,
	Text3D:hText,
	hIcon,
	hClass
};

new NULL_PlayerInfo[pInfo] = {
	/* pID */ 			INVALID_ACCOUNT_ID,
	/* pName */ 		"-", 
	/* pPassword */ 	"-",
	/* pEmail */ 		"-",
	/* pDonate */		0,
	/* pBanned */ 		0,
	/* pAdmin */        0,
	/* pHours */		0,
	/* pColor */		0,
	/* pLicense */      0,
	/* pLicenseAir */   0,
	/* pBank */			0,
	/* pDevice */		0,
	/* pBalance */		0,
	/* pJob */          0,
	/* pSkin */         230, // Скин поумолчанию лучше не ставить нулевым, вдруг что-то пойдет не так и появится CJ
	/* pSex */    		0,
	/* pKarma */		0,
	/* pWanted */  		0,
	/* pFarmSkill */ 	0,
	/* pBusSkill */ 	0,
	                    0,
	/* pCar */			0, 
	/* pCarCol */		0,
	/* pCarCol2 */		0, 
	/* pTaxiTotal */	0,
	/* pOnline */ 		0,
	/* pIP */ 			"0.0.0.0",
	/* pJailed */ 		0,
	/* pJailTime */ 	0,
	/* pMuted */ 		0,
	/* pMuteTime */		0,
	/* pFreshPrice */ 	0
}; 
new Iterator:Admin<MAX_PLAYERS>;// переменная  
new pl_afk_time[MAX_PLAYERS];
new DamageTaken[MAX_PLAYERS];
new ThefStatus[MAX_PLAYERS];
new TheftZone[MAX_PLAYERS];
new stealcar_checkpoint[3];
new gonecar[MAX_PLAYERS] = {INVALID_VEHICLE_ID, ...};
new gone[MAX_PLAYERS] = {-1, ...};
new TCar[MAX_PLAYERS] = {0, ...};
new TimeTCar[MAX_PLAYERS];
new LawPrice[MAX_PLAYERS];
new caridhouse[MAX_PLAYERS] = {INVALID_VEHICLE_ID, ...};
new bool:PlayerLogged[MAX_PLAYERS char];
new spectating[MAX_PLAYERS];
new Route[MAX_PLAYERS];
new Route2[MAX_PLAYERS];
new Route3[MAX_PLAYERS];
new RouteLic[MAX_PLAYERS];
new RouteLicAir[MAX_PLAYERS];
new RouteAir[MAX_PLAYERS];
new RouteAir2[MAX_PLAYERS];
new RouteTrash[MAX_PLAYERS];
new RouteFarm[MAX_PLAYERS];
new UnloadFarm[MAX_PLAYERS];
new ArmyMission[MAX_PLAYERS];
new ArmySteal[MAX_PLAYERS];
new carry[MAX_PLAYERS];
new Client[MAX_PLAYERS];
new farm_checkpoint[5];
new farm_checkpoint_1[5];
new farm_checkpoint_2[5];
new mafia_checkpoint[6];


// 3D TEXT

new Text3D:farmtext;
new Text3D:farmtext1;
new Text3D:farmtext2;

// TEXTDRAWS

new PlayerText:FULLRECON[MAX_PLAYERS];

// NEW
new Menu:AdminMenu;
new Harvest[3];
new HarvestAmount;
new Airport[6];
new Shop[2];
new DrivingSchool[4];
new Runway[2];
new prize;
new award;


new requestt[MAX_PLAYERS] = {INVALID_TIMER_ID, ...}; 
new vehfixtimer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...}; 
new RobTimer[MAX_PLAYERS]  = {INVALID_TIMER_ID, ...};
new AzinoTimer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};
new DrugTimer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};
new Timer_Speed[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};
new CopTimerID[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};
new PlayerTimerID[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};
new LeaveTimer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};
new LawTimer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};
new bskin[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};
new farming[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};
new BinTimer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};
new routetimer[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};
new ReturnTimerID[MAX_PLAYERS] = {INVALID_TIMER_ID, ...};


new orders;
new Float:acarsd[][3] = {
	{2120.0693,2718.2942,10.8203},
	{-1931.6606,271.5569,41.0469},
	{2507.9807,-2113.6448,13.5469}
};
new invite_type = 0;
new LawyerOk;
new bool:PayDDoS;

new Lawyer = INVALID_PLAYER_ID;
new GZInfo[150][GzoneInfo];
new GangInfo[30][Ganginfa];
new PlayerInfo[MAX_PLAYERS][pInfo];
new OLD_HouseInfo[690][hInfo];
new fbi[4];
new TheftAuto[4];
new Warehouse[11];
new Stole[11];
new TotalZones[7];
new GetLicense;
new startcapture = 0;
new gang_profit[7];
new napad = 0, frak = 0;
new ZoneOnBattle[150];new GZSafeTime[150];
new IsCapture = 0;
new ZoneCapture = -1;
new TOTALGZ = 0, ATM[50];
new database;
new selcol[2];
new bank[5];
new cloth[8];
new veh_update;
new Azino[2];
new Farm[5];
new Trash[2];
new CasEn[2];
new TOTALHOUSE = 0;
new gangzone;
new HARVEST_CAR[3];
new robbery[15]; // Пикап
new shop[15]; // Если был nограблен недавно
new robber[15]; // ID грабителя
new drugs;
new lspd[7], mayor[6], grove[3], ballas[3], vagos[3], rifa[3], aztec[3];
new russian[3], triad[3], danang[3], lawstart;
new army;
new ShopBuy[4];
new Cloth[8];
new month, day, hour, minute, second;
new h00[64],h01[64],h02[64];

stock SPD(playerid, dialogid, style, caption[], info[], button1[], button2[])
{
    SetPVarInt(playerid, "DialogID", dialogid);
    return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}
forward bool:Player.Kick(const playerid, const reason[MAX_KICK_REASON], const adminid);
#include <YSI-Include\YSI\YSI\y_testing>
#include <player/kick_system>
#include <core/exp_system>
#include <core/vehicle_utils>
#include <player/fraction_system.pwn>
#include <core/vehicle_system.pwn>
#include <core/textdraw_system.inc>
#include <core/npc_system.inc>

#include <core/saloon.inc>
#include <admin/command/lip.pwn>
#include <player/last_date.pwn>
#include <player/utils.inc>

#include <jobs/dealer.inc>
#include <jobs/porter_system.inc>
#include <jobs/army_plant.inc>
#include <jobs/farm_system>
#include <core/api.casino_log.pwn>
#include <player/player_vehicle>
#include <player/casino_system.pwn>
#include <player/gps_system.pwn>
#include <core/army_utils>
#include <house/house_system>

main() {

}

public OnGameModeInit()
{
	NPC_OnGameModeInit();

	DisableInteriorEnterExits();

	new server_ip[MAX_LENGTH_IP + 1];
	GetConsoleVarAsString("bind", server_ip, sizeof(server_ip));

	if(strcmp(server_ip, GLOBAL_SERVER_IP, false) == 0) {
		test_server = false;
	} else {
		test_server = true;
	}

    gettime(hour, minute, second);

    Saloon_OnGameModeInit();
	Dealer_OnGameModeInit();
	Porter_OnGameModeInit();
	
	CallLocalFunction("Casino_OnGameModeInit", "");
	CallLocalFunction("Gps_OnGameModeInit", "");
	CallLocalFunction("Army_OnGameModeInit", "");
	CallLocalFunction("AT_OnGameModeInit", "");

	AdminMenu = CreateMenu(!" ", 1, 20.0, 170.0, 70.0);
	
	AddMenuItem(AdminMenu, 0, !"Get Stats");
	AddMenuItem(AdminMenu, 0, !"Weapons");
	AddMenuItem(AdminMenu, 0, !"Exit");

    AddPlayerClass(0, 1176.9836,-1324.4713,14.0483, 270, 0, 0, 0, 0, 0, 0); // CJ


   	CreateDynamicMapIcon(1563.8204, -1671.4923, 57.8009, 30, -1, 0, -1, -1, 400.0); // LSPD
   	CreateDynamicMapIcon(1176.9836,-1324.4713,14.0483, 22, -1, 0, -1, -1, 400.0); // LSPD

   	CreateDynamicMapIcon(1481.0507,-1772.3134,18.7958, 19, -1, 0, -1, -1, 400.0); // Mayor
   	CreateDynamicMapIcon(1802.6400,-1933.9400,13.1208, 42, -1, 0, -1, -1, 400.0); // Taxi
   	CreateDynamicMapIcon(2495.3301,-1690.2500,14.7656, 62, -1, 0, -1, -1, 400.0); // Grove
   	CreateDynamicMapIcon(2650.7041,-2021.8694,14.1766, 59, -1, 0, -1, -1, 400.0); // Ballas
	CreateDynamicMapIcon(2185.7859,-1815.2279,13.5469, 61, -1, 0, -1, -1, 400.0); // Rifa
	CreateDynamicMapIcon(2770.6299,-1628.7222,12.1775, 60, -1, 0, -1, -1, 400.0); // Vagos
	CreateDynamicMapIcon(1667.4684,-2106.9395,14.0723, 58, -1, 0, -1, -1, 400.0); // Aztec
	
	CreateDynamicMapIcon(-2026.9200,-99.9395,35.1641, 36, -1, 0, -1, -1, 400.0); // School
    CreateDynamicMapIcon(-2456.1501,503.9343,30.0781, 16, -1, 0, -1, -1, 400.0); // FBI

	CreateDynamicMapIcon(1832.5164,-1839.8253,13.5781, 38, -1, 0, -1, -1, 400.0); // Rob
	CreateDynamicMapIcon(1836.0077,-1685.6646,13.3659, 48, -1, 0, -1, -1, 400.0); // Rob
	CreateDynamicMapIcon(2104.3569,-1804.0612,13.5547, 29, -1, 0, -1, -1, 400.0); // Rob
	CreateDynamicMapIcon(2240.6370,-1663.2640,15.4766, 45, -1, 0, -1, -1, 400.0); // Rob
	CreateDynamicMapIcon(2417.8423,-1220.9553,25.2661, 48, -1, 0, -1, -1, 400.0); // Rob
	CreateDynamicMapIcon(2227.8115,-1720.2245,13.5404, 54, -1, 0, -1, -1, 400.0); // Rob
 	CreateDynamicMapIcon(1975.5535,-2039.1237,13.5469, 39, -1, 0, -1, -1, 400.0); // Rob
	CreateDynamicMapIcon(2071.3540,-1796.2771,13.5533, 7, -1, 0, -1, -1, 400.0); // Rob
 	CreateDynamicMapIcon(2069.6985,-1776.5570,13.5576, 39, -1, 0, -1, -1, 400.0); // Rob
 	CreateDynamicMapIcon(2312.5066,-1645.4086,14.8270, 49, -1, 0, -1, -1, 400.0); // Rob
	CreateDynamicMapIcon(2420.4644,-1506.0500,24.0000, 14, -1, 0, -1, -1, 400.0); // Rob
	CreateDynamicMapIcon(2722.7866,-2024.4041,13.5472, 7, -1, 0, -1, -1, 400.0);

	CreateDynamicMapIcon(987.4270,-1433.8590,13.5469, 27, -1, 0, -1, -1, 400.0);

	CreateDynamicMapIcon(-378.2507,-1426.5870,27.8482, 11, -1, 0, -1, -1, 400.0);
	
	CreateDynamicMapIcon( -1403.2114,495.5126,3.0391,51, -1, 0, -1, -1, 400.0);
	CreateDynamicMapIcon( -1540.1362,113.6978,17.3226,51, -1, 0, -1, -1, 400.0);
	CreateDynamicMapIcon( 1653.5594,1614.4609,10.8203,51, -1, 0, -1, -1, 400.0);

	CreateDynamicMapIcon( -2240.8008,575.6141,35.1719,43, -1, 0, -1, -1, 400.0);
	CreateDynamicMapIcon( -1696.4738,1329.2496,7.1787,44, -1, 0, -1, -1, 400.0);
	CreateDynamicMapIcon( 939.6087,1733.3231,8.8516,34, -1, 0, -1, -1, 400.0);
	
	CreateDynamicMapIcon(452.7378,-1478.5145,30.8151, 45, -1, 0, -1, -1, 400.0); 
	CreateDynamicMapIcon(460.8869,-1501.0599,31.0573, 45, -1, 0, -1, -1, 400.0); 
	CreateDynamicMapIcon(501.7810,-1358.5000,16.1252, 45, -1, 0, -1, -1, 400.0); // Aztec

	CreateDynamicMapIcon(2168.3401,-1673.5699,15.0831, 23, -1, 0, -1, -1, 400.0); // Drugs
	CreateDynamicMapIcon(1411.5537,-1699.5339,13.5395, 52, -1, 0, -1, -1, 400.0); // Bank
	CreateDynamicMapIcon(1021.1028,-1124.1097,23.8691, 25, -1, 0, -1, -1, 400.0); // Bank
	
	CreateDynamicMapIcon(1672.5366,1447.8470,10.7881, 5, -1, 0, -1, -1, 400.0);
	CreateDynamicMapIcon(1956.7334,-2183.6377,13.5469, 5, -1, 0, -1, -1, 400.0);
	
	CreateDynamicMapIcon(2199.4915,-1972.9595,13.5580, 11, -1, 0, -1, -1, 400.0);
    
	CreateDynamicMapIcon(1911.2516,-1774.7469,13.3828, 55, -1, 0, -1, -1, 400.0);

	CreateDynamicMapIcon(1977.9124,-1970.7001,16.6941, 51, -1, 0, -1, -1, 400.0);

    
    mafia_checkpoint[0] = CreateDynamicCP(-2106.4368,132.0322,35.1935, 3.0, -1, -1, -1, 8000.00);
	mafia_checkpoint[1] = CreateDynamicCP(-2122.2070,654.7863,52.3672, 3.0, -1, -1, -1, 8000.00);
	mafia_checkpoint[2] = CreateDynamicCP(-1948.7054,792.5362,55.7225, 3.0, -1, -1, -1, 8000.00);
	mafia_checkpoint[3] = CreateDynamicCP(-1940.4590,1227.4091,31.6296, 3.0, -1, -1, -1, 8000.00);
	mafia_checkpoint[4] = CreateDynamicCP(-2679.0647,1453.6533,7.1016, 3.0, -1, -1, -1, 8000.00);
	mafia_checkpoint[5] = CreateDynamicCP(-1352.5209,-237.4459,14.1484, 3.0, -1, -1, -1, 8000.00);

	farm_checkpoint[0] = CreateDynamicCP(-244.0340,-1374.5000,10.2968, 1.5, -1, -1, -1);
	farm_checkpoint[1] = CreateDynamicCP( -244.5132,-1379.3893,10.1628, 1.5, -1, -1, -1);
	farm_checkpoint[2] = CreateDynamicCP( -241.7643,-1376.9087,10.1990, 1.5, -1, -1, -1);
	farm_checkpoint[3] = CreateDynamicCP( -241.9362,-1378.9124,10.1594, 1.5, -1, -1, -1);
	farm_checkpoint[4] = CreateDynamicCP( -243.1588,-1375.3256,10.2700, 1.5, -1, -1, -1);
	
	farm_checkpoint_1[0] = CreateDynamicCP(-309.6248,-1350.7216,8.6985, 1.5, -1, -1, -1);
	farm_checkpoint_1[1] = CreateDynamicCP(-307.9674,-1350.7539,8.5948, 1.5, -1, -1, -1);
	farm_checkpoint_1[2] = CreateDynamicCP(-305.9592,-1350.8691,8.4713, 1.5, -1, -1, -1);
	farm_checkpoint_1[3] = CreateDynamicCP(-305.0207,-1348.0299,8.3307, 1.5, -1, -1, -1);
	farm_checkpoint_1[4] = CreateDynamicCP(-307.8632,-1350.9745,8.5945, 1.5, -1, -1, -1);

	farm_checkpoint_2[0] = CreateDynamicCP(-288.2651,-1415.0011,12.3010, 1.5, -1, -1, -1);
	farm_checkpoint_2[1] = CreateDynamicCP(-288.8513,-1412.6829,12.4116, 1.5, -1, -1, -1);
	farm_checkpoint_2[2] = CreateDynamicCP(-289.2064,-1410.0813,12.5129, 1.5, -1, -1, -1);
	farm_checkpoint_2[3] = CreateDynamicCP(-290.9688,-1410.3022,12.6391, 1.5, -1, -1, -1);
	farm_checkpoint_2[4] = CreateDynamicCP(-290.4985,-1414.4073,12.4860, 1.5, -1, -1, -1);


	stealcar_checkpoint[0] = CreateDynamicCP(2120.0693,2718.2942,10.8203,8, -1, -1, -1, 8000.00);
	stealcar_checkpoint[1] = CreateDynamicCP(-1931.6606,271.5569,41.0469,8, -1, -1, -1, 8000.00);
	stealcar_checkpoint[2] = CreateDynamicCP(2507.9807,-2113.6448,13.5469,8, -1, -1, -1, 8000.00);

	prize = 0;
	HarvestAmount = 600;
   	gangzone = GangZoneCreate(-84, 1632, 437, 2144);

	SetNameTagDrawDistance(25.0); // Отображение ника
	
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_STREAMED);
	LimitPlayerMarkerRadius(35.0);

    SetTimer("AdverseChance", (10 * 60) * 1000, false);

	SetTimer("UpdateTimers", 1000, false);
	   
    SendRconCommand("ackslimit 5000");

    Lawyer = INVALID_PLAYER_ID;
    
    SetWeather(RandomEx(0,7));
    SetWorldTime(hour);
    
	SetGameModeText("Android");
	EnableStuntBonusForAll(0);
  
	SendRconCommand("rcon_password "SERVER_RCON_PASSWORD"");

	database = mysql_connect(MYSQL_HOSTNAME, MYSQL_USERNAME, MYSQL_DATABASE, MYSQL_PASSWORD);
	mysql_log();
	mysql_pquery(database, !"SET NAMES cp1251");
	CallLocalFunction("OnDataBaseConnect", "");
	printf("[MySQL] Подключение к базе данных сервера ...");
	if(mysql_errno()==0) printf("[!] Подключение к базе данных MySQL успешно");
	else printf("[X] Подключиться к базе данных MySQL не удалось");

	mysql_pquery(database, "UPDATE `players` SET `isOnline` = '0'");

	//mysql_pquery(database,"SELECT * FROM `apartment`","LoadProperty","");
	mysql_pquery(database,"SELECT * FROM `gz`","LoadGangZone","");
	mysql_pquery(database,"SELECT * FROM `warehouse`","LoadWareHouse","");

	CallLocalFunction("Vehicle_OnGameModeInit", "");

	Airport[0] = CreateDynamicPickup(1318, 1, 1672.5366,1447.8470,10.7881);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Аэропорт Las Venturas", -1, 1672.5366,1447.8470,10.7881 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	Airport[1] = CreateDynamicPickup(1318, 1, 1598.2906,1448.3082,10.8281);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход", -1, 1598.2906,1448.3082,10.8281 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	Airport[2] = CreateDynamicPickup(1318, 1, 1956.7334,-2183.6377,13.5469);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Аэропорт Los Santos", -1, 1956.7334,-2183.6377,13.5469 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	Airport[3] = CreateDynamicPickup(1318, 1, 1891.9253,-2328.6743,13.5469);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход", -1, 1891.9253,-2328.6743,13.5469 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	Airport[4] = CreateDynamicPickup(1318, 1, 1685.7137,-2335.2058,-2.6797);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Зал прибытия\n[Вход закрыт]", -1, 1685.7137,-2335.2058,-2.6797 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	Airport[5] = CreateDynamicPickup(1318, 1, 1688.7778,-2344.9832,1905.4918);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход", -1, 1688.7778,-2344.9832,1905.4918 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 0, -1, MAX_DISTANCE_VISIBLE
	);

	Shop[0] = CreateDynamicPickup(1318, 1, 1833.7786,-1842.6016,13.5781);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Магазин 24/7", -1, 1833.7786,-1842.6016,13.5781 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	Shop[1] = CreateDynamicPickup(1318, 1, -31.0068,-92.0113,1003.5469);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход", -1, -30.9903,-92.0113,1003.5469 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 18, -1, MAX_DISTANCE_VISIBLE
	);
	
	DrivingSchool[0] = CreateDynamicPickup(1318, 1, -2026.7,-101.7283,35.1641);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Автошкола", -1, -2026.6150,-101.7283,35.1641 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	DrivingSchool[1] = CreateDynamicPickup(1318, 1, -2026.9160,-103.6016,1035.1836);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход", -1, -2026.9160,-103.6016,1035.1836 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 3, -1, MAX_DISTANCE_VISIBLE
	);
	DrivingSchool[2] = CreateDynamicPickup(1318, 1, -2029.7272,-119.4593,1035.1719);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Задний двор", -1, -2029.7272,-119.4593,1035.1719 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 3, -1, MAX_DISTANCE_VISIBLE
	);
	DrivingSchool[3] = CreateDynamicPickup(1318, 1, -2029.7726,-120.5243,35.1692);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Вход", -1, -2029.7726,-120.5243,35.1692 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 0, -1, MAX_DISTANCE_VISIBLE
	);


	Stole[0] = CreateDynamicPickup(3014, 1,155.1125,1903.3162,18.7070); // stole
	Stole[1] = CreateDynamicPickup(3014, 1,142.0078,1875.4172,17.8434); // stole
	Stole[2] = CreateDynamicPickup(3014, 1,137.4299,1880.2441,17.8359); // stole
	Stole[3] = CreateDynamicPickup(3014, 1,117.9066,1870.5021,17.8359); // stole
	Stole[4] = CreateDynamicPickup(3014, 1,114.8998,1875.1660,17.8359); // stole
	Stole[5] = CreateDynamicPickup(3014, 1,171.5373,1834.8550,17.6406); // stole
	Stole[6] = CreateDynamicPickup(3014, 1,177.0867,1840.9473,17.6406); // stole
	Stole[7] = CreateDynamicPickup(3014, 1,233.2366,1840.9581,17.6406); // stole
	Stole[8] = CreateDynamicPickup(3014, 1,223.2820,1931.4896,17.64068); // stole
	Stole[9] = CreateDynamicPickup(3014, 1,192.5569,1931.4658,17.6406); // stole

	
	GetLicense = CreateDynamicPickup(1581, 1, -2026.7618,-114.8348,1035.1719);
	busstop = CreateDynamicPickup(1239, 1, 1686.2130,-2310.7441,-2.6641);
	

	ATM[0] = CreateDynamicCP(1464.4418,-1749.2397,15.4453,0.8,-1,-1,-1,10);
	ATM[1] = CreateDynamicCP(1094.9678,-1803.0066,13.6040,0.8,-1,-1,-1,10);
	ATM[2] = CreateDynamicCP(-382.3102,-1433.5862,25.7266,0.8,-1,-1,-1,10);
	ATM[3] = CreateDynamicCP(562.3327,-1293.2828,17.2482,0.8,-1,-1,-1,10);
	ATM[4] = CreateDynamicCP(1028.9017,-1117.9712,23.8849,0.8,-1,-1,-1,10);
	ATM[5] = CreateDynamicCP(1752.2013,-1898.7198,13.5575,0.8,-1,-1,-1,10);
	ATM[6] = CreateDynamicCP(460.8766,-1511.9993,30.9612,0.8,-1,-1,-1,10);
	ATM[7] = CreateDynamicCP(-1981.2650,121.8104,27.6875,0.8,-1,-1,-1,10); //
	ATM[8] = CreateDynamicCP(-2243.0112,116.3192,35.3203,0.8,-1,-1,-1,10); //
	ATM[9] = CreateDynamicCP(-2035.2722,-101.3710,35.1641,0.8,-1,-1,-1,10); //
	ATM[10] = CreateDynamicCP(-1828.0797,3.9696,15.1172,0.8,-1,-1,-1,10); //
	ATM[11] = CreateDynamicCP(-1692.5946,414.8079,7.1797,0.8,-1,-1,-1,10); //
	ATM[12] = CreateDynamicCP(-1641.5057,1208.0884,7.1797,0.8,-1,-1,-1,10); //
	ATM[13] = CreateDynamicCP(-2629.3960,1404.4480,7.0938,0.8,-1,-1,-1,10); //
	ATM[14] = CreateDynamicCP(-855.8322,1529.5223,22.5870,0.8,-1,-1,-1,10); //
	ATM[15] = CreateDynamicCP(-300.2624,1045.5856,19.5831,0.8,-1,-1,-1,10); //
	ATM[16] = CreateDynamicCP(54.3784,1211.0280,18.8838,0.8,-1,-1,-1,10); //
	ATM[17] = CreateDynamicCP(2107.8774,897.4530,11.1797,0.8,-1,-1,-1,10); //
	ATM[18] = CreateDynamicCP(2089.8708,1459.7363,10.8203,0.8,-1,-1,-1,10); //
	ATM[19] = CreateDynamicCP(2086.3210,2059.5881,11.0579,0.8,-1,-1,-1,10); //
	ATM[20] = CreateDynamicCP(1629.1119,1811.4559,10.8203,0.8,-1,-1,-1,10); //
	ATM[21] = CreateDynamicCP(1715.8502,1533.0742,10.7629,0.8,-1,-1,-1,10); //
	ATM[22] = CreateDynamicCP(1718.5215,1312.8833,10.8052,0.8,-1,-1,-1,10); //
	ATM[23] = CreateDynamicCP(2271.1575,82.7118,26.4844,0.8,-1,-1,-1,10); //
	ATM[24] = CreateDynamicCP(-2444.5059,512.8886,29.9181,0.8,-1,-1,-1,10); //
	ATM[25] = CreateDynamicCP(-1968.6960,458.5023,35.1719,0.8,-1,-1,-1,10); //
	ATM[26] = CreateDynamicCP(2019.9667,1014.0970,10.8203,0.8,-1,-1,-1,10);
	ATM[27] = CreateDynamicCP(2107.3406,897.4306,11.1797,0.8,-1,-1,-1,10);
	ATM[28] = CreateDynamicCP(2499.6074,926.6871,11.0234,0.8,-1,-1,-1,10);
	ATM[29] = CreateDynamicCP(2646.2542,1129.0181,11.1797,0.8,-1,-1,-1,10);
	ATM[30] = CreateDynamicCP(2848.7437,1294.3943,11.3906,0.8,-1,-1,-1,10);
	ATM[31] = CreateDynamicCP(2637.9407,1675.5981,11.0234,0.8,-1,-1,-1,10);
	ATM[32] = CreateDynamicCP(2638.0032,1852.8722,11.0234,0.8,-1,-1,-1,10);
	ATM[33] = CreateDynamicCP(2466.8394,2031.9677,11.0625,0.8,-1,-1,-1,10);
	ATM[34] = CreateDynamicCP(2565.0981,2064.7314,11.0995,0.8,-1,-1,-1,10);
	ATM[35] = CreateDynamicCP(2366.4106,2084.5137,10.8203,0.8,-1,-1,-1,10);
	ATM[36] = CreateDynamicCP(2086.3455,2083.1289,11.0579,0.8,-1,-1,-1,10);
	ATM[37] = CreateDynamicCP(2173.2346,1411.7605,11.0625,0.8,-1,-1,-1,10);
	ATM[38] = CreateDynamicCP(2281.9297,2431.7458,10.8203,0.8,-1,-1,-1,10);
	ATM[39] = CreateDynamicCP(2188.3606,2478.7637,11.2422,0.8,-1,-1,-1,10);
	ATM[40] = CreateDynamicCP(1697.1517,2208.4438,11.0692,0.8,-1,-1,-1,10);
	ATM[41] = CreateDynamicCP(1590.9152,2217.3467,11.0692,0.8,-1,-1,-1,10);
	ATM[42] = CreateDynamicCP(1163.6672,2075.2834,11.0625,0.8,-1,-1,-1,10);
	ATM[43] = CreateDynamicCP(1665.2988,1412.9814,10.7907,0.8,-1,-1,-1,10);
	ATM[44] = CreateDynamicCP(1665.7294,1483.0128,10.7757,0.8,-1,-1,-1,10);
	ATM[45] = CreateDynamicCP(1695.5045,-2340.9226,1905.4918,0.8,-1,-1,-1,10);

	ATM[46] = CreateDynamicCP(1697.6161,-2334.7483,-2.6797,0.8,-1,-1,-1,10);
	ATM[47] = CreateDynamicCP(1690.8062,-2238.1514,-2.7142,0.8,-1,-1,-1,10);
	ATM[48] = CreateDynamicCP(1690.9069,-2238.1672,13.5396,0.8,-1,-1,-1,10);
	ATM[49] = CreateDynamicCP(1680.3893,-2334.7571,13.5469,0.8,-1,-1,-1,10);
	
	bank[0] = CreateDynamicPickup(1318, 1, 1411.5537,-1699.5339,13.5395); // LSPD Info
	bank[1] = CreateDynamicPickup(1318, 1, 1398.5265,-1678.1429,13.5911); // LSPD Info
	bank[2] = CreateDynamicPickup(1239, 1, 1401.3951,-1681.3376,13.5838); // LSPD Info
	bank[3] = CreateDynamicPickup(1272, 1, 1406.3142,-1681.9421,13.5838); // LSPD Info
	bank[4] = CreateDynamicPickup(1273, 2, 1412.3156,-1681.5946,13.5838);
	
	cloth[0] = CreateDynamicPickup(1275, 1, 217.4962,-98.0213,1005.2578);
	cloth[1] = CreateDynamicPickup(1274, 1, 207.5148,-100.3269,1005.2578);
	
	cloth[2] = CreateDynamicPickup(1275, 1, 215.9162,-155.1320,1000.5234); // VIP CHOOSE
	cloth[3] = CreateDynamicPickup(1274, 1, 204.2251,-159.3508,1000.5234); // VIP BUY

	cloth[4] = CreateDynamicPickup(1275, 1, 209.5619,-8.1712,1005.2109); // VIP CHOOSE
	cloth[5] = CreateDynamicPickup(1274, 1, 206.4406,-7.2221,1001.2109); // VIP BUY
	
	cloth[6] = CreateDynamicPickup(1275, 1, 215.1475,-127.2374,1003.5078); // VIP CHOOSE
	cloth[7] = CreateDynamicPickup(1274, 1, 207.1071,-129.1781,1003.5078); // VIP BUY
	

	lspd[0] = CreateDynamicPickup(1239, 1, 248.8600, 67.9528, 1003.6406); // LSPD Info
	lspd[1] = CreateDynamicPickup(1275, 2, 255.1575, 74.1185, 1003.6406); // LSPD Invite
	lspd[2] = CreateDynamicPickup(1318, 1, 246.4044, 87.4060, 1003.6406); // LSPD Garage
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Гараж", -1, 246.4044, 87.4060, 1003.6406 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 6, -1, MAX_DISTANCE_VISIBLE
	);

	lspd[3] = CreateDynamicPickup(1318, 1, 1555.5010,-1675.6099,16.1953); // LSPD Enter	
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Полицейский департамент", -1, 1555.5010,-1675.6099,16.1953 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	lspd[4] = CreateDynamicPickup(1318, 1, 246.8044,62.3250,1003.6406); // LSPD EXit
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход", -1, 246.8044,62.3250,1003.6406 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 6, -1, MAX_DISTANCE_VISIBLE
	);

	lspd[5] = CreateDynamicPickup(1318, 1, 1568.5867,-1689.9714,6.2188); // LSPD EXit
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Вход в здание", -1, 1568.5867,-1689.9714,6.2188 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	
	lspd[6] = CreateDynamicPickup(321, 8, 261.2201,71.0876,1003.2422);

	CreateDynamic3DTextLabel(!""COLOR_BLUE"Банк штата", -1, 1411.5537,-1699.5339,13.5395 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Цвет 1", -1, 987.4270,-1433.8590,13.5469 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	CreateDynamic3DTextLabel(!""COLOR_BLUE"Цвет 2", -1, 989.8574,-1433.9150,13.5469 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	
	fbi[0] = CreateDynamicPickup(1318, 1, -2456.1501,503.9343,30.0781);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Федеральное бюро расследований", -1, -2456.1501,503.9343,30.0781 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);

	fbi[1] = CreateDynamicPickup(1318, 1, -2500.1760,538.6120,432.6819);
	fbi[2] = CreateDynamicPickup(1314, 2, -2454.8999,513.4279,432.6819);
	fbi[3] = CreateDynamicPickup(1239, 2, -2487.7549,527.0223,432.6819);
	
	LawyerOk = CreateDynamicPickup(1239, 1, 265.9039,77.5524,1001.0391);
	lawstart = CreateDynamicPickup(1275, 2, 257.1116,85.6978,1002.4453);

	mayor[0] = CreateDynamicPickup(1318, 1, 1481.2323,-1728.4963,479.2806); // LSPD Garage
	mayor[1] = CreateDynamicPickup(1318, 1, 1481.0507,-1772.3134,18.7958); // LSPD Garage
	mayor[2] = CreateDynamicPickup(1239, 1, 1481.3876,-1756.9603,479.2806); // Собеседование
	mayor[3] = CreateDynamicPickup(1314, 2, 1469.7438,-1747.1573,479.2871);
	mayor[4] = CreateDynamicPickup(1240, 2, 1469.3823,-1759.7278,479.2806);
	mayor[5] = CreateDynamicPickup(1581, 2, 1489.9640,-1760.1608,479.2806);
	
	Azino[0] = CreateDynamicPickup(1212, 1, 1023.1614,-1192.7471,29.6481);
	Azino[1] = CreateDynamicPickup(1212, 1, 1022.9764,-1196.7971,29.6690);
	
	
	selcol[0] = CreateDynamicPickup(1851, 1, 987.4270,-1433.8590,13.5469);
	selcol[1] = CreateDynamicPickup(1852, 1, 989.8574,-1433.9150,13.5469);


	
	drugs = CreateDynamicPickup(1241, 2, 324.1805,1120.0266,1083.8828);
	
	russian[0] = CreateDynamicPickup(1318, 1, 1061.9630,1548.5292,5.9481);
	russian[1] = CreateDynamicPickup(1318, 1, 937.0792,1733.2640,8.8516);
	russian[2] = CreateDynamicPickup(1314, 2, 1075.8735,1547.1483,5.9481);
	
	triad[0] = CreateDynamicPickup(1318, 1, -2261.0024,475.8131,38.5965);
	triad[1] = CreateDynamicPickup(1318, 1, -2240.5686,578.0452,35.1719);
	triad[2] = CreateDynamicPickup(1314, 1, -2260.8091,476.7599,43.8153);
	
	danang[0] = CreateDynamicPickup(1318, 1, -1694.2039,1331.0332,7.1826);
	danang[1] = CreateDynamicPickup(1318, 1, -1534.4545,1152.1315,7.2198);
	danang[2] = CreateDynamicPickup(1314, 2, -1539.8248,1139.8961,7.2198);
	
	grove[0] = CreateDynamicPickup(1314, 2, 2495.8857,-1711.7562,1014.7422); // Grove Home
	grove[1] = CreateDynamicPickup(1318, 1, 2495.3752,-1691.1403,14.7656); // Grove Home
	grove[2] = CreateDynamicPickup(1318, 1, 2495.9780,-1692.0837,1014.7422); // Grove Home


	ballas[0] = CreateDynamicPickup(1318, 1, 2650.7041,-2021.8694,14.1766);
	ballas[1] = CreateDynamicPickup(1318, 1, 2738.1282,-1787.9785,25.5031);
	ballas[2] = CreateDynamicPickup(1314, 2, 2738.2268,-1772.9186,25.5031);
	
	vagos[0] = CreateDynamicPickup(1318, 1, 2770.6299,-1628.7222,12.1775);
	vagos[1] = CreateDynamicPickup(1318, 1,2693.3994,-1576.3605,20.0395);
	vagos[2] = CreateDynamicPickup(1314, 2, 2687.4824,-1574.4425,20.0395);
	
	rifa[0] = CreateDynamicPickup(1318, 1, 2185.7859,-1815.2279,13.5469);
	rifa[1] = CreateDynamicPickup(1318, 1, 2154.0859,-1781.8308,13.786);
	rifa[2] = CreateDynamicPickup(1314, 2, 2147.9331,-1776.0917,13.7867);
	
	aztec[0] = CreateDynamicPickup(1318, 1, 1667.4684,-2106.9395,14.0723);
	aztec[1] = CreateDynamicPickup(1318, 1, 1674.1849,-2049.2502,14.2069);
	aztec[2] = CreateDynamicPickup(1314, 2, 1667.4358,-2049.2673,14.2069);
	
	army =  CreateDynamicPickup(1314, 2, 117.3086,1934.0143,19.1802);

	
	ShopBuy[0] = CreateDynamicPickup(1274, 2, -28.0933,-89.9526,1003.5469);
	ShopBuy[1] = CreateDynamicPickup(1274, 1, 499.9389,-20.6713,1000.6797);
	ShopBuy[2] = CreateDynamicPickup(1274, 1, 1215.1317,-13.1425,1000.9219);
	ShopBuy[3] = CreateDynamicPickup(1486, 1, 1002.1785,-1190.6299,29.6403);

	Cloth[0] = CreateDynamicPickup(1318, 1, 2244.3032,-1665.5431,15.4766); 
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Binco", -1, 2244.3032,-1665.5431,15.4766 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	Cloth[1] = CreateDynamicPickup(1318, 1, 207.6675,-111.2618,1005.1328); 
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход", -1, 207.6675,-111.2618,1005.1328 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 15, -1, MAX_DISTANCE_VISIBLE
	);

	Cloth[2] = CreateDynamicPickup(1318, 1, 461.6974,-1500.9,31.0459); 
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Victim", -1, 461.6974,-1500.7443,31.0459 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	Cloth[3] = CreateDynamicPickup(1318, 1, 227.2169,-8.2642,1002.2109); 
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход", -1, 227.2169,-8.1642,1002.2109 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 5, -1, MAX_DISTANCE_VISIBLE
	);

	Cloth[4] = CreateDynamicPickup(1318, 1, 454.1967,-1477.9600,30.8133); 
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Didier Sachs", -1, 454.1967,-1477.9600,30.8133 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	Cloth[5] = CreateDynamicPickup(1318, 1, 204.3369,-168.8608,1000.5234); 
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход", -1, 204.3169,-168.8608,1000.5234 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 14, -1, MAX_DISTANCE_VISIBLE
	);

	Cloth[6] = CreateDynamicPickup(1318, 1, 499.5291,-1360.6333,16.3691); 
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Pro Laps", -1, 499.5291,-1360.6333,16.3691 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	Cloth[7] = CreateDynamicPickup(1318, 1, 207.0097,-140.3764,1003.5078); 
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Выход", -1, 207.0097,-140.3764,1003.5078 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 3, -1, MAX_DISTANCE_VISIBLE
	);



	robbery[0] = CreateDynamicPickup(1254, 1, 1832.5164,-1839.8253,13.5781);
	robbery[1] = CreateDynamicPickup(1254, 1, 1836.0077,-1685.6646,13.3659);
	robbery[2] = CreateDynamicPickup(1254, 1, 2104.3569,-1804.0612,13.5547);
	robbery[3] = CreateDynamicPickup(1254, 1, 2240.6370,-1663.2640,15.4766);
	robbery[4] = CreateDynamicPickup(1254, 1, 2417.8423,-1220.9553,25.2661);
	robbery[5] = CreateDynamicPickup(1254, 1, 2227.8115,-1720.2245,13.5404);
	robbery[6] = CreateDynamicPickup(1254, 1, 1975.5535,-2039.1237,13.5469);
	robbery[7] = CreateDynamicPickup(1254, 1, 2071.3540,-1796.2771,13.5533);
	robbery[8] = CreateDynamicPickup(1254, 1, 2069.6985,-1776.5570,13.5576);
	robbery[9] = CreateDynamicPickup(1254, 1, 2312.5066,-1645.4086,14.8270);
	robbery[10] = CreateDynamicPickup(1254, 1, 2420.4644,-1506.0500,24.0000);
	robbery[11] = CreateDynamicPickup(1254, 1, 2722.7866,-2024.4041,13.5472);
	
	robbery[12] = CreateDynamicPickup(2040, 1, -1403.2114,495.5126,3.0391);
	robbery[13] = CreateDynamicPickup(1575, 1, -1540.1362,113.6978,17.3226);
	robbery[14] = CreateDynamicPickup(1575, 1, 1653.5594,1614.4609,10.8203);
	

	Trash[0] = CreateDynamicPickup(1239, 1, 2199.4915,-1972.9595,13.5580);

	Trash[1] = CreateDynamicPickup(1275, 1, 2195.7839,-1969.9625,13.7841);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Раздевалка", -1, 2195.7839,-1969.9625,13.7841 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Место разгрузки", -1, 2199.5505,-2035.3813,13.1105 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	
	CreateDynamic3DTextLabel(!""COLOR_BLUE"Казино", -1, 1022.5065,-1121.4209,23.8701 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	
	CasEn[0] = CreateDynamicPickup(1318, 1, 1022.5065,-1121.4209,23.8701);
	CasEn[1] = CreateDynamicPickup(1318, 1, 1008.6086,-1180.9259,29.6481);
	
	TheftAuto[0] = CreateDynamicPickup(1239, 1, 1911.2516,-1774.7469,13.3828);
	TheftAuto[1] = CreateDynamicPickup(1239,23,acarsd[0][0],acarsd[0][1],acarsd[0][2]);// Выдача мопеда автоугонщикам.
	TheftAuto[2] = CreateDynamicPickup(1239,23,acarsd[1][0],acarsd[1][1],acarsd[1][2]);// Выдача мопеда автоугонщикам.
	TheftAuto[3] = CreateDynamicPickup(1239,23,acarsd[2][0],acarsd[2][1],acarsd[2][2]);// Выдача мопеда автоугонщикам.

	CreateDynamic3DTextLabel(!""COLOR_BLUE"Мэрия штата", -1, 1481.0507,-1772.3134,18.7958 + 1.0,
	MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	// Hospital
	CreateObject(14595, 1139.036376, -1321.477050, 1791.904541, 0.000000, 0.000000, 0.000000);
	CreateDynamicObject(14638, 1113.927001, -1326.466552, 1787.951416, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1491, 1139.744873, -1308.194091, 1787.951416, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2611, 1145.446899, -1316.439453, 1790.162231, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1566, 1142.100463, -1334.054199, 1789.372436, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1566, 1142.100463, -1332.473144, 1789.372436, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1142.051391, -1333.002563, 1791.791992, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1142.051391, -1333.002563, 1791.791992, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1142.051391, -1333.002563, 1791.791992, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1142.051391, -1333.002563, 1791.791992, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1142.051391, -1333.002563, 1791.791992, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1142.051391, -1333.002563, 1791.791992, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2165, 1143.028076, -1325.879394, 1787.951416, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1796, 1144.687988, -1316.885131, 1787.951416, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1796, 1144.687988, -1321.289672, 1787.951416, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1796, 1144.687988, -1323.499389, 1787.951416, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2384, 1147.814453, -1324.666992, 1789.101440, 0.000000, 0.000000, 66.899986, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1796, 1144.687988, -1319.078735, 1787.951416, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2339, 1147.661865, -1318.083374, 1787.951416, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2339, 1147.661865, -1320.283569, 1787.951416, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2339, 1147.661865, -1322.503784, 1787.951416, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2339, 1147.661865, -1324.703857, 1787.951416, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2843, 1147.059326, -1320.558349, 1789.001953, 0.000000, 0.000000, -20.200002, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2636, 1144.168579, -1325.181030, 1788.541992, 0.000000, 0.000000, -12.999999, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16780, 1127.694213, -1301.800537, 1791.989257, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16780, 1134.706909, -1301.800537, 1791.989257, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2207, 1126.714843, -1300.887329, 1787.930786, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2208, 1130.267089, -1302.724243, 1787.841308, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2208, 1130.267089, -1300.842407, 1787.841308, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2208, 1133.627441, -1300.842407, 1787.851318, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2208, 1133.627441, -1302.713500, 1787.851318, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2207, 1134.585693, -1302.718017, 1787.940795, 0.000000, 0.000000, 450.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1714, 1125.162597, -1301.679443, 1787.951416, 0.000000, 0.000000, 123.599990, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1714, 1128.133178, -1304.366088, 1787.921386, 0.000000, 0.000000, 177.500045, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1714, 1129.603393, -1304.431274, 1787.921386, 0.000000, 0.000000, 177.500045, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1714, 1131.355468, -1304.248413, 1787.921386, 0.000000, 0.000000, 177.500045, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1714, 1133.185424, -1304.329467, 1787.921386, 0.000000, 0.000000, 177.500045, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1714, 1133.391845, -1299.312866, 1787.921386, 0.000000, 0.000000, -1.299934, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1714, 1131.820922, -1299.306274, 1787.921386, 0.000000, 0.000000, -1.299934, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1714, 1129.708862, -1299.337524, 1787.921386, 0.000000, 0.000000, -1.299934, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1714, 1128.098999, -1299.300292, 1787.921386, 0.000000, 0.000000, -1.299934, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2614, 1130.376586, -1307.853027, 1790.989135, 0.000000, 0.000000, 540.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1964, 1126.818481, -1301.383911, 1788.852294, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2258, 1141.285522, -1304.562133, 1790.378295, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2267, 1139.721191, -1298.544677, 1790.382690, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1997, 1122.020263, -1325.939453, 1787.951416, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1502, 1127.678222, -1326.672729, 1787.951416, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2603, 1125.407226, -1327.733642, 1788.341796, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2206, 1123.825439, -1333.345581, 1787.951416, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2356, 1124.415893, -1334.594238, 1787.958251, 0.000000, 0.000000, -19.900001, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1964, 1124.276000, -1333.485351, 1789.032470, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1720, 1125.335937, -1332.450927, 1787.951416, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2007, 1123.047241, -1334.656494, 1787.918212, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2131, 1130.906616, -1333.668945, 1787.951416, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2131, 1130.906616, -1331.688232, 1787.951416, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2134, 1130.906494, -1330.693969, 1787.951416, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2134, 1130.906494, -1329.692993, 1787.951416, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1778, 1131.179687, -1327.026489, 1787.951416, 0.000000, 0.000000, 36.399993, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2524, 1130.948974, -1327.847290, 1787.958251, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2272, 1127.084594, -1334.794311, 1789.701904, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1721, 1131.638793, -1326.275512, 1787.951416, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1721, 1130.958374, -1326.275512, 1787.951416, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1721, 1130.237915, -1326.275512, 1787.951416, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1721, 1126.776855, -1326.275512, 1787.951416, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1721, 1126.077026, -1326.275512, 1787.951416, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1721, 1125.366699, -1326.275512, 1787.951416, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1721, 1124.596069, -1326.275512, 1787.951416, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1724, 1104.952758, -1323.385742, 1787.951416, 0.000000, 0.000000, 148.099990, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1724, 1103.980102, -1321.149414, 1787.951416, 0.000000, 0.000000, 60.599964, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1724, 1105.941772, -1319.798583, 1787.962036, 0.000000, 0.000000, -36.700042, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1724, 1106.905761, -1322.029418, 1787.962036, 0.000000, 0.000000, -122.900047, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1815, 1104.927246, -1322.058715, 1787.951416, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2059, 1105.387695, -1321.449462, 1788.451538, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(630, 1127.018310, -1316.975708, 1788.949218, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(630, 1116.027587, -1316.975708, 1788.949218, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1997, 1139.211914, -1337.881225, 1787.951416, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(630, 1136.176147, -1338.033813, 1788.931274, 0.000000, 0.000000, 140.600021, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1776, 1131.904785, -1316.791503, 1789.002319, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1209, 1130.695068, -1316.758544, 1787.901367, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2258, 1109.135864, -1326.342407, 1790.201416, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2272, 1110.170654, -1316.871704, 1789.802124, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2282, 1147.664550, -1320.472167, 1789.870971, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	// Airport
	CreateDynamicObject(3971, 1684.403442, -2329.425781, 1907.046875, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1687.771362, -2336.541503, 1901.696533, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1687.791381, -2318.595214, 1901.696533, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1667.791259, -2318.595214, 1901.696533, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1667.791259, -2336.457031, 1901.696533, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1707.791015, -2318.595214, 1901.696533, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1707.791015, -2336.547607, 1901.696533, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1680.871582, -2339.292968, 1906.443969, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1680.871582, -2339.292968, 1906.443969, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2412, 1691.123535, -2344.823974, 1904.512451, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1673.814331, -2336.146728, 1906.903930, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1673.814331, -2336.146728, 1906.903930, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2948, 1676.432006, -2336.196533, 1904.511718, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2948, 1678.323364, -2336.190673, 1904.511718, 0.000000, 0.000000, -90.099975, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1683.633544, -2314.104980, 1905.242797, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1683.633544, -2314.104980, 1905.242797, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1694.304687, -2314.104980, 1905.242797, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1694.304687, -2314.104980, 1905.242797, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1706.896606, -2314.104980, 1905.242797, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1706.896606, -2314.104980, 1905.242797, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3354, 1661.871582, -2323.446777, 1905.792114, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3354, 1661.871582, -2328.679931, 1905.792114, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3969, 1677.386108, -2319.639892, 1905.349121, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1670.505737, -2314.236816, 1905.402099, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1670.783203, -2314.215087, 1905.242797, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3354, 1715.360595, -2323.446777, 1905.792114, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3354, 1715.360595, -2328.668457, 1905.792114, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1569, 1709.193359, -2336.246337, 1904.514282, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1569, 1713.175415, -2336.246337, 1904.514282, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3657, 1693.889648, -2338.794433, 1905.028320, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3657, 1683.356445, -2338.794433, 1905.028320, 0.000000, 0.000000, 540.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3657, 1683.356445, -2339.565185, 1905.028320, 0.000000, 0.000000, 720.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3657, 1693.890747, -2339.565185, 1905.028320, 0.000000, 0.000000, 720.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3657, 1693.889648, -2342.117675, 1905.028320, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3657, 1693.889648, -2342.878173, 1905.028320, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3657, 1683.356445, -2342.897949, 1905.028320, 0.000000, 0.000000, 720.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3657, 1683.356445, -2342.116455, 1905.028320, 0.000000, 0.000000, 540.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1696.289428, -2340.881835, 1905.057861, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1694.078735, -2311.113525, 1904.211547, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1697.418701, -2311.113525, 1904.211547, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1437, 1698.317626, -2322.615722, 1904.720581, 4.399994, 91.000129, 80.300018, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1704.578857, -2311.113525, 1904.211547, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1707.901000, -2311.113525, 1904.211547, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1680.997436, -2311.113525, 1904.211547, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1673.768676, -2311.113525, 1904.211547, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1670.505737, -2311.113525, 1904.211547, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2960, 1672.219726, -2323.993164, 1904.972290, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2960, 1682.601806, -2323.993164, 1904.972290, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2960, 1695.655151, -2323.993164, 1904.972290, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1688.643432, -2330.222167, 1904.491821, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1676.931274, -2330.222167, 1904.491821, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1700.754638, -2330.222167, 1904.491821, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1700.743530, -2319.702636, 1904.491821, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1688.621337, -2319.702636, 1904.491821, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1677.009399, -2319.702636, 1904.491821, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1684.318359, -2311.113525, 1904.211547, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2960, 1706.136962, -2323.993164, 1904.972290, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(997, 1704.626708, -2323.935546, 1904.992065, 90.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(997, 1694.124511, -2323.915527, 1904.992065, 90.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(997, 1680.911865, -2323.895507, 1904.992065, 90.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(997, 1670.498657, -2323.915527, 1904.992065, 90.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1669.852416, -2322.725585, 1904.901977, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1669.862426, -2317.963134, 1904.901977, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1674.412353, -2317.963134, 1904.901977, 180.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1674.422363, -2322.666015, 1904.901977, 180.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1684.927124, -2322.666015, 1904.901977, 180.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1698.027709, -2322.666015, 1904.901977, 180.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1708.518798, -2322.666015, 1904.901977, 180.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1703.948486, -2319.114013, 1904.901977, 180.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1693.437133, -2319.114013, 1904.901977, 180.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1680.343750, -2319.114013, 1904.901977, 180.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1708.528808, -2318.583251, 1904.901977, 180.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1698.023193, -2317.963134, 1904.901977, 180.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1680.352539, -2317.963134, 1904.901977, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1693.433105, -2317.963134, 1904.901977, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1684.943725, -2317.963134, 1904.901977, 180.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1675.671997, -2315.130859, 1904.901977, 180.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1699.220214, -2315.130859, 1904.901977, 180.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(995, 1703.942993, -2319.043701, 1904.901977, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2775, 1696.079589, -2324.783935, 1909.072631, 17.700000, 0.000000, -0.699999, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2775, 1681.812622, -2324.656494, 1909.162353, 17.099998, 0.499998, -0.500000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2775, 1683.679321, -2333.413574, 1909.179931, 17.099998, 0.499998, 179.500000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2775, 1695.252929, -2333.252197, 1909.098266, 17.099998, 0.499998, 179.500000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3570, 1682.653808, -2319.354492, 1904.181518, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3570, 1672.232910, -2319.354492, 1904.181518, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3570, 1695.956787, -2319.354492, 1904.181518, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3570, 1706.228271, -2319.354492, 1904.181518, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1705.639038, -2346.266113, 1905.857299, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1725.419311, -2327.073242, 1905.857299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1725.419311, -2309.213623, 1905.857299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1705.328857, -2304.496582, 1905.857299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1685.420043, -2304.496582, 1905.857299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1665.400756, -2304.496582, 1905.857299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1652.832153, -2323.426757, 1905.857299, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1652.832153, -2343.443359, 1905.857299, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(8569, 1662.972778, -2345.081298, 1905.847290, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1680.871582, -2342.872802, 1906.443969, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1649, 1677.775512, -2336.136962, 1906.493286, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3851, 1674.093017, -2345.393066, 1905.940673, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1680.153930, -2336.894531, 1904.491821, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1661.950317, -2336.883300, 1904.491821, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1661.039550, -2322.981445, 1905.712280, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1668.989990, -2313.359130, 1893.932495, 0.000000, 180.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2774, 1665.610229, -2312.618408, 1906.173217, 0.000000, 270.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateObject(939, 1675.614135, -2339.186523, 1906.671142, 0.000000, 0.000000, 0.000000, 300.0); // Object will render at 300.0 units.
	CreateObject(939, 1679.021240, -2340.021728, 1906.671142, 0.000000, 0.000000, -93.799949, 300.0); // Object will render at 300.0 units.
	CreateObject(2412, 1687.311767, -2344.823974, 1904.512451, 0.000000, 0.000000, 0.000000, 300.0); // Object will render at 300.0 units.
	CreateObject(4991, 1691.406494, -2339.562500, 1903.742431, 0.000000, 0.000000, 180.000000, 300.0); // Object will render at 300.0 units.
	//Int LSPD
	CreateDynamicObject(2047, 216.040802, 73.954193, 1006.719543, 0.000000, 0.000000, 178.800018, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2206, 215.913619, 77.287322, 1004.044921, 0.000000, 0.000000, -90.400009, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1736, 214.224395, 76.317474, 1006.804809, 0.000000, 0.000000, 91.699989, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1714, 214.391418, 76.338249, 1004.024902, 0.000000, 0.000000, 88.400093, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1815, 215.653884, 81.118873, 1004.019042, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1368, 264.352661, 75.752357, 1000.679321, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1704, 217.470733, 80.437675, 1004.044921, 0.000000, 0.000000, -130.400039, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1667, 216.315734, 81.786384, 1004.625427, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1704, 217.226669, 82.600364, 1004.044921, 0.000000, 0.000000, -61.800025, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2206, 218.955474, 68.245086, 1004.039062, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1723, 214.387573, 80.470748, 1004.005004, 0.699999, 0.000000, 89.800041, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1665, 216.102691, 81.498085, 1004.535400, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1520, 216.160964, 81.806159, 1004.585388, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1667, 216.045791, 81.786384, 1004.625427, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1721, 219.937545, 66.479286, 1004.039062, 0.000000, 0.000000, -0.399993, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2356, 217.587326, 67.342208, 1004.039062, 0.000000, 0.000000, -62.499984, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1368, 262.622802, 77.572326, 1000.679260, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1667, 216.195770, 81.946372, 1004.625427, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2007, 221.317443, 74.325317, 1004.037048, 0.000000, -0.199999, 179.699905, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16779, 217.907363, 78.849876, 1007.516967, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1893, 219.397186, 75.767364, 1007.986450, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1893, 219.457199, 81.357322, 1007.986450, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1893, 215.417160, 81.357322, 1007.986450, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1893, 215.417160, 75.777320, 1007.986450, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2196, 216.068389, 76.828010, 1004.975280, 0.000000, 0.000000, -129.599975, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2967, 215.801589, 76.007881, 1004.965454, 0.000000, 0.000000, -118.900016, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1665, 215.848190, 77.392242, 1004.995605, 0.000000, 0.000000, -163.099990, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1886, 214.423110, 74.383262, 1007.656127, 19.600000, 0.000000, 135.199890, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1808, 225.644302, 80.645225, 1004.039062, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1808, 241.204772, 78.013496, 1004.039062, 0.000000, 0.000000, -89.299964, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1808, 254.213882, 62.540321, 1002.630615, 0.000000, 0.000000, -179.700027, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2911, 241.089019, 70.323280, 1004.039062, 0.000000, 0.000000, 179.699951, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1886, 226.985336, 70.826736, 1007.779785, 19.600000, 0.000000, 135.199890, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1886, 240.748641, 81.932800, 1007.604187, 19.600000, 0.000000, -33.900123, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1886, 242.983276, 71.752189, 1010.252563, 33.299999, 0.000000, 41.499870, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2318, 240.968063, 80.126838, 1005.139831, -0.399998, 0.000000, -179.299972, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2318, 240.358093, 80.119392, 1005.139831, -0.399998, 0.000000, -179.299972, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2318, 239.725708, 80.311714, 1005.141052, -0.399998, 0.000000, 143.700012, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2318, 239.718078, 80.322494, 1005.721618, -0.399998, 0.000000, 143.100173, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2318, 240.357650, 80.155380, 1005.720825, -0.399998, 0.000000, -179.299972, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2318, 240.967620, 80.162826, 1005.720825, -0.399998, 0.000000, -179.299972, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2356, 240.404464, 78.417274, 1004.039062, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1714, 240.667968, 81.741706, 1004.039062, 0.000000, 0.000000, -37.599998, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2221, 240.788909, 80.571052, 1004.948913, 0.000000, 0.000000, -80.399925, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2880, 240.308563, 80.563369, 1004.858276, -23.500003, -79.300010, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2196, 240.659057, 80.189758, 1004.869567, 0.000000, 0.000000, 155.299972, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3785, 241.328247, 75.780220, 1006.870483, -90.400047, 12.500000, -167.999954, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2059, 215.966598, 76.570587, 1004.995300, 0.000000, 0.000000, -112.199943, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2047, 216.914321, 67.438385, 1006.392944, 0.000000, -5.100004, 89.800003, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2196, 218.720657, 66.779235, 1005.009216, 0.000000, 0.000000, 110.599983, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1721, 222.508499, 78.574615, 1004.039062, 0.000000, 0.000000, -90.300025, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2035, 214.017440, 74.521911, 1004.521911, 0.000000, -77.700019, 175.199981, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2040, 214.108184, 74.160575, 1004.155029, 0.000000, 0.000000, 88.500076, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2267, 213.913421, 78.176635, 1006.345642, 0.000000, 0.000000, 89.999916, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2202, 219.516983, 82.514167, 1004.044921, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2007, 221.405349, 82.507827, 1004.044921, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2855, 216.148666, 75.159774, 1004.955444, 0.000000, 0.000000, -97.199974, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2768, 215.621994, 77.364913, 1005.025817, 0.000000, 0.000000, -52.199947, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2609, 214.767898, 74.166641, 1004.765502, 0.000000, 0.000000, -179.300003, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2609, 215.227859, 74.172256, 1004.765502, 0.000000, 0.000000, -179.300003, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2647, 215.253112, 74.163963, 1005.635559, 0.000000, 0.000000, -49.999992, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1721, 222.505508, 77.994613, 1004.039062, 0.000000, 0.000000, -90.300025, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1721, 222.502593, 77.414619, 1004.039062, 0.000000, 0.000000, -90.300025, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1721, 222.499633, 76.834617, 1004.039062, 0.000000, 0.000000, -90.300025, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2026, 219.412231, 69.259407, 1007.549560, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2670, 263.302154, 78.296272, 1000.149169, 0.000000, 0.000000, 94.800010, -1, -1, -1, 300.00, 300.00);
	// крыша мэрии дверь
	CreateDynamicObject(1257, 1689.505126, -2310.802490, -2.455223, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1569, 1497.518676, -1804.583251, 32.424327, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3934, 1534.902343, -1815.629150, 32.471729, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	// грузчик
	CreateDynamicObject(8886, 2053.342529, -1965.354003, 19.145839, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3043, 2047.187500, -1966.902832, 17.147254, 0.000000, 0.000000, -90.399993, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3043, 1981.530029, -1974.481567, 15.595447, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(16003, 1976.267822, -1970.740478, 17.058202, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3666, 1971.972778, -1964.119018, 13.274352, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1431, 2044.029785, -1967.256103, 16.268310, 0.000000, 0.000000, 87.499931, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(14600, 2047.712280, -1965.560058, 16.427534, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1431, 1984.217895, -1974.634033, 14.688305, 0.000000, 0.000000, -91.800056, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3571, 2006.599121, -1974.590820, 17.172609, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1431, 1983.130981, -1974.178955, 14.688305, 0.000000, 0.000000, -91.800056, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1431, 1981.938354, -1974.562133, 14.688305, 0.000000, 0.000000, -91.800056, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1431, 1980.256469, -1974.254272, 14.668305, 0.000000, 0.000000, 108.699928, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1431, 2007.970825, -1972.165039, 16.228305, 0.000000, 0.000000, 176.699935, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1431, 2004.767822, -1971.518310, 16.268304, 0.000000, 0.000000, 114.399909, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1431, 2011.351684, -1974.574340, 16.448312, 0.000000, 0.000000, 88.299911, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1431, 2002.249267, -1974.563232, 16.448312, 0.000000, 0.000000, 88.299911, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1431, 2046.723144, -1966.420166, 16.268310, 0.000000, 0.000000, 179.699951, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(1431, 2046.715087, -1967.950561, 16.268310, 0.000000, 0.000000, -6.100075, -1, -1, -1, 300.00, 300.00); 
	CreateDynamicObject(3043, 2052.396728, -1966.943603, 17.147254, 0.000000, 0.000000, 89.899940, -1, -1, -1, 300.00, 300.00); 
	// ограды
	CreateDynamicObject(5077, 1961.550048, -2183.800048, 14.242197, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 1966.939331, -2193.767578, 11.906311, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 1970.919921, -2197.777832, 11.906311, 0.000000, 0.000000, -180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 1978.900024, -2197.777832, 11.906311, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 1986.938232, -2197.777832, 11.906311, 0.000000, 0.000000, -180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 2005.027343, -2222.892822, 11.906311, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 2005.027343, -2214.882324, 11.906311, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 2005.027343, -2206.850830, 11.906311, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 1994.937988, -2197.790527, 11.906311, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 2001.974487, -2200.336914, 11.906311, 0.000000, 0.000000, 139.900024, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 2000.815795, -2227.575195, 11.916298, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 1992.835571, -2227.575195, 11.916298, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 1984.813110, -2227.575195, 11.916298, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 1976.822998, -2227.575195, 11.916298, 0.000000, 0.000000, 540.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 1968.783081, -2227.575195, 11.916298, 0.000000, 0.000000, 720.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 1960.793579, -2227.575195, 11.916298, 0.000000, 0.000000, 900.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 1952.773559, -2227.575195, 11.916298, 0.000000, 0.000000, 1080.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(986, 1944.751220, -2227.575195, 11.916298, 0.000000, 0.000000, 1260.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3574, 1952.748046, -2220.497070, 15.206870, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3574, 1993.770019, -2216.135742, 15.206870, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3575, 1972.327880, -2216.003417, 15.206875, 0.000000, 0.000000, 630.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(989, 1964.199462, -2189.810058, 14.356881, 0.000000, 0.000000, 106.799964, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(989, 1958.766113, -2189.804931, 14.356881, 0.000000, 0.000000, 106.799964, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(997, 1704.467651, 1602.354980, 9.015625, 0.000000, 0.000000, 73.099998, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(997, 1706.716064, 1609.750488, 9.015625, 0.000000, 0.000000, 73.099998, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(997, 1705.591186, 1606.047363, 9.015625, 0.000000, 0.000000, 73.099998, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1294, 1732.969970, 1599.359985, 13.763390, 0.000000, 0.000000, -14.999857, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1294, 1725.815551, 1614.217529, 13.427816, 0.000000, 0.000000, 165.499877, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1294, 1720.032592, 1593.763916, 13.537819, 0.000000, 0.000000, 164.999816, -1, -1, -1, 300.00, 300.00);
	// airport
	CreateDynamicObject(1569, 1598.718994, 1446.776245, 9.829439, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1569, 1598.712890, 1449.776855, 9.829439, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	// аш
	CreateDynamicObject(982,-2087.63916016,-80.39722443,34.84761810,0.00000000,0.00000000,90.00000000); //object(fenceshit) (1)
	CreateDynamicObject(983,-1242.34179688,-1919.50317383,-3.62699223,0.00000000,0.00000000,90.00000000); //object(fenceshit3) (1)
	CreateDynamicObject(983,-2074.83520508,-83.61250305,34.84761810,0.00000000,0.00000000,0.00000000); //object(fenceshit3) (2)
	CreateDynamicObject(983,-2074.83520508,-99.00683594,34.84761810,0.00000000,0.00000000,0.00000000); //object(fenceshit3) (3)
	CreateDynamicObject(3877,-2069.99072266,-79.83081818,33.92980576,0.00000000,0.00000000,0.00000000); //object(casino_light1) (1)
	CreateDynamicObject(3877,-2072.64282227,-79.83081818,33.92980576,0.00000000,0.00000000,0.00000000); //object(binnt07_la) (3)
	CreateDynamicObject(3877,-2067.15673828,-79.83081818,33.92980576,0.00000000,0.00000000,0.00000000); //object(casino_light1) (1)
	CreateDynamicObject(3877,-2064.33325195,-79.83081818,33.92980576,0.00000000,0.00000000,0.00000000); //object(casino_light1) (1)
	CreateDynamicObject(3877,-2061.47509766,-80.38510895,33.92980576,0.00000000,0.00000000,0.00000000); //object(casino_light1) (1)
	CreateDynamicObject(3877,-2061.47509766,-82.43222809,33.92980576,0.00000000,0.00000000,0.00000000); //object(casino_light1) (1)
	CreateDynamicObject(3877,-2061.47509766,-84.53079224,33.92980576,0.00000000,0.00000000,0.00000000); //object(casino_light1) (1)
	CreateDynamicObject(3877,-2061.47509766,-86.67069244,33.92980576,0.00000000,0.00000000,0.00000000); //object(casino_light1) (1)
	CreateDynamicObject(3877,-2060.89916992,-89.60840607,33.92980576,0.00000000,0.00000000,0.00000000); //object(casino_light1) (1)
	CreateDynamicObject(3877,-2058.65356445,-91.56771088,33.92980576,0.00000000,0.00000000,0.00000000); //object(casino_light1) (1)
	CreateDynamicObject(1257,-2027.72375488,-83.94020844,35.68337784,0.00000000,0.00000000,270.00000000); //object(bustopm) (1)
	CreateDynamicObject(1359,-2030.86218262,-83.17698669,35.20404739,0.00000000,0.00000000,0.00000000); //object(cj_bin1) (1)
	CreateDynamicObject(1215,-2036.94726562,-80.56143188,35.08463593,0.00000000,0.00000000,0.00000000); //object(bollardlight) (1)
	CreateDynamicObject(1215,-2036.94726562,-87.61889648,35.38463593,0.00000000,0.00000000,0.00000000); //object(bollardlight) (2)
	CreateDynamicObject(1215,-2017.47595215,-87.61889648,35.38463593,0.00000000,0.00000000,0.00000000); //object(bollardlight) (3)
	CreateDynamicObject(1215,-2017.47595215,-80.56143188,35.38463593,0.00000000,0.00000000,0.00000000); //object(bollardlight) (4)
	// ждлс
	CreateDynamicObject(970, 1774.119384, -1885.798828, 13.088100, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(970, 1774.119384, -1890.009765, 13.088100, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(970, 1772.025878, -1907.296630, 13.081727, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(970, 1774.082153, -1905.189208, 13.086244, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(970, 1774.082153, -1900.988159, 13.086244, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1214, 1774.122436, -1893.601074, 12.386053, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1214, 1774.122436, -1895.451538, 12.386053, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1214, 1774.122436, -1897.332641, 12.386053, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1226, 1774.760009, -1901.540039, 16.375000, 0.000000, 0.000000, 179.999954, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1226, 1774.760009, -1888.975830, 16.375000, 0.000000, 0.000000, 179.999954, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1256, 1766.038452, -1905.659667, 13.225664, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1256, 1758.968750, -1905.659667, 13.225664, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1211, 1773.600097, -1906.878051, 12.956171, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1346, 1770.253295, -1909.751831, 13.890522, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1776, 1769.858886, -1884.284790, 13.589885, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3660, 1759.135131, -1895.506347, 14.228049, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(738, 1757.366210, -1890.812988, 12.861120, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(738, 1764.227172, -1890.812988, 12.861120, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3660, 1759.135131, -1886.316406, 14.228049, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	// рм	
	CreateDynamicObject(14444, 1065.047119, 1549.655151, 4.768445, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(14497, 1083.921142, 1558.632202, 5.439706, 0.000000, 0.000000, 89.300003, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1493, 1090.429077, 1544.387695, 4.948132, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1493, 1090.429077, 1541.397827, 4.948132, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);	
	// триады
	CreateObject(14534, -2266.921875, 473.739868, 42.221534, 0.000000, 0.000000, 0.000000);
	CreateDynamicObject(14545, -2262.480957, 472.201538, 39.597194, 0.000000, 0.000000, 0.000000, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(14544, -2267.170166, 473.746856, 40.075839, 0.000000, 0.000000, 0.000000, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(1557, -2261.803955, 476.235443, 37.600242, 0.000000, 0.000000, 0.000000, -1, -1, -1, 100.00, 100.00);	
	// да нанг	
	CreateDynamicObject(15053, -1534.489624, 1156.047241, 7.469818, 0.000000, 0.000000, 0.000000, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(1569, -1535.244140, 1152.538818, 6.219818, 0.000000, 0.000000, 0.000000, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(1814, -1540.313476, 1138.688842, 6.219818, 0.000000, 0.000000, 0.000000, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(1757, -1538.756103, 1137.256103, 6.219818, 0.000000, 0.000000, -178.899993, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(2307, -1538.417480, 1142.175048, 6.247327, 0.000000, 0.000000, -90.000000, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(2959, -1535.261840, 1140.341674, 6.227327, 0.000000, 0.000000, -90.000000, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(1501, -1532.445922, 1145.241699, 6.219818, 0.000000, 0.000000, -89.200012, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(14493, -1538.562622, 1152.842163, 8.487334, 0.000000, 0.000000, 0.000000, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(2111, -1539.838989, 1149.521850, 6.619819, 0.000000, 0.000000, 0.000000, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(349, -1540.068481, 1136.577026, 8.359815, 0.000000, 0.000000, 0.000000, -1, -1, -1, 100.00, 100.00);
	CreateDynamicObject(1669, -1539.707641, 1148.943725, 7.187325, 0.000000, 0.000000, 0.000000, -1, -1, -1, 100.00, 100.00);
	// Interior FBI	
	CreateDynamicObject(1557, -2500.600097, 537.079772, 431.681915, 360.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateObject(14594, -2479.155517, 526.900939, 431.666290, 0.000000, 0.000000, 0.000000);
	CreateDynamicObject(1557, -2500.600097, 540.110046, 431.681915, 360.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3851, -2500.548828, 538.574890, 435.831726, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3851, -2500.548828, 538.574890, 435.831726, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1808, -2487.602050, 531.679016, 431.681915, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1808, -2463.078369, 531.679016, 431.681915, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2356, -2459.637695, 540.609069, 431.674102, 0.000000, 0.000000, 77.800018, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2356, -2456.276611, 540.689819, 431.674102, 0.000000, 0.000000, 77.800018, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1555, -2479.198730, 543.697326, 431.681915, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1555, -2505.101074, 521.684570, 431.701934, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1714, -2452.722412, 513.498352, 431.681915, 0.000000, 0.000000, -74.000015, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2206, -2453.842529, 512.490905, 431.681915, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2604, -2453.959716, 539.625061, 432.454132, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2604, -2457.560546, 539.625061, 432.454132, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2604, -2460.610351, 539.625061, 432.454132, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2604, -2463.211669, 549.585327, 432.454132, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2604, -2460.171630, 546.184631, 432.454132, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2356, -2462.452636, 550.747741, 431.681915, 0.000000, 0.000000, 154.099990, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2356, -2458.978271, 547.316711, 431.681915, 0.000000, 0.000000, 115.499977, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2356, -2452.718017, 540.411010, 431.674102, 0.000000, 0.000000, 77.800018, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1964, -2453.621582, 513.018615, 432.761962, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1555, -2497.999755, 513.474304, 431.701934, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	// FBI	
	CreateDynamicObject(2614, -2447.385253, 522.982666, 42.979660, 0.000000, 0.000000, 450.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1215, -2435.501708, 509.514831, 29.709285, 0.000000, 0.000000, -54.199993, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1215, -2430.044921, 519.504455, 29.719287, 0.000000, 0.000000, -54.199993, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1215, -2423.402099, 525.593139, 29.719287, 0.000000, 0.000000, -54.199993, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1215, -2419.187011, 531.832824, 29.719287, 0.000000, 0.000000, 1.500002, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1215, -2422.376708, 542.712951, 29.719287, 0.000000, 0.000000, 1.500002, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1215, -2429.998779, 542.683654, 29.439281, 0.000000, 0.000000, 1.500002, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1215, -2416.631347, 542.632995, 29.719287, 0.000000, 0.000000, 1.500002, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1215, -2430.825927, 511.766204, 29.709285, 0.000000, 0.000000, -54.199993, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1280, -2451.375488, 501.554016, 29.459566, 0.000000, 0.000000, -87.100006, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2670, -2451.438232, 502.170532, 29.176254, 0.000000, 0.000000, 1.000002, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1226, -2427.892822, 497.916687, 32.911918, 0.000000, 0.000000, 115.799987, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1226, -2437.928710, 493.068145, 32.911918, 0.000000, 0.000000, 115.799987, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(647, -2432.115966, 521.937438, 30.573362, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(700, -2433.966796, 512.559875, 29.798894, 0.000000, 0.000000, 56.099952, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(647, -2427.926757, 526.917175, 30.573362, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(7091, -2447.781250, 510.975250, 41.985401, 0.000000, -11.599995, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(7091, -2447.781250, 535.025207, 41.985401, 0.000000, -11.599995, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2886, -2455.264404, 505.320098, 31.027650, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3785, -2455.106445, 502.277954, 32.013935, 360.000000, 0.000000, 4.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3785, -2455.095458, 505.748748, 32.013935, 360.000000, 0.000000, 4.000000, -1, -1, -1, 300.00, 300.00);
	// 51
    CreateObject(3707,353.669983, 1950.344604, 24.623753,0.141593, 0.000000, 180.000000);
    CreateDynamicObject(3279,384.702789, 1892.396484, 16.716242,-1.570796, 0.000000, 180.000000);
    CreateDynamicObject(3279,350.380798, 1807.448975, 17.561840,1.748893, 0.000000, 180.000000);
    CreateDynamicObject(3279, 333.368652, 1795.830444, 17.059250,0.552544, 0.000000, 180.000000);
    CreateDynamicObject(11480,289.229370, 1822.304443, 18.834333,0.570796, 0.000000, 90.000000);
    CreateDynamicObject(11480, 282.921143, 1822.302612, 18.834333,0.570796, 0.000000, 90.000000);
    CreateDynamicObject(16095, 291.7807,1830.3577,16.6481, 0.000000, 0.000000, 270.000000);
	// Bankomet
	CreateDynamicObject(2942, 1697.641113, -2335.411376, -3.059688, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1690.771240, -2237.489013, -3.083789, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1680.428100, -2335.447753, 13.176877, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1690.865112, -2237.504150, 13.189631, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1028.238891, -1117.978759, 23.526176, 0.000000, 0.000000, 450.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1464.424682, -1749.902587, 15.075321, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1751.535522, -1898.748046, 13.207533, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1094.986206, -1803.669189, 13.224089, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 461.528839, -1511.873657, 30.611282, 0.000000, 0.000000, -79.600097, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 562.344177, -1293.945312, 16.868246, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, -382.973236, -1433.612670, 25.356576, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, -1980.602661, 121.827415, 27.307514, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);//
	CreateDynamicObject(2942, -2242.348632, 116.358673, 34.940315, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, -2035.293457, -102.033477, 34.784065, 0.000000, 0.000000, -180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, -1828.742187, 3.990440, 14.737190, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, -1693.065795, 415.273468, 6.819693, 0.000000, 0.000000, 45.400001, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, -1641.967895, 1207.613159, 6.809690, 0.000000, 0.000000, 133.500000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, -2630.014404, 1404.680175, 6.741561, 0.000000, 0.000000, 69.199989, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, -856.494506, 1529.499389, 22.191644, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, -300.924865, 1045.596069, 19.356079, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 54.364681, 1211.691894, 18.493804, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2107.883544, 896.790222, 10.779697, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2090.533691, 1459.720581, 10.430315, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2085.658447, 2059.549560, 10.687909, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1628.449584, 1811.490478, 10.440322, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1715.189819, 1533.138549, 10.384882, 0.000000, 0.000000, 85.400062, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1717.857543, 1312.948486, 10.415160, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2271.157226, 82.047554, 26.084383, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, -2445.168701, 512.938110, 29.533269, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, -1968.033691, 458.489898, 34.791843, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2019.302734, 1014.138671, 10.440315, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2107.352294, 896.767822, 10.779697, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2498.943359, 926.674743, 10.633443, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2646.243408, 1129.681152, 10.799692, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2848.759277, 1295.057128, 11.000625, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2638.603271, 1675.587646, 10.653444, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2638.667968, 1852.850708, 10.673444, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2466.830322, 2031.304565, 10.682507, 0.000000, 0.000000, 1980.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2565.125732, 2065.393798, 10.709524, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2367.073486, 2084.471923, 10.440319, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2085.682861, 2083.130615, 10.667905, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2173.897216, 1411.785156, 10.692507, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2281.931640, 2432.408203, 10.450320, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 2187.698242, 2478.731201, 10.842193, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1697.161987, 2209.106445, 10.679183, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1590.974731, 2218.010009, 10.690319, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1163.004516, 2075.335937, 10.690316, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1664.635742, 1412.961669, 10.419672, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2942, 1665.065795, 1483.049072, 10.414333, 0.000000, 0.000000, 89.700004, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1359, 1080.250000, 1004.450012, 10.690895, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1359, 1025.540039, 1045.010009, 10.690894, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1359, 1141.910034, 1031.319946, 10.610894, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1359, 1150.170043, 1098.489990, 10.660895, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1359, 1095.660034, 1139.290039, 10.660893, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1359, 1033.519042, 1112.493652, 10.660922, 0.680019, 0.327663, -4.197824, -1, -1, -1, 300.00, 300.00);
	// Casino	
	CreateObject(14777, 1008.595886, -1194.930541, 28.640308, 0.000000, 0.000000, 0.000000);
	CreateDynamicObject(1824, 1016.753723, -1203.736328, 30.528118, 0.000000, 0.000000, 179.800048, -1, -1, -1, 75.00, 75.00);
	CreateDynamicObject(2779, 1023.979858, -1192.709838, 28.648120, 0.000000, 0.000000, -92.600036, -1, -1, -1, 75.00, 75.00);
	CreateDynamicObject(2779, 1023.795654, -1196.777221, 28.648120, 0.000000, 0.000000, -92.600036, -1, -1, -1, 75.00, 75.00);
	CreateDynamicObject(1824, 1011.459167, -1195.608520, 29.148118, 0.000000, 0.000000, -180.000000, -1, -1, -1, 75.00, 75.00);
	CreateDynamicObject(2946, 1007.032897, -1180.497436, 28.598119, 0.000000, 0.000000, -90.000000, -1, -1, -1, 75.00, 75.00);
	CreateDynamicObject(2946, 1010.201904, -1180.502929, 28.588117, 0.000000, 0.000000, 90.000000, -1, -1, -1, 75.00, 75.00);	
	// Bank	
	CreateDynamicObject(13007, 1405.581787, -1685.244018, 14.372816, 0.000000, 0.000000, 0.000000, -1, -1, -1, 50.00, 50.00);
	CreateDynamicObject(2946, 1396.936767, -1677.711547, 12.583753, 0.000000, 0.000000, -90.100028, -1, -1, -1, 50.00, 50.00);
	CreateDynamicObject(2946, 1400.106811, -1677.714599, 12.583753, 0.000000, 0.000000, 90.000000, -1, -1, -1, 50.00, 50.00);
	CreateDynamicObject(2947, 1414.989990, -1688.776977, 12.593755, 0.000000, 0.000000, -178.699966, -1, -1, -1, 50.00, 50.00);
	// House 1
	CreateObject(15034, 2108.366455, -2399.008544, 14.326909, 0.000000, 0.000000, 0.000000);
	CreateDynamicObject(1507, 2108.057861, -2403.602050, 12.574722, 0.000000, 0.000000, 0.000000, -1, -1, -1, 50.00, 50.00);
	CreateDynamicObject(1502, 2106.479492, -2400.914306, 12.594711, 0.000000, 0.000000, 90.000000, -1, -1, -1, 50.00, 50.00);
	CreateDynamicObject(14866, 2105.416503, -2394.182861, 13.114721, 0.000000, 0.000000, 87.699981, -1, -1, -1, 50.00, 50.00);
	CreateDynamicObject(2004, 2104.186767, -2397.193603, 14.014725, 0.000000, 0.000000, 90.000000, -1, -1, -1, 50.00, 50.00);
	CreateDynamicObject(2346, 2110.564697, -2393.940917, 12.634720, 0.000000, 0.000000, -90.600013, -1, -1, -1, 50.00, 50.00);
	CreateDynamicObject(1751, 2110.839843, -2394.592041, 13.154724, 0.000000, 0.000000, -90.000000, -1, -1, -1, 50.00, 50.00);
	CreateDynamicObject(2525, 2101.241455, -2398.733154, 12.594721, 0.000000, 0.000000, 0.000000, -1, -1, -1, 50.00, 50.00);
	CreateDynamicObject(2527, 2101.698242, -2401.653808, 12.584721, 0.000000, 0.000000, 90.000000, -1, -1, -1, 50.00, 50.00);
	// House 2
	CreateObject(15030, 1685.815063, -2663.997558, 14.336888, 0.000000, 0.000000, 0.000000);
	CreateDynamicObject(1535, 1691.445434, -2665.010742, 12.536887, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1535, 1691.475585, -2665.040771, 12.536887, 0.000000, 0.000000, 450.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2526, 1682.837890, -2659.345703, 12.586133, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2133, 1682.384277, -2664.657470, 12.586888, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2141, 1682.432128, -2664.680175, 17.676540, 0.000000, -179.999954, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2141, 1683.389404, -2664.650146, 12.576885, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2141, 1681.441162, -2664.680175, 17.676540, 0.000000, -179.999954, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2141, 1680.440551, -2664.680175, 17.676540, 0.000000, -179.999954, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2132, 1680.397094, -2664.661132, 12.588786, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2298, 1687.206420, -2659.277099, 12.585252, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2524, 1681.543334, -2662.053466, 12.558180, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2528, 1683.206665, -2663.080566, 12.605789, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2115, 1681.718017, -2668.287353, 12.541070, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2079, 1683.846069, -2668.291748, 13.221068, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2079, 1682.701782, -2667.881347, 13.221068, 0.000000, 0.000000, 90.999969, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2256, 1691.247314, -2660.533203, 14.766899, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2576, 1684.622558, -2659.377685, 12.586888, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2845, 1685.731201, -2660.704101, 12.586888, 0.000000, 0.000000, 65.500000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16779, 1688.036376, -2663.677001, 16.206893, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);	
	// House 3
	CreateObject(14707, 1889.850708, -2659.038085, 17.186845, 0.000000, 0.000000, 0.000000);
	CreateDynamicObject(14720, 1895.004516, -2677.422119, 12.585210, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2141, 1895.937011, -2672.418701, 12.618717, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(643, 1887.223022, -2674.921386, 13.050287, 0.000000, 0.000000, -86.800003, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2526, 1904.560302, -2663.408447, 13.320469, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2525, 1904.976562, -2658.398437, 13.321733, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2524, 1906.616210, -2659.531982, 13.301540, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1700, 1890.613403, -2647.152587, 12.585283, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2573, 1895.658935, -2645.297119, 12.585283, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2574, 1885.812500, -2645.122070, 12.598020, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1701, 1880.736083, -2647.063720, 12.605230, 0.000000, 0.000000, -270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1493, 1890.318725, -2657.971923, 16.787780, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(939, 1892.494384, -2655.946289, 19.076368, 0.000000, 0.000000, -159.899917, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1745, 1890.508666, -2660.015136, 16.897783, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1493, 1890.244140, -2669.383300, 16.891403, 0.000000, 0.000000, -0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16779, 1891.022583, -2674.746337, 16.175968, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2025, 1876.006835, -2652.211914, 12.593095, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2251, 1881.214965, -2672.671142, 18.597797, 0.000000, 0.000000, 109.599975, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2281, 1893.086791, -2673.184326, 18.787809, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2282, 1893.569091, -2660.532470, 18.657810, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2258, 1896.419921, -2651.652099, 15.145291, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	// House 4	
	CreateObject(14706, 1826.239868, -2664.503906, 15.836872, 0.000000, 0.000000, 0.000000);
	CreateDynamicObject(14720, 1816.089965, -2654.518798, 12.633464, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2115, 1821.083862, -2659.430908, 12.644554, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2807, 1821.156860, -2660.572753, 13.145497, 0.000000, 0.000000, -64.299987, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2807, 1821.130371, -2657.517089, 13.145497, 0.000000, 0.000000, 87.500045, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2800, 1821.170043, -2658.876220, 13.263787, 0.000000, 0.000000, 50.399997, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2141, 1815.213378, -2659.712158, 12.638566, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1701, 1813.904663, -2665.852539, 12.618122, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2296, 1812.466308, -2663.645263, 12.618122, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2516, 1817.465576, -2655.193847, 16.250934, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2528, 1821.363891, -2656.090820, 16.250934, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1208, 1822.647583, -2654.811767, 16.250934, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2524, 1820.022583, -2653.054199, 16.250934, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2842, 1819.003906, -2655.062988, 16.250934, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2298, 1827.947875, -2660.060791, 16.243122, 0.000000, 0.000000, 360.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2297, 1830.015014, -2661.739990, 16.243122, 0.000000, 0.000000, 135.500015, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1704, 1823.574462, -2660.837890, 12.664222, 0.000000, 0.000000, 42.700000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1822, 1823.978271, -2662.758789, 12.664222, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1704, 1824.337158, -2664.124755, 12.664222, 0.000000, 0.000000, 143.099945, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2204, 1829.903564, -2660.960693, 12.664222, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16779, 1818.210083, -2657.625488, 16.126655, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	// Ballas
	CreateObject(15046, 2738.108886, -1795.765991, 25.753055, 0.000000, 0.000000, 0.000000);
	CreateDynamicObject(2959, 2738.881103, -1788.336425, 24.503055, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1505, 2740.226074, -1785.100097, 24.503055, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2370, 2738.880371, -1776.557128, 24.493055, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 2734.702148, -1775.406494, 24.703058, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 2734.702148, -1774.776733, 24.703058, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 2734.702148, -1774.196899, 24.703058, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(349, 2739.486572, -1776.085571, 25.323518, 78.600059, -139.899948, 25.099990, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2329, 2745.841796, -1778.624389, 24.483053, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	// Vagos
	CreateObject(15042, 2693.421630, -1571.265991, 21.039525, 0.000000, 0.000000, 88.399955);
	CreateDynamicObject(14819, 2693.772949, -1577.086914, 20.239521, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1493, 2694.108642, -1564.916381, 19.019508, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 2693.353759, -1570.133911, 19.269531, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2115, 2690.118896, -1568.513183, 19.039525, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1811, 2689.090576, -1569.905151, 19.649530, 0.000000, 0.000000, -121.300003, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1811, 2689.039794, -1567.210815, 19.649530, 0.000000, 0.000000, 104.600006, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1811, 2690.771728, -1567.104125, 19.649530, 0.000000, 0.000000, 72.799987, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 2693.353759, -1567.863647, 19.269531, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(372, 2690.173828, -1568.286865, 19.879926, -86.499992, 0.600000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1575, 2691.032714, -1568.864257, 19.819530, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 2693.353759, -1568.513427, 19.269531, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 2693.353759, -1569.323608, 19.269531, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2695, 2693.705810, -1576.340942, 20.519525, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1728, 2686.937744, -1578.065429, 19.039525, 0.000000, 0.000000, 90.400016, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2114, 2686.851074, -1576.175415, 19.629528, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	// Rifa
	CreateObject(14718, 2151.130371, -1777.371215, 12.778888, 0.000000, 0.000000, 0.000000);
	CreateDynamicObject(3109, 2153.418701, -1782.273437, 14.056701, 0.000000, 0.000000, -89.900009, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1502, 2158.371826, -1778.281494, 12.786701, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1502, 2150.081787, -1780.421508, 12.786701, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2528, 2148.823242, -1779.008789, 12.776701, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2115, 2162.799072, -1779.404052, 12.786701, 0.000000, 0.000000, -97.300003, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2121, 2163.882324, -1781.078247, 13.266700, 0.000000, 0.000000, -132.199981, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2121, 2164.193603, -1779.321777, 13.266700, 0.000000, 0.000000, -73.900001, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2121, 2161.796142, -1779.521362, 13.266700, 0.000000, 0.000000, 57.700004, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1450, 2159.814941, -1782.505126, 13.396704, 0.000000, 0.000000, 174.799972, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2035, 2162.508300, -1779.546875, 13.596695, 0.000000, 0.000000, -121.200004, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2691, 2165.101318, -1779.914062, 14.746706, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2307, 2148.442626, -1776.427734, 12.786701, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 2148.446533, -1777.767578, 12.976700, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 2149.307373, -1777.767578, 12.976700, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 2150.067871, -1777.767578, 12.976700, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 2150.067871, -1777.767578, 12.976700, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1764, 2154.143310, -1775.276855, 12.786701, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1820, 2156.938232, -1776.387207, 12.786701, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1578, 2157.283691, -1776.045166, 13.276702, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2842, 2153.635986, -1782.449951, 12.778888, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2602, 2147.935791, -1779.684692, 13.326698, 0.000000, 0.000000, 87.699996, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2840, 2156.271972, -1775.899658, 12.828890, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1509, 2157.780761, -1775.853149, 13.506703, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2696, 2152.177001, -1777.846801, 14.148889, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	// Aztec
	CreateObject(14756, 1673.815673, -2049.250488, 15.206880, 0.000000, 0.000000, 0.000000);
	CreateDynamicObject(1505, 1674.629028, -2050.002929, 13.206880, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1502, 1669.699707, -2047.041503, 13.206885, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2526, 1671.974243, -2044.339111, 13.206880, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2525, 1670.026000, -2041.614257, 13.214206, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2631, 1670.076049, -2040.241821, 13.176183, 0.000000, 0.399999, -91.699981, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1817, 1670.299194, -2056.019287, 13.276883, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1728, 1671.670898, -2058.909667, 13.206880, 0.000000, 0.000000, 179.299972, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1728, 1667.136230, -2056.430908, 13.206880, 0.000000, 0.000000, 88.899963, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(14384, 1679.391845, -2055.679199, 14.726881, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 1674.351074, -2059.118164, 13.426880, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 1673.590942, -2059.118164, 13.426880, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3014, 1672.861083, -2059.118164, 13.426880, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2046, 1674.085693, -2051.691406, 15.316882, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(336, 1667.270751, -2054.946533, 13.667104, 7.300004, -85.400001, 98.099998, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(348, 1670.614746, -2055.687255, 13.417602, -79.099983, 0.699999, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2145, 1666.460449, -2049.477783, 13.206880, 0.000000, 0.000000, 88.800003, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2145, 1666.474365, -2048.787353, 13.206880, 0.000000, 0.000000, 88.800003, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2145, 1666.488525, -2048.106689, 13.206880, 0.000000, 0.000000, 88.800003, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(14756, 1673.815673, -2049.250488, 15.206880, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2145, 1666.446655, -2050.148193, 13.206880, 0.000000, 0.000000, 88.800003, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2695, 1666.989990, -2048.869384, 14.616879, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	// Мэрия
	CreateObject(14602, 1481.300048, -1742.259033, 483.647766, 0.000000, 0.000000, 90.000000);
	CreateDynamicObject(14596, 1495.333984, -1744.647583, 488.980743, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(14597, 1491.801147, -1763.476440, 497.691986, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(14597, 1491.801147, -1764.207153, 491.872039, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(14597, 1491.801147, -1764.207153, 486.082000, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1502, 1488.418701, -1745.997924, 478.280578, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1557, 1480.480834, -1728.074340, 478.300781, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2245, 1483.803344, -1761.332275, 479.487091, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2245, 1479.032958, -1761.332275, 479.467071, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2257, 1481.187744, -1765.172363, 481.510620, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1706, 1496.239257, -1758.368164, 478.287078, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1706, 1496.239257, -1754.597778, 478.287078, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2167, 1473.796630, -1741.336425, 478.280578, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2167, 1472.635986, -1741.336425, 478.280578, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2164, 1465.755004, -1746.631835, 478.280578, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2165, 1468.906616, -1746.377929, 478.280578, 0.000000, 0.000000, -90.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2181, 1469.213623, -1741.811035, 478.280578, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1811, 1470.212524, -1746.280517, 478.840576, 0.000000, 0.000000, 19.099998, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1715, 1467.393676, -1746.237304, 478.280395, 0.000000, 0.000000, 75.699935, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1715, 1469.480468, -1742.785034, 478.280395, 0.000000, 0.000000, 129.499954, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1715, 1481.306030, -1760.486572, 478.280395, 0.000000, 0.000000, 140.799972, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1557, 1465.542358, -1751.466674, 478.290466, 0.000000, 0.000000, -87.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1820, 1494.949462, -1757.324096, 478.280456, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);

    // Автотюнинг
    CreateDynamicObject(971, 1041.355957, -1460.013671, 12.443194, 0.000000, 0.000000, 90.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(976, 959.250549, -1472.216552, 12.640625, 0.000000, 0.000000, 180.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(976, 959.501281, -1472.246582, 12.640625, 359.699981, 0.100000, 360.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(11313, 1032.190673, -1451.586303, 14.512748, 0.000000, 0.000000, 0.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(1415, 1040.230834, -1456.182861, 12.638116, 0.000000, 0.000000, 0.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(10281, 1031.354125, -1451.515014, 20.194585, 0.000000, -2.700034, -90.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(2670, 1031.280639, -1444.344482, 12.634636, 0.000000, 0.000000, -34.799991, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(997, 954.376525, -1427.167114, 12.560303, 0.000000, 0.000000, 90.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(997, 954.376525, -1419.092895, 12.560303, 0.000000, 0.000000, 90.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(997, 954.376525, -1423.143188, 12.560303, 0.000000, 0.000000, 90.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(3035, 978.701232, -1434.557006, 13.306875, 0.000000, 0.000000, 90.000000,  -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(2671, 980.044372, -1433.983276, 12.546875, 0.000000, 0.000000, -107.999954, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(1358, 1001.526489, -1431.992919, 13.706870, 0.000000, 0.000000, 900.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(1440, 1004.829711, -1431.892944, 13.056881, 0.000000, 0.000000, 34.799999, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(12957, 1027.326293, -1433.667602, 13.266879, 0.000000, 0.000000, 270.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(16444, 1029.981567, -1437.138671, 12.734639, 0.000000, 0.000000, 0.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(8886, 998.302368, -1459.914916, 15.966872, 0.000000, 0.000000, 360.000000,  -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1327, 1021.693481, -1430.693359, 13.361795, -22.499988, 13.800000, 450.000000,  -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1327, 1023.358886, -1431.787841, 13.176887, 180.000000, 90.000000, 90.000000,  -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16002, 950.125854, -1413.755371, 15.170878, 0.000000, 0.000000, 90.000000,  -1, -1, -1, 300.00, 300.00);
	// Island Prison
	CreateObject(13872, -8683.146484, 1716.562255, -11.484272, 5.999999, -5.499999, 0.000000);
	CreateDynamicObject(645, -8728.785156, 1694.089355, 6.936456, 0.000000, 0.000000, 0.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(645, -8675.384765, 1717.450561, 0.546457, 0.000000, 0.000000, 0.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(620, -8699.169921, 1685.973266, 1.927425, 0.000000, 0.000000, 0.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(620, -8741.584960, 1684.032958, 1.257425, 0.000000, 0.000000, 0.000000,  -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(619, -8710.349609, 1735.977539, 4.236859, 0.399999, -27.400007, -129.299835, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(823, -8706.926757, 1735.194458, 6.194666, -2.100003, 0.000000, 0.000000,  -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(17025, -8729.762695, 1679.792480, -2.387078, -34.699996, -14.900001, -33.699993, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(845, -8709.243164, 1702.834472, 8.482150, -7.999996, 3.599999, 0.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(705, -8701.581054, 1708.172851, 6.424663, 0.000000, 0.000000, 0.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(830, -8711.650390, 1738.259033, 4.434227, -12.700000, 6.099998, 27.299964, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(780, -8682.086914, 1735.157226, 0.174928, 0.000000, 0.000000, 0.000000, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(780, -8692.605468, 1739.797241, 0.174928, 0.000000, 0.000000, 65.500000,  -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(780, -8690.657226, 1730.066894, 2.964927, 0.000000, 0.000000, 127.699989,  -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(822, -8691.663085, 1729.337646, 4.578456, 0.000000, 0.000000, 0.000000,  -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(822, -8691.810546, 1738.546020, 2.347954, 0.699999, 6.299997, 0.000000,  -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(822, -8684.180664, 1733.696899, 1.446980, 0.699999, 6.299997, 0.000000,  -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(836, -8734.845703, 1740.739013, 4.085805, -2.199999, -13.499999, -40.900005,  -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(705, -8734.401367, 1736.035888, 2.894660, 0.000000, 0.000000, 67.000022, -1, -1, -1,  300.00, 300.00);
	CreateDynamicObject(17025, -8748.129882, 1697.172241, -1.939833, -34.699996, -14.900001, -167.000030, -1, -1, -1,  300.00, 300.00);


	CreateDynamic3DTextLabel(!"The Rifa", 0x6666ffFF, 2185.8500, -1815.1200, 13.5500 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	CreateDynamic3DTextLabel(!"Grove Street", 0x009900FF, 2495.33, -1690.99, 14.77 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	CreateDynamic3DTextLabel(!"The Ballas", 0xCC00FFFF, 2650.7031, -2021.7233, 14.1766 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	CreateDynamic3DTextLabel(!"Vagos Gang", 0xffcd00FF, 2770.7500, -1628.7200, 12.1800 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);
	CreateDynamic3DTextLabel(!"Aztecas", 0x00F5FFFF, 1667.5200, -2106.9400, 14.0700 + 1.0,
		MAX_DISTANCE_VISIBLE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, MAX_DISTANCE_VISIBLE
	);	
	
	return 1;
}

public OnQueryError(errorid, error[], callback[], query[], connectionHandle)
{
	switch(errorid)
	{
  		case CR_SERVER_GONE_ERROR:
		{
			printf("Lost connection to server");
		}
		case ER_SYNTAX_ERROR:
		{
			printf("Something is wrong in your syntax, query: %s",query);
		}
	}
	return 1;
}

stock LoadAccounts(playerid) {
	GetPlayerName(playerid, PlayerInfo[playerid][pName], MAX_PLAYER_NAME);
	new query_string[49+MAX_PLAYER_NAME-4];
	format(query_string, sizeof(query_string), "SELECT * FROM "TABLE_ACCOUNTS" WHERE `Name` = '%s'", PlayerInfo[playerid][pName]);
	mysql_tquery(database, query_string, "FindPlayerInTable","i", playerid);
	return 1;
}
forward FindPlayerInTable(playerid);
public FindPlayerInTable(playerid)
{
    new rows = cache_get_row_count();
    if(!rows)
    {
        SPD(playerid, dRegister, DIALOG_STYLE_INPUT, "Регистрация на Chance RolePlay", "{FFFFFF}Добро пожаловать на первый кроссплатформенный сервер "COLOR_RED"Chance RolePlay\n{FFFFFF}На нашем сервере можно играть с Android устройств! Подробнее на ChanceRp.Ru\n\nВведите пароль для регистрации нового аккаунта:", "Далее", "Выход");
    }
    else
    {
        SPD(playerid, dLogin, DIALOG_STYLE_INPUT, "Вход в аккаунт", "{FFFFFF}Добро пожаловать на первый кроссплатформенный сервер "COLOR_RED"Chance RolePlay\n{FFFFFF}Введите пароль от аккаунта для того, чтоб продолжить игру:", "Вход", "Выход");
        cache_get_field_content(0, "Password", PlayerInfo[playerid][pPassword]);
    }
    return 1;
}
@_LoadPlayerAccounts(playerid);
@_LoadPlayerAccounts(playerid) {
	new rows = cache_get_row_count();

	if(!rows) {
	    SendClientMessage(playerid, -1, !""COLOR_RED"Для начала игры заведите аккаунт на сайте: {FFFFFF}ChanceRp.ru");
	    SendClientMessage(playerid, -1, !""COLOR_RED"Если у Вас уже есть аккаунт и IP сменился, заново авторизуйтесь на сайте");
	    Kick(playerid);
	    return 1;

	} else {
		PlayerInfo[playerid][pBanned] = cache_get_field_content_int(0, "Banned");
		if(PlayerInfo[playerid][pBanned] > 0) {
			GameTextForPlayer(playerid, "~r~YOU ARE BANNED", 60000, 4);
			Kick(playerid);
			return 1;
		}
 		
		for(new i = 0;i<=TOTALGZ;i++) GangZoneShowForPlayer(playerid,GZInfo[i][gid],GetGangZoneColor(i));
		
		new Name[30];
		cache_get_field_content(0, "Name", PlayerInfo[playerid][pName]);	

		strmid(Name, PlayerInfo[playerid][pName], 0, strlen(PlayerInfo[playerid][pName]), MAX_PLAYER_NAME);

		new temp_int = cache_get_field_content_int(0, "isOnline");

		if(temp_int == 1) {
			new
		        targetid;
		    sscanf(PlayerInfo[playerid][pName], "u", targetid);
		    
		    if(targetid != INVALID_PLAYER_ID) {
		    	Kick(playerid);
				return SendClientMessage(playerid, -1, !""COLOR_RED"Игрок под данным именем уже находится в игре");
		    }
		}
		if(test_server == false) {
			if(Platform[playerid] == 1) { 
				format(Name, sizeof(Name), "%s[PC]", PlayerInfo[playerid][pName]); 
			}
			if(Platform[playerid] == 2) { 
				format(Name, sizeof(Name), "%s[RD]", PlayerInfo[playerid][pName]); 
			}


			SetPlayerName(playerid, Name);
		}
		

		new 
			temp_value_int;

		PlayerInfo[playerid][pID] = cache_get_field_content_int(0, "ID");
		PlayerInfo[playerid][pJailed] = cache_get_field_content_int(0, "Jailed");
		PlayerInfo[playerid][pJailTime] = cache_get_field_content_int(0, "JailTime");
		PlayerInfo[playerid][pMuted] = cache_get_field_content_int(0, "Muted");
		PlayerInfo[playerid][pMuteTime] = cache_get_field_content_int(0, "MuteTime");
		PlayerInfo[playerid][pFreshPrice] = cache_get_field_content_int(0, "FreshPrice");
		
		temp_value_int = cache_get_field_content_int(0, "Job");
		SetPlayerFraction(playerid, Fraction:temp_value_int);

		PlayerInfo[playerid][pSkin] = cache_get_field_content_int(0, "Skin");
		PlayerInfo[playerid][pSex] = cache_get_field_content_int(0, "Sex");
		PlayerInfo[playerid][pLicense] = cache_get_field_content_int(0, "License");
		PlayerInfo[playerid][pLicenseAir] = cache_get_field_content_int(0, "LicenseAir");
		PlayerInfo[playerid][pBank] = cache_get_field_content_int(0, "Bank");
		PlayerInfo[playerid][pDevice] = cache_get_field_content_int(0, "Device");
		PlayerInfo[playerid][pBalance] = cache_get_field_content_int(0, "Balance");
		PlayerInfo[playerid][pKarma] = cache_get_field_content_int(0, "Karma");
		PlayerInfo[playerid][pWanted] = cache_get_field_content_int(0, "Wanted");
		SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
		PlayerInfo[playerid][pFarmSkill] = cache_get_field_content_int(0, "FarmSkill");
		PlayerInfo[playerid][pBusSkill] = cache_get_field_content_int(0, "BusSkill");
		PlayerInfo[playerid][pAirSkill] = cache_get_field_content_int(0, "AirSkill");
		PlayerInfo[playerid][pCar] = cache_get_field_content_int(0, "Car");
		PlayerInfo[playerid][pCarCol] = cache_get_field_content_int(0, "CarCol");
		PlayerInfo[playerid][pCarCol2] = cache_get_field_content_int(0, "CarCol2");
		PlayerInfo[playerid][pTaxiTotal] = cache_get_field_content_int(0, "TaxiTotal");
		PlayerInfo[playerid][pOnline] = cache_get_field_content_int(0, "Online");
		SetPlayerEXP(playerid, cache_get_field_content_int(0, "Score"));

		PlayerInfo[playerid][pHours] = cache_get_field_content_int(0, "Hours");
		PlayerInfo[playerid][pColor] = cache_get_field_content_int(0, "Color");
		PlayerInfo[playerid][pDonate] = cache_get_field_content_int(0, "Donate");
		PlayerInfo[playerid][pAdmin] = cache_get_field_content_int(0, "Admin");
		PlayerLogged{playerid} = true;

		format(small_string, sizeof(small_string), ""COLOR_YELLOW"Вы успешно авторизовались. Приятной игры, %s", PlayerInfo[playerid][pName]);
		UpdateSpawnInfo(playerid);
		TogglePlayerSpectating(playerid, false);
		SendClientMessage(playerid, -1, small_string);
		if(PlayerInfo[playerid][pAdmin] > 0) {
		format(small_string, sizeof(small_string), ""COLOR_RED"Администратор {FFFFFF}%s авторизовался", PlayerInfo[playerid][pName]);
		SendAdminMessage(-1, small_string);
		Iter_Add(Admin,playerid);// в админ авторизацию  er
		}
		if(PlayerInfo[playerid][pJailed] == 0) {
		format(small_string, sizeof(small_string), "~b~~h~Welcome,~n~~w~%s", PlayerInfo[playerid][pName]);
		GameTextForPlayer(playerid, small_string, 5000, 0);
		}
		if(Platform[playerid] == 1) { SpawnPlayer(playerid); }
        if(Platform[playerid] == 0) {
		Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 20, playerid);
		Streamer_SetVisibleItems(STREAMER_TYPE_MAP_ICON, 20, playerid);
		Streamer_SetVisibleItems(STREAMER_TYPE_PICKUP, 100, playerid);
    	}
		if(Platform[playerid] == 1) {
		Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 300, playerid);
		Streamer_SetVisibleItems(STREAMER_TYPE_PICKUP, 500, playerid);
		Streamer_SetVisibleItems(STREAMER_TYPE_MAP_ICON, 300, playerid);
		}
		if(Platform[playerid] == 2 && PlayerInfo[playerid][pAdmin] == 0) return Kick(playerid);


		CallLocalFunction("OnPlayerAuthorization", "i", playerid);
		CallLocalFunction("TD_OnPlayerAuthorization", "i", playerid);
		CallLocalFunction("LD_OnPlayerAuthorization", "i", playerid);
		PlayerTimerID[playerid] = KillTimer(PlayerTimerID[playerid]); 
		return PlayerTimerID[playerid] = SetTimerEx("PlayerUpdate", 1000, false, "d", playerid);
	}
}
SaveGZ(frac, he)
{
	new query[256];
	mysql_format(database, query, 144, "UPDATE gz SET fraction = %i WHERE id = %i LIMIT 1",frac, he);
	mysql_pquery(database, query, "", "");
	return true;
}
GetGangName(fnumbwer)
{
	new string[40];
	switch(fnumbwer)
	{
		case 3: format(string,sizeof(string), "Ballas Gang");
		case 4: format(string,sizeof(string), "Vagos Gang");
		case 2: format(string,sizeof(string), "Grove Street");
		case 6: format(string,sizeof(string), "Aztecas");
		case 5: format(string,sizeof(string), "Rifa Gang");
	}
	return string;
}
GetGangZoneColor(gangzonex) {
	new za;
	switch(GZInfo[gangzonex][gFrak]) {
		case 3: za = 0xd200ff99;
		case 4: za = 0xcfbe0899;
		case 2: za = 0x06b50699;
		case 6: za = 0x03c3b899;
		case 5: za = 0x007fffAA;
		default: za = 0xFEFEFEAA;
	}
	return za;
}
GetGZColorF(fnumber) {
	new zf;
	switch(fnumber) {
		case 3: zf = 0xd200ff99;
		case 4: zf = 0xcfbe0899;
		case 2: zf = 0x06b50699;
		case 6: zf = 0x03c3b899;
		case 5: zf = 0x007fffAA;
	}
	return zf;
}

public OnGameModeExit()
{
	foreach(new i: Player) {
		OnPlayerDisconnect(i, 255);
	}
	mysql_close(database);
	return 1;
}


public OnPlayerConnect(playerid)
{
	if(IsPlayerNPC(playerid)) return 1;
	SetPVarInt(playerid, "OnPlayerRequestClassFix", 1);
	TogglePlayerSpectating(playerid, true);//Собстно, начало обхода
	SetTimerEx("SetPlayerCameraPosForReqClass", 2500, 0, "i", playerid);

	switch(random(5)) {
		case 0:PlayerPlaySound(playerid, 1062,0,0,0);
		case 1:PlayerPlaySound(playerid, 1185,0,0,0);
		case 2:PlayerPlaySound(playerid, 1183,0,0,0);
		case 3:PlayerPlaySound(playerid, 1076,0,0,0);
		case 4:PlayerPlaySound(playerid, 1097,0,0,0);
	}
	gonecar[playerid] = INVALID_VEHICLE_ID;
	Dealer_OnPlayerConnect(playerid);
	Porter_OnPlayerConnect(playerid);
	CallLocalFunction("Gps_OnPlayerConnect", "i", playerid);
	CallLocalFunction("Army_OnPlayerConnect", "i", playerid);

	pPickup_Status{playerid} = false;  

	DamageTaken[playerid] = 0;

	for(new i = 0; i < sizeof(mafia_checkpoint); i++) {
		TogglePlayerDynamicCP(playerid, mafia_checkpoint[i], false);
	}
	for(new i = 0; i < sizeof(farm_checkpoint); i++) {
		TogglePlayerDynamicCP(playerid, farm_checkpoint[i], false);
	}
	for(new i = 0; i < sizeof(farm_checkpoint_1); i++) {
		TogglePlayerDynamicCP(playerid, farm_checkpoint_1[i], false);
	}
	for(new i = 0; i < sizeof(farm_checkpoint_2); i++) {
		TogglePlayerDynamicCP(playerid, farm_checkpoint_2[i], false);
	}
	for(new i = 0; i < sizeof(stealcar_checkpoint); i++) {
		TogglePlayerDynamicCP(playerid, stealcar_checkpoint[i], false);
	}
	Streamer_Update(playerid, STREAMER_TYPE_CP);
    PlayerInfo[playerid] = NULL_PlayerInfo;
    GangZoneShowForPlayer(playerid,gangzone,0xFF7F0066); // 51
 	carry[playerid] = -1;
 	gone[playerid] = -1;
 	ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]); 
    caridhouse[playerid] = INVALID_VEHICLE_ID;
    spectating[playerid] = INVALID_PLAYER_ID;
    Platform[playerid] = -1;
    for(new i = 0; i < 20; i++) {
    	SendClientMessage(playerid, -1, !" ");
    }
	SendClientMessage(playerid, -1, !""COLOR_BLUE"Добро пожаловать на мобильный сервер {FFFFFF}Chance RolePlay");
	SendClientMessage(playerid, -1, !""COLOR_BLUE"Наше сообщество Вконтакте: {FFFFFF}vk.com/ChanceRp");
	format(small_string, sizeof(small_string), ""COLOR_BLUE"Текущий онлайн: {FFFFFF}%d игроков", Iter_Count(Player));
	SendClientMessage(playerid, -1, small_string);


    PlayerLogged{playerid} = false;
    
    gpci(playerid, Client[playerid], 45);
	if(!strcmp(Client[playerid], ""Gpci069"")) {
		Platform[playerid] = 0;
	}
	if(!strcmp(Client[playerid], ""Gpci047"")) {
		SendClientMessage(playerid, -1, !""COLOR_RED"Обновите клиент до последней версии: ChanceRp.Ru/ClientAndroid.zip");
		return Kick(playerid);
	}
	else {
		for(new i; i < sizeof(RakDroidGpci); i++) {
			if(!strcmp(Client[playerid], RakDroidGpci[i])) { 
				Platform[playerid] = 2;
			}
		}
	}
	if(Platform[playerid] == -1) {
		Platform[playerid] = 1;
		new sendername[MAX_PLAYER_NAME];
		GetPlayerName(playerid, sendername, sizeof(sendername));
		if(IsRpNickname(sendername) == 0 && test_server == false)
		{
			SendClientMessage(playerid, -1, !""COLOR_RED"Используйте ник формата: {FFFFFF}Имя_Фамилия");
			return Kick(playerid);
		}
	}
	GetPlayerIp(playerid, PlayerInfo[playerid][pIP], 18);

	FULLRECON[playerid] = CreatePlayerTextDraw(playerid, 617.632446, 134.749969, "_");
	PlayerTextDrawLetterSize(playerid, FULLRECON[playerid], 0.325841, 1.337499);
	PlayerTextDrawAlignment(playerid, FULLRECON[playerid], 3);
	PlayerTextDrawColor(playerid, FULLRECON[playerid], -1);
	PlayerTextDrawSetShadow(playerid, FULLRECON[playerid], 0);
	PlayerTextDrawSetOutline(playerid, FULLRECON[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, FULLRECON[playerid], 51);
	PlayerTextDrawFont(playerid, FULLRECON[playerid], 1);
	PlayerTextDrawSetProportional(playerid, FULLRECON[playerid], 1);    
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	gonecar[playerid] = INVALID_VEHICLE_ID;

	TD_OnPlayerDisconnect(playerid);
	CallLocalFunction("LD_OnPlayerDisconnect", "ii", playerid, reason);
	CallLocalFunction("Casino_OnPlayerDisconnect", "ii", playerid, reason);
	CallLocalFunction("Gps_OnPlayerDisconnect", "ii", playerid, reason);
	CallLocalFunction("Army_OnPlayerDisconnect", "ii", playerid, reason);

	if(PlayerInfo[playerid][pAdmin] > 0) Iter_Remove(Admin,playerid);// там где админ отключается от сервера  

	if(GetPVarInt(playerid,!"OffArrest") > gettime() || GetPVarType(playerid, !"cuffed") == PLAYER_VARTYPE_INT) {
		if(PlayerInfo[playerid][pJailed] == 0) {
			PlayerInfo[playerid][pJailTime] = PlayerInfo[playerid][pWanted];
			PlayerInfo[playerid][pJailed] = 1;
			SetPlayerInt(playerid, "Jailed", PlayerInfo[playerid][pJailed]);
			SetPlayerInt(playerid, "JailTime", PlayerInfo[playerid][pJailTime]);
			PlayerInfo[playerid][pWanted] = 0;
			SetPlayerWanted(playerid, 0);
			SetPlayerInt(playerid, "Wanted", 0);

			new chat[144];
			format(chat, sizeof(chat), ""COLOR_RED"Игрок %s вышел при задержании и был отправлен в тюрьму", PlayerInfo[playerid][pName]);
			SendClientMessageToAll(-1, chat);
		}
	}
	foreach(new i: Player)
	{
		if(GetPlayerState(i) == PLAYER_STATE_SPECTATING && spectating[i] == playerid)
		{
			StopSpectate(i);
			GameTextForPlayer(i,"~r~player disconnected", 3800, 3);
		}
	}
	Dealer_OnPlayerDisconnect(playerid, reason);
	Porter_OnPlayerDisconnect(playerid, reason);

	for(new i = 0; i < sizeof(mafia_checkpoint); i++) {
		TogglePlayerDynamicCP(playerid, mafia_checkpoint[i], false);
	}
	for(new i = 0; i < sizeof(farm_checkpoint); i++) {
		TogglePlayerDynamicCP(playerid, farm_checkpoint[i], false);
	}
	for(new i = 0; i < sizeof(farm_checkpoint_1); i++) {
		TogglePlayerDynamicCP(playerid, farm_checkpoint_1[i], false);
	}
	for(new i = 0; i < sizeof(farm_checkpoint_2); i++) {
		TogglePlayerDynamicCP(playerid, farm_checkpoint_2[i], false);
	}
	for(new i = 0; i < sizeof(stealcar_checkpoint); i++) {
		TogglePlayerDynamicCP(playerid, stealcar_checkpoint[i], false);
	}
    
	if(PlayerLogged{playerid} == false || !IsPlayerConnected(playerid)) return  1;

	mysql_format(database, 
		small_string, sizeof(small_string), 
		"UPDATE `players` SET `Online` = %i WHERE Name = '%e'", 
			PlayerInfo[playerid][pOnline],
			PlayerInfo[playerid][pName]
	);
	mysql_pquery(database, small_string);
	requestt[playerid] = KillTimer(requestt[playerid]); 
	vehfixtimer[playerid] = KillTimer(vehfixtimer[playerid]); 
	RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	AzinoTimer[playerid] = KillTimer(AzinoTimer[playerid]); 
	DrugTimer[playerid] = KillTimer(DrugTimer[playerid]); 
	Timer_Speed[playerid] = KillTimer(Timer_Speed[playerid]); 
	routetimer[playerid] = KillTimer(routetimer[playerid]); 
	PlayerTimerID[playerid] = KillTimer(PlayerTimerID[playerid]); 
	ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]); 
    CopTimerID[playerid] = KillTimer(CopTimerID[playerid]); 
    BinTimer[playerid] = KillTimer(BinTimer[playerid]); 
	ThefStatus[playerid] = 0;
	TheftZone[playerid] = -1;
	TimeTCar[playerid] = 0;
	TCar[playerid] = 0;
	if(IsValidTimer(LeaveTimer[playerid])) KillTimer(LeaveTimer[playerid]),LeaveTimer[playerid] = -1;
    if(IsValidTimer(LawTimer[playerid])) KillTimer(LawTimer[playerid]),LawTimer[playerid] = -1;
    if(Lawyer == playerid) Lawyer = INVALID_PLAYER_ID;

	if(caridhouse[playerid] != INVALID_VEHICLE_ID)
	{
		DestroyVehicle(caridhouse[playerid]);
		caridhouse[playerid] = INVALID_VEHICLE_ID;
	}
	if(gone[playerid] != -1) {
		gone[playerid] = -1;
		gonecar[playerid] = INVALID_VEHICLE_ID;
	}

	if(carry[playerid] != -1) carry[playerid] = -1;

	if(robber[0] == playerid)
	{
		robber[0] = INVALID_PLAYER_ID;
	}
	if(robber[1] == playerid)
	{
		robber[1] = INVALID_PLAYER_ID;
	}
	if(robber[2] == playerid)
	{
		robber[2] = INVALID_PLAYER_ID;
	}
	if(robber[3] == playerid)
	{
		robber[3] = INVALID_PLAYER_ID;
	}
	if(robber[4] == playerid)
	{
		robber[4] = INVALID_PLAYER_ID;
	}
	if(robber[5] == playerid)
	{
		robber[5] = INVALID_PLAYER_ID;
	}
	if(robber[6] == playerid)
	{
		robber[6] = INVALID_PLAYER_ID;
	}
	if(robber[7] == playerid)
	{
		robber[7] = INVALID_PLAYER_ID;
	}
	if(robber[8] == playerid)
	{
		robber[8] = INVALID_PLAYER_ID;
	}
	if(robber[9] == playerid)
	{
		robber[9] = INVALID_PLAYER_ID;
	}
	if(robber[10] == playerid)
	{
		robber[10] = INVALID_PLAYER_ID;
	}
	if(robber[11] == playerid)
	{
		robber[11] = INVALID_PLAYER_ID;
	}
	if(robber[12] == playerid)
	{
		robber[12] = INVALID_PLAYER_ID;
	}
	if(robber[13] == playerid)
	{
		robber[13] = INVALID_PLAYER_ID;
	}

	SetPlayerWanted(playerid, 0);
	return PlayerInfo[playerid] = NULL_PlayerInfo;
}
stock PreloadAnimLib(playerid) 
{ 
    ApplyAnimation(playerid,"BOMBER","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"RAPPING","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"SHOP","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"BEACH","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"SMOKING","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"FOOD","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"ON_LOOKERS","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"DEALER","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"CRACK","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"CARRY","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"COP_AMBIENT","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"PARK","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"INT_HOUSE","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"FOOD","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"CRIB","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"ROB_BANK","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"JST_BUISNESS","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"PED","null",0.0,0,0,0,0,0); 
    ApplyAnimation(playerid,"OTB","null",0.0,0,0,0,0,0); 
    SetPVarInt(playerid, "Animations", 1); 
}  
public OnPlayerSpawn(playerid)
{
	if(GetPVarInt(playerid, "Logged") != 1) return 0; 
	NPC_OnPlayerSpawn(playerid);

	PlayerPlaySound(playerid, 1098 , 0.0, 0.0, 0.0); // Проигрываем пустой звук чтобы выключить звук с авторизации

	if(!GetPVarInt(playerid, "Animations")) PreloadAnimLib(playerid);  // Прогружаем анимации

	DeletePVar(playerid, "OnPlayerRequestClass_F4_Bug");

	if(GetPVarInt(playerid, !"spec") == 1) { // Возвращаем игрока на место после слежки
		SetPlayerPos(playerid,GetPVarFloat(playerid, !"pos_x"), GetPVarFloat(playerid, !"pos_y"), GetPVarFloat(playerid, !"pos_z"));
		SetPlayerFacingAngle(playerid, GetPVarFloat(playerid, !"pos_angle"));
		SetCameraBehindPlayer(playerid);
		SetPlayerInterior(playerid, GetPVarInt(playerid, !"pos_int"));
		SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, !"pos_vw"));
		DeletePVar(playerid, !"pos_x");
		DeletePVar(playerid, !"pos_y");
		DeletePVar(playerid, !"pos_z");
		DeletePVar(playerid, !"pos_angle");
		DeletePVar(playerid, !"pos_int");
		DeletePVar(playerid, !"pos_vw");
		DeletePVar(playerid, !"spec");
	    if(GetPVarInt(playerid, "Mask") == 1) SetPlayerColor(playerid, 0x7a766700);
		return 1;
	}

	SetCameraBehindPlayer(playerid);

	ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]); // Завершаем таймер возвращения в авто
	if(gone[playerid] != -1) {
		gone[playerid] = -1;
		gonecar[playerid] = INVALID_VEHICLE_ID;
		goneaway(playerid);
	}

    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE); // Сбрасываем специальное действие


    // Завершаем авиарейсы
    RouteAir2[playerid] = 0;
    RouteAir[playerid] = 0;
    // 

	new 
		Fraction:fractionid = GetPlayerFraction(playerid);

	if(PlayerInfo[playerid][pJailed] > 0) return 1; // Если игрок в тюрьме позиция будет дана в секундном таймере

	if(fractionid == FRACTION_ARMY) {
			GivePlayerWeapon(playerid, 24, 60);
			GivePlayerWeapon(playerid, 31, 150);
			SetPlayerArmour(playerid, 100);
			SetPlayerFacingAngle(playerid, 90);
			SetPlayerInterior(playerid, 0);
			return SendClientMessage(playerid, -1, !""COLOR_RED"До окончания службы вы будете появляться на базе армии");
	}
	if(IsPlayerInHouse(playerid) == true) {
		return House.LinkPlayer(playerid, GetPlayerHouse(playerid));
	}

	if(fractionid == FRACTION_NONE) {
		SetPlayerInterior(playerid, 0);
		if(GetPVarInt(playerid, "JustCreated") == 1) {
			SetPlayerVirtualWorld(playerid, 12);
			SetPlayerFacingAngle(playerid, 270);
			return DeletePVar(playerid, "JustCreated");
		}
		return 1;
	}
	if(fractionid == FRACTION_LSPD) {
		GivePlayerWeapon(playerid, 24, 150);
		GivePlayerWeapon(playerid, 25, 80);
		GivePlayerWeapon(playerid, 3, 1);
		SetPlayerArmour(playerid, 100);
		SetPlayerInterior(playerid, 0);
		return 1;
	}
	if(fractionid == FRACTION_GROOVE) {
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 5, 1);
		return 1;
	}
	if(fractionid == FRACTION_BALLAS) {
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 5, 1);
		SetPlayerInterior(playerid, 1);
		return 1;
	}
	if(fractionid == FRACTION_VAGOS) {
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 5, 1);
		SetPlayerInterior(playerid, 1);
		return 1;
	}
	if(fractionid == FRACTION_RIFA) {
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 5, 1);
		SetPlayerInterior(playerid, 1);
		return 1;
	}
	if(fractionid == FRACTION_AZTECAS) {
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 5, 1);
		SetPlayerInterior(playerid, 1);
		return 1;
	}
	if(fractionid == FRACTION_RUSSIAN_MAFIA) {
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 30, 150);
		GivePlayerWeapon(playerid, 1, 1);
		SetPlayerInterior(playerid, 1);
		return 1;
	}
	if(fractionid == FRACTION_TRIADA) {
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 8, 1);
		SetPlayerInterior(playerid, 1);
		return 1;
	}
	if(fractionid == FRACTION_DN_BOYS) {
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 8, 1);
		SetPlayerInterior(playerid, 1);
		return 1;
	}
	if(fractionid == FRACTION_FBI) {
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		SetPlayerArmour(playerid, 100);
		SetPlayerInterior(playerid, 2);
		SetPlayerVirtualWorld(playerid, 2);
		return 1;
	}
	if(fractionid == FRACTION_GOVERMENT) {
		SetPlayerInterior(playerid, 1);
		SetPlayerVirtualWorld(playerid, 0);
		return 1;
	}
	return 1;
}
forward UpdateSpawnInfo(playerid);
public UpdateSpawnInfo(playerid) 
{
	new 
	Fraction:fractionid = GetPlayerFraction(playerid);	
	if(fractionid == FRACTION_ARMY) return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 240.7176,1859.7965,14.0840, 270, 0, 0, 0, 0, 0, 0);
	if(GetPlayerHouse(playerid) > 0) {
		new house = GetPVarInt(playerid, "PlayerHouse");
		switch(OLD_HouseInfo[house][hClass]) {
			case 0..1: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), OLD_HouseInfo[house][hExitx]-4, OLD_HouseInfo[house][hExity]+2,OLD_HouseInfo[house][hExitz], 270, 0, 0, 0, 0, 0, 0);
		 	case 2: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), OLD_HouseInfo[house][hExitx], OLD_HouseInfo[house][hExity]+3,OLD_HouseInfo[house][hExitz], 180, 0, 0, 0, 0, 0, 0);
		 	case 3..4: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), OLD_HouseInfo[house][hExitx], OLD_HouseInfo[house][hExity]+8,OLD_HouseInfo[house][hExitz], 180, 0, 0, 0, 0, 0, 0);
		 	case 5: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), OLD_HouseInfo[house][hExitx]+2, OLD_HouseInfo[house][hExity]+12,OLD_HouseInfo[house][hExitz], 180, 0, 0, 0, 0, 0, 0);
			default: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), OLD_HouseInfo[house][hExitx]-4, OLD_HouseInfo[house][hExity]+2,OLD_HouseInfo[house][hExitz], 270, 0, 0, 0, 0, 0, 0);
		}
	}
	if(fractionid == FRACTION_NONE) {
	if(GetPVarInt(playerid, "JustCreated") == 1) return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1669.9775,-2332.2957,1905.4918, 270, 0, 0, 0, 0, 0, 0);
	if(GetPlayerScore(playerid) < 1) {	
	    switch(random(4)) {
			case 0: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1664.2942,-2297.4575,-1.2072, 0, 0, 0, 0, 0, 0, 0);
			case 1: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1664.3304,-2283.1606,-1.2395, 360, 0, 0, 0, 0, 0, 0);
			case 2: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1682.3468,-2297.1970,-1.2161, 0, 0, 0, 0, 0, 0, 0);
			case 3: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1682.3192,-2283.2170,-1.2377, 360, 0, 0, 0, 0, 0, 0);
		}
	}
	if(GetPlayerScore(playerid) > 1) {
	    switch(random(7)) {
			case 0: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1755.4962,-1925.4510,13.5747, 0, 0, 0, 0, 0, 0, 0);
			case 1: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1755.4924,-1924.4202,13.5742, 0, 0, 0, 0, 0, 0, 0);
			case 2: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1108.5388,-1790.3772,16.5938, 90, 0, 0, 0, 0, 0, 0);
			case 3: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1109.2759,-1793.3378,16.5938, 90, 0, 0, 0, 0, 0, 0);
			case 4: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1108.8644,-1796.4742,16.5938, 90, 0, 0, 0, 0, 0, 0);
			case 5: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1108.9258,-1799.5568,16.5938, 90, 0, 0, 0, 0, 0, 0);
			case 6: return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1109.0804,-1802.7028,16.5938, 90, 0, 0, 0, 0, 0, 0);
		}
	}
	}
	if(fractionid == FRACTION_LSPD) return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1552.4500,-1674.9900,16.1953, 90, 0, 0, 0, 0, 0, 0);
	if(fractionid == FRACTION_GROOVE) return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 2495.2859,-1688.5461,13.8737, 0, 0, 0, 0, 0, 0, 0);
	if(fractionid == FRACTION_BALLAS) return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 2742.2385,-1774.7386,25.5106, 0, 0, 0, 0, 0, 0, 0);
	if(fractionid == FRACTION_VAGOS)  return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 2692.4290,-1566.8107,20.0395, 0, 0, 0, 0, 0, 0, 0);
	if(fractionid == FRACTION_RIFA)  return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 2163.1985,-1778.1453,13.7867, 0, 0, 0, 0, 0, 0, 0);
	if(fractionid == FRACTION_AZTECAS)  return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1674.5515,-2056.9834,14.2142, 0, 0, 0, 0, 0, 0, 0);
	if(fractionid == FRACTION_RUSSIAN_MAFIA)  return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1085.6416,1552.5817,5.9481, 0, 0, 0, 0, 0, 0, 0);
	if(fractionid == FRACTION_TRIADA)  return SetSpawnInfo(playerid, 0, GBackSkin(playerid), -2264.1753,476.8297,43.8076, 0, 0, 0, 0, 0, 0, 0);
	if(fractionid == FRACTION_DN_BOYS)  return SetSpawnInfo(playerid, 0, GBackSkin(playerid), -1539.7102,1144.3630,7.2198, 0, 0, 0, 0, 0, 0, 0);
	if(fractionid == FRACTION_FBI)  return SetSpawnInfo(playerid, 0, GBackSkin(playerid), -2455.2639,535.3552,432.6741, 90, 0, 0, 0, 0, 0, 0);
	if(fractionid == FRACTION_GOVERMENT)  return SetSpawnInfo(playerid, 0, GBackSkin(playerid), 1491.7451,-1759.5736,485.0971, 90, 0, 0, 0, 0, 0, 0);
	return 1;
}
public OnPlayerRequestClass(playerid, classid) {

	NPC_OnPlayerRequestClass(playerid, classid);

	UpdateSpawnInfo(playerid);
	if(!GetPVarInt(playerid, "OnPlayerRequestClassFix"))
	{
	    if(GetPVarInt(playerid, "OnPlayerRequestClass_F4_Bug")) return SpawnPlayer(playerid);
	    TogglePlayerSpectating(playerid, true);
	    SetTimerEx("TogglePlayerSpectatingOff", 500, 0, "i", playerid);
	}
	else {
	DeletePVar(playerid, "OnPlayerRequestClassFix");
	SpawnPlayer(playerid);   
	}
	return 1;
}
public OnPlayerDeath(playerid, killerid, reason)
{
	if(IsPlayerNPC(playerid)) return 1;
	UpdateSpawnInfo(playerid);
	CallLocalFunction("GPS_OnPlayerDeath", "i", playerid);
	foreach(new i:Admin) SendDeathMessageToPlayer(i,killerid, playerid, reason);  
	if(GetPVarType(playerid, !"oncapture") == PLAYER_VARTYPE_INT) {
	for(new i = 1;i<=TOTALGZ;i++) {
		if(PlayerInGangZone(playerid,GZInfo[i][gCoords][0], GZInfo[i][gCoords][1],GZInfo[i][gCoords][2],GZInfo[i][gCoords][3]) && ZoneOnBattle[i] == 1)
		{
			new 
			Fraction:fractionid = GetPlayerFraction(playerid);

			if(Fraction:GZInfo[i][gNapad] == fractionid)
			{ 
			GangInfo[GZInfo[i][gFrak]][score] += 1;
			return SpawnPlayer(playerid);
			}	
			if(Fraction:GZInfo[i][gFrak] == fractionid)
			{
			GangInfo[GZInfo[i][gNapad]][score] += 1;
			return SpawnPlayer(playerid);
			}
		}		
	}
	SpawnPlayer(playerid);
	}
	return 1;
}
forward SetPlayerCameraPosForReqClass(playerid);
public SetPlayerCameraPosForReqClass(playerid)
{
		InterpolateCameraPos(playerid, 1687.801391, -1841.209228, 18.435420, 1679.957885, -1960.452270, 52.511661, 120000);
		InterpolateCameraLookAt(playerid, 1691.862915, -1844.102783, 18.072778, 1683.251708, -1957.590332, 50.070373, 120000);
		if(Platform[playerid] == 0) return SPD(playerid, dName, DIALOG_STYLE_INPUT, "Добро пожаловать!", "Введите ваш ник (Используйте формат: Имя_Фамилия)", "Далее", "");
		LoadAccounts(playerid);
		return 1;
}

forward TogglePlayerSpectatingOff(playerid);
public TogglePlayerSpectatingOff(playerid) 
{
    TogglePlayerSpectating(playerid, false),
    SetPVarInt(playerid, "OnPlayerRequestClass_F4_Bug", GetPVarInt(playerid, "OnPlayerRequestClass_F4_Bug")+1);//Чпок
}  
public OnVehicleSpawn(vehicleid)
{
	foreach(new i: Player)
	{
		if(caridhouse[i] == vehicleid) return SetVehicleParamsForPlayerEx(vehicleid,i,0,1);
		else SetVehicleParamsForPlayerEx(vehicleid,i,0,0); 
	}
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

forward OffJails(playerid, name[]);
public OffJails(playerid, name[])
{
		new rows = cache_get_row_count();
        if(!rows) return SendClientMessage(playerid,-1,!""COLOR_RED"Игрок не найден в базе данных"); // Если аккаунт не найден,то выводим текст
        new temp_int, admin_int;
		temp_int = cache_get_field_content_int(0, "isOnline");
		admin_int = cache_get_field_content_int(0, "Admin");
		if(temp_int == 1) {
			return SendClientMessage(playerid, -1, !""COLOR_RED"Игрок под данным именем в игре");
		}
		if(admin_int > 0) {
			return 1;
		}
    	new string[256],reason[32]; // Создаём переменные
    	GetPVarString(playerid,"OffJailReason",reason,sizeof(reason)); // Достаём причину для тюрьмы из PVar
    	format(string,sizeof(string),"UPDATE "TABLE_ACCOUNTS" SET `Jailed` = '2', `JailTime` = '%d' WHERE `Name` = '%s'",GetPVarInt(playerid,"OffJailDay")*60, name); // Форматируем запрос (Вместо `Jail` и `Name` у Вас могут быть другие переменные)
        mysql_tquery(database, string, "", ""); // Отправляем запрос
        format(string,sizeof(string),""COLOR_RED"[Offline] Администратор %s посадил %s в тюрьму на %d мин. Причина: %s",PlayerInfo[playerid][pName],name, GetPVarInt(playerid,"OffJailDay"),reason); // Форматируем текст для всех
        SendAdminMessage(-1, string); 
        DeletePVar(playerid,"OffJailReason"); // Удаляем PVar
        DeletePVar(playerid,"OffMJailDay");// Удаляем PVar
        return 1;
}
forward OffMute(playerid, name[]);
public OffMute(playerid, name[])
{
		new rows = cache_get_row_count();
        if(!rows) return SendClientMessage(playerid,-1,!""COLOR_RED"Игрок не найден в базе данных"); // Если аккаунт не найден,то выводим текст
        new temp_int, admin_int;
		temp_int = cache_get_field_content_int(0, "isOnline");
		admin_int = cache_get_field_content_int(0, "Admin");
		if(temp_int == 1) {
			return SendClientMessage(playerid, -1, !""COLOR_RED"Игрок под данным именем в игре");
		}
		if(admin_int > 0) {
			return 1;
		}
    	new string[256],reason[32]; // Создаём переменные
    	GetPVarString(playerid,"OffMuteReason",reason,sizeof(reason)); // Достаём причину для тюрьмы из PVar
    	format(string,sizeof(string),"UPDATE "TABLE_ACCOUNTS" SET `Muted` = '1', `MuteTime` = '%d' WHERE `Name` = '%s'",GetPVarInt(playerid,"OffMuteDay")*60, name); // Форматируем запрос (Вместо `Jail` и `Name` у Вас могут быть другие переменные)
        mysql_tquery(database, string, "", ""); // Отправляем запрос
        format(string,sizeof(string),""COLOR_RED"[Offline] Администратор %s заблокировал чат игроку %s. Причина: %s",PlayerInfo[playerid][pName],name,reason); // Форматируем текст для всех
        SendAdminMessage(-1, string); 
        DeletePVar(playerid,"OffMuteReason"); // Удаляем PVar
        DeletePVar(playerid,"OffMuteDay");// Удаляем PVar
        return 1;
}
forward OffBan(playerid, name[]);
public OffBan(playerid, name[])
{
		new rows = cache_get_row_count();
        if(!rows) return SendClientMessage(playerid,-1,!""COLOR_RED"Игрок не найден в базе данных"); // Если аккаунт не найден,то выводим текст
        new temp_int, admin_int;
		temp_int = cache_get_field_content_int(0, "isOnline");
		admin_int = cache_get_field_content_int(0, "Admin");
		if(temp_int == 1) {
			return SendClientMessage(playerid, -1, !""COLOR_RED"Игрок под данным именем в игре");
		}
		if(admin_int > 0) {
			return 1;
		}
    	new string[256],reason[32]; // Создаём переменные
    	GetPVarString(playerid,"OffBanReason",reason,sizeof(reason)); // Достаём причину для тюрьмы из PVar
    	format(string,sizeof(string),"UPDATE "TABLE_ACCOUNTS" SET `Banned` = '1' WHERE `Name` = '%s'", name); // Форматируем запрос (Вместо `Jail` и `Name` у Вас могут быть другие переменные)
        mysql_tquery(database, string, "", ""); // Отправляем запрос
        format(string,sizeof(string),""COLOR_RED"[Offline] Администратор %s заблокировал %s. Причина: %s",PlayerInfo[playerid][pName],name,reason); // Форматируем текст для всех
        SendAdminMessage(-1, string); 
        DeletePVar(playerid,"OffBanReason"); // Удаляем PVar
        return 1;
}
public OnPlayerText(playerid, text[])
{
	if(GetPVarType(playerid, !"tasered") == PLAYER_VARTYPE_INT) {
		return 0;
	}
    if(GetPVarInt(playerid, "DialogID"))
    {
        return 0;
    }
	new speach[144];
	if(PlayerInfo[playerid][pMuted] > 0) {
		format(speach, sizeof(speach), ""COLOR_RED"У Вас бан чата! Осталось: %d минут", PlayerInfo[playerid][pMuteTime] / 60);
		SendClientMessage(playerid, -1, speach);
		return 0;
	} else {
		if(GetPVarInt(playerid,"AntiFloodLocal") > gettime()){ SendClientMessage(playerid, -1, !""COLOR_RED"Пожалуйста не флудите"); return false; }
		SetPVarInt(playerid,"AntiFloodLocal",gettime() + 3);
		format(speach, sizeof(speach), "- %s[%d]: %s", PlayerInfo[playerid][pName],playerid, text);
		SetPlayerChatBubble(playerid, text, 0x6ab1ffaa, 20.0, 10000);
		ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_CHAT, speach);
		return 0;
	}
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
	if(GetPVarType(playerid, !"cuffed") == PLAYER_VARTYPE_INT) {
		ApplyAnimation(playerid, "PED", "cower", 1, 1, 0, 0, 0, 0, 1);
		return 0;
	}
    if(GetPVarInt(playerid, "DialogID"))
    {
        return false;
    }
	if(GetPVarInt(playerid,"AntiFloodCMD") > gettime()) { 
		SendClientMessage(playerid, -1, !""COLOR_RED"Пожалуйста не флудите"); 
		return false; 
	}
	SetPVarInt(playerid,"AntiFloodCMD",gettime() + 2);
	return 1;
}
public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if(PlayerInfo[playerid][pAdmin] > 1) SetPlayerPosFindZ(playerid, fX, fY, fZ); 
    return 1;
}
CMD:capture(playerid,params[])
{
	for(new i = 1;i<=TOTALGZ;i++) {
		if(PlayerInGangZone(playerid,GZInfo[i][gCoords][0], GZInfo[i][gCoords][1],GZInfo[i][gCoords][2],GZInfo[i][gCoords][3]) && ZoneOnBattle[i] == 0)
		{
				if(GZInfo[i][gid] == 102 || GZInfo[i][gid] == 69 || GZInfo[i][gid] == 55 || GZInfo[i][gid] == 56|| GZInfo[i][gid] == 44 || GZInfo[i][gid] == 45 || GZInfo[i][gid] == 42) {
					return SendClientMessage(playerid,-1,!""COLOR_RED"Война за данную территорию невозможна");	
				} 
				if(ZoneOnBattle[i] == 1) {
					format(small_string, 127,""COLOR_BLUE"Идет война за территорию между %s и %s", GetGangName(GZInfo[i][gNapad]), GetGangName(GZInfo[i][gFrak]));
					SendClientMessage(playerid,-1, small_string);
					return 1;
				}

				format(small_string, 127,""COLOR_BLUE"Территория находится под влиянием: {FFFFFF}%s", GetGangName(GZInfo[i][gFrak]));
				SendClientMessage(playerid,-1, small_string);
				new 
				Fraction:fractionid = GetPlayerFraction(playerid);

			    if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid > FRACTION_LSPD) {
			    format(small_string,sizeof(small_string),"startcapture - %d",startcapture);
				SendClientMessage(playerid, -1, small_string);
				if(startcapture > 0) return SendClientMessage(playerid,-1,!""COLOR_ORANGE"В этом часу уже была война за территорию");
				new gonline[2];
		  		new 
		  			Fraction:target_fractionid;
		  		foreach(new b: Player)
				{
					target_fractionid = GetPlayerFraction(b);
					if(_:target_fractionid == _:fractionid) gonline[0]++;
					if(_:target_fractionid == _:GZInfo[i][gFrak]) gonline[1]++;
				}
				if(Warehouse[_:fractionid] < 25) return SendClientMessage(playerid, -1, ""COLOR_RED"На складе вашей банды недостаточно материалов. Необходимо: 25");
				if(PlayerInfo[playerid][pKarma] > -100) return SendClientMessage(playerid, -1, !""COLOR_RED"Необходимо -100 законопослушности");
				if(gonline[0] < 5) return SendClientMessage(playerid, -1, !""COLOR_RED"В вашей банде недостаточно людей для нападения. Необходимо: 5");
				if(gonline[1] < 5) return SendClientMessage(playerid, -1, !""COLOR_RED"У данной банды недостаточно людей в сети. Необходимо: 5");
				Warehouse[_:fractionid] -= 25;
				if(GangInfo[_:fractionid][capture] == 1) return SendClientMessage(playerid, -1, !""COLOR_ORANGE"Ваша банда уже учавствует в захвате зоны");
				if(GangInfo[GZInfo[i][gFrak]][capture] == 1) return SendClientMessage(playerid, -1, !""COLOR_ORANGE"Банда, на которую вы хотите напасть уже учавствует в захвате зоны!");
				if(_:GZInfo[i][gFrak] == _:fractionid) return SendClientMessage(playerid, -1, !""COLOR_ORANGE"Вы не можете захватывать зону вашей банды");
				if(IsCapture == 1) return SendClientMessage(playerid, -1, !""COLOR_RED"Уже происходит захват зоны. Дождитесь окончания!");
				IsCapture = 1;
				ZoneCapture = i;
				new zahvatka[128];
				new zahvat[128];
				GZInfo[i][gNapad] = _:fractionid;
				format(zahvatka, 127,""COLOR_BLUE"На вашу территорию напала банда {FFFFFF}%s", GetGangName(GZInfo[i][gNapad]));
				SendFamilyMessage(Fraction:GZInfo[i][gFrak],-1,zahvatka);
				SendFamilyMessage(Fraction:GZInfo[i][gFrak], -1, ""COLOR_BLUE"Эта зона будет мигать на карте 10 минут");
	            SendFamilyMessage(Fraction:GZInfo[i][gFrak], -1, ""COLOR_BLUE"Территория достанется стороне которая сделает больше убийств");
				format(small_string, sizeof(small_string), ""COLOR_BLUE"Если ваших людей будет меньше в квадрате, территория перейдет к {FFFFFF}%s", GZInfo[i][gNapad]);
				format(zahvat,128,"{FFFFFF}%s"COLOR_BLUE" начал захват зоны банды {FFFFFF}%s",PlayerInfo[playerid][pName],GetGangName(GZInfo[i][gFrak]));
				SendFamilyMessage(fractionid,-1,zahvat);
				SendFamilyMessage(fractionid, -1, ""COLOR_BLUE"Эта зона будет мигать на карте 10 минут");
				SendFamilyMessage(fractionid, -1, ""COLOR_BLUE"Территория достанется стороне которая сделает больше убийств");
				SendAdminMessage(-1, ""COLOR_ORANGE"Началась война за территорию");
				GZSafeTime[i] = 600;
				ZoneOnBattle[i] = 1;
				GangInfo[_:fractionid][capture] = 1;
				GangInfo[GZInfo[i][gFrak]][capture] = 1;
				GangInfo[GZInfo[i][gFrak]][captureid] = _:fractionid;
				GangInfo[_:fractionid][captureid] = _:fractionid;
				SetTimer("GangWar", 1000, 0);
				startcapture = 1;
			}
		}
	}
	return 1;
}

CMD:taser(playerid, params[])
{
	if(GetPVarInt(playerid,"AntiFloodMm") > gettime()) return SendClientMessage(playerid, -1, !""COLOR_RED"Тазер может выпускать заряд раз в 10 секунд");
   	SetPVarInt(playerid,"AntiFloodMm",gettime() + 10);

	if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "Нельзя использовать в транспорте");
		
	new 
	Fraction:fractionid = GetPlayerFraction(playerid);

	if(fractionid != FRACTION_LSPD) return 1;
    extract params -> new player:target; else
        return SendClientMessage(playerid, -1, !"Используйте: /(t)aser [id преступника]");

    if(target == INVALID_PLAYER_ID)
        return 1;

    if(target == playerid)
        return 1;

    if(GetDistanceBetweenPlayerz(playerid, target, 8) != 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок слишком далеко");

    if(PlayerInfo[target][pWanted] == 0) return SendClientMessage(playerid, -1, !""COLOR_RED"Игрок не в розыске!");
	
    if(GetPVarType(target, !"tasered") == PLAYER_VARTYPE_INT)
        return SendClientMessage(playerid, -1, !""COLOR_ORANGE"Игрок уже оглушен!");

    if(GetPVarType(target, !"cuffed") == PLAYER_VARTYPE_INT)
    return SendClientMessage(playerid, -1, !""COLOR_RED"Игрок в наручниках");

    SetPVarInt(target, !"tasered", 0);

    if(IsPlayerInAnyVehicle(playerid)) 

    TogglePlayerControllable(target, 0);
    ApplyAnimation(target, "CRACK", "crckdeth1", 4.0, 1, 0, 0, 0, 0);

    SetTimerEx(!"UnTaserPlayer", 1000*7, false, "i", target);

    new
        string[90];

	format(string, sizeof(string), " %s оглушил(а) %s шокером", PlayerInfo[playerid][pName], PlayerInfo[target][pName]);
	ProxDetector(playerid, 20, C_PURPLE, string);
    return 1;
}
alias:taser("t");
cmd:cuff(playerid, params[]) {
	if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "Нельзя использовать в транспорте");
		
	new 
	Fraction:fractionid = GetPlayerFraction(playerid);

	if(fractionid != FRACTION_LSPD) return 1;
    extract params -> new player:target; else
        return SendClientMessage(playerid, -1, !"Используйте: /cuff [id преступника]");

    if(target == INVALID_PLAYER_ID)
        return SendClientMessage(playerid, -1, ""COLOR_RED"Неверный ID");

    if(target == playerid)
        return SendClientMessage(playerid, -1, ""COLOR_RED"Нельзя надеть наручники на себя");

	if(GetDistanceBetweenPlayerz(playerid, target, 8) != 1)
	return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок слишком далеко");

    if(GetPVarType(target, !"cuffed") == PLAYER_VARTYPE_INT)
    return SendClientMessage(playerid, -1, !""COLOR_RED"Игрок уже в наручниках");	

    if(GetPVarType(target, !"tasered") != PLAYER_VARTYPE_INT)
    return SendClientMessage(playerid, -1, !""COLOR_RED"Игрок не оглушен, используйте /taser");

	if(PlayerInfo[target][pWanted] == 0) return SendClientMessage(playerid, -1, !""COLOR_RED"Игрок не в розыске!");

	TogglePlayerControllable(target, 0);
	ApplyAnimation(target, "PED", "cower", 1, 1, 0, 0, 0, 0, 1);

	DeletePVar(target, !"tasered");

	SetPVarInt(target, !"cuffed", 0);

    new
    string[90];

	format(string, sizeof(string), " %s заключил(а) %s в наручники", PlayerInfo[playerid][pName], PlayerInfo[target][pName]);
	ProxDetector(playerid, 20, C_PURPLE, string);
	return 1;

}
cmd:cput(playerid, params[]) {
	if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы должны сидеть в служебном автомобиле");
		
	new 
	Fraction:fractionid = GetPlayerFraction(playerid),
	vehicle_owner;

	if(fractionid != FRACTION_LSPD) return 1;

    extract params -> new player:target; else
        return SendClientMessage(playerid, -1, !"Используйте: /cuff [id преступника]");

    if(target == INVALID_PLAYER_ID)
        return 1;

    if(target == playerid)
        return 1;


	if(GetDistanceBetweenPlayerz(playerid, target, 7) != 1)
	return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок слишком далеко");

    if(GetPVarType(target, !"incar") == PLAYER_VARTYPE_INT)
    return 1;

    if(GetPVarType(target, !"cuffed") != PLAYER_VARTYPE_INT)
    return SendClientMessage(playerid, -1, !""COLOR_RED"Игрок должен быть в наручниках");

	new vehicleid = GetPlayerVehicleID(playerid);

	for(new i = 0; i < sizeof(VehicleInfo); i++) {
		if(VehicleInfo[i][VI_VehicleID] == vehicleid) {
			vehicle_owner = VehicleInfo[i][VI_Owner];

			if(vehicle_owner == VO_FRACTION_LSPD) {
				new freeseat = GetFreeSeat(vehicleid);
				if(freeseat == -1) return SendClientMessage(playerid, -1, !""COLOR_RED"Все места в автомобиле заняты");
				PutPlayerInVehicle(target, vehicleid, freeseat);
				SetPVarInt(target, !"incar", 0);
			}
			else return SendClientMessage(playerid, -1, !""COLOR_RED"Вы должны сидеть в служебном автомобиле");
		}
	}
	return 1;
}
stock PutPlayerBackToPoliceCar(playerid, vehicleid) {
	new vehicle_owner;
	for(new i = 0; i < sizeof(VehicleInfo); i++) {
		if(VehicleInfo[i][VI_VehicleID] == vehicleid) {
			vehicle_owner = VehicleInfo[i][VI_Owner];

			if(vehicle_owner == VO_FRACTION_LSPD) {
				new freeseat = GetFreeSeat(vehicleid);
				if(freeseat == -1) return 1;
				PutPlayerInVehicle(playerid, vehicleid, freeseat);
				SetPVarInt(playerid, !"incar", 0);
			}
			else return 1;
		}
	}
	return 1;
}
cmd:arrest(playerid, params[]) {
	new 
	Fraction:fractionid = GetPlayerFraction(playerid);

	if(fractionid != FRACTION_LSPD) return 1;

    extract params -> new player:target; else
        return SendClientMessage(playerid, -1, !"Используйте: /cuff [id преступника]");

    if(target == INVALID_PLAYER_ID)
        return 1;

    if(target == playerid)
        return 1;

    DeletePVar(target, !"incar");

    if(GetDistanceBetweenPlayerz(playerid, target, 7) != 1) 
    return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок слишком далеко от вас");

    if(GetPVarType(target, !"cuffed") != PLAYER_VARTYPE_INT)
    return SendClientMessage(playerid, -1, !""COLOR_RED"Игрок должен быть в наручниках");

    DeletePVar(target, !"cuffed");

	if(!IsPlayerInRangeOfPoint(playerid, 15, 1568.9657,-1693.8596,5.8906)) 
	return SendClientMessage(playerid, -1, !""COLOR_RED"Вы должны быть рядом с гаражом полицейского департамента");

	format(small_string, 100, "- %s[%d]: Вы задержаны и отправляетесь в КПЗ", PlayerInfo[playerid][pName], playerid);
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_CHAT, small_string);
	format(small_string, 100, ""COLOR_BLUE"Полицейский %s успешно арестовал %s", PlayerInfo[playerid][pName], PlayerInfo[target][pName]);
	SendPoliceAlert(-1, small_string);
	PlayerInfo[target][pJailTime] = PlayerInfo[target][pWanted];
	PlayerInfo[target][pJailed] = 1;
	SetPlayerInt(target, "Jailed", PlayerInfo[target][pJailed]);
	SetPlayerInt(target, "JailTime", PlayerInfo[target][pJailTime]);

	new it = PlayerInfo[target][pJailTime]/10;
	format(small_string,sizeof(small_string),"~g~+%d ~w~EXP", it);
	GameTextForPlayer(playerid, small_string, 3000, 5);

	IncreaseKarma(playerid);
	Player.AddEXP(PlayerInfo[playerid][pID], it, E_ARREST, playerid);
 	if(PlayerInfo[target][pWanted] > 0) {
		PlayerInfo[target][pWanted] = 0;
		SetPlayerWanted(target, 0);
		SetPlayerInt(target, "Wanted", 0);
	}
	return 1;
}
stock GetFreeSeat(vehicleid)
{
    if(!vehicleid) return -1;
    new model = GetVehicleModel(vehicleid);    
    new maxs = GetMaxSeat(model) - 1;
    new bool:seat[3],cnt;    
    for(new i;i<MAX_PLAYERS;i++)
    {
        if(!IsPlayerConnected(i) || GetPlayerVehicleID(i) != vehicleid) continue;
        new pseat = GetPlayerVehicleSeat(i);
        if(pseat < 1 || pseat > 3) continue;
        seat[pseat-1] = true;
        cnt++;
        if(cnt >= maxs) return -1;        
    }
    for(new i;i<3;i++) if(!seat[i]) return i+1;
    return -1;
}
stock GetMaxSeat(modelid)
{
    switch(modelid)
    {
        case 596..598,427,490: return 4;
        case 599,497,528: return 2;        
    }
    return -1;
}  
forward UnTaserPlayer(playerid);
public UnTaserPlayer(playerid)
{
	if(GetPVarType(playerid, !"cuffed") == PLAYER_VARTYPE_INT) return 1;
    if(playerid == INVALID_PLAYER_ID)
        return 0;

    TogglePlayerControllable(playerid, 1);
    DeletePVar(playerid, !"tasered");
    return 1;
}  
CMD:hi(playerid, params[])
{
	if(IsPlayerConnected(playerid))
	{
		if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "Нельзя использовать в транспорте");
		new id,string[200];
		if(sscanf(params,"d",id)) return SendClientMessage(playerid, -1, "Используйте: /hi [id игрока]");
		if(!IsPlayerConnected(id)) return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок не найден");
		if(id == INVALID_PLAYER_ID) return SendClientMessage(playerid, -1, ""COLOR_RED"Игрок не найден");
		if(id == playerid) return 1;
  		new Float:X, Float:Y, Float:Z;
    	GetPlayerPos(id, X, Y, Z);
	    new Float:distance = GetPlayerDistanceFromPoint(playerid, X, Y, Z);
		if(distance < 1.5 && distance > 0.5 )
		{
  			new Float:angle;
			GetPlayerFacingAngle(playerid, angle);
			SetPlayerFacingAngle(id, angle + 180);
			format(string, sizeof(string), " %s пожал(а) руку игроку %s", PlayerInfo[playerid][pName], PlayerInfo[id][pName]);
			ProxDetector(playerid, 20, C_PURPLE, string);
			ApplyAnimation(playerid,"GANGS","hndshkfa",4.1, 0, 1, 1, 0, 0, 1);
			ApplyAnimation(id,"GANGS","hndshkfa",4.1, 0, 1, 1, 0, 0, 1);
			return true;
		}
		else if (distance < 20.0)
		{
			format(string,sizeof(string)," %s машет рукой игроку %s",PlayerInfo[playerid][pName], PlayerInfo[id][pName]);
			ProxDetector(playerid, 20, C_PURPLE, string);
			ApplyAnimation(playerid, "PED", "endchat_03", 4.1, 0, 1, 1, 0, 0, 1);
		}
		else SendClientMessage(playerid, -1,  ""COLOR_ORANGE"Вы слишком далеко от указанного игрока");
	}
	return true;
}
CMD:kiss(playerid, params[])
{
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "Используйте: /kiss [id игрока]");
	if(GetPVarInt(playerid,"LOLIKATime") > gettime()) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Подождите немного");
	if(playerid == params[0]) return true;
	if(GetDistanceBetweenPlayerz(playerid, params[0], 2.00) != 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы слишком далеко от указанного игрока");
	new Float:angle;
	GetPlayerFacingAngle(playerid, angle);
	SetPlayerFacingAngle(params[0], angle + 180);
	format(small_string, sizeof(small_string), "%s поцеловал(а) %s", PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName]);
	ProxDetector(playerid, 20, C_PURPLE, small_string);
	ApplyAnimation(playerid, "KISSING", "Playa_Kiss_02", 3.0, 0, 0, 0, 0, 0); // Kiss
	ApplyAnimation(params[0], "KISSING", "Playa_Kiss_02", 3.0, 0, 0, 0, 0, 0); // Kiss
	SetPVarInt(playerid,"LOLIKATime",gettime()+10);
	return true;
}
CMD:offjail(playerid,params[])
{
    	if(PlayerInfo[playerid][pAdmin] < 4) return 1; // Проверка на админ.права
        new query[128],param_name[24],param_reason[32],param_day; // Лично у меня не работали params[0],params[1] и params[2] поэтому я создал только так.
        if(sscanf(params, "s[24]ds[32]", param_name,param_day,param_reason)) return SendClientMessage(playerid, -1, "Используйте: /offjail [ник] [минуты] [причина]"); // Присваиваем значение
    	if(!strcmp(param_name, "Boulevard_Picard", true) || !strcmp(param_name, "Yolon_Jarero", true) || !strcmp(param_name, "Ricky_Lawrence", true)) return 1;// Проверка на то,что-бы Вас не заблокировали
        if(param_day > 360 || param_day < 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Максимальное наказание - 180 минут"); // Проверяем что бы посадили не больше чем на 180 мин и не меньше 1 минуты
        SetPVarString(playerid,"OffJailReason",param_reason); // Присваиваем причину для тюрьмы PVarом
        SetPVarInt(playerid,"OffJailDay",param_day); // Присваиваем кол-во минут тюрьмы PVarом
        format(query,sizeof(query), "SELECT * FROM "TABLE_ACCOUNTS" WHERE `Name` = '%s'", param_name); // ФОрматируем запрос
        mysql_tquery(database, query, "OffJails", "is", playerid, param_name); // Отправляем запрос
        return 1;
}
CMD:offmute(playerid,params[])
{
    	if(PlayerInfo[playerid][pAdmin] < 4) return 1; // Проверка на админ.права
        new query[128],param_name[24],param_reason[32],param_day; // Лично у меня не работали params[0],params[1] и params[2] поэтому я создал только так.
        if(sscanf(params, "s[24]ds[32]", param_name,param_day,param_reason)) return SendClientMessage(playerid, -1, "Используйте: /offmute [ник] [минуты] [причина]"); // Присваиваем значение
    	if(!strcmp(param_name, "Boulevard_Picard", true) || !strcmp(param_name, "Yolon_Jarero", true) || !strcmp(param_name, "Ricky_Lawrence", true)) return 1;// Проверка на то,что-бы Вас не заблокировали
        if(param_day > 360 || param_day < 1) return SendClientMessage(playerid, -1, ""COLOR_RED"Максимальное наказание - 180 минут"); // Проверяем что бы посадили не больше чем на 180 мин и не меньше 1 минуты
        SetPVarString(playerid,"OffMuteReason",param_reason); // Присваиваем причину для тюрьмы PVarом
        SetPVarInt(playerid,"OffMuteDay",param_day); // Присваиваем кол-во минут тюрьмы PVarом
        format(query,sizeof(query), "SELECT * FROM "TABLE_ACCOUNTS" WHERE `Name` = '%s'", param_name); // ФОрматируем запрос
        mysql_tquery(database, query, "OffMute", "is", playerid, param_name); // Отправляем запрос
        return 1;
}
CMD:offban(playerid,params[])
{
    	if(PlayerInfo[playerid][pAdmin] < 5) return 1; // Проверка на админ.права
        new query[128],param_name[24],param_reason[32]; // Лично у меня не работали params[0],params[1] и params[2] поэтому я создал только так.
        if(sscanf(params, "s[24]s[32]", param_name,param_reason)) return SendClientMessage(playerid, -1, "Используйте: /offban [ник] [причина]"); // Присваиваем значение
    	if(!strcmp(param_name, "Boulevard_Picard", true) || !strcmp(param_name, "Yolon_Jarero", true) || !strcmp(param_name, "Ricky_Lawrence", true)) return 1;// Проверка на то,что-бы Вас не заблокировали
        SetPVarString(playerid,"OffBanReason",param_reason); // Присваиваем причину для тюрьмы PVarом
        format(query,sizeof(query), "SELECT * FROM "TABLE_ACCOUNTS" WHERE `Name` = '%s'", param_name); // ФОрматируем запрос
        mysql_tquery(database, query, "OffBan", "is", playerid, param_name); // Отправляем запрос
        return 1;
}
CMD:cc(playerid, params[]) // by Daniel_Cortez \\ pro-pawn.ru
{
    // проверка на админа (при необходимости замените на свою)
    if(PlayerInfo[playerid][pAdmin] == 5)
    {
        // объявить строковую константу и счётчик цикла
        static const str[] = "";
        new i = 100;

        // трюк, предотвращающий краш компилятора (баг sysreq.c)
        // (баг исправлен в патчах от Zeex, в компиляторах версий 0x030A и новее
        // обход бага не нужен, для чего и используется директива #if)
#if __Pawn < 0x030A
        { if(0 == i) SendClientMessageToAll(0, str); }
#endif

        // передать параметры для SendClientMessageToAll
        #emit    push.c        str
        #emit    push.c        0xFFFFFFFF
        #emit    push.c        8

        // вызвать функцию 100 раз
        do{
            #emit    sysreq.c    SendClientMessageToAll
        }while(--i);

        // освободить стековое пространство, зарезервированное под параметры
        #emit    stack        12
    }
    return 1;
}
CMD:weapon(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 3) // меняем на свой аналог
        return 1;

    new
        targetid,
        weapon_id, weapon_name[MAX_WEAPON_NAME], ammo;

    if (sscanf(params, "u", targetid))
        return SendClientMessage(playerid, -1, "Используйте: /weapon [игрок]");

    static const
        fmt_str_dlg_title[] = "Оружие %s",
        fmt_str_dlg_head_body[] = "Оружие\tКоличество\n",
        fmt_str_dlg_body[] = "%s\t%i\n%s";

    new
        str_dlg_title[sizeof(fmt_str_dlg_title)-2+MAX_PLAYER_NAME+1],
        str_dlg_body[
            (sizeof(fmt_str_dlg_head_body)-1)-2*3+2+
            (((sizeof(fmt_str_dlg_body)-1)-2*5+MAX_WEAPON_NAME+6+2)*12)+1
        ];

    format(str_dlg_title, sizeof(str_dlg_title), fmt_str_dlg_title, PlayerInfo[targetid][pName]);

    for (new i; i <= MAX_WEAPON_SLOTS; i++)
    {
        GetPlayerWeaponData(targetid, i, weapon_id, ammo);
        if (weapon_id == WEAPON_FIST) continue;
        else
        {
            GetWeaponName(weapon_id, weapon_name, MAX_WEAPON_NAME);
            format(str_dlg_body, sizeof(str_dlg_body), fmt_str_dlg_body, weapon_name, ammo, str_dlg_body);
        }
    }

    strins(str_dlg_body, fmt_str_dlg_head_body, 0);

    SPD(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, str_dlg_title, str_dlg_body, "Закрыть", "");
    return 1;
}
CMD:gzn(playerid, params[])
{
		for (new i = 0; i < 130; i++)
		{
		if (PlayerInGangZone(playerid, GZInfo[i][gCoords][0],GZInfo[i][gCoords][1],GZInfo[i][gCoords][2],GZInfo[i][gCoords][3])) //
		{
			new string[100];
			format(string,sizeof(string),"ID: %d",GZInfo[i][gid]);
			SendClientMessage(playerid, -1,string);
			return true;
		}
		}
		return true;
}
CMD:mn(playerid, params[]) {
	if(Platform[playerid] == 0) return SPD(playerid, dMenuAdaptive, DIALOG_STYLE_INPUT,"Главное меню","1. Паспорт персонажа\n2. Навигатор\n3. Помощь\n4. Связь с администрацией\n5. Донат\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Выбрать", "Закрыть");
	SPD(playerid, dMenu, DIALOG_STYLE_LIST,""COLOR_BLUE"Главное меню",""COLOR_BLUE"1. Паспорт персонажа\n2. Навигатор\n3. Помощь\n4. Связь с администрацией\n5. Донат\n6. Настройки", "Выбрать", "Закрыть");
	return true;
}
alias:mn("mm");

new static
	AnimationList[] = {
		!"[1] Танец - 1\n\
		[2] Танец - 2\n\
		[3] Танец - 3\n\
		[4] Танец - 4\n\
		[5] Стойка дилера\n\
		[6] Передал что-то\n\
		[7] Съел что-то\n\
		[8] Справить нужду\n\
		[9] Медитация\n\
		[10] Сидеть раненым\n\
		[11] Спать на боку\n\
		[12] Лечь на спину\n\
		[13] Шлепнуть рукой\n\
		[14] Наносить граффити 1\n\
		[15] Наносить граффити 2\n\
		[16] Курение\n\
		[17] Ограбление\n\
		[18] Одеть маску\n\
		[19] Руки в верх\n\
		[20] Позвать кого-то\n\
		[21] Поднять руки\n\
		[22] Болельщик 1\n\
		[23] Болельщик 2\n\
		[24] Болельщик 3\n\
		[25] Показать средний палец\n\
		[26] Выпить что-то\n\
		[27] Махать руками\n\
		[28] Мужское курение\n\
		[29] Прилечь 1\n\
		[30] Прилечь 2\n\
		[31] Прилечь 3\n\
		[32] Прилечь 4\n\
		[33] Присесть на пол\n\
		[34] Читать реп 1\n\
		[35] Читать реп 2\n\
		[36] Читать реп 3\n\
		[37] Читать реп 4\n\
		[38] Набивать мяч\n\
		[39] Кинуть мяч\n\
		[40] Поднять мяч\n\
		[41] Позвать\n\
		[42] Чинить авто\n\
		[43] Прислониться к авто\n\
		[44] Сложить руки вместе\n\
		[45] Держать биту 1\n\
		[46] Держать биту 2\n\
		[47] Гангстерский жест 1\n\
		[48] Гангстерский жест 2\n\
		[49] Гангстерский жест 3\n\
		[50] Гангстерский жест 4\n\
		[51] Гангстерский жест 5\n\
		[52] Гангстерский жест 6\n\
		[53] Гангстерский жест 7\n\
		[54] Гангстерский жест 8\n\
		[55] Плакать\n\
		[56] Присесть 1\n\
		[57] Присесть 2\n\
		[58] Присесть облокотившись\n\
		[59] Женское курение\n\
		[60] Искусственное дыхание\n\
		[61] Облокотится\n\
		[62] Облокотится 2\n\
		[63] Facepalm\n\
		[64] Чесаться"	
	};

CMD:anim(playerid, params[])
{

	if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, !"Невозможно использовать в машине!");
	if(Platform[playerid] == 0) {
	return SendClientMessage(playerid, -1, !"Используйте: /anim [5-56]");
	}
	if(sscanf(params, "d",params[0]))
		{
			SPD(playerid,dAnim,DIALOG_STYLE_LIST, "{FFFFFF}Список анимаций", AnimationList, "Выбрать", "Отмена");
			return true;
		}
	switch(params[0])
	{
		case 0:
		{
			SPD(playerid,dAnim,DIALOG_STYLE_LIST, "{FFFFFF}Список анимаций", AnimationList, "Выбрать", "Отмена");
			return true;
		}
		case 1: SetPlayerSpecialAction (playerid, SPECIAL_ACTION_DANCE1),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 2: SetPlayerSpecialAction (playerid, SPECIAL_ACTION_DANCE2),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 3: SetPlayerSpecialAction (playerid, SPECIAL_ACTION_DANCE3),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 4: SetPlayerSpecialAction (playerid, SPECIAL_ACTION_DANCE4),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 5: GoAnim(playerid,"DEALER","Dealer_idle",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 6: ApplyAnimation(playerid,"DEALER","Dealer_Deal",4.1,0,0,0,0,0,1);
		case 7: ApplyAnimation(playerid,"FOOD","Eat_Burger",4.1,0,0,0,0,0,1),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 8: ApplyAnimation(playerid,"PAULNMAC","Piss_in",4.1,0,0,0,0,0,1);
		case 9: GoAnim(playerid,"PARK","Tai_Chi_Loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 10: GoAnim(playerid,"CRACK","Crckidle1",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 11: GoAnim(playerid,"CRACK","Crckidle2",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 12: GoAnim(playerid,"CRACK","Crckidle4",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 13: ApplyAnimation(playerid,"SWEET","sweet_ass_slap",4.1,0,0,0,0,0,1);
		case 14: GoAnim(playerid,"SPRAYCAN","spraycan_full",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 15: GoAnim(playerid,"GRAFFITI","spraycan_fire",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 16: GoAnim(playerid,"SMOKING","M_smkstnd_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 17: GoAnim(playerid,"SHOP","ROB_Loop_Threat",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 18: ApplyAnimation(playerid,"SHOP","ROB_shifty",4.1,0,0,0,0,0,1);
		case 19: GoAnim(playerid,"SHOP","SHP_Rob_HandsUP",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 20: GoAnim(playerid,"RYDER","Ryd_Beckon_02",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 21: ApplyAnimation(playerid,"RIOT","Riot_Angry",4.1,0,0,0,0,0,0);
		case 22: GoAnim(playerid,"RIOT","Riot_Angry_B",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 23: GoAnim(playerid,"RIOT","Riot_Chant",4.1,1,1,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 24: GoAnim(playerid,"RIOT","Riot_Punches",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 25: ApplyAnimation(playerid,"PED","fucku",4.1,0,0,0,0,0,1);
		case 26: ApplyAnimation(playerid,"BAR","dnK_StndM_loop",4.1,0,0,0,0,0,1);
		case 27: GoAnim(playerid,"BD_FIRE","BD_Panic_03",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 28: GoAnim(playerid,"BD_FIRE","M_smklean_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 29: GoAnim(playerid,"BEACH","bather",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 30: GoAnim(playerid,"BEACH","Lay_Bac_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 31: GoAnim(playerid,"BEACH","Parksit_w_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 32: GoAnim(playerid,"BEACH","Sitnwait_Loop_W",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 33: GoAnim(playerid,"BEACH","Parksit_M_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 34: GoAnim(playerid,"benchpress","gym_bp_celebrate",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 35: GoAnim(playerid,"LOWRIDER","Rap_C_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 36: GoAnim(playerid,"LOWRIDER","Rap_B_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 37: GoAnim(playerid,"LOWRIDER","Rap_A_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 38: GoAnim(playerid,"BSKTBALL","BBALL_idleloop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 39: ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.1,0,0,0,0,0,1),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 40: ApplyAnimation(playerid,"BSKTBALL","BBALL_pickup",4.1,0,0,0,0,0,1);
		case 41: ApplyAnimation(playerid,"CAMERA","camstnd_cmon",4.1,0,0,0,0,0,1);
		case 42: GoAnim(playerid,"CAR","fixn_car_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 43: GoAnim(playerid,"CAR_CHAT","car_talkm_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 44: GoAnim(playerid,"COP_AMBIENT","coplook_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 45: GoAnim(playerid,"CRACK","Bbalbat_Idle_01",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 46: GoAnim(playerid,"CRACK","Bbalbat_Idle_02",4.1,1,0,0,0,0,0);
		case 47: ApplyAnimation(playerid,"GHANDS","gsign1",4.1,0,0,0,0,0,1);
		case 48: ApplyAnimation(playerid,"GHANDS","gsign2",4.1,0,0,0,0,0,1);
		case 49: ApplyAnimation(playerid,"GHANDS","gsign3",4.1,0,0,0,0,0,1);
		case 50: ApplyAnimation(playerid,"GHANDS","gsign4",4.1,0,0,0,0,0,1);
		case 51: ApplyAnimation(playerid,"GHANDS","gsign5",4.1,0,0,0,0,0,1);
		case 52: ApplyAnimation(playerid,"GHANDS","gsign1LH",4.1,0,0,0,0,0,1);
		case 53: ApplyAnimation(playerid,"GHANDS","gsign2LH",4.1,0,0,0,0,0,1);
		case 54: ApplyAnimation(playerid,"GHANDS","gsign4LH",4.1,0,0,0,0,0,1);
		case 55: GoAnim(playerid,"GRAVEYARD","mrnF_loop",4.1,1,0,0,0,0,0);
		case 56: GoAnim(playerid,"MISC","seat_LR",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 57: GoAnim(playerid,"INT_HOUSE","Lou_in",4.1,0,1,1,1,1,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 58: GoAnim(playerid,"INT_OFFICE","OFF_sit_Bored_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 59: GoAnim(playerid,"LOWRIDER","F_smklean_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 60: ApplyAnimation(playerid,"MEDIC","CPR",4.1,0,0,0,0,0,1),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 61: GoAnim(playerid,"GANGS","LeanIn",4.1,0,1,1,1,1,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 62: GoAnim(playerid,"MISC","plyrlean_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
		case 63: ApplyAnimation(playerid,"MISC","plyr_shkhead",4.1,0,0,0,0,0,1);
		case 64: GoAnim(playerid,"MISC","scratchballs_01",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
	}
	SetPVarInt(playerid,"Animation", 1);
	return true;
}
alias:anim("animlist");

CMD:welcome(playerid, params[]) {
	SendClientMessage(playerid, -1, !""COLOR_ORANGE"Добро пожаловать на проект{FFFFFF} Chance RolePlay");
	SendClientMessage(playerid, -1, !""COLOR_ORANGE"Основная валюта сервера {FFFFFF}EXP. "COLOR_ORANGE"Она является показателем опыта и достатка");
	SendClientMessage(playerid, -1, !""COLOR_ORANGE"Заработать можно на ферме, работая таксистом или водителем автобуса");
	SendClientMessage(playerid, -1, !""COLOR_ORANGE"Чтобы вступить во фракцию, нужно минимум {FFFFFF}100 ЕХР");
	SendClientMessage(playerid, -1, !""COLOR_BLUE"Просмотреть статистику персонажа: {FFFFFF} /mm");
	return true;
}
CMD:taxi(playerid, params[]) {
	// Отправка сообщения о заказе таксистам
	SendClientMessage(playerid, -1, !""COLOR_YELLOW"Вас приветствутет Downtown Cab Co., мы приняли ваш заказ");
	SendClientMessage(playerid, -1, !""COLOR_YELLOW"Мы свяжемся с вами, когда найдем свободный автомобиль");
	return 1;
}
CMD:tp(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 3) return true;
	return Dialog_Show(playerid, Dialog:DIALOG_GPS_SHOW_CATEGORY);
}
CMD:sms(playerid, params[])
{
	if(PlayerInfo[playerid][pDevice] == 0) return SendClientMessage(playerid, -1, !""COLOR_RED"Вам нужен пейджер или телефон. Купите его в магазине");
    if(sscanf(params, "ds[128]",params[0],params[1])) return SendClientMessage(playerid, -1, !"Используйте: /sms [id игрока] [текст]");
    if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, !""COLOR_RED"У вас бан чата");
	if(PlayerInfo[playerid][pBalance] < 5) return SendClientMessage(playerid, -1, !""COLOR_RED"Недостаточно средств. Пополните счет");
	if(PlayerInfo[playerid][pDevice] == 1) format(small_string, 100, "%s достал(а) пейджер", PlayerInfo[playerid][pName]);
	if(PlayerInfo[playerid][pDevice] == 2) format(small_string, 100, "%s достал(а) телефон", PlayerInfo[playerid][pName]);
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
	PlayerInfo[playerid][pBalance] -= 5;
	PlayerPlaySound(playerid, 1053,0,0,0);
	if(!IsPlayerConnected(params[0])) return  1;
	format(small_string, sizeof(small_string), "SMS: %s. Получатель: %s[%d]",params[1], PlayerInfo[params[0]][pName], params[0]);
	SendClientMessage(playerid,  0xF5DEB3AA, small_string);
	format(small_string, sizeof(small_string), "SMS: %s. Отправитель: %s[%d]",params[1],PlayerInfo[playerid][pName], playerid);
	SendClientMessage(params[0], 0xF5DEB3AA, small_string);
	PlayerPlaySound(playerid, 1052,0,0,0);
	PlayerPlaySound(params[0], 20804,0,0,0);
	return 1;
}
CMD:re(playerid,params[])
{
    if(PlayerInfo[playerid][pAdmin] < 2) return true;
    
    if(sscanf(params,"d",params[0])) return SendClientMessage(playerid, -1,!"Используйте: /re [ID]");

	if(PlayerLogged{playerid} == false || !IsPlayerConnected(playerid)) return SendClientMessage(playerid, -1, "Игрок не авторизован");

	if(params[0] == INVALID_PLAYER_ID) return SendClientMessage(playerid, -1, "Игрок не найден");
	if(params[0] == playerid) return SendClientMessage(playerid, -1, "Нельзя наблюдать за самим собой");
	
	if(GetPlayerState(params[0]) != 1 && GetPlayerState(params[0]) != 2 && GetPlayerState(params[0]) != 3) return SendClientMessage(playerid, -1, "Игрок не вступил в игру");

	spectating[playerid] = params[0];

	PlayerTextDrawShow(playerid, FULLRECON[playerid]);
	UpdateSpecTD(playerid);

	if(GetPVarInt(playerid, !"spec") != 1)
	{
	
	new
		Float: player_pos_x,
		Float: player_pos_y,
		Float: player_pos_z,
		Float: player_angle;

	GetPlayerPos(playerid, player_pos_x, player_pos_y, player_pos_z);
	GetPlayerFacingAngle(playerid, player_angle);
	SetPVarFloat(playerid, !"pos_x", player_pos_x);
	SetPVarFloat(playerid, !"pos_y", player_pos_y);
	SetPVarFloat(playerid, !"pos_z", player_pos_z);
	SetPVarFloat(playerid, !"pos_angle", player_angle);

	SetPVarInt(playerid, !"pos_int", GetPlayerInterior(playerid));
	SetPVarInt(playerid, !"pos_vw", GetPlayerVirtualWorld(playerid));
	SetPVarInt(playerid, !"spec", 1);

	}

	if(IsPlayerInAnyVehicle(params[0]))
	{

		SetPlayerVirtualWorld(playerid,GetPlayerVirtualWorld(params[0]));
		SetPlayerInterior(playerid, GetPlayerInterior(params[0]));
		TogglePlayerSpectating(playerid, true);
		PlayerSpectateVehicle(playerid, GetPlayerVehicleID(params[0]));
	}
	else
	{
	    SetPlayerVirtualWorld(playerid,GetPlayerVirtualWorld(params[0]));
		SetPlayerInterior(playerid, GetPlayerInterior(params[0]));
		TogglePlayerSpectating(playerid, true);
		PlayerSpectatePlayer(playerid, params[0]);
 	}

	ShowMenuForPlayer(AdminMenu, playerid);
	return 1;
}
CMD:msg(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 4) return true;
    if(!params[0]) return SendClientMessage(playerid, -1, !"Используйте: /msg [текст]");
    if(strlen(params) > 80) {
    	return SendClientMessage(playerid, -1, "Слишком длинное сообщение");
    }
    if(GetPVarInt(playerid,"AntiFloodAdm") > gettime()){ SendClientMessage(playerid, -1, !""COLOR_RED"Пожалуйста не флудите"); return false; }
   	SetPVarInt(playerid,"AntiFloodAdm",gettime() + 3);
    static string[32 + MAX_PLAYER_NAME + 1 + 80];
	format(string, sizeof(string), ""COLOR_ORANGE"Администратор %s: %s", PlayerInfo[playerid][pName], params[0]);
	SendClientMessageToAll(-1, string);
	return 1;
}

CMD:car(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 5) return true;
    if(sscanf(params,"ddd",params[0],params[1],params[2])) return 1;
    for(new i = 0; i < MAX_ADMIN_CAR; i++) {
    	if(AdminCar[i] == INVALID_VEHICLE_ID) {
			new Float:X,Float:Y,Float:Z;
			GetPlayerPos(playerid, X,Y,Z);
		    AdminCar[i] = CreateVehicle(params[0], X+2,Y,Z, 0.0, params[1], params[2], 9000);
			SendClientMessage(playerid, -1, !""COLOR_RED"Не злоупотребляйте данной функцией и убирайте за собой {FFFFFF}(/delcar)");
			SetVehicleParamsForPlayerEx(AdminCar[i],playerid,0,0);
			return 1;
    	}
    }
    SendClientMessage(playerid, -1, "Созданно максимальное кол-во автомобилей");
	return 1;
}


CMD:delcar(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 5) return true;
	if(IsPlayerInAnyVehicle(playerid) == 0) {
		return 0;
	}

	new vehicleid = GetPlayerVehicleID(playerid);

	for(new i = 0; i < MAX_ADMIN_CAR; i++) {
		if(AdminCar[i] == vehicleid) {
			DestroyVehicle(vehicleid);
			return SendClientMessage(playerid, -1, ""COLOR_GREEN"Автомобиль удален.");
		}
	}
	SendClientMessage(playerid, -1, ""COLOR_ORANGE"Данный автомобиль не был создан администратором.");
	return 1;
}


CMD:netstats(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 6) return true;
    new stats[450+1];
    GetNetworkStats(stats, sizeof(stats)); // получаем статистику сети
    SPD(playerid, 0, DIALOG_STYLE_MSGBOX, !"Статистика сети сервера", stats, !"Закрыть", !"");
    new szString[144];
    format(szString, sizeof(szString), "Packets lost: %.2f percent.", NetStats_PacketLossPercent(playerid));
    SendClientMessage(playerid, -1, szString);
	return 1;
}
forward SendFamilyMessage(Fraction:family, color, string[]);
public SendFamilyMessage(Fraction:family, color, string[])
{
	foreach(new i: Player)
	{
		if(GetPlayerFraction(i) == family)
	    {
			SendClientMessage(i, color, string);
		}
	}
}
forward SendAdminMessage(color, string[]);
public SendAdminMessage(color, string[])
{
	foreach(new i: Player)
	{
		if(PlayerInfo[i][pAdmin] > 0)
		{
			SendClientMessage(i, color, string);
		}
	}
}
CMD:a(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] == 0) return true;
    if(!params[0])return SendClientMessage(playerid, -1, !"Используйте: /a [текст]");
	new chat[144];
	format(chat, sizeof(chat), ""COLOR_RED"[A]{FFFFFF} %s: %s", PlayerInfo[playerid][pName], params[0]);
	SendAdminMessage(-1, chat);
	return 1;
}
CMD:spawncars(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 5) return true;
	if(veh_update == 1) {
		return SendClientMessage(playerid, -1, !"Уже запущенно обновление свободного транспорта. Попробуйте позже");
	}
	static const fmt_str_0[] =
		""COLOR_ORANGE"Администратор %s обновит весь незанятый транспорт через 30 секунд";

	goto skip_array_init;
	new string[sizeof(fmt_str_0) + 1
		+ (- 2 + MAX_PLAYER_NAME)
	];
	skip_array_init:

	format(string, sizeof(string),
		fmt_str_0,
			PlayerInfo[playerid][pName]
	);
	SendClientMessageToAll(-1, string);
	veh_update = 1;
	return SetTimer(!"@_RespawnVehicle", 30_000, false);
}
@_RespawnVehicle();
@_RespawnVehicle() {
	for(new c = 0; c <= GetVehiclePoolSize(); c++) {
		if(IsVehicleOccupied(c) == -1) {
			SetVehicleToRespawn(c);
		}
	}
	veh_update = 0;
	return SendClientMessageToAll(-1, ""COLOR_ORANGE"Весь незанятый транспорт был обновлен");
}

CMD:report(playerid, params[])
{
	new chat[144];
	//if(PlayerInfo[playerid][pAdmin] == 0) return true;
	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, !""COLOR_RED"У вас бан чата");
	if(GetPVarInt(playerid,!"AntiFloodReport") > gettime()){ SendClientMessage(playerid, -1, !"Писать в репорт можно раз в минуту"); return false; }
	if(!params[0])return SendClientMessage(playerid, -1, "Используйте: /report [текст]");
	SetPVarInt(playerid,!"AntiFloodReport",gettime() + 60);
	format(chat, sizeof(chat), "{FF4500}%s[%d]:{ffd700} %s", PlayerInfo[playerid][pName],playerid, params[0]);
	SendAdminMessage(-1, chat);
	SendClientMessage(playerid, -1, !""COLOR_ORANGE"Ваше сообщение было отправлено администраторам сервера. Ожидайте ответа");
	format(small_string, sizeof(small_string),"{FF4500}Отправленный текст: {ffd700}%s",params[0]);
	SendClientMessage(playerid, -1, small_string);
	return 1;
}
CMD:pm(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] == 0) return true;
	if(sscanf(params, "d s[128]",params[0],params[1])) return	SendClientMessage(playerid, -1, !"Используйте: /pm [id игрока] [текст]");
    if(GetPVarInt(params[0],!"GotReport") > gettime()) return 1;
    if(!IsPlayerConnected(params[0])) return  1;
    if(params[0] == INVALID_PLAYER_ID) return 1;
	format(small_string, sizeof(small_string), "%s ответил %s: %s",PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName], params[1]);
 	SendAdminMessage(0xFF9945FF, small_string);
	format(small_string, sizeof(small_string), "Администратор %s ответил: %s",PlayerInfo[playerid][pName], params[1]);
 	SendClientMessage(params[0], 0xFF9945FF, small_string);
 	SetPVarInt(params[0],!"GotReport",gettime() + 5);
	return 1;
}
cmd:thx(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] == 0) return true;
    if(sscanf(params,"d", params[0])) return 1;
	format(small_string, sizeof(small_string), "%s пожелал приятной игры %s",PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName]);
 	SendAdminMessage(0xFF9945FF, small_string);
	format(small_string, sizeof(small_string),"Администратор %s ответил: Администрация Chance RP, желает Вам приятной игры и хорошего настроения :)",PlayerInfo[playerid][pName]);
	SendClientMessage(params[0], 0xFF9945FF, small_string);
	return 1;
}
CMD:f(playerid, params[])
{
	new 
		Fraction:fractionid = GetPlayerFraction(playerid);

	if(fractionid > FRACTION_LSPD && fractionid < FRACTION_ARMY) {

	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, !""COLOR_RED"У вас бан чата");
	if(!params[0])return SendClientMessage(playerid, -1, !"Используйте: /f [текст]");
	new chat[144];
	format(chat, sizeof(chat), "[F] %s: %s", PlayerInfo[playerid][pName], params[0]);
	SendFamilyMessage(fractionid, 0x01FCFFC8, chat);

	}
	return 1;
}
CMD:r(playerid, params[])
{
	new 
		Fraction:fractionid = GetPlayerFraction(playerid);

	if(fractionid != FRACTION_LSPD && fractionid != FRACTION_ARMY && fractionid != FRACTION_FBI) {
		return 1;
	}
	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, !""COLOR_RED"У вас бан чата");
	if(!params[0])return SendClientMessage(playerid, -1, !"Используйте: /f [текст]");
	new chat[144];
	format(chat, sizeof(chat), "[R] %s: %s", PlayerInfo[playerid][pName], params[0]);
	SendFamilyMessage(fractionid, 0x8D8DFFFF, chat);
	return 1;
}
CMD:restart(playerid)
{
	if(PlayerInfo[playerid][pAdmin] < 6) return true;
	SendRconCommand("gmx");
	return 1;
}
CMD:tpcor(playerid,params[])
{
    if(PlayerInfo[playerid][pAdmin] < 6) return true;
	new Float:x,Float:z,Float:y;
	if(sscanf(params,"fff",x,y,z)) return SendClientMessage(playerid, -1,!"Используйте: /tpcor [x] [y] [z]");
	SetPlayerPos(playerid,Float:x,Float:y,Float:z);
	return true;
}
CMD:drugplus(playerid,params[])
{
    if(PlayerInfo[playerid][pAdmin] < 6) return true;
	TOTAL_DRUGS += 150;
	return true;
}
CMD:setint(playerid,params[])
{
    if(PlayerInfo[playerid][pAdmin] < 6) return true;
	if(sscanf(params,"d",params[0])) return SendClientMessage(playerid, -1,!"Используйте: /setint [номер]");
	SetPlayerInterior(playerid, params[0]);
	return true;
}
CMD:skin(playerid,params[])
{
	if(PlayerInfo[playerid][pAdmin] < 5) return true;
	new targetid, amount;
    if(sscanf(params, "ui", targetid, amount))  return SendClientMessage(playerid, -1, "Используйте: /skin [id игрока] [значение]");
    else if(amount > 311 || amount  < 1 || amount == 74) return SendClientMessage(playerid, -1, "Скины от 1 до 311 (искл.: 74)");
	format(small_string, sizeof(small_string), ""COLOR_RED"Администратор %s выдал временный скин игроку %s", PlayerInfo[playerid][pName], PlayerInfo[targetid][pName]);
	SendAdminMessage(-1, small_string);
	format(small_string, sizeof(small_string), ""COLOR_ORANGE"Администратор %s выдал вам временный скин", PlayerInfo[playerid][pName]);
	SendClientMessage(targetid, -1, small_string);
	SetPlayerSkin(targetid, amount);
	return true;
}
CMD:prize(playerid,params[])
{
    if(PlayerInfo[playerid][pAdmin] < 4) return true;
    if(prize == 1) return SendClientMessage(playerid, -1,!""COLOR_RED"Сегодня приз уже был выдан");
    if(sscanf(params,"d",params[0])) return SendClientMessage(playerid, -1,!"Используйте: /prize [ID]");
	Player.AddEXP(PlayerInfo[params[0]][pID], 1000, E_WIN_MPPRIZE, params[0]);
	SendClientMessage(params[0], -1,!""COLOR_GREEN"Поздравляем! Вы выйграли 1000 EXP на мероприятии!");
	SendClientMessage(playerid, -1,!""COLOR_GREEN"Приз в размере 1000 EXP выдан");
	prize = 1;
	return 1;
}
CMD:award(playerid,params[])
{
    if(PlayerInfo[playerid][pAdmin] < 3 && strcmp(PlayerInfo[playerid][pName], "Nekit_Reih") != 0) return true;
    if(award == 3) return SendClientMessage(playerid, -1,!""COLOR_RED"На сегодня всё");
    new 
    	target_name[MAX_PLAYER_NAME];
    if(sscanf(params,"s["#MAX_PLAYER_NAME"]", target_name)) return SendClientMessage(playerid, -1,!"Используйте: /award [Ник игрока]");
	
	new targetAccID = Player.GetAccIDFromName(target_name);
	if(targetAccID == 0) {
		return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Игрок с указанным никнеймом не найден.");
	}
	new targetid = GetPlayerIDFromAccID(targetAccID);

	Player.AddEXP(targetAccID, 1000, E_WIN_AWARD, targetid);
	if(targetid != INVALID_PLAYER_ID) {
		SendClientMessage(targetid, -1,!""COLOR_GREEN"Поздравляем! Вы получили 1000 EXP за активность в свободной группе!");
	}
	SendClientMessage(playerid, -1,!""COLOR_GREEN"Награда в размере 1000 EXP выдана");
	award++;
	return 1;
}

new bool: isUsedCarprize;
CMD:carprize(playerid,params[])
{
    if(PlayerInfo[playerid][pAdmin] < 3 && strcmp(PlayerInfo[playerid][pName], "Yolon_Jarero") != 0) return true;
    if(isUsedCarprize == true) return SendClientMessage(playerid, -1,!""COLOR_RED"На сегодня всё");
    if(sscanf(params,"d",params[0])) return SendClientMessage(playerid, -1,!"Используйте: /carprize [ID]");
	Player.AddEXP(PlayerInfo[params[0]][pID], 500, E_WIN_CARPRIZE, params[0]);
	SendClientMessage(params[0], -1,!""COLOR_GREEN"Поздравляем! Вы получили 500 EXP за победу в мероприятии!");
	SendClientMessage(playerid, -1,!""COLOR_GREEN"Награда в размере 500 EXP выдана");
	isUsedCarprize = true;
	return 1;
}

CMD:gethere(playerid,params[])
{
    if(PlayerInfo[playerid][pAdmin] < 4) {
    	return true;
    }
    new 
    	targetid;

	if(sscanf(params, "u", targetid)) {
		return SendClientMessage(playerid, -1, !"Используйте: /gethere [ID]");
	}
	new 
		Float: X,
		Float: Y,
		Float: Z;
	GetPlayerPos(playerid, X, Y, Z);

	RemovePlayerFromVehicle(targetid);
	SetPlayerPos(targetid, X, Y + 2.00, Z);
	SetPlayerInterior(targetid, GetPlayerInterior(playerid));
	SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));

	return SendClientMessage(targetid, -1, !"Вы были телепортированы администратором");
}
alias:g("goto");
CMD:g(playerid,params[])
{
    if(PlayerInfo[playerid][pAdmin] < 3) return true;
	if(sscanf(params,"d",params[0])) return SendClientMessage(playerid, -1,!"Используйте: /g [ID]");
	new Float:X,Float:Y,Float:Z;
	GetPlayerPos(params[0], X,Y,Z);
	SetPlayerPos(playerid,X,Y+2,Z);
	SetPlayerInterior(playerid, GetPlayerInterior(params[0]));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(params[0]));	
	return SetCameraBehindPlayer(playerid);
}

CMD:ahelp(playerid, params[]) {
	new 
		admin_level = PlayerInfo[playerid][pAdmin];
	
	if(admin_level == 0) {
		return 0;
	}

  	if(admin_level >= 1) {
	  	SendClientMessage(playerid, C_YELLOW, !"Доступные команды:");
	  	SendClientMessage(playerid, C_ORANGE, !"/a /pm /thx /admins");
  	}
  	if(admin_level >= 2) {
  		SendClientMessage(playerid, C_ORANGE, !"/re /reoff /mute /unmute /respawn");
  	}
  	if(admin_level >= 3) {
  		SendClientMessage(playerid, C_ORANGE, !"/g /kick /jail /unjail /tp /weapon /lip");
  	}
  	if(admin_level >= 4) {
  		SendClientMessage(playerid, C_ORANGE, !"/msg /prize /gethere /ban /offjail /offmute");
  	}
    if(admin_level >= 5) {
    	SendClientMessage(playerid, C_ORANGE, !"/spawncars /sban /offban /skick /car /delcar /cc /skin");
    }
	return 1;
}
CMD:id(playerid,params[])
{
	if(sscanf(params,"u",params[0])) return SendClientMessage(playerid, -1, !"Используйте: /id [Ник/Часть ника]");
	new newiy[24+5+1];
	if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, -1, !"Игрока нет в сети!");
	format(newiy, sizeof(newiy), "%s[%d]", PlayerInfo[params[0]][pName], params[0]);
	SendClientMessage(playerid, -1, newiy);
	return true;
}
CMD:reoff(playerid,params[])
{
    if(PlayerInfo[playerid][pAdmin] < 2) return true;
    StopSpectate(playerid);
    return 1;
}
CMD:respawn(playerid,params[])
{
    if(PlayerInfo[playerid][pAdmin] < 2) return true;
	SpawnPlayer(playerid);
    return 1;
}
CMD:kick(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 3) return true;
    new giveplayerid, result[128];
	if(sscanf(params, "ds[64]", giveplayerid, result)) return SendClientMessage(playerid, -1, !"Используйте: /kick [id игрока] [причина]");
	if(giveplayerid == INVALID_PLAYER_ID) return 1;
	if(IsPlayerNPC(giveplayerid)) return 1;
	if(PlayerInfo[giveplayerid][pAdmin] > 5) return true;
	format(small_string, sizeof(small_string), ""COLOR_RED"Администратор %s отключил %s от сервера. Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[giveplayerid][pName], result);
	SendClientMessageToAll(-1, small_string);
	return Kick(giveplayerid);
}
CMD:skick(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 5) return true;
    new giveplayerid, result[128];
	if(sscanf(params, "ds[64]", giveplayerid, result)) return SendClientMessage(playerid, -1, !"Используйте: /skick [id игрока] [причина]");
	if(giveplayerid == INVALID_PLAYER_ID) return 1;
	if(IsPlayerNPC(giveplayerid)) return 1;
	if(PlayerInfo[giveplayerid][pAdmin] > 5) return true;
	format(small_string, sizeof(small_string), ""COLOR_RED"Администратор %s отключил %s от сервера. Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[giveplayerid][pName], result);
	SendAdminMessage(-1, small_string);
	SendClientMessage(giveplayerid, -1, small_string);
	return Kick(giveplayerid);
}
CMD:ban(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 4) return true;
	new giveplayerid, result[128];
	if(sscanf(params, "ds[64]", giveplayerid, result)) return SendClientMessage(playerid, -1, !"Используйте: /ban [id игрока] [причина]");
	if(giveplayerid == INVALID_PLAYER_ID) return 1;
	if(IsPlayerNPC(giveplayerid)) return 1;
	if(PlayerInfo[giveplayerid][pAdmin] > 5) return true;
	format(small_string, sizeof(small_string), ""COLOR_RED"Администратор %s заблокировал %s. Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[giveplayerid][pName], result);
	SendClientMessageToAll(-1, small_string);
 	PlayerInfo[giveplayerid][pBanned] = 1;
	SetPlayerInt(giveplayerid, !"Banned", PlayerInfo[giveplayerid][pBanned]);
 	Ban(giveplayerid);
	return true;
}
CMD:sethp(playerid, params[])
{

    if(5 > PlayerInfo[playerid][pAdmin])
        return 1;

    new
        targetid,
        amount;

    if(sscanf(params, "ui", targetid, amount)) return SendClientMessage(playerid, -1, "Используйте: /sethp [id игрока] [значение]");
    if(IsPlayerNPC(targetid)) return 1;
    if(!(0 <= amount <= 100)) return SendClientMessage(playerid, -1, "Количество здоровья от 0 до 100");
    
    SetPlayerHealth(targetid, amount);

    static const
        fmt_str0[] = ""COLOR_RED"Администратор %s установил игроку %s здоровье: %d";
    
    new
        str[sizeof(fmt_str0) - 2 + MAX_PLAYER_NAME - 2 + 4 - 2 + MAX_PLAYER_NAME - 2 + 4 - 2 + 11];
        

    format(str, sizeof(str), fmt_str0, PlayerInfo[playerid][pName], PlayerInfo[targetid][pName], amount);
    SendAdminMessage(-1, str);
    return 1;
}  
CMD:sban(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 5) return true;
	new giveplayerid, result[128];
	if(sscanf(params, "ds[64]", giveplayerid, result)) return SendClientMessage(playerid, -1, !"Используйте: /sban [id игрока] [причина]");
	if(giveplayerid == INVALID_PLAYER_ID) return 1;
	if(IsPlayerNPC(giveplayerid)) return 1;
	if(PlayerInfo[giveplayerid][pAdmin] > 5) return true;
	format(small_string, sizeof(small_string), ""COLOR_RED"Администратор %s заблокировал %s. Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[giveplayerid][pName], result);
	SendAdminMessage(-1, small_string);
	SendClientMessage(giveplayerid, -1, small_string);
 	PlayerInfo[giveplayerid][pBanned] = 1;
	SetPlayerInt(giveplayerid, !"Banned", PlayerInfo[giveplayerid][pBanned]);
 	Ban(giveplayerid);
	return true;
}
CMD:jail(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 3) return true;
	if(sscanf(params,"dis[128]", params[0],params[1],params[2])) return SendClientMessage(playerid, -1, !"Используйте: /jail [id игрока] [минуты] [причина]");
	if(params[0] == INVALID_PLAYER_ID) return 1;
	if(params[1] > 180) return SendClientMessage(playerid, -1, !""COLOR_ORANGE"Максимальное время тюрьмы - 180 минут");
	if(IsPlayerNPC(params[0])) return 1;
	if(PlayerInfo[params[0]][pAdmin] > 0) return true;
	format(small_string, sizeof(small_string), ""COLOR_RED"Администратор %s посадил в тюрьму %s на %d минут. Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName], params[1], params[2]);
	SendClientMessageToAll(-1, small_string);
	RemovePlayerFromVehicle(params[0]);
	ResetPlayerWeapons(params[0]);
 	PlayerInfo[params[0]][pJailed] = 2;
    PlayerInfo[params[0]][pJailTime] = params[1] * 60;
	SetPlayerInt(params[0], "Jailed", PlayerInfo[params[0]][pJailed]);
	SetPlayerInt(params[0], "JailTime", PlayerInfo[params[0]][pJailTime]);
	return true;
}
CMD:unjail(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 3) return true;
	if(sscanf(params,"d", params[0])) return SendClientMessage(playerid, -1, !"Используйте: /unjail [id игрока]");
	if(PlayerInfo[params[0]][pJailed] == 0) return 1;
	if(params[0] == INVALID_PLAYER_ID) return 1;
	format(small_string, sizeof(small_string), ""COLOR_RED"Администратор %s выпустил из тюрьмы %s", PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName]);
	if(PlayerInfo[params[0]][pAdmin] > 0) SendClientMessageToAll(-1, small_string);
 	PlayerInfo[params[0]][pJailed] = 0;
    PlayerInfo[params[0]][pJailTime] = 0;
	SetPlayerInt(params[0], "Jailed", PlayerInfo[params[0]][pJailed]);
	SetPlayerInt(params[0], "JailTime", PlayerInfo[params[0]][pJailTime]);
	SpawnPlayer(params[0]);
	return true;
}
CMD:mute(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 2) return true;
	if(sscanf(params,"dis[128]", params[0],params[1],params[2])) return SendClientMessage(playerid, -1, "Используйте: /mute [id игрока] [минуты] [причина]");
	if(params[0] == INVALID_PLAYER_ID) return 1;
	if(params[1] > 30) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Максимальный бан чата - 30 минут");
	if(IsPlayerNPC(params[0])) return 1;
	if(PlayerInfo[params[0]][pAdmin] > 0) return true;
	format(small_string, sizeof(small_string), ""COLOR_RED"Администратор %s заблокировал чат игроку %s на %d минут. Причина: %s", PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName], params[1], params[2]);
	SendClientMessageToAll(-1, small_string);
 	PlayerInfo[params[0]][pMuted] = 1;
    PlayerInfo[params[0]][pMuteTime] = params[1] * 60;
	SetPlayerInt(params[0], "Muted", PlayerInfo[params[0]][pMuted]);
	SetPlayerInt(params[0], "MuteTime", PlayerInfo[params[0]][pMuteTime]);
	return true;
}
CMD:unmute(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] < 2) return true;
	if(sscanf(params,"d", params[0])) return SendClientMessage(playerid, -1, "Используйте: /unmute [id игрока]");
	if(PlayerInfo[params[0]][pMuted] < 1) return 1;
	if(params[0] == INVALID_PLAYER_ID) return 1;
	if(IsPlayerNPC(params[0])) return 1;
	format(small_string, sizeof(small_string), ""COLOR_RED"Администратор %s разблокировал чат игроку %s", PlayerInfo[playerid][pName], PlayerInfo[params[0]][pName]);
	SendClientMessageToAll(-1, small_string);
 	PlayerInfo[params[0]][pMuted] = 0;
    PlayerInfo[params[0]][pMuteTime] = 0;
	SetPlayerInt(params[0], "Muted", PlayerInfo[params[0]][pMuted]);
	SetPlayerInt(params[0], "MuteTime", PlayerInfo[params[0]][pMuteTime]);
	return true;
}
CMD:me(playerid, params[])
{
	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У вас бан чата");
	if(sscanf(params, "s[128]",params[0])) return	SendClientMessage(playerid, -1, "Используйте: /me [действие]");
	format(small_string, sizeof(small_string), "%s %s", PlayerInfo[playerid][pName], params[0]);
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
	SetPlayerChatBubble(playerid,params[0],C_PURPLE,30.0,10000);
	return true;
}

CMD:s(playerid, params[])
{
	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У вас бан чата");
	if(sscanf(params, "s[128]",params[0])) return SendClientMessage(playerid, -1, "Используйте: /s [текст]");
	format(small_string, sizeof(small_string), "- %s[%d] крикнул: %s!!", PlayerInfo[playerid][pName], playerid, params[0]);
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE * 2, -1, small_string);
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) { 
		ApplyAnimation(playerid,"ON_LOOKERS","shout_in",9000.999,0,0,0,0,0,1);
	}
	SetPlayerChatBubble(playerid,params[0],0xF5DEB3AA,60.0,10000);
	return true;
}
CMD:whisper(playerid,params[])
{
	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У вас бан чата");
	if(sscanf(params, "s[128]",params[0])) return	SendClientMessage(playerid, -1, "Используйте: /w [текст]");
	format(small_string, 144, "%s шепчет: %s", PlayerInfo[playerid][pName], params[0]);
	ProxDetector(playerid, 4.00, -1, small_string);
	SetPlayerChatBubble(playerid,params[0],0xF5DEB3AA,4.0,10000);
	return 1;
}
CMD:n(playerid, params[])
{
	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У вас бан чата");
	if(isnull(params)) return SendClientMessage(playerid, -1, "Используйте: /n [текст]");
	format(small_string, sizeof(small_string), "%s: (( %s ))", PlayerInfo[playerid][pName], params);
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE, -1, small_string);
	return true;
}
alias:whisper("w");
CMD:try(playerid, params[])
{
	if (isnull(params)) return SendClientMessage(playerid, -1, "Используйте: /try [действие]");
	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У вас бан чата!");
	new dice = 1 + random(2);
	if (dice == 1) format(small_string, sizeof(small_string), " %s %s {B22222}| Неудачно", PlayerInfo[playerid][pName], params);
	else if (dice == 2) format(small_string, sizeof(small_string), " %s %s {09B000}| Удачно", PlayerInfo[playerid][pName], params);
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
	return true;
}
CMD:bug(playerid, params[])
{
	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, !""COLOR_RED"У вас бан чата");
	if(GetPVarInt(playerid,"ReportedBug") > gettime()){ return SendClientMessage(playerid, -1, !""COLOR_RED"Вы уже недавно сообщали о баге"); }
	SetPVarInt(playerid,"ReportedBug",gettime() + 90);
    if (sscanf(params, "s[129]", params))
        return SendClientMessage(playerid, -1, !"Использование: /bug [описание бага]");
    static const bug_str[] = " сообщил о баге: ";
    new string[sizeof(bug_str)+MAX_PLAYER_NAME+128];
    GetPlayerName(playerid, string, sizeof(string));
    strcat(string, bug_str), strcat(string, params);
    new File:f = fopen(!BUG_REPORT_FILE_NAME, io_append);
    if (f == File:0)
        return SendClientMessage(playerid, -1,
            !""COLOR_RED"Ошибка. Попробуйте позже");
    for (new i = -1; string[++i] != '\0';)
        fputchar(f, string[i], false);
    fputchar(f, '\n', false);
    fclose(f);
    SendClientMessage(playerid, -1, !""COLOR_GREEN"Вы успешно сообщили о баге. Спасибо!");
    new chat[144];
    format(chat, sizeof(chat), "{FF4500}%s[%d] оставил баг-репорт:{ffd700} %s", PlayerInfo[playerid][pName],playerid, params[0]);
	SendAdminMessage(-1, chat);
	return 1;

}
 
CMD:sug(playerid, params[])
{
	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, !""COLOR_RED"У вас бан чата");
	if(GetPVarInt(playerid,"ReportedIdea") > gettime()){ return SendClientMessage(playerid, -1, !""COLOR_RED"Вы уже недавно оставляли предложение по улучшению"); }
	SetPVarInt(playerid,"ReportedIdea",gettime() + 120);
    if (sscanf(params, "s[129]", params))
        return SendClientMessage(playerid, -1, !"Использование: /sug [предложение по улучшению]");
    static const sug_str[] = " предложил: ";
    new string[sizeof(sug_str)+MAX_PLAYER_NAME+128];
    GetPlayerName(playerid, string, sizeof(string));
    strcat(string, sug_str), strcat(string, params);
    new File:f = fopen(!SUGGESTION_FILE_NAME, io_append);
    if (f == File:0)
        return SendClientMessage(playerid, -1,
            !""COLOR_RED"Ошибка. Попробуйте позже");
    for (new i = -1; string[++i] != '\0';)
        fputchar(f, string[i], false);
    fputchar(f, '\n', false);
    fclose(f);
    SendClientMessage(playerid, -1, !""COLOR_GREEN"Вы оставили предложение по улучшению. Спасибо!");
    new chat[144];
    format(chat, sizeof(chat), "{FF4500}%s[%d] оставил предложение:{ffd700} %s", PlayerInfo[playerid][pName],playerid, params[0]);
	SendAdminMessage(-1, chat);
	return 1;
}
CMD:do(playerid, params[])
{
	if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У вас бан чата");
	if(sscanf(params, "s[128]",params[0])) return	SendClientMessage(playerid, -1, "Используйте: /do [текст]");
	DoAction(playerid,params[0]);
	return true;
}
CMD:eject(playerid, params[])
{
    if(!IsPlayerInAnyVehicle(playerid)) return true;
    new State = GetPlayerState(playerid);
    if(State!=PLAYER_STATE_DRIVER) return 1;
    if(sscanf(params, "u", params[0])) return SendClientMessage(playerid, -1, "Используйте: /eject [id]");
    new test = GetPlayerVehicleID(playerid);
    if(!IsPlayerConnected(params[0])) return true;
    if(params[0] == playerid) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете выкинуть из машины сами себя!");
    if(!IsPlayerInVehicle(params[0],test)) return true;
    format(small_string, sizeof(small_string), ""COLOR_BLUE"Вы выкинули %s из машины ", PlayerInfo[params[0]][pName]);
    SendClientMessage(playerid, -1, small_string);
    format(small_string, sizeof(small_string), ""COLOR_RED"%s выкинул вас из машины", PlayerInfo[playerid][pName]);
    SendClientMessage(params[0], -1, small_string);
    RemovePlayerFromVehicle(params[0]);
    return true;
}
CMD:time(playerid, params[])
{
	new mtext[24];
	getdate(_, month, day);
	if(month == 1) { 
		mtext = "January"; 
	}
	else if(month == 2) { 
		mtext = "February"; 
	}
	else if(month == 3) { 
		mtext = "March"; 
	}
	else if(month == 4) { 
		mtext = "April"; 
	}
	else if(month == 5) { 
		mtext = "May"; 
	}
	else if(month == 6) { 
		mtext = "June"; 
	}
	else if(month == 7) { 
		mtext = "July"; 
	}
	else if(month == 8) { 
		mtext = "August"; 
	}
	else if(month == 9) { 
		mtext = "September"; 
	}
	else if(month == 10) { 
		mtext = "October"; 
	}
	else if(month == 11) { 
		mtext = "November"; 
	}
	else if(month == 12) { 
		mtext = "December"; 
	}
	gettime(hour, minute);

	format(small_string, sizeof(small_string), "~y~%d %s~n~~g~~w~%d:%02d~g~~n~chance rp", day, mtext, hour, minute);
	GameTextForPlayer(playerid, small_string, 5000, 1);
	format(small_string, sizeof(small_string), "%s взглянул(а) на часы", PlayerInfo[playerid][pName]);
	ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
}
CMD:admins(playerid, params[])
{
    if(PlayerInfo[playerid][pAdmin] >= 1)
    {
    	SendClientMessage(playerid, -1, ""COLOR_BLUE"Администрация в сети:");
	   	foreach(new i: Admin)
		{
			if(PlayerInfo[i][pAdmin] >= 1)
	       	{
	       		new drank[20];
				if(PlayerInfo[i][pAdmin] == 1) { drank = "1"; }
				else if(PlayerInfo[i][pAdmin] == 2) { drank = "2"; }
				else if(PlayerInfo[i][pAdmin] == 3) { drank = "3"; }
				else if(PlayerInfo[i][pAdmin] == 4) { drank = "4"; }
				else if(PlayerInfo[i][pAdmin] == 4 && PlayerInfo[i][pFarmSkill] > 5000) { drank = "Хокаге"; }
				else if(PlayerInfo[i][pAdmin] == 5) { drank = "5"; }
				else if(PlayerInfo[i][pAdmin] == 6) { drank = "Основатель"; }
				else if(PlayerInfo[i][pAdmin] == 9999) { drank = "6"; }
				format(small_string, 256, "%s[%d] | Уровень прав: %s",PlayerInfo[i][pName],i,drank);
				SendClientMessage(playerid, -1, small_string);
		    }
	    }
	}
	return 1;
}
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(IsPlayerNPC(playerid)) return 1;
	if (ispassenger) return 1;


	foreach(new i: Player)
 	{
    	if(IsPlayerInVehicle(i,vehicleid) && GetPlayerState(i) == PLAYER_STATE_DRIVER) {
       	 	new Float:X,Float:Y,Float:Z;
        	//SendClientMessage(playerid, -1, "Сервер понял");
        	GetPlayerPos(playerid,X,Y,Z);
       	 	//SendClientMessage(playerid, -1, "Сервер получил данные");
        	SetPlayerPos(playerid,X,Y,Z);
        	//SendClientMessage(playerid, -1, "Сервер выгнал");
        	ClearPlayerAnimation(playerid);
        	ClearPlayerAnimation(i);
        	PutPlayerInVehicle(i, vehicleid, 0);
        	//SendClientMessage(playerid, -1, "Сервер вернул");
     	}
  	}
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if(IsPlayerNPC(playerid)) return 1;
	if(GetPVarType(playerid, !"incar") != PLAYER_VARTYPE_INT)
    return 1;
	new vehicle_owner;
	for(new i = 0; i < sizeof(VehicleInfo); i++) {
		if(VehicleInfo[i][VI_VehicleID] == vehicleid) {
			vehicle_owner = VehicleInfo[i][VI_Owner];

			if(vehicle_owner == VO_FRACTION_LSPD) {
				DeletePVar(playerid, !"incar");
				PutPlayerBackToPoliceCar(playerid, vehicleid);
			}
		}
	}
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(IsPlayerNPC(playerid)) return 1;
	CallLocalFunction("Salon_OnPlayerStateChange", "iii", playerid, newstate, oldstate);
	foreach(new f: Player)
	{
		if(spectating[f] == playerid)//Проверяем действительно ли следит следящий игрок именно за этим игроком
		{
		    if(!IsPlayerConnected(spectating[f])) callcmd::reoff(playerid,"\0");
			//Колбэк указанный ниже, поможет нам быстро обновить режим слежки
			UpdateSpectatingStatus(f, playerid);
		}
	}
    new vehicleid = GetPlayerVehicleID(playerid);
    new modelid = GetVehicleModel(vehicleid);
    if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER)
    {
    	new return_value = CallLocalFunction("Vehicle_OnPlayerExitVehicle", "ii", playerid, gonecar[playerid]);
    	if(return_value == 0) {
    		gonecar[playerid] = INVALID_VEHICLE_ID;
    	}
    	if(Platform[playerid] == 1) {
			hide_speedo(playerid);
	    }
    }
    if(newstate == PLAYER_STATE_DRIVER) {
    	DisablePlayerRaceCheckpoint(playerid);
    	if(Platform[playerid] == 1) {
			show_speedo(playerid, modelid);
			format(big_string, sizeof(big_string),"%s",GetVehicleText(modelid));
		    PlayerTextDrawSetString(playerid,speedo_TD_3[playerid], big_string);
		}
		Timer_Speed[playerid] = KillTimer(Timer_Speed[playerid]); 
		Timer_Speed[playerid] = SetTimerEx("UpdateSpeed",500,false,"d",playerid);
		if(IsAirVehicle(vehicleid) == 1) {
				if(PlayerInfo[playerid][pLicenseAir] == 0 && GetPVarInt(playerid,"GetLicAir") != 1)
					{
					    SendClientMessage(playerid, -1, ""COLOR_RED"У Вас нет лицензии пилота");
					    SendClientMessage(playerid, -1, ""COLOR_RED"Получить лицензию можно в Автошколе Сан-Фиерро");
					    RemovePlayerFromVehicle(playerid);
	        			return 1;
					}
		}
		
		if(gonecar[playerid] != INVALID_VEHICLE_ID && gonecar[playerid] != vehicleid) {
	  		RemovePlayerFromVehicle(playerid);
	    	
		} else {
			ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
			gonecar[playerid] = INVALID_VEHICLE_ID;
		}

		new 
			return_value = CallLocalFunction("Vehicle_OnPlayerEnterVehicle", "ii", playerid, vehicleid);

		if(return_value == 0) {
			RemovePlayerFromVehicle(playerid);
			return 1;
		} else if(return_value == 1) {
			gonecar[playerid] = vehicleid;
		} 

		if(return_value != 5) {
			if(PlayerInfo[playerid][pLicense] == 0) {
				if(modelid != 481 && modelid != 510 && modelid != 509 && modelid != 462) {
					SendClientMessage(playerid, -1, ""COLOR_RED"У Вас нет водительских прав");
					SendClientMessage(playerid, -1, ""COLOR_RED"Получить лицензию можно в Автошколе Сан-Фиерро");
					RemovePlayerFromVehicle(playerid);
					return 1;
				}
			}
		}

		if(modelid != 481 && modelid != 510 && modelid != 509) {
			format(small_string, 100, "%s завел(а) двигатель", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		}
		if(vehicleid >= HARVEST_CAR[0] && vehicleid <= HARVEST_CAR[2])
		{
		    if(gone[playerid] != -1) return RemovePlayerFromVehicle(playerid);
		    if(GetPVarInt(playerid, "tempjob") != 1) return SetVehicleToRespawn(vehicleid);
		    if(PlayerInfo[playerid][pFarmSkill] < 200) return SetVehicleToRespawn(vehicleid),SendClientMessage(playerid, -1, ""COLOR_RED"Доступно с 200 навыка фермера");
			if(vehicleid == HARVEST_CAR[0] && Harvest[0] < 200) return SetVehicleToRespawn(vehicleid),SendClientMessage(playerid, -1, ""COLOR_RED"Фургон не загружен до конца");
			if(vehicleid == HARVEST_CAR[1] && Harvest[1] < 200) return SetVehicleToRespawn(vehicleid),SendClientMessage(playerid, -1, ""COLOR_RED"Фургон не загружен до конца");
			if(vehicleid == HARVEST_CAR[2] && Harvest[2] < 200) return SetVehicleToRespawn(vehicleid),SendClientMessage(playerid, -1, ""COLOR_RED"Фургон не загружен до конца");
			UnloadFarm[playerid] = 1;
	 		Route2[playerid] = -1;
		 	RouteTrash[playerid] = -1;
		 	RouteFarm[playerid] = -1;
		 	Route3[playerid] = -1;
		 	ArmyMission[playerid] = -1;
		 	Route[playerid] = -1;
		 	RouteLic[playerid] = -1;
		 	RouteLicAir[playerid] = -1;
		 	RouteAir[playerid] = -1;
		 	RouteAir2[playerid] = -1;
		 	SetPlayerRaceCheckpoint(playerid, 1,2178.9387,-1660.8270,14.9413,2178.9387,-1660.8270,14.9413,4); // combine
		 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы отправились на продажу кустов. Доставьте груз");
		 	return 1;
		}

		if(TCar[playerid] != 0)
		{
			if(GetVehicleModel(vehicleid) == TCar[playerid])
			{
				if(ThefStatus[playerid] == 2) return SendClientMessage(playerid, -1, ""COLOR_BLUE"Доставьте автомобиль в указанное на карте место");
				ThefStatus[playerid] = 2;
				SendClientMessage(playerid, -1, ""COLOR_BLUE"Доставьте автомобиль в указанное на карте место");
				new rand = random(sizeof(acarsd));
				TogglePlayerDynamicCP(playerid, stealcar_checkpoint[rand], true);
				GangZoneDestroy(TheftZone[playerid]);
				PlayerInfo[playerid][pWanted] += 1200;
				SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
				SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
				new model = GetVehicleModel(TCar[playerid]);
				format(small_string, sizeof(small_string), "~r~%s theft %s",PlayerInfo[playerid][pName], GetVehicleText(model));
				SendPoliceGameText(small_string);
				return 1;
			}
		}
		for(new i = 0; i < MAX_PLAYERS_CAR; i++) {
			if(Player.CarVehicleID[playerid][i] != INVALID_VEHICLE_ID) {
				if(vehicleid == Player.CarVehicleID[playerid][i]) {
					if(modelid != 481 && modelid != 510 && modelid != 509) {
						format(small_string, sizeof(small_string), 
							""COLOR_BLUE"Пробег вашего транспорта: {FFFFFF}%dкм.", 
								Player.CarMileage[playerid][i] / 1000);						
						SendClientMessage(playerid, -1, small_string);
					}
					return 1;
				}
			}
		}
	}
	if(newstate == PLAYER_STATE_PASSENGER && IsTaxiCar(vehicleid)) {
        SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы сели в такси. Затраты за ваш проезд будут оплачены государством");
    
        new
            vehicle_driver = WhoIsDriver(vehicleid);

        if(vehicle_driver != INVALID_PLAYER_ID) {
            if(GetPVarInt(vehicle_driver,"TaxiPlus") > gettime()){ return false; }

            SendClientMessage(vehicle_driver, -1, ""COLOR_ORANGE"К вашей зарплате прибавлено: {FFFFFF}+50 EXP");
            PlayerInfo[vehicle_driver][pTaxiTotal] += 50;
            SetPlayerInt(vehicle_driver, "TaxiTotal", PlayerInfo[vehicle_driver][pTaxiTotal]);
            SetPVarInt(vehicle_driver, "TaxiPlus",gettime() + 300);
        }
    }
    return 0;
}

stock SpeedVehicle(carid)
{
    new Float:X, Float:Y, Float:Z;
    GetVehicleVelocity(carid,X,Y,Z);
    return floatround( floatsqroot( X * X + Y * Y ) * 100.0 );
}  
stock WhoIsDriver(vehicleid)
{
    foreach(new i: Player)
    {
       	if(GetPlayerVehicleID(i) == vehicleid && GetPlayerState(i) == PLAYER_STATE_DRIVER) return i;
	}
	return INVALID_PLAYER_ID;
}
public OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}
forward CFarm(playerid);
public CFarm(playerid)
{
    SetPVarInt(playerid,"Pizdui", 2);
    ClearAnimations(playerid);
    SendClientMessage(playerid, -1, ""COLOR_ORANGE"Доставьте урожай в автомобиль");
}

stock ClearPlayerAnimation(playerid) {
	ClearAnimations(playerid, 1);
	ApplyAnimation(playerid, !"ped", !"facsurp", 4.0, 1, 0, 0, 1, 1, 1);
	ApplyAnimation(playerid, !"ped", !"facsurp", 4.0, 1, 0, 0, 1, 1, 1);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	return true;
}


PlayerInGangZone(playerid,Float:min_x,Float:min_y,Float:max_x,Float:max_y)
{
	new Float:xxp,Float:yyp,Float:zzp;
	GetPlayerPos(playerid, xxp, yyp, zzp);
	if((xxp <= max_x && xxp >= min_x) && (yyp <= max_y && yyp >= min_y)) return true;
	return false;
}
stock IsANope(carid)
{
	switch(GetVehicleModel(carid))
	{
		case 400,404,436,439,458,466,475,478,479,492,516,517,518,526,527,542,543,546,547,549,567: return true;
		default: return false;
	}
	return false;
}
stock IsAB(carid)
{
	switch(GetVehicleModel(carid))
	{
		case 419,421,445,489,491,533,534,554,555,561,579,580,589,603,418,461,581,586,401,405,412,422,426,467,474,496,507,529,536,540,550,551,566,575,576,585,600: return true;
		default: return false;
	}
	return false;
}
stock IsAA(carid)
{
	switch(GetVehicleModel(carid))
	{
		case 541,522,434,477,480,535,545,558,559,560,562,565,587,602,521,463,468,402,411,415,429,451,506: return true;
		default: return false;
	}
	return false;
}
stock Vehicleforeach(vehicleid)
{
	foreach(new i: Player)
	{
		if(caridhouse[i] == vehicleid) return i;
	}
	return -1;
}
public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) return 0;
    new gettimer = gettime();
    if(pPickup_Status{playerid} && pPickup_AntiFlood[playerid] < gettimer) {
        if(!IsPlayerInRangeOfPoint(playerid,1.0,pPickup_Pos[playerid][0],pPickup_Pos[playerid][1],pPickup_Pos[playerid][2])) pPickup_Status{playerid} = false;
        GetPlayerPos(playerid,pPickup_Pos[playerid][0],pPickup_Pos[playerid][1],pPickup_Pos[playerid][2]);
    }
    if(pPickup_Status{playerid} || pPickup_AntiFlood[playerid] > gettimer) return 1;
    else {
        pPickup_Status{playerid} = true;
        pPickup_AntiFlood[playerid] = gettimer+2;
    }  

	if(Saloon_OP_PickUpDynamicPickup(playerid, pickupid) == 1) return 1;
	if(Dealer_OP_PickUpDynamicPickup(playerid, pickupid) == 1) return 1;
	if(Porter_OP_PickUpDynamicPickup(playerid, pickupid) == 1) return 1;

	if(CallLocalFunction("Army_OP_PickUpDynamicPickup", "ii", playerid, pickupid) == 1) {
		return 1;
	}

	new 
		Fraction: fractionid = GetPlayerFraction(playerid);

    if(pickupid == busstop)
 	{
 		return SendClientMessage(playerid, -1, ""COLOR_BLUE"Аэропорт: Каждые 5 минут курсирует автобус до автошколы");
 	}
	if(pickupid == LawyerOk)
	{
		if(GetPVarInt(playerid,"AntiFloodF") > gettime()){ return false; }
		SetPVarInt(playerid,"AntiFloodF",gettime() + 5);
		if(PlayerInfo[playerid][pJailed] != 1) return 1;
		if(PlayerInfo[playerid][pJailed] == 2) return SendClientMessage(playerid, -1, ""COLOR_RED"Услуга недоступна. Вы заключены за нарушение правил сервера");
		LawPrice[playerid] = PlayerInfo[playerid][pJailTime]/3;
		format(small_string, sizeof(small_string), ""COLOR_RED"Вам нужно {FFFFFF}%d EXP"COLOR_RED" для услуг адвоката",LawPrice[playerid]);
		if(GetPlayerEXP(playerid) < LawPrice[playerid]) return SendClientMessage(playerid, -1, small_string);
	    if(Lawyer == INVALID_PLAYER_ID) return SendClientMessage(playerid, -1, ""COLOR_ORANGE"Свободных адвокатов нет");
	    format(small_string, sizeof(small_string), ""COLOR_ORANGE"Вы выйдите из тюрьмы за %d EXP через 10 секунд",LawPrice[playerid]);
		SendClientMessage(playerid, -1, small_string);
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Чтобы отменить действие - покиньте пикап");
		LawTimer[playerid] = 10;
		return SetPVarInt(playerid,"AntiFloodF",gettime() + 60);
	}
	if(pickupid == lawstart)
	{
	    if(fractionid != FRACTION_GOVERMENT) return 1;
	    if(Lawyer == INVALID_PLAYER_ID) {
			Lawyer = playerid;
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали рабочий день в качестве адвоката");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Отправляйтесь к камерам заключенных");
			LeaveTimer[playerid] = SetTimerEx("LawFail", 10000, false, "i", playerid);
		}
		return 1;
	}
	if(pickupid == TheftAuto[0])
	{
	    SendClientMessage(playerid, -1, ""COLOR_ORANGE"Хочешь угнать тачку и хорошенько подзаработать?");
		if(IsAGang(playerid)) {
			if(PlayerInfo[playerid][pKarma] > -150) {
				return SendClientMessage(playerid, -1, ""COLOR_RED"Необходимо -150 законопослушности");
			}
			if(orders == 0) {
				return SendClientMessage(playerid,-1, ""COLOR_RED"Заказов нет. Приходи в следующем часу");
			}
			format(small_string, sizeof(small_string), ""COLOR_BLUE"На этот час есть: %d заказов на автомобили", orders);
			SendClientMessage(playerid,-1,small_string);
			if(ThefStatus[playerid] > 0) return 1;
			new car[20];
			new sss = 0,
				PlayerKarma = PlayerInfo[playerid][pKarma];

			if((-249 <= PlayerKarma <= -150)) {
				for(new i = GetVehiclePoolSize(); i >= 0; i--) if(IsANope(i) && sss < 20 && IsVehicleOccupied(i) == -1 && Vehicleforeach(i) != -1) car[sss] = i, sss++;
				if(sss == 0) return 1;
				TimeTCar[playerid] = 1200;
			} else if((-349 <= PlayerKarma <= -250)) {
				for(new i = GetVehiclePoolSize(); i >= 0; i--) if(IsAB(i) && sss < 20 && IsVehicleOccupied(i) == -1 && Vehicleforeach(i) != -1) car[sss] = i, sss++;
				if(sss == 0) for(new i = GetVehiclePoolSize(); i >= 0; i--) if(IsANope(i) && sss < 20 && IsVehicleOccupied(i) == -1 && Vehicleforeach(i) != -1) car[sss] = i, sss++;
				if(sss == 0) return 1;
				TimeTCar[playerid] = 900;
			} else if((PlayerKarma <= -350)) {
				for(new i = GetVehiclePoolSize(); i >= 0; i--) if(IsAA(i) && sss < 20 && IsVehicleOccupied(i) == -1 && Vehicleforeach(i) != -1) car[sss] = i, sss++;
				if(sss == 0) for(new i = GetVehiclePoolSize(); i >= 0; i--) if(IsAB(i) && sss < 20 && IsVehicleOccupied(i) == -1 && Vehicleforeach(i) != -1) car[sss] = i, sss++;
				if(sss == 0) for(new i = GetVehiclePoolSize(); i >= 0; i--) if(IsANope(i) && sss < 20 && IsVehicleOccupied(i) == -1 && Vehicleforeach(i) != -1) car[sss] = i, sss++;
				if(sss == 0) return 1;
				TimeTCar[playerid] = 600;
			}
			new randomik = RandomEx(0, sss);
			if(car[randomik] == caridhouse[playerid]) return 1;
			new model = GetVehicleModel(car[randomik]);
			TCar[playerid] = model;
			new Float:X,Float:Y,Float:Z;
			GetVehiclePos(car[randomik],X,Y,Z);
 
			format(small_string, sizeof(small_string), ""COLOR_BLUE"Твое задание, угнать автомобиль {FFFFFF}%s",GetVehicleText(model));
			orders--;
			SendClientMessage(playerid,-1,small_string);
			SendClientMessage(playerid, -1, ""COLOR_BLUE"Район где он находится отмечен черной зоной на карте");
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			TheftZone[playerid] = GangZoneCreate(X-95,Y-80,X+70,Y+85);
			GangZoneShowForPlayer(playerid,TheftZone[playerid],0x00000095);
			
			ThefStatus[playerid] = 1;
		}
		else SendClientMessage(playerid, -1, ""COLOR_RED"Для начала вступи в банду");
		return 1;
	}
	if(pickupid >= Stole[0] && pickupid <= Stole[9])
	{
		if(ArmySteal[playerid] > 0) return 1;
		if(IsAGang(playerid)) {
			DecreaseKarma(playerid);
			
			ArmySteal[playerid] = 5;
			SendClientMessage(playerid, -1, ""COLOR_BLUE"Вы украли 5 заготовок для оружия, доставьте их в дом банды");
		}
		return 1;
	}
	if(pickupid == GetLicense)
	{
		if(Platform[playerid] == 0) return SPD(playerid, dLicenseAdaptive, DIALOG_STYLE_INPUT, "Сдача экзамена", "{FFFFFF}1. Водительские права - 50 EXP\n2. Удостоверение пилота - 250 EXP\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Далее", "Отмена");
		SPD(playerid, dLicense, DIALOG_STYLE_LIST, "Сдача экзамена", "{FFFFFF}1. Водительские права - 50 EXP\n2. Удостоверение пилота - 250 EXP", "Далее", "Отмена");
	   	return 1;
	}
	if(pickupid == Trash[0])
 	{
 		if(GetPVarInt(playerid,"AntiFloodZ") > gettime()){ return false; }
		SetPVarInt(playerid,"AntiFloodZ",gettime() + 5);
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Чтобы начать работу водителя мусоровоза - переоденьтесь в фургоне");
		return 1;
    }
	if(pickupid == Trash[1])
 	{
 		if(GetPVarInt(playerid,"AntiFloodF") > gettime()){ return false; }
		SetPVarInt(playerid,"AntiFloodF",gettime() + 5);
 	    if(GetPVarInt(playerid, "tempjob") == 2) {
	 	    SendClientMessage(playerid, -1, ""COLOR_RED"Вы уволились с работы водителя мусоровоза");
	 	    SetPVarInt(playerid,"tempjob", 0);
			CBackSkin(playerid);
			return 1;
 	    }
 	    if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы состоите во фракции");
 	    SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы начали работу водителем мусоровоза");
 	    SendClientMessage(playerid, -1, ""COLOR_GREEN"Ваша задача вывозить мусор из различных мест города");
 	    SetPVarInt(playerid,"tempjob", 2);
		SetPlayerSkin(playerid, 50);
		return 1;
	}

  	if(pickupid == Farm[4])
 	{
		if(GetPVarInt(playerid,"AntiFloodF") > gettime()){ return false; }
		SetPVarInt(playerid,"AntiFloodF",gettime() + 5);
		SendClientMessage(playerid, -1, "Информация о ферме:");
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Главный фермер: Vlad_Yunusov");
		format(small_string, sizeof(small_string), ""COLOR_ORANGE"Поле засеяно на: %d/600", HarvestAmount);
		SendClientMessage(playerid, -1, small_string);
		format(small_string, sizeof(small_string), ""COLOR_ORANGE"Машина 1: %d/200 | Машина 2: %d/200 | Машина 3: %d/200", Harvest[0],Harvest[1],Harvest[2]);
		SendClientMessage(playerid, -1, small_string);
		return 1;
	}
	if(pickupid == Farm[3])
 	{
		if(GetPVarInt(playerid,"AntiFloodF") > gettime()){ return false; }
		SetPVarInt(playerid,"AntiFloodF",gettime() + 5);
 	    if(GetPVarInt(playerid, "tempjob") == 1) {
 	    	if(GetPVarInt(playerid, "Pizdui") == 2) {
 	    	    if(Harvest[2] > 199) return SendClientMessage(playerid, -1, ""COLOR_RED"Фургон переполнен. Необходимо разгрузить");
 	    		new 
 	    			hmc,
 	    			FarmSkill = PlayerInfo[playerid][pFarmSkill];
 	    		if((0 <= FarmSkill <= 49)) {
					hmc = 1;
					format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/50", hmc, PlayerInfo[playerid][pFarmSkill]);
 	    		} else if(FarmSkill == 50) {
			 		hmc = 2;
			 		format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/100", hmc, PlayerInfo[playerid][pFarmSkill]);
			 		SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			 	} else if((51 <= FarmSkill <= 99)) {
					hmc = 2;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/100", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 100) {
			 	    hmc = 3;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/250", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((101 <= FarmSkill <= 249)) {
			 	    hmc = 3;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/250", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 250) {
			 	    hmc = 4;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/500", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((251 <= FarmSkill <= 499)) {
			 		hmc = 4;
			 		format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/500", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	} else if(FarmSkill == 500) {
			 	    hmc = 5;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/750", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((501 <= FarmSkill <= 749)) {
			 	    hmc = 5;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/750", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 750) {
				 	hmc = 6;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/900", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((751 <= FarmSkill <= 899)) {
				 	hmc = 6;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/900", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 900) {
					hmc = 7;
					format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1000", hmc, PlayerInfo[playerid][pFarmSkill]);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((901 <= FarmSkill <= 999)) {
				 	hmc = 7;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1000", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 1000) {
				 	hmc = 8;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1250", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((1001 <= FarmSkill <= 1249)) {
				 	hmc = 8;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1250", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 1250) {
			 	    hmc = 9;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1500", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((1251 <= FarmSkill <= 1499)) {
				 	hmc = 9;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1500", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 1500) {
				 	hmc = 10;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы достигли максимального уровня фермера. Поздравляем!");
				} else {
					hmc = 10;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: ~b~~h~FULL", hmc);
				}
				Player.AddEXP(PlayerInfo[playerid][pID], hmc, E_JOB_BUS_DRIVER, playerid);
				PlayerInfo[playerid][pFarmSkill] += 1;
				SetPlayerInt(playerid, "FarmSkill", PlayerInfo[playerid][pFarmSkill]);
				GameTextForPlayer(playerid, small_string, 5000, 5);
				HarvestAmount--;
				Harvest[2]++;
				ReloadFarmText();
				if(HarvestAmount < 0) HarvestAmount = 0;
			}

			for(new i = 0; i < sizeof(farm_checkpoint); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint[i], false);
			}
			for(new i = 0; i < sizeof(farm_checkpoint_1); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint_1[i], false);
			}
			for(new i = 0; i < sizeof(farm_checkpoint_2); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint_2[i], false);
			}
			SetPVarInt(playerid,"Pizdui", 1);
			if(HarvestAmount <= 0) return SendClientMessage(playerid, -1, ""COLOR_RED"На поле недостаточно урожая");
			TogglePlayerDynamicCP(playerid, farm_checkpoint[random(sizeof(farm_checkpoint))], true);
			Streamer_Update(playerid, STREAMER_TYPE_CP);
		}
		else SendClientMessage(playerid, -1, ""COLOR_RED"Вы не фермер");
		return 1;
    }
	if(pickupid == Farm[2])
 	{
		if(GetPVarInt(playerid,"AntiFloodF") > gettime()){ return false; }
		SetPVarInt(playerid,"AntiFloodF",gettime() + 5);
 	    if(GetPVarInt(playerid, "tempjob") == 1) {
 	    	if(GetPVarInt(playerid, "Pizdui") == 2) {
 	    	    if(Harvest[1] > 199) return SendClientMessage(playerid, -1, ""COLOR_RED"Фургон переполнен. Необходимо разгрузить");
 	    		new hmc;
				PlayerInfo[playerid][pFarmSkill] += 1;
				SetPlayerInt(playerid, "FarmSkill", PlayerInfo[playerid][pFarmSkill]);
 	    		new 
 	    			FarmSkill = PlayerInfo[playerid][pFarmSkill];
 	    		if((0 <= FarmSkill <= 49)) {
					hmc = 1;
					format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/50", hmc, PlayerInfo[playerid][pFarmSkill]);
 	    		} else if(FarmSkill == 50) {
			 		hmc = 2;
			 		format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/100", hmc, PlayerInfo[playerid][pFarmSkill]);
			 		SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			 	} else if((51 <= FarmSkill <= 99)) {
					hmc = 2;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/100", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 100) {
			 	    hmc = 3;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/250", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((101 <= FarmSkill <= 249)) {
			 	    hmc = 3;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/250", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 250) {
			 	    hmc = 4;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/500", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((251 <= FarmSkill <= 499)) {
			 		hmc = 4;
			 		format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/500", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	} else if(FarmSkill == 500) {
			 	    hmc = 5;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/750", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((501 <= FarmSkill <= 749)) {
			 	    hmc = 5;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/750", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 750) {
				 	hmc = 6;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/900", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((751 <= FarmSkill <= 899)) {
				 	hmc = 6;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/900", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 900) {
					hmc = 7;
					format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1000", hmc, PlayerInfo[playerid][pFarmSkill]);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((901 <= FarmSkill <= 999)) {
				 	hmc = 7;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1000", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 1000) {
				 	hmc = 8;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1250", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((1001 <= FarmSkill <= 1249)) {
				 	hmc = 8;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1250", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 1250) {
			 	    hmc = 9;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1500", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((1251 <= FarmSkill <= 1499)) {
				 	hmc = 9;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1500", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 1500) {
				 	hmc = 10;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы достигли максимального уровня фермера. Поздравляем!");
				} else {
					hmc = 10;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: ~b~~h~FULL", hmc);
				}
				Player.AddEXP(PlayerInfo[playerid][pID], hmc, E_JOB_FARM, playerid);
				GameTextForPlayer(playerid, small_string, 5000, 5);
				HarvestAmount--;
				Harvest[1]++;
				ReloadFarmText();
				if(HarvestAmount < 0) HarvestAmount = 0;
 	    	}
 	    	for(new i = 0; i < sizeof(farm_checkpoint); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint[i], false);
			}
			for(new i = 0; i < sizeof(farm_checkpoint_1); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint_1[i], false);
			}
			for(new i = 0; i < sizeof(farm_checkpoint_2); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint_2[i], false);
			}
 	    	SetPVarInt(playerid,"Pizdui", 1);
    		if(HarvestAmount <= 0) return SendClientMessage(playerid, -1, ""COLOR_RED"На поле недостаточно урожая");
 			TogglePlayerDynamicCP(playerid, farm_checkpoint_1[random(sizeof(farm_checkpoint_1))], true);
 			Streamer_Update(playerid, STREAMER_TYPE_CP);
		}
		else SendClientMessage(playerid, -1, ""COLOR_RED"Вы не фермер");
		return 1;
    }
	if(pickupid == Farm[1])
 	{
		if(GetPVarInt(playerid,"AntiFloodF") > gettime()){ return false; }
		SetPVarInt(playerid,"AntiFloodF",gettime() + 5);
 	    if(GetPVarInt(playerid, "tempjob") == 1) {
 	    	if(GetPVarInt(playerid, "Pizdui") == 2) {
 	    	    if(Harvest[0] > 199) return SendClientMessage(playerid, -1, ""COLOR_RED"Фургон переполнен. Необходимо разгрузить");
 	   			new hmc;
				PlayerInfo[playerid][pFarmSkill] += 1;
				SetPlayerInt(playerid, "FarmSkill", PlayerInfo[playerid][pFarmSkill]);
 	    		new 
 	    			FarmSkill = PlayerInfo[playerid][pFarmSkill];
 	    		if((0 <= FarmSkill <= 49)) {
					hmc = 1;
					format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/50", hmc, PlayerInfo[playerid][pFarmSkill]);
 	    		} else if(FarmSkill == 50) {
			 		hmc = 2;
			 		format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/100", hmc, PlayerInfo[playerid][pFarmSkill]);
			 		SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
			 	} else if((51 <= FarmSkill <= 99)) {
					hmc = 2;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/100", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 100) {
			 	    hmc = 3;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/250", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((101 <= FarmSkill <= 249)) {
			 	    hmc = 3;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/250", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 250) {
			 	    hmc = 4;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/500", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((251 <= FarmSkill <= 499)) {
			 		hmc = 4;
			 		format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/500", hmc, PlayerInfo[playerid][pFarmSkill]);
			 	} else if(FarmSkill == 500) {
			 	    hmc = 5;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/750", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((501 <= FarmSkill <= 749)) {
			 	    hmc = 5;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/750", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 750) {
				 	hmc = 6;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/900", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((751 <= FarmSkill <= 899)) {
				 	hmc = 6;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/900", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 900) {
					hmc = 7;
					format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1000", hmc, PlayerInfo[playerid][pFarmSkill]);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((901 <= FarmSkill <= 999)) {
				 	hmc = 7;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1000", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 1000) {
				 	hmc = 8;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1250", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((1001 <= FarmSkill <= 1249)) {
				 	hmc = 8;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1250", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 1250) {
			 	    hmc = 9;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1500", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Скилл улучшен. Теперь вы будете получать больше EXP");
				} else if((1251 <= FarmSkill <= 1499)) {
				 	hmc = 9;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d/1500", hmc, PlayerInfo[playerid][pFarmSkill]);
				} else if(FarmSkill == 1500) {
				 	hmc = 10;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: %d", hmc, PlayerInfo[playerid][pFarmSkill]);
				 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы достигли максимального уровня фермера. Поздравляем!");
				} else {
					hmc = 10;
				 	format(small_string, sizeof(small_string), "~g~EXP~w~ +%d~n~~y~Skill: ~b~~h~FULL", hmc);
				}
				Player.AddEXP(PlayerInfo[playerid][pID], hmc, E_JOB_FARM, playerid);
				GameTextForPlayer(playerid, small_string, 5000, 5);
				HarvestAmount--;
				Harvest[0]++;
				ReloadFarmText();
				if(HarvestAmount < 0) HarvestAmount = 0;
 	    	}
 	    	for(new i = 0; i < sizeof(farm_checkpoint); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint[i], false);
			}
		  	for(new i = 0; i < sizeof(farm_checkpoint_1); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint_1[i], false);
			}
			for(new i = 0; i < sizeof(farm_checkpoint_2); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint_2[i], false);
			}
 	    	SetPVarInt(playerid,"Pizdui", 1);
    		if(HarvestAmount <= 0) return SendClientMessage(playerid, -1, ""COLOR_RED"На поле недостаточно урожая. Засейте поле");
    		TogglePlayerDynamicCP(playerid, farm_checkpoint_2[random(sizeof(farm_checkpoint_2))], true);
    		Streamer_Update(playerid, STREAMER_TYPE_CP);
		}
		else SendClientMessage(playerid, -1, ""COLOR_RED"Вы не фермер");
		return 1;
    }
	if(pickupid == DrivingSchool[0])
 	{
		SetPlayerPos(playerid, -2028.1647,-105.0986,1035.1719);
		SetPlayerInterior(playerid, 3);
		SetPlayerVirtualWorld(playerid, 12);
		SetPlayerFacingAngle(playerid, 120);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == DrivingSchool[1])
 	{
		SetPlayerPos(playerid, -2026.5680,-100.0698,35.1641);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == DrivingSchool[3])
 	{
		SetPlayerPos(playerid, -2029.5231,-117.4057,1035.1719);
		SetPlayerInterior(playerid, 3);
		SetPlayerVirtualWorld(playerid, 12);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == DrivingSchool[2])
 	{
		SetPlayerPos(playerid, -2029.5573,-122.4770,35.1919);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerFacingAngle(playerid, 180);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == Shop[0])
 	{
		SetPlayerPos(playerid, -30.8413,-90.4022,1003.5469);
		SetPlayerInterior(playerid, 18);
		SetPlayerVirtualWorld(playerid, 11);
		SetPlayerFacingAngle(playerid, 360);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == Shop[1])
 	{
		SetPlayerPos(playerid, 1831.8551,-1842.3892,13.5781);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerFacingAngle(playerid, 90);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == Airport[3])
 	{
		SetPlayerPos(playerid, 1960.9449,-2183.5952,13.5469);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 270);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == Airport[4])
 	{
		return 1;
    }
	if(pickupid == Airport[5])
 	{
		SetPlayerPos(playerid, 1685.8025,-2332.4546,-2.6797);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == Airport[2])
 	{
		SetPlayerPos(playerid, 1895.1206,-2328.8733,13.5469);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 270);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == Airport[1])
 	{
		SetPlayerPos(playerid, 1677.3539,1447.9224,10.7818);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 270);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == Airport[0])
 	{
		SetPlayerPos(playerid, 1594.3190,1447.6788,10.8289);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 90);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == lspd[0])
 	{
 	    if(fractionid > FRACTION_NONE) return SendClientMessage(playerid, -1, "Добро пожаловать в полицейский участок");
		SendClientMessage(playerid, -1, "Чтобы начать рабочий день пройдите в раздевалку");
		return 1;
    }
	if(pickupid == lspd[1])
 	{
 	    if(PlayerInfo[playerid][pKarma] < 100) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть не менее:{FFFFFF} 100");
 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
 		if(fractionid == FRACTION_LSPD) {
	 		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
	 		return 1;
	 	}
	 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
        if(CheckCash(playerid, 100) == false) return 1;
	 	Player.DownEXP(PlayerInfo[playerid][pID], 100, E_INVITE_LSPD, playerid);
	 	SetPlayerFraction(playerid, FRACTION_LSPD, true);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы устроились на работу в Полицейский Департамент!");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Ваша задача патрулировать штат и задерживать преступников!");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вам была выдана рация, используйте её для связи: {FFFFFF}/r");
		SetPlayerColor(playerid, LSPD_COLOR);
		CBackSkin(playerid);
		GivePlayerWeapon(playerid, 24, 150);
		GivePlayerWeapon(playerid, 25, 80);
		GivePlayerWeapon(playerid, 3, 1);
		SetPlayerArmour(playerid, 100);
		

		return 1;
    }
	if(pickupid == lspd[2])
 	{
		SetPlayerPos(playerid, 1568.9657,-1693.8596,5.8906);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 180);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == lspd[3])
 	{
		SetPlayerPos(playerid, 246.6091,63.8309,1003.6406);
		SetPlayerInterior(playerid, 6);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == lspd[4])
 	{
		SetPlayerPos(playerid, 1553.1694,-1675.5588,16.1953);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 90);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == lspd[5])
 	{
		SetPlayerPos(playerid, 246.4036,85.4665,1003.6406);
		SetPlayerInterior(playerid, 6);
		SetPlayerFacingAngle(playerid, 180);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
 	if(pickupid == army)
 	{
 	    if(PlayerInfo[playerid][pKarma] < -50) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть не ниже: {FFFFFF}-50");
 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
 		if(fractionid == FRACTION_ARMY) {
	 		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
	 		return 1;
	 	}
	 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	if(CheckCash(playerid, 100) == false) return 1;
	  	Player.DownEXP(PlayerInfo[playerid][pID], 100, E_INVITE_ARMY, playerid);
 	    SetPlayerFraction(playerid, FRACTION_ARMY, true);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы подписали контракт на срочную службу в армии");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вам была выдана рация, используйте её для связи: {FFFFFF}/r");
		SetPlayerColor(playerid, ARMY_COLOR);
		CBackSkin(playerid);
		GivePlayerWeapon(playerid, 24, 150);
		GivePlayerWeapon(playerid, 31, 150);
		SetPlayerArmour(playerid, 100);
		

		return 1;
    }
	if(pickupid == aztec[0])
 	{
		SetPlayerPos(playerid, 1672.5266,-2049.1316,14.2069);
		SetPlayerInterior(playerid, 1);
		SetPlayerFacingAngle(playerid, 90);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == aztec[1])
 	{
		SetPlayerPos(playerid, 1667.4816,-2108.9382,13.5469);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 180);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == aztec[2])
 	{
 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
 		if(fractionid == FRACTION_AZTECAS) {
	 		if(ArmySteal[playerid] == 5) {
				Warehouse[_:fractionid] += 5;
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы доставили заготовки на склад своей банды");
				DecreaseKarma(playerid);
				
				SetWareInt(fractionid, "amount", Warehouse[_:fractionid]); // he - ID znach - kolvo stolb - imya
				ArmySteal[playerid] = 0;
	 		}
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"На складе банды: %d заготовок оружия", Warehouse[_:fractionid]);
			SendClientMessage(playerid, -1, small_string);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
		 	return 1;
	 	}
	 	if(PlayerInfo[playerid][pKarma] > -50) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть не более:{FFFFFF} -50");
	 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	
		if(TotalZones[6] > TotalZones[5]) {
			if(TotalZones[6] > TotalZones[4]) {
				if(TotalZones[6] > TotalZones[3]) {
					if(TotalZones[6] > TotalZones[2]) {
     				SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете вступить в лидирующую банду");
					return 1;
					}
				}
			}
		}
		if(CheckCash(playerid, 100) == false) return 1;
		Player.DownEXP(PlayerInfo[playerid][pID], 100, E_INVITE_AZTECAS, playerid);
		SetPlayerFraction(playerid, FRACTION_AZTECAS, true);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы вступили в банду Aztecas");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Для общения в чате банды используйте: {FFFFFF}/f");
		SetPlayerColor(playerid, AZTEC_COLOR);
		CBackSkin(playerid);
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 5, 1);
		

		return 1;
    }
	if(pickupid == rifa[0])
 	{
		SetPlayerPos(playerid, 2153.9294,-1780.1713,13.7867);
		SetPlayerInterior(playerid, 1);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == rifa[1])
 	{
		SetPlayerPos(playerid, 2185.9727,-1812.0667,13.54697);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == rifa[2])
 	{
 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
 		if(fractionid == FRACTION_RIFA) {
	 		if(ArmySteal[playerid] == 5) {
				Warehouse[_:fractionid] = Warehouse[_:fractionid]+5;
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы доставили заготовки на склад своей банды");
				SetWareInt(fractionid, "amount", Warehouse[_:fractionid]);
				ArmySteal[playerid] = 0;
	 		}
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"На складе банды: %d заготовок оружия", Warehouse[_:fractionid]);
			SendClientMessage(playerid, -1, small_string);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
		 	return 1;
	 	}
	 	if(PlayerInfo[playerid][pKarma] > -50) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть не более:{FFFFFF} -50");
	 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	
		if(TotalZones[5] > TotalZones[6]) {
			if(TotalZones[5] > TotalZones[4]) {
				if(TotalZones[5] > TotalZones[3]) {
					if(TotalZones[5] > TotalZones[2]) {
     				SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете вступить в лидирующую банду");
					return 1;
					}
				}
			}
		}
		if(CheckCash(playerid, 100) == false) return 1;
  		Player.DownEXP(PlayerInfo[playerid][pID], 100, E_INVITE_RIFA, playerid);
 	    SetPlayerFraction(playerid, FRACTION_RIFA, true);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы вступили в банду Rifa Gang");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Для общения в чате банды используйте: {FFFFFF}/f");

		SetPlayerColor(playerid, RIFA_COLOR);
		CBackSkin(playerid);
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 5, 1);
		

		return 1;
    }
	if(pickupid == vagos[0])
 	{
		SetPlayerPos(playerid, 2691.7751,-1576.3105,20.0395);
		SetPlayerInterior(playerid, 1);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == vagos[1])
 	{
		SetPlayerPos(playerid, 2772.6621,-1628.2477,12.1775);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == vagos[2])
 	{
 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
 		if(fractionid == FRACTION_VAGOS) {
 			if(ArmySteal[playerid] == 5) {
				Warehouse[_:fractionid] = Warehouse[_:fractionid]+5;
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы доставили заготовки на склад своей банды");
				SetWareInt(fractionid, "amount", Warehouse[_:fractionid]);
				ArmySteal[playerid] = 0;
 			}
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"На складе банды: %d заготовок оружия", Warehouse[_:fractionid]);
			SendClientMessage(playerid, -1, small_string);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
		 	return 1;
	 	}
	 	if(PlayerInfo[playerid][pKarma] > -50) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть не более:{FFFFFF} -50");
	 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	
		if(TotalZones[4] > TotalZones[6]) {
			if(TotalZones[4] > TotalZones[5]) {
				if(TotalZones[4] > TotalZones[3]) {
					if(TotalZones[4] > TotalZones[2]) {
     				SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете вступить в лидирующую банду");
					return 1;
					}
				}
			}
		}
		if(CheckCash(playerid, 100) == false) return 1;
		Player.DownEXP(PlayerInfo[playerid][pID], 100, E_INVITE_VAGOS, playerid);
 	   	SetPlayerFraction(playerid, FRACTION_VAGOS, true);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы вступили в банду Vagos Gang");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Для общения в чате банды используйте: {FFFFFF}/f");

		SetPlayerColor(playerid, VAGOS_COLOR);
		CBackSkin(playerid);
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 5, 1);
		

		return 1;
    }
	if(pickupid == Cloth[0])
 	{
		SetPlayerPos(playerid, 207.7884,-108.9535,1005.1328);
		SetPlayerInterior(playerid, 15);
		SetPlayerFacingAngle(playerid, 360);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == Cloth[1])
 	{
		SetPlayerPos(playerid, 2245.0986,-1663.6033,15.4766);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 360);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == Cloth[2])
 	{
		SetPlayerPos(playerid, 226.0482,-8.0069,1002.2109);
		SetPlayerInterior(playerid, 5);
		SetPlayerFacingAngle(playerid, 90);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == Cloth[3])
 	{
		SetPlayerPos(playerid, 459.7586,-1501.1672,31.0387);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 100);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == Cloth[4])
 	{
		SetPlayerPos(playerid, 204.4424,-166.7223,1000.5234);
		SetPlayerInterior(playerid, 14);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == Cloth[5])
 	{
		SetPlayerPos(playerid, 451.9880,-1478.7758,30.8152);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 100);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == Cloth[6])
 	{
		SetPlayerPos(playerid, 207.1658,-137.8920,1003.3125);
		SetPlayerInterior(playerid, 3);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == Cloth[7])
 	{
		SetPlayerPos(playerid, 500.3625,-1358.5323,16.1884);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 337);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == grove[1])
 	{
		SetPlayerPos(playerid, 2495.9802,-1694.4767,1014.7422);
		SetPlayerInterior(playerid, 3);
		SetPlayerFacingAngle(playerid, 180);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == grove[2])
 	{
		SetPlayerPos(playerid, 2495.3098,-1688.5306,13.8640);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == ballas[0])
 	{
		SetPlayerPos(playerid, 2738.0994,-1786.0199,25.5031);
		SetPlayerInterior(playerid, 1);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == ballas[1])
 	{
		SetPlayerPos(playerid, 2649.1306,-2021.5237,13.8233);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 90);
		SetCameraBehindPlayer(playerid);
 		return 1;
 	}
	if(pickupid == ballas[2])
 	{
 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
 		if(fractionid == FRACTION_BALLAS) {
	 		if(ArmySteal[playerid] == 5) {
				Warehouse[_:fractionid] = Warehouse[_:fractionid]+5;
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы доставили заготовки на склад своей банды");
				SetWareInt(fractionid, "amount", Warehouse[_:fractionid]);
				ArmySteal[playerid] = 0;
	 		}
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"На складе банды: %d заготовок оружия", Warehouse[_:fractionid]);
			SendClientMessage(playerid, -1, small_string);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
		 	return 1;
	 	}
	 	if(PlayerInfo[playerid][pKarma] > -50) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть не более:{FFFFFF} -50");
	 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	
		if(TotalZones[3] > TotalZones[6]) {
			if(TotalZones[3] > TotalZones[5]) {
				if(TotalZones[3] > TotalZones[4]) {
					if(TotalZones[3] > TotalZones[2]) {
     				SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете вступить в лидирующую банду");
					return 1;
					}
				}
			}
		}
		if(CheckCash(playerid, 100) == false) return 1;
  		Player.DownEXP(PlayerInfo[playerid][pID], 100, E_INVITE_BALLAS, playerid);
 	    SetPlayerFraction(playerid, FRACTION_BALLAS, true);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы вступили в банду Ballas Gang");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Для общения в чате банды используйте: {FFFFFF}/f");

		SetPlayerColor(playerid, BALLAS_COLOR);
		CBackSkin(playerid);
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 5, 1);
		

		return 1;
    }
	if(pickupid == grove[0])
 	{
 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
 		if(fractionid == FRACTION_GROOVE) {
	 		if(ArmySteal[playerid] == 5) {
				Warehouse[_:fractionid] = Warehouse[_:fractionid]+5;
				SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы доставили заготовки на склад своей банды");
				SetWareInt(fractionid, "amount", Warehouse[_:fractionid]);
				ArmySteal[playerid] = 0;
	 		}
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"На складе банды: %d заготовок оружия", Warehouse[_:fractionid]);
			SendClientMessage(playerid, -1, small_string);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
		 	return 1;
	 	}
	 	if(PlayerInfo[playerid][pKarma] > -50) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть не более:{FFFFFF} -50");
	 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	
		if(TotalZones[2] > TotalZones[6]) {
			if(TotalZones[2] > TotalZones[5]) {
				if(TotalZones[2] > TotalZones[4]) {
					if(TotalZones[2] > TotalZones[3]) {
     				SendClientMessage(playerid, -1, ""COLOR_RED"Вы не можете вступить в лидирующую банду");
					return 1;
					}
				}
			}
		}
		if(CheckCash(playerid, 100) == false) return 1;
  		Player.DownEXP(PlayerInfo[playerid][pID], 100, E_INVITE_GROVE, playerid);
 	    SetPlayerFraction(playerid, FRACTION_GROOVE, true);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы вступили в банду Grove Street");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Для общения в чате банды используйте: {FFFFFF}/f");

		SetPlayerColor(playerid, GROVE_COLOR);
		CBackSkin(playerid);
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 5, 1);
		

		return 1;
    }
	if(pickupid == robbery[0])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid != FRACTION_LSPD) {
			if(shop[0] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Этот бизнес уже был недавно ограблен");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 5);
				return 1;
			}
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали грабить бизнес. Не отходите от него в течение 30 секунд");
			PlayerInfo[playerid][pWanted] += 300;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
			SendPoliceGameText("~r~Robbery at Unity Station 24/7");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 30000, 0, "i", playerid);
	   		SetTimer("Clear0", 1000 * 60 * 5, false);
			robber[0] = playerid;
			shop[0] = 1;
			return 1;
		}
		return 1;
    }
	if(pickupid == robbery[1])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid != FRACTION_LSPD) {
			if(shop[1] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Этот бизнес уже был недавно ограблен");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
				return 1;
			}
		
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали грабить бизнес. Не отходите от него в течение 30 секунд");
			PlayerInfo[playerid][pWanted] += 300;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SendPoliceGameText("~r~Robbery at Alhambra");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 30000, 0, "i", playerid);
	   		SetTimer("Clear1", 1000 * 60 * 5, false);
			robber[1] = playerid;
			shop[1] = 1;
			return 1;
		}
		return 1;
    }
	if(pickupid == robbery[2])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid != FRACTION_LSPD) {
			if(shop[2] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Этот бизнес уже был недавно ограблен");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
				return 1;
			}
		
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали грабить бизнес. Не отходите от него в течение 30 секунд");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если полицейский встанет на этот пикап - вы попадете в тюрьму");
			PlayerInfo[playerid][pWanted] += 300;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
			SendPoliceGameText("~r~Robbery at Idlewood Pizza");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 30000, 0, "i", playerid);
	   		SetTimer("Clear2", 1000 * 60 * 5, false);
			robber[2] = playerid;
			shop[2] = 1;
			return 1;
		}
		return 1;
    }
	if(pickupid == robbery[3])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid != FRACTION_LSPD) {
			if(shop[3] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Этот бизнес уже был недавно ограблен");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);

				return 1;
			}

			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали грабить бизнес. Не отходите от него в течение 30 секунд");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если полицейский встанет на этот пикап - вы попадете в тюрьму");
			PlayerInfo[playerid][pWanted] += 300;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
			SendPoliceGameText("~r~Robbery at Ganton Binco");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 30000, 0, "i", playerid);
	   		SetTimer("Clear3", 1000 * 60 * 5, false);
			robber[3] = playerid;
			shop[3] = 1;
			return 1;
		}
		return 1;
    }
	if(pickupid == robbery[4])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid != FRACTION_LSPD) {
			if(shop[4] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Этот бизнес уже был недавно ограблен");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);

				return 1;
			}
		
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали грабить бизнес. Не отходите от него в течение 30 секунд");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если полицейский встанет на этот пикап - вы попадете в тюрьму");
			PlayerInfo[playerid][pWanted] += 300;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
			SendPoliceGameText("~r~Robbery at Pig Pen Club");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 30000, 0, "i", playerid);
	   		SetTimer("Clear4", 1000 * 60 * 5, false);
			robber[4] = playerid;
			shop[4] = 1;
			return 1;
		}
		return 1;
    }
	if(pickupid == robbery[5])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid != FRACTION_LSPD) {
			if(shop[5] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Этот бизнес уже был недавно ограблен");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
				return 1;
			}
		
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали грабить бизнес. Не отходите от него в течение 30 секунд");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если полицейский встанет на этот пикап - вы попадете в тюрьму");
			PlayerInfo[playerid][pWanted] += 300;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
			SendPoliceGameText("~r~Robbery at Idlewood Gym");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 30000, 0, "i", playerid);
	   		SetTimer("Clear5", 1000 * 60 * 5, false);
			robber[5] = playerid;
			shop[5] = 1;
			return 1;
		}
		return 1;
    }
	if(pickupid == robbery[6])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid != FRACTION_LSPD) {
			if(shop[6] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Этот бизнес уже был недавно ограблен");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
				return 1;
			}
		
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали грабить бизнес. Не отходите от него в течение 30 секунд");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если полицейский встанет на этот пикап - вы попадете в тюрьму");
			PlayerInfo[playerid][pWanted] += 300;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
			SendPoliceGameText("~r~Robbery at El Corona Tattoo");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 30000, 0, "i", playerid);
	   		SetTimer("Clear6", 1000 * 60 * 5, false);
			robber[6] = playerid;
			shop[6] = 1;
			return 1;
		}
		return 1;
    }
	if(pickupid == robbery[7])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid != FRACTION_LSPD) {
			if(shop[7] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Этот бизнес уже был недавно ограблен");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
				return 1;
			}
		
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали грабить бизнес. Не отходите от него в течение 30 секунд");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если полицейский встанет на этот пикап - вы попадете в тюрьму");
			PlayerInfo[playerid][pWanted] += 300;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
			SendPoliceGameText("~r~Robbery at Idlewood Barbershop");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 30000, 0, "i", playerid);
	   		SetTimer("Clear7", 1000 * 60 * 5, false);
			robber[7] = playerid;
			shop[7] = 1;
			return 1;
		}
		return 1;
    }
	if(pickupid == robbery[8])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid != FRACTION_LSPD) {
			if(shop[8] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Этот бизнес уже был недавно ограблен");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
				return 1;
			}
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали грабить бизнес. Не отходите от него в течение 30 секунд");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если полицейский встанет на этот пикап - вы попадете в тюрьму");
			PlayerInfo[playerid][pWanted] += 300;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
			SendPoliceGameText("~r~Robbery at Idlewood Tattoo");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 30000, 0, "i", playerid);
	   		SetTimer("Clear8", 1000 * 60 * 5, false);
			robber[8] = playerid;
			shop[8] = 1;
			return 1;
		}
		return 1;
    }
	if(pickupid == robbery[9])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid != FRACTION_LSPD) {
			if(shop[9] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Этот бизнес уже был недавно ограблен");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
				return 1;
			}
		
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали грабить бизнес. Не отходите от него в течение 30 секунд");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если полицейский встанет на этот пикап - вы попадете в тюрьму");
			PlayerInfo[playerid][pWanted] += 300;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
			SendPoliceGameText("~r~Robbery at 10 Green Bottles");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 30000, 0, "i", playerid);
	   		SetTimer("Clear9", 1000 * 60 * 5, false);
			robber[9] = playerid;
			shop[9] = 1;
			return 1;
		}
		return 1;
    }
	if(pickupid == robbery[10])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid != FRACTION_LSPD) {
			if(shop[10] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Этот бизнес уже был недавно ограблен");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
				return 1;
			}
		
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали грабить бизнес. Не отходите от него в течение 30 секунд");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если полицейский встанет на этот пикап - вы попадете в тюрьму");
			PlayerInfo[playerid][pWanted] += 300;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
			SendPoliceGameText("~r~Robbery at West Cluckin Bell");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 30000, 0, "i", playerid);
	   		SetTimer("Clear10", 1000 * 60 * 5, false);
			robber[10] = playerid;
			shop[10] = 1;
			return 1;
		}
		return 1;
    }
	if(pickupid == robbery[11])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(fractionid < FRACTION_RUSSIAN_MAFIA && fractionid != FRACTION_LSPD) {
			if(shop[11] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Этот бизнес уже был недавно ограблен");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
				return 1;
			}

			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали грабить бизнес. Не отходите от него в течение 30 секунд");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Если полицейский встанет на этот пикап - вы попадете в тюрьму");
			PlayerInfo[playerid][pWanted] += 300;
			SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
			SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
			SendPoliceGameText("~r~Robbery at Seville Barbershop");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 30000, 0, "i", playerid);
	   		SetTimer("Clear11", 1000 * 60 * 5, false);
			robber[11] = playerid;
			shop[11] = 1;
			return 1;
		}
		return 1;
    }
	if(pickupid == robbery[12])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(IsAMafia(playerid)) {
			if(shop[12] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Партия оружия еще не прибыла. Подождите немного");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
				return 1;
			}
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы получили партию оружия. Доставьте её в указанное на карте место");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас есть 2 минуты. Если вы не успеете - сделка провалена");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 120000, 0, "i", playerid);
	   		SetPVarInt(playerid, "robbery_time", 120);
	   		SetTimer("Clear12", 1000 * 60 * 3, false);
			robber[12] = playerid;
			shop[12] = 1;
			switch(random(6)) {
				case 0:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[0], true);
					carry[playerid] = 0;
				}
				case 1:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[1], true);
					carry[playerid] = 1;
				}
				case 2:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[2], true);
					carry[playerid] = 2;
				}
				case 3:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[3], true);
					carry[playerid] = 3;
				}
				case 4:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[4], true);
					carry[playerid] = 4;
				}
				case 5:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[5], true);
					carry[playerid] = 5;
				}
			}
		}
		return 1;
    }
	if(pickupid == robbery[13])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(IsAMafia(playerid)) {
			if(shop[13] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Партия оружия еще не прибыла. Подождите немного");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
				return 1;
			}
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы получили партию наркотиков. Доставьте её в указанное на карте место");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас есть 2 минуты. Если вы не успеете - сделка провалена");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 120000, 0, "i", playerid);
	   		SetPVarInt(playerid, "robbery_time", 120);
	   		SetTimer("Clear13", 1000 * 60 * 3, false);
			robber[13] = playerid;
			shop[13] = 1;
			switch(random(6)) {
				case 0:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[0], true);
					carry[playerid] = 0;
				}
				case 1:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[1], true);
					carry[playerid] = 1;
				}
				case 2:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[2], true);
					carry[playerid] = 2;
				}
				case 3:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[3], true);
					carry[playerid] = 3;
				}
				case 4:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[4], true);
					carry[playerid] = 4;
				}
				case 5:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[5], true);
					carry[playerid] = 5;
				}
			}
		}
		return 1;
    }
	if(pickupid == robbery[14])
 	{
 	    if(GetPVarInt(playerid,"RobOnce") == 1){ return false; }
 		if(IsAMafia(playerid)) {
			if(shop[14] == 1) {
				if(GetPVarInt(playerid,"AntiFloodRob") > gettime()){ return false; }
				SendClientMessage(playerid, -1, "Партия оружия еще не прибыла. Подождите немного");
				SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
				return 1;
			}
			SetPVarInt(playerid,"AntiFloodRob",gettime() + 30);
			SetPVarInt(playerid,"RobOnce", 1);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы получили партию наркотиков. Доставьте её в указанное на карте место");
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"У вас есть 2 минуты. Если вы не успеете - сделка провалена");
		    RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
	   		RobTimer[playerid] = SetTimerEx("Rob", 120000, 0, "i", playerid);
	   		SetPVarInt(playerid, "robbery_time", 120);
	   		SetTimer("Clear14", 1000 * 60 * 3, false);
			robber[14] = playerid;
			shop[14] = 1;
			switch(random(4)) {
				case 0:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[0], true);
					carry[playerid] = 0;
				}
				case 1:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[1], true);
					carry[playerid] = 1;
				}
				case 2:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[2], true);
					carry[playerid] = 2;
				}
				case 3:
				{
					TogglePlayerDynamicCP(playerid, mafia_checkpoint[3], true);
					carry[playerid] = 3;
				}
			}
		}
		return 1;
    }
	if(pickupid == drugs)
 	{
 	    if(GetPVarInt(playerid,"Bought") > gettime()){ return false; }
		if(CheckCash(playerid, 150) == false) return 1;
		Player.DownEXP(PlayerInfo[playerid][pID], 150, E_BUY_DRUGS, playerid);
		GameTextForPlayer(playerid, "~r~-150 ~w~EXP", 3000, 5);
		SetPlayerChatBubble(playerid, "употребил(а) наркотик", 0x000000AA, 10.0, 2000);
		SetPlayerHealth(playerid, 150);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили и употребили наркотик. Ваше здоровье: {FFFFFF} 150 HP");
		SetPlayerWeather(playerid, -68);
		DrugTimer[playerid] = KillTimer(DrugTimer[playerid]); 
		DrugTimer[playerid] = SetTimerEx("DrugsEffect", 6000, false, "i", playerid);
		SetPlayerDrunkLevel(playerid, 6000);
		SetPVarInt(playerid,"Bought",gettime() + 300);
		return 1;
    }
	if(pickupid == ShopBuy[0])
 	{
 		if(Platform[playerid] == 0) return SPD(playerid, dShopAdaptive, DIALOG_STYLE_INPUT, "Ассортимент", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Купить", "Выход");
		SPD(playerid, dShop, DIALOG_STYLE_LIST, "Ассортимент", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP", "Купить", "Выход");
		return 1;
    }
	if(pickupid == ShopBuy[1])
 	{
 		return Alcohol(playerid);
    }
	if(pickupid == ShopBuy[2])
 	{
		return Alcohol(playerid);
    }
	if(pickupid == ShopBuy[3])
 	{
		return Alcohol(playerid);
    }
	if(pickupid == danang[2])
 	{
 		if(PlayerInfo[playerid][pKarma] > -500) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть:{FFFFFF} -500");
 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
 		if(fractionid == FRACTION_DN_BOYS) {
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
	 		return 1;
	 	}
	 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	if(CheckCash(playerid, 100) == false) return 1;
	  	Player.DownEXP(PlayerInfo[playerid][pID], 100, E_INVITE_DNBOYS, playerid);
 	    SetPlayerFraction(playerid, FRACTION_DN_BOYS, true);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы вступили в Da Nang Boys");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Для общения в чате мафии используйте: {FFFFFF}/f");

		SetPlayerColor(playerid, DANANG_COLOR);
		CBackSkin(playerid);
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 8, 1);
		

		return 1;
    }
	if(pickupid == triad[2])
 	{
 	    if(PlayerInfo[playerid][pKarma] > -500) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть:{FFFFFF} -500");
 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
 		if(fractionid == FRACTION_TRIADA) {
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
	 		return 1;
	 	}
	 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	if(CheckCash(playerid, 100) == false) return 1;
	  	Player.DownEXP(PlayerInfo[playerid][pID], 100, E_INVITE_TRIADS, playerid);
 	    SetPlayerFraction(playerid, FRACTION_TRIADA, true);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы вступили в Triads");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Для общения в чате мафии используйте: {FFFFFF}/f");

		SetPlayerColor(playerid, TRIAD_COLOR);
		CBackSkin(playerid);
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 31, 150);
		GivePlayerWeapon(playerid, 8, 1);
		

		return 1;
    }
	if(pickupid == russian[2])
 	{
 	    if(PlayerInfo[playerid][pKarma] > -500) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть:{FFFFFF} -500");
 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
 		if(fractionid == FRACTION_RUSSIAN_MAFIA) {
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
	 		return 1;
	 	}
	 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	if(CheckCash(playerid, 100) == false) return 1;
	  	Player.DownEXP(PlayerInfo[playerid][pID], 100, E_INVITE_PM, playerid);
	 	SetPlayerFraction(playerid, FRACTION_RUSSIAN_MAFIA, true);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы вступили в Русскую Мафию");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Для общения в чате мафии используйте: {FFFFFF}/f");

		SetPlayerColor(playerid, RUSSIA_COLOR);
		CBackSkin(playerid);
		GivePlayerWeapon(playerid, 24, 60);
		GivePlayerWeapon(playerid, 30, 150);
		GivePlayerWeapon(playerid, 1, 1);
		

		return 1;
    }
   	if(pickupid == russian[0]) 
 	{
		SetPlayerPos(playerid, 939.6087,1733.3231,8.8516);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 270);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
   	if(pickupid == russian[1])
 	{
		SetPlayerPos(playerid, 1063.3534,1548.0619,5.9481);
		SetPlayerInterior(playerid, 1);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == triad[0])
 	{
		SetPlayerPos(playerid, -2240.8008,575.6141,35.1719);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 180);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == triad[1])
 	{
		SetPlayerPos(playerid, -2261.9504,474.3629,38.6032);
		SetPlayerInterior(playerid, 1);
		SetPlayerFacingAngle(playerid, 90);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == danang[0])
 	{
		SetPlayerPos(playerid, -1534.6161,1149.9260,7.2198);
		SetPlayerInterior(playerid, 1);
		SetPlayerFacingAngle(playerid, 180);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == danang[1])
 	{
		SetPlayerPos(playerid, -1696.4738,1329.2496,7.1787);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 138);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == Azino[0])
 	{
 	    if(GetPVarInt(playerid,"Boughta") > gettime()){ return false; }
 	    if(GetPlayerScore(playerid) < 25) return SendClientMessage(playerid, -1, ""COLOR_RED"Вам нужно {FFFFFF}25 EXP"COLOR_RED" для игры в автомат");
		Player.DownEXP(PlayerInfo[playerid][pID], 25, E_PLAYING_AZINO_MACHINE, playerid);
		AzinoTimer[playerid] = KillTimer(AzinoTimer[playerid]); 
        AzinoTimer[playerid] = SetTimerEx("GoAzino", 10000, false, "d", playerid);
        SetPVarInt(playerid, "MinusTime", 10);
        GameTextForPlayer(playerid, "~r~-25 EXP", 3000, 4);
        SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали игру, барабан крутится. Подождите 10 секунд");
        SendClientMessage(playerid, -1, ""COLOR_ORANGE"У Вас есть шанс выйграть 1000-9000 EXP или Turismo!");
		format(small_string, 100, "%s запустил игровой автомат...", PlayerInfo[playerid][pName]);
		ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		SetPVarInt(playerid,"Boughta",gettime() + 15);
		return 1;
 	}
	if(pickupid == Azino[1])
 	{
 	    if(GetPVarInt(playerid,"Boughta") > gettime()){ return false; }
 	    if(GetPlayerScore(playerid) < 25) return SendClientMessage(playerid, -1, ""COLOR_RED"Вам нужно {FFFFFF}25 EXP"COLOR_RED" для игры в автомат");
		Player.DownEXP(PlayerInfo[playerid][pID], 25, E_PLAYING_AZINO_MACHINE, playerid);
		AzinoTimer[playerid] = KillTimer(AzinoTimer[playerid]); 
        AzinoTimer[playerid] = SetTimerEx("GoAzino", 10000, false, "d", playerid);
        SetPVarInt(playerid, "MinusTime", 10);
        GameTextForPlayer(playerid, "~r~-25 EXP", 3000, 4);
        SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали игру, барабан крутится. Подождите 10 секунд");
        SendClientMessage(playerid, -1, ""COLOR_ORANGE"У Вас есть шанс выйграть 1000-9000 EXP или Turismo!");
		format(small_string, 100, "%s запустил игровой автомат...", PlayerInfo[playerid][pName]);
		ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		SetPVarInt(playerid,"Boughta",gettime() + 15);
		return 1;
 	}
	if(pickupid == mayor[0])
 	{
		SetPlayerPos(playerid, 1481.2174,-1770.3323,18.7958);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == CasEn[0])
 	{
		SetPlayerPos(playerid, 1008.5361,-1183.1838,29.6481);
		SetPlayerInterior(playerid, 1);
		SetPlayerFacingAngle(playerid, 180);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == CasEn[1])
 	{
		SetPlayerPos(playerid, 1021.9028,-1124.1097,23.8691);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 180);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == fbi[0])
 	{
		SetPlayerPos(playerid, -2498.6301,538.3937,432.6819);
		SetPlayerInterior(playerid, 2);
		SetPlayerVirtualWorld(playerid, 2);
		SetPlayerFacingAngle(playerid, 263);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == fbi[1])
 	{
		SetPlayerPos(playerid, -2453.6165,503.9776,30.0800);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerFacingAngle(playerid, 270);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
    if(pickupid == fbi[2])
 	{
 	    if(PlayerInfo[playerid][pKarma] < 250) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть не ниже: {FFFFFF}250");
 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
 		if(fractionid == FRACTION_FBI) {
	 		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
	 		return 1;
	 	}
	 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	if(CheckCash(playerid, 100) == false) return 1;
	  	Player.DownEXP(PlayerInfo[playerid][pID], 100, E_INVITE_FBI, playerid);
 	    SetPlayerFraction(playerid, FRACTION_FBI, true);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы устроились в Федеральное Бюро");
		//SendClientMessage(playerid, -1, ""COLOR_GREEN"Ваша задача патрулировать штат и задерживать преступников!");
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вам была выдана рация, используйте её для связи: {FFFFFF}/r");
		SetPlayerColor(playerid, FBI_COLOR);
		CBackSkin(playerid);
		GivePlayerWeapon(playerid, 24, 150);
		GivePlayerWeapon(playerid, 31, 150);
		SetPlayerArmour(playerid, 100);
		

		return 1;
    }
	if(pickupid == fbi[3])
 	{
 	    new wanted[90];
        SendClientMessage(playerid, -1, ""COLOR_BLUE"Особо опасные преступники");
 	    foreach(new i: PlayerWanted) {
			if(PlayerInfo[i][pWanted] > 3600) {
				format(wanted, 90, ""COLOR_BLUE"Подозреваемый: {FFFFFF}%s", PlayerInfo[i][pName]);
				SendClientMessage(playerid, -1, wanted);
			}
		}
		return 1;
 	}
	if(pickupid == mayor[1])
 	{
		SetPlayerPos(playerid, 1481.2358,-1730.9078,479.2806);
		SetPlayerInterior(playerid, 1);
		SetPlayerFacingAngle(playerid, 180);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == mayor[2])
 	{
 	    SPD(playerid, dInviting, DIALOG_STYLE_MSGBOX, "Собеседование", "{FFFFFF}Вы действительно хотите пройти собеседование?", "Да", "Нет");
		switch(invite_type) {
			case 1: {
				SendClientMessage(playerid, -1, ""COLOR_ORANGE"Собеседование в Армию. Подождите 10 секунд...");
			}
			case 2: {
				SendClientMessage(playerid, -1, ""COLOR_ORANGE"Собеседование в LSPD. Подождите 10 секунд...");
			}
			case 3: {
	        	SendClientMessage(playerid, -1, ""COLOR_ORANGE"Собеседование в FBI. Подождите 10 секунд...");
			}
			case 0: {
       		 	SendClientMessage(playerid, -1, ""COLOR_ORANGE"Собеседование в Мэрию. Подождите 10 секунд...");
			}
		}
		return 1;
    }
	if(pickupid == mayor[5])
 	{
		SPD(playerid, dNullKarma, DIALOG_STYLE_MSGBOX, "Переоформить паспорт", "Переоформить свой паспорт за 10000 EXP?\n\n"COLOR_RED"Переоформление полностью сбрасывает законопослушность", "Да", "Отмена");
		return 1;
    }
	if(pickupid == mayor[3])
 	{
 		if(fractionid > FRACTION_NONE) {
		 	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы уволились из организации. Теперь вы гражданский");
		 	SetPlayerColor(playerid, CIVIL_COLOR);
		 	SetPlayerArmour(playerid, 0);
		 	ResetPlayerWeapons(playerid);
		 	RemovePlayerFraction(playerid, true);
		 	CBackSkin(playerid);
		 	CopTimerID[playerid] = KillTimer(CopTimerID[playerid]); 
		 	return 1;
	 	} else {
	 		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Здесь можно уволиться, если вы устроены во фракцию");
	 	}
	 	return 1;
    }
	if(pickupid == mayor[4])
 	{
 		new Float:health;
		GetPlayerHealth(playerid,health);
		if (health < 100.0) {
			

			SendClientMessage(playerid, -1, ""COLOR_GREEN"Здоровье пополнено");
		}
		return 1;
    }
   	if(pickupid == selcol[0])
 	{
	 		if(GetPVarInt(playerid,"СolSel") > gettime()){ return false; }
			SetPVarInt(playerid,"СolSel",gettime() + 2);
			PlayerPlaySound(playerid, 1098 , 0.0, 0.0, 0.0);
	 	    switch(GetPVarInt(playerid, "CarCol"))
	 	    {
		 	    case 1: {
			        PlayerInfo[playerid][pCarCol] = 1;
			        SetPVarInt(playerid, "CarCol", 2);
			        SendClientMessage(playerid, -1, "Первый цвет для автомобиля: Белый");
			 		SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
	 			}
		 	    case 2: {
			        PlayerInfo[playerid][pCarCol] = 2;
			        SetPVarInt(playerid, "CarCol", 3);
			        SendClientMessage(playerid, -1, "Первый цвет для автомобиля: {00ffff}Бирюзовый");
			 		SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
		 		}
		 	    case 3: {
			        PlayerInfo[playerid][pCarCol] = 3;
			        SetPVarInt(playerid, "CarCol", 4);
			        SendClientMessage(playerid, -1, "Первый цвет для автомобиля: "COLOR_RED"Красный");
			 		SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
		 		}
		 	    case 4: {
			        PlayerInfo[playerid][pCarCol] = 5;
			        SetPVarInt(playerid, "CarCol", 5);
			        SendClientMessage(playerid, -1, "Первый цвет для автомобиля: {ff33cc}Розовый");
			 		SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
		 		}
		 	    case 5: {
			        PlayerInfo[playerid][pCarCol] = 6;
			        SetPVarInt(playerid, "CarCol", 6);
			        SendClientMessage(playerid, -1, "Первый цвет для автомобиля: {ffff00}Желтый");
			 		SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
		 		}
		 	    case 6: {
			        PlayerInfo[playerid][pCarCol] = 16;
			        SetPVarInt(playerid, "CarCol", 7);
			        SendClientMessage(playerid, -1, "Первый цвет для автомобиля: {009933}Зеленый");
			 		SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
		 		}
		 	    case 7: {
			        PlayerInfo[playerid][pCarCol] = 24;
			        SetPVarInt(playerid, "CarCol", 8);
			        SendClientMessage(playerid, -1, "Первый цвет для автомобиля: {808080}Серый");
			 		SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
		 		}
		 	    case 8: {
			        PlayerInfo[playerid][pCarCol] = 79;
			        SetPVarInt(playerid, "CarCol", 9);
			        SendClientMessage(playerid, -1, "Первый цвет для автомобиля: {3366ff}Синий");
			 		SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
		 		}
		 	    case 9: {
			        PlayerInfo[playerid][pCarCol] = 99;
			        SetPVarInt(playerid, "CarCol", 10);
			        SendClientMessage(playerid, -1, "Первый цвет для автомобиля: {f2e6d9}Кремовый");
			 		SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
		 		}
		   		case 10: {
			        PlayerInfo[playerid][pCarCol] = 118;
			        SetPVarInt(playerid, "CarCol", 0);
			        SendClientMessage(playerid, -1, "Первый цвет для автомобиля: {f2e6d9}Серебро");
			 		SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
		 		}
		 		default: {
			        PlayerInfo[playerid][pCarCol] = 0;
			        SetPVarInt(playerid, "CarCol", 1);
			        SendClientMessage(playerid, -1, "Первый цвет для автомобиля: Черный");
			 		SetPlayerInt(playerid, "CarCol", PlayerInfo[playerid][pCarCol]);
		 		}
	 		}
			return 1;
 	}
   	if(pickupid == selcol[1])
 	{
 			if(GetPVarInt(playerid,"СolSel2") > gettime()){ return false; }
			SetPVarInt(playerid,"СolSel2",gettime() + 2);
			PlayerPlaySound(playerid, 1098 , 0.0, 0.0, 0.0);
 	    	switch(GetPVarInt(playerid, "CarCol2"))
	 	    {
		 	    case 1: {
			        PlayerInfo[playerid][pCarCol2] = 1;
			        SetPVarInt(playerid, "CarCol2", 2);
			        SendClientMessage(playerid, -1, "Второй цвет для автомобиля: Белый");
			 		SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);
		 		}
		 	    case 2: {
			        PlayerInfo[playerid][pCarCol2] = 2;
			        SetPVarInt(playerid, "CarCol2", 3);
			        SendClientMessage(playerid, -1, "Второй цвет для автомобиля: {00ffff}Бирюзовый");
			 		SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);
		 		}
		 	    case 3: {
			        PlayerInfo[playerid][pCarCol2] = 3;
			        SetPVarInt(playerid, "CarCol2", 4);
			        SendClientMessage(playerid, -1, "Второй цвет для автомобиля: "COLOR_RED"Красный");
			 		SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);
		 		}
		 	    case 4: {
			        PlayerInfo[playerid][pCarCol2] = 5;
			        SetPVarInt(playerid, "CarCol2", 5);
			        SendClientMessage(playerid, -1, "Второй цвет для автомобиля: {ff33cc}Розовый");
			 		SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);
		 		}
		 	    case 5: {
			        PlayerInfo[playerid][pCarCol2] = 6;
			        SetPVarInt(playerid, "CarCol2", 6);
			        SendClientMessage(playerid, -1, "Второй цвет для автомобиля: {ffff00}Желтый");
			 		SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);
		 		}
		 	    case 6: {
			        PlayerInfo[playerid][pCarCol2] = 16;
			        SetPVarInt(playerid, "CarCol2", 7);
			        SendClientMessage(playerid, -1, "Второй цвет для автомобиля: {009933}Зеленый");
			 		SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);
		 		}
		 	    case 7: {
			        PlayerInfo[playerid][pCarCol2] = 24;
			        SetPVarInt(playerid, "CarCol2", 8);
			        SendClientMessage(playerid, -1, "Второй цвет для автомобиля: {808080}Серый");
			 		SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);
		 		}
		 	    case 8: {
			        PlayerInfo[playerid][pCarCol2] = 79;
			        SetPVarInt(playerid, "CarCol2", 9);
			        SendClientMessage(playerid, -1, "Второй цвет для автомобиля: {3366ff}Синий");
			 		SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);
		 		}
		 	    case 9: {
			        PlayerInfo[playerid][pCarCol2] = 99;
			        SetPVarInt(playerid, "CarCol2", 10);
			        SendClientMessage(playerid, -1, "Второй цвет для автомобиля: {f2e6d9}Кремовый");
			 		SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);
		 		}
		   		case 10: {
			        PlayerInfo[playerid][pCarCol2] = 118;
			        SetPVarInt(playerid, "CarCol2", 0);
			        SendClientMessage(playerid, -1, "Второй цвет для автомобиля: {f2e6d9}Серебро");
			 		SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);
		 		}
		 		default: {
			        PlayerInfo[playerid][pCarCol2] = 0;
			        SetPVarInt(playerid, "CarCol2", 1);
			        SendClientMessage(playerid, -1, "Второй цвет для автомобиля: Черный");
			 		SetPlayerInt(playerid, "CarCol2", PlayerInfo[playerid][pCarCol2]);
		 		}
 			}
			return 1;
 	}
	if(pickupid == cloth[1])
	{
		if(fractionid > FRACTION_NONE) return SendClientMessage(playerid, -1, "Менять одежду можно только вне фракции");
 		if(GetPVarInt(playerid,"SkinSel") > gettime()){ return false; }
		SetPVarInt(playerid,"SkinSel",gettime() + 5);
		if(GetPVarInt(playerid, "SelSkin") == 0) return SendClientMessage(playerid, -1, "Сначала примерьте одежду");
  		if(GetPlayerScore(playerid) < 1000) return SendClientMessage(playerid, -1, ""COLOR_RED"Вам нужно {FFFFFF}1000 EXP"COLOR_RED" для покупки данной одежды");
  		if(GetPVarInt(playerid,"ShopSkin") != 1) return 1;

		Player.DownEXP(PlayerInfo[playerid][pID], 1000, E_BUY_SLOTHES, playerid);
		new selected;
		selected = GetPlayerSkin(playerid);
		if(selected == PlayerInfo[playerid][pSkin]) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы уже приобрели данную одежду");
 	    
		SetPlayerInt(playerid, "Skin", selected);
		PlayerInfo[playerid][pSkin] = selected;
		SetPVarInt(playerid, "SelSkin", 0);
		if(IsValidTimer(bskin[playerid])) KillTimer(bskin[playerid]),bskin[playerid] = -1;
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили одежду. Хорошего дня!");
 		return 1;
 	}

	if(pickupid == cloth[0])
	{
  		SetPVarInt(playerid,"ShopSkin",1);
	    if(IsValidTimer(bskin[playerid])) KillTimer(bskin[playerid]),bskin[playerid] = -1;
	    bskin[playerid] = SetTimerEx("CBackSkin", 20000, false, "d", playerid);
		if(fractionid > FRACTION_NONE) return SendClientMessage(playerid, -1, "Менять одежду можно только вне фракции");
 		if(GetPVarInt(playerid,"SkinSel") > gettime()){ return false; }
		SetPVarInt(playerid,"SkinSel",gettime() + 2);
		if(PlayerInfo[playerid][pSex] == 0) {
			switch(GetPVarInt(playerid, "SelSkin"))
	    	{
			    case 1: {
				    SetPVarInt(playerid, "SelSkin", 2);
					SetPlayerSkin(playerid, 15);
				}
			    case 2: {
				    SetPVarInt(playerid, "SelSkin", 3);
					SetPlayerSkin(playerid, 21);
				}
			    case 3: {
				    SetPVarInt(playerid, "SelSkin", 4);
					SetPlayerSkin(playerid, 25);
				}
			    case 4: {
				    SetPVarInt(playerid, "SelSkin", 5);
					SetPlayerSkin(playerid, 26);
				}
			    case 5: {
				    SetPVarInt(playerid, "SelSkin", 6);
					SetPlayerSkin(playerid, 44);
				}
			    case 6: {
				    SetPVarInt(playerid, "SelSkin", 7);
					SetPlayerSkin(playerid, 50);
				}
			    case 7: {
				    SetPVarInt(playerid, "SelSkin", 8);
					SetPlayerSkin(playerid, 58);
				}
			    case 8: {
				    SetPVarInt(playerid, "SelSkin", 9);
					SetPlayerSkin(playerid, 30);
				}
			    case 9: {
				    SetPVarInt(playerid, "SelSkin", 10);
					SetPlayerSkin(playerid, 32);
				}
				case 10: {
				    SetPVarInt(playerid, "SelSkin", 11);
				    SetPlayerSkin(playerid, 35);
				}
				case 11: {
				    SetPVarInt(playerid, "SelSkin", 12);
				    SetPlayerSkin(playerid, 36);
				}
				case 12: {
				    SetPVarInt(playerid, "SelSkin", 13);
				    SetPlayerSkin(playerid, 37);
				}
				case 13: {
				    SetPVarInt(playerid, "SelSkin", 14);
				    SetPlayerSkin(playerid, 96);
				}
				case 14: {
				    SetPVarInt(playerid, "SelSkin", 15);
				    SetPlayerSkin(playerid, 95);
				}
				case 15: {
				    SetPVarInt(playerid, "SelSkin", 16);
				    SetPlayerSkin(playerid, 142);
				}
				case 16: {
				    SetPVarInt(playerid, "SelSkin", 17);
				    SetPlayerSkin(playerid, 183);
				}
				case 17: {
			    	SetPVarInt(playerid, "SelSkin", 0);
				}
				default: {
			    	SetPVarInt(playerid, "SelSkin", 1);
					SetPlayerSkin(playerid, 14);
				}
 			}
 		}
		if(PlayerInfo[playerid][pSex] == 1) {
			switch(GetPVarInt(playerid, "SelSkin"))
			{
			    case 1: {
				    SetPVarInt(playerid, "SelSkin", 2);
					SetPlayerSkin(playerid, 13);
				}
			    case 2: {
				    SetPVarInt(playerid, "SelSkin", 3);
					SetPlayerSkin(playerid, 41);
				}
			    case 3: {
				    SetPVarInt(playerid, "SelSkin", 4);
					SetPlayerSkin(playerid, 56);
				}
			    case 4: {
				    SetPVarInt(playerid, "SelSkin", 5);
					SetPlayerSkin(playerid, 193);
				}
			    case 5: {
				    SetPVarInt(playerid, "SelSkin", 6);
					SetPlayerSkin(playerid, 90);
				}
			    case 6: {
				    SetPVarInt(playerid, "SelSkin", 7);
					SetPlayerSkin(playerid, 226);
				}
			    case 7: {
				    SetPVarInt(playerid, "SelSkin", 8);
					SetPlayerSkin(playerid, 195);
				}
				case 8: {
			    	SetPVarInt(playerid, "SelSkin", 0);
				}
				default: {
				    SetPVarInt(playerid, "SelSkin", 1);
					SetPlayerSkin(playerid, 193);
				}
 			}
 		}
 		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы примерили одежду на 20 секунд. Цена: {FFFFFF}1000 EXP");
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Чтобы купить выбранный скин пройдите на кассу");
		return 1;
 	}
 	
	if(pickupid == cloth[3])
	{
		if(fractionid > FRACTION_NONE) return SendClientMessage(playerid, -1, "Менять одежду можно только вне фракции");
 		if(GetPVarInt(playerid,"SkinSel") > gettime()){ return false; }
		SetPVarInt(playerid,"SkinSel",gettime() + 5);
		if(GetPVarInt(playerid, "SelSkin") == 0) return SendClientMessage(playerid, -1, "Сначала примерьте одежду");
  		if(GetPlayerScore(playerid) < 10000) return SendClientMessage(playerid, -1, ""COLOR_RED"Вам нужно {FFFFFF}10000 EXP"COLOR_RED" для покупки данной одежды");
  		if(GetPVarInt(playerid,"ShopSkin") != 2) return 1;
		Player.DownEXP(PlayerInfo[playerid][pID], 10000, E_BUY_SLOTHES, playerid);
		new selected;
		selected = GetPlayerSkin(playerid);
		if(selected == PlayerInfo[playerid][pSkin]) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы уже приобрели данную одежду");

		SetPlayerInt(playerid, "Skin", selected);
		PlayerInfo[playerid][pSkin] = selected;
		SetPVarInt(playerid, "SelSkin", 0);
		if(IsValidTimer(bskin[playerid])) KillTimer(bskin[playerid]),bskin[playerid] = -1;
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили одежду. Хорошего дня!");
 		return 1;
 	}
	if(pickupid == cloth[2])
	{
  		SetPVarInt(playerid,"ShopSkin",2);
	    if(IsValidTimer(bskin[playerid])) KillTimer(bskin[playerid]),bskin[playerid] = -1;
	    bskin[playerid] = SetTimerEx("CBackSkin", 20000, false, "d", playerid);
		if(fractionid > FRACTION_NONE) return SendClientMessage(playerid, -1, "Менять одежду можно только вне фракции");
 		if(GetPVarInt(playerid,"SkinSel") > gettime()){ return false; }
		SetPVarInt(playerid,"SkinSel",gettime() + 2);
		if(PlayerInfo[playerid][pSex] == 0) {
			switch(GetPVarInt(playerid, "SelSkin"))
			{
			    case 1: {
				    SetPVarInt(playerid, "SelSkin", 2);
					SetPlayerSkin(playerid, 264);
				}
			    case 2: {
				    SetPVarInt(playerid, "SelSkin", 3);
					SetPlayerSkin(playerid, 290);
				}
			    case 3: {
				    SetPVarInt(playerid, "SelSkin", 4);
					SetPlayerSkin(playerid, 291);
				}
			    case 4: {
				    SetPVarInt(playerid, "SelSkin", 5);
					SetPlayerSkin(playerid, 292);
				}
			    case 5: {
				    SetPVarInt(playerid, "SelSkin", 6);
					SetPlayerSkin(playerid, 293);
				}
			    case 6: {
				    SetPVarInt(playerid, "SelSkin", 7);
					SetPlayerSkin(playerid, 294);
				}
			    case 7: {
				    SetPVarInt(playerid, "SelSkin", 8);
					SetPlayerSkin(playerid, 46);
				}
			    case 8: {
				    SetPVarInt(playerid, "SelSkin", 9);
					SetPlayerSkin(playerid, 49);
				}
			    case 9: {
				    SetPVarInt(playerid, "SelSkin", 10);
					SetPlayerSkin(playerid, 59);
				}
				case 10: {
				    SetPVarInt(playerid, "SelSkin", 11);
				    SetPlayerSkin(playerid, 68);
				}
				case 11: {
				    SetPVarInt(playerid, "SelSkin", 12);
				    SetPlayerSkin(playerid, 82);
				}
				case 12: {
				    SetPVarInt(playerid, "SelSkin", 13);
				    SetPlayerSkin(playerid, 83);
				}
				case 13: {
				    SetPVarInt(playerid, "SelSkin", 14);
				    SetPlayerSkin(playerid, 84);
				}
				case 14: {
				    SetPVarInt(playerid, "SelSkin", 15);
				    SetPlayerSkin(playerid, 295);
				}
				case 15: {
				    SetPVarInt(playerid, "SelSkin", 16);
				    SetPlayerSkin(playerid, 296);
				}
				case 16: {
				    SetPVarInt(playerid, "SelSkin", 17);
				    SetPlayerSkin(playerid, 185);
				}
				case 17: {
				    SetPVarInt(playerid, "SelSkin", 18);
				    SetPlayerSkin(playerid, 186);
				}
				case 18: {
				    SetPVarInt(playerid, "SelSkin", 19);
				    SetPlayerSkin(playerid, 297);
				}
				case 19: {
				    SetPVarInt(playerid, "SelSkin", 20);
				    SetPlayerSkin(playerid, 119);
				}
				case 20: {
				    SetPVarInt(playerid, "SelSkin", 21);
				    SetPlayerSkin(playerid, 126);
				}
				case 21: {
				    SetPVarInt(playerid, "SelSkin", 22);
				    SetPlayerSkin(playerid, 167);
				}
				case 22: {
				    SetPVarInt(playerid, "SelSkin", 23);
				    SetPlayerSkin(playerid, 181);
				}
				case 23: {
				    SetPVarInt(playerid, "SelSkin", 24);
				    SetPlayerSkin(playerid, 203);
				}
				case 24: {
				    SetPVarInt(playerid, "SelSkin", 25);
				    SetPlayerSkin(playerid, 249);
				}
				case 25: {
			    	SetPVarInt(playerid, "SelSkin", 0);
				}
				default: {
			    	SetPVarInt(playerid, "SelSkin", 1);
					SetPlayerSkin(playerid, 299);
				}
 			}
 		}
		if(PlayerInfo[playerid][pSex] == 1) {
			switch(GetPVarInt(playerid, "SelSkin"))
	   	 	{
			    case 1: {
			    	SetPVarInt(playerid, "SelSkin", 2);
					SetPlayerSkin(playerid, 91);
				}
			    case 2: {
			    	SetPVarInt(playerid, "SelSkin", 3);
					SetPlayerSkin(playerid, 216);
				}
			    case 3: {
			    	SetPVarInt(playerid, "SelSkin", 0);
				}
				default: {
			    	SetPVarInt(playerid, "SelSkin", 1);
					SetPlayerSkin(playerid, 214);
				}
 			}
 		}
 		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы примерили одежду на 20 секунд. Цена: {FFFFFF}10000 EXP");
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Чтобы купить выбранный скин пройдите на кассу");
		return 1;
 	}
	if(pickupid == cloth[5])
	{
		if(fractionid > FRACTION_NONE) return SendClientMessage(playerid, -1, "Менять одежду можно только вне фракции");
 		if(GetPVarInt(playerid,"SkinSel") > gettime()){ return false; }
		SetPVarInt(playerid,"SkinSel",gettime() + 5);
		if(GetPVarInt(playerid, "SelSkin") == 0) return SendClientMessage(playerid, -1, "Сначала примерьте одежду");
  		if(GetPlayerScore(playerid) < 3000) return SendClientMessage(playerid, -1, ""COLOR_RED"Вам нужно {FFFFFF}3000 EXP"COLOR_RED" для покупки данной одежды");
  		if(GetPVarInt(playerid,"ShopSkin") != 3) return 1;
		Player.DownEXP(PlayerInfo[playerid][pID], 3000, E_BUY_SLOTHES, playerid);
		new selected;
		selected = GetPlayerSkin(playerid);
		if(selected == PlayerInfo[playerid][pSkin]) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы уже приобрели данную одежду");

		SetPlayerInt(playerid, "Skin", selected);
		PlayerInfo[playerid][pSkin] = selected;
		SetPVarInt(playerid, "SelSkin", 0);
		if(IsValidTimer(bskin[playerid])) KillTimer(bskin[playerid]),bskin[playerid] = -1;
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили одежду. Хорошего дня!");
 		return 1;
 	}

	if(pickupid == cloth[4])
	{
  		SetPVarInt(playerid,"ShopSkin",3);
	    if(IsValidTimer(bskin[playerid])) KillTimer(bskin[playerid]),bskin[playerid] = -1;
	    bskin[playerid] = SetTimerEx("CBackSkin", 20000, false, "d", playerid);
		if(fractionid > FRACTION_NONE) return SendClientMessage(playerid, -1, "Менять одежду можно только вне фракции");
 		if(GetPVarInt(playerid,"SkinSel") > gettime()){ return false; }
		SetPVarInt(playerid,"SkinSel",gettime() + 2);
		if(PlayerInfo[playerid][pSex] == 0) {
			switch(GetPVarInt(playerid, "SelSkin"))
	   	 	{
			    case 1: {
				    SetPVarInt(playerid, "SelSkin", 2);
					SetPlayerSkin(playerid, 19);
				}
			    case 2: {
				    SetPVarInt(playerid, "SelSkin", 3);
					SetPlayerSkin(playerid, 22);
				}
			    case 3: {
				    SetPVarInt(playerid, "SelSkin", 4);
					SetPlayerSkin(playerid, 28);
				}
			    case 4: {
				    SetPVarInt(playerid, "SelSkin", 5);
					SetPlayerSkin(playerid, 45);
				}
			    case 5: {
				    SetPVarInt(playerid, "SelSkin", 6);
					SetPlayerSkin(playerid, 73);
				}
			    case 6: {
				    SetPVarInt(playerid, "SelSkin", 7);
					SetPlayerSkin(playerid, 170);
				}
				case 7: {
				    SetPVarInt(playerid, "SelSkin", 8);
					SetPlayerSkin(playerid, 143);
				}
			    case 8: {
				    SetPVarInt(playerid, "SelSkin", 9);
					SetPlayerSkin(playerid, 144);
				}
			    case 9: {
				    SetPVarInt(playerid, "SelSkin", 10);
					SetPlayerSkin(playerid, 258);
				}
				case 10: {
				    SetPVarInt(playerid, "SelSkin", 11);
				    SetPlayerSkin(playerid, 97);
				}
				case 11: {
				    SetPVarInt(playerid, "SelSkin", 12);
				    SetPlayerSkin(playerid, 184);
				}
				case 12: {
				    SetPVarInt(playerid, "SelSkin", 13);
				    SetPlayerSkin(playerid, 67);
				}
				case 13: {
				    SetPVarInt(playerid, "SelSkin", 14);
				    SetPlayerSkin(playerid, 180);
				}
				case 14: {
				    SetPVarInt(playerid, "SelSkin", 15);
				    SetPlayerSkin(playerid, 24);
				}
				case 15: {
				    SetPVarInt(playerid, "SelSkin", 16);
				    SetPlayerSkin(playerid, 177);
				}
				case 16: {
				    SetPVarInt(playerid, "SelSkin", 17);
				    SetPlayerSkin(playerid, 176);
				}
				case 17: {
				    SetPVarInt(playerid, "SelSkin", 18);
				    SetPlayerSkin(playerid, 18);
				}
				case 18: {
				    SetPVarInt(playerid, "SelSkin", 19);
				    SetPlayerSkin(playerid, 24);
				}
				case 19: {
			    	SetPVarInt(playerid, "SelSkin", 0);
				}
				default: {
				    SetPVarInt(playerid, "SelSkin", 1);
					SetPlayerSkin(playerid, 7);
				}
 			}
 		}
		if(PlayerInfo[playerid][pSex] == 1) {
			switch(GetPVarInt(playerid, "SelSkin"))
		    {
			    case 1: {
				    SetPVarInt(playerid, "SelSkin", 2);
					SetPlayerSkin(playerid, 55);
				}
			    case 2: {
				    SetPVarInt(playerid, "SelSkin", 3);
					SetPlayerSkin(playerid, 40);
				}
			    case 3: {
				    SetPVarInt(playerid, "SelSkin", 4);
					SetPlayerSkin(playerid, 192);
				}
			    case 4: {
			    	SetPVarInt(playerid, "SelSkin", 0);
				}
				default: {
			    	SetPVarInt(playerid, "SelSkin", 1);
					SetPlayerSkin(playerid, 69);
				}
 			}
 		}
 		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы примерили одежду на 20 секунд. Цена: {FFFFFF}3000 EXP");
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Чтобы купить выбранный скин пройдите на кассу");
		return 1;
 	}
	if(pickupid == cloth[7])
	{
		if(fractionid > FRACTION_NONE) return SendClientMessage(playerid, -1, "Менять одежду можно только вне фракции");
 		if(GetPVarInt(playerid,"SkinSel") > gettime()){ return false; }
		SetPVarInt(playerid,"SkinSel",gettime() + 5);
		if(GetPVarInt(playerid, "SelSkin") == 0) return SendClientMessage(playerid, -1, "Сначала примерьте одежду");
  		if(GetPVarInt(playerid,"ShopSkin") != 4) return 1;
  		if(CheckCash(playerid, 5000) == false) return 1;
		Player.DownEXP(PlayerInfo[playerid][pID], 5000, E_BUY_SLOTHES, playerid);
		new selected;
		selected = GetPlayerSkin(playerid);
		if(selected == PlayerInfo[playerid][pSkin]) return SendClientMessage(playerid, -1, ""COLOR_RED"Вы уже приобрели данную одежду");

		SetPlayerInt(playerid, "Skin", selected);
		PlayerInfo[playerid][pSkin] = selected;
		SetPVarInt(playerid, "SelSkin", 0);
		if(IsValidTimer(bskin[playerid])) KillTimer(bskin[playerid]),bskin[playerid] = -1;
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили одежду. Хорошего дня!");
 		return 1;
 	}

	if(pickupid == cloth[6])
	{
	    SetPVarInt(playerid,"ShopSkin",4);
	    if(IsValidTimer(bskin[playerid])) KillTimer(bskin[playerid]),bskin[playerid] = -1;
	    bskin[playerid] = SetTimerEx("CBackSkin", 20000, false, "d", playerid);
		if(fractionid > FRACTION_NONE) return SendClientMessage(playerid, -1, "Менять одежду можно только вне фракции");
 		if(GetPVarInt(playerid,"SkinSel") > gettime()){ return false; }
		SetPVarInt(playerid,"SkinSel",gettime() + 2);
		if(PlayerInfo[playerid][pSex] == 0) {
			switch(GetPVarInt(playerid, "SelSkin"))
			{
			    case 1: {
				    SetPVarInt(playerid, "SelSkin", 2);
					SetPlayerSkin(playerid, 17);
				}
			    case 2: {
				    SetPVarInt(playerid, "SelSkin", 3);
					SetPlayerSkin(playerid, 20);
				}
			    case 3: {
				    SetPVarInt(playerid, "SelSkin", 4);
					SetPlayerSkin(playerid, 156);
				}
			    case 4: {
				    SetPVarInt(playerid, "SelSkin", 5);
					SetPlayerSkin(playerid, 23);
				}
			    case 5: {
				    SetPVarInt(playerid, "SelSkin", 6);
					SetPlayerSkin(playerid, 29);
				}
			    case 6: {
				    SetPVarInt(playerid, "SelSkin", 7);
					SetPlayerSkin(playerid, 33);
				}
			    case 7: {
				    SetPVarInt(playerid, "SelSkin", 8);
					SetPlayerSkin(playerid, 47);
				}
			    case 8: {
				    SetPVarInt(playerid, "SelSkin", 9);
					SetPlayerSkin(playerid, 48);
				}
			    case 9: {
				    SetPVarInt(playerid, "SelSkin", 10);
					SetPlayerSkin(playerid, 60);
				}
				case 10: {
				    SetPVarInt(playerid, "SelSkin", 11);
				    SetPlayerSkin(playerid, 101);
				}
				case 11: {
				    SetPVarInt(playerid, "SelSkin", 12);
				    SetPlayerSkin(playerid, 241);
				}
				case 12: {
				    SetPVarInt(playerid, "SelSkin", 13);
				    SetPlayerSkin(playerid, 242);
				}
				case 13: {
			    	SetPVarInt(playerid, "SelSkin", 0);
				}
				default: {
			    	SetPVarInt(playerid, "SelSkin", 1);
					SetPlayerSkin(playerid, 250);
				}
 			}
 		}
		if(PlayerInfo[playerid][pSex] == 1) {
			switch(GetPVarInt(playerid, "SelSkin"))
		    {
			    case 1: {
				    SetPVarInt(playerid, "SelSkin", 2);
					SetPlayerSkin(playerid, 12);
				}
			    case 2: {
				    SetPVarInt(playerid, "SelSkin", 3);
					SetPlayerSkin(playerid, 93);
				}
			    case 3: {
			    	SetPVarInt(playerid, "SelSkin", 4);
					SetPlayerSkin(playerid, 233);
				}
			    case 4: {
			    	SetPVarInt(playerid, "SelSkin", 0);
				}
				default: {
				    SetPVarInt(playerid, "SelSkin", 1);
					SetPlayerSkin(playerid, 190);
				}
 			}
 		}
 		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы примерили одежду на 20 секунд. Цена: {FFFFFF}5000 EXP");
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Чтобы купить выбранный скин пройдите на кассу");
		return 1;
 	}
	if(pickupid == bank[0])
 	{
		SetPlayerPos(playerid, 1398.5032,-1679.8954,13.5911);
		SetPlayerInterior(playerid, 1);
		SetPlayerFacingAngle(playerid, 180);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == bank[1])
 	{
		SetPlayerPos(playerid, 1413.1415,-1700.5734,13.5395);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, 240);
		SetCameraBehindPlayer(playerid);
		return 1;
    }
	if(pickupid == bank[2])
 	{
 		SPD(playerid, dBank, DIALOG_STYLE_INPUT,"Банковское отделение","{FFFFFF}1. Снять средства\n2. Положить средства\n3. Пополнить счет мобильного\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Выбрать", "Закрыть");
		PlayerPlaySound(playerid, 4203, 0, 0, 0);
  		format(small_string, sizeof(small_string), ""COLOR_GREEN"Добро пожаловать! Ваш банковский баланс: {FFFFFF} %d EXP", PlayerInfo[playerid][pBank]);
	    SendClientMessage(playerid, -1, small_string);
	    return 1;
    }
	if(pickupid == bank[3])
 	{
 	    if(IsPlayerInHouse(playerid) == true) {
	 	    new 
	 	    	arrayID = GetPlayerHouse(playerid),
	 	    	rent_day = HouseInfo[arrayID][E_HOUSE_RENT_DAY];

	 	    if(rent_day >= 7) { 
	 	    	format(small_string, sizeof(small_string), "~b~DAYS: ~w~%d~n~~r~MAXIMUM", rent_day); 
	 	    	GameTextForPlayer(playerid, small_string, 2500, 4); 
	 	    	return 1;
	 	    }

	 	    new tax;
			switch(HouseInfo[arrayID][E_HOUSE_CLASS] - 1) {
				case 0: tax = 75;
				case 1: tax = 100;
				case 2: tax = 150;
				case 3: tax = 200;
				case 4: tax = 250;
				case 5: tax = 300;
			}
			if(GetPlayerEXP(playerid) < tax) {
				format(small_string, sizeof(small_string),
					""COLOR_RED"Вам нужно {FFFFFF}%d EXP"COLOR_RED" для оплаты жилья на сутки", 
						tax
				);
				SendClientMessage(playerid, -1, small_string);
			    format(small_string, sizeof(small_string), 
			    	"~b~DAYS: ~w~%d", 
			    		rent_day
			    );
			    GameTextForPlayer(playerid, small_string, 2500, 4);
			    return 1;
		    }
		    if(CheckCash(playerid, tax) == false) return 1;
			Player.DownEXP(PlayerInfo[playerid][pID], tax, E_RENTTIME_HOUSE, playerid);
			House.UpRentDay(arrayID);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы оплатили свое жилье на одни сутки");
		    format(small_string, sizeof(small_string), "~r~-%d EXP~n~~b~DAYS: ~w~%d", tax, rent_day++);
		    return GameTextForPlayer(playerid, small_string, 2500, 4);
		} else {
			return SendClientMessage(playerid, -1, ""COLOR_ORANGE"В данном окне принимается квартплата. У вас нет дома");
		}
    }
	if(pickupid == bank[4])
	{
		return 1;
    }
	return 1;
}
forward GangWar();
public GangWar() {
	if(IsCapture == 1 && ZoneCapture != -1) { GzCheck(ZoneCapture); return SetTimer("GangWar", 1000, 0); }
	return 1;
}
public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	if(Dealer_OnPlayerEnterDynamicCP(playerid, checkpointid) == 1) return 1;
	if(Porter_OnPlayerEnterDynamicCP(playerid, checkpointid) == 1) return 1;
	if(Saloon_OnPlayerEnterDynamicCP(playerid, checkpointid) == 1) return 1;

	if(CallLocalFunction("Gps_OnPlayerEnterDynamicCP", "ii", playerid, checkpointid) == 1) {
		return 1;
	}

	if(checkpointid >= ATM[0] && checkpointid <= ATM[49])
 	{
 		SPD(playerid, dBank, DIALOG_STYLE_INPUT,"Банкомат","{FFFFFF}1. Снять средства\n2. Положить средства\n3. Пополнить счет мобильного\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Выбрать", "Закрыть");
		PlayerPlaySound(playerid, 4203, 0, 0, 0);
  		format(small_string, sizeof(small_string), ""COLOR_GREEN"Ваш банковский баланс: {FFFFFF} %d EXP", PlayerInfo[playerid][pBank]);
	    SendClientMessage(playerid, -1, small_string);
	    return 1;
 	}
 	if(checkpointid >= farm_checkpoint[0] && checkpointid <= farm_checkpoint[4]) {
		if(GetPVarInt(playerid, "tempjob") == 1) {
	        if(IsValidTimer(farming[playerid])) KillTimer(farming[playerid]),farming[playerid] = -1;
		    if(GetPVarInt(playerid, "Pizdui") == 0) return 1;
		    for(new i = 0; i < sizeof(farm_checkpoint); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint[i], false);
			}
			for(new i = 0; i < sizeof(farm_checkpoint_1); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint_1[i], false);
			}
			for(new i = 0; i < sizeof(farm_checkpoint_2); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint_2[i], false);
			}
		    farming[playerid] = SetTimerEx("CFarm", 10000, false, "d", playerid);
		    ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,1,1,1,1,0);
		    SendClientMessage(playerid, -1, "Подождите 10 секунд...");
		    SetPVarInt(playerid, "MinusTime", 10);
	    }
	    return 1;
 	}
 	if(checkpointid >= farm_checkpoint_1[0] && checkpointid <= farm_checkpoint_1[4]) {
	 	if(GetPVarInt(playerid, "tempjob") == 1) {
	        if(IsValidTimer(farming[playerid])) KillTimer(farming[playerid]),farming[playerid] = -1;
		    if(GetPVarInt(playerid, "Pizdui") == 0) return 1;
		    for(new i = 0; i < sizeof(farm_checkpoint); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint[i], false);
			}
			for(new i = 0; i < sizeof(farm_checkpoint_1); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint_1[i], false);
			}
			for(new i = 0; i < sizeof(farm_checkpoint_2); i++) {
				TogglePlayerDynamicCP(playerid, farm_checkpoint_2[i], false);
			}
		    farming[playerid] = SetTimerEx("CFarm", 10000, false, "d", playerid);
		    ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,1,1,1,1,0);
		    SendClientMessage(playerid, -1, "Подождите 10 секунд...");
		    SetPVarInt(playerid, "MinusTime", 10);
	    }
	    return 1;
 	}
 	for(new f = 0; f < sizeof(farm_checkpoint_2); f++) {
 		if(farm_checkpoint_2[f] == checkpointid) {
 			if(GetPVarInt(playerid, "tempjob") == 1) {
		        if(IsValidTimer(farming[playerid])) KillTimer(farming[playerid]),farming[playerid] = -1;
			    if(GetPVarInt(playerid, "Pizdui") == 0) return 1;
			   
			    for(new i = 0; i < sizeof(farm_checkpoint); i++) {
					TogglePlayerDynamicCP(playerid, farm_checkpoint[i], false);
				}
				for(new i = 0; i < sizeof(farm_checkpoint_1); i++) {
					TogglePlayerDynamicCP(playerid, farm_checkpoint_1[i], false);
				}
				for(new i = 0; i < sizeof(farm_checkpoint_2); i++) {
					TogglePlayerDynamicCP(playerid, farm_checkpoint_2[i], false);
				}

			    farming[playerid] = SetTimerEx("CFarm", 10000, false, "d", playerid);
			    ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,1,1,1,1,0);
			    SendClientMessage(playerid, -1, "Подождите 10 секунд...");
			    SetPVarInt(playerid, "MinusTime", 10);
		    }
		    return 1;
 		}
 	}
 	if(checkpointid >= stealcar_checkpoint[0] && checkpointid <= stealcar_checkpoint[2]) {
	 	if(ThefStatus[playerid] == 2)
		{
		    new tmpcar = GetPlayerVehicleID(playerid);
		    if(GetVehicleModel(tmpcar) != TCar[playerid]) return SendClientMessage(playerid, -1, ""COLOR_RED"Это не та машина, которую мы заказывали!");
			foreach(new i: Player) {
	
				new price;

				if(IsANope(tmpcar))
				{
					price = RandomEx(75, 125);
				 	format(small_string, sizeof(small_string), ""COLOR_GREEN"Неплохое ведро, держи: {FFFFFF}%d EXP", price);
					SendClientMessage(playerid, -1, small_string);
				}
				if(IsAB(tmpcar))
				{
					price = RandomEx(180, 240);
				 	format(small_string, sizeof(small_string), ""COLOR_GREEN"То что нужно, получай: {FFFFFF}%d EXP", price);
					SendClientMessage(playerid, -1, small_string);
				}
				if(IsAA(tmpcar))
				{
					price = RandomEx(250, 500);
				 	format(small_string, sizeof(small_string), ""COLOR_GREEN"Отличная тачка, вот твои: {FFFFFF}%d EXP", price);
					SendClientMessage(playerid, -1, small_string);
				}
			    
			    Player.AddEXP(PlayerInfo[playerid][pID], price, E_JOB_THEFT_AUTO, playerid);
				DecreaseKarma(playerid);
				
				TimeTCar[playerid] = 0;
				//SetVehicleToRespawn(tmpcar);
				ThefStatus[playerid] = 0;
				TCar[playerid] = 0;
				for(new b = 0; b < sizeof(stealcar_checkpoint); b++) {
					TogglePlayerDynamicCP(playerid, stealcar_checkpoint[b], false);
				}
				return 1;
			}
		}
		return 1;
	}
	if(checkpointid >= mafia_checkpoint[0] && checkpointid <= mafia_checkpoint[5]) {
		if(carry[playerid] > -1) {
			carry[playerid] = -1;

			for(new i = 0; i < sizeof(mafia_checkpoint); i++) {
				TogglePlayerDynamicCP(playerid, mafia_checkpoint[i], false);
			}

	 		new Got = RandomEx(75, 300);
			switch(random(3)) {
				case 0:
				{
				 	format(small_string, sizeof(small_string), ""COLOR_ORANGE"Сделка состоялась вовремя. Вы заработали: {FFFFFF}%d EXP", Got);
					SendClientMessage(playerid, -1, small_string);
					Player.AddEXP(PlayerInfo[playerid][pID], Got, E_GOOD_DEAL, playerid);
					DecreaseKarma(playerid);
					DeletePVar(playerid, "robbery_time");
					return 1;
				}
				case 1: {
					SendClientMessage(playerid, -1, ""COLOR_RED"Сделка провалена. Ваш клиент не привез деньги");
					DecreaseKarma(playerid);
					DeletePVar(playerid, "robbery_time");
				}
				case 2:
				{
					Got = RandomEx(75, 100);
				 	format(small_string, sizeof(small_string), ""COLOR_ORANGE"Сделка состоялась вовремя. Вы заработали: {FFFFFF}%d EXP", Got);
					SendClientMessage(playerid, -1, small_string);
					Player.AddEXP(PlayerInfo[playerid][pID], Got, E_GOOD_DEAL, playerid);
					DecreaseKarma(playerid);
					DeletePVar(playerid, "robbery_time");
					return 1;
				}
			}
		}
		return 1;
	}
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA areaid) {
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) return 0;
	if(CallLocalFunction("Casino_OnPlayerEnterDynArea", "ii", playerid, areaid) == 1) return 1;
	if(CallLocalFunction("AT_OnPlayerEnterDynArea", "ii", playerid, areaid) == 1) return 1;
	return 1;
}

public OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA areaid) {
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) return 0;
	if(CallLocalFunction("Casino_OnPlayerLeaveDynArea", "ii", playerid, areaid) == 1) return 1;
	if(CallLocalFunction("Army_OnPlayerLeaveDynArea", "ii", playerid, areaid) == 1) return 1;
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	if(IsPlayerInAnyVehicle(playerid) == 0) {
		return 1;
	}

	switch(UnloadFarm[playerid]) {
	    case 1: {
			new vehicle;
			vehicle = GetPlayerVehicleID(playerid);
			if(vehicle == HARVEST_CAR[0]) SetPlayerRaceCheckpoint(playerid, 1,-294.1775,-1412.4579,12.8644,-294.1775,-1412.4579,12.8644,5);
			if(vehicle == HARVEST_CAR[1]) SetPlayerRaceCheckpoint(playerid, 1,-306.8991,-1344.1766,8.3550,-306.8991,-1344.1766,8.3550,5);
			if(vehicle == HARVEST_CAR[2]) SetPlayerRaceCheckpoint(playerid, 1,-249.8366,-1376.5028,10.2615,-249.8366,-1376.5028,10.2615,5);
			UnloadFarm[playerid]++;
		    SetPlayerChatBubble(playerid, "доставил(а) сырье на обработку", C_PURPLE, 30.0, 5000);
			format(small_string, 100, "%s доставил(а) сырье на обработку", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
			SendClientMessage(playerid, -1, ""COLOR_ORANGE"Возвращайтесь и разделите прибыль с работниками");
			return 1;
		}
		case 2: {
			new Float:X,Float:Y,Float:Z;
			GetPlayerPos(playerid, X,Y,Z);
			new vehicle;
			vehicle = GetPlayerVehicleID(playerid);
			TOTAL_DRUGS += 60;
			update_drug_text();

			if(vehicle == HARVEST_CAR[0])	Harvest[0] = 0;
			if(vehicle == HARVEST_CAR[1])	Harvest[1] = 0;
			if(vehicle == HARVEST_CAR[2])	Harvest[2] = 0;

			ReloadFarmText();


			UnloadFarm[playerid] = -1;
			SetVehicleToRespawn(vehicle);
			DisablePlayerRaceCheckpoint(playerid);
			new pay = RandomEx(25, 75);
			foreach(new i: Player) {
				if(GetPVarInt(i, "tempjob") == 1) {
					if(IsPlayerInRangeOfPoint(i, 15, X, Y, Z)) {
						Player.AddEXP(PlayerInfo[i][pID], pay, E_FARM_PREMIUM, i);
						format(small_string, 100, ""COLOR_BLUE"Фургон разгружен. Ваша премия: {FFFFFF}+%d EXP", pay*2);
						SendClientMessage(i, -1, small_string);
					}
				}
			}
			return 1;
		}
	}
	switch(RouteFarm[playerid]) {
		case 1: return SetPlayerRaceCheckpoint(playerid, 0,-275.9756,-1416.3439,10.9044,-213.5012,-1405.0016,5.9683,10), RouteFarm[playerid] += 1; // combine
		case 2: return SetPlayerRaceCheckpoint(playerid, 0,-213.5012,-1405.0016,5.9683,-193.6143,-1382.0881,4.7299,10), RouteFarm[playerid] += 1; // combine
		case 3: return SetPlayerRaceCheckpoint(playerid, 0,-193.6143,-1382.0881,4.7299,-246.4743,-1362.7891,9.0994,10), RouteFarm[playerid] += 1; // combine
		case 4: return SetPlayerRaceCheckpoint(playerid, 0,-246.4743,-1362.7891,9.0994,-282.0067,-1368.1895,9.1771,10), RouteFarm[playerid] += 1; // combine
		case 5: return SetPlayerRaceCheckpoint(playerid, 0,-282.0067,-1368.1895,9.1771,-315.0952,-1332.1112,8.4617,10), RouteFarm[playerid] += 1; // combine
		case 6: return SetPlayerRaceCheckpoint(playerid, 0,-315.0952,-1332.1112,8.4617,-289.3944,-1326.7306,7.9310,10), RouteFarm[playerid] += 1; // combine
		case 7: return SetPlayerRaceCheckpoint(playerid, 0,-289.3944,-1326.7306,7.9310,-244.2876,-1321.6423,9.3308,10), RouteFarm[playerid] += 1; // combine
		case 8: return SetPlayerRaceCheckpoint(playerid, 0,-244.2876,-1321.6423,9.3308,-200.8287,-1340.5165,8.6160,10), RouteFarm[playerid] += 1; // combine
		case 9: return SetPlayerRaceCheckpoint(playerid, 0,-200.8287,-1340.5165,8.6160,-189.9037,-1372.4922,4.3427,10), RouteFarm[playerid] += 1; // combine
		case 10: return SetPlayerRaceCheckpoint(playerid, 0,-189.9037,-1372.4922,4.3427,-187.2960,-1404.8115,3.3137,10), RouteFarm[playerid] += 1; // combine
		case 11: return SetPlayerRaceCheckpoint(playerid, 0,-187.2960,-1404.8115,3.3137,-217.4142,-1402.9197,6.6611,10), RouteFarm[playerid] += 1; // combine
		case 12: return SetPlayerRaceCheckpoint(playerid, 0,-217.4142,-1402.9197,6.6611,-283.1469,-1393.8297,10.4023,10), RouteFarm[playerid] += 1; // combine
		case 13: return SetPlayerRaceCheckpoint(playerid, 0,-283.1469,-1393.8297,10.4023,-376.5204,-1446.3860,25.2918,10), RouteFarm[playerid] += 1; // combine
		case 14: return SetPlayerRaceCheckpoint(playerid, 1,-376.5204,-1446.3860,25.2918,-376.5204,-1446.3860,25.2918,10), RouteFarm[playerid] += 1; // combine
		case 15: {
			new vehicle;
			vehicle = GetPlayerVehicleID(playerid);
			SetVehicleToRespawn(vehicle);
			DisablePlayerRaceCheckpoint(playerid);
			new pay = RandomEx(45, 105);
		    Player.AddEXP(PlayerInfo[playerid][pID], pay, E_JOB_COMBAINE, playerid);
			format(small_string, 100, ""COLOR_BLUE"Поле засеяно. Ваша премия: {FFFFFF}+%d EXP", pay);
			SendClientMessage(playerid, -1, small_string);
			HarvestAmount += 600;
		 	return RouteFarm[playerid] = -1;
		}
	}
	if(RouteTrash[playerid]  == 6) {
		new vehicle;
		vehicle = GetPlayerVehicleID(playerid);
		DisablePlayerRaceCheckpoint(playerid);
		new pay = RandomEx(80, 115);
	    Player.AddEXP(PlayerInfo[playerid][pID], pay, E_JOB_DRIVER_TRASH, playerid);
		format(small_string, 100, ""COLOR_BLUE"Мусоровоз разгружен. Ваша зарплата: {FFFFFF}+%d EXP", pay);
		SendClientMessage(playerid, -1, small_string);
		SetVehicleToRespawn(vehicle);
		RouteTrash[playerid] = -1;
		return 1;
	}
	if(RouteTrash[playerid] > 0) {
		TogglePlayerControllable(playerid, 0);
		DisablePlayerRaceCheckpoint(playerid);
		SendClientMessage(playerid, -1, ""COLOR_RED"Подождите 10 секунд...");
		SetPVarInt(playerid, "MinusTime", 10);
		BinTimer[playerid] = KillTimer(BinTimer[playerid]); 
		return BinTimer[playerid] = SetTimerEx("SelectBin", 10000, false, "i", playerid);
	}
	switch(ArmyMission[playerid])
	{
	    case 0: return SetPlayerRaceCheckpoint(playerid, 1, 328.5100,1963.1115,17.6406, 328.5100,1963.1115,17.6406, 5);
	    case 1: {
		    SendClientMessage(playerid, -1, ""COLOR_BLUE"Началась загрузка боеприпасов. Подождите немного...");
			DisablePlayerRaceCheckpoint(playerid);
			SetPVarInt(playerid, "MinusTime", 10);
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			return routetimer[playerid] = SetTimerEx("WareStop", 10000, 0, "i", playerid);
	    }
		case 2: {
			ArmyMission[playerid] = 0;
			SendClientMessage(playerid, -1, ""COLOR_BLUE"Вы доставили военный груз и получили{FFFFFF} +100 EXP");
			DisablePlayerRaceCheckpoint(playerid);
		    Player.AddEXP(PlayerInfo[playerid][pID], 100, E_JOB_CAR_ARMY, playerid);
			return IncreaseKarma(playerid);
		}
	}
	switch(RouteAir2[playerid])
	{
		case 0: return SetPlayerRaceCheckpoint(playerid, 1, 1914.4653,-2328.6389,13.1067, 1914.4653,-2328.6389,13.1067, 20);
		case 1: {
			Runway[1] = 1;
			SetTimerEx("RunwayUpdate", 60_000, false, "i", 1);
			SetPVarInt(playerid, "MinusTime", 60);
			DisablePlayerRaceCheckpoint(playerid);
			SendClientMessage(playerid, -1, "Происходит посадка пассажиров. Подождите 60 секунд...");
			format(small_string, 100, "Пилот %s: Началась посадка на рейс Los Santos - Las Venturas", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, 50, C_PURPLE, small_string);
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			return routetimer[playerid] = SetTimerEx("AirStop2", 60000, 0, "i", playerid);
		}
		case 2: {
			SetPlayerRaceCheckpoint(playerid, 2, 1969.8719,-2493.8650,13.1128, 2108.6331,-2540.6863,13.1079, 20);
			RouteAir2[playerid] = 3;
			return 1;
		}
		case 3: {
			SetPlayerRaceCheckpoint(playerid, 2, 2108.6331,-2540.6863,13.1079, 1938.3038,-2593.4692,13.1112, 20);
			RouteAir2[playerid] = 4; //vzlet

			return 1;
		}
		case 4: {
			SetPlayerRaceCheckpoint(playerid, 2, 1938.3038,-2593.4692,13.1112, 1786.9944,-2593.3850,13.1204, 20);
			RouteAir2[playerid] = 5; //vzlet

			return 1;
		}
		case 5: {
			SetPlayerRaceCheckpoint(playerid, 2, 1786.9944,-2593.3850,13.1204, 1496.7401,1013.8691,163.2980, 20);
			RouteAir2[playerid] = 6; //welcome
			return 1;
		}
		case 6: {
			SetPlayerRaceCheckpoint(playerid, 5, 1496.7401,1013.8691,163.2980, 1477.4979,1324.4023,10.9944, 50);
			RouteAir2[playerid] = 7;
			format(small_string, 100, "Пилот %s: Вылетает рейс Los Santos - Las Venturas", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, 75, C_PURPLE, small_string);

			return 1;
		}
		case 7: {
			SetPlayerRaceCheckpoint(playerid, 2, 1477.4979,1324.4023,10.9944, 1507.5469,1463.4788,10.4105, 20);
			RouteAir2[playerid] = 8;
			return 1;
		}
		case 8: {
			format(small_string, 100, "Пилот %s: Прибывает рейс Las Venturas - Los Santos", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, 75, C_PURPLE, small_string);
			Runway[0] = 1;
			SetTimerEx("RunwayUpdate", 30_000, false, "i", 0);
			SetPVarInt(playerid, "MinusTime", 30);
			DisablePlayerRaceCheckpoint(playerid);
			SendClientMessage(playerid, -1, "Происходит высадка пассажиров. Подождите 30 секунд...");
			format(small_string, 100, "Пилот %s: Началась высадка с рейса Los Santos - Las Venturas", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, 50, C_PURPLE, small_string);
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			return routetimer[playerid] = SetTimerEx("AirStop2", 30000, 0, "i", playerid);
		}
		case 9: {
			SetPlayerRaceCheckpoint(playerid, 2, 1609.3046,1634.0345,10.3938, 1609.3046,1634.0345,10.3938, 20);
			RouteAir2[playerid] = 10; // go
			return 1;
		}
 		case 10: {
			DisablePlayerRaceCheckpoint(playerid);
			RouteAir2[playerid] = 0;
			new vehicle;
			vehicle = GetPlayerVehicleID(playerid);
			SetVehicleToRespawn(vehicle);
			PlayerInfo[playerid][pAirSkill] += 2;
			SetPlayerInt(playerid, "AirSkill", PlayerInfo[playerid][pAirSkill]);
		    new
		    	xmc,
		    	AirSkill = PlayerInfo[playerid][pAirSkill];

		    if((0 <= AirSkill <= 24)) {
				xmc = 100;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык пилота: {FFFFFF} %d/25", PlayerInfo[playerid][pAirSkill]);
			} else if((25 <= AirSkill <= 49)) {
		    	xmc = 125;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык пилота: {FFFFFF} %d/50", PlayerInfo[playerid][pAirSkill]);
			} else if((50 <= AirSkill <= 99)) {
		    	xmc = 150;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык пилота: {FFFFFF} %d/100", PlayerInfo[playerid][pAirSkill]);
			} else if((100 <= AirSkill <= 199)) {
		    	xmc = 200;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык пилота: {FFFFFF} %d/200", PlayerInfo[playerid][pAirSkill]);
			} else if((200 <= AirSkill <= 499)) {
				xmc = 250;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык пилота: {FFFFFF} %d/500", PlayerInfo[playerid][pAirSkill]);
			} else {
				xmc = 450;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык пилота: {FFFFFF} Максимум");
    		}
		    SendClientMessage(playerid, -1, small_string);
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"Рейс завершен. Зарплата: {FFFFFF}+%d EXP", xmc);
		    SendClientMessage(playerid, -1, small_string);
		    Player.AddEXP(PlayerInfo[playerid][pID], xmc, E_JOB_PILOT, playerid);
			return 1;
		}
	}
	switch(RouteAir[playerid])
	{
		case 0: SetPlayerRaceCheckpoint(playerid, 2, 1511.0432,1464.4716,10.4179, 1511.0432,1464.4716,10.4179, 20);
		case 1: {
			Runway[0] = 1;
			SetTimerEx("RunwayUpdate", 60_000, false, "i", 0);
			SetPVarInt(playerid, "MinusTime", 60);
			DisablePlayerRaceCheckpoint(playerid);
			SendClientMessage(playerid, -1, "Происходит посадка пассажиров. Подождите 60 секунд...");
			format(small_string, 100, "Пилот %s: Началась посадка на рейс Las Venturas - Los Santos", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, 50, C_PURPLE, small_string);
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			return routetimer[playerid] = SetTimerEx("AirStop", 60000, 0, "i", playerid);
		}
		case 2: {
			SetPlayerRaceCheckpoint(playerid, 2, 1477.5396,1639.9655,10.3705, 1388.8741,1643.4702,10.3700, 20);
			RouteAir[playerid] = 3;
			return 1;
		}
		case 3: {
			SetPlayerRaceCheckpoint(playerid, 3, 1388.8741,1643.4702,10.3700, 1149.6260,-2403.6128,166.2656, 20);
			RouteAir[playerid] = 4; //vzlet

			return 1;
		}
		case 4: {
			SetPlayerRaceCheckpoint(playerid, 3, 1149.6260,-2403.6128,166.2656, 1498.1334,-2493.9873,13.1282, 20);
			RouteAir[playerid] = 5; //vzlet

			return 1;
		}
		case 5: {
			SetPlayerRaceCheckpoint(playerid, 3, 1498.1334,-2493.9873,13.1282, 1689.8115,-2493.7966,13.1170, 20);
			RouteAir[playerid] = 6; //welcome
			format(small_string, 100, "Пилот %s: Вылетает рейс Las Venturas - Los Santos", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, 75, C_PURPLE, small_string);

			return 1;
		}
		case 6: {
			SetPlayerRaceCheckpoint(playerid, 2, 1689.8115,-2493.7966,13.1170, 1914.4653,-2328.6389,13.1067, 20);
			RouteAir[playerid] = 7;
			format(small_string, 100, "Пилот %s: Прибывает рейс Las Venturas - Los Santos", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, 75, C_PURPLE, small_string);
			return 1;
		}
		case 7: {
			SetPlayerRaceCheckpoint(playerid, 2, 1914.4653,-2328.6389,13.1067, 1914.4653,-2328.6389,13.1067, 20);
			RouteAir[playerid] = 8;
			return 1;
		}
		case 8: {
		    Runway[1] = 1;
		    SetTimerEx("RunwayUpdate", 30_000, false, "i", 1);
		    SetPVarInt(playerid, "MinusTime", 30);
			DisablePlayerRaceCheckpoint(playerid);
			SendClientMessage(playerid, -1, "Происходит высадка пассажиров. Подождите 30 секунд...");
			format(small_string, 100, "Пилот %s: Началась высадка с рейса Las Venturas - Los Santos", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, 50, C_PURPLE, small_string);
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			return routetimer[playerid] = SetTimerEx("AirStop", 30000, 0, "i", playerid);
		}
		case 9: {
			SetPlayerRaceCheckpoint(playerid, 1, 1922.8334,-2249.4912,13.1084, 1922.8334,-2249.4912,13.1084, 20);
			RouteAir[playerid] = 10; // go
			return 1;
		}
 		case 10: {
			DisablePlayerRaceCheckpoint(playerid);
			RouteAir[playerid] = 0;
			new vehicle;
			vehicle = GetPlayerVehicleID(playerid);
			SetVehicleToRespawn(vehicle);
			PlayerInfo[playerid][pAirSkill] += 2;
			SetPlayerInt(playerid, "AirSkill", PlayerInfo[playerid][pAirSkill]);
		    new
		    	xmc,
		    	AirSkill = PlayerInfo[playerid][pAirSkill];
			if((0 <= AirSkill <= 24)) {
				xmc = 100;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык пилота: {FFFFFF} %d/25", PlayerInfo[playerid][pAirSkill]);
			} else if((25 <= AirSkill <= 49)) {
		    	xmc = 125;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык пилота: {FFFFFF} %d/50", PlayerInfo[playerid][pAirSkill]);
			} else if((50 <= AirSkill <= 99)) {
		    	xmc = 150;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык пилота: {FFFFFF} %d/100", PlayerInfo[playerid][pAirSkill]);
			} else if((100 <= AirSkill <= 199)) {
		    	xmc = 200;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык пилота: {FFFFFF} %d/200", PlayerInfo[playerid][pAirSkill]);
			} else if((200 <= AirSkill <= 499)) {
				xmc = 250;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык пилота: {FFFFFF} %d/500", PlayerInfo[playerid][pAirSkill]);
			} else {
				xmc = 450;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык пилота: {FFFFFF} Максимум");
    		}
		    SendClientMessage(playerid, -1, small_string);
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"Рейс завершен. Зарплата: {FFFFFF}+%d EXP", xmc);
		    SendClientMessage(playerid, -1, small_string);
		    Player.AddEXP(PlayerInfo[playerid][pID], xmc, E_JOB_PILOT, playerid);
			return 1;
		}
	}

	switch(RouteLic[playerid])
	{
		case 0: return SetPlayerRaceCheckpoint(playerid, 0, -2047.4313,-83.9501,34.9071, -2004.1478,-46.2495,34.9080, 5);
		case 1: {
			SetPlayerRaceCheckpoint(playerid, 0, -2004.1478,-46.2495,34.9080, -2003.3331,80.7357,27.2799, 5);
			RouteLic[playerid] = 2;
			return 1;
		}
		case 2: {
			SetPlayerRaceCheckpoint(playerid, 0, -2003.3331,80.7357,27.2799,-1999.4675,294.8887,34.1337, 5);
			RouteLic[playerid] = 3;
			return 1;
		}
		case 3: {
			SetPlayerRaceCheckpoint(playerid, 0, -1999.4675,294.8887,34.1337, -2057.4333,323.0464,34.7587, 5);
			RouteLic[playerid] = 4;
			return 1;
		}
		case 4: {
			SetPlayerRaceCheckpoint(playerid, 0, -2057.4333,323.0464,34.7587, -2130.5852,322.8258,34.8651, 5);
			RouteLic[playerid] = 5;
			return 1;
		}
		case 5: {
			SetPlayerRaceCheckpoint(playerid, 0, -2130.5852,322.8258,34.8651, -2149.1624,277.8851,34.9129, 5);
			RouteLic[playerid] = 6;
			return 1;
		}
		case 6: {
			SetPlayerRaceCheckpoint(playerid, 0, -2149.1624,277.8851,34.9129, -2167.2117,73.9648,34.9154, 5);
			RouteLic[playerid] = 7;
			return 1;
		}
		case 7: {
			SetPlayerRaceCheckpoint(playerid, 0, -2167.2117,73.9648,34.9154,-2170.1353,-26.0125,34.9150, 5);
			RouteLic[playerid] = 8;
			return 1;
		}
		case 8: {
			SetPlayerRaceCheckpoint(playerid, 0, -2170.1353,-26.0125,34.9150,-2170.1235,-151.6749,34.9128, 5);
			RouteLic[playerid] = 9;
			return 1;
		}
		case 9: {
			SetPlayerRaceCheckpoint(playerid, 0, -2170.1235,-151.6749,34.9128, -2232.3179,-187.2447,34.9226, 5);
			RouteLic[playerid] = 10;
			return 1;
		}
		case 10: {
			SetPlayerRaceCheckpoint(playerid, 0, -2232.3179,-187.2447,34.9226, -2369.3813,-142.7696,34.9130, 5);
			RouteLic[playerid] = 11;
			return 1;
		}
		case 11: {
			SetPlayerRaceCheckpoint(playerid, 0, -2369.3813,-142.7696,34.9130, -2349.5676,45.3988,34.9089, 5);
			RouteLic[playerid] = 12;
			return 1;
		}
		case 12: {
			SetPlayerRaceCheckpoint(playerid, 0, -2349.5676,45.3988,34.9089,-2249.1389,98.2920,34.9149, 5);
			RouteLic[playerid] = 13;
			return 1;
		}
		case 13: {
			SetPlayerRaceCheckpoint(playerid, 0, -2249.1389,98.2920,34.9149, -2236.9287,318.2916,34.9147, 5);
			RouteLic[playerid] = 14;
			return 1;
		}
		case 14: {
			SetPlayerRaceCheckpoint(playerid, 0, -2236.9287,318.2916,34.9147, -2023.0085,317.8691,34.7584, 5);
			RouteLic[playerid] = 15;
			return 1;
		}
		case 15: {
			SetPlayerRaceCheckpoint(playerid, 0, -2023.0085,317.8691,34.7584, -2009.4728,229.4922,28.0385, 5);
			RouteLic[playerid] = 16;
			return 1;
		}
		case 16: {
			SetPlayerRaceCheckpoint(playerid, 0, -2009.4728,229.4922,28.0385, -2009.8014,54.5820,30.2677, 5);
			RouteLic[playerid] = 17;
			return 1;
		}
		case 17: {
			SetPlayerRaceCheckpoint(playerid, 0, -2009.8014,54.5820,30.2677,-2010.1556,-58.7772,34.9060, 5);
			RouteLic[playerid] = 18;
			return 1;
		}
		case 18: {
			SetPlayerRaceCheckpoint(playerid, 0, -2010.1556,-58.7772,34.9060, -2035.5370,-67.0759,34.9151, 5);
			RouteLic[playerid] = 19;
			return 1;
		}
		case 19: {
			SetPlayerRaceCheckpoint(playerid, 0, -2010.1556,-58.7772,34.9060, -2035.5370,-67.0759,34.9151, 5);
			RouteLic[playerid] = 20;
			return 1;
	 	}
		case 20: {
			SetPlayerRaceCheckpoint(playerid, 1, -2035.5370,-67.0759,34.9151, -2047.4215,-84.8958,34.9070, 5);
			RouteLic[playerid] = 21;
			return 1;
	 	}
	 	case 21: {
			RouteLic[playerid] = 0;
			new vehicle;
			vehicle = GetPlayerVehicleID(playerid);
			SetVehicleToRespawn(vehicle);
			DisablePlayerRaceCheckpoint(playerid);
		    SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы успешно сдали экзамен и получили права!");
		 	DisablePlayerRaceCheckpoint(playerid);
		    PlayerInfo[playerid][pLicense] = 1;
		    SetPlayerInt(playerid, "License", PlayerInfo[playerid][pLicense]);
			SetPVarInt(playerid,"GetLic", 0);
			return 1;
	 	}
	}
	switch(RouteLicAir[playerid])
	{
		case 0: return SetPlayerRaceCheckpoint(playerid, 3, -2052.0408,-187.2903,35.3203, -2059.2136,-295.8495,84.9901, 20);
		case 1: {
			SetPlayerRaceCheckpoint(playerid, 0, -2059.2136,-295.8495,84.9901, -2248.3833,-456.9216,136.8762, 30);
			RouteLicAir[playerid] = 2;
			return 1;
		}
		case 2: {
			SetPlayerRaceCheckpoint(playerid, 0,-2248.3833,-456.9216,136.8762, -2418.7593,-607.9788,202.1245, 30);
			RouteLicAir[playerid] = 3;
			return 1;
		}
		case 3: {
			SetPlayerRaceCheckpoint(playerid, 0, -2418.7593,-607.9788,202.1245, -2541.0583,-463.0311,149.7090, 30);
			RouteLicAir[playerid] = 4;
			return 1;
		}
		case 4: {
			SetPlayerRaceCheckpoint(playerid, 0, -2541.0583,-463.0311,149.7090, -2356.8572,-288.8315,138.9476, 30);
			RouteLicAir[playerid] = 5;
			return 1;
		}
		case 5: {
			SetPlayerRaceCheckpoint(playerid, 0, -2356.8572,-288.8315,138.9476, -2052.0408,-187.2903,35.3203, 30);
			RouteLicAir[playerid] = 6;
			return 1;
		}
		case 6: {
			SetPlayerRaceCheckpoint(playerid, 4, -2052.0408,-187.2903,35.3203, -2052.0408,-187.2903,35.3203, 20);
			RouteLicAir[playerid] = 7;
			return 1;
		}
	 	case 7: {
			RouteLicAir[playerid] = 0;
		    new Float:health;
			new vehicle;
			vehicle = GetPlayerVehicleID(playerid);
			SetVehicleToRespawn(vehicle);
			DisablePlayerRaceCheckpoint(playerid);
		    GetVehicleHealth(vehicle, health);
		    SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы успешно сдали экзамен и получили лицензию пилота!");
		 	DisablePlayerRaceCheckpoint(playerid);
		    PlayerInfo[playerid][pLicenseAir] = 1;
		    SetPlayerInt(playerid, "LicenseAir", PlayerInfo[playerid][pLicenseAir]);
			SetPVarInt(playerid,"GetLicAir", 0);
			return 1;
	 	}
	}
	switch(Route[playerid])
	{
		case 0: return SetPlayerRaceCheckpoint(playerid, 0, 1130.6526,-1743.5892,13.1755, 1172.6687,-1770.6853,13.1796, 5);
		case 1: {
			SetPlayerRaceCheckpoint(playerid, 0, 1172.6687,-1770.6853,13.1796, 1194.7738,-1854.8091,13.1752, 5);
			Route[playerid] = 2;
			PlayerInfo[playerid][pBusSkill] --;
			if(PlayerInfo[playerid][pBusSkill] < 0) PlayerInfo[playerid][pBusSkill] = 0;
			SetPlayerInt(playerid, "BusSkill", PlayerInfo[playerid][pBusSkill]);
			return 1;
		}
		case 2: {
			SetPlayerRaceCheckpoint(playerid, 0, 1194.7738,-1854.8091,13.1752, 1314.9088,-1817.0076,13.1639, 5);
			Route[playerid] = 3;
			return 1;
		}
		case 3: {
			SetPlayerRaceCheckpoint(playerid, 0, 1314.9088,-1817.0076,13.1639, 1315.0186,-1748.1293,13.1611, 5); //
			Route[playerid] = 4;
			return 1;
		}
		case 4: {
			SetPlayerRaceCheckpoint(playerid, 0, 1315.0186,-1748.1293,13.1611, 1373.8833,-1735.1019,13.1635, 5); //
			Route[playerid] = 5;
			return 1;
		}
		case 5: {
			SetPlayerRaceCheckpoint(playerid, 0, 1373.8833,-1735.1019,13.1635, 1445.9802,-1735.4197,13.1608, 5); //
			Route[playerid] = 6;
			return 1;
		}
		case 6: {
			SetPlayerRaceCheckpoint(playerid, 0, 1445.9802,-1735.4197,13.1608, 1475.4797,-1735.5637,13.1633, 5);
			Route[playerid] = 7;
			return 1;
		}
		case 7: {
			SetPlayerRaceCheckpoint(playerid, 1, 1475.4797,-1735.5637,13.1633, 1673.6885,-1735.4968,13.1609, 5);
			Route[playerid] = 8;
			return 1;
		}
		case 8: {
			DisablePlayerRaceCheckpoint(playerid);
			SendClientMessage(playerid, -1, "Остановка. Подождите 10 секунд...");
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			routetimer[playerid] = SetTimerEx("BusStop", 10000, 0, "i", playerid);
			SetPVarInt(playerid, "MinusTime", 10);
			format(small_string, 100, "Водитель %s: Остановка Мэрия штата", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		}
		case 9: {
			SetPlayerRaceCheckpoint(playerid, 0, 1817.8293,-1735.1664,13.1596, 1819.3456,-1813.4141,13.1844, 5); //
			Route[playerid] = 10;
			return 1;
		}
		case 10: {
			SetPlayerRaceCheckpoint(playerid, 0, 1819.3456,-1813.4141,13.1844, 1819.2897,-1870.4648,13.1913, 5); //
			Route[playerid] = 11;
			return 1;
		}
		case 11: {
			SetPlayerRaceCheckpoint(playerid, 0, 1819.2897,-1870.4648,13.1913, 1818.7710,-1907.1416,13.1731, 5); //
			Route[playerid] = 12;
			return 1;
		}
		case 12: {
			SetPlayerRaceCheckpoint(playerid, 1, 1818.7710,-1907.1416,13.1731, 876.8849,-1934.8877,13.1628, 5); //f
		    Route[playerid] = 13;
		    return 1;
	    }
		case 13: {
			DisablePlayerRaceCheckpoint(playerid);
			SendClientMessage(playerid, -1, "Остановка. Подождите 10 секунд...");
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			routetimer[playerid] = SetTimerEx("BusStop", 10000, 0, "i", playerid);
			SetPVarInt(playerid, "MinusTime", 10);
			format(small_string, 100, "Водитель %s: Остановка Таксопарк", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
		}
		case 14: {
			SetPlayerRaceCheckpoint(playerid, 0, 1959.1816,-1969.8948,13.2184, 1958.9706,-2092.0698,13.1676, 5); //
			Route[playerid] = 15;
			return 1;
		}
		case 15: {
			SetPlayerRaceCheckpoint(playerid, 0, 1958.9706,-2092.0698,13.1676, 1983.7018,-2112.4702,13.1222, 5); //
			Route[playerid] = 16;
			return 1;
		}
		case 16: {
			SetPlayerRaceCheckpoint(playerid, 0, 1983.7018,-2112.4702,13.1222, 2089.8477,-2112.7598,13.1037, 5); //
			Route[playerid] = 17;
			return 1;
		}
		case 17: {
			SetPlayerRaceCheckpoint(playerid, 0, 2089.8477,-2112.7598,13.1037, 2179.9163,-2149.9106,13.1542, 5); //
			Route[playerid] = 18;
			return 1;
		}
		case 18: {
			SetPlayerRaceCheckpoint(playerid, 0, 2179.9163,-2149.9106,13.1542, 2265.0615,-2235.2913,13.2845, 5); //
			Route[playerid] = 19;
			return 1;
		}
		case 19: {
			SetPlayerRaceCheckpoint(playerid, 0, 2265.0615,-2235.2913,13.2845, 2341.8574,-2236.5745,13.1521, 5); //
			Route[playerid] = 20;
			return 1;
		}
		case 20: {
			SetPlayerRaceCheckpoint(playerid, 0, 2341.8574,-2236.5745,13.1521, 2545.7178,-2172.6692,13.0248, 5); //
			Route[playerid] = 21;
			return 1;
		}
		case 21: {
			SetPlayerRaceCheckpoint(playerid, 0, 2545.7178,-2172.6692,13.0248, 2825.4358,-2112.7910,10.7079, 5); //
			Route[playerid] = 22;
			return 1;
		}
		case 22: {
			SetPlayerRaceCheckpoint(playerid, 0, 2825.4358,-2112.7910,10.7079, 2840.8699,-1941.5917,10.7159, 5); //
			Route[playerid] = 23;
			return 1;
		}
		case 23: {
			SetPlayerRaceCheckpoint(playerid, 0, 2840.8699,-1941.5917,10.7159, 2801.8223,-1654.7633,10.4728, 5); //
			Route[playerid] = 24;
			return 1;
		}
	    case 24: {
		   	SetPlayerRaceCheckpoint(playerid, 1, 2801.8223,-1654.7633,10.4728, 2667.0901,-1654.5537,10.4752, 5); // f
			Route[playerid] = 25;
			return 1;
		}
		case 25: {
			DisablePlayerRaceCheckpoint(playerid);
			SendClientMessage(playerid, -1, "Остановка. Подождите 10 секунд...");
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			routetimer[playerid] = SetTimerEx("BusStop", 10000, 0, "i", playerid);
			SetPVarInt(playerid, "MinusTime", 10);
			format(small_string, 100, "Водитель %s: Остановка Восточный пляж", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
			return 1;
		}
		case 26: {
			SetPlayerRaceCheckpoint(playerid, 0, 2532.1121,-1729.4828,13.1628, 2450.9299,-1729.6489,13.2863, 5); //
			Route[playerid] = 27;
			return 1;
		}
		case 27: {
			SetPlayerRaceCheckpoint(playerid, 1, 2450.9299,-1729.6489,13.2863, 2276.6689,-1730.1351,13.1628, 5); // f
			Route[playerid] = 28;
			return 1;
		}
		case 28: {
			DisablePlayerRaceCheckpoint(playerid);
			SendClientMessage(playerid, -1, "Остановка. Подождите 10 секунд...");
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			routetimer[playerid] = SetTimerEx("BusStop", 10000, 0, "i", playerid);
			SetPVarInt(playerid, "MinusTime", 10);
			format(small_string, 100, "Водитель %s: Остановка Grove Street", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
			return 1;
		}
		case 29: {
			SetPlayerRaceCheckpoint(playerid, 0, 2162.4392,-1748.8833,13.1573, 1960.0845,-1750.0604,13.1629, 5); //
			Route[playerid] = 30;
			return 1;
		}
		case 30: {
			SetPlayerRaceCheckpoint(playerid, 0, 1960.0845,-1750.0604,13.1629, 1833.9393,-1749.2125,13.1628, 5); //
			Route[playerid] = 31;
			return 1;
		}
		case 31: {
			SetPlayerRaceCheckpoint(playerid, 0, 1833.9393,-1749.2125,13.1628, 1708.6572,-1729.8389,13.1629, 5); //
			Route[playerid] = 32;
			return 1;
		}
		case 32: {
			SetPlayerRaceCheckpoint(playerid, 0, 1708.6572,-1729.8389,13.1629, 1692.1533,-1690.3262,13.1627, 5); //
			Route[playerid] = 33;
			return 1;
		}
		case 33: {
			SetPlayerRaceCheckpoint(playerid, 0, 1692.1533,-1690.3262,13.1627, 1658.2278,-1590.1727,13.1702, 5); //
			Route[playerid] = 34;
			return 1;
		}
		case 34: {
			SetPlayerRaceCheckpoint(playerid, 0, 1658.2278,-1590.1727,13.1702, 1548.3784,-1589.8077,13.1627, 5); //
			Route[playerid] = 35;
			return 1;
		}
		case 35: {
			SetPlayerRaceCheckpoint(playerid, 0, 1548.3784,-1589.8077,13.1627, 1526.6211,-1672.0090,13.1611, 5); //
			Route[playerid] = 36;
			return 1;
		}
		case 36: {
			SetPlayerRaceCheckpoint(playerid, 1, 1526.6211,-1672.0090,13.1611, 1504.3635,-1729.6943,13.1603, 5); // f
			Route[playerid] = 37;
			return 1;
		}
		case 37: {
			DisablePlayerRaceCheckpoint(playerid);
			SendClientMessage(playerid, -1, "Остановка. Подождите 10 секунд...");
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			routetimer[playerid] = SetTimerEx("BusStop", 10000, 0, "i", playerid);
			SetPVarInt(playerid, "MinusTime", 10);
			format(small_string, 100, "Водитель %s: Остановка Полицейский Департамент", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
			return 1;
		}
		case 38: {
			SetPlayerRaceCheckpoint(playerid, 0, 1386.4618,-1756.3813,13.1617, 1386.9150,-1862.8605,13.1614, 5); //
			Route[playerid] = 39;
			return 1;
		}
		case 39: {
			SetPlayerRaceCheckpoint(playerid, 0, 1386.9150,-1862.8605,13.1614, 1337.7184,-1853.0475,13.1675, 5); //
			Route[playerid] = 40;
			return 1;
		}
		case 40: {
			SetPlayerRaceCheckpoint(playerid, 0, 1337.7184,-1853.0475,13.1675, 1281.9629,-1850.2169,13.1684, 5); //
			Route[playerid] = 41;
			return 1;
		}
		case 41: {
			SetPlayerRaceCheckpoint(playerid, 0, 1281.9629,-1850.2169,13.1684, 1245.3251,-1828.3600,13.1830, 5); // fin
			Route[playerid] = 42;
			return 1;
		}
		case 42: {
			SetPlayerRaceCheckpoint(playerid, 1, 1245.3251,-1828.3600,13.1830, 1245.3251,-1828.3600,13.1830, 5); // fin
			Route[playerid] = 43;
			return 1;
		}
		case 43: {
			DisablePlayerRaceCheckpoint(playerid);
			Route[playerid] = 0;
			new vehicle;
			vehicle = GetPlayerVehicleID(playerid);
			SetVehicleToRespawn(vehicle);
			PlayerInfo[playerid][pBusSkill] += 2;
			SetPlayerInt(playerid, "BusSkill", PlayerInfo[playerid][pBusSkill]);
		    new 
		    	xmc,
		    	BusSkill = PlayerInfo[playerid][pBusSkill];

		    if((0 <= BusSkill <= 24)) {
				xmc = 50;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/25", PlayerInfo[playerid][pBusSkill]);
			} else if((25 <= BusSkill <= 49)) {
		    	xmc = 75;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/50", PlayerInfo[playerid][pBusSkill]);
			} else if((50 <= BusSkill <= 99)) {
		    	xmc = 100;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/100", PlayerInfo[playerid][pBusSkill]);
			} else if((100 <= BusSkill <= 199)) {
		    	xmc = 150;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/200", PlayerInfo[playerid][pBusSkill]);
			} else if((200 <= BusSkill <= 499)) {
				xmc = 250;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/500", PlayerInfo[playerid][pBusSkill]);
			} else {
				xmc = 350;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} Максимум");
    		}
		    SendClientMessage(playerid, -1, small_string);
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"Круг завершен. Зарплата: {FFFFFF}+%d EXP", xmc);
		    SendClientMessage(playerid, -1, small_string);
		    Player.AddEXP(PlayerInfo[playerid][pID], xmc, E_JOB_BUS_DRIVER, playerid);
			return 1;
		}
	}
	switch(Route2[playerid])
	{
		case 0: return SetPlayerRaceCheckpoint(playerid, 1, 2809.6353,1302.1759,10.4570,2809.6353,1302.1759,10.4570, 5);
		case 1: {
			DisablePlayerRaceCheckpoint(playerid);
			SendClientMessage(playerid, -1, "Остановка. Подождите 30 секунд...");
			SetPVarInt(playerid, "MinusTime", 30);
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			routetimer[playerid] = SetTimerEx("BusStop2", 30000, 0, "i", playerid);
			format(small_string, 100, "Водитель %s: Остановка Автовокзал Лас-Вентурас", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
			return 1;
		}
		case 2: {
			SetPlayerRaceCheckpoint(playerid, 0, 2769.1545,1475.4580,10.9587, 2639.4485,1448.1586,10.3407, 5);
			Route2[playerid] = 3;
			return 1;
		}
		case 3: {
			SetPlayerRaceCheckpoint(playerid, 0, 2639.4485,1448.1586,10.3407, 2706.0308,1281.7927,6.4420, 5); // here
			Route2[playerid] = 4;
			return 1;
		}
		case 4: {
			SetPlayerRaceCheckpoint(playerid, 0, 2706.0308,1281.7927,6.4420, 2621.4075,928.5538,6.4469, 5); //
			Route2[playerid] = 5;
			return 1;
		}
		case 5: {
			SetPlayerRaceCheckpoint(playerid, 0, 2621.4075,928.5538,6.4469, 2365.2959,854.7721,6.4395, 5); //
			Route2[playerid] = 6;
			return 1;
		}
		case 6: {
			SetPlayerRaceCheckpoint(playerid, 0, 2365.2959,854.7721,6.4395, 1992.2372,855.0261,6.4418, 5);
			Route2[playerid] = 7;
			return 1;
		}
		case 7: {
			SetPlayerRaceCheckpoint(playerid, 0, 1992.2372,855.0261,6.4418, 1785.0820,801.9041,10.8147, 5);
			Route2[playerid] = 8;
			return 1;
		}
		case 8: {
			SetPlayerRaceCheckpoint(playerid, 0, 1785.0820,801.9041,10.8147, 1745.0541,579.1783,24.0793, 5); //
			Route2[playerid] = 9;
			return 1;
		}
		case 9: {
			SetPlayerRaceCheckpoint(playerid, 0, 1745.0541,579.1783,24.0793, 1654.9573,312.5692,29.9793, 5); //
			Route2[playerid] = 10;
			return 1;
		}
		case 10: {
			SetPlayerRaceCheckpoint(playerid, 0, 1654.9573,312.5692,29.9793, 1622.7864,-4.6736,36.44399, 5); //
			Route2[playerid] = 11;
			return 1;
		}
		case 11: {
			SetPlayerRaceCheckpoint(playerid, 0, 1622.7864,-4.6736,36.4439, 1677.5072,-420.4447,33.4097, 5); //
			Route2[playerid] = 12;
			return 1;
		}
		case 12: {
			SetPlayerRaceCheckpoint(playerid, 0, 1677.5072,-420.4447,33.4097, 1692.0481,-706.8760,47.2514, 5); //f
		    Route2[playerid] = 13;
		    return 1;
	    }
		case 13: {
			SetPlayerRaceCheckpoint(playerid, 0, 1692.0481,-706.8760,47.2514, 1636.7799,-839.8529,58.2235, 5); //
			Route2[playerid] = 14;
			return 1;
		}
		case 14: {
			SetPlayerRaceCheckpoint(playerid, 0, 1636.7799,-839.8529,58.2235, 1469.9343,-939.3515,35.9429, 5); //
			Route2[playerid] = 15;
			return 1;
		}
		case 15: {
			SetPlayerRaceCheckpoint(playerid, 0, 1469.9343,-939.3515,35.9429, 1356.0643,-977.9618,30.8393, 5); //
			Route2[playerid] = 16;
			return 1;
		}
		case 16: {
			SetPlayerRaceCheckpoint(playerid, 0, 1356.0643,-977.9618,30.8393, 1340.2274,-1148.3407,23.3682, 5); //
			Route2[playerid] = 17;
			return 1;
		}
		case 17: {
			SetPlayerRaceCheckpoint(playerid, 0, 1340.2274,-1148.3407,23.3682, 1315.2666,-1503.5526,13.0947, 5); //
			Route2[playerid] = 18;
			return 1;
		}
		case 18: {
			SetPlayerRaceCheckpoint(playerid, 0, 1315.2666,-1503.5526,13.0947, 1295.0389,-1644.3304,13.0902, 5); //
			Route2[playerid] = 19;
			return 1;
		}
		case 19: {
			SetPlayerRaceCheckpoint(playerid, 0, 1295.0389,-1644.3304,13.0902, 1261.3240,-1709.7252,13.0890, 5); //
			Route2[playerid] = 20;
			return 1;
		}
		case 20: {
			SetPlayerRaceCheckpoint(playerid, 0, 1261.3240,-1709.7252,13.0890, 1173.4429,-1732.9390,13.2154, 5); //
			Route2[playerid] = 21;
			return 1;
		}
		case 21: {
			SetPlayerRaceCheckpoint(playerid, 0, 1173.4429,-1732.9390,13.2154, 1124.2900,-1738.3217,13.2075, 5); //
			Route2[playerid] = 22;
			return 1;
		}
		case 22: {
			SetPlayerRaceCheckpoint(playerid, 0, 1124.2900,-1738.3217,13.2075, 1094.3568,-1738.1898,13.2466, 5); //
			Route2[playerid] = 23;
			return 1;
		}
		case 23: {
			SetPlayerRaceCheckpoint(playerid, 1, 1094.3568,-1738.1898,13.2466, 1094.3568,-1738.1898,13.2466, 5); //
			Route2[playerid] = 24;
			return 1;
		}
		case 24: {
			DisablePlayerRaceCheckpoint(playerid);
			Route2[playerid] = 0;
			new vehicle;
			vehicle = GetPlayerVehicleID(playerid);
			SetVehicleToRespawn(vehicle);
			PlayerInfo[playerid][pBusSkill] += 2;
			SetPlayerInt(playerid, "BusSkill", PlayerInfo[playerid][pBusSkill]);
		    new 
		    	xmc,
		    	BusSkill = PlayerInfo[playerid][pBusSkill];

		    if((0 <= BusSkill <= 24)) {
				xmc = 50;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/25", PlayerInfo[playerid][pBusSkill]);
			} else if((25 <= BusSkill <= 49)) {
		    	xmc = 75;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/50", PlayerInfo[playerid][pBusSkill]);
			} else if((50 <= BusSkill <= 99)) {
		    	xmc = 100;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/100", PlayerInfo[playerid][pBusSkill]);
			} else if((100 <= BusSkill <= 199)) {
		    	xmc = 150;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/200", PlayerInfo[playerid][pBusSkill]);
			} else if((200 <= BusSkill <= 499)) {
				xmc = 200;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/500", PlayerInfo[playerid][pBusSkill]);
			} else {
				xmc = 300;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} Максимум");
    		}
		    SendClientMessage(playerid, -1, small_string);
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"Круг завершен. Зарплата: {FFFFFF}+%d EXP", xmc);
		    SendClientMessage(playerid, -1, small_string);
		    Player.AddEXP(PlayerInfo[playerid][pID], xmc, E_JOB_BUS_DRIVER, playerid);
			return 1;
		}
	}
	switch(Route3[playerid])
	{
		case 0: return SetPlayerRaceCheckpoint(playerid, 1,-1988.6450,138.3930,27.2461,-1988.6450,138.3930,27.2461, 5);
		case 1: {
			DisablePlayerRaceCheckpoint(playerid);
			SendClientMessage(playerid, -1, "Остановка. Подождите 15 секунд...");
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			routetimer[playerid] = SetTimerEx("BusStop3", 15000, 0, "i", playerid);
			SetPVarInt(playerid, "MinusTime", 15);
			format(small_string, 100, "Водитель %s: Остановка Автовокзал Сан-Фиерро", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
			return 1;
		}
		case 2: {
			SetPlayerRaceCheckpoint(playerid, 0, -2009.7799,190.0612,27.2468, -2009.7573,50.9689,30.7395, 5);
			Route3[playerid] = 3;
			return 1;
		}
		case 3: {
			SetPlayerRaceCheckpoint(playerid, 0, -2009.7573,50.9689,30.7395, -2048.8228,33.5824,34.8789, 5); // here
			Route3[playerid] = 4;
			return 1;
		}
		case 4: {
			SetPlayerRaceCheckpoint(playerid, 0, -2048.8228,33.5824,34.8789, -2089.9421,-10.6358,34.8776, 5); //
			Route3[playerid] = 5;
			return 1;
		}
		case 5: {
			SetPlayerRaceCheckpoint(playerid, 0, -2089.9421,-10.6358,34.8776, -2077.2681,-72.8924,34.8781, 5); //
			Route3[playerid] = 6;
			return 1;
		}
		case 6: {
			SetPlayerRaceCheckpoint(playerid, 0, -2077.2681,-72.8924,34.8781, -2029.1040,-77.7470,35.0282, 5);
			Route3[playerid] = 7;
			return 1;
		}
		case 7: {
			SetPlayerRaceCheckpoint(playerid, 1, -2029.1040,-77.7470,35.0282,-2029.1040,-77.7470,35.0282, 5); //
			Route3[playerid] = 8;
			return 1;
		}
		case 8: {
			DisablePlayerRaceCheckpoint(playerid);
			SendClientMessage(playerid, -1, "Остановка. Подождите 15 секунд...");
			routetimer[playerid] = KillTimer(routetimer[playerid]); 
			routetimer[playerid] = SetTimerEx("BusStop3", 15000, 0, "i", playerid);
			SetPVarInt(playerid, "MinusTime", 15);
			format(small_string, 100, "Водитель %s: Остановка Автошкола", PlayerInfo[playerid][pName]);
			ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
			return 1;
		}
		case 9: {
			SetPlayerRaceCheckpoint(playerid, 0, -1854.7101,-118.7683,5.9268, -1854.7101,-118.7683,5.9268, 5); //
			Route3[playerid] = 10;
			return 1;
		}
		case 10: {
			SetPlayerRaceCheckpoint(playerid, 0, -1854.7101,-118.7683,5.9268, -1801.4520,-130.5810,5.4300, 5); //
			Route3[playerid] = 11;
			return 1;
		}
		case 11: {
			SetPlayerRaceCheckpoint(playerid, 0, -1801.4520,-130.5810,5.4300, -1801.6399,-256.0707,18.8793, 5); //
			Route3[playerid] = 12;
			return 1;
		}
		case 12: {
			SetPlayerRaceCheckpoint(playerid, 0, -1801.6399,-256.0707,18.8793, -1815.6925,-400.7422,15.9548, 5); //f
		    Route3[playerid] = 13;
		    return 1;
	    }
		case 13: {
			SetPlayerRaceCheckpoint(playerid, 0, -1815.6925,-400.7422,15.9548, -1821.7493,-552.6250,15.7331, 5); //
			Route3[playerid] = 14;
			return 1;
		}
		case 14: {
			SetPlayerRaceCheckpoint(playerid, 0, -1821.7493,-552.6250,15.7331, -1787.4788,-584.2288,16.0414, 5); //
			Route3[playerid] = 15;
			return 1;
		}
		case 15: {
			SetPlayerRaceCheckpoint(playerid, 0, -1787.4788,-584.2288,16.0414, -1762.4775,-692.0914,25.1931, 5); //
			Route3[playerid] = 16;
			return 1;
		}
		case 16: {
			SetPlayerRaceCheckpoint(playerid, 0, -1762.4775,-692.0914,25.1931, -1631.5165,-790.1624,45.4642, 5); //
			Route3[playerid] = 17;
			return 1;
		}
		case 17: {
			SetPlayerRaceCheckpoint(playerid, 0, -1631.5165,-790.1624,45.4642, -1491.4242,-823.0391,64.2672, 5); //
			Route3[playerid] = 18;
			return 1;
		}
		case 18: {
			SetPlayerRaceCheckpoint(playerid, 0, -1491.4242,-823.0391,64.2672, -1224.3580,-777.6037,63.6083, 5); //
			Route3[playerid] = 19;
			return 1;
		}
		case 19: {
			SetPlayerRaceCheckpoint(playerid, 0, -1224.3580,-777.6037,63.6083, -1103.4009,-902.4699,76.1163, 5); //
			Route3[playerid] = 20;
			return 1;
		}
		case 20: {
			SetPlayerRaceCheckpoint(playerid, 0, -1103.4009,-902.4699,76.1163, -1008.6852,-999.5681,92.6091, 5); //
			Route3[playerid] = 21;
			return 1;
		}
		case 21: {
			SetPlayerRaceCheckpoint(playerid, 0, -1008.6852,-999.5681,92.6091, -878.1254,-1110.8273,98.3178, 5); //
			Route3[playerid] = 22;
			return 1;
		}
		case 22: {
			SetPlayerRaceCheckpoint(playerid, 0, -878.1254,-1110.8273,98.3178, -758.8220,-1008.7773,77.1448, 5); //
			Route3[playerid] = 23;
			return 1;
		}
		case 23: {
			SetPlayerRaceCheckpoint(playerid, 0, -758.8220,-1008.7773,77.1448, -646.9244,-1001.3293,68.1421, 5); //
			Route3[playerid] = 24;
			return 1;
		}
		case 24: {
			SetPlayerRaceCheckpoint(playerid, 0, -646.9244,-1001.3293,68.1421, -386.4313,-837.4401,46.9065, 5); //
			Route3[playerid] = 25;
			return 1;
		}
		case 25: {
			SetPlayerRaceCheckpoint(playerid, 0, -386.4313,-837.4401,46.9065, -157.5044,-961.7455,28.8297, 5); //
			Route3[playerid] = 26;
			return 1;
		}
		case 26: {
			SetPlayerRaceCheckpoint(playerid, 0, -157.5044,-961.7455,28.8297, -98.5346,-1125.1733,0.7931, 5); //
			Route3[playerid] = 27;
			return 1;
		}
		case 27: {
			SetPlayerRaceCheckpoint(playerid, 0, -98.5346,-1125.1733,0.7931, -159.5574,-1377.3635,2.5837, 5); //
			Route3[playerid] = 28;
			return 1;
		}
		case 28: {
			SetPlayerRaceCheckpoint(playerid, 0, -159.5574,-1377.3635,2.5837, 54.4676,-1541.8804,4.8500, 5); //
			Route3[playerid] = 29;
			return 1;
		}
		case 29: {
			SetPlayerRaceCheckpoint(playerid, 0, 54.4676,-1541.8804,4.8500, 388.5890,-1719.2759,7.5602, 5); //
			Route3[playerid] = 30;
			return 1;
		}
		case 30: {
			SetPlayerRaceCheckpoint(playerid, 0, 388.5890,-1719.2759,7.5602, 823.0443,-1786.6195,13.4243, 5); //
			Route3[playerid] = 31;
			return 1;
		}
		case 31: {
			SetPlayerRaceCheckpoint(playerid, 0, 823.0443,-1786.6195,13.4243, 1036.6509,-1828.0513,13.3161, 5); //
			Route3[playerid] = 32;
			return 1;
		}
		case 32: {
			SetPlayerRaceCheckpoint(playerid, 0, 1036.6509,-1828.0513,13.3161, 1040.4053,-1869.4093,13.1565, 5); //
			Route3[playerid] = 33;
			return 1;
		}
		case 33: {
			SetPlayerRaceCheckpoint(playerid, 1, 1040.4053,-1869.4093,13.1565, 1040.4053,-1869.4093,13.1565, 5); //
			Route3[playerid] = 34;
			return 1;
		}
		case 34: {
			DisablePlayerRaceCheckpoint(playerid);
			Route3[playerid] = 0;
			new vehicle;
			vehicle = GetPlayerVehicleID(playerid);
			SetVehicleToRespawn(vehicle);
			PlayerInfo[playerid][pBusSkill] += 2;
			SetPlayerInt(playerid, "BusSkill", PlayerInfo[playerid][pBusSkill]);
		    new 
		    	xmc,
		    	BusSkill = PlayerInfo[playerid][pBusSkill];

		    if((0 <= BusSkill <= 24)) {
				xmc = 50;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/25", PlayerInfo[playerid][pBusSkill]);
			} else if((25 <= BusSkill <= 49)) {
		    	xmc = 75;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/50", PlayerInfo[playerid][pBusSkill]);
			} else if((50 <= BusSkill <= 99)) {
		    	xmc = 100;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/100", PlayerInfo[playerid][pBusSkill]);
			} else if((100 <= BusSkill <= 199)) {
		    	xmc = 150;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/200", PlayerInfo[playerid][pBusSkill]);
			} else if((200 <= BusSkill <= 499)) {
				xmc = 200;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} %d/500", PlayerInfo[playerid][pBusSkill]);
			} else {
				xmc = 300;
				format(small_string, sizeof(small_string), ""COLOR_ORANGE"Навык водителя автобуса: {FFFFFF} Максимум");
    		}
		    SendClientMessage(playerid, -1, small_string);
			format(small_string, sizeof(small_string), ""COLOR_ORANGE"Круг завершен. Зарплата: {FFFFFF}+%d EXP", xmc);
		    SendClientMessage(playerid, -1, small_string);
		    Player.AddEXP(PlayerInfo[playerid][pID], xmc, E_JOB_BUS_DRIVER, playerid);
			return 1;
		}
	}
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
    return 0;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) return 0;
	new gettimer = gettime();
    if(pPickup_Status{playerid} && pPickup_AntiFlood[playerid] < gettimer) {
        if(!IsPlayerInRangeOfPoint(playerid,1.0,pPickup_Pos[playerid][0],pPickup_Pos[playerid][1],pPickup_Pos[playerid][2])) pPickup_Status{playerid} = false;
        GetPlayerPos(playerid,pPickup_Pos[playerid][0],pPickup_Pos[playerid][1],pPickup_Pos[playerid][2]);
    }
    if(pPickup_Status{playerid} || pPickup_AntiFlood[playerid] > gettimer) return 1;
    else {
        pPickup_Status{playerid} = true;
        pPickup_AntiFlood[playerid] = gettimer+2;
    }  
	return 1;
}
publics: Clear0()
{
	shop[0] = 0;
}
publics: Clear1()
{
	shop[1] = 0;
}
publics: Clear2()
{
	shop[2] = 0;
}
publics: Clear3()
{
	shop[3] = 0;
}
publics: Clear4()
{
	shop[4] = 0;
}
publics: Clear5()
{
	shop[5] = 0;
}
publics: Clear6()
{
	shop[6] = 0;
}
publics: Clear7()
{
	shop[7] = 0;
}
publics: Clear8()
{
	shop[8] = 0;
}
publics: Clear9()
{
	shop[9] = 0;
}
publics: Clear10()
{
	shop[10] = 0;
}
publics: Clear11()
{
	shop[11] = 0;
}
publics: Clear12()
{
	shop[12] = 0;
	SendMafiaAlert(-1,""COLOR_BLUE"На военную базу Сан-Фиерро прибыла партия оружия");
}
publics: Clear13()
{
	shop[13] = 0;
	SendMafiaAlert(-1,""COLOR_BLUE"В порт Сан-Фиерро прибыла партия наркотиков");
}
publics: Clear14()
{
	shop[14] = 0;
	SendMafiaAlert(-1,""COLOR_BLUE"В аэропорт Лас-Вентурас прибыла партия наркотиков");
}
stock SendPoliceAlert(color,string[])
{
	foreach(new i: Player)
	{
		if(GetPlayerFraction(i) == FRACTION_LSPD) {
			SendClientMessage(i,color,string);
		}
	}
	return true;
}
stock SendPoliceGameText(const string[])
{
	foreach(new i: Player)
	{
		if(GetPlayerFraction(i) == FRACTION_LSPD) {
			GameTextForPlayer(i, string, 2500, 4);
		}
	}
	return true;
}

stock SendMafiaAlert(color,string[])
{
	new 
		Fraction: fractionid;
	foreach(new i: Player)
	{
		fractionid = GetPlayerFraction(i);

		if(fractionid >= FRACTION_RUSSIAN_MAFIA && fractionid <= FRACTION_DN_BOYS) {
			SendClientMessage(i,color,string);
		}
	}
	return true;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	new Menu:Current = GetPlayerMenu(playerid);
    if(Current == AdminMenu)
	{
		if(PlayerInfo[playerid][pAdmin] < 1) {
			return Kick(playerid);
		}
		switch(row) {
			case 0: {
				ShowStats(playerid, spectating[playerid]);
				return ShowMenuForPlayer(AdminMenu, playerid);
			}
			case 1: {
				callcmd::weapon(playerid,spectating[playerid]);
				return ShowMenuForPlayer(AdminMenu, playerid);
			}
			case 2:
			{
				return StopSpectate(playerid);
			}
		}
	}
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) 
{ 
	Porter_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	
    if(newkeys & KEY_ANALOG_LEFT) // проверяем нажатие клавиши NUM 4 
    { 
        if(spectating[playerid] != -1 && GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) // проверяем наблюдает ли за кем-либо игрок 
        { 
            if(spectating[playerid] <= 0) spectating[playerid] = GetPlayerPoolSize(); // если игрок наблюдает за минимальным ID, то перекидываем его на максимальный 
            else spectating[playerid]--; // или убавляем -1 от ID игрока за кем следящий наблюдал ранее
            if(spectating[playerid] == INVALID_PLAYER_ID) {
            	spectating[playerid] = GetPlayerPoolSize();
            }
            return UpdateSpectatingStatus(playerid, spectating[playerid]); // обновляем режим слежки 
        } 
    } 
     
    if(newkeys & KEY_ANALOG_RIGHT) // проверяем нажатие клавиши NUM 6 
    { 
        if(spectating[playerid] != -1 && GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) // проверяем наблюдает ли за кем-либо игрок 
        { 
            if(spectating[playerid] >= GetPlayerPoolSize()) spectating[playerid] = 0; // если игрок наблюдает за максимальным ID, перекидываем его на минимальный 
            else spectating[playerid]++; // или добавляем +1 к ID игрока за кем следящий наблюдал ранее 
            if(spectating[playerid] == INVALID_PLAYER_ID) {
            	spectating[playerid] = GetPlayerPoolSize();
            }
            return UpdateSpectatingStatus(playerid, spectating[playerid]); // обновляем режим слежки 
        } 
    } 
    return 1; 
    // Не спорю, удобнее будет из цикла вытаскивать ID самого большого подключившегося игрока 
    // Но, я не думаю что это будет мелочью в плане быстродействия кода. 
    // Можно также завести переменную и записывать в нёё самый последний ID подключившегося игрока (см. примечание 2) 
}  

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}
public OnPlayerUpdate(playerid)
{
	pl_afk_time[playerid] = 0;
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	if(IsPlayerNPC(playerid)) return 1;
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	if(IsPlayerNPC(playerid)) return 1;
	 //Данный паблик вызовется когда игрок за которым следим, пропадет из вида следящего (смена интерьера, виртуального мира)
	if(IsPlayerConnected(forplayerid))
	{
		if(spectating[forplayerid] == playerid)//Проверяем действительно ли следит следящий игрок именно за этим игроком (см. примечание 1)
		{
			//Колбэк указанный ниже, поможет нам быстро обновить режим слежки
			UpdateSpectatingStatus(forplayerid, playerid);
		}
	}
	return 1;
}

stock UpdateSpectatingStatus(spectatorid, spectedid)
{
	if(PlayerInfo[spectatorid][pAdmin] == 0) {
		return true;
	}
	//Еще раз проверяем, совпадает ли значение в переменной следящего игрока с ID игрока за которым следят
	if(spectating[spectatorid] == spectedid)
	{
		//Приведенные ниже строчки-оповещения, вы можете не использовать
		if(GetPlayerState(spectedid) == PLAYER_STATE_WASTED) return callcmd::reoff(spectatorid,"\0"); // игрок убит
		if(GetPlayerState(spectedid) == PLAYER_STATE_SPECTATING) return callcmd::reoff(spectatorid,"\0"); // игрок перешел в режим слежки
		if(!IsPlayerConnected(spectedid)) callcmd::reoff(spectatorid,"\0"); // игрок отключился

		//Снова устанавливаем виртуальный мир следящему, то же самое, проделываем с интерьером
		SetPlayerInterior(spectatorid,GetPlayerInterior(spectedid));
		SetPlayerVirtualWorld(spectatorid,GetPlayerVirtualWorld(spectedid));
		// Update TD
		UpdateSpecTD(spectatorid);
		//Отправляем следящего снова в режим слежки
		TogglePlayerSpectating(spectatorid, true);
		if(IsPlayerInAnyVehicle(spectedid)) PlayerSpectateVehicle(spectatorid, GetPlayerVehicleID(spectedid), SPECTATE_MODE_NORMAL);
		else PlayerSpectatePlayer(spectatorid, spectedid, SPECTATE_MODE_NORMAL);
	}
	return 1;
}

stock StopSpectate(playerid)
{
	PlayerTextDrawHide(playerid, FULLRECON[playerid]);
    HideMenuForPlayer(AdminMenu,playerid);
	TogglePlayerSpectating(playerid, false);
	return spectating[playerid] = INVALID_PLAYER_ID;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	if(IsPlayerNPC(forplayerid)) return 1;
	return SetVehicleParamsForPlayer(vehicleid, forplayerid, VehicleParameters[vehicleid][0], VehicleParameters[vehicleid][1]); 
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}
forward UploadPlayerAccountNumber(playerid);
public UploadPlayerAccountNumber(playerid) PlayerInfo[playerid][pID] = cache_insert_id();
stock CreateNewAccount(playerid, password[], email[])
{
    new query_string[66+MAX_PLAYER_NAME-4+100];
    format(query_string, sizeof(query_string), "INSERT INTO "TABLE_ACCOUNTS" (`Name`, `Password`, `RegIP`, `Email`, `Sex`) VALUES ('%s', '%s', '%s', '%s', CURRENT_TIMESTAMP(), '%d')", PlayerInfo[playerid][pName], password, PlayerInfo[playerid][pIP], email, PlayerInfo[playerid][pSex]);
    mysql_tquery(database, query_string, "UploadPlayerAccountNumber", "i", playerid);
 	UpdateSpawnInfo(playerid);
    format(query_string, sizeof(query_string), "Аккаунт %s успешно зарегистрирован. Администрация желает Вам приятной игры!", PlayerInfo[playerid][pName]);

    SetPVarInt(playerid, "JustCreated", 1);
	
	UploadPlayerAccount(playerid);
    return 1;
}
forward UploadPlayerAccount(playerid);
public UploadPlayerAccount(playerid)
{
	PlayerInfo[playerid][pBanned] = cache_get_field_content_int(0, "Banned");
	if(PlayerInfo[playerid][pBanned] > 0) {
		PlayerPlaySound(playerid, 42801,0,0,0);
		GameTextForPlayer(playerid, "~r~YOU ARE BANNED", 60000, 4);
		Kick(playerid);
		return 1;
	}
	PlayerInfo[playerid][pAdmin] = cache_get_field_content_int(0, "Admin");
	if(Platform[playerid] == 2 && PlayerInfo[playerid][pAdmin] == 0) return Kick(playerid);

	new temp_int = cache_get_field_content_int(0, "isOnline");


	if(temp_int == 1) {
		Kick(playerid);

		new
	        targetid;
	    sscanf(PlayerInfo[playerid][pName], "u", targetid);
	    
	    if(targetid != INVALID_PLAYER_ID) {
			SendClientMessage(playerid, -1, !""COLOR_RED"Игрок под данным именем уже находится в игре");
			return Kick(playerid);
		}
	}
		
	for(new i = 0;i<=TOTALGZ;i++) GangZoneShowForPlayer(playerid,GZInfo[i][gid],GetGangZoneColor(i));
	if(test_server == false) {
		if(Platform[playerid] == 1) {
			new Name[30];
			format(Name, sizeof(Name), "%s[PC]", PlayerInfo[playerid][pName]); 
			SetPlayerName(playerid, Name);
		}
	}
	PlayerInfo[playerid][pID] = cache_get_field_content_int(0, "ID");
	PlayerInfo[playerid][pJailed] = cache_get_field_content_int(0, "Jailed");
	PlayerInfo[playerid][pJailTime] = cache_get_field_content_int(0, "JailTime");
	PlayerInfo[playerid][pMuted] = cache_get_field_content_int(0, "Muted");
	PlayerInfo[playerid][pMuteTime] = cache_get_field_content_int(0, "MuteTime");
	PlayerInfo[playerid][pFreshPrice] = cache_get_field_content_int(0, "FreshPrice");
	temp_int = cache_get_field_content_int(0, "Job");
	SetPlayerFraction(playerid, Fraction:temp_int);
	PlayerInfo[playerid][pSkin] = cache_get_field_content_int(0, "Skin");
	PlayerInfo[playerid][pSex] = cache_get_field_content_int(0, "Sex");
	PlayerInfo[playerid][pLicense] = cache_get_field_content_int(0, "License");
	PlayerInfo[playerid][pLicenseAir] = cache_get_field_content_int(0, "LicenseAir");
	PlayerInfo[playerid][pBank] = cache_get_field_content_int(0, "Bank");
	PlayerInfo[playerid][pDevice] = cache_get_field_content_int(0, "Device");
	PlayerInfo[playerid][pBalance] = cache_get_field_content_int(0, "Balance");
	PlayerInfo[playerid][pKarma] = cache_get_field_content_int(0, "Karma");
	PlayerInfo[playerid][pWanted] = cache_get_field_content_int(0, "Wanted");
	SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
	PlayerInfo[playerid][pFarmSkill] = cache_get_field_content_int(0, "FarmSkill");
	PlayerInfo[playerid][pBusSkill] = cache_get_field_content_int(0, "BusSkill");
	PlayerInfo[playerid][pAirSkill] = cache_get_field_content_int(0, "AirSkill");
	PlayerInfo[playerid][pCar] = cache_get_field_content_int(0, "Car");
	PlayerInfo[playerid][pCarCol] = cache_get_field_content_int(0, "CarCol");
	PlayerInfo[playerid][pCarCol2] = cache_get_field_content_int(0, "CarCol2");
	PlayerInfo[playerid][pTaxiTotal] = cache_get_field_content_int(0, "TaxiTotal");
	PlayerInfo[playerid][pOnline] = cache_get_field_content_int(0, "Online");
	SetPlayerEXP(playerid, cache_get_field_content_int(0, "Score"));
	PlayerInfo[playerid][pHours] = cache_get_field_content_int(0, "Hours");
	PlayerInfo[playerid][pColor] = cache_get_field_content_int(0, "Color");
	PlayerInfo[playerid][pDonate] = cache_get_field_content_int(0, "Donate");

	PlayerLogged{playerid} = true;

	format(small_string, sizeof(small_string), ""COLOR_YELLOW"Вы успешно авторизовались. Приятной игры, %s", PlayerInfo[playerid][pName]);
	SetPVarInt(playerid, "Logged", 1);
	UpdateSpawnInfo(playerid);
	TogglePlayerSpectating(playerid, false);
	SendClientMessage(playerid, -1, small_string);

	if(PlayerInfo[playerid][pAdmin] > 0) {
		format(small_string, sizeof(small_string), ""COLOR_RED"Администратор {FFFFFF}%s авторизовался", PlayerInfo[playerid][pName]);
		SendAdminMessage(-1, small_string);
		Iter_Add(Admin,playerid);// в админ авторизацию  er

	}

	if(PlayerInfo[playerid][pJailed] == 0) {
	format(small_string, sizeof(small_string), "~b~~h~Welcome,~n~~w~%s", PlayerInfo[playerid][pName]);
	GameTextForPlayer(playerid, small_string, 5000, 0);
	}

    if(Platform[playerid] == 0) {
	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 20, playerid);
	Streamer_SetVisibleItems(STREAMER_TYPE_MAP_ICON, 20, playerid);
	Streamer_SetVisibleItems(STREAMER_TYPE_PICKUP, 100, playerid);
	}
	if(Platform[playerid] == 1) {
	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 300, playerid);
	Streamer_SetVisibleItems(STREAMER_TYPE_PICKUP, 500, playerid);
	Streamer_SetVisibleItems(STREAMER_TYPE_MAP_ICON, 300, playerid);
	}
	
	CallLocalFunction("OnPlayerAuthorization", "i", playerid);
	CallLocalFunction("TD_OnPlayerAuthorization", "i", playerid);
	CallLocalFunction("LD_OnPlayerAuthorization", "i", playerid);
	PlayerTimerID[playerid] = KillTimer(PlayerTimerID[playerid]); 
	PlayerTimerID[playerid] = SetTimerEx("PlayerUpdate", 1000, false, "d", playerid);

	return 1;
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(GetPVarInt(playerid,"DialogID") != dialogid) return 1;
	DeletePVar(playerid, "DialogID");

	CallLocalFunction("TD_OnDialogResponse", "iiiis",playerid, dialogid, response, listitem, inputtext[0] ? inputtext : "\1\0");
	CallLocalFunction("OnPlayerDialogShowed", "iiiis", playerid, dialogid, response, listitem, inputtext[0] ? inputtext : "\1\0");
	
	switch(dialogid)
	{
	    case dRegister:
	    {
	        if(!response)
	        {
	            SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Оповещение", "{FFFFFF}Вы были кикнуты с сервера.\n{FF0000}}Причина: Отказ от регистрации", "Выход", "");
	            return Kick(playerid);
	        }
	        if(!strlen(inputtext)) return SPD(playerid, dRegister, DIALOG_STYLE_INPUT, "Регистрация на Chance RolePlay", "{FF0000}Ошибка: {FFFFFF}Вы не можете продолжить регистрацию не введя пароль!\nВведите пароль для регистрации нового аккаунта:\n{C0C0C0}Примечание:\n{666666}- Пароль чувствителен к регистру.\n- Пароль должен содержать от 4 до 30 символов.\n- Пароль может содержать латинские/кириллические символы и цифры (aA-zZ, аА-яЯ, 0-9).", "Далее", "Выход");
	        else if(strlen(inputtext) < 4) return SPD(playerid, dRegister, DIALOG_STYLE_INPUT, "Регистрация на Chance RolePlay", "{FF0000}Ошибка: {FFFFFF}Пароль слишком короткий!\nВведите пароль для регистрации нового аккаунта:\n{C0C0C0}Примечание:\n{666666}- Пароль чувствителен к регистру.\n- Пароль должен содержать от 4 до 30 символов.\n- Пароль может содержать латинские/кириллические символы и цифры (aA-zZ, аА-яЯ, 0-9).", "Далее", "Выход");
	        else if(strlen(inputtext) > 30) return SPD(playerid, dRegister, DIALOG_STYLE_INPUT, "Регистрация на Chance RolePlay", "{FF0000}Ошибка: {FFFFFF}Пароль слишком длинный!\nВведите пароль для регистрации нового аккаунта:\n{C0C0C0}Примечание:\n{666666}- Пароль чувствителен к регистру.\n- Пароль должен содержать от 4 до 30 символов.\n- Пароль может содержать латинские/кириллические символы и цифры (aA-zZ, аА-яЯ, 0-9).", "Далее", "Выход");
	        for(new i = strlen(inputtext)-1; i != -1; i--)
	        {
	            switch(inputtext[i])
	            {
	                case '0'..'9', 'a'..'z', 'A'..'Z': continue;
	                default: return SPD(playerid, dRegister, DIALOG_STYLE_INPUT, "Регистрация на Chance RolePlay", "{FF0000}Ошибка: {FFFFFF}Пароль содержит запрещённые символы!\nВведите пароль для регистрации нового аккаунта:\n{C0C0C0}Примечание:\n{666666}- Пароль чувствителен к регистру.\n- Пароль должен содержать от 4 до 30 символов.\n- Пароль может содержать только латинские символы и цифры (aA-zZ, 0-9).", "Далее", "Выход");
	            }
	        }
	        PlayerInfo[playerid][pPassword][0] = EOS;
	        strins(PlayerInfo[playerid][pPassword], inputtext, 0);
	        SPD(playerid, dEmail, DIALOG_STYLE_INPUT, "Регистрация на Chance RolePlay", "{FFFFFF}Введите Email для регистрации нового аккаунта:", "Далее", "Выход");
	        return 1;
	    }
	    case dEmail:
	    {
	        if(!response)
	        {
	            SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Оповещение", "{FFFFFF}Вы были кикнуты с сервера.\n{FF0000}Причина: Отказ от регистрации", "Выход", "");
	            return Kick(playerid);
	        }
	      	if(strlen(inputtext) < 6) return SPD(playerid, dEmail, DIALOG_STYLE_INPUT, "Регистрация на Chance RolePlay", "{FF0000}Ошибка: {FFFFFF}Email слишком короткий!\nВведите Email для регистрации нового аккаунта:", "Далее", "Выход");
	        else if(strlen(inputtext) > 30) return SPD(playerid, dEmail, DIALOG_STYLE_INPUT, "Регистрация на Chance RolePlay", "{FF0000}Ошибка: {FFFFFF}Email слишком длинный!\nВведите Email для регистрации нового аккаунта:", "Далее", "Выход");
	        else if(IsValidEmail(inputtext) == 0)return SPD(playerid, dEmail, DIALOG_STYLE_INPUT, "Регистрация на Chance RolePlay", "{FF0000}Ошибка: {FFFFFF}Указан недействительный почтовый адрес!\nВведите Email для регистрации нового аккаунта:", "Далее", "Выход");
            static const fmt_str_0[] =
            	"SELECT Email FROM "TABLE_ACCOUNTS" WHERE Email='%e' LIMIT 1";

            mysql_format(database,
            	small_string, sizeof(small_string),
            	fmt_str_0,
            		inputtext
            );

            new Cache: result = mysql_query(database, small_string, true);
            new rows = cache_get_row_count();
            if(rows) {
                SPD(playerid, dEmail, DIALOG_STYLE_INPUT, "Регистрация на Chance RolePlay", "{FF0000}Ошибка: {FFFFFF}Почтовый адрес уже был использован для регистрации!\nВведите Email для регистрации нового аккаунта:", "Далее", "Выход");
                return cache_delete(result);
           	}
            cache_delete(result);

	        PlayerInfo[playerid][pEmail][0] = EOS;
	        strins(PlayerInfo[playerid][pEmail], inputtext, 0);
	        SPD(playerid, dSex, DIALOG_STYLE_MSGBOX, "Регистрация на Chance RolePlay", "{FFFFFF}Выберите пол для вашего персонажа", "Мужчина", "Женщина");
	        return 1;
	    }
	    case dSex:
	    {
	        if(!response)
	        {
				PlayerInfo[playerid][pSex] = 1;
				return CreateNewAccount(playerid, PlayerInfo[playerid][pPassword], PlayerInfo[playerid][pEmail]);
	        }
	        else {
	        	PlayerInfo[playerid][pSex] = 0;
	        	return CreateNewAccount(playerid, PlayerInfo[playerid][pPassword], PlayerInfo[playerid][pEmail]);
	        }
	    }	
		case dNullKarma: 
	    {
	    	if(response) {
	    		CNull(playerid);
	    	}
	    	return 1;
	    }		
	    case dInviting: {
	    	if(response) {
	    	CInvite(playerid);
	    	}
	    	return 1;
	    }		
	    case dLogin:  {
	        if(!response)
	        {
	            SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "Оповещение", "{FFFFFF}Вы были кикнуты с сервера.\n{FF0000}Причина: Отказ от авторизации.\n{FFFFFF}Для выхода с сервера введите \"/q\" в чат", "Выход", "");
	            return Kick(playerid);
	        }
	        if(!strlen(inputtext)) return SPD(playerid, dLogin, DIALOG_STYLE_INPUT, "Вход в аккаунт", "{FF0000}Ошибка: {FFFFFF}Вы не можете продолжить авторизацию не введя пароль!\nВведите пароль от аккаунта для входа на сервер:", "Вход", "Выход");
	        if(!strcmp(PlayerInfo[playerid][pPassword], inputtext))
	        {
	            new query_string[49+MAX_PLAYER_NAME];
	            format(query_string, sizeof(query_string), "SELECT * FROM "TABLE_ACCOUNTS" WHERE `Name` = '%s'", PlayerInfo[playerid][pName]);
	            mysql_tquery(database, query_string, "UploadPlayerAccount","i", playerid);
	        }
	        else
	        {
	            switch(GetPVarInt(playerid, "WrongPassword"))
	            {
	                case 0: SPD(playerid, dLogin, DIALOG_STYLE_INPUT, "Вход в аккаунт", "{FF0000}Ошибка: {FFFFFF}Вы ввели неверный пароль! У Вас осталось 3 попытки.\nВведите пароль от аккаунта для входа на сервер:", "Вход", "Выход");
	                case 1: SPD(playerid, dLogin, DIALOG_STYLE_INPUT, "Вход в аккаунт", "{FF0000}Ошибка: {FFFFFF}Вы ввели неверный пароль! У Вас осталось 2 попытки.\nВведите пароль от аккаунта для входа на сервер:", "Вход", "Выход");
	                case 2: SPD(playerid, dLogin, DIALOG_STYLE_INPUT, "Вход в аккаунт", "{FF0000}Ошибка: {FFFFFF}Вы ввели неверный пароль! У Вас осталась последняя попытка, после чего Вас кикнет.\nВведите пароль от аккаунта для входа на сервер:", "Вход", "Выход");
	                default:
	                {
	                    SPD(playerid, dKickMessage, DIALOG_STYLE_MSGBOX, "", "{FFFFFF}Вы были кикнуты с сервера.\n{FF0000}Причина: Превышен лимит попыток на ввод пароля.\n{FFFFFF}Для выхода с сервера введите \"/q\" в чат", "Выход", "");
	                    return Kick(playerid);
	                }
	            }
	            SetPVarInt(playerid, "WrongPassword", GetPVarInt(playerid, "WrongPassword")+1);
	        }
	        return 1;
	    }
		case dAnim:
		{
			if(!response) return true;
			switch(listitem)
			{
				case 0: SetPlayerSpecialAction (playerid, SPECIAL_ACTION_DANCE1),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 1: SetPlayerSpecialAction (playerid, SPECIAL_ACTION_DANCE2),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 2: SetPlayerSpecialAction (playerid, SPECIAL_ACTION_DANCE3),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 3: SetPlayerSpecialAction (playerid, SPECIAL_ACTION_DANCE4),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 4: GoAnim(playerid,"DEALER","Dealer_idle",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 5: ApplyAnimation(playerid,"DEALER","Dealer_Deal",4.1,0,0,0,0,0,1);
				case 6: ApplyAnimation(playerid,"FOOD","Eat_Burger",4.1,0,0,0,0,0,1),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 7: ApplyAnimation(playerid,"PAULNMAC","Piss_in",4.1,0,0,0,0,0,1);
				case 8: GoAnim(playerid,"PARK","Tai_Chi_Loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 9: GoAnim(playerid,"CRACK","Crckidle1",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 10: GoAnim(playerid,"CRACK","Crckidle2",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 11: GoAnim(playerid,"CRACK","Crckidle4",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 12: ApplyAnimation(playerid,"SWEET","sweet_ass_slap",4.1,0,0,0,0,0,1);
				case 13: GoAnim(playerid,"SPRAYCAN","spraycan_full",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 14: GoAnim(playerid,"GRAFFITI","spraycan_fire",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 15: GoAnim(playerid,"SMOKING","M_smkstnd_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 16: GoAnim(playerid,"SHOP","ROB_Loop_Threat",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 17: ApplyAnimation(playerid,"SHOP","ROB_shifty",4.1,0,0,0,0,0,1);
				case 18: GoAnim(playerid,"SHOP","SHP_Rob_HandsUP",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 19: GoAnim(playerid,"RYDER","Ryd_Beckon_02",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 20: ApplyAnimation(playerid,"RIOT","Riot_Angry",4.1,0,0,0,0,0,0);
				case 21: GoAnim(playerid,"RIOT","Riot_Angry_B",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 22: GoAnim(playerid,"RIOT","Riot_Chant",4.1,1,1,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 23: GoAnim(playerid,"RIOT","Riot_Punches",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 24: ApplyAnimation(playerid,"PED","fucku",4.1,0,0,0,0,0,1);
				case 25: ApplyAnimation(playerid,"BAR","dnK_StndM_loop",4.1,0,0,0,0,0,1);
				case 26: GoAnim(playerid,"BD_FIRE","BD_Panic_03",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 27: GoAnim(playerid,"BD_FIRE","M_smklean_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 28: GoAnim(playerid,"BEACH","bather",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 29: GoAnim(playerid,"BEACH","Lay_Bac_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 30: GoAnim(playerid,"BEACH","Parksit_w_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 31: GoAnim(playerid,"BEACH","Sitnwait_Loop_W",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 32: GoAnim(playerid,"BEACH","Parksit_M_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 33: GoAnim(playerid,"benchpress","gym_bp_celebrate",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 34: GoAnim(playerid,"LOWRIDER","Rap_C_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 35: GoAnim(playerid,"LOWRIDER","Rap_B_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 36: GoAnim(playerid,"LOWRIDER","Rap_A_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 37: GoAnim(playerid,"BSKTBALL","BBALL_idleloop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 38: ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.1,0,0,0,0,0,1),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 39: ApplyAnimation(playerid,"BSKTBALL","BBALL_pickup",4.1,0,0,0,0,0,1);
				case 40: ApplyAnimation(playerid,"CAMERA","camstnd_cmon",4.1,0,0,0,0,0,1);
				case 41: GoAnim(playerid,"CAR","fixn_car_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 42: GoAnim(playerid,"CAR_CHAT","car_talkm_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 43: GoAnim(playerid,"COP_AMBIENT","coplook_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 44: GoAnim(playerid,"CRACK","Bbalbat_Idle_01",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 45: GoAnim(playerid,"CRACK","Bbalbat_Idle_02",4.1,1,0,0,0,0,0);
				case 46: ApplyAnimation(playerid,"GHANDS","gsign1",4.1,0,0,0,0,0,1);
				case 47: ApplyAnimation(playerid,"GHANDS","gsign2",4.1,0,0,0,0,0,1);
				case 48: ApplyAnimation(playerid,"GHANDS","gsign3",4.1,0,0,0,0,0,1);
				case 49: ApplyAnimation(playerid,"GHANDS","gsign4",4.1,0,0,0,0,0,1);
				case 50: ApplyAnimation(playerid,"GHANDS","gsign5",4.1,0,0,0,0,0,1);
				case 51: ApplyAnimation(playerid,"GHANDS","gsign1LH",4.1,0,0,0,0,0,1);
				case 52: ApplyAnimation(playerid,"GHANDS","gsign2LH",4.1,0,0,0,0,0,1);
				case 53: ApplyAnimation(playerid,"GHANDS","gsign4LH",4.1,0,0,0,0,0,1);
				case 54: GoAnim(playerid,"GRAVEYARD","mrnF_loop",4.1,1,0,0,0,0,0);
				case 55: GoAnim(playerid,"MISC","seat_LR",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 56: GoAnim(playerid,"INT_HOUSE","Lou_in",4.1,0,1,1,1,1,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 57: GoAnim(playerid,"INT_OFFICE","OFF_sit_Bored_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 58: GoAnim(playerid,"LOWRIDER","F_smklean_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 59: ApplyAnimation(playerid,"MEDIC","CPR",4.1,0,0,0,0,0,1),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 60: GoAnim(playerid,"GANGS","LeanIn",4.1,0,1,1,1,1,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 61: GoAnim(playerid,"MISC","plyrlean_loop",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
				case 62: ApplyAnimation(playerid,"MISC","plyr_shkhead",4.1,0,0,0,0,0,1);
				case 63: GoAnim(playerid,"MISC","scratchballs_01",4.1,1,0,0,0,0,0),GameTextForPlayer(playerid, "To stop\npress Enter", 2000, 4);
			}
			SetPVarInt(playerid,"Animation", 1);
			return true;
		}
		case dMenu: {
			if(!response) {
				return 1;
			}
			if(response) {
				switch(listitem) {
					case 0: {
						return ShowStats(playerid, playerid);
					}
					case 1: callcmd::gps(playerid,"\0");
					case 2: {
						SPD(playerid, dSupport, DIALOG_STYLE_LIST,"Помощь","1. Список команд\n2. Правила сервера\n3. Справка","Выбрать","Назад");
					}
					case 3: {
						return SPD(playerid, dMenuFeedback, DIALOG_STYLE_LIST, ""COLOR_BLUE"Связь с администрацией","1. Написать администрации в сети\n2. Оставить сообщение о баге\n3. Предложить улучшение", "Выбрать", "Отмена");
					}
					case 4: SPD(playerid, 0, DIALOG_STYLE_MSGBOX,"Информация","{FFFFFF}Купить EXP за реальную валюту можно на нашем сайте: "COLOR_BLUE"ChanceRp.Ru","Закрыть","");
					case 5: SPD(playerid, dMenuSettings, DIALOG_STYLE_LIST, "Настройки","1. Цвет оформления", "Выбрать", "Отмена");
						
				}
			}
			return 1;
		}
		case dStats: {
			if(!response) {
				return 1;
			}
			if(response) {
				return callcmd::mn(playerid,"\0");
			}
		}
		case dMenuAdaptive: {
			if(!response) return 1;
			if(response)
			{
			    if(inputtext[0] == '1') {
			        return ShowStats(playerid, playerid);
			    }
			    else if(inputtext[0] == '2') {
			    	return SPD(playerid, dMenuAdaptive, DIALOG_STYLE_INPUT,"Главное меню","1. Паспорт персонажа\n2. Навигатор\n3. Помощь\n3. Связь с администрацией\n4. Донат\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Выбрать", "Отмена");
			    }
			    else if(inputtext[0] == '3') {
					return SPD(playerid, dSupportAdaptive, DIALOG_STYLE_INPUT,"Помощь","1. Список команд\n2. Правила сервера\n3. Справка\n\n"COLOR_BLUE"Введите цифру выбранного пункта","Выбрать","Назад");
			    }
				else if(inputtext[0] == '4') {
					return SPD(playerid, dMenuFeedbackAdaptive, DIALOG_STYLE_INPUT,"Связь с администрацией","1. Написать администрации в сети\n2. Оставить сообщение о баге\n3. Предложить улучшение\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Выбрать", "Отмена");
			    	
			    }
				else if(inputtext[0] == '5') {
			    	return SPD(playerid, 0, DIALOG_STYLE_MSGBOX,"Информация","{FFFFFF}Купить EXP за реальную валюту можно на нашем сайте: "COLOR_BLUE"ChanceRp.Ru","Закрыть","");
					
			    }
			}
			return 1;
		}
		case dLicense: {
			if(!response) return 1;
			if(response) {
				switch(listitem) {
					case 0: {
		    		if(PlayerInfo[playerid][pLicense] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У Вас уже имеются водительские права");
					if(CheckCash(playerid, 50) == false) return SendClientMessage(playerid, -1, ""COLOR_RED"Недостаточно средств");
					Player.DownEXP(PlayerInfo[playerid][pID], 50, E_LEASE_CAR, playerid);
				    SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали авто-сдачу на права. Пройдите в учебный автомобиль");
				   	SetPVarInt(playerid,"GetLic", 1);
		    		return 1;
			    	}
			    	case 1: {
		    		if(PlayerInfo[playerid][pLicenseAir] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У Вас уже имеется удостоверение пилота");
					if(CheckCash(playerid, 250) == false) return SendClientMessage(playerid, -1, ""COLOR_RED"Недостаточно средств");
					Player.DownEXP(PlayerInfo[playerid][pID], 250, E_LEASE_FLY, playerid);
				    SendClientMessage(playerid, -1, ""COLOR_ORANGE"Пройдите в учебный самолет на заднем дворе");
				   	SetPVarInt(playerid,"GetLicAir", 1);
		    		return 1;
			    }
				}
				return 1;
			}
		}
		case dLicenseAdaptive: {
			if(!response) return 1;
			if(response)
			{
				new inputtext_int = strval(inputtext);
				
			    if(inputtext_int == 1) {
		    		if(PlayerInfo[playerid][pLicense] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У Вас уже имеются водительские права");
					if(CheckCash(playerid, 50) == false) return SendClientMessage(playerid, -1, ""COLOR_RED"Недостаточно средств");
					Player.DownEXP(PlayerInfo[playerid][pID], 50, E_LEASE_CAR, playerid);
				    SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы начали авто-сдачу на права. Пройдите в учебный автомобиль");
				   	SetPVarInt(playerid,"GetLic", 1);
		    		return 1;
			    }
			    if(inputtext_int == 2) {
		    		if(PlayerInfo[playerid][pLicenseAir] == 1) return SendClientMessage(playerid, -1, ""COLOR_RED"У Вас уже имеется удостоверение пилота");
					if(CheckCash(playerid, 250) == false) return SendClientMessage(playerid, -1, ""COLOR_RED"Недостаточно средств");
					Player.DownEXP(PlayerInfo[playerid][pID], 250, E_LEASE_FLY, playerid);
				    SendClientMessage(playerid, -1, ""COLOR_ORANGE"Пройдите в учебный самолет на заднем дворе");
				   	SetPVarInt(playerid,"GetLicAir", 1);
		    		return 1;
			    }
			}
			return 1;
		}	    
 		case dShop: {
		if(!response) return 1;
		if(response)
		{
			switch(listitem)
			{
				case 0: {
			    	if(PlayerInfo[playerid][pDevice] == 1) {
			    		SPD(playerid, dShop, DIALOG_STYLE_LIST, "Ассортимент", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP", "Купить", "Выход");
			    		SendClientMessage(playerid, -1, ""COLOR_RED"У Вас уже есть пейджер");
			    		return 1;
			    	}
			        if(CheckCash(playerid, 250) == false) return 1;	
			        Player.DownEXP(PlayerInfo[playerid][pID], 250, E_BUY_PAGER, playerid);
			        SPD(playerid, dShop, DIALOG_STYLE_LIST, "Ассортимент", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP", "Купить", "Выход");
			    	SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы купили пейджер. Возпользоваться: {FFFFFF}/sms [id]");
			        PlayerInfo[playerid][pDevice] = 1;
					SetPlayerInt(playerid, "Device", PlayerInfo[playerid][pDevice]); 
			    }
			    case 1: {
			    	if(PlayerInfo[playerid][pDevice] == 2) {
			    		SPD(playerid, dShop, DIALOG_STYLE_LIST, "Ассортимент", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP", "Купить", "Выход");
			    		SendClientMessage(playerid, -1, ""COLOR_RED"У Вас уже есть телефон");
			    		return 1;
			    	}
			        if(CheckCash(playerid, 2000) == false) return 1;	
			       	Player.DownEXP(PlayerInfo[playerid][pID], 2000, E_BUY_PHONE, playerid);
			        SPD(playerid, dShop, DIALOG_STYLE_LIST, "Ассортимент", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP", "Купить", "Выход");
			    	SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы купили телефон. Возпользоваться: {FFFFFF}/sms [id]");
			        PlayerInfo[playerid][pDevice] = 2;
					SetPlayerInt(playerid, "Device", PlayerInfo[playerid][pDevice]); 
			    }
			    case 2: {
			 	    if(GetPVarInt(playerid,"Mask") > 0) {
			 	    	SPD(playerid, dShop, DIALOG_STYLE_LIST, "Ассортимент", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP", "Купить", "Выход");
			    		SendClientMessage(playerid, -1, ""COLOR_RED"На вас уже надета маска");
			  			return 1;
			 	    }
			  		if(CheckCash(playerid, 100) == false) return 1;
					Player.DownEXP(PlayerInfo[playerid][pID], 100, E_BUY_MASK, playerid);
					SetPlayerChatBubble(playerid, "надевает маску", C_PURPLE, 10.0, 2000);
					ApplyAnimation(playerid,"SHOP","ROB_shifty",4.1,0,0,0,0,0,1);
					SetPlayerColor(playerid, 0x7a766700);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили и надели маску. Местоположение скрыто");
					SetPVarInt(playerid,"Mask", 1);
				}
			}
		}
		return 1;
		}
 		case dShopAdaptive: {
			if(!response) return 1;
			if(response)
			{
			    if(inputtext[0] == '1') {
			    	if(PlayerInfo[playerid][pDevice] == 1) {
			    		SPD(playerid, dShopAdaptive, DIALOG_STYLE_INPUT, "Ассортимент", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Купить", "Выход");
			    		SendClientMessage(playerid, -1, ""COLOR_RED"У Вас уже есть пейджер");
			    		return 1;
			    	}
			        if(CheckCash(playerid, 250) == false) return 1;	
			        Player.DownEXP(PlayerInfo[playerid][pID], 250, E_BUY_PAGER, playerid);
			        SPD(playerid, dShopAdaptive, DIALOG_STYLE_INPUT, "Ассортимент", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Купить", "Выход");
			        SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы купили пейджер. Возпользоваться: {FFFFFF}/sms [id]");
			        PlayerInfo[playerid][pDevice] = 1;
					SetPlayerInt(playerid, "Device", PlayerInfo[playerid][pDevice]); 
			    }
			    if(inputtext[0] == '2') {
			    	if(PlayerInfo[playerid][pDevice] == 2) {
			    		SPD(playerid, dShopAdaptive, DIALOG_STYLE_INPUT, "Ассортимент", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Купить", "Выход");
			    		SendClientMessage(playerid, -1, ""COLOR_RED"У Вас уже есть телефон");
			    		return 1;
			    	}
			        if(CheckCash(playerid, 2000) == false) return 1;	
			        Player.DownEXP(PlayerInfo[playerid][pID], 2000, E_BUY_PHONE, playerid);
			        SPD(playerid, dShopAdaptive, DIALOG_STYLE_INPUT, "Ассортимент", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Купить", "Выход");
			        SendClientMessage(playerid, -1, ""COLOR_GREEN"Поздравляем! Вы купили телефон. Возпользоваться: {FFFFFF}/sms [id]");
			        PlayerInfo[playerid][pDevice] = 2;
					SetPlayerInt(playerid, "Device", PlayerInfo[playerid][pDevice]); 
			    }
			    else if(inputtext[0] == '3') {
			 	    if(GetPVarInt(playerid,"Mask") > 0) {
			 	    	SPD(playerid, dShopAdaptive, DIALOG_STYLE_INPUT, "Ассортимент", "{FFFFFF}1. Пейджер - 250 EXP\n2. Телефон - 2000 EXP\n3. Маска - 100 EXP\n\n"COLOR_BLUE"Введите цифру выбранного пункта", "Купить", "Выход");
			  			SendClientMessage(playerid, -1, ""COLOR_RED"На вас уже надета маска");
			  			return 1;
			 	    }
			  		if(CheckCash(playerid, 100) == false) return 1;
					Player.DownEXP(PlayerInfo[playerid][pID], 100, E_BUY_MASK, playerid);
					SetPlayerChatBubble(playerid, "надевает маску", C_PURPLE, 10.0, 2000);
					ApplyAnimation(playerid,"SHOP","ROB_shifty",4.1,0,0,0,0,0,1);
					SetPlayerColor(playerid, 0x7a766700);
					SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили и надели маску. Местоположение скрыто");
					SetPVarInt(playerid,"Mask", 1);
				}
			}
			return 1;
		}
		case dName: {
			if(!response) return 1;
			if(response) {
				new nick[MAX_PLAYER_NAME];
				format(nick,sizeof(nick),"%s",inputtext);
				if(IsRpNickname(nick) == 0)
				{
					SendClientMessage(playerid, -1, ""COLOR_RED"Используйте ник формата: {FFFFFF}Имя_Фамилия");
					return SPD(playerid, dName, DIALOG_STYLE_INPUT, "Добро пожаловать!", "Введите ваш ник (Используйте формат: Имя_Фамилия)", "Далее", "");
				}
				SetPlayerName(playerid, nick);
				LoadAccounts(playerid);
			}
			return 1;
		}
		case dBank: {
			if(!response) return 1;
			if(response)
			{
			    if(inputtext[0] == '1') {
			        return SPD(playerid, dBankRecieve, DIALOG_STYLE_INPUT,"Снять средства","{FFFFFF}Введите сумму которую вы хотите снять","Снять","Отмена");
			    }
			    if(inputtext[0] == '2') {
			        return SPD(playerid, dBankPut, DIALOG_STYLE_INPUT,"Положить средства","{FFFFFF}Введите сумму которую вы хотите положить","Далее","Отмена");
			    }
			    else if(inputtext[0] == '3') {
			    	return SPD(playerid, dBankPayPhone, DIALOG_STYLE_INPUT,"Пополнить счет мобильного","{FFFFFF}Введите сумму которую вы хотите положить на счет\n\n"COLOR_ORANGE"Внимание: Принимаются только наличные","Далее","Отмена");
			    }
			}
			return 1;
		}
		case dBankRecieve: {
			if(!response) return 1;
			if(response)
			{
				if(strval(inputtext) > PlayerInfo[playerid][pBank] || strval(inputtext) <= 0) return SPD(playerid, 0, DIALOG_STYLE_MSGBOX,"Ошибка",""COLOR_RED"Операция не выполнена","Закрыть",""), PlayerPlaySound(playerid, 31201, 0, 0, 0);
				RemovePlayerBankEXP(playerid, strval(inputtext));
				Player.AddEXP(PlayerInfo[playerid][pID], strval(inputtext), E_ADD_CASH_BANK, playerid);	
				SPD(playerid, 0, DIALOG_STYLE_MSGBOX,"Успешно",""COLOR_GREEN"Операция проведена успешно","Закрыть","");
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
			}
			return 1;
		}		
		case dBankPut: {
			if(!response) return 1;
			if(response)
			{
				if(strval(inputtext) > GetPlayerEXP(playerid) || strval(inputtext) <= 0) return SPD(playerid, 0, DIALOG_STYLE_MSGBOX,"Ошибка",""COLOR_RED"Операция не выполнена","Закрыть",""), PlayerPlaySound(playerid, 31201, 0, 0, 0);
				Player.DownEXP(PlayerInfo[playerid][pID], strval(inputtext), E_PUT_BANK, playerid);
				AddPlayerBankEXP(playerid, strval(inputtext));	
				SPD(playerid, 0, DIALOG_STYLE_MSGBOX,"Успешно",""COLOR_GREEN"Операция проведена успешно","Закрыть","");
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
			}
			return 1;
		}
		case dBankPayPhone: {
			if(!response) return 1;
			if(response)
			{
				if(PlayerInfo[playerid][pDevice] == 0) return SendClientMessage(playerid, -1, ""COLOR_RED"У вас нет мобильного средства связи");
				if(strval(inputtext) > GetPlayerEXP(playerid) || strval(inputtext) <= 0) return SPD(playerid, 0, DIALOG_STYLE_MSGBOX,"Ошибка",""COLOR_RED"Попробуйте снова","Закрыть",""), PlayerPlaySound(playerid, 31201, 0, 0, 0);
				Player.DownEXP(PlayerInfo[playerid][pID], strval(inputtext), E_BALANCE_PHONE, playerid);
				PlayerInfo[playerid][pBalance] += strval(inputtext);
				SetPlayerInt(playerid, "Balance", PlayerInfo[playerid][pBalance]); 
				SPD(playerid, 0, DIALOG_STYLE_MSGBOX,"Успешно",""COLOR_GREEN"Операция проведена успешно","Закрыть","");
				PlayerPlaySound(playerid, 20804,0,0,0);
				format(small_string, sizeof(small_string), "SMS: Ваш баланс был пополнен на %d EXP. Отправитель: Провайдер", strval(inputtext));
				SendClientMessage(playerid, 0xF5DEB3AA, small_string);
			}
			return 1;
		}			
		case dSupportAdaptive: {
			if(!response) return callcmd::mn(playerid,"\0");
			if(response)
			{
				new 
					value = strval(inputtext);

			    if(value == '1') {
			        return SPD(playerid, dCommandList, DIALOG_STYLE_MSGBOX,"Информация",""COLOR_BLUE"Основные команды:\n{FFFFFF}/sms - отправить сообщение\n/time - узнать время\n/gps - навигатор\n/id - поиск игрока\n/eject - выкинуть из машины","Назад","Далее");
			    }
			    else if(value == '2') {
			    	return SPD(playerid, dRules, DIALOG_STYLE_MSGBOX, "Главное меню",""COLOR_RED"На сервере запрещено:\n{FFFFFF}Использование постороннего ПО, дающего преимущество (любого рода) над другими игроками\nРеклама / Оффтоп / Флуд / Caps Lock в игровые чаты\nНанесение урона игрокам при помощи транспортного средства\nУбийство игроков без RolePlay причины\nНеадекватное и токсичное поведение\nОскорбление игроков / родных\nРазжигание межнациональной розни\nОбман администрации\nПомеха игровому процессу других игроков (под этим также понимается нарушение RolePlay режима)\nПередача аккаунтов / игровой недвижимости и валюты", "Назад", "");
			    }
			    else if(value == '3') {
					SPD(playerid, dRules, DIALOG_STYLE_MSGBOX,"Справка","Более подробно ознакомиться с функционалом сервера можно на портале: "COLOR_BLUE"wiki.chancerp.ru","Назад","");
			    }
			}
			return 1;
		}
		case dSupport: {
			if(!response) return callcmd::mn(playerid,"\0");
			switch(listitem)
			{
			    case 0: {
			        return SPD(playerid, dCommandList, DIALOG_STYLE_MSGBOX,"Информация",""COLOR_BLUE"Основные команды:\n{FFFFFF}/sms - отправить сообщение\n/time - узнать время\n/gps - навигатор\n/id - поиск игрока\n/eject - выкинуть из машины","Назад","Далее");
			    }
			    case 1: {
			    	return SPD(playerid, dRules, DIALOG_STYLE_MSGBOX, "Главное меню",""COLOR_RED"На сервере запрещено:\n{FFFFFF}Использование постороннего ПО, дающего преимущество (любого рода) над другими игроками\nРеклама / Оффтоп / Флуд / Caps Lock в игровые чаты\nНанесение урона игрокам при помощи транспортного средства\nУбийство игроков без RolePlay причины\nНеадекватное и токсичное поведение\nОскорбление игроков / родных\nРазжигание межнациональной розни\nОбман администрации\nПомеха игровому процессу других игроков (под этим также понимается нарушение RolePlay режима)\nПередача аккаунтов / игровой недвижимости и валюты", "Назад", "");
			    }
			    case 2: {
					return SPD(playerid, dRules, DIALOG_STYLE_MSGBOX,"Справка","Более подробно ознакомиться с функционалом сервера можно на портале: "COLOR_BLUE"wiki.chancerp.ru","Назад","");
			    }
			}
			return 1;
		}
		case dRules: {
			if(!response) {
				SPD(playerid, dSupportAdaptive, DIALOG_STYLE_INPUT,"Помощь","1. Список команд\n2. Правила сервера\n3. Справка","Выбрать","Назад");
			}
			if(response) {
				SPD(playerid, dSupportAdaptive, DIALOG_STYLE_INPUT,"Помощь","1. Список команд\n2. Правила сервера\n3. Справка","Выбрать","Назад");
			}
			return 1;
		}
		case dCommandList: {
				if(!response) {					
					SPD(playerid, dCommandList2, DIALOG_STYLE_MSGBOX,"Информация",""COLOR_BLUE"Команды отыгровки:\n{FFFFFF}/anim - анимации\n/me - сообщение о себе от третьего лица\n/s - кричать\n/w - шептать\n/n - локальный OOC чат\n/do - описание происходящего вокруг\n/try - действие (удачно/неудачно)","Назад","Далее");
				
					}
				if(response) {
					if(Platform[playerid] == 1) return SPD(playerid, dSupport, DIALOG_STYLE_LIST,"Помощь","1. Список команд\n2. Правила сервера\n3. Справка","Выбрать","Назад");
					SPD(playerid, dSupportAdaptive, DIALOG_STYLE_INPUT,"Помощь","1. Список команд\n2. Правила сервера\n3. Справка\n\n"COLOR_BLUE"Введите цифру выбранного пункта","Выбрать","Назад");
				}
				return 1;
		}
		case dCommandList2: {
				if(!response) {
					SPD(playerid, dCommandList3, DIALOG_STYLE_MSGBOX,"Информация",""COLOR_BLUE"Команды транспорта:\n{FFFFFF}/lock - замок автомобиля\n/eject - выкинуть из авто\n\n"COLOR_BLUE"Команды полиции:{FFFFFF}\n/(t)aser - оглушить\n/cuff - надеть наручники\n/arrest - арестовать","Назад","Закрыть");
				}
				if(response) {
					return SPD(playerid, dCommandList, DIALOG_STYLE_MSGBOX,"Информация",""COLOR_BLUE"Основные команды:\n{FFFFFF}/sms - отправить сообщение\n/time - узнать время\n/gps - навигатор\n/id - поиск игрока\n/eject - выкинуть из машины\n/lock - замок личного транспорта","Назад","Далее");			
				}
				return 1;
		}
		case dCommandList3: {
				if(!response) {
						return 1;
				}
				if(response) {
					SPD(playerid, dCommandList2, DIALOG_STYLE_MSGBOX,"Информация",""COLOR_BLUE"Команды отыгровки:\n{FFFFFF}/anim - анимации\n/me - сообщение о себе от третьего лица\n/s - кричать\n/w - шептать\n/n - локальный OOC чат\n/do - описание происходящего вокруг\n/try - действие (удачно/неудачно)","Назад","Далее");
				
				}
				return 1;
		}
		case dMenuSettings: {
			if(!response) {
					return callcmd::mn(playerid,"\0");
				}
			if(response) {
				switch(listitem) {
					case 0: callcmd::selectcolor(playerid,"\0");
				}
			}
			return 1;
		}
		case dMenuFeedbackAdaptive: {
			if(!response) { callcmd::mn(playerid,"\0"); }
			if(response)
			{
			    if(inputtext[0] == '1') {
			        return 	SPD(playerid,
					dMenuReport, DIALOG_STYLE_INPUT,
					!"Связь с администрацией",
					"{ffffff}Введите свое сообщение для администраторов сервера\n\
					Оно должно быть кратким и отображать суть Вашего обращения\n\n\
					"COLOR_GREEN"Если Вы хотите подать жалобу на игрока, в этом случае\n\
					Вам будет необходимо указать его ID",
					!"Далее", !"Назад"
				);
			    }
			    else if(inputtext[0] == '2') {
			    	return SPD(playerid,
					dMenuBug, DIALOG_STYLE_INPUT,
					!"Сообщить о баге",
					"Подробно опишите найденную Вами недоработку\n\n\
					"COLOR_GREEN"Если вы первый нашли важную недоработку,\n\
					возможно вы получите вознаграждение",
					!"Отправить", !"Назад"
				);
			    }
				else if(inputtext[0] == '3') {
					SPD(playerid,
					dMenuSug, DIALOG_STYLE_INPUT,
					!"Предложить улучшение",
					"{ffffff}Подробно опишите ваше улучшение и для чего оно нужно\n\n\
					"COLOR_GREEN"Повторяться, предлагать чужие и старые идеи\n\
					не стоит, не тратьте своё время",
					!"Отправить", !"Назад"
				);	
			    }
			}
			return 1;
		}				
		case dMenuFeedback: {
			if(!response) {
				return callcmd::mn(playerid,"\0");
			}
			if(response) {
				switch(listitem) {
					case 0: {
						SPD(playerid,
							dMenuReport, DIALOG_STYLE_INPUT,
							!"Связь с администрацией",
							"{ffffff}Введите свое сообщение для администраторов сервера\n\
							Оно должно быть кратким и отображать суть Вашего обращения\n\n\
							"COLOR_GREEN"Если Вы хотите подать жалобу на игрока, в этом случае\n\
							Вам будет необходимо указать его ID",
							!"Далее", !"Назад"
						);
					}
					case 1: { SPD(playerid,
							dMenuBug, DIALOG_STYLE_INPUT,
							!"Сообщить о баге",
							"Подробно опишите найденную Вами недоработку\n\n\
							"COLOR_GREEN"Если вы первый нашли важную недоработку,\n\
							возможно вы получите вознаграждение",
							!"Отправить", !"Назад"
						);
					}
					case 2: {SPD(playerid,
							dMenuSug, DIALOG_STYLE_INPUT,
							!"Предложить улучшение",
							"{ffffff}Подробно опишите ваше улучшение и для чего оно нужно\n\n\
							"COLOR_GREEN"Повторяться, предлагать чужие и старые идеи\n\
							не стоит, не тратьте своё время",
							!"Отправить", !"Назад"
						);
					}
				}
			}
			return 1;
		}
		case dMenuBug:
		{
			if(!response) {
				return SPD(playerid, dMenuFeedback, DIALOG_STYLE_LIST, ""COLOR_BLUE"Связь с администрацией","1. Написать администрации в сети\n2. Оставить сообщение о баге\n3. Предложить улучшение", "Выбрать", "Отмена");
			}
			if(response) {
				new string_length = strlen(inputtext);
	     		if(string_length > 128 || string_length < 6 || !string_length) {
	     		SPD(playerid,
					dMenuBug, DIALOG_STYLE_INPUT,
					!"Сообщить о баге",
					"{ffffff}Подробно опишите найденную Вами недоработку\n\
					{009900}Если вы первый нашли важную недоработку,\n\
					возможно вы получите вознаграждение",
					!"Отправить", !"Назад"
				);
	     		return 1;
	     		}
				callcmd::bug(playerid, inputtext);
			}
			return 1;
		}
		case dMenuSug:
		{
			if(!response) {
				return SPD(playerid, dMenuFeedback, DIALOG_STYLE_LIST, ""COLOR_BLUE"Связь с администрацией","1. Написать администрации в сети\n2. Оставить сообщение о баге\n3. Предложить улучшение", "Выбрать", "Отмена");
			}
			if(response) {
				new string_length = strlen(inputtext);
	     		if(string_length > 128 || string_length < 6 || !string_length) {
	     		SPD(playerid,
					dMenuSug, DIALOG_STYLE_INPUT,
					!"Предложить улучшение",
					"{ffffff}Подробно опишите ваше улучшение и для чего оно нужно\n\
					{009900}Повторяться, предлагать чужие и старые идеи\n\
					не стоит, не тратьте своё время",
					!"Отправить", !"Назад"
				);
	     		return 1;
	     		}
				callcmd::sug(playerid, inputtext);
			}
			return 1;
		}
	 	case dMenuReport:
	 	{
			if(!response) {
				return SPD(playerid, dMenuFeedback, DIALOG_STYLE_LIST, ""COLOR_BLUE"Связь с администрацией","1. Написать администрации в сети\n2. Оставить сообщение о баге\n3. Предложить улучшение", "Выбрать", "Отмена");
			}
			if(response) {
				new string_length = strlen(inputtext);
				if(PlayerInfo[playerid][pMuted] == 1) return SendClientMessage(playerid, -1, !""COLOR_RED"У вас бан чата");
	     		if(string_length > 128 || string_length < 2 || !string_length) {
				SPD(playerid,
					dMenuReport, DIALOG_STYLE_INPUT,
					!"Связь с администрацией",
					"{ffffff}Введите свое сообщение для администраторов сервера\n\
					Оно должно быть кратким и отображать суть Вашего обращения\n\n\
					{009900}Если Вы хотите подать жалобу на игрока, в этом случае\n\
					Вам будет необходимо указать его ID",
					!"Далее", !"Назад"
				);
	     		return 1;
	     		}
				callcmd::report(playerid, inputtext);
			}
			return 1;
		}
	}
	return 1;

}

GoAnim(playerid,const alib[], const aanim[],Float:atime,amove,ax,ay,az,af,ac)
{
	ApplyAnimation(playerid,alib,aanim,atime,amove,ax,ay,az,af,ac);
	return true;
}
stock IncreaseKarma(playerid) {
	//
	PlayerInfo[playerid][pKarma]++;
	//
	if(PlayerInfo[playerid][pKarma] > 500) {
		PlayerInfo[playerid][pKarma] = 500;
		SetPlayerInt(playerid, "Karma", PlayerInfo[playerid][pKarma]); 
		return 1;
	}
	//
	SetPlayerInt(playerid, "Karma", PlayerInfo[playerid][pKarma]); 
	//
	format(small_string, sizeof(small_string),
		"Законопослушность повышена | Всего: "COLOR_GREEN"%d",
		PlayerInfo[playerid][pKarma]
	);
	SendClientMessage(playerid, -1, small_string);
	return 1;
}
stock DecreaseKarma(playerid) {
	//
	PlayerInfo[playerid][pKarma]--;
	//
	if(PlayerInfo[playerid][pKarma] < -500) {
		PlayerInfo[playerid][pKarma] = -500;
		SetPlayerInt(playerid, "Karma", PlayerInfo[playerid][pKarma]); 
		return 1;
	}
	SetPlayerInt(playerid, "Karma", PlayerInfo[playerid][pKarma]); 

	format(small_string, sizeof(small_string),
		"Законопослушность снижена | Всего: "COLOR_RED"%d",
		PlayerInfo[playerid][pKarma]
	);
	SendClientMessage(playerid, -1, small_string);
	return 1;
}

stock AddPlayerBankEXP(const playerid, const value) {
	if(PlayerLogged{playerid} == false || !IsPlayerConnected(playerid)) {
		return 0;
	}

	PlayerInfo[playerid][pBank] += value;

	static const fmt_str[] =
		"UPDATE players SET  `Bank`='%i' WHERE `Name`='%e' LIMIT 1";
	goto skip_array_init;
	new string[sizeof(fmt_str) + 1
		+ (- 2 + 32)
		+ (- 2 + 64)
		+ (- 2 + 11)
	];
	skip_array_init:

	mysql_format(database,
		string, sizeof(string),
		fmt_str,
			PlayerInfo[playerid][pBank],
			PlayerInfo[playerid][pName]
	);
	new result = mysql_pquery(database, string);
	if(result == 0) {
		return printf("Произошла ошибка при отправке запроса - \"%s\"", string);
	} else {
		return 1;
	}
}

stock RemovePlayerBankEXP(playerid, znach) {
	
	if(PlayerLogged{playerid} == false || !IsPlayerConnected(playerid)) return  1;

	PlayerInfo[playerid][pBank] -= znach;

	static const fmt_str[] =
		"UPDATE players SET  `Bank`='%i' WHERE `Name`='%e' LIMIT 1";
	goto skip_array_init;
	new string[sizeof(fmt_str) + 1
		+ (- 2 + 32)
		+ (- 2 + 64)
		+ (- 2 + 11)
	];
	skip_array_init:

	mysql_format(database,
		string, sizeof(string),
		fmt_str,
			PlayerInfo[playerid][pBank],
			PlayerInfo[playerid][pName]
	);
	new result = mysql_pquery(database, string);
	if(result == 0) {
		return printf("Произошла ошибка при отправке запроса - \"%s\"", string);
	} else {
		return 1;
	}
}

stock SetPlayerInt(playerid, const stolb[], znach) {
	if(PlayerLogged{playerid} == false || !IsPlayerConnected(playerid)) return  1;
	static const fmt_str[] =
		"UPDATE players SET  `%e`='%i' WHERE ID=%i LIMIT 1";
	goto skip_array_init;
	new string[sizeof(fmt_str) + 1
		+ (- 2 + 32)
		+ (- 2 + 64)
		+ (- 2 + MAX_LENGTH_ACCOUNT_ID)
	];
	skip_array_init:

	mysql_format(database,
		string, sizeof(string),
		fmt_str,
			stolb,
			znach,
			GetPlayerAccountID(playerid)
	);
	new result = mysql_pquery(database, string);
	if(result == 0) {
		return printf("Произошла ошибка при отправке запроса - \"%s\"", string);
	} else {
		return 1;
	}
}
stock SetHouseInt(he, const stolb[], znach)
{
	new Query[128];
	mysql_format(database, Query, sizeof(Query), "UPDATE `apartment` SET  %s = '%i' WHERE ID = '%i' LIMIT 1", stolb, znach, OLD_HouseInfo[he][hID]);
	mysql_pquery(database, Query, "", "");
	return true;
}
stock SetWareInt(Fraction:he, const stolb[], znach) // he - ID znach - kolvo stolb - imya
{
	new Query[128];
	mysql_format(database, Query, sizeof(Query), "UPDATE `warehouse` SET  %s = '%i' WHERE ID = '%i' LIMIT 1", stolb, znach, _:he);
	mysql_pquery(database, Query, "", "");
	return true;
}

stock IsRpNickname(const nickname[]) {
	return regex_match(nickname, "[A-Z][a-z]+_[A-Z][a-z]+");
}

stock IsValidIP(const ip[]) {
	return regex_match(ip, "^[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}$");
}


stock IsValidEmail(const mail[]) {
	return regex_match(mail, "[a-zA-Z0-9_\\.]+@([a-zA-Z0-9\\-]+\\.)+[a-zA-Z]{2,4}");
}


stock RandomEx(one, two) {
	return (random(two - one) + one);
}
forward count_return(playerid);
public count_return(playerid) {
	if(gone[playerid] != -1) {
		new g[12];
		format(g, sizeof(g), "~r~%d", gone[playerid]);
		GameTextForPlayer(playerid, g, 1250, 4);
		gone[playerid]--;
		if(gone[playerid] == 0) {
			goneaway(playerid);
			gone[playerid] = -1;
			ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
			return 1;
		}
	}
	ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
	return ReturnTimerID[playerid] = SetTimerEx("count_return", 1000, false, "d", playerid);
}
public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}
stock UpdateSpecTD(playerid) {
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
	{
		new Float:hppp, Float:aermor, Float:health;
		GetPlayerArmour(spectating[playerid],aermor); 
		GetPlayerHealth(spectating[playerid],hppp); 
		GetVehicleHealth(GetPlayerVehicleID(spectating[playerid]),health);
	
		new targetid = spectating[playerid];
		new playersip[20],
			gunname[32];
		if(GetPlayerWeapon(targetid) > 0) {
			GetWeaponName(GetPlayerWeapon(targetid), gunname, sizeof(gunname));
		} else {
			gunname = "-";
		}
		GetPlayerIp(spectating[playerid],playersip,sizeof(playersip));
		format(big_string, sizeof(big_string), 
			"~r~%s (ID %i)~n~\
			~r~IP: ~w~%s~n~\
			~b~Ping: ~w~%i~n~\
			~y~Karma: ~w~%i~n~\
			~y~EXP: ~w~%i~n~\
			~y~Car HP: ~w~%.2f~n~\
			~y~Speed: ~w~%i KM/H~n~\
			~y~Health: ~w~%.2f~n~\
			~y~Armour: ~w~%.2f~n~\
			~y~Weapon: ~w~%s~n~\
			~y~Ammo: ~w~%i~n~",
			PlayerInfo[targetid][pName],
			targetid,
			playersip,
			GetPlayerPing(targetid),
			PlayerInfo[targetid][pKarma],
			GetPlayerEXP(targetid),
			health,
			SpeedVehicle(targetid),
			hppp,
			aermor,
			gunname,
			GetPlayerAmmo(targetid)
		);
		PlayerTextDrawSetString(playerid, FULLRECON[playerid], big_string);
	}
}
forward PlayerUpdate(playerid);
public PlayerUpdate(playerid) {

	pl_afk_time[playerid] ++;

	if(pl_afk_time[playerid] < 5) {
		PlayerInfo[playerid][pOnline]++;
		if(PlayerInfo[playerid][pOnline] >= 3600) { Salary(playerid); }
	}
	/*if(GetPVarInt(playerid, "ac_speed") < gettime()) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && PlayerInfo[playerid][pAdmin] == 0)
	    {
	        new vehicleid = GetPlayerVehicleID(playerid),
	            surf = GetPlayerSurfingVehicleID(playerid),
	            surf_object = GetPlayerSurfingObjectID(playerid);
	 
	        if ((GetVehicleSpeed(vehicleid) > (GetVehicleTopSpeed(vehicleid) + 20)) && !IsAirVehicle(vehicleid) && surf == INVALID_VEHICLE_ID && surf_object == INVALID_OBJECT_ID)
	        {
	            new str_txt[128];
	            format(str_txt, sizeof(str_txt), ""COLOR_RED"%s[%d] использует SpeedHack", PlayerInfo[playerid][pName], playerid);
	            SendAdminMessage(-1, str_txt);
	            SetPVarInt(playerid, "ac_speed", gettime() + 30);
	        }
	    }
	}*/
 	new robbery_time = GetPVarInt(playerid, "robbery_time");
 	robbery_time --;
 	if(robbery_time >= 0) {
 		format(small_string, sizeof(small_string), "~g~~h~ TIME %s", Convert(robbery_time));
		GameTextForPlayer(playerid, small_string, 1500, 4);
		SetPVarInt(playerid, "robbery_time", robbery_time);
 	}

 	new MinusTime = GetPVarInt(playerid, "MinusTime");
 	MinusTime --;
 	if(MinusTime >= 0) {
 		format(small_string, sizeof(small_string), "~g~~h~ TIME %s", Convert(MinusTime));
		GameTextForPlayer(playerid, small_string, 1500, 4);
		SetPVarInt(playerid, "MinusTime", MinusTime);
 	}

	if(RouteAir[playerid] > 4) {
	new small_c[90];
	new Float: fDistance = GetPlayerDistanceFromPoint(playerid, 1922.8334,-2249.4912,13.1084);
	format(small_c, sizeof(small_c), "~b~TO DESTINATION: ~w~%.0f M.", fDistance);
	GameTextForPlayer(playerid, small_c, 5000, 4);
	}
	if(RouteAir2[playerid] > 3) {
	new small_c[90];
	new Float: fDistance = GetPlayerDistanceFromPoint(playerid, 1609.3046,1634.0345,10.3938);
	format(small_c, sizeof(small_c), "~b~TO DESTINATION: ~w~%.0f M.", fDistance);
	GameTextForPlayer(playerid, small_c, 5000, 4);
	}

	if(PlayerInfo[playerid][pAdmin] > 1) UpdateSpecTD(playerid);


	if(PlayerInfo[playerid][pJailed] == 2)
	{
	    if(PlayerInfo[playerid][pWanted] > 0) { 
	    	PlayerInfo[playerid][pWanted] = 0; 
	    	SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
	    	SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]); 
	    }
	    if(!IsPlayerInRangeOfPoint(playerid, 55.0, -8718.3047,1702.0928,10.2857)) {
			RemovePlayerFromVehicle(playerid);
			new zpizdok = RandomEx(15,20);
			SetPlayerPos(playerid, -8718.3047,1702.0928,zpizdok);
			GameTextForPlayer(playerid, "~rBecause you fucked up", 2100, 5);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 666);
		}
		PlayerInfo[playerid][pJailTime]--;
		SetPlayerInt(playerid, "JailTime", PlayerInfo[playerid][pJailTime]);
		new small_update_string[144];
		format(small_update_string, sizeof(small_update_string), "~y~JAIL TIME: ~w~%s", Convert(PlayerInfo[playerid][pJailTime]));
		GameTextForPlayer(playerid, small_update_string, 1100, 5);
		if(PlayerInfo[playerid][pJailTime] < 1)
		{
		if(PlayerInfo[playerid][pJailed] == 1) SetPlayerPos(playerid, 1552.4500,-1674.9900,16.1953);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы заплатили свой долг обществу, теперь вы свободны");
		PlayerInfo[playerid][pJailTime] = 0;
		PlayerInfo[playerid][pJailed] = 0;
		SetPlayerInt(playerid, "Jailed", PlayerInfo[playerid][pJailed]);
		SetPlayerInt(playerid, "JailTime", PlayerInfo[playerid][pJailTime]);
		SetPlayerInterior(playerid, 0);
		SpawnPlayer(playerid);
		}
	}
	if(PlayerInfo[playerid][pJailed] == 1)
	{
	    if(PlayerInfo[playerid][pWanted] > 0) { 
	    	PlayerInfo[playerid][pWanted] = 0; 
	    	SetPlayerWanted(playerid, PlayerInfo[playerid][pWanted]);
	    	SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]); 
	    }
	    if(!IsPlayerInRangeOfPoint(playerid, 10.0, 263.9653,77.3805,1001.0391)) {
			RemovePlayerFromVehicle(playerid);
			SetPlayerPos(playerid, 263.9653,77.3805,1001.0391);
			SetPlayerInterior(playerid, 6);
		}
		PlayerInfo[playerid][pJailTime]--;
		SetPlayerInt(playerid, "JailTime", PlayerInfo[playerid][pJailTime]);
		new small_update_string[144];
		format(small_update_string, sizeof(small_update_string), "~y~JAIL TIME: ~w~%s", Convert(PlayerInfo[playerid][pJailTime]));
		GameTextForPlayer(playerid, small_update_string, 1100, 5);
		if(PlayerInfo[playerid][pJailTime] < 1)
		{
		if(PlayerInfo[playerid][pJailed] == 1) SetPlayerPos(playerid, 1552.4500,-1674.9900,16.1953);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы заплатили свой долг обществу, теперь вы свободны");
		PlayerInfo[playerid][pJailTime] = 0;
		PlayerInfo[playerid][pJailed] = 0;
		SetPlayerInt(playerid, "Jailed", PlayerInfo[playerid][pJailed]);
		SetPlayerInt(playerid, "JailTime", PlayerInfo[playerid][pJailTime]);
		SetPlayerInterior(playerid, 0);
		SpawnPlayer(playerid);
		}
	}
	if(LawTimer[playerid] > 0) {
		LawTimer[playerid]--;
		if(LawTimer[playerid] == 0) {
			Law(playerid);
		}
	}
	if(PlayerInfo[playerid][pWanted] > 0) {
		PlayerInfo[playerid][pWanted]--;
		SetPlayerInt(playerid, "Wanted", PlayerInfo[playerid][pWanted]);
	}
	if(ThefStatus[playerid] > 0) {
		if(TimeTCar[playerid] < 1) {
			ThefStatus[playerid] = 0;
			TCar[playerid] = 0;
			GangZoneDestroy(TheftZone[playerid]);
			for(new i = 0; i < sizeof(stealcar_checkpoint); i++) {
				TogglePlayerDynamicCP(playerid, stealcar_checkpoint[i], false);
			}
			goto skip_all;
		}
		TimeTCar[playerid]--;
		new small_update_string[144];
		format(small_update_string, sizeof(small_update_string), "~w~THEFT AUTO: ~y~%s", Convert(TimeTCar[playerid]));
		GameTextForPlayer(playerid, small_update_string, 1300, 4);
	}
	if(PlayerInfo[playerid][pMuted] > 0 )
	{
		PlayerInfo[playerid][pMuteTime]--;
		SetPlayerInt(playerid, "MuteTime", PlayerInfo[playerid][pMuteTime]);
		if(PlayerInfo[playerid][pMuteTime] < 1)
		{
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Чат разблокирован. Просим вас не нарушать правила!");
			PlayerInfo[playerid][pMuteTime] = 0;
			PlayerInfo[playerid][pMuted] = 0;
			SetPlayerInt(playerid, "Muted", PlayerInfo[playerid][pMuted]);
			SetPlayerInt(playerid, "MuteTime", PlayerInfo[playerid][pMuteTime]);
		}
	}
	if(porter_state[playerid] == 2) {
		ApplyAnimation(playerid, !"CARRY", !"crry_prtial", 4.0, 1, 0, 0, 1, 1, 1);
	}
	skip_all:
	PlayerTimerID[playerid] = KillTimer(PlayerTimerID[playerid]); 
	return PlayerTimerID[playerid] = SetTimerEx("PlayerUpdate", 1000, false, "d", playerid);
}

Convert(number)
{
	new hours = 0, mins = 0, secs = 0, string[100];
	hours = floatround(number / 3600);
	mins = floatround((number / 60) - (hours * 60));
	secs = floatround(number - ((hours * 3600) + (mins * 60)));
	if(hours > 0)
	{
		format(string, 100, "%i:%02d:%02d", hours, mins, secs);
	}
	else
	{
		format(string, 100, "%i:%02d", mins, secs);
	}
	return string;
}
stock GetGangSalary() {
	// Обнуляем переменные зарплат
	gang_profit[1] = 0;
    gang_profit[2] = 0;
    gang_profit[3] = 0;
    gang_profit[4] = 0;
    gang_profit[5] = 0;
    gang_profit[6] = 0;
    // Высчитываем зрплату соразмерную количеству территорий под контролем
	for(new x = 1;x<=TOTALGZ;x++) 
	{
		gang_profit[GZInfo[x][gFrak]] += 6;
	}
	return 1;
}
GzCheck(zoneid)
{
	new string[256];
	new 
	Fraction:target_fractionid;
	//new time[90];
	if(GZSafeTime[zoneid] > 0)
	{
		GZSafeTime[zoneid]--;
		GangZoneFlashForAll(GZInfo[zoneid][gid], GetGZColorF(GZInfo[zoneid][gNapad]));

		foreach(new x: Player)
		{	
			target_fractionid = GetPlayerFraction(x);

			if(_:target_fractionid == _:GZInfo[zoneid][gNapad] || _:target_fractionid == _:GZInfo[zoneid][gFrak])
			{			
				format(small_string, sizeof(small_string), "~w~%d : %d~n~~b~~h~TIME: ~w~%s", GangInfo[GZInfo[zoneid][gNapad]][score],GangInfo[GZInfo[zoneid][gFrak]][score],Convert(GZSafeTime[zoneid]));
				if(GZSafeTime[zoneid] < 301) format(small_string, sizeof(small_string), "~w~%d : %d~n~~y~~h~TIME: ~w~%s", GangInfo[GZInfo[zoneid][gNapad]][score],GangInfo[GZInfo[zoneid][gFrak]][score],Convert(GZSafeTime[zoneid]));
				if(GZSafeTime[zoneid] < 61) format(small_string, sizeof(small_string),"~w~%d : %d~n~~r~~h~TIME: ~w~%s", GangInfo[GZInfo[zoneid][gNapad]][score],GangInfo[GZInfo[zoneid][gFrak]][score],Convert(GZSafeTime[zoneid]));
				GameTextForPlayer(x, small_string, 1500, 4);
				if(GetPVarType(x, !"oncapture") != PLAYER_VARTYPE_INT) SetPVarInt(x, !"oncapture", 0);
			}
		}
	}

	if(ZoneOnBattle[zoneid] == 1 && GZSafeTime[zoneid] == 0)
	{
		foreach(new x: Player)
		{
	 		if(PlayerInGangZone(x,GZInfo[zoneid][gCoords][0], GZInfo[zoneid][gCoords][1],GZInfo[zoneid][gCoords][2],GZInfo[zoneid][gCoords][3]))
		    {
		    	target_fractionid = GetPlayerFraction(x);
				if(target_fractionid == Fraction:GZInfo[zoneid][gNapad]) {napad++;}
				if(target_fractionid == Fraction:GZInfo[zoneid][gFrak]) {frak++;}
				DeletePVar(x, !"oncapture");
		    }
	    }
		if(GangInfo[GZInfo[zoneid][gNapad]][score] == 0 && frak == 0)
		{
			ZoneOnBattle[zoneid] = 0;
			IsCapture=0;
			ZoneCapture = -1;
			GangZoneStopFlashForAll(GZInfo[zoneid][gid]);
			GangInfo[GZInfo[zoneid][gNapad]][captureid] = 0;
			GangInfo[GZInfo[zoneid][gNapad]][capture] = 0;
			GangInfo[GZInfo[zoneid][gNapad]][score] = 0;
			GangInfo[GZInfo[zoneid][gFrak]][captureid] = 0;
			GangInfo[GZInfo[zoneid][gFrak]][capture] = 0;
			GangInfo[GZInfo[zoneid][gFrak]][score] = 0;
			napad = 0;
			frak = 0;
		}
		if(GangInfo[GZInfo[zoneid][gNapad]][score] == GangInfo[GZInfo[zoneid][gFrak]][score])
		{
			format(string, 90, ""COLOR_ORANGE"Счет в войне за территорию равен");
			SendFamilyMessage(Fraction:GZInfo[zoneid][gFrak],-1, string);
			SendFamilyMessage(Fraction:GZInfo[zoneid][gNapad],-1, string);
			SendAdminMessage(-1,string);
			ZoneOnBattle[zoneid] = 0;
			IsCapture=0;
			ZoneCapture = -1;
			GangZoneStopFlashForAll(GZInfo[zoneid][gid]);
			GangInfo[GZInfo[zoneid][gNapad]][captureid] = 0;
			GangInfo[GZInfo[zoneid][gNapad]][capture] = 0;
			GangInfo[GZInfo[zoneid][gNapad]][score] = 0;
			GangInfo[GZInfo[zoneid][gFrak]][captureid] = 0;
			GangInfo[GZInfo[zoneid][gFrak]][capture] = 0;
			GangInfo[GZInfo[zoneid][gFrak]][score] = 0;
 			napad = 0;
			frak = 0;
		}
		else if(GangInfo[GZInfo[zoneid][gNapad]][score] > GangInfo[GZInfo[zoneid][gFrak]][score])
		{
			new zx,zl;
			zx = GZInfo[zoneid][gNapad];
			zl = zoneid;
			switch(GZInfo[zoneid][gFrak])
			{
				case 2: TotalZones[2]--;
				case 3: TotalZones[3]--;
				case 4: TotalZones[4]--;
				case 5: TotalZones[5]--;
				case 6: TotalZones[6]--;
			}
			switch(GZInfo[zoneid][gNapad])
			{
				case 2: TotalZones[2]++;
				case 3: TotalZones[3]++;
				case 4: TotalZones[4]++;
				case 5: TotalZones[5]++;
				case 6: TotalZones[6]++;
			}
			SaveGZ(zx, GZInfo[zl][gid]);
			format(string,90,""COLOR_BLUE"Банда {FFFFFF}%s"COLOR_BLUE" побеждает в войне за территорию",GetGangName(zx));
			SendFamilyMessage(Fraction:GZInfo[zoneid][gFrak],-1, string);
			SendFamilyMessage(Fraction:GZInfo[zoneid][gNapad],-1, string);
			SendAdminMessage(-1,string);
			ZoneOnBattle[zl] =0;
			GangInfo[GZInfo[zl][gNapad]][captureid] = 0;
			GangInfo[GZInfo[zl][gNapad]][capture] = 0;
			GangInfo[GZInfo[zl][gNapad]][score] = 0;
			GangInfo[GZInfo[zl][gFrak]][captureid] = 0;
			GangInfo[GZInfo[zl][gFrak]][capture] = 0;
			GangInfo[GZInfo[zl][gFrak]][score] = 0;
			GZInfo[zl][gFrak] = zx;
			GZInfo[zl][gNapad] = 0;
			IsCapture=0;
			ZoneCapture = -1;
			GangZoneStopFlashForAll(GZInfo[zl][gid]);
			GangZoneHideForAll(GZInfo[zl][gid]);
			GangZoneShowForAll(GZInfo[zl][gid],GetGangZoneColor(zl));
			
			napad = 0;
			frak = 0;
			GetGangSalary();
		}
		else if(GangInfo[GZInfo[zoneid][gNapad]][score] < GangInfo[GZInfo[zoneid][gFrak]][score])
		{
			new zx,zl;
			zx = GZInfo[zoneid][gFrak];
			zl = zoneid;
			format(string,90,""COLOR_BLUE"Банда {FFFFFF}%s"COLOR_BLUE" побеждает в войне за территорию",GetGangName(zx));
			SendFamilyMessage(Fraction:GZInfo[zoneid][gFrak],-1, string);
			SendFamilyMessage(Fraction:GZInfo[zoneid][gNapad],-1, string);
			SendAdminMessage(-1,string);
			ZoneOnBattle[zl] =0;
			GangInfo[GZInfo[zl][gNapad]][captureid] = 0;
			GangInfo[GZInfo[zl][gNapad]][capture] = 0;
			GangInfo[GZInfo[zl][gNapad]][score] = 0;
			GangInfo[GZInfo[zl][gFrak]][captureid] = 0;
			GangInfo[GZInfo[zl][gFrak]][capture] = 0;
			GangInfo[GZInfo[zl][gFrak]][score] = 0;
			IsCapture=0;
			ZoneCapture = -1;
			GZInfo[zl][gFrak] = zx;
			GZInfo[zl][gNapad] = 0;
			GangZoneStopFlashForAll(GZInfo[zl][gid]);
			GangZoneHideForAll(GZInfo[zl][gid]);
			GangZoneShowForAll(GZInfo[zl][gid],GetGangZoneColor(zl));
			napad = 0;
			frak = 0;
		}
	}
}
CMD:gzcolor(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 6) return 1; 
	if(sscanf(params, "d",params[0])) return SendClientMessage(playerid,-1, "Введите: /gzcolor [id банды]");
	for(new i = 0;i<=TOTALGZ;i++)
	{
		if(PlayerInGangZone(playerid,GZInfo[i][gCoords][0], GZInfo[i][gCoords][1],GZInfo[i][gCoords][2],GZInfo[i][gCoords][3]))
		{
			GZInfo[i][gFrak] = params[0];
			GangZoneStopFlashForAll(GZInfo[i][gid]);
			GangZoneHideForAll(GZInfo[i][gid]);
			GangZoneShowForAll(GZInfo[i][gid],GetGangZoneColor(i));
			SaveGZ(GZInfo[i][gFrak], GZInfo[i][gid]);
			return true;
		}
	}
	return true;
}
stock ReloadFarmText() {
	format(h00, sizeof(h00), ""COLOR_BLUE"Загружено:\n {FFFFFF}%d/200", Harvest[0]);
	Update3DTextLabelText(farmtext, 0xFFFFFFFF, h00);
	format(h01, sizeof(h01), ""COLOR_BLUE"Загружено:\n {FFFFFF}%d/200", Harvest[1]);
	Update3DTextLabelText(farmtext1, 0xFFFFFFFF, h01);
	format(h02, sizeof(h02), ""COLOR_BLUE"Загружено:\n {FFFFFF}%d/200", Harvest[2]);
	Update3DTextLabelText(farmtext2, 0xFFFFFFFF, h02);
	return 1;
}
forward GetPayDay();
public GetPayDay() {

	if(invite_type == 0) {
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} В Мэрии штата началось собеседование в Армию");
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} Требования: Законопослушность не ниже -50");
		return invite_type = 1;
	} if(invite_type == 1) {
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} В Мэрии штата началось собеседование в LSPD");
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} Требования: Законопослушность не ниже 100");
		return invite_type = 2;
	} if(invite_type == 2) {
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} В Мэрии штата началось собеседование в FBI");
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} Требования: Законопослушность не ниже 250");
		return invite_type = 3;
	} if(invite_type == 3) {
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} В Мэрии штата началось собеседование в Мэрию");
		SendClientMessageToAll(-1, "{0055ff}[Гос.Новости]{FFFFFF} Требования: Законопослушность не ниже 500");
		return invite_type = 0;
	}
	return 1;
}
stock PayDay() {

	PayDDoS = false;

	printf("New_Day");

	SetWeather(RandomEx(0,8));

	SetTimer("GetPayDay", 30000, 0);

    startcapture = 0;
	GameTextForAll("~y~NEWDAY", 5000, 0);
	format(small_string, sizeof(small_string), ""COLOR_ORANGE"Текущее время: {FFFFFF}%d:00", hour);

    SendClientMessageToAll(-1, small_string);
   	SetWorldTime(hour);
    switch(GetVehiclePoolSize()) {
	    case 0..69: orders = RandomEx(5,9);
	    case 70..99: orders = RandomEx(8,15);
	    default: orders = RandomEx(10,25);
	}
}
forward UpdateTimers();
public UpdateTimers() {

	gettime(hour, minute, second);

	if(minute == 58 && PayDDoS == false) {
		PayDDoS = true;
	}

	if(!minute && PayDDoS == true)
    {
    	PayDay();
    }


    if(test_server == false) {
    	if(second == 00 && minute == 00 && hour == 5 && AutoHouseSell == true)
		{
			SendClientMessageToAll(-1, ""COLOR_BLUE"Запланированный рестарт сервера через 1 минуту");
			
			AutoHouseSell = false;
		}
    }


	if(minute == 1 && second == 00 && hour == 5)
	{
	    SendClientMessageToAll(-1, ""COLOR_BLUE"Начался запланированный рестарт сервера");
	    SendClientMessageToAll(-1, ""COLOR_BLUE"Ожидайте. Это займет буквально минуту");
		SendRconCommand("gmx");
	}


	return SetTimer("UpdateTimers", 1000, false);
}

stock Salary(playerid) {
	SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы отыграли час. Зарплата поступила на ваш банковский счет");
	PlayerInfo[playerid][pHours] += 1;
    SetPlayerInt(playerid, "Hours", PlayerInfo[playerid][pHours]);
	GameTextForPlayer(playerid, "~g~SALARY", 5000, 0);

	PlayerInfo[playerid][pOnline] = 0;

	CheckHouseRentDay(playerid);

	new exp;
    if(PlayerInfo[playerid][pTaxiTotal] > 0) {
	    format(small_string, sizeof(small_string), ""COLOR_ORANGE"Зарплата таксиста: {FFFFFF}+ %d EXP", PlayerInfo[playerid][pTaxiTotal]);
		AddPlayerBankEXP(playerid, PlayerInfo[playerid][pTaxiTotal]);
	    SendClientMessage(playerid, -1, small_string);
     	PlayerInfo[playerid][pTaxiTotal] = 0;
    	SetPlayerInt(playerid, "TaxiTotal", PlayerInfo[playerid][pTaxiTotal]);
    }
    new 
    	Fraction: fractionid = GetPlayerFraction(playerid),
    	player_karma = PlayerInfo[playerid][pKarma];

    if(fractionid == FRACTION_LSPD) {
    	if(player_karma > 99 && player_karma < 149) {
    		exp = 250;
    	} else if(player_karma > 150 && player_karma < 249) {
    		exp = 300;
    	} else if(player_karma > 250 && player_karma < 9999) {
    		exp = 350;
    	} else {
    		exp = 0;
    	}
	    format(small_string, sizeof(small_string), ""COLOR_ORANGE"Зарплата департамента: {FFFFFF}+ %d EXP",exp);
		AddPlayerBankEXP(playerid, exp);
	    SendClientMessage(playerid, -1, small_string); 
	}
    if(fractionid == FRACTION_ARMY) {
    	if(player_karma > 0 && player_karma < 49) {
    		exp = 200;
    	} else if(player_karma > 50 && player_karma < 99) {
    		exp = 250;
    	} else if(player_karma > 100 && player_karma < 9999) {
    		exp = 300;
    	} else {
    		exp = 0;
    	}
	    format(small_string, sizeof(small_string), ""COLOR_ORANGE"Зарплата: {FFFFFF}+ %d EXP",exp);
		AddPlayerBankEXP(playerid, exp);
	    SendClientMessage(playerid, -1, small_string); 
	}
	if(fractionid == FRACTION_FBI) {
	    if(player_karma > 250 && player_karma < 299) {
    		exp = 350;
    	} else if(player_karma > 300 && player_karma < 399) {
    		exp = 400;
    	} else if(player_karma > 400 && player_karma < 9999) {
    		exp = 450;
    	} else {
    		exp = 0;
    	}
    	format(small_string, sizeof(small_string), ""COLOR_ORANGE"Зарплата бюро: {FFFFFF}+ %d EXP",exp);
		AddPlayerBankEXP(playerid, exp);
    	SendClientMessage(playerid, -1, small_string); 
    }
	if(fractionid > FRACTION_LSPD && fractionid < FRACTION_RUSSIAN_MAFIA) {
		exp = gang_profit[_:fractionid];
   	 	format(small_string, sizeof(small_string), ""COLOR_ORANGE"Доля от доходов банды: {FFFFFF}+ %d EXP", exp);
    	AddPlayerBankEXP(playerid, exp);
    	SendClientMessage(playerid, -1, small_string);
	}
	format(small_string, sizeof(small_string), ""COLOR_ORANGE"Ваша законопослушность: {FFFFFF} %d", PlayerInfo[playerid][pKarma]);
    SendClientMessage(playerid, -1, small_string);
 	
	format(small_string, sizeof(small_string), ""COLOR_ORANGE"Ваш банковский баланс: {FFFFFF} %d EXP", PlayerInfo[playerid][pBank]);
    SendClientMessage(playerid, -1, small_string);
    return 1;
}
forward Rob(playerid);
public Rob(playerid)
{
	RobTimer[playerid] = KillTimer(RobTimer[playerid]); 
    SetPVarInt(playerid,"RobOnce", 0);

    new RobExp = RandomEx(20, 75);

	if(robber[0] == playerid)
	{
	    robber[0] = INVALID_PLAYER_ID;
	    if(IsPlayerInRangeOfPoint(playerid, 7.0, 1832.5164,-1839.8253,13.5781) && !IsPlayerInAnyVehicle(playerid)) {
		    format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы успешно ограбили бизнес и получили: {FFFFFF}+%d EXP", RobExp);
	    	SendClientMessage(playerid, -1, small_string);
			Player.AddEXP(PlayerInfo[playerid][pID], RobExp, E_ROBBERY_BUSINESS, playerid);	
			return DecreaseKarma(playerid);
		}
		return 1;
	}
	if(robber[1] == playerid)
	{
		robber[1] = INVALID_PLAYER_ID;
	    if(IsPlayerInRangeOfPoint(playerid, 7.0, 1836.0077,-1685.6646,13.3659) && !IsPlayerInAnyVehicle(playerid)) {
		    format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы успешно ограбили бизнес и получили: {FFFFFF}+%d EXP", RobExp);
	    	SendClientMessage(playerid, -1, small_string);
			Player.AddEXP(PlayerInfo[playerid][pID], RobExp, E_ROBBERY_BUSINESS, playerid);	
			DecreaseKarma(playerid);
		}
		return 1;
	}
	if(robber[2] == playerid)
	{
	    robber[2] = INVALID_PLAYER_ID;
	    if(IsPlayerInRangeOfPoint(playerid, 7.0, 2104.3569,-1804.0612,13.5547) && !IsPlayerInAnyVehicle(playerid)) {
		    format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы успешно ограбили бизнес и получили: {FFFFFF}+%d EXP", RobExp);
	    	SendClientMessage(playerid, -1, small_string);
			Player.AddEXP(PlayerInfo[playerid][pID], RobExp, E_ROBBERY_BUSINESS, playerid);	
			DecreaseKarma(playerid);
		}
		return 1;
	}
	if(robber[3] == playerid)
	{
	    robber[3] = INVALID_PLAYER_ID;
	    if(IsPlayerInRangeOfPoint(playerid, 7.0, 2240.6370,-1663.2640,15.4766) && !IsPlayerInAnyVehicle(playerid)) {
		    format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы успешно ограбили бизнес и получили: {FFFFFF}+%d EXP", RobExp);
	    	SendClientMessage(playerid, -1, small_string);
			Player.AddEXP(PlayerInfo[playerid][pID], RobExp, E_ROBBERY_BUSINESS, playerid);	
			DecreaseKarma(playerid);
		}
		return 1;
	}
	if(robber[4] == playerid)
	{
	    robber[4] = INVALID_PLAYER_ID;
	    if(IsPlayerInRangeOfPoint(playerid, 7.0, 2417.8423,-1220.9553,25.2661) && !IsPlayerInAnyVehicle(playerid)) {
		    format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы успешно ограбили бизнес и получили: {FFFFFF}+%d EXP", RobExp);
	    	SendClientMessage(playerid, -1, small_string);
			Player.AddEXP(PlayerInfo[playerid][pID], RobExp, E_ROBBERY_BUSINESS, playerid);	
			DecreaseKarma(playerid);
		}
		return 1;
	}
	if(robber[5] == playerid)
	{
	    robber[5] = INVALID_PLAYER_ID;
	    if(IsPlayerInRangeOfPoint(playerid, 7.0, 2227.8115,-1720.2245,13.5404) && !IsPlayerInAnyVehicle(playerid)) {
		    format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы успешно ограбили бизнес и получили: {FFFFFF}+%d EXP", RobExp);
	    	SendClientMessage(playerid, -1, small_string);
			Player.AddEXP(PlayerInfo[playerid][pID], RobExp, E_ROBBERY_BUSINESS, playerid);	
			DecreaseKarma(playerid);
		}
		return 1;
	}
	if(robber[6] == playerid)
	{
	    robber[6] = INVALID_PLAYER_ID;
	    if(IsPlayerInRangeOfPoint(playerid, 7.0, 1975.5535,-2039.1237,13.5469) && !IsPlayerInAnyVehicle(playerid)) {
		    format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы успешно ограбили бизнес и получили: {FFFFFF}+%d EXP", RobExp);
	    	SendClientMessage(playerid, -1, small_string);
			Player.AddEXP(PlayerInfo[playerid][pID], RobExp, E_ROBBERY_BUSINESS, playerid);	
			DecreaseKarma(playerid);
		}
		return 1;
	}
	if(robber[7] == playerid)
	{
	    robber[7] = INVALID_PLAYER_ID;
	    if(IsPlayerInRangeOfPoint(playerid, 7.0, 2071.3540,-1796.2771,13.5533) && !IsPlayerInAnyVehicle(playerid)) {
		    format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы успешно ограбили бизнес и получили: {FFFFFF}+%d EXP", RobExp);
	    	SendClientMessage(playerid, -1, small_string);
			Player.AddEXP(PlayerInfo[playerid][pID], RobExp, E_ROBBERY_BUSINESS, playerid);	
			DecreaseKarma(playerid);
		}
		return 1;
	}
	if(robber[8] == playerid)
	{
	    robber[8] = INVALID_PLAYER_ID;
	    if(IsPlayerInRangeOfPoint(playerid, 7.0, 2069.6985,-1776.5570,13.5576) && !IsPlayerInAnyVehicle(playerid)) {
		    format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы успешно ограбили бизнес и получили: {FFFFFF}+%d EXP", RobExp);
	    	SendClientMessage(playerid, -1, small_string);
			Player.AddEXP(PlayerInfo[playerid][pID], RobExp, E_ROBBERY_BUSINESS, playerid);	
			DecreaseKarma(playerid);
		}
		return 1;
	}
	if(robber[9] == playerid)
	{
	    robber[9] = INVALID_PLAYER_ID;
	    if(IsPlayerInRangeOfPoint(playerid, 7.0, 2312.5066,-1645.4086,14.8270) && !IsPlayerInAnyVehicle(playerid)) {
		    format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы успешно ограбили бизнес и получили: {FFFFFF}+%d EXP", RobExp);
	    	SendClientMessage(playerid, -1, small_string);
			Player.AddEXP(PlayerInfo[playerid][pID], RobExp, E_ROBBERY_BUSINESS, playerid);	
			DecreaseKarma(playerid);
		}
		return 1;
	}
	if(robber[10] == playerid)
	{
	    robber[10] = INVALID_PLAYER_ID;
	    if(IsPlayerInRangeOfPoint(playerid, 7.0, 2420.4644,-1506.0500,24.0000) && !IsPlayerInAnyVehicle(playerid)) {
		    format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы успешно ограбили бизнес и получили: {FFFFFF}+%d EXP", RobExp);
	    	SendClientMessage(playerid, -1, small_string);
			Player.AddEXP(PlayerInfo[playerid][pID], RobExp, E_ROBBERY_BUSINESS, playerid);	
			DecreaseKarma(playerid);
		}
		return 1;
	}
	if(robber[11] == playerid)
	{
	    robber[11] = INVALID_PLAYER_ID;
	    if(IsPlayerInRangeOfPoint(playerid, 7.0, 2722.7866,-2024.4041,13.5472) && !IsPlayerInAnyVehicle(playerid)) {
		    format(small_string, sizeof(small_string), ""COLOR_GREEN"Вы успешно ограбили бизнес и получили: {FFFFFF}+%d EXP", RobExp);
	    	SendClientMessage(playerid, -1, small_string);
			Player.AddEXP(PlayerInfo[playerid][pID], RobExp, E_ROBBERY_BUSINESS, playerid);	
			DecreaseKarma(playerid);
		}
		return 1;
	}
	if(robber[12] == playerid)
	{
	    if(carry[playerid] == -1) return 1;
	    robber[12] = INVALID_PLAYER_ID;
		carry[playerid] = -1;
		SendClientMessage(playerid, -1, ""COLOR_RED"Вы не успели на сделку");
		for(new i = 0; i < sizeof(mafia_checkpoint); i++) {
			TogglePlayerDynamicCP(playerid, mafia_checkpoint[i], false);
		}
		return 1;
	}
	if(robber[13] == playerid)
	{
	    if(carry[playerid] == -1) return 1;
	    robber[13] = INVALID_PLAYER_ID;
		carry[playerid] = -1;
		SendClientMessage(playerid, -1, ""COLOR_RED"Вы не успели на сделку");
		for(new i = 0; i < sizeof(mafia_checkpoint); i++) {
			TogglePlayerDynamicCP(playerid, mafia_checkpoint[i], false);
		}
		return 1;
	}
	if(robber[14] == playerid)
	{
	    if(carry[playerid] == -1) return 1;
	    robber[14] = INVALID_PLAYER_ID;
		carry[playerid] = -1;
		SendClientMessage(playerid, -1, ""COLOR_RED"Вы не успели на сделку");
		for(new i = 0; i < sizeof(mafia_checkpoint); i++) {
			TogglePlayerDynamicCP(playerid, mafia_checkpoint[i], false);
		}
		return 1;
	}
	return 1;
}
forward WareStop(playerid);
public WareStop(playerid)
{
	routetimer[playerid] = KillTimer(routetimer[playerid]); 

    if(ArmyMission[playerid] == 1)
	{
		new vehicleid = GetPlayerVehicleID(playerid);

		if(IsWarehouseCar(vehicleid) != 1) {
			return 1;
		}

		switch(random(3)) {
			case 0: {
				SendClientMessage(playerid, -1, "Вы отправляетесь в LSPD с военным грузом");
				ArmyMission[playerid] = 2;
				if(GetVehicleModel(vehicleid) == 548) {
					SetPlayerRaceCheckpoint(playerid, 4, 1564.9432,-1652.7067,28.3956, 1564.9432,-1652.7067,28.3956, 20);
				} else {
					SetPlayerRaceCheckpoint(playerid, 1, 1581.5845,-1627.6393,13.3828, 1581.5845,-1627.6393,13.3828, 5); //
				}
			}
			case 1: {
				SendClientMessage(playerid, -1, "Вы отправляетесь в FBI с военным грузом");
				ArmyMission[playerid] = 2;
				if(GetVehicleModel(vehicleid) == 548) {
					SetPlayerRaceCheckpoint(playerid, 4, -2480.2007,522.8958,51.0638, -2480.2007,522.8958,51.0638, 20);
				} else {
					SetPlayerRaceCheckpoint(playerid, 1, -2440.5425,523.7228,29.9055, -2440.5425,523.7228,29.9055, 5); //
				}
			}
			case 2: {
				SendClientMessage(playerid, -1, "Вы отправляетесь в Ammu-Nation с военным грузом");
				ArmyMission[playerid] = 2;
				if(GetVehicleModel(vehicleid) == 548) {
					SetPlayerRaceCheckpoint(playerid, 4, 1393.2424,-1278.1752,33.4985, 1393.2424,-1278.1752,33.4985, 20);
				} else {
					SetPlayerRaceCheckpoint(playerid, 1, 1362.3386,-1279.4961,13.3828, 1362.3386,-1279.4961,13.3828, 5); //
				}
			}
		}
	}
	return 1;
}
forward AirStop2(playerid);
public AirStop2(playerid)
{
	routetimer[playerid] = KillTimer(routetimer[playerid]); 
    switch(RouteAir2[playerid])
	{
		case 1: {
			PlayerInfo[playerid][pAirSkill] --;
			if(PlayerInfo[playerid][pAirSkill] < 0) PlayerInfo[playerid][pAirSkill] = 0;
			SetPlayerInt(playerid, "AirSkill", PlayerInfo[playerid][pAirSkill]);
			SetPlayerRaceCheckpoint(playerid, 2, 1914.4653,-2328.6389,13.1067,1969.8719,-2493.8650,13.1128, 20); //
			RouteAir2[playerid] = 2;
		}
		case 8: {
			SetPlayerRaceCheckpoint(playerid, 1, 1507.5469,1463.4788,10.4105,1609.3046,1634.0345,10.3938, 20); //
			RouteAir2[playerid] = 9;
		}
	}
}
forward AirStop(playerid);
public AirStop(playerid)
{
	routetimer[playerid] = KillTimer(routetimer[playerid]); 
    switch(RouteAir[playerid])
	{
		case 1: {
			PlayerInfo[playerid][pAirSkill] --;
			if(PlayerInfo[playerid][pAirSkill] < 0) PlayerInfo[playerid][pAirSkill] = 0;
			SetPlayerInt(playerid, "AirSkill", PlayerInfo[playerid][pAirSkill]);
			SetPlayerRaceCheckpoint(playerid, 2, 1511.0432,1464.4716,10.4179, 1477.5396,1639.9655,10.3705, 20);
			RouteAir[playerid] = 2;
		}
		case 8: {
			SetPlayerRaceCheckpoint(playerid, 1, 1914.4653,-2328.6389,13.1067,1922.8334,-2249.4912,13.1084, 20); //
			RouteAir[playerid] = 9;
		}
	}
}
forward BusStop3(playerid);
public BusStop3(playerid)
{
	routetimer[playerid] = KillTimer(routetimer[playerid]); 
    switch(Route3[playerid])
	{
		case 1: {
			PlayerInfo[playerid][pBusSkill] --;
			if(PlayerInfo[playerid][pBusSkill] < 0) PlayerInfo[playerid][pBusSkill] = 0;
			SetPlayerInt(playerid, "BusSkill", PlayerInfo[playerid][pBusSkill]);
			SetPlayerRaceCheckpoint(playerid, 0, -1988.6450,138.3930,27.2461,-2009.7799,190.0612,27.2468, 5); //
			Route3[playerid] = 2;
		}
		case 8: {
			SetPlayerRaceCheckpoint(playerid, 0, -2029.1040,-77.7470,35.0282, -1854.7101,-118.7683,5.9268, 5); //
			Route3[playerid] = 9;
		}
	}
}
forward BusStop2(playerid);
public BusStop2(playerid)
{
	routetimer[playerid] = KillTimer(routetimer[playerid]); 
    switch(Route2[playerid])
	{
		case 1: {
			PlayerInfo[playerid][pBusSkill] --;
			if(PlayerInfo[playerid][pBusSkill] < 0) PlayerInfo[playerid][pBusSkill] = 0;
			SetPlayerInt(playerid, "BusSkill", PlayerInfo[playerid][pBusSkill]);
			SetPlayerRaceCheckpoint(playerid, 0, 2809.6353,1302.1759,10.4570,2769.1545,1475.4580,10.9587, 5); //
			Route2[playerid] = 2;
		}
	}
}
forward BusStop(playerid);
public BusStop(playerid)
{
	routetimer[playerid] = KillTimer(routetimer[playerid]); 
    switch(Route[playerid])
	{
		case 8: {
			SetPlayerRaceCheckpoint(playerid, 0, 1673.6885,-1735.4968,13.1609, 1817.8293,-1735.1664,13.1596, 5); //
			Route[playerid] = 9;
		}
		case 13: {
			SetPlayerRaceCheckpoint(playerid, 0, 1876.8849,-1934.8877,13.1628, 1959.1816,-1969.8948,13.2184, 5); //
			Route[playerid] = 14;
		}
		case 25: {
			SetPlayerRaceCheckpoint(playerid, 0, 2607.9146,-1729.6914,12.0120, 2532.1121,-1729.4828,13.1628, 5); //
			Route[playerid] = 26;
		}
		case 28: {
			SetPlayerRaceCheckpoint(playerid, 0, 2276.6689,-1730.1351,13.1628, 2162.4392,-1748.8833,13.1573, 5); //
			Route[playerid] = 29;
		}
		case 37: {
			SetPlayerRaceCheckpoint(playerid, 0, 1504.3635,-1729.6943,13.1603, 1386.4618,-1756.3813,13.1617, 5); //
			Route[playerid] = 38;
		}
	}
}
stock GetDistanceBetweenPlayerz(playerid, targetid, Float:distance) {
	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid)) {
		return 0;
	}
    new Float: pos_x,
    	Float: pos_y,
    	Float: pos_z;
    GetPlayerPos(targetid, pos_x, pos_y, pos_z);
    new Float: result = GetPlayerDistanceFromPoint(playerid, pos_x, pos_y, pos_z);
    if(floatcmp(result, distance) == -1) {
    	return 1;
    } else {
    	return 0;
    }
}
stock ProxDetector(playerid, Float:max_range, color, string[]) {
    new
        Float: pos_x,
        Float: pos_y,
        Float: pos_z,
        world;

    GetPlayerPos(playerid, pos_x, pos_y, pos_z);
    world = GetPlayerVirtualWorld(playerid);

    foreach(new i: Player)
	{
        if (!IsPlayerStreamedIn(playerid, i) || world != GetPlayerVirtualWorld(i)) {
            continue;
        }
        new DistanceToParam = GetDistanceBetweenPlayerz(playerid, i, max_range);
        if(DistanceToParam != 1) {
            continue;
        }
        SendClientMessage(i, color, string);
    }
    return SendClientMessage(playerid, color, string);
}
public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
   	return 1;

}
public OnPlayerGiveDamage(playerid, damagedid, Float: amount, weaponid, bodypart)
{
	return 1;
}
forward UpdateSpeed(playerid);
public UpdateSpeed(playerid)
{
	Timer_Speed[playerid] = KillTimer(Timer_Speed[playerid]); 

    if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return hide_speedo(playerid);
    new v = GetPlayerVehicleID(playerid);
    new speed_vehicle = SpeedVehicle(v);

    for(new i = 0; i < MAX_PLAYERS_CAR; i++) {
		if(IsPlayerInVehicle(playerid, Player.CarVehicleID[playerid][i])) {
			if(speed_vehicle > 2 && speed_vehicle < 30) Player.CarMileage[playerid][i] += 14;
			if(speed_vehicle > 30 && speed_vehicle < 90) Player.CarMileage[playerid][i] += 44;
			if(speed_vehicle > 90 && speed_vehicle < 1200) Player.CarMileage[playerid][i] += 70;
			if(speed_vehicle > 120) Player.CarMileage[playerid][i] += 90;
			if(speed_vehicle % 4) {
				SetPlayerInt(playerid, "Mileage", Player.CarMileage[playerid][i]);
				if(Platform[playerid] == 1) { 
					format(small_string,sizeof(small_string),"%09d",Player.CarMileage[playerid][i]/1000);
				    PlayerTextDrawSetString(playerid,speedo_TD_2[playerid], small_string);
				}
			}
		}
	}
    if(!v) return Timer_Speed[playerid] = SetTimerEx("UpdateSpeed",500,false,"d",playerid); //запускаем }
    if(Platform[playerid] == 1) {
    	update_speedo(playerid, speed_vehicle);
	}
    return Timer_Speed[playerid] = SetTimerEx("UpdateSpeed",500,false,"d",playerid); //запускаем }
}

publics: DrugsEffect(playerid)
{
	DrugTimer[playerid] = KillTimer(DrugTimer[playerid]); 
	new time[3];
	gettime(time[0], time[1], time[2]);
	SetPlayerTime(playerid, time[0], time[1]);
	SetPlayerWeather(playerid, 1);
	SetPlayerDrunkLevel(playerid, 0);
	SetPVarInt(playerid,"DrugsEffect",0);
	return 1;
}
stock IsVehicleOccupied(vehicleid)
{
	foreach(new i: Player)
	{
		if(IsPlayerInVehicle(i, vehicleid)) return i;
	}
	return -1;
}
publics: LoadWareHouse()
{
    new rows = cache_get_row_count();
	
	if(rows)
	{
		for(new he = 0; he < rows; he++)
		{
   		 	Warehouse[he] = cache_get_field_content_int(he,"amount");
    	}
    }
    return 1;
}
publics: LoadGangZone()
{
    new rows = cache_get_row_count();
	new time = GetTickCount();
	if(rows)
	{
	for(new he = 0; he < rows; he++)
		{
			GZInfo[he][gid] = cache_get_field_content_int(he,"id");
			GZInfo[he][gCoords][0] = cache_get_field_content_float(he,"ginfo1");
			GZInfo[he][gCoords][1] = cache_get_field_content_float(he,"ginfo2");
			GZInfo[he][gCoords][2] = cache_get_field_content_float(he,"ginfo3");
			GZInfo[he][gCoords][3] = cache_get_field_content_float(he,"ginfo4");
			
			GZInfo[he][gFrak] = cache_get_field_content_int(he,"fraction");
			switch(GZInfo[he][gFrak])
			{
			 	case 2: TotalZones[2]++;
			 	case 3: TotalZones[3]++;
			 	case 4: TotalZones[4]++;
			 	case 5: TotalZones[5]++;
			 	case 6: TotalZones[6]++;
			}
			TOTALGZ++;
			GZInfo[he][gid] = GangZoneCreate(GZInfo[he][gCoords][0],GZInfo[he][gCoords][1],GZInfo[he][gCoords][2],GZInfo[he][gCoords][3]);
			ZoneOnBattle[he] = 0;
			GZSafeTime[he] = 0;
		}
	}
	printf("Загружено: %d GangZone за %d м.с", TOTALGZ,GetTickCount() - time);
	GetGangSalary();
	return true;
}

publics: LoadProperty()
{
    new rows = cache_get_row_count();
	new time = GetTickCount(), text[190], klass[20];
	if(rows >= 1857) printf("Кол-во домов в базе больше максимального");
	else if(!rows) printf("Домов в базе не найдено");
	else
	{
		TOTALHOUSE = rows;
		for(new he = 1; he <= rows; he++)
		{
			OLD_HouseInfo[he][hID] = cache_get_field_content_int(he-1,"ID");
			OLD_HouseInfo[he][hEntrancex] = cache_get_field_content_float(he-1,"Entrancex");
			OLD_HouseInfo[he][hEntrancey] = cache_get_field_content_float(he-1,"Entrancey");
			OLD_HouseInfo[he][hEntrancez] = cache_get_field_content_float(he-1,"Entrancez");

			OLD_HouseInfo[he][hCarx] = cache_get_field_content_float(he-1,"Carx");
			OLD_HouseInfo[he][hCary] = cache_get_field_content_float(he-1,"Cary");
			OLD_HouseInfo[he][hCarz] = cache_get_field_content_float(he-1,"Carz");
			OLD_HouseInfo[he][hCarc] = cache_get_field_content_float(he-1,"Carc");

			cache_get_field_content(he-1,"Owner",OLD_HouseInfo[he][hOwner]);
			OLD_HouseInfo[he][hPrice] = cache_get_field_content_int(he-1,"Price");
			OLD_HouseInfo[he][hOwned] = cache_get_field_content_int(he-1,"Owned");
			OLD_HouseInfo[he][hTakings] = cache_get_field_content_int(he-1,"Takings");
			OLD_HouseInfo[he][hClass] = cache_get_field_content_int(he-1,"Class");

			switch(OLD_HouseInfo[he][hClass])
			{
			case 0:
			{
			klass = "Эконом";
			OLD_HouseInfo[he][hInt] = 2;
			OLD_HouseInfo[he][hExitx] = 1691.0641;
			OLD_HouseInfo[he][hExity] = -2665.7048;
			OLD_HouseInfo[he][hExitz] = 13.5869;
			}
			case 1:
			{
			klass = "Доступный";
			OLD_HouseInfo[he][hInt] = 3;
			OLD_HouseInfo[he][hExitx] = 1691.0641;
			OLD_HouseInfo[he][hExity] = -2665.7048;
			OLD_HouseInfo[he][hExitz] = 13.5869;
			}
			case 2:
			{
			klass = "Средний";
			OLD_HouseInfo[he][hInt] = 4;
			OLD_HouseInfo[he][hExitx] = 2108.8228;
			OLD_HouseInfo[he][hExity] = -2403.1648;
			OLD_HouseInfo[he][hExitz] = 13.5847;
			}
			case 3:
			{
			klass = "Элитный";
			OLD_HouseInfo[he][hInt] = 5;
			OLD_HouseInfo[he][hExitx] = 1826.4791;
			OLD_HouseInfo[he][hExity] = -2676.6099;
			OLD_HouseInfo[he][hExitz] = 13.6351;
			}
			case 4:
			{
			klass = "Премиум";
			OLD_HouseInfo[he][hInt] = 6;
			OLD_HouseInfo[he][hExitx] = 1826.4791;
			OLD_HouseInfo[he][hExity] = -2676.6099;
			OLD_HouseInfo[he][hExitz] = 13.6351;
			}
			case 5:
			{
			klass = "Люкс";
			OLD_HouseInfo[he][hInt] = 7;
			OLD_HouseInfo[he][hExitx] = 1877.5209;
			OLD_HouseInfo[he][hExity] = -2673.4766;
			OLD_HouseInfo[he][hExitz] = 13.6030;
			}
			}
			
			if(OLD_HouseInfo[he][hOwned] == 0)
			{
				format(text, sizeof(text),"{11FF00}Дом свободен{FFFFFF}\nКласс: {1C82E8}%s{FFFFFF}\nЦена: {1C82E8}$%d{FFFFFF}", klass, OLD_HouseInfo[he][hPrice]);
				OLD_HouseInfo[he][hPickup] = CreateDynamicPickup(1273, 23, OLD_HouseInfo[he][hEntrancex], OLD_HouseInfo[he][hEntrancey], OLD_HouseInfo[he][hEntrancez],-1);
				OLD_HouseInfo[he][hIcon] = CreateDynamicMapIcon(OLD_HouseInfo[he][hEntrancex], OLD_HouseInfo[he][hEntrancey], OLD_HouseInfo[he][hEntrancez], 31, -1, 0, -1, -1, 100.0);
			}
			if(OLD_HouseInfo[he][hOwned] == 1)
			{
				format(text, sizeof(text),"{FF6347}Дом куплен{FFFFFF}\nВладелец: {7CFC00}%s{FFFFFF}\nКласс: {7CFC00}%s{FFFFFF}{FFFFFF}", OLD_HouseInfo[he][hOwner],klass);
				OLD_HouseInfo[he][hPickup] = CreateDynamicPickup(1272, 23, OLD_HouseInfo[he][hEntrancex], OLD_HouseInfo[he][hEntrancey], OLD_HouseInfo[he][hEntrancez],-1);
			}
			OLD_HouseInfo[he][hText] = CreateDynamic3DTextLabel(text, -1, OLD_HouseInfo[he][hEntrancex], OLD_HouseInfo[he][hEntrancey], OLD_HouseInfo[he][hEntrancez]+1, 3.0);
		}
		printf("============================================");
		printf("Загружено: %d домов за %d м.с", TOTALHOUSE, GetTickCount() - time);
	}
	return true;
}


forward GBackSkin(playerid);
public GBackSkin(playerid)
{
	new 
		Fraction: fractionid = GetPlayerFraction(playerid);

	new
		player_karma = PlayerInfo[playerid][pKarma],
		player_sex = PlayerInfo[playerid][pSex];


	new returnid;
	
	if(fractionid == FRACTION_NONE) {
		SetPlayerColor(playerid, CIVIL_COLOR);
		if(player_sex != 0) {
			returnid = 151;
		} else { returnid = 26; }
	}
	if(PlayerInfo[playerid][pSkin] > 0) {
		returnid = PlayerInfo[playerid][pSkin];
		TogglePlayerControllable(playerid, 1);
		SetPVarInt(playerid, "SelSkin", 0);
	}

	switch(fractionid) {
		case FRACTION_LSPD: {
			SetPlayerColor(playerid, LSPD_COLOR);
			if(player_sex != 0) {
				returnid = 150;
			} else {
				if((player_karma <= 299)) {
					returnid = 284;
				} else if((300 <= player_karma <= 499)) {
					returnid = 280;
				} else if((500 <= player_karma)) {
					returnid = 283;
				}
			}
		}
		case FRACTION_GROOVE: {
			SetPlayerColor(playerid, GROVE_COLOR);
			if(player_sex != 0) {
				returnid = 190;
			} else {
				if((-49 <= player_karma)) {
					returnid = 105;
				} else if((-99 <= player_karma <= -50)) {
					returnid = 106;
				} else if((player_karma <= -100)) {
					returnid = 107;
				}
			}
		}
		case FRACTION_BALLAS: {
			SetPlayerColor(playerid, BALLAS_COLOR);
			if(player_sex != 0) {
				returnid = 13;
			} else {
				if((-49 <= player_karma)) {
					returnid = 103;
				} else if((-99 <= player_karma <= -50)) {
					returnid = 102;
				} else if((player_karma <= -100)) {
					returnid = 104;
				}
			}
		}
		case FRACTION_VAGOS: {
			SetPlayerColor(playerid, VAGOS_COLOR);
			if(player_sex != 0) {
				returnid = 226;
			} else {
				if((-49 <= player_karma)) {
					returnid = 108;
				} else if((-99 <= player_karma <= -50)) {
					returnid = 109;
				} else if((player_karma <= -100)) {
					returnid = 110;
				}
			}
		}
		case FRACTION_RIFA: {
			SetPlayerColor(playerid, RIFA_COLOR);
			if(player_sex != 0) {
				returnid = 41;
			} else {
				if((-49 <= player_karma)) {
					returnid = 175;
				} else if((-99 <= player_karma <= -50)) {
					returnid = 174;
				} else if((player_karma <= -100)) {
					returnid = 173;
				}
			}
		}
		case FRACTION_AZTECAS: {
			SetPlayerColor(playerid, AZTEC_COLOR);
			if(player_sex != 0) {
				returnid = 56;
			} else {
				if((-49 <= player_karma)) {
					returnid = 114;
				} else if((-99 <= player_karma <= -50)) {
					returnid = 116;
				} else if((player_karma <= -100)) {
					returnid = 115;
				}
			}
		}
		case FRACTION_RUSSIAN_MAFIA: {
			SetPlayerColor(playerid, RUSSIA_COLOR);
			if(player_sex != 0) {
				returnid = 192;
			} else {
				if((-499 <= player_karma)) {
					returnid = 112;
				} else if((-749 <= player_karma <= -500)) {
					returnid = 111;
				} else if((player_karma <= -750)) {
					returnid = 125;
				}
			}
		}
		case FRACTION_TRIADA: {
			SetPlayerColor(playerid, TRIAD_COLOR);
			if(player_sex != 0) {
				returnid = 263;
			} else {
				if((-499 <= player_karma)) {
					returnid = 117;
				} else if((-749 <= player_karma <= -500)) {
					returnid = 118;
				} else if((player_karma <= -750)) {
					returnid = 120;
				}
			}
		}
		case FRACTION_DN_BOYS: {
			SetPlayerColor(playerid, DANANG_COLOR);
			if(player_sex != 0) {
				returnid = 224;
			} else {
				if((-499 <= player_karma)) {
					returnid = 121;
				} else if((-749 <= player_karma <= -500)) {
					returnid = 122;
				} else if((player_karma <= -750)) {
					returnid = 123;
				}
			}
		}
		case FRACTION_ARMY: {
			SetPlayerColor(playerid, ARMY_COLOR);
			if(player_sex != 0) {
				returnid = 191;
			} else {
				if((150 <= player_karma <= 299)) {
					returnid = 255;
				} else if((300 <= player_karma)) {
					returnid = 61;
				} else if((player_karma <= 149)) {
					returnid = 287;
				}
			}
		}
		case FRACTION_FBI: {
			SetPlayerColor(playerid, FBI_COLOR);
			if(player_sex != 0) {
				returnid = 141;
			} else {
				if((300 <= player_karma <= 399)) {
					returnid = 166;
				} else if((400 <= player_karma)) {
					returnid = 165;
				} else if((player_karma <= 299)) {
					returnid = 286;
				}
			}
		}
		case FRACTION_GOVERMENT: {
			SetPlayerColor(playerid, MAYOR_COLOR);
			if(PlayerInfo[playerid][pSex] != 0) {
				returnid = 76;
			} else {
				returnid = 187;
			}
		}
	}
	TogglePlayerControllable(playerid, 1);
	SetPVarInt(playerid, "SelSkin", 0);
	return returnid;
}
forward CBackSkin(playerid);
public CBackSkin(playerid)
{
	new 
		Fraction: fractionid = GetPlayerFraction(playerid);
	
	if(fractionid == FRACTION_NONE) {
		SetPlayerColor(playerid, CIVIL_COLOR);
		SetPlayerSkin(playerid,26);

		if(PlayerInfo[playerid][pSex] != 0) {
			SetPlayerSkin(playerid, 151);
		}
	}
	if(PlayerInfo[playerid][pSkin] > 0) {
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		TogglePlayerControllable(playerid, 1);
		SetPVarInt(playerid, "SelSkin", 0);
	}
	new
		player_karma = PlayerInfo[playerid][pKarma],
		player_sex = PlayerInfo[playerid][pSex];

	switch(fractionid) {
		case FRACTION_LSPD: {
			SetPlayerColor(playerid, LSPD_COLOR);
			if(player_sex != 0) {
				SetPlayerSkin(playerid, 150);
			} else {
				if((player_karma <= 299)) {
					SetPlayerSkin(playerid, 284);
				} else if((300 <= player_karma <= 499)) {
					SetPlayerSkin(playerid, 280);
				} else if((500 <= player_karma)) {
					SetPlayerSkin(playerid, 283);
				}
			}
		}
		case FRACTION_GROOVE: {
			SetPlayerColor(playerid, GROVE_COLOR);
			if(player_sex != 0) {
				SetPlayerSkin(playerid, 190);
			} else {
				if((-49 <= player_karma)) {
					SetPlayerSkin(playerid, 105);
				} else if((-99 <= player_karma <= -50)) {
					SetPlayerSkin(playerid, 106);
				} else if((player_karma <= -100)) {
					SetPlayerSkin(playerid, 107);
				}
			}
		}
		case FRACTION_BALLAS: {
			SetPlayerColor(playerid, BALLAS_COLOR);
			if(player_sex != 0) {
				SetPlayerSkin(playerid, 13);
			} else {
				if((-49 <= player_karma)) {
					SetPlayerSkin(playerid, 103);
				} else if((-99 <= player_karma <= -50)) {
					SetPlayerSkin(playerid, 102);
				} else if((player_karma <= -100)) {
					SetPlayerSkin(playerid, 104);
				}
			}
		}
		case FRACTION_VAGOS: {
			SetPlayerColor(playerid, VAGOS_COLOR);
			if(player_sex != 0) {
				SetPlayerSkin(playerid, 226);
			} else {
				if((-49 <= player_karma)) {
					SetPlayerSkin(playerid, 108);
				} else if((-99 <= player_karma <= -50)) {
					SetPlayerSkin(playerid, 109);
				} else if((player_karma <= -100)) {
					SetPlayerSkin(playerid, 110);
				}
			}
		}
		case FRACTION_RIFA: {
			SetPlayerColor(playerid, RIFA_COLOR);
			if(player_sex != 0) {
				SetPlayerSkin(playerid, 41);
			} else {
				if((-49 <= player_karma)) {
					SetPlayerSkin(playerid, 175);
				} else if((-99 <= player_karma <= -50)) {
					SetPlayerSkin(playerid, 174);
				} else if((player_karma <= -100)) {
					SetPlayerSkin(playerid, 173);
				}
			}
		}
		case FRACTION_AZTECAS: {
			SetPlayerColor(playerid, AZTEC_COLOR);
			if(player_sex != 0) {
				SetPlayerSkin(playerid, 56);
			} else {
				if((-49 <= player_karma)) {
					SetPlayerSkin(playerid, 114);
				} else if((-99 <= player_karma <= -50)) {
					SetPlayerSkin(playerid, 116);
				} else if((player_karma <= -100)) {
					SetPlayerSkin(playerid, 115);
				}
			}
		}
		case FRACTION_RUSSIAN_MAFIA: {
			SetPlayerColor(playerid, RUSSIA_COLOR);
			if(player_sex != 0) {
				SetPlayerSkin(playerid, 192);
			} else {
				if((-499 <= player_karma)) {
					SetPlayerSkin(playerid, 112);
				} else if((-749 <= player_karma <= -500)) {
					SetPlayerSkin(playerid, 111);
				} else if((player_karma <= -750)) {
					SetPlayerSkin(playerid, 125);
				}
			}
		}
		case FRACTION_TRIADA: {
			SetPlayerColor(playerid, TRIAD_COLOR);
			if(player_sex != 0) {
				SetPlayerSkin(playerid, 263);
			} else {
				if((-499 <= player_karma)) {
					SetPlayerSkin(playerid, 117);
				} else if((-749 <= player_karma <= -500)) {
					SetPlayerSkin(playerid, 118);
				} else if((player_karma <= -750)) {
					SetPlayerSkin(playerid, 120);
				}
			}
		}
		case FRACTION_DN_BOYS: {
			SetPlayerColor(playerid, DANANG_COLOR);
			if(player_sex != 0) {
				SetPlayerSkin(playerid, 224);
			} else {
				if((-499 <= player_karma)) {
					SetPlayerSkin(playerid, 121);
				} else if((-749 <= player_karma <= -500)) {
					SetPlayerSkin(playerid, 122);
				} else if((player_karma <= -750)) {
					SetPlayerSkin(playerid, 123);
				}
			}
		}
		case FRACTION_ARMY: {
			SetPlayerColor(playerid, ARMY_COLOR);
			if(player_sex != 0) {
				SetPlayerSkin(playerid, 191);
			} else {
				if((150 <= player_karma <= 299)) {
					SetPlayerSkin(playerid, 255);
				} else if((300 <= player_karma)) {
					SetPlayerSkin(playerid, 61);
				} else if((player_karma <= 149)) {
					SetPlayerSkin(playerid, 287);
				}
			}
		}
		case FRACTION_FBI: {
			SetPlayerColor(playerid, FBI_COLOR);
			if(player_sex != 0) {
				SetPlayerSkin(playerid, 141);
			} else {
				if((300 <= player_karma <= 399)) {
					SetPlayerSkin(playerid, 166);
				} else if((400 <= player_karma)) {
					SetPlayerSkin(playerid, 165);
				} else if((player_karma <= 299)) {
					SetPlayerSkin(playerid, 286);
				}
			}
		}
		case FRACTION_GOVERMENT: {
			SetPlayerColor(playerid, MAYOR_COLOR);
			if(PlayerInfo[playerid][pSex] != 0) {
				SetPlayerSkin(playerid, 76);
			} else {
				SetPlayerSkin(playerid, 187);
			}
		}
	}
	TogglePlayerControllable(playerid, 1);
	SetPVarInt(playerid, "SelSkin", 0);
	return 1;
}
forward SetColorName(playerid);
public SetColorName(playerid)
{
	new 
		Fraction: fractionid = GetPlayerFraction(playerid);
	
	if(fractionid == FRACTION_NONE) {
		SetPlayerColor(playerid, CIVIL_COLOR);
	}

	switch(fractionid) {
		case FRACTION_LSPD: {
			SetPlayerColor(playerid, LSPD_COLOR);
		}
		case FRACTION_GROOVE: {
			SetPlayerColor(playerid, GROVE_COLOR);
		}
		case FRACTION_BALLAS: {
			SetPlayerColor(playerid, BALLAS_COLOR);
		}
		case FRACTION_VAGOS: {
			SetPlayerColor(playerid, VAGOS_COLOR);
		}
		case FRACTION_RIFA: {
			SetPlayerColor(playerid, RIFA_COLOR);
		}
		case FRACTION_AZTECAS: {
			SetPlayerColor(playerid, AZTEC_COLOR);
		}
		case FRACTION_RUSSIAN_MAFIA: {
			SetPlayerColor(playerid, RUSSIA_COLOR);
		}
		case FRACTION_TRIADA: {
			SetPlayerColor(playerid, TRIAD_COLOR);
		}
		case FRACTION_DN_BOYS: {
			SetPlayerColor(playerid, DANANG_COLOR);
		}
		case FRACTION_ARMY: {
			SetPlayerColor(playerid, ARMY_COLOR);
		}
		case FRACTION_FBI: {
			SetPlayerColor(playerid, FBI_COLOR);
		}
		case FRACTION_GOVERMENT: {
			SetPlayerColor(playerid, MAYOR_COLOR);
		}
	}
	return 1;
}

forward GoAzino(playerid);
public GoAzino(playerid)
{
	AzinoTimer[playerid] = KillTimer(AzinoTimer[playerid]); 
    switch(random(2)) {
		case 0: {
			GameTextForPlayer(playerid, "~g~~h~ + 50 EXP", 2000, 4);
			Player.AddEXP(PlayerInfo[playerid][pID], 50, E_WIN_AZINO, playerid);	
		}
		case 1: {
			GameTextForPlayer(playerid, "~r~Lose", 3000, 5);
		}
		case 2: {
			GameTextForPlayer(playerid, "~g~~h~ + 50 EXP", 2000, 4);
			Player.AddEXP(PlayerInfo[playerid][pID], 50, E_WIN_AZINO, playerid);
		}
		case 3: {
			GameTextForPlayer(playerid, "~r~Lose", 3000, 5);
		}
	}
	return 1;
}

new
	adverts_type = 0;

forward AdverseChance();
public AdverseChance() {
	if(adverts_type == 0) {
		SendClientMessageToAll(-1, ""COLOR_BLUE"Вступайте в наш Discord-канал для общения: {FFFFFF}ChanceRp.Ru/discord");
		SendClientMessageToAll(-1, ""COLOR_BLUE"И в свободную группу Вконтакте: vk.com/chanceroleplay");
		return adverts_type = 1;
	} if(adverts_type == 1) {
		SendClientMessageToAll(-1, ""COLOR_BLUE"Если вы нашли недоработку, сообщите о ней в тех.раздел нашего форума");
		SendClientMessageToAll(-1, ""COLOR_BLUE"Наш форум: {ffffff}talk.chancerp.ru");
		return adverts_type = 2;
	} if(adverts_type == 2) {
		SendClientMessageToAll(-1, ""COLOR_BLUE"Вы играете на сервере {FFFFFF}Chance RolePlay");
		format(small_string, sizeof(small_string), ""COLOR_BLUE"Текущий онлайн: {FFFFFF}%d игроков", Iter_Count(Player));
		SendClientMessageToAll(-1, small_string);
		return adverts_type = 0;
	}
	return SetTimer("AdverseChance", (10 * 60) * 1000, false);
}

stock ShowStats(playerid, targetid) {
	if(IsPlayerConnected(playerid) && IsPlayerConnected(targetid)) {
		new Fraction: fractionid = GetPlayerFraction(playerid);
		new pass_string[526];
		format(small_string, sizeof(small_string), ""COLOR_WHITE"Осталось до зарплаты:\t"COLOR_ORANGE"%s\n",Convert(3600-PlayerInfo[targetid][pOnline]));strcat(pass_string,small_string);
		format(small_string, sizeof(small_string), ""COLOR_WHITE"Проведено часов:\t\t"COLOR_ORANGE"%d\n\n",PlayerInfo[targetid][pHours]);strcat(pass_string,small_string);
		
		format(small_string, sizeof(small_string), ""COLOR_WHITE"Имя:\t\t\t\t"COLOR_ORANGE"%s\n",PlayerInfo[targetid][pName]);strcat(pass_string,small_string);
		format(small_string,sizeof(small_string),""COLOR_WHITE"Пол:\t\t\t\t"COLOR_ORANGE"%s\n", (PlayerInfo[targetid][pSex] == 0) ? ("Мужской") : ("Женский")); strcat(pass_string,small_string);
		format(small_string,sizeof(small_string),""COLOR_WHITE"Законопослушность:\t\t"COLOR_ORANGE"%d\n\n",PlayerInfo[targetid][pKarma]); strcat(pass_string,small_string);

		format(small_string,sizeof(small_string),""COLOR_WHITE"Фракция:\t\t\t"COLOR_ORANGE"%s\n\n", (fractionid == FRACTION_NONE) ? ("Гражданский") : FractionTitle[_:fractionid-1]); strcat(pass_string,small_string);
		
		format(small_string,sizeof(small_string),""COLOR_WHITE"Транспорт:\t\t\t"COLOR_ORANGE"%s\n",GetVehicleText(PlayerInfo[targetid][pCar])); strcat(pass_string,small_string);
		format(small_string,sizeof(small_string),""COLOR_WHITE"Проживание:\t\t\t"COLOR_ORANGE"%s\n\n",(GetPlayerHouse(targetid)) ? ("Дом") : ("Бездомный")); strcat(pass_string,small_string);
		format(small_string,sizeof(small_string),""COLOR_WHITE"Навык фермера:\t\t"COLOR_ORANGE"%d\n",PlayerInfo[targetid][pFarmSkill]); strcat(pass_string,small_string);
		format(small_string,sizeof(small_string),""COLOR_WHITE"Навык автобуса:\t\t"COLOR_ORANGE"%d\n",PlayerInfo[targetid][pBusSkill]); strcat(pass_string,small_string);
		format(small_string,sizeof(small_string),""COLOR_WHITE"Навык пилота:\t\t\t"COLOR_ORANGE"%d\n",PlayerInfo[targetid][pAirSkill]); strcat(pass_string,small_string);
		if(playerid == targetid) {
			return SPD(playerid,
				dStats, DIALOG_STYLE_MSGBOX,
				"Паспорт персонажа",
				pass_string,
				"Назад", "Закрыть"
			);
		} else {
			format(small_string, sizeof(small_string),
				""COLOR_BLUE"Паспорт %s",
				PlayerInfo[playerid][pName]
			);
			return SPD(playerid,
				0, DIALOG_STYLE_MSGBOX,
				"Паспорт персонажа",
				pass_string,
				"", "Закрыть"
			);
		}
	}
	return 1;
}
stock GetVehicleText(vehicleid)
{
	new vehname[18];
	switch(vehicleid)
	{
        case 400: vehname = "Landstalker";
        case 401: vehname = "Bravura";
        case 402: vehname = "Buffalo";
        case 403: vehname = "Linerunner";
        case 404: vehname = "Perenniel";
        case 405: vehname = "Sentinel";
        case 406: vehname = "Dumper";
        case 407: vehname = "Firetruck";
        case 408: vehname = "Trashmaster";
        case 409: vehname = "Stretch";
        case 410: vehname = "Manana";
        case 411: vehname = "Infernus";
        case 412: vehname = "Voodoo";
        case 413: vehname = "Pony";
        case 414: vehname = "Mule";
        case 415: vehname = "Cheetah";
        case 416: vehname = "Ambulance";
        case 417: vehname = "Leviathan";
        case 418: vehname = "Moonbeam";
        case 419: vehname = "Esperanto";
        case 420: vehname = "Taxi";
        case 421: vehname = "Washington";
        case 422: vehname = "Bobcat";
        case 423: vehname = "Mr Whoopee";
        case 424: vehname = "BF Injection";
        case 425: vehname = "Hunter";
        case 426: vehname = "Premier";
        case 427: vehname = "Enforcer";
        case 428: vehname = "Securicar";
        case 429: vehname = "Banshee";
        case 430: vehname = "Predator";
        case 431: vehname = "Bus";
        case 432: vehname = "Rhino";
        case 433: vehname = "Barracks";
        case 434: vehname = "Hotknife";
        case 435: vehname = "Article Trailer";
        case 436: vehname = "Previon";
        case 437: vehname = "Coach";
        case 438: vehname = "Cabbie";
        case 439: vehname = "Stallion";
        case 440: vehname = "Rumpo";
        case 441: vehname = "RC Bandit";
        case 442: vehname = "Romero";
        case 443: vehname = "Packer";
        case 444: vehname = "Monster";
        case 445: vehname = "Admiral";
        case 446: vehname = "Squallo";
        case 447: vehname = "Seasparrow";
        case 448: vehname = "Pizzaboy";
        case 449: vehname = "Tram";
        case 450: vehname = "Article Trailer 2";
        case 451: vehname = "Turismo";
        case 452: vehname = "Speeder";
        case 453: vehname = "Reefer";
        case 454: vehname = "Tropic";
        case 455: vehname = "Flatbed";
        case 456: vehname = "Yankee";
        case 457: vehname = "Caddy";
        case 458: vehname = "Solair";
        case 459: vehname = "Topfun Van";
        case 460: vehname = "Skimmer";
        case 461: vehname = "PCJ-600";
        case 462: vehname = "Faggio";
        case 463: vehname = "Freeway";
        case 464: vehname = "RC Baron";
        case 465: vehname = "RC Raider";
        case 466: vehname = "Glendale";
        case 467: vehname = "Oceanic";
        case 468: vehname = "Sanchez";
        case 469: vehname = "Sparrow";
        case 470: vehname = "Patriot";
        case 471: vehname = "Quad";
        case 472: vehname = "Coastguard";
        case 473: vehname = "Dinghy";
        case 474: vehname = "Hermes";
        case 475: vehname = "Sabre";
        case 476: vehname = "Rustler";
        case 477: vehname = "ZR-350";
        case 478: vehname = "Walton";
        case 479: vehname = "Regina";
        case 480: vehname = "Comet";
        case 481: vehname = "BMX";
        case 482: vehname = "Burrito";
        case 483: vehname = "Camper";
        case 484: vehname = "Marquis";
        case 485: vehname = "Baggage";
        case 486: vehname = "Dozer";
        case 487: vehname = "Maverick";
        case 488: vehname = "SAN News Maverick";
        case 489: vehname = "Rancher";
        case 490: vehname = "FBI Rancher";
        case 491: vehname = "Virgo";
        case 492: vehname = "Greenwood";
        case 493: vehname = "Jetmax";
        case 494: vehname = "Hotring Racer";
        case 495: vehname = "Sandking";
        case 496: vehname = "Blista Compact";
        case 497: vehname = "Police Maverick";
        case 498: vehname = "Boxville";
        case 499: vehname = "Benson";
        case 500: vehname = "Messa";
        case 501: vehname = "RC Goblin";
        case 502: vehname = "Hotring Racer";
        case 503: vehname = "Hotring Racer";
        case 504: vehname = "Bloodring Banger";
        case 505: vehname = "Rancher";
        case 506: vehname = "Super GT";
        case 507: vehname = "Elegant";
        case 508: vehname = "Journey";
        case 509: vehname = "Bike";
        case 510: vehname = "Mountain Bike";
        case 511: vehname = "Beagle";
        case 512: vehname = "Cropduster";
        case 513: vehname = "Stuntplane";
        case 514: vehname = "Tanker";
        case 515: vehname = "Roadtrain";
        case 516: vehname = "Nebula";
        case 517: vehname = "Majestic";
        case 518: vehname = "Buccaneer";
        case 519: vehname = "Shamal";
        case 520: vehname = "Hydra";
        case 521: vehname = "FCR-900";
        case 522: vehname = "NRG-500";
        case 523: vehname = "HPV1000";
        case 524: vehname = "Cement Truck";
        case 525: vehname = "Towtruck";
        case 526: vehname = "Fortune";
        case 527: vehname = "Cadrona";
        case 528: vehname = "FBI Truck";
        case 529: vehname = "Willard";
        case 530: vehname = "Forklift";
        case 531: vehname = "Tractor";
        case 532: vehname = "Combine Harvester";
        case 533: vehname = "Feltzer";
        case 534: vehname = "Remington";
        case 535: vehname = "Slamvan";
        case 536: vehname = "Blade";
        case 537: vehname = "Freight";
        case 538: vehname = "Brownstreak";
        case 539: vehname = "Vortex";
        case 540: vehname = "Vincent";
        case 541: vehname = "Bullet";
        case 542: vehname = "Clover";
        case 543: vehname = "Sadler";
        case 544: vehname = "Firetruck LA";
        case 545: vehname = "Hustler";
        case 546: vehname = "Intruder";
        case 547: vehname = "Primo";
        case 548: vehname = "Cargobob";
        case 549: vehname = "Tampa";
        case 550: vehname = "Sunrise";
        case 551: vehname = "Merit";
        case 552: vehname = "Utility Van";
        case 553: vehname = "Nevada";
        case 554: vehname = "Yosemite";
        case 555: vehname = "Windsor";
        case 556: vehname = "Monster 'A'";
        case 557: vehname = "Monster 'B'";
        case 558: vehname = "Uranus";
        case 559: vehname = "Jester";
        case 560: vehname = "Sultan";
        case 561: vehname = "Stratum";
        case 562: vehname = "Elegy";
        case 563: vehname = "Raindance";
        case 564: vehname = "RC Tiger";
        case 565: vehname = "Flash";
        case 566: vehname = "Tahoma";
        case 567: vehname = "Savanna";
        case 568: vehname = "Bandito";
        case 569: vehname = "Freight Trailer";
        case 570: vehname = "Streak Trailer";
        case 571: vehname = "Kart";
        case 572: vehname = "Mover";
        case 573: vehname = "Dune";
        case 574: vehname = "Sweeper";
        case 575: vehname = "Broadway";
        case 576: vehname = "Tornado";
        case 577: vehname = "AT400";
        case 578: vehname = "DFT-30";
        case 579: vehname = "Huntley";
        case 580: vehname = "Stafford";
        case 581: vehname = "BF-400";
        case 582: vehname = "Newsvan";
        case 583: vehname = "Tug";
        case 584: vehname = "Petrol Trailer";
        case 585: vehname = "Emperor";
        case 586: vehname = "Wayfarer";
        case 587: vehname = "Euros";
        case 588: vehname = "Hotdog";
        case 589: vehname = "Club";
        case 590: vehname = "Freight Box";
        case 591: vehname = "Article Trailer 3";
        case 592: vehname = "Andromada";
        case 593: vehname = "Dodo";
        case 594: vehname = "RC Cam";
        case 595: vehname = "Launch";
        case 596: vehname = "Police Car (LSPD)";
        case 597: vehname = "Police Car (SFPD)";
        case 598: vehname = "Police Car (LVPD)";
        case 599: vehname = "Police Ranger";
        case 600: vehname = "Picador";
        case 601: vehname = "S.W.A.T";
        case 602: vehname = "Alpha";
        case 603: vehname = "Phoenix";
        case 604: vehname = "Glendale Shit";
        case 605: vehname = "Sadler Shit";
        case 606: vehname = "Baggage Trailer";
        case 607: vehname = "Baggage Traier";
        case 608: vehname = "Tug Stairs";
        case 609: vehname = "Boxville";
        case 610: vehname = "Farm Trailer";
        case 611: vehname = "Utility Trailer";
	}
 	return vehname;
}

stock IsAMafia(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		new Fraction: fractionid = GetPlayerFraction(playerid);
		if(fractionid == FRACTION_RUSSIAN_MAFIA || 
			fractionid == FRACTION_TRIADA || 
			fractionid == FRACTION_DN_BOYS) return true;
	}
	return false;
}

stock IsAGang(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		new Fraction: fractionid = GetPlayerFraction(playerid);
		if(fractionid >= FRACTION_GROOVE && fractionid <= FRACTION_AZTECAS) return true;
	}
	return false;
}
forward LoadVehFix(playerid);
public LoadVehFix(playerid) {
	if(IsPlayerInVehicle(playerid, caridhouse[playerid])) return 1;
	SetVehicleToRespawn(caridhouse[playerid]);
	SetPVarInt(playerid, "FixedOneTime", 1);
	return 1;
}
forward CNull(playerid);
public CNull(playerid)
{
	if(CheckCash(playerid, 10000) == false) return SendClientMessage(playerid, -1, ""COLOR_RED"Недостаточно средств");
	Player.DownEXP(PlayerInfo[playerid][pID], 10000, E_BUY_NEW_PASS, playerid);
	PlayerInfo[playerid][pKarma] = 0;
	SetPlayerInt(playerid, "Karma", PlayerInfo[playerid][pKarma]);
	SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы оплатили пошлину и получили новый паспорт");
	return 1;
}
forward CInvite(playerid);
public CInvite(playerid)
{
	if(!IsPlayerInRangeOfPoint(playerid, 2, 1481.3876,-1756.9603,479.2806)) return 1;
	new Fraction: fractionid = GetPlayerFraction(playerid);
	switch(invite_type) {
		case 1: {
			if(PlayerInfo[playerid][pKarma] < -50) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть не ниже: {FFFFFF}-50");
			if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
			if(fractionid == FRACTION_ARMY) {
				SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
				return 1;
			}
			if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
			SetPlayerFraction(playerid, FRACTION_ARMY, true);
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы подписали контракт на срочную службу в армии");
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вам была выдана рация, используйте её для связи: {FFFFFF}/r");
			SetPlayerColor(playerid, ARMY_COLOR);
			CBackSkin(playerid);
			GivePlayerWeapon(playerid, 24, 150);
			GivePlayerWeapon(playerid, 31, 150);
			SetPlayerArmour(playerid, 100);		

			if(Platform[playerid] == 1) SpawnPlayer(playerid);
			return 1;
		}
		case 2: {
	 	    if(PlayerInfo[playerid][pKarma] < 100) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть не менее:{FFFFFF} 100");
	 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
	 		if(fractionid != FRACTION_NONE) {
			 	SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
			 	return 1;
		 	}
		 	if(fractionid > FRACTION_LSPD) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	    SetPlayerFraction(playerid, FRACTION_LSPD, true);
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы устроились на работу в Полицейский Департамент!");
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Ваша задача патрулировать штат и задерживать преступников!");
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вам была выдана рация, используйте её для связи: {FFFFFF}/r");
			SetPlayerColor(playerid, LSPD_COLOR);
			CBackSkin(playerid);
			GivePlayerWeapon(playerid, 24, 150);
			GivePlayerWeapon(playerid, 25, 80);
			GivePlayerWeapon(playerid, 3, 1);
			SetPlayerArmour(playerid, 100);
			
			return 1;
		}
		case 3: {
	 	    if(PlayerInfo[playerid][pKarma] < 250) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть не ниже: {FFFFFF}250");
	 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
	 		if(fractionid == FRACTION_FBI) {
			 	SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
			 	return 1;
		 	}
		 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	    SetPlayerFraction(playerid, FRACTION_FBI, true);
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы устроились в Федеральное Бюро");
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вам была выдана рация, используйте её для связи: {FFFFFF}/r");
			if(Platform[playerid] == 1) SpawnPlayer(playerid);
			SetPlayerColor(playerid, FBI_COLOR);
			CBackSkin(playerid);
			GivePlayerWeapon(playerid, 24, 150);
			GivePlayerWeapon(playerid, 31, 150);
			SetPlayerArmour(playerid, 100);
			
			return 1;
		}
		case 0: {
	 	    if(PlayerInfo[playerid][pKarma] < 500) return SendClientMessage(playerid, -1, ""COLOR_RED"Ваша законопослушность должна быть не ниже: {FFFFFF}500");
	 	    if(GetPVarInt(playerid, "tempjob") > 0) return SendClientMessage(playerid, -1, "Вы уже устроены на другую работу");
	 		if(fractionid == FRACTION_GOVERMENT) {
			 	SendClientMessage(playerid, -1, ""COLOR_ORANGE"Вы уже состоите в данной фракции. Уволиться можно в мэрии");
			 	return 1;
		 	}
		 	if(fractionid != FRACTION_NONE) return SendClientMessage(playerid, -1, ""COLOR_RED"В данный момент вы состоите в другой фракции. Уволиться можно в мэрии");
	 	    SetPlayerFraction(playerid, FRACTION_GOVERMENT, true);
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы устроились в Мэрию");
			//SendClientMessage(playerid, -1, ""COLOR_GREEN"Ваша задача патрулировать штат и задерживать преступников!");
			SendClientMessage(playerid, -1, ""COLOR_GREEN"Вам была выдана рация, используйте её для связи: {FFFFFF}/r");
			SetPlayerColor(playerid, MAYOR_COLOR);
			CBackSkin(playerid);
				
			return 1;
		}
	}
	return 1;
}
forward Law(playerid);
public Law(playerid)
{
    if(!IsPlayerInRangeOfPoint(playerid, 2, 265.9039,77.5524,1001.0391)) return 1;
    if(!IsPlayerConnected(Lawyer)) return 1;
    
    if(CheckCash(playerid, LawPrice[playerid]) == false) return 1;
    
    Player.DownEXP(PlayerInfo[playerid][pID], LawPrice[playerid], E_BUY_LAWYER, playerid);
    format(small_string, sizeof(small_string), ""COLOR_ORANGE"Вы выпустили %s за %d EXP",PlayerInfo[playerid][pName],LawPrice[playerid]/4);
	SendClientMessage(Lawyer, -1, small_string);
	Player.AddEXP(PlayerInfo[Lawyer][pID], LawPrice[playerid]/4, E_JOB_LAWYER, Lawyer);
	PlayerInfo[playerid][pJailTime] = 3;
	PlayerInfo[playerid][pJailed] = 1;
	SetPlayerInt(playerid, "Jailed", PlayerInfo[playerid][pJailed]);
	SetPlayerInt(playerid, "JailTime", PlayerInfo[playerid][pJailTime]);
	return 1;
}
forward LawFail(playerid);
public LawFail(playerid)
{
    if(IsPlayerInRangeOfPoint(playerid, 8, 265.9039,77.5524,1001.0391)) return LeaveTimer[playerid] = SetTimerEx("LawFail", 10000, false, "i", playerid);
    SendClientMessage(playerid, -1, ""COLOR_RED"Вы закончили рабочий день");
	Lawyer = INVALID_PLAYER_ID;
	if(IsValidTimer(LeaveTimer[playerid])) KillTimer(LeaveTimer[playerid]),LeaveTimer[playerid] = -1;
	return 1;
}

forward SelectBin(playerid);
public SelectBin(playerid) {
	BinTimer[playerid] = KillTimer(BinTimer[playerid]); 
    TogglePlayerControllable(playerid, 1);
	if(RouteTrash[playerid] != 0) {
		RouteTrash[playerid] ++;
	}
	switch(RouteTrash[playerid]) {
		case 2: SendClientMessage(playerid, -1, ""COLOR_ORANGE"Загружено: 1/5. Отправляйтесь на следующее место");
		case 3: SendClientMessage(playerid, -1, ""COLOR_ORANGE"Загружено: 2/5. Отправляйтесь на следующее место");
		case 4: SendClientMessage(playerid, -1, ""COLOR_ORANGE"Загружено: 3/5. Отправляйтесь на следующее место");
		case 5: SendClientMessage(playerid, -1, ""COLOR_ORANGE"Загружено: 4/5. Отправляйтесь на следующее место");
	}
	if(RouteTrash[playerid] > 5) {
		SendClientMessage(playerid, -1, ""COLOR_ORANGE"Загружено: 5/5. Отправляйтесь на разгрузку");
    	return SetPlayerRaceCheckpoint(playerid, 1, 2199.5505,-2035.3813,13.1105, 2199.5505,-2035.3813,13.1105, 5); // unload
	}
	switch(random(20)) {
	    case 0: { SetPlayerRaceCheckpoint(playerid, 0, 1486.4631,-1844.8683,13.1102,1486.4631,-1844.8683,13.1102, 5); }
		case 1: SetPlayerRaceCheckpoint(playerid, 0, 1426.2567,-1844.0217,13.1119,1426.2567,-1844.0217,13.1119, 5);
		case 2: SetPlayerRaceCheckpoint(playerid, 0, 1534.4121,-1448.5444,13.3828,1534.4121,-1448.5444,13.3828, 5);
		case 3: SetPlayerRaceCheckpoint(playerid, 0, 1933.9891,-2033.6768,13.1146,1933.9891,-2033.6768,13.1146, 5);
		case 4: SetPlayerRaceCheckpoint(playerid, 0, 2381.4141,-1937.1492,13.1075,2381.4141,-1937.1492,13.1075, 5);
		case 5: SetPlayerRaceCheckpoint(playerid, 0, 2447.9954,-1977.1823,13.1186,2447.9954,-1977.1823,13.1186, 5);
		case 6: SetPlayerRaceCheckpoint(playerid, 0, 2142.8647,-1342.6594,23.5469,2142.8647,-1342.6594,23.5469, 5);
		case 7: SetPlayerRaceCheckpoint(playerid, 0, 1653.6006,-1061.9578,23.4628,1653.6006,-1061.9578,23.4628, 5);
		case 8: SetPlayerRaceCheckpoint(playerid, 0, 1782.2749,-1114.2012,23.6585,1782.2749,-1114.2012,23.6585, 5);
		case 9: SetPlayerRaceCheckpoint(playerid, 0, 1823.9375,-1145.5192,23.5316,1823.9375,-1145.5192,23.5316, 5);
		case 10: SetPlayerRaceCheckpoint(playerid, 0, 1144.2090,-1355.0071,13.2270,1144.2090,-1355.0071,13.2270, 5);
		case 11: SetPlayerRaceCheckpoint(playerid, 0, 957.0651,-1332.2007,13.0208,957.0651,-1332.2007,13.0208, 5);
		case 12: SetPlayerRaceCheckpoint(playerid, 0, 859.3245,-1369.3916,13.1188,859.3245,-1369.3916,13.1188, 5);
		case 13: SetPlayerRaceCheckpoint(playerid, 0, 891.5518,-1359.4219,13.3815,891.5518,-1359.4219,13.3815, 5);
		case 14: SetPlayerRaceCheckpoint(playerid, 0, -60.3018,-1581.0995,2.1778,-60.3018,-1581.0995,2.1778, 5);
		case 15: SetPlayerRaceCheckpoint(playerid, 0, 475.6409,-1741.1163,8.9391,475.6409,-1741.1163,8.9391, 5);
		case 16: SetPlayerRaceCheckpoint(playerid, 0, 1338.9060,-1828.2147,13.1248,1338.9060,-1828.2147,13.1248, 5);
		case 17: SetPlayerRaceCheckpoint(playerid, 0, 1341.1881,-1787.7170,13.1063,1341.1881,-1787.7170,13.1063, 5);
		case 18: SetPlayerRaceCheckpoint(playerid, 0, 2445.5261,-1892.5731,13.1270,2445.5261,-1892.5731,13.1270, 5);
		case 19: SetPlayerRaceCheckpoint(playerid, 0, 2447.2263,-1976.5076,13.1194,2447.2263,-1976.5076,13.1194, 5);
	}
	return 1;
}
stock goneaway(playerid) {
    if(ArmyMission[playerid] > 0) {
        SendClientMessage(playerid, -1, ""COLOR_RED"Миссия по доставке материалов провалена");
		DisablePlayerRaceCheckpoint(playerid);
		ArmyMission[playerid] = 0;
	}
    if(RouteTrash[playerid] > 0) {
        SendClientMessage(playerid, -1, ""COLOR_RED"Вы покинули рабочий транспорт, работа завершена");
		DisablePlayerRaceCheckpoint(playerid);
		RouteTrash[playerid] = 0;
		CBackSkin(playerid);
		SetPVarInt(playerid,"tempjob", 0);
	}
    if(RouteFarm[playerid] > 0) {
    	SendClientMessage(playerid, -1, ""COLOR_RED"Вы покинули рабочий комбаин. Посев отменен");
		DisablePlayerRaceCheckpoint(playerid);
		RouteFarm[playerid] = 0;
	}
    if(Route[playerid] > 0) {
        SendClientMessage(playerid, -1, ""COLOR_RED"Вы покинули рабочий транспорт, работа завершена");
		DisablePlayerRaceCheckpoint(playerid);
		Route[playerid] = 0;
	}
    if(Route2[playerid] > 0) {
    	SendClientMessage(playerid, -1, ""COLOR_RED"Вы покинули рабочий транспорт, работа завершена");
		DisablePlayerRaceCheckpoint(playerid);
		Route2[playerid] = 0;
	}
    if(Route3[playerid] > 0) {
        SendClientMessage(playerid, -1, ""COLOR_RED"Вы покинули рабочий транспорт, работа завершена");
		DisablePlayerRaceCheckpoint(playerid);
		Route3[playerid] = 0;
	}
    if(RouteAir[playerid] > 0) {
    	SendClientMessage(playerid, -1, ""COLOR_RED"Вы покинули рабочий транспорт, работа завершена");
		DisablePlayerRaceCheckpoint(playerid);
		RouteAir[playerid] = 0;
	}
    if(RouteAir2[playerid] > 0) {
        SendClientMessage(playerid, -1, ""COLOR_RED"Вы покинули рабочий транспорт, работа завершена");
		DisablePlayerRaceCheckpoint(playerid);
		RouteAir2[playerid] = 0;
	}
	return gonecar[playerid] = INVALID_VEHICLE_ID;
}
stock onfootverify(playerid) {
	if(gonecar[playerid] == INVALID_VEHICLE_ID) {
		return 1;
	}
	if(ArmyMission[playerid] > 0) {
		gone[playerid] = 20;
		ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
		ReturnTimerID[playerid] = SetTimerEx("count_return", 1000, false, "d", playerid);
		return SendClientMessage(playerid, -1, ""COLOR_RED"Осталось 20 секунд чтобы вернуться в транспорт");
	}
	if(RouteLic[playerid] > 0) {
		SendClientMessage(playerid, -1, ""COLOR_RED"Экзамен провален");
		DisablePlayerRaceCheckpoint(playerid);
		gonecar[playerid] = INVALID_VEHICLE_ID;
		RouteLicAir[playerid] = 0;
		return 1;
	}
	if(RouteTrash[playerid] > 0) {
		gone[playerid] = 20;
		ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
		ReturnTimerID[playerid] = SetTimerEx("count_return", 1000, false, "d", playerid);
		return SendClientMessage(playerid, -1, ""COLOR_RED"Осталось 20 секунд чтобы вернуться в транспорт");
	}
	if(RouteFarm[playerid] > 0) {
		gone[playerid] = 20;
		ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
		ReturnTimerID[playerid] = SetTimerEx("count_return", 1000, false, "d", playerid);
		return SendClientMessage(playerid, -1, ""COLOR_RED"Осталось 20 секунд чтобы вернуться в транспорт");
	}
	if(UnloadFarm[playerid] > 0) {
		gone[playerid] = 20;
		ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
		ReturnTimerID[playerid] = SetTimerEx("count_return", 1000, false, "d", playerid);
		UnloadFarm[playerid] = 0;
		return SendClientMessage(playerid, -1, ""COLOR_RED"Осталось 20 секунд чтобы вернуться в транспорт");
	}
	if(RouteLicAir[playerid] > 0) {
		SendClientMessage(playerid, -1, ""COLOR_RED"Экзамен провален");
		DisablePlayerRaceCheckpoint(playerid);
		gonecar[playerid] = INVALID_VEHICLE_ID;
		RouteLicAir[playerid] = 0;
		return 1;
	}
	if(Route[playerid] > 0) {
		gone[playerid] = 20;
		ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
		ReturnTimerID[playerid] = SetTimerEx("count_return", 1000, false, "d", playerid);
		return SendClientMessage(playerid, -1, ""COLOR_RED"Осталось 20 секунд чтобы вернуться в транспорт");
	}
	if(Route2[playerid] > 0) {
		gone[playerid] = 20;
		ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
		ReturnTimerID[playerid] = SetTimerEx("count_return", 1000, false, "d", playerid);
		return SendClientMessage(playerid, -1, ""COLOR_RED"Осталось 20 секунд чтобы вернуться в транспорт");
	}
	if(Route3[playerid] > 0) {
		gone[playerid] = 20;
		ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
		ReturnTimerID[playerid] = SetTimerEx("count_return", 1000, false, "d", playerid);
		return SendClientMessage(playerid, -1, ""COLOR_RED"Осталось 20 секунд чтобы вернуться в транспорт");
	}
	if(RouteAir[playerid] > 0) {
		gone[playerid] = 20;
		ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
		ReturnTimerID[playerid] = SetTimerEx("count_return", 1000, false, "d", playerid);
		return SendClientMessage(playerid, -1, ""COLOR_RED"Осталось 20 секунд чтобы вернуться в транспорт");
	}
	if(RouteAir2[playerid] > 0) {
		gone[playerid] = 20;
		ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
		ReturnTimerID[playerid] = SetTimerEx("count_return", 1000, false, "d", playerid);
		return SendClientMessage(playerid, -1, ""COLOR_RED"Осталось 20 секунд чтобы вернуться в транспорт");
	}
	return gonecar[playerid] = INVALID_VEHICLE_ID;
}
stock Float:GetPlayerDistanceToPlayer(playerid, targetid)
{
	new Float:x, Float:y, Float:z, Float:x2, Float:y2, Float:z2;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerPos(targetid, x2, y2, z2);
	return floatsqroot(floatadd(floatpower(x2-x,2),floatpower(y2-y,2)));
}
stock DoAction(const playerid, const action[], const Float:distance = 13.0)
{
	new mes[128];
	format(mes,sizeof(mes),"%s (%s)",action,PlayerInfo[playerid][pName]);
	foreach(new i: Player)
	{
		if(GetPlayerDistanceToPlayer(playerid,i) > distance || GetPlayerVirtualWorld(i) != GetPlayerVirtualWorld(playerid)) continue;
		SendClientMessage(i,0xDD90FFFF,mes);
	}
	return true;
}

stock timer_count_off(const playerid) {
	 gone[playerid] = -1; 
	 ReturnTimerID[playerid] = KillTimer(ReturnTimerID[playerid]);
	 return 1;
}

forward RunwayUpdate(const way);
public RunwayUpdate(const way) {
	if(way == 0) { Runway[0] = 0; }
	if(way == 1) { Runway[1] = 0; }
	return 1;
}
stock Alcohol(const playerid) {
	 	if(GetPVarInt(playerid,"Bought") > gettime()){ return false; }
		if(CheckCash(playerid, 15) == false) return 1;
		GameTextForPlayer(playerid, "~r~-15 ~w~EXP", 3000, 5);
		Player.DownEXP(PlayerInfo[playerid][pID], 15, E_BUY_DRINK, playerid);
		switch(random(7))
		{
		    case 0: {
			    SetPlayerChatBubble(playerid, "выпил(а) бокал виски", C_PURPLE, 30.0, 5000);
				format(small_string, 100, "%s выпил(а) бокал виски", PlayerInfo[playerid][pName]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				SetPlayerDrunkLevel (playerid, 3000);
		    }
		    case 1: {
			    SetPlayerChatBubble(playerid, "выпил(а) бокал вина", C_PURPLE, 30.0, 5000);
				format(small_string, 100, "%s выпил(а) бокал вина", PlayerInfo[playerid][pName]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				SetPlayerDrunkLevel (playerid, 2000);
		    }
		    case 2: {
			    SetPlayerChatBubble(playerid, "выпил(а) рюмку водки", C_PURPLE, 30.0, 5000);
				format(small_string, 100, "%s выпил(а) рюмку водки", PlayerInfo[playerid][pName]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				SetPlayerDrunkLevel (playerid, 5000);
		    }
		    case 3: {
			    SetPlayerChatBubble(playerid, "выпил(а) стопку абсента", C_PURPLE, 30.0, 5000);
				format(small_string, 100, "%s выпил(а) стопку абсента", PlayerInfo[playerid][pName]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				SetPlayerDrunkLevel (playerid, 4000);
		    }
		    case 4: {
			    SetPlayerChatBubble(playerid, "выпил(а) бокал рома", C_PURPLE, 30.0, 5000);
				format(small_string, 100, "%s выпил(а) бокал рома", PlayerInfo[playerid][pName]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				SetPlayerDrunkLevel (playerid, 3000);
		    }
		    case 5: {
			    SetPlayerChatBubble(playerid, "выпил(а) кружку пива", C_PURPLE, 30.0, 5000);
				format(small_string, 100, "%s выпил(а) кружку пива", PlayerInfo[playerid][pName]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				SetPlayerDrunkLevel (playerid, 2000);
		    }
		    case 6: {
			    SetPlayerChatBubble(playerid, "выпил(а) стопку коньяка", C_PURPLE, 30.0, 5000);
				format(small_string, 100, "%s выпил(а) стопку коньяка", PlayerInfo[playerid][pName]);
				ProxDetector(playerid, MAX_DISTANCE_VISIBLE, C_PURPLE, small_string);
				SetPlayerDrunkLevel (playerid, 3000);
		    }
		}
		

		SetPlayerChatBubble(playerid, "выпил(а)", C_PURPLE, 10.0, 2000);
		SendClientMessage(playerid, -1, ""COLOR_GREEN"Вы купили алкоголь и выпили");
		SetPVarInt(playerid,"Bought",gettime() + 10);
		return 1;
}

static const AirVeh[] = { 592, 577, 511, 512, 593, 520, 553, 476, 519, 460, 513, 548, 425, 417, 487, 488, 497, 563, 447, 469 };

stock IsAirVehicle(const vehicleid)
{
    for(new i = 0; i < sizeof(AirVeh); i++)
    {
        if(GetVehicleModel(vehicleid) == AirVeh[i]) return 1;
    }
    return 0;
}

stock SetPlayerWanted(const playerid, const level) {
	if(level != 0) {

		if((10801 >= level)) SetPlayerWantedLevel(playerid, 6);
		if((7201 <= level <= 10800)) SetPlayerWantedLevel(playerid, 5);
		if((5401 <= level <= 7200)) SetPlayerWantedLevel(playerid, 4);
		if((3601 <= level <= 5400)) SetPlayerWantedLevel(playerid, 3);
		if((301 <= level <= 3600)) SetPlayerWantedLevel(playerid, 2);
		if((0 <= level <= 300)) SetPlayerWantedLevel(playerid, 1);


		if(Iter_Contains(PlayerWanted, playerid) == 0) {
			Iter_Add(PlayerWanted, playerid);
		}
	} else {
		SetPlayerWantedLevel(playerid, 0);
		if(Iter_Contains(PlayerWanted, playerid) == 1) {
			Iter_Remove(PlayerWanted, playerid);
		}
	}

	return PlayerInfo[playerid][pWanted] = level;
}

// 77082036172

stock SetVehicleParamsForPlayerEx(vehicleid, playerid, objective, doorslocked) 
{
	SetVehicleParamsForPlayer(vehicleid, playerid, objective, doorslocked);
	new Float:xx,Float:yy,Float:zz;
	GetVehiclePos(vehicleid, xx, yy, zz);
	foreach(new i: Player) { 
		if(IsPlayerInRangeOfPoint(i, 100, xx, yy, zz)) 
			SetVehicleParamsForPlayer(vehicleid, i, objective, doorslocked); 
	}
    VehicleParameters[vehicleid][0] = objective; 
    VehicleParameters[vehicleid][1] = doorslocked; 
    return 1;
}

public OnPlayerEnterDynamicRaceCP(playerid, STREAMER_TAG_RACE_CP checkpointid) {
	return 1;
}
