#ifndef TRADE_WITH_NPC_BUY_OBJECT_HPP
#define TRADE_WITH_NPC_BUY_OBJECT_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_TRADE_WITH_NPC_BUY_OBJECT ('u')

template <> class Packet <PACKET_TRADE_WITH_NPC_BUY_OBJECT>
{
    public:
        static std::string construct(int index);
};

#endif
