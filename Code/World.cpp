#include "Common.hpp"
#include "ScriptCallback.hpp"


namespace Big
{
	void Snowy(bool toggle)
	{
		if (toggle)
		{
			*ScriptGlobal::ScriptGlobal(262145).Add(4723).As<bool*>() = 1;
		}
		else
		{
			*ScriptGlobal::ScriptGlobal(262145).Add(4723).As<bool*>() = 0;
		}
	}

	void SetClouds(const char* cloudtexture)
	{
		MISC::LOAD_CLOUD_HAT(cloudtexture, 3.f);
	}

	void dominos(bool toggle)
	{
		if (toggle)
		{
			NativeVector3 me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
			Hash board = MISC::GET_HASH_KEY("prop_boogieboard_05");
			g_CallbackScript->AddCallback<ModelCallback>(board, [=] {
				static int timer = 0;
				if (GetTickCount() - timer >= 100)
				{
					Object domino = OBJECT::CREATE_OBJECT(board, me.x, me.y - 1, me.z - 1, 1, 1, 1);
					ENTITY::SET_ENTITY_HEADING(domino, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
					timer = GetTickCount();
				}
				});
		}
	}

	void BlackHole()
	{
		static ListPool* r = *(ListPool**)((uintptr_t)GetModuleHandleA(0) + 0x28B5DA0);

		static NativeVector3 oregano;

		oregano = g_black_hole_pos; //ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
		GRAPHICS::DRAW_MARKER(28, oregano.x, oregano.y, oregano.z, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0, 0, 0, 255, false, false, 0, false, NULL, NULL, false);

		for (int i = 0; i < r->capacity; i++)
		{
			std::uint64_t vehicle_entity = r->get(i);
			if (vehicle_entity == NULL)
				continue;
			std::int32_t vehicle = g_GameFunctions->m_PointerToHande(vehicle_entity);
			if (!ENTITY::DOES_ENTITY_EXIST(vehicle))
				continue;
			RequestControlOfEnt(vehicle);
			NativeVector3 l_vHndCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, 0.0f, 0.0f, 0.0f);

			auto pepperoni = ENTITY::GET_ENTITY_COORDS(vehicle, 1);
			auto pineapple = oregano;
			pineapple.z += 1.5f;
			Vector3 extra_cheese = { pineapple.x - pepperoni.x, pineapple.y - pepperoni.y, pineapple.z - pepperoni.z };
			if (distanceBetween(pineapple, pepperoni) > 3.f) {
				ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, (extra_cheese.x / 13) * 0.1f, (extra_cheese.y / 13) * 0.1f, extra_cheese.z / 13, 0.f, 0.f, 0.f, 0, false, true, true, 0, 0);
			}
			else {
				ENTITY::SET_ENTITY_VELOCITY(vehicle, 0.f, 0.f, 0.f);
				ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 0.5f, 0.f, 0.f, extra_cheese.z / 15, 0.f, 0.f, 0.f, 0, false, true, true, 0, 0);
			}

		}
	}

    void Ramp()
    {
        Hash model = MISC::GET_HASH_KEY("lts_prop_lts_ramp_01");
        Hash model1 = MISC::GET_HASH_KEY("prop_skate_halfpipe_cr");
        switch (RampIndex)
        {
        case 0:
            g_CallbackScript->AddCallback<ModelCallback>(model, [=] {

                float length = 5.4f;
                for (int i = 0; i < g_RampCount; i++)
                {
                    NativeVector3 me = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.f, (length * i), i);
                    Object ramp = OBJECT::CREATE_OBJECT(model, me.x, me.y, me.z - 1.75f, 1, 1, 1);
                    ENTITY::SET_ENTITY_HEADING(ramp, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
                    g_Ramp.push_back(ramp);
                }
            });
            break;
        case 1:
            g_CallbackScript->AddCallback<ModelCallback>(model1, [=] {

                float length = 9.25f;
                for (int i = 0; i < g_RampCount; i++)
                {
                    NativeVector3 me = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.f, (length * i), 0.f);
                    Object ramp = OBJECT::CREATE_OBJECT(model1, me.x, me.y, me.z - 1.75f, 1, 1, 1);
                    ENTITY::SET_ENTITY_HEADING(ramp, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
                    g_Ramp.push_back(ramp);
                }
            });
            break;
        }
    }
    void DeleteRamp()
    {
        for (auto ramp : g_Ramp)
        {
            ENTITY::DELETE_ENTITY(&ramp);
        }
    }

	void MiscUpdateLoop()
	{
		if (g_TimeEnable) NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g_Hour, g_Minute, g_Second);
		if (g_PauseTime) CLOCK::PAUSE_CLOCK(true); 
			else CLOCK::PAUSE_CLOCK(false);


		MISC::_SET_RAIN_FX_INTENSITY(g_Rain);
		WATER::_SET_CURRENT_INTENSITY(g_Waves);
		MISC::SET_WIND_SPEED(g_Wind);
		MISC::_SET_CLOUD_HAT_OPACITY(g_Clouds);

		if (g_RGBLight)
		{
			if (g_LightRed > 0 && g_LightBlue == 0)
			{
				g_LightRed--;
				g_LightGreen++;
			}
			if (g_LightGreen > 0 && g_LightRed == 0)
			{
				g_LightGreen--;
				g_LightBlue++;
			}
			if (g_LightBlue > 0 && g_LightGreen == 0)
			{
				g_LightRed++;
				g_LightBlue--;
			}
		}


		if (g_EnableLight)
		{
			NativeVector3 me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
			GRAPHICS::DRAW_LIGHT_WITH_RANGE(me.x, me.y, me.z - 2, g_LightRed, g_LightGreen, g_LightBlue, 999, g_LigtIntensity);
		}

		dominos(g_dominos);

		if (g_black_hole)
		{
			BlackHole();
		}
	}
}