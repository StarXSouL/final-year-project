#pragma once

namespace Big
{
	inline bool g_PauseTime{ false };
	inline bool g_TimeEnable{ false };
	inline int g_Hour{ 23 };
	inline int g_Minute{ 59 };
	inline int g_Second{ 59 };

	inline float g_Rain{ 0.f };
	inline float g_Waves{ 0.f };
	inline float g_Wind{ 0.f };
	inline float g_Clouds{ 0.3f };
	
	inline NativeVector3 g_black_hole_pos;

	inline bool g_EnableLight{ false };
	inline bool g_RGBLight{ false };
	inline int g_LightRed{ 255 };
	inline int g_LightBlue{ 0 };
	inline int g_LightGreen{ 0 };
	inline int g_LigtIntensity{ 20 };

	inline bool g_dominos{ false };

	inline bool g_black_hole{ false };

	inline const char* RampTypes[2]{ "Ramp", "Halfpipe" };
	inline std::vector<std::int32_t> g_Ramp{};
	inline std::size_t RampIndex{0};
	inline int g_RampCount{10};
	void BlackHole();
	void Ramp();
	void DeleteRamp();
	void dominos(bool toggle);

	void SetClouds(const char* cloudtexture);

	void MiscUpdateLoop();
}