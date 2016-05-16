#ifndef MASTER_HPP
#define MASTER_HPP

#include "DataModule.hpp" // out
#include "UtilityModule.hpp" // out
#include "LogicModule.hpp" // out
#include "RenderModule.hpp" // out
#include "World.hpp"
#include "Network.hpp"
#include "Player.hpp"

class Utility
{
    public:
};

class UserInterface
{
    private:
        std::string errorStr;
        bool isErrorShown;

    public:
        void showError(const std::string &str);
        void hideError();
};

class Master
    : public virtual DataModule,
      public virtual UtilityModule,
      public virtual LogicModule,
      public virtual RenderModule
{
    private:
        static Master *instance;
        World world;
        Network network;
        UserInterface userInterface;
        Utility utility;
        PlayerC player;

        void loadResourcesThread();
        void mainLoopMenu();
        void mainLoopGame();

    public:
        void init();
        void run();

        inline World &getWorld()
        {
            return world;
        }

        inline Network &getNetwork()
        {
            return network;
        }

        inline UserInterface &getUserInterface()
        {
            return userInterface;
        }

        inline Utility &getUtility()
        {
            return utility;
        }

        inline PlayerC &getPlayer()
        {
            return player;
        }

        static inline Master &getInstance()
        {
            if(instance != NULL) {
                return *instance;
            }
            else instance = new Master;

            return *instance;
        }

        static void release()
        {
            delete instance;
        }
};

#endif
