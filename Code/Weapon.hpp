#pragma once

namespace Big
{
	//Frame flags
	enum eFrameFlags : std::uint32_t
	{
		eFrameFlagExplosiveAmmo = 1 << 11,
		eFrameFlagFireAmmo = 1 << 12,
		eFrameFlagExplosiveMelee = 1 << 13,
		eFrameFlagSuperJump = 1 << 14,
	};

	//Explosive
	inline std::array<const char*, 39> m_Explosion = { "Grenade", "GrenadeL", "Sticky Bomb", "Molotov", "Rocket", "Tank Shell", "Hi Octane", "Car", "Plane", "Petrol Pump", "Bike", "Steam", "Flame", "Water Hydrant", "Gas Canister", "Boat", "Ship", "Truck", "Bullet", "SmokeG", "SmokeGL", "BZ Gas", "Flare", "Gas Canister2", "Extinguisher", "ProgramAR", "Train", "Barrel", "Propane", "Blimp", "Exploding Flame", "Tanker", "Plane Rocket", "Vehicle Bullet", "Gas Tank", "Firework", "Snowball", "Proximity Mine", "Valkyrie" };
	inline std::size_t m_Explosion_Iterator;
	inline bool m_EnableExplosives{ false };
	inline float m_Damage{ 0.f };
	inline float m_CameraShake{ 0.f };
	inline bool  m_Invisible{ false };
	inline bool  m_Audiable{ false };
	inline bool  m_DamageDisable{ false };

	//GravityGun
	inline std::vector<std::int32_t> GravityGunDatabase{};
	inline float g_PullPushStrength{ 1.5f };
	inline float g_Velocity{ 1.5f };
	inline int m_GravityGunEntityCount{ 1 };
	inline float g_Force{ 5.f };
	inline bool g_GravityGun{ false };
	void GravityBug(bool toggle);
	inline float GravityGunGoto(float aimX, float entityX)
	{
		static float GravityGunVeloPos;
		if (aimX > 0 && entityX > 0)
		{
			GravityGunVeloPos = aimX - (entityX);
		}

		if (aimX < 0 && entityX < 0)
		{
			GravityGunVeloPos = aimX - (entityX);
		}

		if (aimX > 0 && entityX < 0)
		{
			GravityGunVeloPos = aimX + (entityX);
		}

		if (aimX < 0 && entityX > 0)
		{
			GravityGunVeloPos = aimX + (entityX);
		}

		return GravityGunVeloPos;
	}
	inline std::array<const char*, 4> m_Entity = { "Vehicle", "Object", "Pickup", "Propellant" };
	inline std::array<const char*, 10>m_EntityVehicle = { "Adder", "Oppressor", "Rhino", "Insurgent", "Scramjet",  "T20", "Taipan", "Tempesta", "Tezeract", "Turismor", };
	inline std::array<const char*, 10>m_EntityObject = { "p_spinning_anus_s", "prop_pipes_conc_02", "prop_barier_conc_03a", "prop_logpile_07b", "prop_asteroid_01",  "prop_tool_shovel2", "prop_prop_tree_01", "prop_conslift_cage", "prop_bush_lrg_01e_cr", "prop_aircon_t_03", };
	inline std::array<const char*, 4> m_Pickup = { "Vehicle", "Object", "Pickup", "Propellant" };
	inline std::array<const char*, 3> m_PickupType = { "Money", "Armour", "Health" };
	inline std::array<const char*, 9> m_PickupModel = { "Bag", "Alien Egg", "X-Mas Tree","Dildo", "Safe","Med Bag", "Gun Case", "Guitar" "Bag", "Golfbag" };
	inline std::array<const char*, 4> m_PropellantText = { "Firework", "Railgun", "RPG", "Up-n-Atomizer" };
	inline std::array<int, 9> m_HashModels = { -1666779307, 1803116220, 238789712, -422877666, -1251197000, 1368637848, 1213275131, -708789241, 886428669 };
	inline std::array<std::uint32_t, 3> m_HashPickups = { 0x1E9A99F8, 0x4BFB42D1, 0x8F707C18 };
	inline std::array<std::uint32_t, 4> m_PropellantHashes = { 0x7F7497E5, 0x6D544C99, 0xB1CA77B1, 0xAF3696A1 };

