#ifndef OBJECT_CHANGE_ON_GROUND_HPP
#define OBJECT_CHANGE_ON_GROUND_HPP

#include <string>
#include "Packet.hpp"

#define PACKET_OBJECT_CHANGE_ON_GROUND ('o')

template <> class Packet <PACKET_OBJECT_CHANGE_ON_GROUND>
{
    public:
        static std::string construct(int tile_x, int tile_y, bool lostSight);
};

#endif
