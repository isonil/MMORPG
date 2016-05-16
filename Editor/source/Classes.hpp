#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <SFML/Graphics.hpp>
#include <wx/treectrl.h>
#include <string>
#include <list>
#include "global.hpp"

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

class TileTypeClass
{
    public:
        std::string name, resourcesName;
        std::vector <std::vector <sf::Texture> > colorMapTexture;
        std::vector <std::vector <sf::Texture> > normalMapTexture;
        std::vector <std::vector <sf::Sprite> > colorMapSprite;
        std::vector <std::vector <sf::Sprite> > normalMapSprite;

        int widthQuantity, heightQuantity;
        bool isPassable, isShootThroughAble;

        bool isLoaded;

        TileTypeClass()
            :   name("undefined"), resourcesName("undefined"),
                widthQuantity(0), heightQuantity(0),
                isPassable(true), isShootThroughAble(true),
                isLoaded(false) {
        }
};

class SceneryTypeClass
{
    public:
        std::string name, resourcesName;
        sf::Texture colorMapTexture;
        sf::Texture normalMapTexture;
        sf::Texture heightMapTexture;
        sf::Sprite colorMapSprite;
        sf::Sprite normalMapSprite;
        sf::Sprite heightMapSprite;
        int natureType, layer;
        bool isPassable, isShootThroughAble;
        float offsetX, offsetY;

        bool isLoaded;

        SceneryTypeClass()
            :   name("undefined"), resourcesName("undefined"),
                natureType(NATURE_TYPE_NONE), layer(LAYER_ONE),
                isPassable(true), isShootThroughAble(true),
                offsetX(0.f), offsetY(0.f),
                isLoaded(false) {
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
                        std::string text;

                        int requiredQuestProgressIndex, requiredQuestProgressFrom, requiredQuestProgressTo;
                        int leadToBlock;
                        bool startTrade;

                        wxTreeItemId treeItemId;

                        OptionClass()
                            :   textIndex(-1),
                                requiredQuestProgressIndex(-1), requiredQuestProgressFrom(0), requiredQuestProgressTo(0),
                                leadToBlock(-1),
                                startTrade(false),
                                treeItemId(NULL) {
                        }
                };
                int NPCTextIndex;
                std::string NPCText;

                int scriptIndex;
                std::vector <OptionClass> option;

                wxTreeItemId treeItemId;

                DialogueBlockClass()
                    :   NPCTextIndex(-1),
                        scriptIndex(-1),
                        treeItemId(NULL) {
                }
        };

        std::string name;
        int maxHealth, team;

        std::vector <LootObjectClass> lootObject;
        std::vector <TradeObjectClass> tradeObject;
        std::vector <DialogueBlockClass> dialogueBlock;
        int objectTypeOnSlot[CHARACTER_OBJECT_SLOTS_QUANTITY];

        bool isLoaded;

        NPCTypeClass()
            :   name("undefined"),
                maxHealth(100), team(TEAM_0),
                isLoaded(false) {
                    for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
                        objectTypeOnSlot[i] = -1;
                    }
        }
        NPCTypeClass(const std::string newName, int newMaxHealth, int newTeam)
            :   name(newName),
                maxHealth(newMaxHealth), team(newTeam),
                isLoaded(false) {
                    for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
                        objectTypeOnSlot[i] = -1;
                    }
        }
};

class ObjectTypeClass
{
    private:

    public:
        std::string IDName, name, resourcesName;

        sf::Texture colorMapTexture, normalMapTexture, heightMapTexture;
        sf::Sprite colorMapSprite, normalMapSprite, heightMapSprite;

        sf::Texture onCharacterColorMapTexture, onCharacterNormalMapTexture, onCharacterHeightMapTexture;
        sf::Sprite onCharacterColorMapSprite, onCharacterNormalMapSprite, onCharacterHeightMapSprite;

        sf::Texture onWeaponColorMapTexture, onWeaponNormalMapTexture, onWeaponHeightMapTexture;
        sf::Sprite onWeaponColorMapSprite, onWeaponNormalMapSprite, onWeaponHeightMapSprite;

        // for equipment //
        sf::Texture onCharacterNoWeaponColorMapTexture, onCharacterNoWeaponNormalMapTexture, onCharacterNoWeaponHeightMapTexture;
        sf::Sprite onCharacterNoWeaponColorMapSprite, onCharacterNoWeaponNormalMapSprite, onCharacterNoWeaponHeightMapSprite;

        sf::Texture onCharacterSmallWeaponColorMapTexture, onCharacterSmallWeaponNormalMapTexture, onCharacterSmallWeaponHeightMapTexture;
        sf::Sprite onCharacterSmallWeaponColorMapSprite, onCharacterSmallWeaponNormalMapSprite, onCharacterSmallWeaponHeightMapSprite;

