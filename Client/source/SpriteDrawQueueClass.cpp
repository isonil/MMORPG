#include "SpriteDrawQueueClass.hpp"

void SpriteDrawQueueClass::clear()
{
    spriteDraw.clear();
    currentNumber = 0;
}

void SpriteDrawQueueClass::add(sf::Sprite *newSprite, typeEnum type, bool inOrder, float x, float y, float scaleX, float scaleY, float dir)
{
    if(!newSprite) return;
    if(!newSprite->getTexture()) return;

    if(inOrder) {
        spriteDraw.push_back(SpriteDrawClass(newSprite, type, currentNumber, x, y, scaleX, scaleY, dir));
        ++currentNumber;
    }
    else {
        spriteDraw.push_back(SpriteDrawClass(newSprite, type, -1, x, y, scaleX, scaleY, dir));
    }
}

void SpriteDrawQueueClass::sort()
{
    std::sort(spriteDraw.begin(), spriteDraw.end());
}

void SpriteDrawQueueClass::draw()
{
    for(size_t i=0; i<spriteDraw.size(); ++i) {
        _assert(spriteDraw[i].sprite->getTexture(), "Sprite has no texture in draw queue.");
        spriteDraw[i].sprite->setScale(spriteDraw[i].scaleX, spriteDraw[i].scaleY);
        spriteDraw[i].sprite->setRotation(spriteDraw[i].dir);
        spriteDraw[i].sprite->setPosition(spriteDraw[i].x+spriteDraw[i].sprite->getTexture()->getSize().x/2.f*spriteDraw[i].scaleX,
                                          spriteDraw[i].y+spriteDraw[i].sprite->getTexture()->getSize().y/2.f*spriteDraw[i].scaleY);
        spriteDraw[i].sprite->setOrigin(spriteDraw[i].sprite->getTexture()->getSize().x/2.f,
                                        spriteDraw[i].sprite->getTexture()->getSize().y/2.f);

        if(spriteDraw[i].type == COLOR_MAP) colorMapFBO.draw(*spriteDraw[i].sprite);
        else if(spriteDraw[i].type == NORMAL_MAP) normalMapFBO.draw(*spriteDraw[i].sprite);
        else if(spriteDraw[i].type == HEIGHT_MAP) heightMapFBO.draw(*spriteDraw[i].sprite);
        spriteDraw[i].sprite->setOrigin(0.f, 0.f);
    }
}
