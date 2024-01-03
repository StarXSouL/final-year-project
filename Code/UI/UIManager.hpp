#pragma once
#include "../Common.hpp"
#include "../Types.hpp"
#include "TextBox.hpp"
#include "AbstractSubmenu.hpp"

namespace Big::UserInterface
{
	struct RGB_COLOR
	{
		int r = 0,
			g = 0,
			b = 0;
	};

	struct RGBA : RGB_COLOR
	{
		int a = 0;
	};

	struct RGBAF : RGBA
	{
		int f = 0;
	};

	enum class Font : std::int32_t
	{
		ChaletLondon = 0,
		HouseScript = 1,
		Monospace = 2,
		Wingdings = 3,
		ChaletComprimeCologne = 4,
		Pricedown = 7
	};

	enum class HeaderType : std::int32_t
	{
		Static = 0,
		Gradient = 1,
		YTD = 2,
	};

	struct Rectangle
	{
		Vector2 m_Center;
		Vector2 m_Size;

		bool IsInBounds(Vector2 point)
		{
			auto left = m_Center.x - (m_Size.x / 2.f);
			auto right = m_Center.x + (m_Size.x / 2.f);
			auto top = m_Center.y + (m_Size.y / 2.f);
			auto bottom = m_Center.y - (m_Size.y / 2.f);

			if (point.x > right || point.x < left)
				return false;
			if (point.y > top || point.y < bottom)
				return false;

			return true;
		}
	};
	bool FileExists(const std::string& fileName);
	void GET_YTD(std::string name);
	void GET_YTDFullTheme(std::string name);
	inline std::vector<std::string> m_YTDNames;
	inline std::vector<std::string> m_YTDNamesFull;
	std::vector<std::string> YTDLister();
	std::vector<std::string> YTDListerFullTheme();

	inline bool g_FullThemeLoading{ false };

	inline std::string m_YTDName{ "overkill" };
	inline std::string m_PNGName;

	inline std::string FullHeaderName;

	class UIManager
	{
	public:
		explicit UIManager() = default;
		~UIManager() noexcept = default;
		UIManager(UIManager const&) = delete;
		UIManager(UIManager&&) = delete;
		UIManager& operator=(UIManager const&) = delete;
		UIManager& operator=(UIManager&&) = delete;

		template <typename SubmenuType, typename ...TArgs>
		void AddSubmenu(TArgs&&... args)
		{
			auto sub = std::make_unique<SubmenuType>(std::forward<TArgs>(args)...);
			if (m_SubmenuStack.empty())
			{
				m_SubmenuStack.push(sub.get());
			}

			m_AllSubmenus.push_back(std::move(sub));
		}

		void SwitchToSubmenu(std::uint32_t id)
		{
			for (auto&& sub : m_AllSubmenus)
			{
				if (sub->GetId() == id)
				{
					m_SubmenuStack.push(sub.get());
					return;
				}
			}
		}

		void OnTick();
	public:
		std::mutex m_Mutex;

		bool m_Opened = false;
		bool TextKek{ true };
		std::string textkek{ "OverKill"};
		bool m_MouseLocked = false;
		float m_PosX = g_Settings.m_Options["m_PosX"].get<float>();
		float m_PosY = g_Settings.m_Options["m_PosY"].get<float>();
		float m_Width = g_Settings.m_Options["m_Width"].get<float>();
		std::size_t m_OptionsPerPage = 14;
		bool m_Sounds = true;

		// Input
		std::int32_t m_OpenDelay = g_Settings.m_Options["m_OpenDelay"].get<std::int32_t>();
		std::int32_t m_BackDelay = g_Settings.m_Options["m_BackDelay"].get<std::int32_t>();
		std::int32_t m_EnterDelay = g_Settings.m_Options["m_EnterDelay"].get<std::int32_t>();
		std::int32_t m_VerticalDelay = g_Settings.m_Options["m_VerticalDelay"].get<std::int32_t>();
		std::int32_t m_HorizontalDelay = g_Settings.m_Options["m_HorizontalDelay"].get<std::int32_t>();

