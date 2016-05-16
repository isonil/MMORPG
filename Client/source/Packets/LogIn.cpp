#include "LogIn.hpp"

#include <sstream>
#include "global.hpp"
#include "Master.hpp"

void Packet <PACKET_LOG_IN>::onReceive(const ENetEvent &event)
{
    _assert(playerCharacterID < 0, "Received PACKET_LOG_IN while being already logged in.");

    char ch;
    int status = LOG_IN_ERROR_UNKNOWN;
    int x = 0, y = 0, dir = 0;
    int health = 0, maxHealth = 0, experience = 0, level = 1;
    int base_x = 0, base_y = 0;
    int dayTime = 0;
    int rainType = RAIN_TYPE_NONE, snowType = SNOW_TYPE_NONE, stormType = STORM_TYPE_NONE, fogType = FOG_TYPE_NONE;
    int questsQuantity = 0;

    std::istringstream packet((char*)event.packet->data);
    packet >> ch >> status >> x >> y >> dir >> health >> maxHealth >> experience >> level >> base_x >> base_y >> dayTime >> rainType >> snowType >> stormType >> fogType >> questsQuantity;
    if(status >= 0) {
        CharacterClass &player = Master::getInstance().getWorld().getPlayer(status);
        Master::getInstance().getPlayer().setCharacter(player);

        _assert(questsQuantity == (int)Master::getInstance().Quest.size(), "Quests quantity does not match client data in processPacket_logIn.");

        for(int i=0; i<questsQuantity; ++i) {
            int progress = -1;
            packet >> progress;
            _assert(progress >= 0 && progress <= 100, "Incorrect quest progress in processPacket_logIn.");
            Master::getInstance().Quest[i].progress = progress;
        }

        int objectsReceived = 0;
        for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
            int objectType = -1, p1 = -1, p2 = -1, p3 = -1;
            if(!(packet >> objectType >> p1 >> p2 >> p3)) break;
            _assert(objectType < (int)Master::getInstance().ObjectType.size(), "Object type (character slot) out of bounds in processPacket_logIn.");
            Master::getInstance().assignParamsToObject(player.getObjectOnSlot(i), objectType, p1, p2, p3);
            ++objectsReceived;
        }
        for(size_t i=0; i<CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH; ++i) {
            for(size_t j=0; j<CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT; ++j) {
                int objectType = -1, p1 = -1, p2 = -1, p3 = -1;
                if(!(packet >> objectType >> p1 >> p2 >> p3)) break;
                _assert(objectType < (int)Master::getInstance().ObjectType.size(), "Object type (inventory slot) out of bounds in processPacket_logIn.");
                Master::getInstance().assignParamsToObject(player.getObjectInInventory(i, j), objectType, p1, p2, p3);
                ++objectsReceived;
            }
        }
        _assert(objectsReceived == CHARACTER_OBJECT_SLOTS_QUANTITY+CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH*CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT,
                "Received objects quantity does not match client data in processPacket_logIn.");
        _assert(dayTime >= 0, "Day time is negative in processPacket_logIn.");
        _assert(rainType == RAIN_TYPE_NONE || rainType == RAIN_TYPE_SMALL || rainType == RAIN_TYPE_MEDIUM || rainType == RAIN_TYPE_HEAVY,
                "Unknown rain type in processPacket_logIn.");
        _assert(snowType == SNOW_TYPE_NONE || snowType == SNOW_TYPE_SMALL || snowType == SNOW_TYPE_MEDIUM || snowType == SNOW_TYPE_HEAVY,
                "Unknown snow type in processPacket_logIn.");
        _assert(stormType == STORM_TYPE_NONE || stormType == STORM_TYPE_SMALL || stormType == STORM_TYPE_MEDIUM || stormType == STORM_TYPE_HEAVY,
                "Unknown storm type in processPacket_logIn.");
        _assert(fogType == FOG_TYPE_NONE || fogType == FOG_TYPE_SMALL || fogType == FOG_TYPE_MEDIUM || fogType == FOG_TYPE_HEAVY,
                "Unknown fog type in processPacket_logIn.");
        player.setName(Master::getInstance().login);
        player.setPosition(sf::Vector2f(x, y));
        player.setDirection(dir/100.f);
        player.setVisibility(true);
        player.setParam(CHARACTER_PARAM_HEALTH, health);
        player.setParam(CHARACTER_PARAM_MAX_HEALTH, maxHealth);
        player.setParam(CHARACTER_PARAM_EXPERIENCE, experience);
        player.setParam(CHARACTER_PARAM_LEVEL, level);
        player.setParam(CHARACTER_PARAM_BASE_X, base_x);
        player.setParam(CHARACTER_PARAM_BASE_Y, base_y);
        playerCharacterID = status;
        Master::getInstance().Weather.dayTimeInMinutes = dayTime;
        Master::getInstance().Weather.rainType = rainType;
        Master::getInstance().Weather.snowType = snowType;
        Master::getInstance().Weather.stormType = stormType;
        Master::getInstance().Weather.fogType = fogType;
        if(Master::getInstance().Weather.stormType != STORM_TYPE_NONE) {
            Master::getInstance().Weather.timeout_lightning = globalTime+2000.0+rand()%10000;
        }
        info("Logged in as %s (id %d).", Master::getInstance().login, status);
        Master::getInstance().addMessageToChat(Master::getInstance().Interface.localChat, "Logged in.", CHAT_TAB_LOCAL);
        Master::getInstance().addMessageToChat(Master::getInstance().Interface.localChat, "To start a new private chat use /p name", CHAT_TAB_LOCAL);
    }
    else if(status == LOG_IN_ERROR_WRONG_NAME_OR_PASSWORD) {
        Master::getInstance().getUserInterface().showError("Wrong name or password.");
    }
    else if(status == LOG_IN_ERROR_ALREADY_LOGGED_IN) {
        Master::getInstance().getUserInterface().showError("This character is already logged in. If your client crashed wait 10 seconds and try again.");
    }
    else if(status == LOG_IN_ERROR_TIMEOUT) {
        Master::getInstance().getUserInterface().showError("Please wait a few seconds before next log in.");
    }
    else if(status == LOG_IN_ERROR_OUTDATED_CLIENT) {
        Master::getInstance().getUserInterface().showError("Your client is outdated. Please use updater.");
    }
    else if(status == LOG_IN_ERROR_ACCOUNT_BANNED) {
        Master::getInstance().getUserInterface().showError("Your account is banned.");
    }
    else {
        Master::getInstance().getUserInterface().showError("Unknown login error (code %d). Please make sure you have the latest client version. Login information from server could not be read properly or unknown login error occured.");
    }
}

std::string Packet <PACKET_LOG_IN>::construct(const std::string &name, const std::string &password)
{
    std::ostringstream oss;
    //to do spaces to underscores
    oss << PACKET_LOG_IN << ' ' << VERSION << ' ' << name << ' ' << password;
    return oss.str();
}
