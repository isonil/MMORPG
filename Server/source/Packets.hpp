#ifndef PACKETS_HPP
#define PACKETS_HPP

#include <utility>
#include "Packets/LogIn.hpp"
#include "Packets/CharacterPosition.hpp"
#include "Packets/ObjectChangeOnGround.hpp"
#include "Packets/ObjectChangeInInventory.hpp"
#include "Packets/ObjectChangeOnSlot.hpp"
#include "Packets/CharacterParams.hpp"
#include "Packets/CharacterLostSight.hpp"
#include "Packets/Shot.hpp"
#include "Packets/GrenadeLauncherShot.hpp"
#include "Packets/GrenadeThrow.hpp"
#include "Packets/ProjectileHit.hpp"
#include "Packets/CharacterParamChange.hpp"
#include "Packets/Build.hpp"
#include "Packets/ChangeObjectPlaceRequest.hpp"
#include "Packets/ServerMessage.hpp"
#include "Packets/LocalChatMessage.hpp"
#include "Packets/GlobalChatMessage.hpp"
#include "Packets/PrivateChatMessage.hpp"
#include "Packets/PrivateChatRequest.hpp"
#include "Packets/CharacterSlotObjectChange.hpp"
#include "Packets/DayTime.hpp"
#include "Packets/Weather.hpp"
#include "Packets/StartTalkWithNPC.hpp"
#include "Packets/ChooseTalkOption.hpp"
#include "Packets/CurrentDialogueBlock.hpp"
#include "Packets/TradeWithNPCObjectsList.hpp"
#include "Packets/TradeWithNPCBuyObject.hpp"
#include "Packets/QuestProgressChange.hpp"
#include "Packets/EndCurrentNPCInteraction.hpp"

#define MAX_PACKET_INDEX (256)

const std::pair <char, void(*)(const ENetEvent &event)> onReceivePacketList[] =
{
    {PACKET_LOG_IN,                      Packet <PACKET_LOG_IN>::onReceive},
    {PACKET_CHARACTER_POSITION,          Packet <PACKET_CHARACTER_POSITION>::onReceive},
    {PACKET_SHOT,                        Packet <PACKET_SHOT>::onReceive},
    {PACKET_GRENADE_LAUNCHER_SHOT,       Packet <PACKET_GRENADE_LAUNCHER_SHOT>::onReceive},
    {PACKET_GRENADE_THROW,               Packet <PACKET_GRENADE_THROW>::onReceive},
    {PACKET_CHANGE_OBJECT_PLACE_REQUEST, Packet <PACKET_CHANGE_OBJECT_PLACE_REQUEST>::onReceive},
    {PACKET_LOCAL_CHAT_MESSAGE,          Packet <PACKET_LOCAL_CHAT_MESSAGE>::onReceive},
    {PACKET_GLOBAL_CHAT_MESSAGE,         Packet <PACKET_GLOBAL_CHAT_MESSAGE>::onReceive},
    {PACKET_PRIVATE_CHAT_MESSAGE,        Packet <PACKET_PRIVATE_CHAT_MESSAGE>::onReceive},
    {PACKET_PRIVATE_CHAT_REQUEST,        Packet <PACKET_PRIVATE_CHAT_REQUEST>::onReceive},
    {PACKET_START_TALK_WITH_NPC,         Packet <PACKET_START_TALK_WITH_NPC>::onReceive},
    {PACKET_CHOOSE_TALK_OPTION,          Packet <PACKET_CHOOSE_TALK_OPTION>::onReceive},
    {PACKET_TRADE_WITH_NPC_BUY_OBJECT,   Packet <PACKET_TRADE_WITH_NPC_BUY_OBJECT>::onReceive},
    {PACKET_END_CURRENT_NPC_INTERACTION, Packet <PACKET_END_CURRENT_NPC_INTERACTION>::onReceive}
};

#endif
