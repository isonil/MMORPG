#ifndef PROJECTILE_HIT_HPP
#define PROJECTILE_HIT_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_PROJECTILE_HIT ('h')

template <> class Packet <PACKET_PROJECTILE_HIT>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
