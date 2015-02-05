#include "VehicleManager.h"
#include "Constants.h"
#include "sampgdk.h"

using namespace std;

unordered_map<int, bool> VehicleManager::vehicleWindowMap;

void VehicleManager::CreateStartingVehicles()
{
	// DO NOT ADD OR DELETE ANY VEHICLES FROM THIS LIST OR SHIT WILL BE MESSED UP
	CreateVehicle(420, -288.4164, 1326.5234, 54.2781, 84.3199, 6, 6, 600);   										// taxi 1										1
	CreateVehicle(420, -289.4044, 1321.7631, 54.1691, 80.3716, 6, 6, 600);   										// taxi 2										2
	CreateVehicle(420, -289.9427, 1317.2841, 54.0669, 81.6238, 6, 6, 600);   										// taxi 3										3
	CreateVehicle(438, -290.2812, 1312.6821, 54.1862, 83.0581, 6, 6, 600);   										// taxi 4										4
	CreateVehicle(438, -291.1954, 1308.2550, 54.0653, 82.0800, 6, 6, 600);   										// taxi 5										5
	CreateVehicle(438, -291.4790, 1303.5994, 53.9459, 80.7033, 6, 6, 600);  										// taxi 7										6
	CreateVehicle(409, -293.1763, 1294.5857, 53.4653, 82.9199, 6, 3, 600);  										// taxi limo 									7
	CreateVehicle(437, -293.4763, 1298.9156, 53.8723, 81.9176, 6, 6, 600);  										// taxi bus spawn?!								8
	CreateVehicle(487, -314.0985, 1300.4412, 57.8522, 0.9464, 6, 6, 600);   										// taxi 9										9
	CreateVehicle(488, -328.6183, 1299.9198, 57.8937, 0.6170, 6, 6, 600);											// taxi 10										10				

	CreateVehicle(416, -304.3722, 1036.1498, 19.7430, 270.5433, 1, 3, 600); 										// ambulance 1 									11
	CreateVehicle(416, -304.6205, 1027.9274, 19.7429, 268.3362, 1, 3, 600); 										// ambulance 2									12
	CreateVehicle(563, -333.1461, 1049.5354, 26.7179, 180.5284, 1, 3, 600); 										// ambulance 3 (raindance heli)					13
	CreateVehicle(574, -334.3937, 1054.0668, 19.4461, 89.5358, 1, 1, 600); 											// ambulance 4 SWEEPER							14
	CreateVehicle(490, -334.1899, 1057.7920, 19.4459, 90.5261, 1, 3, 600);											// ambulance 5 FBI rancher						15

	CreateVehicle(497, 115.8316, 1848.6610, 17.8459, 271.0461, 40, 99, 600); 										// sheriff copter (pd maverick)					16
	CreateVehicle(497, 116.3933, 1829.7737, 17.8181, 270.9591, 40, 99, 600); 										// sheriff copter (pd maverick)					17
	CreateVehicle(599, 220.7241, 1919.7936, 17.8336, 180.2442, 40, 99, 600); 										// sheriff rancher  1							18
	CreateVehicle(599, 211.2945, 1919.7894, 17.8288, 179.8691, 40, 99, 600); 										// sheriff rancher  2							19
	CreateVehicle(490, 202.4457, 1919.8571, 17.8294, 180.5494, 104, 104, 600); 										// sheriff Govt SUV 3							20
	CreateVehicle(490, 193.1125, 1919.8390, 17.8297, 180.4179, 104, 104, 600); 										// sheriff Govt SUV 4							21
	CreateVehicle(596, 205.6600, 1879.6151, 17.3633, 183.5843, 40, 99, 600); 										// Sheriff_Cruiser1								22
	CreateVehicle(596, 198.0816, 1879.7616, 17.3874, 180.4415, 40, 99, 600); 										// Sheriff_Cruiser2								23
	CreateVehicle(598, 197.7442, 1887.6178, 17.3990, 179.8884, 40, 99, 600); 										// Sheriff_Cruiser3								24
	CreateVehicle(598, 204.8797, 1887.9371, 17.3772, 184.3681, 40, 99, 600); 										// Sheriff_Cruiser4								25
	CreateVehicle(598, -210.7367, 998.8789, 19.3923, 270.3328, 40, 99, 600);  										// FC_SheriffCar1								26
	CreateVehicle(599, -227.0876, 991.3741, 19.7149, 270.3195, 40, 99, 600); 										// FC_SheriffRanger1							27
	CreateVehicle(599, -1400.0750, 2631.6545, 55.9492, 271.0319, 40, 99, 600);										// EQ_SheriffRanger1							28
	CreateVehicle(596, -1400.0161, 2640.8328, 55.4340, 270.2352, 40, 99, 600);										// EQ_SheriffCruiser1							29
	CreateVehicle(598, -1400.0427, 2647.1179, 55.4326, 270.3821, 40, 99, 600);										// EQ_SheriffCruiser2							30
	CreateVehicle(598, 213.6640, 1854.7410, 12.6844, 1.7016, 0, 0, 600);  											// sheriff cruiser 5							31
	CreateVehicle(598, 221.5693, 1855.6372, 12.6830, 1.6758, 0, 0, 600);  											// sheriff cruiser 6							32
	CreateVehicle(601, 205.4735, 1872.1101, 12.9044, 269.3260, 1, 1, 600);  										// PD mr. splashy								33
	CreateVehicle(447, 116.4210, 1839.1362, 17.6523, 272.0304, 0, 0, 600);											// PD seasparrow								34

	CreateVehicle(406, 837.1599, 870.9524, 14.7574, 201.2985, 1, 1, 600);  											// DumperJtruck1								35
	CreateVehicle(406, 845.8845, 874.4843, 14.8791, 203.7575, 1, 1, 600);  											// DumperJtruck2								36

	CreateVehicle(519, 404.4342, 2457.4900, 17.4225, 2.4802, 1, 1, 600);  											// shamal (interior tagged)						37
	CreateVehicle(484, 766.6008, 3749.5850, 0.5233, 70.7478, 181, 181, 600);  										// Admin marquis spawn							38
	CreateVehicle(571, -1703.8419, 1024.3992, 17.2909, 90.7771, 3, 3, 600);  										// nsa car 1 (NOW A KART)						39
	CreateVehicle(571, -1702.9675, 1012.0355, 17.2911, 90.0717, 3, 3, 600);  										// nsa car 2 (NOW A KART)						40
	CreateVehicle(571, -1687.4141, 1003.6402, 17.2907, 89.3311, 3, 3, 600);  										// nsa car 3 (NOW A KART)						41

	CreateVehicle(512, -67.2798, 66.9923, 3.3995, 70.6457, 3, 3, 45);  												// Cropdust Spawn 1								42
	CreateVehicle(512, -75.5594, 69.8315, 3.3991, 70.3844, 81, 81, 45); 											// Cropdust Spawn 2								43

	//  ----------- gang spawns ----------
	CreateVehicle(567, -812.5565, 1569.9752, 26.9068, 358.9483, 93, 93, 600);  										// Cholos Carspawn - Savannah in front of club	44

	CreateVehicle(405, -678.5847, 964.6965, 12.0103, 89.5141, 1, 1, 600);  											// KE sentinel 1 These need headings			45
	CreateVehicle(409, -677.7396, 968.1816, 11.9320, 88.0227, 1, 1, 600);  											// KE limo										46
	CreateVehicle(581, -688.6674, 961.2050, 11.7586, 38.9055, 0, 0, 600);  											// KE_BFSpawn1									47
	CreateVehicle(581, -686.6024, 961.2591, 11.7330, 38.8758, 0, 0, 600);											// KE_BFSpawn2									48

	CreateVehicle(421, 649.5987, 1289.6311, 11.6012, 29, 16, 16, 600);                                             // FBC Washington                               49
	CreateVehicle(554, 644.4683, 1286.8103, 11.8102, 29, 16, 1, 600);                                              // FBC Yosemite                                 50
	CreateVehicle(524, 638.6245, 1284.3319, 12.6462, 209, 1, 16, 600);                                             // FBC Cement Truck                             51
	CreateVehicle(498, 642.9442, 1239.0673, 11.7313, 300, 1, 16, 600);                                             // FBC Boxville                                 52
	CreateVehicle(552, 589.8052, 1226.9822, 11.4173, 209, 1, 16, 600);                                             // FBC Utility                                  53
	CreateVehicle(552, 584.2873, 1223.8284, 11.4097, 209, 1, 16, 600);                                             // FBC Utility 2                                54

	CreateVehicle(463, -167.6570, 1085.3134, 19.2826, 54.5490, 1, 1, 600);  										// Mojave freeway 1								55
	CreateVehicle(463, -167.6692, 1083.9641, 19.2828, 67.5702, 1, 1, 600);  										// Mojave freeway 2								56
	CreateVehicle(463, -167.6406, 1082.4679, 19.2822, 70.1010, 1, 1, 600);  										// Mojave freeway 3								57

	CreateVehicle(581, -237.8767, 2595.9121, 62.2998, 356.7420, 0, 0, 600); 										// Deserted Disciples BF400, #1					58
	CreateVehicle(581, -234.8114, 2595.9534, 62.2987, 359.5977, 0, 0, 600); 										// Deserted Disciples BF400, #2					59
	CreateVehicle(581, -231.7729, 2595.6414, 62.2999, 359.0515, 169, 169, 600); 									// Deserted Disciples BF400, #3					60

	CreateVehicle(603, 796.8129, 1683.8650, 5.1193, 122.6313, 3, 1, 600);  											// WRC Pheonix									
	CreateVehicle(400, 809.5474, 1677.9774, 5.3737, 0.1679, 3, 3, 600);  											// WRC landstalker								
	CreateVehicle(532, 780.2725, 1695.9948, 6.2512, 179.2127, 1, 1, 500);  											// WRC combine									

	CreateVehicle(555, -855.5687, 2746.8108, 45.5144, 184.7242, 3, 3, 600);  										// Erretat Windsor								
	CreateVehicle(523, 218.0764, 1855.1925, 12.9395, 0, 0, 104, 600);												// BCSD Motorcycle

	// ------------ boneyard airport spawns -------
	CreateVehicle(593, 325.3983, 2541.7637, 17.2687, 180.3351, 1, 1, 600);  										// Boneyard Dodo 1
	CreateVehicle(593, 290.7545, 2543.1855, 17.2807, 180.1240, 1, 1, 600);  										// Boneyard Dodo 2
	CreateVehicle(487, 350.7254, 2537.8352, 16.9129, 182.3236, 1, 86, 600); 										// Boneyard Maverick 1
	CreateVehicle(487, 365.6004, 2537.8245, 16.8333, 180.7785, 3, 1, 600); 											// Boneyard Maverick 2
	CreateVehicle(487, 381.0583, 2538.0293, 16.7157, 180.6734, 10, 99, 600); 										// Boneyard Maverick 3
	CreateVehicle(592, -40.8279, 2502.5588, 17.6801, 270.5634, 1, 1, 600); 											// BoneYard BIG FUCKING PLANE

	// ------------ boat spawns -------
	CreateVehicle(473, -419.4787, 1160.5115, -0.2524, 270.5251, 6, 6, 600); 										// FC Dinghy spawn
	CreateVehicle(452, -938.7014, 2649.6758, 40.1290, 136.5486, 1, 1, 600); 										// EQ Speeder spawn
	CreateVehicle(453, -493.4812, 613.8085, -0.3874, 1.1206, 1, 11, 600); 											// FC reefer spawn

	CreateVehicle(498, 1154.6497, 1415.4753, 5.8203, 1.3050, 0, 0, 600); 											// Uber Motors Boxville
	CreateVehicle(498, 1124.7452, 1415.8792, 5.8203, 357.4724, 0, 0, 600); 											// Uber Motors Boxville
	CreateVehicle(445, 1144.0966, 1416.4517, 5.8203, 3.1851, 0, 0, 600); 											// Uber Motors Admiral
	CreateVehicle(445, 1128.6824, 1416.6604, 5.8203, 354.4117, 0, 0, 600); 											// Uber Motors Admiral

	//  ----------- random car spawns ----------
	CreateVehicle(604, -625.0648, 1189.4645, 10.3164, 22.9233, -1, -1, 600); 										// Shitty Glendale under bridge

	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -1525.4744, 2525.3840, 55.5303, 179.9719, -1, -1, 600); 		// LQ Car 1

	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -214.3783, 1023.7228, 19.3664, 90.1629, -1, -1, 600); 			// FC Car 1
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -253.4753, 1023.5632, 19.3715, 90.3106, -1, -1, 600); 			// FC Car 2
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -305.0736, 1011.8260, 19.2998, 269.0440, -1, -1, 600);			// FC Car 3 (Hospital lot)
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -270.1810, 1076.4216, 19.3715, 0.9510, -1, -1, 600); 			// FC Car 4
	CreateVehicle(605, -230.9406, 1055.9912, 19.4417, 162.7207, -1, -1, 600); 										// FC Car 5 (Shitty Glendale by trailer)
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -175.9425, 1020.8526, 19.4487, 90.3946, -1, -1, 600); 			// FC Car 6
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -185.0862, 1069.0322, 19.3713, 0.5464, -1, -1, 600); 			// FC Car 7
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -201.0949, 1051.8784, 19.3725, 179.3618, -1, -1, 600); 			// FC Car 8
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -169.6596, 1143.0320, 19.3713, 270.6666, -1, -1, 600);			// FC Car 9
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -129.5031, 1093.0468, 19.3721, 270.4113, -1, -1, 600); 			// FC Car 10
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -87.2841, 1076.7125, 19.4496, 179.8298, -1, -1, 600); 			// FC Car 11 (Radio station)
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -134.4046, 1177.0005, 19.4558, 206.1003, -1, -1, 600); 			// FC Car 12 (Home furnishing store)
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -138.1444, 1176.4225, 19.4576, 205.1832, -1, -1, 600);			// FC Car 13 (Home furnishing store)
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -79.5422, 1222.5367, 19.4486, 180.4486, -1, -1, 600); 			// FC Car 14 (Hotel)
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -71.0962, 1183.2983, 19.3696, 181.1477, -1, -1, 600); 			// FC Car 15 (bowling)
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -70.9411, 1126.8590, 19.3721, 181.0100, -1, -1, 600); 			// FC Car 16
	CreateVehicle(604, 124.5339, 1066.9445, 13.3164, 176.3219, -1, -1, 600); 										// FC Car 17 (Drive-in theatre shitty glendale?)
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), 171.0681, 1183.7113, 14.4647, 324.4164, -1, -1, 600); 			// FC Car 18 ClucknBell
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), 56.3616, 1157.4613, 18.3717, 0.0429, -1, -1, 600); 				// FC Car 19 Motel
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), 28.5009, 1203.5166, 18.7263, 91.1415, -1, -1, 600); 			// FC Car 20
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), 19.7072, 1164.5437, 19.2994, 179.9821, -1, -1, 600); 			// FC Car 21
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -30.6890, 1166.0442, 19.1118, 179.6470, -1, -1, 600); 			// FC Car 22
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -177.9097, 1217.0720, 19.4485, 89.5024, -1, -1, 600); 			// FC Car 23
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -201.7855, 1223.3408, 19.4491, 0.0168, -1, -1, 600); 			// FC Car 24
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -194.5991, 1223.2766, 19.4479, 180.1653, -1, -1, 600);			// FC Car 25
	CreateVehicle(604, -18.4141, 904.8386, 23.0715, 94.4982, -1, -1, 600); 											// FC Car 26 (Shitty glendale)
	CreateVehicle(605, -176.0698, 948.9362, 16.3630, 21.3980, -1, -1, 600); 										// FC Car 27 (Shitty glendale)

	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -825.1196, 1422.5181, 13.6720, 348.3528, -1, -1, 600);			// LB Car 1
	CreateVehicle(605, -829.8219, 1423.5028, 13.6575, 161.9397, -1, -1, 600); 										// LB Car 2 (Shitty glendale)
	CreateVehicle(604, -652.8883, 1467.8628, 14.0435, 141.5054, -1, -1, 600); 										// LB Car 3 (Shitty glendale)
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -763.9072, 1510.0950, 25.2648, 180.8839, -1, -1, 600); 			// LB Car 4
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -806.4664, 1497.6917, 20.5953, 89.9873, -1, -1, 600); 			// LB Car 5
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -833.5054, 1486.6176, 17.7638, 269.5733, -1, -1, 600); 			// LB Car 6
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -866.0384, 1547.7168, 23.0207, 89.5420, -1, -1, 600); 			// LB Car 7
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -866.6221, 1557.2722, 23.8389, 270.6201, -1, -1, 600); 			// LB Car 8
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -813.8242, 1553.2169, 26.8100, 180.4594, -1, -1, 600); 			// LB Car 9
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -752.1456, 1589.4430, 26.7333, 333.4181, -1, -1, 600); 			// LB Car 10
	CreateVehicle(604, -906.8320, 1712.0446, 27.4721, 49.6424, -1, -1, 600); 										// LB Car 11 (Shitty glendale)
	CreateVehicle(543, -1203.8711, 1812.9711, 41.4906, 44.1263, -1, -1, 600); 										// LB Car 12 (Truck)
	CreateVehicle(543, -1353.6088, 2049.5210, 52.2373, 66.9871, -1, -1, 600); 										// LB Car 13 (Truck)

	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -1529.3245, 2556.4441, 55.5292, 90.9043, -1, -1, 600); 			// EQ Car 2
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -1528.1495, 2606.4919, 55.3850, 90.3336, -1, -1, 600); 			// EQ Car 3
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -1475.6538, 2595.6687, 55.3852, 270.3558, -1, -1, 600); 		// EQ Car 4
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -1440.8177, 2606.6326, 55.3844, 89.8610, -1, -1, 600); 			// EQ Car 5
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -1444.1332, 2676.5313, 55.3844, 91.1249, -1, -1, 600); 			// EQ Car 7
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -1272.9589, 2707.3142, 49.6914, 28.4890, -1, -1, 600); 			// EQ Car 9
	CreateVehicle(605, -1543.9308, 2740.5652, 61.8608, 93.9499, -1, -1, 600); 										// EQ Car 10 (Shitty glendale)
	CreateVehicle(554, -1586.0900, 2678.5361, 55.2258, 87.6208, -1, -1, 600); 										// EQ Car 11 (Truck)
	CreateVehicle(605, -1606.8489, 2460.7534, 63.9250, 183.7480, -1, -1, 600); 										// EQ Car 12 (Shit glendale)

	CreateVehicle(604, -1006.7186, 2742.9541, 42.6284, 69.5747, -1, -1, 600); 										// North Car 1 (Shitty glendale by water)
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -729.7980, 2744.7188, 46.8627, 359.8116, -1, -1, 600); 			// North Car 2
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -741.5485, 2751.9578, 46.8519, 178.4834, -1, -1, 600); 			// North Car 3
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -764.8954, 2760.7898, 45.3984, 0.2327, -1, -1, 600); 			// North Car 4
	CreateVehicle(604, -668.7638, 2701.8174, 71.0144, 131.8937, -1, -1, 600); 										// North Car 5 (Shitty glendale)

	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -519.6965, 2620.1265, 53.0404, 269.4654, -1, -1, 600); 			// Casino Car 1
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -539.5047, 2578.0889, 53.0396, 89.3547, -1, -1, 600); 			// Casino Car 2
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -527.4516, 2604.2095, 53.0390, 269.2840, -1, -1, 600); 			// Casino Car 3
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -509.1484, 2560.8611, 53.0395, 88.8322, -1, -1, 600); 			// Casino Car 4
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -540.1948, 2548.7939, 53.0389, 89.7538, -1, -1, 600); 			// Casino Car 5
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -520.8259, 2571.9971, 53.0400, 269.9868, -1, -1, 600); 			// Casino Car 6

	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), 686.8530, 1949.3715, 5.2707, 359.7953, -1, -1, 600); 			// Random carspawn
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -909.4689, 2020.4481, 60.4988, 312.5078, -1, -1, 600); 			// Random carspawn
	CreateVehicle(RANDOM_ARRAY_ELEMENT(CAR_MODELS), -919.5215, 2001.5712, 60.5006, 128.0709, -1, -1, 600); 			// Random carspawn

	CreateVehicle(445, -97.7961, 1337.9744, 10.2265, 188.6163, 12, 12, 600); 										// admiral spawn
	CreateVehicle(586, 92.2972, 1179.4061, 18.1843, 264.2731, 15, 15, 600); 										// FC Wayfarer spawn
	CreateVehicle(462, -165.5756, 1032.1692, 19.3344, 149.1932, 3, 3, 600); 										// FC moped spawn
	CreateVehicle(586, -1519.9233, 2589.0989, 55.3562, 356.6654, 87, 87, 600); 										// EQ Wayfarer spawn
	CreateVehicle(429, -539.6015, 2604.9219, 53.0951, 52.0096, 3, 1, 600); 											// Casino Banshee spawn
	CreateVehicle(542, -36.8082, 1517.5729, 12.4996, 300.3521, 1, 1, 600); 											// junkyard clover spawn
	CreateVehicle(422, -37.0494, 1521.3391, 12.7422, 303.5507, 1, 11, 600); 										// junkyard bobcat spawn
	CreateVehicle(403, 578.2395, 1639.6874, 7.6001, 121.2795, 99, 99, 600); 										// linerunner spawn
	CreateVehicle(514, 573.2647, 1647.9994, 7.5785, 302.9785, 13, 13, 600); 										// petrol tanker spawn
	CreateVehicle(515, 593.7554, 1649.3018, 8.0151, 120.6864, 7, 7, 600); 											// roadtrain spawn
	CreateVehicle(605, 648.5342, 1711.4177, 6.8093, 220.7210, 88, 88, 600); 										// shitty sadler
	CreateVehicle(531, -70.4997, 101.0592, 3.0787, 69.2011, 86, 86, 600); 											// cropduster TRACTOR spawn
	CreateVehicle(478, -78.0396, 97.2363, 3.1093, 159.6231, 65, 65, 600); 											// cropduster WALTON TRUCK spawn
	CreateVehicle(515, -1299.7994, 2713.6340, 51.0926, 4.8500, 14, 14, 600); 										// EQ roadtrain spawn
	CreateVehicle(588, -102.8405, 1368.9537, 10.1818, 189.5638, 11, 11, 600); 										// HOTDOG SPAWN LOL
	CreateVehicle(545, 701.1185, 1948.6630, 5.3501, 359.9957, 126, 126, 600); 										// pink hustler spawn at big spread ranch lol
}

