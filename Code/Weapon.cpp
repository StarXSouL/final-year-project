#include "Common.hpp"
#include "ScriptCallback.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

namespace Big
{
	void Revivegun(bool toggle)
	{
		if (toggle)
		{
			Entity Target;
			if (is_ped_aiming(PLAYER::PLAYER_PED_ID()))
			{
				Target = get_raycast_entity();
				if (ENTITY::IS_ENTITY_A_PED(Target))
				{
					RequestControlOfEnt(Target);
					if (ENTITY::IS_ENTITY_DEAD(Target, false))
						BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(Target);
					ENTITY::SET_ENTITY_HEALTH(Target, 200);
				}
			}
		}
	}

	void InfiniteAmmo(bool toggle)
	{
		if (toggle)
		{
			Hash cur;
			if (WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &cur, 1))
			{
				if (WEAPON::IS_WEAPON_VALID(cur))
				{
					int maxAmmo;
					if (WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), cur, &maxAmmo))
					{
						WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), cur, maxAmmo, NULL);

						maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), cur, 1);
						if (maxAmmo > 0)
							WEAPON::SET_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), cur, maxAmmo);
					}
				}
			}
		}
	}

	void Carnado(bool toggle)
	{
		if (toggle)
		{
			static int zoom = 20;
			static int rotate{};
			if (GetAsyncKeyState(VK_RBUTTON) || PAD::IS_CONTROL_PRESSED(2, 25))
			{
				//STREAMING::REQUEST_ANIM_DICT("anim@amb@nightclub@lazlow@hi_podium@");
				//BRAIN::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), "anim@amb@nightclub@lazlow@hi_podium@", "danceidle_mi_13_turnaround_laz", 8.f, 8.f, -1, 1, 1, 0, 0, 0);

				rotate += 10;
				HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();
				const int numElements = 10;
				const int arrSize = numElements * 2 + 2;
				int veh[arrSize];
				veh[0] = numElements;
				int count = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), veh);
				if (veh != NULL)
				{
					for (int i = 0; i < count; i++)
					{
						int ID = i * 2 + 2;

						RequestControlOfEnt(veh[ID]);
						if (veh[ID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[ID]))
						{
							g_CallbackScript->AddCallback<NetworkControlCallback>((veh[ID]), [=] { RequestControlOfEnt(veh[ID]); });

							g_CallbackScript->AddCallback<NetworkControlCallback>((veh[ID]), [=] { RequestControlOfEnt(veh[ID]); });
							NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
							NativeVector3 dir = g_Utility->RotationToDirectionV3(rot);
							NativeVector3 spawnPosition = g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(dir, zoom));

							if (ENTITY::IS_ENTITY_A_PED(veh[ID]) && PED::IS_PED_IN_ANY_VEHICLE(veh[ID], 0))
							{
								veh[ID] = PED::GET_VEHICLE_PED_IS_IN(veh[ID], 0);
							}

							g_CallbackScript->AddCallback<NetworkControlCallback>((veh[ID]), [=] { RequestControlOfEnt(veh[ID]); });

							NativeVector3 getcoors1 = ENTITY::GET_ENTITY_COORDS(veh[0], 0);
							NativeVector3 getcoors2 = ENTITY::GET_ENTITY_COORDS(veh[1], 0);
							NativeVector3 getcoors3 = ENTITY::GET_ENTITY_COORDS(veh[2], 0);
							NativeVector3 getcoors4 = ENTITY::GET_ENTITY_COORDS(veh[3], 0);
							NativeVector3 getcoors5 = ENTITY::GET_ENTITY_COORDS(veh[4], 0);
							NativeVector3 getcoors6 = ENTITY::GET_ENTITY_COORDS(veh[5], 0);
							NativeVector3 getcoors7 = ENTITY::GET_ENTITY_COORDS(veh[6], 0);
							NativeVector3 getcoors8 = ENTITY::GET_ENTITY_COORDS(veh[7], 0);
							NativeVector3 getcoors9 = ENTITY::GET_ENTITY_COORDS(veh[8], 0);
							NativeVector3 getcoors10 = ENTITY::GET_ENTITY_COORDS(veh[9], 0);

							float getaimcoorsX1 = GravityGunGoto(spawnPosition.x, getcoors1.x);
							float getaimcoorsY1 = GravityGunGoto(spawnPosition.y, getcoors1.y);
							float getaimcoorsZ1 = GravityGunGoto(spawnPosition.z, getcoors1.z);
							float getaimcoorsX2 = GravityGunGoto(spawnPosition.x, getcoors2.x);
							float getaimcoorsY2 = GravityGunGoto(spawnPosition.y, getcoors2.y);
							float getaimcoorsZ2 = GravityGunGoto(spawnPosition.z, getcoors2.z - 1);
							float getaimcoorsX3 = GravityGunGoto(spawnPosition.x, getcoors3.x);
							float getaimcoorsY3 = GravityGunGoto(spawnPosition.y, getcoors3.y);
							float getaimcoorsZ3 = GravityGunGoto(spawnPosition.z, getcoors3.z - 2);
							float getaimcoorsX4 = GravityGunGoto(spawnPosition.x, getcoors4.x);
							float getaimcoorsY4 = GravityGunGoto(spawnPosition.y, getcoors4.y);
							float getaimcoorsZ4 = GravityGunGoto(spawnPosition.z, getcoors4.z - 3);
							float getaimcoorsX5 = GravityGunGoto(spawnPosition.x, getcoors5.x);
							float getaimcoorsY5 = GravityGunGoto(spawnPosition.y, getcoors5.y);
							float getaimcoorsZ5 = GravityGunGoto(spawnPosition.z, getcoors5.z - 4);
							float getaimcoorsX6 = GravityGunGoto(spawnPosition.x, getcoors6.x);
							float getaimcoorsY6 = GravityGunGoto(spawnPosition.y, getcoors6.y);
							float getaimcoorsZ6 = GravityGunGoto(spawnPosition.z, getcoors6.z - 5);
							float getaimcoorsX7 = GravityGunGoto(spawnPosition.x, getcoors7.x);
							float getaimcoorsY7 = GravityGunGoto(spawnPosition.y, getcoors7.y);
							float getaimcoorsZ7 = GravityGunGoto(spawnPosition.z, getcoors7.z - 6);
							float getaimcoorsX8 = GravityGunGoto(spawnPosition.x, getcoors8.x);
							float getaimcoorsY8 = GravityGunGoto(spawnPosition.y, getcoors8.y);
							float getaimcoorsZ8 = GravityGunGoto(spawnPosition.z, getcoors8.z - 7);
							float getaimcoorsX9 = GravityGunGoto(spawnPosition.x, getcoors9.x);
							float getaimcoorsY9 = GravityGunGoto(spawnPosition.y, getcoors9.y);
							float getaimcoorsZ9 = GravityGunGoto(spawnPosition.z, getcoors9.z - 8);
							float getaimcoorsX10 = GravityGunGoto(spawnPosition.x, getcoors10.x);
							float getaimcoorsY10 = GravityGunGoto(spawnPosition.y, getcoors10.y);
							float getaimcoorsZ10 = GravityGunGoto(spawnPosition.z, getcoors10.z - 9);

							ENTITY::SET_ENTITY_ROTATION(veh[0], 0, 0, rotate, 0, 0);
							ENTITY::SET_ENTITY_ROTATION(veh[1], 0, 0, rotate, 0, 0);
							ENTITY::SET_ENTITY_ROTATION(veh[2], 0, 0, rotate, 0, 0);
							ENTITY::SET_ENTITY_ROTATION(veh[3], 0, 0, rotate, 0, 0);
							ENTITY::SET_ENTITY_ROTATION(veh[4], 0, 0, rotate, 0, 0);
							ENTITY::SET_ENTITY_ROTATION(veh[5], 0, 0, rotate, 0, 0);
							ENTITY::SET_ENTITY_ROTATION(veh[6], 0, 0, rotate, 0, 0);
							ENTITY::SET_ENTITY_ROTATION(veh[7], 0, 0, rotate, 0, 0);
							ENTITY::SET_ENTITY_ROTATION(veh[8], 0, 0, rotate, 0, 0);
							ENTITY::SET_ENTITY_ROTATION(veh[9], 0, 0, rotate, 0, 0);

							ENTITY::SET_ENTITY_VELOCITY(veh[0], getaimcoorsX1 * 0.5, getaimcoorsY1 * 0.5, getaimcoorsZ1 * 0.5);
							ENTITY::SET_ENTITY_VELOCITY(veh[1], getaimcoorsY2 * 0.5, getaimcoorsY2 * 0.5, getaimcoorsZ2 * 0.5);
							ENTITY::SET_ENTITY_VELOCITY(veh[2], getaimcoorsX3 * 0.5, getaimcoorsY3 * 0.5, getaimcoorsZ3 * 0.5);
							ENTITY::SET_ENTITY_VELOCITY(veh[3], getaimcoorsX4 * 0.5, getaimcoorsY4 * 0.5, getaimcoorsZ4 * 0.5);
							ENTITY::SET_ENTITY_VELOCITY(veh[4], getaimcoorsX5 * 0.5, getaimcoorsY5 * 0.5, getaimcoorsZ5 * 0.5);
							ENTITY::SET_ENTITY_VELOCITY(veh[5], getaimcoorsX6 * 0.5, getaimcoorsY6 * 0.5, getaimcoorsZ6 * 0.5);
							ENTITY::SET_ENTITY_VELOCITY(veh[6], getaimcoorsX7 * 0.5, getaimcoorsY7 * 0.5, getaimcoorsZ7 * 0.5);
							ENTITY::SET_ENTITY_VELOCITY(veh[7], getaimcoorsX8 * 0.5, getaimcoorsY8 * 0.5, getaimcoorsZ8 * 0.5);
							ENTITY::SET_ENTITY_VELOCITY(veh[8], getaimcoorsX9 * 0.5, getaimcoorsY9 * 0.5, getaimcoorsZ9 * 0.5);
							ENTITY::SET_ENTITY_VELOCITY(veh[9], getaimcoorsX10 * 0.5, getaimcoorsY10 * 0.5, getaimcoorsZ10 * 0.5);

							if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 261) && zoom <= 20)
							{
								zoom += 1;
							}
							if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 262) && zoom >= 5)
							{
								zoom -= 1;
							}
						}
					}
				}
			}
		}
	}


	void GravityBug(bool toggle)
	{
		if (toggle)
		{
			static bool oneperswitch{ false };
			static int zoom = 10;
			static Entity entitiess;
			static Entity entitiesss;

			switch (GravityGunSize)
			{
			case 0:

				if (GetAsyncKeyState(VK_RBUTTON) || PAD::IS_CONTROL_PRESSED(2, 25))
				{

					if (LockOnEntity)
					{
						if (entitiess == 0)
						{
							PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &entitiess);
						}
					}
					else
					{
						PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &entitiess);
					}
					
				
					g_CallbackScript->AddCallback<NetworkControlCallback>((entitiess), [=] { RequestControlOfEnt(entitiess); });
					NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
					NativeVector3 dir = g_Utility->RotationToDirectionV3(rot);
					NativeVector3 spawnPosition = g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(dir, zoom));

					if (ENTITY::IS_ENTITY_A_PED(entitiess) && PED::IS_PED_IN_ANY_VEHICLE(entitiess, 0))
					{
						entitiess = PED::GET_VEHICLE_PED_IS_IN(entitiess, 0);
					}

					NativeVector3 getcoors = ENTITY::GET_ENTITY_COORDS(entitiess, 0);
					float getaimcoorsX = GravityGunGoto(spawnPosition.x, getcoors.x);
					float getaimcoorsY = GravityGunGoto(spawnPosition.y, getcoors.y);
					float getaimcoorsZ = GravityGunGoto(spawnPosition.z, getcoors.z);
					ENTITY::SET_ENTITY_VELOCITY(entitiess, getaimcoorsX * g_Velocity, getaimcoorsY * g_Velocity, getaimcoorsZ * g_Velocity);

					if (GetAsyncKeyState(VK_LBUTTON) || PAD::IS_CONTROL_PRESSED(2, 24))
					{
						g_CallbackScript->AddCallback<NetworkControlCallback>((entitiess), [=] {
							RequestControlOfEnt(entitiess);
							Entity Vehicle = entitiess;
							ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, dir.x * g_Force * 1000, dir.y * g_Force * 1000, dir.z * g_Force * 1000, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
							Vehicle = entitiesss;
							entitiess = entitiesss;
						});
					}

					
					if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 261))
					{
						zoom += g_PullPushStrength;
					}
					if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 262))
					{
						zoom -= g_PullPushStrength;

					}
				}

				break;
			case 1:
				Entity currEnt;
				static int zoom = 10;
				if (GetAsyncKeyState(VK_RBUTTON) || PAD::IS_CONTROL_PRESSED(2, 25))
				{

					PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &currEnt);
					g_CallbackScript->AddCallback<NetworkControlCallback>((currEnt), [=] { RequestControlOfEnt(currEnt); });
					if (std::find(GravityGunDatabase.begin(), GravityGunDatabase.end(), currEnt) != GravityGunDatabase.end()) {}
					else if (GravityGunDatabase.size() > m_GravityGunEntityCount) {}
					else { GravityGunDatabase.push_back(currEnt); }

					for (std::int32_t entities : GravityGunDatabase)
					{
						g_CallbackScript->AddCallback<NetworkControlCallback>((entities), [=] { RequestControlOfEnt(entities); });
						NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
						NativeVector3 dir = g_Utility->RotationToDirectionV3(rot);
						NativeVector3 spawnPosition = g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(dir, zoom));

						if (ENTITY::IS_ENTITY_A_PED(entities) && PED::IS_PED_IN_ANY_VEHICLE(entities, 0))
						{
							entities = PED::GET_VEHICLE_PED_IS_IN(entities, 0);
						}

						g_CallbackScript->AddCallback<NetworkControlCallback>((entities), [=] { RequestControlOfEnt(entities); });

						NativeVector3 getcoors = ENTITY::GET_ENTITY_COORDS(entities, 0);
						float getaimcoorsX = GravityGunGoto(spawnPosition.x, getcoors.x);
						float getaimcoorsY = GravityGunGoto(spawnPosition.y, getcoors.y);
						float getaimcoorsZ = GravityGunGoto(spawnPosition.z, getcoors.z);
						ENTITY::SET_ENTITY_VELOCITY(entities, getaimcoorsX * g_Velocity, getaimcoorsY * g_Velocity, getaimcoorsZ * g_Velocity);

						if (GetAsyncKeyState(VK_LBUTTON) || PAD::IS_CONTROL_PRESSED(2, 24))
						{
							g_CallbackScript->AddCallback<NetworkControlCallback>((entities), [=] { RequestControlOfEnt(entities); });
							g_CallbackScript->AddCallback<NetworkControlCallback>((entities), [=] {
								RequestControlOfEnt(entities);
								Entity Vehicle = entities;
								ENTITY::APPLY_FORCE_TO_ENTITY(Vehicle, 1, dir.x * g_Force * 1000, dir.y * g_Force * 1000, dir.z * g_Force * 1000, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
								ENTITY::DELETE_ENTITY(&Vehicle);
								GravityGunDatabase.clear();
								ENTITY::DELETE_ENTITY(&Vehicle);
								GravityGunDatabase.erase(GravityGunDatabase.begin(), GravityGunDatabase.end());
								ENTITY::DELETE_ENTITY(&Vehicle);
								free((void*)Vehicle);
								std::vector<std::int32_t>().swap(GravityGunDatabase);

							});
						}

					}
					if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 261))
					{
						zoom += g_PullPushStrength;
					}
					if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 262))
					{
						zoom -= g_PullPushStrength;
					}
				}

				break;
			} //end

		}
	}

	void OneHitAmmo(bool toggle)
	{
		if (toggle)
		{
			Entity EntityTarget;
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget))
			{
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{

					if (ENTITY::IS_ENTITY_A_PED(EntityTarget)
						&& PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1)) {
						EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
					}
					VEHICLE::EXPLODE_VEHICLE(EntityTarget, true, false);
					VEHICLE::SET_VEHICLE_OUT_OF_CONTROL(EntityTarget, true, true);//idk
				}
			}
			PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 9999999.9999f);
			PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 9999999.9999f, NULL);
			PLAYER::SET_PLAYER_WEAPON_DEFENSE_MODIFIER(PLAYER::PLAYER_ID(), 9999999.9999f);
			PLAYER::SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER(PLAYER::PLAYER_ID(), 9999999.9999f);
		}
	}


	void LaserSight(bool toggle)
	{
		if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()))
		{
			if (toggle)
			{
				auto camrot = CAM::GET_GAMEPLAY_CAM_ROT(0);
				auto camdir = g_Utility->RotationToDirectionV3(camrot);
				auto start = ENTITY::GET_ENTITY_COORDS(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID()), 1);
				auto end = g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(camdir, 1.f));

				GRAPHICS::DRAW_LINE(start.x, start.y, start.z, end.x, end.y, end.z, g_UiManager->m_OptionSelectedBackgroundColor.r, g_UiManager->m_OptionSelectedBackgroundColor.g, g_UiManager->m_OptionSelectedBackgroundColor.b, 255);
			}
		}

	}


	void NoRecoil(bool toggle)
	{
		if (toggle)
		{
			Memory::set_value<float>({ 0x8, 0x10B8, 0x20, 0x2F4 }, 0);
			Memory::set_value<float>({ 0x8, 0x10B8, 0x20, 0x124 }, 0);
		}
		else
		{
			Memory::set_value<float>({ 0x8, 0x10B8, 0x20, 0x2F4 }, 1);
			Memory::set_value<float>({ 0x8, 0x10B8, 0x20, 0x124 }, 1);
		}
	}


	

	void RapidFire(bool toggle)
	{
		if (toggle)
		{
			if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
				NativeVector3 gameplayCam = CAM::_GET_GAMEPLAY_CAM_COORDS();
				NativeVector3 gameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
				NativeVector3 gameplayCamDirection = g_Utility->RotationToDirectionV3(gameplayCamRot);
				NativeVector3 startCoords = g_Utility->AddV3(gameplayCam, (g_Utility->MultiplyV3(gameplayCamDirection, 1.0f)));
				NativeVector3 endCoords = g_Utility->AddV3(startCoords, g_Utility->MultiplyV3(gameplayCamDirection, 500.0f));
				Hash weaponhash;
				WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
				if (PAD::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000)) {
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(startCoords.x, startCoords.y, startCoords.z, endCoords.x, endCoords.y, endCoords.z, 50, 1, weaponhash, PLAYER::PLAYER_PED_ID(), 1, 1, 0xbf800000);
				}
			}
		}
	}

	void YoinkGun(bool toggle)
	{
		
			if (toggle)
			{
				Entity Target;
				Vehicle Car;
				if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &Car) && (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &Target)))
				{
					
					RequestControlOfEnt(Target);

					if (ENTITY::IS_ENTITY_A_PED(Target) && PED::IS_PED_IN_ANY_VEHICLE(Target, 1))
					{
						Car = PED::GET_VEHICLE_PED_IS_IN(Target, 0);
						if (PED::IS_PED_IN_VEHICLE(Target, Car, 1))
						{
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Target, 1, 1);
							ENTITY::DELETE_ENTITY(&Target);
							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Target, -1);
						}
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Target, -1);
					}

				}
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), Target, -1);
				}
			}
		
	}

	void AimBot(bool toggle)
	{
		static std::int32_t aimcam;

		if (g_AimbotInterator != 2)
		{
			if (CAM::DOES_CAM_EXIST(aimcam))
			{
				CAM::DESTROY_CAM(aimcam, 1);
				CAM::RENDER_SCRIPT_CAMS(0, true, 700, 1, 1, 0);
			}
		}

		//if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()))
		{
			switch (g_AimbotInterator)
			{
			case 0:
				if (g_AimbotInterator != 2)
				{
					if (CAM::DOES_CAM_EXIST(aimcam))
					{
						CAM::DESTROY_CAM(aimcam, 1);
						CAM::RENDER_SCRIPT_CAMS(0, true, 700, 1, 1, 0);
					}
				}
				break;
			case 1:
				if (1 == 1)
				{
					if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()))
					{
						PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), FALSE);
						const int numElements = 10;
						const int arrSize = numElements * 2 + 2;
						int veh[arrSize];	//0 index is the size of the array	
						veh[0] = numElements;
						int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), veh, -1);
						Ped closest = 0;
						if (veh != NULL)
						{
							for (int i = 0; i < count; i++)
							{
								int offsettedID = i * 2 + 2;
								if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
								{
									for (int j = -1; j <= 2; ++j)
									{

										Any ped = veh[offsettedID];
										NativeVector3 ped_coords = ENTITY::GET_ENTITY_COORDS(ped, TRUE);
										NativeVector3 self_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
										if (closest == 0) closest = ped;
										else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
										Hash weaponhash;
										WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
										float screenX, screenY;
										BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
										if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
										{
											NativeVector3 target_coords = PED::GET_PED_BONE_COORDS(closest, 0x796e, 0, 0, 0);

											if (IsKeyPressed(VK_LBUTTON) && GetTickCount() % 20 == 0)
											{
												MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, target_coords.x, target_coords.y, target_coords.z, 50, 1, weaponhash, PLAYER::PLAYER_PED_ID(), 1, 1, 0xbf800000);
											}


										}
									}
								}
							}
						}
					}
				}
				if (g_AimbotInterator != 2)
				{
					if (CAM::DOES_CAM_EXIST(aimcam))
					{
						CAM::DESTROY_CAM(aimcam, 1);
						CAM::RENDER_SCRIPT_CAMS(0, true, 700, 1, 1, 0);
					}
				}
				break;
			case 2:
				if (g_AimbotInterator == 2)
				{

					NativeVector3 aimpos = CAM::GET_GAMEPLAY_CAM_COORD();
					CAM::DESTROY_ALL_CAMS(true);
					aimcam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", aimpos.x, aimpos.y, aimpos.z, 0, 0, 0, 50, 1, 2);
					CAM::RENDER_SCRIPT_CAMS(1, true, 700, 1, 1, 0);
					CAM::SET_CAM_ACTIVE(aimcam, 1);
					CAM::SET_CAM_ROT(aimcam, CAM::GET_GAMEPLAY_CAM_ROT(0).x, CAM::GET_GAMEPLAY_CAM_ROT(0).y, CAM::GET_GAMEPLAY_CAM_ROT(0).z, 0);

					for (int i = 0; i < 32; i++)
					{
						NativeVector3 target_coords = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), SKEL_Head, 0, 0, 0);
						NativeVector3 ped_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 1);
						NativeVector3 self_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);

						Ped PlayerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						NativeVector3 PedCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
						NativeVector3 Coords = ENTITY::GET_ENTITY_COORDS(PlayerPed, false);
						float distance = g_Utility->GetDistanceFloat(PedCoords, Coords);

						if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()))
						{
							GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("ps_menu", 0);
							GRAPHICS::DRAW_SPRITE("ps_menu", "common_medal", .5, .5, .003, .005, 0, 255, 255, 255, 255, 0);
							if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
							{
								if (i == PLAYER::PLAYER_ID())
									continue;


								const int numElements = 10;
								const int arrSize = numElements * 2 + 2;
								int veh[arrSize];
								veh[0] = numElements;
								int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), veh, -1);
								Ped closest = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
								if (veh != NULL) {
									for (int i = 0; i < count; i++)
									{
										int offsettedID = i * 2 + 2;
										if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
										{
											for (int j = -1; j <= 2; ++j)
											{
												Any ped = veh[offsettedID];

												if (closest == 0) closest = ped;
												else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
												Hash weaponhash;
												WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
												float screenX, screenY;
												BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
												if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
												{
													CAM::POINT_CAM_AT_PED_BONE(aimcam, closest, SKEL_Head, 0, 0, .1, 0);
												}
											}
										}
									}
								}
							}
						}
					}
					if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()))
					{
						const int numElements = 10;
						const int arrSize = numElements * 2 + 2;
						int veh[arrSize];
						veh[0] = numElements;
						int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), veh, -1);
						Ped closest = 0;
						if (veh != NULL) {
							for (int i = 0; i < count; i++)
							{
								int offsettedID = i * 2 + 2;
								if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
								{
									for (int j = -1; j <= 2; ++j)
									{

										Any ped = veh[offsettedID];
										NativeVector3 ped_coords = ENTITY::GET_ENTITY_COORDS(ped, TRUE);
										NativeVector3 self_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
										if (closest == 0) closest = ped;
										else if (MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ped_coords.x, ped_coords.y, ped_coords.z, TRUE) < MISC::GET_DISTANCE_BETWEEN_COORDS(self_coords.x, self_coords.y, self_coords.z, ENTITY::GET_ENTITY_COORDS(closest, TRUE).x, ENTITY::GET_ENTITY_COORDS(closest, TRUE).y, ENTITY::GET_ENTITY_COORDS(closest, TRUE).z, TRUE)) closest = ped;//                                                                                                                            
										Hash weaponhash;
										WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
										float screenX, screenY;
										BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(ENTITY::GET_ENTITY_COORDS(closest, true).x, ENTITY::GET_ENTITY_COORDS(closest, true).y, ENTITY::GET_ENTITY_COORDS(closest, true).z, &screenX, &screenY);
										if (closest != NULL && !ENTITY::IS_ENTITY_DEAD(closest, 0) && onScreen)
										{

											NativeVector3 target_coords = PED::GET_PED_BONE_COORDS(closest, SKEL_Head, 0, 0, 0);

											CAM::POINT_CAM_AT_PED_BONE(aimcam, closest, SKEL_Head, 0, 0, .1, 0);
										}
									}
								}
							}
						}
					}
				}
				if (g_AimbotInterator != 2)
				{
					if (CAM::DOES_CAM_EXIST(aimcam))
					{
						CAM::DESTROY_CAM(aimcam, 1);
						CAM::RENDER_SCRIPT_CAMS(0, true, 700, 1, 1, 0);
					}
				}
				break;
			}
		}
		

	}

	void ForceGun(bool toggle)
	{
		if (toggle)
		{
			Entity EntityTarget;
			NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
			NativeVector3 dir = g_Utility->RotationToDirectionV3(rot);
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget))
			{
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					if (ENTITY::IS_ENTITY_A_PED(EntityTarget)
						&& PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1)) {
						EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
					}
					ENTITY::APPLY_FORCE_TO_ENTITY(EntityTarget, 1, dir.x * 100000.0f, dir.y * 100000.0f, dir.z * 100000.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
				}
			}
		}
	}

	void AirstrikeGun(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				NativeVector3 shoot;
				if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &shoot))
				{
					Hash weaponAssetRocket = MISC::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
					if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
					{
						WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
					}

					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(shoot.x, shoot.y, shoot.z + 25, shoot.x, shoot.y, shoot.z, 100, 1, weaponAssetRocket, PLAYER::PLAYER_PED_ID(), 1, 0, 1000.0);
				}
			}
		}
	}

	void TeleportGun(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				NativeVector3 coords;
				if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &coords))
				{
					ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 0, 0, 0, 1);
				}
			}
		}
	}

	void DeleteGun(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				Entity Delete;
				if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &Delete)) {

					if (ENTITY::DOES_ENTITY_EXIST(Delete) && NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Delete) && PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
					{
						ENTITY::DETACH_ENTITY(Delete, 1, 1);
						ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Delete, 0, 0, 0, 0, 0, 0);
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Delete, 0, 1);
						ENTITY::DELETE_ENTITY(&Delete);
					}
				}
			}
		}
	}

	void RainbowCamo(bool toggle)
	{
		if (toggle)
		{
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			static LPCSTR weaponNames[] = {
				"WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR",
				"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG",
				"WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG",
				"WEAPON_COMBATMG", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
				"WEAPON_STUNGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER_SMOKE",
				"WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
				"WEAPON_MOLOTOV", "WEAPON_FIREEXTINGUISHER", "WEAPON_PETROLCAN", "WEAPON_SNSPISTOL", "WEAPON_SPECIALCARBINE",
				"WEAPON_HEAVYPISTOL", "WEAPON_BULLPUPRIFLE", "WEAPON_HOMINGLAUNCHER", "WEAPON_PROXMINE", "WEAPON_SNOWBALL",
				"WEAPON_VINTAGEPISTOL", "WEAPON_DAGGER", "WEAPON_FIREWORK", "WEAPON_MUSKET", "WEAPON_MARKSMANRIFLE", "WEAPON_HEAVYSHOTGUN",
				"WEAPON_GUSENBERG", "WEAPON_HATCHET", "WEAPON_RAILGUN", "WEAPON_FLAREGUN",
				"WEAPON_KNUCKLE", "GADGET_NIGHTVISION", "GADGET_PARACHUTE", "WEAPON_MARKSMANPISTOL"
			};
			for (int i = 0; i < sizeof(weaponNames) / sizeof(weaponNames[0]); i++)
			{
				if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, MISC::GET_HASH_KEY((char*)weaponNames[i]), 0))
				{
					WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, MISC::GET_HASH_KEY((char*)weaponNames[i]), rand() % 8);
				}
			}
		}

	}

	void MoneyGun(bool toggle)
	{
		if (toggle)
		{
			STREAMING::REQUEST_MODEL(-1666779307);
			Player playerPed = PLAYER::PLAYER_PED_ID();
			if (PAD::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000))
			{
				g_CallbackScript->AddCallback<ModelCallback>(-1666779307, [] {
					NativeVector3 ShootCoord;
					WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &ShootCoord);
					OBJECT::CREATE_AMBIENT_PICKUP(0x1E9A99F8, ShootCoord.x, ShootCoord.y, ShootCoord.z + 0.5f, 0, 2500, -1666779307, FALSE, TRUE);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(-1666779307);
				});
			}
		}
	}

	void RPGun(bool toggle)
	{
		if (toggle)
		{
			STREAMING::REQUEST_MODEL(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"));
			Player playerPed = PLAYER::PLAYER_PED_ID();
			if (PAD::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000))
			{
				g_CallbackScript->AddCallback<ModelCallback>(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"), [] {
					NativeVector3 ShootCoord;
					WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &ShootCoord);
					OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, ShootCoord.x, ShootCoord.y, ShootCoord.z + 0.5f, 0, 2500, MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"), FALSE, TRUE);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(MISC::GET_HASH_KEY("vw_prop_vw_colle_alien"));
				});
			}
		}
	}

	void Lasersight(bool toggle)
	{		
		if (toggle)
		{
			if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_ID()))
			{
				NativeVector3 impact;
				Hash hash = MISC::GET_HASH_KEY("GADGET_PARACHUTE");

				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 1, 1);
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &impact))
					{
						if (!ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID()))
						{
							ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 0, 0, 12);
							BRAIN::SET_PARACHUTE_TASK_THRUST(PLAYER::PLAYER_PED_ID(), 12.f);
							BRAIN::TASK_PARACHUTE_TO_TARGET(PLAYER::PLAYER_PED_ID(), impact.x, impact.y, impact.z);

							if (ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID()))
							{
								ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 0, 12, 0);
							}
						}
					}
				}
			}
		}
	}

	void FlamingAmmo(bool toggle)
	{
		
		{
			if (toggle)
			{
				g_Utility->WriteFlameFlag(eFrameFlagFireAmmo);
			}
			else
			{
				g_Utility->RemoveFlameFlag(eFrameFlagFireAmmo);
			}
		}
	}

	void ExplosiveAmmo(bool toggle)
	{
	
		if (toggle)
		{
			g_Utility->WriteFlameFlag(eFrameFlagExplosiveAmmo);
		}
		else
		{
			g_Utility->RemoveFlameFlag(eFrameFlagExplosiveAmmo);
		}
		
	}


	void GiveWeapons()
	{
		static std::uint32_t Weapons[] = { 0x184140A1, 0xDB26713A, 0x45CD9CF3, 0xC78D71B4, 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, /* Melee  */   0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, /* Handguns */  0x13532244, 0x2BE6766B, 0x2BE6766B, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, /* Submachine Guns */  0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D,   /* Shotguns */ 0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830,  /* Assault Rifles */ 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683,   /* Light Machine Guns */ 0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, /* Sniper Rifles  */ 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, /* Heavy Weapons  */ 0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3,  /*Throwables  */ 0x34A67B97, 0xFBAB5776, 0x060EC506,  /*Miscellaneous  */ 0xAF3696A1, 0x476BF155, 0xB62D1F67,	  /* 1.46  */ 0x2B5EF5EC, 0x2CE227AC, 0x832A1A76, 0x917F6C8C,  /* Casino  */  /* 1.61 */ -610080759, 1853742572, -774507221 /* Criminal Enterprise */};
		for (int i = 0; i < (sizeof(Weapons) / 4); i++) { WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), Weapons[i], 9999, 1); }
	}

	void ExplosiveAmmoFunction(bool toggle)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				NativeVector3 coords;
				if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &coords))
				{
					FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, m_Explosion_Iterator, m_Damage, m_Audiable, m_Invisible, m_CameraShake, m_DamageDisable);
					FIRE::ADD_OWNED_EXPLOSION(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, m_Explosion_Iterator, m_Damage, m_Audiable, m_Invisible, m_CameraShake);
				}
			}
		}
	}



	void PickupGun(bool toggle, std::uint32_t Model, std::uint32_t Pickup, int Value)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				STREAMING::REQUEST_MODEL(Model);
				Player playerPed = PLAYER::PLAYER_PED_ID();
				if (PAD::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000))
				{
					g_CallbackScript->AddCallback<ModelCallback>(Model, [=] {
						NativeVector3 ShootCoord;
						WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &ShootCoord);
						OBJECT::CREATE_AMBIENT_PICKUP(Pickup, ShootCoord.x, ShootCoord.y, ShootCoord.z + 0.5f, 0, Value, Model, FALSE, TRUE);
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model);
					});
				}
			}
		}
	}

	void PaintGun(bool toggle)
	{
		if (toggle)
		{
			NativeVector3 Coords;

			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &Coords))
			{
				positions.push_back(Coords);
			}

			for (auto pos : positions)
			{
				GRAPHICS::DRAW_LIGHT_WITH_RANGE(pos.x, pos.y, pos.z, g_RedPaint, g_GreenPaint, g_BluePaint, m_Range, m_Intensity);
			}
		}
	}

	void TriggerBot(bool enable)
	{
		if (enable)
		{
			Entity PlayerTarget;
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &PlayerTarget))
			{
				if (ENTITY::IS_ENTITY_A_PED(PlayerTarget) && !ENTITY::IS_ENTITY_DEAD(PlayerTarget, 0) && ENTITY::GET_ENTITY_ALPHA(PlayerTarget) == 255)
				{
				//	NativeVector3 Head = PED::GET_PED_BONE_COORDS(PlayerTarget, SKEL_Head, 0.1f, 0.0f, 0.0f);
				//	PED::SET_PED_SHOOTS_AT_COORD(PLAYER::PLAYER_PED_ID(), Head.x, Head.y, Head.z, true);
				}
			}
		}
	}

	void Magnet(bool toggle)
	{
		if (toggle)
		{
			static float zoom{10.f};

			if (GetAsyncKeyState(VK_RBUTTON))
			{
				if (zoom < 40.f)
				{
					if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 261))
					{
						zoom += 2.f;
					}
				}
				if (PAD::IS_DISABLED_CONTROL_PRESSED(2, 262))
				{
					zoom -= 2.f;

				}
				const int pedElements = 10;
				const int pedArrSize = pedElements * 2 + 2;
				int ped[pedArrSize];
				ped[0] = pedElements;
				int pedcount = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), ped, -1);

				const int numElements = 10;
				const int arrSize = numElements * 2 + 2;
				int veh[arrSize];
				veh[0] = numElements;
				int count = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), veh);

				

				if (veh != 0 | ped != 0)
				{
					for (int i = 0; i < count; i++)
					{
						int ofsettedID = i * 2 + 2;
						if (ENTITY::IS_ENTITY_A_PED(veh[ofsettedID]) && PED::IS_PED_IN_ANY_VEHICLE(veh[ofsettedID], false))
						{
							veh[ofsettedID] = PED::GET_VEHICLE_PED_IS_IN(veh[ofsettedID], false);
						}

						NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
						NativeVector3 dir = g_Utility->RotationToDirectionV3(rot);
						NativeVector3 pos = g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(dir, zoom));
						NativeVector3 coords = ENTITY::GET_ENTITY_COORDS(veh[ofsettedID], 0);

						GRAPHICS::_DRAW_SPHERE(pos.x, pos.y, pos.z, 4.f, g_UiManager->m_OptionSelectedBackgroundColor.r, g_UiManager->m_OptionSelectedBackgroundColor.g, g_UiManager->m_OptionSelectedBackgroundColor.b, 0.5f);

						RequestControlOfEnt(veh[ofsettedID]);
						RequestControlOfEnt(ped[ofsettedID]);

						float getaimcoorsX = GravityGunGoto(pos.x, coords.x);
						float getaimcoorsY = GravityGunGoto(pos.y, coords.y);
						float getaimcoorsZ = GravityGunGoto(pos.z, coords.z);

						ENTITY::SET_ENTITY_VELOCITY(ped[ofsettedID], getaimcoorsX * 2.f, getaimcoorsY * 2.f, getaimcoorsZ * 2.f);
						ENTITY::SET_ENTITY_VELOCITY(veh[ofsettedID], getaimcoorsX * 2.f, getaimcoorsY * 2.f, getaimcoorsZ * 2.f);
					}
				}
			}
		}
	}

	void Crosshair()
	{
		auto io = ImGui::GetIO();
		ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiCond_Always);
		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin("###cross", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
		switch (_CrossStyle)
		{
		case 0:
			ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(io.DisplaySize.x * 0.5f - crosssize, io.DisplaySize.y * 0.5f), ImVec2(io.DisplaySize.x * 0.5f + crosssize, io.DisplaySize.y * 0.5f), ImGui::GetColorU32(ImVec4(redcross / 255.f, greencross / 255.f, bluecross / 255.f, 1.f)));
			ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f - crosssize), ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f + crosssize), ImGui::GetColorU32(ImVec4(redcross / 255.f, greencross / 255.f, bluecross / 255.f, 1.f)));
			break;
		case 1:
			ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(io.DisplaySize.x * 0.5f - crosssize, io.DisplaySize.y * 0.5f + crosssize), ImVec2(io.DisplaySize.x * 0.5f + crosssize, io.DisplaySize.y * 0.5f - crosssize), ImGui::GetColorU32(ImVec4(redcross / 255.f, greencross / 255.f, bluecross / 255.f, 1.f)));
			ImGui::GetCurrentWindow()->DrawList->AddLine(ImVec2(io.DisplaySize.x * 0.5f + crosssize, io.DisplaySize.y * 0.5f + crosssize), ImVec2(io.DisplaySize.x * 0.5f - crosssize, io.DisplaySize.y * 0.5f - crosssize), ImGui::GetColorU32(ImVec4(redcross / 255.f, greencross / 255.f, bluecross / 255.f, 1.f)));
			break;
		}
		ImGui::End();
	}

	void EnityGunVehicle(bool toggle, const char* SelectedVehicle, float SpawnDistance, float LaunchSpeed)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				DWORD model = MISC::GET_HASH_KEY(SelectedVehicle);
				NativeVector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
				NativeVector3 dir = g_Utility->RotationToDirectionV3(rot);
				NativeVector3 CamPosition = CAM::GET_GAMEPLAY_CAM_COORD();
				NativeVector3 PlayerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				float spawnDistance = g_Utility->GetDistanceFloat(CamPosition, PlayerPosition);
				spawnDistance += SpawnDistance;
				NativeVector3 spawnPosition = g_Utility->AddV3(CamPosition, g_Utility->MultiplyV3(dir, spawnDistance));

				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()))
				{
					if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
					{
						NativeVector3 playerOffset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0, 5, 0);
						if (PED::IS_PED_ON_FOOT(PLAYER::PLAYER_PED_ID()))
						{
							STREAMING::REQUEST_MODEL(model);
							g_CallbackScript->AddCallback<ModelCallback>(model, [=] {
								Vehicle veh = VEHICLE::CREATE_VEHICLE(model, spawnPosition.x, spawnPosition.y, spawnPosition.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), NETWORK::NETWORK_IS_IN_SESSION(), 1, 0);
								VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, LaunchSpeed);
								STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
								ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
							});
						}
					}
				}
			}
		}
	}

	void PropellantGun(bool toggle, float SpawnDistance, std::uint32_t Model, float Speed)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				float startDistance = g_Utility->GetDistanceFloat(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
				float endDistance = g_Utility->GetDistanceFloat(CAM::GET_GAMEPLAY_CAM_COORD(), ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true));
				startDistance += SpawnDistance;
				endDistance += 1000.0;
				if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
				{
					if (!WEAPON::HAS_WEAPON_ASSET_LOADED(Model))
					{
						WEAPON::REQUEST_WEAPON_ASSET(Model, 31, false);
					}
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).x, g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).y, g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), startDistance)).z, g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).x, g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).y, g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), endDistance)).z, Speed, 1, Model, PLAYER::PLAYER_PED_ID(), 1, 0, -1.0);
				}
			}
		}
	}


	void EntityGunObject(bool toggle, const char* SelectedObject, float SpawnDistance, float LaunchSpeed)
	{
		if (toggle)
		{
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				NativeVector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
				NativeVector3 Dir = g_Utility->RotationToDirectionV3(Rot);
				NativeVector3 CPosition = CAM::GET_GAMEPLAY_CAM_COORD();
				NativeVector3 PlayerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				float spawnDistance = g_Utility->GetDistanceFloat(CPosition, PlayerPosition); spawnDistance += SpawnDistance;
				NativeVector3 SPosition = g_Utility->AddV3(CPosition, g_Utility->MultiplyV3(Dir, spawnDistance));
				DWORD Model = MISC::GET_HASH_KEY(SelectedObject);
				Object ObJect = OBJECT::CREATE_OBJECT(Model, SPosition.x, SPosition.y, SPosition.z, 1, 1, 1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model);
				if (ENTITY::DOES_ENTITY_EXIST(ObJect))
				{
					ENTITY::SET_ENTITY_RECORDS_COLLISIONS(ObJect, true);
					ENTITY::APPLY_FORCE_TO_ENTITY(ObJect, 1, Dir.x * LaunchSpeed, Dir.y * LaunchSpeed, Dir.z * LaunchSpeed, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
				}
			}
		}
	}

	void Attachments()
	{
		switch (_wepattach)
		{
		case 0:
			for (int z = 0; z < sizeof(AllWeapons) / sizeof(AllWeapons[0]); z++)
				for (int i = 0; i < sizeof(AllAttachments) / sizeof(AllAttachments[0]); i++)
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY((char*)AllWeapons[z]), MISC::GET_HASH_KEY((char*)AllAttachments[i]));
			for (int c = 0; c < sizeof(AllWeapons) / sizeof(AllWeapons[0]); c++)
				WEAPON::ADD_AMMO_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY((char*)AllWeapons[c]), 9999);
			break;
		case 1:
			for (int z = 0; z < sizeof(AllWeapons) / sizeof(AllWeapons[0]); z++)
				for (int i = 0; i < sizeof(AllAttachments) / sizeof(AllAttachments[0]); i++)
					WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY((char*)AllWeapons[z]), MISC::GET_HASH_KEY((char*)AllAttachments[i]));
			for (int c = 0; c < sizeof(AllWeapons) / sizeof(AllWeapons[0]); c++)
				WEAPON::ADD_AMMO_TO_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY((char*)AllWeapons[c]), 9999);
		}
	}

	void Flygun(bool toggle)
	{
		if (toggle)
		{
			NativeVector3 impact;
			NativeVector3 test = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
			static NativeVector3 shotfly;
			WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::PLAYER_PED_ID(), MISC::GET_HASH_KEY("GADGET_PARACHUTE"));
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &impact))
			{
				shotfly = impact;
			}
			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
			{
				NativeVector3 entity_velocity;
				entity_velocity.x = (shotfly.x - test.x) * 3.0f;
				entity_velocity.y = (shotfly.y - test.y) * 3.0f;
				entity_velocity.z = (shotfly.z - test.z) * 3.0f;
				TASK::TASK_SKY_DIVE(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::SET_ENTITY_VELOCITY(PLAYER::PLAYER_PED_ID(), entity_velocity.x, entity_velocity.y, entity_velocity.z);

			}
			float distance = MISC::GET_DISTANCE_BETWEEN_COORDS(test.x, test.y, test.z, shotfly.x, shotfly.y, shotfly.z, 0);
			if (distance < 1.0f) {
				BRAIN::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
				TASK::CLEAR_PED_SECONDARY_TASK(PLAYER::PLAYER_PED_ID());
			}
		}
	}
	bool attached_first;
	Entity rope_ent0;

	void RopeGun(bool toggle)
	{
		if (toggle)
		{


			static Object first_rope;
			auto camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
			auto farCoords = g_Utility->AddV3(CAM::GET_GAMEPLAY_CAM_COORD(), g_Utility->MultiplyV3(g_Utility->RotationToDirectionV3(CAM::GET_GAMEPLAY_CAM_ROT(0)), 100.f));
			auto ray = SHAPETEST::_START_SHAPE_TEST_RAY(camCoords.x, camCoords.y, camCoords.z, farCoords.x, farCoords.y, farCoords.z, -1, PLAYER::PLAYER_PED_ID(), 7);
			int hit; NativeVector3 endCoords; NativeVector3 surfaceNormal; Entity ent = 0;
			SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &hit, &endCoords, &surfaceNormal, &ent);

			if (PAD::IS_CONTROL_PRESSED(2, 25) || IsKeyPressed(VK_RBUTTON))
			{
				if (ENTITY::DOES_ENTITY_EXIST(ent) && (ENTITY::IS_ENTITY_A_PED(ent) || ENTITY::IS_ENTITY_A_VEHICLE(ent) || ENTITY::IS_ENTITY_AN_OBJECT(ent)))
				{
					if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
					{
						PHYSICS::ROPE_LOAD_TEXTURES();
						auto pweapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
						auto pwep_coord = ENTITY::GET_ENTITY_COORDS(pweapon, 1);
						if (!attached_first)
						{
							first_rope = PHYSICS::ADD_ROPE(pwep_coord.x, pwep_coord.y, pwep_coord.z, 0, 0, 0, g_Utility->GetDistanceFloat(ENTITY::GET_ENTITY_COORDS(ent, 1), pwep_coord), 1, 300, 0.5f, 0.5f, false, true, true, 1.0f, false, 0);
							NativeVector3 c0 = pwep_coord;
							NativeVector3 c1 = ENTITY::GET_ENTITY_COORDS(ent, 1);

							PHYSICS::ATTACH_ENTITIES_TO_ROPE(first_rope, pweapon, ent, c0.x, c0.y, c0.z, c1.x, c1.y, c1.z, g_Utility->GetDistanceFloat(ENTITY::GET_ENTITY_COORDS(ent, 1), pwep_coord) + 40.f, 0, 0, NULL, NULL);
							PHYSICS::ACTIVATE_PHYSICS(first_rope);

							rope_ent0 = ent;
							attached_first = true;
						}
						else
						{
							PHYSICS::DELETE_ROPE(&first_rope);
							NativeVector3 c0 = ENTITY::GET_ENTITY_COORDS(rope_ent0, 1);
							NativeVector3 c1 = ENTITY::GET_ENTITY_COORDS(ent, 1);

							first_rope = PHYSICS::ADD_ROPE(pwep_coord.x, pwep_coord.y, pwep_coord.z, 0, 0, 0, g_Utility->GetDistanceFloat(ENTITY::GET_ENTITY_COORDS(rope_ent0, 1), ENTITY::GET_ENTITY_COORDS(ent, 1)), 1, 300, 0.5f, 0.5f, false, true, true, 1.0f, false, 0);
							PHYSICS::ACTIVATE_PHYSICS(first_rope);
							PHYSICS::ATTACH_ENTITIES_TO_ROPE(first_rope, rope_ent0, ent, c0.x, c0.y, c0.z, c1.x, c1.y, c1.z, g_Utility->GetDistanceFloat(ENTITY::GET_ENTITY_COORDS(rope_ent0, 1), ENTITY::GET_ENTITY_COORDS(ent, 1)), 0, 0, NULL, NULL);

							first_rope = NULL;
							attached_first = false;
						}
					}
				}
			}
			else
			{
				PHYSICS::DELETE_ROPE(&first_rope); attached_first = false;
			}
		}
	}

	void WeaponUpdateLoop()
	{
		Revivegun(m_ReviveGun);
		InfiniteAmmo(m_InfiniteAmmo);
		ExplosiveAmmo(m_ExplosiveAmmo);
		RapidFire(m_RapidFire);
		OneHitAmmo(m_OneHitAmmo);
		if(m_AimBot)
			AimBot(m_AimBot);
		ForceGun(m_ForceGun);
		AirstrikeGun(m_AirstrikeGun);
		TeleportGun(m_TeleportGun);
		DeleteGun(m_DeleteGun);
		LaserSight(m_LaserSight);
		NoRecoil(m_NoRecoil);//
		RainbowCamo(m_RainbowCamo);
		MoneyGun(m_MoneyGun);
		RPGun(m_RPGun);
		PaintGun(m_EnablePaint);
		FlamingAmmo(m_FlamingAmmo);
		Magnet(m_Magnet);
		GravityBug(g_GravityGun);
		Carnado(g_Carnado);
		YoinkGun(g_YoinkGun);
		Flygun(g_FlyGun);
		ExplosiveAmmoFunction(m_EnableExplosives);
		EnityGunVehicle(m_EnableEntityGunVehicle, m_EntityVehicle[m_EntityVehicleIterator], m_VehicleSpawnDistance, m_VehicleLaunchSpeed);
		EntityGunObject(m_EnableEntityGunObject, m_EntityObject[m_EntityObjectIterator], m_ObjectSpawnDistance, m_ObjectLaunchSpeed);
		PickupGun(m_EnableEntityGunPickups, m_HashModels[m_EntityPickupModelIterator], m_HashPickups[m_EntityPickupModelIterator], m_PickupValue);
		PropellantGun(m_EnableEntityPropellant, m_PropellantSpawnDistance, m_PropellantHashes[m_EntityPropellantIterator], m_ObjectPropellantSpeed);
		RopeGun(g_Rope);
	}
}