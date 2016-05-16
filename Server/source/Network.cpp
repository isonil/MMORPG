#include "Network.hpp"

#include "Master.hpp"

void Network::processPacket(const ENetEvent &event)
{
    if(!event.packet->dataLength) return;
    if((char*)event.packet->data[event.packet->dataLength-1] != 0) return;

    if(event.packet->data[0] == PACKET_LOG_IN) {
        Packet <PACKET_LOG_IN>::onReceive(event);
    }
    if((int)event.peer->data >= 0 && (int)event.peer->data < (int)M.Player.size() && M.Player[(int)event.peer->data].isOnline) {
        uchar type = event.packet->data[0];
        if(onReceivePacketMap[type] != NULL) {
            onReceivePacketMap[type](event);
        }
    }
    else {
        event.peer->data = (void*)-1;
    }
}

void Network::init()
{
    info("Initializing ENet.");
    if(enet_initialize()) {
        error("Could not initialize ENet.");
    }
    atexit(enet_deinitialize);

    info("Creating host.");
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 3847;
    host = enet_host_create(&address, 32, 2, 1500, 100000);
    if(host == NULL) {
        error("Could not create an ENet server host on port %d.", address.port);
    }
    info("ENet server host created on port %d.", address.port);

    /*
        Assigning packet receive callbacks.
        onReceivePacketList is defined as constant array.
        We have to reassign it to onReceivePacketMap to have
        constant-time complexity access to these callbacks.
        onReceivePacketCallback[packetType] will be pointer to callback.
    */

    size_t quantity = sizeof(onReceivePacketList)/sizeof(onReceivePacketList[0]);
    for(size_t i=0; i<quantity; ++i) {
        if(onReceivePacketMap[onReceivePacketList[i].first] == NULL) {
            onReceivePacketMap[onReceivePacketList[i].first] = onReceivePacketList[i].second;
        }
        else {
            _error("Packet identifier duplication (%c).", onReceivePacketList[i].first);
        }
    }
}

void Network::sendPacket(ENetPeer *peer, const std::string &str)
{
    if(host == NULL || peer == NULL) return;

    ENetPacket *packet = enet_packet_create(str.c_str(), str.size()+1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(host);
}

void Network::manageNetworkEvents()
{
    if(host == NULL) return;

    ENetEvent event;
    int hostStatus = enet_host_service(host, &event, 16);
    if(hostStatus == 0) return;
    else if(hostStatus < 0) {
        error("An error occured in enet_host_service (returned %d).", hostStatus);
    }
    switch(event.type) {
        case ENET_EVENT_TYPE_NONE:
            break;
        case ENET_EVENT_TYPE_CONNECT:
            printf("New client connected from %x:%u.\n",
                   event.peer->address.host,
                   event.peer->address.port);
                   event.peer->data = (void*)-1;
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            if(event.packet->dataLength > PACKET_FROM_CLIENT_SIZE_LIMIT) {
                M.forceDisconnect(event.peer);
            }
            else if(event.packet->dataLength) {
                currentPacketData = (char*)event.packet->data;
                processPacket(event);
            }
            currentPacketData = NULL;
            enet_packet_destroy(event.packet); //todo: CAN I DESTOY PACKET WHICH BELONGS TO ALREADY DISCONNECTED PEER?
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            if((int)event.peer->data >= 0 && (int)event.peer->data < (int)M.Player.size()) {
                M.logOutPlayer((int)event.peer->data);
            }
            else printf("Client %d disconnected.\n", (int)event.peer->data);
            event.peer->data = (void*)-1;
            break;
            //todo: DESTROY PEER???
    }
}

Network::Network()
    :   host(NULL)
{
    for(size_t i=0; i<MAX_PACKET_INDEX; ++i) {
        onReceivePacketMap[i] = NULL;
    }
}
