#include "Network.hpp"

#include "global.hpp"
#include "Master.hpp"

void Network::processPacket(const ENetEvent &event)
{
    if(!event.packet->dataLength) return;
    uchar type = event.packet->data[0];
    if(onReceivePacketMap[type] != NULL) {
        onReceivePacketMap[type](event);
    }
    else {
        _error("Received unknown packet (%c).", type);
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
    host = enet_host_create(0, 1, 2, 0, 0);
    if(!host) {
        error("Could not create an ENet host.");
    }
    info("ENet host created.");

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

void Network::sendPacket(const std::string &str)
{
    if(host == NULL || peer == NULL) return;

    ENetPacket *packet = enet_packet_create(str.c_str(), str.size()+1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(host);
}

void Network::manageNetworkEvents()
{
    if(host == NULL || peer == NULL) return;

    static ENetEvent event;
    int hostStatus;

    while(1) {
        hostStatus = enet_host_service(host, &event, 0);
        if(hostStatus < 0) error("An error occured in enet_host_service (returned %d).", hostStatus);
        if(!hostStatus) break;

        switch(event.type) {
            case ENET_EVENT_TYPE_NONE:
                break;

            case ENET_EVENT_TYPE_CONNECT:
                _info("Connection established with %u:%u.",
                      event.peer->address.host,
                      event.peer->address.port);
                peer = event.peer;
                isConnected_ = true;
                isConnectedToServer = true;
                // BLLS
                sendPacket(Packet <PACKET_LOG_IN>::construct(Master::getInstance().login, Master::getInstance().password));
                // BLLS
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                if(event.packet->dataLength &&
                   event.packet->data[event.packet->dataLength-1] == 0) {
                    currentPacketData = (char*)event.packet->data;
                    //processPacket(event);
                    Master::getInstance().getNetwork().processPacket(event);
                    // BLLS
                }
                currentPacketData = NULL;
                enet_packet_destroy(event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                Master::getInstance().getUserInterface().showError("Disconnected from server.");
                _info("Disconnected from server.");
                isConnected_ = false;
                isConnectedToServer = false;
                // BLLS
                playerCharacterID = -1;
                Master::getInstance().login[0] = 0;
                Master::getInstance().password[0] = 0;
                // BLLS
                break;

            default:
                break;
        }
    }
}

bool Network::startConnecting()
{
    if(host == NULL) return false;

    ENetAddress address;
    address.port = 3847;
    enet_address_set_host(&address, "127.0.0.1");
    peer = enet_host_connect(host, &address, 2, 0);
    if(!peer) {
        Master::getInstance().getUserInterface().showError("No available peers for connection.");
        return false;
    }
    return true;
}

void Network::disconnect()
{
    if(peer != NULL) enet_peer_disconnect_now(peer, 0);
    peer = NULL;
    isConnected_ = false;
}

bool Network::isConnected()
{
    return isConnected_;
}

int Network::getPing()
{
    if(peer != NULL) return peer->lastRoundTripTime;
    return 0;
}

Network::Network()
    :   host(NULL),
        peer(NULL),
        isConnected_(false)
{
    for(size_t i=0; i<MAX_PACKET_INDEX; ++i) {
        onReceivePacketMap[i] = NULL;
    }
}
