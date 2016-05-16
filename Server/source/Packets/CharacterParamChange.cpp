#include "CharacterParamChange.hpp"

#include <sstream>

std::string Packet <PACKET_CHARACTER_PARAM_CHANGE>::construct(char characterSet, int characterID, int param, int value)
{
    std::ostringstream oss;
    oss << PACKET_CHARACTER_PARAM_CHANGE << ' ' << characterSet << ' ' << characterID << ' ' << param << ' ' << value;
    return oss.str();
}
