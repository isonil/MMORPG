#ifndef WEATHER_HPP
#define WEATHER_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_WEATHER ('r')

template <> class Packet <PACKET_WEATHER>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
