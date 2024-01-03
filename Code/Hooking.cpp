#include "Hooking.hpp"
#include "Game.hpp"
#include "ScriptManager.hpp"
#include "CustomText.hpp"
#include "Util.hpp"
#include "D3DRenderer.hpp"
#include "UI/UIManager.hpp"
#include <MinHook/MinHook.h>
#include "ScriptCallback.hpp"
#include "MainScript.hpp"

#include "ImGui/imgui.h"

#ifdef BIGBASE_DEBUG
#  pragma comment(lib, "MinHook-Debug.lib")
#else
#  pragma comment(lib, "MinHook-Release.lib")
#endif

namespace Big
{
	namespace
	{
		std::uint32_t g_HookFrameCount{};
	}

	bool Hooks::IsDlcPresent(std::uint32_t hash)
	{
		if (g_Running && g_HookFrameCount != (ImGui::GetIO().Framerate / 2))
		{
			g_HookFrameCount = ImGui::GetIO().Framerate / 2;
			g_ScriptManager->OnGameTick();
		}
		return static_cast<decltype(&IsDlcPresent)>(g_Hooking->m_OriginalIsDlcPresent)(hash);
	}

	const char* Hooks::GetLabelText(void* unk, const char* label)
	{
		if (g_Running)
			if (auto text = g_CustomText->GetText(Joaat(label)))
				return text;

		return static_cast<decltype(&GetLabelText)>(g_Hooking->m_OriginalGetLabelText)(unk, label);
	}

	void Hooks::TransactionErrorHandler(char* entryHeader, char* entryLine1, int instructionalKey, char* entryLine2, BOOL p4, Any p5, Any* p6, Any* p7, BOOL background)
	{
		if (SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == MISC::GET_HASH_KEY("shop_controller") && g_TransactionError)
		{
			return;
		}
		return static_cast<decltype(&TransactionErrorHandler)>(g_Hooking->m_OriginalDisableTransactionError)(entryHeader, entryLine1, instructionalKey, entryLine2, p4, p5, p6, p7, background);
	}

