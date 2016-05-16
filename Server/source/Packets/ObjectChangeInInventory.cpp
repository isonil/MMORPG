#include "ObjectChangeInInventory.hpp"

#include <sstream>
#include "Master.hpp"

std::string Packet <PACKET_OBJECT_CHANGE_IN_INVENTORY>::construct(int inv_x, int inv_y, const ObjectClass &object)
{
    std::ostringstream oss;
    oss << PACKET_OBJECT_CHANGE_IN_INVENTORY << ' ' << inv_x << ' ' << inv_y << ' ';
    Master::getInstance().getObjectParams(oss, object);
    return oss.str();
}
