#include "ObjectChangeOnSlot.hpp"

#include <sstream>
#include "Master.hpp"

std::string Packet <PACKET_OBJECT_CHANGE_ON_SLOT>::construct(int slotIndex, const Object &object)
{
    std::ostringstream oss;
    oss << PACKET_OBJECT_CHANGE_ON_SLOT << ' ' << slotIndex << ' ';
    Master::getInstance().getObjectParams(oss, object);
    return oss.str();
}
