#ifndef START_TALK_WITH_NPC_HPP
#define START_TALK_WITH_NPC_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_START_TALK_WITH_NPC ('f')

template <> class Packet <PACKET_START_TALK_WITH_NPC>
{
    public:
        static std::string construct(int NPCID);
};

#endif
