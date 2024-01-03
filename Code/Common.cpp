#include "Common.hpp"
#include "ImGui/imgui.h"
#include "UI/UIManager.hpp"

bool ToggledOn = false;

namespace Big
{
	void RGBColorWindow(bool show)
	{
		if (show)
		{
			ImGui::Begin("RGB Wheel");
			g_Settings.m_LockMouse = true;

			static Color a;

			static int ridindex = 0;
			static const char* actions[10] = { "Header Background", "Submenu Background", "Selected Background", "Unselected Background", "Footer", "Enabled Toggles", "Disabled Toggles", "Selected Text", "Unselected Text", "Footer Arrow"};
			static float color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };

			if (ImGui::Combo("Action", &ridindex, actions, sizeof(actions) / sizeof(*actions)))
			{
			}
			switch (ridindex)
			{
			case 0:
				g_UiManager->m_HeaderBackgroundColor.r = static_cast<int>(color[0] * 255);
				g_UiManager->m_HeaderBackgroundColor.g = static_cast<int>(color[1] * 0);
				g_UiManager->m_HeaderBackgroundColor.b = static_cast<int>(color[2] * 0);
				g_UiManager->m_HeaderBackgroundColor.a = static_cast<int>(color[3] * 255);
				break;
			case 1:
				g_UiManager->m_SubmenuBarBackgroundColor.r = static_cast<int>(color[0] * 255);
				g_UiManager->m_SubmenuBarBackgroundColor.g = static_cast<int>(color[1] * 255);
				g_UiManager->m_SubmenuBarBackgroundColor.b = static_cast<int>(color[2] * 255);
				g_UiManager->m_SubmenuBarBackgroundColor.a = static_cast<int>(color[3] * 255);
				break;
			case 2:
				g_UiManager->m_OptionSelectedBackgroundColor.r = static_cast<int>(color[0] * 255);
				g_UiManager->m_OptionSelectedBackgroundColor.g = static_cast<int>(color[1] * 255);
				g_UiManager->m_OptionSelectedBackgroundColor.b = static_cast<int>(color[2] * 255);
				g_UiManager->m_OptionSelectedBackgroundColor.a = static_cast<int>(color[3] * 255);
				break;
			case 3:
				g_UiManager->m_OptionUnselectedBackgroundColor.r = static_cast<int>(color[0] * 255);
				g_UiManager->m_OptionUnselectedBackgroundColor.g = static_cast<int>(color[1] * 255);
				g_UiManager->m_OptionUnselectedBackgroundColor.b = static_cast<int>(color[2] * 255);
				g_UiManager->m_OptionUnselectedBackgroundColor.a = static_cast<int>(color[3] * 255);
				break;
			case 4:
				g_UiManager->m_FooterBackgroundColor.r = static_cast<int>(color[0] * 255);
				g_UiManager->m_FooterBackgroundColor.g = static_cast<int>(color[1] * 255);
				g_UiManager->m_FooterBackgroundColor.b = static_cast<int>(color[2] * 255);
				g_UiManager->m_FooterBackgroundColor.a = static_cast<int>(color[3] * 255);
				break;
			case 5:
				g_UiManager->m_SelectedToggle.r = static_cast<int>(color[0] * 255);
				g_UiManager->m_SelectedToggle.g = static_cast<int>(color[1] * 255);
				g_UiManager->m_SelectedToggle.b = static_cast<int>(color[2] * 255);
				g_UiManager->m_SelectedToggle.a = static_cast<int>(color[3] * 255);
				break;
			case 6:
				g_UiManager->m_UnselectedToggle.r = static_cast<int>(color[0] * 255);
				g_UiManager->m_UnselectedToggle.g = static_cast<int>(color[1] * 255);
				g_UiManager->m_UnselectedToggle.b = static_cast<int>(color[2] * 255);
				g_UiManager->m_UnselectedToggle.a = static_cast<int>(color[3] * 255);
				break;
			case 7:
				g_UiManager->m_OptionSelectedTextColor.r = static_cast<int>(color[0] * 255);
				g_UiManager->m_OptionSelectedTextColor.g = static_cast<int>(color[1] * 255);
				g_UiManager->m_OptionSelectedTextColor.b = static_cast<int>(color[2] * 255);
				g_UiManager->m_OptionSelectedTextColor.a = static_cast<int>(color[3] * 255);
				break;
			case 8:
				g_UiManager->m_OptionUnselectedTextColor.r = static_cast<int>(color[0] * 255);
				g_UiManager->m_OptionUnselectedTextColor.g = static_cast<int>(color[1] * 255);
				g_UiManager->m_OptionUnselectedTextColor.b = static_cast<int>(color[2] * 255);
				g_UiManager->m_OptionUnselectedTextColor.a = static_cast<int>(color[3] * 255);
				break;
			case 9:
				g_UiManager->m_FooterSpriteColor.r = static_cast<int>(color[0] * 255);
				g_UiManager->m_FooterSpriteColor.g = static_cast<int>(color[1] * 255);
				g_UiManager->m_FooterSpriteColor.b = static_cast<int>(color[2] * 255);
				g_UiManager->m_FooterSpriteColor.a = static_cast<int>(color[3] * 255);
				break;
			}

			ImGui::ColorEdit4("Color", color);

			a.r = static_cast<int>(color[0] * 255);
			a.g = static_cast<int>(color[1] * 255);
			a.b = static_cast<int>(color[2] * 255);
			a.a = static_cast<int>(color[3] * 255);

			if (ImGui::Button("Close"))
			{
				g_Settings.m_EnableRGBWheel = false;
				g_Settings.m_LockMouse = false;
			}
			ImGui::End();
		}
	}

	void SettingNameWindowSomething()
	{
		if (g_Settings.m_EnableThemeWindow)
		{
			ImGui::Begin("#");
			g_Settings.m_LockMouse = true;
			static char rid[16];
			if (ImGui::InputText("Name", rid, IM_ARRAYSIZE(rid))) {}

			if (ImGui::Button("Create"))
			{
				g_UiManager->WriteNewConfig(rid);
				g_Settings.m_EnableThemeWindow = false;
				g_Settings.m_LockMouse = false;
			}
			ImGui::End();
		}
	}

	void ShowRIDWindow()
	{
		if (g_ShowRIDWindow)
		{
			ImGui::Begin("#Rid");
			g_Settings.m_LockMouse = true;
			static char rid[16];
			if (ImGui::InputText("Handle", rid, IM_ARRAYSIZE(rid))) {}

			if (ImGui::Button("Close"))
			{
				m_SCIDJoiner = atoi(rid);
				g_ShowRIDWindow = false;
				g_Settings.m_LockMouse = false;
			}
			ImGui::End();
		}
	}

	void ShowCustomText()
	{
		
	}

	void FuckIHateCodingRN()
	{
		if (spamstuffidc)
		{
			ImGui::Begin("#Custom Text");
			g_Settings.m_LockMouse = true;
			static char rid[25];
			if (ImGui::InputText("Text", rid, IM_ARRAYSIZE(rid))) {}

			if (ImGui::Button("Set"))
			{
				fuckingmessage = rid;
				spamstuffidc = false;
				g_Settings.m_LockMouse = false;
			}
			ImGui::End();
		}
	}


	std::vector<std::uintptr_t> name_address;
	std::vector<std::uintptr_t> get_name_address() { return name_address; }

