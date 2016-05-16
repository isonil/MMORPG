#ifndef CHARACTER_LOST_SIGHT_HPP
#define CHARACTER_LOST_SIGHT_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_CHARACTER_LOST_SIGHT ('x')

template <> class Packet <PACKET_CHARACTER_LOST_SIGHT>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
