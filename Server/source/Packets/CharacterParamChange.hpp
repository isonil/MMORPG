#ifndef CHARACTER_PARAM_CHANGE
#define CHARACTER_PARAM_CHANGE

#include <string>
#include "Packet.hpp"

#define PACKET_CHARACTER_PARAM_CHANGE ('c')

template <> class Packet <PACKET_CHARACTER_PARAM_CHANGE>
{
    public:
        static std::string construct(char characterSet, int characterID, int param, int value);
};

#endif
