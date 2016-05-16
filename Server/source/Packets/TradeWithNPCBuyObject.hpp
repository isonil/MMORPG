#ifndef TRADE_WITH_NPC_BUY_OBJECT_HPP
#define TRADE_WITH_NPC_BUY_OBJECT_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_TRADE_WITH_NPC_BUY_OBJECT ('u')

template <> class Packet <PACKET_TRADE_WITH_NPC_BUY_OBJECT>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
