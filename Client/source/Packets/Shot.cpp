#include "Shot.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_SHOT>::onReceive(const ENetEvent &event)
{
    char characterSet = 0;
    int ownerID = 0, x = 0, y = 0, dir = 0, projectileID = 0, weaponObjectType = -1;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d %d %d %d", &characterSet, &ownerID, &x, &y, &dir, &projectileID, &weaponObjectType);

    _assert(Master::getInstance().isValidCharacterSet(characterSet), "Invalid character set in processPacket_shot.");
    _assert(ownerID >= 0, "Character ID is negative in processPacket_shot.");
    _assert(projectileID >= 0, "Projectile ID is negative in processPacket_shot.");

    bool isMissile = false;
    if(weaponObjectType >= 0) {
        _assert(weaponObjectType < (int)Master::getInstance().ObjectType.size(), "Weapon object type out of bounds in processPacket_shot.");
        if(Master::getInstance().ObjectType[weaponObjectType].weaponType == WEAPON_TYPE_ROCKET_LAUNCHER) isMissile = true;
        /*if(ObjectType[weaponObjectType].useSound != NULL) {
            playPositionalSound(ObjectType[weaponObjectType].useSound, Player[playerCharacterID].x, Player[playerCharacterID].y, x, y);
        }*/
        // ALLS
    }

    Master::getInstance().Projectile.push_back(ProjectileClass(characterSet,
                                         ownerID,
                                         x, y,
                                         dir/100.f,
                                         projectileID,
                                         isMissile ? PROJECTILE_TYPE_MISSILE : PROJECTILE_TYPE_BULLET));
    Master::getInstance().Particle.push_back(ParticleClass(x, y, 0.f, 0.f, 60.f, (rand()%360)/180.f*M_PI, 1, sf::Color(120,90,80), 255.f, true));

    for(int i=0; i<2; ++i) {
        Master::getInstance().Particle.push_back(ParticleClass(x+rand()%3-1,
                                         y+rand()%3-1,
                                         (rand()%360)/180.f*M_PI,
                                         0.4f, 4.f,
                                         (rand()%360)/180.f*M_PI,
                                         0, sf::Color(20,20,20), 255.f, true));
    }
    if(isMissile) {
        float missileSmoke_x = x-cos(dir/100.f)*75.f;
        float missileSmoke_y = y-sin(dir/100.f)*75.f;
        for(int i=0; i<6; ++i) {
            Master::getInstance().Particle.push_back(ParticleClass(missileSmoke_x+rand()%13-6,
                                             missileSmoke_y+rand()%13-6,
                                             (rand()%360)/180.f*M_PI,
                                             0.4f, 4.f,
                                             (rand()%360)/180.f*M_PI,
                                             0, sf::Color(20,20,20),255.f, true));
        }
    }

    if(characterSet == CHARACTER_PLAYER && ownerID == playerCharacterID) {
        int offsetX = rand()%2+2;
        int offsetY = rand()%2+2;
        Master::getInstance().viewOffsetX = (rand()%2 == 0 ?(offsetX) : (-offsetX));
        Master::getInstance().viewOffsetY = (rand()%2 == 0 ?(offsetY) : (-offsetY));
        if(weaponObjectType >= 0) {
            if(Master::getInstance().ObjectType[weaponObjectType].weaponType == WEAPON_TYPE_ROCKET_LAUNCHER) {
                Master::getInstance().viewOffsetX = -cos(dir/100.f)*(11+rand()%3);
                Master::getInstance().viewOffsetY = -sin(dir/100.f)*(11+rand()%3);
            }
        }

        CharacterClass *player = Master::getInstance().getPlayer().getCharacter();
        _assert(player != NULL, "Player is NULL.");

        ObjectClass &weapon = player->getObjectOnSlot(CHARACTER_OBJECT_SLOT_WEAPON_INDEX);
        if(weapon.type >= 0 && weapon.type == weaponObjectType) {
            _assert(weapon.type < (int)Master::getInstance().ObjectType.size(),
                    "Player weapon object type out of bounds in processPacket_shot.");
            weapon.timeout_shot = globalTime+Master::getInstance().ObjectType[weapon.type].baseShotDelay;
        }
    }
}

std::string Packet <PACKET_SHOT>::construct(float dir)
{
    std::ostringstream oss;
    oss << PACKET_SHOT << ' ' << int(dir*100.f);
    return oss.str();
}
