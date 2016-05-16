#ifndef OBJECT_CHANGE_IN_INVENTORY_HPP
#define OBJECT_CHANGE_IN_INVENTORY_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_OBJECT_CHANGE_IN_INVENTORY ('q')

class ObjectClass;

template <> class Packet <PACKET_OBJECT_CHANGE_IN_INVENTORY>
{
    public:
        static std::string construct(int inv_x, int inv_y, const ObjectClass &object);
};

#endif
