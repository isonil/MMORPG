#ifndef CHARACTER_PARAMS_HPP
#define CHARACTER_PARAMS_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_CHARACTER_PARAMS ('i')

class CharacterClass;

template <> class Packet <PACKET_CHARACTER_PARAMS>
{
    public:
        static std::string construct(const CharacterClass &character, char characterSet, int characterID);
};

#endif
