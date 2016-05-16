#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <SFML/System.hpp>
#include <enet/enet.h>
#include <cmath>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <fstream>

#ifndef M_PI
#  define M_PI (3.141592)
#endif

#define CHARACTER_OBJECT_SLOTS_QUANTITY (5)
#define CHARACTER_OBJECT_SLOT_WEAPON_INDEX (0)
#define CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH (7)
#define CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT (4)
#define PACKET_FROM_CLIENT_SIZE_LIMIT (1000)
#define OBJECTS_PER_TILE_LIMIT (5)
#define CHAT_MESSAGE_LENGTH_LIMIT (50)
#define WEAPON_ATTACHMENTS_QUANTITY (3)
#define OBJECT_ID_GRENADE_LAUNCHER (7)
#define MAX_QUESTS_QUANTITY (100)
#define LOGIN_LENGTH_LIMIT (15)
#define PASSWORD_LENGTH_LIMIT (15)

#define PACKET_LOG_IN ('l')
#define PACKET_CHARACTER_POSITION ('p')
#define PACKET_OBJECT_CHANGE_ON_GROUND ('o')
#define PACKET_OBJECT_CHANGE_IN_INVENTORY ('q')
#define PACKET_OBJECT_CHANGE_ON_SLOT ('w')
#define PACKET_CHARACTER_PARAMS ('i')
#define PACKET_CHARACTER_LOST_SIGHT ('x')
#define PACKET_SHOT ('s')
#define PACKET_GRENADE_LAUNCHER_SHOT ('n')
#define PACKET_GRENADE_THROW ('a')
#define PACKET_PROJECTILE_HIT ('h')
#define PACKET_CHARACTER_PARAM_CHANGE ('c')
#define PACKET_BUILD ('b')
#define PACKET_CHANGE_OBJECT_PLACE_REQUEST ('g')
#define PACKET_SERVER_MESSAGE ('0')
#define PACKET_LOCAL_CHAT_MESSAGE ('1')
#define PACKET_GLOBAL_CHAT_MESSAGE ('2')
#define PACKET_PRIVATE_CHAT_MESSAGE ('3')
#define PACKET_PRIVATE_CHAT_REQUEST ('t')
#define PACKET_CHARACTER_SLOT_OBJECT_CHANGE ('e')
#define PACKET_DAY_TIME ('d')
#define PACKET_WEATHER ('r')
#define PACKET_START_TALK_WITH_NPC ('f')
#define PACKET_CHOOSE_TALK_OPTION ('j')
#define PACKET_CURRENT_DIALOGUE_BLOCK ('k')
#define PACKET_TRADE_WITH_NPC_OBJECTS_LIST ('m')
#define PACKET_TRADE_WITH_NPC_BUY_OBJECT ('u')
#define PACKET_QUEST_PROGRESS_CHANGE ('y')
#define PACKET_END_CURRENT_NPC_INTERACTION ('z')

#define MAX_PACKET_SIZE_CURRENT_DIALOGUE_BLOCK (300)
#define MAX_PACKET_SIZE_TRADE_WITH_NPC_OBJECTS_LIST (1000)
#define MAX_PACKET_SIZE_OBJECT_CHANGE_ON_GROUND (500)
#define MAX_PACKET_SIZE_CHARACTER_PARAM_CHANGE (100)
#define MAX_PACKET_SIZE_CHARACTER_LOST_SIGHT (100)
#define MAX_PACKET_SIZE_CHARACTER_PARAMS (300+LOGIN_LENGTH_LIMIT)
#define MAX_PACKET_SIZE_PROJECTILE_HIT (150)
#define MAX_PACKET_SIZE_SHOT (300)
#define MAX_PACKET_SIZE_GRENADE_LAUNCHER_SHOT (300)
#define MAX_PACKET_SIZE_GRENADE_THROW (300)
#define MAX_PACKET_SIZE_QUEST_PROGRESS_CHANGE (100)
#define MAX_PACKET_SIZE_OBJECT_CHANGE_IN_INVENTORY (300)
#define MAX_PACKET_SIZE_LOG_IN (1500)
#define MAX_PACKET_SIZE_CHARACTER_POSITION (150)
#define MAX_PACKET_SIZE_DAY_TIME (150)
#define MAX_PACKET_SIZE_OBJECT_CHANGE_ON_SLOT (300)
#define MAX_PACKET_SIZE_CHARACTER_SLOT_OBJECT_CHANGE (300)
#define MAX_PACKET_SIZE_LOCAL_CHAT_MESSAGE (100+CHAT_MESSAGE_LENGTH_LIMIT+LOGIN_LENGTH_LIMIT)
#define MAX_PACKET_SIZE_GLOBAL_CHAT_MESSAGE (100+CHAT_MESSAGE_LENGTH_LIMIT+LOGIN_LENGTH_LIMIT)
#define MAX_PACKET_SIZE_PRIVATE_CHAT_MESSAGE (100+CHAT_MESSAGE_LENGTH_LIMIT+LOGIN_LENGTH_LIMIT)
#define MAX_PACKET_SIZE_PRIVATE_CHAT_REQUEST (100+LOGIN_LENGTH_LIMIT)

#define CHARACTER_PLAYER ('p')
#define CHARACTER_NPC ('n')

#define HIT_BLOOD ('b')
#define HIT_NORMAL ('n')
#define HIT_EXPLOSION ('e')
#define HIT_GRENADE_HIT_OBSTACLE ('g')

#define LOG_IN_ERROR_WRONG_NAME_OR_PASSWORD (-1)
#define LOG_IN_ERROR_ALREADY_LOGGED_IN (-2)
#define LOG_IN_ERROR_TIMEOUT (-3)
#define LOG_IN_ERROR_OUTDATED_CLIENT (-4)
#define LOG_IN_ERROR_ACCOUNT_BANNED (-5)

