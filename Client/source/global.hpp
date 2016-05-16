/**
* @file
* @brief File containing all defines and global funcs/vars.
*/

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <OpenLayer.hpp>
#include <enet/enet.h>
#include <string>
#include <vector>
#include <windows.h>
#include <audiere.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/**
* @defgroup MISC_DEFINES_GROUP Miscellaneous defines
* @{
*/
#define MINIMUM_SCREEN_WIDTH (1024) /**< Supported screen width requirement.*/
#define MINIMUM_SCREEN_HEIGHT (768) /**< Supported screen height requirement.*/
#define SUPPORTED_TEXTURE_SIZE_REQUIREMENT (1024) /**< Supported texture size requirement for graphics card. Value must be equal or greater than this variable in order to start game.*/
#define TILE_SIZE (50) /**< Single tile size.*/
#define CHARACTER_RADIUS (23) /**< Character body radius.*/
#define PLAYER_TILES_VIEW_DISTANCE (14) /**< Maximum player view distance in tiles.*/
#define NPC_INTERACTION_MAX_DISTANCE (200.f) /**< Maximum distance from player to NPC when interacting (conversation, trade, etc.).*/
#define MAX_PROJECTILE_TRAVEL_DISTANCE (1000.f) /**< Maximum distance for projectile to travel before it disappears.*/
#define CHARACTER_OBJECT_SLOTS_QUANTITY (5) /**< Character slots quantity.*/
#define CHARACTER_OBJECT_SLOT_WEAPON_INDEX (0) /**< Weapon slot index.*/
#define CHAT_LINES_QUANTITY (9) /**< Number of visible lines in chat.*/
#define RAINDROP_SPLASH_ANIMATION_FRAMES_QUANTITY (3) /**< Number of raindrop splash animation frames.*/
#define CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH (7) /**< Number of available slots in inventory in width.*/
#define CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT (4) /**< Number of available slots in inventory in height.*/
#define OBJECTS_PER_TILE_LIMIT (5) /**< Number of maximum objects laying on a single tile.*/
#define WEAPON_ATTACHMENTS_QUANTITY (3) /**< Number of weapon attachments.*/
#define GRASS_TILE_TYPE_START (0) /**< Tile index where grass tiles start.*/
#define GRASS_TILE_TYPE_END (7) /**< Tile index where grass tiles end.*/
#define PARTICLE_TEXTURES_QUANTITY (4) /**< Number of particle textures.*/
#define OBJECT_ID_GRENADE_LAUNCHER (7) /**< Grenade launcher object index.*/
#define CHAT_MESSAGE_LENGTH_LIMIT (50) /**< Limit for a single chat message.*/
#define MAX_DELTA (1.2f) /**< @todo Check if it's even used, make sure it works correctly everywhere.*/
#define LOGIN_LENGTH_LIMIT (15) /**< String length limit for login.*/
#define PASSWORD_LENGTH_LIMIT (15) /**< String length limit for password.*/
#define LIGHT_TEXTURES_QUANTITY (1) /**< Number of light textures.*/
/** @} */

/**
* @defgroup PACKET_DEFINES_GROUP Packet type defines
*
* Packet type is defined by first byte of each packet.
*
* Packet construction details can be read from code.\n
* IN - from NetworkModule methods called processPacket_packetName.\n
* OUT - from UtilityModule methods called getPacketNamePacket.\n
* These are the only places where packets are constructed or read.
*
* @todo Make sure they are constructed only by getPacketNamePacket methods.
*
* @{
*/
#define PACKET_LOG_IN ('l') /**< (IN/OUT) Sent on login attempt, received on server response.*/
#define PACKET_CHARACTER_POSITION ('p') /**< (IN/OUT) Sending player position, receiving other characters position.*/
#define PACKET_OBJECT_CHANGE_ON_GROUND ('o') /**< (IN) Packet containing objects laying on a tile.*/
#define PACKET_OBJECT_CHANGE_IN_INVENTORY ('q') /**< (IN) Packet containing object on a slot in inventory.*/
#define PACKET_OBJECT_CHANGE_ON_SLOT ('w') /**< (IN) Packet containing object on a slot.*/
#define PACKET_CHARACTER_PARAMS ('i') /**< (IN) Packet containing character params.*/
#define PACKET_CHARACTER_LOST_SIGHT ('x') /**< (IN) Packet received when other character goes out of player's view distance.*/
#define PACKET_SHOT ('s') /**< (IN/OUT) Sent on shot attempt, received on someone's shot.*/
#define PACKET_GRENADE_LAUNCHER_SHOT ('n') /**< (IN/OUT) Sent on shot using grenade launcher attempt, received on someone's grenade launcher shot.*/
#define PACKET_GRENADE_THROW ('a') /**< (IN/OUT) Sent on grenade throw attempt, received on someone's grenade throw.*/
#define PACKET_PROJECTILE_HIT ('h') /**< (IN) Received when projectile hits something.*/
#define PACKET_CHARACTER_PARAM_CHANGE ('c') /**< (IN) Received when character's param has changed.*/
#define PACKET_BUILD ('b') /**< not yet implemented.*/
#define PACKET_CHANGE_OBJECT_PLACE_REQUEST ('g') /**< (OUT) Sent on change object place attempt.*/
#define PACKET_SERVER_MESSAGE ('0') /**< (IN) Received on server message.*/
#define PACKET_LOCAL_CHAT_MESSAGE ('1') /**< (IN/OUT) Received on new local chat message, sent when player says something on local chat.*/
#define PACKET_GLOBAL_CHAT_MESSAGE ('2') /**< (IN/OUT) Received on new global chat message, sent when player says something on global chat.*/
#define PACKET_PRIVATE_CHAT_MESSAGE ('3') /**< (IN/OUT) Received on new private chat message, sent when player says something on private chat.*/
#define PACKET_PRIVATE_CHAT_REQUEST ('t') /**< (OUT) Sent when player wants to start a new private chat.*/
#define PACKET_CHARACTER_SLOT_OBJECT_CHANGE ('e') /**< (IN) Received when other character's slot object has changed.*/
#define PACKET_DAY_TIME ('d') /**< (IN) Packet containing current day time.*/
#define PACKET_WEATHER ('r') /**< (IN) Packet containing current weather.*/
#define PACKET_START_TALK_WITH_NPC ('f') /**< (OUT) Sent when player wants to start a conversation with NPC.*/
#define PACKET_CHOOSE_TALK_OPTION ('j') /**< (OUT) Sent when player selects NPC conversation response.*/
#define PACKET_CURRENT_DIALOGUE_BLOCK ('k') /**< (IN) Packet containing current dialogue block.*/
#define PACKET_TRADE_WITH_NPC_OBJECTS_LIST ('m') /**< (IN) Packet containing objects list when trading with NPC.*/
#define PACKET_TRADE_WITH_NPC_BUY_OBJECT ('u') /**< (OUT) Sent when player wants to buy an object from NPC.*/
#define PACKET_QUEST_PROGRESS_CHANGE ('y') /**< (IN) Packet containing quest progress.*/
#define PACKET_END_CURRENT_NPC_INTERACTION ('z') /**< (OUT) Sent when player wans to end current NPC interaction (for example by closing trade window).*/
/** @} */

/**
* @defgroup MAX_PACKET_SIZE_DEFINES_GROUP Max packet size defines
*
* Max packet size in bytes for outgoing packets.\n
* They are used when constructing packet in getPacketNamePacket()
* methods in UtilityModule.
*
* @{
*/
#define MAX_PACKET_SIZE_LOG_IN (150+LOGIN_LENGTH_LIMIT+PASSWORD_LENGTH_LIMIT)
#define MAX_PACKET_SIZE_END_CURRENT_NPC_INTERACTION (5) /**< Max packet size for #PACKET_END_CURRENT_NPC_INTERACTION.*/
#define MAX_PACKET_SIZE_CHOOSE_TALK_OPTION (150) /**< Max packet size for #PACKET_CHOOSE_TALK_OPTION.*/
#define MAX_PACKET_SIZE_CHANGE_OBJECT_PLACE_REQUEST (300) /**< Max packet size for #PACKET_CHANGE_OBJECT_PLACE_REQUEST.*/
#define MAX_PACKET_SIZE_LOCAL_CHAT_MESSAGE (100+CHAT_MESSAGE_LENGTH_LIMIT)
#define MAX_PACKET_SIZE_GLOBAL_CHAT_MESSAGE (100+CHAT_MESSAGE_LENGTH_LIMIT)
#define MAX_PACKET_SIZE_PRIVATE_CHAT_MESSAGE (100+CHAT_MESSAGE_LENGTH_LIMIT)
#define MAX_PACKET_SIZE_PRIVATE_CHAT_REQUEST (100+LOGIN_LENGTH_LIMIT)
/** @} */

/**
* @defgroup LOG_IN_ERROR_DEFINES_GROUP Log in error defines
* @{
*/
#define LOG_IN_ERROR_WRONG_NAME_OR_PASSWORD (-1) /**< Sent login or password was incorrect.*/
#define LOG_IN_ERROR_ALREADY_LOGGED_IN (-2) /**< Received when this character is already in-game.*/
#define LOG_IN_ERROR_TIMEOUT (-3) /**< Received when previous log in attempt was a few seconds ago.*/
#define LOG_IN_ERROR_OUTDATED_CLIENT (-4) /**< Received when client's version is old.*/
#define LOG_IN_ERROR_ACCOUNT_BANNED (-5) /**< Received when this account is banned.*/
#define LOG_IN_ERROR_UNKNOWN (-6) /**< All log in errors with error code equal or less than this one are considered as unknown.*/
/** @} */

#define PLAYER_OFFLINE (-1)
#define PLAYER_DOESNT_EXIST (-2)

#define CHARACTER_PLAYER ('p')
#define CHARACTER_NPC ('n')

#define HIT_BLOOD ('b')
#define HIT_NORMAL ('n')
#define HIT_EXPLOSION ('e')
#define HIT_GRENADE_HIT_OBSTACLE ('g')

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
#define CHARACTER_PARAMS_QUANTITY (7)

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

#define CHAT_TAB_LOCAL (-1)
#define CHAT_TAB_GLOBAL (-2)

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

#define QUEST_TYPE_NONE (0)
#define QUEST_TYPE_MAIN (1)
#define QUEST_TYPE_SIDE (2)

const int AllowedChatKeys[] = {
    KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,
    KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,KEY_H,KEY_J,KEY_K,KEY_L,
    KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,KEY_N,KEY_M,
    KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,
    KEY_SPACE,KEY_SLASH,KEY_TILDE,KEY_MINUS,KEY_EQUALS,KEY_OPENBRACE,KEY_CLOSEBRACE,
    KEY_COLON,KEY_SEMICOLON,KEY_QUOTE,KEY_BACKSLASH,KEY_BACKSLASH2,KEY_COMMA,KEY_STOP
};
const int AllowedChatKeysQuantity = 50;

const char sfKeyArray[][2] = {
    {'a', 'A'}, //A
    {'b', 'B'}, //B
    {'c', 'C'}, //C
    {'d', 'D'}, //D
    {'e', 'E'}, //E
    {'f', 'F'}, //F
    {'g', 'G'}, //G
    {'h', 'H'}, //H
    {'i', 'I'}, //I
    {'j', 'J'}, //J
    {'k', 'K'}, //K
    {'l', 'L'}, //L
    {'m', 'M'}, //M
    {'n', 'N'}, //N
    {'o', 'O'}, //O
    {'p', 'P'}, //P
    {'q', 'Q'}, //Q
    {'r', 'R'}, //R
    {'s', 'S'}, //S
    {'t', 'T'}, //T
    {'u', 'U'}, //U
    {'v', 'V'}, //V
    {'w', 'W'}, //W
    {'x', 'X'}, //X
    {'y', 'Y'}, //Y
    {'z', 'Z'}, //Z
    {'0', ')'}, //Num0
    {'1', '!'}, //Num1
    {'2', '@'}, //Num2
    {'3', '#'}, //Num3
    {'4', '$'}, //Num4
    {'5', '%'}, //Num5
    {'6', '^'}, //Num6
    {'7', '&'}, //Num7
    {'8', '*'}, //Num8
    {'9', '('}, //Num9
    {0, 0}, //Escape
    {0, 0}, //LControl
    {0, 0}, //LShift
    {0, 0}, //LAlt
    {0, 0}, //LSystem
    {0, 0}, //RControl
    {0, 0}, //RShift
    {0, 0}, //RAlt
    {0, 0}, //RSystem
    {0, 0}, //Menu
    {'[', '{'}, //LBracket
    {']', '}'}, //RBracket
    {';', ':'}, //SemiColon
    {',', '<'}, //Comma
    {'.', '>'}, //Period
    {'\'', '\"'}, //Quote
    {'/', '?'}, //Slash
    {'\\', '|'}, //BackSlash
    {'`', '~'}, //Tilde
    {'=', '+'}, //Equal
    {'-', '_'}, //Dash
    {' ', ' '}, //Space
    {0, 0}, //Return
    {0, 0}, //Back
    {0, 0}, //Tab
    {0, 0}, //PageUp
    {0, 0}, //PageDown
    {0, 0}, //End
    {0, 0}, //Home
    {0, 0}, //Insert
    {0, 0}, //Delete
    {'+', '+'}, //Add
    {'-', '-'}, //Subtract
    {'*', '*'}, //Multiply
    {'/', '/'}, //Divide
    {0, 0}, //Left
    {0, 0}, //Right
    {0, 0}, //Up
    {0, 0}, //Down
    {'0', '0'}, //Numpad0
    {'1', '1'}, //Numpad1
    {'2', '2'}, //Numpad2
    {'3', '3'}, //Numpad3
    {'4', '4'}, //Numpad4
    {'5', '5'}, //Numpad5
    {'6', '6'}, //Numpad6
    {'7', '7'}, //Numpad7
    {'8', '8'}, //Numpad8
    {'9', '9'}, //Numpad9
    {0, 0}, //F1
    {0, 0}, //F2
    {0, 0}, //F3
    {0, 0}, //F4
    {0, 0}, //F5
    {0, 0}, //F6
    {0, 0}, //F7
    {0, 0}, //F8
    {0, 0}, //F9
    {0, 0}, //F10
    {0, 0}, //F11
    {0, 0}, //F12
    {0, 0}, //F13
    {0, 0}, //F14
    {0, 0}, //F15
    {0, 0}, //Pause
};
const char VERSION[] = "pre-alpha-1.0";

inline void dateAndTimeToFile(std::ofstream &out);

class LogManagerClass : public std::streambuf
{
    private:
        std::ofstream logFile;
        bool newLine;

        void saveString(const char *str, size_t size)
        {
            fwrite(str, 1, size, stdout);
            if(logFile) {
                logFile.write(str, size);
                logFile.flush();
            }
        }

    protected:
        std::streamsize xsputn(const char *str, std::streamsize size)
        {
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
        bool create(const std::string &path) {
            logFile.open(path.c_str());
            if(logFile) {
                logFile << "Log file created on ";
                dateAndTimeToFile(logFile);
                logFile << "\n";
                logFile << "Client version: " << VERSION << "\n";
                logFile << "Build: " << __DATE__ << " " << __TIME__ << "\n";
                logFile << "\n";
            }
            return logFile;
        }

        void saveMessage(const char *prefix, const char *format, const va_list &va)
        {
            int size = vsnprintf(NULL, 0, format, va);
            if(size < 0) {
                char str[] = "[error] Could not get size in saveMessage.\n";
                saveString(str, strlen(str));
                return;
            }
            char *str = new char[size+1];
            vsnprintf(str, size+1, format, va);
            saveString("[", 1);
            saveString(prefix, strlen(prefix));
            saveString("] ", 2);
            saveString(str, size);
            saveString("\n", 1);
            delete []str;
        }

        void saveMessage(const char *prefix, const char *format, ...)
        {
            va_list va;
            va_start(va, format);
            saveMessage(prefix, format, va);
            va_end(va);
        }

        LogManagerClass()
            :   newLine(true) {
        }
};

extern sf::RenderWindow window;
extern sf::Clock globalClock;
extern sf::RenderTexture colorMapFBO;
extern sf::RenderTexture normalMapFBO;
extern sf::RenderTexture heightMapFBO;
extern sf::RenderTexture shadowMapFBO;
extern sf::RenderTexture ambientShadowMapFBO;
extern sf::RenderTexture lightDiffuseMap1FBO;
extern sf::RenderTexture lightDiffuseMap2FBO;
extern sf::RenderTexture lightSpecularMap1FBO;
extern sf::RenderTexture lightSpecularMap2FBO;
extern sf::RenderTexture sceneFBO;
extern std::vector <sf::Event::KeyEvent> keyBuff;
extern double globalTime;
extern double deltaTime;
extern int mx, my, mb;
extern int playerCharacterIndex;
extern char *currentPacketData;
extern bool isConnectedToServer;
extern bool LMBEventHandled, RMBEventHandled;
extern bool keyBuffHandled;

extern LogManagerClass logManager;

extern LARGE_INTEGER queryPerformance_frequency;
extern bool queryPerformance_isAvailable;

const int EXP_TABLE_SIZE = 54;
const int EXP_TABLE[] = {0,0,100,300,600,1100,1850,2950,4450,6450,9250,13050,18050,26050,41050,66050,102050,
152050,205050,262050,322050,386050,454050,528050,608050,697050,792050,892050,1002050,1122050,1257050,
1407050,1567050,1735050,1910050,2100050,2310050,2560050,2840050,3170050,3560050,4040050,4620050,5220050,
6010050,7010050,8310050,9960050,11960050,14460050,17460050,21260050,26260050};

enum LMBActionEnum {LMB_FREE, LMB_FREE_OUTSIDE, LMB_NEW_PRESSED, LMB_NEW_PRESSED_OUTSIDE, LMB_PRESSED, LMB_PRESSED_OUTSIDE};

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
    va_list va;
    va_start(va, format);
    logManager.saveMessage("info", format, va);
    va_end(va);
}

inline void error(const char *format, ...)
{
    va_list va;
    va_start(va, format);
    logManager.saveMessage("error", format, va);
    va_end(va);
    allegro_message("Error: %s", format);
    exit(1);
}

inline void _assert(bool expr, const char *msg)
{
    if(!expr) {
        logManager.saveMessage("assert", "Assertion failed. Message: %s", msg);
        allegro_message("Assertion failed. Message: %s\nIf this error appeared for an unknown reason\nplease let us know about it.\n-Dev team", msg);
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

void loadTexture(sf::Texture &tex, const std::string &path, bool checkIfExists = false);
void loadImage(sf::Image &img, const std::string &path, bool checkIfExists = false);
void loadSample(SAMPLE **sample, const std::string &path, bool checkIfExists = false);
bool fileExists(const std::string &path);
int getTextWidth(sf::Text &text);
int getTextWidth(const std::string &text, int characterSize);
char scanCodeToChar(int scancode, bool shift);
LONG crashHandler(_EXCEPTION_POINTERS *exInfo);

#endif
