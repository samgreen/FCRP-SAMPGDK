#pragma once
#include "sampgdk.h"
#include <stdlib.h>

#define UPDATED_TIMESTAMP	__TIMESTAMP__
// Server MOTD
#define MOTD				"Welcome back to the revolution. Please report all bugs using the /reportbug feature."

// NSA MOTD
#define NSA_MOTD1 			"our cover id is professional black market dealers and badasses basically"
#define NSA_MOTD2 			"     - jeff"
//#define NSA_MOTD3 		" "
//#define NSA_MOTD4 		" "
//#define NSA_MOTD5 		" "

#define MAX_AMMO			65000

// Colors
#define COLOR_FADE1 		0xE6E6E6E6
#define COLOR_FADE2 		0xC8C8C8C8
#define COLOR_FADE3 		0xAAAAAAAA
#define COLOR_FADE4 		0x8C8C8C8C
#define COLOR_FADE5 		0x6E6E6E6E

#define COLOR_MAGENTA 		0xFF00FFFF
#define COLOR_GRAD1 		0xB4B5B7FF
#define COLOR_GREEN 		0x33AA33AA
#define COLOR_RED 			0xAA3333AA
#define COLOR_LIGHTRED 		0xFF6347AA
#define COLOR_LIGHTBLUE 	0x33CCFFAA
#define COLOR_LIGHTGREEN 	0x9ACD32AA
#define COLOR_YELLOW 		0xFFFF00AA
#define COLOR_WHITE 		0xFFFFFFAA
#define COLOR_PURPLE 		0xC2A2DAAA
#define COLOR_BLACK 		0x000000FF
#define COLOR_TURQUOISE 	0x48D1CCFF
#define COLOR_GOLD 			0xFFD700FF
#define COLOR_BLUE			0x3399FFAA
#define COLOR_EMOTE 		0xC2A2DAAA
#define COLOR_OOC 			0xE0FFFFAA
#define COLOR_ORANGE 		0xFF9721AA
#define COLOR_SYSTEM 		0xEFEFF7AA
#define COLOR_HOTPINK 		0xFF0080FF
#define COLOR_PINKISH 		0xFF8282AA

#define RANDOM_ARRAY_ELEMENT(anArray) anArray[rand() % sizeof(anArray)]

// ----- random newb spawns -----
//float RANDOM_SPAWNS[][3] = {
//	{  26.1551, 922.8038, 23.6378 },
//	{ -92.5513, 970.8187, 19.9593 },
//	{ -56.5206, 935.9814, 21.2074 },
//	{  20.2909, 949.5159, 20.3168 }
//};

// News Messages
const char NEWS_MESSAGES[][MAX_CLIENT_MESSAGE] = {
	"Property values in Bone County plummet! San Andreans rush to capitalize!",
	"Toxic waste has been found in areas around Bone County; how will it affect us?",
	"Pot legalization push SQUASHED by local BCSD Commissioner!",
	"The BCSD have a law suit headed towards them; what will happen? Time will only tell.",
	"Mayoral Elections spur into action! Who will get YOUR vote?"
};

// card name array
const char CARD_NAMES[][20] = {
	"Ace of Spades",
	"Ace of Hearts",
	"Ace of Diamonds",
	"Ace of Clubs",
	"2 of Spades",
	"2 of Hearts",
	"2 of Diamonds",
	"2 of Clubs",
	"3 of Spades",
	"3 of Hearts",
	"3 of Diamonds",
	"3 of Clubs",
	"4 of Spades",
	"4 of Hearts",
	"4 of Diamonds",
	"4 of Clubs",
	"5 of Spades",
	"5 of Hearts",
	"5 of Diamonds",
	"5 of Clubs",
	"6 of Spades",
	"6 of Hearts",
	"6 of Diamonds",
	"6 of Clubs",
	"7 of Spades",
	"7 of Hearts",
	"7 of Diamonds",
	"7 of Clubs",
	"8 of Spades",
	"8 of Hearts",
	"8 of Diamonds",
	"8 of Clubs",
	"9 of Spades",
	"9 of Hearts",
	"9 of Diamonds",
	"9 of Clubs",
	"10 of Spades",
	"10 of Hearts",
	"10 of Diamonds",
	"10 of Clubs",
	"Jack of Spades",
	"Jack of Hearts",
	"Jack of Diamonds",
	"Jack of Clubs",
	"Queen of Spades",
	"Queen of Hearts",
	"Queen of Diamonds",
	"Queen of Clubs",
	"King of Spades",
	"King of Hearts",
	"King of Diamonds",
	"King of Clubs"
};