string VehicleManager::GetVehicleName(int vehicleID)
{
	return string(VEHICLE_NAMES[GetVehicleModel(vehicleID)]);
}

bool VehicleManager::IsCropduster(int vehicleID)
{
	return (vehicleID == 512);
}

bool VehicleManager::IsSemiTruck(int vehicleID) {
	static const int SEMI_TRUCK_MODELS[3] =
	{
		403,
		514,
		515
	};

	const int vehicleModelID = GetVehicleModel(vehicleID);
	for (int i = 0; i < sizeof(SEMI_TRUCK_MODELS); i++)
	{
		if (vehicleModelID == SEMI_TRUCK_MODELS[i])
		{
			return true;
		}
	}
	return false;
}

// standard cars
bool VehicleManager::IsClassDVehicle(int vehicleID)
{
	static const int CLASS_D_VEHICLES[] =
	{
		420, 445, 504, 401, 518, 527, 542, 507, 562,
		585, 419, 526, 604, 466, 492, 474, 546, 517,
		410, 551, 516, 467, 600, 426, 436, 547, 405,
		580, 560, 550, 549, 540, 491, 529, 421, 602,
		429, 496, 402, 541, 415, 589, 587, 565, 494,
		502, 503, 411, 559, 603, 475, 506, 451, 477,
		418, 404, 479, 458, 561, 483, 457, 508, 596,
		598, 597, 599, 544, 434, 545, 571, 442, 409
	};

	const int vehicleModelID = GetVehicleModel(vehicleID);
	for (int i = 0; i < sizeof(CLASS_D_VEHICLES); i++)
	{
		if (vehicleModelID == CLASS_D_VEHICLES[i]) return true;
	}
	return false;
}

