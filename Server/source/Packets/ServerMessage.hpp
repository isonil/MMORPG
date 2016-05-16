#ifndef SERVER_MESSAGE_HPP
#define SERVER_MESSAGE_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_SERVER_MESSAGE ('0')

template <> class Packet <PACKET_SERVER_MESSAGE>
{
    public:
        static std::string construct();
};

#endif
