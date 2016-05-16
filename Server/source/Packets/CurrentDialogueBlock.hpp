#ifndef CURRENT_DIALOGUE_BLOCK_HPP
#define CURRENT_DIALOGUE_BLOCK_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_CURRENT_DIALOGUE_BLOCK ('k')

class CharacterClass;

template <> class Packet <PACKET_CURRENT_DIALOGUE_BLOCK>
{
    public:
        static std::string construct(CharacterClass &player);
};

#endif
