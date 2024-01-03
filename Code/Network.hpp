#pragma once

enum ScriptEvents
{
	/* NEW ONES */
	PROTECTION_BOUNTY_I = 1915499503,
	PROTECTION_BOUNTY_II = 1294995624,

	PROTECTION_CLAIM_BOUNTY = 2881715287,
	PROTECTION_CEO_BAN = 1240068495,
	PROTECTION_CEO_KICK = -1425016400,
	PROTECTION_CEO_MONEY = 547083265,
	PROTECTION_CLEAR_WANTED = 1449852136,
	PROTECTION_FAKE_DEPOSIT = -1529596656,
	PROTECTION_FORCE_MISSION_I = -283041276,
	PROTECTION_FORCE_MISSION_II = 4011926020,//IDK BUT HOOKING GIVES ME ERROR
	PROTECTION_FORCE_MISSION_III = 360408846,
	PROTECTION_FORCE_MISSION_IIII = 1368055548,
//	PROTECTION_FORCE_MISSION_V = -2926911748,
	PROTECTION_GTA_BANNER_I = 145637109,
	PROTECTION_GTA_BANNER_II = -7642965105622237451,
	PROTECTION_PERSONAL_VEHICLE = -1838276770,
	PROTECTION_OFF_RADAR = -1973627888,
	PROTECTION_ROTATE_CAM = -1388926377,
	PROTECTION_FORCE_CUTSCENE = 2131601101,
	PROTECTION_FORCE_ISLAND = 1361475530,
	PROTECTION_SOUND_SPAM = 1111927333,
	PROTECTION_SPECTATE = -2131157870,
	PROTECTION_FORCE_APARTMENT = -1390976345,
	PROTECTION_TRANSACTION_ERROR = -768108950,
	PROTECTION_VEHICLE_KICK_I = -714268990,
	PROTECTION_VEHICLE_KICK_II = 3580698306,
	PROTECTION_NETWORK_BAIL = 1674887089,
	PROTECTION_FREEZE_I = 1214823473,
	PROTECTION_FREEZE_II = 2130458390,
	PROTECTION_BRIBE = -2095232746,
	PROTECTION_BLOCK_PASSIVE = 65268844,
	PROTECTION_KICK_I = 2071375245,
	PROTECTION_KICK_II = -1991423686,
	PROTECTION_CRASH_I = 526822748,
	PROTECTION_CRASH_II = -555356783,
	PROTECTION_CRASH_III = -637352381,
	PROTECTION_CRASH_IIII = -51486976,
	//PROTECTION_STAND_CRASH_ELEGANT = -2624134500 && 373610513 && -3768144548 && -3799154164,
	PROTECTION_STAND_CRASH_ELEGANT_HASH_II = 373610513,
	//PROTECTION_STAND_CRASH_ELEGANT_HASH_II = -3768144548,
	//PROTECTION_STAND_CRASH_ELEGANT_HASH_II = -3799154164,
	//PROTECTION_NOTIFY = 2765370640,
	//PROTECTION_SEND_TEXT_MESSAGE = -2624134500,
};

