#include "CharacterLostSight.hpp"

#include <sstream>

std::string Packet <PACKET_CHARACTER_LOST_SIGHT>::construct(char characterSet, int characterID)
{
    std::ostringstream oss;
    oss << PACKET_CHARACTER_LOST_SIGHT << ' ' << characterSet << ' ' << characterID;
    return oss.str();
}