#define PLAYER_OFFLINE (-1)
#define PLAYER_DOESNT_EXIST (-2)

#define TILE_SIZE (50)
#define PLAYER_TILES_VIEW_DISTANCE (14)
#define CHARACTER_RADIUS (22)
#define STEP_SIZE_LIMIT (30)
#define MAX_DELTA (1.2f)
#define NPC_INTERACTION_MAX_DISTANCE (200.f)
#define MAX_PROJECTILE_TRAVEL_DISTANCE (1000.f)

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

#define OBJECT_PLACE_NONE (0)
#define OBJECT_PLACE_GROUND (1)
#define OBJECT_PLACE_INVENTORY (2)
#define OBJECT_PLACE_SLOT (3)
#define OBJECT_PLACE_CONTAINER (4)
#define OBJECT_PLACE_INVENTORY_WEAPON_ATTACHMENT (5)
#define OBJECT_PLACE_SLOT_WEAPON_ATTACHMENT (6)

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

#define TEAM_0 (0) //players' team, citizens' team
#define TEAM_1 (1) //enemies' team

#define SCRIPT_FUNC_ADD_EXP (0)
#define SCRIPT_FUNC_ADD_MONEY (1)
#define SCRIPT_FUNC_SET_QUEST_PROGRESS (2)
#define SCRIPT_FUNC_END_DIALOGUE (3)
#define SCRIPT_IF_FUNC_QUEST_PROGRESS (4)

#define NPC_INTERACTION_TYPE_NONE (0)
#define NPC_INTERACTION_TYPE_TALK (1)
#define NPC_INTERACTION_TYPE_TRADE (2)

#define AI_MOVEMENT_TYPE_STAND (0)
#define AI_MOVEMENT_TYPE_MOVE_BY_CHECKPOINTS (1)
#define AI_MOVEMENT_TYPE_MOVE_BY_DISTANCE (2)

#define CHARACTER_RANK_PLAYER (0)
#define CHARACTER_RANK_GM (1)

#define CHARACTER_FACTION_RANK_RECRUIT (0)
#define CHARACTER_FACTION_RANK_MEMBER (1)
#define CHARACTER_FACTION_RANK_COMMANDER (2)
#define CHARACTER_FACTION_RANK_LEADER (3)

#define _assert_break(expr, name, id, msg) if(!_assert(expr, name, id, msg)) break;
#define _assert_return(expr, name, id, msg) if(!_assert(expr, name, id, msg)) return;
#define _assert_return_value(expr, name, id, msg, returnValue) if(!_assert(expr, name, id, msg)) return returnValue;
#define _assert_exit(expr, name, id, msg) if(!_assert(expr, name, id, msg)) {_getch(); exit(1);}

typedef unsigned char uchar;
#define Character CharacterClass
#define Object ObjectClass

/*const int allowedChatKeys[] = {
    KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,
    KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,KEY_H,KEY_J,KEY_K,KEY_L,
    KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,KEY_N,KEY_M,
    KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,
    KEY_SPACE,KEY_SLASH,KEY_TILDE,KEY_MINUS,KEY_EQUALS,KEY_OPENBRACE,KEY_CLOSEBRACE,
    KEY_COLON,KEY_SEMICOLON,KEY_QUOTE,KEY_BACKSLASH,KEY_BACKSLASH2,KEY_COMMA,KEY_STOP
};
const int allowedChatKeysQuantity = 50;*/

const char VERSION[] = "pre-alpha-1.0";

inline void dateAndTimeToFile(std::ofstream &out);
char *getString(const char *format, const va_list &va);

class LogManagerClass
{
    private:
        std::ofstream logFile;

        void saveString(const char *str, size_t size)
        {
            if(str == NULL) return;
            fwrite(str, 1, size, stdout);
            if(logFile) {
                logFile.write(str, size);
                logFile.flush();
            }
        }

    public:
        bool create(const std::string &path)
        {
            logFile.open(path.c_str());
            if(logFile) {
                logFile << "Log file created on ";
                dateAndTimeToFile(logFile);
                logFile << "\n";
                logFile << "Server version: " << VERSION << "\n";
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
};

extern sf::Clock globalClock;
extern char *currentPacketData;
extern double globalTime;
extern double deltaTime;

extern LogManagerClass logManager;

const int EXP_TABLE_SIZE = 54;
const int EXP_TABLE[] = {0,0,100,300,600,1100,1850,2950,4450,6450,9250,13050,18050,26050,41050,66050,102050,
152050,205050,262050,322050,386050,454050,528050,608050,697050,792050,892050,1002050,1122050,1257050,
1407050,1567050,1735050,1910050,2100050,2310050,2560050,2840050,3170050,3560050,4040050,4620050,5220050,
6010050,7010050,8310050,9960050,11960050,14460050,17460050,21260050,26260050};

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
    logManager.saveMessageVA("error", format, va);
    va_end(va);
    exit(1);
}

inline void _error(const char *format, ...)
{
    if(format == NULL) return;
    va_list va;
    va_start(va, format);
    logManager.saveMessageVA("error", format, va);
    va_end(va);
    exit(1);
}

inline bool _assert(bool expr, const char *playerName, int playerIndex, const char *message)
{
    if(message == NULL) return expr;
    if(!expr) {
        if(playerName != NULL) {
            logManager.saveMessageFormatted("assert", "Assertion failed for player %s (id %d). Message: %s", playerName, playerIndex, message);
        }
        else {
            logManager.saveMessageFormatted("assert", "Assertion failed. Message: %s", message);
        }
    }
    return expr;
}

//char scanCodeToChar(int scancode, bool shift);
LONG crashHandler(struct _EXCEPTION_POINTERS *exInfo);

#endif
