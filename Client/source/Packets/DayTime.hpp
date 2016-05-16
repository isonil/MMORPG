#ifndef DAY_TIME_HPP
#define DAY_TIME_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_DAY_TIME ('d')

template <> class Packet <PACKET_DAY_TIME>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
