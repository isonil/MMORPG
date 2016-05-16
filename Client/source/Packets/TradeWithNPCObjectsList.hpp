#ifndef TRADE_WITH_NPC_OBJECTS_LIST_HPP
#define TRADE_WITH_NPC_OBJECTS_LIST_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_TRADE_WITH_NPC_OBJECTS_LIST ('m')

template <> class Packet <PACKET_TRADE_WITH_NPC_OBJECTS_LIST>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
