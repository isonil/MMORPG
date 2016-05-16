#ifndef PRIVATE_CHAT_MESSAGE_HPP
#define PRIVATE_CHAT_MESSAGE_HPP

#include <enet/enet.h>
#include <string>
#include "Packet.hpp"

#define PACKET_PRIVATE_CHAT_MESSAGE ('3')

template <> class Packet <PACKET_PRIVATE_CHAT_MESSAGE>
{
    public:
        static void onReceive(const ENetEvent &event);
        static std::string construct(int playerID, const std::string &text);
};

#endif
