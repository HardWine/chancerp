#if defined _enterance_included
	#endinput
#endif
#define _enterance_included

#define INVALID_ICON_ID			-1
#define ICON_VIEW_DISTANCE		400.0

#define MAX_DOOR				112
#define AREA_SIZE 				1.5
#define DOOR_PICKUP_TYPE		1
#define DOOR_STREAM_DISTANCE	175.0
#define DOOR_VW_ADDENDUM		100	

#define ENTERANCE 				0
#define EXIT 					1

#define COST_247SHOP            100000
#define COST_BAR                60000
#define COST_CLUB               250000
#define COST_RESTRAUNT          125000
#define COST_BARBER             70000
#define COST_TATTOO             50000
#define COST_CLOTHES            300000
#define COST_AMMUNATION         320000
#define COST_GYM                225000

/*

    Extras Note:
    Extra #1: Air Conditioner sound play on enter and stop on exit.
    Usable in custom created interiors.
    Extra #2: Extra to create pickup in previous pickup world.
    Use this to create pickup in special VW.

*/

// 0 - ENTERANCE, 1 - EXIT. Simple
new Door_Pickup[MAX_DOOR][2];
new Door_Area[MAX_DOOR][2];

enum
    EnterCoords__ {
        Float:ent_X,
        Float:ent_Y,
        Float:ent_Z,
        Float:ent_A,
        Float:ent_X2,
        Float:ent_Y2,
        Float:ent_Z2,
        Float:ent_A2,   
    };

enum
    StructurePickup__ {
    	Model,
        Float:ent_X,
        Float:ent_Y,
        Float:ent_Z,
    	Model2,
        Float:ent_X2,
        Float:ent_Y2,
        Float:ent_Z2,        
    };  

enum
    Properties__ {
		IID,
		Icon,  
        Extra,
        IName[32], 
        ICost,
    };         

