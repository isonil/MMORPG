#include "TradeWithNPCBuyObject.hpp"

#include "Master.hpp"

void Packet <PACKET_TRADE_WITH_NPC_BUY_OBJECT>::onReceive(const ENetEvent &event)
{
    int objectIndex = -1;
    sscanf((char*)event.packet->data, "%*c %d", &objectIndex);

    if(M.Player[(int)event.peer->data].NPCInteraction.type == NPC_INTERACTION_TYPE_TRADE) {
        _assert_return(M.Player[(int)event.peer->data].NPCInteraction.NPCIndex >= 0 &&
                       M.Player[(int)event.peer->data].NPCInteraction.NPCIndex < (int)M.NPC.size(),
                       M.Player[(int)event.peer->data].name.c_str(),
                       (int)event.peer->data,
                       "NPCInteraction.NPCIndex out of bounds in processPacket_tradeWithNPCBuyObject.");
    }

    bool tradeAllowed = true;
    if(M.Player[(int)event.peer->data].NPCInteraction.type != NPC_INTERACTION_TYPE_TRADE) tradeAllowed = false;
    else if(M.NPC[M.Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType < 0) tradeAllowed = false;
    else {
        _assert_return(M.NPC[M.Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType < (int)M.NPCType.size(),
                       M.Player[(int)event.peer->data].name.c_str(),
                       (int)event.peer->data,
                       "M.NPC type out of bounds in processPacket_tradeWithNPCBuyObject.");
        if(objectIndex < 0 || objectIndex >= (int)M.NPCType[M.NPC[M.Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].tradeObject.size())
            tradeAllowed = false;
        else {
            int objectType = M.NPCType[M.NPC[M.Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].tradeObject[objectIndex].objectType;
            _assert_return(objectType >= 0 && objectType < (int)M.ObjectType.size(),
                           M.Player[(int)event.peer->data].name.c_str(),
                           (int)event.peer->data,
                           "Trade object type out of bounds in processPacket_tradeWithNPCBuyObject.");
            if(M.Player[(int)event.peer->data].param[CHARACTER_PARAM_MONEY] < M.ObjectType[objectType].value)
                tradeAllowed = false;
        }
    }

    if(tradeAllowed) {
        int objectType = M.NPCType[M.NPC[M.Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].tradeObject[objectIndex].objectType;
        int price = M.ObjectType[M.NPCType[M.NPC[M.Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].tradeObject[objectIndex].objectType].value;
        M.addObjectToPlayerInventory(M.Player[(int)event.peer->data], ObjectClass(objectType));
        M.changeCharacterParamBy(M.Player[(int)event.peer->data], CHARACTER_PLAYER, (int)event.peer->data, CHARACTER_PARAM_MONEY, -price, false);
    }
}
