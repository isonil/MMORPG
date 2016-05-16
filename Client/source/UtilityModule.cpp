#include "UtilityModule.hpp"

void UtilityModule::resetWorld()
{
    Player.clear();
    NPC.clear();
    for(size_t i=0; i<Tile.size(); ++i) {
        for(size_t j=0; j<Tile[i].size(); ++j) {
            Tile[i][j].object.clear();
        }
    }
    LightSource.clear();
    for(size_t i=0; i<Quest.size(); ++i) {
        Quest[i].progress = 0;
    }
    Projectile.clear();
    Particle.clear();
    Weather.dayTimeInMinutes = 0.0;
    Weather.rainType = RAIN_TYPE_MEDIUM;
    Weather.snowType = SNOW_TYPE_NONE;
    Weather.stormType = STORM_TYPE_MEDIUM;
    Weather.fogType = FOG_TYPE_NONE;
    Weather.timeout_lightning = globalTime+1000.0+rand()%3000;
    View.x = 1400.f;
    View.y = 920.f;
    View.distance = std::max(window.getSize().x, window.getSize().y)/1024.f*0.8f;
    shadowCaster.clear();
    objectOnMouse.objectType = -1;
    currentDialogueBlock.active = false;
    currentTradeWithNPC.active = false;
    viewOffsetX = 0.f;
    viewOffsetY = 0.f;
    automaticShooting = false;
}

void UtilityModule::saveSettings()
{
    std::ofstream out("settings.ini");
    if(out) {
        out << "[Settings]" << std::endl
            << "fullscreen = " << (int)GameSettings.fullscreen << std::endl
            << "screenWidth = " << GameSettings.screenWidth << std::endl
            << "screenHeight = " << GameSettings.screenHeight << std::endl
            << "sound = " << (int)GameSettings.sound << std::endl;
        out.close();
    }
    else {
        error("Could not create 'settings.ini'.");
    }
}

bool UtilityModule::isOutOfMap(int tile_x, int tile_y)
{
    if(tile_x < 0 || tile_y < 0 || tile_x >= (int)Tile.size()) return true;
    if(tile_y >= (int)Tile[tile_x].size()) return true;
    return false;
}

bool UtilityModule::isStackable(int objectType)
{
    _assert(objectType >= 0 && objectType < (int)ObjectType.size(), "Object type out of bounds in isStackable.");
    if(ObjectType[objectType].baseType == OBJECT_BASE_TYPE_AMMUNITION) return true;
    return false;
}

bool UtilityModule::isPassable(int tile_x, int tile_y)
{
    if(isOutOfMap(tile_x, tile_y)) return false;

    if(Tile[tile_x][tile_y].tileType >= 0) {
        _assert(Tile[tile_x][tile_y].tileType < (int)TileType.size(), "TileType out of bounds in isPassable.");
        if(!TileType[Tile[tile_x][tile_y].tileType].isPassable) return false;
    }
    else return false;

    if(Tile[tile_x][tile_y].sceneryType >= 0) {
        _assert(Tile[tile_x][tile_y].sceneryType < (int)SceneryType.size(), "SceneryType out of bounds in isPassable.");
        if(!SceneryType[Tile[tile_x][tile_y].sceneryType].isPassable) return false;
    }

    for(std::list <ObjectClass>::const_iterator it=Tile[tile_x][tile_y].object.begin(); it!=Tile[tile_x][tile_y].object.end(); ++it) {
        _assert(it->type < (int)ObjectType.size(), "ObjectType out of bounds in isPassable.");
        if(!ObjectType[it->type].isPassable) return false;
    }

    return true;
}

bool UtilityModule::isValidCharacterSet(char characterSet)
{
    if(characterSet == CHARACTER_PLAYER ||
       characterSet == CHARACTER_NPC) return true;
    else return false;
}

bool UtilityModule::canObjectBePlacedOnSlot(int objectType, int slotIndex)
{
    if(objectType < 0) return false;
    _assert(objectType < (int)ObjectType.size(),
            "Object type out of bounds in canObjectBePlacedOnSlot.");
    _assert(slotIndex >= 0 && slotIndex < CHARACTER_OBJECT_SLOTS_QUANTITY,
            "Object slot index out of bounds in canObjectBePlacedOnSlot.");
    if(ObjectType[objectType].baseType != objectSlot[slotIndex].baseType) return false;

    if(objectSlot[slotIndex].baseType == OBJECT_BASE_TYPE_EQUIPMENT) {
        if(ObjectType[objectType].equipmentType == objectSlot[slotIndex].equipmentType)
            return true;
        else return false;
    }
    return true;
}

