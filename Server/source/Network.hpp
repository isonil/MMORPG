#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <enet/enet.h>
#include <string>
#include "Packets.hpp"

class Network
{
    private:
        void(*onReceivePacketMap[MAX_PACKET_INDEX])(const ENetEvent &event);
        ENetHost *host;

        void processPacket(const ENetEvent &event);

    public:
        void init();
        void sendPacket(ENetPeer *peer, const std::string &str);
        void manageNetworkEvents();

        Network();
};

#endif