        sf::Texture onCharacterBigWeaponColorMapTexture, onCharacterBigWeaponNormalMapTexture, onCharacterBigWeaponHeightMapTexture;
        sf::Sprite onCharacterBigWeaponColorMapSprite, onCharacterBigWeaponNormalMapSprite, onCharacterBigWeaponHeightMapSprite;
        // // // // // //

        int baseType, weaponType, equipmentType, attachmentType, layer;
        float offsetX, offsetY, spriteScale;
        bool isPassable, isShootThroughAble, isAutomatic, isStackable;
        int baseDamage;
        int baseShotDelay;
        int value;

        bool isLoaded;

        ObjectTypeClass()
            :   IDName("ID_UNDEFINED"), name("undefined"), resourcesName("undefined"),
                baseType(OBJECT_BASE_TYPE_NONE), weaponType(WEAPON_TYPE_NONE), equipmentType(EQUIPMENT_TYPE_NONE), attachmentType(ATTACHMENT_TYPE_NONE), layer(LAYER_ONE),
                offsetX(0.f), offsetY(0.f), spriteScale(1.f),
                isPassable(true), isShootThroughAble(true), isAutomatic(false), isStackable(false),
                baseDamage(0), baseShotDelay(1000),
                value(0),
                isLoaded(false) {
        }
};

class ObjectClass
{
    private:

    public:
        int type;
        int param[OBJECT_PARAMS_QUANTITY];

        double timeout_shot;

        inline void clear()
        {
            type = -1;
            for(int i=0; i<OBJECT_PARAMS_QUANTITY; ++i) {
                param[i] = 0;
            }
            param[OBJECT_PARAM_ADDON_1] = -1;
            param[OBJECT_PARAM_ADDON_2] = -1;
            param[OBJECT_PARAM_ADDON_3] = -1;
            timeout_shot = 0.0;
        }

        ObjectClass() {
            clear();
        }
        ObjectClass(int newType) {
            clear();
            type = newType;
        }
};

class ObjectSlotClass
{
    private:

    public:
        int baseType, equipmentType;

        sf::Texture defaultOnCharacterNoWeaponColorMapTexture, defaultOnCharacterNoWeaponNormalMapTexture, defaultOnCharacterNoWeaponHeightMapTexture;
        sf::Sprite defaultOnCharacterNoWeaponColorMapSprite, defaultOnCharacterNoWeaponNormalMapSprite, defaultOnCharacterNoWeaponHeightMapSprite;

        sf::Texture defaultOnCharacterSmallWeaponColorMapTexture, defaultOnCharacterSmallWeaponNormalMapTexture, defaultOnCharacterSmallWeaponHeightMapTexture;
        sf::Sprite defaultOnCharacterSmallWeaponColorMapSprite, defaultOnCharacterSmallWeaponNormalMapSprite, defaultOnCharacterSmallWeaponHeightMapSprite;

        sf::Texture defaultOnCharacterBigWeaponColorMapTexture, defaultOnCharacterBigWeaponNormalMapTexture, defaultOnCharacterBigWeaponHeightMapTexture;
        sf::Sprite defaultOnCharacterBigWeaponColorMapSprite, defaultOnCharacterBigWeaponNormalMapSprite, defaultOnCharacterBigWeaponHeightMapSprite;

        std::string spritesPath;

