#include "GrenadeLauncherShot.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_GRENADE_LAUNCHER_SHOT>::onReceive(const ENetEvent &event)
{
    int x = 0, y = 0;
    sscanf((char*)event.packet->data, "%*c %d %d", &x, &y);

    ObjectClass *weapon = &M.Player[(int)event.peer->data].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX];
    _assert_return(weapon->type < (int)M.ObjectType.size(), M.Player[(int)event.peer->data].name.c_str(), (int)event.peer->data,
                   "Weapon object type out of bounds in processPacket_grenadeLauncherShot.");

    bool shotAllowed = true;
    if(weapon->type < 0) shotAllowed = false;
    else if(M.ObjectType[weapon->type].baseType != OBJECT_BASE_TYPE_WEAPON) shotAllowed = false;
    else if(weapon->param[OBJECT_PARAM_ADDON_3] != OBJECT_ID_GRENADE_LAUNCHER) shotAllowed = false;
    else if(fabs(x-Master::getInstance().Player[(int)event.peer->data].x) > PLAYER_TILES_VIEW_DISTANCE*TILE_SIZE ||
            fabs(y-Master::getInstance().Player[(int)event.peer->data].y) > PLAYER_TILES_VIEW_DISTANCE*TILE_SIZE) shotAllowed = false;
    else if(globalTime >= M.Player[(int)event.peer->data].timeout_grenadeLauncherShot) {
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
    else shotAllowed = false;

    if(shotAllowed) {
        Master::getInstance().Player[(int)event.peer->data].timeout_grenadeLauncherShot = globalTime+3000;
        Master::getInstance().characterShootGrenadeLauncher(M.Player[(int)event.peer->data], CHARACTER_PLAYER, (int)event.peer->data, x, y);
    }
}

std::string Packet <PACKET_GRENADE_LAUNCHER_SHOT>::construct(char characterSet, int characterID, int x, int y, int dir, int projectileID, int weaponObjectType)
{
    std::ostringstream oss;
    oss << PACKET_GRENADE_LAUNCHER_SHOT << ' '
        << characterSet << ' '
        << characterID << ' '
        << x << ' '
        << y << ' '
        << dir << ' '
        << projectileID << ' '
        << weaponObjectType;
    return oss.str();
}
