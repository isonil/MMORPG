/**
* @file
* @brief File containing LogicModule class.
*/

#ifndef LOGIC_MODULE_HPP
#define LOGIC_MODULE_HPP

#include "DataModule.hpp"
#include "UtilityModule.hpp"

/**
* @brief One of @ref MODULES_GROUP. Class holding window logic
* callbacks and main logic methods called directly from game loop.
*
* @ingroup MODULES_GROUP
*
* All protected methods in LogicModule are called directly from
* Client::mainLoopMenu or Client::mainLoopGame.
*
* All methods called directly from game loop begin with 'logic'.
* They can be divided into smaller ones, for example:
* @code
*   private:
*     void logicExample_something();
*     void logicExample_somethingElse();
*
*   protected:
*     void logicExample();
* @endcode
*
* This class also holds window logic callbacks
* which names have following syntax:
* @code
*   callback_logicXWindow
* @endcode
* where X is window's name.
*/
class LogicModule
    : public virtual DataModule,
      public virtual UtilityModule
{
    private:
        void logicInterface_windows(bool &mouseOverAnyWindow);
        void logicInterface_chat(bool mouseOverAnyWindow);
        void logicInterface_onMouseObjectDrop(bool mouseOverAnyWindow);
        void logicInterface_dialogue(bool mouseOverAnyWindow);
        void logicInterface_pickUpObject(bool mouseOverAnyWindow);
        void logicInterface_objectDescription(bool mouseOverAnyWindow);
        void logicInterface_changeChatTab();
        void logicInterface_keyboard();
        void logicInterface_statusLogMessages();

    protected:
        void logicMenuInterface();
        void logicInterface();
        void logicCharacters();
        void logicPlayerInput();
        void logicSendPosition();
        void logicProjectiles();
        void logicParticles();
        void logicWeather();
        void logicView();

        void callback_logicCharacterInventoryWindow(InterfaceClass &interface, WindowClass &window, enum LMBActionEnum LMBAction);
        void callback_logicObjectDescriptionWindow(InterfaceClass &interface, WindowClass &window, enum LMBActionEnum LMBAction);
        void callback_logicTradeWithNPCWindow(InterfaceClass &interface, WindowClass &window, enum LMBActionEnum LMBAction);
};

#endif
