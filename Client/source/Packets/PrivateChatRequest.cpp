#include "PrivateChatRequest.hpp"

#include <sstream>

void Packet <PACKET_PRIVATE_CHAT_REQUEST>::onReceive(const ENetEvent &event)
{
    int playerIndex = 0;
    char *name = new char[event.packet->dataLength+1];
    name[0] = 0;

    sscanf((char*)event.packet->data, "%*c %d %s", &playerIndex, name);

    if(playerIndex == PLAYER_OFFLINE) {
        addMessageToCurrentChat("Player is offline.");
    }
    else if(playerIndex == PLAYER_DOESNT_EXIST) {
        addMessageToCurrentChat("Player doesn't exist.");
    }
    else if(playerIndex >= 0) {
        if(playerIndex >= (int)Player.size()) Player.resize(playerIndex+1);
        bool tabExists = false;
        for(size_t i=0; i<Interface.chatTab.size(); ++i) {
            if(Interface.chatTab[i].chat == playerIndex) {
                tabExists = true;
                break;
            }
        }
        if(!tabExists) {
            Interface.chatTab.push_back(ChatTabClass(playerIndex));
        }
        Interface.currentChat = playerIndex;
    }
    delete []name;
}

std::string Packet <PACKET_PRIVATE_CHAT_REQUEST>::construct(const std::string &playerName)
{
    std::ostringstream oss;
    oss << PACKET_PRIVATE_CHAT_REQUEST << ' ' << playerName;
    return oss.str();
}
