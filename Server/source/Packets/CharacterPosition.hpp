#ifndef CHARACTER_POSITION_HPP
#define CHARACTER_POSITION_HPP

#include <enet/enet.h>
#include <string>
#include "Packet.hpp"

#define PACKET_CHARACTER_POSITION ('p')

template <> class Packet <PACKET_CHARACTER_POSITION>
{
    public:
        static void onReceive(const ENetEvent &event);
        static std::string construct(char characterSet, int characterID, float x, float y, float dir);
};

#endif
