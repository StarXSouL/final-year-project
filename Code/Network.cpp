#include "Common.hpp"
#include "ScriptCallback.hpp"
#include <random>

namespace Big
{
	void TazePlayer()
	{
		int currentAttempt = 0;
		int maxAttempts = 20;
		while (!ENTITY::IS_ENTITY_DEAD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false))
		{
			if (currentAttempt >= maxAttempts)
			{
				break;
			}
			else
			{
				NativeVector3 destination = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), SKEL_ROOT, 0.0f, 0.0f, 0.0f);
				NativeVector3 origin = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), SKEL_R_Hand, 0.0f, 0.0f, 0.2f);
				Hash tazerHash = MISC::GET_HASH_KEY((char*)"WEAPON_STUNGUN");
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1, 0, tazerHash, PLAYER::PLAYER_PED_ID(), false, false, 1);
				currentAttempt++;
			}
		}
	}

	void RamPlayer()
	{
		Hash model = MISC::GET_HASH_KEY("INSURGENT");

		g_CallbackScript->AddCallback<ModelCallback>(model, [model] {
			float offset;
			STREAMING::REQUEST_MODEL(model);
			NativeVector3 pCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0.0, -10.0, 0.0);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				NativeVector3 dim1, dim2;
				MISC::GET_MODEL_DIMENSIONS(model, &dim1, &dim2);

				offset = dim2.y * 1.6;

				NativeVector3 dir = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
				float rot = (ENTITY::GET_ENTITY_ROTATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0)).z;
				pCoords.x + (dir.x * offset);
				pCoords.y + (dir.y * offset);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(model, pCoords.x, pCoords.y, pCoords.z, rot, true, false, 0);

				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 0);
				ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 1000.0);
			}
			});
	}

	void TeleportToPlayer()
	{
		Entity handle;
		NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true))
		{
			std::int32_t ped_veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), false);
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), ped_veh, -2);
		}
		else 
		{
			PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : handle = PLAYER::PLAYER_PED_ID();
			ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);
		}
	}

	void NetworkCeoBan(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { 1240068495, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 3, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { 1240068495, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkCeoKick(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { -1425016400, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 3, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { -1425016400, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkRotateCam(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { -3735749176626599337, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { -3735749176626599337, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkForceJob(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { 4011926020, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { 4011926020, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkForceJob2(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { -283041276, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { -283041276, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkForceJob3(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { 360408846, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { 360408846, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkVehicleKick(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { 3580698306, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { 3580698306, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkGtaBanner(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { -7642965105622237451, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { -7642965105622237451, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkBlockPassive(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { 65268844, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { 65268844, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkDestroyPrivateVehicle(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { -714268990, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { -714268990, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkTransactionError(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { 547083265, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { 547083265, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkInfinityLoad(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { -1390976345, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { -1390976345, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkFreezePlayer(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { 2130458390, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { 2130458390, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkClaimBounty(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { 2881715287, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { 2881715287, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkNeverWanted(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { 1449852136, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { 1449852136, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void NetworkOffRadar(bool lobby)
	{
		if (lobby)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { -1973627888, i };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 2, 1 << i);
			}
		}
		else
		{
			DWORD64 args[2] = { -1973627888, g_SelectedPlayer };
			SCRIPT::TRIGGER_SCRIPT_EVENT(0, args, 2, 1 << g_SelectedPlayer);
		}
	}

	void AIOCrash()
	{

		DWORD dummy = 0xFF;
		Hash hash = MISC::GET_HASH_KEY("adder");;
		uint64_t model_info = g_GameFunctions->m_ModelInfo(hash, &dummy);
		if (model_info != 0) {

			g_CallbackScript->AddCallback<ModelCallback>((hash), [=] {
				*reinterpret_cast<int*>(model_info + 0x340) = 8;
				NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, coords.x, coords.y, coords.z, 0, true, false, 0);
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::VEH_TO_NET(veh), 1);
				if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(veh))
					DECORATOR::DECOR_SET_INT(veh, "MPBitset", (1 << 10));
				if (ENTITY::DOES_ENTITY_EXIST(veh)) {
					ENTITY::SET_ENTITY_VISIBLE(veh, 1, 0);
					VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 0);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
				}
				*reinterpret_cast<int*>(model_info + 0x340) = 0;

				});
		}

	}

	const uint32_t InvalidObjects[] =
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
		-1231365640
	};

	void DesyncProtection(bool toggle)
	{
		if (toggle)
		{
			Entity me = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_PED_ID());
			int net = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(me);
			while (NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(net))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(net);
			}
			NETWORK::_SET_NETWORK_ID_SYNC_TO_PLAYER(net, PLAYER::PLAYER_ID(), true);
		}
	}

	void DuplaicateVehicle(std::int32_t player)
	{
		Vehicle pedVeh = NULL;
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(player, 0))
		{
			pedVeh = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			if (ENTITY::DOES_ENTITY_EXIST(pedVeh))
			{
				Hash vehicleModelHash = ENTITY::GET_ENTITY_MODEL(pedVeh);
				g_CallbackScript->AddCallback<ModelCallback>(vehicleModelHash, [vehicleModelHash, playerPed, pedVeh]
				{
					NativeVector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
					Vehicle playerVeh = VEHICLE::CREATE_VEHICLE(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z, ENTITY::GET_ENTITY_HEADING(playerPed), true, false, 0);
					PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, -1);
					int primaryColor, secondaryColor;
					VEHICLE::GET_VEHICLE_COLOURS(pedVeh, &primaryColor, &secondaryColor);
					VEHICLE::SET_VEHICLE_COLOURS(playerVeh, primaryColor, secondaryColor);
					if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(pedVeh))
					{
						int r, g, b;
						VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(pedVeh, &r, &g, &b);
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVeh, r, g, b);
					}
					if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(pedVeh))
					{
						int r, g, b;
						VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(pedVeh, &r, &g, &b);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(playerVeh, r, g, b);
					}
					if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicleModelHash) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicleModelHash))
					{
						VEHICLE::SET_VEHICLE_MOD_KIT(playerVeh, 0);
						VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, VEHICLE::GET_VEHICLE_WHEEL_TYPE(pedVeh));
						for (int i = 0; i <= 24; i++)
						{
							if (i > 16 && i < 23)
								VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, i, VEHICLE::IS_TOGGLE_MOD_ON(pedVeh, i));
							else
								VEHICLE::SET_VEHICLE_MOD(playerVeh, i, VEHICLE::GET_VEHICLE_MOD(pedVeh, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(pedVeh, i));
						}
						int tireSmokeColor[3], pearlescentColor, wheelColor;
						VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(pedVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
						VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(pedVeh));
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(pedVeh));
						VEHICLE::GET_VEHICLE_EXTRA_COLOURS(pedVeh, &pearlescentColor, &wheelColor);
						VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, pearlescentColor, wheelColor);
						if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(pedVeh, 0))
						{
							int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(pedVeh);
							if (convertableState == 0 || convertableState == 3 || convertableState == 5)
								VEHICLE::RAISE_CONVERTIBLE_ROOF(playerVeh, 1);
							else
								VEHICLE::LOWER_CONVERTIBLE_ROOF(playerVeh, 1);
						}
						for (int i = 0; i <= 3; i++)
						{
							VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(pedVeh, i));
						}
						for (int i = 0; i <= 11; i++)
						{
							if (VEHICLE::DOES_EXTRA_EXIST(pedVeh, i))
								VEHICLE::SET_VEHICLE_EXTRA(playerVeh, i, !VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(pedVeh, i));
						}
						if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(pedVeh) > 1) && VEHICLE::GET_VEHICLE_LIVERY(pedVeh) >= 0)
						{
							VEHICLE::SET_VEHICLE_LIVERY(playerVeh, VEHICLE::GET_VEHICLE_LIVERY(pedVeh));
						}
						int neonColor[3];
						VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
						VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, neonColor[0], neonColor[1], neonColor[2]);
						VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(pedVeh));
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVeh, VEHICLE::GET_VEHICLE_DIRT_LEVEL(pedVeh));
					}
					//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);
				});
			}
		}
	}

	void BypassMap(bool toggle)
	{
		if (toggle)
		{
			PLAYER::_EXPAND_WORLD_LIMITS(50000.0, 50000.0, 50.0);
			PLAYER::_EXPAND_WORLD_LIMITS(-50000.0, -50000.0, 50.0);

			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("am_armybase");
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("restrictedareas");
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_armybase");
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_lossantosintl");
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prison");
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prisonvanbreak");
			MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("am_doors");
		}
	}

	void displayforretards(bool toggle, int bodyindex)
	{
		
	}

	void FuckFuckFuck(int modelindex, int bodypartindex)
	{

		Hash model = MISC::GET_HASH_KEY(Objects[modelindex]);
		NativeVector3 player = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0);
		g_CallbackScript->AddCallback<ModelCallback>(model, [=] {
			Object obj = OBJECT::CREATE_OBJECT(model, player.x, player.y, player.z, 1, 1, 1);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(obj, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), Bodypartsint[bodypartindex], 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1);
			ent.push_back(obj);
		});
	}

	void FuckFuckFuckFuckFuckFuck()
	{
		for (auto a : ent)
		{
	
			ENTITY::DETACH_ENTITY(a, 1, 1);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(a, 1, 1);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&a);
			ENTITY::DELETE_ENTITY(&a);
			ent.clear();
		}
	}


	void IDontCare1()
	{
		Hash oball = MISC::GET_HASH_KEY("prop_juicestand");

		g_CallbackScript->AddCallback<ModelCallback>(oball, [=] {

			int orangeball = OBJECT::CREATE_OBJECT(oball, 0, 0, 0, true, 1, 0);
			RequestControlOfEnt(orangeball);
			ENTITY::SET_ENTITY_VISIBLE(orangeball, 0, 0);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(orangeball, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
		});
	}

	void IDontCare2()
	{
		uint32_t Weapons[] = { 0x184140A1, 0xDB26713A, 0x45CD9CF3, 0xC78D71B4, 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, /* Melee  */   0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, /* Handguns */  0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, /* Submachine Guns */  0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D,   /* Shotguns */ 0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830,  /* Assault Rifles */ 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683,   /* Light Machine Guns */ 0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, /* Sniper Rifles  */ 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, /* Heavy Weapons  */ 0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3,  /*Throwables  */ 0x34A67B97, 0xFBAB5776, 0x060EC506,  /*Miscellaneous  */ 0xAF3696A1, 0x476BF155, 0xB62D1F67,	  /* 1.46  */ 0x2B5EF5EC, 0x2CE227AC, 0x832A1A76, 0x917F6C8C,  /* Casino  */  /* 1.61 */ -610080759, 1853742572, -774507221 /* Criminal Enterprise */ };
		for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), Weapons[i], 9999, 1);
		}
	}

	void IDontCare3()
	{
		Entity car = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0);
		ENTITY::SET_ENTITY_INVINCIBLE(car, true);
	}

	void NetworkMakeVehicleInvisible()
	{
		Entity car = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0);
		ENTITY::SET_ENTITY_VISIBLE(car, 0, 1);

	}

	void IDontCare4()
	{
		int handle[76]; //var num3 = sub_34009(A_0, (A_1) + 264, (A_1) + 272);
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, &handle[0], 13);
		NETWORK::NETWORK_ADD_FRIEND(&handle[0], "Join the Cult");
	}

	void IDontCare5()
	{
		int handle[76];
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(g_SelectedPlayer, &handle[0], 13);
		NETWORK::NETWORK_SHOW_PROFILE_UI(&handle[0]);
	}

	void PeopleBuyingMenusForPlayerThigsAreBeyondRetardedFuckThemHonestly()
	{
		Player playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, 0);
		{
			RequestControlOfEnt(veh);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 300.0);
		}
	}

	void Peepe(bool toggle)
	{
		if (toggle)
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(1, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer));
		else
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(0, PLAYER::PLAYER_ID());
	}

	void NetworkHostKick()
	{
		if (g_SelectedPlayer != PLAYER::PLAYER_ID())
			NETWORK::NETWORK_SESSION_KICK_PLAYER(g_SelectedPlayer);
		else
			notifyMap(26, "Just try to enjoy this game man...");
	}

	void NetworkDestroyTank()
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0);
		VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(veh, -VEHICLE::GET_VEHICLE_PETROL_TANK_HEALTH(veh));
		notifyMap(1, "HAHAHA ur such a bad boy");
	}

	void NetworkCageThisNigger()
	{
		NativeVector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0);
		OBJECT::CREATE_OBJECT(959275690, remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
	}

	void NetworkUpdateLoop()
	{
		NetworkUpdateYuhsObeseStatus();
		BypassMap(g_BypassMap);
		DesyncProtection(g_DesyncKick);
	}

	inline std::string Weaponheld(Player player)
	{
		Hash weaponHash;
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), &weaponHash, 0);
		switch (weaponHash)
		{	//New hashes MK2  0xBFE256D4, 0x88374054, 0xCB96392F, 0x78A97CD0, 0x555AF99A, 0x394F415C, 0xFAD1F1C9, 0x969C3D67, 0x84D6FAFD, 0xDBBD7280, 0xA914799, 0x6A6C02E0
		case -1569615261:
			return "Unarmed";
			break;
		case -1716189206:
			return "Knife";
			break;
		case 1737195953:
			return "Nightstick";
			break;
		case 1317494643:
			return "Hammer";
			break;
		case -1786099057:
			return "Bat";
			break;
		case -2067956739:
			return "Crowbar";
			break;
		case 1141786504:
			return "Golfclub";
			break;
		case -102323637:
			return "Bottle";
			break;
		case -1834847097:
			return "Dagger";
			break;
		case -102973651:
			return "Hatchet";
			break;
		case -656458692:
			return "Knuckle Duster";
			break;
		case -581044007:
			return "Machete";
			break;
		case -1951375401:
			return "Flashlight";
			break;
		case -538741184:
			return "Switch Blade";
			break;
		case -1810795771:
			return "Poolcue";
			break;
		case 419712736:
			return "Wrench";
			break;
		case -853065399:
			return "Battle Axe";
			break;
		case 0x3813FC08:
			return "Stone Hatchet";
			break;
		case 453432689:
			return "Pistol";
			break;
		case 3219281620:
			return "Pistol Mk2";
			break;
		case 1593441988:
			return "Combat Pistol";
			break;
		case -1716589765:
			return "Pistol 50";
			break;
		case -1076751822:
			return "SNS Pistol";
			break;
		case 0x88374054:
			return "SNS Pistol Mk2";
			break;
		case -771403250:
			return "Heavy Pistol";
			break;
		case 137902532:
			return "Vintage Pistol";
			break;
		case -598887786:
			return "Marksman Pistol";
			break;
		case -1045183535:
			return "Revolver";
			break;
		case 0xCB96392F:
			return "Revolver Mk2";
			break;
		case 584646201:
			return "AP Pistol";
			break;
		case 911657153:
			return "Stun Gun";
			break;
		case 1198879012:
			return "Flare Gun";
			break;
		case 0x97EA20B8:
			return "Double Action Revolver";
			break;
		case 0xAF3696A1:
			return "Up-n-Atomizer";
			break;
		case 324215364:
			return "Micro SMG";
			break;
		case -619010992:
			return "Machine Pistol";
			break;
		case 736523883:
			return "SMG";
			break;
		case 2024373456:
			return "SMG Mk2";
			break;
		case -270015777:
			return "Assault SMG";
			break;
		case 171789620:
			return "Combat PDW";
			break;
		case -1660422300:
			return "MG";
			break;
		case 2144741730:
			return "Combat MG";
			break;
		case 368662592:
			return "Combat MG Mk2";
			break;
		case 1627465347:
			return "Gusenberg";
			break;
		case -1121678507:
			return "Mini SMG";
			break;
		case 0x476BF155:
			return "Unholy Hellbringer";
			break;
		case -1074790547:
			return "Assault Rifle";
			break;
		case 961495388:
			return "Assault Rifle Mk2";
			break;
		case -2084633992:
			return "Carbine Rifle";
			break;
		case 4208062921:
			return "Carbine Rifle Mk2";
			break;
		case -1357824103:
			return "Advanced Rifle";
			break;
		case -1063057011:
			return "Special Carbine";
			break;
		case 0x969C3D67:
			return "Special Carbine Mk2";
			break;
		case 2132975508:
			return "Bullpup Rifle";
			break;
		case 0x84D6FAFD:
			return "Bullpup Rifle Mk2";
			break;
		case 1649403952:
			return "Compact Rifle";
			break;
		case 100416529:
			return "Sniper Rifle";
			break;
		case 205991906:
			return "Heavy Sniper";
			break;
		case 177293209:
			return "Heavy Sniper Mk2";
			break;
		case -952879014:
			return "Marksman Rifle";
			break;
		case 0x6A6C02E0:
			return "Marksman Rifle Mk2";
			break;
		case 487013001:
			return "Pump Shotgun";
			break;
		case 0x555AF99A:
			return "Pump Shotgun Mk2";
			break;
		case 2017895192:
			return "Sawnoff Shotgun";
			break;
		case -1654528753:
			return "Bullpup Shotgun";
			break;
		case -494615257:
			return "Assault Shotgun";
			break;
		case -1466123874:
			return "Musket";
			break;
		case 984333226:
			return "Heavy Shotgun";
			break;
		case -275439685:
			return "Double Barrel Shotgun";
			break;
		case 317205821:
			return "Sweeper Shotgun";
			break;
		case -1568386805:
			return "Grenade Launcher";
			break;
		case -1312131151:
			return "RPG";
			break;
		case 1119849093:
			return "Minigun";
			break;
		case 2138347493:
			return "Firework";
			break;
		case 1834241177:
			return "Railgun";
			break;
		case 1672152130:
			return "Homing Launcher";
			break;
		case 1305664598:
			return "Grenade Launcher Smoke";
			break;
		case 125959754:
			return "Compact Launcher";
			break;
		case 0xB62D1F67:
			return "Widowmaker";
			break;
		case -1813897027:
			return "Grenade";
			break;
		case 741814745:
			return "Sticky Bomb";
			break;
		case -1420407917:
			return "Proximity Mine";
			break;
		case -1600701090:
			return "BZ Gas";
			break;
		case 615608432:
			return "Molotov";
			break;
		case 101631238:
			return "Fire Extinguisher";
			break;
		case 883325847:
			return "Petrol Can";
			break;
		case 1233104067:
			return "Flare";
			break;
		case 600439132:
			return "Ball";
			break;
		case 126349499:
			return "Snowball";
			break;
		case -37975472:
			return "Smoke Grenade";
			break;
		case -1169823560:
			return "Pipebomb";
			break;
		case -72657034:
			return "Parachute";
			break;

		default:
			return "None Found";
			break;
		}
		return "Unknown";
	}

	inline float GetDistanceFloat(NativeVector3 pointA, NativeVector3 pointB) {
		float a_x = pointA.x;
		float a_y = pointA.y;
		float a_z = pointA.z;
		float b_x = pointB.x;
		float b_y = pointB.y;
		float b_z = pointB.z;
		double x_ba = (double)(b_x - a_x);
		double y_ba = (double)(b_y - a_y);
		double z_ba = (double)(b_z - a_z);
		double y_2 = y_ba * y_ba;
		double x_2 = x_ba * x_ba;
		double sum_2 = y_2 + x_2;
		return(float)sqrt(sum_2 + z_ba);
	}

	void pedinfo(std::int32_t player, bool show)
	{

		/*if (!show) return;
		Hash Street[2]{};
		float RoundedDistance{};
		Ped PlayerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Vehicle Vehicle = PED::GET_VEHICLE_PED_IS_IN(PlayerPed, false);
		NativeVector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		NativeVector3 Coords = ENTITY::GET_ENTITY_COORDS(PlayerPed, false);
		Hash VehicleHash = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PlayerPed, 0));
		bool Connected = NETWORK::NETWORK_IS_SESSION_ACTIVE();
		bool InVehicle = PED::IS_PED_IN_ANY_VEHICLE(PlayerPed, true);
		PATHFIND::GET_STREET_NAME_AT_COORD(Coords.x, Coords.y, Coords.z, &Street[0], &Street[1]);
		const char* RID = "Nigga";
		int netHandle[13];
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, netHandle, 13);
		
		if (yesyes2)
		{
			RID = "Private";
		}
		else
		{
			RID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);
		}
		

		std::stringstream coordx;
		coordx << std::fixed << std::setprecision(0) << Coords.x;
		std::string COORDX = coordx.str();

		std::stringstream coordy;
		coordy << std::fixed << std::setprecision(0) << Coords.y;
		std::string COORDY = coordy.str();

		std::stringstream coordz;
		coordz << std::fixed << std::setprecision(0) << Coords.z;
		std::string COORDZ = coordz.str();

		int HealthProgress = ENTITY::GET_ENTITY_HEALTH(PlayerPed) * 100 / ENTITY::GET_ENTITY_MAX_HEALTH(PlayerPed);

		int ArmorProgress = PED::GET_PED_ARMOUR(PlayerPed) * 100 / PLAYER::GET_PLAYER_MAX_ARMOUR(player);
		std::ostringstream WantedLevel; WantedLevel << "~s~" << PLAYER::GET_PLAYER_WANTED_LEVEL(player);

		long long money = *script_global(1590908).at(player, 874).at(205).at(3).as<long long*>();
		int rp = *script_global(1590908).at(player, 874).at(205).at(5).as<int*>();
		int rank = *script_global(1590908).at(player, 874).at(205).at(6).as<int*>();
		int kills = *script_global(1590908).at(player, 874).at(205).at(28).as<int*>();
		int deaths = *script_global(1590908).at(player, 874).at(205).at(29).as<int*>();
		float kd = *script_global(1590908).at(player, 874).at(205).at(26).as<float*>();
		int _handle = *script_global(1590908).at(player, 874).at(205).at(56).as<int*>();
		int handle2 = *script_global(1590908).at(player, 874).at(205).at(3).as<int*>();
		int bankMoney = _handle - handle2;
		int totalmoney = money + bankMoney;

		std::stringstream _kd;
		_kd << std::fixed << std::setprecision(2) << kd;
		std::string KD = _kd.str();

		const char* empty = "";
		float speed = ENTITY::GET_ENTITY_SPEED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
		int inInterior = INTERIOR::GET_INTERIOR_FROM_ENTITY(PlayerPed);

		bool frnd;

		NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(player);
		bool self, Friend, Cutscene, Modder, Modded, Host, Interior, Talking = false;

		int handle[76];
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &handle[0], 13);
		if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle[0], 13))
		{
			Friend = NETWORK::NETWORK_IS_FRIEND(&handle[0]);
		}
		const char* sender = PLAYER::GET_PLAYER_NAME(player);

		float distance = GetDistanceFloat(PedCoords, Coords);
		std::ostringstream Distance;
		Distance << distance;


		const char* direction = "";
		float pedHeading = ENTITY::_GET_ENTITY_PHYSICS_HEADING(PlayerPed);
		if (pedHeading < 90)
			direction = "North ";
		else if (pedHeading > 90 && pedHeading < 180)
			direction = "East ";
		else if (pedHeading > 180 && pedHeading < 270)
			direction = "South ";
		else if (pedHeading > 270 && pedHeading < 360)
			direction = "West ";

		std::stringstream heading;
		heading << std::fixed << std::setprecision(0) << pedHeading;
		std::string Heading = heading.str();

		std::string ipaddress;
		char ipBuf[32] = {};
		char buffer[32] = {};
		static auto nice = (std::uintptr_t(*)(int))Memory::pattern("40 53 48 83 EC 20 33 DB 38 1D ? ? ? ? 74 1C").count(1).get(0).get<void>(0);
		auto porto = Memory::pattern("40 53 48 83 EC 20 33 DB 38 1D ? ? ? ? 74 1C").count(1).get(0).get<void>(0);
		auto woah = nice(player);
		if (woah)
		{
			auto okay = *(uintptr_t*)(woah + 0x10C8);
			if (okay)
			{
				auto port = (uint16_t*)(okay + 0x38);
				std::snprintf(buffer, sizeof(buffer), "%u", *port);
				auto ip = (BYTE*)(okay + 0x6C);
				std::snprintf(ipBuf, sizeof(ipBuf) - 1, "%u.%u.%u.%u", ip[3], ip[2], ip[1], *ip);
			}
		}
		const char* ipguy = ipBuf;
		if (yesyes3)
		{
			ipaddress = "Private";
		}
		else
		{
			ipaddress = ipguy;
		}

		if (ENTITY::DOES_ENTITY_EXIST(PlayerPed))
		{
			g_UiManager->PlayerBox(PLAYER::GET_PLAYER_NAME(player));
			g_UiManager->PlayerMultiInfo("Rank", std::to_string(rank), "Health", std::to_string(ENTITY::GET_ENTITY_HEALTH(PlayerPed)));
			g_UiManager->PlayerMultiInfo("Cash", std::to_string(money), "Armor", std::to_string(PED::GET_PED_ARMOUR(PlayerPed)));
			g_UiManager->PlayerMultiInfo("Bank", std::to_string(bankMoney), "Wanted Level", std::to_string(PLAYER::GET_PLAYER_WANTED_LEVEL(player)) + "/5");
			g_UiManager->PlayerMultiInfo("K/D", KD, "State", ENTITY::IS_ENTITY_DEAD(player, NULL) ? "Alive" : "Dead");
			g_UiManager->PlayerInfo("Weapon", Weaponheld(player).c_str());
			if (PED::IS_PED_IN_ANY_VEHICLE(PlayerPed, true))
				g_UiManager->PlayerInfo("Vehicle", PED::IS_PED_IN_ANY_VEHICLE(PlayerPed, 1) ? HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PlayerPed, 0)))) : "None");
			g_UiManager->PlayerInfo("Zone", &("~s~" + (std::string)HUD::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(Coords.x, Coords.y, Coords.z)))[0]);
			g_UiManager->PlayerInfo("Street", HUD::GET_STREET_NAME_FROM_HASH_KEY(Street[0]));
			g_UiManager->PlayerMultiInfo("Coords", "[" + COORDX + "," + COORDY + "," + COORDZ + "]", "Heading", direction + Heading);
			g_UiManager->PlayerMultiInfo("Distance", (char*)Distance.str().c_str(), "Script Host", (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) == player) ? "Yes" : "No");
			g_UiManager->PlayerMultiInfo("Invincibility", PLAYER::GET_PLAYER_INVINCIBLE(player) ? "Yes" : "No", "Invisible", !ENTITY::IS_ENTITY_VISIBLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player)) ? "Yes" : "No");
			g_UiManager->PlayerInfo("RID", RID);
		}*/
	}

	std::vector<std::pair<std::uint64_t, std::int32_t>> MigrationQueue;

	void HostQueue()
	{
		/*g_UiManager->HostMigrationManager();

		if (NETWORK::NETWORK_IS_IN_SESSION())
		{
			MigrationQueue.clear();
			for (auto i = 0; i < 32; i++) {
				if (!NETWORK::NETWORK_IS_PLAYER_ACTIVE(i))
					continue;
				if (g_GameFunctions->m_GetNetPlayer(i)->is_host())
					continue;
				const char* NamePointer = PLAYER::GET_PLAYER_NAME(i);
				if (NamePointer == nullptr)
					continue;
				std::uint64_t PlayerKey = *(std::uint64_t*)(NamePointer - 0x24);
				if (PlayerKey == NULL)
					continue;
				MigrationQueue.push_back(std::make_pair(PlayerKey, i));
			}

			std::sort(MigrationQueue.begin(), MigrationQueue.end());

			for (int i = 0; i < MigrationQueue.size(); i++)
			{
				std::string a = PLAYER::GET_PLAYER_NAME(MigrationQueue.at(i).second);
				g_UiManager->HostMigrationText(a);
			}
		}*/
	}

	void NetworkUpdateYuhsObeseStatus()
	{
		Peepe(yuhisfat);
		//DropRP(dropthemrpmyg);

		if (g_AngryPlanesEnable)
			g_angry_planes.tick();
			

		//BlockChat(g_BlockChat);

		if (g_CloneProtections)
			CloneProtections();
	}
	
	void FindSession(int sessiontype)
	{
		int join;
		switch (sessiontype)
		{
		case 1:
			join = 0;
			break;
		case 2:
			join = 1;
			break;
		case 3:
			join = 10;
			break;
		case 4:
			join = 11;
			break;
		case 5:
			join = 9;
			break;
		case 6:
			join = 6;
			break;
		case 7:
			join = 12;
			break;
		case 8:
			join = 2;
			break;
		}

		g_FiberScript->addTask([=] {
			if (globalHandle(1574589).As<int>() == -1)
			{
				globalHandle(1574589).At(2).As<int>() = -1;
				globalHandle(1574589).As<int>() = 1;
				g_FiberScript->Wait(0);
				globalHandle(1574589).As<int>() = join;
				globalHandle(1574589).As<int>() = 0;
			}
			else
			{
				globalHandle(1575015).As<int>() = join;
				globalHandle(1574589).As<int>() = 1;
				g_FiberScript->Wait(0);
				globalHandle(1574589).As<int>() = 0;
			}
			});
	}

	void erase(std::vector<int>& myNumbers_in, int number_in)
	{
		std::vector<int>::iterator iter = myNumbers_in.begin();
		std::vector<int>::iterator endIter = myNumbers_in.end();
		for (; iter != endIter; ++iter)
		{
			if (*iter == number_in)
			{
				myNumbers_in.erase(iter);
			}
		}
	}

	void DropRP(bool toggle, std::int32_t ped)
	{
		if (toggle)
		{
			if (std::find(g_Players.RPDrop.begin(), g_Players.RPDrop.end(), ped) != g_Players.RPDrop.end()) {}
			else g_Players.RPDrop.push_back(ped);
		}
		else
		{
			if (std::find(g_Players.RPDrop.begin(), g_Players.RPDrop.end(), ped) != g_Players.RPDrop.end()) { erase(g_Players.RPDrop, g_Players.PlayerIndex[g_SelectedPlayer]); }
		}
	}

	void PackedStatBoolResearch(int index)
	{
		if (index >= 15369 && index < 15561)
		{
			int character;
			STATS::STAT_GET_INT(Joaat("mpply_last_mp_char"), &character, -1);
			int hash = STATS::_GET_NGSTAT_BOOL_HASH((index - 15369), 0, 1, character, "_DLCGUNPSTAT_BOOL");
			int mask = ((index - 15369) - STATS::_0xF4D8E7AC2A27758C((index - 15369)) * 64);
			STATS::STAT_SET_BOOL_MASKED(hash, 1, mask, 1);
		}
	}

	void PackedStatBoolCasinoHeistOutfits(int index)
	{
		if (index >= 28098 && index < 28354) {
			int character;
			STATS::STAT_GET_INT(Joaat("mpply_last_mp_char"), &character, -1);
			int hash = STATS::_GET_NGSTAT_BOOL_HASH((index - 28098), 0, 1, character, "_CASINOHSTPSTAT_BOOL");
			int mask = ((index - 28098) - STATS::_0xF4D8E7AC2A27758C((index - 28098)) * 64);
			STATS::STAT_SET_BOOL_MASKED(hash, 1, mask, 1);
		}
	}

	void PackedStatBoolArenaWar(int index) {
		if (index >= 24962 && index < 25538) {
			int character;
			STATS::STAT_GET_INT(Joaat("mpply_last_mp_char"), &character, -1);
			int hash = STATS::_GET_NGSTAT_BOOL_HASH((index - 24962), 0, 1, character, "_ARENAWARSPSTAT_BOOL");
			int mask = ((index - 24962) - STATS::_0xF4D8E7AC2A27758C((index - 24962)) * 64);
			STATS::STAT_SET_BOOL_MASKED(hash, 1, mask, 1);
		}
	}

	void IncreaseStamina()
	{
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 0);
	}

	void IncreaseStrength()
	{
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 0);
	}

	void InceaseLoungh()
	{
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 0);
	}

	void IncreaseDriving()
	{
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 0);
	}

	void IncreaseFly()
	{
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 0);
	}

	void IncreaseShooting()
	{
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 0);
	}

	void IncreaseStealth()
	{
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 0);
	}

	void UnlimitedSnacks()
	{
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 999999999, 1);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), 999999999, 1);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), 999999999, 1);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), 999999999, 1);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), 999999999, 1);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_NO_BOUGHT_YUM_SNACKS"), 999999999, 1);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_NO_BOUGHT_HEALTH_SNACKS"), 999999999, 1);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_NO_BOUGHT_EPIC_SNACKS"), 999999999, 1);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_NUMBER_OF_ORANGE_BOUGHT"), 999999999, 1);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CIGARETTES_BOUGHT"), 999999999, 1);
	}

	void RedesignCharacter()
	{
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_FM_CHANGECHAR_ASKED"), 0, 1);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_FM_CHANGECHAR_ASKED"), 0, 1);
	}

	void NightClubPopularity()
	{
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CLUB_POPULARITY"), 1000, 0);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_CLUB_POPULARITY"), 1000, 0);
	}

	void DamagePlayer()
	{
		if (!NETWORK::NETWORK_IS_IN_SESSION())
		{
			notifyMap(12, "Get up your fat ass and join a session!");
		}
		else
		{
			if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0))
			{
				NativeVector3 rndm = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 1);
				FIRE::ADD_EXPLOSION(rndm.x, rndm.y, rndm.z, 3, 5, 0, 1, 0, 0);
			}
			else
			{
				notifyMap(12, "You can't Damage the targetted player reason: Player is in Vehicle!");
			}
		}
	}

	void NetworkDesyncKick()
	{
		if (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) != PLAYER::PLAYER_ID()) {
			ForceHostOfScript();
		}

		auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
		auto player = (CNetGamePlayers*)g_GameFunctions->m_GetNetPlayer(g_SelectedPlayer);
		if (g_GameFunctions->m_NetworkPlayerManager && *g_GameFunctions->m_NetworkPlayerManager && ENTITY::DOES_ENTITY_EXIST(ped), g_GameFunctions->m_GetNetPlayer(g_SelectedPlayer))
		{
			(*g_GameFunctions->m_NetworkPlayerManager)->RemovePlayer(player);
			WEAPON::REMOVE_ALL_PED_WEAPONS(ped, TRUE);
		}
	}

	void NetworkKillPlayer()
	{
		NativeVector3 GetPlayerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(g_SelectedPlayer), true);
		FIRE::ADD_EXPLOSION(GetPlayerCoords.x, GetPlayerCoords.y, GetPlayerCoords.z, 18, 2, 0, 1, 0, false);
	}

	void NetworkExplodePlayer() 
	{
		NativeVector3 GetPlayerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(g_SelectedPlayer), true);
		FIRE::ADD_EXPLOSION(GetPlayerCoords.x, GetPlayerCoords.y, GetPlayerCoords.z, 29, 20, true, false, 0, false);
		PED::EXPLODE_PED_HEAD(PLAYER::GET_PLAYER_PED(g_SelectedPlayer), 0x145F1012);
	}
	Ped spawn_ped(Hash hash, NativeVector3 coords, float heading) {
		g_CallbackScript->AddCallback<ModelCallback>(hash, [=] {
			int l_nNetworkId = NETWORK::PED_TO_NET(PED::CREATE_PED(4, hash, coords.x, coords.y, coords.z, heading, TRUE, FALSE));
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(l_nNetworkId, TRUE);
			if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(NETWORK::NET_TO_PED(l_nNetworkId)))
				return NETWORK::NET_TO_PED(l_nNetworkId);
		});
		//g_Logger->Info("Fuck");
		return NULL;
	}

	void CloneCrash()
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		NativeVector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0f, 0.0f, 0.0f);
		Ped target_ped = spawn_ped(MISC::GET_HASH_KEY("s_m_m_movalien_01"), coords, 0.0f);
		/*if (ENTITY::DOES_ENTITY_EXIST(target_ped)) {
			uint64_t target_entity = g_GameFunctions->m_GetEntityFromScriptGuild(target_ped);
			if (target_entity) {
				clone_crash_entity[g_SelectedPlayer] = target_entity;
				do_clone_crash[g_SelectedPlayer] = true;
			}
		}*/
	}

	bool Command(std::string& str, std::string check)
	{
		std::size_t found = str.find_first_of(' ');
		if (found != std::string::npos)
		{
			if (str.substr(0, found) == check)
			{
				str = str.substr(found + 1, str.size());
				return true;
			}
		}
		else
		{
			if (str == check)
				return true;
		}
		return false;
	}

	void SpawnVehicleCommandFunction(const char* toSpawn, std::int32_t player) {
		Hash model = MISC::GET_HASH_KEY(toSpawn);
		g_CallbackScript->AddCallback<ModelCallback>((model), [=] {

			NativeVector3 s_coords = ENTITY::GET_ENTITY_COORDS(player, true);
			Vehicle _veh = VEHICLE::CREATE_VEHICLE(model, s_coords.x + 2.f, s_coords.y, s_coords.z, ENTITY::GET_ENTITY_HEADING(player), true, true, true);
			//DECORATOR::DECOR_SET_INT(_veh, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(player));
			DECORATOR::DECOR_SET_INT(_veh, "MPBitset", 0);
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(_veh);
			VEHICLE::SET_VEHICLE_ENGINE_ON(_veh, true, true, true);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(_veh, 0);

		});
	}

	void moneyDrop(bool enable, int amount, int delay, int xPlus, int yPlus, int zPlus, int Height)
	{
		if (enable)
		{
			Ped playerped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
			if (!ENTITY::DOES_ENTITY_EXIST(playerped)) return;
			if ((timeGetTime() - t) > delay)
			{
				g_CallbackScript->AddCallback<ModelCallback>(-1666779307, [=] {
					NativeVector3 playerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0);
					OBJECT::CREATE_AMBIENT_PICKUP(1704231442, playerPosition.x + xPlus, playerPosition.y + yPlus, playerPosition.z + zPlus, Height, amount, -1666779307, FALSE, TRUE);
				});
				t = timeGetTime();
			}

		}
	}

	atArrayBig<GtaThread*>* gta_threads;
	GtaThread* FindThread(uint32_t hash)
	{
		for (auto thread : *g_GameFunctions->gta_threads)
			if (thread && thread->m_context.ThreadID && thread->m_handler && thread->m_script_hash == hash)
				return thread;
		return nullptr;
	}

	void ForceHostOfScript()
	{
		g_Logger->Info("Searching for thread...");
		if (const auto script_thread = FindThread(0xC875557D)) {
			g_Logger->Info("Patching token...");
			g_GameFunctions->small_host_token_patch = true;
			g_Logger->Info("Getting player...");
			auto* const net_player = reinterpret_cast<CNetGamePlayers*>(g_GameFunctions->m_GetHostOfScript(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_PED_ID())));
			g_Logger->Info("Forcing host...");
			g_GameFunctions->m_ForceHostOfScript(script_thread->m_net_component, net_player);
			g_Logger->Info("Done");
		}

	}

	void CloneProtections()
	{
		if (!CUTSCENE::IS_CUTSCENE_ACTIVE() && !CUTSCENE::IS_CUTSCENE_PLAYING() && !STREAMING::IS_NETWORK_LOADING_SCENE()
			&& !NETWORK::NETWORK_IS_IN_MP_CUTSCENE() && !INTERIOR::IS_INTERIOR_SCENE())
		{
			Ped Closest;
			NativeVector3 MyPos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			if (PED::GET_CLOSEST_PED(MyPos.x, MyPos.y, MyPos.z, 5, true, true, &Closest, false, true, -1))
			{
				if (ENTITY::GET_ENTITY_MODEL(Closest) == ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()))
				{
					if (!PED::IS_PED_A_PLAYER(Closest))
					{
						if (ENTITY::DOES_ENTITY_EXIST(Closest))
						{
							if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Closest))
							{
								if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Closest))
								{
									RequestControlOfid(Closest);
									RequestControlOfEnt(Closest);
									ENTITY::SET_ENTITY_COLLISION(Closest, 0, 0);
									ENTITY::SET_ENTITY_COORDS(Closest, 999999, 999999, 999999, 0, 0, 0, 1);
									ENTITY::_SET_ENTITY_SOMETHING(Closest, true);
									ENTITY::SET_ENTITY_HEALTH(Closest, -1);
									ENTITY::SET_ENTITY_ALPHA(Closest, 0, 1);
									MISC::CLEAR_AREA_OF_PEDS(MyPos.x, MyPos.y, MyPos.z, 3.f, 1);
									notifyMap(27, "Type: Cloning\nStatus: Blocked");
								}
							}
						}
					}
				}
			}
		}
	}

	void DropMgr()
	{
		if (g_Drops.size() <= 0)
			return;

		for (int i = 0; i < g_Drops.size(); ++i)
		{
			NativeVector3 coords = { g_Drops[i].x, g_Drops[i].y, g_Drops[i].z };
			if (g_Drops[i].Activated)
			{
				g_CallbackScript->AddCallback<ModelCallback>(g_Drops[i].PickupHash, [=] {
					if ((GetTickCount() - g_Drops[i].Timer >= g_Drops[i].Delay))
					{
						OBJECT::CREATE_AMBIENT_PICKUP(1704231442, coords.x, coords.y, coords.z + 1.3f, 0, g_Drops[i].Amount, g_Drops[i].PickupHash, true, false);
						g_Drops[i].Timer = GetTickCount();
					}
				});
			}
		}
	}

	void BlockChat(bool toggle)
	{

	}

	float distanceBetween(NativeVector3 A, NativeVector3 B) 
	{
		return MISC::GET_DISTANCE_BETWEEN_COORDS(A.x, A.y, A.z, B.x, B.y, B.z, 1);
	}

	bool is_ped_aiming(Ped ped)
	{
		return PED::GET_PED_CONFIG_FLAG(ped, 78, true);
	}

	Entity get_raycast_entity()
	{
		NativeVector3 cam_coord = CAM::GET_GAMEPLAY_CAM_COORD();
		NativeVector3 cam_rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
		NativeVector3 cam_dir = g_Utility->RotationToDirectionV3(cam_rot);
		static Entity entity;

		static float start_x, start_y, start_z, end_x, end_y, end_z;
		static int hit;
		static int ent;

		start_x = cam_coord.x + cam_dir.x;
		start_y = cam_coord.y + cam_dir.y;
		start_z = cam_coord.z + cam_dir.z;

		end_x = cam_coord.x + (cam_dir.x * 0x800);
		end_y = cam_coord.y + (cam_dir.y * 0x800);
		end_z = cam_coord.z + (cam_dir.z * 0x800);

		int handle = SHAPETEST::_START_SHAPE_TEST_RAY(start_x, start_y, start_z, end_x, end_y, end_z, -1, 0, true);

		NativeVector3 end_coords = NativeVector3(end_x, end_y, end_z);
		NativeVector3 surface_normal = NativeVector3(start_x, start_y, start_z);

		SHAPETEST::GET_SHAPE_TEST_RESULT(handle, &hit, &end_coords, &surface_normal, &entity);

		if (entity == NULL)
			return 0;
		if (!ENTITY::DOES_ENTITY_EXIST(entity))
			return 0;

		return entity;
	}

	bool is_player_in_interior(Player player)
	{
		auto player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		bool interior = INTERIOR::GET_INTERIOR_FROM_ENTITY(player_ped);

		return INTERIOR::IS_VALID_INTERIOR(interior);
	}

	bool is_player_friend(Player player)
	{
		int handle[13];
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &handle[0], 13);

		if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle[0], 13))
			return NETWORK::NETWORK_IS_FRIEND(&handle[0]);

		return NULL;
	}

	float random_float_in_range(float start, float end)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(start, end);

		return static_cast<float>(dist(mt));
	}

	int random_number_in_range(int start, int end)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(start, end);

		return static_cast<int>(dist(mt));
	}

	void angry_planes::tick()
	{
		initialize_variables(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), 0), -1275859404);
		spawn_planes();
	}

	void angry_planes::initialize_variables(Ped ped, NativeVector3 coords, uint32_t enemy_hash)
	{
		this->player_ped = ped;
		this->player_coords = coords;
		this->enemy_hash = enemy_hash;

		if (this->player_ped)
			this->initialized = true;
	}

	Ped angry_planes::create_enemy(uint32_t hash, NativeVector3 coords)
	{
		if (this->initialized)
		{
			if (STREAMING::IS_MODEL_VALID(hash) && STREAMING::IS_MODEL_IN_CDIMAGE(hash))
			{
				STREAMING::REQUEST_MODEL(hash);
				if (STREAMING::HAS_MODEL_LOADED(hash))
				{
					auto ped = PED::CREATE_PED(26, this->enemy_hash, coords.x, coords.y, coords.z, 0, TRUE, TRUE);
					PED::SET_PED_AS_ENEMY(ped, TRUE);
					PED::SET_PED_COMBAT_ATTRIBUTES(ped, 1, TRUE);
					PED::SET_PED_COMBAT_ATTRIBUTES(ped, 46, TRUE);
					PED::SET_PED_COMBAT_ATTRIBUTES(ped, 16, TRUE);
					PED::SET_PED_COMBAT_ABILITY(ped, 2);
					PED::SET_PED_FLEE_ATTRIBUTES(ped, 0, FALSE);

					return ped;
				}
				else
				{
					STREAMING::REQUEST_MODEL(hash);
				}
			}
		}

		return 0;
	}

	Vehicle angry_planes::spawn_plane(uint32_t hash)
	{
		if (this->initialized)
		{
			if (STREAMING::IS_MODEL_VALID(hash) && STREAMING::IS_MODEL_IN_CDIMAGE(hash))
			{
				if (VEHICLE::IS_THIS_MODEL_A_PLANE(hash))
				{
					STREAMING::REQUEST_MODEL(hash);
					if (STREAMING::HAS_MODEL_LOADED(hash))
					{
						NativeVector3 coords;
						coords.x = this->player_coords.x + random_float_in_range(-this->spawn_range, this->spawn_range);
						coords.y = this->player_coords.y + random_float_in_range(-this->spawn_range, this->spawn_range);
						coords.z = this->player_coords.z + 150.f;

						if (auto enemy = this->create_enemy(this->enemy_hash, coords))
						{
							auto heading = ENTITY::GET_ENTITY_HEADING(this->player_ped);
							auto veh = VEHICLE::CREATE_VEHICLE(hash, coords.x, coords.y, coords.z, heading, TRUE, TRUE, 0);
							if (veh)
							{
								VEHICLE::SET_VEHICLE_ENGINE_ON(veh, TRUE, TRUE, FALSE);
								VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(veh, TRUE);
								PED::SET_PED_INTO_VEHICLE(enemy, veh, -1);
								ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0, 10.5f, 0., 0, 0, 0, true, true, true, true, false, true);
								ENTITY::SET_ENTITY_HEADING(veh, 45.f);
								BRAIN::TASK_PLANE_MISSION(enemy, veh,
									PED::IS_PED_IN_ANY_VEHICLE(this->player_ped, TRUE) ? PED::GET_VEHICLE_PED_IS_USING(this->player_ped) : 0, this->player_ped,
									this->player_coords.x, this->player_coords.y, this->player_coords.z,
									4, 20.f, -1, -1, 0, 100, 0);

								if (g_AngryPlanesRockets)
								{
									BRAIN::TASK_SHOOT_AT_ENTITY(enemy, this->player_ped, 2000, MISC::GET_HASH_KEY("FIRING_PATTERN_FULL_AUTO"));
									BRAIN::TASK_COMBAT_PED(enemy, this->player_ped, 0, 16);
								}

								plane str;
								str.ped = enemy;
								str.id = veh;
								this->m_spawned_planes.push_back(str);
							}

							return veh;
						}
					}
					else
					{
						STREAMING::REQUEST_MODEL(hash);
					}
				}
			}
		}

		return 0;
	}

	void angry_planes::check_for_alive_planes()
	{
		int d = 0;

		for (auto i : this->m_spawned_planes)
		{
			if (!ENTITY::DOES_ENTITY_EXIST(i.ped) ||
				!ENTITY::DOES_ENTITY_EXIST(i.id) ||
				ENTITY::GET_ENTITY_HEALTH(i.ped) == 0 ||
				ENTITY::GET_ENTITY_HEALTH(i.id) == 0)
			{
				this->m_spawned_planes.erase(this->m_spawned_planes.begin() + d);
			}

			d++;
		}
	}

	void angry_planes::spawn_planes()
	{
		this->check_for_alive_planes();

		if (m_spawned_planes.size() != this->max_planes_to_spawn)
		{
			auto rand = random_number_in_range(0, (int)this->m_plane_hashes.size());
			this->spawn_plane(this->m_plane_hashes[rand]);
		}
	}

	void angry_planes::cleanup()
	{
		for (auto& i : m_spawned_planes)
		{
			if (ENTITY::DOES_ENTITY_EXIST(i.ped))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(i.ped);
				BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(i.ped);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(i.ped, 1, 1);
				ENTITY::DELETE_ENTITY(&i.ped);
			}
		}
		for (auto& i : m_spawned_planes)
		{
			if (ENTITY::DOES_ENTITY_EXIST(i.id))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(i.id);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(i.id, 1, 1);
				ENTITY::DELETE_ENTITY(&i.id);
			}
		}
		m_spawned_planes.resize(0);
	}


	void shittycrash()
	{
		/*
		7FF6E24E7970

        7FF6DFBA0000

        2947970
		*/
		g_Logger->Info("a");
		static uintptr_t ModuleBaseAdress__ = (uintptr_t)GetModuleHandle(NULL);
		std::uintptr_t GTA_NETWORK_OBJECT_MGR_INTERFACE = (ModuleBaseAdress__ + 0x2947970);

		std::uintptr_t GTA_GET_ENTITY_FROM_SCRIPT_GUID = (ModuleBaseAdress__ + 0x2B4740);

		g_Logger->Info("b");
		std::int32_t player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
		g_Logger->Info("c");
		if (ENTITY::DOES_ENTITY_EXIST(player_ped))
		{
			g_Logger->Info("d");
			std::int32_t decoy_ped = spawn_ped(MISC::GET_HASH_KEY("s_m_m_movalien_01"), ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player_ped, 0.0f, 0.0f, 0.0f), ENTITY::GET_ENTITY_HEADING(player_ped));
			g_Logger->Info("e");
			std::uint64_t player_entity = (((std::uint64_t(*)(std::int32_t))GTA_GET_ENTITY_FROM_SCRIPT_GUID), player_ped);
			g_Logger->Info("f");
			g_Logger->Info(std::to_string(player_entity).c_str());
			if (player_entity)
			{
				g_Logger->Info("g");
				std::uint64_t player_net_obj = *(std::uint64_t*)(player_entity + 0xD0);
				g_Logger->Info("h");
				if (player_net_obj)
				{
					g_Logger->Info("i");
					auto net_game_player = (CNetGamePlayers*)g_GameFunctions->m_GetNetPlayer(g_SelectedPlayer);
					g_Logger->Info("j");
					if (net_game_player)
					{
						g_Logger->Info("k");
						std::uint64_t decoy_entity = (((std::uint64_t(*)(std::int32_t))GTA_GET_ENTITY_FROM_SCRIPT_GUID), decoy_ped);
						g_Logger->Info("l");
						if (decoy_entity)
						{
							g_Logger->Info("m");
							std::uint64_t decoy_net_obj = *(std::uint64_t*)(decoy_entity + 0xD0);
							g_Logger->Info("n");
							if (decoy_net_obj)
							{
								g_Logger->Info("o");
								// get ptr to net id
								std::uint16_t* decoy_net_id = (std::uint16_t*)(decoy_net_obj + 0xA);
								g_Logger->Info("p");
								// cache
								std::uint16_t cached_decoy_net_id = *decoy_net_id;
								g_Logger->Info("q");
								// spoof to player's net id
								*decoy_net_id = *(std::uint16_t*)(player_net_obj + 0xA);
								g_Logger->Info("r");
								// pack remove
								g_GameFunctions->m_PackCloneRemove(GTA_NETWORK_OBJECT_MGR_INTERFACE, player_net_obj, *(std::uint64_t*)net_game_player, true);
								g_Logger->Info("s");
								// restore
								*decoy_net_id = cached_decoy_net_id;
								g_Logger->Info("t");
								g_Logger->Info("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO CRASHO???");
							}
						}
					}
				}
			}
		}
	}
}

