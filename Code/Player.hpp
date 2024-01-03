#pragma once
#include "Types.hpp"

namespace Big
{
	void PlayerUpdateLoop();

	uintptr_t FindAddy(uintptr_t ptr, std::vector<unsigned int> offsets);

	//Bypass
	inline char g_OriginalWeatherBypass3[4];
	inline bool cool{ false };
	inline bool cool2{ false };
	inline bool cool3{ false };
	inline bool cool4{ false };
	inline bool cool5{ false };
	inline bool cool6{ false };
	inline bool cool7{ false };
	inline bool cool8{ false };
	inline bool cool9{ false };


	inline bool ERR_NET_ARRAY{ true };

	inline bool g_PP{ false};

	inline bool JoinLeave = true;

	inline bool processnetobjprotecc;

	//Noclip
	inline float g_NoClipSpeed{ 2.f };
	inline bool g_NoClip{ false };
	void NoClip(std::size_t type, float speed, bool toggle);
	inline const char* NoclipTypes[2]{ "Classic", "Walking" };
	inline std::size_t NoclipIterator = 0;

	//Particle
	void PTFXCALLBoneless(const char* call1, const char* call2, const char* name, int bone);
	void GlowManager(bool toggle);
	inline bool m_Head{ false };
	inline bool m_RightHand{ false };
	inline bool m_LeftHand{ false };
	inline bool m_RightFood{ false };
	inline bool m_LeftFood{ false };
	inline bool m_EnableGlow{ false };
	inline float m_GlowScale{ 0.1f };
	inline std::array<const char*, 7> m_Particle = { "Lines", "Alien", "Alien2", "Clown", "Lightning", "Ghost", "Electric" };
	inline std::array<const char*, 7> m_ParticleCalls0 = { "scr_rcpaparazzo1", "scr_rcbarry1", "scr_rcbarry1", "scr_rcbarry2", "scr_rcbarry2", "scr_agencyheist", "scr_agencyheistb" };
	inline std::array<const char*, 7> m_ParticleCalls1 = { "scr_mich4_firework_sparkle_spawn", "scr_alien_disintegrate", "scr_alien_teleport", "scr_clown_appears", "scr_clown_death", "scr_fbi_dd_breach_smoke", "scr_agency3b_elec_box" };
	inline std::size_t m_ParticleIterator{ 0 };

	//Animations
	inline std::array<const char*, 6> m_Animations = { "Cheerful", "Stripper Dance", "Source", "Receiver", "Twerk", "On Fire" };
	inline std::array<const char*, 6> m_Dict = { "amb@world_human_cheering@female_a", "mini@strip_club@pole_dance@pole_dance1", "rcmpaparazzo_2", "rcmpaparazzo_2", "switch@trevor@mocks_lapdance", "ragdoll@human" };
	inline std::array<const char*, 6> m_Anims = { "base", "pd_dance_01", "shag_loop_a", "shag_loop_poppy", "001443_01_trvs_28_idle_stripper", "on_fire" };
	inline std::size_t m_Anim = 0;
	inline bool m_Controllable{ false };
	inline bool m_Contort{ false };
	void Animation();
	void doAnimation(const char* anim, const char* animid);

	//Clipset
	inline std::array<const char*, 29> m_Styles = { "Generic (Male)", "Generic (Female)", "Cop", "Gangster", "Hipster", "Hobo", "Fat", "Lester", "Drunk", "Sexy", "Alien", "Business", "Casual", "Clipboard", "Coward", "On Fire", "Fleeing", "Hiking", "Hurried", "Injured", "Intimidating", "Muscle", "Quick", "Sad", "Shady", "Shocked", "Arrogant", "Hand bag", "Heels" };
	inline std::array<const char*, 29> m_StyleId = { "move_m@generic" ,"move_f@generic","move_cop@action","move_m@gangster@generic", "move_m@hipster@a" ,"move_m@hobo@a","move_m@fat@a","move_lester_CaneUp","move_m@drunk@a", "move_m@drunk@moderatedrunk","move_m@drunk@verydrunk","move_f@sexy@a","move_m@alien", "move_m@business@a","move_m@casual@a",	"move_m@clipboard","move_m@coward","move_m@fire", "move_m@flee@a","move_m@hiking","move_m@hurry@a","move_injured_generic","move_m@intimidation@1h", "move_m@muscle@a", "move_m@quick", "move_m@sad@a","move_m@shadyped@a","move_m@shocked@a", "move_f@arrogant@a" };

