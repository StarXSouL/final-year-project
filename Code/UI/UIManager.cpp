#include "UIManager.hpp"
#include "../Timer.hpp"
#include "../Natives.hpp"
#include "../Lists.hpp"
#include "../Translation.hpp"

std::string properRightText;

float selectedTarget = 0;
double current = 0;
int currentOpacity;
int targetOpacity = 1000;
float scrollCurrent = 0;
float scrollTarget = 0;
int currentSelected, fullAmount;

float X_Info{};
float Y_Info{};
float X_GameInfo{ 0.96f };
float Y_GameInfo{};

float X_Notify{};
float Y_Notify{};

bool first = true;
bool cooldown = false;
bool negative = false;
bool editing = false;

float X_InfoFloat{};
float Y_InfoFloat{};

float X_HostMigration{};
float Y_HostMigration{};

double lerp(double start, double end, double amount) {
	return start * (1 - amount) + end * amount;
}

double opt_start = 0;
double opt_end = 0;


namespace Big::UserInterface
{
	bool FileExists(const std::string& fileName)
	{
		struct stat buffer;
		return (stat(fileName.c_str(), &buffer) == 0);
	}

	void GET_YTD(std::string name)
	{
		static uint32_t* (*pRegisterFile)(int*, const char*, bool, const char*, bool) = reinterpret_cast<decltype(pRegisterFile)>(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").count(1).get(0).get<void>(0));
		std::string path = g_Settings.appdatapath + "\\Textures\\" + m_YTDName + ".ytd";

		int textureID;
		if (FileExists(path)) {
			pRegisterFile(&textureID, path.c_str(), true, name.c_str(), false);
		}
	}

	void GET_YTDFullTheme(std::string name)
	{
		static uint32_t* (*pRegisterFile)(int*, const char*, bool, const char*, bool) = reinterpret_cast<decltype(pRegisterFile)>(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").count(1).get(0).get<void>(0));
		std::string path = g_Settings.appdatapath + "\\Textures\\Full Themes\\" + FullHeaderName + ".ytd";

		int textureID;
		if (FileExists(path)) {
			pRegisterFile(&textureID, path.c_str(), true, name.c_str(), false);
		}
	}

	std::vector<std::string> YTDLister()
	{
		std::vector<std::string> tempVector;
		std::stringstream tempStringStream;
		for (auto& collectedFiles : std::filesystem::directory_iterator(g_Settings.appdatapath + "\\Textures\\"))
		{
			tempStringStream << collectedFiles;
			std::string oing = tempStringStream.str();
			if (oing.substr(oing.find_last_of(".") + 1) == "ytd")
			{
				unsigned foundAmount = oing.find_last_of("/\\");
				std::string TempHolder = oing.substr(0, foundAmount);
				std::string TempHolder2 = oing.substr(foundAmount + 1);
				tempVector.push_back(TempHolder2.substr(0, TempHolder2.find(".", 0)));
				m_YTDNames = tempVector;
			}
		}
		return tempVector;
	}

	std::vector<std::string> YTDListerFullTheme()
	{
		std::vector<std::string> tempVector;
		std::stringstream tempStringStream;
		for (auto& collectedFiles : std::filesystem::directory_iterator(g_Settings.appdatapath + "\\Textures\\Full Themes\\"))
		{
			tempStringStream << collectedFiles;
			std::string oing = tempStringStream.str();
			if (oing.substr(oing.find_last_of(".") + 1) == "ytd")
			{
				unsigned foundAmount = oing.find_last_of("/\\");
				std::string TempHolder = oing.substr(0, foundAmount);
				std::string TempHolder2 = oing.substr(foundAmount + 1);
				tempVector.push_back(TempHolder2.substr(0, TempHolder2.find(".", 0)));
				m_YTDNamesFull = tempVector;
			}
		}
		return tempVector;
	}

	void UIManager::OnTick()
	{
		GameInfo();
		minusOpacity = 255;
		{
			if (minusOpacity != 0 && GetTickCount() % 12 == 0)
			{
				minusOpacity--;
			}
		}
		{
			if (currentOpacity != targetOpacity) currentOpacity = lerp(currentOpacity, targetOpacity, m_ScrollSpeed * 2);
			if ((currentOpacity > targetOpacity - 0.0005) && (currentOpacity < targetOpacity + 0.0005))
			{
				currentOpacity = targetOpacity;
			}
			minusOpacity = currentOpacity;
		}
		{
			if (scrollCurrent != scrollTarget) scrollCurrent = lerp(scrollCurrent, scrollTarget, m_ScrollSpeed);
			if ((scrollCurrent > scrollTarget - 0.0005) && (scrollCurrent < scrollTarget + 0.0005))
			{
				scrollCurrent = scrollTarget;
			}
		}
		{
			if (current != selectedTarget) current = lerp(current, selectedTarget, m_ScrollSpeed);
			if ((current > selectedTarget - 0.0005) && (current < selectedTarget + 0.0005))
			{
				current = selectedTarget;
			}
		}
		{
			if (minusOpacity != targetOpacity) minusOpacity = lerp(minusOpacity, targetOpacity, 0.0025f);
			if ((minusOpacity > targetOpacity - 2) && (minusOpacity < targetOpacity + 2))
			{
				minusOpacity = targetOpacity;
			}
			//minusOpacity = currentOpacity;
		}

		std::lock_guard lock(m_Mutex);

		if (IsMouseLocked())
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			ShowCursor(true);
			SetCursor(LoadCursorA(NULL, IDC_ARROW));

			if (GetMenuRect().IsInBounds(GetMousePos()))
			{
				g_Logger->Info("Kekkeke");
			}
		}

		if (g_UiManager->m_Opened && g_Settings.m_LockMouse)
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}

		CheckForInput();
		HandleInput();

		if (m_Opened)
		{
			g_Utility->openedYet = false;
			PAD::DISABLE_CONTROL_ACTION(0, 27, true);

			m_DrawBaseY = m_PosY;
			if (!m_SubmenuStack.empty())
			{
				auto sub = m_SubmenuStack.top();
				sub->Reset();
				sub->Execute();
				DrawHeader(sub);
				if (m_ShowSubmenubar)
				{
					DrawSubmenuBar(sub);
				}
				if (sub->GetNumOptions() != 0)
				{
					std::size_t startPoint = 0;
					std::size_t endPoint = sub->GetNumOptions() > m_OptionsPerPage ? m_OptionsPerPage : sub->GetNumOptions();
					if (sub->GetNumOptions() > m_OptionsPerPage && sub->GetSelectedOption() >= m_OptionsPerPage - 6)
					{
						for (int i = 0; i < 6; i++)
						{
							if (sub->GetSelectedOption() < sub->GetNumOptions() - i)
							{
								startPoint = sub->GetSelectedOption() - g_UiManager->m_OptionsPerPage + i + 1;
								endPoint = sub->GetSelectedOption() + i + 1;
							}
						}
					}
					float tmp_base = m_DrawBaseY;

					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j)
					{
						float tmp_point = tmp_base + ((m_OptionHeight) / 2.f);
						if (i == startPoint) opt_start = tmp_point;
						if (i == endPoint - 1) opt_end = tmp_point;

						if (g_FullThemeLoading)
						{

							DrawSprite(
								FullHeaderName.c_str(),
								"Unselected",
								m_PosX,
								tmp_point,
								m_Width,
								m_OptionHeight,
								{ m_OptionUnselectedBackgroundColor.r, m_OptionUnselectedBackgroundColor.g, m_OptionUnselectedBackgroundColor.b, m_OptionUnselectedBackgroundColor.a },
								0);
							if (m_Smoothscroll)
							{
								DrawSprite(
									FullHeaderName.c_str(),
									"Selected",
									m_PosX,
									scrollCurrent,
									m_Width,
									m_OptionHeight,
									m_OptionSelectedBackgroundColor, 0);
							}
						}
						else
						{
							DrawRect(
								m_PosX,
								tmp_point,
								m_Width,
								m_OptionHeight,
								m_OptionUnselectedBackgroundColor);

							if (m_Smoothscroll)
							{
								DrawRect(
									m_PosX,
									scrollCurrent,
									m_Width,
									m_OptionHeight,
									m_OptionSelectedBackgroundColor);
							}
						}
						fullAmount = endPoint;
						tmp_base += m_OptionHeight;
					}
					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j)
					{
						currentSelected = sub->GetSelectedOption();

						DrawOption(sub->GetOption(i), sub, (i == sub->GetSelectedOption()));
					}
				}
			}

