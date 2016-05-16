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
        void renderCharacters(const std::vector <CharacterClass> &Character, bool useNPCTypeSlots);

        bool textureSplatting_isTileDifferent(int tileType1, int tileType2);

    protected:
        void renderMapLayerOne();
        void renderMapShadows();
        void renderMapLayerTwo();
        void renderMapLayerThree();
        void renderAllCharacters();
        void renderLights();
        void renderInterface();

    public:
        void renderTileTypes(sf::RenderWindow &window);
        void renderSceneryTypes(sf::RenderWindow &window);
        void renderObjectTypes(sf::RenderWindow &window);
        void renderNPCTypes(sf::RenderWindow &window);
        void renderLightSourceTypes(sf::RenderWindow &window);
        void renderTriggers(sf::RenderWindow &window);
        void renderEffects(sf::RenderWindow &window);
        void renderZoneTypes(sf::RenderWindow &window);
};

#endif
