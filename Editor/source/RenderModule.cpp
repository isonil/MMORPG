#include "RenderModule.hpp"

/**
* @brief Displays weapon with addons.
*
* @param object Weapon object.
* @param screen_x X position on screen.
* @param screen_y Y position on screen.
* @param screen_w Width to which weapon sprite should be resized.
* @param screen_h Height to which weapon sprite should be resized.
* @param inScale Decides whether weapon sprite should be displayed in scale.
* @param useDrawQueue Decides whether sprites should be added to draw queue.
* @param alpha Alpha channel. Only available when drawing as interface.
*
* @todo Move to UtilityModule.
*/
void RenderModule::blitWeaponWithAddons(const ObjectClass &object, float screen_x, float screen_y, float screen_w, float screen_h, bool inScale, bool drawAsInterface, int alpha)
{
    _assert(object.type >= 0 && object.type < (int)ObjectType.size(), "Object type out of bounds in blitWeaponWithAddons.");
    _assert(ObjectType[object.type].colorMapSprite.getTexture() &&
            ObjectType[object.type].colorMapSprite.getTexture()->getSize().x &&
            ObjectType[object.type].colorMapSprite.getTexture()->getSize().y,
            "Weapon has no texture in blitWeaponWithAddons.");

    float new_screen_w = screen_w;
    float new_screen_h = screen_h;

    if(inScale) {
        new_screen_w *= ObjectType[object.type].spriteScale;
        new_screen_h *= ObjectType[object.type].spriteScale;
    }

    if(drawAsInterface) {
        ObjectType[object.type].colorMapSprite.setColor(sf::Color(255, 255, 255, alpha));
        ObjectType[object.type].colorMapSprite.setPosition(int(screen_x+(screen_w-new_screen_w)/2.f),
                                                           int(screen_y+(screen_h-new_screen_h)/2.f));
        ObjectType[object.type].colorMapSprite.setScale(new_screen_w/ObjectType[object.type].colorMapSprite.getTexture()->getSize().x,
                                                        new_screen_h/ObjectType[object.type].colorMapSprite.getTexture()->getSize().y);
        window.draw(ObjectType[object.type].colorMapSprite);
        ObjectType[object.type].colorMapSprite.setColor(sf::Color::White);
    }
    else {
        spriteDrawQueue.add(&ObjectType[object.type].colorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                            screen_x+(screen_w-new_screen_w)/2.f,
                            screen_y+(screen_h-new_screen_h)/2.f,
                            new_screen_w/ObjectType[object.type].colorMapSprite.getTexture()->getSize().x,
                            new_screen_h/ObjectType[object.type].colorMapSprite.getTexture()->getSize().y);

        if(ObjectType[object.type].normalMapSprite.getTexture() && ObjectType[object.type].normalMapSprite.getTexture()->getSize().x)
            spriteDrawQueue.add(&ObjectType[object.type].normalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                screen_x+(screen_w-new_screen_w)/2.f,
                                screen_y+(screen_h-new_screen_h)/2.f,
                                new_screen_w/ObjectType[object.type].normalMapSprite.getTexture()->getSize().x,
                                new_screen_h/ObjectType[object.type].normalMapSprite.getTexture()->getSize().y);

        if(ObjectType[object.type].heightMapSprite.getTexture() && ObjectType[object.type].heightMapSprite.getTexture()->getSize().x)
            spriteDrawQueue.add(&ObjectType[object.type].heightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                screen_x+(screen_w-new_screen_w)/2.f,
                                screen_y+(screen_h-new_screen_h)/2.f,
                                new_screen_w/ObjectType[object.type].heightMapSprite.getTexture()->getSize().x,
                                new_screen_h/ObjectType[object.type].heightMapSprite.getTexture()->getSize().y);
    }

    if(object.param[OBJECT_PARAM_ADDON_1] >= 0) {
        _assert(object.param[OBJECT_PARAM_ADDON_1] < (int)ObjectType.size(), "OBJECT_PARAM_ADDON_1 out of bounds in blitWeaponWithAddons.");
        _assert(ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite.getTexture() &&
                ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite.getTexture()->getSize().x &&
                ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite.getTexture()->getSize().y,
                "Weapon attachment 1 has no texture in blitWeaponWithAddons.");

        if(drawAsInterface) {
            ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite.setColor(sf::Color(255, 255, 255, alpha));
            ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite.setPosition(screen_x+(screen_w-new_screen_w)/2.f,
                                                                                              screen_y+(screen_h-new_screen_h)/2.f);
            ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite.setScale(new_screen_w/ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite.getTexture()->getSize().x,
                                                                                           new_screen_h/ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite.getTexture()->getSize().y);
            window.draw(ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite);
            ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite.setColor(sf::Color::White);
        }
        else {
            spriteDrawQueue.add(&ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                screen_x+(screen_w-new_screen_w)/2.f,
                                screen_y+(screen_h-new_screen_h)/2.f,
                                new_screen_w/ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite.getTexture()->getSize().x,
                                new_screen_h/ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponColorMapSprite.getTexture()->getSize().y);

            if(ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponNormalMapSprite.getTexture() && ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponNormalMapSprite.getTexture()->getSize().x)
                spriteDrawQueue.add(&ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                    screen_x+(screen_w-new_screen_w)/2.f,
                                    screen_y+(screen_h-new_screen_h)/2.f,
                                    new_screen_w/ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponNormalMapSprite.getTexture()->getSize().x,
                                    new_screen_h/ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponNormalMapSprite.getTexture()->getSize().y);

            if(ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponHeightMapSprite.getTexture() && ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponHeightMapSprite.getTexture()->getSize().x)
                spriteDrawQueue.add(&ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                    screen_x+(screen_w-new_screen_w)/2.f,
                                    screen_y+(screen_h-new_screen_h)/2.f,
                                    new_screen_w/ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponHeightMapSprite.getTexture()->getSize().x,
                                    new_screen_h/ObjectType[object.param[OBJECT_PARAM_ADDON_1]].onWeaponHeightMapSprite.getTexture()->getSize().y);
        }
    }
    if(object.param[OBJECT_PARAM_ADDON_2] >= 0) {
        _assert(object.param[OBJECT_PARAM_ADDON_2] < (int)ObjectType.size(), "OBJECT_PARAM_ADDON_2 out of bounds in blitWeaponWithAddons.");
        _assert(ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite.getTexture() &&
                ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite.getTexture()->getSize().x &&
                ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite.getTexture()->getSize().y,
                "Weapon attachment 2 has no texture in blitWeaponWithAddons.");

        if(drawAsInterface) {
            ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite.setColor(sf::Color(255, 255, 255, alpha));
            ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite.setPosition(screen_x+(screen_w-new_screen_w)/2.f,
                                                                                              screen_y+(screen_h-new_screen_h)/2.f);
            ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite.setScale(new_screen_w/ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite.getTexture()->getSize().x,
                                                                                           new_screen_h/ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite.getTexture()->getSize().y);
            window.draw(ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite);
            ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite.setColor(sf::Color::White);
        }
        else {
            spriteDrawQueue.add(&ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                screen_x+(screen_w-new_screen_w)/2.f,
                                screen_y+(screen_h-new_screen_h)/2.f,
                                new_screen_w/ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite.getTexture()->getSize().x,
                                new_screen_h/ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponColorMapSprite.getTexture()->getSize().y);

            if(ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponNormalMapSprite.getTexture() && ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponNormalMapSprite.getTexture()->getSize().x)
                spriteDrawQueue.add(&ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                    screen_x+(screen_w-new_screen_w)/2.f,
                                    screen_y+(screen_h-new_screen_h)/2.f,
                                    new_screen_w/ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponNormalMapSprite.getTexture()->getSize().x,
                                    new_screen_h/ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponNormalMapSprite.getTexture()->getSize().y);

            if(ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponHeightMapSprite.getTexture() && ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponHeightMapSprite.getTexture()->getSize().x)
                spriteDrawQueue.add(&ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                    screen_x+(screen_w-new_screen_w)/2.f,
                                    screen_y+(screen_h-new_screen_h)/2.f,
                                    new_screen_w/ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponHeightMapSprite.getTexture()->getSize().x,
                                    new_screen_h/ObjectType[object.param[OBJECT_PARAM_ADDON_2]].onWeaponHeightMapSprite.getTexture()->getSize().y);
        }
    }
    if(object.param[OBJECT_PARAM_ADDON_3] >= 0) {
        _assert(object.param[OBJECT_PARAM_ADDON_3] < (int)ObjectType.size(), "OBJECT_PARAM_ADDON_3 out of bounds in blitWeaponWithAddons.");
        _assert(ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite.getTexture() &&
                ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite.getTexture()->getSize().x &&
                ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite.getTexture()->getSize().y,
                "Weapon attachment 3 has no texture in blitWeaponWithAddons.");

        if(drawAsInterface) {
            ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite.setColor(sf::Color(255, 255, 255, alpha));
            ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite.setPosition(screen_x+(screen_w-new_screen_w)/2.f,
                                                                                              screen_y+(screen_h-new_screen_h)/2.f);
            ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite.setScale(new_screen_w/ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite.getTexture()->getSize().x,
                                                                                           new_screen_h/ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite.getTexture()->getSize().y);
            window.draw(ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite);
            ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite.setColor(sf::Color::White);
        }
        else {
            spriteDrawQueue.add(&ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                screen_x+(screen_w-new_screen_w)/2.f,
                                screen_y+(screen_h-new_screen_h)/2.f,
                                new_screen_w/ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite.getTexture()->getSize().x,
                                new_screen_h/ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponColorMapSprite.getTexture()->getSize().y);

            if(ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponNormalMapSprite.getTexture() && ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponNormalMapSprite.getTexture()->getSize().x)
                spriteDrawQueue.add(&ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                    screen_x+(screen_w-new_screen_w)/2.f,
                                    screen_y+(screen_h-new_screen_h)/2.f,
                                    new_screen_w/ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponNormalMapSprite.getTexture()->getSize().x,
                                    new_screen_h/ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponNormalMapSprite.getTexture()->getSize().y);

            if(ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponHeightMapSprite.getTexture() && ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponHeightMapSprite.getTexture()->getSize().x)
                spriteDrawQueue.add(&ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                    screen_x+(screen_w-new_screen_w)/2.f,
                                    screen_y+(screen_h-new_screen_h)/2.f,
                                    new_screen_w/ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponHeightMapSprite.getTexture()->getSize().x,
                                    new_screen_h/ObjectType[object.param[OBJECT_PARAM_ADDON_3]].onWeaponHeightMapSprite.getTexture()->getSize().y);
        }
    }
}

