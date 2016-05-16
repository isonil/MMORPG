#include "ChooseTalkOption.hpp"

#include <sstream>

std::string Packet <PACKET_CHOOSE_TALK_OPTION>::construct(int num)
{
    std::ostringstream oss;
    oss << PACKET_CHOOSE_TALK_OPTION << ' ' << num;
    return oss.str();
}
