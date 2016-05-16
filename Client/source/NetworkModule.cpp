#include "NetworkModule.hpp"

/**
* @brief Method called from game loop.
*/
void NetworkModule::manageNetworkEvents()
{
    static ENetEvent event;
    int hostStatus;
    while(1) {
        hostStatus = enet_host_service(client, &event, 0);
        if(hostStatus < 0) error("An error occured in enet_host_service (returned %d).", hostStatus);
        else if(hostStatus == 0) break;
        switch(event.type) {
            case ENET_EVENT_TYPE_NONE:
                break;
            case ENET_EVENT_TYPE_CONNECT:
                info("Connection established - %u:%u.",
                     event.peer->address.host,
                     event.peer->address.port);
                peer = event.peer;
                isConnectedToServer = true;
                char packet[MAX_PACKET_SIZE_LOG_IN];
                sprintf(packet, "%c %s %s %s", PACKET_LOG_IN, VERSION, login, password);
                sendPacket(0, packet);
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                //printf("Received packet \"%s\" on channel %u\n",
                //       event.packet->data,event.channelID);
                if(event.packet->dataLength && (char*)event.packet->data[event.packet->dataLength-1] == 0) {
                    currentPacketData = (char*)event.packet->data;
                    processPacket(event);
                }
                currentPacketData = NULL;
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                inGameError = "Disconnected from server.";
                info("Disconnected from server.");
                isConnectedToServer = false;
                playerCharacterIndex = -1;
                login[0] = 0;
                password[0] = 0;
                break;
        }
    }
}

/**
* @brief Method called after receiving packet.
*/
void NetworkModule::processPacket(const ENetEvent &event)
{
    if(event.packet->dataLength == 0) return;

    if(event.packet->data[0] == PACKET_LOG_IN) {
        processPacket_logIn(event);
    }
    if(event.packet->data[0] == PACKET_CHARACTER_POSITION) {
        processPacket_characterPosition(event);
    }
    if(event.packet->data[0] == PACKET_OBJECT_CHANGE_ON_GROUND) {
        processPacket_objectChangeOnGround(event);
    }
    if(event.packet->data[0] == PACKET_OBJECT_CHANGE_IN_INVENTORY) {
        processPacket_objectChangeInInventory(event);
    }
    if(event.packet->data[0] == PACKET_OBJECT_CHANGE_ON_SLOT) {
        processPacket_objectChangeOnSlot(event);
    }
    if(event.packet->data[0] == PACKET_CHARACTER_PARAMS) {
        processPacket_characterParams(event);
    }
    if(event.packet->data[0] == PACKET_CHARACTER_LOST_SIGHT) {
        processPacket_characterLostSight(event);
    }
    if(event.packet->data[0] == PACKET_SHOT) {
        processPacket_shot(event);
    }
    if(event.packet->data[0] == PACKET_GRENADE_LAUNCHER_SHOT) {
        processPacket_grenadeLauncherShot(event);
    }
    if(event.packet->data[0] == PACKET_GRENADE_THROW) {
        processPacket_grenadeThrow(event);
    }
    if(event.packet->data[0] == PACKET_PROJECTILE_HIT) {
        processPacket_projectileHit(event);
    }
    if(event.packet->data[0] == PACKET_CHARACTER_PARAM_CHANGE) {
        processPacket_characterParamChange(event);
    }
    if(event.packet->data[0] == PACKET_SERVER_MESSAGE) {
        processPacket_serverMessage(event);
    }
    if(event.packet->data[0] == PACKET_LOCAL_CHAT_MESSAGE) {
        processPacket_localChatMessage(event);
    }
    if(event.packet->data[0] == PACKET_GLOBAL_CHAT_MESSAGE) {
        processPacket_globalChatMessage(event);
    }
    if(event.packet->data[0] == PACKET_PRIVATE_CHAT_MESSAGE) {
        processPacket_privateChatMessage(event);
    }
    if(event.packet->data[0] == PACKET_PRIVATE_CHAT_REQUEST) {
        processPacket_privateChatRequest(event);
    }
    if(event.packet->data[0] == PACKET_CHARACTER_SLOT_OBJECT_CHANGE) {
        processPacket_characterSlotObjectChange(event);
    }
    if(event.packet->data[0] == PACKET_DAY_TIME) {
        processPacket_dayTime(event);
    }
    if(event.packet->data[0] == PACKET_WEATHER) {
        processPacket_weather(event);
    }
    if(event.packet->data[0] == PACKET_CURRENT_DIALOGUE_BLOCK) {
        processPacket_currentDialogueBlock(event);
    }
    if(event.packet->data[0] == PACKET_TRADE_WITH_NPC_OBJECTS_LIST) {
        processPacket_tradeWithNPCObjectsList(event);
    }
    if(event.packet->data[0] == PACKET_QUEST_PROGRESS_CHANGE) {
        processPacket_questProgressChange(event);
    }
}

