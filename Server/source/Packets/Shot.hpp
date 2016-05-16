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
        static std::string construct(char characterSet, int characterID, int x, int y, int dir, int projectileID, int weaponObjectType);
};

#endif
