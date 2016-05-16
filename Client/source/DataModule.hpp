#ifndef DATA_MODULE_HPP
#define DATA_MODULE_HPP

#include "Classes.hpp"
#include "SpriteDrawQueueClass.hpp"

class DataModule
{
    protected:
        std::vector <CharacterClass> Player;
        std::vector <CharacterClass> NPC;
        std::vector <TileTypeClass> TileType;
        std::vector <SceneryTypeClass> SceneryType;
        std::vector <ObjectTypeClass> ObjectType;
        std::vector <std::vector <TileClass> > Tile;
        std::vector <LightSourceClass> LightSource;
        std::vector <std::string> Text;
        std::vector <QuestClass> Quest;
        std::list <ProjectileClass> Projectile;
        std::list <ParticleClass> Particle;
        WeatherClass Weather;
        InterfaceClass Interface;
        GameSettingsClass GameSettings;
        ViewClass View;

        bool quit;
        bool loadingDone;
        char login[LOGIN_LENGTH_LIMIT+5];
        char password[PASSWORD_LENGTH_LIMIT+5];
        std::string inGameError;
        std::vector <ShadowCasterClass> shadowCaster;
        sf::Mutex loadingDoneMutex;
        sf::Shader lightShader, alphaGradientShader, waterShader;
        sf::Shader lightToLightDiffuseMapShader;
        sf::Shader lightToLightSpecularMapShader;
        sf::Shader postProcessShader;
        sf::RenderStates addRenderState, multiplyRenderState;
        audiere::AudioDevicePtr audiereAudioDevice;
        ObjectOnMouseClass objectOnMouse;
        CurrentDialogueBlockClass currentDialogueBlock;
        CurrentTradeWithNPCClass currentTradeWithNPC;
        SpriteDrawQueueClass spriteDrawQueue;
        sf::Texture missingTexture;
        sf::Texture penumbraTexture;
        sf::Texture mouseTexture;
        sf::Texture mouseMoveObjectTexture;
        sf::Texture particleTexture[PARTICLE_TEXTURES_QUANTITY];
        sf::Sprite particleSprite[PARTICLE_TEXTURES_QUANTITY];
        sf::Texture minimapTexture;
        sf::Texture missileTexture;
        sf::Texture grenadeLauncherGrenadeTexture;
        sf::Texture grenadeTexture;
        sf::Texture waterColorMapTexture;
        sf::Texture waterNormalMapTexture;
        sf::Texture waterNoiseTexture;
        sf::Texture skyTexture;
        sf::Sprite waterSprite;
        sf::Texture lightTexture[LIGHT_TEXTURES_QUANTITY];
        sf::Sprite lightSprite[LIGHT_TEXTURES_QUANTITY];
        SAMPLE *bulletHitSample;
        SAMPLE *bulletBloodHitSample;
        SAMPLE *explosionSample;
        SAMPLE *grenadeLauncherShotSample;
        SAMPLE *grenadeThrowSample;
        SAMPLE *grenadeBounceSample;
        SAMPLE *levelUpSample;
        ENetHost *client;
        ENetPeer *peer;
        int randomArray[10][10];
        int ambientLight;
        double timeout_sendPosition;
        double timeout_lightningLight;
        double timeout_grenadeLauncherShot;
        double timeout_grenadeThrow;
        float viewOffsetX, viewOffsetY;
        bool automaticShooting;

        void loadTileTypes(const std::string &path);
        void loadSceneryTypes(const std::string &path);
        void loadObjectSlotDefaultSprites();
        void loadObjectTypes(const std::string &path);
        void loadMap(const std::string &path);
        void loadTexts(const std::string &path);
        void loadQuests(const std::string &path, const std::string &questsPath);
        void loadGameSettings(const std::string &path);
        void applyMissingTexture();
        void applyTextureSmoothing();

        DataModule()
            :   quit(false),
                loadingDone(false),
                bulletHitSample(NULL),
                bulletBloodHitSample(NULL),
                explosionSample(NULL),
                grenadeLauncherShotSample(NULL),
                grenadeThrowSample(NULL),
                grenadeBounceSample(NULL),
                levelUpSample(NULL),
                client(NULL),
                peer(NULL),
                ambientLight(0),
                timeout_sendPosition(0.0),
                timeout_lightningLight(0.0),
                timeout_grenadeLauncherShot(0.0),
                timeout_grenadeThrow(0.0),
                viewOffsetX(0.f), viewOffsetY(0.f),
                automaticShooting(false) {
            login[0] = 0;
            password[0] = 0;
        }
};

extern ObjectSlotClass objectSlot[CHARACTER_OBJECT_SLOTS_QUANTITY];

const WeaponAttachmentSlotClass weaponAttachmentSlot[WEAPON_ATTACHMENTS_QUANTITY] = {
    WeaponAttachmentSlotClass(ATTACHMENT_TYPE_SIGHT, 187.f, 23.f),
    WeaponAttachmentSlotClass(ATTACHMENT_TYPE_BARREL, 187.f, 83.f),
    WeaponAttachmentSlotClass(ATTACHMENT_TYPE_MISC, 187.f, 143.f)
};

#endif
