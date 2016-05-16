#include "EndCurrentNPCInteraction.hpp"

#include <sstream>

std::string Packet <PACKET_END_CURRENT_NPC_INTERACTION>::construct()
{
    std::ostringstream oss;
    oss << PACKET_END_CURRENT_NPC_INTERACTION;
    return oss.str();
}