			DrawFooter();
			DrawDescription();
		}
	}

	void UIManager::CheckForInput()
	{
		ResetInput();

		m_OpenKeyPressed = IsKeyPressed(VK_F8);
		m_BackKeyPressed = IsKeyPressed(VK_BACK);
		m_EnterKeyPressed = IsKeyPressed(VK_RETURN);
		m_UpKeyPressed = IsKeyPressed(VK_UP);
		m_DownKeyPressed = IsKeyPressed(VK_DOWN);
		m_LeftKeyPressed = IsKeyPressed(VK_LEFT);
		m_RightKeyPressed = IsKeyPressed(VK_RIGHT);
	}

	void UIManager::HandleInput()
	{
		static auto openTicker = GetTickCount();
		if (m_OpenKeyPressed && GetTickCount() - openTicker >= static_cast<std::uint32_t>(m_OpenDelay))
		{
			openTicker = GetTickCount();
			m_Opened ^= true;

			if (m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		}

		static Timer backTimer(0ms);
		backTimer.SetDelay(std::chrono::milliseconds(m_BackDelay));
		if (m_Opened && m_BackKeyPressed && backTimer.Update())
		{
			if (m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

			if (m_SubmenuStack.size() <= 1)
			{
				m_Opened = false;
			}
			else
			{
				m_SubmenuStack.pop();
			}
		}

		if (m_Opened && !m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();

			static Timer enterTimer(0ms);
			enterTimer.SetDelay(std::chrono::milliseconds(m_EnterDelay));
			if (m_EnterKeyPressed && sub->GetNumOptions() != 0 && enterTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::EnterPress);
				}
			}

			static Timer upTimer(0ms);
			upTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
			if (m_UpKeyPressed && sub->GetNumOptions() != 0 && upTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->ScrollBackward();
			}

			static Timer downTimer(0ms);
			downTimer.SetDelay(std::chrono::milliseconds(m_VerticalDelay));
			if (m_DownKeyPressed && sub->GetNumOptions() != 0 && downTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->ScrollForward();
			}

			static Timer leftTimer(0ms);
			leftTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
			if (m_LeftKeyPressed && sub->GetNumOptions() != 0 && leftTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::LeftPress);
				}
			}

			static Timer rightTimer(0ms);
			rightTimer.SetDelay(std::chrono::milliseconds(m_HorizontalDelay));
			if (m_RightKeyPressed && sub->GetNumOptions() != 0 && rightTimer.Update())
			{
				if (m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::RightPress);
				}
			}
		}
	}

	void UIManager::ResetInput()
	{
		m_OpenKeyPressed = false;
		m_BackKeyPressed = false;
		m_EnterKeyPressed = false;
		m_UpKeyPressed = false;
		m_DownKeyPressed = false;
		m_LeftKeyPressed = false;
		m_RightKeyPressed = false;
	}

	void UIManager::DrawHeader(AbstractSubmenu* sub)
	{
		if (g_FullThemeLoading)
		{
			GET_YTDFullTheme(FullHeaderName + ".ytd");
			DrawSprite(
				FullHeaderName.c_str(),
				"Header",
				m_PosX - (m_HeaderGradientStretch / 2.f),
				m_DrawBaseY + (m_HeaderHeight / 2.f),
				m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
				m_HeaderHeight,
				{ 255, 255, 255, m_HeaderBackgroundColor.a },
				0);
		}
		else
		{
			switch (m_HeaderType)
			{
			case HeaderType::Static:
				DrawRect(
					m_PosX,
					m_DrawBaseY + (m_HeaderHeight / 2.f), m_Width,
					m_HeaderHeight,
					m_HeaderBackgroundColor);
				break;
			case HeaderType::Gradient:
				for (std::size_t i = 0; i < (m_HeaderGradientTransparent ? 1 : 20); ++i)
				{
					DrawSprite(
						"aircraft_dials",
						"aircraft_dials_g0",
						m_PosX - (m_HeaderGradientStretch / 2.f),
						m_DrawBaseY + (m_HeaderHeight / 2.f),
						m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
						m_HeaderHeight,
						m_HeaderGradientColorRight,
						m_HeaderGradientFlip ? 0.f : 180.f);
					DrawSprite(
						"aircraft_dials",
						"aircraft_dials_g0",
						m_PosX + (m_HeaderGradientStretch / 2.f),
						m_DrawBaseY + (m_HeaderHeight / 2.f),
						m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
						m_HeaderHeight,
						m_HeaderGradientColorLeft,
						m_HeaderGradientFlip ? 180.f : 0.f);
				}
				break;
			case HeaderType::YTD:
				GET_YTD(m_YTDName + ".ytd");
				DrawSprite(
					m_YTDName.c_str(),
					m_YTDName.c_str(),
					m_PosX - (m_HeaderGradientStretch / 2.f),
					m_DrawBaseY + (m_HeaderHeight / 2.f),
					m_Width + m_HeaderGradientStretch + m_HeaderGradientFiller,
					m_HeaderHeight,
					{ 255, 255, 255, m_HeaderBackgroundColor.a },
					0);
				break;
			}

			if (m_HeaderText)
			{
				if (TextKek)
				{
					DrawCenteredText(
						textkek.c_str(),
						m_PosX,
						m_DrawBaseY + (m_HeaderHeight / 2.f) - (GetTextHeight(m_HeaderFont, m_HeaderTextSize) / 2.f),
						m_HeaderTextSize,
						m_HeaderFont,
						m_HeaderTextColor,
						false, true);
				}
				else
				{
					DrawCenteredText(
						sub->GetName(),
						m_PosX,
						m_DrawBaseY + (m_HeaderHeight / 2.f) - (GetTextHeight(m_HeaderFont, m_HeaderTextSize) / 2.f),
						m_HeaderTextSize,
						m_HeaderFont,
						m_HeaderTextColor,
						false, true);
				}
			}
		}

		m_DrawBaseY += m_HeaderHeight;
	}

	void UIManager::DrawSubmenuBar(AbstractSubmenu* sub)
	{
		char leftText[64] = {};
		std::strncpy(&leftText[0], sub->GetName(), sizeof(leftText) - 1);
		std::transform(std::begin(leftText), std::end(leftText), std::begin(leftText), [](char c) { return static_cast<char>(toupper(c)); });

		char rightText[32] = {};
		std::snprintf(rightText, sizeof(rightText) - 1, "%zu / %zu", sub->GetSelectedOption() + 1, sub->GetNumOptions());

		if (g_FullThemeLoading)
		{
			GET_YTDFullTheme(FullHeaderName + ".ytd");
			DrawSprite(
				FullHeaderName.c_str(),
				"Subtitle",
				m_PosX,
				m_DrawBaseY + (m_SubmenuBarHeight / 2.f),
				m_Width, m_SubmenuBarHeight,
				m_SubmenuBarBackgroundColor, 0);
		}
		else
		{
			DrawRect(
				m_PosX,
				m_DrawBaseY + (m_SubmenuBarHeight / 2.f),
				m_Width, m_SubmenuBarHeight,
				m_SubmenuBarBackgroundColor);
		}
		DrawLeftText(
			&leftText[0],
			m_PosX - (m_Width / m_SubmenuBarPadding),
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f) - (GetTextHeight(m_SubmenuBarFont, m_SubmenuBarTextSize) / 1.5f),
			m_SubmenuBarTextSize, m_SubmenuBarFont,
			m_SubmenuBarTextColor,
			false, true);
		DrawRightText(
			&rightText[0],
			m_PosX + (m_Width / m_SubmenuBarPadding),
			m_DrawBaseY + (m_SubmenuBarHeight / 2.f) - (GetTextHeight(m_SubmenuBarFont, m_SubmenuBarTextSize) / 1.5f),
			m_SubmenuBarTextSize, m_SubmenuBarFont,
			m_SubmenuBarTextColor,
			false, true);

		m_DrawBaseY += m_SubmenuBarHeight;
	}

	void UIManager::DrawOption(AbstractOption* opt, AbstractSubmenu* sub, bool selected)
	{
		if (g_FullThemeLoading)
		{
			GET_YTDFullTheme(FullHeaderName + ".ytd");

			if (opt->GetFlag(OptionFlag::Enterable))
			{

				DrawSprite(
					FullHeaderName.c_str(),
					selected ? "SelectedSubmenu" : "UnselectedSubmenu",
					m_PosX + (m_Width / m_OptionPadding) - 0.01f,
					m_DrawBaseY + (m_OptionHeight / 2.f) + 0.011f - (GetTextHeight(Font::Monospace, m_OptionTextSize) / 1.725f),
					0.010f,
					0.020f,
					{ 255, 255, 255, 255 },
					0);

			}

			if (opt->GetFlag(OptionFlag::BoolOption))
			{

				if (ToggledOn)
				{
					DrawSprite(
						FullHeaderName.c_str(),
						"Enabled",
						m_PosX + (m_Width / m_OptionPadding) - 0.01f,
						m_DrawBaseY + (m_OptionHeight / 2.f) + 0.011f - (GetTextHeight(Font::Monospace, m_OptionTextSize) / 1.725f),
						0.010f,
						0.020f,
						{ 255, 255, 255, m_SelectedToggle.a },
						0);
				}
				else if (!ToggledOn)
				{
					DrawSprite(
						FullHeaderName.c_str(),
						"Disabled",
						m_PosX + (m_Width / m_OptionPadding) - 0.01f,
						m_DrawBaseY + (m_OptionHeight / 2.f) + 0.011f - (GetTextHeight(Font::Monospace, m_OptionTextSize) / 1.725f),
						0.010f,
						0.020f,
						{ 255, 255, 255, m_UnselectedToggle.a },
						0);
				}

			}
		}
		else
		{
			if (opt->GetFlag(OptionFlag::Enterable))
			{
				if (IndicatorIterator == 0)
				{
					DrawRightText(
						">",
						m_PosX + (m_Width / m_OptionPadding),
						m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(Font::Monospace, m_OptionTextSize) / 1.725f),
						m_OptionTextSize,
						Font::Monospace,
						selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
						false, false);
				}
				else if (IndicatorIterator == 1)
				{
					DrawRect(m_PosX + (m_Width / m_OptionPadding) + 0.003f,
						m_DrawBaseY + ((m_OptionHeight) / 2.f), 0.0055,
						m_OptionHeight,
						{ m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b, 190 });
				}
			}

			if (opt->GetFlag(OptionFlag::BoolOption))
			{
				auto res = GetSpriteScale(m_ToggleScale);
				if (ToggleIterator == 0)
				{
					if (ToggledOn)
					{
						GRAPHICS::DRAW_SPRITE("CommonMenu", "common_medal",
							g_UiManager->m_PosX + (g_UiManager->m_Width / g_UiManager->m_OptionPadding - 0.005f)
							, g_UiManager->m_DrawBaseY + (g_UiManager->m_OptionHeight / 2.f) - (g_UiManager->GetTextHeight(g_UiManager->m_OptionFont
								, g_UiManager->m_OptionTextSize) / 1.5f) + 0.014f
							, res.x, res.y, 0.0, m_SelectedToggle.r, m_SelectedToggle.g, m_SelectedToggle.b, m_SelectedToggle.a, 1);
					}
					else if (!ToggledOn)
					{
						GRAPHICS::DRAW_SPRITE("CommonMenu", "common_medal",
							g_UiManager->m_PosX + (g_UiManager->m_Width / g_UiManager->m_OptionPadding - 0.005f)
							, g_UiManager->m_DrawBaseY + (g_UiManager->m_OptionHeight / 2.f) - (g_UiManager->GetTextHeight(g_UiManager->m_OptionFont
								, g_UiManager->m_OptionTextSize) / 1.5f) + 0.014f
							, res.x, res.y, 0.0, m_UnselectedToggle.r, m_UnselectedToggle.g, m_UnselectedToggle.b, m_UnselectedToggle.a, 1);
					}
				}
				else if (ToggleIterator == 1)
				{
					if (ToggledOn)
					{
						GRAPHICS::DRAW_SPRITE("CommonMenu", "shop_box_tick",
							g_UiManager->m_PosX + (g_UiManager->m_Width / g_UiManager->m_OptionPadding - 0.005f)
							, g_UiManager->m_DrawBaseY + (g_UiManager->m_OptionHeight / 2.f) - (g_UiManager->GetTextHeight(g_UiManager->m_OptionFont
								, g_UiManager->m_OptionTextSize) / 1.5f) + 0.014f
							, res.x, res.y, 0.0, m_SelectedToggle.r, m_SelectedToggle.g, m_SelectedToggle.b, m_SelectedToggle.a, 1);
					}
					else if (!ToggledOn)
					{
						GRAPHICS::DRAW_SPRITE("CommonMenu", "shop_box_blank",
							g_UiManager->m_PosX + (g_UiManager->m_Width / g_UiManager->m_OptionPadding - 0.005f)
							, g_UiManager->m_DrawBaseY + (g_UiManager->m_OptionHeight / 2.f) - (g_UiManager->GetTextHeight(g_UiManager->m_OptionFont
								, g_UiManager->m_OptionTextSize) / 1.5f) + 0.014f
							, res.x, res.y, 0.0, m_UnselectedToggle.r, m_UnselectedToggle.g, m_UnselectedToggle.b, m_UnselectedToggle.a, 1);
					}
				}
			}
		}

		if (selected)
		{
			if (!m_Smoothscroll)
			{
				DrawRect(
					m_PosX,
					m_DrawBaseY + (m_OptionHeight / 2.f),
					m_Width,
					m_OptionHeight,
					m_OptionSelectedBackgroundColor);
			}
			else
			{
				scrollTarget = m_DrawBaseY + (m_OptionHeight / 2.f);
			}

		}

		DrawLeftText(
			opt->GetLeftText(),
			m_PosX - (m_Width / m_OptionPadding),
			m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
			m_OptionTextSize,
			m_OptionFont,
			selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
			false, false);

		DrawRightText(
			opt->GetRightText(),
			m_PosX + (m_Width / m_OptionPadding),
			m_DrawBaseY + (m_OptionHeight / 2.f) - (GetTextHeight(m_OptionFont, m_OptionTextSize) / 1.5f),
			m_OptionTextSize,
			m_OptionFont,
			selected ? m_OptionSelectedTextColor : m_OptionUnselectedTextColor,
			false, false);

		m_DrawBaseY += m_OptionHeight;
	}

	void UIManager::DrawFooter()
	{
		float size = m_FooterSpriteSize;
		float rotation = 0.f;
		const char* texture = "shop_arrows_upanddown";

		auto sizee = GetSpriteScale(size);

		if (g_FullThemeLoading)
		{
			GET_YTDFullTheme(FullHeaderName + ".ytd");
			DrawSprite(
				FullHeaderName.c_str(),
				"Footer",
				m_PosX,
				m_DrawBaseY + (m_FooterHeight / 2.f),
				m_Width,
				m_FooterHeight,
				{ 255, 255, 255, 255 }, 0);
		}
		else
		{
			DrawRect(
				m_PosX,
				m_DrawBaseY + (m_FooterHeight / 2.f),
				m_Width,
				m_FooterHeight,
				m_FooterBackgroundColor);
		}

		if (!m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();
			if (sub->GetSelectedOption() == 0)
			{
				rotation = 90.f;
				texture = "arrowright";
				size *= 0.8f;
			}
			else if (sub->GetSelectedOption() + 1 == sub->GetNumOptions())
			{
				rotation = 270.f;
				texture = "arrowright";
				size *= 0.8f;
			}
		}

		DrawSprite(
			"commonmenu",
			texture,
			m_PosX,
			m_DrawBaseY + (m_FooterHeight / 2.f),
			sizee.x,
			sizee.y,
			m_FooterSpriteColor,
			rotation);

		m_DrawBaseY += m_FooterHeight;
	}

	void UIManager::DrawDescription()
	{
		const char* description{};

		if (!m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();
			if (sub->GetNumOptions())
			{
				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					description = opt->GetDescription();
				}
			}
		}

		if (!description || !*description)
			return;

		m_DrawBaseY += m_DescriptionHeightPadding;

		DrawRect(
			m_PosX,
			m_DrawBaseY + (m_DescriptionHeight / 2.f),
			m_Width,
			m_DescriptionHeight,
			m_DescriptionBackgroundColor);

		auto spriteSize = GetSpriteScale(m_DescriptionSpriteSize);
		DrawSprite(
			"shared", "info_icon_32",
			m_PosX - (m_Width / m_DescriptionPadding) + (spriteSize.x / 2.f),
			m_DrawBaseY + (m_DescriptionHeight / 2.f),
			spriteSize.x,
			spriteSize.y,
			m_DescriptionSpriteColor,
			0.f
		);

		DrawLeftText(
			description,
			m_PosX - (m_Width / m_DescriptionPadding) + (spriteSize.x * 1.15f),
			m_DrawBaseY + (m_DescriptionHeight / 2.f) - (GetTextHeight(m_DescriptionFont, m_DescriptionTextSize) / 1.5f),
			m_DescriptionTextSize,
			m_DescriptionFont,
			m_DescriptionTextColor,
			false, false
		);

		m_DrawBaseY += m_DescriptionHeight;
	}

	void UIManager::DrawRect(float x, float y, float width, float height, Color color)
	{
		GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, color.a, 0);
	}

	void UIManager::DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation)
	{
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
		{
			GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, color.a, 0);
		}
		else
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
		}
	}

	void UIManager::DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_SCALE(size, size);
		HUD::SET_TEXT_FONT(static_cast<int>(font));
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (outline)
			HUD::SET_TEXT_OUTLINE();
		if (shadow)
			HUD::SET_TEXT_DROP_SHADOW();

		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
	}

	void UIManager::DrawCenteredText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_CENTRE(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	void UIManager::DrawRightText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_WRAP(0.f, x);
		HUD::SET_TEXT_RIGHT_JUSTIFY(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	void UIManager::Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
		}
		else
		{
			GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a, 0);
		}
	}

	float UIManager::GetTextHeight(Font font, float size)
	{
		return HUD::_GET_TEXT_SCALE_HEIGHT(size, static_cast<int>(font));
	}

	Vector2 UIManager::GetSpriteScale(float size)
	{
		int x;
		int y;
		GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);

		return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
	}

	bool UIManager::IsMouseLocked()
	{
		return m_Opened && m_MouseLocked;
	}

	Rectangle UIManager::GetMenuRect()
	{
		float height = m_HeaderHeight;
		height += m_SubmenuBarHeight;

		if (!m_SubmenuStack.empty())
		{
			height += m_OptionHeight * std::min(m_SubmenuStack.top()->GetNumOptions(), m_OptionsPerPage);
		}

		height += m_FooterHeight;

		return
		{
			{ m_PosX + (m_Width / 2.f), m_PosY + (height / 2.f) },
			{ m_Width, height }
		};
	}

	Vector2 UIManager::GetMousePos()
	{
		POINT point;
		GetCursorPos(&point);

		return Vector2{ static_cast<float>(point.x), static_cast<float>(point.y) };
	}

	void UIManager::PlayerInfoText(std::string text, RGBAF rgbaf, Font font, Vector2 position, Vector2 size, bool center, bool right)
	{
		HUD::SET_TEXT_RIGHT_JUSTIFY(right);
		HUD::SET_TEXT_CENTRE(center);
		HUD::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
		HUD::SET_TEXT_FONT(static_cast<int>(font));
		HUD::SET_TEXT_SCALE(size.x, size.y);
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, NULL);
	}

	void UIManager::PlayerBox(std::string name)
	{
		if (m_PosX > 0.5f)
			X_InfoFloat = m_PosX - 0.25f;
		else
			X_InfoFloat = m_PosX + 0.25f;

		//name
		GRAPHICS::DRAW_RECT(
			X_InfoFloat,
			m_PosY + 0.014f,
			0.26f, 0.0275f,
			0, 0, 0, 180,
			0.f);

		//name line
		GRAPHICS::DRAW_RECT(
			X_InfoFloat,
			m_PosY,
			0.26f, 0.001f,
			m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b, m_HeaderBackgroundColor.a,
			0.f);

		PlayerInfoText(name,
			{ 255, 255, 255, 255, 1 },
			Font::HouseScript,
			{ X_InfoFloat - 0.127f, m_PosY },
			GetSpriteScale(0.38f),
			0,
			0);

		//main line
		GRAPHICS::DRAW_RECT(
			X_InfoFloat,
			m_PosY + 0.035f,
			0.26f, 0.001f,
			m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b, m_HeaderBackgroundColor.a,
			0.f);


		Y_InfoFloat = m_PosY + 0.0492f;
	}

	void UIManager::PlayerInfo(std::string one, std::string two)
	{
		//main
		GRAPHICS::DRAW_RECT(
			X_InfoFloat,
			Y_InfoFloat - 0.001f,
			0.26f, 0.025f,
			0, 0, 0, 180,
			0.f);

		PlayerInfoText(one,
			{ 255,255,255,255 },
			Font::ChaletLondon,
			{ X_InfoFloat - 0.1265f, Y_InfoFloat - 0.01f },
			GetSpriteScale(0.25f),
			0,
			0);

		HUD::SET_TEXT_WRAP(0.f, X_InfoFloat + 0.125f);

		PlayerInfoText(two,
			{ 255,255,255,255 },
			Font::ChaletLondon,
			{ X_InfoFloat,
			Y_InfoFloat - 0.01f },
			GetSpriteScale(0.25f),
			false,
			true);

		Y_InfoFloat += 0.025f;
	}

	void UIManager::PlayerMultiInfo(std::string one, std::string two, std::string three, std::string four)
	{
		//main
		GRAPHICS::DRAW_RECT(
			X_InfoFloat,
			Y_InfoFloat - 0.001f,
			0.26f, 0.025f,
			0, 0, 0, 180,
			0.f);

		PlayerInfoText(one,
			{ 255,255,255,255 },
			Font::ChaletLondon,
			{ X_InfoFloat - 0.1265f, Y_InfoFloat - 0.01f },
			GetSpriteScale(0.25f),
			0,
			0);

		HUD::SET_TEXT_WRAP(0.f, X_InfoFloat - 0.0045f);

		PlayerInfoText(two,
			{ 255,255,255,255 },
			Font::ChaletLondon,
			{ X_InfoFloat - 0.0045f,
			Y_InfoFloat - 0.01f },
			GetSpriteScale(0.25f),
			false,
			true);

		//Divider
		DrawRect(
			X_InfoFloat,
			Y_InfoFloat,
			0.00125f,
			0.015f,
			{ 255, 255, 255, 255 });

		PlayerInfoText(three,
			{ 255,255,255,255 },
			Font::ChaletLondon,
			{ X_InfoFloat + 0.005f,
			Y_InfoFloat - 0.01f },
			GetSpriteScale(0.25f),
			0,
			0);

		HUD::SET_TEXT_WRAP(0.f, X_InfoFloat + 0.125f);

		PlayerInfoText(four,
			{ 255,255,255,255 },
			Font::ChaletLondon,
			{ X_InfoFloat + 0.125f,
			Y_InfoFloat - 0.01f },
			GetSpriteScale(0.25f),
			0,
			1);

		Y_InfoFloat += 0.025f;
	}

	void UIManager::HostMigrationManager()
	{
		if (yesyes4) {
			if (m_PosX > 0.5f)
				X_HostMigration = m_PosX - 0.18f;
			else
				X_HostMigration = m_PosX + 0.18f;

			PlayerInfoText("Host Queue",
				{ 255, 255, 255, 255, 1 },
				Font::HouseScript,
				{ X_HostMigration - 0.0475f, m_PosY },
				GetSpriteScale(0.38f),
				0,
				0);

			GRAPHICS::DRAW_RECT(X_HostMigration, m_PosY + 0.014f, 0.10f, 0.0255f, 0, 0, 0, 180, 0);

			//main line
			GRAPHICS::DRAW_RECT(
				X_HostMigration,
				m_PosY + 0.001f,
				0.10f, 0.001f,
				m_HeaderBackgroundColor.r, m_HeaderBackgroundColor.g, m_HeaderBackgroundColor.b, m_HeaderBackgroundColor.a,
				0.f);


			Y_HostMigration = m_PosY + 0.012f;
		}
	}

	void UIManager::DisplayInfoText(std::string text, RGBAF rgbaf, Vector2 position, float size, bool center, bool right)
	{
		HUD::SET_TEXT_RIGHT_JUSTIFY(right);
		HUD::SET_TEXT_CENTRE(center);
		HUD::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
		HUD::SET_TEXT_SCALE(0, size);
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, NULL);
	}

	void UIManager::GameInfo()
	{
		float size = 0.25f;
		float spaceing = 0.02f;

		float FRAMES = MISC::GET_FRAME_TIME();
		int FPS = (1.0f / FRAMES);
		char FPStext[60];
		snprintf(FPStext, sizeof(FPStext), "%d", FPS);

		int slots = 32 - NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
		char freeslots[32];
		snprintf(freeslots, sizeof(freeslots), "%d", slots);

		NativeVector3 playerPos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
		char _playercoords[32];
		snprintf(_playercoords, sizeof(_playercoords), "%d, %d, %d", (int)playerPos.x, (int)playerPos.y, (int)playerPos.z);

		if (g_Fps || g_FreeSlots || g_Position)
		{
			GRAPHICS::DRAW_RECT(X_GameInfo - 0.033f, Y_GameInfo + 0.002, .14, .003, 0, 0, 0, 255, 0);
		}

		if (g_Fps)
		{
			DisplayInfoText(TRANSLATE("FPS"),
				{ 255,255,255,255 },
				{ X_GameInfo - 0.102f, Y_GameInfo + 0.002f },
				size,
				0,
				0);

			HUD::SET_TEXT_WRAP(0.f, X_GameInfo + 0.035f);

			DisplayInfoText(FPStext,
				{ 255,255,255,255 },
				{ X_GameInfo + 0.01f,
				Y_GameInfo + 0.002f },
				size,
				false,
				true);

			GRAPHICS::DRAW_RECT(X_GameInfo - 0.033f, Y_GameInfo + 0.013, .14, .02, 0, 0, 0, 160, 0);
			Y_GameInfo += spaceing;
		}
		if (g_FreeSlots)
		{
			DisplayInfoText(TRANSLATE("Free Slots"),
				{ 255,255,255,255 },
				{ X_GameInfo - 0.102f, Y_GameInfo + 0.002f },
				size,
				0,
				0);

			HUD::SET_TEXT_WRAP(0.f, X_GameInfo + 0.035f);

			DisplayInfoText(freeslots,
				{ 255,255,255,255 },
				{ X_GameInfo + 0.01f,
				Y_GameInfo + 0.002f },
				size,
				false,
				true);

			GRAPHICS::DRAW_RECT(X_GameInfo - 0.033f, Y_GameInfo + 0.013, .14, .02, 0, 0, 0, 160, 0);
			Y_GameInfo += spaceing;
		}
		if (g_Position)
		{
			DisplayInfoText(TRANSLATE("Position"),
				{ 255,255,255,255 },
				{ X_GameInfo - 0.102f, Y_GameInfo + 0.002f },
				size,
				0,
				0);

			HUD::SET_TEXT_WRAP(0.f, X_GameInfo + 0.035f);

			DisplayInfoText(_playercoords,
				{ 255,255,255,255 },
				{ X_GameInfo + 0.01f,
				Y_GameInfo + 0.002f },
				size,
				false,
				true);

			GRAPHICS::DRAW_RECT(X_GameInfo - 0.033f, Y_GameInfo + 0.013, .14, .02, 0, 0, 0, 160, 0);
			Y_GameInfo += spaceing;
		}
		Y_GameInfo = 0.01;
	}

	void UIManager::HostMigrationText(std::string token)
	{
		if (yesyes4) {
			PlayerInfoText(token,
				{ 255,255,255,255 },
				Font::ChaletLondon,
				{ X_HostMigration - 0.0475f, Y_HostMigration + 0.0125f },
				GetSpriteScale(0.25f),
				0,
				0);

			GRAPHICS::DRAW_RECT(X_HostMigration, Y_HostMigration + 0.0265f, 0.10f, .0225f, 0, 0, 0, 180, 0);

			Y_HostMigration += 0.0225f;
		}
	}
}
