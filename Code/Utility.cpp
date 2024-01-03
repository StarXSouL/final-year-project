#include "Common.hpp"
#include "ImGui/imgui.h"
#include "Translation.hpp"

using namespace Big;

NativeVector3 Utilityy::RotationToDirectionV3(NativeVector3 rot) {
	NativeVector3 dir;
	float radiansZ = rot.z * 0.0174532924f;
	float radiansX = rot.x * 0.0174532924f;
	float num = abs((float)cos((double)radiansX));
	dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
	dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
	dir.z = (float)sin((double)radiansX);
	return dir;
}

NativeVector3 Utilityy::AddV3(NativeVector3 vectorA, NativeVector3 vectorB) {
	NativeVector3 result;
	result.x = vectorA.x;
	result.y = vectorA.y;
	result.z = vectorA.z;
	result.x += vectorB.x;
	result.y += vectorB.y;
	result.z += vectorB.z;
	return result;
}

NativeVector3 Utilityy::MultiplyV3(NativeVector3 vector, float x) {
	NativeVector3 result;
	result.x = vector.x;
	result.y = vector.y;
	result.z = vector.z;
	result.x *= x;
	result.y *= x;
	result.z *= x;
	return result;
}

float Utilityy::GetDistanceFloat(NativeVector3 pointA, NativeVector3 pointB) {
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

float Utilityy::GetVectorLengthFloat(NativeVector3* vector) {
	double x = (double)vector->x;
	double y = (double)vector->y;
	double z = (double)vector->z;
	return(float)sqrt(x * x + y * y + z * z);
}


NativeVector3 Utilityy::GetBlipIcon()
{
	static NativeVector3 zero;
	NativeVector3 coords;

	bool blipFound = false;
	// search for marker blip
	int blipIterator = HUD::_GET_BLIP_INFO_ID_ITERATOR();
	for (Blip i = HUD::GET_FIRST_BLIP_INFO_ID(blipIterator); HUD::DOES_BLIP_EXIST(i) != 0; i = HUD::GET_NEXT_BLIP_INFO_ID(blipIterator))
	{
		if (HUD::GET_BLIP_INFO_ID_TYPE(i) == 4)
		{
			coords = HUD::GET_BLIP_INFO_ID_COORD(i);
			blipFound = true;
			break;
		}
	}
	if (blipFound)
	{
		return coords;
	}

	return zero;
}

void Utilityy::WriteFlameFlag(uint32_t Flag)
{
	
	uint32_t CurrentValue = Memory::get_value<uint32_t>({ 0x8, 0x10A8, 0x270 });
	Memory::set_value<uint32_t>({ 0x8, 0x10A8, 0x270 }, CurrentValue |= Flag);
	
}

void Utilityy::RemoveFlameFlag(uint32_t Flag)
{
	
	uint32_t CurrentValue = Memory::get_value<uint32_t>({ 0x8, 0x10A8, 0x270 });
	Memory::set_value<uint32_t>({ 0x8, 0x10A8, 0x270 }, CurrentValue &= ~(1 << Flag));
}
	
void notifyMap(int notifyColor, const char* fmt, ...)
{
	char buf[2048] = { 0 };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);

	char buff2[2048] = { 0 };
	sprintf_s(buff2, "%s", buf);

	HUD::SET_TEXT_OUTLINE();
	HUD::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
	HUD::_SET_NOTIFICATION_BACKGROUND_COLOR(notifyColor);
	HUD::_DRAW_NOTIFICATION(FALSE, FALSE);
}	void notifyMap(std::string str) { notifyMap(&str[0]); }

void ApplyForceToEntity(Entity e, float x, float y, float z)
{
	if (e != PLAYER::PLAYER_PED_ID() && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(e) == FALSE)
	{
		RequestControlOfEnt(e);
	}

	ENTITY::APPLY_FORCE_TO_ENTITY(e, 1, x, y, z, 0, 0, 0, 0, 1, 1, 1, 0, 1);

}

void RequestControlOfid(Entity netid)
{
	int tick = 0;

	while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
		tick++;
	}
}

void WelcomeScreen(bool enable)
{
	if (enable)
	{
		int scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("mp_big_message_freemode");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(scaleform, "SHOW_SHARD_WASTED_MP_MESSAGE");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING("~r~OverKill");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING("Open Key: F8");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(5);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(scaleform, 255, 255, 255, 255, 0);
	}
}

void low_graphics(bool toggle)
{
	if (toggle)
	{
		NativeVector3 me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		STREAMING::_SET_FOCUS_AREA(me.x, me.y, me.z - 2000, me.x, me.y, me.z - 2000);
	}
}

void RequestControlOfEnt(Entity entity)
{
	int tick = 0;
	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		tick++;
	}
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
		RequestControlOfid(netID);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
	}
}

void UtilityUpdateLoop()
{
	WelcomeScreen(g_Utility->openedYet);
	low_graphics(g_Utility->g_low_graphics);
}

script_global::script_global(std::size_t index) :
	m_index(index)
{
}

script_global script_global::at(std::ptrdiff_t index)
{
	return script_global(m_index + index);
}

script_global script_global::at(std::ptrdiff_t index, std::size_t size)
{
	return script_global(m_index + 1 + (index * size));
}

void* script_global::get()
{
	return g_GameFunctions->m_ScriptGlobals[m_index >> 0x12 & 0x3F] + (m_index & 0x3FFFF);
}