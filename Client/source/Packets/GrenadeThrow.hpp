#ifndef GRENADE_THROW_HPP
#define GRENADE_THROW_HPP

#include <enet/enet.h>
#include <string>
#include "Packet.hpp"

#define PACKET_GRENADE_THROW ('a')

template <> class Packet <PACKET_GRENADE_THROW>
{
    public:
        static void onReceive(const ENetEvent &event);
        static std::string construct(float atX, float atY);
};

#endif
