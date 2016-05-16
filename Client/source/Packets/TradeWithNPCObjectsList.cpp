#include "TradeWithNPCObjectsList.hpp"

#include "Master.hpp"

void Packet <PACKET_TRADE_WITH_NPC_OBJECTS_LIST>::onReceive(const ENetEvent &event)
{
    char ch;
    int NPCIndex = -1, objectsQuantity = 0;
    std::istringstream iss((char*)event.packet->data);
    iss >> ch >> NPCIndex >> objectsQuantity;

    Master::getInstance().currentTradeWithNPC.NPCIndex = NPCIndex;
    Master::getInstance().currentTradeWithNPC.NPCObjectType.clear();
    for(int i=0; i<objectsQuantity; ++i) {
        int object = -1;
        iss >> object;
        if(object >= 0) {
            _assert(object < (int)Master::getInstance().ObjectType.size(),
                    "Object type out of bounds in processPacket_tradeWithNPCObjectsList.");
            Master::getInstance().currentTradeWithNPC.NPCObjectType.push_back(object);
        }
    }
    if(NPCIndex >= 0) Master::getInstance().currentTradeWithNPC.active = true;
    else Master::getInstance().currentTradeWithNPC.active = false;

    for(std::list <WindowClass>::iterator it=Master::getInstance().Interface.window.begin(); it!=Master::getInstance().Interface.window.end(); ++it) {
        if(it->title == "Trade with NPC") {
            it->visible = Master::getInstance().currentTradeWithNPC.active;
            Master::getInstance().Interface.window.push_front(*it);
            Master::getInstance().Interface.window.erase(it);
            break;
        }
    }
}
