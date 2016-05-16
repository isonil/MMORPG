#include "PrivateChatMessage.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_PRIVATE_CHAT_MESSAGE>::onReceive(const ENetEvent &event)
{
    std::string playerIndexStr;
    int playerIndex = -1;
    std::string message;
    bool spaceEncountered = false;

    for(size_t i=2; i<event.packet->dataLength; ++i) {
        if(event.packet->data[i] == '\0') continue;

        if(event.packet->data[i] == ' ' && !spaceEncountered)
            spaceEncountered = true;
        else if(spaceEncountered) {
            message += event.packet->data[i];
        }
        else {
            playerIndexStr += event.packet->data[i];
        }
    }

    if(message.size() > CHAT_MESSAGE_LENGTH_LIMIT) return;

    sscanf(playerIndexStr.c_str(), "%d", &playerIndex);
    if(playerIndex >= 0 && playerIndex < (int)M.Player.size()) {
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
            if(M.Player[playerIndex].isOnline) {
                std::string packet = Packet <PACKET_PRIVATE_CHAT_MESSAGE>::construct((int)event.peer->data, M.getPlayerRichName(M.Player[(int)event.peer->data], (int)event.peer->data), message);
                M.Player[playerIndex].sendPacket(packet);
                packet = Packet <PACKET_PRIVATE_CHAT_MESSAGE>::construct(playerIndex, M.getPlayerRichName(M.Player[(int)event.peer->data], (int)event.peer->data), message);
                M.Player[(int)event.peer->data].sendPacket(packet);
            }
            else {
                std::string packet = Packet <PACKET_PRIVATE_CHAT_MESSAGE>::construct(playerIndex, "system", "This player is offline.");
                M.Player[(int)event.peer->data].sendPacket(packet);
            }
        }
    }
}

std::string Packet <PACKET_PRIVATE_CHAT_MESSAGE>::construct(int playerID, const std::string &name, const std::string &message)
{
    std::ostringstream oss;
    oss << PACKET_PRIVATE_CHAT_MESSAGE << ' ' << playerID << ' ' << name << ' ' << message;
    return oss.str();
}
