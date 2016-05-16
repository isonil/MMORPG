#include "GlobalChatMessage.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_GLOBAL_CHAT_MESSAGE>::onReceive(const ENetEvent &event)
{
    std::string message;
    for(size_t i=2; i<event.packet->dataLength; ++i)
        if(event.packet->data[i] != '\0') message += event.packet->data[i];

    if(message.size() > CHAT_MESSAGE_LENGTH_LIMIT) return;

    //to do: timeout for messages
    bool forbiddenCharacters = false;
    /*for(size_t i=0; i<message.size(); ++i) {
        bool allowed = false;
        for(int j=0; j<allowedChatKeysQuantity; ++j) {
            if(scanCodeToChar(allowedChatKeys[j], false) == message[i] || scanCodeToChar(allowedChatKeys[j], true) == message[i]) {
                allowed = true;
                break;
            }
        }
        if(!allowed) {
            forbiddenCharacters = true;
            break;
        }
    }*/
    if(!forbiddenCharacters && !message.empty()) {
        for(size_t i=0; i<M.Player.size(); ++i) {
            if(M.Player[i].isOnline) {
                std::string packet = Packet <PACKET_GLOBAL_CHAT_MESSAGE>::construct(M.getPlayerRichName(M.Player[(int)event.peer->data], (int)event.peer->data).c_str(),
                                                                                    message.c_str());
                M.Player[(int)event.peer->data].sendPacket(packet);
            }
        }
    }
}

std::string Packet <PACKET_GLOBAL_CHAT_MESSAGE>::construct(const std::string &name, const std::string &message)
{
    std::ostringstream oss;
    oss << PACKET_GLOBAL_CHAT_MESSAGE << ' ' << name << ": " << message;
    return oss.str();
}