/**
* @brief Method called after receiving #PACKET_LOG_IN.
*/
void NetworkModule::processPacket_logIn(const ENetEvent &event)
{
    _assert(playerCharacterIndex < 0, "Received PACKET_LOG_IN while being already logged in.");

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
        Player.resize(status+1);
        _assert(questsQuantity == (int)Quest.size(), "Quests quantity does not match client data in processPacket_logIn.");

        for(int i=0; i<questsQuantity; ++i) {
            int progress = -1;
            packet >> progress;
            _assert(progress >= 0 && progress <= 100, "Incorrect quest progress in processPacket_logIn.");
            Quest[i].progress = progress;
        }

        int objectsReceived = 0;
        for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
            int objectType = -1, p1 = -1, p2 = -1, p3 = -1;
            if(!(packet >> objectType >> p1 >> p2 >> p3)) break;
            _assert(objectType < (int)ObjectType.size(), "Object type (character slot) out of bounds in processPacket_logIn.");
            assignParamsToObject(Player[status].objectOnSlot[i], objectType, p1, p2, p3);
            ++objectsReceived;
        }
        for(size_t i=0; i<Player[status].objectInInventory.size(); ++i) {
            for(size_t j=0; j<Player[status].objectInInventory[i].size(); ++j) {
                int objectType = -1, p1 = -1, p2 = -1, p3 = -1;
                if(!(packet >> objectType >> p1 >> p2 >> p3)) break;
                _assert(objectType < (int)ObjectType.size(), "Object type (inventory slot) out of bounds in processPacket_logIn.");
                assignParamsToObject(Player[status].objectInInventory[i][j], objectType, p1, p2, p3);
                ++objectsReceived;
            }
        }
        _assert(!Player[status].objectInInventory.empty(), "There are no player's inventory slots in processPacket_logIn.");
        _assert(Player[status].objectInInventory[0].size(), "There are no player's inventory slots in processPacket_logIn.");
        _assert(objectsReceived == CHARACTER_OBJECT_SLOTS_QUANTITY+(int)Player[status].objectInInventory.size()*(int)Player[status].objectInInventory[0].size(),
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
        Player[status].name = login;
        Player[status].x = x;
        Player[status].y = y;
        Player[status].dir = dir/100.f;
        Player[status].isSeen = true;
        Player[status].param[CHARACTER_PARAM_HEALTH] = health;
        Player[status].param[CHARACTER_PARAM_MAX_HEALTH] = maxHealth;
        Player[status].param[CHARACTER_PARAM_EXPERIENCE] = experience;
        Player[status].param[CHARACTER_PARAM_LEVEL] = level;
        Player[status].param[CHARACTER_PARAM_BASE_X] = base_x;
        Player[status].param[CHARACTER_PARAM_BASE_Y] = base_y;
        playerCharacterIndex = status;
        Weather.dayTimeInMinutes = dayTime;
        Weather.rainType = rainType;
        Weather.snowType = snowType;
        Weather.stormType = stormType;
        Weather.fogType = fogType;
        if(Weather.stormType != STORM_TYPE_NONE) Weather.timeout_lightning = globalTime+2000.0+rand()%10000;
        info("Logged in as %s (id %d).", login, status);
        addMessageToChat(Interface.localChat, "Logged in.", CHAT_TAB_LOCAL);
        addMessageToChat(Interface.localChat, "To start a new private chat use /p name", CHAT_TAB_LOCAL);
    }
    else if(status == LOG_IN_ERROR_WRONG_NAME_OR_PASSWORD) {
        inGameError = "Wrong name or password.";
    }
    else if(status == LOG_IN_ERROR_ALREADY_LOGGED_IN) {
        inGameError = "This character is already logged in. If your client crashed wait 10 seconds and try again.";
    }
    else if(status == LOG_IN_ERROR_TIMEOUT) {
        inGameError = "Please wait a few seconds before next log in.";
    }
    else if(status == LOG_IN_ERROR_OUTDATED_CLIENT) {
        inGameError = "Your client is outdated. Please use updater.";
    }
    else if(status == LOG_IN_ERROR_ACCOUNT_BANNED) {
        inGameError = "Your account is banned.";
    }
    else {
        inGameError = "Unknown login error (code %d). Please make sure you have the latest client version. Login information from server could not be read properly or unknown login error occured.";
    }
}

/**
* @brief Method called after receiving #PACKET_CHARACTER_POSITION.
*/
void NetworkModule::processPacket_characterPosition(const ENetEvent &event)
{
    char characterSet = 0;
    int id = 0, x = 0, y = 0, dir = 0;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d %d", &characterSet, &id, &x, &y, &dir);

    _assert(isValidCharacterSet(characterSet), "Invalid character set in processPacket_characterPosition.");
    _assert(id >= 0,"Character index is negative in processPacket_characterPosition.");

    CharacterClass *character;
    if(characterSet == CHARACTER_PLAYER) {
        if(id >= (int)Player.size()) Player.resize(id+1);
        character = &Player[id];
    }
    else {
        if(id >= (int)NPC.size()) NPC.resize(id+1);
        character = &NPC[id];
    }

    if(id == playerCharacterIndex && characterSet == CHARACTER_PLAYER) {
        Player[id].x = x;
        Player[id].y = y;
        Player[id].dir = dir/100.f;
    }
    else if(fabs(character->x-x) > 150.f || fabs(character->y-y) > 150.f) {
        character->x = x;
        character->toX =x ;
        character->y = y;
        character->toY =y ;
        character->dir = dir/100.f;
        character->speed = 7.5f;
    }
    else {
        character->toX = x;
        character->toY = y;
        float distance = getDistance(character->x, character->y, x, y);
        character->speed = distance*0.24f;
    }
    character->toDir = dir/100.f;
}

/**
* @brief Method called after receiving #PACKET_OBJECT_CHANGE_ON_GROUND.
*/
void NetworkModule::processPacket_objectChangeOnGround(const ENetEvent &event)
{
    char ch;
    int objectType = -1, x = 0, y = 0, p1 = -1, p2 = -1, p3 = -1;
    std::istringstream packet((char*)event.packet->data);
    packet >> ch >> x >> y;

    _assert(!isOutOfMap(x, y) ,"Position out of bounds in processPacket_objectChangeOnGround.");
    Tile[x][y].object.clear();
    while(packet >> objectType >> p1 >> p2 >> p3) {
        if(objectType >= 0) {
            Tile[x][y].object.push_back(ObjectClass());
            _assert(objectType < (int)ObjectType.size(), "Object type out of bounds in processPacket_objectChangeOnGround.");
            assignParamsToObject(Tile[x][y].object.back(), objectType, p1, p2, p3);
        }
    }
}

