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
* @brief Displays object description.
*
* Position is automatically aligned so it won't
* be displayed outside of the screen.
*
* Note that object description alpha channel is set
* via Interface.objectDescriptionAlpha.
*
* @param object Object which description should be displayed.
* @param x X position on screen for description to be displayed.
* @param y Y position on screen for description to be displayed.
*
* @todo Move to UtilityModule.
*/
void RenderModule::blitObjectDescription(const ObjectClass &object, int x, int y)
{
    if(object.type < 0) return;
    _assert(object.type < (int)ObjectType.size(), "Object type out of bounds in blitObjectDescription.");

    int w = 200, h = 0;
    if(ObjectType[object.type].baseType == OBJECT_BASE_TYPE_WEAPON) {
        h = 172;
        if(object.param[OBJECT_PARAM_ADDON_1] >= 0) h += 11;
        if(object.param[OBJECT_PARAM_ADDON_2] >= 0) h += 11;
        if(object.param[OBJECT_PARAM_ADDON_3] >= 0) h += 11;
    }
    else if(ObjectType[object.type].baseType == OBJECT_BASE_TYPE_EQUIPMENT) h = 133;
    else if(ObjectType[object.type].baseType == OBJECT_BASE_TYPE_ADDON) h = 144;
    else h = 122;

    if(x > (int)window.getSize().x-w) x = (int)window.getSize().x-w;
    if(y > (int)window.getSize().y-h) y = (int)window.getSize().y-h;

    sf::RectangleShape rect(sf::Vector2f(w, h));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color(80, 80, 80, int(Interface.objectDescriptionAlpha/2.5f)));
    rect.setOutlineColor(sf::Color(30, 30, 30, int(Interface.objectDescriptionAlpha/1.5f)));
    rect.setOutlineThickness(1);
    window.draw(rect);

    blitObjectDescriptionText(object, x+3, y+100, (int)Interface.objectDescriptionAlpha);

    if(ObjectType[object.type].baseType == OBJECT_BASE_TYPE_WEAPON) {
        blitWeaponWithAddons(object, x+50+3, y+3, 100, 100, true, true, (int)Interface.objectDescriptionAlpha);
    }
    else {
        float w = 100.f;
        float h = 100.f;
        float new_w = 100.f*ObjectType[object.type].spriteScale;
        float new_h = 100.f*ObjectType[object.type].spriteScale;

        sf::Sprite &spr = ObjectType[object.type].colorMapSprite;
        _assert(spr.getTexture() && spr.getTexture()->getSize().x && spr.getTexture()->getSize().y,
                "Object type has no texture in blitObjectDescription.");
        spr.setPosition(x+50+3+(w-new_w)/2.f, y+3+(h-new_h)/2.f);
        spr.setScale(new_w/spr.getTexture()->getSize().x,
                     new_h/spr.getTexture()->getSize().y);
        spr.setColor(sf::Color(255, 255, 255, (int)Interface.objectDescriptionAlpha));
        window.draw(spr);
        spr.setColor(sf::Color::White);
    }
}

/**
* @brief Displays object description text.
*
* @param object Object which description text should be displayed.
* @param x X position on screen for description text to be displayed.
* @param y Y position on screen for description text to be displayed.
* @param alpha Alpha channel for description text.
*
* @todo Move to UtilityModule.
*/
void RenderModule::blitObjectDescriptionText(const ObjectClass &object, int x, int y, int alpha)
{
    if(object.type < 0) return;
    _assert(object.type < (int)ObjectType.size(), "Object type out of bounds in blitObjectDescriptionText.");

    sf::Text text;
    text.setCharacterSize(11);
    char buff[300];

    int offsetY = 0;
    text.setColor(sf::Color(255, 255, 255, alpha));
    text.setString(ObjectType[object.type].name);
    text.setPosition(x, y+offsetY);
    window.draw(text);
    offsetY += 11;
    text.setString(getObjectBaseTypeName(ObjectType[object.type].baseType));
    text.setPosition(x, y+offsetY);
    window.draw(text);
    offsetY += 11;

    if(ObjectType[object.type].baseType == OBJECT_BASE_TYPE_WEAPON) {
        text.setString(getWeaponTypeName(ObjectType[object.type].weaponType));
        text.setPosition(x, y+offsetY);
        window.draw(text);
        offsetY += 11;
        text.setColor(sf::Color(255, 150, 150, alpha));
        if(ObjectType[object.type].isAutomatic) {
            text.setString("Automatic shot");
            text.setPosition(x, y+offsetY);
            window.draw(text);
        }
        else {
            text.setString("Single shot");
            text.setPosition(x, y+offsetY);
            window.draw(text);
        }
        offsetY += 11;
        text.setColor(sf::Color(255, 200, 150, alpha));

        sprintf(buff, "Damage: %d hp", ObjectType[object.type].baseDamage);
        text.setString(buff);
        text.setPosition(x, y+offsetY);
        window.draw(text);
        offsetY += 11;

        sprintf(buff, "Shot delay: %d ms", ObjectType[object.type].baseShotDelay);
        text.setString(buff);
        text.setPosition(x, y+offsetY);
        window.draw(text);
        offsetY += 11;

        text.setColor(sf::Color(150, 255, 150, alpha));
        if(object.param[OBJECT_PARAM_ADDON_1] >= 0) {
            _assert(object.param[OBJECT_PARAM_ADDON_1] < (int)ObjectType.size(), "OBJECT_PARAM_ADDON_1 out of bounds in blitObjectDescriptionText.");
            sprintf(buff, "Addon: %s", ObjectType[object.param[OBJECT_PARAM_ADDON_1]].name.c_str());
            text.setString(buff);
            text.setPosition(x, y+offsetY);
            window.draw(text);
            offsetY += 11;
        }
        if(object.param[OBJECT_PARAM_ADDON_2] >= 0) {
            _assert(object.param[OBJECT_PARAM_ADDON_2] < (int)ObjectType.size(), "OBJECT_PARAM_ADDON_2 out of bounds in blitObjectDescriptionText.");
            sprintf(buff, "Addon: %s", ObjectType[object.param[OBJECT_PARAM_ADDON_2]].name.c_str());
            text.setString(buff);
            text.setPosition(x, y+offsetY);
            window.draw(text);
            offsetY += 11;
        }
        if(object.param[OBJECT_PARAM_ADDON_3] >= 0) {
            _assert(object.param[OBJECT_PARAM_ADDON_3] < (int)ObjectType.size(), "OBJECT_PARAM_ADDON_3 out of bounds in blitObjectDescriptionText.");
            sprintf(buff, "Addon: %s", ObjectType[object.param[OBJECT_PARAM_ADDON_3]].name.c_str());
            text.setString(buff);
            text.setPosition(x, y+offsetY);
            window.draw(text);
            offsetY += 11;
        }
    }
    else if(ObjectType[object.type].baseType == OBJECT_BASE_TYPE_EQUIPMENT) {
        text.setColor(sf::Color(255, 255, 255, alpha));
        text.setString(getEquipmentTypeName(ObjectType[object.type].equipmentType));
        text.setPosition(x, y+offsetY);
        window.draw(text);
        offsetY += 11;
    }
    else if(ObjectType[object.type].baseType == OBJECT_BASE_TYPE_ADDON) {
        text.setColor(sf::Color(255, 255, 255, alpha));
        text.setString(getAttachmentTypeName(ObjectType[object.type].attachmentType));
        text.setPosition(x, y+offsetY);
        window.draw(text);
        offsetY += 11;

        sprintf(buff, "for: %s", getWeaponTypeName(ObjectType[object.type].weaponType).c_str());
        text.setString(buff);
        text.setPosition(x, y+offsetY);
        window.draw(text);
        offsetY += 11;
    }
}

void RenderModule::drawAmbientShadow(sf::Sprite &spr, const sf::Texture &tex, float shadowX, float shadowY, float scaleX, float scaleY, float shadowLength, bool fakeShadow, float fakeShadowDir)
{
    if(fakeShadow) {
        spr.setPosition(shadowX+cos(Weather.ambientShadowDir)*shadowLength*Weather.ambientShadowLength*View.distance,
                        shadowY+sin(Weather.ambientShadowDir)*shadowLength*Weather.ambientShadowLength*View.distance);
        spr.setScale(scaleX, scaleY);
        spr.setRotation(fakeShadowDir);
        spr.setOrigin(tex.getSize().x/2.f, tex.getSize().y/2.f);

        spr.setColor(sf::Color(0.f, 0.f, 0.f, 0.75f*Weather.ambientShadowAlpha));
        ambientShadowMapFBO.draw(spr);
        spr.setColor(sf::Color::White);
    }
    else {
        sf::Vector2f from(shadowX, shadowY);
        sf::Vector2f to(shadowX+cos(Weather.ambientShadowDir)*shadowLength*Weather.ambientShadowLength*View.distance,
                        shadowY+sin(Weather.ambientShadowDir)*shadowLength*Weather.ambientShadowLength*View.distance);
        spr.setOrigin(0.f, tex.getSize().y/2.f);
        spr.setPosition(from);
        float dir2 = atan2(to.y-from.y, to.x-from.x);
        spr.setRotation(dir2*180.f/M_PI);
        spr.setScale(getDistance(from.x, from.y, to.x, to.y)/(float)tex.getSize().x, View.distance);
        spr.setColor(sf::Color(255.f, 255.f, 255.f, 0.75f*Weather.ambientShadowAlpha));
        ambientShadowMapFBO.draw(spr);
        spr.setColor(sf::Color::White);
    }
}

