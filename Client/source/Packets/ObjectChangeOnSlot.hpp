#ifndef OBJECT_CHANGE_ON_SLOT_HPP
#define OBJECT_CHANGE_ON_SLOT_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_OBJECT_CHANGE_ON_SLOT ('w')

template <> class Packet <PACKET_OBJECT_CHANGE_ON_SLOT>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
