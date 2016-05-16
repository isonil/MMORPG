
#ifndef UTILITY_MODULE_HPP
#define UTILITY_MODULE_HPP

#include "DataModule.hpp"

class UtilityModule
    : public virtual DataModule
{
    public:
        bool isOutOfMap(int tile_x, int tile_y);
        bool isStackable(int objectType);
        bool isPassable(int tile_x, int tile_y);
        void compileAndVerifyAllScripts();
        void updateDelta();
        float getDistance(float x1, float y1, float x2, float y2);
        float getDistance(const CharacterClass &ch1, const CharacterClass &ch2);
        vPoint getScreenPosition(float posX, float posY, const ViewClass &View);
        vPoint getWorldPosition(float posX, float posY, const ViewClass &View);
        std::string intToString(int val);
        std::string floatToString(float val);
        std::string spacesToUnderscores(const std::string &str);
        std::string underscoresToSpaces(const std::string &str);
        bool compileScript(ScriptClass &script, std::string &errorOutput);
        void changeEntityValue(wxGridEvent& event);
        void updateErrorLog();
        void removeTileType(int index);
        void removeSceneryType(int index);
        void removeObjectType(int index);
        void removeNPCType(int index);
        void resetEntityPreferencesGrid();
        void validateNPCMovementCheckpoints(const std::vector <CharacterClass> &NPC);
        void changeNPCMovementCheckpoint(int NPCIndex, int checkpointIndex);
};

#endif
