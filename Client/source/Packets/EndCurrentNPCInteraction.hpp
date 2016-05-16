#ifndef END_CURRENT_NPC_INTERACTION_HPP
#define END_CURRENT_NPC_INTERACTION_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_END_CURRENT_NPC_INTERACTION ('z')

template <> class Packet <PACKET_END_CURRENT_NPC_INTERACTION>
{
    public:
        static std::string construct();
};

#endif