/**
* @brief Renders characters with their equipment and weapon.
* @param character Characters container.
*/
void RenderModule::renderCharacters(const std::vector <CharacterClass> &character, bool useNPCTypeSlots)
{
    spriteDrawQueue.clear();

    for(size_t i=0; i<character.size(); ++i) {
        vPoint pos = getScreenPosition(character[i].x, character[i].y, View);

        if(useNPCTypeSlots) _assert(character[i].NPCType >= 0 && character[i].NPCType < (int)NPCType.size(),
                                    "NPC type index out of bounds in renderCharacters.");

        int weaponType = character[i].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX].type;
        if(useNPCTypeSlots) weaponType = NPCType[character[i].NPCType].objectTypeOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX];

        if(weaponType >= 0) {
            _assert(weaponType < (int)ObjectType.size(), "Character weapon object type out of bounds in renderCharacters.");

            if(ObjectType[weaponType].weaponType == WEAPON_TYPE_SMALL_GUN) {
                for(size_t j=0; j<CHARACTER_OBJECT_SLOTS_QUANTITY; ++j) {
                    if(objectSlot[j].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;

                    int type = character[i].objectOnSlot[j].type;
                    if(useNPCTypeSlots) type = NPCType[character[i].NPCType].objectTypeOnSlot[j];

                    if(type < 0) {
                        if(!objectSlot[j].defaultOnCharacterSmallWeaponColorMapSprite.getTexture()) continue;

                        float screen_x = pos.x-objectSlot[j].defaultOnCharacterSmallWeaponColorMapSprite.getTexture()->getSize().x/2.f*View.distance;
                        float screen_y = pos.y-objectSlot[j].defaultOnCharacterSmallWeaponColorMapSprite.getTexture()->getSize().y/2.f*View.distance;

                        spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterSmallWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                            screen_x, screen_y,
                                            View.distance, View.distance,
                                            character[i].dir*180.f/M_PI);

                        if(objectSlot[j].defaultOnCharacterSmallWeaponNormalMapSprite.getTexture() && objectSlot[j].defaultOnCharacterSmallWeaponNormalMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterSmallWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                                screen_x, screen_y,
                                                View.distance, View.distance,
                                                character[i].dir*180.f/M_PI);

                        if(objectSlot[j].defaultOnCharacterSmallWeaponHeightMapSprite.getTexture() && objectSlot[j].defaultOnCharacterSmallWeaponHeightMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterSmallWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                                screen_x, screen_y,
                                                View.distance, View.distance,
                                                character[i].dir*180.f/M_PI);
                    }
                    else {
                        _assert(type < (int)ObjectType.size(), "Slot object type out of bounds in renderCharacters.");

                        if(!ObjectType[type].onCharacterSmallWeaponColorMapSprite.getTexture()) continue;

                        float screen_x = pos.x-ObjectType[type].onCharacterSmallWeaponColorMapTexture.getSize().x/2.f*View.distance;
                        float screen_y = pos.y-ObjectType[type].onCharacterSmallWeaponColorMapTexture.getSize().y/2.f*View.distance;

                        spriteDrawQueue.add(&ObjectType[type].onCharacterSmallWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                            screen_x, screen_y,
                                            View.distance, View.distance,
                                            character[i].dir*180.f/M_PI);

                        if(ObjectType[type].onCharacterSmallWeaponNormalMapSprite.getTexture() && ObjectType[type].onCharacterSmallWeaponNormalMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&ObjectType[type].onCharacterSmallWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                                screen_x, screen_y,
                                                View.distance, View.distance,
                                                character[i].dir*180.f/M_PI);

                        if(ObjectType[type].onCharacterSmallWeaponHeightMapSprite.getTexture() && ObjectType[type].onCharacterSmallWeaponHeightMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&ObjectType[type].onCharacterSmallWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                                screen_x, screen_y,
                                                View.distance, View.distance,
                                                character[i].dir*180.f/M_PI);
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
                                              character[i].dir);*/
                    }
                }
            }
            else if(ObjectType[weaponType].weaponType == WEAPON_TYPE_BIG_GUN ||
                    ObjectType[weaponType].weaponType == WEAPON_TYPE_ROCKET_LAUNCHER) {
                for(size_t j=0; j<CHARACTER_OBJECT_SLOTS_QUANTITY; ++j) {
                    if(objectSlot[j].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;

                    int type = character[i].objectOnSlot[j].type;
                    if(useNPCTypeSlots) type = NPCType[character[i].NPCType].objectTypeOnSlot[j];

                    if(type < 0) {
                        if(!objectSlot[j].defaultOnCharacterBigWeaponColorMapSprite.getTexture()) continue;

                        float screen_x = pos.x-objectSlot[j].defaultOnCharacterBigWeaponColorMapSprite.getTexture()->getSize().x/2.f*View.distance;
                        float screen_y = pos.y-objectSlot[j].defaultOnCharacterBigWeaponColorMapSprite.getTexture()->getSize().y/2.f*View.distance;

                        spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterBigWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                            screen_x, screen_y,
                                            View.distance, View.distance,
                                            character[i].dir*180.f/M_PI);

                        if(objectSlot[j].defaultOnCharacterBigWeaponNormalMapSprite.getTexture() && objectSlot[j].defaultOnCharacterBigWeaponNormalMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterBigWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                                screen_x, screen_y,
                                                View.distance, View.distance,
                                                character[i].dir*180.f/M_PI);

                        if(objectSlot[j].defaultOnCharacterBigWeaponHeightMapSprite.getTexture() && objectSlot[j].defaultOnCharacterBigWeaponHeightMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterBigWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                                screen_x, screen_y,
                                                View.distance, View.distance,
                                                character[i].dir*180.f/M_PI);
                    }
                    else {
                        _assert(type < (int)ObjectType.size(), "Slot object type out of bounds in renderCharacters.");

                        if(!ObjectType[type].onCharacterBigWeaponColorMapSprite.getTexture()) continue;

                        float screen_x = pos.x-ObjectType[type].onCharacterBigWeaponColorMapTexture.getSize().x/2.f*View.distance;
                        float screen_y = pos.y-ObjectType[type].onCharacterBigWeaponColorMapTexture.getSize().y/2.f*View.distance;

                        spriteDrawQueue.add(&ObjectType[type].onCharacterBigWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                            screen_x, screen_y,
                                            View.distance, View.distance,
                                            character[i].dir*180.f/M_PI);

                        if(ObjectType[type].onCharacterBigWeaponNormalMapSprite.getTexture() && ObjectType[type].onCharacterBigWeaponNormalMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&ObjectType[type].onCharacterBigWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                                screen_x, screen_y,
                                                View.distance, View.distance,
                                                character[i].dir*180.f/M_PI);

                        if(ObjectType[type].onCharacterBigWeaponHeightMapSprite.getTexture() && ObjectType[type].onCharacterBigWeaponHeightMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&ObjectType[type].onCharacterBigWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                                screen_x, screen_y,
                                                View.distance, View.distance,
                                                character[i].dir*180.f/M_PI);
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
                                              character[i].dir);*/
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
                                  character[i].dir);*/

            _assert(ObjectType[weaponType].onCharacterColorMapSprite.getTexture(), "Weapon sprite has no texture in renderCharacters.");

            float screen_x = pos.x-ObjectType[weaponType].onCharacterColorMapSprite.getTexture()->getSize().x/2.f*View.distance;
            float screen_y = pos.y-ObjectType[weaponType].onCharacterColorMapSprite.getTexture()->getSize().y/2.f*View.distance;

            spriteDrawQueue.add(&ObjectType[weaponType].onCharacterColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                screen_x, screen_y,
                                View.distance, View.distance,
                                character[i].dir*180.f/M_PI);

            if(ObjectType[weaponType].onCharacterNormalMapSprite.getTexture() && ObjectType[weaponType].onCharacterNormalMapSprite.getTexture()->getSize().x)
                spriteDrawQueue.add(&ObjectType[weaponType].onCharacterNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                    screen_x, screen_y,
                                    View.distance, View.distance,
                                    character[i].dir*180.f/M_PI);

            if(ObjectType[weaponType].onCharacterHeightMapSprite.getTexture() && ObjectType[weaponType].onCharacterHeightMapSprite.getTexture()->getSize().x)
                spriteDrawQueue.add(&ObjectType[weaponType].onCharacterHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                    screen_x, screen_y,
                                    View.distance, View.distance,
                                    character[i].dir*180.f/M_PI);
        }
        else {
            for(size_t j=0; j<CHARACTER_OBJECT_SLOTS_QUANTITY; ++j) {
                if(objectSlot[j].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;

                int type = character[i].objectOnSlot[j].type;
                if(useNPCTypeSlots) type = NPCType[character[i].NPCType].objectTypeOnSlot[j];

                if(type < 0) {
                    if(!objectSlot[j].defaultOnCharacterNoWeaponColorMapSprite.getTexture()) continue;

                    float screen_x = pos.x-objectSlot[j].defaultOnCharacterNoWeaponColorMapSprite.getTexture()->getSize().x/2.f*View.distance;
                    float screen_y = pos.y-objectSlot[j].defaultOnCharacterNoWeaponColorMapSprite.getTexture()->getSize().y/2.f*View.distance;

                    spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterNoWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                        screen_x, screen_y,
                                        View.distance, View.distance,
                                        character[i].dir*180.f/M_PI);

                    if(objectSlot[j].defaultOnCharacterNoWeaponNormalMapSprite.getTexture() && objectSlot[j].defaultOnCharacterNoWeaponNormalMapSprite.getTexture()->getSize().x)
                        spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterNoWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                            screen_x, screen_y,
                                            View.distance, View.distance,
                                            character[i].dir*180.f/M_PI);

                    if(objectSlot[j].defaultOnCharacterNoWeaponHeightMapSprite.getTexture() && objectSlot[j].defaultOnCharacterNoWeaponHeightMapSprite.getTexture()->getSize().x)
                        spriteDrawQueue.add(&objectSlot[j].defaultOnCharacterNoWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                            screen_x, screen_y,
                                            View.distance, View.distance,
                                            character[i].dir*180.f/M_PI);
                }
                else {
                    _assert(type < (int)ObjectType.size(), "Slot object type out of bounds in renderCharacters.");

                    if(!ObjectType[type].onCharacterNoWeaponColorMapSprite.getTexture()) continue;

                    float screen_x = pos.x-ObjectType[type].onCharacterNoWeaponColorMapTexture.getSize().x/2.f*View.distance;
                    float screen_y = pos.y-ObjectType[type].onCharacterNoWeaponColorMapTexture.getSize().y/2.f*View.distance;

                    spriteDrawQueue.add(&ObjectType[type].onCharacterNoWeaponColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                        screen_x, screen_y,
                                        View.distance, View.distance,
                                        character[i].dir*180.f/M_PI);

                    if(ObjectType[type].onCharacterNoWeaponNormalMapSprite.getTexture() && ObjectType[type].onCharacterNoWeaponNormalMapSprite.getTexture()->getSize().x)
                        spriteDrawQueue.add(&ObjectType[type].onCharacterNoWeaponNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                            screen_x, screen_y,
                                            View.distance, View.distance,
                                            character[i].dir*180.f/M_PI);

                    if(ObjectType[type].onCharacterNoWeaponHeightMapSprite.getTexture() && ObjectType[type].onCharacterNoWeaponHeightMapSprite.getTexture()->getSize().x)
                        spriteDrawQueue.add(&ObjectType[type].onCharacterNoWeaponHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                            screen_x, screen_y,
                                            View.distance, View.distance,
                                            character[i].dir*180.f/M_PI);
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
                                          character[i].dir);*/
                }
            }
        }
    }

    spriteDrawQueue.sort();
    spriteDrawQueue.draw();
}

