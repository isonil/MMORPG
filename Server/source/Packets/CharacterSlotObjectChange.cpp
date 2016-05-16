#include "CharacterSlotObjectChange.hpp"

#include <sstream>

std::string Packet <PACKET_CHARACTER_SLOT_OBJECT_CHANGE>::construct(char characterSet, int characterID, int slotIndex, int objectType)
{
    std::ostringstream oss;
    oss << PACKET_CHARACTER_SLOT_OBJECT_CHANGE << ' ' << characterSet << ' ' << characterID << ' ' << slotIndex << ' ' << objectType;
    return oss.str();
}
