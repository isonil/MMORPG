#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <string>
#include <vector>
#include <list>
#include "global.hpp"

class ObjectClass
{
    public:
        int type;
        int param[OBJECT_PARAMS_QUANTITY];

        double timeout_shot;

        inline void clear()
        {
            type = -1;
            timeout_shot = 0.0;
            for(int i=0; i<OBJECT_PARAMS_QUANTITY; ++i) {
                param[i] = 0;
            }
            param[OBJECT_PARAM_ADDON_1] = -1;
            param[OBJECT_PARAM_ADDON_2] = -1;
            param[OBJECT_PARAM_ADDON_3] = -1;
            param[OBJECT_PARAM_QUANTITY] = 1;
        }

        ObjectClass() {
            clear();
        }
        ObjectClass(int newType) {
            clear();
            type = newType;
        }
};

class TilePositionClass
{
    public:
        int x, y;
        TilePositionClass()
            :   x(0), y(0) {
        }
        TilePositionClass(int newX, int newY)
            :   x(newX), y(newY) {
        }
};

class CharacterClass
{
    public:
        class NPCInteractionClass
        {
            public:
                int type;
                int NPCIndex;
                int dialogueBlock;
                NPCInteractionClass()
                    :   type(NPC_INTERACTION_TYPE_NONE),
                        NPCIndex(-1),
                        dialogueBlock(-1) {
                }
        };

        ENetPeer *peer;
        std::string name, password;

        float x, y, dir, respawn_x, respawn_y, respawn_dir;
        bool isOnline;
        NPCInteractionClass NPCInteraction;
        int NPCType, team;

        ObjectClass objectOnSlot[CHARACTER_OBJECT_SLOTS_QUANTITY];
        std::vector <std::vector <ObjectClass> > objectInInventory;
        int param[CHARACTER_PARAMS_QUANTITY];
        int questProgress[MAX_QUESTS_QUANTITY];

        double timeout_logIn;
        double timeout_playerSendPosition;
        double timeout_playerSendDayTime;
        double timeout_respawn;
        double timeout_grenadeLauncherShot;
        double timeout_grenadeThrow;
        double timeout_AI_checkTarget;
        double timeout_AI_changeDodgeMoveDir;
        double timeout_AI_wander_turn;

        char AI_targetCharacterSet;
        int AI_targetIndex;
        int AI_dodgeMoveDir;
        bool AI_targetCanShootTo;
        bool AI_staticDirection;
        int AI_movementType;
        float AI_movementDistance;
        std::vector <TilePositionClass> AI_movementCheckpoint;
        TilePositionClass AI_nextMoveTile;

        inline void clearTimeouts()
        {
            timeout_logIn = 0.0;
            timeout_playerSendPosition = 0.0;
            timeout_playerSendDayTime = 0.0;
            timeout_respawn = 0.0;
            timeout_grenadeLauncherShot = 0.0;
            timeout_grenadeThrow = 0.0;
            timeout_AI_checkTarget = 0.0;
            timeout_AI_changeDodgeMoveDir = 0.0;
            timeout_AI_wander_turn = 0.0;
        }

        inline void clearAI()
        {
            AI_targetCharacterSet = 0;
            AI_targetIndex = -1;
            AI_dodgeMoveDir = rand()%4;
            AI_targetCanShootTo = false;
            AI_staticDirection = false;
            AI_movementType = AI_MOVEMENT_TYPE_STAND;
            AI_movementDistance = 0.f;
            AI_nextMoveTile.x = -1;
            AI_nextMoveTile.y = -1;
        }

        void sendPacket(const std::string &str);