/**
* @todo clean
*/
bool RenderModule::textureSplatting_isTileDifferent(int tileType1, int tileType2)
{
    if(tileType1 >= GRASS_TILE_TYPE_START && tileType1 <= GRASS_TILE_TYPE_END) tileType1 = GRASS_TILE_TYPE_START;
    if(tileType2 >= GRASS_TILE_TYPE_START && tileType2 <= GRASS_TILE_TYPE_END) tileType2 = GRASS_TILE_TYPE_START;
    return tileType1 != tileType2;
}

/**
* @brief Renders map first layer.
*/
void RenderModule::renderMapLayerOne()
{
    spriteDrawQueue.clear();

    vPoint pos1 = getWorldPosition(0.f, 0.f, View);
    vPoint pos2 = getWorldPosition(window.getSize().x/2.f, window.getSize().y/2.f, View);
    for(int i=int(pos1.y/TILE_SIZE-1); i<=int((2*pos2.y-pos1.y)/TILE_SIZE)+15; ++i) {
        for(int j=int((pos1.x)/TILE_SIZE-1); j<=int((2*pos2.x-pos1.x)/TILE_SIZE)+15; ++j) {
            vPoint pos = getScreenPosition(j*TILE_SIZE, i*TILE_SIZE, View);
            if(isOutOfMap(j, i)) continue;

            if(Tile[j][i].tileType < 0) {
                sf::RectangleShape shape(sf::Vector2f(TILE_SIZE*View.distance, TILE_SIZE*View.distance));
                shape.setPosition(pos.x, pos.y);
                shape.setFillColor(sf::Color(50, 50, 150));
                colorMapFBO.draw(shape);
            }
            else {
                _assert(Tile[j][i].tileType < (int)TileType.size(), "Tile type out of bounds in renderMapLayerOne.");
                _assert(TileType[Tile[j][i].tileType].widthQuantity > 0 &&
                        TileType[Tile[j][i].tileType].heightQuantity > 0,
                        "Tile size too small in renderMapLayerOne.");

                int wx = abs(j%TileType[Tile[j][i].tileType].widthQuantity);
                int wy = abs(i%TileType[Tile[j][i].tileType].heightQuantity);
                spriteDrawQueue.add(&TileType[Tile[j][i].tileType].colorMapSprite[wx][wy], SpriteDrawQueueClass::COLOR_MAP, false, pos.x, pos.y, View.distance, View.distance);
                if(TileType[Tile[j][i].tileType].normalMapSprite[wx][wy].getTexture() &&
                   TileType[Tile[j][i].tileType].normalMapSprite[wx][wy].getTexture()->getSize().x)
                    spriteDrawQueue.add(&TileType[Tile[j][i].tileType].normalMapSprite[wx][wy], SpriteDrawQueueClass::NORMAL_MAP, false, pos.x, pos.y, View.distance, View.distance);
            }
            if(Tile[j][i].sceneryType >= 0) {
                _assert(Tile[j][i].sceneryType < (int)SceneryType.size(), "Scenery type out of bounds in renderMapLayerOne.");
                if(SceneryType[Tile[j][i].sceneryType].layer == LAYER_ONE) {
                    float screen_x = pos.x-(SceneryType[Tile[j][i].sceneryType].colorMapTexture.getSize().x-TILE_SIZE)*View.distance+SceneryType[Tile[j][i].sceneryType].offsetX*View.distance;
                    float screen_y = pos.y-(SceneryType[Tile[j][i].sceneryType].colorMapTexture.getSize().y-TILE_SIZE)*View.distance+SceneryType[Tile[j][i].sceneryType].offsetY*View.distance;

                    if(SceneryType[Tile[j][i].sceneryType].natureType == NATURE_TYPE_WATER_FLOAT) {
                        float arc = randomArray[abs(i%10)][abs(j%10)]+globalTime/1000.f;
                        float moveX = cos(arc)*1.7f*View.distance;
                        float moveY = sin(arc)/1.9f*View.distance;
                        float dir = randomArray[abs(i%10)][abs(j%10)]+cos(arc/1.2f+randomArray[abs(i%10)][abs(j%10)])/6.f;

                        spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].colorMapSprite, SpriteDrawQueueClass::COLOR_MAP, false,
                                            screen_x+moveX, screen_y+moveY,
                                            View.distance, View.distance,
                                            dir*180.f/M_PI);
                        if(SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].normalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, false,
                                                screen_x+moveX, screen_y+moveY,
                                                View.distance, View.distance,
                                                dir*180.f/M_PI);
                        if(SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].heightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, false,
                                                screen_x+moveX, screen_y+moveY,
                                                View.distance, View.distance,
                                                dir*180.f/M_PI);
                    }
                    else if(SceneryType[Tile[j][i].sceneryType].natureType == NATURE_TYPE_WATER_FLOAT_STATIC) {
                        float arc = randomArray[abs(i%10)][abs(j%10)]+globalTime/1000.f;
                        float moveX = cos(arc)*1.7f*View.distance;
                        float moveY = sin(arc)/1.9f*View.distance;
                        float dir = cos(arc)/7.f;

                        spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].colorMapSprite, SpriteDrawQueueClass::COLOR_MAP, false,
                                            screen_x+moveX, screen_y+moveY,
                                            View.distance, View.distance,
                                            dir*180.f/M_PI);
                        if(SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].normalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, false,
                                                screen_x+moveX, screen_y+moveY,
                                                View.distance, View.distance,
                                                dir*180.f/M_PI);
                        if(SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].heightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, false,
                                                screen_x+moveX, screen_y+moveY,
                                                View.distance, View.distance,
                                                dir*180.f/M_PI);
                    }
                    else {
                        spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].colorMapSprite, SpriteDrawQueueClass::COLOR_MAP, false,
                                            screen_x, screen_y,
                                            View.distance, View.distance);
                        if(SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].normalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, false,
                                                screen_x, screen_y,
                                                View.distance, View.distance);
                        if(SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].heightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, false,
                                                screen_x, screen_y,
                                                View.distance, View.distance);
                    }
                }
            }
            for(std::list <ObjectClass>::iterator it=Tile[j][i].object.begin(); it!=Tile[j][i].object.end(); ++it) {
                _assert(it->type >= 0 && it->type < (int)ObjectType.size(), "Object type out of bounds in renderMapLayerOne.");
                if(ObjectType[it->type].layer == LAYER_ONE) {
                    _assert(ObjectType[it->type].colorMapSprite.getTexture(), "Object sprite has no texture in renderMapLayerOne.");

                    if(ObjectType[it->type].baseType == OBJECT_BASE_TYPE_WEAPON) {
                        blitWeaponWithAddons(*it,
                                             pos.x, pos.y,
                                             TILE_SIZE*View.distance,
                                             TILE_SIZE*View.distance,
                                             true,
                                             false);
                    }
                    else if(ObjectType[it->type].baseType == OBJECT_BASE_TYPE_STRUCTURE) {
                        float screen_x = pos.x-(ObjectType[it->type].colorMapSprite.getTexture()->getSize().x*ObjectType[it->type].spriteScale-TILE_SIZE)*View.distance;
                        float screen_y = pos.y-(ObjectType[it->type].colorMapSprite.getTexture()->getSize().y*ObjectType[it->type].spriteScale-TILE_SIZE)*View.distance;
                        float screen_w = ObjectType[it->type].colorMapSprite.getTexture()->getSize().x*ObjectType[it->type].spriteScale*View.distance;
                        float screen_h = ObjectType[it->type].colorMapSprite.getTexture()->getSize().y*ObjectType[it->type].spriteScale*View.distance;

                        spriteDrawQueue.add(&ObjectType[it->type].colorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                            screen_x, screen_y,
                                            screen_w/ObjectType[it->type].colorMapSprite.getTexture()->getSize().x,
                                            screen_h/ObjectType[it->type].colorMapSprite.getTexture()->getSize().y);

                        if(ObjectType[it->type].normalMapSprite.getTexture() && ObjectType[it->type].normalMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&ObjectType[it->type].normalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                                screen_x, screen_y,
                                                screen_w/ObjectType[it->type].normalMapSprite.getTexture()->getSize().x,
                                                screen_h/ObjectType[it->type].normalMapSprite.getTexture()->getSize().y);

                        if(ObjectType[it->type].heightMapSprite.getTexture() && ObjectType[it->type].heightMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&ObjectType[it->type].heightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                                screen_x, screen_y,
                                                screen_w/ObjectType[it->type].heightMapSprite.getTexture()->getSize().x,
                                                screen_h/ObjectType[it->type].heightMapSprite.getTexture()->getSize().y);
                    }
                    else {
                        float screen_w = TILE_SIZE*View.distance*ObjectType[it->type].spriteScale;
                        float screen_h = TILE_SIZE*View.distance*ObjectType[it->type].spriteScale;
                        float screen_x = pos.x+(TILE_SIZE*View.distance-screen_w)/2.f;
                        float screen_y = pos.y+(TILE_SIZE*View.distance-screen_h)/2.f;

                        spriteDrawQueue.add(&ObjectType[it->type].colorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                            screen_x, screen_y,
                                            screen_w/ObjectType[it->type].colorMapSprite.getTexture()->getSize().x,
                                            screen_h/ObjectType[it->type].colorMapSprite.getTexture()->getSize().y);

                        if(ObjectType[it->type].normalMapSprite.getTexture() && ObjectType[it->type].normalMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&ObjectType[it->type].normalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                                screen_x, screen_y,
                                                screen_w/ObjectType[it->type].normalMapSprite.getTexture()->getSize().x,
                                                screen_h/ObjectType[it->type].normalMapSprite.getTexture()->getSize().y);

                        if(ObjectType[it->type].heightMapSprite.getTexture() && ObjectType[it->type].heightMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&ObjectType[it->type].heightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                                screen_x, screen_y,
                                                screen_w/ObjectType[it->type].heightMapSprite.getTexture()->getSize().x,
                                                screen_h/ObjectType[it->type].heightMapSprite.getTexture()->getSize().y);
                    }
                }
            }
        }
    }

    spriteDrawQueue.sort();
    spriteDrawQueue.draw();
}