	inline std::size_t m_EntityPickupTypeIterator;
	inline std::size_t m_EntityPickupModelIterator;
	inline std::size_t m_EntityIterator;
	inline std::size_t m_EntityVehicleIterator;
	inline std::size_t m_EntityObjectIterator;
	inline std::size_t m_EntityPropellantIterator;

	inline std::size_t g_GravityGunIterator;

	//Paint
	inline int m_R{ false };
	inline int m_G{ false };
	inline int m_B{ false };
	inline float m_Range{ 0.1f };
	inline float m_Intensity{ 1000.f };
	inline bool m_EnablePaint{ false };
	inline std::vector<NativeVector3> positions;
	//Basic
	inline bool m_ReviveGun{ false };
	inline bool m_InfiniteAmmo{false};
	inline bool m_ExplosiveAmmo{false};
	inline bool m_RapidFire{false};
	inline bool g_Carnado{ false };
	inline bool m_OneHitAmmo{false};
	inline bool m_LaserSight{false};
	inline bool m_NoRecoil{false};
	inline bool m_GravityGun{false};
	inline bool m_AimBot{false};
	inline bool m_ForceGun{false};
	inline bool m_AirstrikeGun{false};
	inline bool m_TeleportGun{false};
	inline bool m_DeleteGun{false};
	inline bool m_RainbowCamo{false};
	inline bool m_MoneyGun{false};
	inline bool m_RPGun{false};
	inline bool m_FlamingAmmo{false};
	inline bool m_Magnet{ false };
	inline bool g_Rope{ false };

	inline const char* wepattach[] = {
	"Add All", "Remove All"
	};
	inline std::size_t _wepattach = 0;

	inline const char* CrossStyle[2] { "Plus", "Cross" };
	inline std::size_t _CrossStyle{ 0 };
	inline float crosssize{ 6.f };
	inline float redcross{ 255.f};
	inline float greencross{ 0.f};
	inline float bluecross{  0.f };
	inline bool testicalcancer{ false };
	inline std::size_t g_AimbotInterator{0};
	inline const char* AimbotArray[3]{ "None", "Weak", "Heavy" };
	inline bool g_YoinkGun{ false };

	inline int g_RedPaint{ 0 };
	inline int g_BluePaint{ 255 };
	inline int g_GreenPaint{ 0 };

	inline const char* GravityGunStyle[2]{ "Static", "Dynamic" };
	inline std::size_t GravityGunSize{ 0 };

	inline bool LockOnEntity{ false };

	void YoinkGun(bool toggle);
	void Crosshair();
	void Revivegun(bool toggle);
	void InfiniteAmmo(bool toggle);
	void ExplosiveAmmo(bool toggle);
	void RapidFire(bool toggle);
	void OneHitAmmo(bool toggle);
	void LaserSight(bool toggle);
	void NoRecoil(bool toggle);
	void AimBot(bool toggle);
	void ForceGun(bool toggle);
	void AirstrikeGun(bool toggle);
	void TeleportGun(bool toggle);
	void DeleteGun(bool toggle);
	void RainbowCamo(bool toggle);
	void MoneyGun(bool toggle);
	void RPGun(bool toggle);
	void Lasersight(bool toggle);
	void FlamingAmmo(bool toggle);
	void ExplosiveAmmoFunction(bool toggle);
	void TriggerBot(bool enable);
	void GiveWeapons();
	void WeaponUpdateLoop();
	void RopeGun(bool toggle);
	inline bool g_FlyGun{ false };
	void Attachments();
	void Flygun(bool toggle);

