#ifndef OBJECT_CHANGE_ON_GROUND_HPP
#define OBJECT_CHANGE_ON_GROUND_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_OBJECT_CHANGE_ON_GROUND ('o')

template <> class Packet <PACKET_OBJECT_CHANGE_ON_GROUND>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
