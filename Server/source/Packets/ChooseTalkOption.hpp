#ifndef CHOOSE_TALK_OPTION_HPP
#define CHOOSE_TALK_OPTION_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_CHOOSE_TALK_OPTION ('j')

template <> class Packet <PACKET_CHOOSE_TALK_OPTION>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
