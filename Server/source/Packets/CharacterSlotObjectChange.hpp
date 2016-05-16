#ifndef CHARACTER_SLOT_OBJECT_CHANGE_HPP
#define CHARACTER_SLOT_OBJECT_CHANGE_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_CHARACTER_SLOT_OBJECT_CHANGE ('e')

template <> class Packet <PACKET_CHARACTER_SLOT_OBJECT_CHANGE>
{
    public:
        static std::string construct(char characterSet, int characterID, int slotIndex, int objectType);
};

#endif
