#include "GrenadeThrow.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_GRENADE_THROW>::onReceive(const ENetEvent &event)
{
    int x = 0, y = 0;
    sscanf((char*)event.packet->data, "%*c %d %d", &x, &y);

    bool throwAllowed = true;
    if(fabs(x-Master::getInstance().Player[(int)event.peer->data].x) > PLAYER_TILES_VIEW_DISTANCE*TILE_SIZE ||
       fabs(y-Master::getInstance().Player[(int)event.peer->data].y) > PLAYER_TILES_VIEW_DISTANCE*TILE_SIZE) throwAllowed = false;
    else if(globalTime >= Master::getInstance().Player[(int)event.peer->data].timeout_grenadeThrow) {
        //check ammo
        /*
        shotAllowed=false;
        for() {
            for() {
                if(ammo) {
                    ammo remove
                    shotAllowed=true;
                    break;
            }
            if(shotAllowed) break;
        }
        */
    }
    else throwAllowed = false;

    if(throwAllowed) {
        Master::getInstance().Player[(int)event.peer->data].timeout_grenadeThrow = globalTime+3000;
        Master::getInstance().characterThrowGrenade(M.Player[(int)event.peer->data], CHARACTER_PLAYER, (int)event.peer->data, x, y);
    }
}

std::string Packet <PACKET_GRENADE_THROW>::construct(char characterSet, int characterID, int x, int y, int dir, int projectileID, int target_x, int target_y)
{
    std::ostringstream oss;
    oss << PACKET_GRENADE_THROW << ' '
        << characterSet << ' '
        << characterID << ' '
        << x << ' '
        << y << ' '
        << dir << ' '
        << projectileID << ' '
        << target_x << ' '
        << target_y;
    return oss.str();
}
