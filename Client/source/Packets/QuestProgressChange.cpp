#include "QuestProgressChange.hpp"

#include "Master.hpp"

void Packet <PACKET_QUEST_PROGRESS_CHANGE>::onReceive(const ENetEvent &event)
{
    int questIndex = -1, questProgress = -1;
    sscanf((char*)event.packet->data, "%*c %d %d", &questIndex, &questProgress);

    _assert(questIndex >= 0 && questIndex < (int)Master::getInstance().Quest.size(),
            "Quest index out of bounds in processPacket_questProgressChange.");
    _assert(questProgress >= 0 && questProgress <= 100,
            "Incorrect quest progress in processPacket_questProgressChange.");

    Master::getInstance().Quest[questIndex].progress = questProgress;
}
