#ifndef LOG_IN_HPP
#define LOG_IN_HPP

#include <enet/enet.h>
#include <string>
#include "Packet.hpp"

#define PACKET_LOG_IN ('l')

template <> class Packet <PACKET_LOG_IN>
{
    public:
        static void onReceive(const ENetEvent &event);
        static std::string construct(const std::string &name, const std::string &password);
};

#endif
