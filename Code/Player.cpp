#include "Common.hpp"
#include "MainScript.hpp"
#include "ScriptCallback.hpp"
static int Animflag{};

namespace Big
{
	static uintptr_t ModuleBaseAdress = (uintptr_t)GetModuleHandle(NULL);

	uintptr_t FindAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
	{
		uintptr_t addr = ptr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			addr = *(uintptr_t*)addr;
			addr += offsets[i];
		}
		return addr;
	}

	void Patch(BYTE* dst, BYTE* src, unsigned int size)
	{
		DWORD oldprotect;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
		memcpy(dst, src, size);
		VirtualProtect(dst, size, oldprotect, &oldprotect);
	}

	void Nop(BYTE* dst, unsigned int size)
	{
		DWORD oldprotect;
		VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
		memset(dst, 0x90, size);
		VirtualProtect(dst, size, oldprotect, &oldprotect);
	}

	
	void AzimuthEastColorWeatherBypass(bool toggle)
	{
		if (toggle)
		{
			std::fill_n(g_GameFunctions->m_WeatherBypass, 4, '\x90');
		}
		else
		{
			std::copy_n("\x0F\x29\x62\x20", 4, g_GameFunctions->m_WeatherBypass);
		}
	}

	void AzimuthWestColorWeatherBypass(bool toggle)
	{
		if (toggle)
		{
			std::fill_n(g_GameFunctions->m_WeatherBypass2, 7, '\x90'); //0F 14 E3 0F 29 62 50
		}
		else
		{
			std::copy_n("\x0F\x14\xE3\x0F\x29\x62\x50", 7, g_GameFunctions->m_WeatherBypass2);
		}
	}

	void AzimuthTransitionColorWeatherBypass(bool toggle)
	{

		if (toggle)
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE400BD), (BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
		}
		else
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE400BD), (BYTE*)"\x0F\x29\xA2\x80\x00\x00\00", 7);
		}
	}

	void CloudBaseMinusMidColor(bool toggle)
	{

		if (toggle)
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE35B0D), (BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
		}
		else
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE35B0D), (BYTE*)"\x0F\x29\x8B\x60\x03\x00\x00", 7);
		}
	}

	void CloudMidColor(bool toggle)
	{

		if (toggle)
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE4047D), (BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
		}
		else
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE4047D), (BYTE*)"\x0F\x29\xA2\x80\x03\x00\x00", 7);
		}
	}

	void MoonColor(bool toggle)
	{

		if (toggle)
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE40387), (BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
		}
		else
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE40387), (BYTE*)"\x0F\x29\x82\x50\x05\x00\x00", 7);
		}
	}

	void SunColor(bool toggle)
	{

		if (toggle)
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE4027D), (BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
		}
		else
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE4027D), (BYTE*)"\x0F\x29\x82\xC0\x01\x00\x00", 7);
		}
	}

	void ZenithColor(bool toggle)
	{

		if (toggle)
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE40103), (BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
		}
		else
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE40103), (BYTE*)"\x0F\x29\xA2\xB0\x00\x00\x00", 7);
		}
	}

	void ZenithTransition(bool toggle)
	{

		if (toggle)
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE4013D), (BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
		}
		else
		{
			Patch((BYTE*)(ModuleBaseAdress + 0xE4013D), (BYTE*)"\x0F\x29\xA2\xE0\00\x00\x00", 7);
		}
	}

	void AzimuthEastColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26CFAB0, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_0 + 0x8;

		*(float*)ptr_0 = (red / 255.f) * m_AzimuthEastIntensity;
		*(float*)ptr_1 = (green / 255.f) * m_AzimuthEastIntensity;
		*(float*)ptr_2 = (blue / 255.f) * m_AzimuthEastIntensity;
	}
	void AzimuthEastColorBypass()
	{
		std::fill_n(g_GameFunctions->m_WeatherBypass, 4, '\x90');
	}

	void AzimuthWestColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26CFAE0, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_0 + 0x8;

		*(float*)ptr_0 = (red / 255.f) * m_AzimuthWestIntensity;
		*(float*)ptr_1 = (green / 255.f) * m_AzimuthWestIntensity;
		*(float*)ptr_2 = (blue / 255.f) * m_AzimuthWestIntensity;
	}
	void AzimuthWestColorBypass()
	{
		std::fill_n(g_GameFunctions->m_WeatherBypass2, 7, '\x90');
	}

	void AzimuthTransitionColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26CFB10, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_0 + 0x8;

		*(float*)ptr_0 = (red / 255.f) * m_AzimuthTransitionIntensity;
		*(float*)ptr_1 = (green / 255.f) * m_AzimuthTransitionIntensity;
		*(float*)ptr_2 = (blue / 255.f) * m_AzimuthTransitionIntensity;
	}
	void AzimuthTransitionColorBypass()
	{
		//Patch((BYTE*)(ModuleBaseAdress + 0xE3AE11), (BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
		std::fill_n(g_GameFunctions->m_WeatherBypass5, 7, '\x90');
	}

	void CloudBaseColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26CFDF0, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_0 + 0x8;

		*(float*)ptr_0 = (red / 255.f) * m_CloudBaseIntensity;
		*(float*)ptr_1 = (green / 255.f) * m_CloudBaseIntensity;
		*(float*)ptr_2 = (blue / 255.f) * m_CloudBaseIntensity;
	}
	void CloudBaseColorBypass()
	{
		std::fill_n(g_GameFunctions->m_WeatherBypass6, 7, '\x90');
	}

	void CloudMidColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26CFE10, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_0 + 0x8;

		*(float*)ptr_0 = (red / 255.f) * m_CloudMidIntensity;
		*(float*)ptr_1 = (green / 255.f) * m_CloudMidIntensity;
		*(float*)ptr_2 = (blue / 255.f) * m_CloudMidIntensity;
	}
	void CloudMidColorBypass()
	{
		std::fill_n(g_GameFunctions->m_WeatherBypass7, 7, '\x90');
	}

	void MoonColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26CFFE0, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_0 + 0x8;

		*(float*)ptr_0 = (red / 255.f) * m_MoonIntensity;
		*(float*)ptr_1 = (green / 255.f) * m_MoonIntensity;
		*(float*)ptr_2 = (blue / 255.f) * m_MoonIntensity;
	}
	void MoonColorBypass()
	{
		//Patch((BYTE*)(ModuleBaseAdress + 0xE3B0DB), (BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
		std::fill_n(g_GameFunctions->m_WeatherBypass3, 7, '\x90');
	}

	void SunColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26CFC50, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_0 + 0x8;

		*(float*)ptr_0 = (red / 255.f) * m_SunIntensity;
		*(float*)ptr_1 = (green / 255.f) * m_SunIntensity;
		*(float*)ptr_2 = (blue / 255.f) * m_SunIntensity;
	}
	void SunColorBypass()
	{
		//Patch((BYTE*)(ModuleBaseAdress + 0xE3AFD1), (BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
		std::fill_n(g_GameFunctions->m_WeatherBypass4, 7, '\x90');
	}

	void ZenithColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26CFB40, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_0 + 0x8;

		*(float*)ptr_0 = (red / 255.f) * m_ZenithIntensity;
		*(float*)ptr_1 = (green / 255.f) * m_ZenithIntensity;
		*(float*)ptr_2 = (blue / 255.f) * m_ZenithIntensity;
	}
	void ZenithColorBypass()
	{
		std::fill_n(g_GameFunctions->m_WeatherBypass8, 7, '\x90');
	}

	void ZenithTransitionColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26CFB70, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_0 + 0x8;

		*(float*)ptr_0 = (red / 255.f) * m_ZenithTransitionIntensity;
		*(float*)ptr_1 = (green / 255.f) * m_ZenithTransitionIntensity;
		*(float*)ptr_2 = (blue / 255.f) * m_ZenithTransitionIntensity;
	}
	void ZenithTransitionColorBypass() 
	{
		std::fill_n(g_GameFunctions->m_WeatherBypass9, 7, '\x90');
	}

	void RainstormColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26FA3A0, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_1 + 0x4;

		*(float*)ptr_0 = (red / 255.f) * RainstormIntensity;
		*(float*)ptr_1 = (green / 255.f) * RainstormIntensity;
		*(float*)ptr_2 = (blue / 255.f) * RainstormIntensity;
	}

	void RainstormVariables()
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26FA2DC, {}); //Difference of C4
		static uintptr_t ptr_1 = FindAddy(ModuleBaseAdress + 0x26FA390, {}); //Difference of 10
		static uintptr_t ptr_2 = ptr_1 + 0x4;

		*(float*)ptr_0 = RainstormGravity;
		*(float*)ptr_1 = RainstormSizeX;
		*(float*)ptr_2 = RainstormSizeY;
	}

	void ThunderColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26FA500, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_1 + 0x4;

		*(float*)ptr_0 = (red / 255.f) * ThunderIntensity;
		*(float*)ptr_1 = (green / 255.f) * ThunderIntensity;
		*(float*)ptr_2 = (blue / 255.f) * ThunderIntensity;
	}

	void ThunderVariables()
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26FA43C, {});
		static uintptr_t ptr_1 = FindAddy(ModuleBaseAdress + 0x26FA4F0, {});
		static uintptr_t ptr_2 = ptr_1 + 0x4;

		*(float*)ptr_0 = ThunderGravity;
		*(float*)ptr_1 = ThunderSizeX;
		*(float*)ptr_2 = ThunderSizeY;
	}

	void LightSnowColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26FA660, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_1 + 0x4;

		*(float*)ptr_0 = (red / 255.f) * LightSnowIntensity;
		*(float*)ptr_1 = (green / 255.f) * LightSnowIntensity;
		*(float*)ptr_2 = (blue / 255.f) * LightSnowIntensity;
	}

	void LightSnowVariables()
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26FA59C, {});
		static uintptr_t ptr_1 = FindAddy(ModuleBaseAdress + 0x26FA650, {});
		static uintptr_t ptr_2 = ptr_1 + 0x4;

		*(float*)ptr_0 = LightSnowGravity;
		*(float*)ptr_1 = LightSnowSizeX;
		*(float*)ptr_2 = LightSnowSizeY;
	}

	void HeavySnowColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26FA7C0, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_1 + 0x4;

		*(float*)ptr_0 = (red / 255.f) * HeavySnowIntensity;
		*(float*)ptr_1 = (green / 255.f) * HeavySnowIntensity;
		*(float*)ptr_2 = (blue / 255.f) * HeavySnowIntensity;
	}

	void HeavySnowVariables()
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26FA6FC, {});
		static uintptr_t ptr_1 = FindAddy(ModuleBaseAdress + 0x26FA7B0, {});
		static uintptr_t ptr_2 = ptr_1 + 0x4;

		*(float*)ptr_0 = HeavySnowGravity;
		*(float*)ptr_1 = HeavySnowSizeX;
		*(float*)ptr_2 = HeavySnowSizeY;
	}

	void BlizzardColor(float red, float green, float blue)
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26FA920, {});
		static uintptr_t ptr_1 = ptr_0 + 0x4;
		static uintptr_t ptr_2 = ptr_1 + 0x4;

		*(float*)ptr_0 = (red / 255.f) * BlizzardIntensity;
		*(float*)ptr_1 = (green / 255.f) * BlizzardIntensity;
		*(float*)ptr_2 = (blue / 255.f) * BlizzardIntensity;
	}

	void BlizzardVariables()
	{
		static uintptr_t ptr_0 = FindAddy(ModuleBaseAdress + 0x26FA85C, {});
		static uintptr_t ptr_1 = FindAddy(ModuleBaseAdress + 0x26FA910, {});
		static uintptr_t ptr_2 = ptr_1 + 0x4;

		*(float*)ptr_0 = BlizzardGravity;
		*(float*)ptr_1 = BlizzardSizeX;
		*(float*)ptr_2 = BlizzardSizeY;
	}


	void Rainbow2()
	{
		if (r > 0 && b == 0) {
			r--;
			g++;
		}
		if (g > 0 && r == 0) {
			g--;
			b++;
		}
		if (b > 0 && g == 0) {
			r++;
			b--;
		}
	}
	void AzimuthRainbow()
	{
		
		if (m_RainbowAzimuthEast)
		{
			AzimuthEastColor(r, g, b);
			m_AzimuthEastRed = r;
			m_AzimuthEastGreen = g;
			m_AzimuthEastBlue = b;
		}
		if (m_RainbowAzimuthWest)
		{
			AzimuthWestColor(r, g, b);
			m_AzimuthWestRed = r;
			m_AzimuthWestGreen = g;
			m_AzimuthWestBlue = b;
		}
		if (m_RainbowAzimuthTransition)
		{
			AzimuthTransitionColor(r, g, b);
			m_AzimuthTransitionRed = r;
			m_AzimuthTransitionGreen = g;
			m_AzimuthTransitionBlue = b;
		}
		if (m_RainbowCloudBase)
		{
			CloudBaseColor(r, g, b);
			m_CloudBaseRed = r;
			m_CloudBaseGreen = g;
			m_CloudBaseBlue = b;
		}
		if (m_RainbowCloudMid)
		{
			CloudMidColor(r, g, b);
			m_CloudMidRed = r;
			m_CloudMidGreen = g;
			m_CloudMidBlue = b;
		}
		if (m_RainbowMoon)
		{
			MoonColor(r, g, b);
			m_MoonRed = r;
			m_MoonGreen = g;
			m_MoonBlue = b;
		}
		if (m_RainbowSun)
		{
			SunColor(r, g, b);
			m_SunRed = r;
			m_SunGreen = g;
			m_SunBlue = b;
		}
		if (m_RainbowZenith)
		{
			ZenithColor(r, g, b);
			m_ZenithRed = r;
			m_ZenithGreen = g;
			m_ZenithBlue = b;
		}
		if (m_RainbowZenithTransition)
		{
			ZenithTransitionColor(r, g, b);
			m_ZenithTransitionRed = r;
			m_ZenithTransitionGreen = g;
			m_ZenithTransitionBlue = b;
		}
		
	}

	void NoClip(std::size_t type, float speed, bool toggle)
	{
		if (toggle)
		{
			auto ped = PLAYER::PLAYER_PED_ID();
			NativeVector3 gameplay_cam_coord{ CAM::GET_GAMEPLAY_CAM_COORD() };
			NativeVector3 entity_coords{ ENTITY::GET_ENTITY_COORDS(ped, true) };
			auto startDist = std::distance(&gameplay_cam_coord, &entity_coords);
			auto pos = ENTITY::GET_ENTITY_COORDS(ped, false);

			switch (type)
			{
			case 0:
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, pos.x, pos.y, pos.z, false, false, false);

				if (GetAsyncKeyState(0x53) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) //s
				{
					if (IsKeyPressed(VK_LSHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21))
						startDist -= 3.0;
					if (IsKeyPressed(VK_SPACE) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 22))
						startDist += .5;

					startDist -= speed;
					startDist -= .3f;
					NativeVector3 coords = g_Utility->AddV3(ENTITY::GET_ENTITY_COORDS(ped, 1), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDist));

					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, false, false, false);
				}
				if (GetAsyncKeyState(0x57) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269)) //w
				{
					if (IsKeyPressed(VK_LSHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21))
						startDist += 3.0;
					if (IsKeyPressed(VK_SPACE) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 22))
						startDist -= .5;

					startDist += speed;
					startDist += 1.f;
					NativeVector3 coords = g_Utility->AddV3(ENTITY::GET_ENTITY_COORDS(ped, 1), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDist));

					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, false, false, false);
				}

				break;
			case 1:
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, pos.x, pos.y, pos.z, true, true, true);

				if (GetAsyncKeyState(0x53) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) //s
				{
					if (IsKeyPressed(VK_LSHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21))
						startDist -= 3.0;
					if (IsKeyPressed(VK_SPACE) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 22))
						startDist += .5;

					startDist -= speed;
					startDist -= .3f;
					NativeVector3 coords = g_Utility->AddV3(ENTITY::GET_ENTITY_COORDS(ped, 1), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDist));

					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, true, true, true);
				}
				if (GetAsyncKeyState(0x57) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269)) //w
				{
					if (IsKeyPressed(VK_LSHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21))
						startDist += 3.0;
					if (IsKeyPressed(VK_SPACE) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 22))
						startDist -= .5;

					startDist += speed;
					startDist += 1.f;
					NativeVector3 coords = g_Utility->AddV3(ENTITY::GET_ENTITY_COORDS(ped, 1), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDist));

					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, true, true, true);
				}
				break;
			}
		}
	}

	void Invincible(bool toggle)
	{
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), toggle);
	}
		
	void NeverWanted(bool toggle)
	{
		if (toggle)
		{
			PLAYER::SET_MAX_WANTED_LEVEL(6);
			PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, 0);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
			g_WantedLevel = 0;
		}
	}

	void Handtrails(bool toggle)
	{
		if (toggle)
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_mich4_firework_sparkle_spawn", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, SKEL_L_Hand, handscale, false, false, false);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(handred / 255, handgreen / 255, handblue / 255);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(handalpha / 255);

			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcpaparazzo1");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("scr_mich4_firework_sparkle_spawn", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, SKEL_R_Hand, handscale, false, false, false);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(handred / 255, handgreen / 255, handblue / 255);
			GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(handalpha / 255);
		}
	}

	void NoRagodoll(bool toggle)
	{
		if (toggle)
		{
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), false);
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
		}
		else
		{
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), true);
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), true);
		}
	}

	void AlwaysRagdoll(bool toggle)
	{
		if (toggle)
		{
			PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), true);
		}
		else
		{
			PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), false);
		}
	}

	void DieOnRagdoll(bool toggle)
	{
		if (toggle)
		{
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 33, true);
		}
		else
		{
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 33, false);
		}
	}

	void Invisible(bool toggle)
	{
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			if (toggle)
			{
				ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, 0);
			}
			else ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, 0);
		}

	}

	void Fly(bool toggle)
	{
		if (toggle)
		{
			g_NoRagdoll = true;
			Hash hash = MISC::GET_HASH_KEY("GADGET_PARACHUTE");

			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 1, 1);
			PED::SET_PED_TO_RAGDOLL_WITH_FALL(PLAYER::PLAYER_PED_ID(), 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);

			if (ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID()) && !PED::IS_PED_RAGDOLL(PLAYER::PLAYER_PED_ID()))
			{
				if (GetAsyncKeyState(VK_SHIFT))
				{
					ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 0, 6, 0);
				}
				if (GetAsyncKeyState(0x53))
				{
					ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 0, -6, 0);
				}
				if (GetAsyncKeyState(VK_SPACE))
				{
					ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 0, 0, 6);
				}
			}
		}
	}

	void Forcefield(bool toggle)
	{
		if (toggle)
		{
			g_Invincible = false;
			NativeVector3 pCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
			FIRE::ADD_EXPLOSION(pCoords.x + 1, pCoords.y + 1, pCoords.z, 7, 9.0f, false, true, 0.0f, true);
			FIRE::ADD_EXPLOSION(pCoords.x + 2, pCoords.y + 2, pCoords.z, 7, 9.0f, false, true, 0.0f, true);
			FIRE::ADD_EXPLOSION(pCoords.x + 3, pCoords.y + 3, pCoords.z, 7, 9.0f, false, true, 0.0f, true);
			FIRE::ADD_EXPLOSION(pCoords.x + 4, pCoords.y + 4, pCoords.z, 7, 9.0f, false, true, 0.0f, true);
			FIRE::ADD_EXPLOSION(pCoords.x + 5, pCoords.y + 5, pCoords.z, 7, 9.0f, false, true, 0.0f, true);
			FIRE::ADD_EXPLOSION(pCoords.x + 6, pCoords.y + 6, pCoords.z, 7, 9.0f, false, true, 0.0f, true);
			FIRE::ADD_EXPLOSION(pCoords.x + 7, pCoords.y + 7, pCoords.z, 7, 9.0f, false, true, 0.0f, true);

			auto ped = PLAYER::PLAYER_PED_ID();
			NativeVector3 gameplay_cam_coord{ CAM::GET_GAMEPLAY_CAM_COORD() }; 
			NativeVector3 entity_coords{ ENTITY::GET_ENTITY_COORDS(ped, true) };
			auto startDist = std::distance(&gameplay_cam_coord, &entity_coords);
			auto pos = ENTITY::GET_ENTITY_COORDS(ped, false);

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, pos.x, pos.y, pos.z, true, true, true);

			if (GetAsyncKeyState(0x53) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) //s
			{
				if (IsKeyPressed(VK_LSHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21))
					startDist -= 3.0;
				if (IsKeyPressed(VK_SPACE) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 22))
					startDist += .5;

				NativeVector3 coords = g_Utility->AddV3(ENTITY::GET_ENTITY_COORDS(ped, 1), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDist));

				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, true, true, true);
			}
			if (GetAsyncKeyState(0x57) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269)) //w
			{
				if (IsKeyPressed(VK_LSHIFT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 21))
					startDist += 3.0;
				if (IsKeyPressed(VK_SPACE) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, 22))
					startDist -= .5;

				startDist += 0.20;
				startDist += 1.f;
				NativeVector3 coords = g_Utility->AddV3(ENTITY::GET_ENTITY_COORDS(ped, 1), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDist));

				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, true, true, true);
			}
		}
	}

	void TeleportFunction(Vector3 coords)
	{
		int Handle = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
		{
			ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), coords.x, coords.y, coords.z, 0, 0, 0, 1);
		}
		else
			ENTITY::SET_ENTITY_COORDS(Handle, coords.x, coords.y, coords.z, 0, 0, 0, 1);
	}

	void SuperJump(bool toggle)
	{
		if (toggle)
		{
			g_NoRagdoll = true;
			g_Utility->WriteFlameFlag(eFrameFlagSuperJump);
		}
	}

	void WalkUnderWater(bool toggle)
	{
		if (toggle)
		{
			auto playerPed = PLAYER::PLAYER_PED_ID();
			if (ENTITY::IS_ENTITY_IN_WATER(playerPed))
			{
				PED::SET_PED_CONFIG_FLAG(playerPed, 65, false);
				PED::SET_PED_CONFIG_FLAG(playerPed, 66, false);
				PED::SET_PED_CONFIG_FLAG(playerPed, 168, false);

				if (PED::IS_PED_JUMPING(playerPed))
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, true, 0, 0, 0.7f, 0, 0, 0, true, true, true, true, false, true);
				}

				if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(playerPed) > 1.2f)
				{
					PED::SET_PED_CONFIG_FLAG(playerPed, 60, false);
					PED::SET_PED_CONFIG_FLAG(playerPed, 61, false);
					PED::SET_PED_CONFIG_FLAG(playerPed, 104, false);
					PED::SET_PED_CONFIG_FLAG(playerPed, 276, false);
					PED::SET_PED_CONFIG_FLAG(playerPed, 76, true);
					ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, true, 0, 0, -0.7f, 0, 0, 0, true, true, true, true, false, true);
				}

				if (BRAIN::GET_IS_TASK_ACTIVE(playerPed, 281) && PED::IS_PED_SWIMMING(playerPed) && PED::IS_PED_SWIMMING_UNDER_WATER(playerPed))
				{
					BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
				}
			}
		}
	}

	void WalkOnWater(bool toggle)
	{
		if (toggle)
		{
			Hash ferris = MISC::GET_HASH_KEY("prop_container_ld2");
			NativeVector3 me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
			float water;
			static int timer = 0;
			static Object model;

			WATER::SET_DEEP_OCEAN_SCALER(-1.f);
			if (WATER::GET_WATER_HEIGHT(me.x, me.y, me.z, &water))
			{
				if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1))
				{
					g_CallbackScript->AddCallback<ModelCallback>(ferris, [=] {
						if (GetTickCount() - timer >= 0)
						{
							model = OBJECT::CREATE_OBJECT(ferris, me.x, me.y, me.z, 1, 1, 1);
							RequestControlOfEnt(model);
							ENTITY::SET_ENTITY_VISIBLE(model, 0, 0);
							ENTITY::FREEZE_ENTITY_POSITION(model, 1);
							ENTITY::SET_ENTITY_ROTATION(model, 0, 0, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 0, 0);
							ENTITY::SET_ENTITY_COORDS(model, me.x, me.y, water - 2.8f, 0, 0, 0, 1);
							timer = GetTickCount();
						}
					});
				}
			}
			if (ENTITY::DOES_ENTITY_EXIST(model))
			{
				RequestControlOfEnt(model);
				OBJECT::DELETE_OBJECT(&model);
			}
		}
		
	}

	void PTFXCALLBoneless(const char* call1, const char* call2, const char* name, int bone)
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET(call1);
		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(call2);
		int ptfx = GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(name, PLAYER::PLAYER_PED_ID(), 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.0f, bone, m_GlowScale, 1, 1, 1);
		STREAMING::REMOVE_PTFX_ASSET();
	}

	void Pullover(bool toggle)
	{
		if (toggle)
		{
			NativeVector3 me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
			const int peds = 10;
			const int _arrSize = peds * 2 + 2;
			int ped[_arrSize];
			ped[0] = peds;
			int _count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), ped, -1);

			const int numElements = 10;
			const int arrSize = numElements * 2 + 2;
			int veh[arrSize];
			veh[0] = numElements;
			int count = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), veh);
			if (veh != NULL && ped != NULL)
			{
				for (int i = 0; i < count; i++) for (int j = 0; j < _count; j++)
				{
					int offsettedID = i * 2 + 2;
					int ID = j * 2 + 2;
					RequestControlOfEnt(veh[offsettedID]);
					RequestControlOfEnt(ped[ID]);
					NativeVector3 mee = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
					NativeVector3 cars = ENTITY::GET_ENTITY_COORDS(veh[offsettedID], 1);
					if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
					{
						BRAIN::TASK_VEHICLE_MISSION(ped[ID], veh[offsettedID], PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 16, 0, 0, 0, 0, 0);
					}
				}
			}
		}
	}

	void GlowManager(bool toggle)
	{
		if (toggle)
		{
			if (m_Head) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0x796e); }
			if (m_RightHand) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0xdead); }
			if (m_LeftHand) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0x8cbd); }
			if (m_RightFood) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0xcc4d); }
			if (m_LeftFood) { PTFXCALLBoneless(m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls0[m_ParticleIterator], m_ParticleCalls1[m_ParticleIterator], 0x3779); }
		}
	}

	void doAnimation(const char* anim, const char* animid)
	{
		int pPlayer = PLAYER::PLAYER_PED_ID();
		STREAMING::REQUEST_ANIM_DICT(anim);
		if (STREAMING::HAS_ANIM_DICT_LOADED((anim)))
		{
			BRAIN::TASK_PLAY_ANIM(pPlayer, anim, animid, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
		}
	}

	void Animation()
	{
		STREAMING::REQUEST_ANIM_DICT(m_Dict[m_Anim]);
		BRAIN::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), m_Dict[m_Anim], m_Anims[m_Anim], 8.f, 8.f, -1, Animflag, 1, 0, 0, 0);
	}

	void Proofs(bool bulletproof, bool fireproof, bool explosionproof, bool collisionproof, bool meleeproof, bool drownproof)
	{
		ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), bulletproof, fireproof, explosionproof, collisionproof, meleeproof, 0, 0, drownproof);
	}

	void SetPlayerVariation(int componentId, int drawableId, int textureId, int paletteId)
	{
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), componentId, drawableId, textureId, paletteId);
	}

	void ResetPedVariation()
	{
		for (int i = 0; i < 12; i++)
		{
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, 0, 0, 0);
		}
	}

	void RandomizePedVariation()
	{
		PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0);
	}

	void CreateOutfitFile()
	{

	}

	void LoadOutfitd(std::string name)
	{

	}

	void Width()
	{
		//Memory::set_value<float>({ 0x8, 0x0064 }, g_Width);
	}
	void Height()
	{
		//Memory::set_value<float>({ 0x8, 0x88 }, g_Height);
	}
	void Alpha()
	{
		ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), g_Alpha, 0);
	}

	void ReducedCollision(bool toggle)
	{
		if (toggle)
			Memory::set_value<float>({ 0x8, 0x30, 0x10, 0x20, 0x70, 0x0, 0x2C }, -1.0);
	}

	void SetWantedLevel(int level)
	{
		PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), level, 0);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
	}

	void Ninjajump(bool toggle)
	{		
		if (toggle)
		{
			static int flip;
			MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
			if (PED::IS_PED_JUMPING(PLAYER::PLAYER_PED_ID()))
			{
				if (ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID()))
				{
					flip -= 10;
					ENTITY::SET_ENTITY_ROTATION(PLAYER::PLAYER_PED_ID(), flip, 0, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 0, 0);
				}
			}
		}
	}

	void ModifyWater(bool toggle)
	{
		if (toggle)
		{
			NativeVector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			WATER::MODIFY_WATER(Coords.x, Coords.y, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 2, Coords.y, -10, 10);
			WATER::MODIFY_WATER(Coords.x, Coords.y + 2, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 2, Coords.y + 2, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 4, Coords.y, -10, 10);
			WATER::MODIFY_WATER(Coords.x, Coords.y + 4, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 4, Coords.y + 4, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 6, Coords.y, -10, 10);
			WATER::MODIFY_WATER(Coords.x, Coords.y + 6, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 6, Coords.y + 6, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 8, Coords.y, -10, 10);
			WATER::MODIFY_WATER(Coords.x, Coords.y + 8, -10, 10);
			WATER::MODIFY_WATER(Coords.x + 8, Coords.y + 8, -10, 10);
		}
	}

	void OffRadar(bool toggle)
	{
		if (toggle)
		{
			*script_global(2657704).at(PLAYER::PLAYER_ID(), 463).at(210).as<bool*>() = 1;
			*script_global(2672524).at(57).as<int32_t*>() = NETWORK::GET_NETWORK_TIME();
		}
	}

	void NoclipHotkey(bool toggle)
	{
		if (toggle)
		{
			if (GetAsyncKeyState(VK_F6) & 1)
			{
				g_NoClip = !g_NoClip;
			}
		}
	}

	void ChangeModel(const char* To_Change)
	{
		Hash Model_To_Change = MISC::GET_HASH_KEY(To_Change);
		STREAMING::REQUEST_MODEL(Model_To_Change);
		{
			NativeVector3 Coordinates = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			Coordinates.x + 2;
			if (STREAMING::IS_MODEL_IN_CDIMAGE(Model_To_Change))
			{
				g_FiberScript->addTask([=] {
					if (STREAMING::IS_MODEL_VALID(Model_To_Change))
					{
						Ped PED_Spawn = PED::CREATE_PED(26, Model_To_Change, Coordinates.x, Coordinates.y, Coordinates.z, 0, true, true);
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED_Spawn);
						auto NET_ID = NETWORK::PED_TO_NET(PED_Spawn);
						DECORATOR::DECOR_SET_INT(PED_Spawn, (char*)"MPBitset", 0);
						NETWORK::NETWORK_REGISTER_ENTITY_AS_NETWORKED(PED_Spawn);
						ENTITY::_SET_ENTITY_SOMETHING(PED_Spawn, false);
						if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(PED_Spawn))
							NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NET_ID, true);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(PED_Spawn, true, true);
						NETWORK::SET_NETWORK_ID_CAN_MIGRATE(NETWORK::PED_TO_NET(PED_Spawn), TRUE);
						if (!DECORATOR::DECOR_EXIST_ON(PED_Spawn, "MissionType"))
						{
							DECORATOR::DECOR_REGISTER("MissionType", 3);
							DECORATOR::DECOR_SET_INT(PED_Spawn, "MissionType", 0);

						}
						Ped PED_TO_DELETE = PLAYER::PLAYER_PED_ID();
						PLAYER::CHANGE_PLAYER_PED(PLAYER::PLAYER_ID(), PED_Spawn, true, true);
						ENTITY::DELETE_ENTITY(&PED_TO_DELETE);
					}
				});
			}
		}
	}

	void Policemode()
	{
		g_FiberScript->addTask([]() {

			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 0, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 2, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 7, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 8, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 10, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, 0, 0, 0);

			g_FiberScript->Wait(5);

			if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == MISC::GET_HASH_KEY("mp_m_freemode_01"))
			{
				//male
				PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, 46, 0, 0);

				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, 55, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, 35, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, 25, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, 182, 0, 0);
			}
			else
			{
				//female
				PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), 0, 45, 0, 0);

				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 11, 48, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 4, 34, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 6, 25, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 3, 227, 0, 0);
			}
			});
	}

	void RevealPlayers(bool toggle)
	{
		if (toggle)
		{
			*script_global(2657704).at(PLAYER::PLAYER_ID() * 463).at(213).as<bool*>() = 1;
			*script_global(2672524).at(58).as<int32_t*>() = NETWORK::GET_NETWORK_TIME();
		}
	}

	void SlowMotion(bool toggle)
	{
		if (toggle)
		{
			MISC::SET_TIME_SCALE(0.2);
		}
		else
		{
			if (g_DeadEye)
				MISC::SET_TIME_SCALE(0.6);
			else
				MISC::SET_TIME_SCALE(1);
		}
	}

	void DeadEye(bool toggle)
	{
		if (toggle)
		{
			MISC::SET_TIME_SCALE(0.6);
		}
		else
		{
			if (g_SlowMotion)
				MISC::SET_TIME_SCALE(0.2);
			else
				MISC::SET_TIME_SCALE(1);
		}
	}

	void FootTrails(bool toggle)
	{
		if (toggle)
		{
			GRAPHICS::_SET_FORCE_PED_FOOTSTEPS_TRACKS(true);
		}
		else
		{
			GRAPHICS::_SET_FORCE_PED_FOOTSTEPS_TRACKS(false);
		}
	}