bool UtilityModule::playerCollides()
{
    for(size_t i=0; i<Player.size(); ++i) {
        if((int)i == playerCharacterIndex) continue;
        if(!Player[i].isSeen) continue;
        if(getDistance((int)Player[i].x, (int)Player[i].y, (int)Player[playerCharacterIndex].x, (int)Player[playerCharacterIndex].y) <= 2*CHARACTER_RADIUS) {
            return true;
        }
    }
    for(size_t i=0; i<NPC.size(); ++i) {
        if(!NPC[i].isSeen) continue;
        if(getDistance((int)NPC[i].x, (int)NPC[i].y, (int)Player[playerCharacterIndex].x, (int)Player[playerCharacterIndex].y) <= 2*CHARACTER_RADIUS) {
            return true;
        }
    }
    for(int i=int(Player[playerCharacterIndex].x/TILE_SIZE-1); i<=Player[playerCharacterIndex].x/TILE_SIZE+1; ++i) {
        for(int j=int(Player[playerCharacterIndex].y/TILE_SIZE-1); j<=Player[playerCharacterIndex].y/TILE_SIZE+1; ++j) {
            if(!isPassable(i, j) &&
                (int)Player[playerCharacterIndex].x-CHARACTER_RADIUS < i*TILE_SIZE+TILE_SIZE &&
                (int)Player[playerCharacterIndex].x+CHARACTER_RADIUS > i*TILE_SIZE &&
                (int)Player[playerCharacterIndex].y-CHARACTER_RADIUS < j*TILE_SIZE+TILE_SIZE &&
                (int)Player[playerCharacterIndex].y+CHARACTER_RADIUS > j*TILE_SIZE) {
                    return true;
            }
        }
    }
    return false;
}

bool UtilityModule::playerMove(float dir)
{
    float delta = deltaTime;
    if(delta > MAX_DELTA) delta = MAX_DELTA;

    float step_x = delta*7.f;
    float step_y = delta*7.f;
    const float smallStep_x = 5.f;
    const float smallStep_y = 5.f;

    bool collided = false;
    while(step_x > 0.001f || step_y > 0.001f) {
        float currentStep_x, currentStep_y;
        if(step_x > smallStep_x) currentStep_x = smallStep_x;
        else currentStep_x = step_x;
        if(step_y > smallStep_y) currentStep_y = smallStep_y;
        else currentStep_y = step_y;

        Player[playerCharacterIndex].x += currentStep_x*cos(dir);
        if(playerCollides()) {
            Player[playerCharacterIndex].x -= currentStep_x*cos(dir);
            collided = true;
        }

        Player[playerCharacterIndex].y += currentStep_y*sin(dir);
        if(playerCollides()) {
            Player[playerCharacterIndex].y -= currentStep_y*sin(dir);
            collided = true;
        }

        step_x -= smallStep_x;
        step_y -= smallStep_y;
        if(step_x < 0.f) step_x = 0.f;
        if(step_y < 0.f) step_y = 0.f;
    }
    return !collided;
}

void UtilityModule::updateDelta()
{
    if(queryPerformance_isAvailable) {
        static long long previous_ms = 0;
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        long long current_ms = counter.QuadPart;
        long long frequency = queryPerformance_frequency.QuadPart;
        current_ms *= 1000LL;
        if(frequency) current_ms /= frequency;
        if(previous_ms != 0LL) deltaTime = (current_ms-previous_ms)/(1000.f/30.f);
        else deltaTime = 0.f;
        previous_ms = current_ms;
    }
    else deltaTime = ol::FpsCounter::GetDeltaTime();
}

