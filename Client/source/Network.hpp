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
        ENetPeer *peer;
        bool isConnected_;

        void processPacket(const ENetEvent &event);

    public:
        void init();
        void sendPacket(const std::string &str);
        void manageNetworkEvents();
        bool startConnecting();
        void disconnect();
        bool isConnected();
        int getPing();

        Network();
};

#endif
