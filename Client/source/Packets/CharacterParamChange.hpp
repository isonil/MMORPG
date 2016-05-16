#ifndef CHARACTER_PARAM_CHANGE
#define CHARACTER_PARAM_CHANGE

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_CHARACTER_PARAM_CHANGE ('c')

template <> class Packet <PACKET_CHARACTER_PARAM_CHANGE>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