inline std::array<std::pair<const char*, std::int32_t>, 51> BunkerResearch
{
	{ {"APC Sam Battery",15381},
	{"Ballistic Equipment",15382},
	{"Half-track 20mm Quad Autocannon",15428},
	{"Weaponized Tampa Dual Remote Minigun",15429},
	{"Weaponized Tampa Rear-Firing Mortar",15430},
	{"Weaponized Tampa Front Missile Launchers",15431},
	{"Weaponized Tampa Heavy Chassis Upgrade",15491},
	{"Dune FAV 40mm Grenade Launcher",15432},
	{"Dune FAV 7.62mm Minigun",15433},
	{"Insurgent Pick-Up Custom .50 Cal Minigun",15434},
	{"Insurgent Pick-Up Custom Heavy Armor Plating",15435},
	{"Technical Custom 7.62mm Minigun",15436},
	{"Technical Custom Ram-bar",15437},
	{"Technical Custom Brute-bar",15438},
	{"Technical Custom Heavy Chassis Upgrade",15439},
	{"Oppressor Missile Launchers",15447},
	{"Fractal Livery Set",15448},
	{"Digital Livery Set",15449},
	{"Geometric Livery Set",15450},
	{"Nature Reserve Livery Set",15451},
	{"Naval Battle Livery Set",15452},
	{"Anti-Aircraft Trailer Dual 20mm Flak",15453},
	{"Anti-Aircraft Trailer Homing Missile Battery",15454},
	{"Mobile Operations Center Rear Turrets",15455},
	{"Incendiary Rounds",15456},
	{"Hollow Point Rounds",15457},
	{"Armor Piercing Rounds",15458},
	{"Full Metal Jacket Rounds",15459},
	{"Explosive Rounds",15460},
	{"Pistol Mk II Mounted Scope",15461},
	{"Pistol Mk II Compensator",15462},
	{"SMG Mk II Holographic Sight",15463},
	{"SMG Mk II Heavy Barrel",15464},
	{"Heavy Sniper Mk II Night Vision Scope",15465},
	{"Heavy Sniper Mk II Thermal Scope",15466},
	{"Heavy Sniper Mk II Heavy Barrel",15467},
	{"Combat MG Mk II Holographic Sight",15468},
	{"Combat MG Mk II Heavy Barrel",15469},
	{"Assault Rifle Mk II Holographic Sight",15470},
	{"Assault Rifle Mk II Heavy Barrel",15471},
	{"Carbine Rifle Mk II Holographic Sight",15472},
	{"Carbine Rifle Mk II Heavy Barrel",15473},
	{"Proximity Mines",15474},
	{"Brushstroke Camo Mk II Weapon Livery",15492},
	{"Skull Mk II Weapon Livery",15493},
	{"Sessanta Nove Mk II Weapon Livery",15494},
	{"Perseus Mk II Weapon Livery",15495},
	{"Leopard Mk II Weapon Livery",15496},
	{"Zebra Mk II Weapon Livery",15497},
	{"Geometric Mk II Weapon Livery",15498},
	{"Boom! Mk II Weapon Livery",15499} }
};

inline std::array<std::pair<const char*, std::int32_t>, 22> CasinoHeistOutfits
{
	{
		{"Refuse Collectors",28225},
		{"Undertakers",28226},
		{"Valet Outfits",28227},
		{"Prision Guards",28229},
		{"FIB Suits",28230},
		{"Gruppe Sechs Gear",28232},
		{"Bugstars Uniforms",28233},
		{"Maintenance",28234},
		{"Yung Ancestors",28235},
		{"Firefighter Gear",28236},
		{"Orderly Armor",28237},
		{"Upscale Armor",28238},
		{"Evening Armor",28239},
		{"Reinforced: Padded Combat",28240},
		{"Reinforced: Bulk Combat",28241},
		{"Reinforced: Compact Combat",28242},
		{"Balaclava Crook",28243},
		{"Classic Crook",28244},
		{"High-end Crook",28245},
		{"Infiltration: Upgraded Tech",28246},
		{"Infiltration: Advanced Tech",28247},
		{"Infiltration: Modernized Tech",28248}
    }
};

