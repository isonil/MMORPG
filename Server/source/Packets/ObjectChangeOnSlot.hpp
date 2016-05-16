#ifndef OBJECT_CHANGE_ON_SLOT_HPP
#define OBJECT_CHANGE_ON_SLOT_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_OBJECT_CHANGE_ON_SLOT ('w')

class ObjectClass;

template <> class Packet <PACKET_OBJECT_CHANGE_ON_SLOT>
{
    public:
        static std::string construct(int slotIndex, const ObjectClass &object);
};

#endif