/**
* @brief deprecated
* @todo clean
*/
void RenderModule::renderMapShadows()
{
    vPoint pos1 = getWorldPosition(0.f, 0.f, View);
    vPoint pos2 = getWorldPosition(window.getSize().x/2.f, window.getSize().y/2, View);
    for(int i=int(pos1.y/TILE_SIZE-1); i<=int((2*pos2.y-pos1.y)/TILE_SIZE)+15; ++i) {
        for(int j=int((pos1.x)/TILE_SIZE-1); j<=int((2*pos2.x-pos1.x)/TILE_SIZE)+15; ++j) {
            if(isOutOfMap(j, i)) continue;

            vPoint pos = getScreenPosition(j*TILE_SIZE, i*TILE_SIZE, View);
            if(Tile[j][i].sceneryType >= 0) {
                _assert(Tile[j][i].sceneryType < (int)SceneryType.size(), "Scenery type out of bounds in renderMapShadows.");
                if(SceneryType[Tile[j][i].sceneryType].layer == LAYER_TWO || SceneryType[Tile[j][i].sceneryType].layer == LAYER_THREE) {
                    // ***
                    /*
                    float screen_x = pos.x-(SceneryType[Tile[j][i].sceneryType].sprite.Width()-TILE_SIZE)*View.distance;
                    float screen_y = pos.y-(SceneryType[Tile[j][i].sceneryType].sprite.Height()-TILE_SIZE)*View.distance;
                    float screen_w = SceneryType[Tile[j][i].sceneryType].sprite.Width()*View.distance;
                    float screen_h = SceneryType[Tile[j][i].sceneryType].sprite.Height()*View.distance;*/

                    /*float real_x=j*TILE_SIZE-SceneryType[Tile[j][i].sceneryType].sprite.Width()+TILE_SIZE;
                    float real_y=i*TILE_SIZE-SceneryType[Tile[j][i].sceneryType].sprite.Height()+TILE_SIZE;
                    float real_w=SceneryType[Tile[j][i].sceneryType].sprite.Width();
                    float real_h=SceneryType[Tile[j][i].sceneryType].sprite.Height();*/

                    // ***
                    /*
                    if(SceneryType[Tile[j][i].sceneryType].natureType == NATURE_TYPE_TREE) {
                        float arc = globalTime/1000.f;
                        float stretch = cos(arc)*5.f;
                        float move = cos(arc)*4.f;
                        float dir = randomArray[abs(i%10)][abs(j%10)]+cos(arc/1.9f+randomArray[abs(i%10)][abs(j%10)])/17.f;
                        SceneryType[Tile[j][i].sceneryType].sprite.BlitTransformed(screen_x+(move/3.5f+23.f)*View.distance,
                                                                                   screen_y+23.f*View.distance,
                                                                                   screen_w+stretch*View.distance,
                                                                                   screen_h,
                                                                                   dir, Tinted(Rgba::BLACK), 0.4f);
                    }
                    else if(SceneryType[Tile[j][i].sceneryType].natureType == NATURE_TYPE_FERN) {
                        for(int k=0; k<5; ++k) {
                            float arc = randomArray[abs((i+k)%10)][abs(j%10)]+globalTime/1000.f;
                            float stretch = cos(arc)*1.5f;
                            float dir = (360/5*k+randomArray[abs((i+k)%10)][abs(j%10)]%20-10)*M_PI/180.f+randomArray[abs(i%10)][abs(j%10)]+cos(arc+randomArray[abs(i%10)][abs(j%10)])/10.f;
                            SceneryType[Tile[j][i].sceneryType].sprite.BlitTransformed(screen_x+10.f*View.distance,
                                                                                       screen_y+10.f*View.distance,
                                                                                       screen_w+stretch*View.distance,
                                                                                       screen_h,
                                                                                       dir, Tinted(Rgba::BLACK), 0.4f);
                        }
                    }
                    else {

                    }*/
                }
            }
        }
    }
}

