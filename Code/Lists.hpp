#pragma once
#include "UI/UIManager.hpp"

namespace Big::Lists
{
	enum Submenu : std::uint32_t
	{
		SubmenuHome,
		SubmenuSettings,
		SubmenuTesting,
		SubmenuSettingsHeader,
		SubmenuSettingsHeaderStaticBackground,
		SubmenuSettingsHeaderGradientBackground,
		SubmenuSettingsTextures,
		SubmenuSettingsHeaderText,
		SubmenuSettingsSubmenuBar,
		SubmenuSettingsOption,
		SubmenuSettingsFooter,
		SubmenuSettingsDescription,
		SubmenuSettingsInput,
		SubmenuSettingsLanguage,
		SubmenuSelectedPlayer,
		SubmenuPlayerList,
		SubmenuPlayerDisplay,
		SubmenuTest,
		SubmenuNetwork,
		SubmenuWorld,
		Weather,
		SubmenuVehicle,
		SubmenuHornboost,
		SubmenuVehicleSpawner,
		SubmenuVehicleTrails,
		SubmenuDrop,
		RIDSubmenu,
		SubmenuVehicleFly,
		SubmenuVehicleWeapons,
		SubmenuParticles,
		SubmenuPlayer,
		SubmenuTestStuff,
		SubmenuVehicleRampBuilder,
		SubmenuVehicleAcrobatics,
		SubmenuTestStuffCool,
		SubmenuNoClip,
		SubmenuWalkstyles,
		SubmenuProofs,
		SubmenuWardrobe,
		SubmenuHotkeys,
		SubmenuHandtrail,
		SubmenuGlow,
		SubmenuAnimation,
		SubmenuModels,
		SubmenuSenarios,
		SubmenuSession,
		SubmenuProtections,
		SubmenuProtectionsModel,
		SubmenuProtectionsOther,
		SubmenuProtectionsScript,
		SubmenuProtectionsNetwork,
		SubmenuThemes,
		SubmenuFullThemes,
		SubmenuInfoBox,
		SubmenuWeapon,
		SubmenuSavedRIDS,
		SubmenuClouds,
		SubmenuPOV,
		SubmenuWeather,
		SubmenuTime,
		SubmenuSpotlight,
		SubmenuSkyColor,
		SubmenuHaven,
		SubmenuRampBuilder,
		SubmenuWaterMain,
		SubmenuBlackHole,
		SubmenuPolice,
		SubmenuGravityBug,
		SubmenuRecovery,
		SubmenuChatCommands,
		SubmenuCrosshair,
		SubmenuPaintGun,
		EntityGunSub,
		EntityGunSub1,
		EntityGunSub2,
		EntityGunSub3,
		SubemenuAngryPanes,
		SubmenuBenevolent,
		SubmenuAttachments,
		SubmenuTeleportPlayer,
		SubmenuTextPlayer,
		TeleportBlip,
		TeleportIndoors,
		TeleportOutdoors,
		TeleportLosSantosCustoms,
		TeleportClothesShops,
		TeleportAirports,
		TeleportAmmunations,
		TeleportBarberShops,
		TeleportTattooShop,
		TeleportStores,
		SubmenuTeleports,
		SubmenuFriendList,
		SubmenuRecentPlayers,
		SubmenuDrops,
		SubmenuSelectedDrop,
		SubmenuWaterQuads,
		SubmenuWaterTune,
		PrecipitationSubmenu,

		SubmenuFriendly,
		SubmenuEvil,
		SubmenuMalicious,
		SubmenuOnlineVehicle,
		SubmenuScriptEvents,
		SubmenuScriptEventsButtons,
		SubmenuScriptEventsLooped,
		SubmenuCrashes

	};

	inline const char* HeaderTypesFrontend[]
	{
		"Static",
		"Gradient",
		"YTD"
	};

	inline UserInterface::HeaderType HeaderTypesBackend[]
	{
		UserInterface::HeaderType::Static,
		UserInterface::HeaderType::Gradient,
		UserInterface::HeaderType::YTD
	};

	inline std::size_t HeaderTypesPosition = 0;

	inline const char* IntegratedGUI[2]{"Native And Texture", "Full Texture"};
	inline std::size_t HeaderTypesIndex = 0;

	inline const char* DemoList[10]
	{
		"One",
		"Two",
		"Three",
		"Four",
		"Five",
		"Six",
		"Seven",
		"Eight",
		"Nine",
		"Ten"
	};

	class CVehicleList
	{
	public:

		inline static std::size_t VehicleListPos = 0;
		constexpr static inline std::array<const char*, 24> VehicleLists{ "Super", "Sports", "Sports Classic", "Sedans", "Motorcycles", "Cycles", "Helicopters",  "Planes", "Boats", "Military", "Emergency", "Commercials", "Muscle", "OffRoad", "SUVs", "Open Wheel", "Trailer", "Trains", "Service", "Utlity", "Vans", "Industrial", "Coupes", "Compacts" };

