#include "QuestProgressChange.hpp"

#include <sstream>
#include "Master.hpp"

std::string Packet <PACKET_QUEST_PROGRESS_CHANGE>::construct(int questIndex, int progress)
{
    _assert_return_value(questIndex >= 0 && questIndex < (int)Master::getInstance().Quest.size(), NULL, 0,
                         "Quest index out of bounds in getquestProgressChangePacket.", "");

    std::ostringstream oss;
    oss << PACKET_QUEST_PROGRESS_CHANGE << ' ' << questIndex << ' ' << progress;
    return oss.str();
}
