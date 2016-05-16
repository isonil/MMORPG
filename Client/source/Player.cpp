#include "Player.hpp"

#include "Master.hpp"

void PlayerC::setCharacter(CharacterClass &player)
{
    character = &player;
}

void PlayerC::updatePlayerInput()
{
    bool moved = false;

    if(!keyBuffHandled) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {moved = true; Master::getInstance().playerMove(-M_PI/2.f);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {moved = true; Master::getInstance().playerMove(M_PI/2.f);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {moved = true; Master::getInstance().playerMove(-M_PI);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {moved = true; Master::getInstance().playerMove(0.f);}
    }

    if(!moved) character->timerStep.setDuration(200.0);
    else if(character->timerStep.hasPassed()) {
        character->timerStep.setDuration(460.0);
        int tile_x = character->position.x/TILE_SIZE;
        int tile_y = character->position.y/TILE_SIZE;
        if(!Master::getInstance().isOutOfMap(tile_x, tile_y) && Master::getInstance().Tile[tile_x][tile_y].tileType >= 0) {
            _assert(Master::getInstance().Tile[tile_x][tile_y].tileType < Master::getInstance().TileType.size(), "Tile type out of bounds in logicPlayerInput.");
            character->stepSound.setBuffer(Master::getInstance().TileType[Master::getInstance().Tile[tile_x][tile_y].tileType].stepSoundBuffer);
            character->stepSound.setVolume(35.f);
            character->stepSound.play();
        }
    }

    character->dir = atan2(my-(float)window.getSize().y/2.f, mx-(float)window.getSize().x/2.f);
    if(mb == 1 && (!LMBEventHandled || Master::getInstance().automaticShooting)) {
        LMBEventHandled = true;
        Master::getInstance().automaticShooting = false;

        ObjectClass *weapon = &character->objectOnSlot[CHARACTER_OBJECT_SLOT_WEAPON_INDEX];
        if(weapon->type >= 0) {
            _assert(weapon->type < (int)Master::getInstance().ObjectType.size(), "Weapon object type out of bounds in logicPlayerInput.");
            if(Master::getInstance().ObjectType[weapon->type].isAutomatic)
                Master::getInstance().automaticShooting = true;
            if(globalTime >= weapon->timeout_shot) {
                Master::getInstance().getNetwork().sendPacket(Packet <PACKET_SHOT>::construct(character->dir));
                weapon->timeout_shot = globalTime+Master::getInstance().ObjectType[weapon->type].baseShotDelay;
            }
        }
    }
    if(mb == 0) Master::getInstance().automaticShooting = false;
}

void PlayerC::updateSendPosition()
{
    if(globalTime >= Master::getInstance().timeout_sendPosition) {

        Master::getInstance().getNetwork().sendPacket(Packet <PACKET_CHARACTER_POSITION>::construct(character->position.x,
                                                                                                    character->position.y,
                                                                                                    character->dir));
        Master::getInstance().timeout_sendPosition = globalTime+100.0;
    }
}

bool PlayerC::collides()
{
    return Master::getInstance().getWorld().characterCollides(*character);
}

bool PlayerC::move(float dir)
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

        character->position.x += currentStep_x*cos(dir);
        if(collides()) {
            character->position.x -= currentStep_x*cos(dir);
            collided = true;
        }

        character->position.y += currentStep_y*sin(dir);
        if(collides()) {
            character->position.y -= currentStep_y*sin(dir);
            collided = true;
        }

        step_x -= smallStep_x;
        step_y -= smallStep_y;
        if(step_x < 0.f) step_x = 0.f;
        if(step_y < 0.f) step_y = 0.f;
    }
    return !collided;
}

PlayerC::PlayerC()
    :   character(NULL) {
}