new
    Pickup[MAX_DOOR][StructurePickup__] = {
    	// 24/7 El Corona
    	{1274,1833.7821,-1842.6052,13.5781,
    	1274,-25.9,-141.5574,1003.5469},    
    	// 24/7 Idlewood
    	{1274,1928.5931,-1776.3269,13.5469,
    	1274,-27.3530,-58.2693,1003.5469},    
    	// 24/7 Willowfield
    	{1274,2424.8186,-1922.2562,13.5385,
    	1274,-27.3530,-58.2693,1003.5469},  
    	// 24/7 Ganton
    	{1274,2424.2307,-1742.7959,13.5458,
    	1274,-27.3530,-58.2693,1003.5469},  	
    	// 24/7 Commerce
    	{1274,1352.3857,-1759.2537,13.5078,
    	1274,-31.0124,-92.0106,1003.5469},  	
    	// 24/7 Market
    	{1274,1128.6615,-1270.5221,13.546,
    	1274,-27.3530,-58.2693,1003.5469}, 
    	// 24/7 Commerce 2
    	{1274,1398.6876,-1881.7793,13.5469,
    	1274,-25.9,-141.5574,1003.5469},   
    	// 24/7 Idlewood 2
    	{1274,2001.8527,-1761.9608,13.5391,
    	1274,-25.9,-141.5574,1003.5469},   
    	// 24/7 East
    	{1274,2353.5498,-1534.0009,24.0000,
    	1274,-25.9,-141.5574,1003.5469},   
    	// 24/7 East 2
    	{1274,2380.9109,-1213.6266,27.4223,
    	1274,-25.9,-141.5574,1003.5469},   
    	// 24/7 Market 2
    	{1274,1104.8522,-1370.0302,13.9844,
    	1274,-25.9,-141.5574,1003.5469},   
    	// 24/7 Mulholland
    	{1274,1000.5950,-919.9266,42.3281,
    	1274,-31.0124,-92.0106,1003.5469},  
    	// 24/7 Mulholland 2
    	{1274,1315.5129,-897.6816,39.5781,
    	1274,-31.0124,-92.0106,1003.5469},  
    	// 24/7 Las Colinas
    	{1274,2713.1062,-1108.8516,69.5775,
    	1274,-31.0124,-92.0106,1003.5469},  
    	// Idlewood Pizza Stack
    	{1274,2105.4885,-1806.5076,13.5547,
    	1274,372.3855,-133.5249,1001.4922},  
    	// Cluckin Bell Willowfield
    	{1274,2397.8367,-1899.1863,13.5469,
    	1274,364.8856,-11.7540,1001.8516},  
    	// Cluckin Bell East
    	{1274,2419.8235,-1508.9697,24.0000,
    	1274,364.8856,-11.7540,1001.8516},  
    	// Cluckin Bell Market
    	{1274,928.9166,-1352.9690,13.3438,
    	1274,364.8856,-11.7540,1001.8516},  
    	// Burger Shot Marina
    	{1274,810.4847,-1616.1897,13.5469,
    	1274,362.8949,-75.1884,1001.5078},  
    	// Burger Shot Mulholland
    	{1274,1199.2744,-918.1514,43.1230,
    	1274,362.8949,-75.1884,1001.5078},  
    	// Tattoo Parlor Idlewood
    	{1274,2068.5803,-1779.8092,13.5596,
    	1274,-204.3987,-44.4025,1002.2734},  
    	// Tattoo Parlor El Corona
    	{1274,1976.6520,-2036.6708,13.5469,
    	1274,-204.3987,-44.4025,1002.2734},  
    	// Barbershop Idlewood
    	{1274,2070.6267,-1793.8221,13.5469,
    	1274,418.5679,-84.3685,1001.8047},  
    	// Barbershop Playa Del Sevile
    	{1274,2724.4570,-2026.5740,13.5547,
    	1274,411.6237,-23.1645,1001.8047}, 
    	// Barbershop Marina
    	{1274,824.0261,-1588.2869,13.5436,
    	1274,411.6237,-23.1645,1001.8047},   
    	// Club Alhambra
    	{1274,1836.9614,-1682.4702,13.3261,
    	1274,493.4008,-24.8784,1000.6797},  
    	// Strip Club Pig Pen
    	{1274,2421.5510,-1219.2424,25.5616,
    	1274,1204.7811,-13.8520,1000.9219}, 
    	// Bar 10 Green Bottles 
    	{1274,2310.0737,-1643.5228,14.8270,
    	1274,501.9419,-67.5630,998.7578}, 
    	// Bar Atlantic
    	{1274,2361.3987,-1332.4882,24.0044,
    	1274,501.9419,-67.5630,998.7578}, 
    	// Bar El Corona
    	{1274,1951.4489,-2041.3254,13.5469,
    	1274,501.9419,-67.5630,998.7578}, 
    	// Ammunation
    	{1274,1368.8180,-1279.7813,13.5469,
    	1274,285.3991,-41.7380,1001.5156},     
    	// Ammunation Willowfield
    	{1274,2400.4822,-1981.9956,13.5469,
    	1274,296.8440,-112.0707,1001.5156},   	
    	// Binco
    	{1274,2244.3516,-1665.4622,15.47669,
    	1274,207.6364,-111.2670,1005.1328},       	
    	// Sub Urban
    	{1274,2112.8379,-1211.4554,23.9629,
    	1274,203.7464,-50.6655,1001.8047},    
    	// Zip
    	{1274,1456.4812,-1137.5978,23.9483,
    	1274,161.3591,-97.1104,1001.8047},   
    	// Victim
    	{1274,461.7101,-1500.8400,31.0449,
    	1274,227.4614,-8.1838,1002.2109},  
    	// Didier Sachs
    	{1274,454.2079,-1477.9941,30.8143,
    	1274,204.2840,-168.8605,1000.5234},  
    	// Pro Laps
    	{1274,499.5103,-1360.6260,16.3691,
    	1274,207.0273,-140.3763,1003.5078},  
        // Barbershop Dillimore
        {1274,672.0863,-496.8552,16.3359,
        1274,418.5679,-84.3685,1001.8047},
        // Dillimore Pizza Stack
        {1274,203.4313,-201.9456,1.5781,
        1274,372.3855,-133.5249,1001.4922},
        // Montgomery Pizza Stack
        {1274,1367.7906,248.2575,19.5669,
        1274,372.3855,-133.5249,1001.4922},
        // Palomino Creek Pizza Stack
        {1274,2331.8088,75.0731,26.6210,
        1274,372.3855,-133.5249,1001.4922},
        // Ammunation Blueberry
        {1274,243.2948,-178.3618,1.5822,
        1274,285.3991,-41.7380,1001.5156},   
        // Ammunation Palomino Creek
        {1274,2333.2134,61.5893,26.7058,
        1274,285.3991,-41.7380,1001.5156},   
        // Ammunation Angel Pine
        {1274,-2093.6792,-2464.9319,30.6250,
        1274,285.3991,-41.7380,1001.5156},   
        // 24/7 Whetstone
        {1274,-1562.5875,-2733.0005,48.7435,
        1274,-25.9,-141.5574,1003.5469},    
        // Cluckin Bell Angel Pine
        {1274,-2155.2996,-2460.1426,30.8516,
        1274,364.8856,-11.7540,1001.8516},  
        // Cluckin Bell Emerald Isle
        {1274,2101.8923,2228.8252,11.0234,
        1274,364.8856,-11.7540,1001.8516},  
        // Cluckin Bell Fort Carson
        {1274,172.9955,1177.1760,14.7578,
        1274,364.8856,-11.7540,1001.8516},  
        // 24/7 Fort Carson
        {1274,-99.1745,1083.2277,19.7500,
        1274,-25.9,-141.5574,1003.5469}, 
        // Bar Fort Carson
        {1274,-179.7101,1087.4896,19.7422,
        1274,501.9419,-67.5630,998.7578}, 
        // Ammunation Fort Carson
        {1274,-316.1622,829.8685,14.2422,
        1274,285.3991,-41.7380,1001.5156},    
        // Ammunation El Quebrados
        {1274,-1508.8744,2610.7014,55.8359,
        1274,296.8440,-112.0707,1001.5156},  
        // Ammunation Bone County
        {1274,776.7212,1871.4183,4.9067,
        1274,296.8440,-112.0707,1001.5156},  
        // Binco Las Venturas
        {1274,1657.0374,1733.3226,10.8281,
        1274,207.6364,-111.2670,1005.1328},  
        // Binco Emerald Isle
        {1274,2101.8923,2257.4336,11.0234,
        1274,207.6364,-111.2670,1005.1328},  
        // Barbershop Redsands East
        {1274,2080.3474,2122.8650,10.8203,
        1274,411.6237,-23.1645,1001.8047}, 
        // Tattoo Parlor Redsands East
        {1274,2094.7502,2122.8594,10.8203,
        1274,-204.3987,-44.4025,1002.2734},  
        // Zip Emerald Isle
        {1274,2090.4822,2224.7009,11.0234,
        1274,161.3591,-97.1104,1001.8047},  
        // 24/7 Redsands East
        {1274,1937.8262,2307.2622,10.8203,
        1274,-31.0124,-92.0106,1003.5469},  
        // 24/7 Emerald Isle
        {1274,2097.6267,2224.7014,11.0234,
        1274,-31.0124,-92.0106,1003.5469},  
        // 24/7 Starfish Casino
        {1274,2194.9407,1990.9999,12.2969,
        1274,-27.3530,-58.2693,1003.5469}, 
        // 24/7 Roca Escalante
        {1274,2247.6597,2396.1907,10.8203,
        1274,-27.3530,-58.2693,1003.5469}, 
        // Burger Shot Whitewood
        {1274,1157.9176,2072.2566,11.0625,
        1274,362.8949,-75.1884,1001.5078},  
        // Burger Shot Redsands East
        {1274,1872.2539,2071.8794,11.0625,
        1274,362.8949,-75.1884,1001.5078}, 
        // Burger Shot Spiny Bed
        {1274,2169.4082,2795.8667,10.8203,
        1274,362.8949,-75.1884,1001.5078}, 
        // Roca Escalante Pizza Stack
        {1274,2351.8264,2533.6289,10.8203,
        1274,372.3855,-133.5249,1001.4922},
        // Emerald Isle Pizza Stack
        {1274,2083.3523,2224.7012,11.0234,
        1274,372.3855,-133.5249,1001.4922},
        // Pilgrim Pizza Stack
        {1274,2638.7881,1849.8163,11.0234,
        1274,372.3855,-133.5249,1001.4922},
        // Creek Pizza Stack
        {1274,2756.7976,2477.3203,11.0625,
        1274,372.3855,-133.5249,1001.4922},
        // Burger Shot Old Venturas Strip
        {1274,2472.8660,2034.1683,11.0625,
        1274,362.8949,-75.1884,1001.5078}, 
        // Old Venturas Strip 24/7
        {1274,2452.4978,2065.1875,10.8203,
        1274,-25.9,-141.5574,1003.5469},  
        // Starfish Casino 24/7
        {1274,2546.5122,1972.6677,10.8203,
        1274,-25.9,-141.5574,1003.5469},  
        // Creek 24/7
        {1274,2884.5461,2454.0396,11.0690,
        1274,-25.9,-141.5574,1003.5469},  
        // Ammunation Old Venturas Strip
        {1274,2539.5427,2083.9414,10.8203,
        1274,296.8440,-112.0707,1001.5156},  
        // Ammunation Come-A-Lot
        {1274,2159.4763,943.1951,10.8203,
        1274,296.8440,-112.0707,1001.5156},
        // Ammunation Ocean Flats
        {1274,-2626.6179,208.2481,4.8125,
        1274,285.3991,-41.7380,1001.5156},   
        // Pier 69 Pizza Stack
        {1274,-1721.1553,1359.7078,7.1853,
        1274,372.3855,-133.5249,1001.4922},  
        // Financial Pizza Stack
        {1274,-1808.7339,945.8966,24.8906,
        1274,372.3855,-133.5249,1001.4922},  
        // Cluckin Bell Old Venturas Strip
        {1274,2393.2317,2041.6425,10.8203,
        1274,364.8856,-11.7540,1001.8516},  
        // Cluckin Bell Piligrim
        {1274,2638.2246,1671.9332,11.0234,
        1274,364.8856,-11.7540,1001.8516},  
        // Cluckin Bell Creek
        {1274,2838.1956,2407.6873,11.0690,
        1274,364.8856,-11.7540,1001.8516},  
        // Cluckin Bell Downtown
        {1274,-1816.5630,618.5236,35.1719,
        1274,364.8856,-11.7540,1001.8516},  
        // Cluckin Bell City Hall SF
        {1274,-2672.2358,257.9239,4.6328,
        1274,364.8856,-11.7540,1001.8516},  
        // Burger Shot Downtown
        {1274,-1912.3940,827.8785,35.2265,
        1274,362.8949,-75.1884,1001.5078}, 
        // Burger Shot Juniper Hollow
        {1274,-2356.0449,1008.0203,50.8984,
        1274,362.8949,-75.1884,1001.5078}, 
        // Burger Shot Garcia
        {1274,-2336.8679,-166.7862,35.5547,
        1274,362.8949,-75.1884,1001.5078}, 
        // Bar Old Venturas Strip
        {1274,2441.1182,2065.4846,10.8203,
        1274,501.9419,-67.5630,998.7578}, 
        // Bar Garcia
        {1274,-2242.1443,-88.2245,35.3203,
        1274,501.9419,-67.5630,998.7578}, 
        // Barbershop Queens
        {1274,-2571.3435,246.7722,10.4535,
        1274,418.5679,-84.3685,1001.8047},  
        // Tattoo Parlor Hushberry
        {1274,-2490.9951,-38.8902,25.6172,
        1274,-204.3987,-44.4025,1002.2734},  
        // Zip Piligrim
        {1274,2572.0598,1904.9429,11.0234,
        1274,161.3591,-97.1104,1001.8047},  
        // Zip Downtown
        {1274,-1882.2714,866.5182,35.1719,
        1274,161.3591,-97.1104,1001.8047},  
        // Binco Juniper Hill
        {1274,-2373.8665,910.1220,45.4453,
        1274,207.6364,-111.2670,1005.1328},    
        // Pro Laps Creek
        {1274,2826.1248,2407.5249,11.0625,
        1274,207.0273,-140.3763,1003.5078},  
        // Sub Urban Creek
        {1274,2779.7537,2453.8962,11.0625,
        1274,203.7464,-50.6655,1001.8047},    
        // Sub Urban Hashbury
        {1274,-2489.8618,-29.0739,25.6172,
        1274,203.7464,-50.6655,1001.8047},  
        // Victim Creek
        {1274,2802.9421,2430.7078,11.0625,
        1274,227.4614,-8.1838,1002.2109},  
        // Victim Financial
        {1274,-1694.5596,951.8972,24.8906,
        1274,227.4614,-8.1838,1002.2109},  



    //};
         //* Common pickups starts here *//
        // Pleasure Domes
        {1318,-2624.6465,1412.7330,7.0938,
        1318,-2636.6802,1402.4667,906.4609},         
        // Ganton Gym
        {1318,2229.9011,-1721.2567,13.5613,
        1318,772.2991,-5.5162,1000.7285},
        // Cobra Gym
        {1318,-2270.5930,-155.9438,35.3203,
        1318,774.1147,-50.4770,1000.5859},
        // LV Gym
        {1318,1968.7786,2295.8726,16.4559,
        1318,773.8799,-78.8459,1000.6628},
        // Hospital LS
        {1318,1172.0946,-1323.3228,15.4029,
        1318,1124.3765,-1316.7871,1788.9514},
        // Hospital SF
        {1318,-2655.0825,640.1654,14.4545,
        1318,1124.3765,-1316.7871,1788.9514},
        // Hospital LV
        {1318,1607.3817,1815.2421,10.8203,
        1318,1124.3765,-1316.7871,1788.9514},
        // San News
        {1318,1653.9393,-1654.7565,22.5156,
        1318,1175.2660,-1189.9443,87.0787},
        // Church LS
        {1318,1720.2656,-1741.1660,13.5469,
        1318,388.2274,2324.3857,1889.5764},
        // Church SF
        {1318,-1989.8995,1117.8882,54.4688,
        1318,388.2274,2324.3857,1889.5764},
        // Church LV
        {1318,2519.9985,918.4730,11.0234,
        1318,388.2274,2324.3857,1889.5764},
        // Driving School
        {1318,-2026.7,-101.7283,35.1641,
        1318,-2026.9160,-103.6016,1035.1836},
        // Trucker Office
        {1318,-49.8653,-267.3860,6.1832,
        1318,217.9692,1752.1858,3000.8308}     

};

