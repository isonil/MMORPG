#include "GrenadeLauncherShot.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_GRENADE_LAUNCHER_SHOT>::onReceive(const ENetEvent &event)
{
    char characterSet = 0;
    int ownerID = 0, x = 0, y = 0, dir = 0, projectileID = 0, weaponObjectType = -1;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d %d %d %d", &characterSet, &ownerID, &x, &y, &dir, &projectileID, &weaponObjectType);

    _assert(Master::getInstance().isValidCharacterSet(characterSet), "Invalid character set in processPacket_grenadeLauncherShot.");
    _assert(ownerID >= 0, "Character ID is negative in processPacket_grenadeLauncherShot.");
    _assert(projectileID >= 0, "Projectile ID is negative in processPacket_grenadeLauncherShot.");

    _assert(weaponObjectType < (int)Master::getInstance().ObjectType.size(),
            "Weapon object type out of bounds in processPacket_grenadeLauncherShot.");
    //playPositionalSound(grenadeLauncherShotSample, Player[playerCharacterID].x, Player[playerCharacterID].y, x, y);
    // ALLS
    Master::getInstance().Projectile.push_back(ProjectileClass(characterSet,
                                         ownerID,
                                         x, y,
                                         dir/100.f,
                                         projectileID,
                                         PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE));
    for(int i=0; i<6; ++i) {
        Master::getInstance().Particle.push_back(ParticleClass(x+rand()%7-3,
                                         y+rand()%7-3,
                                         (rand()%360)/180.f*M_PI,
                                         0.4f, 4.f,
                                         (rand()%360)/180.f*M_PI,
                                         0, sf::Color(20,20,20), 255.f, true));
    }

    if(characterSet == CHARACTER_PLAYER && ownerID == playerCharacterID) {
        Master::getInstance().viewOffsetX = -cos(dir/100.f)*(7+rand()%3);
        Master::getInstance().viewOffsetY = -sin(dir/100.f)*(7+rand()%3);
        Master::getInstance().timeout_grenadeLauncherShot = globalTime+3000;
    }
}

std::string Packet <PACKET_GRENADE_LAUNCHER_SHOT>::construct(float atX, float atY)
{
    std::ostringstream oss;
    oss << PACKET_GRENADE_LAUNCHER_SHOT << ' ' << (int)atX << ' ' << (int)atY;
    return oss.str();
}
