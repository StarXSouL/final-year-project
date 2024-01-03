#include "Common.hpp"
#include "Types.hpp"
#include "ScriptCallback.hpp"
using namespace Big::UserInterface;


namespace Big
{

	void RVC(bool toggle)
	{
		if (toggle)
		{
			g_Collision = false;
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false);
		}
		else
		{
			static bool fuck;
			fuck = true;
			if (fuck)
			{
				g_Collision = true;
			}
			fuck = false;
		}

	}

	void Hornboost(bool toggle)
	{
		if (toggle && PAD::IS_CONTROL_PRESSED(2, 86)) //INPUT_VEH_HORN
		{
			std::int32_t l_vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			std::float_t s_VehicleSpeed = ENTITY::GET_ENTITY_SPEED(l_vehicle);

			if (!ENTITY::DOES_ENTITY_EXIST(l_vehicle)) return;

			if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(l_vehicle) != 0) {
				NETWORK::SET_NETWORK_ID_CAN_MIGRATE(l_vehicle, true);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(l_vehicle);
			}

			if (m_AudioBoost)
			{
				AUDIO::SET_VEHICLE_BOOST_ACTIVE(l_vehicle, true);
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(l_vehicle, s_VehicleSpeed + m_SpeedBoost);
				AUDIO::SET_VEHICLE_BOOST_ACTIVE(l_vehicle, false);
			}
			else
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(l_vehicle, s_VehicleSpeed + m_SpeedBoost);
			}

			if (m_BoostEffect)
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("RaceTurboLight");
			}

		}
	}

	void VehicleFly(bool toggle, float speed)
	{
		if (toggle)
		{
			if (PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) != NULL) {
				std::int32_t l_vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

				VEHICLE::SET_VEHICLE_GRAVITY(l_vehicle, false);

				NativeVector3 GCR = CAM::GET_GAMEPLAY_CAM_ROT(2);
				ENTITY::SET_ENTITY_ROTATION(l_vehicle, GCR.x, GCR.y, GCR.z, 2, 1);

				if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 87)) //INPUT_VEH_FLY_THROTTLE_UP
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(l_vehicle, speed);
				}
				else
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(l_vehicle, 0.0f);
				}
			}

		}
	}

	void AutoFlip(bool toggle)
	{
		if (toggle)
		{
			std::int32_t l_vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			float l_roll = ENTITY::GET_ENTITY_ROLL(l_vehicle);
			if (ENTITY::IS_ENTITY_UPSIDEDOWN(l_vehicle) && (l_roll > 160 || l_roll < -160)) {
				if (!ENTITY::IS_ENTITY_IN_AIR(l_vehicle) && !ENTITY::IS_ENTITY_IN_WATER(l_vehicle) && !VEHICLE::IS_THIS_MODEL_A_PLANE(l_vehicle) && !VEHICLE::IS_THIS_MODEL_A_HELI(l_vehicle)) {
					RequestControlOfEnt(l_vehicle);
					ENTITY::SET_ENTITY_ROTATION(l_vehicle, 0, 0, ENTITY::GET_ENTITY_ROTATION(l_vehicle, 2).z, 2, 1);
				}
			}
		}
	}

	void Autofix()
	{
		if (g_Autofix)
		{
			if (VEHICLE::_IS_VEHICLE_DAMAGED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)))
			{
				VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
			}
			VEHICLE::SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
		}
	}

	void Seatbelt(bool toggle)
	{
		if (toggle)
		{
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 1);
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, false);
		}
	}

	void Driftmode(bool toggle)
	{
		if (toggle)
		{
			if (GetAsyncKeyState(VK_SPACE))
				VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
			else
				VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
		}
	}

	void VehicleInvincible(bool toggle)
	{
		if (toggle)
		{
			VEHICLE::SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
			ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
		}
	}

	void CustomWheelPTFX(const char* streamName, const char* PTFXName, const char* wheel)
	{
		
		int myVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		STREAMING::REQUEST_NAMED_PTFX_ASSET(streamName);
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(streamName))
		{
			NativeVector3 pos2 = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, wheel));
			GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(streamName);
			GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(PTFXName, pos2.x, pos2.y, pos2.z, 0.f, 0.f, 0.f, m_GlowScale0, false, false, false);
		}
		else STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
	}

	void GlowManager0(bool toggle)
	{
		if (toggle)
		{
			if (m_RightFrontWheel) { CustomWheelPTFX(m_ParticleCalls00[m_ParticleIterator0], m_ParticleCalls10[m_ParticleIterator0], "wheel_rf"); }
			if (m_LeftFrontWheel) { CustomWheelPTFX(m_ParticleCalls00[m_ParticleIterator0], m_ParticleCalls10[m_ParticleIterator0], "wheel_lf"); }
			if (m_RightBackWheel) { CustomWheelPTFX(m_ParticleCalls00[m_ParticleIterator0], m_ParticleCalls10[m_ParticleIterator0], "wheel_rr"); }
			if (m_LeftBackWheel) { CustomWheelPTFX(m_ParticleCalls00[m_ParticleIterator0], m_ParticleCalls10[m_ParticleIterator0], "wheel_lr"); }
		}
	}

	void VehicleRockets(bool toggle, std::uint32_t Model, float Speed, bool lazersight, std::int32_t vehicle)
	{
		static DWORD ShootTime = 0;
		if (toggle)
		{
			Player player = PLAYER::PLAYER_ID();
			Ped playerPed = PLAYER::PLAYER_PED_ID();

			std::int32_t veh = vehicle;
			NativeVector3 v0, v1;

			NativeVector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
			NativeVector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
			NativeVector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
			NativeVector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

			if (lazersight)
			{
				GRAPHICS::DRAW_LINE(coords0from.x, coords0from.y, coords0from.z, coords0to.x, coords0to.y, coords0to.z, g_UiManager->m_OptionSelectedBackgroundColor.r, g_UiManager->m_OptionSelectedBackgroundColor.g, g_UiManager->m_OptionSelectedBackgroundColor.b, 255);
				GRAPHICS::DRAW_LINE(coords1from.x, coords1from.y, coords1from.z, coords1to.x, coords1to.y, coords1to.z, g_UiManager->m_OptionSelectedBackgroundColor.r, g_UiManager->m_OptionSelectedBackgroundColor.g, g_UiManager->m_OptionSelectedBackgroundColor.b, 255);
			}

			bool bSelect = IsKeyPressed(VK_CONTROL);
			if (bSelect && ShootTime + g_WeaponDelay < GetTickCount() && PLAYER::IS_PLAYER_CONTROL_ON(player))
			{

				MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

				if (!WEAPON::HAS_WEAPON_ASSET_LOADED(Model)) {}

				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z, coords0to.x, coords0to.y, coords0to.z, Speed, 1, Model, playerPed, 1, 0, -1.0);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z, coords1to.x, coords1to.y, coords1to.z, Speed, 1, Model, playerPed, 1, 0, -1.0);

				ShootTime = GetTickCount();
			}
		}
	}

	void DuplicateVehicle(std::int32_t player)
	{
		globalHandle(4533757).As<bool>() = 1;
		Hash model = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(player, false));

		if (STREAMING::IS_MODEL_VALID(model)) {

			const char* vehname = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
			const char* name_veh = HUD::_GET_LABEL_TEXT(vehname);


			STREAMING::REQUEST_MODEL(model);
			NativeVector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			float forward = 5;
			float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());

			Vehicle car = PED::GET_VEHICLE_PED_IS_IN(player, 0);
			float _Speed = ENTITY::GET_ENTITY_SPEED(car);

			int r;
			int g;
			int b;

			int sr;
			int sg;
			int sb;

			VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(player, false), &r, &g, &b);
			VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(player, false), &sr, &sg, &sb);

			int spoiler = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 0);
			int fbumper = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 1);
			int rbumper = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 2);
			int sideskirt = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 3);
			int exhaust = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 4);
			int frame = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 5);
			int grille = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 6);
			int hood = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 7);
			int fender = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 8);
			int rfender = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 9);
			int roof = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 10);
			int engine = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 11);
			int brakes = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 12);
			int transmission = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 13);
			int horns = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 14);
			int suspension = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 15);
			int armor = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 16);
			int fwheels = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 23);
			int rwheels = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 24);
			int plateholder = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 25);
			int trimdesign = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 27);
			int ornaments = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 28);
			int dialdesign = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 30);
			int steeringwheel = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 33);
			int shifterleavers = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 34);
			int plaques = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 35);
			int hydraulics = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 38);
			int livery = VEHICLE::GET_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_IN(player, false), 48);

			g_CallbackScript->AddCallback<ModelCallback>(model, [model, heading, _Speed, ourCoords, forward, r, g, b, sr, sg, sb, spoiler, fbumper, rbumper, sideskirt, exhaust, frame, grille, hood, fender, rfender, roof, engine, brakes, transmission, horns, suspension, armor, fwheels, rwheels,
				plateholder, trimdesign, ornaments, dialdesign, steeringwheel, shifterleavers, plaques, hydraulics, livery, player] {
					if (STREAMING::HAS_MODEL_LOADED(model))
					{
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
						Vehicle veh = VEHICLE::CREATE_VEHICLE(model, ourCoords.x, ourCoords.y + forward, ourCoords.z, heading, true, true, 1);

						VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, true);
						VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 1);
						if (player == PLAYER::PLAYER_PED_ID())
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, _Speed);
						DECORATOR::DECOR_SET_INT(veh, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(PLAYER::PLAYER_ID()));
						DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
						VEHICLE::SET_VEHICLE_IS_STOLEN(veh, false);
						AUDIO::SET_RADIO_TO_STATION_INDEX(0);
						ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(veh));

						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, r, g, b);
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, sr, sg, sb);

						VEHICLE::SET_VEHICLE_MOD(veh, 0, spoiler, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 1, fbumper, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 2, rbumper, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 3, sideskirt, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 4, exhaust, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 5, frame, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 6, grille, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 7, hood, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 8, fender, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 9, rfender, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 10, roof, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 11, engine, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 12, brakes, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 13, transmission, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 14, horns, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 15, suspension, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 16, armor, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 23, fwheels, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 24, rwheels, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 25, plateholder, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 27, trimdesign, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 28, ornaments, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 30, dialdesign, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 33, steeringwheel, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 34, shifterleavers, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 35, plaques, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 38, hydraulics, false);
						VEHICLE::SET_VEHICLE_MOD(veh, 48, livery, false);
					}
				});
		}
	}

	void MaxVehicle()
	{
		VEHICLE::SET_VEHICLE_MOD_KIT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		for (int i = 0; i < 50; i++) { VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false); }
		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 2);
	}

	void vehicle_acrobatics(int type)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true))
		{
			switch (type)
			{
			case 0:
				ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1, 0.f, 0.f, 7.0f, 0.f, 0.f, 0.f, 0, true, true, true, false, false); //bunny hop
				break;
			case 1:
				ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1, 0.f, 0.f, 10.0f, -7.f, 0.f, 0.f, 0, true, true, true, false, false); //kickflip
				break;
			case 2:
				ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1, 0.f, 0.f, 13.0f, 0.f, -6.f, 0.f, 0, true, true, true, false, false); //frontflip
				break;
			case 3:
				ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 1, 0.f, 0.f, 13.0f, 0.f, 6.f, 0.f, 0, true, true, true, false, false); //backflip
				break;
			}
		}
	}

	void VehicleRamp(bool front, bool back, bool left, bool right)
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		Hash ramp = MISC::GET_HASH_KEY("lts_prop_lts_ramp_01");
		g_CallbackScript->AddCallback<ModelCallback>(ramp, [=] {
			if (ENTITY::DOES_ENTITY_EXIST(veh))
			{
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(veh);

				if (front)
				{
					std::int32_t Object = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, veh, 0, 0, 5, 0.3f, 0, 0, 180, 0, 0, 0, 0, 2, 1);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
					}
				}

				if (back)
				{
					std::int32_t Object = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, veh, 0, 0, -5, 0.3f, 0, 0, 360, 0, 0, 0, 0, 2, 1);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
					}
				}

				if (left)
				{
					std::int32_t Object = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, veh, 0, -5, 0, 0.3f, 0, 0, -90, 0, 0, 0, 0, 2, 1);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
					}
				}

				if (right)
				{
					std::int32_t Object = OBJECT::CREATE_OBJECT(ramp, 0.f, 0.f, 0.f, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(Object))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Object, veh, 0, 5, 0, 0.3f, 0, 0, 90, 0, 0, 0, 0, 2, 1);
						ENTITY::SET_ENTITY_COLLISION(Object, 1, 0);
					}
				}

			}
		});
	}

	void DisplayVehicle(std::string texture1, std::string texture2)
	{
		float VehBannerWidth = 0.13f;
		float VehBannerHeight = 0.045f;
		RGBA line{ 255, 255, 255, 255 };
		float lineX = { g_UiManager->m_PosX - 0.19f };
		float lineY = 0.2451f;

		g_UiManager->Spriter(texture1, texture2, g_UiManager->m_PosX + 0.19f, 0.1795f, 0.13f, 0.13f, 0, 255, 255, 255, 255);
	}

	void SpawnVehicle(uint32_t model)
	{
		*script_global(4540731).as<bool*>() = 1;
		std::uint32_t l_CurrentVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		std::float_t _heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		g_CallbackScript->AddCallback<ModelCallback>((model), [=] {
			NativeVector3 s_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			std::float_t s_VehicleSpeed = ENTITY::GET_ENTITY_SPEED(l_CurrentVehicle);
			Vehicle _veh = VEHICLE::CREATE_VEHICLE(model, s_coords.x + 2.f, s_coords.y, s_coords.z, _heading, true, true, true);
			const char* vehname = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model));
			DECORATOR::DECOR_SET_INT(_veh, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(PLAYER::PLAYER_ID()));
			DECORATOR::DECOR_SET_INT(_veh, "MPBitset", 0);
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(_veh);
			VEHICLE::SET_VEHICLE_ENGINE_ON(_veh, true, true, true);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(_veh, 0);

			if (g_SpawnInVeh) {
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), _veh, -1);
			}

			if (g_SpawnInvinc) {
				ENTITY::SET_ENTITY_INVINCIBLE(_veh, true);
			}
			
			if (g_SpawnMaxed) {
				VEHICLE::SET_VEHICLE_MOD_KIT(_veh, 0);
				for (int i = 0; i < 50; i++) { VEHICLE::SET_VEHICLE_MOD(_veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(_veh, i) - 1, false); }
				VEHICLE::SET_VEHICLE_WINDOW_TINT(_veh, 2);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(_veh, "OverKill");
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(_veh, 1);
			}

			VEHICLE::SET_VEHICLE_FORWARD_SPEED(_veh, s_VehicleSpeed);
		});
	}

	void SpawnVehicle2(uint32_t model)
	{
		std::uint32_t l_CurrentVehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		std::float_t _heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		g_CallbackScript->AddCallback<ModelCallback>((model), [=] {
			NativeVector3 s_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer), true);
			Vehicle _veh = VEHICLE::CREATE_VEHICLE(model, s_coords.x + 2.f, s_coords.y, s_coords.z, _heading, true, true, true);
			const char* vehname = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model));
			DECORATOR::DECOR_SET_INT(_veh, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(PLAYER::PLAYER_ID()));
			DECORATOR::DECOR_SET_INT(_veh, "MPBitset", 0);
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(_veh);
			VEHICLE::SET_VEHICLE_ENGINE_ON(_veh, true, true, true);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(_veh, 0);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(_veh, 9999);
			ENTITY::SET_ENTITY_VISIBLE(_veh, 0, 1);
			ENTITY::APPLY_FORCE_TO_ENTITY((_veh, false), 1, 0.f, 0.f, 7.0f, 0.f, 0.f, 0.f, 0, true, true, true, false, false);
			});
	}

	void DriveUnderWater(bool toggle)
	{
		if (toggle)
		{
			VEHICLE::SET_VEHICLE_ENGINE_ON(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), true, true, true);
		}
	}

	void ForceVehicleToGround(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0);
			}
		}
	}

	void GlitchVehicle(bool toggle)
	{
		if (toggle)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
			NativeVector3 Rot = ENTITY::GET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 20);
			Rot.z = Rot.z + 20.0;
			ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0, 0, Rot.z, 20, 10);
	    }
	}

	void ThreeSixtyVehicle(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
				NativeVector3 Rot = ENTITY::GET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 2);
				Rot.z = Rot.z + 2.0;
				ENTITY::SET_ENTITY_ROTATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0, 0, Rot.z, 2, 1);
			}
		}
	}

	void EngineAlwaysOn(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				VEHICLE::SET_VEHICLE_ENGINE_ON(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), true, true, true);
			}
		}
	}

	void DriveOnWater(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				Hash ferris = MISC::GET_HASH_KEY("prop_container_ld2");
				NativeVector3 me = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
				float water;
				static int timer = 0;
				static Object model;

				WATER::SET_DEEP_OCEAN_SCALER(-1.f);
				if (WATER::GET_WATER_HEIGHT(me.x, me.y, me.z, &water))
				{
					if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1))
					{
						g_CallbackScript->AddCallback<ModelCallback>(ferris, [=] {
							if (GetTickCount() - timer >= 0)
							{
								model = OBJECT::CREATE_OBJECT(ferris, me.x, me.y, me.z, 1, 1, 1);
								RequestControlOfEnt(model);
								ENTITY::SET_ENTITY_VISIBLE(model, 0, 0);
								ENTITY::FREEZE_ENTITY_POSITION(model, 1);
								ENTITY::SET_ENTITY_ROTATION(model, 0, 0, ENTITY::GET_ENTITY_HEADING(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)), 0, 0);
								ENTITY::SET_ENTITY_COORDS(model, me.x, me.y, water - 2.7f, 0, 0, 0, 1);
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
	}

	void ContainerRider()
	{
		static Object container;
		auto selfVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		NativeVector3 min, max;
		NativeVector3 cmin, cmax;
		auto c = ENTITY::GET_ENTITY_COORDS(selfVeh, 1);
		MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(selfVeh), &min, &max);
		MISC::GET_MODEL_DIMENSIONS(MISC::GET_HASH_KEY("prop_container_ld2"), &cmin, &cmax);

		if (!PED::IS_PED_ON_ANY_BIKE(PLAYER::PLAYER_PED_ID())) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
				notifyMap(116, "Container rider requires a bike.");
				return;
			}
		}

		if (!STREAMING::HAS_MODEL_LOADED(MISC::GET_HASH_KEY("prop_container_ld2")))
			STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("prop_container_ld2"));

		if (!ENTITY::DOES_ENTITY_EXIST(container) || !VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(selfVeh)) {
			static auto tickeer = GetTickCount();
			if ((GetTickCount() - tickeer) >= 1000) {
				if (PAD::IS_CONTROL_PRESSED(2, 111)) {
					tickeer = GetTickCount();
					ENTITY::APPLY_FORCE_TO_ENTITY(selfVeh, 0, 0, 0, 1.5, 0, 0, 0, 0, 1, 1, 1, 0, 1);
				}
			}
			static auto ticker = GetTickCount();
			if (ENTITY::DOES_ENTITY_EXIST(container)) {
				RequestControlOfEnt(container);
				ENTITY::SET_ENTITY_COORDS(container, 0.f, 0.f, 0.f, 1, 1, 1, 0);
				ENTITY::DELETE_ENTITY(&container);
				OBJECT::DELETE_OBJECT(&container);
			}
			container = OBJECT::CREATE_OBJECT(MISC::GET_HASH_KEY("prop_container_ld2"), c.x, c.y, c.z - ((max.z / 2) + cmax.z), 1, 1, 0);
			ENTITY::SET_ENTITY_ROTATION(container, ENTITY::GET_ENTITY_PITCH(selfVeh), 0.f, ENTITY::GET_ENTITY_HEADING(selfVeh), 0, 0);
		}
	}

	void RainbowVehicle()
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			if (FadeR > 0 && FadeB == 0)
			{
				FadeR--;
				FadeG++;
			}
			if (FadeG > 0 && FadeR == 0)
			{
				FadeG--;
				FadeB++;
			}
			if (FadeB > 0 && FadeG == 0)
			{
				FadeR++;
				FadeB--;
			}
		}
		switch (RainbowIterator)
		{
		case 0:

			break;
		case 1:
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1));
				if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1)))
					return;

				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), FadeR, FadeG, FadeB);
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), FadeR, FadeG, FadeB);

				if (VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 0) && VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 1) && VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 2) && VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 3)) VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1),  FadeR, FadeG, FadeB);
				else {
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 0, 1);
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 1, 1);
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 2, 1);
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 3, 1);
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1),  FadeR, FadeG, FadeB);
				}
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1),  FadeR, FadeG, FadeB);
			}
			break;
		case 2:
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1));
				if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1)))
					return;

				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));

				if (VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 0) && VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 1) && VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 2) && VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 3)) VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), FadeR, FadeG, FadeB);
				else {
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 0, 1);
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 1, 1);
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 2, 1);
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), 3, 1);
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
				}
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255), MISC::GET_RANDOM_INT_IN_RANGE(0, 255));
			}
			break;
		}
	}

	static uintptr_t ModuleBaseAdress = (uintptr_t)GetModuleHandle(NULL);

	void BetterGrip(bool toggle)
	{
		if (toggle)
		{
			*(float*)FindAddy(ModuleBaseAdress + 0x19343B0, {}) = 0.f;
		}
		else
		{
			*(float*)FindAddy(ModuleBaseAdress + 0x19343B0, {}) = 0.16666667f;
		}
	}

	void FixVehicle()
	{
		VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0.0f);
		VEHICLE::SET_VEHICLE_ENGINE_HEALTH(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 2000.0f);
		VEHICLE::SET_VEHICLE_BODY_HEALTH(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 2000.0f);
	}

	void RepairVehHotkey(bool toggle)
	{
		if (toggle)
		{
			if (GetAsyncKeyState(VK_F3) & 1)
			{
				FixVehicle();
			}
		}
	}

	void VehicleFlyHotkey(bool toggle)
	{
		if (toggle)
		{
			if (GetAsyncKeyState(VK_F4) & 1)
			{
				g_VehicleFly = !g_VehicleFly;
			}
		}
	}

	/*
	if (!strcmp(g_VehSpawn.c_str(), "")) {
			std::uint32_t model = MISC::GET_HASH_KEY(g_VehSpawn.c_str());
			g_VehSpawn = "";
			g_Logger->Info(g_VehSpawn.c_str());
			SpawnVehicle(model);
		}
	*/

	void SpawnByName(bool toggle)
	{
		if (toggle)
		{
			g_VehicleSpawnByName = false;
			SpawnVehicle(MISC::GET_HASH_KEY(g_VehSpawn.c_str()));
			g_VehSpawn = "";
		}
	}

	void VehicleUpdateLoop()
	{
		//SpawnByName(g_VehicleSpawnByName);

		//if (g_SkipEnterAnimation) { PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(PLAYER::PLAYER_PED_ID()), -1); };
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			VehicleFlyHotkey(g_VehicleFlyHotkey);
			RepairVehHotkey(g_RepairVehHotkey);
			Hornboost(m_Hornboost);
			VehicleFly(g_VehicleFly, g_FlySpeed);
			AutoFlip(g_Autoflip);
			Autofix();
			Seatbelt(g_Seatbelt);
			Driftmode(g_Driftmode);
			VehicleInvincible(g_InvincibleVehicle);
			GlowManager0(m_EnableGlowVehicle);
			VehicleRockets(g_VehicleWeapons, VehicleWeaponHashes[VehicleWeaponIterator], g_WeaponSpeed, g_Lasersight, PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
			DriveUnderWater(g_DriveUnderWater);
			ForceVehicleToGround(g_ForceToGround);
			GlitchVehicle(g_GlitchVehicle);
			ThreeSixtyVehicle(g_ThreeSixty);
			EngineAlwaysOn(g_EngineAlwaysOn);
			DriveOnWater(g_DriveOnWater);
			RainbowVehicle();

			if (g_ContainerRider)
				ContainerRider();

			//BetterGrip(g_BetterGrip);

			if (g_EnableTrails)
			{
				GRAPHICS::_SET_FORCE_VEHICLE_TRAILS(true);

				//7FF6E22BB110 = 26E13C0 = 0x26E1A14 = 654 1.57
				//7FF6E22BB110 = 271B110 = 0x271B764 = 654 1.58


				//*(int*)FindAddy(ModuleBaseAdress + 0x271B764, {}) = g_TrailsRed;
				//*(int*)FindAddy(ModuleBaseAdress + 0x271B765, {}) = g_TrailsGreen;
				//*(int*)FindAddy(ModuleBaseAdress + 0x271B766, {}) = g_TrailsBlue;
				

				if (g_RGBTrails)
				{
					if (g_TrailsRed > 0 && g_TrailsBlue == 0)
					{
						g_TrailsRed--;
						g_TrailsGreen++;
					}
					if (g_TrailsGreen > 0 && g_TrailsRed == 0)
					{
						g_TrailsGreen--;
						g_TrailsBlue++;
					}
					if (g_TrailsBlue > 0 && g_TrailsGreen == 0)
					{
						g_TrailsRed++;
						g_TrailsBlue--;
					}
				}
			}

			ENTITY::SET_ENTITY_RENDER_SCORCHED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), static_cast<int>(g_Scorched));

			ENTITY::SET_ENTITY_COLLISION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), g_Collision, true);

			if (g_InvisibleVehicle) { ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), false, 0); }

			if (g_BypassSpeed) { ENTITY::SET_ENTITY_MAX_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 10000000.f); }

			switch (AbilityIterator)
			{
			case 0:
				Memory::set_value<byte>({ 0x8, 0xD10, 0x20, 0x58B }, 0);
				break;
			case 1:
				Memory::set_value<byte>({ 0x8, 0xD10, 0x20, 0x58B }, 66);
				VEHICLE::_SET_VEHICLE_ROCKET_BOOST_REFILL_TIME(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0.f);
				break;
			case 2:
				Memory::set_value<byte>({ 0x8, 0xD10, 0x20, 0x58B }, 40);
				break;
			}

			if (g_JumpIterator)
			{
				int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				switch (g_JumpIterator)
				{
				case 0:
					break;
				case 1:
					if (GetAsyncKeyState(VK_SPACE) & 1 && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
						ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(veh), 0 + ENTITY::GET_ENTITY_FORWARD_Y(veh), 10.f, 0, 0, 0, 1, 0, 1, 1, 1, 1);
					}
					break;
				case 2:
					if (GetAsyncKeyState(VK_SPACE) && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
						ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(veh), 0 + ENTITY::GET_ENTITY_FORWARD_Y(veh), 0.5f, 0, 0, 0, 1, 0, 1, 1, 1, 1);
					}
					break;
				}
			}
		}
	}
}