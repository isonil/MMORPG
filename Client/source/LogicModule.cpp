#include "LogicModule.hpp"

/**
* @brief Logic related to windows.
*/
void LogicModule::logicInterface_windows(bool &mouseOverAnyWindow)
{
    for(std::list <WindowClass>::iterator it=Interface.window.begin(); it!=Interface.window.end(); ++it) {
        if(!it->visible) {
            it->dragging = false;
            continue;
        }
        if(it->dragging) {
            it->x = mx-it->draggingOffsetX;
            it->y = my-it->draggingOffsetY;
            if(it->x < -it->w+20) it->x = -it->w+20;
            if(it->x > (int)window.getSize().x-20) it->x = (int)window.getSize().x-20;
            if(it->y < 0) it->y = 0;
            if(it->y > (int)window.getSize().y-20) it->y = (int)window.getSize().y-20;
        }
        bool mouseOverWindow = false;
        if(mx >= it->x && mx <= it->x+it->w && my >= it->y && my <= it->y+it->h) {
            if(!mouseOverAnyWindow) mouseOverWindow = true;
            mouseOverAnyWindow = true;
        }
        if(mb == 1 && !LMBEventHandled && mouseOverWindow) {
            LMBEventHandled = true;
            if(my <= it->y+15.f && mx < it->x+it->w-12.f) {
                it->dragging = true;
                it->draggingOffsetX = mx-it->x;
                it->draggingOffsetY = my-it->y;
            }
            if(mx >= it->x+it->w-12.f && mx <= it->x+it->w && my >= it->y && my <= it->y+12.f) {
                it->closeButtonBeingPressed = true;
            }
            if(it->LogicCallback != NULL) (this->*(it->LogicCallback))(Interface, *it, LMB_NEW_PRESSED);
            Interface.window.push_front(*it);
            Interface.window.erase(it);
            break;
        }
        else if(mb == 1 && mouseOverWindow) {
            if(it->LogicCallback != NULL) (this->*(it->LogicCallback))(Interface, *it, LMB_PRESSED);
        }
        else if(mb == 1) {
            if(it->LogicCallback != NULL) (this->*(it->LogicCallback))(Interface, *it, LMB_PRESSED_OUTSIDE);
        }
        else if(mouseOverWindow) {
            if(it->closeButtonBeingPressed && mx >= it->x+it->w-12.f && mx <= it->x+it->w && my >= it->y && my <= it->y+12.f) {
                it->closeButtonBeingPressed = false;
                it->visible = false;
                onCloseWindowCallback(*it);
            }
            else if(it->LogicCallback != NULL) (this->*(it->LogicCallback))(Interface, *it, LMB_FREE);
        }
        else {
            if(it->LogicCallback != NULL) (this->*(it->LogicCallback))(Interface, *it, LMB_FREE_OUTSIDE);
        }

        if(mb == 0) {
            it->dragging = false;
            it->closeButtonBeingPressed = false;
        }
    }
}

/**
* @brief Logic related to chat.
*/
void LogicModule::logicInterface_chat(bool mouseOverAnyWindow)
{
    if((!mouseOverAnyWindow && mx >= Interface.chatX && mx <= Interface.chatX+(int)Interface.chatWindowTexture.getSize().x &&
        my >= Interface.chatY && my <= Interface.chatY+(int)Interface.chatWindowTexture.getSize().y+(int)Interface.chatEditBoxTexture.getSize().y)
        ||  Interface.GUIControl.editBox["chatEditBox"].isFocused) {
        Interface.chatAlpha += deltaTime*15.f;
    }
    else {
        Interface.chatAlpha -= deltaTime*15.f;
    }
    if(Interface.chatAlpha < 170.f) Interface.chatAlpha = 170.f;
    if(Interface.chatAlpha > 255.f) Interface.chatAlpha = 255.f;
}

/**
* @brief Logic related to dropping object (currently holding on mouse) on ground.
*/
void LogicModule::logicInterface_onMouseObjectDrop(bool mouseOverAnyWindow)
{
    if(objectOnMouse.objectType >= 0 && mb != 1) {
        if(mouseOverAnyWindow) objectOnMouse.objectType = -1;
        else {
            vPoint pos = getWorldPosition(mx, my, View);
            int tile_x = int(pos.x/TILE_SIZE);
            int tile_y = int(pos.y/TILE_SIZE);
            if(!isOutOfMap(tile_x, tile_y)) {
                if(abs((int)Player[playerCharacterIndex].x/TILE_SIZE-tile_x) <= 1 &&
                   abs((int)Player[playerCharacterIndex].y/TILE_SIZE-tile_y) <= 1) {
                    if(isPassable(tile_x, tile_y)) {
                        if(Tile[tile_x][tile_y].object.size() < OBJECTS_PER_TILE_LIMIT) {
                            sendChangeObjectPlaceRequest(OBJECT_PLACE_GROUND, int(pos.x/TILE_SIZE), int(pos.y/TILE_SIZE), -1);
                        }
                        else {
                            Interface.statusLogMessage.push_back(StatusLogMessageClass("No free space on this tile."));
                        }
                    }
                    else {
                        Interface.statusLogMessage.push_back(StatusLogMessageClass("No free space on this tile."));
                    }
                }
                else {
                    Interface.statusLogMessage.push_back(StatusLogMessageClass("Too far to throw an object."));
                }
            }
            objectOnMouse.objectType = -1;
        }
    }
}

/**
* @brief Logic related to dialogue.
*/
void LogicModule::logicInterface_dialogue(bool mouseOverAnyWindow)
{
    if(!mouseOverAnyWindow && mb == 1 && !LMBEventHandled && currentDialogueBlock.active && my >= (int)window.getSize().y-100) {
        LMBEventHandled = true;
        int num = 0;
        for(size_t i=0; i<currentDialogueBlock.optionTextIndex.size(); ++i) {
            if(currentDialogueBlock.optionTextIndex[i] >= 0) {
                if(mx >= (int)Interface.chatWindowTexture.getSize().x+30 &&
                   my >= (int)window.getSize().y-60+(num-1)*10 &&
                   my < (int)window.getSize().y-60+num*10) {
                    char packet[MAX_PACKET_SIZE_CHOOSE_TALK_OPTION];
                    getChooseTalkOptionPacket(packet, i);
                    sendPacket(0, packet);
                    break;
                }
                ++num;
            }
        }
    }
}

