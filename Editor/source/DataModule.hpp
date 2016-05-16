#ifndef DATA_MODULE_HPP
#define DATA_MODULE_HPP

#include "Classes.hpp"
#include "utility.hpp"
#include "SpriteDrawQueueClass.hpp"
#include "container.hpp"

class DataModule
{
    public:
        std::vector <CharacterClass> Player;
        std::vector <CharacterClass> NPC;
        container <TileTypeClass> TileType;
        container <SceneryTypeClass> SceneryType;
        container <ObjectTypeClass> ObjectType;
        container <LightTypeClass> LightType;
        std::vector <std::vector <TileClass> > Tile;
        std::vector <NPCTypeClass> NPCType;
        std::vector <LightSourceClass> StaticLightSource;
        std::vector <TextClass> Text;
        std::vector <QuestClass> Quest;
        std::vector <ScriptClass> Script;

        ViewClass View;

        std::vector <ShadowCasterClass> shadowCaster;
        SpriteDrawQueueClass spriteDrawQueue;

        sf::RenderStates addRenderState, multiplyRenderState;
        sf::RenderWindow window;
        sf::Texture missingTexture;
        sf::Texture penumbraTexture;
        sf::Texture minimapTexture;
        sf::Texture mouseTexture;
        sf::Texture waterColorMapTexture;
        sf::Texture waterNormalMapTexture;
        sf::Texture waterNoiseTexture;
        sf::Texture skyTexture;
        sf::Sprite waterSprite;
        sf::Texture lightIconTexture;
        sf::Sprite lightIconSprite;
        int randomArray[10][10];
        int ambientLight;

        int getScriptIDByIDName(const std::string &IDName);
        int getQuestIDByIDName(const std::string &IDName);

        void loadClientTileTypes(const std::string &path);
        void loadClientSceneryTypes(const std::string &path);
        void loadClientObjectSlotDefaultSprites();
        void loadClientObjectTypes(const std::string &path);
        void loadClientLightTypes(const std::string &path);
        void loadClientStaticLightSources(const std::string &path);
        void loadClientMap(const std::string &path);
        void loadClientTexts(const std::string &path);
        void loadClientQuests(const std::string &path, const std::string &questsPath);
        void loadServerQuests(const std::string &path);
        void loadServerScripts(const std::string &path, const std::string &scriptsPath);
        void loadServerNPCTypes(const std::string &path, const std::string &NPCTypesPath);
        void loadServerNPCs(const std::string &path);
        void loadServerTileTypes(const std::string &path);
        void loadServerSceneryTypes(const std::string &path);
        void loadServerObjectTypes(const std::string &path);

        void applyMissingTexture();
        void applyTextureSmoothing();

        DataModule()
            :   ambientLight(0) {
        }

    public:
        inline sf::RenderWindow *getWindow()
        {
            return &window;
        }
};

extern ObjectSlotClass objectSlot[CHARACTER_OBJECT_SLOTS_QUANTITY];

const WeaponAttachmentSlotClass weaponAttachmentSlot[WEAPON_ATTACHMENTS_QUANTITY] = {
    WeaponAttachmentSlotClass(ATTACHMENT_TYPE_SIGHT),
    WeaponAttachmentSlotClass(ATTACHMENT_TYPE_BARREL),
    WeaponAttachmentSlotClass(ATTACHMENT_TYPE_MISC)
};

#endif
