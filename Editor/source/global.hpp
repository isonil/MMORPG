/**
* @file
* @brief File containing all defines and global funcs/vars.
*/

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <wx/choice.h>
#include <wx/stattext.h>
#include <wx/grid.h>
#include <wx/listbox.h>
#include <wx/checkbox.h>
#include <wx/slider.h>
#include <wx/textctrl.h>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <windows.h>
#include <conio.h>

/**
* @defgroup MISC_DEFINES_GROUP Miscellaneous defines
* @{
*/
#define SUPPORTED_TEXTURE_SIZE_REQUIREMENT (1024) /**< Supported texture size requirement for graphics card. Value must be equal or greater than this variable in order to start game.*/
#define TILE_SIZE (50) /**< Single tile size.*/
#define CHARACTER_RADIUS (23) /**< Character body radius.*/
#define PLAYER_TILES_VIEW_DISTANCE (14) /**< Maximum player view distance in tiles.*/
#define CHARACTER_OBJECT_SLOTS_QUANTITY (5) /**< Character slots quantity.*/
#define CHARACTER_OBJECT_SLOT_WEAPON_INDEX (0) /**< Weapon slot index.*/
#define CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH (7) /**< Number of available slots in inventory in width.*/
#define CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT (4) /**< Number of available slots in inventory in height.*/
#define WEAPON_ATTACHMENTS_QUANTITY (3) /**< Number of weapon attachments.*/
#define GRASS_TILE_TYPE_START (0) /**< Tile index where grass tiles start.*/
#define GRASS_TILE_TYPE_END (7) /**< Tile index where grass tiles end.*/
/** @} */

#define CHARACTER_PLAYER ('p')
#define CHARACTER_NPC ('n')

#define LAYER_ONE (0)
#define LAYER_TWO (1)
#define LAYER_THREE (2)

#define CHARACTER_PARAM_HEALTH (0)
#define CHARACTER_PARAM_MAX_HEALTH (1)
#define CHARACTER_PARAM_EXPERIENCE (2)
#define CHARACTER_PARAM_BASE_X (3)
#define CHARACTER_PARAM_BASE_Y (4)
#define CHARACTER_PARAM_MONEY (5)
#define CHARACTER_PARAM_LEVEL (6)
#define CHARACTER_PARAM_RANK (7)
#define CHARACTER_PARAM_FACTION (8)
#define CHARACTER_PARAM_FACTION_RANK (9)
#define CHARACTER_PARAMS_QUANTITY (10)

#define OBJECT_PARAM_QUANTITY (0)
#define OBJECT_PARAM_OWNER (1)
#define OBJECT_PARAM_CONDITION (2)
#define OBJECT_PARAM_ADDON_1 (3)
#define OBJECT_PARAM_ADDON_2 (4)
#define OBJECT_PARAM_ADDON_3 (5)
#define OBJECT_PARAMS_QUANTITY (6)

#define OBJECT_BASE_TYPE_NONE (0)
#define OBJECT_BASE_TYPE_WEAPON (1)
#define OBJECT_BASE_TYPE_EQUIPMENT (2)
#define OBJECT_BASE_TYPE_STRUCTURE (3)
#define OBJECT_BASE_TYPE_ADDON (4)
#define OBJECT_BASE_TYPE_MISC (5)
#define OBJECT_BASE_TYPE_AMMUNITION (6)

#define WEAPON_TYPE_NONE (0)
#define WEAPON_TYPE_BIG_GUN (1)
#define WEAPON_TYPE_SMALL_GUN (2)
#define WEAPON_TYPE_ROCKET_LAUNCHER (3)

#define EQUIPMENT_TYPE_NONE (0)
#define EQUIPMENT_TYPE_HELMET (1)
#define EQUIPMENT_TYPE_VEST (2)
#define EQUIPMENT_TYPE_BOOTS (3)
#define EQUIPMENT_TYPE_GLOVES (4)