/**
* @brief Logic related to picking up object from ground.
*/
void LogicModule::logicInterface_pickUpObject(bool mouseOverAnyWindow)
{
    if(!mouseOverAnyWindow && mb == 2 && !RMBEventHandled) {
        RMBEventHandled = true;
        vPoint pos = getWorldPosition(mx, my, View);
        int tileX = int(pos.x/TILE_SIZE);
        int tileY = int(pos.y/TILE_SIZE);
        if(!isOutOfMap(tileX, tileY)) {
            if(!Tile[tileX][tileY].object.empty()) {
                if(abs((int)Player[playerCharacterIndex].x/TILE_SIZE-tileX) <= 1 &&
                   abs((int)Player[playerCharacterIndex].y/TILE_SIZE-tileY) <= 1) {
                    int invX = -1, invY = -1;
                    for(int i=0; i<CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT; ++i) {
                        for(int j=0; j<CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH; ++j) {
                            if(Player[playerCharacterIndex].objectInInventory[j][i].type < 0) {
                                invX = j, invY = i;
                                break;
                            }
                        }
                        if(invX >= 0 && invY >= 0) break;
                    }
                    if(invX >= 0 && invY >= 0) {
                        objectOnMouse.objectType = Tile[tileX][tileY].object.back().type;
                        objectOnMouse.place = OBJECT_PLACE_GROUND;
                        objectOnMouse.placeX = tileX;
                        objectOnMouse.placeY = tileY;
                        sendChangeObjectPlaceRequest(OBJECT_PLACE_INVENTORY, invX, invY, -1);
                        objectOnMouse.objectType = -1;
                    }
                    else {
                        Interface.statusLogMessage.push_back(StatusLogMessageClass("No free space in inventory."));
                    }
                }
                else {
                    Interface.statusLogMessage.push_back(StatusLogMessageClass("Too far to reach."));
                }
            }
        }
    }
}

/**
* @brief Logic related to opening object description window.
*/
void LogicModule::logicInterface_objectDescription(bool mouseOverAnyWindow)
{
    if(mouseOverAnyWindow && mb == 2 && !RMBEventHandled) {
        RMBEventHandled = true;
        if(Interface.inventoryMouseOverSlot >= 0 && Interface.inventoryMouseOverSlot < CHARACTER_OBJECT_SLOTS_QUANTITY) {
            if(Player[playerCharacterIndex].objectOnSlot[Interface.inventoryMouseOverSlot].type >= 0) {
                Interface.objectDescriptionSlot = Interface.inventoryMouseOverSlot;
                Interface.objectDescriptionInvX = -1;
                Interface.objectDescriptionInvY = -1;
                for(std::list <WindowClass>::iterator it=Interface.window.begin(); it!=Interface.window.end(); ++it) {
                    if(it->title == "Object Description") {
                        it->visible = true;
                        Interface.window.push_front(*it);
                        Interface.window.erase(it);
                        return;
                    }
                }
            }
        }
        else if(Interface.inventoryMouseOverInvX >= 0 && Interface.inventoryMouseOverInvX < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
                Interface.inventoryMouseOverInvY >= 0 && Interface.inventoryMouseOverInvY < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT) {
            if(Player[playerCharacterIndex].objectInInventory[Interface.inventoryMouseOverInvX][Interface.inventoryMouseOverInvY].type >= 0) {
                Interface.objectDescriptionSlot = -1;
                Interface.objectDescriptionInvX = Interface.inventoryMouseOverInvX;
                Interface.objectDescriptionInvY = Interface.inventoryMouseOverInvY;
                for(std::list <WindowClass>::iterator it=Interface.window.begin(); it!=Interface.window.end(); ++it) {
                    if(it->title == "Object Description") {
                        it->visible = true;
                        Interface.window.push_front(*it);
                        Interface.window.erase(it);
                        return;
                    }
                }
            }
        }
    }
}

/**
* @brief Logic related to changing chat tab.
*/
void LogicModule::logicInterface_changeChatTab()
{
    if(mb == 1 && !LMBEventHandled &&
       mx >= Interface.chatX && mx <= Interface.chatX+(int)Interface.chatWindowTexture.getSize().x &&
       my >= Interface.chatY && my <= Interface.chatY+((int)Interface.chatTabTexture.getSize().y-3)+(int)Interface.chatWindowTexture.getSize().y+(int)Interface.chatEditBoxTexture.getSize().y) {
        if(mx >= Interface.chatX+3 &&
           mx <= Interface.chatX+3+(int)Interface.chatTab.size()*(int)Interface.chatTabTexture.getSize().x &&
           my <= Interface.chatY+(int)Interface.chatTabTexture.getSize().y) {
            int tabIndex = (mx-Interface.chatX-3)/Interface.chatTabTexture.getSize().x;
            if(tabIndex >= 0 && tabIndex < (int)Interface.chatTab.size())
                Interface.currentChat = Interface.chatTab[tabIndex].chat;
        }
        LMBEventHandled = true;
    }

    for(size_t i=0; i<Interface.chatTab.size(); ++i) {
        if(Interface.chatTab[i].chat == Interface.currentChat)
            Interface.chatTab[i].newMessage = false;
    }
}

