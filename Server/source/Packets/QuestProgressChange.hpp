#ifndef QUEST_PROGRESS_CHANGE_HPP
#define QUEST_PROGRESS_CHANGE_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_QUEST_PROGRESS_CHANGE ('y')

template <> class Packet <PACKET_QUEST_PROGRESS_CHANGE>
{
    public:
        static std::string construct(int questIndex, int progress);
};

#endif
