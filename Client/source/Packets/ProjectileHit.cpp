#include "ProjectileHit.hpp"

#include "Master.hpp"

void Packet <PACKET_PROJECTILE_HIT>::onReceive(const ENetEvent &event)
{
    char hitType = 0;
    int x = 0, y = 0, projectileId = 0;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d", &hitType, &x, &y, &projectileId);

    _assert(hitType == HIT_BLOOD || hitType == HIT_NORMAL ||
            hitType == HIT_EXPLOSION || hitType == HIT_GRENADE_HIT_OBSTACLE,
            "Invalid hit type in processPacket_projectileHit.");
    _assert(projectileId >= 0,"Projectile id is negative in processPacket_projectileHit.");

    for(std::list <ProjectileClass>::iterator it=Master::getInstance().Projectile.begin(); it!=Master::getInstance().Projectile.end();) {
        if(it->id == projectileId) {
            if(hitType == HIT_GRENADE_HIT_OBSTACLE) {
                it->x = x-cos(it->dir)*5.f;
                it->y = y-sin(it->dir)*5.f;
                it->grenadeFlySpeed = 0.f;
            }
            else Master::getInstance().Projectile.erase(it);
            break;
        }
        ++it;
    }
    if(hitType == HIT_BLOOD) {
        for(int i=0; i<5; ++i) {
            Master::getInstance().Particle.push_back(ParticleClass(x+rand()%7-3,
                                             y+rand()%7-3,
                                             (rand()%360)/180.f*M_PI,
                                             7.f, 30.f,
                                             (rand()%360)/180.f*M_PI,
                                             2, sf::Color(50,0,0), 255.f, true));
        }
        //PlayPositionalSound(bulletBloodHitSample,Player[playerCharacterID].x,Player[playerCharacterID].y,x,y);
    }
    else if(hitType == HIT_NORMAL) {
        for(int i=0; i<5; ++i) {
            Master::getInstance().Particle.push_back(ParticleClass(x+rand()%3-1,
                                             y+rand()%3-1,
                                             (rand()%360)/180.f*M_PI,
                                             1.f, 6.5f,
                                             (rand()%360)/180.f*M_PI,
                                             0, sf::Color(20, 20, 20), 255.f, true));
        }
        //PlayPositionalSound(bulletHitSample,Player[playerCharacterID].x,Player[playerCharacterID].y,x,y);
    }
    else if(hitType == HIT_EXPLOSION) {
        for(int i=0; i<30; ++i) {
            Master::getInstance().Particle.push_back(ParticleClass(x+rand()%13-6,
                                             y+rand()%13-6,
                                             (rand()%360)/180.f*M_PI,
                                             0.3f,
                                             5.f+(rand()%80)/100.f,
                                             0.f, 3,
                                             sf::Color(100+rand()%50, 20+rand()%80, 30),
                                             255.f, true));
        }
        for(int i=0; i<150; ++i) {
            Master::getInstance().Particle.push_back(ParticleClass(x+rand()%25-14,
                                             y+rand()%25-14,
                                             (rand()%360)/180.f*M_PI,
                                             0.3f+(rand()%80)/100.f,
                                             5.f+(rand()%80)/100.f,
                                             0.f, 3, sf::Color::Black,
                                             220.f, false));
        }
        for(int i=0; i<150; ++i) {
            Master::getInstance().Particle.push_back(ParticleClass(x+rand()%25-14,
                                             y+rand()%25-14,
                                             (rand()%360)/180.f*M_PI,
                                             0.3f+(rand()%150)/100.f,
                                             5.f+(rand()%80)/100.f,
                                             0.f, 3,
                                             sf::Color(100+rand()%50, 20+rand()%80, 30),
                                             255.f, true));
        }

        CharacterClass *player = Master::getInstance().getPlayer().getCharacter();
        _assert(player != NULL, "Player is NULL.");

        float dir = atan2(y-player->getPosition().y, x-player->getPosition().x);
        float distance = Master::getInstance().getDistance(player->getPosition().x, player->getPosition().y, x, y);
        if(distance > 1200.f) distance = 1200.f;
        Master::getInstance().viewOffsetX = -cos(dir)*(4.f+(1200.f-distance)/45.f);
        Master::getInstance().viewOffsetY = -sin(dir)*(4.f+(1200.f-distance)/45.f);
        //playPositionalSound(explosionSample, Player[playerCharacterID].x, Player[playerCharacterID].y, x, y);
        // ALLS
    }
    else if(hitType == HIT_GRENADE_HIT_OBSTACLE) {
        //playPositionalSound(grenadeBounceSample, Player[playerCharacterID].x, Player[playerCharacterID].y, x, y);
        // ALLS
    }
}