/**
* @brief Method called after receiving #PACKET_OBJECT_CHANGE_IN_INVENTORY.
*/
void NetworkModule::processPacket_objectChangeInInventory(const ENetEvent &event)
{
    int x = 0, y = 0, objectType = -1, p1 = -1, p2 = -1, p3 = -1;
    sscanf((char*)event.packet->data, "%*c %d %d %d %d %d %d", &x, &y, &objectType, &p1, &p2, &p3);

    _assert(x >= 0 && x < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
            y >= 0 && y < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT,
            "Position out of bounds in processPacket_objectChangeInInventory.");
    _assert(objectType < (int)ObjectType.size(),
            "Object type out of bounds in processPacket_objectChangeInInventory.");

    Player[playerCharacterIndex].objectInInventory[x][y].clear();
    assignParamsToObject(Player[playerCharacterIndex].objectInInventory[x][y], objectType, p1, p2, p3);
}

/**
* @brief Method called after receiving #PACKET_OBJECT_CHANGE_ON_SLOT.
*/
void NetworkModule::processPacket_objectChangeOnSlot(const ENetEvent &event)
{
    int slot = 0, objectType = -1, p1 = -1, p2 = -1, p3 = -1;
    sscanf((char*)event.packet->data, "%*c %d %d %d %d %d", &slot, &objectType, &p1, &p2, &p3);

    _assert(slot >= 0 && slot < CHARACTER_OBJECT_SLOTS_QUANTITY,
            "Slot index out of bounds in processPacket_objectChangeOnSlot.");
    _assert(objectType < (int)ObjectType.size(),
            "Object type out of bounds in processPacket_objectChangeOnSlot.");

    Player[playerCharacterIndex].objectOnSlot[slot].clear();
    assignParamsToObject(Player[playerCharacterIndex].objectOnSlot[slot], objectType, p1, p2, p3);
}

/**
* @brief Method called after receiving #PACKET_CHARACTER_PARAMS.
*/
void NetworkModule::processPacket_characterParams(const ENetEvent &event)
{
    char ch, characterSet=0;
    int id = 0, x = 0, y = 0, dir = 0;
    int health = 0, maxHealth=0;
    int level = 1;
    std::string name = "undefined";

    std::istringstream packet((char*)event.packet->data);
    packet >> ch >> characterSet >> id >> name >> x >> y >> dir >> health >> maxHealth >> level;

    _assert(isValidCharacterSet(characterSet), "Invalid character set in processPacket_characterParams.");
    _assert(id >= 0, "Character index is negative in processPacket_characterParams.");

    CharacterClass *character;
    if(characterSet == CHARACTER_PLAYER) {
        if(id >= (int)Player.size()) Player.resize(id+1);
        character = &Player[id];
    }
    else {
        if(id >= (int)NPC.size()) NPC.resize(id+1);
        character = &NPC[id];
    }
    character->name = name;
    character->x = x;
    character->y = y;
    character->toX = x;
    character->toY = y;
    character->dir = dir/100.f;
    character->toDir = dir/100.f;
    character->isSeen = true;
    character->param[CHARACTER_PARAM_HEALTH] = health;
    character->param[CHARACTER_PARAM_MAX_HEALTH] = maxHealth;
    character->param[CHARACTER_PARAM_LEVEL] = level;
    for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
        packet >> character->objectOnSlot[i].type;
        _assert(character->objectOnSlot[i].type < (int)ObjectType.size(),
                "Slot object type out of bounds in processPacket_characterParams.");
    }
}

/**
* @brief Method called after receiving #PACKET_CHARACTER_LOST_SIGHT.
*/
void NetworkModule::processPacket_characterLostSight(const ENetEvent &event)
{
    char characterSet = 0;
    int id = 0;
    sscanf((char*)event.packet->data, "%*c %c %d", &characterSet, &id);

    _assert(isValidCharacterSet(characterSet), "Invalid character set in processPacket_characterLostSight.");
    _assert(id >= 0,"Character index is negative in processPacket_characterLostSight.");

    CharacterClass *character;
    if(characterSet == CHARACTER_PLAYER) {
        if(id >= (int)Player.size()) Player.resize(id+1);
        character = &Player[id];
    }
    else {
        if(id >= (int)NPC.size()) NPC.resize(id+1);
        character = &NPC[id];
    }
    character->isSeen = false;
    character->x = 0.f;
    character->y = 0.f;
    character->toX = 0.f;
    character->toY = 0.f;
}

