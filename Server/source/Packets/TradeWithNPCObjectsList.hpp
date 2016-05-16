#ifndef TRADE_WITH_NPC_OBJECTS_LIST_HPP
#define TRADE_WITH_NPC_OBJECTS_LIST_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_TRADE_WITH_NPC_OBJECTS_LIST ('m')

class CharacterClass;

template <> class Packet <PACKET_TRADE_WITH_NPC_OBJECTS_LIST>
{
    public:
        static std::string construct(CharacterClass &player);
};

#endif