inline std::array<std::pair<const char*, std::int32_t>, 139> ArenaWarOutfits
{
	{
		{"Yellow/Blue Robot Bodysuit",25244},
		{"Blue/Red Hero Bodysuit",25245},
		{"Green/Purple Shapes Bodysuit",25246},
		{"Blue&Pink/Red&Green Contours Bodysuit",25247},
		{"Green/Purple Martian Bodysuit",25248},
		{"Blue/Red Reptile Bodysuit",25249},
		{"Blue/Pink Galaxy Bodysuit",25250},
		{"Red&Blue/Blue&Green Nebula Bodysuit",25000},
		{"All Space Creature Suits",25251},
		{"All Space Cyclops Suits",25252},
		{"All Space Horro Suits",25253},
		{"All Retro Suits",25254},
		{"All Astronaut Suits",25255},
		{"All Space Traveler Suits",25256},
		{"Pogo Space Monkey",25257},
		{"Republican Space Ranger",25258},
		{"Green/Yellow/White/Black Space Rangers Tee",25265},
		{"Green/Black Space Ranger Logo Tee",25266},
		{"Yellow/White Phases Tee",25267},
		{"Pink/Blue Rocket Splash Tee",25268},
		{"Pink/Black Spacesuit Alien Tee",24977},
		{"Pink/Blue/Purple Moons Tee",25269},
		{"Red/Green/Blue Isn't Free Tee ",25270},
		{"All Raider Tops",25271},
		{"All Leather Feather Tops",25272},
		{"All Mercenary Tops",25273},
		{"Benedict Light Beer Hoodie",25274},
		{"Taco Bomb Hoodie",25275},
		{"Cluckin'Bell Logo Bomb Hoodie",25276},
		{"Patriot Beer Hoodie",25277},
		{"Pisswasser Hoodie",25278},
		{"Burger Shot Hoodie",25279},
		{"Corn Dog Hoodie",25280},
		{"Donut Hoodie",25281},
		{"Lucky Plucker Hoodie",25282},
		{"Logger Light Hoodie",25283},
		{"Pizza Hoodie",25284},
		{"Fries Hoodie",25285},
		{"Mushrooms Hoodie",25286},
		{"Redwood Hoodie",25287},
		{"eCola Infectious Hoodie",25288},
		{"Cluckin'Bell Logo Hoodie",25289},
		{"Lemons Hoodie",25290},
		{"Tacos Hoodie",25291},
		{"Burger Shot Pattern Sweater",25292},
		{"Burger Shot Logo Sweater",25293},
		{"Burger Shot Sweater",25294},
		{"Green/White Sprunk Sweater",25295},
		{"Wigwam Sweater",25296},
		{"Taco Bomb Chili Sweater",25297},
		{"Green/Yellow Bomb Sweater",25298},
		{"Cluckin'Bell Logo Bomb Sweater",25299},
		{"Blue Cluckin'Bell Sweater",25300},
		{"Black Cluckin'Bell Sweater",25301},
		{"Infectious/Red eCola Sweater",25302},
		{"Orange/Red MeTV Sweater",25303},
		{"Magenta/Cyan Heat Sweater",25304},
		{"Degenatron Sweater",25305},
		{"Red/Black Pisswasser Sweater",25306},
		{"Bolt Burger Sweater",25307},
		{"Lucky Plucker Logo Bomb Sweater",25308},
		{"Lucky Plucker Sweater",25309},
		{"Dark Red/Red/Black/Blue Burger Shot Hockey Shirt",25310},
		{"Black/Blue Cluckin' Bell Hockey Shirt",25311},
		{"Wigwam Hockey Shirt",25312},
		{"Redwood Hockey Shirt",25313},
		{"Bean Machine Hockey Shirt",25314},
		{"Red eCola Hockey Shirt",25315},
		{"Black eCola Hockey Shirt",25316},
		{"Blue/Black Phat Chips Hockey Shirt",25317},
		{"Green/Dark Green Sprunk Hockey Shirt",25318},
		{"Sprunk Classic Hockey Shirt",25319},
		{"Burger Shot Black Tee",25320},
		{"Burger Shot Logo Tee",25321},
		{"Cluckin'Bell Logo Tee",25322},
		{"Cluckin'Bell Black Tee",25323},
		{"Cluckin'Bell Filled Logo Tee",25324},
		{"eCola Black Tee",25325},
		{"Lucky Plucker Tee",25326},
		{"Pisswasser Tee",25327},
		{"Sprunk Tee",25328},
		{"Taco Bomb Chili Tee",25329},
		{"Taco Bomb Black Tee",25330},
		{"Up-n-Atom Hamburgers Tee",25331},
		{"Up-n-Atom Tee",25332},
		{"Wigwam Tee",25333},
		{"Degenatron ROYGBIV Tee",25334},
		{"CNT Tee",25335},
		{"Qub3d Tee",25336},
		{"Righteous Slaughter Tee",25337},
		{"Space Monkey Full Tee",25338},
		{"Space Monkey Pixel Tee",25339},
		{"Space Monkey Enemy Tee",25340},
		{"Burger Shot Tee",25341},
		{"Heat Rises Tee",25342},
		{"Space Monkey Logo Tee",25343},
		{"Space Monkey Suit Tee",25344},
		{"Space Monkey Face Tee",25345},
		{"Space Monkey Mosaic Tee",25346},
		{"Bolt Burger Logo Tee",25347},
		{"Bolt Burger Hunger Tee",24970},
		{"Exsorbeo 720 Tee",25348},
		{"Heat Blue Logo Tee",25349},
		{"Heat Blue Ball Logo Tee",25350},
		{"Heat Blue Pop Art Logo Tee",25351},
		{"MeTV Blue 90s Tee",25352},
		{"MeTV Blue Safari Tee",25353},
		{"Burger Shot Target Tee",25354},
		{"eCola Infectious Tee",25355},
		{"Up-n-Atom White Tee",25356},
		{"Jock Cranley Patriot Tee",25357},
		{"CCC TV Tee",25358},
		{"Degenatron Logo Tee",25359},
		{"eCola White Tee",25360},
		{"eCola Pass It On Tee",25361},
		{"TW@ Tee",25362},
		{"All Chain Pants",25363},
		{"All Chain Shorts",25364},
		{"All Stitch Pants",25365},
		{"All Raider Pants",25366},
		{"All Raider Boots",25366},
		{"All Light Ups",25367},
		{"All Flaming Skull Boots",25368},
		{"All Skull Harness Boots",25369},
		{"All Plated Boots",25370},
		{"Burger Shot Fries/Burgers Cap",25371},
		{"Burger Shot Logo Cap",25373},
		{"Burger Shot Bullseye Cap",25374},
		{"Yellow/Blue Cluckin'Bell Cap",25375},
		{"Cluckin'Bell Logos Cap",25377},
		{"Pink/Purple/Black Hotdogs Cap",25378},
		{"Green/White/- Taco Bomb Cap",25379},
		{"Red/White Lucky Plucker Cap",25382},
		{"Lucky Plucker White/Red Pattern Cap",25383},
		{"Black/White Pisswasser Cap",25386},
		{"Taco Canvas Hat",25390},
		{"Burger Shot Canvas Hat",25391},
		{"Cluckin'Bell Canvas Hat",25392},
		{"Hotdogs Canvas Hat",25393}
	}
};