	void Handtrails(bool toggle);
	inline float handred{ 255.f };
	inline float handgreen{ 0.f };
	inline float handblue{ 0.f };
	inline float handalpha{ 255.f };
	inline float handscale{ 0.5f };
	inline bool m_Handtrails{ false };
	void Handtrails(bool toggle);

	//Proofs
	inline bool m_Bulleproof{ false };
	inline bool m_FireProof{ false };
	inline bool m_ExplosionsProof{ false };
	inline bool m_MeleeProof{ false };
	inline bool m_DrownProof{ false };
	inline bool m_CollisionProof{ false };
	void Proofs(bool bulletproof, bool fireproof, bool explosionproof, bool collisionproof, bool meleeproof, bool drownproof);

	//Outfits
	inline std::array<const char*, 12> m_ComponentIdList{ "Nothing", "Mask", "Hair", "Gloves", "Pants", "Bags", "Shoes", "Accessories", "Shirts", "Bulletproof Vests", "Emblems", "Jackets" };
	void SetPlayerVariation(int componentId, int drawableId, int textureId, int paletteId);
	void ResetPedVariation();
	void RandomizePedVariation();
	void CreateOutfitFile();
	void LoadOutfitd(std::string name);
	inline int m_ComponentId{ 0 };
	inline int m_DrawableId{ 0 };
	inline int m_TextureId{ 0 };
	inline int m_PaletteId{ 0 };
	inline std::size_t m_ClothIterator{ 0 };
	inline int s0{ 0 }, s1{ 0 }, s2{ 0 }, s3{ 0 }, a0{ 0 }, a1{ 0 }, a2{ 0 }, a3{ 0 }, b0{ 0 }, b1{ 0 }, b2{ 0 }, b3{ 0 }, c0{ 0 }, c1{ 0 }, c2{ 0 }, c3{ 0 }, d0{ 0 }, d1{ 0 }, d2{ 0 }, d3{ 0 }, e0{ 0 }, e1{ 0 }, e2{ 0 }, e3{ 0 }, f0{ 0 }, f1{ 0 }, f2{ 0 }, f3{ 0 }, g0{ 0 }, g1{ 0 }, g2{ 0 }, g3{ 0 }, h0{ 0 }, h1{ 0 }, h2{ 0 }, h3{ 0 }, i0{ 0 }, i1{ 0 }, i2{ 0 }, i3{ 0 }, j0{ 0 }, j1{ 0 }, j2{ 0 }, j3{ 0 }, k0{ 0 }, k1{ 0 }, k2{ 0 }, k3{ 0 }, l0{ 0 }, l1{ 0 }, l2{ 0 }, l3{ 0 };

	//Basic
	inline bool g_TeleportHotkey{ false };
	inline bool g_NoClipHotkey{ false };
	inline int g_WantedLevel{ 0 };
	inline bool g_NightVision{ false };
	inline bool g_EmulatePolice{ false };
	inline bool g_Pedspullover{ false };
	inline bool g_ThermalVision{ false };
	inline bool g_Invincible{ true };
	inline bool g_NeverWanted{ true };
	inline bool g_NoRagdoll{ true };
	inline bool g_AlwaysRagdoll{ false };
	inline bool g_DieOnRagdoll{ false };
	inline bool g_Invisible{ false };
	inline bool g_Fly{ false };
	inline bool g_Forcefield{ false };
	inline bool g_Superjump{ false };
	inline bool g_WalkUnderWater{ false };
	inline float g_Height{ 1.f };
	inline float g_Width{ 1.f };
	inline int g_Alpha{ 255 };
	inline float Saturation{ 1.1f };
	inline float Fog{ 0.00002 };
	inline float Sun{ 0.001 };
	inline float Dimensions{ 0.001 };
	inline float POV{ 0.01745329238f };
	inline float SkyIntensity{ 1.f };
	inline float CloudSomething{ 1.f };
	inline bool g_FastRun{ false };
	inline bool g_FastSwim{ false };
	inline bool g_ReducedCollision{ false };
	inline bool g_NinjaJump{false};
	inline bool g_ModifyWater{false};
	inline bool g_OffRadar{ false };
	inline bool g_RevealedPlayers{ false };
	inline bool g_WalkOnWater{ false };
	inline bool g_Cool{ false };
	inline bool g_SlowMotion{ false };
	inline bool g_DeadEye{ false };
	inline bool g_FootTrails{ false };

