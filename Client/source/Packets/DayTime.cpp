#include "DayTime.hpp"

#include "Master.hpp"

void Packet <PACKET_DAY_TIME>::onReceive(const ENetEvent &event)
{
    int dayTime = 0;
    sscanf((char*)event.packet->data, "%*c %d", &dayTime);
    _assert(dayTime >= 0, "Day time is negative in processPacket_dayTime.");
    if(abs((int)Master::getInstance().Weather.dayTimeInMinutes-dayTime) > 2) {
        Master::getInstance().Weather.dayTimeInMinutes = dayTime;
    }
}
