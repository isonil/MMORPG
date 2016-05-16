/**
* @file
* @brief File containing RenderModule class.
*/

#ifndef RENDER_MODULE_HPP
#define RENDER_MODULE_HPP

#include "DataModule.hpp"
#include "UtilityModule.hpp"
#include "SpriteDrawQueueClass.hpp"

/**
* @brief One of @ref MODULES_GROUP. Class holding window render
* callbacks and main render methods called directly from game loop.
*
* @ingroup MODULES_GROUP
*
* All protected methods in RenderModule are called directly from
* Client::mainLoopMenu or Client::mainLoopGame.
*
* All methods called directly from game loop begin with 'render'.
* They can be divided into smaller ones, for example:
* @code
*   private:
*     void renderExample_something();
*     void renderExample_somethingElse();
*
*   protected:
*     void renderExample();
* @endcode
*
* This class also holds window render callbacks
* which names have following syntax:
* @code
*   callback_renderXWindow
* @endcode
* where X is window's name.
*/
class RenderModule
    : public virtual DataModule,
      public virtual UtilityModule
{
    private:
        void blitWeaponWithAddons(const ObjectClass &object, float screen_x, float screen_y, float screen_w, float screen_h, bool inScale, bool drawAsInterface, int alpha = 255);
        void blitObjectDescription(const ObjectClass &object, int x, int y);
        void blitObjectDescriptionText(const ObjectClass &object, int x, int y, int alpha);
        void drawAmbientShadow(sf::Sprite &spr, const sf::Texture &tex, float shadowX, float shadowY, float scaleX, float scaleY, float shadowLength, bool fakeShadow, float fakeShadowDir);
        void renderCharacters(const std::vector <CharacterClass> &character);
        void renderInterface_characterNamesAndMessages();
        void renderInterface_chat();
        void renderInterface_chatMessages(const std::vector <std::string> &chat);
        void renderInterface_statusLogMessages();
        void renderInterface_playerCharacterInterfaceAndMinimap();
        void renderInterface_dialogue();
        void renderInterface_windows(bool &mouseOverAnyWindow);
        void renderInterface_objectDescription(bool mouseOverAnyWindow);
        void renderLights_shadows(float screenX, float screenY);

        float getLightIntensity(float x, float y);
        bool textureSplatting_isTileDifferent(int tileType1, int tileType2);

    protected:
        void renderMapLayerOne();
        void renderMapShadows();
        void renderMapLayerTwo();
        void renderMapLayerThree();
        void renderAllCharacters();
        void renderProjectiles();
        void renderParticles();
        void renderWeather();
        void renderLights();
        void renderMenuInterface();
        void renderInterface();

        void callback_renderCharacterInventoryWindow(const InterfaceClass &interface, const WindowClass &GUIWindow);
        void callback_renderObjectDescriptionWindow(const InterfaceClass &interface, const WindowClass &window);
        void callback_renderTradeWithNPCWindow(const InterfaceClass &interface, const WindowClass &window);
        void callback_renderCharacterStatsWindow(const InterfaceClass &interface, const WindowClass &window);
};

#endif