		constexpr static inline std::array<const char*, 52> Super = { "adder", "autarch", "banshee2", "bullet", "champion", "cheetah", "cyclone", "deveste", "entity2", "entityxf", "emerus", "fmj", "furia", "gp1", "ignus", "infernus", "italigtb", "italigtb2", "krieger", "le7b", "nero", "nero2", "osiris", "penetrator", "pfister811", "prototipo", "prototipo", "reaper", "s80", "sc1", "scramjet", "sheava", "sultanrs", "t20", "taipan", "tempesta", "tezeract", "thrax", "tigon", "turismor", "tyrant", "tyrus", "vacca", "vagner", "vigilante", "visione", "voltic", "voltic2", "xa21", "zeno", "zentorno", "zorrusso" };
		constexpr static inline std::array<const char*, 95> Sports = { "alpha", "banshee", "bestiagts", "blista2", "blista3", "buffalo", "buffalo2", "buffalo3", "calico", "carbonizzare", "comet2", "comet3", "comet4", "comet5", "comet7", "coquette", "coquette4", "cypher", "drafter", "deveste", "euros", "elegy", "elegy2", "feltzer2", "flashgt", "furoregt", "fusilade", "futo", "futo2", "gb200", "growler", "hotring", "komoda", "imorgon", "issi7", "italigto", "jugular", "jester", "jester2", "jester3", "jester4", "khamelion", "kuruma", "kuruma2", "locust", "lynx", "massacro", "massacro2", "neo", "neon", "ninef", "ninef2", "omnis", "paragon", "paragon2", "pariah", "penumbra", "penumbra2", "raiden", "rapidgt", "rapidgt2", "raptor", "remus", "revolter", "rt3000", "ruston", "schafter2", "schafter3", "schafter4", "schafter5", "schafter6", "schlagen", "schwarzer", "sentinel3", "seven70", "specter", "specter2", "streiter", "sugoi", "sultan", "sultan2", "sultan3", "surano", "tampa2", "tropos", "vectre", "verlierer2", "vstr", "zr380", "zr3802", "zr3803", "italirsx", "veto", "veto2", "vstr" };
		constexpr static inline std::array<const char*, 46> SportsClassic = { "ardent", "btype", "btype2", "btype3", "casco", "cheetah2", "coquette2", "deluxo", "dynasty", "fagaloa", "feltzer3", "gt500", "infernus2", "jb700", "jb7002", "mamba", "manana", "manana2", "michelli", "monroe", "nebula", "peyote", "peyote3", "pigalle", "rapidgt3", "retinue", "retinue2", "savestra", "stinger", "stingergt", "stromberg", "swinger", "torero", "tornado", "tornado2", "tornado3", "tornado4" ,"tornado5", "tornado6", "turismo2", "viseris", "z190", "ztype", "zion3","cheburek", "toreador" };
		constexpr static inline std::array<const char*, 34> Sedans = { "asea", "asea2", "asterope", "cinquemila", "cog55", "cog552", "cognoscenti", "cognoscenti2", "deity", "emperor", "emperor2", "emperor3", "fugitive", "glendale", "glendale2", "ingot", "intruder", "limo2", "premier", "primo", "primo2", "regina", "romero", "stafford", "stanier", "stratum", "stretch", "superd", "surge", "tailgater", "tailgater2", "warrener", "warrener2", "washington" };
		constexpr static inline std::array<const char*, 54> Motorcycles = { "akuma", "avarus", "bagger", "bati", "bati2", "bf400", "carbonrs", "chimera", "cliffhanger", "daemon", "daemon2", "defiler", "deathbike", "deathbike2", "deathbike3", "diablous", "diablous2", "double", "enduro", "esskey", "faggio", "faggio2", "faggio3", "fcr", "fcr2", "gargoyle", "hakuchou", "hakuchou2", "hexer", "innovation", "lectro", "manchez", "nemesis", "nightblade", "oppressor", "oppressor2", "pcj", "ratbike", "ruffian", "rrocket", "sanchez", "sanchez2", "sanctus", "shotaro", "sovereign", "stryder", "thrust", "vader", "vindicator", "vortex", "wolfsbane", "zombiea", "zombieb", "manchez2" };
		constexpr static inline std::array<const char*, 7>  Cycles = { "bmx", "cruiser", "fixter", "scorcher", "tribike", "tribike2", "tribike3" };
		constexpr static inline std::array<const char*, 1> Helicopters = { "annihilator" };
		constexpr static inline std::array<const char*, 1> Planes = { "besra" };
		constexpr static inline std::array<const char*, 1> Boats = { "jetmax" };
		/*constexpr static inline std::array<const char*, 26> Helicopters = {"akula", "annihilator", "buzzard", "buzzard2", "cargobob", "cargobob2", "cargobob3", "cargobob4", "frogger", "frogger2", "havok", "hunter", "maverick", "savage", "seasparrow", "skylift", "supervolito", "supervolito2", "swift", "swift2", "valkyrie", "valkyrie2", "volatus", "annihilator2", "seasparrow2", "seasparrow3"};
		constexpr static inline std::array<const char*, 39> Planes = { "alphaz1", "avenger", "avenger2", "besra", "blimp", "blimp2", "blimp3", "bombushka",	"cargoplane", "cuban800", "dodo", "duster", "howard", "hydra", "jet", "lazer","luxor", "luxor2", "mammatus", "microlight", "miljet", "mogul", "molotok", "nimbus", "nokota", "pyro", "rogue", "seabreeze", "shamal", "starling", "strikeforce", "stunt", "titan", "tula", "velum", "velum2", "vestra", "volatol", "alkonost" };
		constexpr static inline std::array<const char*, 23> Boats = { "avisa", "dinghy", "jetmax", "marquis", "seashark", "seashark2", "seashark3", "speeder", "speeder2", "squalo", "submersible", "submersible2", "suntrap", "toro", "toro2", "tropic", "tropic2", "tug", "avisa", "dinghy5", "kosatka", "longfin", "patrolboat" };*/
		constexpr static inline std::array<const char*, 17> Military = { "apc", "barracks", "barracks2", "barracks3", "barrage", "chernobog", "crusader", "halftrack", "khanjali", "minitank", "rhino", "scarab", "scarab2", "scarab3", "thruster", "trailersmall2", "vetir" };
		constexpr static inline std::array<const char*, 21> Emergency = { "ambulance", "fbi", "fbi2", "firetruck", "lguard", "pbus", "police", "police2", "police3", "police4", "policeb", "polmav", "policeold1", "policeold2", "policet", "pranger", "predator", "riot", "riot2", "sheriff", "sheriff2" };
		constexpr static inline std::array<const char*, 20> Commercials = { "benson", "biff", "cerberus", "cerberus2", "cerberus3", "hauler", "hauler2", "mule", "mule2", "mule3", "mule4", "packer", "phantom", "phantom2", "phantom3", "pounder", "pounder2", "stockade", "stockade3", "terbyte" };
		constexpr static inline std::array<const char*, 71> Muscle = { "blade", "buccaneer", "buccaneer2", "chino", "chino2", "clique", "coquette3", "deviant", "dominator", "dominator2", "dominator3", "dominator4", "dominator5", "dominator6", "dukes", "dukes2", "dukes3", "faction", "faction2", "faction3", "ellie", "gauntlet","gauntlet2", "gauntlet3", "gauntlet4", "gauntlet5", "hermes", "hotknife", "hustler", "impaler", "impaler2", "impaler3","impaler4", "imperator", "imperator2", "imperator3", "lurcher", "moonbeam", "moonbeam2", "nightshade", "peyote2", "phoenix", "picador", "ratloader", "ratloader2", "ruiner", "ruiner2", "ruiner3", "sabregt", "sabregt2", "slamvan", "slamvan2", "slamvan3", "slamvan4", "slamvan5", "slamvan6", "stalion", "stalion2", "tampa", "tampa3", "tulip", "vamos", "vigero", "virgo", "virgo2", "virgo3", "voodoo", "voodoo2", "yosemite", "yosemite2","yosemite3" };
		constexpr static inline std::array<const char*, 58> OffRoad = { "bfinjection", "bifta", "blazer", "blazer2", "blazer3", "blazer4", "blazer5", "bodhi2", "brawler", "bruiser", "bruiser2", "bruiser3", "brutus", "brutus2", "brutus3", "caracara", "caracara2", "dloader", "dubsta3", "dune", "dune2", "dune3", "dune4", "dune5", "everon", "freecrawler", "hellion", "insurgent", "insurgent2", "insurgent3", "kalahari", "kamacho", "marshall", "mesa3", "monster", "monster3", "monster4", "monster5", "menacer", "outlaw", "nightshark", "rancherxl", "rancherxl2", "rebel", "rebel2", "rcbandito", "riata", "sandking", "sandking2", "technical", "technical2", "technical3", "trophytruck", "trophytruck2", "vagrant", "zhaba", "verus", "winky" };
		constexpr static inline std::array<const char*, 34> SUVs = { "baller", "baller2", "baller3", "baller4", "baller5", "baller6", "bjxl", "cavalcade", "cavalcade2", "contender", "dubsta", "dubsta2", "fq2", "granger", "gresley", "habanero", "huntley", "landstalker", "landstalker2", "mesa", "mesa2", "movak", "patriot", "patriot2", "radi", "rebla", "rocoto", "seminole", "seminole2", "serrano", "toros", "xls", "xls2", "squaddie" };
		constexpr static inline std::array<const char*, 4>  OpenWheel = { "formula", "formula2", "openwheel1", "openwheel2" };
		constexpr static inline std::array<const char*, 25> Trailer = { "armytanker", "armytrailer", "armytrailer2", "baletrailer", "boattrailer", "cablecar", "docktrailer", "freighttrailer", "graintrailer", "proptrailer", "raketrailer", "tr2", "tr3", "tr4", "trflat", "tvtrailer", "tanker", "tanker2", "trailerlarge", "trailerlogs", "trailersmall", "trailers", "trailers2", "trailers3", "trailers4" };
		constexpr static inline std::array<const char*, 7>  Trains = { "freight", "freightcar", "freightcont1", "freightcont2", "freightgrain", "metrotrain", "tankercar" };
		constexpr static inline std::array<const char*, 12> Service = { "airbus", "brickade", "bus", "coach", "pbus2", "rallytruck", "rentalbus", "taxi", "tourbus", "trash", "trash2", "wastelander" };
		constexpr static inline std::array<const char*, 20> Utility = { "airtug", "caddy", "caddy2", "caddy3", "docktug", "forklift", "mower", "ripley", "sadler", "sadler2", "scrap", "towtruck", "towtruck2", "tractor", "tractor2", "tractor3", "utillitruck", "utillitruck2", "utillitruck3", "slamtruck" };
		constexpr static inline std::array<const char*, 35> Vans = { "bison", "bison2", "bison3", "bobcatxl", "boxville", "boxville2", "boxville3", "boxville4", "boxville5", "burrito", "burrito2", "burrito3", "burrito4", "burrito5", "camper", "gburrito", "gburrito2", "journey", "minivan", "minivan2", "paradise", "pony", "pony2", "rumpo", "rumpo2", "rumpo3", "speedo", "speedo2", "speedo4", "surfer", "surfer2", "taco", "youga", "youga2", "youga3" };
		constexpr static inline std::array<const char*, 11> Industrial = { "bulldozer", "cutter", "dump", "flatbed", "guardian", "handler", "mixer", "mixer2", "rubble", "tiptruck", "tiptruck2", };
		constexpr static inline std::array<const char*, 14> Coupes = { "cogcabrio", "exemplar", "f620", "felon", "felon2", "jackal", "oracle", "oracle2", "sentinel", "sentinel2", "windsor", "windsor2", "zion", "zion2" };
		constexpr static inline std::array<const char*, 17> Compacts = { "asbo", "blista", "brioso", "club", "dilettante", "dilettante2", "kanjo", "issi2", "issi3", "issi4", "issi5", "issi6", "panto", "prairie", "rhapsody", "brioso2", "weevil" };

	}; inline std::unique_ptr<CVehicleList> g_VehicleList;