void UtilityModule::assignParamsToObject(ObjectClass &Object, int objectType, int p1, int p2, int p3)
{
    _assert(objectType < (int)ObjectType.size(), "Object type out of bounds in assignParamsToObject.");

    Object.type = objectType;
    if(objectType >= 0) {
        if(ObjectType[objectType].baseType == OBJECT_BASE_TYPE_WEAPON) {
            _assert(p1 < (int)ObjectType.size(), "Weapon attachment 1 object type out of bounds in assignParamsToObject.");
            _assert(p2 < (int)ObjectType.size(), "Weapon attachment 2 object type out of bounds in assignParamsToObject.");
            _assert(p3 < (int)ObjectType.size(), "Weapon attachment 3 object type out of bounds in assignParamsToObject.");
            Object.param[OBJECT_PARAM_ADDON_1] = p1;
            Object.param[OBJECT_PARAM_ADDON_2] = p2;
            Object.param[OBJECT_PARAM_ADDON_3] = p3;
        }
        else if(ObjectType[objectType].baseType == OBJECT_BASE_TYPE_STRUCTURE) {
            Object.param[OBJECT_PARAM_OWNER] = p1;
            Object.param[OBJECT_PARAM_CONDITION] = p2;
        }
        else if(isStackable(objectType)) {
            Object.param[OBJECT_PARAM_QUANTITY] = p1;
        }
    }
}

void UtilityModule::addMessageToChat(std::vector <std::string> &chat, const std::string &message, int chatTab)
{
    sf::Text text;
    text.setCharacterSize(11);

    std::string buff;
    for(size_t i=0; i<message.size(); ++i) {
        text.setString(buff+message[i]);
        if(getTextWidth(text) > (int)Interface.chatWindowTexture.getSize().x-12) {
            if(buff.size()) {
                size_t rspace = buff.rfind(' ');
                if(rspace != std::string::npos) {
                    chat.push_back(buff.substr(0, rspace+1));
                    if(rspace+1 < buff.size())
                       buff = buff.substr(rspace+1);
                    else buff.clear();
                }
                else {
                    chat.push_back(buff);
                    buff.clear();
                }
            }
        }
        buff += message[i];
    }
    if(buff.size()) chat.push_back(buff);

    for(size_t i=0; i<Interface.chatTab.size(); ++i) {
        if(Interface.chatTab[i].chat == chatTab) {
            Interface.chatTab[i].newMessage = true;
            break;
        }
    }
}

void UtilityModule::addMessageToCurrentChat(const std::string &message)
{
    if(Interface.currentChat == CHAT_TAB_LOCAL) addMessageToChat(Interface.localChat, message, CHAT_TAB_LOCAL);
    else if(Interface.currentChat == CHAT_TAB_GLOBAL) addMessageToChat(Interface.globalChat, message, CHAT_TAB_GLOBAL);
    else if(Interface.currentChat >= 0) {
        _assert(Interface.currentChat < (int)Player.size(), "Private chat player index out of bounds in addMessageToCurrentChat.");
        addMessageToChat(Player[Interface.currentChat].privateChat, message, Interface.currentChat);
    }
}

void UtilityModule::playPositionalSound(const SAMPLE *sound, float receiver_x, float receiver_y, float source_x, float source_y)
{
    _assert(sound != NULL,"Sound is NULL in playPositionalSound.");

    float dist = getDistance(receiver_x, receiver_y, source_x, source_y);
    float volume = 255.f;
    float position = 127.f;
    if(dist > 300.f) {
        volume -= (dist-300.f)*0.23f;
        if(volume < 5.f) volume = 5.f;
    }
    if(fabs(source_x-receiver_x) > 300.f) {
        if(source_x > receiver_x) {
            position += (source_x-receiver_x-300.f)*0.11f;
        }
        else {
            position -= (receiver_x-source_x-300.f)*0.11f;
        }
        if(position > 240.f) position = 240.f;
        if(position < 15.f) position = 15.f;
    }
    play_sample(sound, (int)volume, (int)position, 1000, 0);
}

void UtilityModule::adjustSoundVolumeSmoothly(audiere::OutputStreamPtr &sound, float volumeTarget)
{
    float newVolume = 0.f;
    if(fabs(sound->getVolume()-volumeTarget) < deltaTime/60.f) newVolume = volumeTarget;
    else if(sound->getVolume() > volumeTarget) newVolume = sound->getVolume()-deltaTime/60.f;
    else newVolume = sound->getVolume()+deltaTime/60.f;
    sound->setVolume(newVolume);
    if(sound->getVolume() > 0.01f) {
        if(!sound->isPlaying()) {
            sound->play();
        }
    }
    else if(sound->isPlaying()) {
        sound->stop();
        sound->reset();
    }
}

void UtilityModule::onCloseWindowCallback(const WindowClass &window)
{
    if(window.title == "Trade with NPC") {
        char packet[MAX_PACKET_SIZE_END_CURRENT_NPC_INTERACTION];
        getEndCurrentNPCInteractionPacket(packet);
        sendPacket(0, packet);
    }
}

