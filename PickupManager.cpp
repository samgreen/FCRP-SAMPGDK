#include "PickupManager.h"
#include "sampgdk.h"

PickupManager::PickupManager() {}
PickupManager::~PickupManager() {}

void PickupManager::CreatePickups()
{
	// -------------- icons ------------------
	AddStaticPickup(1239, 23, 230.9678, 1885.0745, 17.6406, 0); 		// PD entrance
	AddStaticPickup(1239, 23, -310.1276, 1303.5784, 53.6643, 0);  		// taxi interior entrance
	AddStaticPickup(1239, 23, -1371.8241, 1580.1323, 1052.5313, 0); 	// taxi interior exit
	AddStaticPickup(1239, 23, 2139.4114, -2291.1338, 20.6646, 0); 		// corp 1 package pickup
	AddStaticPickup(1239, 23, 631.4086, 1252.6676, 11.6911, 0); 		// corp 1 warehouse entrance
	AddStaticPickup(1239, 23, 2156.8601, -2274.7690, 13.3119, 0); 		// corp 1 warehouse exit
	AddStaticPickup(1239, 23, -692.1733, 939.5443, 13.6328, 0); 		// corp 2 package pickup
	AddStaticPickup(1274, 23, -179.9634, 1133.1444, 19.7422, 0); 		// bank entrance
	AddStaticPickup(1239, 23, -181.4953, 1034.7903, 19.7422, 0); 		// 24/7 A entrance 
	AddStaticPickup(1239, 23, 51.0424, 1521.1890, 32.0149, 0); 			// mat pickup
	AddStaticPickup(1239, 23, -928.9985, 2022.5295, 60.9141, 0); 		// mat dropoff
	AddStaticPickup(1239, 23, 2137.6240, -2282.2087, 20.6719, 0);		// gunlocker big corp spawn
	AddStaticPickup(1239, 23, -783.6580, 1519.2717, 27.0442, 0); 		// Las Barancas Gunlocker
	AddStaticPickup(1239, 23, -1526.1495, 2624.9775, 55.8359, 0); 		// El Quebrados Gunlocker
	AddStaticPickup(1239, 23, -1364.4390, 2055.6584, 52.5156, 0); 		// bait shop gunlocker
	AddStaticPickup(1239, 23, 674.1207, 1706.6729, 7.1875, 0); 			// big store gunlocker
	AddStaticPickup(1239, 23, -688.1145, 932.3109, 13.6328, 0); 		// gunlocker small corp spawn
	AddStaticPickup(1239, 23, -205.4993, 1165.2073, 19.7422, 0); 		// gunlocker main street
	AddStaticPickup(1239, 23, 172.5752, 1176.5787, 14.7645, 0); 		// cluckin bell 1 entrance
	AddStaticPickup(1239, 23, 369.4928, -6.6979, 1001.8589, 0); 		// cluckin bell 1 menu location
	AddStaticPickup(1239, 23, -2482.4417, -122.8426, 25.6237, 0);		// bing's boobs & bongs
	AddStaticPickup(1239, 23, -746.6204, 1589.3191, 26.9609, 0); 		// LB 24/7
	AddStaticPickup(1239, 23, -713.4171, 681.8257, 3.8607, 0);  		// drug dealer job
	AddStaticPickup(1239, 23, -90.6001, 1118.4298, 20.7860, 0);  		// wheelman job
	AddStaticPickup(1239, 23, -366.5633, 1195.6937, 19.6198, 0);  		// low level drug /get
	AddStaticPickup(1239, 23, -1182.7694, -1129.0146, 129.2188, 0);		// high quantity pot /get
	AddStaticPickup(1239, 23, 331.4772, 1122.4630, 1084.6694, 0);  		// crack /get
	AddStaticPickup(1276, 23, 355.4525, 209.5901, 1008.3828, 0);  		// /learn station in library (tiki icon)
	AddStaticPickup(1239, 23, 354.6090, 203.6496, 1008.3828, 0);		// /levelup station in library
	AddStaticPickup(1274, 23, -828.3200, 1503.7880, 19.7908, 0);  		// Las Barancas bank
	AddStaticPickup(1239, 23, 204.1489, 1867.6849, 12.8861, 0);			// ground level PD arrest point
	AddStaticPickup(1239, 23, 240.4763, 1871.6873, 31.5778, 0); 		// rooftop PD arrest point
	AddStaticPickup(1314, 23, 361.7229, 209.4560, 1008.3828, 0);		// /info station1 in library (2 player icon)
	AddStaticPickup(1314, 23, 363.8543, 209.4886, 1008.3828, 0); 		// /info station2 in library (ditto)
	AddStaticPickup(1239, 23, -830.8702, 1983.7864, 9.4007, 0);  		// entrance to druglab at sherman dam
	AddStaticPickup(1239, 23, 2542.9314, -1296.0159, 1044.1250, 0);		// makedrug table
	AddStaticPickup(1240, 23, -331.5458, 1050.8583, 19.7392, 0);  		// EMS refill station FC
	AddStaticPickup(1240, 23, -322.3870, 1057.8359, 19.8917, 0);		// EMS heal point FC
	AddStaticPickup(1239, 23, 662.5282, 1717.0443, 7.1875, 0); 			// 24/7 C
	AddStaticPickup(1239, 23, -1483.4847, 2614.4500, 58.7879, 0); 		// merc job
	AddStaticPickup(1275, 23, -321.6136, 1048.6813, 20.3403, 0); 		// skin icon
	AddStaticPickup(1275, 23, -1514.9629, 2520.1213, 55.9589, 0); 		// skin icon EQ
	AddStaticPickup(1239, 23, -329.3828, 835.5164, 14.2422, 0); 		// arms job
	AddStaticPickup(1239, 23, 234.5382, 111.4735, 1003.2257, 0); 		// PD /clear
	AddStaticPickup(1253, 23, -1830.7037, 624.9372, 32.0431, 0); 		// nsa pickup I WOULD SKATE THIS icon
	AddStaticPickup(1238, 23, 1094.1666, 1599.0883, 12.5469, 0); 		// uber motors icon
	AddStaticPickup(1238, 23, -1402.9467, -250.8844, 1043.1064, 0); 	// stadium /exit icon

	// --- mickey's interior icons ---
	AddStaticPickup(1239, 23, -818.2014, 1560.5498, 27.1172, 0); 		// Mexican Lounge
	AddStaticPickup(1239, 23, -1465.6117, 2611.5933, 56.1797, 0);
	AddStaticPickup(1239, 23, 794.3044, 1687.1449, 5.2813, 0);
	AddStaticPickup(1239, 23, -368.5613, 1168.5143, 20.2719, 0);
	AddStaticPickup(1239, 23, -552.6055, 2594.0142, 53.9348, 0);
	AddStaticPickup(1239, 23, -205.6373, 1152.8442, 19.8903, 0);
	AddStaticPickup(1239, 23, -180.4815, 1088.0306, 19.7422, 0);
	AddStaticPickup(1239, 23, 423.9344, 2536.3774, 16.1484, 0); 		// red barons house
	AddStaticPickup(1239, 23, -217.5264, 979.0179, 19.5021, 0); 		// fort carson sheriff dept
	AddStaticPickup(1239, 23, -143.9999, 1224.5057, 19.8992, 0); 		// FC donut shop
	AddStaticPickup(1239, 23, -1213.5530, 1830.8236, 41.9297, 0); 		// Cluckin Bell 2
	AddStaticPickup(1310, 23, 798.0900, 3768.3074, 2.3365, 0); 			// Admin Haus Interior
	AddStaticPickup(1239, 23, -857.7042, 1535.8347, 22.5870, 0); 		// Smokin' Beef Grill
	AddStaticPickup(1239, 23, -1051.6421, 1550.1176, 33.4376, 0);		// Crack House
	AddStaticPickup(1239, 23, -314.6049, 1774.4526, 43.6406, 0); 		// regular tom's gym
	AddStaticPickup(1239, 23, -151.7618, 881.6793, 18.4516, 0); 		// Fort Carson small safehouse
	AddStaticPickup(1239, 23, -88.6126, 1378.2150, 10.2734, 0); 		// Lil Probe Inn
	AddStaticPickup(1239, 23, 693.5699, 1966.9011, 5.5391, 0); 			// big spread ranch
	AddStaticPickup(1239, 23, -91.0821, 1189.2250, 19.7422, 0); 		// bowlin smokes club
	AddStaticPickup(1239, 23, -1568.4006, 2629.5366, 55.8403, 0); 		// safehouse
	AddStaticPickup(1239, 23, 14.6241, 1120.7893, 20.9399, 0); 			// safehouse
	AddStaticPickup(1239, 23, 2579.6768, -1305.6183, 1037.7734, 0); 	// drug lab exit
	AddStaticPickup(1239, 23, -594.3536, 2018.7255, 60.5381, 0); 		// sherman dam entrance	
	AddStaticPickup(1247, 23, 272.8162, 118.5439, 1004.617, 0);			// Police Armor / Health icon
	AddStaticPickup(1239, 23, -254.6683, 2603.5513, 62.8582, 0);		// Dis Club Enter
}

void PickupManager::AddDefaultPickup(int modelID, float x, float y, float z)
{
	AddStaticPickup(modelID, 23, x, y, z, 0); 
}
