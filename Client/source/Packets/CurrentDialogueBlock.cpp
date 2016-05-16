#include "CurrentDialogueBlock.hpp"

#include "Master.hpp"

void Packet <PACKET_CURRENT_DIALOGUE_BLOCK>::onReceive(const ENetEvent &event)
{
    char ch;
    int NPCIndex = -1, NPCTextIndex = -1, optionsQuantity = 0;
    std::istringstream iss((char*)event.packet->data);
    iss >> ch >> NPCIndex >> NPCTextIndex >> optionsQuantity;

    _assert(NPCTextIndex < (int)Master::getInstance().Text.size(),
            "NPC text index out of bounds in processPacket_currentDialogueBlock.");

    Master::getInstance().currentDialogueBlock.NPCIndex = NPCIndex;
    Master::getInstance().currentDialogueBlock.NPCTextIndex = NPCTextIndex;
    Master::getInstance().currentDialogueBlock.optionTextIndex.clear();
    for(int i=0; i<optionsQuantity; ++i) {
        int optionTextIndex = -1;
        iss >> optionTextIndex;
        _assert(optionTextIndex < (int)Master::getInstance().Text.size(),
                "Option text index out of bounds in processPacket_currentDialogueBlock.");
        Master::getInstance().currentDialogueBlock.optionTextIndex.push_back(optionTextIndex);
    }
    if(NPCIndex >= 0) Master::getInstance().currentDialogueBlock.active = true;
    else Master::getInstance().currentDialogueBlock.active = false;
}