#define ATTACHMENT_TYPE_NONE (0)
#define ATTACHMENT_TYPE_SIGHT (1)
#define ATTACHMENT_TYPE_BARREL (2)
#define ATTACHMENT_TYPE_MISC (3)

#define PROJECTILE_TYPE_NONE (0)
#define PROJECTILE_TYPE_BULLET (1)
#define PROJECTILE_TYPE_MISSILE (2)
#define PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE (3)
#define PROJECTILE_TYPE_GRENADE (4)

#define NATURE_TYPE_NONE (0)
#define NATURE_TYPE_TREE (1)
#define NATURE_TYPE_WATER_FLOAT (2)
#define NATURE_TYPE_WATER_FLOAT_STATIC (3)
#define NATURE_TYPE_FERN (4)
#define NATURE_TYPE_STONE (5)
#define NATURE_TYPE_GRASS (6)

#define RAIN_TYPE_NONE (0)
#define RAIN_TYPE_SMALL (1)
#define RAIN_TYPE_MEDIUM (2)
#define RAIN_TYPE_HEAVY (3)

#define SNOW_TYPE_NONE (0)
#define SNOW_TYPE_SMALL (1)
#define SNOW_TYPE_MEDIUM (2)
#define SNOW_TYPE_HEAVY (3)

#define STORM_TYPE_NONE (0)
#define STORM_TYPE_SMALL (1)
#define STORM_TYPE_MEDIUM (2)
#define STORM_TYPE_HEAVY (3)

#define FOG_TYPE_NONE (0)
#define FOG_TYPE_SMALL (1)
#define FOG_TYPE_MEDIUM (2)
#define FOG_TYPE_HEAVY (3)

#define QUEST_TYPE_NONE (0)
#define QUEST_TYPE_MAIN (1)
#define QUEST_TYPE_SIDE (2)

#define ENTITY_TYPE_NONE (0)
#define ENTITY_TYPE_TILE_TYPE (1)
#define ENTITY_TYPE_SCENERY_TYPE (2)
#define ENTITY_TYPE_OBJECT_TYPE (3)
#define ENTITY_TYPE_NPC_TYPE (4)
#define ENTITY_TYPE_SCRIPT (5)
#define ENTITY_TYPE_QUEST (6)
#define ENTITY_TYPE_TEXT (7)
#define ENTITY_TYPE_SCENERY (8)
#define ENTITY_TYPE_OBJECT (9)
#define ENTITY_TYPE_NPC (10)
#define ENTITY_TYPE_LIGHT_SOURCE_TYPE (11)
#define ENTITY_TYPE_TRIGGER (12)

#define SCRIPT_FUNC_ADD_EXP (0)
#define SCRIPT_FUNC_ADD_MONEY (1)
#define SCRIPT_FUNC_SET_QUEST_PROGRESS (2)
#define SCRIPT_FUNC_END_DIALOGUE (3)
#define SCRIPT_IF_FUNC_QUEST_PROGRESS (4)

#define AI_MOVEMENT_TYPE_STAND (0)
#define AI_MOVEMENT_TYPE_MOVE_BY_CHECKPOINTS (1)
#define AI_MOVEMENT_TYPE_MOVE_BY_DISTANCE (2)

#define CHARACTER_RANK_PLAYER (0)
#define CHARACTER_RANK_GM (1)

#define CHARACTER_FACTION_RANK_RECRUIT (0)
#define CHARACTER_FACTION_RANK_MEMBER (1)
#define CHARACTER_FACTION_RANK_COMMANDER (2)
#define CHARACTER_FACTION_RANK_LEADER (3)

#define TEAM_0 (0)
#define TEAM_1 (1)

inline void dateAndTimeToFile(std::ofstream &out);
char *getString(const char *format, const va_list &va);
void messageBox(const char *title, const char *message, ...);

class LogManagerClass : public std::streambuf
{
    private:
        std::ofstream logFile;
        bool newLine;