/**
* @brief Renders map second layer.
*/
void RenderModule::renderMapLayerTwo()
{
    spriteDrawQueue.clear();

    vPoint pos1 = getWorldPosition(0.f, 0.f, View);
    vPoint pos2 = getWorldPosition(window.getSize().x/2.f, window.getSize().y/2.f, View);
    for(int i=int(pos1.y/TILE_SIZE-1); i<=int((2*pos2.y-pos1.y)/TILE_SIZE)+15; ++i) {
        for(int j=int((pos1.x)/TILE_SIZE-1); j<=int((2*pos2.x-pos1.x)/TILE_SIZE)+15; ++j) {
            if(isOutOfMap(j, i)) continue;

            vPoint pos = getScreenPosition(j*TILE_SIZE, i*TILE_SIZE, View);
            if(Tile[j][i].sceneryType >= 0) {
                _assert(Tile[j][i].sceneryType < (int)SceneryType.size(), "Scenery type out of bounds in renderMapLayerTwo.");
                if(SceneryType[Tile[j][i].sceneryType].layer == LAYER_TWO) {
                    float screen_x = pos.x-(SceneryType[Tile[j][i].sceneryType].colorMapTexture.getSize().x-TILE_SIZE)*View.distance+SceneryType[Tile[j][i].sceneryType].offsetX*View.distance;
                    float screen_y = pos.y-(SceneryType[Tile[j][i].sceneryType].colorMapTexture.getSize().y-TILE_SIZE)*View.distance+SceneryType[Tile[j][i].sceneryType].offsetY*View.distance;
                    float real_w = SceneryType[Tile[j][i].sceneryType].colorMapTexture.getSize().x;
                    float screen_w = real_w*View.distance;

                    if(SceneryType[Tile[j][i].sceneryType].natureType == NATURE_TYPE_FERN) {
                        for(int k=0; k<5; ++k) {
                            float arc = randomArray[abs((i+k)%10)][abs(j%10)]+globalTime/1000.f;
                            float stretch = cos(arc)*1.5f*View.distance;
                            float dir = (360/5*k+randomArray[abs((i+k)%10)][abs(j%10)]%20-10)*M_PI/180.f+randomArray[abs(i%10)][abs(j%10)]+cos(arc+randomArray[abs(i%10)][abs(j%10)])/10.f;

                            spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].colorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                                screen_x, screen_y,
                                                (screen_w+stretch)/real_w, View.distance,
                                                dir*180.f/M_PI);
                            if(SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture() &&
                               SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture()->getSize().x)
                                spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].normalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                                    screen_x, screen_y,
                                                    (screen_w+stretch)/real_w, View.distance,
                                                    dir*180.f/M_PI);
                            if(SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture() &&
                               SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture()->getSize().x)
                                spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].heightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                                    screen_x, screen_y,
                                                    (screen_w+stretch)/real_w, View.distance,
                                                    dir*180.f/M_PI);
                        }
                    }
                    else {
                        spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].colorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                            screen_x, screen_y,
                                            View.distance, View.distance);
                        if(SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture()->getSize().x)
                                spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].normalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                                screen_x, screen_y,
                                                View.distance, View.distance);
                        if(SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].heightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                                screen_x, screen_y,
                                                View.distance, View.distance);

                        shadowCaster.resize(shadowCaster.size()+1);
                        shadowCaster.back().vertex.push_back(vPoint(pos.x, pos.y));
                        shadowCaster.back().vertex.push_back(vPoint(pos.x+TILE_SIZE*View.distance, pos.y));
                        shadowCaster.back().vertex.push_back(vPoint(pos.x+TILE_SIZE*View.distance, pos.y+TILE_SIZE*View.distance));
                        shadowCaster.back().vertex.push_back(vPoint(pos.x, pos.y+TILE_SIZE*View.distance));
                    }
                }
            }
            for(std::list <ObjectClass>::iterator it=Tile[j][i].object.begin(); it!=Tile[j][i].object.end(); ++it) {
                _assert(it->type >= 0 && it->type < (int)ObjectType.size(), "Object type out of bounds in renderMapLayerTwo.");
                if(ObjectType[it->type].layer == LAYER_TWO) {
                    _assert(ObjectType[it->type].colorMapSprite.getTexture(), "Object sprite has no texture in renderMapLayerTwo.");

                    float screen_x = pos.x-(ObjectType[it->type].colorMapSprite.getTexture()->getSize().x*ObjectType[it->type].spriteScale-TILE_SIZE)*View.distance+ObjectType[it->type].offsetX*View.distance;
                    float screen_y = pos.y-(ObjectType[it->type].colorMapSprite.getTexture()->getSize().y*ObjectType[it->type].spriteScale-TILE_SIZE)*View.distance+ObjectType[it->type].offsetY*View.distance;
                    float screen_w = ObjectType[it->type].colorMapSprite.getTexture()->getSize().x*ObjectType[it->type].spriteScale*View.distance;
                    float screen_h = ObjectType[it->type].colorMapSprite.getTexture()->getSize().y*ObjectType[it->type].spriteScale*View.distance;

                    spriteDrawQueue.add(&ObjectType[it->type].colorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                        screen_x, screen_y,
                                        screen_w/ObjectType[it->type].colorMapSprite.getTexture()->getSize().x,
                                        screen_h/ObjectType[it->type].colorMapSprite.getTexture()->getSize().y);

                    if(ObjectType[it->type].normalMapSprite.getTexture() && ObjectType[it->type].normalMapSprite.getTexture()->getSize().x)
                        spriteDrawQueue.add(&ObjectType[it->type].normalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                            screen_x, screen_y,
                                            screen_w/ObjectType[it->type].normalMapSprite.getTexture()->getSize().x,
                                            screen_h/ObjectType[it->type].normalMapSprite.getTexture()->getSize().y);

                    if(ObjectType[it->type].heightMapSprite.getTexture() && ObjectType[it->type].heightMapSprite.getTexture()->getSize().x)
                        spriteDrawQueue.add(&ObjectType[it->type].heightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                            screen_x, screen_y,
                                            screen_w/ObjectType[it->type].heightMapSprite.getTexture()->getSize().x,
                                            screen_h/ObjectType[it->type].heightMapSprite.getTexture()->getSize().y);

                    shadowCaster.resize(shadowCaster.size()+1);
                    shadowCaster.back().vertex.push_back(vPoint(pos.x, pos.y));
                    shadowCaster.back().vertex.push_back(vPoint(pos.x+TILE_SIZE*View.distance, pos.y));
                    shadowCaster.back().vertex.push_back(vPoint(pos.x+TILE_SIZE*View.distance, pos.y+TILE_SIZE*View.distance));
                    shadowCaster.back().vertex.push_back(vPoint(pos.x, pos.y+TILE_SIZE*View.distance));
                }
            }
        }
    }

    spriteDrawQueue.sort();
    spriteDrawQueue.draw();
}

