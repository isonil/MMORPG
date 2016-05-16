#include "CharacterParams.hpp"

#include <sstream>
#include "Master.hpp"

std::string Packet <PACKET_CHARACTER_PARAMS>::construct(const Character &character, char characterSet, int characterID)
{
    std::ostringstream oss;
    oss << PACKET_CHARACTER_PARAMS << ' '
        << characterSet << ' '
        << characterID << ' '
        << character.name.c_str() << ' '
        << (int)character.x << ' '
        << (int)character.y << ' '
        << int(character.dir*100.f) << ' '
        << character.param[CHARACTER_PARAM_HEALTH] << ' '
        << character.param[CHARACTER_PARAM_MAX_HEALTH] << ' '
        << character.param[CHARACTER_PARAM_LEVEL] << ' ';
    for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
        oss << character.objectOnSlot[i].type << ' ';
    }
    return oss.str();
}