        void saveString(const char *str, size_t size)
        {
            if(str == NULL) return;
            fwrite(str, 1, size, stdout);
            if(logFile) {
                logFile.write(str, size);
                logFile.flush();
            }
        }

    protected:
        std::streamsize xsputn(const char *str, std::streamsize size)
        {
            if(str == NULL) return size;
            if(newLine) {
                newLine = false;
                saveString("[sf::err] ", 10);
            }
            if(size && str[size-1] == '\n') {
                newLine = true;
            }
            saveString(str, size);
            return size;
        }

        int overflow(int c)
        {
            newLine = true;
            saveString("\n", 1);
            return 0;
        }

    public:
        bool create(const std::string &path)
        {
            logFile.open(path.c_str());
            if(logFile) {
                logFile << "Log file created on ";
                dateAndTimeToFile(logFile);
                logFile << "\n";
                logFile << "Build: " << __DATE__ << " " << __TIME__ << " ";
                #ifdef DEBUG
                logFile << "Debug\n";
                #else
                logFile << "Release\n";
                #endif
                logFile << "\n";
            }
            return logFile;
        }

        void saveMessageVA(const char *prefix, const char *format, const va_list &va)
        {
            if(prefix == NULL || format == NULL) return;
            char *str = getString(format, va);
            saveString("[", 1);
            saveString(prefix, strlen(prefix));
            saveString("] ", 2);
            saveString(str, strlen(str));
            saveString("\n", 1);
            delete []str;
        }

        void saveMessageFormatted(const char *prefix, const char *format, ...)
        {
            if(prefix == NULL || format == NULL) return;
            va_list va;
            va_start(va, format);
            saveMessageVA(prefix, format, va);
            va_end(va);
        }

        void saveMessage(const char *prefix, const char *message)
        {
            if(prefix == NULL || message == NULL) return;
            saveMessageFormatted(prefix, "%s", message);
        }

        LogManagerClass()
            :   newLine(true) {
        }
};

extern wxWindow *wxMainWindow;
extern wxChoice *wxEntitySelection1;
extern wxChoice *wxEntitySelection2;
extern wxStaticText *wxEntityText;
extern wxGrid *wxEntityGrid;
extern wxListBox *wxScriptsListBox;
extern wxListBox *wxQuestsListBox;
extern wxListBox *wxTextsListBox;
extern wxCheckBox *wxGridCheckBox;
extern wxCheckBox *wxMinimapCheckBox;
extern wxChoice *wxDisplaySelection;
extern wxTextCtrl *wxErrorLogEditBox;

extern sf::Clock globalClock;
extern sf::RenderTexture colorMapFBO;
extern sf::RenderTexture normalMapFBO;
extern sf::RenderTexture heightMapFBO;
extern double globalTime;
extern double deltaTime;
extern double saved_timer;
extern int mx, my, mb;
extern bool LMBEventHandled, RMBEventHandled;

extern int selectionEntityType;
extern int selectionEntityIndex;
extern int selectionListBoxSelectionIndex;
extern int selectionEntityX;
extern int selectionEntityY;

extern int editingScriptIndex;
extern int editingNPCTypeIndex;
extern int editingQuestIndex;

extern LogManagerClass logManager;

inline bool floatCompare(float f1, float f2, float diff)
{
    if(fabs(f1-f2) <= diff) return true;
    return false;
}

inline void dateAndTimeToFile(std::ofstream &out)
{
    if(out) {
        tm *currentTime;
        time_t currentTimeTemp;
        time(&currentTimeTemp);
        currentTime = localtime(&currentTimeTemp);
        out << currentTime->tm_mday << '.' << currentTime->tm_mon+1 << '.' << currentTime->tm_year+1900 << ' ';
        if(currentTime->tm_hour < 10) out << '0';
        out << currentTime->tm_hour << ':';
        if(currentTime->tm_min < 10) out << '0';
        out << currentTime->tm_min;
    }
}

inline void info(const char *format, ...)
{
    if(format == NULL) return;
    va_list va;
    va_start(va, format);
    logManager.saveMessageVA("info", format, va);
    va_end(va);
}

