#include "TradeWithNPCObjectsList.hpp"

#include <sstream>
#include "Master.hpp"
#include "Classes.hpp"

std::string Packet <PACKET_TRADE_WITH_NPC_OBJECTS_LIST>::construct(Character &player)
{
    std::ostringstream oss;
    if(player.NPCInteraction.type == NPC_INTERACTION_TYPE_TRADE) {
        oss << PACKET_TRADE_WITH_NPC_OBJECTS_LIST << ' '
            << player.NPCInteraction.NPCIndex << ' ';
    }
    else {
        oss << PACKET_TRADE_WITH_NPC_OBJECTS_LIST << ' '
            << "-1";
    }

    if(player.NPCInteraction.type == NPC_INTERACTION_TYPE_TRADE) {
        if(player.NPCInteraction.NPCIndex < 0 ||
           player.NPCInteraction.NPCIndex >= (int)M.NPC.size()) {
            player.NPCInteraction.type = NPC_INTERACTION_TYPE_NONE;
            _assert_return_value(0, NULL, 0, "NPCInteraction.NPCIndex out of bounds in getTradeWithNPCObjectsListPacket.", "");
        }

        CharacterClass *merchant = &M.NPC[player.NPCInteraction.NPCIndex];
        _assert_return_value(merchant->NPCType >= 0 && merchant->NPCType < (int)M.NPCType.size(), NULL, 0,
                       "Merchant NPC type out of bounds in getTradeWithNPCObjectsListPacket.", "");

        oss << M.NPCType[merchant->NPCType].tradeObject.size() << " ";
        for(size_t i=0; i<M.NPCType[merchant->NPCType].tradeObject.size(); ++i) {
            oss << M.NPCType[merchant->NPCType].tradeObject[i].objectType << " ";
        }
    }
    return oss.str();
}
