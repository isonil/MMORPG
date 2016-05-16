#include "ObjectChangeOnGround.hpp"

#include <sstream>
#include "Master.hpp"

std::string Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(int tile_x, int tile_y, bool lostSight)
{
    _assert_return_value(!Master::getInstance().isOutOfMap(tile_x, tile_y), NULL, 0,
                         "Position out of bounds in getObjectChangeOnGroundPacket.", "")

    std::ostringstream oss;

    if(lostSight || M.Tile[tile_x][tile_y].object.empty()) {
        oss << PACKET_OBJECT_CHANGE_ON_GROUND << ' ' << tile_x << ' ' << tile_y;
    }
    else {
        oss << PACKET_OBJECT_CHANGE_ON_GROUND << ' ' << tile_x << ' ' << tile_y << ' ';
        std::list <ObjectClass>::iterator it;
        int skip_quantity = (int)Master::getInstance().Tile[tile_x][tile_y].object.size()-OBJECTS_PER_TILE_LIMIT;
        if(skip_quantity < 0) skip_quantity = 0;
        int i = 0;
        for(it=Master::getInstance().Tile[tile_x][tile_y].object.begin(); it!=Master::getInstance().Tile[tile_x][tile_y].object.end(); ++it, ++i) {
            if(i == skip_quantity) break;
        }
        for(; it!=Master::getInstance().Tile[tile_x][tile_y].object.end(); ++it) {
            Master::getInstance().getObjectParams(oss, *it);
        }
    }
    return oss.str();
}
