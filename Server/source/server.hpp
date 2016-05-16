#ifndef SERVER_HPP
#define SERVER_HPP

#include <OpenLayer.hpp>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <vector>
#include <list>
#include <queue>
#include <enet/enet.h>
#include "DataModule.hpp"
#include "UtilityModule.hpp"
#include "LogicModule.hpp"
#include "NetworkModule.hpp"
#include "global.hpp"
#include "benchmark.hpp"

class Server
    : public virtual DataModule,
      public virtual UtilityModule,
      public virtual LogicModule,
      public virtual NetworkModule
{
    private:
        void mainLoop();

    public:
        void init();
        void initDebug();
        void run();

        inline static Server &getInstance() {
            static Server instance;
            return instance;
        }
};

#endif
