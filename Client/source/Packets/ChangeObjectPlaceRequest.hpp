#ifndef CHANGE_OBJECT_PLACE_REQUEST
#define CHANGE_OBJECT_PLACE_REQUEST

#include <string>
#include "Packet.hpp"

#define PACKET_CHANGE_OBJECT_PLACE_REQUEST ('g')

template <> class Packet <PACKET_CHANGE_OBJECT_PLACE_REQUEST>
{
    public:
        static std::string construct(int place, int p1, int p2, int p3, int destPlace, int dp1, int dp2, int dp3);
};

#endif
