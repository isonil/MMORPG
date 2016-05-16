#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "global.hpp"
#include "GUIControls.hpp"

class LogicModule;
class RenderModule;
class InterfaceClass;
class RenderModule;
class LogicModule;

class MessageOverHeadClass
{
    public:
        std::string message;
        float alpha;
        bool fadesAway;
        double timeout_startFadingAway;

        MessageOverHeadClass()
            :   message(""),
                alpha(0.f),
                fadesAway(false),
                timeout_startFadingAway(0.0) {
        }
        MessageOverHeadClass(const std::string &newMessage)
            :   message(newMessage),
                alpha(0.f),
                fadesAway(false),
                timeout_startFadingAway(globalTime+5000.0) {
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
        bool isPassable;

        bool isLoaded;

        TileTypeClass()
            :   name("undefined"), resourcesName("undefined"),
                widthQuantity(0), heightQuantity(0),
                isPassable(true),
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
        sf::Texture shadowTexture;
        sf::Sprite colorMapSprite;
        sf::Sprite normalMapSprite;
        sf::Sprite heightMapSprite;
        sf::Sprite shadowSprite;
        int natureType, layer;
        bool isPassable;
        float offsetX, offsetY;

        bool isLoaded;

        SceneryTypeClass()
            :   name("undefined"), resourcesName("undefined"),
                natureType(NATURE_TYPE_NONE), layer(LAYER_ONE),
                isPassable(true),
                offsetX(0.f), offsetY(0.f),
                isLoaded(false) {
        }
};

class ObjectTypeClass
{
    private:

    public:
        std::string name, resourcesName;

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

        SAMPLE *useSound;
        int baseType, weaponType, equipmentType, attachmentType, layer;
        float offsetX, offsetY, spriteScale;
        bool isPassable, isAutomatic, isStackable;
        int baseDamage;
        int baseShotDelay;
        int value;

        bool isLoaded;

        ObjectTypeClass()
            :   name("undefined"), resourcesName("undefined"),
                useSound(NULL),
                baseType(OBJECT_BASE_TYPE_NONE), weaponType(WEAPON_TYPE_NONE), equipmentType(EQUIPMENT_TYPE_NONE), layer(LAYER_ONE),
                offsetX(0.f), offsetY(0.f), spriteScale(1.f),
                isPassable(true), isAutomatic(false), isStackable(false),
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
        float offsetX, offsetY;

        sf::Texture defaultOnCharacterNoWeaponColorMapTexture, defaultOnCharacterNoWeaponNormalMapTexture, defaultOnCharacterNoWeaponHeightMapTexture;
        sf::Sprite defaultOnCharacterNoWeaponColorMapSprite, defaultOnCharacterNoWeaponNormalMapSprite, defaultOnCharacterNoWeaponHeightMapSprite;

        sf::Texture defaultOnCharacterSmallWeaponColorMapTexture, defaultOnCharacterSmallWeaponNormalMapTexture, defaultOnCharacterSmallWeaponHeightMapTexture;
        sf::Sprite defaultOnCharacterSmallWeaponColorMapSprite, defaultOnCharacterSmallWeaponNormalMapSprite, defaultOnCharacterSmallWeaponHeightMapSprite;

        sf::Texture defaultOnCharacterBigWeaponColorMapTexture, defaultOnCharacterBigWeaponNormalMapTexture, defaultOnCharacterBigWeaponHeightMapTexture;
        sf::Sprite defaultOnCharacterBigWeaponColorMapSprite, defaultOnCharacterBigWeaponNormalMapSprite, defaultOnCharacterBigWeaponHeightMapSprite;

        std::string spritesPath;

        ObjectSlotClass()
            :   baseType(OBJECT_BASE_TYPE_NONE), equipmentType(EQUIPMENT_TYPE_NONE),
                offsetX(0.f), offsetY(0.f) {
        }
        ObjectSlotClass(int newBaseType, int newEquipmentType, float newOffsetX, float newOffsetY, const std::string &newSpritesPath)
            :   baseType(newBaseType), equipmentType(newEquipmentType),
                offsetX(newOffsetX), offsetY(newOffsetY),
                spritesPath(newSpritesPath) {
        }
};

class WeaponAttachmentSlotClass
{
    public:
        int attachmentType;
        float offsetX, offsetY;

