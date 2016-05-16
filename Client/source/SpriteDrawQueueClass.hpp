#ifndef SPRITE_DRAW_QUEUE_CLASS_HPP
#define SPRITE_DRAW_QUEUE_CLASS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "global.hpp"

class SpriteDrawQueueClass
{
    public:
        enum typeEnum {COLOR_MAP, NORMAL_MAP, HEIGHT_MAP};

    private:
        class SpriteDrawClass
        {
            public:
                sf::Sprite *sprite;
                typeEnum type;
                int number;

                float x, y;
                float scaleX, scaleY;
                float dir;

                SpriteDrawClass(sf::Sprite *newSprite, typeEnum newType, int newNumber, float newX, float newY, float newScaleX, float newScaleY, float newDir)
                    :   sprite(newSprite),
                        type(newType),
                        number(newNumber),
                        x(newX), y(newY),
                        scaleX(newScaleX), scaleY(newScaleY),
                        dir(newDir) {
                }

                inline bool operator < (const SpriteDrawClass &t) const
                {
                    if(type < t.type) return true;
                    else if(type > t.type) return false;
                    else if(number < t.number) return true;
                    else if(number > t.number) return false;
                    return sprite->getTexture() < t.sprite->getTexture();
                }
        };
        int currentNumber;
        std::vector <SpriteDrawClass> spriteDraw;

    public:
        void clear();
        void add(sf::Sprite *newSprite, typeEnum type, bool inOrder, float x, float y, float scaleX = 1.f, float scaleY = 1.f, float dir = 0.f);
        void sort();
        void draw();

        SpriteDrawQueueClass()
            :   currentNumber(0) {
        }
};

#endif
