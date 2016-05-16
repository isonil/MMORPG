#ifndef LOGIC_MODULE_HPP
#define LOGIC_MODULE_HPP

#include "DataModule.hpp"
#include "UtilityModule.hpp"

class LogicModule
    : public virtual DataModule,
      public virtual UtilityModule
{
    public:
        void logicInterface();
        void onClick(int x, int y);
        void onRClick(int x, int y);
        void onEntitySelectClick(int x, int y, bool doubleClick);
        void tileTypesClick(int x, int y);
        void sceneryTypesClick(int x, int y);
        void objectTypesClick(int x, int y);
        void NPCTypesClick(int x, int y, bool doubleClick);
        void lightSourceTypesClick(int x, int y);
        void triggersClick(int x, int y);
        void effectsClick(int x, int y);
        void zoneTypesClick(int x, int y);
};

#endif
