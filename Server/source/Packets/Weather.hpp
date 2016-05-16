#ifndef WEATHER_HPP
#define WEATHER_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_WEATHER ('r')

template <> class Packet <PACKET_WEATHER>
{
    public:
        static std::string construct();
};

#endif
