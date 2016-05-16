#include "ChangeObjectPlaceRequest.hpp"

#include <sstream>

std::string Packet <PACKET_CHANGE_OBJECT_PLACE_REQUEST>::construct(int place, int p1, int p2, int p3, int destPlace, int dp1, int dp2, int dp3)
{
    std::ostringstream oss;
    oss << PACKET_CHANGE_OBJECT_PLACE_REQUEST << ' '
        << place << ' ' << p1 << ' ' << p2 << ' ' << p3 << ' '
        << destPlace << ' ' << dp1 << ' ' << dp2 << ' ' << dp3;
    return oss.str();
}