const char WEAPON_NAMES[][32] =
{
	"Unarmed",
	"Brass Knuckles",
	"Golf Club",
	"Night Stick",
	"Knife",
	"Baseball Bat",
	"Shovel",
	"Pool cue",
	"Katana",
	"Chainsaw",
	"Purple Dildo",
	"White Dildo",
	"Long White Dildo",
	"White Dildo 2",
	"Flowers",
	"Cane",
	"Grenades",
	"Tear Gas",
	"Molotovs",
	"Vehicle Missile",
	"Hydra Flare",
	"Jetpack",
	"Pistol",
	"Silenced Pistol",
	"Desert Eagle",
	"Shotgun",
	"Sawn Off Shotgun",
	"Combat Shotgun",
	"Micro Uzi",
	"MP5",
	"AK47",
	"M4",
	"Tec9",
	"Rifle",
	"Sniper Rifle",
	"RPG",
	"Stinger",
	"Flame Thrower",
	"Minigun",
	"Satchels",
	"Detonator",
	"Spray Paint",
	"Fire Extinguisher",
	"Camera",
	"Nightvision Goggles",
	"Thermal Goggles",
	"Parachute",
	"Fake Pistol",
	"",
	"Vehicle",
	"Helicopter",
	"Explosion",
	"",
	"Drowned",
	"Collision"
};

