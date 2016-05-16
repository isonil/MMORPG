#ifndef CHARACTER_LOST_SIGHT_HPP
#define CHARACTER_LOST_SIGHT_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_CHARACTER_LOST_SIGHT ('x')

template <> class Packet <PACKET_CHARACTER_LOST_SIGHT>
{
    public:
        static std::string construct(char characterSet, int characterID);
};

#endif
