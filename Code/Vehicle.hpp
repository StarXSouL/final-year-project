
namespace Big
{
	//Hornboost
	inline bool m_AudioBoost{ false };
	inline float m_SpeedBoost{ 2.f };
	inline bool m_BoostEffect{ false };
	inline bool m_Hornboost{ false };
	void Hornboost(bool toggle);
	
	//Particles
	inline bool m_EnableGlowVehicle{ false };
	inline bool m_RightFrontWheel{ false };
	inline bool m_LeftFrontWheel{ false };
	inline bool m_RightBackWheel{ false };
	inline bool m_LeftBackWheel{ false };
	inline float m_GlowScale0{ 0.2f };
	void CustomWheelPTFX(const char* streamName, const char* PTFXName, const char* wheel);
	void GlowManager0(bool toggle);
	inline std::array<const char*, 6> m_Particle0 = { "Alien", "Alien2", "Clown", "Lightning", "Ghost", "Electric" };
	inline std::array<const char*, 6> m_ParticleCalls00 = { "scr_rcbarry1", "scr_rcbarry1", "scr_rcbarry2", "scr_rcbarry2", "scr_agencyheist", "scr_agencyheistb" };
	inline std::array<const char*, 6> m_ParticleCalls10 = { "scr_alien_disintegrate", "scr_alien_teleport", "scr_clown_appears", "scr_clown_death", "scr_fbi_dd_breach_smoke", "scr_agency3b_elec_box" };
	inline std::size_t m_ParticleIterator0{ 0 };

	//Weapons
	inline std::array<const char*, 3> VehicleWeapons = { "Rocket", "Explosive", "Red Light" };
	inline std::array<std::uint32_t, 3> VehicleWeaponHashes = { -1090665087, 0xE2822A29, 0x5D6660AB };
	inline std::size_t VehicleWeaponIterator{ 0 };
	inline int g_WeaponDelay{1000};
	inline bool g_VehicleWeapons{ false };
	inline bool g_Lasersight{ false };
	inline float g_WeaponSpeed{ 250.f };

	//Basic
	inline const char* Ability[3]{ "Off", "Boost", "Jump"};
	inline std::size_t AbilityIterator{ 0 };
	inline std::array<const char*, 3> g_Jump = { "Off", "Tap", "Hold" };
	inline std::size_t g_JumpIterator{0};
	inline std::size_t RainbowIterator{ 0 };
	inline std::array<const char*, 3> g_RainbowText = { "Off", "Smooth", "Rapid" };
	inline bool g_VehicleFly{ false };
	inline float g_FlySpeed{ 130.f };
	inline bool g_Collision{ true };
	inline bool g_BypassSpeed{ true };
	inline bool g_rvc{ false };
	inline bool g_Parachute{ false };
	inline bool g_InvincibleVehicle{ false };
	inline bool g_InvisibleVehicle{ false };
	inline bool g_SpawnInVeh{ false };
	inline bool g_SpawnInvinc{ false };
	inline bool g_SpawnMaxed{ false };
	inline bool g_AddToList{ false };
	inline bool g_Autoflip{ false };
	inline bool g_Autofix{ false };
	inline bool g_Seatbelt{ false };
	inline bool g_Driftmode{ false };
	inline bool g_SkipEnterAnimation{ false };
	inline bool g_Scorched{ false };
	inline bool g_DriveUnderWater{ false };
	inline bool g_ForceToGround{ false };
	inline bool g_GlitchVehicle{ false };
	inline bool g_ThreeSixty{false};
	inline bool g_RainbowVehicle{false};
	inline bool g_EngineAlwaysOn{ false };
	inline bool g_DriveOnWater{ false };
	inline bool g_RepairVehHotkey{ false };
	inline bool g_VehicleFlyHotkey{ false };
	inline bool g_VehicleSpawnByName{ false };
	inline int FadeR{ 255 }, FadeG{ 0 }, FadeB{0};

	inline int  m_PickupValue{ 2500 };
	inline int  m_PickupMaxInt{ 2500 };
	inline int  m_SelectorValue{ 0 };

	inline float m_VehicleSpawnDistance{ 10.f };
	inline float m_VehicleLaunchSpeed{ 500.f };
	inline float m_ObjectSpawnDistance{ 10.f };
	inline float m_ObjectLaunchSpeed{ 500.f };
	inline float m_ObjectPropellantSpeed{ 500.f };
	inline float m_PropellantSpawnDistance{ 10.f };

	inline bool m_EnableEntityGunVehicle{false};
	inline bool m_EnableEntityGunObject{false};
	inline bool m_EnableEntityGunPickups{false};
	inline bool m_EnableEntityPropellant{false};
	inline bool m_EnableEntityPedestrians{false};
	inline bool g_ContainerRider{ false };

	inline bool g_EnableTrails{ false };
	inline bool g_RGBTrails{ false };
	inline int g_TrailsRed{ 255 };
	inline int g_TrailsBlue{ 0 };
	inline int g_TrailsGreen{ 0 };

	inline bool g_BetterGrip{ false };

	void RVC(bool toggle);
	void DuplicateVehicle(std::int32_t player);
	void FixVehicle();
	void VehicleFlyHotkey(bool toggle);
	void RepairVehHotkey(bool toggle);
	void vehicle_acrobatics(int type);
	void VehicleRamp(bool front, bool back, bool left, bool right);
	void BetterGrip(bool toggle);
	void VehicleInvincible(bool toggle);
	void Driftmode(bool toggle);
	void AutoFlip(bool toggle);
	void VehicleFly(bool toggle, float speed);
	void Seatbelt(bool toggle);
	void Autofix();
	void MaxVehicle();
	void DisplayVehicle(std::string texture1, std::string texture2);
	void SpawnVehicle(uint32_t model);
	void DriveUnderWater(bool toggle);
	void ForceVehicleToGround(bool toggle);
	void GlitchVehicle(bool toggle);
	void ThreeSixtyVehicle(bool toggle);
	void EngineAlwaysOn(bool toggle);
	void DriveOnWater(bool toggle);
	void ContainerRider();
	void VehicleUpdateLoop();
	void SpawnVehicle2(uint32_t model);
}