	inline float m_AzimuthEastRed{ 0.f };
	inline float m_AzimuthEastGreen{ 0.f };
	inline float m_AzimuthEastBlue{ 0.f };
	inline float m_AzimuthEastIntensity{ 1.f };
	inline float m_AzimuthWestRed{ 0.f };
	inline float m_AzimuthWestGreen{ 0.f };
	inline float m_AzimuthWestBlue{ 0.f };
	inline float m_AzimuthWestIntensity{ 1.f };
	inline float m_AzimuthTransitionRed{ 0.f };
	inline float m_AzimuthTransitionGreen{ 0.f };
	inline float m_AzimuthTransitionBlue{ 0.f };
	inline float m_AzimuthTransitionIntensity{ 1.f };
	inline float m_CloudBaseRed{ 0.f };
	inline float m_CloudBaseGreen{ 0.f };
	inline float m_CloudBaseBlue{ 0.f };
	inline float m_CloudBaseIntensity{ 1.f };
	inline float m_CloudMidRed{ 0.f };
	inline float m_CloudMidGreen{ 0.f };
	inline float m_CloudMidBlue{ 0.f };
	inline float m_CloudMidIntensity{ 1.f };
	inline float m_MoonRed{ 0.f };
	inline float m_MoonGreen{ 0.f };
	inline float m_MoonBlue{ 0.f };
	inline float m_MoonIntensity{ 1.f };
	inline float m_SunRed{ 0.f };
	inline float m_SunGreen{ 0.f };
	inline float m_SunBlue{ 0.f };
	inline float m_SunIntensity{ 1.f };
	inline float m_ZenithRed{ 0.f };
	inline float m_ZenithGreen{ 0.f };
	inline float m_ZenithBlue{ 0.f };
	inline float m_ZenithIntensity{ 1.f };
	inline float m_ZenithTransitionRed{ 0.f };
	inline float m_ZenithTransitionGreen{ 0.f };
	inline float m_ZenithTransitionBlue{ 0.f };
	inline float m_ZenithTransitionIntensity{ 1.f };
	inline float RainstormIntensity{ 1.f };
	inline float RainstormRed{ 0.f };
	inline float RainstormGreen{ 0.f };
	inline float RainstormBlue{ 0.f };
	inline float RainstormGravity{ -12.f };
	inline float RainstormSizeX{ 0.01499999966f };
	inline float RainstormSizeY{ 0.400000006f };
	inline float ThunderIntensity{ 1.f };
	inline float ThunderRed{ 0.f };
	inline float ThunderGreen{ 0.f };
	inline float ThunderBlue{ 0.f };
	inline float ThunderGravity{ -12.f };
	inline float ThunderSizeX{ 0.009999999776f };
	inline float ThunderSizeY{ 0.6000000238f };
	inline float LightSnowIntensity{ 1.f };
	inline float LightSnowRed{ 0.6000000238f };
	inline float LightSnowGreen{ 0.6000000238f };
	inline float LightSnowBlue{ 0.6000000238f };
	inline float LightSnowGravity{ -0.5f };
	inline float LightSnowSizeX{ 0.02500000037f };
	inline float LightSnowSizeY{ 0.02500000037f };
	inline float HeavySnowIntensity{ 1.f };
	inline float HeavySnowRed{ 0.6000000238f };
	inline float HeavySnowGreen{ 0.6000000238f };
	inline float HeavySnowBlue{ 0.6000000238f };
	inline float HeavySnowGravity{ -1.f };
	inline float HeavySnowSizeX{ 0.02500000037f };
	inline float HeavySnowSizeY{ 0.02500000037f };
	inline float BlizzardIntensity{ 1.f };
	inline float BlizzardRed{ 1.f };
	inline float BlizzardGreen{ 1.f };
	inline float BlizzardBlue{ 1.f };
	inline float BlizzardGravity{ -1.f };
	inline float BlizzardSizeX{ 0.02500000037f };
	inline float BlizzardSizeY{ 0.02500000037f };

