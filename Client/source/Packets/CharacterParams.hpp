#ifndef CHARACTER_PARAMS_HPP
#define CHARACTER_PARAMS_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_CHARACTER_PARAMS ('i')

template <> class Packet <PACKET_CHARACTER_PARAMS>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
