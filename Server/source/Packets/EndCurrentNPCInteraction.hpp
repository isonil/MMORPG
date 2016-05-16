#ifndef END_CURRENT_NPC_INTERACTION_HPP
#define END_CURRENT_NPC_INTERACTION_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_END_CURRENT_NPC_INTERACTION ('z')

template <> class Packet <PACKET_END_CURRENT_NPC_INTERACTION>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
