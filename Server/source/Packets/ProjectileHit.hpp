#ifndef PROJECTILE_HIT_HPP
#define PROJECTILE_HIT_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_PROJECTILE_HIT ('h')

template <> class Packet <PACKET_PROJECTILE_HIT>
{
    public:
        static std::string construct(int hitType, int x, int y, int projectileID);
};

#endif
