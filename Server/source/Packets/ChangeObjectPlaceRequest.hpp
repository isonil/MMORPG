#ifndef CHANGE_OBJECT_PLACE_REQUEST
#define CHANGE_OBJECT_PLACE_REQUEST

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_CHANGE_OBJECT_PLACE_REQUEST ('g')

template <> class Packet <PACKET_CHANGE_OBJECT_PLACE_REQUEST>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