new
    EnterCoords[MAX_DOOR][EnterCoords__] = {
    	// 24/7 El Corona
    	{-26.2114,-139.1527,1003.5469,0.0,
    	1831.1776,-1842.4895,13.5781,90.0},
    	// 24/7 Idlewood
    	{-27.3447,-55.8258,1003.5469,0.0,
    	1930.9739,-1776.2433,13.5469,270.0},
    	// 24/7 Willowfield
    	{-27.3447,-55.8258,1003.5469,0.0,
    	2422.2754,-1923.9199,13.5469,125.0},
    	// 24/7 Ganton
    	{-27.3447,-55.8258,1003.5469,0.0,
    	2421.9954,-1740.6545,13.5469,47.7},
    	// 24/7 Commerce
    	{-30.9875,-89.6806,1003.5469,360.0000,
    	1352.4203,-1755.5282,13.3538,0.0},
    	// 24/7 Market
    	{-27.3447,-55.8258,1003.5469,0.0,
    	1128.8197,-1273.3861,13.5469,180.0},
    	// 24/7 Commerce 2
    	{-26.2114,-139.1527,1003.5469,0.0,
    	1398.4012,-1878.9829,13.5469,0.0},
    	// 24/7 Idlewood 2
    	{-26.2114,-139.1527,1003.5469,0.0,
    	2001.7920,-1758.7308,13.5469,0.0},
    	// 24/7 East
    	{-26.2114,-139.1527,1003.5469,0.0,
    	2353.4822,-1530.9946,24.0000,0.0},
    	// 24/7 East 2
    	{-26.2114,-139.1527,1003.5469,0.0,
    	2377.4456,-1213.7982,27.4297,90.0},
    	// 24/7 Market 2
    	{-26.2114,-139.1527,1003.5469,0.0,
    	1105.2175,-1373.5896,13.9844,180.0},
    	// 24/7 Mulholland
    	{-30.9875,-89.6806,1003.5469,360.0000,
    	997.6285,-920.4487,42.1797,100.0},
    	// 24/7 Mulholland 2
    	{-30.9875,-89.6806,1003.5469,360.0000,
    	1315.3120,-900.6538,39.5781,180.0},
    	// 24/7 Las Colinas
    	{-30.9875,-89.6806,1003.5469,360.0000,
    	2716.0515,-1108.7679,69.5736,270.0},
    	// Idlewood Pizza
    	{372.4435,-130.8061,1001.4922,0.0000,
    	2102.6565,-1806.4850,13.55471,90.0},
    	// Cluckin Bell Willowfield
    	{366.0002,-9.4338,1001.8516,360.0,
    	2397.8826,-1896.1918,13.3828,360.0},
    	// Cluckin Bell East
    	{366.0002,-9.4338,1001.8516,360.0,
    	2422.6814,-1508.8746,23.9922,270.0},
    	// Cluckin Bell Market
    	{366.0002,-9.4338,1001.8516,360.0,
    	926.0221,-1352.9316,13.3438,90.0},
    	// Burger Shot Marina
    	{366.0545,-73.3270,1001.5078,318.7592,
    	813.4742,-1616.4459,13.5547,256.5499},
    	// Burger Shot Mulholland
    	{366.0545,-73.3270,1001.5078,318.7592,
    	1199.6510,-921.0301,43.1035,187.0},
    	// Tattoo Parlor Idlewood
    	{-204.1540,-41.9165,1002.2734,0.0,
    	2071.5454,-1779.6984,13.5596,270.0},
    	// Tattoo Parlor El Corona
    	{-204.1540,-41.9165,1002.2734,0.0,
    	1973.8174,-2036.7526,13.5469,90.0},
    	// Barbershop Idlewood
    	{418.5297,-81.4262,1001.8047,0.0,
    	2073.6250,-1793.9183,13.5469,270.0},
    	// Barbershop Playa Del Sevile
    	{411.6730,-20.4541,1001.8047,360.0,
    	2721.2080,-2026.6320,13.5472,90.0},
    	// Barbershop Marina
    	{411.6730,-20.4541,1001.8047,360.0,
    	822.0331,-1590.5200,13.5545,138.0},
    	// Club Alhambra
    	{493.2604,-21.4579,1000.6797,0.0,
    	1833.4507,-1682.4767,13.4728,90.0},
    	// Strip Club Pig Pen
    	{1205.0081,-10.7681,1000.9219,0.0,
    	2421.5781,-1222.8376,25.3321,180.0},
		// Bar 10 Green Bottles 
		{502.0477,-70.6021,998.7578,180.0,
		2307.8220,-1646.1943,14.8270,180.0},
		// Bar Atlantic
		{502.0477,-70.6021,998.7578,180.0,
		2364.7141,-1332.4061,24.0078,270.0},
		// Bar El Corona
		{502.0477,-70.6021,998.7578,180.0,
		1955.0370,-2041.2200,13.5469,270.0},	
		// Ammunation
		{285.4748,-38.7987,1001.5156,360.0,
		1365.9216,-1279.8931,13.5469,90.0},			
		// Ammunation Willowfield	
		{296.8887,-109.2648,1001.5156,360.0,
		2400.4822,-1979.0392,13.5469,0.0},		
		// Binco
		{207.5219,-109.7448,1005.1328,345.0,
		2245.0981,-1662.6085,15.4690,345.0},
		// Sub Urban
		{203.8984,-47.6728,1001.8047,0.0,
		2112.7329,-1214.6234,23.9675,180.0},	
		// Zip
		{161.30,-94.04,1001.80,360.0,
		1458.6636,-1140.1521,24.0687,220.0},	
		// Victim
		{223.6943,-8.0969,1002.2109,90.0,
		458.5868,-1501.5376,31.0369,100.0},	
		// Didier Sachs
		{204.4170,-166.3974,1000.5234,360.0,
		451.3058,-1479.1121,30.8126,111.0},	
		// Pro Laps
		{206.9911,-137.5289,1003.0938,360.0,
		500.7222,-1357.4952,16.1328,340.0},	
        // Barbershop Dillimore
        {418.5297,-81.4262,1001.8047,0.0,
        675.3163,-497.0128,16.3359,270.0},
        // Blueberry Pizza Stack
        {372.4435,-130.8061,1001.4922,0.0000,
        203.3997,-205.7403,1.5781,180.0},
        // Montgomery Pizza Stack
        {372.4435,-130.8061,1001.4922,0.0000,
        1365.0647,249.4230,19.5669,66.0},
        // Palomino Creek Pizza Stack
        {372.4435,-130.8061,1001.4922,0.0000,
        2335.2083,75.0771,26.4830,270.0},
        // Ammunation Blueberry
        {285.4748,-38.7987,1001.5156,360.0,
        240.0002,-178.2550,1.5781,90.0}, 
        // Ammunation Palomino Creek
        {285.4748,-38.7987,1001.5156,360.0,
        2335.8137,61.6884,26.4821,270.0}, 
        // Ammunation Angel Pine
        {285.4748,-38.7987,1001.5156,360.0,
        -2091.7942,-2462.7478,30.6250,319.0}, 
        // 24/7 Whetstone
        {-26.2114,-139.1527,1003.5469,0.0,
        -1559.9265,-2734.9338,48.7435,234.0},
        // Cluckin Bell Angel Pine
        {366.0002,-9.4338,1001.8516,360.0,
        -2152.9758,-2461.8120,30.8516,229.0},
        // Cluckin Bell Emerald Isle
        {366.0002,-9.4338,1001.8516,360.0,
        2104.6570,2229.0217,11.0234,270.0},
        // Cluckin Bell Fort Carson
        {366.0002,-9.4338,1001.8516,360.0,
        171.0602,1174.5070,14.7578,143.0},
        // 24/7 Fort Carson
        {-26.2114,-139.1527,1003.5469,0.0,
        -99.3013,1085.6095,19.7422,0.0},
        // Bar Fort Carson
        {502.0477,-70.6021,998.7578,180.0,
        -181.8702,1089.4631,19.7422,47.0},
        // Ammunation Fort Carson
        {285.4748,-38.7987,1001.5156,360.0,
        -313.5447,829.8996,14.2422,270.0}, 
        // Ammunation El Quebrados   
        {296.8887,-109.2648,1001.5156,360.0,
        -1508.9193,2607.9033,55.8359,177.6},      
        // Ammunation Bone County 
        {296.8887,-109.2648,1001.5156,360.0,
        779.3183,1871.3215,4.9061,270.0},    
        // Binco Las Venturas
        {207.5219,-109.7448,1005.1328,345.0,
        1653.8604,1733.2893,10.8203,90.0},
        // Binco Emeral Isle
        {207.5219,-109.7448,1005.1328,345.0,
        2104.4543,2257.4514,11.0234,270.0},
        // Barbershop Redsands East
        {411.6730,-20.4541,1001.8047,360.0,
        2080.0229,2120.1218,10.8125,180.0},
        // Tattoo Parlor Redsands East
        {-204.1540,-41.9165,1002.2734,0.0,
        2094.8835,2119.9104,10.8203,180.0},
        // Zip Emerald Isle
        {161.30,-94.04,1001.80,360.0,
        2090.6829,2222.5771,10.8203,180.0},
        // 24/7 Redsands East
        {-30.9875,-89.6806,1003.5469,360.0000,
        1934.8257,2307.1445,10.8203,90.0},
        // 24/7 Emerald Isle
        {-30.9875,-89.6806,1003.5469,360.0000,
        2097.7368,2222.2161,10.8203,180.0},
        // 24/7 Starfish Casino
        {-27.3447,-55.8258,1003.5469,0.0,
        2192.8674,1990.9613,12.2969,90.0},
        // 24/7 Roca Escalante
        {-27.3447,-55.8258,1003.5469,0.0,
        2247.7351,2398.8137,10.8203,360.0},
        // Burger Whitewood
        {366.0545,-73.3270,1001.5078,318.7592,
        1160.7927,2072.2031,11.0625,270.0},
        // Burger Redsands East
        {366.0545,-73.3270,1001.5078,318.7592,
        1875.6401,2071.8569,11.0625,270.0},
        // Burger Spiny Bed
        {366.0545,-73.3270,1001.5078,318.7592,
        2172.0879,2795.7927,10.8203,270.0},
        // Roca Escalante Pizza Stack
        {372.4435,-130.8061,1001.4922,0.0000,
        2351.8823,2530.7058,10.8203,180.0},
        // Emerald Isle Pizza Stack
        {372.4435,-130.8061,1001.4922,0.0000,
        2083.3438,2222.4377,10.8203,180.0},
        // Pilgrim Pizza Stack
        {372.4435,-130.8061,1001.4922,0.0000,
        2632.5085,1849.9186,10.8203,90.0},
        // Creek Pizza Stack
        {372.4435,-130.8061,1001.4922,0.0000,
        2756.4963,2473.7473,11.0625,137.0238},
        // Burger Old Venturas Strip
        {366.0545,-73.3270,1001.5078,318.7592,
        2470.3704,2034.1469,11.0625,90.0},
        // 24/7 Old Venturas Strip
        {-26.2114,-139.1527,1003.5469,0.0,
        2452.67, 2061.62, 10.82 ,360.0},
        // 24/7 Starfish Casino
        {-26.2114,-139.1527,1003.5469,0.0,
        2546.7146,1970.0492,10.8203,185.0},
        // 24/7 Creek
        {-26.2114,-139.1527,1003.5469,0.0,
        2887.3462,2452.4102,11.0690,224.0},
        // Ammunation Old Venturas Strip 
        {296.8887,-109.2648,1001.5156,360.0,
        2536.8606,2083.8171,10.8203,90.0},  
        // Ammunation Come-A-Lot
        {296.8887,-109.2648,1001.5156,360.0,
        2155.5649,943.1818,10.8203,90.0},  
        // Ammunation Ocean Flats
        {285.4748,-38.7987,1001.5156,360.0,
        -2626.8440,210.7694,4.5921,0.0}, 
        // Pier 69 Pizza Stack
        {372.4435,-130.8061,1001.4922,0.0000,
        -1724.0063,1359.4421,7.1875,90.0},
        // Financial Pizza Stack
        {372.4435,-130.8061,1001.4922,0.0000,
        -1807.0627,944.2289,24.8906,225.0},
        // Cluckin Bell Old Venturas Strip
        {366.0002,-9.4338,1001.8516,360.0,
        2393.1670,2045.6594,10.8203,0.0},
        // Cluckin Bell Piligrim
        {366.0002,-9.4338,1001.8516,360.0,
        2635.8738,1671.8846,11.0234,90.0},
        // Cluckin Bell Creek
        {366.0002,-9.4338,1001.8516,360.0,
        2840.8062,2406.1675,11.0690,227.0},
        // Cluckin Bell Downtown
        {366.0002,-9.4338,1001.8516,360.0,
        -1816.4703,615.8589,35.1719,180.0},
        // Cluckin Bell City Hall SF
        {366.0002,-9.4338,1001.8516,360.0,
        -2672.1792,262.9997,4.6328,0.0},
        // Burger Downtown
        {366.0545,-73.3270,1001.5078,318.7592,
        -1910.4961,830.1155,35.1719,319.0},
        // Burger Juniper Hollow
        {366.0545,-73.3270,1001.5078,318.7592,
        -2358.4924,1007.8475,50.7698,90.0},
        // Burger Garcia
        {366.0545,-73.3270,1001.5078,318.7592,
        -2333.5161,-166.7397,35.5547,270.0},
        // Bar Old Venturas Strip
        {502.0477,-70.6021,998.7578,180.0,
        2440.9219,2062.6204,10.8203,180.0},
        // Bar Garcia
        {502.0477,-70.6021,998.7578,180.0,
        -2244.9670,-88.4304,35.3203,90.0},
        // Barbershop Queens
        {418.5297,-81.4262,1001.8047,0.0,
        -2569.4565,244.7343,10.2118,223.0},
        // Tattoo Parlor Hushberry
        {-204.1540,-41.9165,1002.2734,0.0,
        -2493.7097,-39.0030,25.7656,90.0},
        // Zip Piligrim
        {161.30,-94.04,1001.80,360.0,
        2572.1128,1901.5944,11.0234,180.0},
        // Zip Downtown
        {161.30,-94.04,1001.80,360.0,
        -1884.2562,864.4302,35.1719,136.0},
        // Binco Juniper Hill
        {207.5219,-109.7448,1005.1328,345.0,
        -2376.5806,910.0474,45.4453,90.0},
        // Pro Laps Creek
        {206.9911,-137.5289,1003.0938,360.0,
        2824.7498,2404.8970,11.0625,141.0}, 
        // Sub Urban Creek
        {203.8984,-47.6728,1001.8047,0.0,
        2778.3723,2451.5261,11.0625,138.0},
        // Sub Urban Hashbury
        {203.8984,-47.6728,1001.8047,0.0,
        -2493.1882,-29.0187,25.7656,90.0},
        // Victim Creek
        {223.6943,-8.0969,1002.2109,90.0,
        2801.6892,2428.2341,11.0625,131.0}, 
        // Victim Financial
        {223.6943,-8.0969,1002.2109,90.0,
        -1696.2939,949.9283,24.8906,138.0}, 
    //};
         //* Common pickups starts here *//
        // Pleasure Domes
        {-2636.7146,1405.5967,906.4609,0.0,
        -2623.9495,1410.0289,7.0938,190.0},    
        // Ganton Gym
        {770.9346,-1.1705,1000.7276,30.0,
        2227.5342,-1723.5419,13.5521,130.0},
        // Cobra Gym
        {774.0788,-48.1101,1000.5859,0.0,
        -2267.9673,-155.9535,35.3203,270.0},
        // LV Gym
        {773.9128,-76.4009,1000.6544,360.0,
        1967.3403,2294.7722,16.4559,90.0},
        // Hospital LS
        {1124.4630,-1319.4034,1788.9583,270.0,
        1176.4637,-1323.3270,14.0226,270.0},
        // Hospital SF
        {1124.4630,-1319.4034,1788.9583,270.0,
        -2655.0740,637.0269,14.4531,180.0},
        // Hospital LV
        {1124.4630,-1319.4034,1788.9583,270.0,
        1607.3958,1818.3477,10.8203,360.0},
        // San News
        {1175.3049,-1187.2043,87.0787,0.0,
        1653.6193,-1658.3634,22.5156,180.0},
        // Church LS
        {386.1117,2324.3118,1889.5669,90.0,
        1720.3527,-1738.5055,13.5469,0.0},
        // Church SF
        {386.1117,2324.3118,1889.5669,90.0,
        -1986.7612,1117.8251,53.9808,270.0},
        // Church LV
        {386.1117,2324.3118,1889.5669,90.0,
        2522.8987,918.5251,10.8203,270.0},
        // Driving School
        {-2028.1647,-105.0986,1035.1719,120.0,
        -2026.5680,-100.0698,35.1641,0.0},
        // Trucker Office
        {214.2948,1754.4468,3000.8308,360.0,
        -50.0768,-274.3593,5.4297,180.0}        

};
new
    Properties[MAX_DOOR][Properties__] = {
    	
        // 24/7 El Corona
        {16, 52, -1, "24/7 El Corona", COST_247SHOP},
        // 24/7 Idlewood
        {6, 52, -1, "24/7 Idlewood", COST_247SHOP},
        // 24/7 Willowfield
        {6, 52, -1, "24/7 Willowfield", COST_247SHOP},
        // 24/7 Ganton
        {6, 52, -1, "24/7 Ganton", COST_247SHOP},
        // 24/7 Commerce
        {18, 52, -1, "24/7 Commerce", COST_247SHOP},
        // 24/7 Market
        {6, 52, -1, "24/7 Market", COST_247SHOP},
        // 24/7 Commerce 2
        {16, 52, -1, "24/7 Commerce #2", COST_247SHOP},
        // 24/7 Idlewood 2
        {16, 52, -1, "24/7 Idlewood #2", COST_247SHOP},
        // 24/7 East
        {16, 52, -1, "24/7 East", COST_247SHOP},
        // 24/7 East 2
        {16, 52, -1, "24/7 East #2", COST_247SHOP},
        // 24/7 Market 2
        {16, 52, -1, "24/7 Market #2", COST_247SHOP},
        // 24/7 Mulholland
        {18, 52, -1, "24/7 Mulholland", COST_247SHOP},
        // 24/7 Mulholland 2
        {18, 52, -1, "24/7 Mulholland #2", COST_247SHOP},
        // 24/7 Las Colinas
        {18, 52, -1, "24/7 Las Colinas", COST_247SHOP},
        // Idlewood Pizza
        {5, 29, -1, "Idlewood Pizza", COST_RESTRAUNT},
        // Cluckin Bell Willowfield
        {9, 14, -1, "Cluckin Bell Willowfield", COST_RESTRAUNT},
        // Cluckin Bell East
        {9, 14, -1, "Cluckin Bell East", COST_RESTRAUNT},
        // Cluckin Bell Market
        {9, 14, -1, "Cluckin Bell Market", COST_RESTRAUNT},
        // Burger Shot Marina
        {10, 10, -1, "Burger Shot Marina", COST_RESTRAUNT},
        // Burger Shot Mulholland
        {10, 10, -1, "Burger Shot Mulholland", COST_RESTRAUNT},
        // Tattoo Parlor Idlewood
        {3, 39, -1, "Tattoo Parlor Idlewood", COST_TATTOO},
        // Tattoo Parlor El Corona
        {3, 39, -1, "Tattoo Parlor El Corona", COST_TATTOO},
        // Barbershop Idlewood
        {3, 7, -1, "Barbershop Idlewood", COST_BARBER},
        // Barbershop Playa Del Sevile
        {2, 7, -1, "Barbershop Playa Del Sevile", COST_BARBER},
        // Barbershop Marina
        {2, 7, -1, "Barbershop Marina", COST_BARBER},
        // Club Alhambra
        {17, 48, -1, "Club Alhambra", COST_CLUB},
        // Strip Club Pig Pen
        {2, 48, -1, "Strip Club Pig Pen", COST_CLUB},
        // Bar 10 Green Bottles 
        {11, 49, -1, "Bar 10 Green Bottles", COST_BAR},
        // Bar Atlantic
        {11, 49, -1, "Bar Atlantic", COST_BAR},
        // Bar El Corona
        {11, 49, -1, "Bar El Corona", COST_BAR},
        // Ammunation
        {1, 6, -1, "Ammunation", COST_AMMUNATION},
        // Ammunation Willowfield
        {6, 6, -1, "Ammunation Willowfield", COST_AMMUNATION},
        // Binco
        {15, 45, -1, "Binco", COST_CLOTHES},
        // Sub Urban
        {1, 45, -1, "Sub Urban", COST_CLOTHES},
        // Zip
        {18, 45, -1, "Zip", COST_CLOTHES},
        // Victim
        {5, 45, -1, "Victim", COST_CLOTHES},
        // Didier Sachs
        {14, 45, -1, "Didier Sachs", COST_CLOTHES},
        // Pro Laps
        {3, 45, -1, "Pro Laps", COST_CLOTHES},
        // Barbershop Dillimore
        {3, 7, -1, "Barbershop Dillimore", COST_BARBER},
        // Blueberry Pizza Stack
        {5, 29, -1, "Blueberry Pizza", COST_RESTRAUNT},
        // Montgomery Pizza Stack
        {5, 29, -1, "Montgomery Pizza", COST_RESTRAUNT},
        // Palomino Creek Pizza Stack
        {5, 29, -1, "Palomino Creek Pizza", COST_RESTRAUNT},
        // Ammunation Blueberry
        {1, 6, -1, "Ammunation Blueberry", COST_AMMUNATION},
        // Ammunation Palomino Creek
        {1, 6, -1, "Ammunation Palomino Creek", COST_AMMUNATION},
        // Ammunation Angel Pine
        {1, 6, -1, "Ammunation Angel Pine", COST_AMMUNATION},
        // 24/7 Whetstone
        {16, 52, -1, "24/7 Whetstone", COST_247SHOP},
        // Cluckin Bell Angel Pine
        {9, 14, -1, "Cluckin Bell Angel Pine", COST_RESTRAUNT},
        // Cluckin Bell Emerald Isle
        {9, 14, -1, "Cluckin Bell Emerald Isle", COST_RESTRAUNT},
        // Cluckin Bell Fort Carson
        {9, 14, -1, "Cluckin Bell Fort Carson", COST_RESTRAUNT},  
        // 24/7 Fort Carson
        {16, 52, -1, "24/7 Fort Carson", COST_247SHOP},     
        // Bar Fort Carson
        {11, 49, -1, "Bar Fort Carson", COST_BAR}, 
        // Ammunation Fort Carson
        {1, 6, -1, "Ammunation Fort Carson", COST_AMMUNATION},
        // Ammunation El Quebrados
        {6, 6, -1, "Ammunation El Quebrados", COST_AMMUNATION},
        // Ammunation Bone County
        {6, 6, -1, "Ammunation Bone County", COST_AMMUNATION},
        // Binco Las Venturas
        {15, 45, -1, "Binco Las Venturas", COST_CLOTHES},
        // Binco Emerald Isle
        {15, 45, -1, "Binco Emerald Isle", COST_CLOTHES},
        // Barbershop Redsands East
        {2, 7, -1, "Barbershop Redsands East", COST_BARBER},
        // Tattoo Parlor Redsands East
        {3, 39, -1, "Tattoo Parlor Redsands East", COST_TATTOO},
        // Zip Emerald Isle
        {18, 45, -1, "Zip Emerald Isle", COST_247SHOP},
        // 24/7 Redsands East
        {18, 52, -1, "24/7 Redsands East", COST_247SHOP},
        // 24/7 Emerald Isle
        {18, 52, -1, "24/7 Emerald Isle", COST_247SHOP},
        // 24/7  Starfish Casino
        {6, 52, -1, "24/7 Starfish Casino", COST_247SHOP},
        // 24/7  Roca Escalante
        {6, 52, -1, "24/7 Roca Escalante", COST_247SHOP},
        // Burger Whitewood
        {10, 10, -1, "Burger Shot Whitewood", COST_RESTRAUNT},
        // Burger  Redsands East
        {10, 10, -1, "Burger Shot Redsands East", COST_RESTRAUNT},
        // Burger Spiny Bed
        {10, 10, -1, "Burger Shot Spiny Bed", COST_RESTRAUNT},
        // Roca Escalante Pizza
        {5, 29, -1, "Roca Escalante Pizza", COST_RESTRAUNT},
        // Emerald Isle Pizza
        {5, 29, -1, "Emerald Isle Pizza", COST_RESTRAUNT},
        // Pilgrim Pizza
        {5, 29, -1, "Pilgrim Pizza", COST_RESTRAUNT},
        // Creek Pizza
        {5, 29, -1, "Creek Pizza", COST_RESTRAUNT},
        // Burger Old Venturas Strip
        {10, 10, -1, "Burger Shot Old Venturas Strip", COST_RESTRAUNT},
        // 24/7 Old Venturas Strip
        {16, 52, -1, "24/7 Old Venturas Strip", COST_247SHOP},
        // 24/7 Starfish Casino
        {16, 52, -1, "24/7 Starfish Casino", COST_247SHOP},
        // 24/7 Creek
        {16, 52, -1, "24/7 Creek", COST_247SHOP},
        // Ammunation Old Venturas Strip
        {6, 6, -1, "Ammunation Old Venturas Strip", COST_AMMUNATION},
        // Ammunation Old Venturas Strip
        {6, 6, -1, "Ammunation Come-A-Lot", COST_AMMUNATION},
        // Ammunation Ocean Flats
        {1, 6, -1, "Ammunation Ocean Flats", COST_AMMUNATION},
        // Pier 69 Pizza
        {5, 29, -1, "Pier 69 Pizza", COST_RESTRAUNT},
        // Financial Pizza
        {5, 29, -1, "Financial Pizza", COST_RESTRAUNT},
        // Cluckin Bell Old Venturas Strip
        {9, 14, -1, "Cluckin Bell Old Venturas Strip", COST_RESTRAUNT},
        // Cluckin Bell Piligrim
        {9, 14, -1, "Cluckin Bell Piligrim", COST_RESTRAUNT},
        // Cluckin Bell Creek
        {9, 14, -1, "Cluckin Bell Creek", COST_RESTRAUNT},
        // Cluckin Bell Downtown
        {9, 14, -1, "Cluckin Bell Downtown", COST_RESTRAUNT},
        // Cluckin Bell City Hall SF
        {9, 14, -1, "Cluckin Bell City Hall SF", COST_RESTRAUNT},
        // Burger Downtown
        {10, 10, -1, "Burger Shot Downtown", COST_RESTRAUNT},
        // Burger Juniper Hollow
        {10, 10, -1, "Burger Shot Juniper Hollow", COST_RESTRAUNT},
        // Burger Garcia
        {10, 10, -1, "Burger Shot Garcia", COST_RESTRAUNT},
        // Bar Old Venturas Strip
        {11, 49, -1, "Bar Old Venturas Strip", COST_BAR}, 
        // Bar Garcia
        {11, 49, -1, "Bar Garcia", COST_BAR}, 
        // Barbershop Queens
        {3, 7, -1, "Barbershop Queens", COST_BARBER},
        // Tattoo Parlor Hushberry
        {3, 39, -1, "Tattoo Parlor Hushberry", COST_TATTOO},
        // Zip Piligrim
        {18, 45, -1, "Zip Piligrim", COST_CLOTHES},
        // Zip Downtown
        {18, 45, -1, "Zip Downtown", COST_CLOTHES},
        // Binco  Juniper Hill
        {15, 45, -1, "Binco  Juniper Hill", COST_CLOTHES},
        // Pro Laps Creek
        {3, 45, -1, "Pro Laps Creek", COST_CLOTHES},
        // Sub Urban Creek
        {1, 45, -1, "Sub Urban Creek", COST_CLOTHES},
        // Sub Urban Hashbury
        {1, 45, -1, "Sub Urban Hashbury", COST_CLOTHES},
        // Victim Creek
        {5, 45, -1, "Victim Creek", COST_CLOTHES},
        // Victim Financial
        {5, 45, -1, "Victim Financial", COST_CLOTHES},

//};

        //* Common pickups starts here *//

        // Pleasure Domes
        {3, 23, -1, "Pleasure Domes", -1},   
        // Ganton Gym
        {5, 54, -1, "Ganton Gym", -1},
        // Cobra Gym
        {6, 54, -1, "Cobra Gym", -1},
        // Cobra Gym
        {7, 54, -1, "LV Gym", -1},
        // Hospital LS
        {1, 22, 1, "Hospital LS", -1},
        // Hospital SF
        {1, 22, 1, "Hospital SF", -1},
        // Hospital LV
        {1, 22, 1, "Hospital LV", -1},
        // San News
        {0, 38, 2, "San News", -1},
        // Church LS
        {1, 12, 1, "Church", -1},
        // Church SF
        {1, 12, 1, "Church", -1},
        // Church LV
        {1, 12, 1, "Church", -1}, 
        // Driving School
        {1, 36, 1, "Driving School", -1},
        // Driving School
        {1, 51, 1, "Trucker Office", -1}       

};