namespace Big
{
	//RID
	inline const char* g_RIDArray[4]{ "Join", "Spectate", "View Profile", "Friend Request" };
	inline std::uint32_t g_RIDHash{ 0xDA4858C1 };
	inline std::size_t g_RIDIndex{0};
	inline bool g_ShowRIDWindow{false}; 

	void shittycrash();

	//Protections
	inline bool g_BlockChat{ true };
	inline bool g_EnableChatCommands{ false };
	inline bool g_EnableChatCommandsWeapons{ false };
	inline bool g_EnableChatCommandsSpawn{ false };
	inline std::vector<std::string> m_JoinPlayers;

	inline bool p_PROTECTION_BOUNTY{ true };
	inline bool p_PROTECTION_CLAIM_BOUNTY{ true };
	inline bool p_PROTECTION_CEO_BAN{ true };
	inline bool p_PROTECTION_CEO_KICK{ true };
	inline bool p_PROTECTION_CEO_MONEY{ true };
	inline bool p_PROTECTION_CLEAR_WANTED{ true };
	inline bool p_PROTECTION_FAKE_DEPOSIT{ true };
	inline bool p_PROTECTION_FORCE_MISSION{ true };
	inline bool p_PROTECTION_GTA_BANNER{ false };
	inline bool p_PROTECTION_PERSONAL_VEHICLE{ true };
	inline bool p_PROTECTION_OFF_RADAR{ true };
	inline bool p_PROTECTION_ROTATE_CAM{ false };
	inline bool p_PROTECTION_FORCE_CUTSCENE{ true };
	inline bool p_PROTECTION_FORCE_ISLAND{ true };
	inline bool p_PROTECTION_SOUND_SPAM{ true };
	inline bool p_PROTECTION_SPECTATE{ true };
	inline bool p_PROTECTION_FORCE_APARTMENT{ true };
	inline bool p_PROTECTION_TRANSACTION_ERROR{ true };
	inline bool p_PROTECTION_VEHICLE_KICK{ true };
	inline bool p_PROTECTION_NETWORK_BAIL{ true };
	inline bool p_PROTECTION_FREEZE{ true };
	inline bool p_PROTECTION_BRIBE{ true };
	inline bool p_PROTECTION_BLOCK_PASSIVE{ true };
	inline bool p_PROTECTION_KICK{ true };
	inline bool p_PROTECTION_CRASH{ true };
	inline bool p_PROTECTION_NOTIFY{ true };

	inline bool p_NOTIFY_EVENTS{ true };

