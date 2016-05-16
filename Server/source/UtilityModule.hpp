#ifndef UTILITY_MODULE_HPP
#define UTILITY_MODULE_HPP

#include <queue>
#include "DataModule.hpp"
#include "utility.hpp"

class UtilityModule
    : public virtual DataModule
{
    public:
        bool isDead(const CharacterClass &ch);
        bool isProjectileExplosive(int projectileType);
        bool isOutOfMap(int tile_x, int tile_y);
        bool isViewSegmentOutOfBounds(int viewSegment_x, int viewSegment_y);
        bool isValidCharacterSet(char characterSet);
        bool isStackable(int objectType);
        bool isPickUpAble(int objectType);
        bool isPassable(int tile_x, int tile_y);
        bool isShootThroughAble(int tile_x, int tile_y);
        bool isOnSight(const CharacterClass &ch1, const CharacterClass &ch2);
        bool isPassableBetween(float first_x, float first_y, float second_x, float second_y);
        bool isShootThroughAbleBetween(float first_x, float first_y, float second_x, float second_y);
        bool canObjectBePlacedOnSlot(int objectType, int slotIndex);
        bool NPCCollides(int NPCIndex);
        bool playerCollides(int playerIndex);
        void updateDelta();
        void getObjectParams(std::ostringstream &oss, const ObjectClass &object);
        void runScript(int playerIndex, int scriptIndex);
        int logInToAccount(const std::string &name, const std::string &password);
        bool characterShoot(const CharacterClass &character, char shooterCharacterSet, int shooterIndex);
        bool characterShootGrenadeLauncher(const CharacterClass &character, char shooterCharacterSet, int shooterIndex, int target_x, int target_y);
        bool characterThrowGrenade(const CharacterClass &character, char shooterCharacterSet, int shooterIndex, int target_x, int target_y);
        void changePlayerExpBy(int playerIndex, int value);
        void changeCharacterParamTo(CharacterClass &character, char characterSet, int characterIndex, int param, int value, bool sendToAllInView);
        void changeCharacterParamBy(CharacterClass &character, char characterSet, int characterIndex, int param, int value, bool sendToAllInView);
        bool changeCharacterPosition(char characterSet, int characterIndex, float x, float y, bool searchFreeSpace);
        char projectileMove(ProjectileClass &projectile);
        void makeExplosion(const ProjectileClass &projectile, float x, float y);
        void characterHitByProjectile(char characterSet, int characterIndex, const ProjectileClass &projectile);
        void updateTileForPlayers(int tile_x, int tile_y);
        bool NPCMove(int NPCIndex, float dir, float speedMultiplier = 1.f);
        bool NPCMoveConstantDistance(int NPCIndex, float dir, float distance);
        void removePlayerIndexFromTile(int tile_x, int tile_y, int playerIndex);
        void removeNPCIndexFromTile(int tile_x, int tile_y, int NPCIndex);
        void removePlayerIndexFromViewSegment(int viewSegment_x, int viewSegment_y, int playerIndex);
        void removeNPCIndexFromViewSegment(int viewSegment_x, int viewSegment_y, int NPCIndex);
        void endNPCInteraction(CharacterClass &player);
        void getNextMoveTile(TilePositionClass &tilePosition, float from_x, float from_y, float to_x, float to_y);
        bool addObjectToPlayerInventory(CharacterClass &player, const ObjectClass &object);
        std::string getPlayerRichName(CharacterClass &player, int playerIndex);
        float getDistance(float x1, float y1, float x2, float y2);
        float getDistance(const CharacterClass &ch1, const CharacterClass &ch2);
        void validateNPCMovementCheckpoints(const std::vector <CharacterClass> &NPC);
        void logOutPlayer(int playerIndex);
        void forceDisconnect(ENetPeer *peer);
        void sendToAllPlayersInView(const char *packet, int viewSegmentsDistance, float x, float y, int playerIndexException);
        void getCurrentDialogueBlockPacket(char *packet, CharacterClass &player);
        void getTradeWithNPCObjectsListPacket(char *packet, CharacterClass &player);
        void getObjectChangeOnGroundPacket(char *packet, int tile_x, int tile_y, bool lostSight);
        void getCharacterParamChangePacket(char *packet, const CharacterClass &character, char characterSet, int characterIndex, int param);
        void getCharacterLostSightPacket(char *packet, char characterSet, int characterIndex);
        void getCharacterParamsPacket(char *packet, const CharacterClass &character, char characterSet, int characterIndex);
        void getProjectileHitPacket(char *packet, int hitType, int x, int y, int projectileId);
        void getShotPacket(char *packet, char characterSet, int characterIndex, int x, int y, int dir, int projectileId, int weaponObjectType);
        void getGrenadeLauncherShotPacket(char *packet, char characterSet, int characterIndex, int x, int y, int dir, int projectileId, int weaponObjectType);
        void getGrenadeThrowPacket(char *packet, char characterSet, int characterIndex, int x, int y, int dir, int projectileId, int target_x, int target_y);
        void getQuestProgressChangePacket(char *packet, const CharacterClass &player, int questIndex);
        void getObjectChangeInInventoryPacket(char *packet, int inv_x, int inv_y, const ObjectClass &object);
        void getObjectChangeOnSlotPacket(char *packet, int slotIndex, const ObjectClass &object);
        void getCharacterSlotObjectChangePacket(char *packet, char characterSet, int characterIndex, int slotIndex, int objectType);
};

#endif