/**
* @brief Renders map third layer.
*/
void RenderModule::renderMapLayerThree()
{
    spriteDrawQueue.clear();

    vPoint pos1 = getWorldPosition(0.f, 0.f, View);
    vPoint pos2 = getWorldPosition(window.getSize().x/2.f, window.getSize().y/2.f, View);
    for(int i=int(pos1.y/TILE_SIZE-1); i<=int((2*pos2.y-pos1.y)/TILE_SIZE)+15; ++i) {
        for(int j=int((pos1.x)/TILE_SIZE-1); j<=int((2*pos2.x-pos1.x)/TILE_SIZE)+15; ++j) {
            if(isOutOfMap(j, i)) continue;

            vPoint pos = getScreenPosition(j*TILE_SIZE, i*TILE_SIZE, View);
            if(Tile[j][i].sceneryType >= 0) {
                _assert(Tile[j][i].sceneryType < (int)SceneryType.size(), "Scenery type out of bounds in renderMapLayerThree.");
                if(SceneryType[Tile[j][i].sceneryType].layer == LAYER_THREE) {
                    float screen_x = pos.x-(SceneryType[Tile[j][i].sceneryType].colorMapTexture.getSize().x-TILE_SIZE)*View.distance+SceneryType[Tile[j][i].sceneryType].offsetX*View.distance;
                    float screen_y = pos.y-(SceneryType[Tile[j][i].sceneryType].colorMapTexture.getSize().y-TILE_SIZE)*View.distance+SceneryType[Tile[j][i].sceneryType].offsetY*View.distance;
                    float real_w = SceneryType[Tile[j][i].sceneryType].colorMapTexture.getSize().x;
                    float screen_w = real_w*View.distance;

                    if(SceneryType[Tile[j][i].sceneryType].natureType == NATURE_TYPE_TREE) {
                        float arc = globalTime/1500.f;
                        float stretch = cos(arc)*2.f*View.distance;
                        float move = cos(arc)*1.5f*View.distance;
                        float dir = randomArray[abs(i%10)][abs(j%10)]+cos(arc/2.5f+randomArray[abs(i%10)][abs(j%10)])/17.f;

                        spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].colorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                            screen_x+move, screen_y,
                                            (screen_w+stretch)/real_w, View.distance,
                                            dir*180.f/M_PI);
                        if(SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].normalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                                screen_x+move, screen_y,
                                                (screen_w+stretch)/real_w, View.distance,
                                                dir*180.f/M_PI);
                        if(SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].heightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                                screen_x+move, screen_y,
                                                (screen_w+stretch)/real_w, View.distance,
                                                dir*180.f/M_PI);
                    }
                    else {
                        spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].colorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                            screen_x, screen_y,
                                            View.distance, View.distance);
                        if(SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].normalMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].normalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                                screen_x, screen_y,
                                                View.distance, View.distance);
                        if(SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].heightMapSprite.getTexture()->getSize().x)
                            spriteDrawQueue.add(&SceneryType[Tile[j][i].sceneryType].heightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                                screen_x, screen_y,
                                                View.distance, View.distance);
                    }
                }
            }
        }
    }

    spriteDrawQueue.sort();
    spriteDrawQueue.draw();
}

