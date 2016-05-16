#ifndef CHOOSE_TALK_OPTION_HPP
#define CHOOSE_TALK_OPTION_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_CHOOSE_TALK_OPTION ('j')

template <> class Packet <PACKET_CHOOSE_TALK_OPTION>
{
    public:
        static std::string construct(int num);
};

#endif