inline void error(const char *format, ...)
{
    if(format == NULL) return;
    va_list va;
    va_start(va, format);
    char *message = getString(format, va);
    va_end(va);
    logManager.saveMessage("error", message);
    messageBox("Error", "%s", message);
    delete []message;
    exit(1);
}

inline void _assert(bool expr, const char *message)
{
    if(message == NULL) return;
    if(!expr) {
        logManager.saveMessageFormatted("assert", "Assertion failed. Message: %s", message);
        messageBox("Assert", "Assertion failed. Message: %s\nIf this error appeared for an unknown reason\nplease let us know about it.\n-Dev team", message);
        exit(1);
    }
}

inline std::string getObjectBaseTypeName(int baseType)
{
    if(baseType == OBJECT_BASE_TYPE_NONE) return "None";
    else if(baseType == OBJECT_BASE_TYPE_WEAPON) return "Weapon";
    else if(baseType == OBJECT_BASE_TYPE_EQUIPMENT) return "Equipment";
    else if(baseType == OBJECT_BASE_TYPE_STRUCTURE) return "Structure";
    else if(baseType == OBJECT_BASE_TYPE_ADDON) return "Weapon attachment";
    else if(baseType == OBJECT_BASE_TYPE_MISC) return "Miscellaneous";
    return "?";
}

inline std::string getObjectCatalogueName(int baseType)
{
    if(baseType == OBJECT_BASE_TYPE_NONE) return "other";
    else if(baseType == OBJECT_BASE_TYPE_WEAPON) return "weapons";
    else if(baseType == OBJECT_BASE_TYPE_EQUIPMENT) return "equipment";
    else if(baseType == OBJECT_BASE_TYPE_STRUCTURE) return "structures";
    else if(baseType == OBJECT_BASE_TYPE_ADDON) return "attachments";
    else if(baseType == OBJECT_BASE_TYPE_MISC) return "misc";
    return "unknown";
}

inline std::string getWeaponTypeName(int weaponType)
{
    if(weaponType == WEAPON_TYPE_NONE) return "None";
    else if(weaponType == WEAPON_TYPE_BIG_GUN) return "Big gun";
    else if(weaponType == WEAPON_TYPE_SMALL_GUN) return "Small gun";
    else if(weaponType == WEAPON_TYPE_ROCKET_LAUNCHER) return "Rocket launcher";
    return "?";
}

inline std::string getEquipmentTypeName(int equipmentType)
{
    if(equipmentType == EQUIPMENT_TYPE_NONE) return "None";
    else if(equipmentType == EQUIPMENT_TYPE_HELMET) return "Helmet";
    else if(equipmentType == EQUIPMENT_TYPE_VEST) return "Vest";
    else if(equipmentType == EQUIPMENT_TYPE_BOOTS) return "Boots";
    else if(equipmentType == EQUIPMENT_TYPE_GLOVES) return "Gloves";
    return "?";
}

inline std::string getAttachmentTypeName(int attachmentType)
{
    if(attachmentType == ATTACHMENT_TYPE_NONE) return "None";
    else if(attachmentType == ATTACHMENT_TYPE_SIGHT) return "Sight attachment";
    else if(attachmentType == ATTACHMENT_TYPE_BARREL) return "Barrel attachment";
    else if(attachmentType == ATTACHMENT_TYPE_MISC) return "Miscellaneous attachment";
    return "?";
}

wxColour getColorById(int id);
void messageBox(const char *title, const char *format, ...);
void loadTexture(sf::Texture &tex, const std::string &path, bool checkIfExists = false);
void loadImage(sf::Image &img, const std::string &path, bool checkIfExists = false);
bool fileExists(const std::string &path);
int getTextWidth(sf::Text &text);
int getTextWidth(const std::string &text, int characterSize);
LONG crashHandler(_EXCEPTION_POINTERS *exInfo);

#endif