/**
* @brief Renders all characters.
*/
void RenderModule::renderAllCharacters()
{
    renderCharacters(Player, false);
    renderCharacters(NPC, true);
}

void RenderModule::renderLights()
{
    for(size_t i=0; i<StaticLightSource.size(); ++i) {
        _assert(StaticLightSource[i].type >= 0 && StaticLightSource[i].type < (int)LightType.size(),
                "Light type index out of bounds in renderLights.");

        vPoint pos = getScreenPosition(StaticLightSource[i].x, StaticLightSource[i].y, View);
        //LightType[StaticLightSource[i].type].sprite.setPosition(sf::Vector2f(pos.x-lightTexture[StaticLightSource[i].textureIndex].getSize().x/2.f*View.distance,
        //                                                                     pos.y-lightTexture[StaticLightSource[i].textureIndex].getSize().y/2.f*View.distance));
        LightType[StaticLightSource[i].type].sprite.setPosition(sf::Vector2f(pos.x, pos.y));
        LightType[StaticLightSource[i].type].sprite.setOrigin(LightType[StaticLightSource[i].type].originX,
                                                              LightType[StaticLightSource[i].type].originY);
        LightType[StaticLightSource[i].type].sprite.setScale(View.distance, View.distance);
        LightType[StaticLightSource[i].type].sprite.setColor(sf::Color(255, 255, 255, 150));
        colorMapFBO.draw(LightType[StaticLightSource[i].type].sprite, addRenderState);
        LightType[StaticLightSource[i].type].sprite.setColor(sf::Color::White);
    }
    for(size_t i=0; i<StaticLightSource.size(); ++i) {
        vPoint pos = getScreenPosition(StaticLightSource[i].x, StaticLightSource[i].y, View);
        lightIconSprite.setPosition(sf::Vector2f(pos.x-lightIconTexture.getSize().x/2.f*View.distance,
                                                 pos.y-lightIconTexture.getSize().y/2.f*View.distance));
        lightIconSprite.setScale(View.distance, View.distance);
        lightIconSprite.setColor(sf::Color(255, 255, 255, 200));
        colorMapFBO.draw(lightIconSprite);
        lightIconSprite.setColor(sf::Color::White);
    }
}

void RenderModule::renderInterface()
{
    if(selectionEntityType == ENTITY_TYPE_SCENERY ||
       selectionEntityType == ENTITY_TYPE_OBJECT) {
        vPoint pos = getScreenPosition(selectionEntityX*TILE_SIZE, selectionEntityY*TILE_SIZE, View);
        sf::RectangleShape rect(sf::Vector2f(TILE_SIZE*View.distance, TILE_SIZE*View.distance));
        rect.setOutlineColor(sf::Color(100, 100, 255));
        rect.setOutlineThickness(2);
        rect.setFillColor(sf::Color::Transparent);
        rect.setPosition(pos.x, pos.y);
        colorMapFBO.draw(rect);
    }
    else if(selectionEntityType == ENTITY_TYPE_NPC) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)NPC.size(),
                "NPC index out of bounds in renderInterface.");

        vPoint pos = getScreenPosition(NPC[selectionEntityIndex].x, NPC[selectionEntityIndex].y, View);
        sf::RectangleShape rect(sf::Vector2f(2.f*CHARACTER_RADIUS*View.distance, 2.f*CHARACTER_RADIUS*View.distance));
        rect.setOutlineColor(sf::Color(100, 100, 255));
        rect.setOutlineThickness(2);
        rect.setFillColor(sf::Color::Transparent);
        rect.setPosition(pos.x-CHARACTER_RADIUS*View.distance, pos.y-CHARACTER_RADIUS*View.distance);
        colorMapFBO.draw(rect);

        if(!NPC[selectionEntityIndex].AI_movementCheckpoint.empty()) {
            vPoint firstCheckpointPos = getScreenPosition(NPC[selectionEntityIndex].AI_movementCheckpoint[0].x*TILE_SIZE+TILE_SIZE/2.f,
                                                          NPC[selectionEntityIndex].AI_movementCheckpoint[0].y*TILE_SIZE+TILE_SIZE/2.f, View);

            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(pos.x, pos.y);
            line[0].color = sf::Color(100, 100, 130, 250);
            line[1].position = sf::Vector2f(firstCheckpointPos.x, firstCheckpointPos.y);
            line[1].color = sf::Color(100, 100, 130, 250);
            colorMapFBO.draw(line);

            size_t size = NPC[selectionEntityIndex].AI_movementCheckpoint.size();

            vPoint *checkpointPos = new vPoint[size];
            checkpointPos[0] = firstCheckpointPos;
            for(size_t i=1; i<size; ++i) {
                checkpointPos[i] = getScreenPosition(NPC[selectionEntityIndex].AI_movementCheckpoint[i].x*TILE_SIZE+TILE_SIZE/2.f,
                                                     NPC[selectionEntityIndex].AI_movementCheckpoint[i].y*TILE_SIZE+TILE_SIZE/2.f, View);
            }

            for(size_t i=0; i<size; ++i) {
                sf::VertexArray line(sf::Lines, 2);
                line[0].position = sf::Vector2f(checkpointPos[i].x, checkpointPos[i].y);
                line[0].color = sf::Color(255, 255, 255, 170);
                line[1].position = sf::Vector2f(checkpointPos[(i+1)%size].x, checkpointPos[(i+1)%size].y);
                line[1].color = sf::Color(255, 255, 255, 170);
                colorMapFBO.draw(line);
            }

            for(size_t i=0; i<size; ++i) {
                sf::CircleShape marker(15.f*View.distance);
                marker.setPosition(checkpointPos[i].x-15.f*View.distance, checkpointPos[i].y-15.f*View.distance);
                marker.setFillColor(sf::Color(50, 200, 50));
                marker.setOutlineThickness(1);
                marker.setOutlineColor(sf::Color::White);
                colorMapFBO.draw(marker);

                sf::Text text;
                text.setString(intToString(i+1).c_str());
                text.setColor(sf::Color::Black);
                text.setCharacterSize(11);
                text.setPosition((int)checkpointPos[i].x-getTextWidth(text)/2, (int)checkpointPos[i].y-5);
                colorMapFBO.draw(text);
            }

            delete []checkpointPos;
        }
    }
    sf::Sprite minimapSprite(minimapTexture);
    minimapSprite.setPosition((float)window.getSize().x-180.f, (float)window.getSize().y-180.f);
    minimapSprite.setScale(180.f/(float)minimapTexture.getSize().x, 180.f/(float)minimapTexture.getSize().y);
    minimapSprite.setColor(sf::Color(255, 255, 255, 100));
    colorMapFBO.draw(minimapSprite);
    sf::RectangleShape rect(sf::Vector2f(5.f, 5.f));
    rect.setFillColor(sf::Color(0, 255, 0, 200));
    _assert(!Tile.empty() && !Tile[0].empty(), "Map is empty in renderInterface.");
    rect.setPosition((float)window.getSize().x-180.f+View.x*180.f/(Tile.size()*TILE_SIZE)-2.5f,
                     (float)window.getSize().y-180.f+View.y*180.f/(Tile[0].size()*TILE_SIZE)-2.5f);
    colorMapFBO.draw(rect);
}

