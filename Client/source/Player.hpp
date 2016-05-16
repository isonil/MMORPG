#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "global.hpp"

class Character;

class PlayerC
{
    private:
        Character *character;

    public:
        void setCharacter(CharacterClass &player);
        void updatePlayerInput();
        void updateSendPosition();
        bool collides();
        bool move(float dir);

        inline Character *getCharacter()
        {
            return character;
        }

        PlayerC();
};

#endif