        WeaponAttachmentSlotClass()
            :   attachmentType(ATTACHMENT_TYPE_NONE),
                offsetX(0.f), offsetY(0.f) {
        }
        WeaponAttachmentSlotClass(int newAttachmentType, float newOffsetX, float newOffsetY)
            :   attachmentType(newAttachmentType),
                offsetX(newOffsetX), offsetY(newOffsetY) {
        }
};

class CharacterClass
{
    public:
        std::string name;
        float x, y, toX, toY, dir, toDir;
        float speed;
        bool isSeen;

        ObjectClass objectOnSlot[CHARACTER_OBJECT_SLOTS_QUANTITY];
        std::vector <std::vector <ObjectClass> > objectInInventory;
        int param[CHARACTER_PARAMS_QUANTITY];

        std::vector <std::string> privateChat;
        std::list <MessageOverHeadClass> messageOverHead;

        CharacterClass()
            :   x(0.f), y(0.f), toX(0.f), toY(0.f), dir(0.f), toDir(0.f),
                speed(7.5f),
                isSeen(false),
                objectInInventory(CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH, std::vector <ObjectClass> (CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT)) {
                    for(int i=0; i<CHARACTER_PARAMS_QUANTITY; ++i) {
                        param[i] = 0;
                    }
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

class LightSourceClass
{
    private:

    public:
        float x, y;
        sf::Vector3f color;
        int textureIndex;

        LightSourceClass()
            :   x(0.f), y(0.f),
                color(1.f, 1.f, 1.f),
                textureIndex(-1) {
        }
        LightSourceClass(float newX, float newY)
            :   x(newX), y(newY),
                color(1.f, 1.f, 1.f),
                textureIndex(-1) {
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

        std::string name, resourcesName;
        int progress;
        std::vector <QuestProgressTextClass> questProgressText;
        int questType;

        QuestClass()
            :   name("undefined"), resourcesName("undefined"),
                progress(0),
                questType(QUEST_TYPE_NONE) {
        }
};

class ProjectileClass
{
    public:
        float x, y, trailX, trailY, dir;
        float distanceTraveled;
        char ownerCharacterType;
        int id, ownerId, projectileType;
        float missileParticlesTimer;

        float grenadeRotation;
        float grenadeThrowDistance;
        float grenadeFlySpeed;
        double timeout_grenadeExplode;
        int grenadeBouncedQuantity;

        ProjectileClass()
            :   x(0.f), y(0.f), trailX(0.f), trailY(0.f), dir(0.f),
                distanceTraveled(0.f),
                ownerCharacterType(0),
                id(0), ownerId(-1), projectileType(PROJECTILE_TYPE_NONE),
                missileParticlesTimer(0.f),
                grenadeRotation(0.f),
                grenadeThrowDistance(0.f),
                grenadeFlySpeed(20.f),
                timeout_grenadeExplode(0.0),
                grenadeBouncedQuantity(0) {
        }
        ProjectileClass(char newOwnerCharacterType, int newOwnerId, float newX, float newY, float newDir, int newId, int newProjectileType)
            :   x(newX), y(newY), trailX(newX), trailY(newY), dir(newDir),
                distanceTraveled(0.f),
                ownerCharacterType(newOwnerCharacterType),
                id(newId), ownerId(newOwnerId), projectileType(newProjectileType),
                missileParticlesTimer(0.f),
                grenadeRotation(0.f),
                grenadeThrowDistance(0.f),
                grenadeFlySpeed(20.f),
                timeout_grenadeExplode(0.0),
                grenadeBouncedQuantity(0) {
        }
};

class ParticleClass
{
    public:
        float x, y, dir, speed, fadeAwaySpeed, rotation;
        int textureIndex;
        sf::Color color;
        float alpha;
        bool additiveBlending;
        bool drawOnTop;

        ParticleClass()
            :   x(0.f), y(0.f), dir(0.f), speed(0.f), fadeAwaySpeed(0.f), rotation(0.f),
                textureIndex(-1),
                color(sf::Color::Black),
                alpha(0.f),
                additiveBlending(false),
                drawOnTop(false) {
        }
        ParticleClass(float newX, float newY, float newDir, float newSpeed, float newFadeAwaySpeed, float newRotation, int newTextureIndex, const sf::Color &newColor, float newAlpha, bool newAdditiveBlending, bool newDrawOnTop = false)
            :   x(newX), y(newY), dir(newDir), speed(newSpeed), fadeAwaySpeed(newFadeAwaySpeed), rotation(newRotation),
                textureIndex(newTextureIndex),
                color(newColor),
                alpha(newAlpha),
                additiveBlending(newAdditiveBlending),
                drawOnTop(newDrawOnTop) {
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

class WeatherClass
{
    public:
        std::list <RainDropClass> rainDrop;
        sf::Texture rainDropSplashFrameTexture[RAINDROP_SPLASH_ANIMATION_FRAMES_QUANTITY];
        sf::Sprite rainDropSplashFrameSprite[RAINDROP_SPLASH_ANIMATION_FRAMES_QUANTITY];
        SAMPLE *lightningSample;
        audiere::OutputStreamPtr dayBackgroundSound;
        audiere::OutputStreamPtr nightBackgroundSound;
        audiere::OutputStreamPtr smallRainSound;
        audiere::OutputStreamPtr mediumRainSound;
        audiere::OutputStreamPtr heavyRainSound;

        double dayTimeInMinutes;
        int rainType, snowType, stormType, fogType;
        float rainIntensity, snowIntensity, fogIntensity;
        double timeout_lightning;

        float sunScreenPosX, sunScreenPosY;
        float moonScreenPosX, moonScreenPosY;

        float ambientShadowLength;
        float ambientShadowDir;
        float ambientShadowAlpha;
        sf::Vector3f ambientLightColor;

        WeatherClass()
            :   lightningSample(NULL),
                dayTimeInMinutes(0.0),
                rainType(RAIN_TYPE_NONE), snowType(SNOW_TYPE_NONE), stormType(STORM_TYPE_NONE), fogType(FOG_TYPE_NONE),
                rainIntensity(0.f), snowIntensity(0.f), fogIntensity(0.f),
                timeout_lightning(0.0),
                sunScreenPosX(0.f), sunScreenPosY(0.f),
                moonScreenPosX(500.f), moonScreenPosY(500.f),
                ambientShadowLength(0.f),
                ambientShadowDir(0.f),
                ambientShadowAlpha(0.f),
                ambientLightColor(1.f, 1.f, 1.f) {
        }
};

class GameSettingsClass
{
    public:
        bool loaded;
        bool fullscreen;
        int screenWidth, screenHeight;
        bool sound;

        GameSettingsClass()
            :   loaded(false),
                fullscreen(false),
                screenWidth(-1), screenHeight(-1),
                sound(true) {
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

class ObjectOnMouseClass
{
    public:
        int objectType;
        int place, placeX, placeY, placeSlot, placeSlot2;

        ObjectOnMouseClass()
            :   objectType(-1),
                place(OBJECT_PLACE_NONE), placeX(0), placeY(0), placeSlot(0), placeSlot2(0) {
        }
};

class CurrentDialogueBlockClass
{
    public:
        bool active;
        int NPCIndex;
        int NPCTextIndex;
        std::vector <int> optionTextIndex;

        CurrentDialogueBlockClass()
            :   active(false),
                NPCIndex(-1),
                NPCTextIndex(-1) {
        }
};

class CurrentTradeWithNPCClass
{
    public:
        bool active;
        int NPCIndex;
        std::vector <int> NPCObjectType;

        CurrentTradeWithNPCClass()
            :   active(false),
                NPCIndex(-1) {
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

class StatusLogMessageClass
{
    public:
        std::string message;
        sf::Color color;
        float offsetX, y, alpha;
        bool fadesAway;
        double timeout_startFadingAway;

        StatusLogMessageClass()
            :   message(""),
                color(sf::Color::White),
                offsetX(30.f), y(window.getSize().y), alpha(0.f),
                fadesAway(false),
                timeout_startFadingAway(0.0) {
        }
        StatusLogMessageClass(const std::string &new_message, const sf::Color &new_color = sf::Color::White)
            :   message(new_message),
                color(new_color),
                offsetX(30.f), y(window.getSize().y), alpha(0.f),
                fadesAway(false),
                timeout_startFadingAway(globalTime+4000.0) {
        }
};

class ChatTabClass
{
    public:
        int chat;
        bool newMessage;

        ChatTabClass()
            :   chat(0),
                newMessage(false) {
        }
        ChatTabClass(int newChat)
            :   chat(newChat),
                newMessage(false) {
        }
};

class WindowClass
{
    public:
        std::string title;
        float x, y, w, h;
        bool visible;

        GUIControlManagerClass GUIControl;

        bool dragging;
        float draggingOffsetX;
        float draggingOffsetY;

        bool closeButtonBeingPressed;

        void(LogicModule::*LogicCallback)(InterfaceClass&, WindowClass&, enum LMBActionEnum);
        void(RenderModule::*RenderCallback)(const InterfaceClass&, const WindowClass&);

        inline void setLogicCallback(void(LogicModule::*newLogicCallback)(InterfaceClass&, WindowClass&, enum LMBActionEnum)) {
            LogicCallback = newLogicCallback;
        }

        inline void setRenderCallback(void(RenderModule::*newRenderCallback)(const InterfaceClass&, const WindowClass&)) {
            RenderCallback = newRenderCallback;
        }

        WindowClass()
            :   title("undefined"), x(0.f), y(0.f), w(0.f), h(0.f), visible(false), dragging(false), draggingOffsetX(0.f), draggingOffsetY(0.f),
                closeButtonBeingPressed(false),
                LogicCallback(NULL), RenderCallback(NULL) {
        }
        WindowClass(const std::string &new_title, float new_x, float new_y, float new_w, float new_h)
            :   title(new_title), x(new_x), y(new_y), w(new_w), h(new_h), visible(true), dragging(false), draggingOffsetX(0.f), draggingOffsetY(0.f),
                closeButtonBeingPressed(false),
                LogicCallback(NULL), RenderCallback(NULL) {
        }
};

class InterfaceClass
{
    public:
        GUIControlManagerClass menuGUIControl;
        GUIControlManagerClass menuErrorGUIControl;
        GUIControlManagerClass GUIControl;

        sf::Texture chatWindowTexture, chatEditBoxTexture, chatTabTexture;
        sf::Sprite chatWindowSprite, chatEditBoxSprite, chatTabSprite;

        int chatX, chatY, currentChat;
        float chatAlpha;
        int chatStartingLine;
        std::vector <std::string> localChat;
        std::vector <std::string> globalChat;
        std::vector <ChatTabClass> chatTab;

        std::list <StatusLogMessageClass> statusLogMessage;
        std::list <WindowClass> window;

        float objectDescriptionAlpha;
        int inventoryMouseOverSlot;
        int inventoryMouseOverInvX, inventoryMouseOverInvY;
        int mouseOverWeaponAttachmentSlot;
        int mouseOverTradeWithNPCObjectIndex;

        int objectDescriptionSlot;
        int objectDescriptionInvX;
        int objectDescriptionInvY;

        sf::Texture objectSlotTexture;
        sf::Sprite objectSlotSprite;

        InterfaceClass()
            :   chatX(0), chatY(0), currentChat(CHAT_TAB_LOCAL),
                chatAlpha(170.f),
                chatStartingLine(-1),
                objectDescriptionAlpha(0.f),
                inventoryMouseOverSlot(-1), inventoryMouseOverInvX(-1), inventoryMouseOverInvY(-1),
                mouseOverWeaponAttachmentSlot(-1),
                mouseOverTradeWithNPCObjectIndex(-1),
                objectDescriptionSlot(-1), objectDescriptionInvX(-1), objectDescriptionInvY(-1) {
        }
};

#endif
