#ifndef DAY_TIME_HPP
#define DAY_TIME_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_DAY_TIME ('d')

template <> class Packet <PACKET_DAY_TIME>
{
    public:
        static std::string construct(double dayTime);
};

#endif
