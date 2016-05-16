#ifndef MASTER_HPP
#define MASTER_HPP

#include "DataModule.hpp" // out
#include "UtilityModule.hpp" // out
#include "LogicModule.hpp" // out
#include "NetworkModule.hpp" // out
#include "World.hpp"
#include "Network.hpp"

#define M Master::getInstance()

class Master
    : public virtual DataModule,
      public virtual UtilityModule,
      public virtual LogicModule,
      public virtual NetworkModule
{
    private:
        static Master *instance;
        World world;
        Network network;

        void mainLoop();

    public:
        void init();
        void initDebug();
        void run();

        inline World &getWorld()
        {
            return world;
        }

        inline Network &getNetwork()
        {
            return network;
        }

        inline static Master &getInstance()
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