        ObjectSlotClass()
            :   baseType(OBJECT_BASE_TYPE_NONE), equipmentType(EQUIPMENT_TYPE_NONE) {
        }
        ObjectSlotClass(int newBaseType, int newEquipmentType, const std::string &newSpritesPath)
            :   baseType(newBaseType), equipmentType(newEquipmentType),
                spritesPath(newSpritesPath) {
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

class CharacterClass
{
    public:
        std::string name;
        float x, y, respawn_x, respawn_y, dir, respawn_dir;
        int NPCType, team;

        ObjectClass objectOnSlot[CHARACTER_OBJECT_SLOTS_QUANTITY];
        std::vector <std::vector <ObjectClass> > objectInInventory;
        int param[CHARACTER_PARAMS_QUANTITY];

        std::vector <std::string> privateChat;

        bool AI_staticDirection;
        int AI_movementType;
        float AI_movementDistance;
        std::vector <TilePositionClass> AI_movementCheckpoint;

        CharacterClass()
            :   x(0.f), y(0.f), respawn_x(0.f), respawn_y(0.f), dir(0.f), respawn_dir(0.f),
                NPCType(-1), team(TEAM_0),
                objectInInventory(CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH, std::vector <ObjectClass> (CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT)),
                AI_staticDirection(false),
                AI_movementType(AI_MOVEMENT_TYPE_STAND),
                AI_movementDistance(0.f) {
                    for(int i=0; i<CHARACTER_PARAMS_QUANTITY; ++i) {
                        param[i] = 0;
                    }
                    param[CHARACTER_PARAM_HEALTH] = 100;
                    param[CHARACTER_PARAM_MAX_HEALTH] = 100;
                    param[CHARACTER_PARAM_LEVEL] = 1;
                    param[CHARACTER_PARAM_FACTION] = -1;
                    privateChat.push_back("Private conversation.");
        }
};

class TileClass
{
    public:
        int tileType, sceneryType;
        std::list <ObjectClass> object;

        TileClass()
            :   tileType(-1), sceneryType(-1) {
        }
        TileClass(int newTileType, int newSceneryType)
            :   tileType(newTileType), sceneryType(newSceneryType) {
        }
};

class LightTypeClass
{
    public:
        sf::Texture texture;
        sf::Sprite sprite;
        std::string textureName;
        float originX, originY;

        LightTypeClass()
            :   textureName("undefined"),
                originX(0), originY(0) {
        }
};

class LightSourceClass
{
    public:
        float x, y;
        int type;
        sf::Vector3f color;

        LightSourceClass()
            :   x(0.f), y(0.f),
                type(-1),
                color(1.f, 1.f, 1.f) {
        }
        LightSourceClass(float newX, float newY, int newType, const sf::Vector3f &newColor)
            :   x(newX), y(newY),
                type(newType),
                color(newColor) {
        }
};

class QuestClass
{
    public:
        class QuestProgressTextClass
        {
            public:
                int progressFrom, progressTo;
                std::string text;

                QuestProgressTextClass()
                    :   progressFrom(-1), progressTo(-1),
                        text("undefined") {
                }
                QuestProgressTextClass(int newProgressFrom, int newProgressTo, const std::string &newText)
                    :   progressFrom(newProgressFrom), progressTo(newProgressTo),
                        text(newText) {
                }
        };

        std::string IDName, name;
        int progress;
        std::vector <QuestProgressTextClass> questProgressText;
        int questType;

        bool isLoaded;

        QuestClass()
            :   IDName("ID_UNDEFINED"), name("undefined"),
                progress(0),
                questType(QUEST_TYPE_NONE),
                isLoaded(false) {
        }
};

class RainDropClass
{
    public:
        float x, y;
        bool isSplashing;
        int splashFrame;

        double timeout_splash;
        double timeout_nextSplashFrame;

        RainDropClass() {}
        RainDropClass(float newX, float newY)
            :   x(newX), y(newY), isSplashing(false), splashFrame(-1), timeout_splash(globalTime+rand()%1300), timeout_nextSplashFrame(0.0) {
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
        bool isLoaded;
        std::string IDName, script;

        ScriptClass()
            :   isLoaded(false),
                IDName("ID_UNDEFINED") {
        }
};

class TextClass
{
    public:
        std::string str;
        bool isLoaded;

        TextClass(const std::string &newStr)
            :   str(newStr),
                isLoaded(false) {
        }
        TextClass()
            :   str("undefined"),
                isLoaded(false) {
        }
};

class ViewClass
{
    public:
        float x, y;
        float distance;

        ViewClass()
            :   x(0.f), y(0.f), distance(1.f) {
        }
        ViewClass(float newX, float newY, float newDistance)
            :   x(newX), y(newY), distance(newDistance) {
        }
};

class vPoint {
    public:
        float x, y;

        inline vPoint operator - (const vPoint &p) const
        {
            return vPoint(x-p.x, y-p.y);
        }

        inline vPoint operator + (const vPoint &p) const
        {
            return vPoint(x+p.x, y+p.y);
        }

        inline vPoint operator * (float val) const
        {
            return vPoint(x*val, y*val);
        }

        float lineSide(const vPoint &p1, const vPoint &p2) const
        {
            float w = (p2.x-p1.x)*(y-p1.y)-(p2.y-p1.y)*(x-p1.x);
            if(fabs(w) < 0.001f) return 0.f;
            else if(w < 0.f) return -1.f;
            else return 1.f;
        }

        void normalize()
        {
            float len = sqrt(x*x+y*y);
            x /= len;
            y /= len;
        }

        vPoint() {}
        vPoint(float new_x, float new_y) :
                    x(new_x), y(new_y) {
        }
};

class ShadowCasterClass
{
    public:
        std::vector <vPoint> vertex;
};

#endif
