#ifndef GRENADE_LAUNCHER_SHOT_HPP
#define GRENADE_LAUNCHER_SHOT_HPP

#include <enet/enet.h>
#include <string>
#include "Packet.hpp"

#define PACKET_GRENADE_LAUNCHER_SHOT ('n')

template <> class Packet <PACKET_GRENADE_LAUNCHER_SHOT>
{
    public:
        static void onReceive(const ENetEvent &event);
        static std::string construct(float atX, float atY);
};

#endif