// heavy duty
bool VehicleManager::IsClassCVehicle(int vehicleID)
{
	static const int CLASS_C_VEHICLES[] = {
		499, 498, 609, 524, 578, 455, 403, 414, 443,
		514, 515, 440, 408, 552, 416, 433, 431, 437,
		406, 588, 423, 428, 525, 512,
	};

	const int vehicleModelID = GetVehicleModel(vehicleID);
	for (int i = 0; i < sizeof(CLASS_C_VEHICLES); i++)
	{
		if (vehicleModelID == CLASS_C_VEHICLES[i]) return true;
	}
	return false; // return 0
}

// bikes
bool VehicleManager::IsClassBVehicle(int vehicleID)
{
	static const int CLASS_B_VEHICLES[] =
	{
		586, 468, 471, 463, 462, 523
	};

	const int vehicleModelID = GetVehicleModel(vehicleID);
	for (int i = 0; i < sizeof(CLASS_B_VEHICLES); i++)
	{
		if (GetVehicleModel(vehicleID) == CLASS_B_VEHICLES[i]) return true;
	}
	return false; // return 0
}

// sports bikes
bool VehicleManager::IsClassB2Vehicle(int vehicleID)
{
	static const int CLASS_B2_VEHICLES[] =
	{
		581, 521, 522, 461
	};

	const int vehicleModelID = GetVehicleModel(vehicleID);
	for (int i = 0; i < sizeof(CLASS_B2_VEHICLES); i++)
	{
		if (GetVehicleModel(vehicleID) == CLASS_B2_VEHICLES[i]) return true;
	}
	return false; // return 0
}

