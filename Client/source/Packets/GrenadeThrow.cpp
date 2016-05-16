#include "GrenadeThrow.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_GRENADE_THROW>::onReceive(const ENetEvent &event)
{
    char characterSet = 0;
    int ownerID = 0, x = 0, y = 0, dir = 0, projectileID = 0, target_x = 0, target_y = 0;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d %d %d %d %d", &characterSet, &ownerID, &x, &y, &dir, &projectileID, &target_x, &target_y);

    _assert(Master::getInstance().isValidCharacterSet(characterSet), "Invalid character set in processPacket_grenadeThrow.");
    _assert(ownerID >= 0, "Character ID is negative in processPacket_grenadeThrow.");
    _assert(projectileID >= 0, "Projectile ID is negative in processPacket_grenadeThrow.");

    //playPositionalSound(grenadeThrowSample, Player[playerCharacterID].x, Player[playerCharacterID].y, x, y);
    // ALLS
    Master::getInstance().Projectile.push_back(ProjectileClass(characterSet,
                                         ownerID,
                                         x, y,
                                         dir/100.f,
                                         projectileID,
                                         PROJECTILE_TYPE_GRENADE));
    Master::getInstance().Projectile.back().grenadeRotation = (rand()%360)*M_PI/180.f;
    Master::getInstance().Projectile.back().grenadeThrowDistance = Master::getInstance().getDistance(x,y,target_x,target_y);
    Master::getInstance().Projectile.back().timeout_grenadeExplode = globalTime+3000.0;

    if(characterSet == CHARACTER_PLAYER && ownerID == playerCharacterID) {
        Master::getInstance().viewOffsetX = -cos(dir/100.f)*(3+rand()%3);
        Master::getInstance().viewOffsetY = -sin(dir/100.f)*(3+rand()%3);
        Master::getInstance().timeout_grenadeThrow = globalTime+3000.0;
    }
}

std::string Packet <PACKET_GRENADE_THROW>::construct(float atX, float atY)
{
    std::ostringstream oss;
    oss << PACKET_GRENADE_THROW << ' ' << (int)atX << ' ' << (int)atY;
    return oss.str();
}
