#include "CharacterSlotObjectChange.hpp"

#include "Master.hpp"

void Packet <PACKET_CHARACTER_SLOT_OBJECT_CHANGE>::onReceive(const ENetEvent &event)
{
    char characterSet = 0;
    int characterID = -1, slot = -1, objectType = -1;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d", &characterSet, &characterID, &slot, &objectType);

    _assert(Master::getInstance().isValidCharacterSet(characterSet), "Invalid character set in processPacket_characterSlotObjectChange.");
    _assert(characterID >= 0, "Character ID is negative in processPacket_characterSlotObjectChange.");
    _assert(slot >= 0 && slot < CHARACTER_OBJECT_SLOTS_QUANTITY, "Slot index out of bounds in processPacket_characterSlotObjectChange.");
    _assert(objectType < (int)Master::getInstance().ObjectType.size(), "Object type out of bounds in processPacket_characterSlotObjectChange.");

    CharacterClass &character = Master::getInstance().getWorld().getCharacter(characterSet, characterID);
    character.getObjectOnSlot(slot).type = objectType;
}