/**
* @brief Logic related to managing keyboard input.
*/
void LogicModule::logicInterface_keyboard()
{
    EditBoxClass &chatEditBox = Interface.GUIControl.editBox["chatEditBox"];

    if(!keyBuffHandled) {
        //We don't set keyBuffHandled to true in order to let
        //logicPlayerInput() handle real-time keyboard events.
        //There are no further places which handle event based
        //keyboard keys, so there is no need to set keyBuffHandled
        //to true.
        for(size_t i=0; i<keyBuff.size(); ++i) {
            if(keyBuff[i].code == sf::Keyboard::Return) {
                if(chatEditBox.isFocused) {
                    if(chatEditBox.text.size()) {
                        //In this particular case we need to set
                        //keyBuffHandled to true to avoid situation
                        //where user holds for example A key and presses
                        //enter key to send message. In this way he
                        //would move left for 1 frame.
                        keyBuffHandled = true;
                        bool isPrivateChatRequest = false;

                        if(chatEditBox.text.size() >= 4) {
                            if(chatEditBox.text[0] == '/' && chatEditBox.text[1] == 'p') {
                                std::string name = chatEditBox.text.substr(3);
                                if(name.size() <= LOGIN_LENGTH_LIMIT) {
                                    char packet[MAX_PACKET_SIZE_PRIVATE_CHAT_REQUEST];
                                    sprintf(packet, "%c %s", PACKET_PRIVATE_CHAT_REQUEST, name.c_str());
                                    sendPacket(0, packet);
                                }
                                isPrivateChatRequest = true;
                            }
                        }
                        if(!isPrivateChatRequest) {
                            if(Interface.currentChat == CHAT_TAB_LOCAL) {
                                char packet[MAX_PACKET_SIZE_LOCAL_CHAT_MESSAGE];
                                sprintf(packet, "%c %s", PACKET_LOCAL_CHAT_MESSAGE, chatEditBox.text.c_str());
                                sendPacket(0, packet);
                            }
                            else if(Interface.currentChat == CHAT_TAB_GLOBAL) {
                                char packet[MAX_PACKET_SIZE_GLOBAL_CHAT_MESSAGE];
                                sprintf(packet, "%c %s", PACKET_GLOBAL_CHAT_MESSAGE, chatEditBox.text.c_str());
                                sendPacket(0, packet);
                            }
                            else if(Interface.currentChat >= 0) {
                                char packet[MAX_PACKET_SIZE_PRIVATE_CHAT_MESSAGE];
                                sprintf(packet, "%c %d %s", PACKET_PRIVATE_CHAT_MESSAGE, Interface.currentChat, chatEditBox.text.c_str());
                                sendPacket(0, packet);
                            }
                        }
                        chatEditBox.reset();
                        chatEditBox.setFocused();
                    }
                    else chatEditBox.isFocused = false;
                }
                else chatEditBox.isFocused = true;
            }
            else if(keyBuff[i].code == sf::Keyboard::Escape) {
                if(chatEditBox.isFocused) {
                    chatEditBox.isFocused = false;
                    chatEditBox.selectingFrom = -1;
                }
                else {
                    bool closed = false;
                    for(std::list <WindowClass>::iterator it=Interface.window.begin(); it!=Interface.window.end(); ++it) {
                        if(it->visible) {
                            it->visible = false;
                            onCloseWindowCallback(*it);
                            closed = true;
                            break;
                        }
                    }
                    if(!closed) {
                        /*
                        else if(menu opened) {
                            close menu
                        }
                        else {
                            open menu
                        }
                        */
                    }
                }
            }
            else if(keyBuff[i].code == sf::Keyboard::I) {
                for(std::list <WindowClass>::iterator it=Interface.window.begin(); it!=Interface.window.end(); ++it) {
                    if(it->title == "Character Inventory") {
                        it->visible = !it->visible;
                        if(it->visible) {
                            Interface.window.push_front(*it);
                            Interface.window.erase(it);
                        }
                        else {
                            Interface.inventoryMouseOverSlot = -1;
                            Interface.inventoryMouseOverInvX = -1;
                            Interface.inventoryMouseOverInvY = -1;
                            Interface.mouseOverWeaponAttachmentSlot = -1;
                            Interface.mouseOverTradeWithNPCObjectIndex = -1;
                        }
                        break;
                    }
                }
            }
            else if(keyBuff[i].code == sf::Keyboard::Q) {
                if(globalTime >= timeout_grenadeThrow) {
                    vPoint pos = getWorldPosition(mx, my, View);
                    char packet[60];
                    sprintf(packet, "%c %d %d", PACKET_GRENADE_THROW, (int)pos.x, (int)pos.y);
                    sendPacket(0, packet);
                    timeout_grenadeThrow = globalTime+3000;
                }
            }
            else if(keyBuff[i].code == sf::Keyboard::E) {
                ObjectClass *weapon = &Player[playerCharacterIndex].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX];
                if(weapon->type >= 0) {
                    _assert(weapon->type < (int)ObjectType.size(), "Weapon object type out of bounds in logicPlayerInput.");
                    if(weapon->param[OBJECT_PARAM_ADDON_3] == OBJECT_ID_GRENADE_LAUNCHER) {
                        if(globalTime >= timeout_grenadeLauncherShot) {
                            vPoint pos = getWorldPosition(mx, my, View);
                            char packet[60];
                            sprintf(packet, "%c %d %d", PACKET_GRENADE_LAUNCHER_SHOT, (int)pos.x, (int)pos.y);
                            sendPacket(0, packet);
                            timeout_grenadeLauncherShot = globalTime+3000;
                        }
                    }
                }
            }
            else if(keyBuff[i].code == sf::Keyboard::T) {
                vPoint pos = getWorldPosition(mx, my, View);
                for(size_t j=0; j<NPC.size(); ++j) {
                    if(NPC[j].isSeen && getDistance(pos.x, pos.y, NPC[j].x, NPC[j].y) <= CHARACTER_RADIUS) {
                        if(getDistance(Player[playerCharacterIndex], NPC[j]) <= NPC_INTERACTION_MAX_DISTANCE) {
                            char packet[50];
                            sprintf(packet, "%c %d", PACKET_START_TALK_WITH_NPC, j);
                            sendPacket(0, packet);
                        }
                        else {
                            Interface.statusLogMessage.push_back(StatusLogMessageClass("Too far to talk with NPC."));
                        }
                        break;
                    }
                }
            }
        }
    }
}

/**
* @brief Logic related to status log messages.
*/
void LogicModule::logicInterface_statusLogMessages()
{
    for(std::list <StatusLogMessageClass>::iterator it=Interface.statusLogMessage.begin(); it!=Interface.statusLogMessage.end();) {
        if(it->fadesAway) {
            it->alpha -= deltaTime*4.f;
            if(it->alpha <= 0.f) {
                it = Interface.statusLogMessage.erase(it);
                continue;
            }
        }
        else {
            it->alpha += deltaTime*20.f;
            if(it->alpha > 255.f) it->alpha = 255.f;
        }
        if(globalTime >= it->timeout_startFadingAway) {
            it->fadesAway = true;
        }
        ++it;
    }

    float destinationY = window.getSize().y-(float)Interface.statusLogMessage.size()*10.f-10.f;
    for(std::list <StatusLogMessageClass>::iterator it=Interface.statusLogMessage.begin(); it!=Interface.statusLogMessage.end(); ++it) {
        if(it->offsetX > 0.f) {
            it->offsetX -= deltaTime*4.f;
            if(it->offsetX < 0.f) it->offsetX = 0.f;
        }
        if(fabs(it->y-destinationY) < deltaTime*4.f) it->y = destinationY;
        else if(it->y>destinationY) it->y -= deltaTime*4.f;
        else it->y += deltaTime*4.f;
        destinationY += 10.f;
    }
}

/**
* @brief Logic related to menu interface.
*/
void LogicModule::logicMenuInterface()
{
    if(mb != 1) LMBEventHandled = false;
    if(mb != 2) RMBEventHandled = false;

    if(inGameError.empty()) {
        Interface.menuGUIControl.logic(false);
    }
    else {
        Interface.menuErrorGUIControl.logic(false);
    }

    EditBoxClass &logInLoginEditBox = Interface.menuGUIControl.editBox["logInLoginEditBox"];
    EditBoxClass &logInPasswordEditBox = Interface.menuGUIControl.editBox["logInPasswordEditBox"];

    ButtonClass &logInButton = Interface.menuGUIControl.button["logInButton"];
    if(logInButton.wasPressed) {
        logInButton.wasPressed = false;

        if(logInLoginEditBox.text.size() &&
           logInPasswordEditBox.text.size() &&
           logInLoginEditBox.text.size() <= LOGIN_LENGTH_LIMIT &&
           logInPasswordEditBox.text.size() <= PASSWORD_LENGTH_LIMIT) {
            sprintf(login, "%s", logInLoginEditBox.text.c_str());
            sprintf(password, "%s", logInPasswordEditBox.text.c_str());
        }
    }

    ButtonClass &settingsButton = Interface.menuGUIControl.button["settingsButton"];
    if(settingsButton.wasPressed) {
        settingsButton.wasPressed = false;
    }

    ButtonClass &quitButton = Interface.menuGUIControl.button["quitButton"];
    if(quitButton.wasPressed) {
        quitButton.wasPressed = false;
        quit = true;
    }

    ButtonClass &OKButton = Interface.menuErrorGUIControl.button["OKButton"];
    if(OKButton.wasPressed) {
        OKButton.wasPressed = false;
        inGameError.clear();
    }

    if(!keyBuffHandled) {
        keyBuffHandled = true;
        for(size_t i=0; i<keyBuff.size(); ++i) {
            if(keyBuff[i].code == sf::Keyboard::Return) {
                if(!inGameError.empty()) {
                    inGameError.clear();
                }
                else {
                    if(logInLoginEditBox.text.size() &&
                       logInPasswordEditBox.text.size() &&
                       logInLoginEditBox.text.size() <= LOGIN_LENGTH_LIMIT &&
                       logInPasswordEditBox.text.size() <= PASSWORD_LENGTH_LIMIT) {
                        sprintf(login, "%s", logInLoginEditBox.text.c_str());
                        sprintf(password, "%s", logInPasswordEditBox.text.c_str());
                    }
                }
            }
            else if(keyBuff[i].code == sf::Keyboard::Escape) {
                inGameError.clear();
            }
            else if(keyBuff[i].code == sf::Keyboard::Tab &&
                    inGameError.empty()) {
                if(logInLoginEditBox.isFocused) {
                    logInLoginEditBox.isFocused = false;
                    logInPasswordEditBox.setFocused();
                }
                else if(logInPasswordEditBox.isFocused) {
                    logInLoginEditBox.setFocused();
                    logInPasswordEditBox.isFocused = false;
                }
            }
        }
    }
}

