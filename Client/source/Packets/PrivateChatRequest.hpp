#ifndef PRIVATE_CHAT_REQUEST_HPP
#define PRIVATE_CHAT_REQUEST_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_PRIVATE_CHAT_REQUEST ('t')

template <> class Packet <PACKET_PRIVATE_CHAT_REQUEST>
{
    public:
        static void onReceive(const ENetEvent &event);
        static std::string construct(const std::string &playerName);
};

#endif
