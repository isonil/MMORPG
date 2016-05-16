#include "Weather.hpp"

#include "Master.hpp"

void Packet <PACKET_WEATHER>::onReceive(const ENetEvent &event)
{
    int rainType = RAIN_TYPE_NONE, snowType = SNOW_TYPE_NONE, stormType = STORM_TYPE_NONE, fogType = FOG_TYPE_NONE;
    sscanf((char*)event.packet->data, "%*c %d %d %d %d", &rainType, &snowType, &stormType, &fogType);

    _assert(rainType == RAIN_TYPE_NONE || rainType == RAIN_TYPE_SMALL ||
            rainType == RAIN_TYPE_MEDIUM || rainType == RAIN_TYPE_HEAVY,
            "Unknown rain type in processPacket_weather.");
    _assert(snowType == SNOW_TYPE_NONE || snowType == SNOW_TYPE_SMALL ||
            snowType == SNOW_TYPE_MEDIUM || snowType == SNOW_TYPE_HEAVY,
            "Unknown snow type in processPacket_weather.");
    _assert(stormType == STORM_TYPE_NONE || stormType == STORM_TYPE_SMALL ||
            stormType == STORM_TYPE_MEDIUM || stormType == STORM_TYPE_HEAVY,
            "Unknown storm type in processPacket_weather.");
    _assert(fogType == FOG_TYPE_NONE || fogType == FOG_TYPE_SMALL ||
            fogType == FOG_TYPE_MEDIUM || fogType == FOG_TYPE_HEAVY,
            "Unknown fog type in processPacket_weather.");

    if(stormType != STORM_TYPE_NONE && Master::getInstance().Weather.stormType == STORM_TYPE_NONE) {
        Master::getInstance().Weather.timeout_lightning = globalTime+2000.0+rand()%10000;
    }
    Master::getInstance().Weather.rainType = rainType;
    Master::getInstance().Weather.snowType = snowType;
    Master::getInstance().Weather.stormType = stormType;
    Master::getInstance().Weather.fogType = fogType;
}