/**
* @brief Logic related to interface.
*/
void LogicModule::logicInterface()
{
    Interface.inventoryMouseOverSlot = -1;
    Interface.inventoryMouseOverInvX = -1;
    Interface.inventoryMouseOverInvY = -1;
    Interface.mouseOverWeaponAttachmentSlot = -1;
    Interface.mouseOverTradeWithNPCObjectIndex = -1;

    if(mb != 1) LMBEventHandled = false;
    if(mb != 2) RMBEventHandled = false;

    bool mouseOverAnyWindow = false;

    logicInterface_windows(mouseOverAnyWindow);
    logicInterface_chat(mouseOverAnyWindow);
    logicInterface_onMouseObjectDrop(mouseOverAnyWindow);
    logicInterface_dialogue(mouseOverAnyWindow);
    logicInterface_pickUpObject(mouseOverAnyWindow);
    logicInterface_objectDescription(mouseOverAnyWindow);

    Interface.GUIControl.logic(mouseOverAnyWindow);

    logicInterface_changeChatTab();
    logicInterface_keyboard();
    logicInterface_statusLogMessages();
}

/**
* @brief Logic related to characters.
*/
void LogicModule::logicCharacters()
{
    for(size_t i=0; i<Player.size(); ++i) {
        for(std::list <MessageOverHeadClass>::iterator it=Player[i].messageOverHead.begin(); it!=Player[i].messageOverHead.end();) {
            if(it->fadesAway) {
                it->alpha -= deltaTime*5.f;
                if(it->alpha <= 0.f) {
                    it = Player[i].messageOverHead.erase(it);
                    continue;
                }
            }
            else {
                it->alpha += deltaTime*25.f;
                if(it->alpha > 255.f) it->alpha = 255.f;
            }
            if(globalTime >= it->timeout_startFadingAway) {
                it->fadesAway = true;
            }
            ++it;
        }

        if(!Player[i].isSeen) continue;
        if((int)i == playerCharacterIndex) continue;

        float tmp = Player[i].dir-Player[i].toDir;
        if(tmp < -M_PI) tmp += 2*M_PI;
        if(tmp > M_PI) tmp -= 2*M_PI;
        if(fabs(tmp) <= deltaTime/2.f) Player[i].dir = Player[i].toDir;
        else if(tmp < 0) {
            Player[i].dir += deltaTime/2.f;
            if(Player[i].dir > M_PI) Player[i].dir = -2*M_PI+Player[i].dir;
        }
        else {
            Player[i].dir -= deltaTime/2.f;
            if(Player[i].dir < -M_PI) Player[i].dir = 2*M_PI+Player[i].dir;
        }

        if(!floatCompare(Player[i].x, Player[i].toX, 0.01f) || !floatCompare(Player[i].y, Player[i].toY, 0.01f)) {
            float dir = atan2(Player[i].toY-Player[i].y, Player[i].toX-Player[i].x);
            float dir_cos = cos(dir);
            float dir_sin = sin(dir);
            if(fabs(Player[i].x-Player[i].toX) <= deltaTime*Player[i].speed*dir_cos)
                Player[i].x = Player[i].toX;
            else {
                Player[i].x += deltaTime*Player[i].speed*dir_cos;
            }
            if(fabs(Player[i].y-Player[i].toY) <= deltaTime*Player[i].speed*dir_sin)
                Player[i].y = Player[i].toY;
            else {
                Player[i].y += deltaTime*Player[i].speed*dir_sin;
            }
        }
    }

    for(size_t i=0; i<NPC.size(); ++i) {
        if(!NPC[i].isSeen) continue;

        float tmp = NPC[i].dir-NPC[i].toDir;
        if(tmp < -M_PI) tmp += 2*M_PI;
        if(tmp > M_PI) tmp -= 2*M_PI;
        if(fabs(tmp) <= deltaTime/2.f) NPC[i].dir = NPC[i].toDir;
        else if(tmp < 0) {
            NPC[i].dir += deltaTime/2.f;
            if(NPC[i].dir > M_PI) NPC[i].dir = -2*M_PI+NPC[i].dir;
        }
        else {
            NPC[i].dir -= deltaTime/2.f;
            if(NPC[i].dir < -M_PI) NPC[i].dir = 2*M_PI+NPC[i].dir;
        }

        if(!floatCompare(NPC[i].x, NPC[i].toX, 0.01f) || !floatCompare(NPC[i].y, NPC[i].toY, 0.01f)) {
            float dir = atan2(NPC[i].toY-NPC[i].y, NPC[i].toX-NPC[i].x);
            float dir_cos = cos(dir);
            float dir_sin = sin(dir);
            if(fabs(NPC[i].x-NPC[i].toX) <= deltaTime*NPC[i].speed*dir_cos)
                NPC[i].x = NPC[i].toX;
            else {
                NPC[i].x += deltaTime*NPC[i].speed*dir_cos;
            }
            if(fabs(NPC[i].y-NPC[i].toY) <= deltaTime*NPC[i].speed*dir_sin)
                NPC[i].y = NPC[i].toY;
            else {
                NPC[i].y += deltaTime*NPC[i].speed*dir_sin;
            }
        }
    }
}

/**
* @brief Logic related to input which affects in-game player.
*/
void LogicModule::logicPlayerInput()
{
    if(!keyBuffHandled) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) playerMove(-M_PI/2.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) playerMove(M_PI/2.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) playerMove(-M_PI);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) playerMove(0.f);
    }
    Player[playerCharacterIndex].dir = atan2(my-(float)window.getSize().y/2.f, mx-(float)window.getSize().x/2.f);
    if(mb == 1 && (!LMBEventHandled || automaticShooting)) {
        LMBEventHandled = true;
        automaticShooting = false;

        ObjectClass *weapon = &Player[playerCharacterIndex].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX];
        if(weapon->type >= 0) {
            _assert(weapon->type < (int)ObjectType.size(), "Weapon object type out of bounds in logicPlayerInput.");
            if(ObjectType[weapon->type].isAutomatic)
                automaticShooting = true;
            if(globalTime >= weapon->timeout_shot) {
                char packet[30];
                sprintf(packet, "%c %d", PACKET_SHOT, int(Player[playerCharacterIndex].dir*100.f));
                sendPacket(0, packet);
                weapon->timeout_shot = globalTime + ObjectType[weapon->type].baseShotDelay;
            }
        }
    }
    if(mb == 0) automaticShooting = false;
}

