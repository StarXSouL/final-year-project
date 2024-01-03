#include "MainScript.hpp"
#include "ScriptCallback.hpp"
#include "Lists.hpp"
#include "Natives.hpp"
#include "Timer.hpp"
#include "Translation.hpp"
#include "CustomText.hpp"
#include "UI/UIManager.hpp"
#include "UI/BoolOption.hpp"
#include "UI/ChooseOption.hpp"
#include "UI/NumberOption.hpp"
#include "UI/RegularOption.hpp"
#include "UI/SubOption.hpp"
#include "UI/RegularSubmenu.hpp"
#include "UI/PlayerSubmenu.hpp"
#include "Discord/DiscordHandler.hpp"
#include "Auth.hpp"

#include "obfuscator.h"
#include "meta_random.h"
#include <cpr/cpr.h>

using namespace Big::Lists;
using namespace UserInterface;

bool enabletextspam;

namespace Big
{

	bool MainScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType MainScript::GetType()
	{
		return ScriptType::Game;
	}

	void MainScript::Initialize()
	{
		//auth();

		if(true)
		{
			m_Initialized = true;
			g_Standard = true;
			g_Basic = true;
			g_Vip = true;
			g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_JOINING"), "Loading GTA Online with " BIGBASE_NAME "...");
			g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_QUITTING"), "Leaving with " BIGBASE_NAME "...");
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_QUIT_MP"), "Exiting GTA Online with " BIGBASE_NAME);
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_ENTER_MP"), "Play GTA Online with " BIGBASE_NAME);
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_EXIT_GAME"), "Quit GTA with" BIGBASE_NAME);
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_GO"), "Freemode with " BIGBASE_NAME);
			g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_MPREENTER"), "Joining a new session with " BIGBASE_NAME "...");
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_FRIEND_FM"), "Closed Friend Session with " BIGBASE_NAME "...");
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_GOTO_STORE"), "Purchase Shark Cards with " BIGBASE_NAME "...");
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_INF_EXIT"), "Quit to desktop with " BIGBASE_NAME "?");
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_CRESES"), "Joining A Crew Only Session with " BIGBASE_NAME "...");
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_INF_PGOB"), "Cut to the chase and	 head straight into the world of GTA Online with " BIGBASE_NAME "...");
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_INF_PGOT"), "Online w/ " BIGBASE_NAME "!");
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_INVO_FM"), "Join A Invite Only Session with " BIGBASE_NAME ".");
			g_CustomText->AddText(CONSTEXPR_JOAAT("LOADING_SPLAYER_L"), "Loading Story Mode with " BIGBASE_NAME "...");
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_NCREW_FM"), "Join A Crew Session with " BIGBASE_NAME ".");
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_CREW_FM"), "Join A Closed Crew Session with " BIGBASE_NAME ".");
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_SOLO_FM"), "Join A Solo Session with " BIGBASE_NAME ".");
			g_CustomText->AddText(CONSTEXPR_JOAAT("PM_FRESES"), "Join A Friends Only Session with " BIGBASE_NAME ".");
			g_CustomText->AddText(CONSTEXPR_JOAAT("MP_CHAT_ALL"), BIGBASE_NAME);

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Home"), SubmenuHome, [](RegularSubmenu* sub)
				{
					sub->AddOption<SubOption>(TRANSLATE("Player"), nullptr, SubmenuPlayer);
					sub->AddOption<SubOption>(TRANSLATE("Vehicle"), nullptr, SubmenuVehicle);
					sub->AddOption<SubOption>(TRANSLATE("Weapon"), nullptr, SubmenuWeapon);
					sub->AddOption<SubOption>(TRANSLATE("Network"), nullptr, SubmenuNetwork);
					sub->AddOption<SubOption>(TRANSLATE("World"), nullptr, SubmenuWorld);
					sub->AddOption<SubOption>(TRANSLATE("Teleports"), nullptr, SubmenuTeleports);
					sub->AddOption<SubOption>(TRANSLATE("Settings"), nullptr, SubmenuSettings);
					/*if (g_Staff) {
						sub->AddOption<SubOption>("Testing", nullptr, SubmenuTesting);
						sub->AddOption<BoolOption<bool>>("Log Script Events", nullptr, &g_LogScriptEvents, BoolDisplay::OnOff);
					}*/
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Testing", SubmenuTesting, [](RegularSubmenu* sub)
				{
					static int nignog{ 0 };
					sub->AddOption<NumberOption<int>>(TRANSLATE("Wanted Level"), nullptr, &nignog, 0, 30, 1, 3, true, "", "", [] { notifyMap(nignog, "hello!"); });

					sub->AddOption<RegularOption>("Test", nullptr, [] {
						Player plrMe = PLAYER::PLAYER_ID();
						if (PED::IS_PED_MODEL(plrMe, MISC::GET_HASH_KEY("player_zero")))
						{
							g_Logger->Info("F");
						}
						else if (PED::IS_PED_MODEL(plrMe, MISC::GET_HASH_KEY("player_one")))
						{
							g_Logger->Info("M");
						}
						else if (PED::IS_PED_MODEL(plrMe, MISC::GET_HASH_KEY("player_two")))
						{
							g_Logger->Info("T");
						}
						});

					sub->AddOption<RegularOption>("Test Input", nullptr, [] {
						g_UiManager->m_Opened = false;
						MISC::DISPLAY_ONSCREEN_KEYBOARD(0, "Spawn Vehicle", "", "", "", "", "", 25);

						g_CallbackScript->AddCallback<KeyBoardCallBack>("", 25, [] {
							g_VehSpawn = MISC::GET_ONSCREEN_KEYBOARD_RESULT();
							g_UiManager->m_Opened = true;
							g_VehicleSpawnByName = true;
							});
						});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Vehicle Spawner"), SubmenuTestStuff, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Type"), nullptr, &g_VehicleList->VehicleLists, &g_VehicleList->VehicleListPos);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Invincible"), nullptr, &g_SpawnInvinc, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Spawn In Veh"), nullptr, &g_SpawnInVeh, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Spawn Maxed"), nullptr, &g_SpawnMaxed, BoolDisplay::OnOff);
					//sub->AddOption<BoolOption<bool>>(TRANSLATE("Blip"), nullptr, &m_BlipVeh, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Add To Veh"), nullptr, &g_AddToList, BoolDisplay::OnOff);
					switch (g_VehicleList->VehicleListPos) {
					case 0:
						for (const char* car : g_VehicleList->Super) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 1:
						for (const char* car : g_VehicleList->Sports) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 2:
						for (const char* car : g_VehicleList->SportsClassic) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 3:
						for (const char* car : g_VehicleList->Sedans) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 4:
						for (const char* car : g_VehicleList->Motorcycles) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 5:
						for (const char* car : g_VehicleList->Cycles) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 6:
						for (const char* car : g_VehicleList->Helicopters) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 7:
						for (const char* car : g_VehicleList->Planes) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 8:
						for (const char* car : g_VehicleList->Boats) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 9:
						for (const char* car : g_VehicleList->Military) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 10:
						for (const char* car : g_VehicleList->Emergency) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 11:
						for (const char* car : g_VehicleList->Commercials) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 12:
						for (const char* car : g_VehicleList->Muscle) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 13:
						for (const char* car : g_VehicleList->OffRoad) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 14:
						for (const char* car : g_VehicleList->SUVs) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 15:
						for (const char* car : g_VehicleList->OpenWheel) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 16:
						for (const char* car : g_VehicleList->Trailer) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 17:
						for (const char* car : g_VehicleList->Trains) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 18:
						for (const char* car : g_VehicleList->Service) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 19:
						for (const char* car : g_VehicleList->Utility) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 20:
						for (const char* car : g_VehicleList->Vans) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 21:
						for (const char* car : g_VehicleList->Industrial) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 22:
						for (const char* car : g_VehicleList->Coupes) {
							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					case 23:
						for (const char* car : g_VehicleList->Compacts) {
							/*if (sub->GetSelectedOption() == sub->GetNumOptions()) {
								std::string pic[2] = { "**Invalid**", "**Invalid**" };
								for (int i = 0; i < 267; i++)
								{
									if (car == VehiclePreviews[i].vehicleName) {
										pic[0] = VehiclePreviews[i].vehiclePreviewDict;
										pic[1] = VehiclePreviews[i].vehicleName;
										break;
									}
								}
								DisplayVehicle(pic[0], pic[1]);
							}*/

							const char* name_veh = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(car)));
							sub->AddOption<RegularOption>(name_veh, nullptr, [car] {  SpawnVehicle(MISC::GET_HASH_KEY(car)); });
						}
						break;
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Acrobatics"), SubmenuVehicleAcrobatics, [](RegularSubmenu* sub)
				{
					sub->AddOption<RegularOption>(("Front Flip"), nullptr, [=] { vehicle_acrobatics(2); });
					sub->AddOption<RegularOption>(("Side Flip"), nullptr, [=] { vehicle_acrobatics(1); });
					sub->AddOption<RegularOption>(("Back Flip"), nullptr, [=] { vehicle_acrobatics(3); });
					sub->AddOption<RegularOption>(("Bunny Hop"), nullptr, [=] { vehicle_acrobatics(0); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Ramps"), SubmenuVehicleRampBuilder, [](RegularSubmenu* sub)
				{
					static bool m_Rampfront;
					static bool m_Rampback;
					static bool m_Rampleft;
					static bool m_Rampright;
					sub->AddOption<BoolOption<bool>>(("Front"), nullptr, &m_Rampfront, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(("Back"), nullptr, &m_Rampback, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(("Left"), nullptr, &m_Rampleft, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(("Right"), nullptr, &m_Rampright, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<RegularOption>(("Create"), nullptr, [] { VehicleRamp(m_Rampfront, m_Rampback, m_Rampleft, m_Rampright); });
					sub->AddOption<RegularOption>(("Delete"), nullptr, [] {
						for (int i = 0; i < 4; i++)
						{
							static Hash ramp = MISC::GET_HASH_KEY("lts_prop_lts_ramp_01");
							NativeVector3 pedpos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
							Object ObjToDelete = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pedpos.x, pedpos.y, pedpos.z, 10.f, ramp, 0, 1, 1);
							OBJECT::DELETE_OBJECT(&ObjToDelete);
						}
						});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Manipulation"), SubmenuPOV, [](RegularSubmenu* sub)
				{
					//sub->AddOption<NumberOption<float>>(TRANSLATE("3D Manipulation"), nullptr, &Dimensions, 0.f, 100.f, 5.f, 1);
					sub->AddOption<NumberOption<float>>(TRANSLATE("POV Manipulation"), nullptr, &POV, 0.f, 2.f, 0.001, 5);
					sub->AddOption<RegularOption>(TRANSLATE("Reset"), nullptr, [] {
						static uintptr_t ModuleBaseAdress = (uintptr_t)GetModuleHandle(NULL);
						Dimensions = { 0.001 };
						POV = { 0.01745329238f };
						//*(float*)FindAddy(ModuleBaseAdress + 0x2812EBC, {}) = Dimensions;
						*(float*)FindAddy(ModuleBaseAdress + 0x1908B2C, {}) = POV;
						});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Ramp Builder"), SubmenuRampBuilder, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Object:"), nullptr, &RampTypes, &RampIndex);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Amount"), nullptr, &g_RampCount, 1, 50, 1);
					sub->AddOption<RegularOption>(TRANSLATE("Create"), nullptr, [] { Ramp(); });
					sub->AddOption<RegularOption>(TRANSLATE("Delete"), nullptr, [] { DeleteRamp(); });
				});

			static uintptr_t ModuleBaseAdress = (uintptr_t)GetModuleHandle(NULL);

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Water"), SubmenuWaterMain, [](RegularSubmenu* sub)
				{
					sub->AddOption<SubOption>(TRANSLATE("Tuning"), nullptr, SubmenuWaterTune);
					//sub->AddOption<SubOption>(TRANSLATE("Quads"), nullptr, SubmenuWaterQuads);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Tune"), SubmenuWaterTune, [](RegularSubmenu* sub)
				{
					static CWaterTune* WaterTune = reinterpret_cast<CWaterTune*>(0x1D20874 + ModuleBaseAdress);
					sub->AddOption<NumberOption<float>>("Ripple Scale", nullptr, &WaterTune->fRippleScale, -10.0f, 10.0f, 0.1f);
					sub->AddOption<NumberOption<float>>("Foam Scale", nullptr, &WaterTune->fOceanFoamScale, -10.0f, 10.0f, 0.1f);
					sub->AddOption<NumberOption<float>>("Specular Falloff", nullptr, &WaterTune->fSpecularFalloff, 800.0f, 1200.0f, 0.5f);
					sub->AddOption<NumberOption<float>>("Pierce Intensity", nullptr, &WaterTune->fFodPierceIntensity, -100.0f, 100.0f, 0.25f);
					sub->AddOption<NumberOption<float>>("Refraction Blend", nullptr, &WaterTune->fRefractionBlend, -10.0f, 10.0f, 0.1f);
					sub->AddOption<NumberOption<float>>("Refraction Exponent", nullptr, &WaterTune->fRefractionExponent, -10.0f, 10.0f, 0.1f);
					sub->AddOption<NumberOption<float>>("Cycle Depth", nullptr, &WaterTune->fWaterCycleDepth, -1000.0f, 1000.0f, 1.0f);
					sub->AddOption<NumberOption<float>>("Cycle Fade", nullptr, &WaterTune->fWaterCycleFade, -1000.0f, 1000.0f, 1.0f);
					sub->AddOption<NumberOption<float>>(OBFUSCATE("Lightning Depth"), nullptr, &WaterTune->fWaterLightningDepth, -1000.0f, 1000.0f, 1.0f);
					sub->AddOption<NumberOption<float>>(OBFUSCATE("Lightning Fade"), nullptr, &WaterTune->fWaterLightningFade, -1000.0f, 1000.0f, 1.0f);
					sub->AddOption<NumberOption<float>>("Mod Depth", nullptr, &WaterTune->fDeepWaterModDepth, -1000.0f, 1000.0f, 1.0f);
					sub->AddOption<NumberOption<float>>("Mod Fade", nullptr, &WaterTune->fDeepWaterModFade, -1000.0f, 1000.0f, 1.0f);
					sub->AddOption<NumberOption<float>>("Rays Lerp Start", nullptr, &WaterTune->fGodRaysLerpStart, -1000.0f, 1000.0f, 1.0f);
					sub->AddOption<NumberOption<float>>("Rays Lerp End", nullptr, &WaterTune->fGodRaysLerpEnd, -1000.0f, 1000.0f, 1.0f);
					sub->AddOption<NumberOption<float>>("Foam Scale", nullptr, &WaterTune->fDisturbFoamScale, -10.0f, 10.0f, 0.1f);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Quads"), SubmenuWaterQuads, [](RegularSubmenu* sub)
				{
					static CWaterDataItem* Water = (CWaterDataItem*)(*(std::uintptr_t*)(0x22A1150 + ModuleBaseAdress) + (1 * 0x1C));
					static __int16 iMinX{ Water->iMinX }; //0x0000 X Coord 1
					static __int16 iMinY{ Water->iMinY }; //0x0002  Y Coord 1
					static __int16 iMaxX{ Water->iMaxX }; //0x0004 X Coord 2
					static __int16 iMaxY{ Water->iMaxY }; //0x0006 Y Coord 2
					static __int8 iAlphaSW{ Water->iAlphaSW }; //0x0008  (South West, default 26)
					static __int8 iAlphaSE{ Water->iAlphaSE }; //0x0009  (South East, default 26)
					static __int8 iAlphaNW{ Water->iAlphaNW }; //0x000A  (North West, default 26)
					static __int8 iAlphaNE{ Water->iAlphaNE }; //0x000B  (North East, default 26)
					static float fHeight{ Water->fHeight }; //0x0014 (Z-Height, default 0.0)
					static BYTE bHasLimitedDepth{ Water->bHasLimitedDepth }; //0x0018  (Second bit [binary 10] = On, gives the water quad an effective range of 6 z-points)
					sub->AddOption<RegularOption>(TRANSLATE("No Water"), nullptr, [=] {
						for (int i = 0; i < 821; i++) {
							CWaterDataItem* Water = (CWaterDataItem*)(*(std::uintptr_t*)(0x22B6DD0 + ModuleBaseAdress) + (i * 0x1C));
							Water->fHeight = -1000.f;
						}
						});
					sub->AddOption<RegularOption>(TRANSLATE("Raise Water"), nullptr, [=] {
						for (int i = 0; i < 821; i++) {
							CWaterDataItem* Water = (CWaterDataItem*)(*(std::uintptr_t*)(0x22B6DD0 + ModuleBaseAdress) + (i * 0x1C));
							Water->fHeight = 1000.f;
						}
						});
					sub->AddOption<RegularOption>(TRANSLATE("Transparrent Water"), nullptr, [=] {
						CWaterTune* WaterTune = reinterpret_cast<CWaterTune*>(0x1D20874 + ModuleBaseAdress);
						WaterTune->fDisturbFoamScale = 0.0f;
						for (int i = 0; i < 821; i++) {
							CWaterDataItem* Water = (CWaterDataItem*)(*(std::uintptr_t*)(0x22B6DD0 + ModuleBaseAdress) + (i * 0x1C));
							Water->iAlphaNE = 0;
							Water->iAlphaNW = 0;
							Water->iAlphaSE = 0;
							Water->iAlphaSW = 0;
						}
						});
					sub->AddOption<RegularOption>(TRANSLATE("Opaque Water"), nullptr, [=] {
						for (int i = 0; i < 821; i++) {
							CWaterDataItem* Water = (CWaterDataItem*)(*(std::uintptr_t*)(0x22B6DD0 + ModuleBaseAdress) + (i * 0x1C));
							Water->iAlphaNE = -1;
							Water->iAlphaNW = -1;
							Water->iAlphaSE = -1;
							Water->iAlphaSW = -1;
						}
						});
					sub->AddOption<RegularOption>(TRANSLATE("Default Water"), nullptr, [=] {
						CWaterTune* WaterTune = reinterpret_cast<CWaterTune*>(0x1D20874 + ModuleBaseAdress);
						WaterTune->fDisturbFoamScale = 0.05f;
						for (int i = 0; i < 821; i++) {
							CWaterDataItem* Water = (CWaterDataItem*)(*(std::uintptr_t*)(0x22B6DD0 + ModuleBaseAdress) + (i * 0x1C));
							Water->iAlphaNE = 26;
							Water->iAlphaNW = 26;
							Water->iAlphaSE = 26;
							Water->iAlphaSW = 26;
							Water->fHeight = 0;
						}
						});
					sub->AddOption<NumberOption<__int16>>("Min X", nullptr, &iMinX, -10000, 10000, 10, 0);
					sub->AddOption<NumberOption<__int16>>("Min Y", nullptr, &iMinY, -10000, 10000, 10, 0);
					sub->AddOption<NumberOption<__int16>>("Max X", nullptr, &iMaxX, -10000, 10000, 10, 0);
					sub->AddOption<NumberOption<__int16>>("Max Y", nullptr, &iMaxY, -10000, 10000, 10, 0);
					sub->AddOption<NumberOption<__int8>>("Alpha South West", nullptr, &iAlphaSW, -1000, 1000, 25, 0);
					sub->AddOption<NumberOption<__int8>>("Alpha South East", nullptr, &iAlphaSE, -1000, 1000, 25, 0);
					sub->AddOption<NumberOption<__int8>>("Alpha North West", nullptr, &iAlphaNW, -1000, 1000, 25);
					sub->AddOption<NumberOption<__int8>>("Alpha North East", nullptr, &iAlphaNE, -1000, 1000, 25);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Height"), nullptr, &fHeight, -1000.f, 10000.f, 250.f);
					sub->AddOption<NumberOption<BYTE>>(TRANSLATE("Limited Depth"), nullptr, &bHasLimitedDepth, -10.f, 10, 1);
					sub->AddOption<RegularOption>(TRANSLATE("Apply Data"), nullptr, [=] {
						for (int i = 0; i < 821; i++) {
							CWaterDataItem* Water = (CWaterDataItem*)(*(std::uintptr_t*)(0x22B6DD0 + ModuleBaseAdress) + (i * 0x1C));
							Water->iMinX = iMinX;
							Water->iMinY = iMinY;
							Water->iMaxX = iMaxX;
							Water->iMaxY = iMaxY;
							Water->iAlphaNE = iAlphaNE;
							Water->iAlphaNW = iAlphaNW;
							Water->iAlphaSE = iAlphaSE;
							Water->fHeight = fHeight;
							Water->bHasLimitedDepth = bHasLimitedDepth;
						}
						});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("World"), SubmenuWorld, [](RegularSubmenu* sub)
				{
					sub->AddOption<RegularOption>(TRANSLATE("Skip Cutscene"), nullptr, [] { CUTSCENE::STOP_CUTSCENE_IMMEDIATELY(); });
					//sub->AddOption<SubOption>(TRANSLATE("Sky Color"), nullptr, SubmenuSkyColor);
					//sub->AddOption<SubOption>(("Precipitation"), nullptr, PrecipitationSubmenu);
					//sub->AddOption<SubOption>(TRANSLATE("Manipulation"), nullptr, SubmenuPOV);
					//sub->AddOption<SubOption>(TRANSLATE("Clouds"), nullptr, SubmenuClouds);
					sub->AddOption<SubOption>(TRANSLATE("Weather"), nullptr, SubmenuWeather);
					sub->AddOption<SubOption>(TRANSLATE("Time"), nullptr, SubmenuTime);
					sub->AddOption<SubOption>(TRANSLATE("Map Color"), nullptr, SubmenuSpotlight);
					sub->AddOption<SubOption>(TRANSLATE("Ramp Builder"), nullptr, SubmenuRampBuilder);
					//sub->AddOption<SubOption>(TRANSLATE("Water"), nullptr, SubmenuWaterMain);
					//sub->AddOption<SubOption>(("Black Hole"), nullptr, SubmenuBlackHole);
					sub->AddOption<SubOption>(("Police Mode"), nullptr, SubmenuPolice);
					/*sub->AddOption<BoolOption<bool>>(("Low Graphics"), nullptr, &g_Utility->g_low_graphics, BoolDisplay::OnOff, []
						{
							if(g_Utility->g_low_graphics){}
							else
							{
								STREAMING::CLEAR_FOCUS();
							}
						});*/
						//sub->AddOption<BoolOption<bool>>(("Dominos"), nullptr, &g_dominos, BoolDisplay::OnOff);
						//sub->AddOption<NumberOption<float>>(TRANSLATE("Rain Level:"), nullptr, &g_Rain, 0, 1000, 1.5, 2, false);
						//sub->AddOption<NumberOption<float>>(TRANSLATE("Wave Level:"), nullptr, &g_Waves, 0, 1000, 1.5, 2, false);
						//sub->AddOption<NumberOption<float>>(TRANSLATE("Wind Level:"), nullptr, &g_Wind, 0, 1000, 1.5, 2, false);
						//sub->AddOption<NumberOption<float>>(TRANSLATE("Cloud Alpha"), nullptr, &g_Clouds, 0, 1000, 0.10, 2, false);
						////sub->AddOption<NumberOption<float>>(TRANSLATE("Sky Alpha"), nullptr, &SkyIntensity, -1.f, 1000, 0.25f, 2);
						////sub->AddOption<NumberOption<float>>(TRANSLATE("Saturation"), nullptr, &Saturation, -10.f, 255.f, 0.1f, 2);
						//sub->AddOption<NumberOption<float>>(TRANSLATE("Fog"), nullptr, &Fog, 0.f, 2.f, 0.00002, 5);
						//sub->AddOption<NumberOption<float>>(TRANSLATE("Distance to Sun"), nullptr, &Sun, 0.f, 2.f, 0.001, 3);
						//sub->AddOption<RegularOption>(TRANSLATE("Reset Game Variables"), nullptr, [] {
						//	Saturation = { 1.f };
						//	Fog = { 0.f };
						//	Sun = { 0.001 };
						//	SkyIntensity = { 1.f };
						//	*(float*)FindAddy(ModuleBaseAdress + 0x284CC08, {}) = SkyIntensity;
						//	*(float*)FindAddy(ModuleBaseAdress + 0x284CC0C, {}) = Saturation;
						//	*(float*)FindAddy(ModuleBaseAdress + 0x19C4E60, {}) = Fog;
						//	*(float*)FindAddy(ModuleBaseAdress + 0x19C4E64, {}) = Sun;
						//	});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Police Mode", SubmenuPolice, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>("Peds Pullover", nullptr, &g_Pedspullover, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>("Emulate Police", nullptr, &g_EmulatePolice, BoolDisplay::OnOff);
					sub->AddOption<RegularOption>("Police Outfit", nullptr, [] { Policemode(); });
					sub->AddOption<RegularOption>("Police Vehicle", nullptr, [] { SpawnVehicle(MISC::GET_HASH_KEY("Police")); });
					sub->AddOption<RegularOption>("Get Nightstick", nullptr, [] { WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("weapon_nightstick"), 1, 1); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Black Hole"), SubmenuBlackHole, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(("Enable"), nullptr, &g_black_hole, BoolDisplay::OnOff);
					sub->AddOption<RegularOption>(("Set Black Hole"), nullptr, [=]
						{
							g_black_hole_pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
						});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Map Color"), SubmenuSpotlight, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &g_EnableLight, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Rainbow"), nullptr, &g_RGBLight, BoolDisplay::OnOff);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Intensity"), nullptr, &g_LigtIntensity, 0, 100, 2, false);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Red"), nullptr, &g_LightRed, 0, 255, 1);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Green"), nullptr, &g_LightGreen, 0, 255, 1);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Blue"), nullptr, &g_LightBlue, 0, 255, 1);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Sky Color"), SubmenuSkyColor, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Quadrant"), nullptr, &SkyColor2, &_SkyColor2);
					switch (_SkyColor2)
					{
					case 0:
						sub->AddOption<NumberOption<float>>(TRANSLATE("Red"), nullptr, &m_AzimuthEastRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { AzimuthEastColorBypass(); AzimuthEastColor(m_AzimuthEastRed, m_AzimuthEastGreen, m_AzimuthEastBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Green"), nullptr, &m_AzimuthEastGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { AzimuthEastColorBypass(); AzimuthEastColor(m_AzimuthEastRed, m_AzimuthEastGreen, m_AzimuthEastBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Blue"), nullptr, &m_AzimuthEastBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { AzimuthEastColorBypass(); AzimuthEastColor(m_AzimuthEastRed, m_AzimuthEastGreen, m_AzimuthEastBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Intensity"), nullptr, &m_AzimuthEastIntensity, 1.f, 5.f, 0.1f, 1, true, "", "", [] { AzimuthEastColor(m_AzimuthEastRed, m_AzimuthEastGreen, m_AzimuthEastBlue); });
						sub->AddOption<BoolOption<bool>>(TRANSLATE("Rainbow"), nullptr, &m_RainbowAzimuthEast, BoolDisplay::OnOff, false, [] { AzimuthEastColorBypass(); });
						sub->AddOption<RegularOption>(TRANSLATE("Default"), nullptr, [] { std::copy_n("\x0F\x29\x62\x20", 4, g_GameFunctions->m_WeatherBypass); });
						break;
					case 1:
						sub->AddOption<NumberOption<float>>(TRANSLATE("Red"), nullptr, &m_AzimuthWestRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { AzimuthWestColorBypass(); AzimuthWestColor(m_AzimuthWestRed, m_AzimuthWestGreen, m_AzimuthWestBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Green"), nullptr, &m_AzimuthWestGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { AzimuthWestColorBypass(); AzimuthWestColor(m_AzimuthWestRed, m_AzimuthWestGreen, m_AzimuthWestBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Blue"), nullptr, &m_AzimuthWestBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { AzimuthWestColorBypass(); AzimuthWestColor(m_AzimuthWestRed, m_AzimuthWestGreen, m_AzimuthWestBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Intensity"), nullptr, &m_AzimuthWestIntensity, 1.f, 5.f, 0.1f, 1, true, "", "", [] { AzimuthWestColor(m_AzimuthWestRed, m_AzimuthWestGreen, m_AzimuthWestBlue); });
						sub->AddOption<BoolOption<bool>>(TRANSLATE("Rainbow"), nullptr, &m_RainbowAzimuthWest, BoolDisplay::OnOff, false, [] { AzimuthWestColorBypass(); });
						sub->AddOption<RegularOption>(TRANSLATE("Default"), nullptr, [] { std::copy_n("\x0F\x14\xE3\x0F\x29\x62\x50", 7, g_GameFunctions->m_WeatherBypass2); }); //GTA5.exe+E3AE11 - 0F29 A2 80000000     

						break;
					case 2:
						sub->AddOption<NumberOption<float>>(TRANSLATE("Red"), nullptr, &m_AzimuthTransitionRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { AzimuthTransitionColorBypass(); AzimuthTransitionColor(m_AzimuthTransitionRed, m_AzimuthTransitionGreen, m_AzimuthTransitionBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Green"), nullptr, &m_AzimuthTransitionGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { AzimuthTransitionColorBypass(); AzimuthTransitionColor(m_AzimuthTransitionRed, m_AzimuthTransitionGreen, m_AzimuthTransitionBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Blue"), nullptr, &m_AzimuthTransitionBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { AzimuthTransitionColorBypass(); AzimuthTransitionColor(m_AzimuthTransitionRed, m_AzimuthTransitionGreen, m_AzimuthTransitionBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Intensity"), nullptr, &m_AzimuthTransitionIntensity, 1.f, 5.f, 0.1f, 1, true, "", "", [] { AzimuthTransitionColor(m_AzimuthTransitionRed, m_AzimuthTransitionGreen, m_AzimuthTransitionBlue); });
						sub->AddOption<BoolOption<bool>>(TRANSLATE("Rainbow"), nullptr, &m_RainbowAzimuthTransition, BoolDisplay::OnOff, false, [] { AzimuthTransitionColorBypass(); });
						sub->AddOption<RegularOption>(TRANSLATE("Default"), nullptr, [] {  std::copy_n("\x0F\x29\xA2\x80\x00\x00\x00", 7, g_GameFunctions->m_WeatherBypass5); });
						break;
					case 3:
						sub->AddOption<NumberOption<float>>(TRANSLATE("Red"), nullptr, &m_CloudBaseRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { CloudBaseColorBypass(); CloudBaseColor(m_CloudBaseRed, m_CloudBaseGreen, m_CloudBaseBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Green"), nullptr, &m_CloudBaseGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { CloudBaseColorBypass(); CloudBaseColor(m_CloudBaseRed, m_CloudBaseGreen, m_CloudBaseBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Blue"), nullptr, &m_CloudBaseBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { CloudBaseColorBypass(); CloudBaseColor(m_CloudBaseRed, m_CloudBaseGreen, m_CloudBaseBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Intensity"), nullptr, &m_CloudBaseIntensity, 1.f, 5.f, 0.1f, 1, true, "", "", [] { CloudBaseColor(m_CloudBaseRed, m_CloudBaseGreen, m_CloudBaseBlue); });
						sub->AddOption<BoolOption<bool>>(TRANSLATE("Rainbow"), nullptr, &m_RainbowCloudBase, BoolDisplay::OnOff, false, [] { CloudBaseColorBypass(); });
						sub->AddOption<RegularOption>(TRANSLATE("Default"), nullptr, [] { std::copy_n("\x0F\x29\x8B\x60\x03\x00\x00", 7, g_GameFunctions->m_WeatherBypass6); });
						break;
					case 4:
						sub->AddOption<NumberOption<float>>(TRANSLATE("Red"), nullptr, &m_CloudMidRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { CloudMidColorBypass(); CloudMidColor(m_CloudMidRed, m_CloudMidGreen, m_CloudMidBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Green"), nullptr, &m_CloudMidGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { CloudMidColorBypass(); CloudMidColor(m_CloudMidRed, m_CloudMidGreen, m_CloudMidBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Blue"), nullptr, &m_CloudMidBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { CloudMidColorBypass(); CloudMidColor(m_CloudMidRed, m_CloudMidGreen, m_CloudMidBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Intensity"), nullptr, &m_CloudMidIntensity, 1.f, 5.f, 0.1f, 1, true, "", "", [] { CloudMidColor(m_CloudMidRed, m_CloudMidGreen, m_CloudMidBlue); });
						sub->AddOption<BoolOption<bool>>(TRANSLATE("Rainbow"), nullptr, &m_RainbowCloudMid, BoolDisplay::OnOff, false, [] { CloudMidColorBypass(); });
						sub->AddOption<RegularOption>(TRANSLATE("Default"), nullptr, [] {  std::copy_n("\x0F\x29\xA2\x80\x03\x00\x00", 7, g_GameFunctions->m_WeatherBypass7); });
						break;
					case 5:
						sub->AddOption<NumberOption<float>>(TRANSLATE("Red"), nullptr, &m_MoonRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { MoonColorBypass(); MoonColor(m_MoonRed, m_MoonGreen, m_MoonBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Green"), nullptr, &m_MoonGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { MoonColorBypass(); MoonColor(m_MoonRed, m_MoonGreen, m_MoonBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Blue"), nullptr, &m_MoonBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { MoonColorBypass(); MoonColor(m_MoonRed, m_MoonGreen, m_MoonBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Intensity"), nullptr, &m_MoonIntensity, 1.f, 5.f, 0.1f, 1, true, "", "", [] { MoonColor(m_MoonRed, m_MoonGreen, m_MoonBlue); });
						sub->AddOption<BoolOption<bool>>(TRANSLATE("Rainbow"), nullptr, &m_RainbowMoon, BoolDisplay::OnOff, false, [] { MoonColorBypass(); });
						sub->AddOption<RegularOption>(TRANSLATE("Default"), nullptr, [] {  std::copy_n("\x0F\x29\x82\x50\x05\x00\x00", 7, g_GameFunctions->m_WeatherBypass3); });
						break;
					case 6:
						sub->AddOption<NumberOption<float>>(TRANSLATE("Red"), nullptr, &m_SunRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { SunColorBypass(); SunColor(m_SunRed, m_SunGreen, m_SunBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Green"), nullptr, &m_SunGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { SunColorBypass(); SunColor(m_SunRed, m_SunGreen, m_SunBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Blue"), nullptr, &m_SunBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { SunColorBypass(); SunColor(m_SunRed, m_SunGreen, m_SunBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Intensity"), nullptr, &m_SunIntensity, 1.f, 5.f, 0.1f, 1, true, "", "", [] { SunColor(m_SunRed, m_SunGreen, m_SunBlue); });
						sub->AddOption<BoolOption<bool>>(TRANSLATE("Rainbow"), nullptr, &m_RainbowSun, BoolDisplay::OnOff, false, [] { SunColorBypass(); });
						sub->AddOption<RegularOption>(TRANSLATE("Default"), nullptr, [] {  std::copy_n("\x0F\x29\x82\xC0\x01\x00\x00", 7, g_GameFunctions->m_WeatherBypass4); });
						break;
					case 7:
						sub->AddOption<NumberOption<float>>(TRANSLATE("Red"), nullptr, &m_ZenithRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { ZenithColorBypass(); ZenithColor(m_ZenithRed, m_ZenithGreen, m_ZenithBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Green"), nullptr, &m_ZenithGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { ZenithColorBypass(); ZenithColor(m_ZenithRed, m_ZenithGreen, m_ZenithBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Blue"), nullptr, &m_ZenithBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { ZenithColorBypass(); ZenithColor(m_ZenithRed, m_ZenithGreen, m_ZenithBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Intensity"), nullptr, &m_ZenithIntensity, 1.f, 5.f, 0.1f, 1, true, "", "", [] { ZenithColor(m_ZenithRed, m_ZenithGreen, m_ZenithBlue); });
						sub->AddOption<BoolOption<bool>>(TRANSLATE("Rainbow"), nullptr, &m_RainbowZenith, BoolDisplay::OnOff, false, [] { ZenithColorBypass(); });
						sub->AddOption<RegularOption>(TRANSLATE("Default"), nullptr, [] {  std::copy_n("\x0F\x29\xA2\xB0\x00\x00\x00", 7, g_GameFunctions->m_WeatherBypass8); });
						break;
					case 8:
						sub->AddOption<NumberOption<float>>(TRANSLATE("Red"), nullptr, &m_ZenithTransitionRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { ZenithTransitionColorBypass(); ZenithTransitionColor(m_ZenithTransitionRed, m_ZenithTransitionGreen, m_ZenithTransitionBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Green"), nullptr, &m_ZenithTransitionGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { ZenithTransitionColorBypass(); ZenithTransitionColor(m_ZenithTransitionRed, m_ZenithTransitionGreen, m_ZenithTransitionBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Blue"), nullptr, &m_ZenithTransitionBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { ZenithTransitionColorBypass(); ZenithTransitionColor(m_ZenithTransitionRed, m_ZenithTransitionGreen, m_ZenithTransitionBlue); });
						sub->AddOption<NumberOption<float>>(TRANSLATE("Intensity"), nullptr, &m_ZenithTransitionIntensity, 1.f, 5.f, 0.1f, 1, true, "", "", [] { ZenithTransitionColor(m_ZenithTransitionRed, m_ZenithTransitionGreen, m_ZenithTransitionBlue); });
						sub->AddOption<BoolOption<bool>>(TRANSLATE("Rainbow"), nullptr, &m_RainbowZenithTransition, BoolDisplay::OnOff, false, [] { ZenithTransitionColorBypass(); });
						sub->AddOption<RegularOption>(TRANSLATE("Default"), nullptr, [] {  std::copy_n("\x0F\x29\xA2\xE0\00\x00\x00", 7, g_GameFunctions->m_WeatherBypass9); });
						break;
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Clouds"), SubmenuClouds, [](RegularSubmenu* sub)
				{
					sub->AddOption<RegularOption>("Clear", nullptr, [] { MISC::_CLEAR_CLOUD_HAT(); });
					sub->AddOption<RegularOption>("Shower", nullptr, [] { SetClouds("Shower"); });
					sub->AddOption<RegularOption>("Snowy", nullptr, [] { SetClouds("Snowy 01"); });
					sub->AddOption<RegularOption>("Stormy", nullptr, [] { SetClouds("Stormy 01"); });
					sub->AddOption<RegularOption>("Stratoscumulus", nullptr, [] { SetClouds("Stratoscumulus"); });
					sub->AddOption<RegularOption>("Stripey", nullptr, [] { SetClouds("Stripey"); });
					sub->AddOption<RegularOption>("Wispy", nullptr, [] { SetClouds("Wispy"); });
					sub->AddOption<RegularOption>("Altostratus", nullptr, [] { SetClouds("Altostratus"); });
					sub->AddOption<RegularOption>("Cirrocumulus", nullptr, [] { SetClouds("Cirrocumulus"); });
					sub->AddOption<RegularOption>("Cirrus", nullptr, [] { SetClouds("Altostratus"); });
					sub->AddOption<RegularOption>("Clear", nullptr, [] { SetClouds("Clear 01"); });
					sub->AddOption<RegularOption>("Cloudy", nullptr, [] { SetClouds("Cloudy 01"); });
					sub->AddOption<RegularOption>("Contrails", nullptr, [] { SetClouds("Contrails"); });
					sub->AddOption<RegularOption>("No Clouds", nullptr, [] { SetClouds("NoClouds"); });
					sub->AddOption<RegularOption>("Puffs", nullptr, [] { SetClouds("Puffs"); });
					sub->AddOption<RegularOption>("Rain", nullptr, [] { SetClouds("Rain"); });
					sub->AddOption<RegularOption>("Snow", nullptr, [] { SetClouds("Snow"); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Weather"), SubmenuWeather, [](RegularSubmenu* sub)
				{
					sub->AddOption<RegularOption>("Random", nullptr, [] {MISC::SET_RANDOM_WEATHER_TYPE(); });
					sub->AddOption<RegularOption>("Clear", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("clear"); });
					sub->AddOption<RegularOption>("Clearing", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("clearing"); });
					sub->AddOption<RegularOption>("Clouds", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("clouds"); });
					sub->AddOption<RegularOption>("Sunny", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("extrasunny"); });
					sub->AddOption<RegularOption>("Fog", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("foggy"); });
					sub->AddOption<RegularOption>("Halloween", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("halloween"); });
					sub->AddOption<RegularOption>("Neutral", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("neutral"); });
					sub->AddOption<RegularOption>("Overcast", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("overcast"); });
					sub->AddOption<RegularOption>("Rain", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("rain"); });
					sub->AddOption<RegularOption>("Smog", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("smog"); });
					sub->AddOption<RegularOption>("Snow", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("snow"); });
					sub->AddOption<RegularOption>("Snowlight", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("snowlight"); });
					sub->AddOption<RegularOption>("Christmas", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("xmas"); });
					sub->AddOption<RegularOption>("Thunder", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("thunder"); });
					sub->AddOption<RegularOption>(OBFUSCATE("Lightning"), nullptr, [] { MISC::_CREATE_LIGHTNING_THUNDER(); });
				});

			/*g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Friends"), SubmenuFriendList, [](RegularSubmenu* sub)
				{
					std::int32_t friend_count = NETWORK::NETWORK_GET_FRIEND_COUNT();
					for (std::int32_t i = 0; i < friend_count; i++)
					{
						const char* l_ = NETWORK::NETWORK_GET_FRIEND_NAME(i);
						if (l_ != nullptr)
						{
							std::string name(l_);
							if (NETWORK::NETWORK_IS_FRIEND_INDEX_ONLINE(i)) {
								name += " ~g~[ONLINE]";
								if (NETWORK::NETWORK_IS_FRIEND_IN_SAME_TITLE(l_)) {
									name += " ~w~[GTA V]";
									if (NETWORK::NETWORK_IS_FRIEND_IN_MULTIPLAYER(l_)) {
										name += " ~b~[MP]";
									}
									else {
										name += " ~y~[SP]";
									}
								}
							}
							else
							{
								name += " ~c~[OFFLINE]";
							}
							sub->AddOption<RegularOption>(name.c_str(), nullptr, [=] {
								int netHandle[13];
								NETWORK::NETWORK_HANDLE_FROM_FRIEND(i, netHandle, 13);
								const char* RID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);
								g_FiberScript->addTask([=] {
									m_SCIDJoiner = atoi(RID);
									g_Logger->Info(RID);
									m_EnableSCIDJoiner = true;
									HUD::ACTIVATE_FRONTEND_MENU(0XD528C7E2, 0, 2);
									g_FiberScript->Wait(250);
									if (m_PlayerListPointer)
									{
										g_GameFunctions->m_PlayerGUIOptions(m_PlayerListPointer, &g_RIDHash);
										m_PlayerListPointer = 0;
										g_FiberScript->Wait(300);
									}
									m_EnableSCIDJoiner = false;
									});
								});
						}
					}
				});*/

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Time"), SubmenuTime, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Pause Time"), nullptr, &g_PauseTime, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &g_TimeEnable, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<NumberOption<int>>(TRANSLATE("Hour:"), nullptr, &g_Hour, 0, 23, 1, 1, false);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Minute:"), nullptr, &g_Minute, 0, 59, 1, 1, false);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Second:"), nullptr, &g_Second, 0, 59, 1, 1, false);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Gravity Gun"), SubmenuGravityBug, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Type"), nullptr, &GravityGunStyle, &GravityGunSize);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &g_GravityGun, BoolDisplay::OnOff, false, [] {});
					if (GravityGunSize == 1)
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Entities"), nullptr, &m_GravityGunEntityCount, 0, 20, 1, 1, false);
					}
					else
					{
						sub->AddOption<BoolOption<bool>>(TRANSLATE("Lock On Entity"), nullptr, &LockOnEntity, BoolDisplay::OnOff, false, [] {});
					}
					sub->AddOption<NumberOption<float>>(TRANSLATE("Force:"), nullptr, &g_Force, 0, 100.f, 0.5, 1, false);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Velocity:"), nullptr, &g_Velocity, 0, 100.f, 0.5, 2, false);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Pull/Push Strength:"), nullptr, &g_PullPushStrength, 0, 100.f, 0.5, 1, false);

				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Crosshair"), SubmenuCrosshair, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &testicalcancer, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Type"), nullptr, &CrossStyle, &_CrossStyle);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Size"), nullptr, &crosssize, 1.f, 20.f, 1, 0);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Red"), nullptr, &redcross, 0.f, 255.f, 1, 0);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Green"), nullptr, &greencross, 0.f, 255.f, 1, 0);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Blue"), nullptr, &bluecross, 0.f, 255.f, 1, 0);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Paint"), SubmenuPaintGun, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &m_EnablePaint, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<NumberOption<float>>(TRANSLATE("Range"), nullptr, &m_Range, 0.1f, 10.f, 0.1f, 1);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Intensity"), nullptr, &m_Intensity, 1.f, 2000.f, 25.f, 0);
					sub->AddOption<RegularOption>(TRANSLATE("Erase"), nullptr, [] { positions.clear(); });
					sub->AddOption<NumberOption<int>>(TRANSLATE("Red"), nullptr, &g_RedPaint, 0, 255, 1, 0);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Green"), nullptr, &g_GreenPaint, 0, 255, 1, 0);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Blue"), nullptr, &g_BluePaint, 0, 255, 1, 0);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Bullet Swap"), EntityGunSub, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Swap To:"), nullptr, &m_PropellantText, &m_EntityPropellantIterator);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Velocity:"), nullptr, &m_ObjectPropellantSpeed, 0, 1000.f, 10.f, 0, true, "", "", [] {});
					sub->AddOption<NumberOption<float>>(TRANSLATE("Distance:"), nullptr, &m_PropellantSpawnDistance, 0, 20.f, 0.5f, 1, true, "", "", [] {});

					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &m_EnableEntityPropellant, BoolDisplay::OnOff, false, [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Vehicle"), EntityGunSub1, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Vehicle:"), nullptr, &m_EntityVehicle, &m_EntityVehicleIterator);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Velocity:"), nullptr, &m_VehicleLaunchSpeed, 0, 1000.f, 10.f, 0, true, "", "", [] {});
					sub->AddOption<NumberOption<float>>(TRANSLATE("Distance:"), nullptr, &m_VehicleSpawnDistance, 0, 10.f, 0.2f, 1, true, "", "", [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &m_EnableEntityGunVehicle, BoolDisplay::OnOff, false, [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Objects"), EntityGunSub2, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Object:"), nullptr, &m_EntityObject, &m_EntityObjectIterator);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Velocity:"), nullptr, &m_ObjectLaunchSpeed, 0, 1500.f, 15.f, 0, true, "", "", [] {});
					sub->AddOption<NumberOption<float>>(TRANSLATE("Distance:"), nullptr, &m_ObjectSpawnDistance, 0, 20.f, 0.5f, 1, true, "", "", [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &m_EnableEntityGunObject, BoolDisplay::OnOff, false, [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Pickup"), EntityGunSub3, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &m_EnableEntityGunPickups, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Hash:"), nullptr, &m_PickupType, &m_EntityPickupTypeIterator);
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Object:"), nullptr, &m_PickupModel, &m_EntityPickupModelIterator);
					switch (m_EntityPickupTypeIterator) {
					case 0:
					{
						if (m_EntityPickupTypeIterator == 0 && m_EntityPickupModelIterator == 0)
						{
							sub->AddOption<NumberOption<int>>(TRANSLATE("Value:"), nullptr, &m_PickupValue, 0, 2500, 100, 1, true, "", "", [] {});
						}
						else
						{
							if (m_PickupValue > 2000) m_PickupValue = 0;
							sub->AddOption<NumberOption<int>>(TRANSLATE("Value:"), nullptr, &m_PickupValue, 0, 2000, 100, 1, true, "", "", [] {});
						}
					} break;
					case 1: { if (m_PickupValue > 100) { m_PickupValue = 0; } sub->AddOption<NumberOption<int>>(TRANSLATE("Value:"), nullptr, &m_PickupValue, 0, 100, 5, 1, true, "", "", [] {}); } break;
					case 2: { if (m_PickupValue > 200) { m_PickupValue = 0; } sub->AddOption<NumberOption<int>>(TRANSLATE("Value:"), nullptr, &m_PickupValue, 0, 200, 10, 1, true, "", "", [] {}); } break;
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Weapon"), SubmenuWeapon, [](RegularSubmenu* sub)
				{
					sub->AddOption<SubOption>(TRANSLATE("Gravity Gun"), nullptr, SubmenuGravityBug);
					sub->AddOption<SubOption>(TRANSLATE("Crosshair"), nullptr, SubmenuCrosshair);
					sub->AddOption<SubOption>(TRANSLATE("Paint"), nullptr, SubmenuPaintGun);
					sub->AddOption<SubOption>(TRANSLATE("Bullet Swap"), nullptr, EntityGunSub);
					sub->AddOption<SubOption>(TRANSLATE("Vehicle"), nullptr, EntityGunSub1);
					sub->AddOption<SubOption>(TRANSLATE("Object1"), nullptr, EntityGunSub2);
					//sub->AddOption<SubOption>(TRANSLATE("Pickup"), nullptr, EntityGunSub3);
					sub->AddOption<RegularOption>(TRANSLATE("Give Weapons"), nullptr, [] { GiveWeapons(); });
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Attachments:"), nullptr, &wepattach, &_wepattach, false, [] { Attachments(); });
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Rainbow"), nullptr, &m_RainbowCamo, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Teathers"), nullptr, &g_Rope, BoolDisplay::OnOff, false, [] {});
					if (g_Vip || g_Staff)
						//sub->AddOption<BoolOption<bool>>(TRANSLATE("Carnado"), nullptr, &g_Carnado, BoolDisplay::OnOff, false, [] {});

						sub->AddOption<BoolOption<bool>>(TRANSLATE("Rapid Fire"), nullptr, &m_RapidFire, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Hijack Vehicle"), nullptr, &g_YoinkGun, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Infinite"), nullptr, &m_InfiniteAmmo, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Magnet"), nullptr, &m_Magnet, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Aim Assist:"), nullptr, &AimbotArray, &g_AimbotInterator);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Teleport"), nullptr, &m_TeleportGun, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Lasersight"), nullptr, &m_LaserSight, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Force"), nullptr, &m_ForceGun, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Delete"), nullptr, &m_DeleteGun, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(("Revive"), nullptr, &m_ReviveGun, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Explosive"), nullptr, &m_ExplosiveAmmo, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Fly"), nullptr, &g_FlyGun, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Flame"), nullptr, &m_FlamingAmmo, BoolDisplay::OnOff, false, [] {});
					//sub->AddOption<BoolOption<bool>>(TRANSLATE("Bags"), nullptr, &m_MoneyGun, BoolDisplay::OnOff, false, [] {});
					//sub->AddOption<BoolOption<bool>>(TRANSLATE("0 Recoil"), nullptr, &m_NoRecoil, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Airstrike"), nullptr, &m_AirstrikeGun, BoolDisplay::OnOff, false, [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Handtrails", SubmenuHandtrail, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(("Toggle"), nullptr, &m_Handtrails, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<NumberOption<float>>(("Scale"), nullptr, &handscale, 0.f, 255.f, 0.01f, 2, true, "", "", [] {});
					sub->AddOption<NumberOption<float>>(("Red"), nullptr, &handred, 0, 255, 1, 0, true, "", "", [] {});
					sub->AddOption<NumberOption<float>>(("Green"), nullptr, &handgreen, 0, 255, 1, 0, true, "", "", [] {});
					sub->AddOption<NumberOption<float>>(("Blue"), nullptr, &handblue, 0, 255, 1, 0, true, "", "", [] {});
					sub->AddOption<NumberOption<float>>(("Opacity"), nullptr, &handalpha, 0, 255, 1, 0, true, "", "", [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Hotkeys", SubmenuHotkeys, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>("Repair Vehicle", nullptr, &g_RepairVehHotkey, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Vehicle Fly"), nullptr, &g_VehicleFlyHotkey, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Waypoint"), nullptr, &g_TeleportHotkey, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Noclip"), nullptr, &g_NoClipHotkey, BoolDisplay::OnOff, false, [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Player"), SubmenuPlayer, [](RegularSubmenu* sub)
				{
					static int nignog{ 0 };
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Invincible"), nullptr, &g_Invincible, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Never Wanted"), nullptr, &g_NeverWanted, BoolDisplay::OnOff);
					sub->AddOption<SubOption>(TRANSLATE("Noclip"), nullptr, SubmenuNoClip);
					sub->AddOption<SubOption>(("Models"), nullptr, SubmenuModels);
					sub->AddOption<SubOption>(TRANSLATE("Animation"), nullptr, SubmenuAnimation);
					sub->AddOption<SubOption>(TRANSLATE("Particles"), nullptr, SubmenuGlow);
					sub->AddOption<SubOption>(TRANSLATE("Clipset"), nullptr, SubmenuWalkstyles);
					sub->AddOption<SubOption>(TRANSLATE("Proofs"), nullptr, SubmenuProofs);
					sub->AddOption<SubOption>(TRANSLATE("Wardrobe"), nullptr, SubmenuWardrobe);
					sub->AddOption<SubOption>(TRANSLATE("Handtrails"), nullptr, SubmenuHandtrail);
					sub->AddOption<SubOption>(TRANSLATE("Hotkeys"), nullptr, SubmenuHotkeys);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("No Ragdoll"), nullptr, &g_NoRagdoll, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Always Ragdoll"), nullptr, &g_AlwaysRagdoll, BoolDisplay::OnOff);
					if (g_Vip || g_Staff)
						sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Die On Ragdoll"), nullptr, &g_DieOnRagdoll, BoolDisplay::OnOff);