	inline LPCSTR AllWeapons[] = {
			"WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR",
			"WEAPON_PISTOL", "WEAPON_COMBATPISTOL","weapon_hatchet", "weapon_battleaxe","weapon_stone_hatchet", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG",
			"WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG",
			"WEAPON_COMBATMG", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
			"WEAPON_STUNGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER_SMOKE",
			"WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
			"WEAPON_MOLOTOV", "WEAPON_FIREEXTINGUISHER", "WEAPON_PETROLCAN",
			"WEAPON_SNSPISTOL", "WEAPON_SPECIALCARBINE", "WEAPON_HEAVYPISTOL", "WEAPON_BULLPUPRIFLE", "WEAPON_HOMINGLAUNCHER",
			"WEAPON_PROXMINE", "WEAPON_SNOWBALL", "WEAPON_VINTAGEPISTOL", "WEAPON_DAGGER", "WEAPON_FIREWORK", "WEAPON_MUSKET",
			"WEAPON_MARKSMANRIFLE", "WEAPON_HEAVYSHOTGUN", "WEAPON_GUSENBERG", "WEAPON_HATCHET", "WEAPON_RAILGUN",
			"WEAPON_COMBATPDW", "WEAPON_KNUCKLE", "WEAPON_MARKSMANPISTOL", "WEAPON_RAYPISTOL", "weapon_ceramicpistol", "weapon_navyrevolver", "weapon_gadgetpistol", "weapon_autoshotgun", "weapon_combatshotgun", "weapon_assaultrifle_mk2",
			"weapon_carbinerifle_mk2", "weapon_specialcarbine_mk2", "weapon_bullpuprifle_mk2", "weapon_compactrifle", "weapon_militaryrifle", "weapon_heavysniper_mk2", "weapon_marksmanrifle_mk2", "weapon_raycarbine", "weapon_minismg",
			"weapon_dbshotgun", "weapon_compactlauncher", "weapon_rayminigun", "weapon_pipebomb", "weapon_flare", "weapon_smokegrenade", "weapon_pistol_mk2", "weapon_snspistol_mk2", "weapon_revolver_mk2", "weapon_combatmg_mk2", "weapon_pumpshotgun_mk2",
			"weapon_machinepistol", "weapon_smg_mk2"
	};

