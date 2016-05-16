/**
* @file
* @brief File containing NetworkModule class.
*/

#ifndef NETWORK_MODULE_HPP
#define NETWORK_MODULE_HPP

#include "DataModule.hpp"
#include "UtilityModule.hpp"

/**
* @brief One of @ref MODULES_GROUP. Class holding methods managing
* network events called directly from game loop.
*
* @ingroup MODULES_GROUP
*
* Each frame in game loop manageNetworkEvents() is called.\n
* When packet arrives processPacket() is then called which may call
* other method depending on packet type.
*
* All methods processing a single packet called from processPacket()
* have following syntax:
* @code
*   processPacket_X
* @endcode
* where X is packet type name.
*
* @see PACKET_DEFINES_GROUP
*/
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
        void processPacket_objectChangeOnGround(const ENetEvent &event);
        void processPacket_objectChangeInInventory(const ENetEvent &event);
        void processPacket_objectChangeOnSlot(const ENetEvent &event);
        void processPacket_characterParams(const ENetEvent &event);
        void processPacket_characterLostSight(const ENetEvent &event);
        void processPacket_shot(const ENetEvent &event);
        void processPacket_grenadeLauncherShot(const ENetEvent &event);
        void processPacket_grenadeThrow(const ENetEvent &event);
        void processPacket_projectileHit(const ENetEvent &event);
        void processPacket_characterParamChange(const ENetEvent &event);
        void processPacket_serverMessage(const ENetEvent &event);
        void processPacket_localChatMessage(const ENetEvent &event);
        void processPacket_globalChatMessage(const ENetEvent &event);
        void processPacket_privateChatMessage(const ENetEvent &event);
        void processPacket_privateChatRequest(const ENetEvent &event);
        void processPacket_characterSlotObjectChange(const ENetEvent &event);
        void processPacket_dayTime(const ENetEvent &event);
        void processPacket_weather(const ENetEvent &event);
        void processPacket_currentDialogueBlock(const ENetEvent &event);
        void processPacket_tradeWithNPCObjectsList(const ENetEvent &event);
        void processPacket_questProgressChange(const ENetEvent &event);
};

#endif
