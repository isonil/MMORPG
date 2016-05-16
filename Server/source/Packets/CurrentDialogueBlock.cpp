#include "CurrentDialogueBlock.hpp"

#include <sstream>
#include "Master.hpp"

std::string Packet <PACKET_CURRENT_DIALOGUE_BLOCK>::construct(Character &player)
{
    std::ostringstream oss;
    if(player.NPCInteraction.type == NPC_INTERACTION_TYPE_TALK) {
        oss << PACKET_CURRENT_DIALOGUE_BLOCK << " "
            << player.NPCInteraction.NPCIndex << " ";
    }
    else {
        oss << PACKET_CURRENT_DIALOGUE_BLOCK << " "
            << "-1";
    }

    if(player.NPCInteraction.type == NPC_INTERACTION_TYPE_TALK) {
        if(player.NPCInteraction.NPCIndex < 0 ||
           player.NPCInteraction.NPCIndex >= (int)M.NPC.size()) {
            player.NPCInteraction.type = NPC_INTERACTION_TYPE_NONE;
            _assert_return_value(0, NULL, 0, "NPCInteraction.NPCIndex out of bounds in getCurrentDialogueBlockPacket.", "");
        }

        CharacterClass *interlocutor = &M.NPC[player.NPCInteraction.NPCIndex];
        _assert_return_value(interlocutor->NPCType >= 0 && interlocutor->NPCType < (int)M.NPCType.size(), NULL, 0,
                             "Interlocutor NPC type out of bounds in getCurrentDialogueBlockPacket.", "");
        _assert_return_value(player.NPCInteraction.dialogueBlock >= 0 &&
                             player.NPCInteraction.dialogueBlock < (int)M.NPCType[interlocutor->NPCType].dialogueBlock.size(), NULL, 0,
                            "Dialogue block out of bounds in getCurrentDialogueBlockPacket.", "");

        oss << M.NPCType[interlocutor->NPCType].dialogueBlock[player.NPCInteraction.dialogueBlock].NPCTextIndex << " "
            << M.NPCType[interlocutor->NPCType].dialogueBlock[player.NPCInteraction.dialogueBlock].option.size() << " ";

        for(size_t i=0; i<M.NPCType[interlocutor->NPCType].dialogueBlock[player.NPCInteraction.dialogueBlock].option.size(); ++i) {
            const NPCTypeClass::DialogueBlockClass::OptionClass *option;
            option = &M.NPCType[interlocutor->NPCType].dialogueBlock[player.NPCInteraction.dialogueBlock].option[i];

            bool sendOption = false;
            if(option->requiredQuestProgressIndex >= 0) {
                if(player.questProgress[option->requiredQuestProgressIndex] >= option->requiredQuestProgressFrom &&
                   player.questProgress[option->requiredQuestProgressIndex] <= option->requiredQuestProgressTo) {
                    sendOption = true;
                }
            }
            else sendOption = true;

            if(sendOption) {
                oss << M.NPCType[interlocutor->NPCType].dialogueBlock[player.NPCInteraction.dialogueBlock].option[i].textIndex << " ";
            }
            else oss << "-1 ";
        }
    }
    return oss.str();
}