	inline LPCSTR AllAttachments[] = {
		"COMPONENT_PISTOL_CLIP_02", "COMPONENT_AT_PI_FLSH", "COMPONENT_AT_PI_SUPP_02", "COMPONENT_PISTOL_VARMOD_LUXE", "COMPONENT_COMBATPISTOL_CLIP_02", "COMPONENT_AT_PI_FLSH", "COMPONENT_AT_PI_SUPP", "COMPONENT_COMBATPISTOL_VARMOD_LOWRIDER",
		"COMPONENT_APPISTOL_CLIP_02", "COMPONENT_AT_PI_FLSH", "COMPONENT_AT_PI_SUPP", "COMPONENT_APPISTOL_VARMOD_LUXE", "COMPONENT_PISTOL50_CLIP_02", "COMPONENT_AT_PI_FLSH", "COMPONENT_AT_AR_SUPP_02", "COMPONENT_PISTOL50_VARMOD_LUXE",
		"COMPONENT_REVOLVER_VARMOD_GOON", "COMPONENT_SNSPISTOL_CLIP_02", "COMPONENT_SNSPISTOL_VARMOD_LOWRIDER", "COMPONENT_HEAVYPISTOL_CLIP_02", "COMPONENT_AT_PI_FLSH", "COMPONENT_AT_PI_SUPP", "COMPONENT_HEAVYPISTOL_VARMOD_LUXE",
		"COMPONENT_REVOLVER_MK2_CLIP_INCENDIARY", "COMPONENT_AT_SIGHTS", "COMPONENT_AT_PI_FLSH", "COMPONENT_AT_PI_COMP_03", "COMPONENT_REVOLVER_MK2_CAMO_10", "COMPONENT_SNSPISTOL_MK2_CLIP_INCENDIARY", "COMPONENT_AT_PI_FLSH_03", "COMPONENT_AT_PI_RAIL_02",
		"COMPONENT_AT_PI_SUPP_02", "COMPONENT_SNSPISTOL_MK2_CAMO_10", "COMPONENT_PISTOL_MK2_CLIP_INCENDIARY", "COMPONENT_AT_PI_RAIL", "COMPONENT_AT_PI_FLSH_02", "COMPONENT_AT_PI_SUPP_02", "COMPONENT_PISTOL_MK2_CAMO_10", "COMPONENT_VINTAGEPISTOL_CLIP_02",
		"COMPONENT_AT_PI_SUPP", "COMPONENT_RAYPISTOL_VARMOD_XMAS18", "COMPONENT_CERAMICPISTOL_CLIP_02", "COMPONENT_CERAMICPISTOL_SUPP",

		"COMPONENT_MICROSMG_CLIP_02","COMPONENT_AT_PI_FLSH","COMPONENT_AT_SCOPE_MACRO","COMPONENT_AT_AR_SUPP_02","COMPONENT_MICROSMG_VARMOD_LUXE","COMPONENT_SMG_CLIP_03","COMPONENT_AT_AR_FLSH","COMPONENT_AT_SCOPE_MACRO_02","COMPONENT_AT_PI_SUPP",
		"COMPONENT_SMG_VARMOD_LUXE","COMPONENT_ASSAULTSMG_CLIP_02","COMPONENT_AT_AR_FLSH","COMPONENT_AT_SCOPE_MACRO","COMPONENT_AT_AR_SUPP_02","COMPONENT_ASSAULTSMG_VARMOD_LOWRIDER","COMPONENT_MINISMG_CLIP_02","COMPONENT_SMG_MK2_CLIP_02",
		"COMPONENT_SMG_MK2_CLIP_INCENDIARY","COMPONENT_AT_AR_FLSH","COMPONENT_AT_SIGHTS_SMG","COMPONENT_AT_MUZZLE_05","COMPONENT_AT_SB_BARREL_02","COMPONENT_SMG_MK2_CAMO_10","COMPONENT_MACHINEPISTOL_CLIP_03","COMPONENT_AT_PI_SUPP",
		"COMPONENT_COMBATPDW_CLIP_03","COMPONENT_AT_AR_FLSH","COMPONENT_AT_AR_AFGRIP","COMPONENT_AT_SCOPE_SMALL",

		"COMPONENT_AT_AR_FLSH","COMPONENT_AT_SR_SUPP","COMPONENT_PUMPSHOTGUN_VARMOD_LOWRIDER","COMPONENT_SAWNOFFSHOTGUN_VARMOD_LUXE","COMPONENT_ASSAULTSHOTGUN_CLIP_02","COMPONENT_AT_AR_FLSH","COMPONENT_AT_AR_SUPP","COMPONENT_AT_AR_AFGRIP",
		"COMPONENT_AT_AR_FLSH","COMPONENT_AT_AR_SUPP_02","COMPONENT_AT_AR_AFGRIP","COMPONENT_PUMPSHOTGUN_MK2_CLIP_INCENDIARY","COMPONENT_AT_SIGHTS","COMPONENT_AT_AR_FLSH","COMPONENT_AT_SR_SUPP_03","COMPONENT_PUMPSHOTGUN_MK2_CAMO_10",
		"COMPONENT_HEAVYSHOTGUN_CLIP_03","COMPONENT_AT_AR_FLSH","COMPONENT_AT_AR_SUPP_02","COMPONENT_AT_AR_FLSH","COMPONENT_AT_AR_SUPP",

		"COMPONENT_ASSAULTRIFLE_CLIP_03","COMPONENT_AT_AR_FLSH","COMPONENT_AT_SCOPE_MACRO","COMPONENT_AT_AR_SUPP_02","COMPONENT_AT_AR_AFGRIP","COMPONENT_ASSAULTRIFLE_VARMOD_LUXE","COMPONENT_CARBINERIFLE_CLIP_03","COMPONENT_AT_AR_FLSH",
		"COMPONENT_AT_SCOPE_MEDIUM","COMPONENT_AT_AR_SUPP","COMPONENT_AT_AR_AFGRIP","COMPONENT_CARBINERIFLE_VARMOD_LUXE","COMPONENT_ADVANCEDRIFLE_CLIP_02","COMPONENT_AT_AR_FLSH","COMPONENT_AT_SCOPE_SMALL","COMPONENT_AT_AR_SUPP",
		"COMPONENT_ADVANCEDRIFLE_VARMOD_LUXE","COMPONENT_SPECIALCARBINE_CLIP_03","COMPONENT_AT_AR_FLSH","COMPONENT_AT_SCOPE_MEDIUM","COMPONENT_AT_AR_SUPP_02","COMPONENT_AT_AR_AFGRIP","COMPONENT_SPECIALCARBINE_VARMOD_LOWRIDER",
		"COMPONENT_BULLPUPRIFLE_CLIP_02","COMPONENT_AT_AR_FLSH","COMPONENT_AT_SCOPE_SMALL","COMPONENT_AT_AR_SUPP","COMPONENT_AT_AR_AFGRIP","COMPONENT_BULLPUPRIFLE_VARMOD_LOW","COMPONENT_BULLPUPRIFLE_MK2_CLIP_02","COMPONENT_BULLPUPRIFLE_MK2_CLIP_INCENDIARY",
		"COMPONENT_AT_AR_FLSH","COMPONENT_AT_SIGHTS","COMPONENT_AT_BP_BARREL_02","COMPONENT_AT_MUZZLE_05","COMPONENT_AT_AR_AFGRIP_02","COMPONENT_BULLPUPRIFLE_MK2_CAMO_10","COMPONENT_SPECIALCARBINE_MK2_CLIP_02","COMPONENT_SPECIALCARBINE_MK2_CLIP_INCENDIARY",
		"COMPONENT_AT_AR_FLSH","COMPONENT_AT_SIGHTS","COMPONENT_AT_MUZZLE_05","COMPONENT_AT_AR_AFGRIP_02","COMPONENT_AT_SC_BARREL_02","COMPONENT_SPECIALCARBINE_MK2_CAMO_10","COMPONENT_ASSAULTRIFLE_MK2_CLIP_02","COMPONENT_ASSAULTRIFLE_MK2_CLIP_INCENDIARY"
		,"COMPONENT_AT_AR_AFGRIP_02","COMPONENT_AT_AR_FLSH","COMPONENT_AT_SIGHTS","COMPONENT_AT_MUZZLE_05","COMPONENT_AT_AR_BARREL_02","COMPONENT_ASSAULTRIFLE_MK2_CAMO_10","COMPONENT_CARBINERIFLE_MK2_CLIP_02","COMPONENT_CARBINERIFLE_MK2_CLIP_INCENDIARY"
		,"COMPONENT_AT_AR_AFGRIP_02","COMPONENT_AT_AR_FLSH","COMPONENT_AT_SIGHTS","COMPONENT_AT_MUZZLE_05","COMPONENT_AT_CR_BARREL_02","COMPONENT_CARBINERIFLE_MK2_CAMO_10","COMPONENT_COMPACTRIFLE_CLIP_03","COMPONENT_MILITARYRIFLE_CLIP_02",
		"COMPONENT_AT_SCOPE_SMALL","COMPONENT_AT_AR_FLSH","COMPONENT_AT_AR_SUPP",

		"COMPONENT_MG_CLIP_02","COMPONENT_AT_SCOPE_SMALL_02","COMPONENT_MG_VARMOD_LOWRIDER","COMPONENT_COMBATMG_CLIP_02","COMPONENT_AT_SCOPE_MEDIUM","COMPONENT_AT_AR_AFGRIP","COMPONENT_COMBATMG_VARMOD_LOWRIDER","COMPONENT_COMBATMG_MK2_CLIP_02",
		"COMPONENT_COMBATMG_MK2_CLIP_INCENDIARY","COMPONENT_AT_AR_AFGRIP_02","COMPONENT_AT_SIGHTS","COMPONENT_AT_MUZZLE_05","COMPONENT_AT_MG_BARREL_02","COMPONENT_COMBATMG_MK2_CAMO_10","COMPONENT_GUSENBERG_CLIP_02",

		"COMPONENT_AT_AR_SUPP_02","COMPONENT_AT_SCOPE_MAX","COMPONENT_SNIPERRIFLE_VARMOD_LUXE","COMPONENT_AT_SCOPE_MAX","COMPONENT_MARKSMANRIFLE_MK2_CLIP_02","COMPONENT_MARKSMANRIFLE_MK2_CLIP_INCENDIARY","COMPONENT_AT_SCOPE_LARGE_FIXED_ZOOM_MK2",
		"COMPONENT_AT_AR_FLSH","COMPONENT_AT_MUZZLE_05","COMPONENT_AT_MRFL_BARREL_02","COMPONENT_AT_AR_AFGRIP_02","COMPONENT_MARKSMANRIFLE_MK2_CAMO_10","COMPONENT_HEAVYSNIPER_MK2_CLIP_02","COMPONENT_HEAVYSNIPER_MK2_CLIP_INCENDIARY",
		"COMPONENT_AT_SCOPE_THERMAL","COMPONENT_AT_MUZZLE_09","COMPONENT_AT_SR_BARREL_02","COMPONENT_HEAVYSNIPER_MK2_CAMO_10","COMPONENT_MARKSMANRIFLE_CLIP_02","COMPONENT_AT_SCOPE_LARGE_FIXED_ZOOM","COMPONENT_AT_AR_FLSH",
		"COMPONENT_AT_AR_SUPP","COMPONENT_AT_AR_AFGRIP","COMPONENT_MARKSMANRIFLE_VARMOD_LUXE",

		"COMPONENT_AT_AR_FLSH","COMPONENT_AT_AR_AFGRIP","COMPONENT_AT_SCOPE_SMALL"

	};

