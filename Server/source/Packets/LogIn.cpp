#include "LogIn.hpp"

#include <sstream>
#include "global.hpp"
#include "Master.hpp"

void Packet <PACKET_LOG_IN>::onReceive(const ENetEvent &event)
{
    if((int)event.peer->data >= 0 && (int)event.peer->data < (int)Master::getInstance().Player.size()) {
        Master::getInstance().logOutPlayer((int)event.peer->data);
    }
    event.peer->data = (void*)-1;

    char *name = new char[event.packet->dataLength+1];
    char *password = new char[event.packet->dataLength+1];
    char *clientVersion = new char[event.packet->dataLength+1];

    name[0] = 0, password[0] = 0, clientVersion[0] = 0;
    sscanf((char*)event.packet->data, "%*c %s %s %s", clientVersion, name, password);
    if(strlen(name) > LOGIN_LENGTH_LIMIT ||
       strlen(password) > PASSWORD_LENGTH_LIMIT) {
        Master::getInstance().forceDisconnect(event.peer);
        return;
    }

    int status;
    if(strcmp(clientVersion, VERSION)) status = LOG_IN_ERROR_OUTDATED_CLIENT;
    else status = M.logInToAccount(name, password);

    if(status >= 0) {
        event.peer->data = (void*)status;
        Master::getInstance().Player[status].peer = event.peer;
        Master::getInstance().Player[status].isOnline = true;
        printf("Player %s (id %d) logged in.\n", name, status);
    }

    char packet[MAX_PACKET_SIZE_LOG_IN];
    if(status >= 0) {
        std::ostringstream oss_packet;
        oss_packet
            << PACKET_LOG_IN << " "
            << status << " "
            << (int)Master::getInstance().Player[status].x << " "
            << (int)Master::getInstance().Player[status].y << " "
            << int(Master::getInstance().Player[status].dir*100.f) << " "
            << Master::getInstance().Player[status].param[CHARACTER_PARAM_HEALTH] << " "
            << Master::getInstance().Player[status].param[CHARACTER_PARAM_MAX_HEALTH] << " "
            << Master::getInstance().Player[status].param[CHARACTER_PARAM_EXPERIENCE] << " "
            << Master::getInstance().Player[status].param[CHARACTER_PARAM_LEVEL] << " "
            << Master::getInstance().Player[status].param[CHARACTER_PARAM_BASE_X] << " "
            << Master::getInstance().Player[status].param[CHARACTER_PARAM_BASE_Y] << " "
            << (int)Master::getInstance().Weather.dayTimeInMinutes << " "
            << Master::getInstance().Weather.rainType << " "
            << Master::getInstance().Weather.snowType << " "
            << Master::getInstance().Weather.stormType << " "
            << Master::getInstance().Weather.fogType << " "
            << Master::getInstance().Quest.size() << " ";
        for(size_t i=0; i<Master::getInstance().Quest.size(); ++i) {
            oss_packet << Master::getInstance().Player[status].questProgress[i] << " ";
        }
        for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
            Master::getInstance().getObjectParams(oss_packet, M.Player[status].objectOnSlot[i]);
        }
        for(size_t i=0; i<Master::getInstance().Player[status].objectInInventory.size(); ++i) {
            for(size_t j=0; j<Master::getInstance().Player[status].objectInInventory[i].size(); ++j) {
                Master::getInstance().getObjectParams(oss_packet, M.Player[status].objectInInventory[i][j]);
            }
        }
        sprintf(packet, "%s", oss_packet.str().c_str());
    }
    else sprintf(packet, "%c %d", PACKET_LOG_IN, status);

    M.getNetwork().sendPacket(event.peer, packet);
    if(status < 0) return;

    Master::getInstance().Player[status].timeout_playerSendDayTime = globalTime+30000.0+rand()%30000;
    Master::getInstance().Player[status].NPCInteraction.type = NPC_INTERACTION_TYPE_NONE;
    sprintf(packet, "%s", Packet <PACKET_CHARACTER_PARAMS>::construct(M.Player[status], CHARACTER_PLAYER, status).c_str());
    M.getNetwork().sendPacket(event.peer, packet);

    int tile_x = int(M.Player[status].x/TILE_SIZE);
    int tile_y = int(M.Player[status].y/TILE_SIZE);
    int viewSegment_x = int(M.Player[status].x/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));
    int viewSegment_y = int(M.Player[status].y/(TILE_SIZE*PLAYER_TILES_VIEW_DISTANCE));

    _assert_return(!Master::getInstance().isOutOfMap(tile_x, tile_y), M.Player[status].name.c_str(), status,
                   "Position out of bounds in processPacket_logIn.");
    _assert_return(!Master::getInstance().isViewSegmentOutOfBounds(viewSegment_x, viewSegment_y), M.Player[status].name.c_str(), status,
                   "View segment out of bounds in processPacket_logIn.");

    for(int i=tile_x-PLAYER_TILES_VIEW_DISTANCE; i<=tile_x+PLAYER_TILES_VIEW_DISTANCE; ++i) {
        for(int j=tile_y-PLAYER_TILES_VIEW_DISTANCE; j<=tile_y+PLAYER_TILES_VIEW_DISTANCE; ++j) {
            if(Master::getInstance().isOutOfMap(i, j)) continue;
            if(!Master::getInstance().Tile[i][j].object.empty()) {
                std::string packet = Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::construct(i, j, false);
                M.getNetwork().sendPacket(event.peer, packet);
            }
        }
    }
    for(size_t i=0; i<M.Player.size(); ++i) {
        if((int)i == (int)event.peer->data) continue;
        if(!Master::getInstance().Player[i].isOnline) continue;

        bool onSight = Master::getInstance().isOnSight(M.Player[i], M.Player[(int)event.peer->data]);
        if(onSight) {
            std::string packet1;
            std::string packet2;
            packet1 = Packet <PACKET_CHARACTER_PARAMS>::construct(Master::getInstance().Player[i], CHARACTER_PLAYER, i);
            packet2 = Packet <PACKET_CHARACTER_PARAMS>::construct(Master::getInstance().Player[(int)event.peer->data], CHARACTER_PLAYER, (int)event.peer->data);
            M.getNetwork().sendPacket(event.peer, packet1);
            M.Player[i].sendPacket(packet2);
        }
    }
    for(size_t i=0; i<M.NPC.size(); ++i) {
        bool onSight = Master::getInstance().isOnSight(M.NPC[i], M.Player[(int)event.peer->data]);
        if(onSight) {
            std::string packet = Packet <PACKET_CHARACTER_PARAMS>::construct(M.NPC[i], CHARACTER_NPC, i);
            M.getNetwork().sendPacket(event.peer, packet);
        }
    }

    Master::getInstance().Tile[tile_x][tile_y].playerIndex.push_back(status);
    Master::getInstance().ViewSegment[viewSegment_x][viewSegment_y].playerIndex.push_back(status);

    delete []name;
    delete []password;
    delete []clientVersion;
}

std::string Packet <PACKET_LOG_IN>::construct()
{

}

