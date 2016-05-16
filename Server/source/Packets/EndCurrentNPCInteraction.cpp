#include "EndCurrentNPCInteraction.hpp"

#include "Master.hpp"

void Packet <PACKET_END_CURRENT_NPC_INTERACTION>::onReceive(const ENetEvent &event)
{
    Master::getInstance().Player[(int)event.peer->data].NPCInteraction.type = NPC_INTERACTION_TYPE_NONE;
}