	inline bool m_RainbowAzimuthEast{ false };
	inline bool m_RainbowAzimuthWest{ false };
	inline bool m_RainbowAzimuthTransition{ false };
	inline bool m_RainbowCloudBase{ false };
	inline bool m_RainbowCloudMid{ false };
	inline bool m_RainbowMoon{ false };
	inline bool m_RainbowSun{ false };
	inline bool m_RainbowZenith{ false };
	inline bool m_RainbowZenithTransition{ false };
	inline const char* SkyColor2[9] = {
		"Azimuth East", "Azimuth West", "Azimuth Transition", "Cloud Base", "Cloud Mid", "Moon", "Sun", "Zenith", "Zenith Transition"
	};
	inline std::size_t _SkyColor2 = 0;

	inline const char* RainColor2[5] = {
	"Rainstorm", "Thunder", "Light Snow", "Heavy Snow", "Blizzard"
	};
	inline std::size_t _RainColor2 = 0;

	inline const char* Display1[2]{ "Enabled", "Disabled" };
	inline std::size_t Displayy1{ 0 };
	inline const char* Display2[2]{ "Enabled", "Disabled" };
	inline std::size_t Displayy2{ 0 };
	inline const char* Display3[2]{ "Enabled", "Disabled" };
	inline std::size_t Displayy3{ 0 };
	inline const char* Display4[2]{ "Enabled", "Disabled" };
	inline std::size_t Displayy4{ 0 };

	inline std::size_t Displayy5{ 0 };
	inline const char* Display5[2]{ "Enabled", "Disabled" };
	inline std::size_t Displayy6{ 0 };
	inline const char* Display6[2]{ "Enabled", "Disabled" };
	inline std::size_t Displayy7{ 0 };
	inline const char* Display7[2]{ "Enabled", "Disabled" };

	inline const char* Syncing[3]{ "Allow", "Restrict", "None" };

	inline bool yesyes1{ false };
	inline bool yesyes2{ false };
	inline bool yesyes3{ false };
	inline bool yesyes4{ true };

	inline uint8_t r = 255, g = 0, b = 0;
	void Patch(BYTE* dst, BYTE* src, unsigned int size);

	void TeleportFunction(Vector3 coords);
	void AzimuthEastColor(float red, float green, float blue);
	void AzimuthEastColorBypass();
	void AzimuthWestColor(float red, float green, float blue);
	void AzimuthWestColorBypass();
	void AzimuthTransitionColor(float red, float green, float blue);
	void AzimuthTransitionColorBypass();
	void CloudBaseColor(float red, float green, float blue);
	void CloudBaseColorBypass();
	void CloudMidColor(float red, float green, float blue);
	void CloudMidColorBypass();
	void MoonColor(float red, float green, float blue);
	void MoonColorBypass();
	void SunColor(float red, float green, float blue);
	void SunColorBypass();
	void ZenithColor(float red, float green, float blue);
	void ZenithColorBypass();
	void ZenithTransitionColor(float red, float green, float blue);
	void ZenithTransitionColorBypass();
	void AzimuthRainbow();
	void RainstormColor(float red, float green, float blue);
	void RainstormVariables();
	void ThunderColor(float red, float green, float blue);
	void ThunderVariables();
	void LightSnowColor(float red, float green, float blue);
	void LightSnowVariables();
	void HeavySnowColor(float red, float green, float blue);
	void HeavySnowVariables();
	void BlizzardColor(float red, float green, float blue);
	void BlizzardVariables();

	void ChangeModel(const char* To_Change);
	void Policemode();
	void Pullover(bool toggle);
	void NoclipHotkey(bool toggle);
	void Invincible(bool toggle);
	void WalkUnderWater(bool toggle);
	void NeverWanted(bool toggle);
	void NoRagodoll(bool toggle);
	void AlwaysRagdoll(bool toggle);
	void DieOnRagdoll(bool toggle);
	void Invisible(bool toggle);
	void Forcefield(bool toggle);
	void Fly(bool toggle);
	void SuperJump(bool toggle);
	void Width();
	void Height();
	void Alpha();
	void FastRun(bool toggle);
	void FastSwim(bool toggle);
	void ReducedCollision(bool toggle);
	void SetWantedLevel(int level);
	void Ninjajump(bool toggle);
	void ModifyWater(bool toggle);
	void OffRadar(bool toggle);
	void RevealPlayers(bool toggle);
	void WalkOnWater(bool toggle);
	void SlowMotion(bool toggle);
	void DeadEye(bool toggle);
}