	class CPedList
	{
	public:

		inline static std::size_t PedListPos = 0;
		constexpr static inline std::array<const char*, 3> PedLists{ "Male", "Female", "Animal"};

		constexpr static inline std::array<const char*, 3> Male = { "s_m_y_cop_01", "A_C_shepherd", "s_m_m_fibsec_01" };
		constexpr static inline std::array<const char*, 1> Female = { "s_f_y_cop_01" };
		constexpr static inline std::array<const char*, 32> Animal = { "a_c_boar", "a_c_cat_01", "a_c_chickenhawk", "a_c_chimp", "a_c_chop", "a_c_cormorant", "a_c_cow", "a_c_coyote", "a_c_crow", "a_c_deer", "a_c_dolphin", "a_c_fish", "a_c_hen", "a_c_humpback", "a_c_husky", "a_c_killerwhale", "a_c_mtlion", "a_c_pig", "a_c_pigeon", "a_c_poodle", "a_c_pug", "a_c_rabbit_01", "a_c_rat", "a_c_retriever", "a_c_rhesus", "a_c_rottweiler", "a_c_seagull", "a_c_sharkhammer", "a_c_sharktiger", "a_c_shepherd", "a_c_stingray", "a_c_westy" };

	}; inline std::unique_ptr<CPedList> g_PedList;