#define baseaddr 0x7FF68DE50000

/*
func: 0x7ff690662eac
base: 0x7ff68de50000
0x2812ea8



//Fog : 1908B20
 unk1 : 1908B24
 unk2 : 1908B28
 unk3 : 1908B2C
 unk4 : 
*/
	void PlayerUpdateLoop()
	{
		
		if (g_MainScript->m_Initialized)
		{
			//uintptr_t ModuleBaseAdress = (uintptr_t)GetModuleHandle(NULL);
			
			//*(float*)FindAddy(ModuleBaseAdress + 0x28CF1FC, {}) = Dimensions; //0x284CC1C
		//	*(float*)FindAddy(ModuleBaseAdress + 0x284CC08, {}) = SkyIntensity;
		//	*(float*)FindAddy(ModuleBaseAdress + 0x284CC0C, {}) = Saturation; 
			//*(float*)FindAddy(ModuleBaseAdress + 0x19C4E60, {}) = Fog; //0F 2F 35 ? ? ? ? 0F 86 ? ? ? ? 0F 28 05 ? ? ? ? 
			//*(float*)FindAddy(ModuleBaseAdress + 0x19C4E64, {}) = Sun; //F3 0F 59 0D ? ? ? ? 45 8A C1 
			//*(float*)FindAddy(ModuleBaseAdress + 0x19C4E6C, {}) = POV; //F3 0F 59 35 ? ? ? ? F3 0F 11 BF ? ? ? ? 
		//	 
		//	static bool yesyes{ true };

		//	if (yesyes)
		//	{

		//	}


		//	static bool dump{ false };
		//	if (dump)
		//	{
		//		static bool g{ false };
		//		if (!g)
		//		{
		//			FILE* f;
		//			freopen_s(&f, "CONOUT$", "w", stdout);

		//			std::cout << "Saturation : 0x" << std::hex << (g_GameFunctions->m_Saturation - ModuleBaseAdress) << std::endl;
		//			std::cout << "Fog : 0x" << std::hex << (g_GameFunctions->m_Fog - ModuleBaseAdress) << std::endl;
		//			std::cout << "Sky Intensity : 0x" << std::hex << (g_GameFunctions->m_SkyIntensity - ModuleBaseAdress) << std::endl;
		//			
		//		}
		//		g = { true };
		//	}
		//	if (!g_Running)
		//		FreeConsole();

		}

		if (g_Cool)
		{
			static float zoom{ 5 };

			

			NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
			NativeVector3 dir = g_Utility->RotationToDirectionV3(rot);
			NativeVector3 pos = g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(dir, zoom));

			//GRAPHICS::_DRAW_SPHERE(pos.x, pos.y, pos.z, 4.f, g_UiManager->m_OptionSelectedBackgroundColor.r, g_UiManager->m_OptionSelectedBackgroundColor.g, g_UiManager->m_OptionSelectedBackgroundColor.b, 0.5f);
			NativeVector3 pCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);



			for (auto g : g_Rockets)
			{
				NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(g, 0);

				float getaimcoorsX = GravityGunGoto(pos.x, coords.x);
				float getaimcoorsY = GravityGunGoto(pos.y, coords.y);
				float getaimcoorsZ = GravityGunGoto(pos.z, coords.z);

				double x = sin(getaimcoorsX * 180 / 3.14);
				double y = cos(getaimcoorsY * 180 / 3.14);

				ENTITY::SET_ENTITY_VELOCITY(g, x, y, getaimcoorsZ);
			}

		}

		if (g_ThermalVision || g_NightVision)
		{
			GRAPHICS::SET_SEETHROUGH(g_ThermalVision);
			GRAPHICS::SET_NIGHTVISION(g_NightVision);
		}
		PED::SET_PED_AS_COP(PLAYER::PLAYER_PED_ID(), g_EmulatePolice);

		Rainbow2();
		//AzimuthRainbow();

		Pullover(g_Pedspullover);

		NoclipHotkey(g_NoClipHotkey);
		Invincible(g_Invincible);
		NeverWanted(g_NeverWanted);
		NoRagodoll(g_NoRagdoll);
		AlwaysRagdoll(g_AlwaysRagdoll);
		DieOnRagdoll(g_DieOnRagdoll);
		Invisible(g_Invisible);
		NoClip(NoclipIterator, g_NoClipSpeed, g_NoClip);
		Fly(g_Fly);
		Forcefield(g_Forcefield);
		SuperJump(g_Superjump);
		WalkUnderWater(g_WalkUnderWater);
		GlowManager(m_EnableGlow);
		Proofs(m_Bulleproof, m_FireProof, m_ExplosionsProof, m_CollisionProof, m_MeleeProof, m_DrownProof);
		
		ReducedCollision(g_ReducedCollision);
		ModifyWater(g_ModifyWater);
		Ninjajump(g_NinjaJump);
		OffRadar(g_OffRadar);
		RevealPlayers(g_RevealedPlayers);
		WalkOnWater(g_WalkOnWater);
		Handtrails(m_Handtrails);
		SlowMotion(g_SlowMotion);
		DeadEye(g_DeadEye);
		FootTrails(g_FootTrails);
		Alpha();

		if (m_Contort)
			Animflag = 511;
		if (m_Controllable)
			Animflag = 63;
		if (!m_Contort && !m_Controllable)
			Animflag = 1;
	}





}



//26ABD50 - 268CD50 = 1F000
//26C29F0 + 1F000 = 