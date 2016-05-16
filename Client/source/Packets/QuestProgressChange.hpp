#ifndef QUEST_PROGRESS_CHANGE_HPP
#define QUEST_PROGRESS_CHANGE_HPP

#include <enet/enet.h>
#include "Packet.hpp"

#define PACKET_QUEST_PROGRESS_CHANGE ('y')

template <> class Packet <PACKET_QUEST_PROGRESS_CHANGE>
{
    public:
        static void onReceive(const ENetEvent &event);
};

#endif
