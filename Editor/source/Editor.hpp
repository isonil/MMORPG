/**
* @file
* @brief File containing master class Editor.
*/

#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <vector>
#include <list>
#include <string>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include "DataModule.hpp"
#include "LogicModule.hpp"
#include "RenderModule.hpp"

/**
* @brief Master class which combines all @ref MODULES_GROUP
* together.
*
* This class is responsible for initializing Editor rendering,
* managing and rendering game world or openGL-rendered GUI panels.\n
*
* Class has only one instance.\n
* Every member of any module outside of the class hierarchy
* can be called as follows.
* @code
*   Editor::getInstance().member;
* @endcode
*/
class Editor
    : public virtual DataModule,
      public virtual UtilityModule,
      public virtual LogicModule,
      public virtual RenderModule
{
    public:
        void init();
        void renderAll();
        void save();

        /**
        * @brief Instance handler for Editor class.
        * @return Editor instance.
        */
        inline static Editor &getInstance() {
            static Editor instance;
            return instance;
        }
};

#endif
