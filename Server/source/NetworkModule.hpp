#ifndef NETWORK_MODULE_HPP
#define NETWORK_MODULE_HPP

#include "DataModule.hpp"
#include "UtilityModule.hpp"

class NetworkModule
    : public virtual DataModule,
      public virtual UtilityModule
{
    protected:
        void manageNetworkEvents();

    private:
        void processPacket(const ENetEvent &event);
        void processPacket_logIn(const ENetEvent &event);
        void processPacket_characterPosition(const ENetEvent &event);
        void processPacket_shot(const ENetEvent &event);
        void processPacket_grenadeLauncherShot(const ENetEvent &event);
        void processPacket_grenadeThrow(const ENetEvent &event);
        void processPacket_build(const ENetEvent &event);
        void processPacket_changeObjectPlaceRequest(const ENetEvent &event);
        void processPacket_localChatMessage(const ENetEvent &event);
        void processPacket_globalChatMessage(const ENetEvent &event);
        void processPacket_privateChatMessage(const ENetEvent &event);
        void processPacket_privateChatRequest(const ENetEvent &event);
        void processPacket_startTalkWithNPC(const ENetEvent &event);
        void processPacket_chooseTalkOption(const ENetEvent &event);
        void processPacket_tradeWithNPCBuyObject(const ENetEvent &event);
        void processPacket_endCurrentNPCInteraction(const ENetEvent &event);
};

#endif
