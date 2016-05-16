#include "World.hpp"

#include "global.hpp"
#include "Master.hpp"
#include "Classes.hpp"

void World::updatePlayers()
{
    for(size_t i=0; i<Player.size(); ++i) {
        Player[i].update();
    }
}

void World::updateNPCs()
{
    for(size_t i=0; i<NPC.size(); ++i) {
        NPC[i].update();
    }
}

bool World::characterCollides(const CharacterClass &character)
{
    if(!character.isVisible()) return false;

    for(size_t i=0; i<Player.size(); ++i) {
        if(character.getCharacterSet() == CHARACTER_PLAYER &&
           character.getID() == Player[i].getID()) continue;
        if(!Player[i].isVisible()) continue;

        if(Master::getInstance().getDistance((int)Player[i].position.x, (int)Player[i].position.y,
                                             (int)character.position.x, (int)character.position.y) <= 2*CHARACTER_RADIUS) {
            return true;
        }
    }
    for(size_t i=0; i<NPC.size(); ++i) {
        if(character.getCharacterSet() == CHARACTER_NPC &&
           character.getID() == NPC[i].getID()) continue;
        if(!NPC[i].isVisible()) continue;

        if(Master::getInstance().getDistance((int)NPC[i].position.x, (int)NPC[i].position.y,
                                             (int)character.position.x, (int)character.position.y) <= 2*CHARACTER_RADIUS) {
            return true;
        }
    }
    for(int i=int(character.position.x/TILE_SIZE-1); i<=character.position.x/TILE_SIZE+1; ++i) {
        for(int j=int(character.position.y/TILE_SIZE-1); j<=character.position.y/TILE_SIZE+1; ++j) {
            if(!Master::getInstance().isPassable(i, j) &&
                (int)character.position.x-CHARACTER_RADIUS < i*TILE_SIZE+TILE_SIZE &&
                (int)character.position.x+CHARACTER_RADIUS > i*TILE_SIZE &&
                (int)character.position.y-CHARACTER_RADIUS < j*TILE_SIZE+TILE_SIZE &&
                (int)character.position.y+CHARACTER_RADIUS > j*TILE_SIZE) {
                    return true;
            }
        }
    }
    return false;
}

void World::renderCharacters()
{
    for(size_t i=0; i<Player.size(); ++i) {
        Player[i].render();
    }

    for(size_t i=0; i<NPC.size(); ++i) {
        NPC[i].render();
    }
}

void World::renderCharactersNameAndMessages()
{
    for(size_t i=0; i<Player.size(); ++i) {
        Player[i].renderNameAndMessages();
    }

    for(size_t i=0; i<NPC.size(); ++i) {
        NPC[i].renderNameAndMessages();
    }
}

void World::reset()
{
    Player.clear();
    NPC.clear();
}

CharacterClass &World::getCharacter(char characterSet, int ID)
{
    _assert(Master::getInstance().isValidCharacterSet(characterSet),
            "Character set is invalid.");
    _assert(ID >= 0, "Character ID is negative.");

    if(characterSet == CHARACTER_PLAYER) return getPlayer(ID);
    if(characterSet == CHARACTER_NPC) return getNPC(ID);
}

CharacterClass &World::getPlayer(int ID)
{
    _assert(ID >= 0, "Player ID is negative.");
    for(size_t i=Player.size(); i<=ID; ++i) {
        Player.push_back(CharacterClass());
        Player.back().characterSet = CHARACTER_PLAYER;
        Player.back().ID = Player.size()-1;
    }
    return Player[ID];
}

CharacterClass &World::getNPC(int ID)
{
    _assert(ID >= 0, "NPC ID is negative.");
    for(size_t i=NPC.size(); i<=ID; ++i) {
        NPC.push_back(CharacterClass());
        NPC.back().characterSet = CHARACTER_NPC;
        NPC.back().ID = NPC.size()-1;
    }
    return NPC[ID];
}

CharacterClass *World::getNPCAt(float x, float y)
{
    for(size_t i=0; i<NPC.size(); ++i) {
        if(NPC[i].isVisible() && NPC[i].getDistance(x, y) <= CHARACTER_RADIUS) {
            return &NPC[i];
        }
    }
    return NULL;
}
