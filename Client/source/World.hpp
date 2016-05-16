#ifndef WORLD_HPP
#define WORLD_HPP

#include "container.hpp"
#include "Classes.hpp"

class World
{
    private:
        container <CharacterClass> Player;
        container <CharacterClass> NPC;

    public:
        void updatePlayers();
        void updateNPCs();
        bool characterCollides(const CharacterClass &character);
        void renderCharacters();
        void renderCharactersNameAndMessages();
        void reset();

        CharacterClass &getCharacter(char characterSet, int ID);
        CharacterClass &getPlayer(int ID);
        CharacterClass &getNPC(int ID);
        CharacterClass *getNPCAt(float x, float y);
};

#endif
