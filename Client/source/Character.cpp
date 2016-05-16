#include "Classes.hpp"

#include "global.hpp"
#include "Master.hpp"

void Character::update()
{
    if(characterSet == CHARACTER_PLAYER) {
        for(std::list <MessageOverHeadClass>::iterator it=messageOverHead.begin(); it!=messageOverHead.end();) {
            if(it->fadesAway) {
                it->alpha -= deltaTime*5.f;
                if(it->alpha <= 0.f) {
                    it = messageOverHead.erase(it);
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

        if(ID == playerCharacterID) return;;
    }

    if(!isSeen) return;;

    float tmp = dir-destDir;
    if(tmp < -M_PI) tmp += 2*M_PI;
    if(tmp > M_PI) tmp -= 2*M_PI;
    if(fabs(tmp) <= deltaTime/2.f) dir = destDir;
    else if(tmp < 0) {
        dir += deltaTime/2.f;
        if(dir > M_PI) dir = -2*M_PI+dir;
    }
    else {
        dir -= deltaTime/2.f;
        if(dir < -M_PI) dir = 2*M_PI+dir;
    }

    if(!floatCompare(position.x, destPosition.x, 0.01f) || !floatCompare(position.y, destPosition.y, 0.01f)) {
        float dir = atan2(destPosition.y-position.y, destPosition.x-position.x);
        float dir_cos = cos(dir);
        float dir_sin = sin(dir);
        if(fabs(position.x-destPosition.x) <= deltaTime*speed*dir_cos)
            position.x = destPosition.x;
        else {
            position.x += deltaTime*speed*dir_cos;
        }
        if(fabs(position.y-destPosition.y) <= deltaTime*speed*dir_sin)
            position.y = destPosition.y;
        else {
            position.y += deltaTime*speed*dir_sin;
        }
    }
}

void Character::render() const
{
    if(!isSeen) return;
    vPoint pos = Master::getInstance().getScreenPosition(position.x, position.y, Master::getInstance().View);
    const ObjectClass *weapon = &objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX];

    if(weapon->type >= 0) {
        _assert(weapon->type < (int)Master::getInstance().ObjectType.size(), "Character weapon object type out of bounds in renderCharacters.");

        if(Master::getInstance().ObjectType[weapon->type].weaponType == WEAPON_TYPE_SMALL_GUN) {
            for(size_t j=0; j<CHARACTER_OBJECT_SLOTS_QUANTITY; ++j) {
                if(objectSlot[j].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;

                int type = objectOnSlot[j].type;
                if(type < 0) {
                    if(!objectSlot[j].defaultOnCharacterSmallWeaponColorMapSprite.getTexture()) continue;

                    float screen_x = pos.x-objectSlot[j].defaultOnCharacterSmallWeaponColorMapSprite.getTexture()->getSize().x/2.f*Master::getInstance().View.distance;
                    float screen_y = pos.y-objectSlot[j].defaultOnCharacterSmallWeaponColorMapSprite.getTexture()->getSize().y/2.f*Master::getInstance().View.distance;

                    Master::getInstance().spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterSmallWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                                              screen_x, screen_y,
                                                              Master::getInstance().View.distance, Master::getInstance().View.distance,
                                                              dir*180.f/M_PI);

                    if(objectSlot[j].defaultOnCharacterSmallWeaponNormalMapSprite.getTexture() && objectSlot[j].defaultOnCharacterSmallWeaponNormalMapSprite.getTexture()->getSize().x)
                        Master::getInstance().spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterSmallWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                            screen_x, screen_y,
                                            Master::getInstance().View.distance, Master::getInstance().View.distance,
                                            dir*180.f/M_PI);

                    if(objectSlot[j].defaultOnCharacterSmallWeaponHeightMapSprite.getTexture() && objectSlot[j].defaultOnCharacterSmallWeaponHeightMapSprite.getTexture()->getSize().x)
                        Master::getInstance().spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterSmallWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                            screen_x, screen_y,
                                            Master::getInstance().View.distance, Master::getInstance().View.distance,
                                            dir*180.f/M_PI);
                }
                else {
                    _assert(type < (int)Master::getInstance().ObjectType.size(), "Slot object type out of bounds in renderCharacters.");

                    if(!Master::getInstance().ObjectType[type].onCharacterSmallWeaponColorMapSprite.getTexture()) continue;

                    float screen_x = pos.x-Master::getInstance().ObjectType[type].onCharacterSmallWeaponColorMapTexture.getSize().x/2.f*Master::getInstance().View.distance;
                    float screen_y = pos.y-Master::getInstance().ObjectType[type].onCharacterSmallWeaponColorMapTexture.getSize().y/2.f*Master::getInstance().View.distance;

                    Master::getInstance().spriteDrawQueue.add(&Master::getInstance().ObjectType[type].onCharacterSmallWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                        screen_x, screen_y,
                                        Master::getInstance().View.distance, Master::getInstance().View.distance,
                                        dir*180.f/M_PI);

                    if(Master::getInstance().ObjectType[type].onCharacterSmallWeaponNormalMapSprite.getTexture() && Master::getInstance().ObjectType[type].onCharacterSmallWeaponNormalMapSprite.getTexture()->getSize().x)
                        Master::getInstance().spriteDrawQueue.add(&Master::getInstance().ObjectType[type].onCharacterSmallWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                            screen_x, screen_y,
                                            Master::getInstance().View.distance, Master::getInstance().View.distance,
                                            dir*180.f/M_PI);

                    if(Master::getInstance().ObjectType[type].onCharacterSmallWeaponHeightMapSprite.getTexture() && Master::getInstance().ObjectType[type].onCharacterSmallWeaponHeightMapSprite.getTexture()->getSize().x)
                        Master::getInstance().spriteDrawQueue.add(&Master::getInstance().ObjectType[type].onCharacterSmallWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                            screen_x, screen_y,
                                            Master::getInstance().View.distance, Master::getInstance().View.distance,
                                            dir*180.f/M_PI);

                    // ***
                    /*
                    float screen_w = ObjectType[type].on_character_sprite_small_weapon.Width()*View.distance;
                    float screen_h = ObjectType[type].on_character_sprite_small_weapon.Height()*View.distance;
                    float real_w = ObjectType[type].on_character_sprite_small_weapon.Width();
                    float real_h = ObjectType[type].on_character_sprite_small_weapon.Height();
                    blitTransformedShaded(ObjectType[type].on_character_sprite_small_weapon,
                                          screen_x, screen_y,
                                          screen_w, screen_h,
                                          real_x, real_y,
                                          real_w, real_h,
                                          dir);*/
                }
            }
        }
        else if(Master::getInstance().ObjectType[weapon->type].weaponType == WEAPON_TYPE_BIG_GUN ||
                Master::getInstance().ObjectType[weapon->type].weaponType == WEAPON_TYPE_ROCKET_LAUNCHER) {
            for(size_t j=0; j<CHARACTER_OBJECT_SLOTS_QUANTITY; ++j) {
                if(objectSlot[j].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;

                int type = objectOnSlot[j].type;
                if(type < 0) {
                    if(!objectSlot[j].defaultOnCharacterBigWeaponColorMapSprite.getTexture()) continue;

                    float screen_x = pos.x-objectSlot[j].defaultOnCharacterBigWeaponColorMapSprite.getTexture()->getSize().x/2.f*Master::getInstance().View.distance;
                    float screen_y = pos.y-objectSlot[j].defaultOnCharacterBigWeaponColorMapSprite.getTexture()->getSize().y/2.f*Master::getInstance().View.distance;

                    Master::getInstance().spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterBigWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                        screen_x, screen_y,
                                        Master::getInstance().View.distance, Master::getInstance().View.distance,
                                        dir*180.f/M_PI);

                    if(objectSlot[j].defaultOnCharacterBigWeaponNormalMapSprite.getTexture() && objectSlot[j].defaultOnCharacterBigWeaponNormalMapSprite.getTexture()->getSize().x)
                        Master::getInstance().spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterBigWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                            screen_x, screen_y,
                                            Master::getInstance().View.distance, Master::getInstance().View.distance,
                                            dir*180.f/M_PI);

                    if(objectSlot[j].defaultOnCharacterBigWeaponHeightMapSprite.getTexture() && objectSlot[j].defaultOnCharacterBigWeaponHeightMapSprite.getTexture()->getSize().x)
                        Master::getInstance().spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterBigWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                            screen_x, screen_y,
                                            Master::getInstance().View.distance, Master::getInstance().View.distance,
                                            dir*180.f/M_PI);
                }
                else {
                    _assert(type < (int)Master::getInstance().ObjectType.size(), "Slot object type out of bounds in renderCharacters.");

                    if(!Master::getInstance().ObjectType[type].onCharacterBigWeaponColorMapSprite.getTexture()) continue;

                    float screen_x = pos.x-Master::getInstance().ObjectType[type].onCharacterBigWeaponColorMapTexture.getSize().x/2.f*Master::getInstance().View.distance;
                    float screen_y = pos.y-Master::getInstance().ObjectType[type].onCharacterBigWeaponColorMapTexture.getSize().y/2.f*Master::getInstance().View.distance;

                    Master::getInstance().spriteDrawQueue.add(&Master::getInstance().ObjectType[type].onCharacterBigWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                        screen_x, screen_y,
                                        Master::getInstance().View.distance, Master::getInstance().View.distance,
                                        dir*180.f/M_PI);

                    if(Master::getInstance().ObjectType[type].onCharacterBigWeaponNormalMapSprite.getTexture() && Master::getInstance().ObjectType[type].onCharacterBigWeaponNormalMapSprite.getTexture()->getSize().x)
                        Master::getInstance().spriteDrawQueue.add(&Master::getInstance().ObjectType[type].onCharacterBigWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                            screen_x, screen_y,
                                            Master::getInstance().View.distance, Master::getInstance().View.distance,
                                            dir*180.f/M_PI);

                    if(Master::getInstance().ObjectType[type].onCharacterBigWeaponHeightMapSprite.getTexture() && Master::getInstance().ObjectType[type].onCharacterBigWeaponHeightMapSprite.getTexture()->getSize().x)
                        Master::getInstance().spriteDrawQueue.add(&Master::getInstance().ObjectType[type].onCharacterBigWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                            screen_x, screen_y,
                                            Master::getInstance().View.distance, Master::getInstance().View.distance,
                                            dir*180.f/M_PI);
                    // ***
                    /*
                    float screen_w = ObjectType[type].on_character_sprite_big_weapon.Width()*View.distance;
                    float screen_h = ObjectType[type].on_character_sprite_big_weapon.Height()*View.distance;
                    float real_w = ObjectType[type].on_character_sprite_big_weapon.Width();
                    float real_h = ObjectType[type].on_character_sprite_big_weapon.Height();
                    blitTransformedShaded(ObjectType[type].on_character_sprite_big_weapon,
                                          screen_x, screen_y,
                                          screen_w, screen_h,
                                          real_x, real_y,
                                          real_w, real_h,
                                          dir);*/
                }
            }
        }
        // ***
        /*
        float screen_w = ObjectType[weapon->type].on_character_sprite.Width()*View.distance;
        float screen_h = ObjectType[weapon->type].on_character_sprite.Height()*View.distance;
        float real_w = ObjectType[weapon->type].on_character_sprite.Width();
        float real_h = ObjectType[weapon->type].on_character_sprite.Height();
        blitTransformedShaded(ObjectType[weapon->type].on_character_sprite,
                              screen_x, screen_y,
                              screen_w, screen_h,
                              real_x, real_y,
                              real_w, real_h,
                              dir);*/

        _assert(Master::getInstance().ObjectType[weapon->type].onCharacterColorMapSprite.getTexture(), "Weapon sprite has no texture in renderCharacters.");

        float screen_x = pos.x-Master::getInstance().ObjectType[weapon->type].onCharacterColorMapSprite.getTexture()->getSize().x/2.f*Master::getInstance().View.distance;
        float screen_y = pos.y-Master::getInstance().ObjectType[weapon->type].onCharacterColorMapSprite.getTexture()->getSize().y/2.f*Master::getInstance().View.distance;

        Master::getInstance().spriteDrawQueue.add(&Master::getInstance().ObjectType[weapon->type].onCharacterColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                            screen_x, screen_y,
                            Master::getInstance().View.distance, Master::getInstance().View.distance,
                            dir*180.f/M_PI);

        if(Master::getInstance().ObjectType[weapon->type].onCharacterNormalMapSprite.getTexture() && Master::getInstance().ObjectType[weapon->type].onCharacterNormalMapSprite.getTexture()->getSize().x)
            Master::getInstance().spriteDrawQueue.add(&Master::getInstance().ObjectType[weapon->type].onCharacterNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                screen_x, screen_y,
                                Master::getInstance().View.distance, Master::getInstance().View.distance,
                                dir*180.f/M_PI);

        if(Master::getInstance().ObjectType[weapon->type].onCharacterHeightMapSprite.getTexture() && Master::getInstance().ObjectType[weapon->type].onCharacterHeightMapSprite.getTexture()->getSize().x)
            Master::getInstance().spriteDrawQueue.add(&Master::getInstance().ObjectType[weapon->type].onCharacterHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                screen_x, screen_y,
                                Master::getInstance().View.distance, Master::getInstance().View.distance,
                                dir*180.f/M_PI);
    }
    else {
        for(size_t j=0; j<CHARACTER_OBJECT_SLOTS_QUANTITY; ++j) {
            if(objectSlot[j].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;

            int type = objectOnSlot[j].type;
            if(type < 0) {
                if(!objectSlot[j].defaultOnCharacterNoWeaponColorMapSprite.getTexture()) continue;

                float screen_x = pos.x-objectSlot[j].defaultOnCharacterNoWeaponColorMapSprite.getTexture()->getSize().x/2.f*Master::getInstance().View.distance;
                float screen_y = pos.y-objectSlot[j].defaultOnCharacterNoWeaponColorMapSprite.getTexture()->getSize().y/2.f*Master::getInstance().View.distance;

                Master::getInstance().spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterNoWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                    screen_x, screen_y,
                                    Master::getInstance().View.distance, Master::getInstance().View.distance,
                                    dir*180.f/M_PI);

                if(objectSlot[j].defaultOnCharacterNoWeaponNormalMapSprite.getTexture() && objectSlot[j].defaultOnCharacterNoWeaponNormalMapSprite.getTexture()->getSize().x)
                    Master::getInstance().spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterNoWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                        screen_x, screen_y,
                                        Master::getInstance().View.distance, Master::getInstance().View.distance,
                                        dir*180.f/M_PI);

                if(objectSlot[j].defaultOnCharacterNoWeaponHeightMapSprite.getTexture() && objectSlot[j].defaultOnCharacterNoWeaponHeightMapSprite.getTexture()->getSize().x)
                    Master::getInstance().spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterNoWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                        screen_x, screen_y,
                                        Master::getInstance().View.distance, Master::getInstance().View.distance,
                                        dir*180.f/M_PI);
            }
            else {
                _assert(type < (int)Master::getInstance().ObjectType.size(), "Slot object type out of bounds in renderCharacters.");

                if(!Master::getInstance().ObjectType[type].onCharacterNoWeaponColorMapSprite.getTexture()) continue;

                float screen_x = pos.x-Master::getInstance().ObjectType[type].onCharacterNoWeaponColorMapTexture.getSize().x/2.f*Master::getInstance().View.distance;
                float screen_y = pos.y-Master::getInstance().ObjectType[type].onCharacterNoWeaponColorMapTexture.getSize().y/2.f*Master::getInstance().View.distance;

                Master::getInstance().spriteDrawQueue.add(&Master::getInstance().ObjectType[type].onCharacterNoWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                    screen_x, screen_y,
                                    Master::getInstance().View.distance, Master::getInstance().View.distance,
                                    dir*180.f/M_PI);

                if(Master::getInstance().ObjectType[type].onCharacterNoWeaponNormalMapSprite.getTexture() && Master::getInstance().ObjectType[type].onCharacterNoWeaponNormalMapSprite.getTexture()->getSize().x)
                    Master::getInstance().spriteDrawQueue.add(&Master::getInstance().ObjectType[type].onCharacterNoWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                        screen_x, screen_y,
                                        Master::getInstance().View.distance, Master::getInstance().View.distance,
                                        dir*180.f/M_PI);

                if(Master::getInstance().ObjectType[type].onCharacterNoWeaponHeightMapSprite.getTexture() && Master::getInstance().ObjectType[type].onCharacterNoWeaponHeightMapSprite.getTexture()->getSize().x)
                    Master::getInstance().spriteDrawQueue.add(&Master::getInstance().ObjectType[type].onCharacterNoWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                        screen_x, screen_y,
                                        Master::getInstance().View.distance, Master::getInstance().View.distance,
                                        dir*180.f/M_PI);

                // ***
                /*
                float screen_w = ObjectType[type].on_character_sprite_no_weapon.Width()*View.distance;
                float screen_h = ObjectType[type].on_character_sprite_no_weapon.Height()*View.distance;
                float real_w = ObjectType[type].on_character_sprite_no_weapon.Width();
                float real_h = ObjectType[type].on_character_sprite_no_weapon.Height();
                blitTransformedShaded(ObjectType[type].on_character_sprite_no_weapon,
                                      screen_x, screen_y,
                                      screen_w, screen_h,
                                      real_x, real_y,
                                      real_w, real_h,
                                      dir);*/
            }
        }
    }
}

