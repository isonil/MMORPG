#include "PrivateChatRequest.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_PRIVATE_CHAT_REQUEST>::onReceive(const ENetEvent &event)
{
    char *name = new char[event.packet->dataLength+1];
    name[0] = 0;
    sscanf((char*)event.packet->data, "%*c %s", name);

    if(strlen(name) > LOGIN_LENGTH_LIMIT) return;

    std::string packet;
    bool exists = false;
    for(size_t i=0; i<M.Player.size(); ++i) {
        if(M.Player[i].name == name) {
            if(M.Player[i].isOnline) packet = Packet <PACKET_PRIVATE_CHAT_REQUEST>::construct(i, M.Player[i].name);
            else packet = Packet <PACKET_PRIVATE_CHAT_REQUEST>::construct(PLAYER_OFFLINE, "");
            exists = true;
            break;
        }
    }
    if(!exists) packet = Packet <PACKET_PRIVATE_CHAT_REQUEST>::construct(PLAYER_DOESNT_EXIST, "");
    M.Player[(int)event.peer->data].sendPacket(packet);

    delete []name;
}

std::string Packet <PACKET_PRIVATE_CHAT_REQUEST>::construct(int playerIDOrStatus, const std::string &name)
{
    std::ostringstream oss;
    oss << PACKET_PRIVATE_CHAT_REQUEST << ' ' << playerIDOrStatus << ' ' << name;
    return oss.str();
}