	inline bool g_RemoveWeapons{ false };
	inline bool g_Give_Weapons{ false };
	inline bool g_SoundEvent{ false };
	inline bool g_WantedLevelProtectiom{ false };
	inline bool g_Explosions{ false };
	inline bool g_Fire{ false };
	inline bool g_ClearPedTasks{ true };
	inline bool g_PTFX{ false };
	inline bool g_RequestPickup{ true };
	inline bool g_VoteKick{ true };
	inline bool g_RequestControl{ true };
	inline bool g_BlockReports{ true };
	inline bool g_DesyncKick{ true };

	inline bool g_BlockJoining{ false };
	inline bool g_TransactionError{ false };
	inline bool g_OtherProtections{ false };
	inline bool g_CloneProtections{ true };

	inline bool g_CargoPlanes{ false };
	inline bool g_Cage{ true };
	inline bool g_InvalidModels{ true };
	inline bool g_BlockPickup{ true };
	inline bool g_BlockInvalidObjects{ true };


	inline int g_SyncProtection;

	void DesyncProtection(bool toggle);

	void DuplaicateVehicle(std::int32_t player);

	//Basic
	inline bool g_Fps{ true };
	inline bool g_FreeSlots{ true };
	inline bool g_Position{ true };
	inline bool g_BypassChat{ false };
	inline bool g_BypassMap{ false };

	inline bool do_clone_crash[32] = { false };
	inline uint64_t clone_crash_entity[32] = { 0 };

	void CloneCrash();
	void BlockChat(bool toggle);

	void NetworkUpdateLoop();
	inline bool yuhisfat{ false };
	void Peepe(bool toggle);
	bool Command(std::string& str, std::string check);
	void SpawnVehicleCommandFunction(const char* toSpawn, std::int32_t player);
	bool is_player_in_interior(Player player);
	bool is_player_friend(Player player);
	Entity get_raycast_entity();
	bool is_ped_aiming(Ped ped);
	float distanceBetween(NativeVector3 A, NativeVector3 B);

	inline int t = 0;
	inline int dHeight = 0;
	inline int dx, dy, dz = 0;

	inline int dAmount = 2500;
	inline int dDelay = 100;
	inline bool dEnable;

	void moneyDrop(bool enable, int amount, int delay, int xPlus, int yPlus, int zPlus, int Height);

	inline const char* Objects[33] = {

	 "prop_consign_01a", "prop_cheetah_covered", "ind_prop_dlc_roller_car_02","prop_map_door_01", "prop_sign_road_06r", "prop_homeles_shelter_01","prop_gravestones_10a", "prop_wheelchair_01", "prop_coffin_02b", "prop_cs_protest_sign_01",
	"prop_xmas_ext", "prop_bikini_disp_04", "prop_prlg_snowpile", "p_cs_mp_jet_01_s", "prop_snow_bench_01", "prop_parasol_02_c", "hei_prop_heist_weed_pallet_02",
	"prop_water_corpse_01", "prop_weed_01", "p_spinning_anus_s", "prop_fnclink_02gate1", "prop_container_04mb", "prop_barrel_02b",
	"ind_prop_dlc_flag_01", "p_binbag_01_s", "prop_cheetah_covered", "prop_toolchest_05", "prop_cactus_01a",  "prop_juicestand", "prop_rad_waste_barrel_01", "prop_road_memorial_02"
	"prop_roadpole_01b", "prop_conc_blocks01a", "prop_roadcone01b",
	};
	inline std::size_t ObjectIndex = 0;

	inline const char* Bodyparts[5]{ "Head", "Right Hand", "Left Hand", "Right Foot", "Left Food" };
	inline const int Bodypartsint[5]{ 0x796e, 0xdead, 0x8cbd, 0xcc4d, 0x3779 };
	void FuckFuckFuck(int modelindex, int bodypartindex);
	inline std::vector<std::int32_t> ent;
	inline std::size_t BodyIndex = 0;
	void FuckFuckFuckFuckFuckFuck();