void Character::renderNameAndMessages() const
{
    if(isSeen) {
        vPoint pos = Master::getInstance().getScreenPosition(position.x, position.y, Master::getInstance().View);

        sf::Text text;

        text.setCharacterSize(11);
        text.setString(name);
        text.setColor(sf::Color::White);
        int nameTextX = int(pos.x-getTextWidth(text)/2.f*Master::getInstance().View.distance);
        int nameTextY = int(pos.y-text.getLocalBounds().height/2.f*Master::getInstance().View.distance-(CHARACTER_RADIUS+10)*Master::getInstance().View.distance);
        float nameTextWidth = getTextWidth(text);
        text.setPosition(nameTextX, nameTextY);
        window.draw(text);

        char health[100];
        sprintf(health, "%d / %d", param[CHARACTER_PARAM_HEALTH], param[CHARACTER_PARAM_MAX_HEALTH]);
        text.setCharacterSize(8);
        text.setString(health);
        text.setColor(sf::Color(220, 50, 50));
        text.setPosition(nameTextX+int((nameTextWidth-getTextWidth(text))/2.f),
                         nameTextY-int(10.f*Master::getInstance().View.distance));
        window.draw(text);

        text.setCharacterSize(11);
        int messageOffsetY = messageOverHead.size()*10;
        for(std::list <MessageOverHeadClass>::const_iterator it=messageOverHead.begin(); it!=messageOverHead.end(); ++it) {
            text.setString(it->message);
            text.setColor(sf::Color(230, 230, 230, (int)it->alpha));
            text.setPosition(nameTextX+int((nameTextWidth-getTextWidth(text))/2.f),
                             nameTextY-int(10.f*Master::getInstance().View.distance)-10-messageOffsetY);
            window.draw(text);
            messageOffsetY -= 10;
        }
    }
}

void Character::addMessageOverHead(const std::string &str)
{
    messageOverHead.push_back(MessageOverHeadClass(str));
}

float Character::getDistance(float x, float y)
{
    return sqrt((x-position.x)*(x-position.x)+(y-position.y)*(y-position.y));
}

float Character::getDistance(const CharacterClass &character)
{
    return sqrt((character.position.x-position.x)*(character.position.x-position.x)+
                (character.position.y-position.y)*(character.position.y-position.y));
}
