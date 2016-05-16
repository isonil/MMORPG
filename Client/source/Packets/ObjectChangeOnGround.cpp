#include "ObjectChangeOnGround.hpp"

#include "Master.hpp"

void Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::onReceive(const ENetEvent &event)
{
    char ch;
    int objectType = -1, x = 0, y = 0, p1 = -1, p2 = -1, p3 = -1;
    std::istringstream packet((char*)event.packet->data);
    packet >> ch >> x >> y;

    _assert(!Master::getInstance().isOutOfMap(x, y) ,"Position out of bounds in processPacket_objectChangeOnGround.");
    Master::getInstance().Tile[x][y].object.clear();
    while(packet >> objectType >> p1 >> p2 >> p3) {
        if(objectType >= 0) {
            Master::getInstance().Tile[x][y].object.push_back(ObjectClass());
            _assert(objectType < (int)Master::getInstance().ObjectType.size(),
                    "Object type out of bounds in processPacket_objectChangeOnGround.");
            Master::getInstance().assignParamsToObject(Master::getInstance().Tile[x][y].object.back(), objectType, p1, p2, p3);
        }
    }
}