	void IDontCare1();
	void IDontCare2();
	void IDontCare3();
	void IDontCare4();
	void IDontCare5();
	void PeopleBuyingMenusForPlayerThigsAreBeyondRetardedFuckThemHonestly();
	void pedinfo(std::int32_t player, bool show);
	void HostQueue();
	void NetworkMakeVehicleInvisible();
	void NetworkHostKick();
	void NetworkCageThisNigger();
	void NetworkForceJob(bool lobby);
	void NetworkCeoBan(bool lobby);
	void NetworkCeoKick(bool lobby);
	void NetworkRotateCam(bool lobby);
	void NetworkGtaBanner(bool lobby);
	void NetworkVehicleKick(bool lobby);
	void NetworkBlockPassive(bool lobby);
	void NetworkForceJob2(bool lobby);
	void NetworkDestroyPrivateVehicle(bool lobby);
	void NetworkForceJob3(bool lobby);
	void NetworkTransactionError(bool lobby);
	void NetworkInfinityLoad(bool lobby);
	void NetworkFreezePlayer(bool lobby);
	void NetworkClaimBounty(bool lobby);
	void NetworkNeverWanted(bool lobby);
	void NetworkOffRadar(bool lobby);
	void AIOCrash();
	void NetworkDestroyTank();
	void NetworkKillPlayer();
	void NetworkDesyncKick();
	void TeleportToPlayer();
	void RamPlayer();
	void TazePlayer();
	void NetworkExplodePlayer();


	inline std::size_t SessionTypeIndex = 0;
	inline std::array<const char*, 8> SessionTypes = { "Public Session", "New Public Session", "Solo Session", "Invite Only", "Friend Session", "Closed Friend Session", "Crew Session", "Closed Crew Session" };
	void FindSession(int sessiontype);

	inline bool dropthemrpmyg[32];
	void DropRP(bool toggle, std::int32_t ped);

	void NetworkUpdateYuhsObeseStatus();
	void ForceHostOfScript();
	struct Playerss
	{
		std::vector<std::int32_t> RPDrop{};
		std::vector<std::int32_t> PlayerIndex{};
	}; inline Playerss g_Players;


	void IncreaseStamina();
	void IncreaseStrength();
	void InceaseLoungh();
	void IncreaseDriving();
	void IncreaseFly();
	void IncreaseShooting();
	void IncreaseStealth();
	void UnlimitedSnacks();
	void RedesignCharacter();
	void DamagePlayer();


	void PackedStatBoolResearch(int index);
	void PackedStatBoolCasinoHeistOutfits(int index);
	void PackedStatBoolArenaWar(int index);
	void CloneProtections();


	struct DropTemplate
	{
		bool Activated{};
		std::uint32_t PickupHash{};
			
		int Delay{};
		int Amount{};
		int Timer{};

		float x{};
		float y{};
		float z{};
	};


	inline std::vector<DropTemplate> g_Drops{};
	inline std::string g_SelectedDropLabel{};
	inline int SelectedDrop{};

	void DropMgr();

	inline bool g_AngryPlanesEnable{ false };
	inline bool g_AngryPlanesRockets{false};

	//Text Color
	inline const char* ColorNameColors[] = {
		"Default", "~r~Red", "~b~Blue", "~g~Green", "~y~Yellow", "~p~Purple", "~q~Pink", "~o~Orange", "~c~Grey", "~m~Darker Grey", "~u~Black"// "~h~Bold"
	};
	inline const char* NameColors[] = {
		"", "~r~", "~b~", "~g~", "~y~", "~p~", "~q~", "~o~", "~c~", "~m~", "~u~"
	};
	inline std::size_t _Namecolors = 0;



	class angry_planes
	{

	public:

		void tick();
		void cleanup();

		float spawn_range = 400.f;
		NativeVector3 player_coords{};

		int max_planes_to_spawn = 15;

	private:

		std::vector<uint32_t> m_plane_hashes
		{
			0x2F03547B,
			0x31F0B376,
			0x46699F47,
			0xAD6065C0,
			0x64DE07A1,
			0x39D6E83F,
			0xB39B0AE6,
			0x64DE07A1,
			0xC5DD6967
		};

		struct plane
		{
			int id;
			int ped;
		};

		std::vector<plane> m_spawned_planes{};
		Ped player_ped{};
		bool initialized{};
		uint32_t enemy_hash{};

		void initialize_variables(Ped ped, NativeVector3 coords, uint32_t enemy_hash);
		Ped create_enemy(uint32_t hash, NativeVector3 coords);
		Vehicle spawn_plane(uint32_t hash);
		void check_for_alive_planes();
		void spawn_planes();
	};

	inline angry_planes g_angry_planes;
}

/*namespace Big
{
	void CeoBan(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { 1240068495, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { 1240068495, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << g_SelectedPlayer);
		}
	}
}*/