#pragma execution_character_set("utf-8")
	void SetName(const std::string& name)
	{
		static std::uintptr_t name_ptr = Memory::get_multilayer_pointer(g_GameVariables->m_WorldPtr, { 0x08, 0x10C8, 0xA4 });

		if (name_address.empty())
		{
			std::string curr_mask;
			const char* name = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID());
			for (uint8_t i = 0; i < strlen(name); i++) curr_mask += "x";
			const char* mask = curr_mask.c_str();

			for (std::uintptr_t addr : Memory::get_string_addresses(name)) {
				char buff[100];
				_snprintf_s(buff, sizeof(buff), "OtherName\t\t 0x%p (0x%.8X)", addr, addr - Memory::get_base());
				name_address.push_back((addr));
			}

			if (name_ptr)
				name_address.push_back((name_ptr));
		}

		size_t newLen = name.size() + 1;
		if (newLen <= 1 || newLen > 20)
			return;

		char buffer[0x20] = {};
		char* source = (char*)PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()) + 0x5C;
		size_t	curLen = strlen(source) + 1;
		strncpy_s(buffer, source, curLen);

		for (uint32_t i = 0, found = 0, match = 0; found < 4; ++source)
		{
			if (*source != buffer[i])
				goto LABEL_RESET;

			if (++match < curLen)
			{
				++i;
				continue;
			}

			strncpy_s(source - i, newLen, &name[0], newLen);
			++found;

		LABEL_RESET:
			i = match = 0;
		}
		int size = get_name_address().size();
		int i = 0;
		for (std::uintptr_t Address : get_name_address()) {
			i++;
			strncpy((char*)Address, &name[0], newLen);
		}
	}

	void NameChangerWindow()
	{
		if (shownamechangerthing)
		{
			ImGui::Begin("#Custom Text");
			g_Settings.m_LockMouse = true;
			static char name[16];
			if (ImGui::InputText("Name", name, IM_ARRAYSIZE(name))) {}

			if (ImGui::Button("Set"))
			{
				SetName(name);
				shownamechangerthing = false;
				g_Settings.m_LockMouse = false;
				notifyMap(25, "Successfully spoofed your serversided name to %s", name);
			}

			ImGui::End();
		}
	}
}