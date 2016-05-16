#include "TradeWithNPCBuyObject.hpp"

#include <sstream>

std::string Packet <PACKET_TRADE_WITH_NPC_BUY_OBJECT>::construct(int index)
{
    std::ostringstream oss;
    oss << PACKET_TRADE_WITH_NPC_BUY_OBJECT << ' ' << index;
    return oss.str();
}