/**
* @brief Method called after receiving #PACKET_SHOT.
*/
void NetworkModule::processPacket_shot(const ENetEvent &event)
{
    char characterSet=0;
    int ownerId = 0, x = 0, y = 0, dir = 0, projectileId = 0, weaponObjectType = -1;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d %d %d %d", &characterSet, &ownerId, &x, &y, &dir, &projectileId, &weaponObjectType);

    _assert(isValidCharacterSet(characterSet), "Invalid character set in processPacket_shot.");
    _assert(ownerId >= 0, "Character index is negative in processPacket_shot.");
    _assert(projectileId >= 0, "Projectile id is negative in processPacket_shot.");

    if(characterSet == CHARACTER_PLAYER) {
        if(ownerId >= (int)Player.size()) Player.resize(ownerId+1);
    }
    else {
        if(ownerId >= (int)NPC.size()) NPC.resize(ownerId+1);
    }

    bool isMissile = false;
    if(weaponObjectType >= 0) {
        _assert(weaponObjectType < (int)ObjectType.size(), "Weapon object type out of bounds in processPacket_shot.");
        if(ObjectType[weaponObjectType].weaponType == WEAPON_TYPE_ROCKET_LAUNCHER) isMissile = true;
        if(ObjectType[weaponObjectType].useSound != NULL) {
            playPositionalSound(ObjectType[weaponObjectType].useSound, Player[playerCharacterIndex].x, Player[playerCharacterIndex].y, x, y);
        }
    }

    Projectile.push_back(ProjectileClass(characterSet,
                                         ownerId,
                                         x, y,
                                         dir/100.f,
                                         projectileId,
                                         isMissile ? PROJECTILE_TYPE_MISSILE : PROJECTILE_TYPE_BULLET));
    Particle.push_back(ParticleClass(x, y, 0.f, 0.f, 60.f, (rand()%360)/180.f*M_PI, 1, sf::Color(120,90,80), 255.f, true));

    for(int i=0; i<2; ++i) {
        Particle.push_back(ParticleClass(x+rand()%3-1,
                                         y+rand()%3-1,
                                         (rand()%360)/180.f*M_PI,
                                         0.4f, 4.f,
                                         (rand()%360)/180.f*M_PI,
                                         0, sf::Color(20,20,20), 255.f, true));
    }
    if(isMissile) {
        float missileSmoke_x = x-cos(dir/100.f)*75.f;
        float missileSmoke_y = y-sin(dir/100.f)*75.f;
        for(int i=0; i<6; ++i) {
            Particle.push_back(ParticleClass(missileSmoke_x+rand()%13-6,
                                             missileSmoke_y+rand()%13-6,
                                             (rand()%360)/180.f*M_PI,
                                             0.4f, 4.f,
                                             (rand()%360)/180.f*M_PI,
                                             0, sf::Color(20,20,20),255.f, true));
        }
    }

    if(characterSet == CHARACTER_PLAYER && ownerId == playerCharacterIndex) {
        int offsetX = rand()%2+2;
        int offsetY = rand()%2+2;
        viewOffsetX = (rand()%2 == 0 ?(offsetX) : (-offsetX));
        viewOffsetY = (rand()%2 == 0 ?(offsetY) : (-offsetY));
        if(weaponObjectType >= 0) {
            if(ObjectType[weaponObjectType].weaponType == WEAPON_TYPE_ROCKET_LAUNCHER) {
                viewOffsetX = -cos(dir/100.f)*(11+rand()%3);
                viewOffsetY = -sin(dir/100.f)*(11+rand()%3);
            }
        }
        ObjectClass *weapon = &Player[playerCharacterIndex].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX];
        if(weapon->type >= 0 && weapon->type == weaponObjectType) {
            _assert(weapon->type < (int)ObjectType.size(), "Player weapon object type out of bounds in processPacket_shot.");
            weapon->timeout_shot = globalTime+ObjectType[weapon->type].baseShotDelay;
        }
    }
}

/**
* @brief Method called after receiving #PACKET_GRENADE_LAUNCHER_SHOT.
*/
void NetworkModule::processPacket_grenadeLauncherShot(const ENetEvent &event)
{
    char characterSet=0;
    int ownerId = 0, x = 0, y = 0, dir = 0, projectileId = 0, weaponObjectType = -1;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d %d %d %d", &characterSet, &ownerId, &x, &y, &dir, &projectileId, &weaponObjectType);

    _assert(isValidCharacterSet(characterSet), "Invalid character set in processPacket_grenadeLauncherShot.");
    _assert(ownerId >= 0, "Character index is negative in processPacket_grenadeLauncherShot.");
    _assert(projectileId >= 0, "Projectile id is negative in processPacket_grenadeLauncherShot.");

    if(characterSet == CHARACTER_PLAYER) {
        if(ownerId >= (int)Player.size()) Player.resize(ownerId+1);
    }
    else {
        if(ownerId >= (int)NPC.size()) NPC.resize(ownerId+1);
    }

    _assert(weaponObjectType < (int)ObjectType.size(), "Weapon object type out of bounds in processPacket_grenadeLauncherShot.");
    playPositionalSound(grenadeLauncherShotSample, Player[playerCharacterIndex].x, Player[playerCharacterIndex].y, x, y);
    Projectile.push_back(ProjectileClass(characterSet,
                                         ownerId,
                                         x, y,
                                         dir/100.f,
                                         projectileId,
                                         PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE));
    for(int i=0; i<6; ++i) {
        Particle.push_back(ParticleClass(x+rand()%7-3,
                                         y+rand()%7-3,
                                         (rand()%360)/180.f*M_PI,
                                         0.4f, 4.f,
                                         (rand()%360)/180.f*M_PI,
                                         0, sf::Color(20,20,20), 255.f, true));
    }

    if(characterSet == CHARACTER_PLAYER && ownerId == playerCharacterIndex) {
        viewOffsetX = -cos(dir/100.f)*(7+rand()%3);
        viewOffsetY = -sin(dir/100.f)*(7+rand()%3);
        timeout_grenadeLauncherShot = globalTime+3000;
    }
}

