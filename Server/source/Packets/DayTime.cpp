#include "DayTime.hpp"

#include <sstream>

std::string Packet <PACKET_DAY_TIME>::construct(double dayTime)
{
    std::ostringstream oss;
    oss << PACKET_DAY_TIME << ' ' << (int)dayTime;
    return oss.str();
}
