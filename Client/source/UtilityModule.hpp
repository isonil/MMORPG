
#ifndef UTILITY_MODULE_HPP
#define UTILITY_MODULE_HPP

#include "DataModule.hpp"

class UtilityModule
    : public virtual DataModule
{
    protected:
        void resetWorld();
        void saveSettings();
        bool isOutOfMap(int tile_x, int tile_y);
        bool isStackable(int objectType);
        bool isPassable(int tile_x, int tile_y);
        bool isValidCharacterSet(char characterSet);
        bool canObjectBePlacedOnSlot(int objectType, int slotIndex);
        bool playerCollides();
        bool playerMove(float dir);
        void updateDelta();
        void assignParamsToObject(ObjectClass &Object, int objectType, int p1, int p2, int p3);
        void addMessageToChat(std::vector <std::string> &chat, const std::string &message, int chatTab);
        void addMessageToCurrentChat(const std::string &message);
        void playPositionalSound(const SAMPLE *sound, float receiver_x, float receiver_y, float source_x, float source_y);
        void adjustSoundVolumeSmoothly(audiere::OutputStreamPtr &sound, float volumeTarget);
        void onCloseWindowCallback(const WindowClass &window);
        float getDistance(float x1, float y1, float x2, float y2);
        float getDistance(const CharacterClass &ch1, const CharacterClass &ch2);
        vPoint getScreenPosition(float posX, float posY, const ViewClass &View);
        vPoint getWorldPosition(float posX, float posY, const ViewClass &View);
        void sendPacket(int channel, const char *packet_str);
        void sendChangeObjectPlaceRequest(int destinationPlace, int p1, int p2, int p3);
        void getChooseTalkOptionPacket(char *packet, int num);
        void getChangeObjectPlaceRequestPacket(char *packet, int place, int p1, int p2, int p3, int destPlace, int dp1, int dp2, int dp3);
        void getEndCurrentNPCInteractionPacket(char *packet);
};

#endif
