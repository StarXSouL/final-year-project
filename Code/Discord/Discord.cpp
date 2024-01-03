#include "DiscordHandler.hpp"
#include "Discord_Register.h"
#include "Discord_RPC.h"
#include <chrono>
#include "../Common.hpp"
#pragma comment(lib, "discord-rpc.lib")

using namespace Big;

void discordhandler::Init() {
    DiscordEventHandlers handlers;
    std::memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize("574190796136513536", &handlers, 1, "0");
}

void discordhandler::Tick() {
    static int64_t StartTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    DiscordRichPresence discordPresence;
    std::memset(&discordPresence, 0, sizeof(discordPresence));
    if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
        discordPresence.state = "Playing in online";
        discordPresence.partySize = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
        discordPresence.partyMax = 32;
    } else {
        discordPresence.state = "Playing in story mode";
    }
    if (g_Role == "Staff") {
        discordPresence.details = "Using OverKill [STAFF]";
    } else if (g_Role == "VIP") {
        discordPresence.details = "Using OverKill [VIP]";
    } else if (g_Role == "Standard") {
        discordPresence.details = "Using OverKill [STANDARD]";
    } else if (g_Role == "Basic") {
        discordPresence.details = "Using OverKill [BASIC]";
    } else {
        discordPresence.details = "Using OverKill [GTA V]";
    }
    discordPresence.startTimestamp = StartTime;
    discordPresence.largeImageKey = "logo";
    discordPresence.smallImageKey = "gta";
    discordPresence.smallImageText = "V1.0.2";
    discordPresence.largeImageText = "website";
    discordPresence.instance = 1;

    Discord_UpdatePresence(&discordPresence);
}

void discordhandler::Shutdown() {
    Discord_ClearPresence();
    Discord_Shutdown();
}