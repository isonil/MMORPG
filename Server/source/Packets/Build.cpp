#include "Build.hpp"

/*
int objectType = -1;
    int x = 0, y = 0;
    sscanf((char*)event.packet->data, "%*c %d %d %d", &objectType, &x, &y);

    bool buildAllowed = true;
    if(objectType < 0 || objectType >= (int)ObjectType.size()) buildAllowed = false;
    else if(ObjectType[objectType].baseType != OBJECT_BASE_TYPE_STRUCTURE) buildAllowed = false;
    else if(isOutOfMap(x, y)) buildAllowed = false;
    else if(!Tile[x][y].object.empty()) buildAllowed = false;

    if(buildAllowed) {
        //check if player can reach destination
        //check if player is not too far
        //check materials
        //check collision
        Tile[x][y].object.push_back(ObjectClass());
        Tile[x][y].object.back().type=objectType;
        Tile[x][y].object.back().param[OBJECT_PARAM_OWNER]=(int)event.peer->data;
        Tile[x][y].object.back().param[OBJECT_PARAM_CONDITION]=100;
        //send to all players
        //updateTileForPlayers
    }*/