/**
* @brief Method called after receiving #PACKET_GRENADE_THROW.
*/
void NetworkModule::processPacket_grenadeThrow(const ENetEvent &event)
{
    char characterSet=0;
    int ownerId = 0, x = 0, y = 0, dir = 0, projectileId = 0, target_x = 0, target_y = 0;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d %d %d %d %d", &characterSet, &ownerId, &x, &y, &dir, &projectileId, &target_x, &target_y);

    _assert(isValidCharacterSet(characterSet), "Invalid character set in processPacket_grenadeThrow.");
    _assert(ownerId >= 0, "Character index is negative in processPacket_grenadeThrow.");
    _assert(projectileId >= 0, "Projectile id is negative in processPacket_grenadeThrow.");

    if(characterSet == CHARACTER_PLAYER) {
        if(ownerId >= (int)Player.size()) Player.resize(ownerId+1);
    }
    else {
        if(ownerId >= (int)NPC.size()) NPC.resize(ownerId+1);
    }

    playPositionalSound(grenadeThrowSample, Player[playerCharacterIndex].x, Player[playerCharacterIndex].y, x, y);
    Projectile.push_back(ProjectileClass(characterSet,
                                         ownerId,
                                         x, y,
                                         dir/100.f,
                                         projectileId,
                                         PROJECTILE_TYPE_GRENADE));
    Projectile.back().grenadeRotation = (rand()%360)*M_PI/180.f;
    Projectile.back().grenadeThrowDistance = getDistance(x,y,target_x,target_y);
    Projectile.back().timeout_grenadeExplode = globalTime+3000.0;

    if(characterSet == CHARACTER_PLAYER && ownerId == playerCharacterIndex) {
        viewOffsetX = -cos(dir/100.f)*(3+rand()%3);
        viewOffsetY = -sin(dir/100.f)*(3+rand()%3);
        timeout_grenadeThrow = globalTime+3000.0;
    }
}

/**
* @brief Method called after receiving #PACKET_PROJECTILE_HIT.
*/
void NetworkModule::processPacket_projectileHit(const ENetEvent &event)
{
    char hitType = 0;
    int x = 0, y = 0, projectileId = 0;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d", &hitType, &x, &y, &projectileId);

    _assert(hitType == HIT_BLOOD || hitType == HIT_NORMAL ||
            hitType == HIT_EXPLOSION || hitType == HIT_GRENADE_HIT_OBSTACLE,
            "Invalid hit type in processPacket_projectileHit.");
    _assert(projectileId >= 0,"Projectile id is negative in processPacket_projectileHit.");

    for(std::list <ProjectileClass>::iterator it=Projectile.begin(); it!=Projectile.end();) {
        if(it->id == projectileId) {
            if(hitType == HIT_GRENADE_HIT_OBSTACLE) {
                it->x = x-cos(it->dir)*5.f;
                it->y = y-sin(it->dir)*5.f;
                it->grenadeFlySpeed = 0.f;
            }
            else Projectile.erase(it);
            break;
        }
        ++it;
    }
    if(hitType == HIT_BLOOD) {
        for(int i=0; i<5; ++i) {
            Particle.push_back(ParticleClass(x+rand()%7-3,
                                             y+rand()%7-3,
                                             (rand()%360)/180.f*M_PI,
                                             7.f, 30.f,
                                             (rand()%360)/180.f*M_PI,
                                             2, sf::Color(50,0,0), 255.f, true));
        }
        //PlayPositionalSound(bulletBloodHitSample,Player[playerCharacterIndex].x,Player[playerCharacterIndex].y,x,y);
    }
    else if(hitType == HIT_NORMAL) {
        for(int i=0; i<5; ++i) {
            Particle.push_back(ParticleClass(x+rand()%3-1,
                                             y+rand()%3-1,
                                             (rand()%360)/180.f*M_PI,
                                             1.f, 6.5f,
                                             (rand()%360)/180.f*M_PI,
                                             0, sf::Color(20, 20, 20), 255.f, true));
        }
        //PlayPositionalSound(bulletHitSample,Player[playerCharacterIndex].x,Player[playerCharacterIndex].y,x,y);
    }
    else if(hitType == HIT_EXPLOSION) {
        for(int i=0; i<30; ++i) {
            Particle.push_back(ParticleClass(x+rand()%13-6,
                                             y+rand()%13-6,
                                             (rand()%360)/180.f*M_PI,
                                             0.3f,
                                             5.f+(rand()%80)/100.f,
                                             0.f, 3,
                                             sf::Color(100+rand()%50, 20+rand()%80, 30),
                                             255.f, true));
        }
        for(int i=0; i<150; ++i) {
            Particle.push_back(ParticleClass(x+rand()%25-14,
                                             y+rand()%25-14,
                                             (rand()%360)/180.f*M_PI,
                                             0.3f+(rand()%80)/100.f,
                                             5.f+(rand()%80)/100.f,
                                             0.f, 3, sf::Color::Black,
                                             220.f, false));
        }
        for(int i=0; i<150; ++i) {
            Particle.push_back(ParticleClass(x+rand()%25-14,
                                             y+rand()%25-14,
                                             (rand()%360)/180.f*M_PI,
                                             0.3f+(rand()%150)/100.f,
                                             5.f+(rand()%80)/100.f,
                                             0.f, 3,
                                             sf::Color(100+rand()%50, 20+rand()%80, 30),
                                             255.f, true));
        }

        float dir = atan2(y-Player[playerCharacterIndex].y, x-Player[playerCharacterIndex].x);
        float distance = getDistance(Player[playerCharacterIndex].x, Player[playerCharacterIndex].y, x, y);
        if(distance > 1200.f) distance = 1200.f;
        viewOffsetX = -cos(dir)*(4.f+(1200.f-distance)/45.f);
        viewOffsetY = -sin(dir)*(4.f+(1200.f-distance)/45.f);
        playPositionalSound(explosionSample, Player[playerCharacterIndex].x, Player[playerCharacterIndex].y, x, y);
    }
    else if(hitType == HIT_GRENADE_HIT_OBSTACLE) {
        playPositionalSound(grenadeBounceSample, Player[playerCharacterIndex].x, Player[playerCharacterIndex].y, x, y);
    }
}

