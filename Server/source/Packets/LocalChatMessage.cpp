#include "LocalChatMessage.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_LOCAL_CHAT_MESSAGE>::onReceive(const ENetEvent &event)
{
    std::string message;
    for(size_t i=2; i<event.packet->dataLength; ++i)
        if(event.packet->data[i] != '\0') message += event.packet->data[i];

    if(message.size() > CHAT_MESSAGE_LENGTH_LIMIT) return;

    if(message == "/home") {
        M.changeCharacterPosition(CHARACTER_PLAYER, (int)event.peer->data, 522*TILE_SIZE, 505*TILE_SIZE, true);
        message = "";
    }

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
        char packet[MAX_PACKET_SIZE_LOCAL_CHAT_MESSAGE];
        sprintf(packet, "%c %d %s: %s", PACKET_LOCAL_CHAT_MESSAGE,
                                        (int)event.peer->data,
                                        M.getPlayerRichName(M.Player[(int)event.peer->data], (int)event.peer->data).c_str(),
                                        message.c_str());
        M.sendToAllPlayersInView(packet, 1, M.Player[(int)event.peer->data].x, M.Player[(int)event.peer->data].y, -1);
    }
}

std::string Packet <PACKET_LOCAL_CHAT_MESSAGE>::construct(int playerID, const std::string &name, const std::string &message)
{
    std::ostringstream oss;
    oss << PACKET_LOCAL_CHAT_MESSAGE << ' ' << playerID << ' ' << name << ": " << message;
    return oss.str();
}
