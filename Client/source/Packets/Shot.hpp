#ifndef SHOT_HPP
#define SHOT_HPP

#include <enet/enet.h>
#include <string>
#include "Packet.hpp"

#define PACKET_SHOT ('s')

template <> class Packet <PACKET_SHOT>
{
    public:
        static void onReceive(const ENetEvent &event);
        static std::string construct(float dir);
};

#endif
