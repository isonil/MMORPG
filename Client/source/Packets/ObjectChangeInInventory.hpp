#ifndef OBJECT_CHANGE_IN_INVENTORY_HPP
#define OBJECT_CHANGE_IN_INVENTORY_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_OBJECT_CHANGE_IN_INVENTORY ('q')

template <> class Packet <PACKET_OBJECT_CHANGE_IN_INVENTORY>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
