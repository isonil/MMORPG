#ifndef GLOBAL_CHAT_MESSAGE_HPP
#define GLOBAL_CHAT_MESSAGE_HPP

#include <enet/enet.h>
#include <string>
#include "Packet.hpp"

#define PACKET_GLOBAL_CHAT_MESSAGE ('2')

template <> class Packet <PACKET_GLOBAL_CHAT_MESSAGE>
{
    public:
        static void onReceive(const ENetEvent &event);
        static std::string construct(const std::string &text);
};

#endif
