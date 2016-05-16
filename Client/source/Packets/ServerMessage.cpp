#include "ServerMessage.hpp"

#include "Master.hpp"

void Packet <PACKET_SERVER_MESSAGE>::onReceive(const ENetEvent &event)
{
    std::string message;
    for(size_t i=2; i<event.packet->dataLength; ++i)
        if(event.packet->data[i] != '\0') message += event.packet->data[i];
    Master::getInstance().addMessageToChat(Master::getInstance().Interface.localChat, message, CHAT_TAB_LOCAL);
    Master::getInstance().addMessageToChat(Master::getInstance().Interface.globalChat, message, CHAT_TAB_GLOBAL);
}