	static struct {
		const char* vehiclePreviewDict;
		const char* vehicleName;
	} VehiclePreviews[332] = {
		{ "lgm_default", "adder" },
		{ "lgm_default", "banshee" },
		{ "lgm_default", "bullet" },
		{ "lgm_default", "carbon" },
		{ "lgm_default", "carboniz" },
		{ "lgm_default", "cheetah" },
		{ "lgm_default", "cogcabri" },
		{ "lgm_default", "comet2" },
		{ "lgm_default", "coquette" },
		{ "lgm_default", "elegy2" },
		{ "lgm_default", "entityxf" },
		{ "lgm_default", "exemplar" },
		{ "lgm_default", "feltzer" },
		{ "lgm_default", "hotknife" },
		{ "lgm_default", "infernus" },
		{ "lgm_default", "jb700" },
		{ "lgm_default", "khamel" },
		{ "lgm_default", "monroe" },
		{ "lgm_default", "ninef" },
		{ "lgm_default", "ninef2" },
		{ "lgm_default", "rapidgt" },
		{ "lgm_default", "rapidgt2" },
		{ "lgm_default", "stinger" },
		{ "lgm_default", "stingerg" },
		{ "lgm_default", "superd" },
		{ "lgm_default", "surano_convertable" },
		{ "lgm_default", "vacca" },
		{ "lgm_default", "voltic_tless" },
		{ "lgm_default", "ztype" },
		{ "lgm_dlc_apartments", "baller3" },
		{ "lgm_dlc_apartments", "baller4" },
		{ "lgm_dlc_apartments", "voltic_tless" },
		{ "lgm_dlc_apartments", "cog55" },
		{ "lgm_dlc_apartments", "cognosc" },
		{ "lgm_dlc_apartments", "mamba" },
		{ "lgm_dlc_apartments", "niteshad" },
		{ "lgm_dlc_apartments", "schafter3" },
		{ "lgm_dlc_apartments", "schafter4" },
		{ "lgm_dlc_apartments", "verlier" },
		{ "lgm_dlc_arena", "cliquexmas" },
		{ "lgm_dlc_arena", "deveste" },
		{ "lgm_dlc_arena", "deviant" },
		{ "lgm_dlc_arena", "italigto" },
		{ "lgm_dlc_arena", "schlagen" },
		{ "lgm_dlc_arena", "toros" },
		{ "lgm_dlc_arena", "clique" },
		{ "lgm_dlc_assault", "flashgt" },
		{ "lgm_dlc_assault", "gb200" },
		{ "lgm_dlc_assault", "jester3" },
		{ "lgm_dlc_assault", "taipan" },
		{ "lgm_dlc_assault", "tezeract" },
		{ "lgm_dlc_assault", "tyrant" },
		{ "lgm_dlc_assault", "entity2" },
		{ "lgm_dlc_battle", "freecrawler" },
		{ "lgm_dlc_battle", "stafford" },
		{ "lgm_dlc_battle", "swinger" },
		{ "lgm_dlc_biker", "hakuchou2" },
		{ "lgm_dlc_biker", "raptor" },
		{ "lgm_dlc_biker", "shotaro" },
		{ "lgm_dlc_business", "alpha" },
		{ "lgm_dlc_business", "jester" },
		{ "lgm_dlc_business", "turismor" },
		{ "lgm_dlc_business2", "banshee_tless" },
		{ "lgm_dlc_business2", "coquette_tless" },
		{ "lgm_dlc_business2", "huntley" },
		{ "lgm_dlc_business2", "massacro" },
		{ "lgm_dlc_business2", "stinger_tless" },
		{ "lgm_dlc_business2", "thrust" },
		{ "lgm_dlc_business2", "voltic_htop" },
		{ "lgm_dlc_business2", "zentorno" },
		{ "lgm_dlc_casinoheist", "imorgon" },
		{ "lgm_dlc_casinoheist", "komoda" },
		{ "lgm_dlc_casinoheist", "rebla" },
		{ "lgm_dlc_casinoheist", "stryder" },
		{ "lgm_dlc_casinoheist", "vstr" },
		{ "lgm_dlc_casinoheist", "formula" },
		{ "lgm_dlc_casinoheist", "formula2" },
		{ "lgm_dlc_casinoheist", "furia" },
		{ "lgm_dlc_executive1", "bestiagts" },
		{ "lgm_dlc_executive1", "fmj" },
		{ "lgm_dlc_executive1", "pfister811" },
		{ "lgm_dlc_executive1", "prototipo" },
		{ "lgm_dlc_executive1", "reaper" },
		{ "lgm_dlc_executive1", "seven70" },
		{ "lgm_dlc_executive1", "windsor2" },
		{ "lgm_dlc_executive1", "xls_web_vehicle_regular_b" },
		{ "lgm_dlc_gunrunning", "vagner" },
		{ "lgm_dlc_gunrunning", "xa21" },
		{ "lgm_dlc_gunrunning", "cheetah2" },
		{ "lgm_dlc_gunrunning", "torero" },
		{ "lgm_dlc_heist", "casco" },
		{ "lgm_dlc_heist", "lectro" },
		{ "lgm_dlc_heist4", "italirsx" },
		{ "lgm_dlc_importexport", "penetrator" },
		{ "lgm_dlc_importexport", "tempesta" },
		{ "lgm_dlc_lts_creator", "furore" },
		{ "lgm_dlc_luxe", "brawler" },
		{ "lgm_dlc_luxe", "chino" },
		{ "lgm_dlc_luxe", "coquette3" },
		{ "lgm_dlc_luxe", "feltzer3" },
		{ "lgm_dlc_luxe", "osiris" },
		{ "lgm_dlc_luxe", "t20" },
		{ "lgm_dlc_luxe", "vindicator" },
		{ "lgm_dlc_luxe", "virgo" },
		{ "lgm_dlc_luxe", "windsor_windsor_lgm_1_b" },
		{ "lgm_dlc_pilot", "coquette2" },
		{ "lgm_dlc_pilot", "coquette2_tless" },
		{ "lgm_dlc_specialraces", "gp1" },
		{ "lgm_dlc_specialraces", "infernus2" },
		{ "lgm_dlc_specialraces", "ruston" },
		{ "lgm_dlc_specialraces", "turismo2" },
		{ "lgm_dlc_security", "baller7" },
		{ "lgm_dlc_security", "champion" },
		{ "lgm_dlc_security", "cinquemila" },
		{ "lgm_dlc_security", "comet7" },
		{ "lgm_dlc_security", "deity" },
		{ "lgm_dlc_security", "ignus" },
		{ "lgm_dlc_security", "jubilee" },
		{ "lgm_dlc_security", "reever" },
		{ "lgm_dlc_security", "shinobi" },
		{ "lgm_dlc_security", "zeno" },
		{ "lgm_dlc_security", "astron" },
		{ "lgm_dlc_smuggler", "cyclone" },
		{ "lgm_dlc_smuggler", "rapidgt3" },
		{ "lgm_dlc_smuggler", "visione" },
		{ "lgm_dlc_stunt", "le7b_lms_le7b_livery_1_b" },
		{ "lgm_dlc_stunt", "lynx_lms_lynx_livery_2_b" },
		{ "lgm_dlc_stunt", "sheava_lms_sheava_livery_2_b" },
		{ "lgm_dlc_stunt", "tyrus_lms_tyrus_livery_1_b" },
		{ "lgm_dlc_summer2020", "openwheel2" },
		{ "lgm_dlc_summer2020", "tigon" },
		{ "lgm_dlc_summer2020", "coquette4" },
		{ "lgm_dlc_summer2020", "openwheel1" },
		{ "lgm_dlc_tuner", "cypher" },
		{ "lgm_dlc_tuner", "euros" },
		{ "lgm_dlc_tuner", "growler" },
		{ "lgm_dlc_tuner", "jester4" },
		{ "lgm_dlc_tuner", "tailgater2" },
		{ "lgm_dlc_tuner", "vectre" },
		{ "lgm_dlc_tuner", "zr350" },
		{ "lgm_dlc_tuner", "comet6" },
		{ "lgm_dlc_valentines", "roosevelt" },
		{ "lgm_dlc_valentines2", "roosevelt2" },
		{ "lgm_dlc_vinewood", "jugular" },
		{ "lgm_dlc_vinewood", "krieger" },
		{ "lgm_dlc_vinewood", "locust" },
		{ "lgm_dlc_vinewood", "neo" },
		{ "lgm_dlc_vinewood", "novak" },
		{ "lgm_dlc_vinewood", "paragon" },
		{ "lgm_dlc_vinewood", "rrocket" },
		{ "lgm_dlc_vinewood", "s80" },
		{ "lgm_dlc_vinewood", "thrax" },
		{ "lgm_dlc_vinewood", "zorrusso" },
		{ "lgm_dlc_vinewood", "drafter" },
		{ "lgm_dlc_vinewood", "emerus" },
		{ "lsc_default", "buccaneer2" },
		{ "lsc_default", "chino2" },
		{ "lsc_default", "faction2" },
		{ "lsc_default", "moonbeam2" },
		{ "lsc_default", "primo2" },
		{ "lsc_default", "voodoo" },
		{ "lsc_dlc_import_export", "comet3" },
		{ "lsc_dlc_import_export", "diablous2" },
		{ "lsc_dlc_import_export", "elegy" },
		{ "lsc_dlc_import_export", "fcr2" },
		{ "lsc_dlc_import_export", "italiagtb2" },
		{ "lsc_dlc_import_export", "nero2" },
		{ "lsc_dlc_import_export", "specter2" },
		{ "lsc_jan2016", "banshee2" },
		{ "lsc_jan2016", "sultan2" },
		{ "lsc_lowrider2", "faction3" },
		{ "lsc_lowrider2", "minivan2" },
		{ "lsc_lowrider2", "sabregt2" },
		{ "lsc_lowrider2", "slamvan3" },
		{ "lsc_lowrider2", "tornado5" },
		{ "lsc_lowrider2", "virgo2" },
		{ "sssa_default", "akuma" },
		{ "sssa_default", "baller2" },
		{ "sssa_default", "banshee" },
		{ "sssa_default", "bati" },
		{ "sssa_default", "bati2_sss_cerveza_b" },
		{ "sssa_default", "bfinject" },
		{ "sssa_default", "bifta" },
		{ "sssa_default", "bison" },
		{ "sssa_default", "blazer" },
		{ "sssa_default", "bodhi" },
		{ "sssa_default", "cavcade" },
		{ "sssa_default", "comet2" },
		{ "sssa_default", "dilettan" },
		{ "sssa_default", "double" },
		{ "sssa_default", "dune" },
		{ "sssa_default", "exemplar" },
		{ "sssa_default", "faggio" },
		{ "sssa_default", "felon" },
		{ "sssa_default", "felon2" },
		{ "sssa_default", "feltzer" },
		{ "sssa_default", "fugitive" },
		{ "sssa_default", "gauntlet" },
		{ "sssa_default", "hexer" },
		{ "sssa_default", "infernus" },
		{ "sssa_default", "issi2" },
		{ "sssa_default", "kalahari" },
		{ "sssa_default", "ninef" },
		{ "sssa_default", "oracle" },
		{ "sssa_default", "paradise_sss_logger_b" },
		{ "sssa_default", "pcj" },
		{ "sssa_default", "rebel" },
		{ "sssa_default", "rocoto" },
		{ "sssa_default", "ruffian" },
		{ "sssa_default", "sadler" },
		{ "sssa_default", "sanchez_sss_atomic_b" },
		{ "sssa_default", "sanchez2" },
		{ "sssa_default", "sandkin2" },
		{ "sssa_default", "sandking" },
		{ "sssa_default", "schwarze" },
		{ "sssa_default", "superd" },
		{ "sssa_default", "surano" },
		{ "sssa_default", "vacca" },
		{ "sssa_default", "vader" },
		{ "sssa_default", "vigero" },
		{ "sssa_default", "zion" },
		{ "sssa_default", "zion2" },
		{ "sssa_dlc_biker", "avarus" },
		{ "sssa_dlc_biker", "bagger" },
		{ "sssa_dlc_biker", "blazer4" },
		{ "sssa_dlc_biker", "chimera" },
		{ "sssa_dlc_biker", "daemon2" },
		{ "sssa_dlc_biker", "defiler" },
		{ "sssa_dlc_biker", "esskey" },
		{ "sssa_dlc_biker", "faggio3" },
		{ "sssa_dlc_biker", "faggion" },
		{ "sssa_dlc_biker", "manchez" },
		{ "sssa_dlc_biker", "nightblade" },
		{ "sssa_dlc_biker", "ratbike" },
		{ "sssa_dlc_biker", "sanctus" },
		{ "sssa_dlc_biker", "tornado6" },
		{ "sssa_dlc_biker", "vortex" },
		{ "sssa_dlc_biker", "woflsbane" },
		{ "sssa_dlc_biker", "youga2" },
		{ "sssa_dlc_biker", "zombiea" },
		{ "sssa_dlc_biker", "zombieb" },
		{ "sssa_dlc_business", "asea" },
		{ "sssa_dlc_business", "astrope" },
		{ "sssa_dlc_business", "bobcatxl" },
		{ "sssa_dlc_business", "cavcade2" },
		{ "sssa_dlc_business", "granger" },
		{ "sssa_dlc_business", "ingot" },
		{ "sssa_dlc_business", "intruder" },
		{ "sssa_dlc_business", "minivan" },
		{ "sssa_dlc_business", "premier" },
		{ "sssa_dlc_business", "radi" },
		{ "sssa_dlc_business", "rancherx" },
		{ "sssa_dlc_business", "stanier" },
		{ "sssa_dlc_business", "stratum" },
		{ "sssa_dlc_business", "washingt" },
		{ "sssa_dlc_business2", "dominato" },
		{ "sssa_dlc_business2", "f620" },
		{ "sssa_dlc_business2", "fusilade" },
		{ "sssa_dlc_business2", "penumbra" },
		{ "sssa_dlc_business2", "sentinel" },
		{ "sssa_dlc_business2", "sentinel_convertable" },
		{ "sssa_dlc_christmas_2", "jester2" },
		{ "sssa_dlc_christmas_2", "massacro2" },
		{ "sssa_dlc_christmas_2", "rloader2" },
		{ "sssa_dlc_christmas_2", "slamvan" },
		{ "sssa_dlc_christmas_3", "tampa" },
		{ "sssa_dlc_executive_1", "rumpo3" },
		{ "sssa_dlc_halloween", "btype2_sss_death_b" },
		{ "sssa_dlc_halloween", "lurcher_sss_hangman_b" },
		{ "sssa_dlc_heist", "blade" },
		{ "sssa_dlc_heist", "enduro" },
		{ "sssa_dlc_heist", "gburrito2" },
		{ "sssa_dlc_heist", "gresley" },
		{ "sssa_dlc_heist", "guardian" },
		{ "sssa_dlc_heist", "innovation" },
		{ "sssa_dlc_heist", "jackal" },
		{ "sssa_dlc_heist", "kuruma" },
		{ "sssa_dlc_heist", "kuruma2" },
		{ "sssa_dlc_heist", "landstalker" },
		{ "sssa_dlc_heist", "nemesis" },
		{ "sssa_dlc_heist", "oracle1" },
		{ "sssa_dlc_heist", "rumpo" },
		{ "sssa_dlc_heist", "schafter2" },
		{ "sssa_dlc_heist", "seminole" },
		{ "sssa_dlc_heist", "surge" },
		{ "sssa_dlc_hipster", "blade" },
		{ "sssa_dlc_hipster", "blazer3" },
		{ "sssa_dlc_hipster", "buffalo" },
		{ "sssa_dlc_hipster", "buffalo2" },
		{ "sssa_dlc_hipster", "glendale" },
		{ "sssa_dlc_hipster", "panto" },
		{ "sssa_dlc_hipster", "picador" },
		{ "sssa_dlc_hipster", "pigalle" },
		{ "sssa_dlc_hipster", "primo" },
		{ "sssa_dlc_hipster", "rebel2" },
		{ "sssa_dlc_hipster", "regina" },
		{ "sssa_dlc_hipster", "rhapsody" },
		{ "sssa_dlc_hipster", "surfer" },
		{ "sssa_dlc_hipster", "tailgater" },
		{ "sssa_dlc_hipster", "warrener" },
		{ "sssa_dlc_hipster", "youga" },
		{ "sssa_dlc_independence", "sovereign" },
		{ "sssa_dlc_lts_creator", "hakuchou" },
		{ "sssa_dlc_lts_creator", "innovation" },
		{ "sssa_dlc_lts_creator", "kalahari_topless" },
		{ "sssa_dlc_mp_to_sp", "blista2" },
		{ "sssa_dlc_mp_to_sp", "buffalo3" },
		{ "sssa_dlc_mp_to_sp", "dominator2" },
		{ "sssa_dlc_mp_to_sp", "dukes" },
		{ "sssa_dlc_mp_to_sp", "gauntlet2" },
		{ "sssa_dlc_mp_to_sp", "stalion2" },
		{ "sssa_dlc_mp_to_sp", "stallion" },
		{ "sssa_dlc_stunt", "bf400_sss_bf400_livery_1_b" },
		{ "sssa_dlc_stunt", "brioso_sss_brioso_livery_1_b" },
		{ "sssa_dlc_stunt", "cliffhanger_sss_cliffhanger_livery_1_b" },
		{ "sssa_dlc_stunt", "contender" },
		{ "sssa_dlc_stunt", "gargoyle_sss_gargoyle_livery_1_b" },
		{ "sssa_dlc_stunt", "omnis_sss_omnis_livery_1_b" },
		{ "sssa_dlc_stunt", "rallytruck_sss_dune_livery_1_b" },
		{ "sssa_dlc_stunt", "tampa2_sss_tampa2_livery_1_b" },
		{ "sssa_dlc_stunt", "trophy_sss_trophy_livery_1_b" },
		{ "sssa_dlc_stunt", "trophy2_sss_trophy2_livery_1_b" },
		{ "sssa_dlc_stunt", "tropos_sss_tropos_livery_1_b" },
		{ "sssa_dlc_valentines", "rloader" },
		{ "candc_gunrunning", "apc" },
		{ "candc_gunrunning", "ardent" },
		{ "candc_gunrunning", "dune3" },
		{ "candc_gunrunning", "halftrack" },
		{ "candc_gunrunning", "nightshark" },
		{ "candc_gunrunning", "oppressor" },
		{ "candc_gunrunning", "tampa3" },
		{ "candc_gunrunning", "trsmall2" },
	};
	
	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsOutdoor[56] = {
		{ "IAA Roof", 134.085,-637.859,262.851 },
		{ "FIB Roof", 150.126,-754.591,262.865 },
		{ "Maze Bank Roof", -75.015,-818.215,326.176 },
		{ "Top Of The Mt Chilad", 450.718,5566.614,806.183 },
		{ "Most Northerly Point", 24.775,7644.102,19.055 },
		{ "Vinewood Bowl Stage", 686.245,577.950,130.461 },
		{ "Sisyphus Theater Stage", 205.316,1167.378,227.005 },
		{ "Galileo Observatory Roof", -438.804,1076.097,352.411 },
		{ "Kortz Center", -2243.810,264.048,174.615 },
		{ "Chumash Historic", -3426.683,967.738,8.347 },
		{ "Paleto Bay Pier", -275.522,6635.835,7.425 },
		{ "God's thumb", -1006.402,6272.383,1.503 },
		{ "Calafia Train Bridge", -517.869,4425.284,89.795 },
		{ "Altruist Cult Camp", -1170.841,4926.646,224.295 },
		{ "Maze Bank Arena Roof", -324.300,-1968.545,67.002 },
		{ "Marlowe Vineyards", -1868.971,2095.674,139.115 },
		{ "Hippy Camp", 2476.712,3789.645,41.226 },
		{ "Devin Weston's House", -2639.872,1866.812,160.135 },
		{ "Abandon Mine", -595.342,2086.008,131.412 },
		{ "Weed Farm", 2208.777,5578.235,53.735 },
		{ "Stab City", 126.975,3714.419,46.827 },
		{ "Airplane Graveyard Airplane Tail", 2395.096,3049.616,60.053 },
		{ "Satellite Dish Antenna", 2034.988,2953.105,74.602 },
		{ "Satellite Dishes", 2062.123,2942.055,47.431 },
		{ "Windmill Top", 2026.677,1842.684,133.313 },
		{ "Sandy Shores Building Site Crane", 1051.209,2280.452,89.727 },
		{ "Rebel Radio", 736.153,2583.143,79.634 },
		{ "Quarry", 2954.196,2783.410,41.004 },
		{ "Palmer-Taylor Power Station Chimney", 2732.931,1577.540,83.671 },
		{ "Merryweather Dock", 486.417,-3339.692,6.070 },
		{ "Cargo Ship", 899.678,-2882.191,19.013 },
		{ "Del Perro Pier", -1850.127,-1231.751,13.017 },
		{ "Play Boy Mansion", -1475.234,167.088,55.841 },
		{ "Jolene Cranley-Evans Ghost", 3059.620,5564.246,197.091 },
		{ "NOOSE Headquarters", 2535.243,-383.799,92.993 },
		{ "Snowman", 971.245,-1620.993,30.111 },
		{ "Oriental Theater", 293.089,180.466,104.301 },
		{ "Beach Skatepark", -1374.881,-1398.835,6.141 },
		{ "Underpass Skatepark", 718.341,-1218.714,26.014 },
		{ "Casino", 925.329,46.152,80.908 },
		{ "University of San Andreas", -1696.866,142.747,64.372 },
		{ "La Puerta Freeway Bridge", -543.932,-2225.543,122.366 },
		{ "Land Act Dam", 1660.369,-12.013,170.020 },
		{ "Mount Gordo", 2877.633,5911.078,369.624 },
		{ "Little Seoul", -889.655,-853.499,20.566 },
		{ "Epsilon Building", -695.025,82.955,55.855 },
		{ "The Richman Hotel", -1330.911,340.871,64.078 },
		{ "Vinewood Sign", 711.362,1198.134,348.526 },
		{ "Los Santos Golf Club", -1336.715,59.051,55.246 },
		{ "Chicken", -31.010,6316.830,40.083 },
		{ "Little Portola", -635.463,-242.402,38.175 },
		{ "Pacific Bluffs Country Club", -3022.222,39.968,13.611 },
		{ "Paleto Forest Sawmill Chimney", -549.467,5308.221,114.146 },
		{ "Mirror Park", 1070.206,-711.958,58.483 },
		{ "Rocket", 1608.698,6438.096,37.637 },
		{ "El Gordo Lighthouse", 3430.155,5174.196,41.280 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsIndoor[16] = {
		{ "Strip Club DJ Booth", 126.135,-1278.583,29.270 },
		{ "Blaine County Savings Bank", -109.299,6464.035,31.627 },
		{ "Police Station", 436.491,-982.172,30.699 },
		{ "Humane Labs Tunnel", 3525.495,3705.301,20.992 },
		{ "Ammunation Office", 12.494,-1110.130,29.797 },
		{ "Ammunation Gun Range", 22.153,-1072.854,29.797 },
		{ "Trevor's Meth Lab", 1391.773,3608.716,38.942 },
		{ "Pacific Standard Bank Vault", 255.851,217.030,101.683 },
		{ "Lester's House", 1273.898,-1719.304,54.771 },
		{ "Floyd's Apartment", -1150.703,-1520.713,10.633 },
		{ "FIB Top Floor", 135.733,-749.216,258.152 },
		{ "IAA Office", 117.220,-620.938,206.047 },
		{ "Pacific Standard Bank", 235.046,216.434,106.287 },
		{ "Fort Zancudo ATC Entrance", -2344.373,3267.498,32.811 },
		{ "Fort Zancudo ATC Top Floor", -2358.132,3249.754,101.451 },
		{ "Torture Room", 147.170,-2201.804,4.688 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsLSC[6] = {
		{ "Benny's Garage", -206.91985,-1300.7858,31.29598 },
		{ "Beekers Garage", 120.13485,6616.1055,31.850428 },
		{ "Sandy Shores", 1174.49,2658.1643,38.070953 },
		{ "Grand Senora Dust", -1136.742,-1982.3253,13.164545 },
		{ "Burton", -375.6223,-128.76067,38.684124 },
		{ "La Mesa", 707.62823,-1087.7771,22.433643 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsCS[13] = {
		{ "Paleto Bay", -4.509100,6521.252930,30.571024 },
		{ "Grapeseed", 1678.057495,4819.882324,41.299820 },
		{ "Grand Senora", 1179.679688,2691.378662,37.124043 },
		{ "Great Chaparral", -1089.404785,2697.033447,19.442095 },
		{ "Suburban Havick", 134.122055,-200.211334,53.864090 },
		{ "Ponsonbys Burton", -148.234741,-308.074463,38.104240 },
		{ "Ponsonbys Rockford Hills", -725.551453,-162.833710,36.570301 },
		{ "Ponsonbys Morningwood", -1460.654419,-227.550964,48.728519 },
		{ "Suburban Del Perro", -1210.620361,-784.160217,16.549015 },
		{ "Masks Vespucci Beach", -1342.185913,-1280.013428,4.443256 },
		{ "Binco Vespucci", -814.432800,-1085.986938,10.567306 },
		{ "Binco Strawberry", 411.403564,-806.654907,28.742212 },
		{ "Strawberry", 89.320786,-1392.317627,28.800083 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsTS[6] = {
		{ "Paleto Bay", -285.910400,6202.941895,30.626459 },
		{ "Sandy Shores", 1853.771851,3746.440918,32.395195 },
		{ "Chumash", -3155.888672,1073.844482,20.188726 },
		{ "Vinewood", 318.228790,164.457535,103.146561 },
		{ "Vespucci", -1163.504639,-1413.232788,4.360025 },
		{ "El Burro Heights", 1318.160889,-1642.176147,51.787762 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsStores[9] = {
		{ "Banham Canyon", -3037.177246, 590.165283, 7.78449 },
		{ "Chumash", -3237.171387, 1004.163879, 12.354364 },
		{ "Grand Senora Desert", 2683.951172, 3281.507324, 55.347145 },
		{ "Harmony", 543.490784, 2675.008301, 42.162228 },
		{ "Mount Chiliad", 1730.461914, 6410.027344, 35.384476 },
		{ "Sandy Shores", 1966.198853, 3738.300537, 32.251864 },
		{ "Strawberry", 28.123456, -1351.123456, 29.123456 },
		{ "Tataviam Mountains", 2561.452881, 384.998932, 108.532890 },
		{ "Vinewood", 376.287079, 322.833252, 103.418564 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsAmmo[11] = {
		{ "Paleto Bay", -318.859039,6074.433105,30.614943 },
		{ "Sandy Shores", 1704.671997,3748.880615,33.286053 },
		{ "Great Chaparral", -1108.600830,2685.694092,18.177374 },
		{ "Chumash", -3155.888672,1073.844482,20.188726 },
		{ "Palomino Fwy", 2571.371826,313.879608,107.970573 },
		{ "Hawick", 235.666794,-42.263149,69.221313 },
		{ "Morningwood", -1328.592896,-387.114410,36.126881 },
		{ "Little Seoul", -665.232727,-952.522522,20.866556 },
		{ "La Mesa", 844.439026,-1009.422424,27.511728 },
		{ "Pillbox Hill", 17.377790,-1122.183105,28.469843 },
		{ "Cypress Flats", 814.442017,-2130.448486,28.867798 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsBS[6] = {
		{ "Paleto Bay", -286.639038,6239.389648,30.567659 },
		{ "Sandy Shores", 1938.357910,3717.808350,31.607185 },
		{ "Havick", -27.791309,-136.863708,56.515392 },
		{ "Rockford Hills", -829.426392,-191.582718,36.921909 },
		{ "Vespucci", -1294.995239,-1117.641724,6.157444 },
		{ "Mirror Park", 1198.025757,-471.814178,65.670250 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsAirport[7] = {
		{ "Los Santos Airport", -1070.906250,-2972.122803,13.773568 },
		{ "Flight School", -1142.084229,-2697.341553,13.324973 },
		{ "Sandy Shores", 1682.196411,3279.987793,40.647972 },
		{ "McKenzie Airfield", -1682.196411,3279.987793,40.647972 },
		{ "Fort Zancudo", -2446.711182,3142.811035,32.194775 },
		{ "Fort Zancudo Front", -1563.743286,2769.382080,16.819347 },
		{ "LS Airport Hangar", -978.708496,-3001.840820,13.317889 },
	};
}