/**
* @brief Method called after receiving #PACKET_CHARACTER_PARAM_CHANGE.
*/
void NetworkModule::processPacket_characterParamChange(const ENetEvent &event)
{
    char characterSet = 0;
    int id = 0, param = 0, value = 0;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d", &characterSet, &id, &param, &value);

    _assert(isValidCharacterSet(characterSet), "Invalid character set in processPacket_characterParamChange.");
    _assert(id >= 0, "Character index is negative in processPacket_characterParamChange.");
    _assert(param >= 0 && param < CHARACTER_PARAMS_QUANTITY, "Character param out of bounds in processPacket_characterParamChange.");

    CharacterClass *character;
    if(characterSet == CHARACTER_PLAYER) {
        if(id >= (int)Player.size()) Player.resize(id+1);
        character = &Player[id];
    }
    else {
        if(id >= (int)NPC.size()) NPC.resize(id+1);
        character = &NPC[id];
    }

    if(characterSet == CHARACTER_PLAYER && id == playerCharacterIndex) {
        if(param == CHARACTER_PARAM_HEALTH && value < character->param[param]) {
            int offsetX = rand()%2+2;
            int offsetY = rand()%2+2;
            viewOffsetX = (rand()%2 == 0?(offsetX):(-offsetX));
            viewOffsetY = (rand()%2 == 0?(offsetY):(-offsetY));
        }
        if(param == CHARACTER_PARAM_EXPERIENCE) {
            int diff = value-character->param[param];
            if(diff > 0) {
                char message[100];
                sprintf(message, "+%d exp", diff);
                Interface.statusLogMessage.push_back(StatusLogMessageClass(message, sf::Color(100, 100, 255)));
            }
            else if(diff < 0) {
                char message[100];
                sprintf(message, "%d exp", diff);
                Interface.statusLogMessage.push_back(StatusLogMessageClass(message, sf::Color(255, 50, 50)));
            }
        }
        if(param == CHARACTER_PARAM_MONEY) {
            int diff = value-character->param[param];
            if(diff > 0) {
                char message[100];
                sprintf(message, "+%d money", diff);
                Interface.statusLogMessage.push_back(StatusLogMessageClass(message, sf::Color(255, 255, 50)));
            }
            else if(diff < 0) {
                char message[100];
                sprintf(message, "%d money", diff);
                Interface.statusLogMessage.push_back(StatusLogMessageClass(message, sf::Color(255, 50, 50)));
            }
        }
        if(param == CHARACTER_PARAM_LEVEL) {
            int diff = value-character->param[param];
            if(diff > 0) {
                Interface.statusLogMessage.push_back(StatusLogMessageClass("You advanced in experience level.", sf::Color(50, 255, 50)));
            }
            else if(diff < 0) {
                Interface.statusLogMessage.push_back(StatusLogMessageClass("You lost an experience level.", sf::Color(255, 50, 50)));
            }
        }
    }
    if(param == CHARACTER_PARAM_LEVEL) {
        int diff = value-character->param[param];
        if(diff > 0) {
            for(int i=0; i<100; ++i) {
                Particle.push_back(ParticleClass(character->x+rand()%25-12,
                                                 character->y+rand()%25-12,
                                                 (rand()%360)/180.f*M_PI,
                                                 0.4f, 4.f,
                                                 (rand()%360)/180.f*M_PI,
                                                 0, sf::Color(20, 20, 150),
                                                 255.f, true));
            }
            playPositionalSound(levelUpSample, Player[playerCharacterIndex].x, Player[playerCharacterIndex].y, character->x, character->y);
        }
    }
    character->param[param] = value;
}

/**
* @brief Method called after receiving #PACKET_SERVER_MESSAGE.
*/
void NetworkModule::processPacket_serverMessage(const ENetEvent &event)
{
    std::string message;
    for(size_t i=2; i<event.packet->dataLength; ++i)
        if(event.packet->data[i] != '\0') message += event.packet->data[i];
    addMessageToChat(Interface.localChat, message, CHAT_TAB_LOCAL);
    addMessageToChat(Interface.globalChat, message, CHAT_TAB_GLOBAL);
}

/**
* @brief Method called after receiving #PACKET_LOCAL_CHAT_MESSAGE.
*/
void NetworkModule::processPacket_localChatMessage(const ENetEvent &event)
{
    std::string playerIndexStr;
    int playerIndex = -1;
    std::string message;
    bool spaceEncountered = false;

    for(size_t i=2; i<event.packet->dataLength; ++i) {
        if(event.packet->data[i] == '\0') continue;
        if(event.packet->data[i] == ' ' && !spaceEncountered) spaceEncountered = true;
        else if(spaceEncountered) {
            message += event.packet->data[i];
        }
        else {
            playerIndexStr += event.packet->data[i];
        }
    }

    _assert(playerIndexStr.size(), "Player index string is empty in processPacket_localChatMessage.");
    sscanf(playerIndexStr.c_str(), "%d", &playerIndex);
    _assert(playerIndex >= 0,"Player index is negative in processPacket_localChatMessage.");

    if(playerIndex >= (int)Player.size()) Player.resize(playerIndex+1);
    addMessageToChat(Interface.localChat, message, CHAT_TAB_LOCAL);
    std::string messageOverHead;
    size_t colonPos = message.find(':');
    if(colonPos != std::string::npos && colonPos+2 < message.size()) {
        messageOverHead = message.substr(colonPos+2);
    }
    else messageOverHead = message;

    sf::Text text;
    text.setCharacterSize(11);

    std::string buff;
    for(size_t i=0; i<messageOverHead.size(); ++i) {
        text.setString(buff+messageOverHead[i]);
        if(getTextWidth(text) > 200) {
            if(buff.size()) {
                size_t rspace = buff.rfind(' ');
                if(rspace != std::string::npos) {
                    int spaceLeftEnd = (int)rspace;
                    while(spaceLeftEnd >= 0 && buff[spaceLeftEnd] == ' ') {
                        --spaceLeftEnd;
                    }
                    if(spaceLeftEnd >= 0) {
                        Player[playerIndex].messageOverHead.push_back(MessageOverHeadClass(buff.substr(0, spaceLeftEnd+1)));
                    }
                    if(rspace+1 < buff.size()) buff = buff.substr(rspace+1);
                    else buff.clear();
                }
                else {
                    Player[playerIndex].messageOverHead.push_back(MessageOverHeadClass(buff+'-'));
                    buff.clear();
                }
            }
        }
        buff += messageOverHead[i];
    }
    if(buff.size()) Player[playerIndex].messageOverHead.push_back(MessageOverHeadClass(buff));
}

