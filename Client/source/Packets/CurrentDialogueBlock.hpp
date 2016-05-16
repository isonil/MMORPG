#ifndef CURRENT_DIALOGUE_BLOCK_HPP
#define CURRENT_DIALOGUE_BLOCK_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_CURRENT_DIALOGUE_BLOCK ('k')

template <> class Packet <PACKET_CURRENT_DIALOGUE_BLOCK>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
