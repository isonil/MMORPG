#ifndef PRIVATE_CHAT_REQUEST_HPP
#define PRIVATE_CHAT_REQUEST_HPP

#include <enet/enet.h>
#include <string>
#include "Packet.hpp"

#define PACKET_PRIVATE_CHAT_REQUEST ('t')

template <> class Packet <PACKET_PRIVATE_CHAT_REQUEST>
{
    public:
        static void onReceive(const ENetEvent &event);
        static std::string construct(int playerIDOrStatus, const std::string &name);
};

#endif
