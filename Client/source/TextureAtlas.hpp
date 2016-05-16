#ifndef TEXTURE_ATLAS_HPP
#define TEXTURE_ATLAS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "container.hpp"

class CTextureAtlas
{
    public:
        void add(sf::Texture &tex, sf::Sprite &spr, const std::string &path, bool checkIfExists = false);
        void add(sf::Texture &tex, sf::Sprite &spr, const sf::Image &img, const sf::IntRect &rect);
        void pack(int atlasSize);

        inline const sf::Texture &getTexture() const
        {
            return textureAtlasTexture;
        }

    private:
        class CContent
        {
            public:
                sf::Texture *tex;
                sf::Sprite *spr;
                sf::Image img;

                CContent() {}
                CContent(sf::Texture *newTex, sf::Sprite *newSpr)
                    :   tex(newTex), spr(newSpr) {
                }
        };

        sf::Image textureAtlasImage;
        sf::Texture textureAtlasTexture;
        container <CContent> content;
};

#endif