/**
* @brief Method called after receiving #PACKET_GLOBAL_CHAT_MESSAGE.
*/
void NetworkModule::processPacket_globalChatMessage(const ENetEvent &event)
{
    std::string message;
    for(size_t i=2; i<event.packet->dataLength; ++i)
        if(event.packet->data[i] != '\0') message += event.packet->data[i];
    addMessageToChat(Interface.globalChat, message, CHAT_TAB_GLOBAL);
}

/**
* @brief Method called after receiving #PACKET_PRIVATE_CHAT_MESSAGE.
*/
void NetworkModule::processPacket_privateChatMessage(const ENetEvent &event)
{
    int messageStartIndex = -1;
    std::string playerIndexStr;
    int playerIndex = -1;
    std::string message;
    bool spaceEncountered = false;

    for(size_t i=2; i<event.packet->dataLength; ++i) {
        if(event.packet->data[i] == '\0') continue;
        if(event.packet->data[i] == ' ' && !spaceEncountered) spaceEncountered = true;
        else if(spaceEncountered) {
            message += event.packet->data[i];
            if(messageStartIndex == -1) messageStartIndex = i;
        }
        else {
            playerIndexStr += event.packet->data[i];
        }
    }

    _assert(playerIndexStr.size(), "Player index string is empty in processPacket_privateChatMessage.");
    sscanf(playerIndexStr.c_str(), "%d", &playerIndex);
    _assert(playerIndex >= 0, "Player index is negative in processPacket_privateChatMessage.");

    if(messageStartIndex != -1) {
        if(playerIndex >= (int)Player.size()) Player.resize(playerIndex+1);
        if(!Player[playerIndex].name.size()) {
            std::string newName;
            for(size_t i=messageStartIndex; i<event.packet->dataLength; ++i) {
                if(event.packet->data[i] == ':' || event.packet->data[i] == '\0') break;
                newName += event.packet->data[i];
            }
            Player[playerIndex].name = newName;
        }
        bool tabExists = false;
        for(size_t i=0; i<Interface.chatTab.size(); ++i) {
            if(Interface.chatTab[i].chat == playerIndex) {
                tabExists = true;
                break;
            }
        }
        if(!tabExists) {
            Interface.chatTab.push_back(ChatTabClass(playerIndex));
        }
        addMessageToChat(Player[playerIndex].privateChat, message, playerIndex);
    }
}

/**
* @brief Method called after receiving #PACKET_PRIVATE_CHAT_REQUEST.
*/
void NetworkModule::processPacket_privateChatRequest(const ENetEvent &event)
{
    int playerIndex = 0;
    char *name = new char[event.packet->dataLength+1];
    name[0] = 0;

    sscanf((char*)event.packet->data, "%*c %d %s", &playerIndex, name);

    if(playerIndex == PLAYER_OFFLINE) {
        addMessageToCurrentChat("Player is offline.");
    }
    else if(playerIndex == PLAYER_DOESNT_EXIST) {
        addMessageToCurrentChat("Player doesn't exist.");
    }
    else if(playerIndex >= 0) {
        if(playerIndex >= (int)Player.size()) Player.resize(playerIndex+1);
        bool tabExists = false;
        for(size_t i=0; i<Interface.chatTab.size(); ++i) {
            if(Interface.chatTab[i].chat == playerIndex) {
                tabExists = true;
                break;
            }
        }
        if(!tabExists) {
            Interface.chatTab.push_back(ChatTabClass(playerIndex));
        }
        Interface.currentChat = playerIndex;
    }
    delete []name;
}

/**
* @brief Method called after receiving #PACKET_CHARACTER_SLOT_OBJECT_CHANGE.
*
* It cannot be merged with #PACKET_OBJECT_CHANGE_ON_SLOT because here
* none of the object informations are sent. Just object type index.
*/
void NetworkModule::processPacket_characterSlotObjectChange(const ENetEvent &event)
{
    char characterSet = 0;
    int characterIndex = -1, slot = -1, objectType = -1;
    sscanf((char*)event.packet->data, "%*c %c %d %d %d", &characterSet, &characterIndex, &slot, &objectType);

    _assert(isValidCharacterSet(characterSet), "Invalid character set in processPacket_characterSlotObjectChange.");
    _assert(characterIndex >= 0, "Character index is negative in processPacket_characterSlotObjectChange.");
    _assert(slot >= 0 && slot < CHARACTER_OBJECT_SLOTS_QUANTITY, "Slot index out of bounds in processPacket_characterSlotObjectChange.");
    _assert(objectType < (int)ObjectType.size(), "Object type out of bounds in processPacket_characterSlotObjectChange.");

    CharacterClass *character;
    if(characterSet == CHARACTER_PLAYER) {
        if(characterIndex >= (int)Player.size()) Player.resize(characterIndex+1);
        character = &Player[characterIndex];
    }
    else {
        if(characterIndex >= (int)NPC.size()) NPC.resize(characterIndex+1);
        character = &NPC[characterIndex];
    }
    character->objectOnSlot[slot].type = objectType;
}