	void EnityGunVehicle(bool toggle, const char* SelectedVehicle, float SpawnDistance, float LaunchSpeed);
	void EntityGunObject(bool toggle, const char* SelectedObject, float SpawnDistance, float LaunchSpeed);
	void PickupGun(bool toggle, std::uint32_t Model, std::uint32_t Pickup, int Value);
	void PropellantGun(bool toggle, float SpawnDistance, std::uint32_t Model, float Speed);

	
}

enum eBone
{
	SKEL_ROOT = 0x0,
	SKEL_Pelvis = 0x2e28,
	SKEL_L_Thigh = 0xe39f,
	SKEL_L_Calf = 0xf9bb,
	SKEL_L_Foot = 0x3779,
	SKEL_L_Toe0 = 0x83c,
	IK_L_Foot = 0xfedd,
	PH_L_Foot = 0xe175,
	MH_L_Knee = 0xb3fe,
	SKEL_R_Thigh = 0xca72,
	SKEL_R_Calf = 0x9000,
	SKEL_R_Foot = 0xCC4D,
	SKEL_R_Toe0 = 0x512d,
	IK_R_Foot = 0x8aae,
	PH_R_Foot = 0x60e6,
	MH_R_Knee = 0x3fcf,
	RB_L_ThighRoll = 0x5c57,
	RB_R_ThighRoll = 0x192a,
	SKEL_Spine_Root = 0xe0fd,
	SKEL_Spine0 = 0x5c01,
	SKEL_Spine1 = 0x60f0,
	SKEL_Spine2 = 0x60f1,
	SKEL_Spine3 = 0x60f2,
	SKEL_L_Clavicle = 0xfcd9,
	SKEL_L_UpperArm = 0xb1c5,
	SKEL_L_Forearm = 0xeeeb,
	SKEL_L_Hand = 0x49d9,
	SKEL_L_Finger00 = 0x67f2,
	SKEL_L_Finger01 = 0xff9,
	SKEL_L_Finger02 = 0xffa,
	SKEL_L_Finger10 = 0x67f3,
	SKEL_L_Finger11 = 0x1049,
	SKEL_L_Finger12 = 0x104a,
	SKEL_L_Finger20 = 0x67f4,
	SKEL_L_Finger21 = 0x1059,
	SKEL_L_Finger22 = 0x105a,
	SKEL_L_Finger30 = 0x67f5,
	SKEL_L_Finger31 = 0x1029,
	SKEL_L_Finger32 = 0x102a,
	SKEL_L_Finger40 = 0x67f6,
	SKEL_L_Finger41 = 0x1039,
	SKEL_L_Finger42 = 0x103a,
	PH_L_Hand = 0xeb95,
	IK_L_Hand = 0x8cbd,
	RB_L_ForeArmRoll = 0xee4f,
	RB_L_ArmRoll = 0x1470,
	MH_L_Elbow = 0x58b7,
	SKEL_R_Clavicle = 0x29d2,
	SKEL_R_UpperArm = 0x9d4d,
	SKEL_R_Forearm = 0x6e5c,
	SKEL_R_Hand = 0xdead,
	SKEL_R_Finger00 = 0xe5f2,
	SKEL_R_Finger01 = 0xfa10,
	SKEL_R_Finger02 = 0xfa11,
	SKEL_R_Finger10 = 0xe5f3,
	SKEL_R_Finger11 = 0xfa60,
	SKEL_R_Finger12 = 0xfa61,
	SKEL_R_Finger20 = 0xe5f4,
	SKEL_R_Finger21 = 0xfa70,
	SKEL_R_Finger22 = 0xfa71,
	SKEL_R_Finger30 = 0xe5f5,
	SKEL_R_Finger31 = 0xfa40,
	SKEL_R_Finger32 = 0xfa41,
	SKEL_R_Finger40 = 0xe5f6,
	SKEL_R_Finger41 = 0xfa50,
	SKEL_R_Finger42 = 0xfa51,
	PH_R_Hand = 0x6f06,
	IK_R_Hand = 0x188e,
	RB_R_ForeArmRoll = 0xab22,
	RB_R_ArmRoll = 0x90ff,
	MH_R_Elbow = 0xbb0,
	SKEL_Neck_1 = 0x9995,
	SKEL_Head = 0x796e,
	IK_Head = 0x322c,
	FACIAL_facialRoot = 0xfe2c,
	FB_L_Brow_Out_000 = 0xe3db,
	FB_L_Lid_Upper_000 = 0xb2b6,
	FB_L_Eye_000 = 0x62ac,
	FB_L_CheekBone_000 = 0x542e,
	FB_L_Lip_Corner_000 = 0x74ac,
	FB_R_Lid_Upper_000 = 0xaa10,
	FB_R_Eye_000 = 0x6b52,
	FB_R_CheekBone_000 = 0x4b88,
	FB_R_Brow_Out_000 = 0x54c,
	FB_R_Lip_Corner_000 = 0x2ba6,
	FB_Brow_Centre_000 = 0x9149,
	FB_UpperLipRoot_000 = 0x4ed2,
	FB_UpperLip_000 = 0xf18f,
	FB_L_Lip_Top_000 = 0x4f37,
	FB_R_Lip_Top_000 = 0x4537,
	FB_Jaw_000 = 0xb4a0,
	FB_LowerLipRoot_000 = 0x4324,
	FB_LowerLip_000 = 0x508f,
	FB_L_Lip_Bot_000 = 0xb93b,
	FB_R_Lip_Bot_000 = 0xc33b,
	FB_Tongue_000 = 0xb987,
	RB_Neck_1 = 0x8b93,
	IK_Root = 0xdd1c
};