        CharacterClass()
            :   peer(NULL),
                name("undefined"), password("undefined"),
                x(0.f), y(0.f), dir(0.f), respawn_x(0.f), respawn_y(0.f), respawn_dir(0.f),
                isOnline(false),
                NPCType(-1), team(TEAM_0),
                objectInInventory(CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH, std::vector <ObjectClass> (CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT)) {
                    for(int i=0; i<CHARACTER_PARAMS_QUANTITY; ++i) {
                        param[i] = 0;
                    }
                    for(int i=0; i<MAX_QUESTS_QUANTITY; ++i) {
                        questProgress[i] = 0;
                    }
                    param[CHARACTER_PARAM_HEALTH] = 100;
                    param[CHARACTER_PARAM_MAX_HEALTH] = 100;
                    param[CHARACTER_PARAM_LEVEL] = 1;
                    param[CHARACTER_PARAM_FACTION] = -1;
                    clearTimeouts();
                    clearAI();
        }
        CharacterClass(const std::string &new_name, const std::string &new_password)
            :   peer(NULL),
                name(new_name), password(new_password),
                x(0.f), y(0.f), dir(0.f), respawn_x(0.f), respawn_y(0.f), respawn_dir(0.f),
                isOnline(false),
                NPCType(-1), team(TEAM_0),
                objectInInventory(CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH, std::vector <ObjectClass> (CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT)) {
                    for(int i=0; i<CHARACTER_PARAMS_QUANTITY; ++i) {
                        param[i] = 0;
                    }
                    for(int i=0; i<MAX_QUESTS_QUANTITY; ++i) {
                        questProgress[i] = 0;
                    }
                    param[CHARACTER_PARAM_HEALTH] = 100;
                    param[CHARACTER_PARAM_MAX_HEALTH] = 100;
                    param[CHARACTER_PARAM_LEVEL] = 1;
                    param[CHARACTER_PARAM_FACTION] = -1;
                    clearTimeouts();
                    clearAI();
        }
};

class NPCTypeClass
{
    public:
        class LootObjectClass
        {
            public:
                int objectType;
                int quantityFrom, quantityTo, chance;
                LootObjectClass(int newObjectType, int newQuantityFrom, int newQuantityTo, int newChance)
                    :   objectType(newObjectType),
                        quantityFrom(newQuantityFrom), quantityTo(newQuantityTo),
                        chance(newChance) {
                }
        };
        class TradeObjectClass
        {
            public:
                int objectType;
                TradeObjectClass(int newObjectType)
                    :   objectType(newObjectType) {
                }
        };
        class DialogueBlockClass
        {
            public:
                class OptionClass
                {
                    public:
                        int textIndex;
                        int requiredQuestProgressIndex, requiredQuestProgressFrom, requiredQuestProgressTo;
                        int leadToBlock;
                        bool startTrade;

                        OptionClass()
                            :   textIndex(-1),
                                requiredQuestProgressIndex(-1), requiredQuestProgressFrom(0), requiredQuestProgressTo(0),
                                leadToBlock(-1),
                                startTrade(false) {
                        }
                };
                int NPCTextIndex;
                int scriptIndex;
                std::vector <OptionClass> option;

                DialogueBlockClass()
                    :   NPCTextIndex(-1),
                        scriptIndex(-1) {
                }
        };

        std::string name;
        int maxHealth, team;
        std::vector <LootObjectClass> lootObject;
        std::vector <TradeObjectClass> tradeObject;
        std::vector <DialogueBlockClass> dialogueBlock;
        int objectTypeOnSlot[CHARACTER_OBJECT_SLOTS_QUANTITY];

        NPCTypeClass()
            :   name("undefined"),
                maxHealth(100), team(TEAM_0) {
                    for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
                        objectTypeOnSlot[i] = -1;
                    }
        }
        NPCTypeClass(const std::string newName, int newMaxHealth, int newTeam)
            :   name(newName),
                maxHealth(newMaxHealth), team(newTeam) {
                    for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
                        objectTypeOnSlot[i] = -1;
                    }
        }
};

class ObjectTypeClass
{
    public:
        std::string IDName, name;
        int baseType, weaponType, equipmentType, attachmentType;
        bool isPassable, isShootThroughAble, isAutomatic, isStackable;
        int baseDamage, baseShotDelay;
        int value;

        double timeout_shot;

        ObjectTypeClass()
            :   IDName("ID_UNDEFINED"), name("undefined"),
                baseType(OBJECT_BASE_TYPE_NONE), weaponType(WEAPON_TYPE_NONE), equipmentType(EQUIPMENT_TYPE_NONE), attachmentType(ATTACHMENT_TYPE_NONE),
                isPassable(true), isShootThroughAble(true), isAutomatic(false), isStackable(false),
                baseDamage(0), baseShotDelay(1000),
                value(0),
                timeout_shot(0.0) {
        }
};

class ObjectSlotClass
{
    public:
        int baseType, equipmentType;

        ObjectSlotClass()
            :   baseType(OBJECT_BASE_TYPE_NONE), equipmentType(EQUIPMENT_TYPE_NONE) {
        }
        ObjectSlotClass(int newBaseType, int newEquipmentType)
            :   baseType(newBaseType), equipmentType(newEquipmentType) {
        }
};