// airplanes
bool IsClassPVehicle(int vehicleID)
{
	static const int CLASS_P_VEHICLES[] =
	{
		592, 577, 511, 593, 553, 519, 460, 513
	};

	const int vehicleModelID = GetVehicleModel(vehicleID);
	for (int i = 0; i < sizeof(CLASS_P_VEHICLES); i++)
	{
		if (GetVehicleModel(vehicleID) == CLASS_P_VEHICLES[i]) return true;
	}
	return false;
}

// whirlybirds
bool VehicleManager::IsClassRVehicle(int vehicleID)
{
	static const int CLASS_R_VEHICLES[] =
	{
		548, 417, 487, 488, 563, 469
	};

	const int vehicleModelID = GetVehicleModel(vehicleID);
	for (int i = 0; i < sizeof(CLASS_R_VEHICLES); i++)
	{
		if (vehicleModelID == CLASS_R_VEHICLES[i]) return true;
	}
	return false;
}

// military
bool VehicleManager::IsClassM2Vehicle(int vehicleID)
{
	static const int CLASS_M2_VEHICLES[] =
	{
		427, 490, 528, 407, 432, 601, 520, 425, 476, 447
	};

	const int vehicleModelID = GetVehicleModel(vehicleID);
	for (int i = 0; i < sizeof(CLASS_M2_VEHICLES); i++)
	{
		if (GetVehicleModel(vehicleID) == CLASS_M2_VEHICLES[i]) return true;
	}
	return false;
}