		// Header
		float m_HeaderHeight = g_Settings.m_Options["m_HeaderHeight"].get<float>();
		bool m_HeaderText = g_Settings.m_Options["m_HeaderText"].get<bool>();
		float m_HeaderTextSize = g_Settings.m_Options["m_HeaderTextSize"].get<float>();
		Font m_HeaderFont = Font::HouseScript;
		Color m_HeaderBackgroundColor{ g_Settings.m_Options["m_HeaderBackgroundColor.r"].get<int>(), g_Settings.m_Options["m_HeaderBackgroundColor.g"].get<int>(), g_Settings.m_Options["m_HeaderBackgroundColor.b"].get<int>(), g_Settings.m_Options["m_HeaderBackgroundColor.a"].get<int>() };
		Color m_HeaderTextColor{ g_Settings.m_Options["m_HeaderTextColor.r"].get<int>(), g_Settings.m_Options["m_HeaderTextColor.g"].get<int>(), g_Settings.m_Options["m_HeaderTextColor.b"].get<int>(), g_Settings.m_Options["m_HeaderTextColor.a"].get<int>() };
		HeaderType m_HeaderType = HeaderType::YTD;

		bool m_Smoothscroll{ g_Settings.m_Options["m_Smoothscroll"].get<bool>() };

		bool m_HeaderGradientTransparent = g_Settings.m_Options["m_HeaderGradientTransparent"].get<bool>();
		bool m_HeaderGradientFlip = g_Settings.m_Options["m_HeaderGradientFlip"].get<bool>();
		float m_HeaderGradientStretch = g_Settings.m_Options["m_HeaderGradientStretch"].get<float>();
		float m_HeaderGradientFiller = g_Settings.m_Options["m_HeaderGradientFiller"].get<float>();
		Color m_HeaderGradientColorRight{ g_Settings.m_Options["m_HeaderGradientColorRight.r"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorRight.g"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorRight.b"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorRight.a"].get<int>() };
		Color m_HeaderGradientColorLeft{ g_Settings.m_Options["m_HeaderGradientColorLeft.r"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorLeft.g"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorLeft.b"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorLeft.a"].get<int>() };

		// Submenu bar
		float m_SubmenuBarHeight = g_Settings.m_Options["m_SubmenuBarHeight"].get<float>();
		float m_SubmenuBarTextSize = g_Settings.m_Options["m_SubmenuBarTextSize"].get<float>();
		Font m_SubmenuBarFont = Font::ChaletLondon;
		float m_SubmenuBarPadding = g_Settings.m_Options["m_SubmenuBarPadding"].get<float>();
		Color m_SubmenuBarBackgroundColor{ g_Settings.m_Options["m_SubmenuBarBackgroundColor.r"].get<int>(), g_Settings.m_Options["m_SubmenuBarBackgroundColor.g"].get<int>(), g_Settings.m_Options["m_SubmenuBarBackgroundColor.b"].get<int>(), g_Settings.m_Options["m_SubmenuBarBackgroundColor.a"].get<int>() };
		Color m_SubmenuBarTextColor{ g_Settings.m_Options["m_SubmenuBarTextColor.r"].get<int>(), g_Settings.m_Options["m_SubmenuBarTextColor.g"].get<int>(), g_Settings.m_Options["m_SubmenuBarTextColor.b"].get<int>(), g_Settings.m_Options["m_SubmenuBarTextColor.a"].get<int>() };
		bool m_ShowSubmenubar = g_Settings.m_Options["m_ShowSubmenubar"].get<bool>();

		// Options
		float m_OptionHeight = g_Settings.m_Options["m_OptionHeight"].get<float>();
		float m_OptionTextSize = g_Settings.m_Options["m_OptionTextSize"].get<float>();
		Font m_OptionFont = Font::ChaletLondon;
		float m_OptionPadding = g_Settings.m_Options["m_OptionPadding"].get<float>();
		Color m_OptionSelectedTextColor{ g_Settings.m_Options["m_OptionUnselectedTextColor.r"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.g"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.b"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.a"].get<int>() };
		Color m_OptionUnselectedTextColor{ g_Settings.m_Options["m_OptionUnselectedTextColor.r"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.g"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.b"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.a"].get<int>() };
		Color m_OptionSelectedBackgroundColor{ 0, 128, 128, 170 };
		Color m_OptionUnselectedBackgroundColor{ g_Settings.m_Options["m_OptionUnselectedBackgroundColor.r"].get<int>(), g_Settings.m_Options["m_OptionUnselectedBackgroundColor.g"].get<int>(), g_Settings.m_Options["m_OptionUnselectedBackgroundColor.b"].get<int>(), 170 };

		float m_ToggleScale{ g_Settings.m_Options["m_ToggleScale"].get<float>() };
		Color m_SelectedToggle{ g_Settings.m_Options["m_SelectedToggle.r"].get<int>(), g_Settings.m_Options["m_SelectedToggle.g"].get<int>(), g_Settings.m_Options["m_SelectedToggle.b"].get<int>(), g_Settings.m_Options["m_SelectedToggle.a"].get<int>() };
		Color m_UnselectedToggle{ g_Settings.m_Options["m_UnselectedToggle.r"].get<int>(), g_Settings.m_Options["m_UnselectedToggle.g"].get<int>(), g_Settings.m_Options["m_UnselectedToggle.b"].get<int>(), g_Settings.m_Options["m_UnselectedToggle.a"].get<int>() };

		// Footer
		float m_FooterHeight = g_Settings.m_Options["m_FooterSpriteSize"].get<float>();
		float m_FooterSpriteSize = g_Settings.m_Options["m_FooterSpriteSize"].get<float>();
		Color m_FooterBackgroundColor{ g_Settings.m_Options["m_FooterBackgroundColor.r"].get<int>(), g_Settings.m_Options["m_FooterBackgroundColor.g"].get<int>(), g_Settings.m_Options["m_FooterBackgroundColor.b"].get<int>(), g_Settings.m_Options["m_FooterBackgroundColor.a"].get<int>() };
		Color m_FooterSpriteColor{ g_Settings.m_Options["m_FooterSpriteColor.r"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.g"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.b"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.a"].get<int>() };

		// Description
		float m_DescriptionHeightPadding = g_Settings.m_Options["m_DescriptionHeightPadding"].get<float>();
		float m_DescriptionHeight = g_Settings.m_Options["m_DescriptionHeight"].get<float>();
		float m_DescriptionTextSize = g_Settings.m_Options["m_DescriptionTextSize"].get<float>();
		Font m_DescriptionFont = Font::ChaletLondon;
		Color m_DescriptionBackgroundColor{ g_Settings.m_Options["m_FooterSpriteColor.r"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.g"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.b"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.a"].get<int>() };
		Color m_DescriptionTextColor{ g_Settings.m_Options["m_FooterSpriteColor.r"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.g"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.b"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.a"].get<int>() };
		float m_DescriptionSpriteSize = g_Settings.m_Options["m_DescriptionSpriteSize"].get<float>();
		float m_DescriptionPadding = g_Settings.m_Options["m_DescriptionPadding"].get<float>();
		Color m_DescriptionSpriteColor{ g_Settings.m_Options["m_DescriptionSpriteColor.r"].get<int>(), g_Settings.m_Options["m_DescriptionSpriteColor.g"].get<int>(), g_Settings.m_Options["m_DescriptionSpriteColor.b"].get<int>(), g_Settings.m_Options["m_DescriptionSpriteColor.a"].get<int>() };

		// Smooth Scroll
		int minusOpacity = 0;
		float m_ScrollSpeed = g_Settings.m_Options["m_ScrollSpeed"].get<float>();

		void DisplayInfoText(std::string text, RGBAF rgbaf, Vector2 position, float size, bool center, bool right);
		void PlayerInfo(std::string one, std::string two);
		void PlayerInfoText(std::string text, RGBAF rgbaf, Font font, Vector2 position, Vector2 size, bool center, bool right);
		void PlayerMultiInfo(std::string one, std::string two, std::string three, std::string four);
		void HostMigrationManager();
		void GameInfo();
		void HostMigrationText(std::string token);
		void PlayerBox(std::string name);

		const char* ToggleList[3]
		{
			"Buttons",
			"Checkmarks",
			"Text"
		};
		std::size_t ToggleIterator = g_Settings.m_Options["ToggleIterator"].get<std::size_t>();

		const char* IndicatorList[3]
		{
			"Arrows",
			"Lines",
			"None"
		};
		std::size_t IndicatorIterator = g_Settings.m_Options["IndicatorIterator"].get<std::size_t>();

		void LoadTheme(const char* str)
		{
			std::string path = g_Settings.appdatapath + "\\Themes\\" + static_cast<std::string>(str) + ".json";
			std::ifstream file(path);
			if (!std::filesystem::exists(path))
			{
				g_Logger->Info("Failed to load %s", str);
				g_Logger->Info("Loading default settings...");
				g_Settings.Initialize();
			}
			g_Logger->Info("Loading %s", str);
			file >> g_Settings.m_Options;

			for (auto& e : g_Settings.m_Options.items())
			{
				if (g_Settings.m_Options.count(e.key()) == 0)
				{
					path = true;
					g_Settings.m_Options[e.key()] = e.value();
				}
			}

			// Input
			m_OpenDelay = g_Settings.m_Options["m_OpenDelay"].get<std::int32_t>();
			m_BackDelay = g_Settings.m_Options["m_BackDelay"].get<std::int32_t>();
			m_EnterDelay = g_Settings.m_Options["m_EnterDelay"].get<std::int32_t>();
			m_VerticalDelay = g_Settings.m_Options["m_VerticalDelay"].get<std::int32_t>();
			m_HorizontalDelay = g_Settings.m_Options["m_HorizontalDelay"].get<std::int32_t>();

			// Header
			m_HeaderHeight = g_Settings.m_Options["m_HeaderHeight"].get<float>();
			m_HeaderText = g_Settings.m_Options["m_HeaderText"].get<bool>();
			m_HeaderTextSize = g_Settings.m_Options["m_HeaderTextSize"].get<float>();
			m_HeaderFont = Font::HouseScript;
			m_HeaderBackgroundColor = { g_Settings.m_Options["m_HeaderBackgroundColor.r"].get<int>(), g_Settings.m_Options["m_HeaderBackgroundColor.g"].get<int>(), g_Settings.m_Options["m_HeaderBackgroundColor.b"].get<int>(), g_Settings.m_Options["m_HeaderBackgroundColor.a"].get<int>() };
			m_HeaderTextColor = { g_Settings.m_Options["m_HeaderTextColor.r"].get<int>(), g_Settings.m_Options["m_HeaderTextColor.g"].get<int>(), g_Settings.m_Options["m_HeaderTextColor.b"].get<int>(), g_Settings.m_Options["m_HeaderTextColor.a"].get<int>() };


			m_HeaderGradientTransparent = g_Settings.m_Options["m_HeaderGradientTransparent"].get<float>();
			m_HeaderGradientFlip = g_Settings.m_Options["m_HeaderGradientFlip"].get<float>();
			m_HeaderGradientStretch = g_Settings.m_Options["m_HeaderGradientStretch"].get<float>();
			m_HeaderGradientFiller = g_Settings.m_Options["m_HeaderGradientFiller"].get<float>();
			m_HeaderGradientColorRight = { g_Settings.m_Options["m_HeaderGradientColorRight.r"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorRight.g"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorRight.b"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorRight.a"].get<int>() };
			m_HeaderGradientColorLeft = { g_Settings.m_Options["m_HeaderGradientColorLeft.r"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorLeft.g"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorLeft.b"].get<int>(), g_Settings.m_Options["m_HeaderGradientColorLeft.a"].get<int>() };

			// Submenu bar
			m_SubmenuBarHeight = g_Settings.m_Options["m_SubmenuBarHeight"].get<float>();
			m_SubmenuBarTextSize = g_Settings.m_Options["m_SubmenuBarTextSize"].get<float>();
			m_SubmenuBarFont = Font::ChaletLondon;
			m_SubmenuBarPadding = g_Settings.m_Options["m_SubmenuBarPadding"].get<float>();
			m_SubmenuBarBackgroundColor = { g_Settings.m_Options["m_SubmenuBarBackgroundColor.r"].get<int>(), g_Settings.m_Options["m_SubmenuBarBackgroundColor.g"].get<int>(), g_Settings.m_Options["m_SubmenuBarBackgroundColor.b"].get<int>(), g_Settings.m_Options["m_SubmenuBarBackgroundColor.a"].get<int>() };
			m_SubmenuBarTextColor = { g_Settings.m_Options["m_SubmenuBarTextColor.r"].get<int>(), g_Settings.m_Options["m_SubmenuBarTextColor.g"].get<int>(), g_Settings.m_Options["m_SubmenuBarTextColor.b"].get<int>(), g_Settings.m_Options["m_SubmenuBarTextColor.a"].get<int>() };
			m_ShowSubmenubar = g_Settings.m_Options["m_ShowSubmenubar"].get<bool>();

			// Options
			m_OptionHeight = g_Settings.m_Options["m_OptionHeight"].get<float>();
			m_OptionTextSize = g_Settings.m_Options["m_OptionTextSize"].get<float>();
			m_OptionFont = Font::ChaletLondon;
			m_OptionPadding = g_Settings.m_Options["m_OptionPadding"].get<float>();
			m_OptionSelectedTextColor = { g_Settings.m_Options["m_OptionUnselectedTextColor.r"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.g"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.b"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.a"].get<int>() };
			m_OptionUnselectedTextColor = { g_Settings.m_Options["m_OptionUnselectedTextColor.r"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.g"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.b"].get<int>(), g_Settings.m_Options["m_OptionUnselectedTextColor.a"].get<int>() };
			m_OptionSelectedBackgroundColor = { 0, 128, 128, 170 };
			m_OptionUnselectedBackgroundColor = { g_Settings.m_Options["m_OptionUnselectedBackgroundColor.r"].get<int>(), g_Settings.m_Options["m_OptionUnselectedBackgroundColor.g"].get<int>(), g_Settings.m_Options["m_OptionUnselectedBackgroundColor.b"].get<int>(), 170 };

			m_ToggleScale = { g_Settings.m_Options["m_ToggleScale"].get<float>() };
			m_SelectedToggle = { g_Settings.m_Options["m_SelectedToggle.r"].get<int>(), g_Settings.m_Options["m_SelectedToggle.g"].get<int>(), g_Settings.m_Options["m_SelectedToggle.b"].get<int>(), g_Settings.m_Options["m_SelectedToggle.a"].get<int>() };
			m_UnselectedToggle = { g_Settings.m_Options["m_UnselectedToggle.r"].get<int>(), g_Settings.m_Options["m_UnselectedToggle.g"].get<int>(), g_Settings.m_Options["m_UnselectedToggle.b"].get<int>(), g_Settings.m_Options["m_UnselectedToggle.a"].get<int>() };

			// Footer
			m_FooterHeight = g_Settings.m_Options["m_FooterSpriteSize"].get<float>();
			m_FooterSpriteSize = g_Settings.m_Options["m_FooterSpriteSize"].get<float>();
			m_FooterBackgroundColor = { g_Settings.m_Options["m_FooterBackgroundColor.r"].get<int>(), g_Settings.m_Options["m_FooterBackgroundColor.g"].get<int>(), g_Settings.m_Options["m_FooterBackgroundColor.b"].get<int>(), g_Settings.m_Options["m_FooterBackgroundColor.a"].get<int>() };
			m_FooterSpriteColor = { g_Settings.m_Options["m_FooterSpriteColor.r"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.g"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.b"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.a"].get<int>() };

			// Description
			m_DescriptionHeightPadding = g_Settings.m_Options["m_DescriptionHeightPadding"].get<float>();
			m_DescriptionHeight = g_Settings.m_Options["m_DescriptionHeight"].get<float>();
			m_DescriptionTextSize = g_Settings.m_Options["m_DescriptionTextSize"].get<float>();
			m_DescriptionFont = Font::ChaletLondon;
			m_DescriptionBackgroundColor = { g_Settings.m_Options["m_FooterSpriteColor.r"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.g"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.b"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.a"].get<int>() };
			m_DescriptionTextColor = { g_Settings.m_Options["m_FooterSpriteColor.r"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.g"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.b"].get<int>(), g_Settings.m_Options["m_FooterSpriteColor.a"].get<int>() };
			m_DescriptionSpriteSize = g_Settings.m_Options["m_DescriptionSpriteSize"].get<float>();
			m_DescriptionPadding = g_Settings.m_Options["m_DescriptionPadding"].get<float>();
			m_DescriptionSpriteColor = { g_Settings.m_Options["m_DescriptionSpriteColor.r"].get<int>(), g_Settings.m_Options["m_DescriptionSpriteColor.g"].get<int>(), g_Settings.m_Options["m_DescriptionSpriteColor.b"].get<int>(), g_Settings.m_Options["m_DescriptionSpriteColor.a"].get<int>() };

			ToggleIterator = g_Settings.m_Options["ToggleIterator"].get<std::size_t>();
			IndicatorIterator = g_Settings.m_Options["IndicatorIterator"].get<std::size_t>();

			m_Width = g_Settings.m_Options["m_Width"].get<float>();
			m_PosX = g_Settings.m_Options["m_PosX"].get<float>();
			m_PosY = g_Settings.m_Options["m_PosY"].get<float>();

			m_HeaderType = HeaderType::YTD;
			m_Smoothscroll = g_Settings.m_Options["m_Smoothscroll"].get<bool>();

			m_ScrollSpeed = g_Settings.m_Options["m_ScrollSpeed"].get<float>();
			//g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_MAINTIT"), g_UiManager->textkek.c_str());
			g_Logger->Info("Successfully loaded %s", str);
		}

		void WriteNewConfig(std::string str)
		{
			nlohmann::json CurrentTheme
			{
				{ "m_OptionUnselectedTextColor.r", m_OptionUnselectedTextColor.r },
				{ "m_OptionUnselectedTextColor.g", m_OptionUnselectedTextColor.g },
				{ "m_OptionUnselectedTextColor.b", m_OptionUnselectedTextColor.b },
				{ "m_OptionUnselectedTextColor.a", m_OptionUnselectedTextColor.a },

				{ "m_OptionSelectedTextColor.r", m_OptionSelectedTextColor.r },
				{ "m_OptionSelectedTextColor.g", m_OptionSelectedTextColor.g },
				{ "m_OptionSelectedTextColor.b", m_OptionSelectedTextColor.b },
				{ "m_OptionSelectedTextColor.a", m_OptionSelectedTextColor.a },

				{ "m_OptionUnselectedBackgroundColor.r", m_OptionUnselectedBackgroundColor.r},
				{ "m_OptionUnselectedBackgroundColor.g", m_OptionUnselectedBackgroundColor.g},
				{ "m_OptionUnselectedBackgroundColor.b", m_OptionUnselectedBackgroundColor.b},
				{ "m_OptionUnselectedBackgroundColor.a", m_OptionUnselectedBackgroundColor.a},

				{ "m_SubmenuBarTextColor.r", m_SubmenuBarTextColor.r },
				{ "m_SubmenuBarTextColor.g", m_SubmenuBarTextColor.g },
				{ "m_SubmenuBarTextColor.b", m_SubmenuBarTextColor.b },
				{ "m_SubmenuBarTextColor.a", m_SubmenuBarTextColor.a },

				{ "m_SubmenuBarBackgroundColor.r", m_SubmenuBarBackgroundColor.r },
				{ "m_SubmenuBarBackgroundColor.g", m_SubmenuBarBackgroundColor.g },
				{ "m_SubmenuBarBackgroundColor.b", m_SubmenuBarBackgroundColor.b },
				{ "m_SubmenuBarBackgroundColor.a", m_SubmenuBarBackgroundColor.a },

				{ "m_SelectedToggle.r", m_SelectedToggle.r },
				{ "m_SelectedToggle.g", m_SelectedToggle.g },
				{ "m_SelectedToggle.b", m_SelectedToggle.b },
				{ "m_SelectedToggle.a", m_SelectedToggle.a },

				{ "m_UnselectedToggle.r", m_UnselectedToggle.r },
				{ "m_UnselectedToggle.g", m_UnselectedToggle.g },
				{ "m_UnselectedToggle.b", m_UnselectedToggle.b },
				{ "m_UnselectedToggle.a", m_UnselectedToggle.a },

				{ "m_HeaderGradientColorLeft.r", m_HeaderGradientColorLeft.r },
				{ "m_HeaderGradientColorLeft.g", m_HeaderGradientColorLeft.g },
				{ "m_HeaderGradientColorLeft.b", m_HeaderGradientColorLeft.b },
				{ "m_HeaderGradientColorLeft.a", m_HeaderGradientColorLeft.a },

				{ "m_HeaderGradientColorRight.r", m_HeaderGradientColorRight.r },
				{ "m_HeaderGradientColorRight.g", m_HeaderGradientColorRight.g },
				{ "m_HeaderGradientColorRight.b", m_HeaderGradientColorRight.b },
				{ "m_HeaderGradientColorRight.a", m_HeaderGradientColorRight.a },

				{ "m_HeaderTextColor.r", m_HeaderTextColor.a },
				{ "m_HeaderTextColor.g", m_HeaderTextColor.g },
				{ "m_HeaderTextColor.b", m_HeaderTextColor.b },
				{ "m_HeaderTextColor.a", m_HeaderTextColor.a },

				{ "m_FooterSpriteColor.r", m_FooterSpriteColor.r },
				{ "m_FooterSpriteColor.g", m_FooterSpriteColor.g },
				{ "m_FooterSpriteColor.b", m_FooterSpriteColor.b },
				{ "m_FooterSpriteColor.a", m_FooterSpriteColor.a },

				{ "m_FooterBackgroundColor.r", m_FooterBackgroundColor.r },
				{ "m_FooterBackgroundColor.g", m_FooterBackgroundColor.g },
				{ "m_FooterBackgroundColor.b", m_FooterBackgroundColor.b },
				{ "m_FooterBackgroundColor.a", m_FooterBackgroundColor.a },

				{ "m_HeaderBackgroundColor.r", m_HeaderBackgroundColor.r },
				{ "m_HeaderBackgroundColor.g", m_HeaderBackgroundColor.g },
				{ "m_HeaderBackgroundColor.b", m_HeaderBackgroundColor.b },
				{ "m_HeaderBackgroundColor.a", m_HeaderBackgroundColor.a },

				{ "m_HeaderHeight", m_HeaderHeight },
				{ "m_SubmenuBarHeight", m_SubmenuBarHeight },
				{ "m_SubmenuBarTextSize", m_SubmenuBarTextSize },
				{ "m_SubmenuBarPadding", m_SubmenuBarPadding },

				{ "m_FooterSpriteSize", m_FooterSpriteSize },
				{ "m_FooterHeight", m_FooterHeight },
				{ "m_ToggleScale", m_ToggleScale },
				{ "m_HeaderGradientStretch", m_HeaderGradientStretch },
				{ "m_HeaderGradientFiller", m_HeaderGradientFiller },
				{ "m_OptionPadding", m_OptionPadding },
				{ "m_OptionTextSize", m_OptionTextSize },
				{ "m_OptionHeight", m_OptionHeight },
				{ "m_HeaderTextSize", m_HeaderTextSize },
				{ "m_HeaderText", m_HeaderText },
				{ "m_HeaderGradientTransparent", m_HeaderGradientTransparent },
				{ "m_HeaderGradientFlip", m_HeaderGradientFlip },
				{ "m_HeaderHeight", m_HeaderHeight },

				{ "m_OpenDelay", m_OpenDelay },
				{ "m_BackDelay", m_BackDelay },
				{ "m_EnterDelay", m_EnterDelay },
				{ "m_VerticalDelay", m_VerticalDelay },
				{ "m_HorizontalDelay", m_HorizontalDelay },
				{ "m_DescriptionHeightPadding", m_DescriptionHeightPadding },
				{ "m_DescriptionHeight", m_DescriptionHeight },
				{ "m_DescriptionTextSize", m_DescriptionTextSize },
				{ "m_DescriptionSpriteSize", m_DescriptionSpriteSize },
				{ "m_DescriptionPadding", m_DescriptionPadding },

				{ "m_DescriptionBackgroundColor.r", m_DescriptionBackgroundColor.r },
				{ "m_DescriptionBackgroundColor.g", m_DescriptionBackgroundColor.g },
				{ "m_DescriptionBackgroundColor.b", m_DescriptionBackgroundColor.b },
				{ "m_DescriptionBackgroundColor.a", m_DescriptionBackgroundColor.a },

				{ "m_DescriptionTextColor.r", m_DescriptionTextColor.r },
				{ "m_DescriptionTextColor.g", m_DescriptionTextColor.g },
				{ "m_DescriptionTextColor.b", m_DescriptionTextColor.b },
				{ "m_DescriptionTextColor.a", m_DescriptionTextColor.a },

				{ "m_DescriptionSpriteColor.r", m_DescriptionSpriteColor.r },
				{ "m_DescriptionSpriteColor.g", m_DescriptionSpriteColor.g },
				{ "m_DescriptionSpriteColor.b", m_DescriptionSpriteColor.b },
				{ "m_DescriptionSpriteColor.a", m_DescriptionSpriteColor.a },

				{ "m_PosX", m_PosX },
				{ "m_PosY", m_PosY },
				{ "m_Width", m_Width },

				{ "m_ShowSubmenubar", m_ShowSubmenubar },
				{ "ToggleIterator", ToggleIterator },
				{ "IndicatorIterator", IndicatorIterator },

				{ "m_Width", m_Width },
				{ "m_PosX", m_PosX },
				{ "m_PosY", m_PosY },

				{ "m_HeaderType", m_HeaderType },
				{ "m_Smoothscroll", m_Smoothscroll },
				{"m_ScrollSpeed", m_ScrollSpeed }
			};

			std::string path = g_Settings.appdatapath + "\\Themes\\" + str + ".json";
			std::ofstream file(path, std::ios::out);

			file << CurrentTheme.dump(4);
			file.close();
			g_Settings.m_Options.clear();
			g_Settings.m_Options = CurrentTheme;
		}

		float m_DrawBaseY{};
		void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
		float GetTextHeight(Font font, float size);
		std::stack<AbstractSubmenu*, std::vector<AbstractSubmenu*>> m_SubmenuStack;
	private:
		bool m_OpenKeyPressed = false;
		bool m_BackKeyPressed = false;
		bool m_EnterKeyPressed = false;
		bool m_UpKeyPressed = false;
		bool m_DownKeyPressed = false;
		bool m_LeftKeyPressed = false;
		bool m_RightKeyPressed = false;
		void CheckForInput();
		void HandleInput();
		void ResetInput();

		void DrawHeader(AbstractSubmenu* sub);
		void DrawSubmenuBar(AbstractSubmenu* sub);
		void DrawOption(AbstractOption* opt, AbstractSubmenu* sub, bool selected);
		void DrawFooter();
		void DrawDescription();

		void DrawRect(float x, float y, float width, float height, Color color);
		void DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation);
		void DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawCenteredText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawRightText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		Vector2 GetSpriteScale(float size);

		bool IsMouseLocked();
		Rectangle GetMenuRect();
		Vector2 GetMousePos();

		std::vector<std::unique_ptr<AbstractSubmenu>> m_AllSubmenus;
	};
}

namespace Big
{
	inline std::unique_ptr<UserInterface::UIManager> g_UiManager;
}
