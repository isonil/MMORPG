#include "StartTalkWithNPC.hpp"

#include <sstream>

std::string Packet <PACKET_START_TALK_WITH_NPC>::construct(int NPCID)
{
    std::ostringstream oss;
    oss << PACKET_START_TALK_WITH_NPC << ' ' << NPCID;
    return oss.str();
}