// Car Types
bool VehicleManager::IsBoat(int vehicleID)
{
	static const int BOAT_VEHICLE_MODELS[] =
	{
		472, 473, 493, 595, 484, 430, 453, 446, 554
	};

	const int vehicleModelID = GetVehicleModel(vehicleID);
	for (int i = 0; i < sizeof(BOAT_VEHICLE_MODELS); i++)
	{
		if (GetVehicleModel(vehicleID) == BOAT_VEHICLE_MODELS[i]) return true;
	}
	return false;
}

bool VehicleManager::IsBike(int vehicleID)
{
	static const int BIKE_VEHICLE_MODELS[] =
	{
		581, 509, 481, 462, 521, 463, 510, 522, 461, 448, 471, 468, 586, 523
	};

	const int vehicleModelID = GetVehicleModel(vehicleID);
	for (int i = 0; i < sizeof(BIKE_VEHICLE_MODELS); i++)
	{
		if (GetVehicleModel(vehicleID) == BIKE_VEHICLE_MODELS[i]) return true;
	}
	return false;
}

bool VehicleManager::IsWindowOpen(int vehicleID)
{
	auto i = vehicleWindowMap.find(vehicleID);
	if (i != vehicleWindowMap.cend())
	{
		return i->second;
	}
	return false;
}

void VehicleManager::SetWindowState(int vehicleID, bool isOpen)
{
	vehicleWindowMap[vehicleID] = isOpen;
}
