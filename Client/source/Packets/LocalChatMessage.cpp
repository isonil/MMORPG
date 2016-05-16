#include "LocalChatMessage.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_LOCAL_CHAT_MESSAGE>::onReceive(const ENetEvent &event)
{
    std::string playerIndexStr;
    int playerIndex = -1;
    std::string message;
    bool spaceEncountered = false;

    for(size_t i=2; i<event.packet->dataLength; ++i) {
        if(event.packet->data[i] == '\0') continue;
        if(event.packet->data[i] == ' ' && !spaceEncountered) spaceEncountered = true;
        else if(spaceEncountered) {
            message += event.packet->data[i];
        }
        else {
            playerIndexStr += event.packet->data[i];
        }
    }

    _assert(playerIndexStr.size(), "Player index string is empty in processPacket_localChatMessage.");
    sscanf(playerIndexStr.c_str(), "%d", &playerIndex);
    _assert(playerIndex >= 0,"Player index is negative in processPacket_localChatMessage.");

    CharacterClass &player = Master::getInstance().getWorld().getPlayer(playerIndex);

    Master::getInstance().addMessageToChat(Master::getInstance().Interface.localChat, message, CHAT_TAB_LOCAL);
    std::string messageOverHead;
    size_t colonPos = message.find(':');
    if(colonPos != std::string::npos && colonPos+2 < message.size()) {
        messageOverHead = message.substr(colonPos+2);
    }
    else messageOverHead = message;

    sf::Text text;
    text.setCharacterSize(11);

    std::string buff;
    for(size_t i=0; i<messageOverHead.size(); ++i) {
        if(messageOverHead[i] == '`') {++i; continue;}
        text.setString(buff+messageOverHead[i]);
        if(getTextWidth(text) > 200) {
            if(buff.size()) {
                size_t rspace = buff.rfind(' ');
                if(rspace != std::string::npos) {
                    int spaceLeftEnd = (int)rspace;
                    while(spaceLeftEnd >= 0 && buff[spaceLeftEnd] == ' ') {
                        --spaceLeftEnd;
                    }
                    if(spaceLeftEnd >= 0) {
                        player.addMessageOverHead(buff.substr(0, spaceLeftEnd+1));
                    }
                    if(rspace+1 < buff.size()) buff = buff.substr(rspace+1);
                    else buff.clear();
                }
                else {
                    player.addMessageOverHead(buff+'-');
                    buff.clear();
                }
            }
        }
        buff += messageOverHead[i];
    }
    if(buff.size()) player.addMessageOverHead(buff);
}

std::string Packet <PACKET_LOCAL_CHAT_MESSAGE>::construct(const std::string &text)
{
    std::ostringstream oss;
    oss << PACKET_LOCAL_CHAT_MESSAGE << ' ' << text;
    return oss.str();
}
