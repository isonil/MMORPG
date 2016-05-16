#include "StartTalkWithNPC.hpp"

#include "Master.hpp"

void Packet <PACKET_START_TALK_WITH_NPC>::onReceive(const ENetEvent &event)
{
    int NPCIndex = -1;
    sscanf((char*)event.packet->data, "%*c %d", &NPCIndex);

    if(NPCIndex < 0 || NPCIndex >= (int)M.NPC.size()) return;
    if(M.NPC[NPCIndex].NPCType < 0) return;
    _assert_return(M.NPC[NPCIndex].NPCType < (int)M.NPCType.size(), M.Player[(int)event.peer->data].name.c_str(), (int)event.peer->data,
                   "NPC type out of bounds in processPacket_startTalkWithNPC.");

    bool talkAllowed = true;
    if(M.getDistance(M.Player[(int)event.peer->data], M.NPC[NPCIndex]) > NPC_INTERACTION_MAX_DISTANCE) talkAllowed = false;
    else if(M.Player[(int)event.peer->data].team != M.NPC[NPCIndex].team) talkAllowed = false;
    else if(M.NPCType[M.NPC[NPCIndex].NPCType].dialogueBlock.empty()) talkAllowed = false;
    else if(M.Player[(int)event.peer->data].NPCInteraction.type != NPC_INTERACTION_TYPE_NONE) talkAllowed = false;
    if(talkAllowed) {
        M.Player[(int)event.peer->data].NPCInteraction.type = NPC_INTERACTION_TYPE_TALK;
        M.Player[(int)event.peer->data].NPCInteraction.NPCIndex = NPCIndex;
        M.Player[(int)event.peer->data].NPCInteraction.dialogueBlock = 0;
        if(M.NPCType[M.NPC[NPCIndex].NPCType].dialogueBlock[0].scriptIndex >= 0) {
            M.runScript((int)event.peer->data, M.NPCType[M.NPC[NPCIndex].NPCType].dialogueBlock[0].scriptIndex);
        }
        if(M.Player[(int)event.peer->data].NPCInteraction.type == NPC_INTERACTION_TYPE_TALK) {
            std::string packet = Packet <PACKET_CURRENT_DIALOGUE_BLOCK>::construct(M.Player[(int)event.peer->data]);
            M.Player[(int)event.peer->data].sendPacket(packet);
        }
    }
}