const char VEHICLE_NAMES[][32] = {
	"Landstalker",
	"Bravura",
	"Buffalo",
	"Linerunner",
	"Pereniel",
	"Sentinel",
	"Dumper",
	"Firetruck",
	"Trashmaster",
	"Stretch",
	"Manana",
	"Infernus",
	"Voodoo",
	"Pony",
	"Mule",
	"Cheetah",
	"Ambulance",
	"Leviathan",
	"Moonbeam",
	"Esperanto",
	"Taxi",
	"Washington",
	"Bobcat",
	"Mr Whoopee",
	"BF Injection",
	"Hunter",
	"Premier",
	"Enforcer",
	"Securicar",
	"Banshee",
	"Predator",
	"Bus",
	"Rhino",
	"Barracks",
	"Hotknife",
	"Trailer",
	"Previon",
	"Coach",
	"Cabbie",
	"Stallion",
	"Rumpo",
	"RC Bandit",
	"Romero",
	"Packer",
	"Monster Truck",
	"Admiral",
	"Squalo",
	"Seasparrow",
	"Pizzaboy",
	"Tram",
	"Trailer",
	"Turismo",
	"Speeder",
	"Reefer",
	"Tropic",
	"Flatbed",
	"Yankee",
	"Caddy",
	"Solair",
	"Berkley's RC Van",
	"Skimmer",
	"PCJ-600",
	"Faggio",
	"Freeway",
	"RC Baron",
	"RC Raider",
	"Glendale",
	"Oceanic",
	"Sanchez",
	"Sparrow",
	"Patriot",
	"Quad",
	"Coastguard",
	"Dinghy",
	"Hermes",
	"Sabre",
	"Rustler",
	"ZR-350",
	"Walton",
	"Regina",
	"Comet",
	"BMX",
	"Burrito",
	"Camper",
	"Marquis",
	"Baggage",
	"Dozer",
	"Maverick",
	"News Chopper",
	"Rancher",
	"Govt SUV",
	"Virgo",
	"Greenwood",
	"Jetmax",
	"Hotring",
	"Sandking",
	"Blista Compact",
	"Police Maverick",
	"Boxville",
	"Benson",
	"Mesa",
	"RC Goblin",
	"Hotring Racer",
	"Hotring Racer",
	"Bloodring Banger",
	"Rancher",
	"Super GT",
	"Elegant",
	"Journey",
	"Bike",
	"Mountain Bike",
	"Beagle",
	"Cropdust",
	"Stunt",
	"Tanker",
	"RoadTrain",
	"Nebula",
	"Majestic",
	"Buccaneer",
	"Shamal",
	"Hydra",
	"FCR-900",
	"NRG-500",
	"BCSD Motorcycle",
	"Cement Truck",
	"Tow Truck",
	"Fortune",
	"Cadrona",
	"FBI Truck",
	"Willard",
	"Forklift",
	"Tractor",
	"Combine",
	"Feltzer",
	"Remington",
	"Slamvan",
	"Blade",
	"Freight",
	"Streak",
	"Vortex",
	"Vincent",
	"Bullet",
	"Clover",
	"Sadler",
	"Firetruck",
	"Hustler",
	"Intruder",
	"Primo",
	"Cargobob",
	"Tampa",
	"Sunrise",
	"Merit",
	"Utility",
	"Nevada",
	"Yosemite",
	"Windsor",
	"Monster Truck",
	"Monster Truck",
	"Uranus",
	"Jester",
	"Sultan",
	"Stratum",
	"Elegy",
	"Raindance",
	"RC Tiger",
	"Flash",
	"Tahoma",
	"Savanna",
	"Bandito",
	"Freight",
	"Trailer",
	"Kart",
	"Mower",
	"Duneride",
	"Sweeper",
	"Broadway",
	"Tornado",
	"AT-400",
	"DFT-30",
	"Huntley",
	"Stafford",
	"BF-400",
	"Newsvan",
	"Tug",
	"Trailer",
	"Emperor",
	"Wayfarer",
	"Euros",
	"Hotdog",
	"Club",
	"Trailer",
	"Trailer",
	"Andromada",
	"Dodo",
	"RC Cam",
	"Launch",
	"BCSD Cruiser",
	"Police Car (SFPD)",
	"BCSD Cruiser",
	"BCSD Ranger",
	"Picador",
	"BCSD S.W.A.T. Van",
	"Alpha",
	"Phoenix",
	"Glendale",
	"Sadler",
	"Luggage Trailer",
	"Luggage Trailer",
	"Stair Trailer",
	"Boxville",
	"Farm Plow",
	"Utility Trailer"
};

