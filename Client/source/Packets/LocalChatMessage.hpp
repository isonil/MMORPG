#ifndef LOCAL_CHAT_MESSAGE_HPP
#define LOCAL_CHAT_MESSAGE_HPP

#include <enet/enet.h>
#include <string>
#include "Packet.hpp"

#define PACKET_LOCAL_CHAT_MESSAGE ('1')

template <> class Packet <PACKET_LOCAL_CHAT_MESSAGE>
{
    public:
        static void onReceive(const ENetEvent &event);
        static std::string construct(const std::string &text);
};

#endif