/**
* @brief Logic related to sending player's position.
*/
void LogicModule::logicSendPosition()
{
    if(globalTime >= timeout_sendPosition) {
        char packet[100];
        sprintf(packet, "%c %d %d %d",
                PACKET_CHARACTER_POSITION,
                (int)Player[playerCharacterIndex].x,
                (int)Player[playerCharacterIndex].y,
                int(Player[playerCharacterIndex].dir*100.f));
        sendPacket(0, packet);
        timeout_sendPosition = globalTime+100.0;
    }
}

/**
* @brief Logic related to projectiles.
*/
void LogicModule::logicProjectiles()
{
    for(std::list <ProjectileClass>::iterator it=Projectile.begin(); it!=Projectile.end();) {
        std::list <ProjectileClass>::iterator projectile = it;
        ++it;

        float move_x = 0.f;
        float move_y = 0.f;
        if(projectile->projectileType == PROJECTILE_TYPE_MISSILE) {
            float boost = projectile->distanceTraveled/20.f+15.f;
            move_x = cos(projectile->dir)*deltaTime*boost;
            move_y = sin(projectile->dir)*deltaTime*boost;
        }
        else if(projectile->projectileType == PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE) {
            move_x = cos(projectile->dir)*deltaTime*30.f;
            move_y = sin(projectile->dir)*deltaTime*30.f;
        }
        else if(projectile->projectileType == PROJECTILE_TYPE_GRENADE) {
            if(projectile->distanceTraveled >= projectile->grenadeThrowDistance &&
               projectile->grenadeFlySpeed > 0.01f) {
                if(projectile->distanceTraveled < projectile->grenadeThrowDistance+40.f) {
                    projectile->grenadeFlySpeed = 8.f;
                    if(projectile->grenadeBouncedQuantity == 0) {
                        playPositionalSound(grenadeBounceSample, Player[playerCharacterIndex].x, Player[playerCharacterIndex].y, projectile->x, projectile->y);
                        projectile->grenadeBouncedQuantity = 1;
                    }
                }
                else if(projectile->distanceTraveled < projectile->grenadeThrowDistance+60.f) {
                    projectile->grenadeFlySpeed = 3.f;
                }
                else if(projectile->distanceTraveled < projectile->grenadeThrowDistance+70.f) {
                    projectile->grenadeFlySpeed = 1.f;
                    if(projectile->grenadeBouncedQuantity <= 1) {
                        playPositionalSound(grenadeBounceSample, Player[playerCharacterIndex].x, Player[playerCharacterIndex].y, projectile->x, projectile->y);
                        projectile->grenadeBouncedQuantity = 2;
                    }
                }
                else projectile->grenadeFlySpeed = 0.f;
            }
            projectile->grenadeRotation += projectile->grenadeFlySpeed/30.f*deltaTime;
            move_x = cos(projectile->dir)*deltaTime*projectile->grenadeFlySpeed;
            move_y = sin(projectile->dir)*deltaTime*projectile->grenadeFlySpeed;
        }
        else {
            move_x = cos(projectile->dir)*deltaTime*60.f;
            move_y = sin(projectile->dir)*deltaTime*60.f;
        }
        projectile->x += move_x;
        projectile->y += move_y;
        if(projectile->distanceTraveled >= 300.f) {
            projectile->trailX += move_x;
            projectile->trailY += move_y;
        }
        if(projectile->projectileType == PROJECTILE_TYPE_MISSILE) {
            projectile->missileParticlesTimer += deltaTime*10.f;
            for(int i=0; i<(int)projectile->missileParticlesTimer; ++i) {
                Particle.push_back(ParticleClass(projectile->x+rand()%11-5,
                                                 projectile->y+rand()%11-5,
                                                 (rand()%360)/180.f*M_PI,
                                                 0.5f, 6.f, 0.f, 0,
                                                 sf::Color(80+rand()%200, 80, 40),
                                                 255.f, true));
            }
            projectile->missileParticlesTimer -= (int)projectile->missileParticlesTimer;
        }
        projectile->distanceTraveled += sqrt(move_x*move_x+move_y*move_y);
        if(projectile->distanceTraveled >= MAX_PROJECTILE_TRAVEL_DISTANCE ||
           (projectile->projectileType == PROJECTILE_TYPE_GRENADE &&
            globalTime >= projectile->timeout_grenadeExplode)) {
            Projectile.erase(projectile);
            continue;
        }
    }
}

/**
* @brief Logic related to particles.
*/
void LogicModule::logicParticles()
{
    for(std::list <ParticleClass>::iterator it=Particle.begin(); it!=Particle.end();) {
        it->x += cos(it->dir)*deltaTime*it->speed;
        it->y += sin(it->dir)*deltaTime*it->speed;
        it->alpha -= deltaTime*it->fadeAwaySpeed;
        if(it->alpha <= 0.f) {
            it = Particle.erase(it);
        }
        else ++it;
    }
}

