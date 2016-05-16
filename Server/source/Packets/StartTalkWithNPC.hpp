#ifndef START_TALK_WITH_NPC_HPP
#define START_TALK_WITH_NPC_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_START_TALK_WITH_NPC ('f')

template <> class Packet <PACKET_START_TALK_WITH_NPC>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
