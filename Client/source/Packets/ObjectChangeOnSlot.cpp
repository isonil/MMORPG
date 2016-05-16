#include "ObjectChangeOnSlot.hpp"

#include "MAster.hpp"

void Packet <PACKET_OBJECT_CHANGE_ON_SLOT>::onReceive(const ENetEvent &event)
{
    int slot = 0, objectType = -1, p1 = -1, p2 = -1, p3 = -1;
    sscanf((char*)event.packet->data, "%*c %d %d %d %d %d", &slot, &objectType, &p1, &p2, &p3);

    _assert(slot >= 0 && slot < CHARACTER_OBJECT_SLOTS_QUANTITY,
            "Slot index out of bounds in processPacket_objectChangeOnSlot.");
    _assert(objectType < (int)Master::getInstance().ObjectType.size(),
            "Object type out of bounds in processPacket_objectChangeOnSlot.");

    CharacterClass *player = Master::getInstance().getPlayer().getCharacter();
    _assert(player != NULL, "Player is NULL.");

    player->getObjectOnSlot(slot).clear();
    Master::getInstance().assignParamsToObject(player->getObjectOnSlot(slot), objectType, p1, p2, p3);
}