float UtilityModule::getDistance(float x1, float y1, float x2, float y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

float UtilityModule::getDistance(const CharacterClass &ch1, const CharacterClass &ch2)
{
    return getDistance(ch1.x, ch1.y, ch2.x, ch2.y);
}

vPoint UtilityModule::getScreenPosition(float posX, float posY, const ViewClass &View)
{
    return vPoint(
        posX*View.distance-(View.x-(float)window.getSize().x/2.f)+(1-View.distance)*View.x,
        posY*View.distance-(View.y-(float)window.getSize().y/2.f)+(1-View.distance)*View.y
    );
}

vPoint UtilityModule::getWorldPosition(float posX, float posY, const ViewClass &View)
{
    return vPoint(
        (posX+View.x-(float)window.getSize().x/2.f-(1-View.distance)*View.x)/View.distance,
        (posY+View.y-(float)window.getSize().y/2.f-(1-View.distance)*View.y)/View.distance
    );
}

void UtilityModule::sendPacket(int channel, const char *packet_str)
{
    _assert(packet_str != NULL, "Packet is NULL in sendPacket.");
    ENetPacket *packet = enet_packet_create(packet_str, strlen(packet_str)+1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, channel, packet);
    enet_host_flush(client);
}

void UtilityModule::sendChangeObjectPlaceRequest(int destinationPlace, int p1, int p2, int p3)
{
    _assert(destinationPlace != OBJECT_PLACE_NONE, "Object destination place is OBJECT_PLACE_NONE in sendChangeObjectPlaceRequest.");
    _assert(objectOnMouse.place != OBJECT_PLACE_NONE, "Object place is OBJECT_PLACE_NONE in sendChangeObjectPlaceRequest.");
    _assert(objectOnMouse.objectType >= 0, "On mouse object type is negative in sendChangeObjectPlaceRequest.");

    int objectPlace_p1 = -1, objectPlace_p2 = -1, objectPlace_p3 = -1;
    if(objectOnMouse.place == OBJECT_PLACE_GROUND) {
        objectPlace_p1 = objectOnMouse.placeX;
        objectPlace_p2 = objectOnMouse.placeY;
    }
    else if(objectOnMouse.place == OBJECT_PLACE_INVENTORY) {
        objectPlace_p1 = objectOnMouse.placeX;
        objectPlace_p2 = objectOnMouse.placeY;
    }
    else if(objectOnMouse.place == OBJECT_PLACE_SLOT) {
        objectPlace_p1 = objectOnMouse.placeSlot;
    }
    else if(objectOnMouse.place == OBJECT_PLACE_CONTAINER) {
        //to do
    }
    else if(objectOnMouse.place == OBJECT_PLACE_INVENTORY_WEAPON_ATTACHMENT) {
        objectPlace_p1 = objectOnMouse.placeX;
        objectPlace_p2 = objectOnMouse.placeY;
        objectPlace_p3 = objectOnMouse.placeSlot2;
    }
    else if(objectOnMouse.place == OBJECT_PLACE_SLOT_WEAPON_ATTACHMENT) {
        objectPlace_p1 = objectOnMouse.placeSlot;
        objectPlace_p2 = objectOnMouse.placeSlot2;
    }

    if(objectOnMouse.place == destinationPlace && objectPlace_p1 == p1 && objectPlace_p2 == p2 && objectPlace_p3 == p3) return;
    char packet[MAX_PACKET_SIZE_CHANGE_OBJECT_PLACE_REQUEST];
    getChangeObjectPlaceRequestPacket(packet, objectOnMouse.place, objectPlace_p1, objectPlace_p2, objectPlace_p3, destinationPlace, p1, p2, p3);
    sendPacket(0, packet);
}

void UtilityModule::getChooseTalkOptionPacket(char *packet, int num)
{
    sprintf(packet, "%c %d", PACKET_CHOOSE_TALK_OPTION, num);
}

void UtilityModule::getChangeObjectPlaceRequestPacket(char *packet, int place, int p1, int p2, int p3, int destPlace, int dp1, int dp2, int dp3)
{
    sprintf(packet, "%c %d %d %d %d %d %d %d %d", PACKET_CHANGE_OBJECT_PLACE_REQUEST, place, p1, p2, p3, destPlace, dp1, dp2, dp3);
}

void UtilityModule::getEndCurrentNPCInteractionPacket(char *packet)
{
    sprintf(packet, "%c", PACKET_END_CURRENT_NPC_INTERACTION);
}
