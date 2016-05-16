#include "ChooseTalkOption.hpp"

#include "Master.hpp"

void Packet <PACKET_CHOOSE_TALK_OPTION>::onReceive(const ENetEvent &event)
{
    int option = -1;
    sscanf((char*)event.packet->data, "%*c %d", &option);

    bool optionAllowed = true;
    if(Master::getInstance().Player[(int)event.peer->data].NPCInteraction.type == NPC_INTERACTION_TYPE_TALK) {
        _assert_return(Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex >= 0 &&
                       Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex < (int)Master::getInstance().NPC.size(),
                       Master::getInstance().Player[(int)event.peer->data].name.c_str(),
                       (int)event.peer->data,
                       "NPCInteraction.NPCIndex out of bounds in processPacket_chooseTalkOption.");

        if(Master::getInstance().NPC[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType < 0) {
            Master::getInstance().Player[(int)event.peer->data].NPCInteraction.type = NPC_INTERACTION_TYPE_NONE;
            return;
        }

        _assert_return(Master::getInstance().NPC[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType < (int)Master::getInstance().NPCType.size(),
                       Master::getInstance().Player[(int)event.peer->data].name.c_str(),
                       (int)event.peer->data,
                       "NPC type index out of bounds in processPacket_chooseTalkOption.");
        _assert_return(Master::getInstance().Player[(int)event.peer->data].NPCInteraction.dialogueBlock >= 0 &&
                       Master::getInstance().Player[(int)event.peer->data].NPCInteraction.dialogueBlock < (int)Master::getInstance().NPCType[Master::getInstance().NPC[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].dialogueBlock.size(),
                       Master::getInstance().Player[(int)event.peer->data].name.c_str(),
                       (int)event.peer->data,
                       "Dialogue block out of bounds in processPacket_chooseTalkOption.");
    }

    if(Master::getInstance().Player[(int)event.peer->data].NPCInteraction.type != NPC_INTERACTION_TYPE_TALK)
        optionAllowed = false;
    else if(option < 0 || option >= (int)Master::getInstance().NPCType[Master::getInstance().NPC[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].dialogueBlock[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.dialogueBlock].option.size())
        optionAllowed = false;
    else {
        NPCTypeClass::DialogueBlockClass::OptionClass *option_p;
        option_p = &Master::getInstance().NPCType[Master::getInstance().NPC[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].dialogueBlock[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.dialogueBlock].option[option];
        if(option_p->requiredQuestProgressIndex >= 0) {
            _assert_return(option_p->requiredQuestProgressIndex < (int)Master::getInstance().Quest.size(),
                           Master::getInstance().Player[(int)event.peer->data].name.c_str(),
                           (int)event.peer->data,
                           "Dialogue option required quest progress index out of bounds in processPacket_chooseTalkOption.");
            if(Master::getInstance().Player[(int)event.peer->data].questProgress[option_p->requiredQuestProgressIndex] < option_p->requiredQuestProgressFrom ||
               Master::getInstance().Player[(int)event.peer->data].questProgress[option_p->requiredQuestProgressIndex] > option_p->requiredQuestProgressTo)
                optionAllowed = false;
        }
    }
    if(optionAllowed) {
        bool startTrade = false;
        int tradeNPCIndex = Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex;

        if(Master::getInstance().NPCType[Master::getInstance().NPC[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].dialogueBlock[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.dialogueBlock].option[option].startTrade) {
            startTrade = true;
        }
        Master::getInstance().Player[(int)event.peer->data].NPCInteraction.dialogueBlock = Master::getInstance().NPCType[Master::getInstance().NPC[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].dialogueBlock[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.dialogueBlock].option[option].leadToBlock;
        _assert_return(Master::getInstance().Player[(int)event.peer->data].NPCInteraction.dialogueBlock < (int)Master::getInstance().NPCType[Master::getInstance().NPC[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].dialogueBlock.size(),
                       Master::getInstance().Player[(int)event.peer->data].name.c_str(),
                       (int)event.peer->data,
                       "Dialogue block after change out of bounds in processPacket_chooseTalkOption.");
        if(Master::getInstance().Player[(int)event.peer->data].NPCInteraction.dialogueBlock < 0) {
            Master::getInstance().endNPCInteraction(Master::getInstance().Player[(int)event.peer->data]);
        }
        else if(Master::getInstance().NPCType[Master::getInstance().NPC[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].dialogueBlock[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.dialogueBlock].scriptIndex >= 0) {
            _assert_return(Master::getInstance().NPCType[Master::getInstance().NPC[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].dialogueBlock[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.dialogueBlock].scriptIndex
                           < (int)Master::getInstance().Script.size(),
                           Master::getInstance().Player[(int)event.peer->data].name.c_str(),
                           (int)event.peer->data,
                           "Script index out of bounds in processPacket_chooseTalkOption.");
            Master::getInstance().runScript((int)event.peer->data, Master::getInstance().NPCType[Master::getInstance().NPC[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex].NPCType].dialogueBlock[Master::getInstance().Player[(int)event.peer->data].NPCInteraction.dialogueBlock].scriptIndex);
        }

        if(startTrade) {
            if(Master::getInstance().Player[(int)event.peer->data].NPCInteraction.type == NPC_INTERACTION_TYPE_TALK) {
                Master::getInstance().endNPCInteraction(M.Player[(int)event.peer->data]);
            }
            Master::getInstance().Player[(int)event.peer->data].NPCInteraction.type = NPC_INTERACTION_TYPE_TRADE;
            Master::getInstance().Player[(int)event.peer->data].NPCInteraction.NPCIndex = tradeNPCIndex;

            std::string packet = Packet <PACKET_TRADE_WITH_NPC_OBJECTS_LIST>::construct(M.Player[(int)event.peer->data]);
            M.Player[(int)event.peer->data].sendPacket(packet);
        }

        if(Master::getInstance().Player[(int)event.peer->data].NPCInteraction.type == NPC_INTERACTION_TYPE_TALK) {
            std::string packet = Packet <PACKET_CURRENT_DIALOGUE_BLOCK>::construct(M.Player[(int)event.peer->data]);
            M.Player[(int)event.peer->data].sendPacket(packet);
        }
    }
}
