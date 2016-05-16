#ifndef CHARACTER_SLOT_OBJECT_CHANGE_HPP
#define CHARACTER_SLOT_OBJECT_CHANGE_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_CHARACTER_SLOT_OBJECT_CHANGE ('e')

template <> class Packet <PACKET_CHARACTER_SLOT_OBJECT_CHANGE>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