forward LoadEntrance();
public LoadEntrance() {
    for(new i = 0; i < MAX_DOOR; i++) {

        // Map Icon (if defined)
        if(Properties[i][Icon] != INVALID_ICON_ID) {
            CreateDynamicMapIcon(Pickup[i][ent_X],
                Pickup[i][ent_Y],
                Pickup[i][ent_Z],
                Properties[i][Icon], -1, 0, -1,
                -1, ICON_VIEW_DISTANCE);
        }
        // Enterance (Pickup)
        Door_Pickup[i][ENTERANCE] = CreateDynamicPickup(Pickup[i][Model],
            DOOR_PICKUP_TYPE,
            Pickup[i][ent_X],
            Pickup[i][ent_Y],
            Pickup[i][ent_Z],
            0,
            -1,
            -1,
            DOOR_STREAM_DISTANCE);
        // Exit (Pickup)
        Door_Pickup[i][EXIT] = CreateDynamicPickup(Pickup[i][Model2],
            DOOR_PICKUP_TYPE,
            Pickup[i][ent_X2],
            Pickup[i][ent_Y2],
            Pickup[i][ent_Z2],
            DOOR_VW_ADDENDUM+i,
            -1,
            -1,
            DOOR_STREAM_DISTANCE);
        // Enterance (Area)
        Door_Area[i][ENTERANCE] = CreateDynamicCylinder(Pickup[i][ent_X],
            Pickup[i][ent_Y],
            Pickup[i][ent_Z]-0.2,
            Pickup[i][ent_Z]+0.2,
            AREA_SIZE,
            0,
            -1);
        // Exit (Area)
        Door_Area[i][EXIT] = CreateDynamicCylinder(Pickup[i][ent_X2],
            Pickup[i][ent_Y2],
            Pickup[i][ent_Z2]-0.2,
            Pickup[i][ent_Z2]+0.2,
            AREA_SIZE,
            DOOR_VW_ADDENDUM+i,
            -1);
    }
}
forward Entrances(playerid, areaid);
public Entrances(playerid, areaid) {
	if(IsPlayerInAnyVehicle(playerid)) return 1;
	new 
		door = -1;

	ClearPlayerAnimation(playerid);

	for(new i = 0; i < MAX_DOOR; i++) {
			if(areaid == Door_Area[i][ENTERANCE]) {	

                SetPVarInt(playerid, "Extra", Properties[i][Extra]);
				SetPlayerPos(playerid, Pickup[i][ent_X],
				Pickup[i][ent_Y],
				Pickup[i][ent_Z]);
				SetPlayerFacingAngle(playerid, EnterCoords[i][ent_A2]-180);
				door = i;
				break;
			} else {
			if(areaid == Door_Area[i][EXIT]) {

                SetPVarInt(playerid, "Extra", Properties[i][Extra]);
				SetPlayerPos(playerid, Pickup[i][ent_X2],
				Pickup[i][ent_Y2],
				Pickup[i][ent_Z2]);
				SetPlayerFacingAngle(playerid, EnterCoords[i][ent_A]-180);	
				door = i;
				break;
			}
		}
	}
	if(door == -1) return 1;
    ApplyAnimation(playerid, "ped", "Walk_DoorPartial", 4.0, 0, 1, 1, 1, 1, 1); 
	//PlayerPlaySound(playerid, 14407, 0, 0, 0);
	SetPVarInt(playerid, "Door", door);
	return entrance_timer[playerid] = SetTimerEx("Enterance", 800, false, "i", playerid);
}