					sub->AddOption<BoolOption<bool>>(TRANSLATE("Invisible"), nullptr, &g_Invisible, BoolDisplay::OnOff);
					//sub->AddOption<NumberOption<float>>(TRANSLATE("Width"), nullptr, &g_Width, 0.f, 10.f, 0.1f, 1); // BROKEN
					//sub->AddOption<NumberOption<float>>(TRANSLATE("Height"), nullptr, &g_Height, 0.f, 10.f, 0.1f, 1);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Alpha"), nullptr, &g_Alpha, 0, 255, 10);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Super Jump"), nullptr, &g_Superjump, BoolDisplay::OnOff);
					if (g_Vip || g_Staff)
						sub->AddOption<BoolOption<bool>>(TRANSLATE("Salto Jump"), nullptr, &g_NinjaJump, BoolDisplay::OnOff);

					sub->AddOption<BoolOption<bool>>(TRANSLATE("Fast Run"), nullptr, &g_FastRun, BoolDisplay::OnOff, []
						{
							if (g_FastRun)
								Memory::set_value<float>({ 0x8, 0x10A8, 0xD40 }, 3.f);
							else
								Memory::set_value<float>({ 0x8, 0x10A8, 0xD40 }, 1.f);
						});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Fast Swim"), nullptr, &g_FastSwim, BoolDisplay::OnOff, []
						{
							if (g_FastSwim)
								Memory::set_value<float>({ 0x8, 0x10A8, 0x1c8 }, 3.f);
							else
								Memory::set_value<float>({ 0x8, 0x10A8, 0x1c8 }, 1.f);
						});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Reduced Collision"), nullptr, &g_ReducedCollision, BoolDisplay::OnOff, []
						{
							if (g_ReducedCollision)
							{
							}
							else
								Memory::set_value<float>({ 0x8, 0x30, 0x10, 0x20, 0x70, 0x0, 0x2C }, 0.25);
						});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Fly"), nullptr, &g_Fly, BoolDisplay::OnOff);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Wanted Level"), nullptr, &nignog, 0, 5, 1, 3, true, "", "", [] { SetWantedLevel(nignog); });
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Night Vision"), nullptr, &g_NightVision, BoolDisplay::OnOff, false, []
						{
							if (g_NightVision) { *script_global(1853988).at(1).at(PLAYER::PLAYER_ID() * 867).at(823).at(10).at(1).as<bool*>() = 1; }
							else
							{
								*script_global(1853988).at(1).at(PLAYER::PLAYER_ID() * 867).at(823).at(10).at(1).as<bool*>() = 0;
								GRAPHICS::SET_NIGHTVISION(false);
							}
						});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Thermal Vision"), nullptr, &g_ThermalVision, BoolDisplay::OnOff, false, []
						{
							if (g_ThermalVision) { *script_global(1853988).at(1).at(PLAYER::PLAYER_ID() * 867).at(823).at(10).at(1).as<bool*>() = 1; }
							else
							{
								*script_global(1853988).at(1).at(PLAYER::PLAYER_ID() * 867).at(823).at(10).at(1).as<bool*>() = 0;
								GRAPHICS::SET_SEETHROUGH(false);
							}
						});
					if (g_Vip || g_Staff)
						sub->AddOption<BoolOption<bool>>(TRANSLATE("Dance"), nullptr, &g_Forcefield, BoolDisplay::OnOff);

					sub->AddOption<BoolOption<bool>>(TRANSLATE("Off Radar"), nullptr, &g_OffRadar, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Reveal Players"), nullptr, &g_RevealedPlayers, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Walk Under Water"), nullptr, &g_WalkUnderWater, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Walk On Water"), nullptr, &g_WalkOnWater, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Move Water Away"), nullptr, &g_ModifyWater, BoolDisplay::OnOff);

					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Slow Motion"), nullptr, &g_SlowMotion, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Dead Eye Motion"), nullptr, &g_DeadEye, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Foot Trails"), nullptr, &g_FootTrails, BoolDisplay::OnOff);
					sub->AddOption<RegularOption>(TRANSLATE("Max Health"), nullptr, [] { ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), ENTITY::GET_ENTITY_MAX_HEALTH(PLAYER::PLAYER_PED_ID())); });
					sub->AddOption<RegularOption>(TRANSLATE("Max Armour"), nullptr, [] { PED::SET_PED_ARMOUR(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_ID())); });
					sub->AddOption<RegularOption>(TRANSLATE("Clean"), nullptr, [] { PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID()); });
					sub->AddOption<RegularOption>(TRANSLATE("Dry"), nullptr, [] { PED::CLEAR_PED_WETNESS(PLAYER::PLAYER_PED_ID()); });
					sub->AddOption<RegularOption>(TRANSLATE("Skydive"), nullptr, [] { NativeVector3 me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0); WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("gadget_parachute"), 1, 0); ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), me.x, me.y, me.z + 1000, 0, 0, 0, 0); });
					sub->AddOption<RegularOption>(TRANSLATE("Clone Ped"), nullptr, [] { PED::CLONE_PED(PLAYER::PLAYER_PED_ID(), ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 0, 1); });
					sub->AddOption<RegularOption>(TRANSLATE("Suicide"), nullptr, [] { ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Models", SubmenuModels, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Type"), nullptr, &g_PedList->PedLists, &g_PedList->PedListPos);
					switch (g_PedList->PedListPos) {
					case 0:
						for (const char* ped : g_PedList->Male) {
							sub->AddOption<RegularOption>(ped, nullptr, [ped] { ChangeModel(ped); });
						}
						break;
					case 1:
						for (const char* ped : g_PedList->Female) {
							sub->AddOption<RegularOption>(ped, nullptr, [ped] { ChangeModel(ped); });
						}
						break;
					case 2:
						for (const char* ped : g_PedList->Animal) {
							sub->AddOption<RegularOption>(ped, nullptr, [ped] { ChangeModel(ped); });
						}
						break;
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Precipitation", PrecipitationSubmenu, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>("Precipitation", nullptr, &RainColor2, &_RainColor2);
					switch (_RainColor2)
					{
					case 0:
						sub->AddOption<NumberOption<float>>("Red", nullptr, &RainstormRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { RainstormColor(RainstormRed, RainstormGreen, RainstormBlue); });
						sub->AddOption<NumberOption<float>>("Green", nullptr, &RainstormGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { RainstormColor(RainstormRed, RainstormGreen, RainstormBlue); });
						sub->AddOption<NumberOption<float>>("Blue", nullptr, &RainstormBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { RainstormColor(RainstormRed, RainstormGreen, RainstormBlue); });
						sub->AddOption<NumberOption<float>>("Intensity", nullptr, &RainstormIntensity, 1.f, 100.f, 1.f, 1, true, "", "", [] { RainstormColor(RainstormRed, RainstormGreen, RainstormBlue); });
						sub->AddOption<NumberOption<float>>("Gravity", nullptr, &RainstormGravity, -25.f, 25.f, 1.f, 1, true, "", "", [] { RainstormVariables(); });
						sub->AddOption<NumberOption<float>>("Size Width", nullptr, &RainstormSizeX, 0.1f, 100.f, 0.05f, 2, true, "", "", [] { RainstormVariables(); });
						sub->AddOption<NumberOption<float>>("Size Horizontal", nullptr, &RainstormSizeY, 0.1f, 100.f, 0.05f, 1, true, "", "", [] { RainstormVariables(); });
						sub->AddOption<RegularOption>("Start Rain", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("Rain"); });
						sub->AddOption<RegularOption>("Default", nullptr, [] { RainstormRed = 0.400000006; RainstormGreen = 0.400000006; RainstormBlue = 0.400000006; RainstormGravity = -12.f; RainstormSizeX = 0.01499999966f; RainstormSizeY = 0.400000006; RainstormVariables(); RainstormColor(RainstormRed, RainstormGreen, RainstormBlue); });
						break;
					case 1:
						sub->AddOption<NumberOption<float>>("Red", nullptr, &ThunderRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { ThunderColor(ThunderRed, ThunderGreen, ThunderBlue); });
						sub->AddOption<NumberOption<float>>("Green", nullptr, &ThunderGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { ThunderColor(ThunderRed, ThunderGreen, ThunderBlue); });
						sub->AddOption<NumberOption<float>>("Blue", nullptr, &ThunderBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { ThunderColor(ThunderRed, ThunderGreen, ThunderBlue); });
						sub->AddOption<NumberOption<float>>("Intensity", nullptr, &ThunderIntensity, 1.f, 100.f, 1.f, 1, true, "", "", [] { ThunderColor(ThunderRed, ThunderGreen, ThunderBlue); });
						sub->AddOption<NumberOption<float>>("Gravity", nullptr, &ThunderGravity, -25.f, 25.f, 1.f, 1, true, "", "", [] { ThunderVariables(); });
						sub->AddOption<NumberOption<float>>("Size Width", nullptr, &ThunderSizeX, 0.1f, 100.f, 0.05f, 2, true, "", "", [] { ThunderVariables(); });
						sub->AddOption<NumberOption<float>>("Size Horizontal", nullptr, &ThunderSizeY, 0.1f, 100.f, 0.05f, 1, true, "", "", [] { ThunderVariables(); });
						sub->AddOption<RegularOption>("Start Thunder", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("Thunder"); });
						sub->AddOption<RegularOption>("Default", nullptr, [] { ThunderIntensity = 1.f; ThunderRed = 0.f; ThunderGreen = 0.f; ThunderBlue = 0.f; ThunderGravity = -12.f; ThunderSizeX = 0.009999999776f; ThunderSizeY = 0.6000000238f; ThunderVariables(); ThunderColor(ThunderRed, ThunderGreen, ThunderBlue); });
						break;
					case 2:
						sub->AddOption<NumberOption<float>>("Red", nullptr, &LightSnowRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { LightSnowColor(LightSnowRed, LightSnowGreen, LightSnowBlue); });
						sub->AddOption<NumberOption<float>>("Green", nullptr, &LightSnowGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { LightSnowColor(LightSnowRed, LightSnowGreen, LightSnowBlue); });
						sub->AddOption<NumberOption<float>>("Blue", nullptr, &LightSnowBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { LightSnowColor(LightSnowRed, LightSnowGreen, LightSnowBlue); });
						sub->AddOption<NumberOption<float>>("Intensity", nullptr, &LightSnowIntensity, 0.1f, 100.f, 1.f, 1, true, "", "", [] { LightSnowColor(LightSnowRed, LightSnowGreen, LightSnowBlue); });
						sub->AddOption<NumberOption<float>>("Gravity", nullptr, &LightSnowGravity, -25.f, 25.f, 1.f, 1, true, "", "", [] { LightSnowVariables(); });
						sub->AddOption<NumberOption<float>>("Size Width", nullptr, &LightSnowSizeX, 1.f, 100.f, 0.05f, 2, true, "", "", [] { LightSnowVariables(); });
						sub->AddOption<NumberOption<float>>("Size Horizontal", nullptr, &LightSnowSizeY, 1.f, 100.f, 0.05f, 1, true, "", "", [] { LightSnowVariables(); });
						sub->AddOption<RegularOption>("Start Snowlight", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("Snowlight"); });
						sub->AddOption<RegularOption>("Default", nullptr, [] { LightSnowIntensity = 1.f; LightSnowRed = 0.6000000238f; LightSnowGreen = 0.6000000238f; LightSnowBlue = 0.6000000238f; LightSnowGravity = -0.5f; LightSnowSizeX = 0.02500000037f; LightSnowSizeY = 0.02500000037f; LightSnowVariables(); LightSnowColor(LightSnowRed, LightSnowGreen, LightSnowBlue); });
						break;
					case 3:
						sub->AddOption<NumberOption<float>>("Red", nullptr, &HeavySnowRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { HeavySnowColor(HeavySnowRed, HeavySnowGreen, HeavySnowBlue); });
						sub->AddOption<NumberOption<float>>("Green", nullptr, &HeavySnowGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { HeavySnowColor(HeavySnowRed, HeavySnowGreen, HeavySnowBlue); });
						sub->AddOption<NumberOption<float>>("Blue", nullptr, &HeavySnowBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { HeavySnowColor(HeavySnowRed, HeavySnowGreen, HeavySnowBlue); });
						sub->AddOption<NumberOption<float>>("Intensity", nullptr, &HeavySnowIntensity, 0.1f, 100.f, 1.f, 1, true, "", "", [] { HeavySnowColor(HeavySnowRed, HeavySnowGreen, HeavySnowBlue); });
						sub->AddOption<NumberOption<float>>("Gravity", nullptr, &HeavySnowGravity, -25.f, 25.f, 1.f, 1, true, "", "", [] { HeavySnowVariables(); });
						sub->AddOption<NumberOption<float>>("Size Width", nullptr, &HeavySnowSizeX, 1.f, 100.f, 0.05f, 2, true, "", "", [] { HeavySnowVariables(); });
						sub->AddOption<NumberOption<float>>("Size Horizontal", nullptr, &HeavySnowSizeY, 1.f, 100.f, 0.05f, 1, true, "", "", [] { HeavySnowVariables(); });
						sub->AddOption<RegularOption>("Start Heavysnow", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("SNOW"); });
						sub->AddOption<RegularOption>("Default", nullptr, [] { HeavySnowIntensity = 1.f; HeavySnowRed = 0.6000000238f; HeavySnowGreen = 0.6000000238f; HeavySnowBlue = 0.6000000238f; HeavySnowGravity = -0.5f; HeavySnowSizeX = 0.02500000037f; HeavySnowSizeY = 0.02500000037f; HeavySnowVariables(); HeavySnowColor(HeavySnowRed, HeavySnowGreen, HeavySnowBlue); });
						break;
					case 4:
						sub->AddOption<NumberOption<float>>("Red", nullptr, &BlizzardRed, 0.f, 255.f, 1.f, 0, true, "", "", [] { BlizzardColor(BlizzardRed, BlizzardGreen, BlizzardBlue); });
						sub->AddOption<NumberOption<float>>("Green", nullptr, &BlizzardGreen, 0.f, 255.f, 1.f, 0, true, "", "", [] { BlizzardColor(BlizzardRed, BlizzardGreen, BlizzardBlue); });
						sub->AddOption<NumberOption<float>>("Blue", nullptr, &BlizzardBlue, 0.f, 255.f, 1.f, 0, true, "", "", [] { BlizzardColor(BlizzardRed, BlizzardGreen, BlizzardBlue); });
						sub->AddOption<NumberOption<float>>("Intensity", nullptr, &BlizzardIntensity, 0.1f, 100.f, 1.f, 1, true, "", "", [] { BlizzardColor(BlizzardRed, BlizzardGreen, BlizzardBlue); });
						sub->AddOption<NumberOption<float>>("Gravity", nullptr, &BlizzardGravity, -25.f, 25.f, 1.f, 1, true, "", "", [] { BlizzardVariables(); });
						sub->AddOption<NumberOption<float>>("Size Width", nullptr, &BlizzardSizeX, 1.f, 100.f, 0.05f, 2, true, "", "", [] { BlizzardVariables(); });
						sub->AddOption<NumberOption<float>>("Size Horizontal", nullptr, &BlizzardSizeY, 1.f, 100.f, 0.05f, 1, true, "", "", [] { BlizzardVariables(); });
						sub->AddOption<RegularOption>("Start Blizzard", nullptr, [] {MISC::SET_WEATHER_TYPE_NOW_PERSIST("Blizzard"); });
						sub->AddOption<RegularOption>("Default", nullptr, [] { BlizzardIntensity = 1.f; BlizzardRed = 1.f; BlizzardGreen = 1.f; BlizzardBlue = 1.f; BlizzardGravity = -0.5f; BlizzardSizeX = 0.02500000037f; BlizzardSizeY = 0.02500000037f; BlizzardVariables(); BlizzardColor(BlizzardRed, BlizzardGreen, BlizzardBlue); });
						break;
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Particles"), SubmenuGlow, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &m_EnableGlow, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<NumberOption<float>>(TRANSLATE("Scale"), nullptr, &m_GlowScale, 0, 2, 0.1f, 1, true, "", "", [] {});
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Particle"), nullptr, &m_Particle, &m_ParticleIterator);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Head"), nullptr, &m_Head, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Right Hand"), nullptr, &m_RightHand, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Left Hand"), nullptr, &m_LeftHand, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Right Foot"), nullptr, &m_RightFood, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Left Foot"), nullptr, &m_LeftFood, BoolDisplay::OnOff, false, [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Animations"), SubmenuAnimation, [](RegularSubmenu* sub)
				{
					sub->AddOption<SubOption>(TRANSLATE("Senarios"), nullptr, SubmenuSenarios);
					sub->AddOption<RegularOption>(TRANSLATE("Stop All Animations"), nullptr, [] { BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); BRAIN::CLEAR_PED_SECONDARY_TASK(PLAYER::PLAYER_PED_ID()); });
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Controllable"), nullptr, &m_Controllable, BoolDisplay::OnOff, false);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Contort"), nullptr, &m_Contort, BoolDisplay::OnOff, false);
					//sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Animations"), nullptr, &m_Animations, &m_Anim, false, [] { Animation(); });
					sub->AddOption<RegularOption>(TRANSLATE("SexReceiver"), nullptr, [] { doAnimation("rcmpaparazzo_2", "shag_loop_poppy"); });
					sub->AddOption<RegularOption>(TRANSLATE("SexGiver"), nullptr, [] { doAnimation("rcmpaparazzo_2", "shag_loop_a"); });
					sub->AddOption<RegularOption>(TRANSLATE("StripperDance"), nullptr, [] { doAnimation("mini@strip_club@private_dance@part1", "priv_dance_p1"); });
					sub->AddOption<RegularOption>(TRANSLATE("PoleDance"), nullptr, [] { doAnimation("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); });
					sub->AddOption<RegularOption>(TRANSLATE("PushUps"), nullptr, [] { doAnimation("amb@world_human_push_ups@male@base", "base"); });
					sub->AddOption<RegularOption>(TRANSLATE("SitUps"), nullptr, [] { doAnimation("amb@world_human_sit_ups@male@base", "base"); });
					sub->AddOption<RegularOption>(TRANSLATE("Celebrate"), nullptr, [] { doAnimation("rcmfanatic1celebrate", "celebrate"); });
					sub->AddOption<RegularOption>(TRANSLATE("Electrocution"), nullptr, [] { doAnimation("ragdoll@human", "electrocute"); });
					sub->AddOption<RegularOption>(TRANSLATE("Suicide"), nullptr, [] { doAnimation("mp_suicide", "pistol"); });
					sub->AddOption<RegularOption>(TRANSLATE("Showering"), nullptr, [] { doAnimation("mp_safehouseshower@male@", "male_shower_idle_b"); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Senarios"), SubmenuSenarios, [](RegularSubmenu* sub)
				{
					sub->AddOption<RegularOption>(TRANSLATE("Stop All Animations"), nullptr, [] { BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); BRAIN::CLEAR_PED_SECONDARY_TASK(PLAYER::PLAYER_PED_ID()); });
					sub->AddOption<RegularOption>(TRANSLATE("Paparazzi"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PAPARAZZI", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("DrugDealer"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRUG_DEALER_HARD", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("DrinkingCoffee"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_AA_COFFEE", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("PlayingInstruments"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSICIAN", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Flexing"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSCLE_FLEX", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Jogging"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_JOG_STANDING", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Binoculars"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BINOCULARS", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Clipboard"), nullptr, [] {BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CLIPBOARD", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("BenchPress"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("ChinUps"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MUSCLE_CHIN_UPS", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("BBQ"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_BBQ", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Superhero"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SUPERHERO", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Fishing"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_FISHING", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Drilling"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CONST_DRILL", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Tennis"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_TENNIS_PLAYER", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Hammering"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HAMMERING", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Smoking Pot"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SMOKING_POT", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Welding"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_WELDING", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Gold Player"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GOLF_PLAYER", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Drinking"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRINKING", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Idle Cop"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_COP_IDLES", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Film Shocking"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Leaf Blower"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GARDENER_LEAF_BLOWER", 0, true); });
					sub->AddOption<RegularOption>(TRANSLATE("Security"), nullptr, [] { BRAIN::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SECURITY_SHINE_TORCH", 0, true); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Noclip"), SubmenuNoClip, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Type"), nullptr, &NoclipTypes, &NoclipIterator);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Noclip"), nullptr, &g_NoClip, BoolDisplay::OnOff);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Speed"), nullptr, &g_NoClipSpeed, 0.2f, 20.f, 0.2f, 2);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Clipset"), SubmenuWalkstyles, [](RegularSubmenu* sub) {
				for (int i = 0; i < 29; i++) {
					sub->AddOption<RegularOption>(m_Styles[i], nullptr, [=]
						{
							g_FiberScript->addTask([=] { STREAMING::REQUEST_ANIM_SET(m_StyleId[i]);
							while (!STREAMING::HAS_ANIM_SET_LOADED(m_StyleId[i])) g_FiberScript->Wait(0);
							PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), m_StyleId[i], 1.0f); });
						});
				}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Proofs"), SubmenuProofs, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Bulletproof"), nullptr, &m_Bulleproof, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Explosionproof"), nullptr, &m_ExplosionsProof, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Fireproof"), nullptr, &m_FireProof, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Meleeproof"), nullptr, &m_MeleeProof, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("DrownProof"), nullptr, &m_DrownProof, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Collisionproof"), nullptr, &m_CollisionProof, BoolDisplay::OnOff, false, [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Wardrobe"), SubmenuWardrobe, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Component:"), nullptr, &m_ComponentIdList, &m_ClothIterator);
					switch (m_ClothIterator)
					{
					case 0:
					{

					}
					break;
					case 1:
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Drawable"), nullptr, &s1, 0, 200, 1, 1, true, "", "", [] {SetPlayerVariation(m_ClothIterator, s1, s2, s3); });
						sub->AddOption<NumberOption<int>>(TRANSLATE("Texture"), nullptr, &s2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_ClothIterator, s1, s2, s3); });
					}
					break;
					case 2:
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Drawable"), nullptr, &a1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_ClothIterator, a1, a2, a3); });
						sub->AddOption<NumberOption<int>>(TRANSLATE("Texture"), nullptr, &a2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_ClothIterator, a1, a2, a3); });
					}
					break;
					case 3:
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Drawable"), nullptr, &b1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_ClothIterator, b1, b2, b3); });
						sub->AddOption<NumberOption<int>>(TRANSLATE("Texture"), nullptr, &b2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_ClothIterator, b1, b2, b3); });
					}
					break;
					case 4:
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Drawable"), nullptr, &c1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_ClothIterator, c1, c2, c3); });
						sub->AddOption<NumberOption<int>>(TRANSLATE("Texture"), nullptr, &c2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_ClothIterator, c1, c2, c3); });
					}
					break;
					case 5:
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Drawable"), nullptr, &d1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_ClothIterator, d1, d2, d3); });
						sub->AddOption<NumberOption<int>>(TRANSLATE("Texture"), nullptr, &d2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_ClothIterator, d1, d2, d3); });
					}
					break;
					case 6:
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Drawable"), nullptr, &e1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_ClothIterator, e1, e2, e3); });
						sub->AddOption<NumberOption<int>>(TRANSLATE("Texture"), nullptr, &e2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_ClothIterator, e1, e2, e3); });
					}
					break;
					case 7:
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Drawable"), nullptr, &f1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_ClothIterator, f1, f2, f3); });
						sub->AddOption<NumberOption<int>>(TRANSLATE("Texture"), nullptr, &f2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_ClothIterator, f1, f2, f3); });
					}
					break;
					case 8:
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Drawable"), nullptr, &g1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_ClothIterator, g1, g2, g3); });
						sub->AddOption<NumberOption<int>>(TRANSLATE("Texture"), nullptr, &g2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_ClothIterator, g1, g2, g3); });
					}
					break;
					case 9:
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Drawable"), nullptr, &h1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_ClothIterator, h1, h2, h3); });
						sub->AddOption<NumberOption<int>>(TRANSLATE("Texture"), nullptr, &h2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_ClothIterator, h1, h2, h3); });
					}
					break;
					case 10:
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Drawable"), nullptr, &i1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_ClothIterator, i1, i2, i3); });
						sub->AddOption<NumberOption<int>>(TRANSLATE("Texture"), nullptr, &i2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_ClothIterator, i1, i2, i3); });
					}
					break;
					case 11:
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Drawable"), nullptr, &j1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_ClothIterator, j1, j2, j3); });
						sub->AddOption<NumberOption<int>>(TRANSLATE("Texture"), nullptr, &j2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_ClothIterator, j1, j2, j3); });
					}
					break;
					case 12:
					{
						sub->AddOption<NumberOption<int>>(TRANSLATE("Drawable"), nullptr, &k1, 0, 500, 1, 1, true, "", "", [] {SetPlayerVariation(m_ClothIterator, k1, k2, k3); });
						sub->AddOption<NumberOption<int>>(TRANSLATE("Texture"), nullptr, &k2, 0, 500, 1, 1, true, "", "", [] { SetPlayerVariation(m_ClothIterator, k1, k2, k3); });
					}
					break;
					}
					sub->AddOption<RegularOption>(TRANSLATE("Reset"), nullptr, [] { ResetPedVariation(); });
					sub->AddOption<RegularOption>(TRANSLATE("Randomize"), nullptr, [] { RandomizePedVariation(); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Trails"), SubmenuVehicleTrails, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &g_EnableTrails, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Rainbow"), nullptr, &g_RGBTrails, BoolDisplay::OnOff);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Red"), nullptr, &g_TrailsRed, 0, 255, 1);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Green"), nullptr, &g_TrailsGreen, 0, 255, 1);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Blue"), nullptr, &g_TrailsBlue, 0, 255, 1);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Drop"), SubmenuDrop, [](RegularSubmenu* sub)
				{
					sub->AddOption<NumberOption<int>>(TRANSLATE("Value"), nullptr, &dAmount, 0, 2500, 100, 1, false);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Delay"), nullptr, &dDelay, 0, 1000, 10, 1, false);
					sub->AddOption<NumberOption<int>>(TRANSLATE("Height"), nullptr, &dz, 0, 10, 1, 1, false);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Drop"), nullptr, &dEnable, BoolDisplay::OnOff, false);
					sub->AddOption<NumberOption<int>>("X", nullptr, &dx, 0, 10, 1, 1, false);
					sub->AddOption<NumberOption<int>>("Y", nullptr, &dy, 0, 10, 1, 1, false);
					sub->AddOption<NumberOption<int>>("Z", nullptr, &dHeight, 0, 10, 1, 1, false);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Vehicle"), SubmenuVehicle, [](RegularSubmenu* sub)
				{
					sub->AddOption<SubOption>(TRANSLATE("Spawner"), nullptr, SubmenuTestStuff);
					sub->AddOption<SubOption>(TRANSLATE("Ramp Builder"), nullptr, SubmenuVehicleRampBuilder);
					sub->AddOption<SubOption>(TRANSLATE("Acrobatics"), nullptr, SubmenuVehicleAcrobatics);
					sub->AddOption<SubOption>(TRANSLATE("Hornboost"), nullptr, SubmenuHornboost);
					sub->AddOption<SubOption>(TRANSLATE("Fly"), nullptr, SubmenuVehicleFly);
					sub->AddOption<SubOption>(TRANSLATE("Particles"), nullptr, SubmenuParticles);
					sub->AddOption<SubOption>(TRANSLATE("Weapons"), nullptr, SubmenuVehicleWeapons);
					//sub->AddOption<SubOption>(TRANSLATE("Trails"), nullptr, SubmenuVehicleTrails);
					sub->AddOption<RegularOption>(TRANSLATE("Max"), nullptr, [] { MaxVehicle(); });
					sub->AddOption<RegularOption>(("Change Plate"), nullptr, [] {
						g_UiManager->m_Opened = false;
						MISC::DISPLAY_ONSCREEN_KEYBOARD(0, "Spawn Vehicle", "", "", "", "", "", 25);

						g_CallbackScript->AddCallback<KeyBoardCallBack>("", 25, [] {
							int Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle, MISC::GET_ONSCREEN_KEYBOARD_RESULT());
							g_UiManager->m_Opened = true;
							});
						});
					sub->AddOption<RegularOption>(TRANSLATE("Flip"), nullptr, [] { VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0); });
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Abilities"), nullptr, &Ability, &AbilityIterator, true, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Invincible"), nullptr, &g_InvincibleVehicle, BoolDisplay::OnOff, false, [] {
						if(g_InvincibleVehicle){}
						else {
							ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
							VEHICLE::SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
						}
					});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Invisible"), nullptr, &g_InvisibleVehicle, BoolDisplay::OnOff, false, [] {
						if(g_InvisibleVehicle){}
						else { ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), true, 0); }
					});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Parachute"), nullptr, &g_Parachute, BoolDisplay::OnOff, false, []
						{
							Memory::set_value<int>({ 0x8, 0xD10, 0x20, 0x58C }, static_cast<int>(g_Parachute));
						});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Container Rider"), nullptr, &g_ContainerRider, BoolDisplay::OnOff, false, [] {});
					//sub->AddOption<BoolOption<bool>>(TRANSLATE("Better Grip"), nullptr, &g_BetterGrip, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Autofix"), nullptr, &g_Autofix, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Autoflip"), nullptr, &g_Autoflip, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Reduce Vehicle Colission"), nullptr, &g_rvc, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Seatbelt"), nullptr, &g_Seatbelt, BoolDisplay::OnOff, false, [] {
						if(g_Seatbelt){}
						else {
							PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
							PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, true);
						}
					});
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Jump:"), nullptr, &g_Jump, &g_JumpIterator);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Driftmode"), nullptr, &g_Driftmode, BoolDisplay::OnOff, false, [] {});
					//sub->AddOption<BoolOption<bool>>(TRANSLATE("Fast Enter"), nullptr, &g_SkipEnterAnimation, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Render Scorched"), nullptr, &g_Scorched, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Drive On Water"), nullptr, &g_DriveOnWater, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Drive Under Water"), nullptr, &g_DriveUnderWater, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Force To Ground"), nullptr, &g_ForceToGround, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Rainbow"), nullptr, &g_RainbowText, &RainbowIterator);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Glitch"), nullptr, &g_GlitchVehicle, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>("360", nullptr, &g_ThreeSixty, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Engine Always On"), nullptr, &g_EngineAlwaysOn, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<RegularOption>(TRANSLATE("Repair"), nullptr, [] { FixVehicle(); });
					sub->AddOption<RegularOption>(TRANSLATE("Max"), nullptr, [] { MaxVehicle(); });
					sub->AddOption<RegularOption>(TRANSLATE("Open Doors"), nullptr, [] { for (int i = 0; i < 6; i++) { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), i, true, false); } });
					sub->AddOption<RegularOption>(TRANSLATE("Close Doors"), nullptr, [] { VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true); });
					sub->AddOption<RegularOption>(TRANSLATE("Delete Doors"), nullptr, []
						{
							Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
							for (int DoorIndex = 0; DoorIndex <= 6; DoorIndex++) {
								VEHICLE::SET_VEHICLE_DOOR_BROKEN(playerVeh, DoorIndex, 1);
							}
						});
					sub->AddOption<RegularOption>(TRANSLATE("Clean"), nullptr, [] { GRAPHICS::WASH_DECALS_FROM_VEHICLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 100.0f); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Hornboost"), SubmenuHornboost, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &m_Hornboost, BoolDisplay::OnOff, false, [] {
						if(m_Hornboost){}
						else { GRAPHICS::CLEAR_TIMECYCLE_MODIFIER(); }
					});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Audio"), nullptr, &m_AudioBoost, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Effect"), nullptr, &m_BoostEffect, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<NumberOption<float>>(TRANSLATE("Speed"), nullptr, &m_SpeedBoost, 0, 100, 0.5f, 1, false);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Particles"), SubmenuParticles, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &m_EnableGlowVehicle, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<NumberOption<float>>(TRANSLATE("Scale"), nullptr, &m_GlowScale0, 0, 2, 0.1f, 1, true, "", "", [] {});
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Particle"), nullptr, &m_Particle0, &m_ParticleIterator0);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Right Front Wheel"), nullptr, &m_RightFrontWheel, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Left Front Wheel"), nullptr, &m_LeftFrontWheel, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Right Back Wheel"), nullptr, &m_RightBackWheel, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Left Back Wheel"), nullptr, &m_LeftBackWheel, BoolDisplay::OnOff, false, [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Fly"), SubmenuVehicleFly, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Fly"), nullptr, &g_VehicleFly, BoolDisplay::OnOff, false, [] {
						if(g_VehicleFly){}
						else { VEHICLE::SET_VEHICLE_GRAVITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true); }
					});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Collision"), nullptr, &g_Collision, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Bypass Speed Limit"), nullptr, &g_BypassSpeed, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<NumberOption<float>>(TRANSLATE("Speed"), nullptr, &g_FlySpeed, 0, 1000, 5.f, 1, false);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Weapons"), SubmenuVehicleWeapons, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Weapon"), nullptr, &VehicleWeapons, &VehicleWeaponIterator);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Speed"), nullptr, &g_WeaponSpeed, 0, 500.f, 10.f, 1, true, "", "", [] {});
					sub->AddOption<NumberOption<int>>(TRANSLATE("Delay:"), nullptr, &g_WeaponDelay, 0, 1000, 50, 1, true, "", "", [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Prediction"), nullptr, &g_Lasersight, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Activate"), nullptr, &g_VehicleWeapons, BoolDisplay::OnOff, false, [] {});
				});



			/*g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Rockstar ID Joiner"), RIDSubmenu, [](RegularSubmenu* sub)
			{
				sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Action:"), nullptr, &g_RIDArray, &g_RIDIndex);
				sub->AddOption<RegularOption>(TRANSLATE("Enter RID"), nullptr, [] { g_ShowRIDWindow = true; });
				sub->AddOption<RegularOption>(TRANSLATE("Perform Action"), nullptr, []
					{
						g_FiberScript->addTask([] {
							m_EnableSCIDJoiner = true;
							HUD::ACTIVATE_FRONTEND_MENU(0XD528C7E2, 0, 2);
							g_FiberScript->Wait(250);
							if (m_PlayerListPointer)
							{
								g_GameFunctions->m_PlayerGUIOptions(m_PlayerListPointer, &g_RIDHash);
								m_PlayerListPointer = 0;
								g_FiberScript->Wait(300);
							}
							m_EnableSCIDJoiner = false;
							});
					});
			});*/

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Network"), SubmenuNetwork, [](RegularSubmenu* sub)
				{
					g_InPlayerList = false;
					//HostQueue();
					sub->AddOption<RegularOption>(TRANSLATE("Force Script Host"), nullptr, [] { ForceHostOfScript(); });
					sub->AddOption<SubOption>(TRANSLATE("Playerlist"), nullptr, SubmenuPlayerList);
					sub->AddOption<SubOption>(TRANSLATE("Friend List"), nullptr, SubmenuFriendList);
					sub->AddOption<SubOption>(TRANSLATE("Protections"), nullptr, SubmenuProtections);

					if (g_Vip || g_Staff)
						//sub->AddOption<SubOption>(TRANSLATE("Recovery"), nullptr, SubmenuRecovery);

					//sub->AddOption<SubOption>(TRANSLATE("Rockstar ID Joiner"), nullptr, RIDSubmenu);
						sub->AddOption<SubOption>(TRANSLATE("Display Settings"), nullptr, SubmenuPlayerDisplay);
					//sub->AddOption<SubOption>(TRANSLATE("Recent Players"), nullptr, SubmenuRecentPlayers);
					//sub->AddOption<SubOption>(TRANSLATE("Drops"), nullptr, SubmenuDrops);
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Find"), nullptr, &SessionTypes, &SessionTypeIndex, false, [] {  FindSession(SessionTypeIndex); });
					//sub->AddOption<RegularOption>(TRANSLATE("Name Spoofer"), nullptr, [] {	shownamechangerthing = true; });
					//sub->AddOption<BoolOption<bool>>("IP Spoofer", nullptr, &ipstuff, BoolDisplay::OnOff, false, [] {});
					//sub->AddOption<BoolOption<bool>>("SCID Spoofer", nullptr, &scidstuff, BoolDisplay::OnOff, false, [] {});
					//sub->AddOption<BoolOption<bool>>(TRANSLATE("Overwrite Chat Restrictions"), nullptr, &g_BypassChat, BoolDisplay::OnOff, false, [] {});
					//sub->AddOption<BoolOption<bool>>(TRANSLATE("Overwrite Map Restrictions"), nullptr, &g_BypassMap, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(("Player Join/Leave Notifications"), nullptr, &JoinLeave, BoolDisplay::OnOff, false, [] {});

					sub->AddOption<RegularOption>(("Explode Lobby"), nullptr, []
						{
							for (int i = 0; i < 32; ++i) {
								if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {
									NativeVector3 GetPlayerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(i), true);
									FIRE::ADD_EXPLOSION(GetPlayerCoords.x, GetPlayerCoords.y, GetPlayerCoords.z, 29, 20, true, false, 0, false);
									PED::EXPLODE_PED_HEAD(PLAYER::GET_PLAYER_PED(g_SelectedPlayer), 0x145F1012);
								}
							}
						});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Drops"), SubmenuDrops, [](RegularSubmenu* sub)
				{
					auto top = g_UiManager->m_SubmenuStack.top();
					SelectedDrop = top->GetSelectedOption() - 1;

					sub->AddOption<RegularOption>(TRANSLATE("Create Drop"), nullptr, [] {
						auto coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
						g_Drops.push_back({ true, 0x9CA6F755, 500, 2500, 0, coords.x, coords.y, coords.z });
						});
					for (auto i = 0; i < g_Drops.size(); ++i)
					{
						std::string gg = (std::string)(TRANSLATE("Drop")) + " " + std::to_string(i + 1);
						sub->AddOption<BoolOption<bool>>(gg.c_str(), nullptr, &g_Drops[SelectedDrop].Activated, BoolDisplay::OnOff, false, [&] {});
					}

					static bool notifyaboutfuckingbug;

					if (!notifyaboutfuckingbug)
					{
						notifyMap(116, "for some reason the toggles doesn't display properly.\ncant be bothered fixing it, deal with it");
						notifyaboutfuckingbug = false;
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Recovery"), SubmenuRecovery, [](RegularSubmenu* sub)
				{
					sub->AddOption<RegularOption>("Increase Stamina", nullptr, [] { IncreaseStamina(); });
					sub->AddOption<RegularOption>("Increase Strength", nullptr, [] { IncreaseStrength(); });
					sub->AddOption<RegularOption>("Increase Loungh", nullptr, [] { InceaseLoungh(); });
					sub->AddOption<RegularOption>("Increase Driving", nullptr, [] { IncreaseDriving(); });
					sub->AddOption<RegularOption>("Increase Flying", nullptr, [] { IncreaseFly(); });
					sub->AddOption<RegularOption>("Increase Shooting", nullptr, [] { IncreaseShooting(); });
					sub->AddOption<RegularOption>("Increase Stealth", nullptr, [] { IncreaseStealth(); });

					/*sub->AddOption<RegularOption>(TRANSLATE("Bunker Research"), nullptr, []
						{
							for (auto& i : BunkerResearch)
							{
								notifyMap(27, "Unlocking... %s", i.first);
								PackedStatBoolResearch(i.second);
							}
						});*/
					sub->AddOption<RegularOption>(("Casino Heist Outfits"), nullptr, []
						{
							for (auto& i : CasinoHeistOutfits)
							{
								notifyMap(27, "Unlocking... %s", i.first);
								PackedStatBoolCasinoHeistOutfits(i.second);
							}
						});
					sub->AddOption<RegularOption>(("Arena War Outfits"), nullptr, []
						{
							for (auto& i : ArenaWarOutfits)
							{
								notifyMap(27, "Unlocking... %s", i.first);
								PackedStatBoolArenaWar(i.second);
							}
						});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Display Settings"), SubmenuPlayerDisplay, [](RegularSubmenu* sub)
				{
					HostQueue();

					sub->AddOption<ChooseOption<const char*, std::size_t>>("Host Queue", nullptr, &Display4, &Displayy4);
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Rockstar ID"), nullptr, &Display2, &Displayy2);
					sub->AddOption<ChooseOption<const char*, std::size_t>>("IP", nullptr, &Display3, &Displayy3);
					if (Displayy2 == 1) { yesyes2 = true; }
					else { yesyes2 = false; }
					if (Displayy3 == 1) { yesyes3 = true; }
					else { yesyes3 = false; }
					if (Displayy4 == 1) { yesyes4 = false; }
					else { yesyes4 = true; }
				});


			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Protections"), SubmenuProtections, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>("Notify Events", nullptr, &p_NOTIFY_EVENTS, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<SubOption>(TRANSLATE("Create Events"), nullptr, SubmenuProtectionsModel);
					sub->AddOption<SubOption>(TRANSLATE("Network Events"), nullptr, SubmenuProtectionsNetwork);
					sub->AddOption<SubOption>(TRANSLATE("Script Events"), nullptr, SubmenuProtectionsScript);
					sub->AddOption<SubOption>(TRANSLATE("Other"), nullptr, SubmenuProtectionsOther);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Create Events"), SubmenuProtectionsModel, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Invalid Models"), nullptr, &g_InvalidModels, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Invalid Objects"), nullptr, &g_BlockInvalidObjects, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Cargo Planes"), nullptr, &g_CargoPlanes, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Cages"), nullptr, &g_Cage, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Clones"), nullptr, &g_CloneProtections, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Pick Up Kicks"), nullptr, &g_BlockPickup, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Invalid Entity Handling & Invalid Entity Hashes"), nullptr, &processnetobjprotecc, BoolDisplay::OnOff, false, [] {});
					static bool fff;
					sub->AddOption<BoolOption<bool>>(("Entity Spam"), nullptr, &fff, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<ChooseOption<const char*, int>>(TRANSLATE("Model Syncing"), nullptr, &Syncing, &g_SyncProtection);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Network Events"), SubmenuProtectionsNetwork, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Request Pickup"), nullptr, &g_RequestPickup, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Request Control"), nullptr, &g_RequestControl, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Remove Weapons"), nullptr, &g_RemoveWeapons, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Clear Ped Tasks"), nullptr, &g_ClearPedTasks, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Give Weapons"), nullptr, &g_Give_Weapons, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Sound Spam"), nullptr, &g_SoundEvent, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Wanted Level"), nullptr, &g_WantedLevelProtectiom, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Explosions"), nullptr, &g_Explosions, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Fire"), nullptr, &g_Fire, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>("PTFX", nullptr, &g_PTFX, BoolDisplay::OnOff, false, [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Script Events"), SubmenuProtectionsScript, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Bounty"), nullptr, &p_PROTECTION_BOUNTY, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Claim Bounty"), nullptr, &p_PROTECTION_CLAIM_BOUNTY, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Ceo Ban"), nullptr, &p_PROTECTION_CEO_BAN, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Ceo Kick"), nullptr, &p_PROTECTION_CEO_KICK, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Ceo Money"), nullptr, &p_PROTECTION_CEO_MONEY, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Clear Wanted"), nullptr, &p_PROTECTION_CLEAR_WANTED, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Fake Deposit"), nullptr, &p_PROTECTION_FAKE_DEPOSIT, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Force Mission"), nullptr, &p_PROTECTION_FORCE_MISSION, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("GTA Banner"), nullptr, &p_PROTECTION_GTA_BANNER, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Personal Vehicle"), nullptr, &p_PROTECTION_PERSONAL_VEHICLE, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Off Radar"), nullptr, &p_PROTECTION_OFF_RADAR, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Rotate Cam"), nullptr, &p_PROTECTION_ROTATE_CAM, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Force Cutscene"), nullptr, &p_PROTECTION_FORCE_CUTSCENE, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Force Island"), nullptr, &p_PROTECTION_FORCE_ISLAND, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Sound Spam"), nullptr, &p_PROTECTION_SOUND_SPAM, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Spectate"), nullptr, &p_PROTECTION_SPECTATE, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Force Apartment"), nullptr, &p_PROTECTION_FORCE_APARTMENT, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Transaction Error"), nullptr, &p_PROTECTION_TRANSACTION_ERROR, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Vehicle Kick"), nullptr, &p_PROTECTION_VEHICLE_KICK, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Network Bail"), nullptr, &p_PROTECTION_NETWORK_BAIL, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Freeze"), nullptr, &p_PROTECTION_FREEZE, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Bribe"), nullptr, &p_PROTECTION_BRIBE, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Block Passive"), nullptr, &p_PROTECTION_BLOCK_PASSIVE, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Kick protection"), nullptr, &p_PROTECTION_KICK, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Crash protection"), nullptr, &p_PROTECTION_CRASH, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Notify protection"), nullptr, &p_PROTECTION_NOTIFY, BoolDisplay::OnOff, false, [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Other Events"), SubmenuProtectionsOther, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Reports"), nullptr, &g_BlockReports, BoolDisplay::OnOff, false, [] {});
					//sub->AddOption<BoolOption<bool>>(("ERR_NET_ARRAY Crash"), nullptr, &ERR_NET_ARRAY, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(("Presence"), nullptr, &g_PP, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Desync Kick"), nullptr, &g_DesyncKick, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Transaction Error"), nullptr, &g_TransactionError, BoolDisplay::OnOff, false, [] {});
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Block Joining"), nullptr, &g_BlockJoining, BoolDisplay::OnOff, false, [] {});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Demo_sub"), SubmenuTest, [](RegularSubmenu* sub)
				{
					sub->AddOption<RegularOption>(("RegularOption_demo"), "A regular option.", []
						{
							g_Logger->Info("You pressed the test option");
						});

					static bool testBool1{};
					sub->AddOption<BoolOption<bool>>(("BoolOnOff_demo"), nullptr, &testBool1, BoolDisplay::OnOff);
					static bool testBool2{};
					sub->AddOption<BoolOption<bool>>(("BoolYesNo_demo"), nullptr, &testBool2, BoolDisplay::YesNo);

					static std::int32_t int32Test{ 69 };


					static std::int64_t int64Test{ 420 };
					sub->AddOption<NumberOption<std::int64_t>>("Int64", nullptr, &int64Test, 0, 1000, 10);

					static float floatTest{ 6.9f };
					sub->AddOption<NumberOption<float>>("Float", nullptr, &floatTest, 0.f, 10.f, 0.1f, 1);

					static std::vector<std::uint64_t> vector{ 1, 2, 3 };
					static std::size_t vectorPos{};

					sub->AddOption<ChooseOption<std::uint64_t, std::size_t>>("Vector", nullptr, &vector, &vectorPos);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("SubmenuSettings"), SubmenuSettings, [](RegularSubmenu* sub)
				{
					//sub->AddOption<RegularOption>(TRANSLATE("RGBA Wheel Editor"), nullptr, [] { g_Settings.m_EnableRGBWheel = true; });
					//sub->AddOption<RegularOption>(TRANSLATE("Save Settings"), nullptr, [] { g_Settings.m_EnableThemeWindow = true; });
					//sub->AddOption<SubOption>(TRANSLATE("Full Theme"), nullptr, SubmenuFullThemes);
					sub->AddOption<SubOption>(TRANSLATE("Header"), nullptr, SubmenuSettingsHeader);
					sub->AddOption<SubOption>(TRANSLATE("SubmenuBar"), nullptr, SubmenuSettingsSubmenuBar);
					sub->AddOption<SubOption>(TRANSLATE("Option"), nullptr, SubmenuSettingsOption);
					sub->AddOption<SubOption>(TRANSLATE("Footer"), nullptr, SubmenuSettingsFooter);
					sub->AddOption<SubOption>(TRANSLATE("Description"), nullptr, SubmenuSettingsDescription);
					sub->AddOption<SubOption>(("Info Box"), nullptr, SubmenuInfoBox);
					sub->AddOption<SubOption>(TRANSLATE("Input"), nullptr, SubmenuSettingsInput);
					sub->AddOption<SubOption>(TRANSLATE("Language"), nullptr, SubmenuSettingsLanguage);
					//sub->AddOption<SubOption>(TRANSLATE("Themes"), nullptr, SubmenuThemes);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Sounds"), nullptr, &g_UiManager->m_Sounds, BoolDisplay::OnOff);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Transition"), nullptr, &g_UiManager->m_ScrollSpeed, 0.f, 1.f, 0.05f, 2);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Smooth Scroll"), nullptr, &g_UiManager->m_Smoothscroll, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<std::atomic_bool>>(TRANSLATE("Log Window"), nullptr, &g_Settings.m_LogWindow, BoolDisplay::OnOff);
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Toggles"), nullptr, &g_UiManager->ToggleList, &g_UiManager->ToggleIterator);
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Submenu Indicators"), nullptr, &g_UiManager->IndicatorList, &g_UiManager->IndicatorIterator);
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Rockstar ID"), nullptr, &Display2, &Displayy2);
					sub->AddOption<NumberOption<float>>(TRANSLATE("X Position"), nullptr, &g_UiManager->m_PosX, 0.f, 1.f, 0.01f, 2);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Y Position"), nullptr, &g_UiManager->m_PosY, 0.f, 1.f, 0.01f, 2);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Width"), nullptr, &g_UiManager->m_Width, 0.01f, 1.f, 0.01f, 2);
					sub->AddOption<NumberOption<std::size_t>>(TRANSLATE("Visible Options"), nullptr, &g_UiManager->m_OptionsPerPage, 1, 25);
					sub->AddOption<RegularOption>(std::move(RegularOption(TRANSLATE("Version")).SetRightText(g_GameVariables->m_GameBuild)));
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Info Box"), SubmenuInfoBox, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>("FPS", nullptr, &Display5, &Displayy5);
					sub->AddOption<ChooseOption<const char*, std::size_t>>("Free Slots", nullptr, &Display6, &Displayy6);
					sub->AddOption<ChooseOption<const char*, std::size_t>>("Position", nullptr, &Display7, &Displayy7);

					if (Displayy5 == 1) { g_Fps = false; }
					else { g_Fps = true; }
					if (Displayy6 == 1) { g_FreeSlots = false; }
					else { g_FreeSlots = true; }
					if (Displayy7 == 1) { g_Position = false; }
					else { g_Position = true; }
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Language"), SubmenuSettingsLanguage, [](RegularSubmenu* sub)
				{
					namespace fs = std::filesystem;
					fs::directory_iterator dirIt{ g_TranslationManager->GetTranslationDirectory() };
					for (auto&& dirEntry : dirIt)
					{
						if (dirEntry.is_regular_file())
						{
							auto path = dirEntry.path();
							if (path.has_filename())
							{
								sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
									{
										g_TranslationManager->LoadTranslations(path.stem().u8string().c_str());
									});
							}
						}
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("SubmenuBar"), SubmenuSettingsSubmenuBar, [](RegularSubmenu* sub)
				{
					sub->AddOption<NumberOption<float>>(TRANSLATE("Height"), nullptr, &g_UiManager->m_SubmenuBarHeight, 0.01f, 0.1f, 0.001f, 3);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Text Size"), nullptr, &g_UiManager->m_SubmenuBarTextSize, 0.01f, 1.f, 0.01f, 2);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Show"), nullptr, &g_UiManager->m_ShowSubmenubar, BoolDisplay::OnOff);
					sub->AddOption<NumberOption<int>>(("Background R"), nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Background G"), nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Background B"), nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Background A"), nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.a, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Text R"), nullptr, &g_UiManager->m_SubmenuBarTextColor.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Text G"), nullptr, &g_UiManager->m_SubmenuBarTextColor.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Text B"), nullptr, &g_UiManager->m_SubmenuBarTextColor.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Text A"), nullptr, &g_UiManager->m_SubmenuBarTextColor.a, '\0', static_cast<int>(255));
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("SubmenuSettingsOption"), SubmenuSettingsOption, [](RegularSubmenu* sub)
				{
					sub->AddOption<NumberOption<float>>(TRANSLATE("Height"), nullptr, &g_UiManager->m_OptionHeight, 0.01f, 0.1f, 0.001f, 3);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Text Size"), nullptr, &g_UiManager->m_OptionTextSize, 0.01f, 1.f, 0.01f, 2);
					sub->AddOption<NumberOption<int>>(("Selected Background R"), nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.r, 0, 255, 1);
					sub->AddOption<NumberOption<int>>(("Selected Background G"), nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.g, 0, 255, 1);
					sub->AddOption<NumberOption<int>>(("Selected Background B"), nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.b, 0, 255, 1);
					sub->AddOption<NumberOption<int>>(("Selected Background A"), nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.a, 0, 255, 1);
					sub->AddOption<NumberOption<int>>(("Unselected Background R"), nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Unselected Background G"), nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Unselected Background B"), nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Unselected Background A"), nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.a, '\0', static_cast<int>(255));

					sub->AddOption<NumberOption<int>>(("Selected Text R"), nullptr, &g_UiManager->m_OptionSelectedTextColor.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Selected Text G"), nullptr, &g_UiManager->m_OptionSelectedTextColor.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Selected Text B"), nullptr, &g_UiManager->m_OptionSelectedTextColor.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Selected Text A"), nullptr, &g_UiManager->m_OptionSelectedTextColor.a, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Unselected Text R"), nullptr, &g_UiManager->m_OptionUnselectedTextColor.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Unselected Text G"), nullptr, &g_UiManager->m_OptionUnselectedTextColor.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Unselected Text B"), nullptr, &g_UiManager->m_OptionUnselectedTextColor.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Unselected Text A"), nullptr, &g_UiManager->m_OptionUnselectedTextColor.a, '\0', static_cast<int>(255));

					sub->AddOption<NumberOption<int>>(("Enabled Toggle R"), nullptr, &g_UiManager->m_SelectedToggle.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Enabled Toggle G"), nullptr, &g_UiManager->m_SelectedToggle.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Enabled Toggle B"), nullptr, &g_UiManager->m_SelectedToggle.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Enabled Toggle A"), nullptr, &g_UiManager->m_SelectedToggle.a, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Disabled Toggle R"), nullptr, &g_UiManager->m_UnselectedToggle.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Disabled Toggle G"), nullptr, &g_UiManager->m_UnselectedToggle.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Disabled Toggle B"), nullptr, &g_UiManager->m_UnselectedToggle.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Disabled Toggle A"), nullptr, &g_UiManager->m_UnselectedToggle.a, '\0', static_cast<int>(255));


					sub->AddOption<NumberOption<float>>(TRANSLATE("Scale Of Toggles"), nullptr, &g_UiManager->m_ToggleScale, 0.010f, 1.f, 0.002f, 2);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("SubmenuSettingsFooter"), SubmenuSettingsFooter, [](RegularSubmenu* sub)
				{
					sub->AddOption<NumberOption<float>>(TRANSLATE("aHeight"), nullptr, &g_UiManager->m_FooterHeight, 0.01f, 0.1f, 0.001f, 3);
					sub->AddOption<NumberOption<float>>(TRANSLATE("aSprite Size"), nullptr, &g_UiManager->m_FooterSpriteSize, 0.01f, 1.f, 0.001f, 3);

					sub->AddOption<NumberOption<int>>(("Background R"), nullptr, &g_UiManager->m_FooterBackgroundColor.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Background G"), nullptr, &g_UiManager->m_FooterBackgroundColor.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Background B"), nullptr, &g_UiManager->m_FooterBackgroundColor.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Background A"), nullptr, &g_UiManager->m_FooterBackgroundColor.a, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Sprite R"), nullptr, &g_UiManager->m_FooterSpriteColor.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Sprite G"), nullptr, &g_UiManager->m_FooterSpriteColor.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Sprite B"), nullptr, &g_UiManager->m_FooterSpriteColor.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("Sprite A"), nullptr, &g_UiManager->m_FooterSpriteColor.a, '\0', static_cast<int>(255));
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("SubmenuSettingsHeader"), SubmenuSettingsHeader, [](RegularSubmenu* sub)
				{
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Headertype"), nullptr, &Lists::HeaderTypesFrontend, &Lists::HeaderTypesPosition, true, []
						{
							g_UiManager->m_HeaderType = Lists::HeaderTypesBackend[Lists::HeaderTypesPosition];
						});

					switch (g_UiManager->m_HeaderType)
					{
					case HeaderType::Static:
						sub->AddOption<SubOption>(TRANSLATE("Header Background"), nullptr, SubmenuSettingsHeaderStaticBackground);
						break;
					case HeaderType::Gradient:
						sub->AddOption<SubOption>(TRANSLATE("Header Gradient"), nullptr, SubmenuSettingsHeaderGradientBackground);
						break;
					}
					sub->AddOption<SubOption>(TRANSLATE("Header Text"), nullptr, SubmenuSettingsHeaderText);
					sub->AddOption<NumberOption<float>>(TRANSLATE("Header Height"), nullptr, &g_UiManager->m_HeaderHeight, 0.01f, 0.2f, 0.001f, 3);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("SubmenuSettingsHeaderStaticBackground"), SubmenuSettingsHeaderStaticBackground, [](RegularSubmenu* sub)
				{
					sub->AddOption<NumberOption<int>>("R", nullptr, &g_UiManager->m_HeaderBackgroundColor.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>("G", nullptr, &g_UiManager->m_HeaderBackgroundColor.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>("B", nullptr, &g_UiManager->m_HeaderBackgroundColor.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>("A", nullptr, &g_UiManager->m_HeaderBackgroundColor.a, '\0', static_cast<int>(255));
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("SubmenuSettingsHeaderGradientBackground"), SubmenuSettingsHeaderGradientBackground, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Header Transparent"), nullptr, &g_UiManager->m_HeaderGradientTransparent, BoolDisplay::YesNo);
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Header Flip"), nullptr, &g_UiManager->m_HeaderGradientFlip, BoolDisplay::YesNo);

					sub->AddOption<NumberOption<int>>("R1", TRANSLATE("Currently Not Supported on the RGBA Wheel"), &g_UiManager->m_HeaderGradientColorLeft.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>("G1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>("B1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>("A1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.a, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>("R2", nullptr, &g_UiManager->m_HeaderGradientColorRight.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>("G2", nullptr, &g_UiManager->m_HeaderGradientColorRight.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>("B2", nullptr, &g_UiManager->m_HeaderGradientColorRight.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>("A2", nullptr, &g_UiManager->m_HeaderGradientColorRight.a, '\0', static_cast<int>(255));
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("SubmenuSettingsHeaderText"), SubmenuSettingsHeaderText, [](RegularSubmenu* sub)
				{
					sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable"), nullptr, &g_UiManager->m_HeaderText, BoolDisplay::OnOff);
					//sub->AddOption<BoolOption<bool>>(TRANSLATE("Enable Custom Text"), nullptr, &g_UiManager->TextKek, BoolDisplay::OnOff);
					//sub->AddOption<RegularOption>(TRANSLATE("Set Custom Text"), nullptr, [] { g_CustomTextShow = true; });
					sub->AddOption<NumberOption<float>>(TRANSLATE("Size"), nullptr, &g_UiManager->m_HeaderTextSize, 0.1f, 2.f, 0.01f, 2);
					sub->AddOption<NumberOption<int>>(("R"), nullptr, &g_UiManager->m_HeaderTextColor.r, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("G"), nullptr, &g_UiManager->m_HeaderTextColor.g, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("B"), nullptr, &g_UiManager->m_HeaderTextColor.b, '\0', static_cast<int>(255));
					sub->AddOption<NumberOption<int>>(("A"), nullptr, &g_UiManager->m_HeaderTextColor.a, '\0', static_cast<int>(255));
					g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_MAINTIT"), g_UiManager->textkek.c_str());
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("SubmenuSettingsDescription"), SubmenuSettingsDescription, [](RegularSubmenu* sub)
				{
					sub->AddOption<NumberOption<float>>(TRANSLATE("bPadding"), TRANSLATE("Padding before the description rect."), &g_UiManager->m_DescriptionHeightPadding, 0.01f, 1.f, 0.001f, 3);
					sub->AddOption<NumberOption<float>>(TRANSLATE("bHeight"), TRANSLATE("Size of the description rect."), &g_UiManager->m_DescriptionHeight, 0.01f, 1.f, 0.001f, 3);
					sub->AddOption<NumberOption<float>>(TRANSLATE("bText Size"), TRANSLATE("Size of the description text."), &g_UiManager->m_DescriptionTextSize, 0.1f, 2.f, 0.01f, 2);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("SubmenuSettingsInput"), SubmenuSettingsInput, [](RegularSubmenu* sub)
				{
					sub->AddOption<NumberOption<std::int32_t>>(TRANSLATE("Open Delay"), nullptr, &g_UiManager->m_OpenDelay, 10, 1000, 10, 0);
					sub->AddOption<NumberOption<std::int32_t>>(TRANSLATE("Back Delay"), nullptr, &g_UiManager->m_BackDelay, 10, 1000, 10, 0);
					sub->AddOption<NumberOption<std::int32_t>>(TRANSLATE("Enter Delay"), nullptr, &g_UiManager->m_EnterDelay, 10, 1000, 10, 0);
					sub->AddOption<NumberOption<std::int32_t>>(TRANSLATE("Vertical Delay"), nullptr, &g_UiManager->m_VerticalDelay, 10, 1000, 10, 0);
					sub->AddOption<NumberOption<std::int32_t>>(TRANSLATE("Horizontal Delay"), nullptr, &g_UiManager->m_HorizontalDelay, 10, 1000, 10, 0);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Playerlist"), SubmenuPlayerList, [](RegularSubmenu* sub)
				{
					g_InPlayerList = true;
					for (std::uint32_t i = 0; i < 32; ++i)
					{
						if (sub->GetSelectedOption() == sub->GetNumOptions()) {
							//pedinfo(i, 1);
						}
						if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
						{
							std::string name = PLAYER::GET_PLAYER_NAME(i);

							if (i == PLAYER::PLAYER_ID())
								name.append(" ~b~[ME]");
							if (i == NETWORK::NETWORK_GET_HOST_OF_SCRIPT("Freemode", 4294967295, 0))
								name.append(" ~y~[SCRIPT HOST]");
							if (is_player_friend(i))
								name.append(" ~g~[FRIEND]");
							if (is_player_in_interior(i))
								name.append(" ~p~[INTERIOR]");

							sub->AddOption<SubOption>(name.c_str(), nullptr, SubmenuSelectedPlayer, [=]
								{
									g_SelectedPlayer = i;
								});
						}
					}
				});



			g_UiManager->AddSubmenu<PlayerSubmenu>(&g_SelectedPlayer, SubmenuSelectedPlayer, [](PlayerSubmenu* sub)
				{
					pedinfo(g_SelectedPlayer, 1);

					sub->AddOption<BoolOption<bool>>(/*TRANSLATE*/("Stalk Player"), nullptr, &yuhisfat, BoolDisplay::OnOff);
					sub->AddOption<RegularOption>(TRANSLATE("Teleport To Player"), nullptr, [] { TeleportToPlayer(); });
					sub->AddOption<SubOption>(/*TRANSLATE*/("Benevolent"), nullptr, SubmenuFriendly);
					sub->AddOption<SubOption>(/*TRANSLATE*/("Evil"), nullptr, SubmenuEvil);
					sub->AddOption<SubOption>(/*TRANSLATE*/("Vehicle Options"), nullptr, SubmenuOnlineVehicle);

				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Benevolent"), SubmenuFriendly, [](RegularSubmenu* sub)
				{pedinfo(g_SelectedPlayer, 1);
			sub->AddOption<RegularOption>(/*TRANSLATE*/("Give all weapons"), nullptr, [] { IDontCare2(); });
			sub->AddOption<RegularOption>(/*TRANSLATE*/("Semi God"), nullptr, [] { IDontCare1(); });
			sub->AddOption<RegularOption>(TRANSLATE("Send Friend Request"), nullptr, [] { IDontCare4(); });
			sub->AddOption<RegularOption>(TRANSLATE("Display Profile"), nullptr, [] { IDontCare5(); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Malicious"), SubmenuEvil, [](RegularSubmenu* sub)
				{
					pedinfo(g_SelectedPlayer, 1);
					sub->AddOption<SubOption>(/*TRANSLATE*/("Attachments"), nullptr, SubmenuAttachments);
					sub->AddOption<SubOption>(/*TRANSLATE*/("Angry Planes"), nullptr, SubemenuAngryPanes);
					//sub->AddOption<SubOption>(/*TRANSLATE*/("Script Events"), nullptr, SubmenuScriptEvents);
					//if (g_Vip || g_Staff)
					//{
					//	sub->AddOption<SubOption>(/*TRANSLATE*/("Crashes"), nullptr, SubmenuCrashes);
					//}
					//else
					//{
					//	sub->AddOption<RegularOption>("Buy VIP to get access to crashes", nullptr, [] {});
					//}
					sub->AddOption<RegularOption>(("Damage Player"), nullptr, [] { DamagePlayer(); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Taze Player"), nullptr, [] { TazePlayer(); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Ram Player"), nullptr, [] { IDontCare3(); });
					//sub->AddOption<RegularOption>(("Host Kick"), nullptr, [] { NetworkHostKick(); });
					//sub->AddOption<RegularOption>(TRANSLATE("Desync Kick"), nullptr, [] { NetworkDesyncKick(); });
					sub->AddOption<RegularOption>(("Kill Player"), nullptr, [] { NetworkKillPlayer(); });
					sub->AddOption<RegularOption>(("Explode Player"), nullptr, [] { NetworkExplodePlayer(); });
					sub->AddOption<RegularOption>(TRANSLATE("Cage"), nullptr, [] {
						NativeVector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0);
						OBJECT::CREATE_OBJECT(959275690, remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
						});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Attachments"), SubmenuAttachments, [](RegularSubmenu* sub)
				{
					pedinfo(g_SelectedPlayer, 1);
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Objects:"), nullptr, &Objects, &ObjectIndex);
					sub->AddOption<ChooseOption<const char*, std::size_t>>(TRANSLATE("Bodypart:"), nullptr, &Bodyparts, &BodyIndex);
					sub->AddOption<RegularOption>(TRANSLATE("Attach"), nullptr, [] {  FuckFuckFuck(ObjectIndex, BodyIndex); });
					sub->AddOption<RegularOption>(TRANSLATE("Detach"), nullptr, [] { FuckFuckFuckFuckFuckFuck(); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Angry Planes"), SubemenuAngryPanes, [](RegularSubmenu* sub)
				{
					pedinfo(g_SelectedPlayer, 1);
					sub->AddOption<NumberOption<int>>(("Amount"), nullptr, &g_angry_planes.max_planes_to_spawn, 1, 50, 1, 0);
					sub->AddOption<BoolOption<bool>>(("Spawn Planes"), nullptr, &g_AngryPlanesEnable, BoolDisplay::OnOff, false, [] { if (g_AngryPlanesEnable == false) { g_angry_planes.cleanup(); } });
					sub->AddOption<BoolOption<bool>>(("Equip With Rockets"), nullptr, &g_AngryPlanesRockets, BoolDisplay::OnOff);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Script Events"), SubmenuScriptEvents, [](RegularSubmenu* sub)
				{
					pedinfo(g_SelectedPlayer, 1);
					sub->AddOption<SubOption>(/*TRANSLATE*/("Button"), nullptr, SubmenuScriptEventsButtons);
					sub->AddOption<SubOption>(/*TRANSLATE*/("Looped"), nullptr, SubmenuScriptEventsLooped);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Script Events"), SubmenuScriptEventsButtons, [](RegularSubmenu* sub)
				{
					pedinfo(g_SelectedPlayer, 1);
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Ceo Kick"), nullptr, [] { NetworkCeoKick(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Ceo Ban"), nullptr, [] { NetworkCeoBan(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Rotate Cam"), nullptr, [] { NetworkRotateCam(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Force Job"), nullptr, [] { NetworkForceJob(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Force Job II"), nullptr, [] { NetworkForceJob2(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Force Job III"), nullptr, [] { NetworkForceJob3(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("GTA Banner"), nullptr, [] { NetworkGtaBanner(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Vehicle Kick"), nullptr, [] { NetworkVehicleKick(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Block Passive"), nullptr, [] { NetworkBlockPassive(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Destroy Private Vehicle"), nullptr, [] { NetworkDestroyPrivateVehicle(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Sound Spam"), nullptr, [] { NetworkTransactionError(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Infinity Loading"), nullptr, [] { NetworkInfinityLoad(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Freeze Player"), nullptr, [] { NetworkFreezePlayer(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Claim Bounty"), nullptr, [] { NetworkClaimBounty(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Never Wanted"), nullptr, [] { NetworkNeverWanted(false); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Off Radar"), nullptr, [] { NetworkOffRadar(false); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Script Events"), SubmenuScriptEventsLooped, [](RegularSubmenu* sub)
				{
					pedinfo(g_SelectedPlayer, 1);


				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Vehicle"), SubmenuOnlineVehicle, [](RegularSubmenu* sub)
				{
					pedinfo(g_SelectedPlayer, 1);
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Set Godmode"), nullptr, [] { IDontCare3(); });
					sub->AddOption<RegularOption>(/*TRANSLATE*/("Set Invisible"), nullptr, [] { NetworkMakeVehicleInvisible(); });
					sub->AddOption<RegularOption>(("Damage Tank"), nullptr, [] { NetworkDestroyTank(); });
					sub->AddOption<RegularOption>(("KillVehEngine"), "", []
						{
							Vehicle target = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
							if (target)
								VEHICLE::SET_VEHICLE_ENGINE_HEALTH(target, -4000.f);
						});
					sub->AddOption<RegularOption>(("PopTires"), nullptr, []
						{
							Vehicle selectedlPlayerveh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), FALSE);
							bool isveh = PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), FALSE);

							if (isveh)
							{
								NetworkControlCallback obj(selectedlPlayerveh, [=] {
									VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(selectedlPlayerveh, TRUE);

									for (int i = 6; i--;)
									{
										VEHICLE::SET_VEHICLE_TYRE_BURST(selectedlPlayerveh, i, TRUE, 1000.f);
									}
									});

								obj.OnFailure();
								obj.OnSuccess();
							}
							else
							{

							}
						});
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Crashes"), SubmenuCrashes, [](RegularSubmenu* sub)
				{
					pedinfo(g_SelectedPlayer, 1);
					sub->AddOption<RegularOption>(TRANSLATE("AIO Crash"), nullptr, [] { AIOCrash(); });
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(("Message"), SubmenuTextPlayer, [](RegularSubmenu* sub)
				{
					static std::string messageeee;
					messageeee = fuckingmessage;
					static bool ifbold;
					sub->AddOption<RegularOption>(("Input"), nullptr, [] {	spamstuffidc = true; });
					sub->AddOption<ChooseOption<const char*, std::size_t>>(("Color"), nullptr, &ColorNameColors, &_Namecolors);
					sub->AddOption<BoolOption<bool>>(("Bold Text"), nullptr, &ifbold, BoolDisplay::OnOff);
					sub->AddOption<BoolOption<bool>>(("Enable Spam"), nullptr, &enabletextspam, BoolDisplay::OnOff);

					sub->AddOption<RegularOption>(("Send Once"), nullptr, [] {
						std::string bold;

						if (ifbold)
						{
							bold = "~h~";
						}
						else
						{
							bold = "";
						}

						std::string color = NameColors[_Namecolors];
						std::string message = messageeee;
						std::string custom = bold + color + message;
						if (NETWORK::NETWORK_IS_SESSION_STARTED())
						{
							int m_handle[13];
							NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, &m_handle[0], 13);
							if (NETWORK::NETWORK_IS_HANDLE_VALID(&m_handle[0], 13))
								NETWORK::NETWORK_SEND_TEXT_MESSAGE(message.c_str(), &m_handle[0]);
						}
						});

					///

					if (enabletextspam)
					{
						std::string bold;

						if (ifbold)
						{
							bold = "~h~";
						}
						else
						{
							bold = "";
						}

						std::string color = NameColors[_Namecolors];
						std::string message = messageeee;
						std::string custom = bold + color + message;
						if (NETWORK::NETWORK_IS_SESSION_STARTED())
						{
							int m_handle[13];
							NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, &m_handle[0], 13);
							if (NETWORK::NETWORK_IS_HANDLE_VALID(&m_handle[0], 13))
								NETWORK::NETWORK_SEND_TEXT_MESSAGE(message.c_str(), &m_handle[0]);
						}
					}


					//////////////

					if (messageeee != "")
					{
						std::string bold;

						if (ifbold)
						{
							bold = "~h~";
						}
						else
						{
							bold = "";
						}

						HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
						HUD::SET_TEXT_SCALE(0.8f, 0.8f);
						HUD::SET_TEXT_CENTRE(true);

						std::string color = NameColors[_Namecolors];
						std::string message = messageeee;
						std::string custom = bold + color + message;

						HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(custom.c_str());
						HUD::END_TEXT_COMMAND_DISPLAY_TEXT(0.5f, 0.85f, 0);
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>(TRANSLATE("Teleports"), SubmenuTeleports, [](RegularSubmenu* sub)
				{
					sub->AddOption<RegularOption>(TRANSLATE("Teleport To Waypoint"), nullptr, []
						{
							g_FiberScript->addTask([]()
								{
									NativeVector3 coords = g_Utility->GetBlipIcon();
									Ped ped = PLAYER::PLAYER_PED_ID();

									if (coords.x == 0 && coords.y == 0) { return; }

									if (PED::IS_PED_IN_ANY_VEHICLE(ped, 0))
										ped = PED::GET_VEHICLE_PED_IS_USING(ped);

									bool isGroundAvailable = false;
									std::vector<float> GROUND_HEIGHT{ 100.0f, 150.0f, 50.0f, 0.0f, 200.0f, 250.0f, 300.0f, 350.0f, 400.0f, 450.0f, 500.0f, 550.0f, 600.0f, 650.0f, 700.0f, 750.0f, 800.0f };

									for (int i = 0; i < GROUND_HEIGHT.size(); i++)
									{
										ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, GROUND_HEIGHT[i], 0, 0, 1);

										g_FiberScript->Wait(100);

										if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, GROUND_HEIGHT[i], &coords.z, 0))
										{
											isGroundAvailable = true;
											coords.z += 3.0;
											break;
										}
									}
									ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, coords.x, coords.y, coords.z, 0, 0, 1);
								});
						});

					sub->AddOption<RegularOption>(TRANSLATE("Teleport To Objective"), nullptr, []
						{
							g_FiberScript->addTask([]()
								{
									NativeVector3 location;

									if (get_objective_location(location))
									{
										PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), location.x, location.y, location.z);
									}
								});
						});
					sub->AddOption<SubOption>("Indoors", nullptr, TeleportIndoors);
					sub->AddOption<SubOption>("Outdoors", nullptr, TeleportOutdoors);
					sub->AddOption<SubOption>("Los Santos Customs", nullptr, TeleportLosSantosCustoms);
					sub->AddOption<SubOption>("Clothes Shops", nullptr, TeleportClothesShops);
					sub->AddOption<SubOption>("Airports", nullptr, TeleportAirports);
					sub->AddOption<SubOption>("Ammunations", nullptr, TeleportAmmunations);
					sub->AddOption<SubOption>("Barber Shops", nullptr, TeleportBarberShops);
					sub->AddOption<SubOption>("Tattoo Shop", nullptr, TeleportTattooShop);
					sub->AddOption<SubOption>("Stores", nullptr, TeleportStores);
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Indoors", TeleportIndoors, [](RegularSubmenu* sub)
				{
					for (int i = 0; i < 16; i++)
					{
						sub->AddOption<RegularOption>(TPLocationsIndoor[i].Name, nullptr, [i] {
							Vector3 coords{ TPLocationsIndoor[i].X, TPLocationsIndoor[i].Y, TPLocationsIndoor[i].Z };
							TeleportFunction(coords);
							});
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Outdoors", TeleportOutdoors, [](RegularSubmenu* sub)
				{
					for (int i = 0; i < 56; i++)
					{
						sub->AddOption<RegularOption>(TPLocationsOutdoor[i].Name, nullptr, [i] {
							Vector3 coords{ TPLocationsOutdoor[i].X, TPLocationsOutdoor[i].Y, TPLocationsOutdoor[i].Z };
							TeleportFunction(coords);
							});
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Los Santos Customs", TeleportLosSantosCustoms, [](RegularSubmenu* sub)
				{
					for (int i = 0; i < 6; i++)
					{
						sub->AddOption<RegularOption>(TPLocationsLSC[i].Name, nullptr, [i] {
							Vector3 coords{ TPLocationsLSC[i].X, TPLocationsLSC[i].Y, TPLocationsLSC[i].Z };
							TeleportFunction(coords);
							});
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Clothes Shops", TeleportClothesShops, [](RegularSubmenu* sub)
				{
					for (int i = 0; i < 13; i++)
					{
						sub->AddOption<RegularOption>(TPLocationsCS[i].Name, nullptr, [i] {
							Vector3 coords{ TPLocationsCS[i].X, TPLocationsCS[i].Y, TPLocationsCS[i].Z };
							TeleportFunction(coords);
							});
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Airports", TeleportAirports, [](RegularSubmenu* sub)
				{
					for (int i = 0; i < 7; i++)
					{
						sub->AddOption<RegularOption>(TPLocationsAirport[i].Name, nullptr, [i] {
							Vector3 coords{ TPLocationsAirport[i].X, TPLocationsAirport[i].Y, TPLocationsAirport[i].Z };
							TeleportFunction(coords);
							});
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Ammunations", TeleportAmmunations, [](RegularSubmenu* sub)
				{
					for (int i = 0; i < 11; i++)
					{
						sub->AddOption<RegularOption>(TPLocationsAmmo[i].Name, nullptr, [i] {
							Vector3 coords{ TPLocationsAmmo[i].X, TPLocationsAmmo[i].Y, TPLocationsAmmo[i].Z };
							TeleportFunction(coords);
							});
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Barber Shops", TeleportBarberShops, [](RegularSubmenu* sub)
				{
					for (int i = 0; i < 6; i++)
					{
						sub->AddOption<RegularOption>(TPLocationsBS[i].Name, nullptr, [i] {
							Vector3 coords{ TPLocationsBS[i].X, TPLocationsBS[i].Y, TPLocationsBS[i].Z };
							TeleportFunction(coords);
							});
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Tattoo Shop", TeleportTattooShop, [](RegularSubmenu* sub)
				{
					for (int i = 0; i < 6; i++)
					{
						sub->AddOption<RegularOption>(TPLocationsTS[i].Name, nullptr, [i] {
							Vector3 coords{ TPLocationsTS[i].X, TPLocationsTS[i].Y, TPLocationsTS[i].Z };
							TeleportFunction(coords);
							});
					}
				});

			g_UiManager->AddSubmenu<RegularSubmenu>("Stores", TeleportStores, [](RegularSubmenu* sub)
				{
					for (int i = 0; i < 9; i++)
					{
						sub->AddOption<RegularOption>(TPLocationsStores[i].Name, nullptr, [i] {
							Vector3 coords{ TPLocationsStores[i].X, TPLocationsStores[i].Y, TPLocationsStores[i].Z };
							TeleportFunction(coords);
							});
					}
				});
		}
	}

	void MainScript::Destroy()
	{
		g_UiManager.reset();
	}

	void MainScript::Tick()
	{
		/*globalHandle(1379108).As<int>() = INT_MAX;
		globalHandle(203).As<int>() = INT_MAX;
		globalHandle(1165).As<int>() = INT_MAX;
		globalHandle(1165).As<int>() = INT_MAX;*/

		/*static uintptr_t ModuleBaseAdress = (uintptr_t)GetModuleHandle(NULL);
		static std::uintptr_t GTA_SEND_CLONE_SYNC_PATCH = ModuleBaseAdress + 0x169A854;

		g_Utility->g_fake_position ? *(std::uint8_t*)(GTA_SEND_CLONE_SYNC_PATCH) = 0xC3 : *(std::uint8_t*)(GTA_SEND_CLONE_SYNC_PATCH) = 0x48;*/

		if (m_Initialized)
		{
			PlayerUpdateLoop();
			VehicleUpdateLoop();
			WeaponUpdateLoop();
			NetworkUpdateLoop();
			MiscUpdateLoop();
			UtilityUpdateLoop();

			//moneyDrop(dEnable, dAmount, dDelay, dx, dy, dz, dHeight);
			//dominos(g_dominos);
			//RVC(g_rvc);
			//DropMgr();
		}

		//globalHandle(4533757).As<bool>() = 1;

		g_UiManager->OnTick();
		//g_Discord->Tick();
	}
}