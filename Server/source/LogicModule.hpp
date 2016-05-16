#ifndef LOGIC_MODULE_HPP
#define LOGIC_MODULE_HPP

#include "DataModule.hpp"
#include "UtilityModule.hpp"
#include "NetworkModule.hpp"
#include "benchmark.hpp"

class LogicModule
    : public virtual DataModule,
      public virtual UtilityModule,
      public virtual NetworkModule
{
    protected:
        void logicPlayers();
        void logicAI();
        void logicProjectiles();
        void logicWeather();
};

#endif