/**
* @brief Renders characters with their equipment and weapon.
* @param character Characters container.
*/
void RenderModule::renderCharacters(const std::vector <CharacterClass> &character)
{
    for(size_t i=0; i<character.size(); ++i) {
        if(!character[i].isSeen) continue;
        vPoint pos = getScreenPosition(character[i].x, character[i].y, View);
        const ObjectClass *weapon = &character[i].objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX];

        if(weapon->type >= 0) {
            _assert(weapon->type < (int)ObjectType.size(), "Character weapon object type out of bounds in renderCharacters.");

            if(ObjectType[weapon->type].weaponType == WEAPON_TYPE_SMALL_GUN) {
                for(size_t j=0; j<CHARACTER_OBJECT_SLOTS_QUANTITY; ++j) {
                    if(objectSlot[j].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;

                    int type = character[i].objectOnSlot[j].type;
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
            else if(ObjectType[weapon->type].weaponType == WEAPON_TYPE_BIG_GUN ||
                    ObjectType[weapon->type].weaponType == WEAPON_TYPE_ROCKET_LAUNCHER) {
                for(size_t j=0; j<CHARACTER_OBJECT_SLOTS_QUANTITY; ++j) {
                    if(objectSlot[j].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;

                    int type = character[i].objectOnSlot[j].type;
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

            _assert(ObjectType[weapon->type].onCharacterColorMapSprite.getTexture(), "Weapon sprite has no texture in renderCharacters.");

            float screen_x = pos.x-ObjectType[weapon->type].onCharacterColorMapSprite.getTexture()->getSize().x/2.f*View.distance;
            float screen_y = pos.y-ObjectType[weapon->type].onCharacterColorMapSprite.getTexture()->getSize().y/2.f*View.distance;

            spriteDrawQueue.add(&ObjectType[weapon->type].onCharacterColorMapSprite, SpriteDrawQueueClass::COLOR_MAP, true,
                                screen_x, screen_y,
                                View.distance, View.distance,
                                character[i].dir*180.f/M_PI);

            if(ObjectType[weapon->type].onCharacterNormalMapSprite.getTexture() && ObjectType[weapon->type].onCharacterNormalMapSprite.getTexture()->getSize().x)
                spriteDrawQueue.add(&ObjectType[weapon->type].onCharacterNormalMapSprite, SpriteDrawQueueClass::NORMAL_MAP, true,
                                    screen_x, screen_y,
                                    View.distance, View.distance,
                                    character[i].dir*180.f/M_PI);

            if(ObjectType[weapon->type].onCharacterHeightMapSprite.getTexture() && ObjectType[weapon->type].onCharacterHeightMapSprite.getTexture()->getSize().x)
                spriteDrawQueue.add(&ObjectType[weapon->type].onCharacterHeightMapSprite, SpriteDrawQueueClass::HEIGHT_MAP, true,
                                    screen_x, screen_y,
                                    View.distance, View.distance,
                                    character[i].dir*180.f/M_PI);
        }
        else {
            for(size_t j=0; j<CHARACTER_OBJECT_SLOTS_QUANTITY; ++j) {
                if(objectSlot[j].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;

                int type = character[i].objectOnSlot[j].type;
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
}

/**
* @brief Renders character names and messages over head.
*/
void RenderModule::renderInterface_characterNamesAndMessages()
{
    for(size_t i=0; i<Player.size(); ++i) {
        if(Player[i].isSeen) {
            vPoint pos = getScreenPosition(Player[i].x, Player[i].y, View);

            sf::Text text;

            text.setCharacterSize(11);
            text.setString(Player[i].name);
            text.setColor(sf::Color::White);
            int nameTextX = int(pos.x-getTextWidth(text)/2.f*View.distance);
            int nameTextY = int(pos.y-text.getLocalBounds().height/2.f*View.distance-(CHARACTER_RADIUS+10)*View.distance);
            float nameTextWidth = getTextWidth(text);
            text.setPosition(nameTextX, nameTextY);
            window.draw(text);

            char health[100];
            sprintf(health, "%d / %d", Player[i].param[CHARACTER_PARAM_HEALTH], Player[i].param[CHARACTER_PARAM_MAX_HEALTH]);
            text.setCharacterSize(8);
            text.setString(health);
            text.setColor(sf::Color(220, 50, 50));
            text.setPosition(nameTextX+int((nameTextWidth-getTextWidth(text))/2.f),
                             nameTextY-int(10.f*View.distance));
            window.draw(text);

            text.setCharacterSize(11);
            int messageOffsetY = Player[i].messageOverHead.size()*10;
            for(std::list <MessageOverHeadClass>::iterator it=Player[i].messageOverHead.begin(); it!=Player[i].messageOverHead.end(); ++it) {
                text.setString(it->message);
                text.setColor(sf::Color(230, 230, 230, (int)it->alpha));
                text.setPosition(nameTextX+int((nameTextWidth-getTextWidth(text))/2.f),
                                 nameTextY-int(10.f*View.distance)-10-messageOffsetY);
                window.draw(text);
                messageOffsetY -= 10;
            }
        }
    }

    for(size_t i=0; i<NPC.size(); ++i) {
        if(NPC[i].isSeen) {
            vPoint pos = getScreenPosition(NPC[i].x, NPC[i].y, View);

            sf::Text text;

            text.setCharacterSize(11);
            text.setString(NPC[i].name);
            text.setColor(sf::Color(200, 200, 100));
            int nameTextX = int(pos.x-getTextWidth(text)/2.f*View.distance);
            int nameTextY = int(pos.y-text.getLocalBounds().height/2.f*View.distance-(CHARACTER_RADIUS+10)*View.distance);
            float nameTextWidth = getTextWidth(text);
            text.setPosition(nameTextX, nameTextY);
            window.draw(text);

            char health[100];
            sprintf(health, "%d / %d", NPC[i].param[CHARACTER_PARAM_HEALTH], NPC[i].param[CHARACTER_PARAM_MAX_HEALTH]);
            text.setCharacterSize(8);
            text.setString(health);
            text.setColor(sf::Color(220, 50, 50));
            text.setPosition(nameTextX+int((nameTextWidth-getTextWidth(text))/2.f),
                             nameTextY-int(10.f*View.distance));
            window.draw(text);
        }
    }
}

/**
* @brief Renders chat.
*/
void RenderModule::renderInterface_chat()
{
    for(size_t i=0; i<Interface.chatTab.size(); ++i) {
        if(Interface.chatTab[i].chat == Interface.currentChat) {
            Interface.chatTabSprite.setPosition(Interface.chatX+3+i*Interface.chatTabTexture.getSize().x,
                                                Interface.chatY);
            Interface.chatTabSprite.setScale(1.f, (Interface.chatTabTexture.getSize().y+1.f)/(float)Interface.chatTabTexture.getSize().y);
            Interface.chatTabSprite.setColor(sf::Color(255, 255, 255, (int)Interface.chatAlpha));
            window.draw(Interface.chatTabSprite);
        }
        else {
            Interface.chatTabSprite.setPosition(Interface.chatX+3+i*Interface.chatTabTexture.getSize().x,
                                                Interface.chatY);
            Interface.chatTabSprite.setScale(1.f, 1.f);
            Interface.chatTabSprite.setColor(sf::Color(150, 150, 150, (int)Interface.chatAlpha));
            window.draw(Interface.chatTabSprite);
        }

        sf::Text text;
        text.setCharacterSize(10);
        char label[15];
        label[0] = 0;
        if(Interface.chatTab[i].chat == CHAT_TAB_LOCAL) sprintf(label, "Local");
        else if(Interface.chatTab[i].chat == CHAT_TAB_GLOBAL) sprintf(label, "Global");
        else if(Interface.chatTab[i].chat >= 0 && Interface.chatTab[i].chat < (int)Player.size()) {
            if(Player[Interface.chatTab[i].chat].name.length() > 3) {
                sprintf(label, "%s..", Player[Interface.chatTab[i].chat].name.substr(0,3).c_str());
            }
            else sprintf(label, "%s", Player[Interface.chatTab[i].chat].name.c_str());
        }
        text.setString(label);
        if(Interface.chatTab[i].chat == Interface.currentChat)
            text.setColor(sf::Color(210, 210, 255, (int)Interface.chatAlpha));
        else if(Interface.chatTab[i].newMessage)
            text.setColor(sf::Color(255, 50, 50, (int)Interface.chatAlpha));
        else text.setColor(sf::Color(150, 150, 255, (int)Interface.chatAlpha));

        text.setPosition(Interface.chatX+3+i*Interface.chatTabTexture.getSize().x+3, Interface.chatY+2);
        window.draw(text);
    }

    Interface.chatWindowSprite.setPosition(Interface.chatX,
                                           Interface.chatY+(float)Interface.chatTabTexture.getSize().y-3.f);
    Interface.chatWindowSprite.setColor(sf::Color(255, 255, 255, (int)Interface.chatAlpha));
    window.draw(Interface.chatWindowSprite);

    Interface.chatEditBoxSprite.setPosition(Interface.chatX,
                                            Interface.chatY+Interface.chatTabTexture.getSize().y+Interface.chatWindowTexture.getSize().y-3);
    Interface.chatEditBoxSprite.setColor(sf::Color(255, 255, 255, (int)Interface.chatAlpha));
    window.draw(Interface.chatEditBoxSprite);

    if(Interface.currentChat == CHAT_TAB_LOCAL) {
        renderInterface_chatMessages(Interface.localChat);
    }
    else if(Interface.currentChat == CHAT_TAB_GLOBAL) {
        renderInterface_chatMessages(Interface.globalChat);
    }
    else if(Interface.currentChat >= 0) {
        _assert(Interface.currentChat < (int)Player.size(), "Private chat player index out of bounds in renderInterface_renderChat.");
        renderInterface_chatMessages(Player[Interface.currentChat].privateChat);
    }
}

/**
* @brief Renders chat messages in chat window.
* @param chat Chat messages container.
*/
void RenderModule::renderInterface_chatMessages(const std::vector <std::string> &chat)
{
    int startingLine = 0;
    if(Interface.chatStartingLine >= 0) startingLine = Interface.chatStartingLine;
    else startingLine = (int)chat.size()-CHAT_LINES_QUANTITY;
    if(startingLine < 0) startingLine = 0;

    sf::Text text;
    text.setColor(sf::Color(230, 230, 230, (int)Interface.chatAlpha));
    text.setCharacterSize(11);
    for(int i=startingLine; i<(int)chat.size(); ++i) {
        if(i-startingLine > CHAT_LINES_QUANTITY) break;
        text.setString(chat[i]);
        text.setPosition(Interface.chatX+6, Interface.chatY+Interface.chatTabTexture.getSize().y+5+(i-startingLine)*10-3);
        window.draw(text);
    }
}

/**
* @brief Renders status log messages.
*/
void RenderModule::renderInterface_statusLogMessages()
{
    sf::Text text;
    text.setCharacterSize(11);

    for(std::list <StatusLogMessageClass>::iterator it=Interface.statusLogMessage.begin(); it!=Interface.statusLogMessage.end(); ++it) {
        text.setColor(sf::Color(it->color.r, it->color.g, it->color.b, (int)it->alpha));
        text.setString(it->message);
        text.setPosition(int(Interface.chatWindowTexture.getSize().x+10.f+it->offsetX), (int)it->y);
        window.draw(text);
    }
}

/**
* @brief Renders player character interface and minimap.
*/
void RenderModule::renderInterface_playerCharacterInterfaceAndMinimap()
{
    int minimap_from_x = 0;
    int minimap_from_y = 0;

    sf::Text text;
    text.setCharacterSize(11);

    if(playerCharacterIndex >= 0) {
        char buf[200];
        sprintf(buf, "Time: %02d:%02d   Health: %d/%d   FPS %.0lf   PING: %d",
                int(Weather.dayTimeInMinutes/60.0),
                (int)Weather.dayTimeInMinutes%60,
                Player[playerCharacterIndex].param[CHARACTER_PARAM_HEALTH],
                Player[playerCharacterIndex].param[CHARACTER_PARAM_MAX_HEALTH],
                ol::FpsCounter::GetFps(),
                peer->lastRoundTripTime);

        text.setColor(sf::Color(255, 40, 40));
        text.setPosition(13, 4);
        text.setString(buf);
        window.draw(text);

        minimap_from_x = int(Player[playerCharacterIndex].x/TILE_SIZE)-60;
        minimap_from_y = int(Player[playerCharacterIndex].y/TILE_SIZE)-60;
        if(minimap_from_x < 0) minimap_from_x = 0;
        if(minimap_from_x > minimapTexture.getSize().x-120) minimap_from_x = minimapTexture.getSize().x-120;
        if(minimap_from_y < 0) minimap_from_y = 0;
        if(minimap_from_y > minimapTexture.getSize().y-120) minimap_from_y = minimapTexture.getSize().y-120;
    }
    else {

    }
    //minimapTexture.Blit(window.getSize().x-120-minimap_from_x, -minimap_from_y, Clipped(minimap_from_x, minimap_from_y, 120, 120));
}

/**
* @brief Renders dialogue.
*/
void RenderModule::renderInterface_dialogue()
{
    sf::ConvexShape rect;
    rect.setPointCount(4);
    rect.setPoint(0, sf::Vector2f((float)Interface.chatWindowTexture.getSize().x-3.f, (float)window.getSize().y-100.f));
    rect.setPoint(1, sf::Vector2f((float)window.getSize().x, (float)window.getSize().y-100.f));
    rect.setPoint(2, sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
    rect.setPoint(3, sf::Vector2f((float)Interface.chatWindowTexture.getSize().x-3.f, (float)window.getSize().y));
    rect.setFillColor(sf::Color(0, 0, 0, 180));

    sf::Text text;
    text.setCharacterSize(11);

    if(currentDialogueBlock.active) {
        window.draw(rect);

        text.setColor(sf::Color(180, 230, 180));
        if(currentDialogueBlock.NPCTextIndex >= 0) {
            _assert(currentDialogueBlock.NPCTextIndex < (int)Text.size(), "NPC text index out of bounds in renderInterface_renderDialogue.");
            text.setPosition(Interface.chatWindowTexture.getSize().x+50, window.getSize().y-90);
            text.setString(Text[currentDialogueBlock.NPCTextIndex]);
            window.draw(text);
        }

        int num = 0;
        for(size_t i=0; i<currentDialogueBlock.optionTextIndex.size(); ++i) {
            if(currentDialogueBlock.optionTextIndex[i] >= 0) {
                _assert(currentDialogueBlock.optionTextIndex[i] < (int)Text.size(), "Option text index out of bounds in renderInterface_renderDialogue.");

                if(mx >= Interface.chatWindowTexture.getSize().x+30 &&
                   my >= window.getSize().y-60+(num-1)*10 &&
                   my < window.getSize().y-60+num*10) text.setColor(sf::Color(180, 180, 230));
                else text.setColor(sf::Color(150, 150, 200));

                text.setPosition(Interface.chatWindowTexture.getSize().x+30, window.getSize().y-70+num*10);
                text.setString(Text[currentDialogueBlock.optionTextIndex[i]]);
                window.draw(text);
                ++num;
            }
        }
    }
}

/**
* @brief Renders interface windows.
*/
void RenderModule::renderInterface_windows(bool &mouseOverAnyWindow)
{
    sf::RectangleShape rect;
    sf::VertexArray line(sf::Lines, 2);

    sf::Text text;
    text.setCharacterSize(11);
    text.setColor(sf::Color(230, 230, 230));

    for(std::list <WindowClass>::reverse_iterator it=Interface.window.rbegin(); it!=Interface.window.rend(); ++it) {
        if(!it->visible) continue;

        rect.setSize(sf::Vector2f(it->w, 15));
        rect.setPosition(it->x, it->y);
        rect.setFillColor(sf::Color(70, 70, 70));
        window.draw(rect);
        rect.setSize(sf::Vector2f(it->w, it->h-15));
        rect.setPosition(it->x, it->y+15);
        rect.setFillColor(sf::Color(70, 70, 70, 140));
        window.draw(rect);

        if(it->closeButtonBeingPressed) {
            line[0].color = sf::Color(220, 220, 220);
            line[1].color = sf::Color(220, 220, 220);
            line[0].position = sf::Vector2f(it->x+it->w-12, it->y+3);
            line[1].position = sf::Vector2f(it->x+it->w-3, it->y+12);
            window.draw(line);
            line[0].position = sf::Vector2f(it->x+it->w-12, it->y+12);
            line[1].position = sf::Vector2f(it->x+it->w-3, it->y+3);
            window.draw(line);
        }
        else {
            line[0].color = sf::Color(160, 160, 160);
            line[1].color = sf::Color(160, 160, 160);
            line[0].position = sf::Vector2f(it->x+it->w-12, it->y+3);
            line[1].position = sf::Vector2f(it->x+it->w-3, it->y+12);
            window.draw(line);
            line[0].position = sf::Vector2f(it->x+it->w-12, it->y+12);
            line[1].position = sf::Vector2f(it->x+it->w-3, it->y+3);
            window.draw(line);
        }

        text.setString(it->title);
        text.setPosition(int(it->x+(it->w-getTextWidth(text))/2), it->y+1);
        window.draw(text);

        if(it->RenderCallback != NULL) (this->*(it->RenderCallback))(Interface, *it);
        if(mx >= it->x && mx <= it->x+it->w && my >= it->y && my <= it->y+it->h) mouseOverAnyWindow = true;
    }
}

/**
* @brief Renders short object description.
*/
void RenderModule::renderInterface_objectDescription(bool mouseOverAnyWindow)
{
    bool objectDescriptionShown = false;
    if(!mouseOverAnyWindow) {
        vPoint pos = getWorldPosition(mx,my,View);
        int tile_x = int(pos.x/TILE_SIZE);
        int tile_y = int(pos.y/TILE_SIZE);
        if(!isOutOfMap(tile_x, tile_y)) {
            if(!Tile[tile_x][tile_y].object.empty() && !automaticShooting) {
                blitObjectDescription(Tile[tile_x][tile_y].object.back(), mx, my);
                objectDescriptionShown = true;
            }
        }
    }
    else {
        if(Interface.inventoryMouseOverSlot >= 0 && Interface.inventoryMouseOverSlot < CHARACTER_OBJECT_SLOTS_QUANTITY) {
            if(Player[playerCharacterIndex].objectOnSlot[Interface.inventoryMouseOverSlot].type >= 0 && objectOnMouse.objectType < 0) {
                blitObjectDescription(Player[playerCharacterIndex].objectOnSlot[Interface.inventoryMouseOverSlot], mx, my);
                objectDescriptionShown = true;
            }
        }
        else if(Interface.inventoryMouseOverInvX >= 0 && Interface.inventoryMouseOverInvX < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
                Interface.inventoryMouseOverInvY >= 0 && Interface.inventoryMouseOverInvY < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT) {
                    if(Player[playerCharacterIndex].objectInInventory[Interface.inventoryMouseOverInvX][Interface.inventoryMouseOverInvY].type >= 0 &&
                       objectOnMouse.objectType < 0) {
                        blitObjectDescription(Player[playerCharacterIndex].objectInInventory[Interface.inventoryMouseOverInvX][Interface.inventoryMouseOverInvY],
                                              mx, my);
                        objectDescriptionShown = true;
                    }
        }
        else if(Interface.mouseOverWeaponAttachmentSlot >= 0 && Interface.mouseOverWeaponAttachmentSlot < WEAPON_ATTACHMENTS_QUANTITY) {
            ObjectClass *object = NULL;

            if(Interface.objectDescriptionSlot >= 0 && Interface.objectDescriptionSlot < CHARACTER_OBJECT_SLOTS_QUANTITY)
                object = &Player[playerCharacterIndex].objectOnSlot[Interface.objectDescriptionSlot];
            else if(Interface.objectDescriptionInvX >= 0 && Interface.objectDescriptionInvX < CHARACTER_INVENTORY_SLOTS_QUANTITY_WIDTH &&
                    Interface.objectDescriptionInvY >= 0 && Interface.objectDescriptionInvY < CHARACTER_INVENTORY_SLOTS_QUANTITY_HEIGHT)
                object = &Player[playerCharacterIndex].objectInInventory[Interface.objectDescriptionInvX][Interface.objectDescriptionInvY];

            if(object != NULL) {
                if(object->type >= 0) {
                    if(object->param[OBJECT_PARAM_ADDON_1+Interface.mouseOverWeaponAttachmentSlot] >= 0 && objectOnMouse.objectType < 0) {
                        blitObjectDescription(ObjectClass(object->param[OBJECT_PARAM_ADDON_1+Interface.mouseOverWeaponAttachmentSlot]),
                                              mx, my);
                        objectDescriptionShown = true;
                    }
                }
                else Interface.mouseOverWeaponAttachmentSlot = -1;
            }
            else Interface.mouseOverWeaponAttachmentSlot = -1;
        }
        else if(Interface.mouseOverTradeWithNPCObjectIndex >= 0 &&
                Interface.mouseOverTradeWithNPCObjectIndex < (int)currentTradeWithNPC.NPCObjectType.size()) {
            blitObjectDescription(ObjectClass(currentTradeWithNPC.NPCObjectType[Interface.mouseOverTradeWithNPCObjectIndex]),
                                  mx, my);
            objectDescriptionShown = true;
        }
    }

    if(objectDescriptionShown) {
        Interface.objectDescriptionAlpha += deltaTime*25.f;
        if(Interface.objectDescriptionAlpha > 255.f) Interface.objectDescriptionAlpha = 255.f;
    }
    else {
        Interface.objectDescriptionAlpha -= deltaTime*30.f;
        if(Interface.objectDescriptionAlpha < 0.f) Interface.objectDescriptionAlpha = 0.f;
    }
}

/**
* @brief Renders dynamic shadows for given light source.
*
* Full description in code.
*/
void RenderModule::renderLights_shadows(float screenX, float screenY)
{
    /*
                 5      6
                *      *
                *     *
               *     *        7
               1----2      *
               |    |   *
               4----3*


            X

          _____________________________________________________
          X - light source

          Rendering dynamic shadows is very simple. All we have
          to do is to find shadow polygon nodes for each shadow
          caster and render it as black color to shadow FBO.

          Our goal is to find polygon 1, 2, 3, 7, 6, 5.
    */

    vPoint lightPos(screenX, screenY);
    for(size_t i=0; i<shadowCaster.size(); ++i) {
        /*
            In the first step we need to find first node which
            will belong to shadow caster and our shadow polygon.
            (In example case it will be node 1, see picture.)

            We need to iterate through shadow caster nodes
            and find such node that our light source
            will be on the left side of line constructed by
            previous node and this node but on right side of
            line constructed by this node and the next one.
            (All shadow caster nodes are given clockwise.)
        */
        int vertex1Index = -1;
        for(size_t j=0; j<shadowCaster[i].vertex.size(); ++j) {
            if(lightPos.lineSide(shadowCaster[i].vertex[j], shadowCaster[i].vertex[(j+1)%shadowCaster[i].vertex.size()]) < 0.f &&
               lightPos.lineSide(shadowCaster[i].vertex[(j+1)%shadowCaster[i].vertex.size()], shadowCaster[i].vertex[(j+2)%shadowCaster[i].vertex.size()]) > 0.f) {
                vertex1Index = (j+1)%shadowCaster[i].vertex.size();
                break;
            }
        }
        if(vertex1Index < 0) continue;

        /*
            In next step we begin with the node we found in
            previous step and iterate through all shadow caster
            nodes untill we find the last node that belongs
            to shadow caster and our shadow polygon.
        */
        std::vector <vPoint> shadowPolygon;
        for(size_t j=vertex1Index; j<vertex1Index+shadowCaster[i].vertex.size(); ++j) {
            shadowPolygon.push_back(shadowCaster[i].vertex[j%shadowCaster[i].vertex.size()]);
            if(lightPos.lineSide(shadowCaster[i].vertex[j%shadowCaster[i].vertex.size()], shadowCaster[i].vertex[(j+1)%shadowCaster[i].vertex.size()]) > 0.f &&
               lightPos.lineSide(shadowCaster[i].vertex[(j+1)%shadowCaster[i].vertex.size()], shadowCaster[i].vertex[(j+2)%shadowCaster[i].vertex.size()]) < 0.f) {
                shadowPolygon.push_back(shadowCaster[i].vertex[(j+1)%shadowCaster[i].vertex.size()]);
                break;
            }
        }

        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setFillColor(sf::Color::Black);

        /*
            In final step for each node already found
            we need to find further node corresponding
            to it. (For example 1->5, see picture.)
            And then draw triangles to fill whole shadow
            polygon.
        */
        size_t quantity = shadowPolygon.size();
        if(quantity < 2) continue;
        for(size_t j=0; j<quantity; ++j) {
            if(j > 0) {
                triangle.setPoint(0, sf::Vector2f(shadowPolygon[j-1].x, shadowPolygon[j-1].y));
                triangle.setPoint(1, sf::Vector2f(shadowPolygon[j].x, shadowPolygon[j].y));

                vPoint newVertex = shadowPolygon[j]-lightPos;
                newVertex.normalize();
                newVertex = shadowPolygon[j]+newVertex*2000.f;
                shadowPolygon.push_back(newVertex);

                triangle.setPoint(2, sf::Vector2f(newVertex.x, newVertex.y));
                shadowMapFBO.draw(triangle);
            }
            if(j < quantity-1) {
                triangle.setPoint(0, sf::Vector2f(shadowPolygon[j].x, shadowPolygon[j].y));

                vPoint newVertex = shadowPolygon[j]-lightPos;
                newVertex.normalize();
                newVertex = shadowPolygon[j]+newVertex*2000.f;
                shadowPolygon.push_back(newVertex);

                triangle.setPoint(1, sf::Vector2f(newVertex.x, newVertex.y));

                newVertex = shadowPolygon[j+1]-lightPos;
                newVertex.normalize();
                newVertex = shadowPolygon[j+1]+newVertex*2000.f;
                shadowPolygon.push_back(newVertex);

                triangle.setPoint(2, sf::Vector2f(newVertex.x, newVertex.y));
                shadowMapFBO.draw(triangle);
            }
        }

        sf::VertexArray penumbra(sf::Triangles, 3);
        penumbra[0].position = sf::Vector2f(shadowPolygon[0].x, shadowPolygon[0].y);
        penumbra[1].position = sf::Vector2f(shadowPolygon[quantity].x, shadowPolygon[quantity].y);

        vPoint newVertex = vPoint(shadowPolygon[quantity].x, shadowPolygon[quantity].y)-vPoint(shadowPolygon[0].x, shadowPolygon[0].y);
        newVertex = vPoint(-newVertex.y, newVertex.x);
        newVertex.normalize();
        newVertex = lightPos+newVertex*10.f;
        newVertex = vPoint(shadowPolygon[0].x, shadowPolygon[0].y)-newVertex;
        newVertex.normalize();
        newVertex = vPoint(shadowPolygon[0].x, shadowPolygon[0].y)+newVertex*2000.f;

        penumbra[2].position = sf::Vector2f(newVertex.x, newVertex.y);

        penumbra[0].texCoords = sf::Vector2f(0, penumbraTexture.getSize().y);
        penumbra[1].texCoords = sf::Vector2f(penumbraTexture.getSize().x, 0);
        penumbra[2].texCoords = sf::Vector2f(0, 0);

        shadowMapFBO.draw(penumbra, &penumbraTexture);

        penumbra[0].position = sf::Vector2f(shadowPolygon[quantity-1].x, shadowPolygon[quantity-1].y);
        penumbra[1].position = sf::Vector2f(shadowPolygon.back().x, shadowPolygon.back().y);

        newVertex = vPoint(shadowPolygon.back().x, shadowPolygon.back().y)-vPoint(shadowPolygon[quantity-1].x, shadowPolygon[quantity-1].y);
        newVertex = vPoint(newVertex.y, -newVertex.x);
        newVertex.normalize();
        newVertex = lightPos+newVertex*30.f;
        newVertex = vPoint(shadowPolygon[quantity-1].x, shadowPolygon[quantity-1].y)-newVertex;
        newVertex.normalize();
        newVertex = vPoint(shadowPolygon[quantity-1].x, shadowPolygon[quantity-1].y)+newVertex*2000.f;

        penumbra[2].position = sf::Vector2f(newVertex.x, newVertex.y);

        penumbra[0].texCoords = sf::Vector2f(0, penumbraTexture.getSize().y);
        penumbra[1].texCoords = sf::Vector2f(penumbraTexture.getSize().x, 0);
        penumbra[2].texCoords = sf::Vector2f(0, 0);

        shadowMapFBO.draw(penumbra, &penumbraTexture);
    }
}

/**
* @todo clean
*/
float RenderModule::getLightIntensity(float x, float y)
{
    float intensity = 0.f;
    for(size_t i=0; i<LightSource.size(); ++i) {
        float dist = getDistance(LightSource[i].x, LightSource[i].y, x, y);
        float tempIntensity = 0.f;//(-255*dist)/LightSource[i].intensity+255.f;
        if(tempIntensity > intensity) intensity = tempIntensity;
    }
    return intensity;
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
    vPoint pos1 = getWorldPosition(0.f, 0.f, View);
    vPoint pos2 = getWorldPosition(window.getSize().x/2.f, window.getSize().y/2.f, View);
    for(int i=int(pos1.y/TILE_SIZE-1); i<=int((2*pos2.y-pos1.y)/TILE_SIZE)+15; ++i) {
        for(int j=int((pos1.x)/TILE_SIZE-1); j<=int((2*pos2.x-pos1.x)/TILE_SIZE)+15; ++j) {
            vPoint pos = getScreenPosition(j*TILE_SIZE, i*TILE_SIZE, View);
            if(isOutOfMap(j, i)) continue;

            if(Tile[j][i].tileType < 0) {
                if(!isOutOfMap(j-1, i-1) && !isOutOfMap(j+1, i+1)) {
                waterSprite.setPosition(pos.x, pos.y);
                    waterSprite.setScale(TILE_SIZE*View.distance/(float)waterColorMapTexture.getSize().x,
                                         TILE_SIZE*View.distance/(float)waterColorMapTexture.getSize().y);

                    waterShader.setParameter("waterColorMapTexture", waterColorMapTexture);
                    waterShader.setParameter("waterNormalMapTexture", waterNormalMapTexture);
                    waterShader.setParameter("waterNoiseTexture", waterNoiseTexture);
                    waterShader.setParameter("skyTexture", skyTexture);
                    waterShader.setParameter("time", globalTime/1000.f);
                    waterShader.setParameter("tileX", float(j%5));
                    waterShader.setParameter("tileY", float(i%5));
                    waterShader.setParameter("tileCornerRealPos", j*TILE_SIZE, i*TILE_SIZE);
                    waterShader.setParameter("tileSize", TILE_SIZE);
                    if(Tile[j-1][i-1].tileType >= 0) waterShader.setParameter("texUpLeft", 1.f);
                    else waterShader.setParameter("texUpLeft", 0.f);
                    if(Tile[j][i-1].tileType >= 0) waterShader.setParameter("texUp", 1.f);
                    else waterShader.setParameter("texUp", 0.f);
                    if(Tile[j+1][i-1].tileType >= 0) waterShader.setParameter("texUpRight", 1.f);
                    else waterShader.setParameter("texUpRight", 0.f);
                    if(Tile[j+1][i].tileType >= 0) waterShader.setParameter("texRight", 1.f);
                    else waterShader.setParameter("texRight", 0.f);
                    if(Tile[j+1][i+1].tileType >= 0) waterShader.setParameter("texDownRight", 1.f);
                    else waterShader.setParameter("texDownRight", 0.f);
                    if(Tile[j][i+1].tileType >= 0) waterShader.setParameter("texDown", 1.f);
                    else waterShader.setParameter("texDown", 0.f);
                    if(Tile[j-1][i+1].tileType >= 0) waterShader.setParameter("texDownLeft", 1.f);
                    else waterShader.setParameter("texDownLeft", 0.f);
                    if(Tile[j-1][i].tileType >= 0) waterShader.setParameter("texLeft", 1.f);
                    else waterShader.setParameter("texLeft", 0.f);
                    waterShader.setParameter("textureSplattingTexture", TileType[0].colorMapTexture[0][0]);
                    waterShader.setParameter("x", pos.x/window.getSize().x);
                    waterShader.setParameter("y", pos.y/window.getSize().y);

                    colorMapFBO.draw(waterSprite, &waterShader);
                }
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
    ambientShadowMapFBO.clear(sf::Color(0, 0, 0, 0));

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

                            /*drawAmbientShadow(SceneryType[Tile[j][i].sceneryType].colorMapSprite,
                                              SceneryType[Tile[j][i].sceneryType].colorMapTexture,
                                              screen_x, screen_y,
                                              (screen_w+stretch)/real_w, View.distance,
                                              dir*180.f/M_PI, 6.f);*/
                            drawAmbientShadow(SceneryType[Tile[j][i].sceneryType].colorMapSprite,
                                              SceneryType[Tile[j][i].sceneryType].colorMapTexture,
                                              screen_x+SceneryType[Tile[j][i].sceneryType].colorMapTexture.getSize().x/2.f*View.distance,
                                              screen_y+SceneryType[Tile[j][i].sceneryType].colorMapTexture.getSize().y/2.f*View.distance,
                                              (screen_w+stretch)/real_w, View.distance,
                                              20.f, true, dir*180.f/M_PI);

                            if(!sf::Mouse::isButtonPressed(sf::Mouse::Right))
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

    ambientShadowMapFBO.display();
    sf::Sprite ambientShadow(ambientShadowMapFBO.getTexture());
    ambientShadow.setColor(sf::Color(255, 255, 255, 200));
    colorMapFBO.draw(ambientShadow);

    spriteDrawQueue.sort();
    spriteDrawQueue.draw();
}

/**
* @brief Renders map third layer.
*/
void RenderModule::renderMapLayerThree()
{
    spriteDrawQueue.clear();
    ambientShadowMapFBO.clear(sf::Color(0, 0, 0, 0));

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
                        float arc = globalTime/1000.f;
                        float stretch = cos(arc)*4.f*View.distance;
                        float move = cos(arc)*4.f*View.distance;
                        float dir = randomArray[abs(i%10)][abs(j%10)]+cos(arc/2.5f+randomArray[abs(i%10)][abs(j%10)])/17.f;

                        if(SceneryType[Tile[j][i].sceneryType].shadowSprite.getTexture() &&
                           SceneryType[Tile[j][i].sceneryType].shadowSprite.getTexture()->getSize().x)
                            drawAmbientShadow(SceneryType[Tile[j][i].sceneryType].shadowSprite,
                                              SceneryType[Tile[j][i].sceneryType].shadowTexture,
                                              screen_x+move+SceneryType[Tile[j][i].sceneryType].colorMapTexture.getSize().x/2.f*View.distance,
                                              screen_y+SceneryType[Tile[j][i].sceneryType].colorMapTexture.getSize().y/2.f*View.distance,
                                              (screen_w+stretch)/real_w, View.distance,
                                              500.f, false, 0.f);

                        if(!sf::Mouse::isButtonPressed(sf::Mouse::Right))
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

    ambientShadowMapFBO.display();
    sf::Sprite ambientShadow(ambientShadowMapFBO.getTexture());
    ambientShadow.setColor(sf::Color(255, 255, 255, 200));
    colorMapFBO.draw(ambientShadow);

    spriteDrawQueue.sort();
    spriteDrawQueue.draw();
}

/**
* @brief Renders all characters.
*/
void RenderModule::renderAllCharacters()
{
    renderCharacters(Player);
    renderCharacters(NPC);
}

/**
* @brief Renders projectiles.
*/
void RenderModule::renderProjectiles()
{
    for(std::list <ProjectileClass>::const_iterator it=Projectile.begin(); it!=Projectile.end();) {
        std::list <ProjectileClass>::const_iterator projectile = it;
        ++it;

        vPoint pos1 = getScreenPosition(projectile->trailX, projectile->trailY, View);
        vPoint pos2 = getScreenPosition(projectile->x, projectile->y, View);

        if(projectile->projectileType == PROJECTILE_TYPE_MISSILE) {
            // ***
            /*
            missileTexture.BlitTransformed(pos2.x, pos2.y,
                                          missileTexture.Width()*View.distance,
                                          missileTexture.Height()*View.distance,
                                          projectile->dir);*/
        }
        else if(projectile->projectileType == PROJECTILE_TYPE_GRENADE_LAUNCHER_GRENADE) {
            // ***
            /*
            grenadeLauncherGrenadeTexture.BlitTransformed(pos2.x, pos2.y,
                                                         grenadeLauncherGrenadeTexture.Width()*View.distance,
                                                         grenadeLauncherGrenadeTexture.Height()*View.distance,
                                                         projectile->dir);*/
        }
        else if(projectile->projectileType == PROJECTILE_TYPE_GRENADE) {
            // ***
            /*
            grenadeTexture.BlitTransformed(pos2.x, pos2.y,
                                          grenadeTexture.Width()*View.distance,
                                          grenadeTexture.Height()*View.distance,
                                          projectile->grenadeRotation);*/
        }
        else {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(pos1.x, pos1.y);
            line[0].color = sf::Color(255, 255, 255, 50);
            line[1].position = sf::Vector2f(pos2.x, pos2.y);
            line[1].color = sf::Color(255, 255, 255, 255);
            colorMapFBO.draw(line);
        }
    }
}

/**
* @brief Renders particles.
*/
void RenderModule::renderParticles()
{
    for(std::list <ParticleClass>::const_iterator it=Particle.begin(); it!=Particle.end(); ++it) {
        if(it->drawOnTop) continue;
        _assert(it->textureIndex >= 0 && it->textureIndex < PARTICLE_TEXTURES_QUANTITY,
                "Particle sprite index out of bounds in renderParticles.");

        vPoint pos = getScreenPosition(it->x, it->y, View);
        /*float screen_x = pos.x;
        float screen_y = pos.y;
        float screen_w = particleTexture[it->spriteIndex].getSize().x*View.distance;
        float screen_h = particleTexture[it->spriteIndex].getSize().y*View.distance;
        float real_x = it->x;
        float real_y = it->y;
        float real_w = particleTexture[it->spriteIndex].getSize().x;
        float real_h = particleTexture[it->spriteIndex].getSize().y;*/
        particleSprite[it->textureIndex].setPosition(pos.x-particleSprite[it->textureIndex].getTexture()->getSize().x/2.f,
                                                    pos.y-particleSprite[it->textureIndex].getTexture()->getSize().y/2.f);
        particleSprite[it->textureIndex].setScale(View.distance, View.distance);
        particleSprite[it->textureIndex].setColor(sf::Color(it->color.r, it->color.g, it->color.b, (int)it->alpha));
        if(it->additiveBlending) colorMapFBO.draw(particleSprite[it->textureIndex], addRenderState);
        else colorMapFBO.draw(particleSprite[it->textureIndex]);
        // ***
        /*
        blitTransformedShaded(ParticleSprite[it->spriteIndex],
                              screen_x, screen_y,
                              screen_w, screen_h,
                              real_x, real_y,
                              real_w, real_h,
                              it->rotation, true,
                              it->color, it->alpha/255.f);*/
    }
    for(std::list <ParticleClass>::const_iterator it=Particle.begin(); it!=Particle.end(); ++it) {
        if(!it->drawOnTop) continue;
        _assert(it->textureIndex >= 0 && it->textureIndex < PARTICLE_TEXTURES_QUANTITY,
                "Particle sprite index out of bounds in renderParticles.");

        vPoint pos = getScreenPosition(it->x, it->y, View);
        particleSprite[it->textureIndex].setPosition(pos.x, pos.y);
        particleSprite[it->textureIndex].setScale(View.distance, View.distance);
        particleSprite[it->textureIndex].setColor(sf::Color(it->color.r, it->color.g, it->color.b, (int)it->alpha));
        if(it->additiveBlending) colorMapFBO.draw(particleSprite[it->textureIndex], addRenderState);
        else colorMapFBO.draw(particleSprite[it->textureIndex]);
        // ***
        /*
        blitTransformedShaded(ParticleSprite[it->spriteIndex],
                              screen_x, screen_y,
                              screen_w, screen_h,
                              real_x, real_y,
                              real_w, real_h,
                              it->rotation, true,
                              it->color, it->alpha/255.f);*/
    }
    //Blenders::Set(ALPHA_BLENDER);
}

/**
* @brief Renders weather.
*/
void RenderModule::renderWeather()
{
    sf::VertexArray line(sf::Lines, 2);
    line[0].color = sf::Color(200, 200, 255, 150);
    line[1].color = sf::Color(200, 200, 255, 0);

    for(std::list <RainDropClass>::iterator it=Weather.rainDrop.begin(); it!=Weather.rainDrop.end(); ++it) {
        if(globalTime < it->timeout_splash) {
            line[0].position = sf::Vector2f(it->x, it->y);
            line[1].position = sf::Vector2f(it->x-30.f, it->y-30.f);
            colorMapFBO.draw(line);
        }
        else if(it->splashFrame >= 0) {
            _assert(it->splashFrame < RAINDROP_SPLASH_ANIMATION_FRAMES_QUANTITY,
                    "Raindrop splash animation frame index out of bounds in renderWeather.");

            Weather.rainDropSplashFrameSprite[it->splashFrame].setPosition(it->x, it->y);
            colorMapFBO.draw(Weather.rainDropSplashFrameSprite[it->splashFrame]);
        }
    }
    static float offset = 0.f;
    static sf::Texture fogTexture;
    static bool firstTime = true;
    if(firstTime) {
        firstTime = false;
        fogTexture.loadFromFile("gfx/misc/fog.png");
    }
    static sf::Sprite fogSprite(fogTexture);
    offset -= deltaTime*2.f;
    if(offset < -(float)fogTexture.getSize().x) {
        offset += (float)fogTexture.getSize().x;
    }
    for(int i=0; i<window.getSize().x/fogTexture.getSize().x+2; ++i) {
        for(int j=0; j<window.getSize().y/fogTexture.getSize().y+1; ++j) {
            fogSprite.setPosition(i*(float)fogTexture.getSize().x+offset, j*fogTexture.getSize().y);
            //colorMapFBO.draw(fogSprite);
        }
    }
}

/**
* @brief Renders lights.
*/
void RenderModule::renderLights()
{
    static sf::Texture light;
    static bool first = true;
    if(first) {
        first = false;
        light.loadFromFile("light.png");
    }

    lightDiffuseMap1FBO.clear(sf::Color(ambientLight, ambientLight, ambientLight));
    lightDiffuseMap2FBO.clear(sf::Color(ambientLight, ambientLight, ambientLight));
    lightSpecularMap1FBO.clear(sf::Color(0, 0, 0));
    lightSpecularMap2FBO.clear(sf::Color(0, 0, 0));
    lightDiffuseMap1FBO.display();
    lightDiffuseMap2FBO.display();
    lightSpecularMap1FBO.display();
    lightSpecularMap2FBO.display();

    for(size_t i=0; i<LightSource.size(); ++i) {
        lightToLightDiffuseMapShader.setParameter("lightTexture", light);
        lightToLightSpecularMapShader.setParameter("lightTexture", light);
        if(i%2) {
            lightToLightDiffuseMapShader.setParameter("previousLightDiffuseMap", lightDiffuseMap2FBO.getTexture());
            lightToLightSpecularMapShader.setParameter("previousLightSpecularMap", lightSpecularMap2FBO.getTexture());
        }
        else {
            lightToLightDiffuseMapShader.setParameter("previousLightDiffuseMap", lightDiffuseMap1FBO.getTexture());
            lightToLightSpecularMapShader.setParameter("previousLightSpecularMap", lightSpecularMap1FBO.getTexture());
        }
        vPoint pos = getScreenPosition(LightSource[i].x, LightSource[i].y, View);
        _assert(LightSource[i].textureIndex >= 0 && LightSource[i].textureIndex < LIGHT_TEXTURES_QUANTITY,
                "Light texture index out of bounds in renderLights.");
        sf::Sprite &spr = lightSprite[LightSource[i].textureIndex];
        spr.setPosition(pos.x-(float)lightTexture[LightSource[i].textureIndex].getSize().x/2.f,
                        pos.y-(float)lightTexture[LightSource[i].textureIndex].getSize().y/2.f);

        lightToLightDiffuseMapShader.setParameter("lightPos", pos.x/(float)window.getSize().x, pos.y/(float)window.getSize().y);
        lightToLightSpecularMapShader.setParameter("lightPos", pos.x/(float)window.getSize().x, pos.y/(float)window.getSize().y);
        lightToLightSpecularMapShader.setParameter("lightCol", LightSource[i].color);

        shadowMapFBO.clear(sf::Color::White);
        renderLights_shadows(pos.x, pos.y);
        shadowMapFBO.display();

        if(i%2) {
            lightDiffuseMap1FBO.draw(spr, &lightToLightDiffuseMapShader);
            lightSpecularMap1FBO.draw(spr, &lightToLightSpecularMapShader);
            lightDiffuseMap1FBO.display();
            lightSpecularMap1FBO.display();
            lightDiffuseMap2FBO.draw(sf::Sprite(lightDiffuseMap1FBO.getTexture()), sf::BlendNone);
            lightSpecularMap2FBO.draw(sf::Sprite(lightSpecularMap1FBO.getTexture()), sf::BlendNone);
            lightDiffuseMap2FBO.display();
            lightSpecularMap2FBO.display();
        }
        else {
            lightDiffuseMap2FBO.draw(spr, &lightToLightDiffuseMapShader);
            lightSpecularMap2FBO.draw(spr, &lightToLightSpecularMapShader);
            lightDiffuseMap2FBO.display();
            lightSpecularMap2FBO.display();
            lightDiffuseMap1FBO.draw(sf::Sprite(lightDiffuseMap2FBO.getTexture()), sf::BlendNone);
            lightSpecularMap1FBO.draw(sf::Sprite(lightSpecularMap2FBO.getTexture()), sf::BlendNone);
            lightDiffuseMap1FBO.display();
            lightSpecularMap1FBO.display();
        }
    }
}

/**
* @brief Renders menu interface.
*/
void RenderModule::renderMenuInterface()
{
    if(inGameError.empty()) {
        sf::Text text;
        text.setCharacterSize(24);
        text.setString("Project Zero");
        text.setStyle(sf::Text::Bold);
        text.setPosition((window.getSize().x-getTextWidth("Project Zero", 24))/2-3,
                         window.getSize().y/2-90);
        text.setColor(sf::Color::White);
        window.draw(text);
        Interface.menuGUIControl.render();
    }
    else {
        sf::Text text;
        text.setCharacterSize(11);
        text.setString(inGameError);
        text.setPosition((window.getSize().x-getTextWidth(inGameError, 11))/2,
                         window.getSize().y/2-50);
        text.setColor(sf::Color(220, 100, 100));
        window.draw(text);
        Interface.menuErrorGUIControl.render();
    }
}

/**
* @brief Renders interface.
*/
void RenderModule::renderInterface()
{
    bool mouseOverAnyWindow = false;

    renderInterface_characterNamesAndMessages();
    renderInterface_chat();

    Interface.GUIControl.render();

    renderInterface_statusLogMessages();
    renderInterface_playerCharacterInterfaceAndMinimap();
    renderInterface_dialogue();
    renderInterface_windows(mouseOverAnyWindow);
    renderInterface_objectDescription(mouseOverAnyWindow);

    // ***
    /*if(objectOnMouse.objectType >= 0) mouseMoveObjectTexture.Blit(mx,my);
    else mouseTexture.Blit(mx,my);*/
}

/**
* @brief Character inventory window render callback.
*/
void RenderModule::callback_renderCharacterInventoryWindow(const InterfaceClass &interface, const WindowClass &GUIWindow)
{
    if(playerCharacterIndex < 0) return;

    float characterObjectSlotOffsetX = 30.f;
    float characterObjectSlotOffsetY = 30.f;
    float characterInventoryOffsetX = 18.f;
    float characterInventoryOffsetY = 215.f;

    for(int i=0; i<CHARACTER_OBJECT_SLOTS_QUANTITY; ++i) {
        float x = GUIWindow.x+characterObjectSlotOffsetX+objectSlot[i].offsetX;
        float y = GUIWindow.y+characterObjectSlotOffsetY+objectSlot[i].offsetY;

        if(interface.inventoryMouseOverSlot == i &&
           objectOnMouse.objectType >= 0 &&
           Player[playerCharacterIndex].objectOnSlot[i].type < 0) {
            _assert(objectOnMouse.objectType < (int)ObjectType.size(),
                    "Object on mouse type out of bounds in callback_renderCharacterInventoryWindow.");

            if(canObjectBePlacedOnSlot(objectOnMouse.objectType, i)) {
                Interface.objectSlotSprite.setPosition(x, y);
                Interface.objectSlotSprite.setColor(sf::Color(255, 255, 255, 180));
                window.draw(Interface.objectSlotSprite);
                Interface.objectSlotSprite.setColor(sf::Color::White);
            }
            else {
                Interface.objectSlotSprite.setPosition(x, y);
                Interface.objectSlotSprite.setColor(sf::Color(255, 100, 100));
                window.draw(Interface.objectSlotSprite);
                Interface.objectSlotSprite.setColor(sf::Color::White);
            }
        }
        else {
            Interface.objectSlotSprite.setPosition(x, y);
            window.draw(Interface.objectSlotSprite);
        }
        if(Player[playerCharacterIndex].objectOnSlot[i].type >= 0) {
            _assert(Player[playerCharacterIndex].objectOnSlot[i].type < (int)ObjectType.size(),
                    "On slot object type index out of bounds in callback_renderCharacterInventoryWindow.");
            if(ObjectType[Player[playerCharacterIndex].objectOnSlot[i].type].baseType == OBJECT_BASE_TYPE_WEAPON)
                blitWeaponWithAddons(Player[playerCharacterIndex].objectOnSlot[i], x, y,
                                     interface.objectSlotTexture.getSize().x,
                                     interface.objectSlotTexture.getSize().y,
                                     false,
                                     true);
            else {
                sf::Sprite &spr = ObjectType[Player[playerCharacterIndex].objectOnSlot[i].type].colorMapSprite;
                _assert(spr.getTexture() && spr.getTexture()->getSize().x && spr.getTexture()->getSize().y,
                        "Object type has no texture in callback_renderCharacterInventoryWindow.");
                spr.setPosition(x, y);
                spr.setScale((float)Interface.objectSlotTexture.getSize().x/spr.getTexture()->getSize().x,
                             (float)Interface.objectSlotTexture.getSize().y/spr.getTexture()->getSize().y);
                window.draw(spr);
            }
        }
    }
    for(size_t i=0; i<Player[playerCharacterIndex].objectInInventory.size(); ++i) {
        for(size_t j=0; j<Player[playerCharacterIndex].objectInInventory[i].size(); ++j) {
            float x = GUIWindow.x+characterInventoryOffsetX+i*interface.objectSlotTexture.getSize().x;
            float y = GUIWindow.y+characterInventoryOffsetY+j*interface.objectSlotTexture.getSize().y;

            if(interface.inventoryMouseOverInvX == (int)i && interface.inventoryMouseOverInvY == (int)j &&
               objectOnMouse.objectType >= 0 && Player[playerCharacterIndex].objectInInventory[i][j].type < 0) {
                   Interface.objectSlotSprite.setPosition(x, y);
                   Interface.objectSlotSprite.setColor(sf::Color(255, 255, 255, 180));
                   window.draw(Interface.objectSlotSprite);
                   Interface.objectSlotSprite.setColor(sf::Color::White);
            }
            else {
                Interface.objectSlotSprite.setPosition(x, y);
                window.draw(Interface.objectSlotSprite);
            }
            if(Player[playerCharacterIndex].objectInInventory[i][j].type >= 0) {
                _assert(Player[playerCharacterIndex].objectInInventory[i][j].type < (int)ObjectType.size(),
                        "Inventory object type index out of bounds in callback_renderCharacterInventoryWindow.");
                if(ObjectType[Player[playerCharacterIndex].objectInInventory[i][j].type].baseType == OBJECT_BASE_TYPE_WEAPON)
                    blitWeaponWithAddons(Player[playerCharacterIndex].objectInInventory[i][j], x, y,
                                         interface.objectSlotTexture.getSize().x,
                                         interface.objectSlotTexture.getSize().y,
                                         false,
                                         true);
                else {
                    sf::Sprite &spr = ObjectType[Player[playerCharacterIndex].objectInInventory[i][j].type].colorMapSprite;
                    _assert(spr.getTexture() && spr.getTexture()->getSize().x && spr.getTexture()->getSize().y,
                            "Object type has no texture in callback_renderCharacterInventoryWindow.");
                    spr.setPosition(x, y);
                    spr.setScale((float)Interface.objectSlotTexture.getSize().x/spr.getTexture()->getSize().x,
                                 (float)Interface.objectSlotTexture.getSize().y/spr.getTexture()->getSize().y);
                    window.draw(spr);
                }
            }
        }
    }

    char buff[200];
    sf::Text text;
    text.setCharacterSize(11);

    text.setColor(sf::Color::White);
    text.setString(Player[playerCharacterIndex].name);
    text.setPosition(GUIWindow.x+210.f, GUIWindow.y+30.f);
    window.draw(text);

    sprintf(buff, "Level: %d", Player[playerCharacterIndex].param[CHARACTER_PARAM_LEVEL]);
    text.setString(buff);
    text.setPosition(GUIWindow.x+210.f, GUIWindow.y+50.f);
    window.draw(text);

    sprintf(buff, "Experience: %d", Player[playerCharacterIndex].param[CHARACTER_PARAM_EXPERIENCE]);
    text.setString(buff);
    text.setPosition(GUIWindow.x+210.f, GUIWindow.y+60.f);
    window.draw(text);

    if(Player[playerCharacterIndex].param[CHARACTER_PARAM_LEVEL] < EXP_TABLE_SIZE-1) {
        _assert(Player[playerCharacterIndex].param[CHARACTER_PARAM_LEVEL] >= 0,
                "Level is negative in callback_renderCharacterInventoryWindow.");
        sprintf(buff, "Experience TNL: %d", EXP_TABLE[Player[playerCharacterIndex].param[CHARACTER_PARAM_LEVEL]+1]-Player[playerCharacterIndex].param[CHARACTER_PARAM_EXPERIENCE]);
    }
    else sprintf(buff, "Experience TNL: MAX LEVEL");
    text.setString(buff);
    text.setPosition(GUIWindow.x+210.f, GUIWindow.y+70.f);
    window.draw(text);

    sprintf(buff, "Money: %d", Player[playerCharacterIndex].param[CHARACTER_PARAM_MONEY]);
    text.setString(buff);
    text.setPosition(GUIWindow.x+210.f, GUIWindow.y+80.f);
    window.draw(text);
}

/**
* @brief Object description window render callback.
*/
void RenderModule::callback_renderObjectDescriptionWindow(const InterfaceClass &interface, const WindowClass &GUIWindow)
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
    if(noObject) return;

    _assert(object->type < (int)ObjectType.size(),
            "Object type out of bounds in callback_renderObjectDescriptionWindow.");
    blitObjectDescriptionText(*object, (int)GUIWindow.x+5, (int)GUIWindow.y+100, 255);
    if(ObjectType[object->type].baseType == OBJECT_BASE_TYPE_WEAPON) {
        blitWeaponWithAddons(*object, GUIWindow.x+45.f, GUIWindow.y+15.f, 100, 100, true, true);
        for(int i=0; i<WEAPON_ATTACHMENTS_QUANTITY; ++i) {
            float x = GUIWindow.x+weaponAttachmentSlot[i].offsetX;
            float y = GUIWindow.y+weaponAttachmentSlot[i].offsetY;
            if(interface.mouseOverWeaponAttachmentSlot == i &&
               objectOnMouse.objectType >= 0 &&
               object->param[OBJECT_PARAM_ADDON_1+i] < 0) {
                _assert(objectOnMouse.objectType < (int)ObjectType.size(),
                        "Object on mouse type out of bounds in callback_renderObjectDescriptionWindow.");
                if(ObjectType[objectOnMouse.objectType].baseType == OBJECT_BASE_TYPE_ADDON &&
                   ObjectType[objectOnMouse.objectType].attachmentType == weaponAttachmentSlot[i].attachmentType &&
                   ObjectType[objectOnMouse.objectType].weaponType == ObjectType[object->type].weaponType) {
                       Interface.objectSlotSprite.setPosition(x, y);
                       Interface.objectSlotSprite.setColor(sf::Color(255, 255, 255, 180));
                       window.draw(Interface.objectSlotSprite);
                       Interface.objectSlotSprite.setColor(sf::Color::White);
                }
                else {
                    Interface.objectSlotSprite.setPosition(x, y);
                    Interface.objectSlotSprite.setColor(sf::Color(255, 100, 100));
                    window.draw(Interface.objectSlotSprite);
                    Interface.objectSlotSprite.setColor(sf::Color::White);
                }
            }
            else {
                Interface.objectSlotSprite.setPosition(x, y);
                window.draw(Interface.objectSlotSprite);
            }

            if(object->param[OBJECT_PARAM_ADDON_1+i] >= 0) {
                _assert(object->param[OBJECT_PARAM_ADDON_1+i] < (int)ObjectType.size(),
                        "Weapon attachment object type out of bounds in callback_renderObjectDescriptionWindow.");
                sf::Sprite &spr = ObjectType[object->param[OBJECT_PARAM_ADDON_1+i]].colorMapSprite;
                _assert(spr.getTexture() && spr.getTexture()->getSize().x && spr.getTexture()->getSize().y,
                        "Object type has no texture in callback_renderObjectDescriptionWindow.");
                spr.setPosition(x, y);
                spr.setScale((float)Interface.objectSlotTexture.getSize().x/spr.getTexture()->getSize().x,
                             (float)Interface.objectSlotTexture.getSize().y/spr.getTexture()->getSize().y);
                window.draw(spr);
            }
        }
    }
    else {
        sf::Sprite &spr = ObjectType[object->type].colorMapSprite;
        _assert(spr.getTexture() && spr.getTexture()->getSize().x && spr.getTexture()->getSize().y,
                "Object type has no texture in callback_renderObjectDescriptionWindow.");
        spr.setPosition(GUIWindow.x+50, GUIWindow.y+15);
        spr.setScale(100.f/spr.getTexture()->getSize().x,
                     100.f/spr.getTexture()->getSize().y);
        window.draw(spr);
    }
}

/**
* @brief Trade with NPC window render callback.
*/
void RenderModule::callback_renderTradeWithNPCWindow(const InterfaceClass &interface, const WindowClass &GUIWindow)
{
    if(playerCharacterIndex < 0) return;

    sf::RectangleShape rect;
    sf::VertexArray line(sf::Lines, 2);
    sf::Text text;
    text.setCharacterSize(11);

    for(size_t i=0; i<currentTradeWithNPC.NPCObjectType.size(); ++i) {
        if((int)i == Interface.mouseOverTradeWithNPCObjectIndex) {
            rect.setPosition(GUIWindow.x+1, GUIWindow.y+20+i*50);
            rect.setSize(sf::Vector2f(250.f, 49.f));
            rect.setFillColor(sf::Color(170, 170, 170, 190));
            window.draw(rect);
        }
        line[0].color = sf::Color(170, 170, 170, 210);
        line[1].color = sf::Color(170, 170, 170, 210);
        line[0].position = sf::Vector2f(GUIWindow.x+250.f, GUIWindow.y+20.f+i*50.f);
        line[1].position = sf::Vector2f(GUIWindow.x+250.f, GUIWindow.y+20.f+i*50.f+49.f);
        window.draw(line);

        if(i != currentTradeWithNPC.NPCObjectType.size()-1) {
            line[0].position = sf::Vector2f(GUIWindow.x+1.f,GUIWindow.y+20.f+i*50.f+49.f);
            line[1].position = sf::Vector2f(GUIWindow.x+250.f,GUIWindow.y+20.f+i*50.f+49.f);
            window.draw(line);
        }
        _assert(currentTradeWithNPC.NPCObjectType[i] >= 0 &&
                currentTradeWithNPC.NPCObjectType[i] < (int)ObjectType.size(),
                "NPC trade object type out of bounds in callback_renderTradeWithNPCWindow.");

        sf::Sprite &spr = ObjectType[currentTradeWithNPC.NPCObjectType[i]].colorMapSprite;
        _assert(spr.getTexture() && spr.getTexture()->getSize().x && spr.getTexture()->getSize().y,
                "Object type has no texture in callback_renderTradeWithNPCWindow.");
        spr.setPosition(GUIWindow.x+20, GUIWindow.y+20+i*50+1);
        spr.setScale(48.f/spr.getTexture()->getSize().x,
                     48.f/spr.getTexture()->getSize().y);
        window.draw(spr);

        text.setColor(sf::Color::White);
        text.setString(ObjectType[currentTradeWithNPC.NPCObjectType[i]].name);
        text.setPosition(GUIWindow.x+100, GUIWindow.y+20+i*50+25);
        window.draw(text);

        text.setColor(sf::Color(200, 200, 100));
        char buff[100];
        sprintf(buff, "%d$", ObjectType[currentTradeWithNPC.NPCObjectType[i]].value);
        text.setString(buff);
        text.setPosition(GUIWindow.x+100, GUIWindow.y+20+i*50+35);
        window.draw(text);
    }
}

/**
* @brief Character stats window render callback.
*/
void RenderModule::callback_renderCharacterStatsWindow(const InterfaceClass &interface, const WindowClass &window)
{
    if(playerCharacterIndex < 0) return;

    /*
    FontMain.SetColor(Rgba::WHITE);
    FontMain.Print(Player[playerCharacterIndex].name,int(window.x+10.f),int(window.y+25.f));
    char buff[200];
    sprintf(buff,"Level: %d",Player[playerCharacterIndex].Param[CHARACTER_PARAM_LEVEL]);
    FontMain.Print(buff,int(window.x+10.f),int(window.y+45.f));
    sprintf(buff,"Experience: %d",Player[playerCharacterIndex].Param[CHARACTER_PARAM_EXPERIENCE]);
    FontMain.Print(buff,int(window.x+10.f),int(window.y+55.f));
    sprintf(buff,"Experience TNL: %d",0);
    FontMain.Print(buff,int(window.x+10.f),int(window.y+65.f));*/
}
