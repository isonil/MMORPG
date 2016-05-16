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
    {PACKET_LOG_IN,                       Packet <PACKET_LOG_IN>::onReceive},
    {PACKET_CHARACTER_POSITION,           Packet <PACKET_CHARACTER_POSITION>::onReceive},
    {PACKET_OBJECT_CHANGE_ON_GROUND,      Packet <PACKET_OBJECT_CHANGE_ON_GROUND>::onReceive},
    {PACKET_OBJECT_CHANGE_IN_INVENTORY,   Packet <PACKET_OBJECT_CHANGE_IN_INVENTORY>::onReceive},
    {PACKET_OBJECT_CHANGE_ON_SLOT,        Packet <PACKET_OBJECT_CHANGE_ON_SLOT>::onReceive},
    {PACKET_CHARACTER_PARAMS,             Packet <PACKET_CHARACTER_PARAMS>::onReceive},
    {PACKET_CHARACTER_LOST_SIGHT,         Packet <PACKET_CHARACTER_LOST_SIGHT>::onReceive},
    {PACKET_SHOT,                         Packet <PACKET_SHOT>::onReceive},
    {PACKET_GRENADE_LAUNCHER_SHOT,        Packet <PACKET_GRENADE_LAUNCHER_SHOT>::onReceive},
    {PACKET_GRENADE_THROW,                Packet <PACKET_GRENADE_THROW>::onReceive},
    {PACKET_PROJECTILE_HIT,               Packet <PACKET_PROJECTILE_HIT>::onReceive},
    {PACKET_CHARACTER_PARAM_CHANGE,       Packet <PACKET_CHARACTER_PARAM_CHANGE>::onReceive},
    {PACKET_SERVER_MESSAGE,               Packet <PACKET_SERVER_MESSAGE>::onReceive},
    {PACKET_LOCAL_CHAT_MESSAGE,           Packet <PACKET_LOCAL_CHAT_MESSAGE>::onReceive},
    {PACKET_GLOBAL_CHAT_MESSAGE,          Packet <PACKET_GLOBAL_CHAT_MESSAGE>::onReceive},
    {PACKET_PRIVATE_CHAT_MESSAGE,         Packet <PACKET_PRIVATE_CHAT_MESSAGE>::onReceive},
    {PACKET_CHARACTER_SLOT_OBJECT_CHANGE, Packet <PACKET_CHARACTER_SLOT_OBJECT_CHANGE>::onReceive},
    {PACKET_DAY_TIME,                     Packet <PACKET_DAY_TIME>::onReceive},
    {PACKET_WEATHER,                      Packet <PACKET_WEATHER>::onReceive},
    {PACKET_CURRENT_DIALOGUE_BLOCK,       Packet <PACKET_CURRENT_DIALOGUE_BLOCK>::onReceive},
    {PACKET_TRADE_WITH_NPC_OBJECTS_LIST,  Packet <PACKET_TRADE_WITH_NPC_OBJECTS_LIST>::onReceive},
    {PACKET_QUEST_PROGRESS_CHANGE,        Packet <PACKET_QUEST_PROGRESS_CHANGE>::onReceive}
};

  //Packet <character> dummy ## variableName(onReceivePacket);

//#define REGISTER_PACKET(variableName)                       \
  //static Packet <variableName> dummy ## variableName;
//REGISTER_PACKET(PACKET_LOG_IN);
//REGISTER_PACKET(PACKET_CHARACTER_POSITION);

#endif
