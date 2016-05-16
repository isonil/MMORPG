#include "CharacterPosition.hpp"

#include <sstream>
#include "Master.hpp"

void Packet <PACKET_CHARACTER_POSITION>::onReceive(const ENetEvent &event)
{
    int x = 0, y = 0, dir = 0;
    sscanf((char*)event.packet->data, "%*c %d %d %d", &x, &y, &dir);

    //todo speedlimit

    Master::getInstance().Player[(int)event.peer->data].dir = dir/100.f;

    int tile_x = x/TILE_SIZE;
    int tile_y = y/TILE_SIZE;
    if(tile_x < 0) x = 0;
    if(tile_y < 0) y = 0;
    if(tile_x >= int(Master::getInstance().Tile.size())) {
        x = (int)Master::getInstance().Tile.size()*TILE_SIZE-TILE_SIZE;
        tile_x = x/TILE_SIZE;
    }
    if(tile_y >= int(Master::getInstance().Tile[tile_x].size())) {
        y = (int)Master::getInstance().Tile[tile_x].size()*TILE_SIZE-TILE_SIZE;
        tile_y = y/TILE_SIZE;
    }

    bool stepSizeLimitExceeded = false;
    if(fabs(Master::getInstance().Player[(int)event.peer->data].x-x) > STEP_SIZE_LIMIT) {
        if(x > Master::getInstance().Player[(int)event.peer->data].x) {
            x = int(Master::getInstance().Player[(int)event.peer->data].x+STEP_SIZE_LIMIT);
        }
        else x = int(Master::getInstance().Player[(int)event.peer->data].x-STEP_SIZE_LIMIT);
        stepSizeLimitExceeded = true;
    }
    if(fabs(Master::getInstance().Player[(int)event.peer->data].y-y) > STEP_SIZE_LIMIT) {
        if(y > Master::getInstance().Player[(int)event.peer->data].y) {
            y = int(Master::getInstance().Player[(int)event.peer->data].y+STEP_SIZE_LIMIT);
        }
        else y = int(Master::getInstance().Player[(int)event.peer->data].y-STEP_SIZE_LIMIT);
        stepSizeLimitExceeded = true;
    }

    bool cantMove = false;
    if(!stepSizeLimitExceeded) {
        if(!Master::getInstance().changeCharacterPosition(CHARACTER_PLAYER, (int)event.peer->data, x, y, false)) {
            cantMove = true;
        }
    }

    if(stepSizeLimitExceeded || cantMove) {
        std::string packet = Packet <PACKET_CHARACTER_POSITION>::construct(CHARACTER_PLAYER,
                                                                           (int)event.peer->data,
                                                                           Master::getInstance().Player[(int)event.peer->data].x,
                                                                           Master::getInstance().Player[(int)event.peer->data].y,
                                                                           Master::getInstance().Player[(int)event.peer->data].dir);
        M.Player[(int)event.peer->data].sendPacket(packet);
    }

    int viewSegment_x = int(Master::getInstance().Player[(int)event.peer->data].x/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));
    int viewSegment_y = int(Master::getInstance().Player[(int)event.peer->data].y/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));

    for(int i=viewSegment_x-1; i<=viewSegment_x+1; ++i) {
        for(int j=viewSegment_y-1; j<=viewSegment_y+1; ++j) {
            if(Master::getInstance().isViewSegmentOutOfBounds(i, j)) continue;

            for(size_t k=0; k<Master::getInstance().ViewSegment[i][j].playerIndex.size(); ++k) {
                int playerIndex = Master::getInstance().ViewSegment[i][j].playerIndex[k];
                if(playerIndex == (int)event.peer->data) continue;
                if(Master::getInstance().isOnSight(Master::getInstance().Player[(int)event.peer->data], Master::getInstance().Player[playerIndex])) {
                    std::string packet = Packet <PACKET_CHARACTER_POSITION>::construct(CHARACTER_PLAYER,
                                                                                       playerIndex,
                                                                                       Master::getInstance().Player[playerIndex].x,
                                                                                       Master::getInstance().Player[playerIndex].y,
                                                                                       Master::getInstance().Player[playerIndex].dir);
                    M.Player[(int)event.peer->data].sendPacket(packet);
                }
            }
            for(size_t k=0; k<Master::getInstance().ViewSegment[i][j].NPCIndex.size(); ++k) {
                int NPCIndex = Master::getInstance().ViewSegment[i][j].NPCIndex[k];
                if(Master::getInstance().isOnSight(Master::getInstance().Player[(int)event.peer->data], Master::getInstance().NPC[NPCIndex])) {
                    std::string packet = Packet <PACKET_CHARACTER_POSITION>::construct(CHARACTER_NPC,
                                                                                       NPCIndex,
                                                                                       Master::getInstance().NPC[NPCIndex].x,
                                                                                       Master::getInstance().NPC[NPCIndex].y,
                                                                                       Master::getInstance().NPC[NPCIndex].dir);
                    M.Player[(int)event.peer->data].sendPacket(packet);
                }
            }
        }
    }

    if(globalTime >= Master::getInstance().Player[(int)event.peer->data].timeout_playerSendDayTime) {
        Master::getInstance().Player[(int)event.peer->data].timeout_playerSendDayTime = globalTime+30000.0+rand()%30000;

        std::string packet = Packet <PACKET_DAY_TIME>::construct(Master::getInstance().Weather.dayTimeInMinutes);
        M.Player[(int)event.peer->data].sendPacket(packet);
    }
}

std::string Packet <PACKET_CHARACTER_POSITION>::construct(char characterSet, int characterID, float x, float y, float dir)
{
    std::ostringstream oss;
    oss << PACKET_CHARACTER_POSITION << ' ' << characterSet << ' ' << characterID << ' '
        << (int)x << ' ' << (int)y << ' ' << int(dir*100.f);
    return oss.str();
}