/**
* @brief Logic related to weather.
*/
void LogicModule::logicWeather()
{
    float player_x, player_y;
    if(playerCharacterIndex >= 0) {
        player_x = Player[playerCharacterIndex].x;
        player_y = Player[playerCharacterIndex].y;
    }
    else {
        player_x = View.x;
        player_y = View.y;
    }
    static float previous_player_x = player_x;
    static float previous_player_y = player_y;

    for(std::list <RainDropClass>::iterator it=Weather.rainDrop.begin(); it!=Weather.rainDrop.end();) {
        if(globalTime < it->timeout_splash) {
            it->x += deltaTime*35.f-(player_x-previous_player_x)/2.f;
            it->y += deltaTime*35.f-(player_y-previous_player_y)/2.f;
            if(it->x > window.getSize().x || it->y > window.getSize().y) {
                it = Weather.rainDrop.erase(it);
                continue;
            }
        }
        else {
            it->x -= player_x-previous_player_x;
            it->y -= player_y-previous_player_y;
            if(it->splashFrame < 0) {
                it->splashFrame = 0;
                it->timeout_nextSplashFrame = globalTime+40.0;
            }
            else {
                if(globalTime >= it->timeout_nextSplashFrame) {
                    ++(it->splashFrame);
                    if(it->splashFrame == RAINDROP_SPLASH_ANIMATION_FRAMES_QUANTITY) {
                        it = Weather.rainDrop.erase(it);
                        continue;
                    }
                }
            }
        }
        ++it;
    }

    previous_player_x = player_x;
    previous_player_y = player_y;

    float target_rainIntensity = 0.f;
    if(Weather.rainType == RAIN_TYPE_SMALL) target_rainIntensity = 2.5f;
    else if(Weather.rainType == RAIN_TYPE_MEDIUM) target_rainIntensity = 4.5f;
    else if(Weather.rainType == RAIN_TYPE_HEAVY) target_rainIntensity = 10.f;

    if(fabs(Weather.rainIntensity-target_rainIntensity) < deltaTime/12.f)
        Weather.rainIntensity = target_rainIntensity;
    else if(Weather.rainIntensity > target_rainIntensity)
        Weather.rainIntensity -= deltaTime/12.f;
    else Weather.rainIntensity += deltaTime/12.f;

    static float newWeatherDrops = 0;
    newWeatherDrops += Weather.rainIntensity*deltaTime;
    for(int i=0; i<(int)newWeatherDrops; ++i) {
        bool verticalRandom = rand()%2;
        if(verticalRandom) Weather.rainDrop.push_back(RainDropClass(0.f, rand()%window.getSize().y));
        else Weather.rainDrop.push_back(RainDropClass(rand()%window.getSize().x, 0.f));
    }
    newWeatherDrops -= (int)newWeatherDrops;

    if(Weather.stormType != STORM_TYPE_NONE) {
        if(globalTime >= Weather.timeout_lightning) {
            playPositionalSound(Weather.lightningSample,
                                player_x,
                                player_y,
                                player_x+rand()%1000-500,
                                player_y+rand()%1000-500);
            timeout_lightningLight = globalTime+50.0;
            if(Weather.stormType == STORM_TYPE_SMALL) Weather.timeout_lightning = globalTime+6000.0+rand()%28000;
            else if(Weather.stormType == STORM_TYPE_MEDIUM) Weather.timeout_lightning = globalTime+5000.0+rand()%25000;
            else if(Weather.stormType == STORM_TYPE_HEAVY) Weather.timeout_lightning = globalTime+4000.0+rand()%20000;
            else Weather.timeout_lightning = globalTime+6000.0+rand()%28000;
        }
    }

    Weather.dayTimeInMinutes += (1000.0/30.0*deltaTime)/1000.0;
    if(Weather.dayTimeInMinutes > 60.0*24.0) Weather.dayTimeInMinutes -= 60.0*24.0;

    if(Weather.dayTimeInMinutes >= 60.0*3.0 && Weather.dayTimeInMinutes <= 60.0*23.0) {
        if(Weather.dayTimeInMinutes < 60.0*12.0) {
            ambientLight = int((Weather.dayTimeInMinutes-60.0*3.0)*255.0/(60.0*9.0));
        }
        else if(Weather.dayTimeInMinutes > 60.0*14.0) {
            ambientLight = 255-int((Weather.dayTimeInMinutes-60.0*14.0)*255.0/(60.0*9.0));
        }
        else ambientLight = 255;
    }
    else ambientLight = 0;
    ambientLight = 10.f+((float)ambientLight/255.f)*245.f;

    if(Weather.dayTimeInMinutes < 60.0*12.0) {
        Weather.ambientShadowLength = 0.4+(1.0-Weather.dayTimeInMinutes/(60.0*12.0))*0.6;
    }
    else {
        Weather.ambientShadowLength = 0.4+(Weather.dayTimeInMinutes-60.0*12.0)/(60.0*12.0)*0.6;
    }
    Weather.ambientShadowDir = ((1.0-Weather.dayTimeInMinutes/(60.0*24.0))*1.5-0.5)*M_PI;
    if(Weather.dayTimeInMinutes < 60.0*3.0 ||
       Weather.dayTimeInMinutes > 60.0*21.0) {
        Weather.ambientShadowAlpha = 0.f;
    }
    else if(Weather.dayTimeInMinutes < 60.0*8.0) {
        Weather.ambientShadowAlpha = (1.0-(60.0*8.0-Weather.dayTimeInMinutes)/(60.0*5.0))*255.0;
    }
    else if(Weather.dayTimeInMinutes > 60.0*16.0) {
        Weather.ambientShadowAlpha = (60.0*21.0-Weather.dayTimeInMinutes)/(60.0*5.0)*255.0;
    }
    else Weather.ambientShadowAlpha = 255.f;

    sf::Vector3f nightCol(0.65f, 0.65f, 1.f);
    sf::Vector3f morningCol(1.f, 0.8f, 0.4f);
    sf::Vector3f dayCol(1.f, 1.f, 1.f);
    sf::Vector3f eveningCol(1.f, 0.8f, 0.4f);

    if(Weather.dayTimeInMinutes < 60.0*3.0) {
        Weather.ambientLightColor = nightCol;
    }
    else if(Weather.dayTimeInMinutes < 60.0*6.0) {
        float factor = (Weather.dayTimeInMinutes-60.0*3.0)/(60.0*3.0);
        Weather.ambientLightColor = (1.f-factor)*nightCol+factor*morningCol;
    }
    else if(Weather.dayTimeInMinutes < 60.0*9.0) {
        float factor = (Weather.dayTimeInMinutes-60.0*6.0)/(60.0*3.0);
        Weather.ambientLightColor = (1.f-factor)*morningCol+factor*dayCol;
    }
    else if(Weather.dayTimeInMinutes < 60.0*15.0) {
        Weather.ambientLightColor = dayCol;
    }
    else if(Weather.dayTimeInMinutes < 60.0*19.0) {
        float factor = (Weather.dayTimeInMinutes-60.0*15.0)/(60.0*4.0);
        Weather.ambientLightColor = (1.f-factor)*dayCol+factor*eveningCol;
    }
    else if(Weather.dayTimeInMinutes < 60.0*22.0) {
        float factor = (Weather.dayTimeInMinutes-60.0*19.0)/(60.0*3.0);
        Weather.ambientLightColor = (1.f-factor)*eveningCol+factor*nightCol;
    }
    else Weather.ambientLightColor = nightCol;

    Weather.sunScreenPosX = 0.f;
    Weather.sunScreenPosY = 0.f;
    Weather.moonScreenPosX = 0.f;
    Weather.moonScreenPosY = 0.f;
    _assert(!Tile.empty(),"Map is empty in logicWeather.");
    _assert(!Tile[0].empty(),"Map is empty in logicWeather.");
    if(Weather.dayTimeInMinutes < 60.0*6.0 ||
       Weather.dayTimeInMinutes > 60.0*22.0) {
        float tmp = 0.f;
        if(Weather.dayTimeInMinutes > 60.0*22.0) tmp = Weather.dayTimeInMinutes-60.0*22.0;
        else tmp = Weather.dayTimeInMinutes+60.0*2.0;
        Weather.moonScreenPosX = window.getSize().x-(window.getSize().x+100)*tmp/(60.0*8.0);
        Weather.moonScreenPosY = window.getSize().y-player_y*window.getSize().y/(Tile[0].size()*TILE_SIZE);
    }
    else if(Weather.dayTimeInMinutes > 60.0*10.0 && Weather.dayTimeInMinutes < 60.0*18.0) {
        float tmp = Weather.dayTimeInMinutes-60.0*10.0;
        Weather.sunScreenPosX = window.getSize().x-(window.getSize().x+100)*tmp/(60.0*8.0);
        Weather.sunScreenPosY = window.getSize().y-player_y*window.getSize().y/(Tile[0].size()*TILE_SIZE);
    }

    float smallRainSoundVolumeTarget = 0.f;
    float mediumRainSoundVolumeTarget = 0.f;
    float heavyRainSoundVolumeTarget = 0.f;
    float dayBackgroundSoundVolumeTarget = 0.f;
    float nightBackgroundSoundVolumeTarget = 0.f;
    if(Weather.rainType == RAIN_TYPE_SMALL) smallRainSoundVolumeTarget = 0.5f;
    else if(Weather.rainType == RAIN_TYPE_MEDIUM) mediumRainSoundVolumeTarget = 0.5f;
    else if(Weather.rainType == RAIN_TYPE_HEAVY) heavyRainSoundVolumeTarget = 0.5f;
    else if(Weather.dayTimeInMinutes < 60.0*6.0 || Weather.dayTimeInMinutes > 60.0*22.0) nightBackgroundSoundVolumeTarget = 0.5f;
    else dayBackgroundSoundVolumeTarget = 0.5f;

    adjustSoundVolumeSmoothly(Weather.smallRainSound, smallRainSoundVolumeTarget);
    adjustSoundVolumeSmoothly(Weather.mediumRainSound, mediumRainSoundVolumeTarget);
    adjustSoundVolumeSmoothly(Weather.heavyRainSound, heavyRainSoundVolumeTarget);
    adjustSoundVolumeSmoothly(Weather.dayBackgroundSound, dayBackgroundSoundVolumeTarget);
    adjustSoundVolumeSmoothly(Weather.nightBackgroundSound, nightBackgroundSoundVolumeTarget);
}

