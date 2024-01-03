#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT _WIN32_WINNT_WIN7
#include <winsdkver.h>
#include <sdkddkver.h>
#include <windows.h>
#include <winternl.h>
#include <d3d11.h>

#include <cassert>
#include <cinttypes>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <vector>

#define BIGBASE_WIDE_IMPL(str) L ## str
#define BIGBASE_WIDE(str) BIGBASE_WIDE_IMPL(str)

#define BIGBASE_STRINGIZE_IMPL(x) #x
#define BIGBASE_STRINGIZE(x) BIGBASE_STRINGIZE_IMPL(x)

#define BIGBASE_NAME "OverKill"

namespace Big
{
	using namespace std::chrono_literals;
	namespace fs = std::filesystem;

	inline HMODULE g_Module{};
	inline std::atomic_bool g_Running = true;

	inline const char* g_Role = "Basic";

	inline std::atomic_bool g_Basic;
	inline std::atomic_bool g_Standard;
	inline std::atomic_bool g_Vip;
	inline std::atomic_bool g_Tester;
	inline std::atomic_bool g_Staff;

	inline std::uint32_t g_SelectedPlayer{};

	inline std::string g_VehSpawn = "";

	inline bool g_LogScriptEvents = false;

	inline bool g_authed{ false };

	void NameChangerWindow();

	void RGBColorWindow(bool show);
	void SettingNameWindowSomething();
	void ShowRIDWindow();

	inline bool g_CustomTextShow{ false };
	inline bool shownamechangerthing{ false };
	void ShowCustomText();

	inline std::string fuckingmessage = "Not to flex, but I know a female";
	inline bool spamstuffidc{ false };
	void FuckIHateCodingRN();
}

#include "Settings.hpp"
#include "Logger.hpp"
#include "Util.hpp"
#include "Memory.hpp"
#include "Game.hpp"
#include "ScriptGlobal.hpp"
#include "Player.hpp"
#include "Natives.hpp"
#include "Utility.hpp"
#include "Fiberscript.hpp"
#include "MemoryEdit.hpp"
#include "Vehicle.hpp"
#include "Weapon.hpp"
#include "Network.hpp"
#include "World.hpp"
#include "Teleport.hpp"


extern bool ToggledOn;