/**
* @file
* @brief File containing master class Client.
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <OpenLayer.hpp>
#include "DataModule.hpp"
#include "UtilityModule.hpp"
#include "LogicModule.hpp"
#include "RenderModule.hpp"
#include "NetworkModule.hpp"

/**
* @brief Master class which combines all @ref MODULES_GROUP
* together.
*
* This class is responsible for initializing game and
* managing main game loop.\n
*
* Class has only one instance.\n
* Every member of any module outside of the class hierarchy
* can be called as follows.
* @code
*   Client::getInstance().member;
* @endcode
*/
class Client
    : public virtual DataModule,
      public virtual UtilityModule,
      public virtual LogicModule,
      public virtual RenderModule,
      public virtual NetworkModule
{
    private:
        void loadResourcesThread();
        void mainLoopMenu();
        void mainLoopGame();

    public:
        void init();
        void run();

        /**
        * @brief Instance handler for Client class.
        * @return Client instance.
        */
        inline static Client &getInstance() {
            static Client instance;
            return instance;
        }
};

#endif