	bool Hooks::GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount)
	{
		auto result = static_cast<decltype(&GetEventData)>(g_Hooking->m_OriginalGetEventData)(eventGroup, eventIndex, args, argCount);
		if (NETWORK::NETWORK_IS_SESSION_ACTIVE())
		{
			if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(args[1]))
			{
				if (ENTITY::DOES_ENTITY_EXIST(ped))
				{
					if (result && g_LogScriptEvents)
					{
						g_Logger->Info(PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])));
						g_Logger->Info("Script event group: %i", eventGroup);
						g_Logger->Info("Script event index: %i", eventIndex);
						g_Logger->Info("Script event argcount: %i", argCount);
						for (std::uint32_t i = 0; i < argCount; ++i)
							g_Logger->Info("Script event args[%u] : %" PRIi64, i, args[i]);
					}

					int netHandle[13];
					const char* RID = "Nigga";
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, netHandle, 13);
					RID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);

					switch (args[0])
					{
					case PROTECTION_BOUNTY_I:
						if (p_PROTECTION_BOUNTY && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Bounty\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_BOUNTY_II:
						if (p_PROTECTION_BOUNTY && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Bounty\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_CLAIM_BOUNTY:
						if (p_PROTECTION_CLAIM_BOUNTY && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Bounty\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_CEO_BAN:
						if (p_PROTECTION_CEO_BAN && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Ceo Ban\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_CEO_KICK:
						if (p_PROTECTION_CEO_KICK && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Ceo Kick\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_CEO_MONEY:
						if (p_PROTECTION_CEO_MONEY && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Ceo Money\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_CLEAR_WANTED:
						if (p_PROTECTION_CLEAR_WANTED && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Ceo Ban\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_FAKE_DEPOSIT:
						if (p_PROTECTION_FAKE_DEPOSIT && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Fake Deposit\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_FORCE_MISSION_I:
						if (p_PROTECTION_FORCE_MISSION && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Force Mission\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case 4011926020:
						if (p_PROTECTION_FORCE_MISSION && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Force Mission\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_FORCE_MISSION_III:
						if (p_PROTECTION_FORCE_MISSION && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Force Mission\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_FORCE_MISSION_IIII:
						if (p_PROTECTION_FORCE_MISSION && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Force Mission\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_GTA_BANNER_I:
						if (p_PROTECTION_GTA_BANNER && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: GTA Banner\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_PERSONAL_VEHICLE:
						if (p_PROTECTION_PERSONAL_VEHICLE && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Destroy Personal Vehicle\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_OFF_RADAR:
						if (p_PROTECTION_OFF_RADAR && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Off Radar\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_ROTATE_CAM:
						if (p_PROTECTION_ROTATE_CAM && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Rotate Cam\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_FORCE_CUTSCENE:
						if (p_PROTECTION_FORCE_CUTSCENE && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Force Cutscene\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_FORCE_ISLAND:
						if (p_PROTECTION_FORCE_ISLAND && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Force Island\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_SOUND_SPAM:
						if (p_PROTECTION_SOUND_SPAM && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Sound Spam\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_SPECTATE:
						if (p_PROTECTION_SPECTATE && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Spectate\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_FORCE_APARTMENT:
						if (p_PROTECTION_FORCE_APARTMENT && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Force Apartment\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_TRANSACTION_ERROR:
						if (p_PROTECTION_TRANSACTION_ERROR && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Transaction Error\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_VEHICLE_KICK_I:
						if (p_PROTECTION_VEHICLE_KICK && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Vehicle Kick\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case 3580698306:
						if (p_PROTECTION_VEHICLE_KICK && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Vehicle Kick\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_NETWORK_BAIL:
						if (p_PROTECTION_NETWORK_BAIL && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Network Bail\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_FREEZE_I:
						if (p_PROTECTION_FREEZE && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Freeze\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_FREEZE_II:
						if (p_PROTECTION_FREEZE && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Freeze\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_BRIBE:
						if (p_PROTECTION_BRIBE && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Bribe\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_BLOCK_PASSIVE:
						if (p_PROTECTION_BLOCK_PASSIVE && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Block Passive\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_KICK_I:
						if (p_PROTECTION_KICK && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Kick\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_KICK_II:
						if (p_PROTECTION_KICK && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Kick\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_CRASH_I:
						if (p_PROTECTION_CRASH && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Crash\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_CRASH_II:
						if (p_PROTECTION_CRASH && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Crash\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_CRASH_III:
						if (p_PROTECTION_CRASH && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Crash\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case PROTECTION_CRASH_IIII:
						if (p_PROTECTION_CRASH && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Crash\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					case 2765370640:
						if (p_PROTECTION_NOTIFY && g_Vip)
						{
							if (p_NOTIFY_EVENTS)
							{
								notifyMap(27, "Type: Crash\nStatus: Blocked\nFrom: %s\nRockstar ID: %s", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(args[1])), RID);
							}
							args[0] = 1234;
							return false;
						}
						break;
					}
				}
			}
		}
		return result;
	}

	void Hooks::SendCloneSync(uint64_t a1, __int64 net_game_player, uint64_t net_obj, uint64_t a4, uint64_t a5, bool a6)
	{
		BYTE player = *reinterpret_cast<BYTE*>(net_game_player + 0x21);
		if (do_clone_crash[player] && clone_crash_entity[player] != NULL) {
			uint64_t net_object = *reinterpret_cast<uint64_t*>(clone_crash_entity[net_game_player] + 0xC4);
			std::uint64_t target_net_obj = *(std::uint64_t*)(player + 0xC4);
			if (net_obj) static_cast<decltype(&SendCloneSync)>(g_Hooking->m_OriginalSendCloneSync)(a1, net_game_player, net_object, a4, a5, a6);
			g_Logger->Info("Crashing...");
		}
		return static_cast<decltype(&SendCloneSync)>(g_Hooking->m_OriginalSendCloneSync)(a1, net_game_player, net_obj, a4, a5, a6);
	}

	bool Hooks::WriteSyncDataString(void* sync_data, const char* input, std::size_t length)
	{
		static bool bomuld{ true };

		if (bomuld)
		{
			std::string string_to_spoof = "Bomuld On Top";
			for (std::int32_t i = 0; i < 32; i++)
			{
				const char* raw_name = PLAYER::GET_PLAYER_NAME(i);
				if (raw_name != nullptr)
				{
					if (!strcmp(input, raw_name))
					{
						return  static_cast<decltype(&WriteSyncDataString)>(g_Hooking->m_OriginalSendCloneSync)(sync_data, string_to_spoof.c_str(), string_to_spoof.size() + 1);
					}
				}
			}
		}
		g_Logger->Info("Running");

		return static_cast<decltype(&WriteSyncDataString)>(g_Hooking->m_OriginalSendCloneSync)(sync_data, "Bomuld On Top", length);
	}

	bool Hooks::CanApplyToObject(netSyncTree* sync_tree, netObject* net_obj)
	{
		auto const root = *(void**)((uint8_t*)sync_tree + 0x10);
		auto const vehicle_creation_data = (void*)((uint8_t*)root + 0x11B8);
		auto model_hash = *(uint32_t*)((uint8_t*)vehicle_creation_data + 0xC8);
		auto model_info = g_GameFunctions->m_ModelInfo(model_hash, nullptr);
		std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);
		std::uint8_t objOwner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
		std::int32_t vehicle_type = *(std::uint8_t*)(model_info + 0x340);

		if (g_SyncProtection == 1 && g_Vip)
		{
			if (model_info)
			{
				if (model_type == 5)
				{
					if (p_NOTIFY_EVENTS)
					{
						notifyMap(27, "Type: Sync\nFrom: %s\nStatus: Blocked", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(objOwner)));
					}
					return false;
				}
			}
		}
		else if (g_SyncProtection == 2 && g_Vip)
		{
			std::uint8_t objOwner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
			if (p_NOTIFY_EVENTS)
			{
				notifyMap(27, "Type: Sync\nFrom: %s\nStatus: Blocked", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(objOwner)));
			}
			return false;
		}
		return static_cast<decltype(&CanApplyToObject)>(g_Hooking->m_OriginalCanApplyToObject)(sync_tree, net_obj);
	}

	__int64* Hooks::game_invite(__int64* a1, __int64* a2, __int64 a3)
	{
		if (g_PP)
		{
			if (a3 == 30)
			{
				return 0;
			}
		}
		return static_cast<decltype(&game_invite)>(g_Hooking->m_OriginalGameInvite)(a1, a2, a3);
	}

	int Hooks::IncrementStatEvent(__int64 neteventclass, CNetGamePlayers* Source)
	{
		const auto StatHash = *reinterpret_cast<DWORD*>(neteventclass + 0x30);
		BYTE* IP = reinterpret_cast<BYTE*>(&Source->PlayerInfo->m_external_ip);
		if (g_BlockReports && g_Vip)
		{
			switch (StatHash)
			{
			case 0xE7072CD: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Hate\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType: Hate\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			case 0x9F79BA0B: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Exploit\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType: Exploit\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			case 0x762F9994: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Annoying\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType: Annoying\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			case 0xB722D6C0: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Hate\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType: Hate\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			case 0xCBFD04A4: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Game Exploits\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType: Game Exploits\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			case 0x368F6FD9: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Bad Crew Emblem\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType: Bad Crew Emblem\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			case 0x3B566D5C: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Bad Crew Status\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType: Bad Crew Status\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			case 0x03511A79: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Bad Crew Moto\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType: Bad Crew Moto\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			case 0xAA238FF0: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Bad Crew Name\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType:  Bad Crew Name\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			case 0xF3DE4879: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Offensive UGC\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType: Offensive UGC\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			case 0xE8FB6DD5: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Offensive Tag Plate\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType: Offensive Tag Plate\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			case 0x3CDB43E2: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Offensive Language\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType: Offensive Language\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			case 0x9C6A0C42: {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Reporter: %s\nType: Griefing\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
					notifyMap(27, "Reporter: %s\nType: Griefing\nR*ID: %i\nIP: %i.%i.%i.%i", Source->PlayerInfo->sName, Source->PlayerInfo->m_rockstar_id, *(IP + 3), *(IP + 2), *(IP + 1), *IP);
				}
				return true;
				break;
			}
			};
		}
		return static_cast<decltype(&IncrementStatEvent)>(g_Hooking->m_OriginalIncrementStatEvent)(neteventclass, Source);
	}

	void Hooks::NetworkEventHandler(__int64 a1, CNetGamePlayers* a2, CNetGamePlayers* a3, unsigned __int16 a4, int a5, int a6, __int64 a7, __int64 a8)
	{
		auto ptr = Memory::pattern("66 83 FA ? 73 13 0F B7 C2 4C 89 84 C1 ? ? ? ? 4C 89 8C C1").count(1).get(0).get<char>(0);
		auto num_events = *(std::uint8_t*)(ptr + 3);
		auto name_offset = *(std::int32_t*)(ptr + 21);
		auto eventName = reinterpret_cast<char*>(*reinterpret_cast<__int64*>(a1 + 8 * a4 + name_offset));

		if (g_RemoveWeapons && g_Vip) {
			if (a4 == 14) {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Event: Remove Weapon\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
					notifyMap(27, "Event: Remove Weapon\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
				}
			}
		}
		if (g_VoteKick && g_Vip) {
			if (a4 == 64) {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Event: Votekick\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
					notifyMap(27, "Event: VoteKick\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
				}
			}
		}
		if (g_Give_Weapons && g_Vip) {
			if (a4 == 12) {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Event: Give Weapon\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
					notifyMap(27, "Event: Give Weapon\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
				}
			}
		}
		if (g_SoundEvent && g_Vip) {
			if (a4 == 51) {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Event: Sound\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
					notifyMap(27, "Event: Sound\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
				}
				return;
			}
		}
		if (g_WantedLevelProtectiom && g_Vip) {
			if (a4 == 22) {
				if (a3->is_local_player())
				{
					if (p_NOTIFY_EVENTS)
					{
						g_Logger->Info("Event: Wanted Level\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
						notifyMap(27, "Event: Wanted Level\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
					}
					return;
				}
			}
		}
		if (g_Explosions && g_Vip) {
			if (a4 == 17) {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Event: Explosion\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
					notifyMap(27, "Event: Explosion\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
				}
				return;
			}
		}
		if (g_Fire && g_Vip) {
			if (a4 == 16) {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Event: Fire\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
					notifyMap(27, "Event: Fire\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
				}
				return;
			}
		}
		if (g_ClearPedTasks && g_Vip) {
			if (a4 == 43) {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Event: Clear Tasks\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
					notifyMap(27, "Event: Clear Tasks\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
				}
				return;
			}
		}
		if (g_PTFX && g_Vip) {
			if (a4 == 75) {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Event: PTFX\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
					notifyMap(27, "Event: PTFX\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
				}
				return;
			}
		}
		if (g_RequestControl && g_Vip) {
			if (a4 == 4) {
				if (p_NOTIFY_EVENTS)
				{
					g_Logger->Info("Event: Request Controls\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
					notifyMap(27, "Event: Request Controls\nStatus: Blocked\nFrom: %s\nRID: %i", a2->PlayerInfo->sName, a2->PlayerInfo->m_rockstar_id);
				}
				return;
			}
		}

		return static_cast<decltype(&NetworkEventHandler)>(g_Hooking->m_OriginalNetworkHandler)(a1, a2, a3, a4, a5, a6, a7, a8);
	}

	void Hooks::pls(__int64 a1, __int64 a2, __int64 PlayerMaybe, __int64 a4, char a5)
	{
		g_Logger->Info("__int64 a1: %i", a1);
		g_Logger->Info("__int64 a2: %i", a2);
		g_Logger->Info("__int64 Player: %s", g_GameFunctions->m_ChatSender(PlayerMaybe)->PlayerInfo->sName);
		g_Logger->Info("__int64 a4: %i", a4);
		g_Logger->Info("char a5: %s", a5);

		return static_cast<decltype(&pls)>(g_Hooking->aaaaaaa)(a1, a2, a3, a4, a5);
	}

	LRESULT Hooks::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		g_D3DRenderer->WndProc(hWnd, msg, wParam, lParam);
		return static_cast<decltype(&WndProc)>(g_Hooking->m_OriginalWndProc)(hWnd, msg, wParam, lParam);
	}

	HRESULT Hooks::Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags)
	{
		if (g_Running)
		{
			g_D3DRenderer->BeginFrame();
			g_ScriptManager->OnD3DTick();
			RGBColorWindow(g_Settings.m_EnableRGBWheel);
			SettingNameWindowSomething();
			ShowRIDWindow();
			ShowCustomText();
			NameChangerWindow();
			FuckIHateCodingRN();
			if (testicalcancer) Crosshair();
			g_D3DRenderer->EndFrame();
		}
		return g_Hooking->m_D3DHook.GetOriginal<decltype(&Present)>(PresentIndex)(dis, syncInterval, flags);
	}

	HRESULT Hooks::ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
	{
		if (g_Running)
		{
			g_D3DRenderer->PreResize();
			auto hr = g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
			if (SUCCEEDED(hr))
			{
				g_D3DRenderer->PostResize();
			}
			return hr;
		}
		return g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
	}

	void* Hooks::AssignNewPhysicalIndexHandler(void* NetworkPlayerMgr, CNetGamePlayers* NetGamePlayer, uint8_t NewIndex)
	{
		if (JoinLeave)
		{
			if (NewIndex == 255)
			{
				if (yesyes2)
				{
					g_Logger->Info("%s is leaving slot\nR*ID: Private", NetGamePlayer->PlayerInfo->sName, NewIndex);
					notifyMap(116, "%s is leaving slot\nR*ID: Private", NetGamePlayer->PlayerInfo->sName, NewIndex);
				}
				else
				{
					g_Logger->Info("%s is leaving slot %d\nR*ID: %i", NetGamePlayer->PlayerInfo->sName, NewIndex, NetGamePlayer->PlayerInfo->m_rockstar_id);
					notifyMap(116, "%s is leaving slot %d\nR*ID: %i", NetGamePlayer->PlayerInfo->sName, NewIndex, NetGamePlayer->PlayerInfo->m_rockstar_id);
				}
			}
			else
			{
				if (yesyes2)
				{
					g_Logger->Info("%s is joining slot %d\nR*ID: Private", NetGamePlayer->PlayerInfo->sName, NewIndex);
					notifyMap(116, "%s is joining slot %d\nR*ID: Private", NetGamePlayer->PlayerInfo->sName, NewIndex);
				}
				else
				{
					g_Logger->Info("%s is joining slot %d\nR*ID: %i", NetGamePlayer->PlayerInfo->sName, NewIndex, NetGamePlayer->PlayerInfo->m_rockstar_id);
					notifyMap(116, "%s is joining slot %d\nR*ID: %i", NetGamePlayer->PlayerInfo->sName, NewIndex, NetGamePlayer->PlayerInfo->m_rockstar_id);
				}
			}
		}
		return static_cast<decltype(&AssignNewPhysicalIndexHandler)>(g_Hooking->m_OriginalAssignPhysicalIndex)(NetworkPlayerMgr, NetGamePlayer, NewIndex);
	}

	__int64* Hooks::PlayerWildCardHandler(std::int32_t friendIndex)
	{
		auto original = static_cast<decltype(&PlayerWildCardHandler)>(g_Hooking->m_OriginalRIDFunction)(friendIndex);
		if (m_EnableSCIDJoiner)
		{
			*original = m_SCIDJoiner;
			return original;
		}
		return static_cast<decltype(&PlayerWildCardHandler)>(g_Hooking->m_OriginalRIDFunction)(friendIndex);
	}

	__int64 Hooks::CPlayerListMenuConstructor(__int64 a1, __int64 a2, __int64 a3)
	{
		auto result = static_cast<decltype(&CPlayerListMenuConstructor)>(g_Hooking->m_OriginalJoinSessionHook)(a1, a2, a3);
		m_PlayerListPointer = result;
		return result;
	}

	bool Hooks::ScriptedGameEvent(void* events, CNetGamePlayers* SourcePlayer, CNetGamePlayers* ReceivingPlayer)
	{
		auto args = (std::int64_t*)(((std::uintptr_t)events) + 0x70);
		auto argCount = *(std::uint32_t*)(((std::uintptr_t)events) + 0x224) / sizeof(std::int64_t);
		static bool log{ true };
		if (ReceivingPlayer == g_GameFunctions->m_GetPlayerNetworkId(PLAYER::PLAYER_ID()))
		{
			if (SourcePlayer == nullptr) return false;
			if (log)
			{
				g_Logger->Info("Event ID: %i", args[0]);
				g_Logger->Info("Event Args: %i", argCount);
				g_Logger->Info("Sender ID: %i", SourcePlayer->m_player_id);
				g_Logger->Info("Event Sender: %s", SourcePlayer->PlayerInfo->sName);
			}

		}
		return static_cast<decltype(&ScriptedGameEvent)>(g_Hooking->m_OriginalScriptedGameEvent)(events, SourcePlayer, ReceivingPlayer);
	}

	__int64 Hooks::GetModelInfo(__int64 a1, DWORD* a2)
	{
		if (g_InvalidModels && g_Vip)
		{
			if (a1 == 0x3F039CBA) //slod_human
			{
				if (p_NOTIFY_EVENTS)
				{
					notifyMap(27, "Invalid Model Detected\nStatus: Blocked\nModel: slod_human");
				}
				a1 = 0x392D62AA;
				return false;
			}
			if (a1 == 0x856CFB02) //slod_large_quadped
			{
				if (p_NOTIFY_EVENTS)
				{
					notifyMap(27, "Invalid Model Detected\nStatus: Blocked\nModel: slod_large_quadped");
				}
				a1 = 0x392D62AA;
				return false;
			}
			if (a1 == 0x2D7030F3) //slod_small_quadped
			{
				if (p_NOTIFY_EVENTS)
				{
					notifyMap(27, "Invalid Model Detected\nStatus: Blocked\nModel: slod_small_quadped");
				}
				a1 = 0x392D62AA;
				return false;
			}
			if (a1 == 0x471BE4B2) //a_c_humpback
			{
				if (p_NOTIFY_EVENTS)
				{
					notifyMap(27, "Invalid Model Detected\nStatus: Blocked\nModel: a_c_humpback");
				}
				a1 = 0x392D62AA;
				return false;
			}
			if (a1 == 0xBAD7BB80) //a_f_o_indian_01
			{
				if (p_NOTIFY_EVENTS)
				{
					notifyMap(27, "Invalid Model Detected\nStatus: Blocked\nModel: a_f_o_indian_01");
				}
				a1 = 0x392D62AA;
				return false;
			}
		}

		if (g_BlockPickup && g_Vip)
		{
			if (a1 == 0x4D6514A3)
			{
				if (p_NOTIFY_EVENTS)
				{
					notifyMap(27, "Pickup Kick Detected\nStatus: Blocked\nModel: RPModel");
				}
				a1 = 0x392D62AA;
				return false;
			}
		}

		if (g_CargoPlanes && g_Vip)
		{
			if (a1 == 0x15F27762)
			{
				if (p_NOTIFY_EVENTS)
				{
					if (p_NOTIFY_EVENTS)
					{
						notifyMap(27, "Cargoplane Detected\nStatus: Blocked");
					}
				}
				a1 = 0x392D62AA;
			}
		}
		if (g_Cage && g_Vip)
		{
			const static std::uint32_t cages[] = { 959275690, -782380509, -476875122, 2044620980, 1202315039, -779638860, 138278167, 1533556199, 1337911167, 2138176025, 86064437, -733833763, 779277682, -1004830663,  1688773919, -1234220885, -930747176, 2081936690, -1698655922, -528704006, 237402445, -1992528326, -1235332710, 2081936690, 1326581024, 1025978577, 894554243, 1603346205, -1662909450, 169991796, -2007868701 };
			for (int i = 0; i < sizeof(cages); i++)
			{
				if (a1 == cages[i])
				{
					return false;
				}
			}
		}
		return static_cast<decltype(&GetModelInfo)>(g_Hooking->m_OriginalGetModelInfo)(a1, a2);
	}

	void Hooks::BlockInvalidObjects()
	{
		if (g_BlockInvalidObjects && g_Vip)
		{
			uint32_t Objects[] =
			{
				386259036,
				450174759,
				1567950121,
				1734157390,
				1759812941,
				2040219850,
				1727217687,
				-993438434,
				-990984874,
				-818431457,
				-681705050,
				-568850501,
				 3301528862,
				 3303982422,
				 3476535839,
				 3726116795,
				 -1231365640,
				 3041841304,
				 762327283,
				 1057201338
			};

			NativeVector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			for (Entity CrashObj : Objects)
			{
				ENTITY::DELETE_ENTITY(&CrashObj);
			}
		}
	}

	int Hooks::ChatBypassHook(__int64 ChatType, const char* Input, const char** Output)
	{
		if (g_BypassChat)
		{
			return -1;
		}
		return static_cast<decltype(&ChatBypassHook)>(g_Hooking->m_OriginalBypassChat)(ChatType, Input, Output);
	}

	void Hooks::ChatMessage(void* thisptr, __int64  unk1, __int64  unk2, const char* message)
	{
		if (message == nullptr) { return static_cast<decltype(&ChatMessage)>(g_Hooking->m_OriginalChatMessage)(thisptr, unk1, unk2, message); }

		g_Logger->Info("[CHAT] Name: %s | %s", g_GameFunctions->m_ChatSender(unk2)->PlayerInfo->sName, message);
		std::string strmsg = message;
		if (g_EnableChatCommands)
		{
			if (g_EnableChatCommandsSpawn) if (Command(strmsg, "/spawn")) { SpawnVehicleCommandFunction(strmsg.c_str(), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_GameFunctions->m_ChatSender(unk2)->m_player_id)); }
			if (g_EnableChatCommandsWeapons) if (Command(strmsg, "/weapons")) { static std::uint32_t Weapons[] = { 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, /* Melee  */   0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, /* Handguns */  0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, /* Submachine Guns */  0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D,   /* Shotguns */ 0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830,  /* Assault Rifles */ 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683,   /* Light Machine Guns */ 0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, /* Sniper Rifles  */ 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, /* Heavy Weapons  */ 0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3,  /*Throwables  */ 0x34A67B97, 0xFBAB5776, 0x060EC506,  /*Miscellaneous  */ 0xAF3696A1, 0x476BF155, 0xB62D1F67,	  /* 1.46  */ 0x2B5EF5EC, 0x2CE227AC, 0x832A1A76, 0x917F6C8C  /* Casino  */ }; for (int i = 0; i < (sizeof(Weapons) / 4); i++) { WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_GameFunctions->m_ChatSender(unk2)->m_player_id), Weapons[i], 9999, 1); } }

		}

		return static_cast<decltype(&ChatMessage)>(g_Hooking->m_OriginalChatMessage)(thisptr, unk1, unk2, message);
	}

	bool Hooks::ProcessNetObject(std::uint64_t sync_tree, std::uint64_t net_obj)
	{
		if (processnetobjprotecc && g_Vip)
		{
			DWORD dummy = 0xFF;

			switch (*reinterpret_cast<std::uint16_t*>(net_obj + 0x8))
			{
			case 0UI16:
			{
				std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // automobile
				std::uint64_t model_info = g_GameFunctions->m_ModelInfo(hash, &dummy);

				if (model_info)
				{
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);

					if (model_type == 5)
					{
						std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (vehicle_type != 0 && vehicle_type != 3)
						{
							return false;
						}
					}
					else
					{
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (p_NOTIFY_EVENTS)
						{
							notifyMap(27, "Type: Sync\nFrom: %s\nStatus: Blocked\nInvalid Car Hash", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)));
						}
						return false;
					}
				}
				break;
			}
			case 1UI16:
			{
				std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // bike
				std::uint64_t model_info = g_GameFunctions->m_ModelInfo(hash, &dummy);

				if (model_info)
				{
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);

					if (model_type == 5)
					{
						std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (vehicle_type != 11 && vehicle_type != 12) {
							return false;
						}
					}
					else
					{
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (p_NOTIFY_EVENTS)
						{
							notifyMap(27, "Type: Sync\nFrom: %s\nStatus: Blocked\nInvalid Bike Hash", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)));
						}
						return false;
					}
				}
				break;
			}
			case 2UI16:
			{
				std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // boat
				std::uint64_t model_info = g_GameFunctions->m_ModelInfo(hash, &dummy);

				if (model_info)
				{
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);

					if (model_type == 5)
					{
						std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (vehicle_type != 13) {
							return false;
						}
					}
					else
					{
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (p_NOTIFY_EVENTS)
						{
							notifyMap(27, "Type: Sync\nFrom: %s\nStatus: Blocked\nInvalid Boat Hash", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)));
						}
						return false;
					}
				}
				break;
			}
			case 4UI16:
			{
				std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // heli
				std::uint64_t model_info = g_GameFunctions->m_ModelInfo(hash, &dummy);

				if (model_info)
				{
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);

					if (model_type == 5)
					{
						std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (vehicle_type != 8) {
							return false;
						}
					}
					else
					{
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (p_NOTIFY_EVENTS)
						{
							notifyMap(27, "Type: Sync\nFrom: %s\nStatus: Blocked\nInvalid Heli Hash", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)));
						}
						return false;
					}
				}
				break;
			}
			case 9UI16:
			{
				std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // plane
				std::uint64_t model_info = g_GameFunctions->m_ModelInfo(hash, &dummy);

				if (model_info)
				{
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);

					if (model_type == 5)
					{
						std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (vehicle_type != 1 && vehicle_type != 9) {
							return false;
						}
					}
					else
					{
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (p_NOTIFY_EVENTS)
						{
							notifyMap(27, "Type: Sync\nFrom: %s\nStatus: Blocked\nInvalid Plane Hash", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)));
						}
						return false;
					}
				}

				break;
			}
			case 10UI16:
			{
				std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // submarine
				std::uint64_t model_info = g_GameFunctions->m_ModelInfo(hash, &dummy);

				if (model_info)
				{
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);

					if (model_type == 5)
					{
						std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (vehicle_type != 15) {
							return false;
						}
					}
					else
					{
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (p_NOTIFY_EVENTS)
						{
							notifyMap(27, "Type: Sync\nFrom: %s\nStatus: Blocked\nInvalid Submarine Hash", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)));
						}
						return false;
					}
				}

				break;
			}
			case 12UI16:
			{
				std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // trailer
				std::uint64_t model_info = g_GameFunctions->m_ModelInfo(hash, &dummy);

				if (model_info)
				{
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);

					if (model_type == 5)
					{
						std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (vehicle_type != 15) {
							return false;
						}
					}
					else
					{
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (p_NOTIFY_EVENTS)
						{
							notifyMap(27, "Type: Sync\nFrom: %s\nStatus: Blocked\nInvalid Submarine Hash", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)));
						}
						return false;
					}
				}
				break;
			}
			case 13UI16:
			{
				std::uint32_t hash = *(std::uint32_t*)((sync_tree + 0x1680) + 0xC8);  // trailer
				std::uint64_t model_info = g_GameFunctions->m_ModelInfo(hash, &dummy);

				if (model_info)
				{
					std::int32_t model_type = (*(std::uint8_t*)(model_info + 0x9D) & 0x1F);

					if (model_type == 5)
					{
						std::int32_t vehicle_type = *(std::int32_t*)(model_info + 0x340);
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (vehicle_type != 14) {
							return false;
						}
					}
					else
					{
						std::uint8_t owner = *reinterpret_cast<std::uint8_t*>(net_obj + 0x49);
						if (p_NOTIFY_EVENTS)
						{
							notifyMap(27, "Type: Sync\nFrom: %s\nStatus: Blocked\nInvalid Train Hash", PLAYER::GET_PLAYER_NAME(static_cast<std::int32_t>(owner)));
						}
						return false;
					}
				}
				break;
			}
			}
		}
		return static_cast<decltype(&ProcessNetObject)>(g_Hooking->m_OriginalProcessNetObject)(sync_tree, net_obj);
	}

	bool Hooks::SendNetInfo(netPlayerData* player, __int64 a2, __int64 a3, DWORD* a4)
	{
		if (scidstuff)
		{
			player->m_rockstar_id = 12345678;
		}

		if (ipstuff)
		{
			player->m_online_ip.m_field1 = 1;
			player->m_online_ip.m_field2 = 3;
			player->m_online_ip.m_field3 = 3;
			player->m_online_ip.m_field4 = 7;
		}

		return static_cast<decltype(&SendNetInfo)>(g_Hooking->m_OriginalSendNetInfo)(player, a2, a3, a4);
	}

	bool Hooks::PickupRewardMoneyIsApplicableToPlayer(void* thisptr, void* unk, void* ped)
	{
		return false;
	}

	Hooking::Hooking() :
		m_D3DHook(g_GameVariables->m_Swapchain, 18),
		m_ObjectBypass(Signature("74 48 E8 ? ? ? ? 48 8B 48 48").Scan().Add(3).Rip().Add(30).As<char*>())
	{

		std::copy_n(m_ObjectBypass, 2, m_OriginalObjectBypass);
		g_Logger->Info("started hooking");
		MH_Initialize();
		MH_CreateHook(g_GameFunctions->m_IsDlcPresent, &Hooks::IsDlcPresent, &m_OriginalIsDlcPresent);
		MH_CreateHook(g_GameFunctions->m_GetLabelText, &Hooks::GetLabelText, &m_OriginalGetLabelText);
		MH_CreateHook(g_GameFunctions->m_GetEventData, &Hooks::GetEventData, &m_OriginalGetEventData);
		MH_CreateHook(g_GameFunctions->m_WndProc, &Hooks::WndProc, &m_OriginalWndProc); 		MH_Initialize();
		MH_CreateHook(g_GameFunctions->m_AssignPhysicalIndexHandler, &Hooks::AssignNewPhysicalIndexHandler, &m_OriginalAssignPhysicalIndex);
		MH_CreateHook(g_GameFunctions->m_PlayerListMenuConstructor, &Hooks::CPlayerListMenuConstructor, &m_OriginalJoinSessionHook);
		MH_CreateHook(g_GameFunctions->m_PlayerWildcard, &Hooks::PlayerWildCardHandler, &m_OriginalRIDFunction);
		MH_CreateHook(g_GameFunctions->m_NetworkEvents, &Hooks::NetworkEventHandler, &m_OriginalNetworkHandler);
		MH_CreateHook(g_GameFunctions->m_TransactionError, &Hooks::TransactionErrorHandler, &m_OriginalDisableTransactionError);
		MH_CreateHook(g_GameFunctions->m_ModelInfo, &Hooks::GetModelInfo, &m_OriginalGetModelInfo);
		//MH_CreateHook(g_GameFunctions->m_BypassChat, &Hooks::ChatBypassHook, &m_OriginalBypassChat); 		
		MH_CreateHook(g_GameFunctions->m_PickupRewardMoneyIsApplicableToPlayer, &Hooks::PickupRewardMoneyIsApplicableToPlayer, &m_OriginalPickupRewardMoneyIsApplicableToPlayer);
		//MH_CreateHook(g_GameFunctions->m_ChatMessage, &Hooks::ChatMessage, &m_OriginalChatMessage); 	
		MH_CreateHook(g_GameFunctions->m_SendNetInfo, &Hooks::SendNetInfo, &m_OriginalSendNetInfo);
		MH_CreateHook(g_GameFunctions->m_ProcessNetObject, &Hooks::ProcessNetObject, &m_OriginalProcessNetObject);
		MH_CreateHook(g_GameFunctions->m_CanApplyToObject, &Hooks::CanApplyToObject, &m_OriginalCanApplyToObject);
		MH_CreateHook(g_GameFunctions->m_presence_game_invite, &Hooks::game_invite, &m_OriginalGameInvite);
		//	MH_CreateHook(g_GameFunctions->m_WriteSyncDataString, &Hooks::WriteSyncDataString, &m_OriginalWriteSyncDataString);
		//	MH_CreateHook(g_GameFunctions->m_SendCloneSync, &Hooks::SendCloneSync, &m_OriginalSendCloneSync);
			//MH_CreateHook(g_GameFunctions->m_ScriptedGameEvent, &Hooks::ScriptedGameEvent, &m_OriginalScriptedGameEvent); wouldn't recommend future me using this
		m_D3DHook.Hook(&Hooks::Present, Hooks::PresentIndex);
		m_D3DHook.Hook(&Hooks::ResizeBuffers, Hooks::ResizeBuffersIndex);
	}

	Hooking::~Hooking() noexcept
	{
		MH_RemoveHook(g_GameFunctions->m_WndProc);
		MH_RemoveHook(g_GameFunctions->m_GetEventData);
		MH_RemoveHook(g_GameFunctions->m_GetLabelText);
		MH_RemoveHook(g_GameFunctions->m_IsDlcPresent);
		MH_RemoveHook(g_GameFunctions->m_AssignPhysicalIndexHandler);
		MH_RemoveHook(g_GameFunctions->m_PlayerListMenuConstructor);
		MH_RemoveHook(g_GameFunctions->m_PlayerWildcard);
		MH_RemoveHook(g_GameFunctions->m_NetworkEvents);
		MH_RemoveHook(g_GameFunctions->m_TransactionError);
		MH_RemoveHook(g_GameFunctions->m_ModelInfo);
		MH_RemoveHook(g_GameFunctions->m_BypassChat);
		MH_RemoveHook(g_GameFunctions->m_ChatMessage);
		MH_RemoveHook(g_GameFunctions->m_SendNetInfo);
		MH_RemoveHook(g_GameFunctions->m_PickupRewardMoneyIsApplicableToPlayer);
		MH_RemoveHook(g_GameFunctions->m_ProcessNetObject);
		MH_RemoveHook(g_GameFunctions->m_CanApplyToObject);
		MH_RemoveHook(g_GameFunctions->m_presence_game_invite);
		//MH_RemoveHook(g_GameFunctions->m_WriteSyncDataString);
		//MH_RemoveHook(g_GameFunctions->m_SendCloneSync);
		//MH_RemoveHook(g_GameFunctions->m_ScriptedGameEvent);
		MH_Uninitialize();
	}

	void Hooking::Hook()
	{
		std::fill_n(m_ObjectBypass, 2, '\x90');
		m_D3DHook.Enable();

		MH_EnableHook(MH_ALL_HOOKS);
	}

	void Hooking::Unhook()
	{
		std::copy_n(m_OriginalObjectBypass, 2, m_ObjectBypass);
		m_D3DHook.Disable();
		g_GameFunctions->small_host_token_patch = false;
		MH_DisableHook(MH_ALL_HOOKS);
	}
}
