#include "Shot.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_SHOT>::onReceive(const ENetEvent &event)
{
    int dir = 0;
    sscanf((char*)event.packet->data, "%*c %d", &dir);
    M.Player[(int)event.peer->data].dir = dir/100.f;

    ObjectClass *weapon = &M.Player[(int)event.peer->data].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX];
    _assert_return(weapon->type < (int)M.ObjectType.size(), M.Player[(int)event.peer->data].name.c_str(), (int)event.peer->data,
                   "Weapon object type out of bounds in processPacket_shot.");
    bool shotAllowed = true;
    if(weapon->type < 0) shotAllowed = false;
    else if(M.ObjectType[weapon->type].baseType != OBJECT_BASE_TYPE_WEAPON) shotAllowed = false;
    else if(globalTime >= weapon->timeout_shot) {
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
        weapon->timeout_shot = globalTime+M.ObjectType[weapon->type].baseShotDelay;
        M.characterShoot(M.Player[(int)event.peer->data], CHARACTER_PLAYER, (int)event.peer->data);
    }
}

std::string Packet <PACKET_SHOT>::construct(char characterSet, int characterID, int x, int y, int dir, int projectileID, int weaponObjectType)
{
    std::ostringstream oss;
    oss << PACKET_SHOT << ' '
        << characterSet << ' '
        << characterID << ' '
        << x << ' '
        << y << ' '
        << dir << ' '
        << projectileID << ' '
        << weaponObjectType;
    return oss.str();
}
