#include "PrivateChatMessage.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_PRIVATE_CHAT_MESSAGE>::onReceive(const ENetEvent &event)
{
    int messageStartIndex = -1;
    std::string playerIndexStr;
    int playerIndex = -1;
    std::string message;
    bool spaceEncountered = false;

    for(size_t i=2; i<event.packet->dataLength; ++i) {
        if(event.packet->data[i] == '\0') continue;
        if(event.packet->data[i] == ' ' && !spaceEncountered) spaceEncountered = true;
        else if(spaceEncountered) {
            message += event.packet->data[i];
            if(messageStartIndex == -1) messageStartIndex = i;
        }
        else {
            playerIndexStr += event.packet->data[i];
        }
    }

    _assert(playerIndexStr.size(), "Player index string is empty in processPacket_privateChatMessage.");
    sscanf(playerIndexStr.c_str(), "%d", &playerIndex);
    _assert(playerIndex >= 0, "Player index is negative in processPacket_privateChatMessage.");

    if(messageStartIndex != -1) {
        CharacterClass &player = Master::getInstance().getWorld().getPlayer(playerIndex);

        if(!player.getName().size()) {
            std::string newName;
            for(size_t i=messageStartIndex; i<event.packet->dataLength; ++i) {
                if(event.packet->data[i] == ':' || event.packet->data[i] == '\0') break;
                newName += event.packet->data[i];
            }
            player.setName(newName);
        }
        bool tabExists = false;
        for(size_t i=0; i<Master::getInstance().Interface.chatTab.size(); ++i) {
            if(Master::getInstance().Interface.chatTab[i].chat == playerIndex) {
                tabExists = true;
                break;
            }
        }
        if(!tabExists) {
            Master::getInstance().Interface.chatTab.push_back(ChatTabClass(playerIndex));
        }
        Master::getInstance().addMessageToChat(player.getPrivateChat(), message, playerIndex);
    }
}

std::string Packet <PACKET_PRIVATE_CHAT_MESSAGE>::construct(int playerID, const std::string &text)
{
    std::ostringstream oss;
    oss << PACKET_PRIVATE_CHAT_MESSAGE << ' ' << playerID << ' ' << text;
    return oss.str();
}