class WeaponAttachmentSlotClass
{
    public:
        int attachmentType;

        WeaponAttachmentSlotClass()
            :   attachmentType(ATTACHMENT_TYPE_NONE) {
        }
        WeaponAttachmentSlotClass(int newAttachmentType)
            :   attachmentType(newAttachmentType) {
        }
};

class QuestClass
{
    public:
        std::string IDName, name;
        bool isLoaded;

        QuestClass()
            :   IDName("ID_UNDEFINED"),
                name("undefined"),
                isLoaded(false) {
        }
};

class SceneryTypeClass
{
    public:
        std::string name;
        bool isPassable, isShootThroughAble;

        SceneryTypeClass()
            :   name("undefined"),
                isPassable(true), isShootThroughAble(true) {
        }
};

class ScriptClass
{
    public:
        class InstructionClass
        {
            public:
                int callFunc;
                bool ifStatement;
                int ifStatementJumpToInstruction;

                int p1int, p2int, p3int;
                std::string p1str, p2str, p3str;

                InstructionClass()
                    :   callFunc(-1),
                        ifStatement(false),
                        ifStatementJumpToInstruction(-1),
                        p1int(-1), p2int(-1), p3int(-1) {
                }
        };

        std::vector <InstructionClass> instruction;
        std::string IDName;
        std::string script;

        bool isLoaded;

        ScriptClass()
            :   IDName("ID_UDNEFINED"),
                isLoaded(false) {
        }
};

class TileTypeClass
{
    public:
        std::string name;
        bool isPassable, isShootThroughAble;

        TileTypeClass()
            :   name("undefined"),
                isPassable(true), isShootThroughAble(true) {
        }
};

class TileClass
{
    public:
        int tileType, sceneryType;
        std::list <ObjectClass> object;

        std::vector <int> playerIndex;
        std::vector <int> NPCIndex;

        TilePositionClass BFS_fromTile;
        bool BFS_visited;

        TileClass()
            :   tileType(-1), sceneryType(-1),
                BFS_fromTile(TilePositionClass(-1, -1)),
                BFS_visited(false) {
        }
        TileClass(int newTileType, int newSceneryType)
            :   tileType(newTileType), sceneryType(newSceneryType),
                BFS_fromTile(TilePositionClass(-1, -1)),
                BFS_visited(false) {
        }
};

class ViewSegmentClass
{
    public:
        std::vector <int> playerIndex;
        std::vector <int> NPCIndex;
};

class ProjectileClass
{
    public:
        float x, y, dir, target_x, target_y;
        float distanceTraveled;
        char ownerCharacterType;
        int id, ownerIndex, projectileType;

        float grenadeThrowDistance;
        float grenadeFlySpeed;
        bool grenadeHitObstaclePacketSent;
        double timeout_grenadeExplode;

        int team, damage;
        bool pvp;

        ProjectileClass(char newOwnerCharacterType, int newOwnerIndex, float newX, float newY, float newDir, int newId, int newProjectileType, int newTeam, int newDamage, bool newPvp)
            :   x(newX), y(newY), dir(newDir), target_x(0.f), target_y(0.f),
                distanceTraveled(0.f),
                ownerCharacterType(newOwnerCharacterType),
                id(newId), ownerIndex(newOwnerIndex), projectileType(newProjectileType),
                grenadeThrowDistance(0.f),
                grenadeFlySpeed(20.f),
                grenadeHitObstaclePacketSent(false),
                timeout_grenadeExplode(0.0),
                team(newTeam), damage(newDamage), pvp(newPvp) {
        }
};

class FactionClass
{
    public:
        std::string name, shortName;
        std::vector <int> memberPlayerIndex;
        std::vector <int> invitedPlayerIndex;

        FactionClass()
            :   name("undefined"),
                shortName("undefined") {
        }
};

class WeatherClass
{
    public:
        double dayTimeInMinutes;
        int rainType, snowType, stormType, fogType;

        WeatherClass()
            :   dayTimeInMinutes(0.0),
                rainType(RAIN_TYPE_NONE), snowType(SNOW_TYPE_NONE), stormType(STORM_TYPE_NONE), fogType(FOG_TYPE_NONE) {
        }
};

#endif