forward Enterance(playerid);
public Enterance(playerid) {

    entrance_timer[playerid] = KillTimer(entrance_timer[playerid]);

	new 
		door = GetPVarInt(playerid, "Door");

	if(GetPlayerVirtualWorld(playerid) == 0) {
        
		SetPlayerPos(playerid,
			EnterCoords[door][ent_X],
			EnterCoords[door][ent_Y],
			EnterCoords[door][ent_Z]);
		SetPlayerFacingAngle(playerid, EnterCoords[door][ent_A]);
		SetCameraBehindPlayer(playerid);
		SetPlayerVirtualWorld(playerid, DOOR_VW_ADDENDUM+door);
        GameTextForPlayer(playerid, Properties[door][IName], 1000, 1);
        ExtraInt(playerid, GetPVarInt(playerid, "Extra"), 0);
	} else {
        if(GetPVarInt(playerid, "robbing_now") == 1) {
            RobTimer[playerid] = KillTimer(RobTimer[playerid]);
            DeletePVar(playerid, "MinusTime");
            new mate = GetPVarInt(playerid, "mate");
            if(mate != -1) {
                RobTimer[mate] = KillTimer(RobTimer[mate]);
                DeletePVar(playerid, "MinusTime");
            }
        }
		SetPlayerPos(playerid,
			EnterCoords[door][ent_X2],
			EnterCoords[door][ent_Y2],
			EnterCoords[door][ent_Z2]);
		SetPlayerFacingAngle(playerid, EnterCoords[door][ent_A2]);
		SetCameraBehindPlayer(playerid);		
		SetPlayerVirtualWorld(playerid, 0);
        ExtraInt(playerid, GetPVarInt(playerid, "Extra"), 1);
	}

    // SetPlayerScreenColour(playerid, 0x000000FF);
    // FadePlayerScreenColour(playerid, 0x00000000, GetPlayerPing(playerid)+2000, 25);    

	if(GetPlayerInterior(playerid) == 0) {
		SetPlayerInterior(playerid, Properties[door][IID]);
	} else SetPlayerInterior(playerid, 0);
	ClearPlayerAnimation(playerid);

}

stock ExtraInt(playerid, extra_id = -1, io = -1) {

    // 0 = Enter
    // 1 = Exit

    switch(extra_id) {
        case 1: {
            if(io == 0) PlayerPlaySound(playerid, 1,  0.0, 0.0, 0.0);
            if(io == 1) PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
        }
        case 2: {

            if(io == 0) {
                SetPVarInt(playerid, "permanent_day", 1); 
                SetPlayerTime(playerid, 12, 0);
                SetPlayerWeather(playerid, 1);
            }
            if(io == 1) {
                DeletePVar(playerid, "permanent_day");
            }
        }
        default: return 1;
    }

    return 1;
}


stock PickupReturn(pickupid) {
    for(new i = 0; i < MAX_DOOR; i++) {
        if(pickupid == Door_Pickup[i][ENTERANCE]) {
            return 0;
        }
    }
    return 1;
}