/**
* @brief Logic related to view.
*/
void LogicModule::logicView()
{
    View.x = Player[playerCharacterIndex].x+((float)mx/(float)window.getSize().x-0.5f)*25.f+viewOffsetX;
    View.y = Player[playerCharacterIndex].y+((float)my/(float)window.getSize().y-0.5f)*25.f+viewOffsetY;
    if(!floatCompare(viewOffsetX, 0.f, 0.01f) || !floatCompare(viewOffsetY, 0.f, 0.01f)) {
        float dir = atan2(-viewOffsetY,-viewOffsetX);
        if(fabs(viewOffsetX) < deltaTime*4.f) viewOffsetX = 0.f;
        else viewOffsetX += cos(dir)*deltaTime*4.f;
        if(fabs(viewOffsetY) < deltaTime*4.f) viewOffsetY = 0.f;
        else viewOffsetY += sin(dir)*deltaTime*4.f;
    }
    static float vd = 0.8f;
    vd = std::max(window.getSize().x, window.getSize().y)/1024.f*0.8f;
    View.distance = vd;
}

/**
* @brief Character inventory window logic callback.
*/
void LogicModule::callback_logicCharacterInventoryWindow(InterfaceClass &interface, WindowClass &window, enum LMBActionEnum LMBAction)
{
    if(playerCharacterIndex < 0) return;

    float characterObjectSlotOffsetX = 30.f;
    float characterObjectSlotOffsetY = 30.f;
    float characterInventoryOffsetX = 18.f;
    float characterInventoryOffsetY = 215.f;

    interface.inventoryMouseOverSlot = -1;
    interface.inventoryMouseOverInvX = -1;
    interface.inventoryMouseOverInvY = -1;

    for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
        float x = window.x+characterObjectSlotOffsetX+objectSlot[i].offsetX;
        float y = window.y+characterObjectSlotOffsetY+objectSlot[i].offsetY;
        if(mx >= x && mx <= x+interface.objectSlotTexture.getSize().x &&
           my >= y && my <= y+interface.objectSlotTexture.getSize().y
           && (LMBAction == LMB_FREE ||
               LMBAction == LMB_PRESSED ||
               LMBAction == LMB_NEW_PRESSED)) {
            interface.inventoryMouseOverSlot = i;
        }
    }
    for(size_t i=0; i<Player[playerCharacterIndex].objectInInventory.size(); ++i) {
        for(size_t j=0; j<Player[playerCharacterIndex].objectInInventory[i].size(); ++j) {
            float x = window.x+characterInventoryOffsetX+i*interface.objectSlotTexture.getSize().x;
            float y = window.y+characterInventoryOffsetY+j*interface.objectSlotTexture.getSize().y;
            if(mx >= x && mx <= x+interface.objectSlotTexture.getSize().x &&
               my >= y && my <= y+interface.objectSlotTexture.getSize().y
               && (LMBAction == LMB_FREE ||
                   LMBAction == LMB_PRESSED ||
                   LMBAction == LMB_NEW_PRESSED)) {
                interface.inventoryMouseOverInvX = i;
                interface.inventoryMouseOverInvY = j;
            }
        }
    }
    if(objectOnMouse.objectType < 0) {
        if(LMBAction == LMB_NEW_PRESSED) {
            if(interface.inventoryMouseOverSlot >= 0 &&
               interface.inventoryMouseOverSlot < CHARACTER_OBJECT_SLOTS_QUANTITY) {
                objectOnMouse.objectType = Player[playerCharacterIndex].objectOnSlot[interface.inventoryMouseOverSlot].type;
                objectOnMouse.place = OBJECT_PLACE_SLOT;
                objectOnMouse.placeSlot = interface.inventoryMouseOverSlot;
            }
            else if(interface.inventoryMouseOverInvX >= 0 &&
                    interface.inventoryMouseOverInvX < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
                    interface.inventoryMouseOverInvY >= 0 &&
                    interface.inventoryMouseOverInvY < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT) {
                objectOnMouse.objectType = Player[playerCharacterIndex].objectInInventory[interface.inventoryMouseOverInvX][interface.inventoryMouseOverInvY].type;
                objectOnMouse.place = OBJECT_PLACE_INVENTORY;
                objectOnMouse.placeX = interface.inventoryMouseOverInvX;
                objectOnMouse.placeY = interface.inventoryMouseOverInvY;
            }
        }
    }
    else {
        _assert(objectOnMouse.objectType < (int)ObjectType.size(), "Object on mouse type out of bounds in callback_logicCharacterInventoryWindow.");
        if(LMBAction == LMB_FREE) {
            if(interface.inventoryMouseOverSlot >= 0) {
                if(interface.inventoryMouseOverSlot < CHARACTER_OBJECT_SLOTS_QUANTITY) {
                    if(canObjectBePlacedOnSlot(objectOnMouse.objectType, interface.inventoryMouseOverSlot)) {
                        sendChangeObjectPlaceRequest(OBJECT_PLACE_SLOT, interface.inventoryMouseOverSlot, -1, -1);
                    }
                }
                objectOnMouse.objectType = -1;
            }
            else if(interface.inventoryMouseOverInvX >= 0 && interface.inventoryMouseOverInvY >= 0) {
                if(interface.inventoryMouseOverInvX < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
                   interface.inventoryMouseOverInvY < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT) {
                    sendChangeObjectPlaceRequest(OBJECT_PLACE_INVENTORY, interface.inventoryMouseOverInvX, interface.inventoryMouseOverInvY, -1);
                }
                objectOnMouse.objectType = -1;
            }
        }
    }
}