const char DEATH_MESSAGES[][MAX_CLIENT_MESSAGE] = {
	"breaks his back doing the limbo and dies",
	"chokes on his own vomit",
	"holds his breath until he passes out",
	"stabs himself in the heart with a toothpick",
	"plucks out his own eyes and bleeds to death",
	"falls into a VC trap VC#1",
	"eats the poisonous part of the blowfish",
	"trips on a rock into a vat of acid",
	"types /kill",
	"screams 'JIHAD' and cranks his neck violently, snapping it",
	"is struck down by the wrath of the Gods",
	"freaks out and walks off a cliff",
	"got abducted by an aliens and was anal-probed to death",
	"took the red pill",
	"took the blue pill",
	"ate the purple berries, it taastes like burrning",
	"gets his head chopped off by a red ninja",
	"takes a green ninja's shuriken to the eye and bleeds to death",
	"gets his heart ripped out by a blue ninja",
	"is sliced in half by a yellow ninja",
	"is incinerated by BLACKMAGE for 727 damage!  Critical hit!",
	"got foited in the face and died",
	"got blown up by the Red Baron while he was doing a stunt",
	"has a heart attack due to high cholesterol and dies",
	"dies from breast cancer",
	"headbutts a wall and ends himself",
	"gets eaten by zombies",
	"crossed paths with the FeralCatGang and got raped to death",
	"gets hit by a yo-yo flying through the sky and dies",
	"ate some bad taco-truck earlier",
	"ran with scissors, fell, and died",
	"baxed some dags and died",
	"put a plastic bag over his head and suffocated to death",
	"tried to eat a candy bar too fast and choked to death",
	"gets trampled by a horse",
	"is taken away by a bear, and eaten",
	"gets run over by a bus",
	"tried huffing bearmace and died",
	"gets eaten by a dinosaur",
	"is too lazy to run back",
	"/killed to avoid living",
	"is consumed by the power of the ring",
	"gets struck in the face by a flying African Swallow",
	"eats some antifreeze",
	"eats rat poison because it looked like candy",
	"drank laundry detergent because it looked like soda",
	"put LimeAway on his pancakes because it looked like syrup",
	"eats ceiling insulation and dies of itchy stomach",
	"steps on a rusty nail, gets tetanus and dies",
	"is bitten by a raccoon, gets rabies, and dies",
	"gets mauled by a rabid bear",
	"is slain by the white rabbit",
	"gets the plague and dies",
	"gets stung by a bee and dies to allergies",
	"opens an envelope of anthrax",
	"rubs against a chinaman and dies from SARS",
	"gets struck by lightning and dies",
	"is brutally beaten by the pink power ranger, and dies",
	"is bitten by a rattlesnake and dies",
	"eats a rock and dies",
	"falls in quicksand and dies",
	"falls in hot-lava and dies",
	"gets attacked by a crocodile, and dies",
	"gets trampled by a hoard of Mongorians, and dies",
	"gets stung by a scorpion, and dies",
	"sees a group of gothic kids, and dies from loathing",
	"sees some emo kids and ends himself",
	"eats a cup of sand and dies",
	"falls on a large cactus and dies",
	"gets attacked by rabid coyotes and dies",
	"contracts the T-Virus and dies"
};

const char GAGGED_MESSAGES[][32] = {
	"Mrrggfff..",
	"Mmmmpphhh!!",
	"NGGGGHHHHH",
	"Mmmrrrpphhh!",
	"Mmmrraaalllpppp!!!",
	"HHHRRRMMM!",
	"Arrrmmmphhhh!",
	"MMMrrrrrAGHHHrrr!",
	"RreeeeMMRRFFF!",
	"AEEEIIIIFRRRPP!",
	"HRLLLLPPP!",
	"ShhhhhFARRRRRRAHHH!",
	"GGrrahhhhMRRRR!",
	"EiiiARFARRRR",
	"MrrrfffNrrrrr!",
	"Gerreraarraerrr!",
	"RrrrrrrmmAaaagght!",
	"Geeeeeaawhhh!",
	"shhhheeeeeeFARRRR!",
	"ReeeeeArrrghhhhh!",
	"PhhhhhRRRRRrrr!",
	"RRRRRHhhhhhmMMMMph!",
	"GaarhhhhhhHHHmmmp!",
	"Hurf Durf"
};

static const int CAR_MODELS[] = {
	422, // bobcat
	496, // blista compact
	401, // bravura
	482, // burrito
	483, // camper
	542, // clover
	507, // elegant
	562, // elegy
	533, // feltzer
	466, // glendale
	492, // greenwood
	579, // huntley
	546, // intruder
	508, // journey
	400, // landstalker
	517, // majestic
	410, // manana
	551, // merit
	500, // mesa
	516, // nebula
	467, // oceanic
	404, // perennial
	600, // picador
	426, // premier
	436, // previon
	547, // primo
	479, // regina
	475, // sabre
	567, // savanna
	549, // tampa
	576, // tornado
	558, // uranus
	540, // vincent
	554, // yosemite	
};