/**
* @brief Method called after receiving #PACKET_DAY_TIME.
*/
void NetworkModule::processPacket_dayTime(const ENetEvent &event)
{
    int dayTime = 0;
    sscanf((char*)event.packet->data, "%*c %d", &dayTime);
    _assert(dayTime >= 0,"Day time is negative in processPacket_dayTime.");
    if(abs((int)Weather.dayTimeInMinutes-dayTime) > 2) Weather.dayTimeInMinutes = dayTime;
}

/**
* @brief Method called after receiving #PACKET_WEATHER.
*/
void NetworkModule::processPacket_weather(const ENetEvent &event)
{
    int rainType = RAIN_TYPE_NONE, snowType = SNOW_TYPE_NONE, stormType = STORM_TYPE_NONE, fogType = FOG_TYPE_NONE;
    sscanf((char*)event.packet->data, "%*c %d %d %d %d", &rainType, &snowType, &stormType, &fogType);

    _assert(rainType == RAIN_TYPE_NONE || rainType == RAIN_TYPE_SMALL ||
            rainType == RAIN_TYPE_MEDIUM || rainType == RAIN_TYPE_HEAVY,
            "Unknown rain type in processPacket_weather.");
    _assert(snowType == SNOW_TYPE_NONE || snowType == SNOW_TYPE_SMALL ||
            snowType == SNOW_TYPE_MEDIUM || snowType == SNOW_TYPE_HEAVY,
            "Unknown snow type in processPacket_weather.");
    _assert(stormType == STORM_TYPE_NONE || stormType == STORM_TYPE_SMALL ||
            stormType == STORM_TYPE_MEDIUM || stormType == STORM_TYPE_HEAVY,
            "Unknown storm type in processPacket_weather.");
    _assert(fogType == FOG_TYPE_NONE || fogType == FOG_TYPE_SMALL ||
            fogType == FOG_TYPE_MEDIUM || fogType == FOG_TYPE_HEAVY,
            "Unknown fog type in processPacket_weather.");

    if(stormType != STORM_TYPE_NONE && Weather.stormType == STORM_TYPE_NONE) Weather.timeout_lightning = globalTime+2000.0+rand()%10000;
    Weather.rainType = rainType;
    Weather.snowType = snowType;
    Weather.stormType = stormType;
    Weather.fogType = fogType;
}

/**
* @brief Method called after receiving #PACKET_CURRENT_DIALOGUE_BLOCK.
*/
void NetworkModule::processPacket_currentDialogueBlock(const ENetEvent &event)
{
    char ch;
    int NPCIndex = -1, NPCTextIndex = -1, optionsQuantity = 0;
    std::istringstream iss((char*)event.packet->data);
    iss >> ch >> NPCIndex >> NPCTextIndex >> optionsQuantity;

    _assert(NPCTextIndex < (int)Text.size(),"NPC text index out of bounds in processPacket_currentDialogueBlock.");

    currentDialogueBlock.NPCIndex = NPCIndex;
    currentDialogueBlock.NPCTextIndex = NPCTextIndex;
    currentDialogueBlock.optionTextIndex.clear();
    for(int i=0; i<optionsQuantity; ++i) {
        int optionTextIndex = -1;
        iss >> optionTextIndex;
        _assert(optionTextIndex < (int)Text.size(), "Option text index out of bounds in processPacket_currentDialogueBlock.");
        currentDialogueBlock.optionTextIndex.push_back(optionTextIndex);
    }
    if(NPCIndex >= 0) currentDialogueBlock.active = true;
    else currentDialogueBlock.active = false;
}

/**
* @brief Method called after receiving #PACKET_TRADE_WITH_NPC_OBJECTS_LIST.
*/
void NetworkModule::processPacket_tradeWithNPCObjectsList(const ENetEvent &event)
{
    char ch;
    int NPCIndex = -1, objectsQuantity = 0;
    std::istringstream iss((char*)event.packet->data);
    iss >> ch >> NPCIndex >> objectsQuantity;

    currentTradeWithNPC.NPCIndex = NPCIndex;
    currentTradeWithNPC.NPCObjectType.clear();
    for(int i=0; i<objectsQuantity; ++i) {
        int object = -1;
        iss >> object;
        if(object >= 0) {
            _assert(object < (int)ObjectType.size(), "Object type out of bounds in processPacket_tradeWithNPCObjectsList.");
            currentTradeWithNPC.NPCObjectType.push_back(object);
        }
    }
    if(NPCIndex >= 0) currentTradeWithNPC.active = true;
    else currentTradeWithNPC.active = false;

    for(std::list <WindowClass>::iterator it=Interface.window.begin(); it!=Interface.window.end(); ++it) {
        if(it->title == "Trade with NPC") {
            it->visible = currentTradeWithNPC.active;
            Interface.window.push_front(*it);
            Interface.window.erase(it);
            break;
        }
    }
}

/**
* @brief Method called after receiving #PACKET_QUEST_PROGRESS_CHANGE.
*/
void NetworkModule::processPacket_questProgressChange(const ENetEvent &event)
{
    int questIndex = -1, questProgress = -1;
    sscanf((char*)event.packet->data, "%*c %d %d", &questIndex, &questProgress);

    _assert(questIndex >= 0 && questIndex < (int)Quest.size(), "Quest index out of bounds in processPacket_questProgressChange.");
    _assert(questProgress >= 0 && questProgress <= 100, "Incorrect quest progress in processPacket_questProgressChange.");

    Quest[questIndex].progress = questProgress;
}