void RenderModule::renderTileTypes(sf::RenderWindow &window)
{
    int num = 0;
    for(size_t i=0; i<TileType.size(); ++i) {
        if(!TileType[i].isLoaded) continue;

        if(TileType[i].colorMapTexture.size() &&
           TileType[i].colorMapTexture[0].size() &&
           TileType[i].colorMapTexture[0][0].getSize().x) {
            TileType[i].colorMapSprite[0][0].setPosition((num%3)*55, (num/3)*55);
            TileType[i].colorMapSprite[0][0].setScale(55.f/TileType[i].colorMapTexture[0][0].getSize().x, 55.f/TileType[i].colorMapTexture[0][0].getSize().y);
            window.draw(TileType[i].colorMapSprite[0][0]);
        }
        if(selectionEntityType == ENTITY_TYPE_TILE_TYPE && i == selectionEntityIndex) {
            sf::RectangleShape selection(sf::Vector2f(53.f, 53.f));
            selection.setPosition((num%3)*55+1, (num/3)*55+1);
            selection.setFillColor(sf::Color::Transparent);
            selection.setOutlineColor(sf::Color(51, 153, 255));
            selection.setOutlineThickness(1);
            window.draw(selection);
        }
        ++num;
    }
}

void RenderModule::renderSceneryTypes(sf::RenderWindow &window)
{
    int num = 0;
    for(size_t i=0; i<SceneryType.size(); ++i) {
        if(!SceneryType[i].isLoaded) continue;

        if(SceneryType[i].colorMapTexture.getSize().x) {
            SceneryType[i].colorMapSprite.setPosition((num%3)*55, (num/3)*55);
            SceneryType[i].colorMapSprite.setScale(55.f/SceneryType[i].colorMapTexture.getSize().x, 55.f/SceneryType[i].colorMapTexture.getSize().y);
            SceneryType[i].colorMapSprite.setRotation(0.f);
            SceneryType[i].colorMapSprite.setOrigin(0.f, 0.f);
            window.draw(SceneryType[i].colorMapSprite);
        }
        if(selectionEntityType == ENTITY_TYPE_SCENERY_TYPE && i == selectionEntityIndex) {
            sf::RectangleShape selection(sf::Vector2f(53.f, 53.f));
            selection.setPosition((num%3)*55+1, (num/3)*55+1);
            selection.setFillColor(sf::Color::Transparent);
            selection.setOutlineColor(sf::Color(51, 153, 255));
            selection.setOutlineThickness(1);
            window.draw(selection);
        }
        ++num;
    }
}

void RenderModule::renderObjectTypes(sf::RenderWindow &window)
{
    int num = 0;
    for(size_t i=0; i<ObjectType.size(); ++i) {
        if(!ObjectType[i].isLoaded) continue;

        if(ObjectType[i].colorMapTexture.getSize().x) {
            ObjectType[i].colorMapSprite.setPosition((num%3)*55, (num/3)*55);
            ObjectType[i].colorMapSprite.setScale(55.f/ObjectType[i].colorMapTexture.getSize().x, 55.f/ObjectType[i].colorMapTexture.getSize().y);
            ObjectType[i].colorMapSprite.setRotation(0.f);
            ObjectType[i].colorMapSprite.setOrigin(0.f, 0.f);
            window.draw(ObjectType[i].colorMapSprite);
        }
        if(selectionEntityType == ENTITY_TYPE_OBJECT_TYPE && i == selectionEntityIndex) {
            sf::RectangleShape selection(sf::Vector2f(53.f, 53.f));
            selection.setPosition((num%3)*55+1, (num/3)*55+1);
            selection.setFillColor(sf::Color::Transparent);
            selection.setOutlineColor(sf::Color(51, 153, 255));
            selection.setOutlineThickness(1);
            window.draw(selection);
        }
        ++num;
    }
}

void RenderModule::renderNPCTypes(sf::RenderWindow &window)
{
    int num = 0;
    for(size_t i=0; i<NPCType.size(); ++i) {
        if(!NPCType[i].isLoaded) continue;

        std::vector <std::string> word;
        std::string buff;
        for(size_t j=0; j<NPCType[i].name.size(); ++j) {
            if(NPCType[i].name[j] == ' ') {
                word.push_back(buff);
                buff.clear();
            }
            else buff += NPCType[i].name[j];
        }
        if(!buff.empty()) word.push_back(buff);

        for(size_t j=0; j<word.size(); ++j) {
            sf::Text text;
            text.setString(word[j].c_str());
            text.setCharacterSize(11);
            text.setPosition((num%3)*55+27-getTextWidth(text)/2, (num/3)*55+27-(int)word.size()*10/2+(int)j*10);
            text.setColor(sf::Color::Black);
            window.draw(text);
        }

        if(selectionEntityType == ENTITY_TYPE_NPC_TYPE && i == selectionEntityIndex) {
            sf::RectangleShape selection(sf::Vector2f(53.f, 53.f));
            selection.setPosition((num%3)*55+1, (num/3)*55+1);
            selection.setFillColor(sf::Color::Transparent);
            selection.setOutlineColor(sf::Color(51, 153, 255));
            selection.setOutlineThickness(1);
            window.draw(selection);
        }
        ++num;
    }
}

void RenderModule::renderLightSourceTypes(sf::RenderWindow &window)
{
    for(size_t i=0; i<LightType.size(); ++i) {
        LightType[i].sprite.setPosition((i%3)*55, (i/3)*55);
        LightType[i].sprite.setOrigin(0.f, 0.f);
        LightType[i].sprite.setScale(55.f/LightType[i].texture.getSize().x, 55.f/LightType[i].texture.getSize().y);
        window.draw(LightType[i].sprite);

        if(selectionEntityType == ENTITY_TYPE_LIGHT_SOURCE_TYPE && i == selectionEntityIndex) {
            sf::RectangleShape selection(sf::Vector2f(53.f, 53.f));
            selection.setPosition((i%3)*55+1, (i/3)*55+1);
            selection.setFillColor(sf::Color::Transparent);
            selection.setOutlineColor(sf::Color(51, 153, 255));
            selection.setOutlineThickness(1);
            window.draw(selection);
        }
    }
}

void RenderModule::renderTriggers(sf::RenderWindow &window)
{

}

void RenderModule::renderEffects(sf::RenderWindow &window)
{

}

void RenderModule::renderZoneTypes(sf::RenderWindow &window)
{

}
