#include "ProjectileHit.hpp"

#include <sstream>

std::string Packet <PACKET_PROJECTILE_HIT>::construct(int hitType, int x, int y, int projectileID)
{
    std::ostringstream oss;
    oss << PACKET_PROJECTILE_HIT << ' ' << hitType << ' ' << x << ' ' << y << ' ' << projectileID;
    return oss.str();
}