/**
* @brief Object description window logic callback.
*/
void LogicModule::callback_logicObjectDescriptionWindow(InterfaceClass &interface, WindowClass &window, enum LMBActionEnum LMBAction)
{
    if(playerCharacterIndex < 0) return;

    ObjectClass *object = NULL;

    if(interface.objectDescriptionSlot >= 0 &&
       interface.objectDescriptionSlot < CHARACTER_OBJECT_SLOTS_QUANTITY)
        object = &Player[playerCharacterIndex].objectOnSlot[interface.objectDescriptionSlot];
    else if(interface.objectDescriptionInvX >= 0 &&
            interface.objectDescriptionInvX < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
            interface.objectDescriptionInvY >= 0 &&
            interface.objectDescriptionInvY < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT)
        object = &Player[playerCharacterIndex].objectInInventory[interface.objectDescriptionInvX][interface.objectDescriptionInvY];

    bool noObject = false;
    if(object == NULL) noObject = true;
    else if(object->type < 0) noObject = true;
    if(noObject) {
        interface.objectDescriptionSlot = -1;
        interface.objectDescriptionInvX = -1;
        interface.objectDescriptionInvY = -1;
        window.visible = false;
        return;
    }
    _assert(object->type < (int)ObjectType.size(), "Object type out of bounds in callback_logicObjectDescriptionWindow.");
    interface.mouseOverWeaponAttachmentSlot = -1;
    if(playerCharacterIndex >= 0 && ObjectType[object->type].baseType == OBJECT_BASE_TYPE_WEAPON) {
        for(int i=0; i<WEAPON_ATTACHMENTS_QUANTITY; ++i) {
            float x = window.x+weaponAttachmentSlot[i].offsetX;
            float y = window.y+weaponAttachmentSlot[i].offsetY;
            if(mx >= x && mx <= x+interface.objectSlotTexture.getSize().x &&
               my >= y && my <= y+interface.objectSlotTexture.getSize().y &&
               (LMBAction == LMB_FREE ||
                LMBAction == LMB_PRESSED ||
                LMBAction == LMB_NEW_PRESSED)) {
                interface.mouseOverWeaponAttachmentSlot = i;
            }
        }
        if(objectOnMouse.objectType < 0) {
            if(LMBAction == LMB_NEW_PRESSED) {
                if(interface.mouseOverWeaponAttachmentSlot >= 0 &&
                   interface.mouseOverWeaponAttachmentSlot < WEAPON_ATTACHMENTS_QUANTITY) {
                    if(interface.objectDescriptionSlot >= 0 &&
                       interface.objectDescriptionSlot < CHARACTER_OBJECT_SLOTS_QUANTITY) {
                        objectOnMouse.objectType = Player[playerCharacterIndex].objectOnSlot[interface.objectDescriptionSlot].param[OBJECT_PARAM_ADDON_1+interface.mouseOverWeaponAttachmentSlot];
                        objectOnMouse.place = OBJECT_PLACE_SLOT_WEAPON_ATTACHMENT;
                    }
                    else if(interface.objectDescriptionInvX >= 0 &&
                            interface.objectDescriptionInvX < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
                            interface.objectDescriptionInvY >= 0 &&
                            interface.objectDescriptionInvY < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT) {
                        objectOnMouse.objectType = Player[playerCharacterIndex].objectInInventory[interface.objectDescriptionInvX][interface.objectDescriptionInvY].param[OBJECT_PARAM_ADDON_1+interface.mouseOverWeaponAttachmentSlot];
                        objectOnMouse.place = OBJECT_PLACE_INVENTORY_WEAPON_ATTACHMENT;
                    }
                    objectOnMouse.placeSlot2 = interface.mouseOverWeaponAttachmentSlot;
                    objectOnMouse.placeSlot = interface.objectDescriptionSlot;
                    objectOnMouse.placeX = interface.objectDescriptionInvX;
                    objectOnMouse.placeY = interface.objectDescriptionInvY;
                }
            }
        }
        else {
            _assert(objectOnMouse.objectType < (int)ObjectType.size(), "Object on mouse type out of bounds in callback_logicObjectDescriptionWindow.");
            if(LMBAction == LMB_FREE) {
                if(interface.mouseOverWeaponAttachmentSlot >= 0) {
                    if(interface.mouseOverWeaponAttachmentSlot < WEAPON_ATTACHMENTS_QUANTITY) {
                        if(ObjectType[objectOnMouse.objectType].baseType == OBJECT_BASE_TYPE_ADDON &&
                           ObjectType[objectOnMouse.objectType].attachmentType == weaponAttachmentSlot[interface.mouseOverWeaponAttachmentSlot].attachmentType &&
                           ObjectType[objectOnMouse.objectType].weaponType == ObjectType[object->type].weaponType) {
                            if(interface.objectDescriptionSlot >= 0 &&
                               interface.objectDescriptionSlot < CHARACTER_OBJECT_SLOTS_QUANTITY) {
                                sendChangeObjectPlaceRequest(OBJECT_PLACE_SLOT_WEAPON_ATTACHMENT, interface.objectDescriptionSlot, interface.mouseOverWeaponAttachmentSlot, -1);
                            }
                            else if(interface.objectDescriptionInvX >= 0 &&
                                    interface.objectDescriptionInvX < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
                                    interface.objectDescriptionInvY >= 0 &&
                                    interface.objectDescriptionInvY < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT) {
                                sendChangeObjectPlaceRequest(OBJECT_PLACE_INVENTORY_WEAPON_ATTACHMENT, interface.objectDescriptionInvX, interface.objectDescriptionInvY, interface.mouseOverWeaponAttachmentSlot);
                            }
                        }
                    }
                    objectOnMouse.objectType = -1;
                }
            }
        }
    }
}

/**
* @brief Trade with NPC window logic callback.
*/
void LogicModule::callback_logicTradeWithNPCWindow(InterfaceClass &interface, WindowClass &window, enum LMBActionEnum LMBAction)
{
    if(playerCharacterIndex < 0) return;

    if(!currentTradeWithNPC.active) {
        window.visible = false;
        return;
    }
    for(size_t i=0; i<currentTradeWithNPC.NPCObjectType.size(); ++i) {
        if(mx >= window.x+1.f &&
           my >= window.y+20.f+i*50.f &&
           mx <= window.x+251.f &&
           my < window.y+20.f+(i+1)*50.f) {
            if(LMBAction == LMB_NEW_PRESSED) {
                if(Player[playerCharacterIndex].param[CHARACTER_PARAM_MONEY] < ObjectType[currentTradeWithNPC.NPCObjectType[i]].value) {
                    interface.statusLogMessage.push_back(StatusLogMessageClass("Not enough money.", sf::Color(255, 50, 50)));
                }
                else {
                    char packet[50];
                    sprintf(packet,"%c %d", PACKET_TRADE_WITH_NPC_BUY_OBJECT, i);
                    sendPacket(0, packet);
                }
            }
            if(LMBAction == LMB_FREE) {
                interface.mouseOverTradeWithNPCObjectIndex = i;
            }
        }
    }
}
