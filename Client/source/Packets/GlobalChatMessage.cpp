#include "GlobalChatMessage.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_GLOBAL_CHAT_MESSAGE>::onReceive(const ENetEvent &event)
{
    std::string message;
    for(size_t i=2; i<event.packet->dataLength; ++i)
        if(event.packet->data[i] != '\0') message += event.packet->data[i];
    Master::getInstance().addMessageToChat(Master::getInstance().Interface.globalChat, message, CHAT_TAB_GLOBAL);
}

std::string Packet <PACKET_GLOBAL_CHAT_MESSAGE>::construct(const std::string &text)
{
    std::ostringstream oss;
    oss << PACKET_GLOBAL_CHAT_MESSAGE << ' ' << text;
    return oss.str();
}
