#include "ObjectChangeInInventory.hpp"

#include "Master.hpp"

void Packet <PACKET_OBJECT_CHANGE_IN_INVENTORY>::onReceive(const ENetEvent &event)
{
    int x = 0, y = 0, objectType = -1, p1 = -1, p2 = -1, p3 = -1;
    sscanf((char*)event.packet->data, "%*c %d %d %d %d %d %d", &x, &y, &objectType, &p1, &p2, &p3);

    _assert(x >= 0 && x < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
            y >= 0 && y < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT,
            "Position out of bounds in processPacket_objectChangeInInventory.");
    _assert(objectType < (int)Master::getInstance().ObjectType.size(),
            "Object type out of bounds in processPacket_objectChangeInInventory.");

    CharacterClass *player = Master::getInstance().getPlayer().getCharacter();
    _assert(player != NULL, "Player is NULL.");

    player->getObjectInInventory(x, y).clear();
    Master::getInstance().assignParamsToObject(player->getObjectInInventory(x, y), objectType, p1, p2, p3);
}
