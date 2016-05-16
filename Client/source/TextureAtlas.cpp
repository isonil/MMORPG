#include "TextureAtlas.hpp"
#include "TexturePacker.hpp"
#include "global.hpp"

void CTextureAtlas::add(sf::Texture &tex, sf::Sprite &spr, const std::string &path, bool checkIfExists)
{
    spr.setTexture(textureAtlasTexture);
    if(!checkIfExists || fileExists(path)) {
        content.push_back(CContent(&tex, &spr));
        loadImage(content.back().img, path);
        if(!tex.loadFromImage(content.back().img)) {
            error("Could not load texture from image in CTextureAtlas::add.");
        }
    }
}

void CTextureAtlas::add(sf::Texture &tex, sf::Sprite &spr, const sf::Image &img, const sf::IntRect &rect)
{
    spr.setTexture(textureAtlasTexture);
    content.push_back(CContent(&tex, &spr));
    if(!tex.loadFromImage(img, rect)) {
        error("Could not load texture from image in CTextureAtlas::add.");
    }
    content.back().img.create(tex.getSize().x, tex.getSize().y);
    content.back().img.copy(img, 0, 0, rect);
}

void CTextureAtlas::pack(int atlasSize)
{
    _assert(atlasSize > 0, "Atlas size is too small in CTextureAtlas::pack.");

    CTexturePacker texturePacker(atlasSize);

    std::vector <int> texSize;
    for(size_t i=0; i<content.size(); ++i) {
        texturePacker.add(content[i].tex->getSize().x+2,
                          content[i].tex->getSize().y+2);
    }
    texturePacker.pack();

    textureAtlasImage.create(atlasSize, atlasSize, sf::Color::Transparent);

    for(size_t i=0; i<content.size(); ++i) {
        int x, y, w, h;
        texturePacker.get(i, x, y, w, h);
        /*
          Overwriting w and h because we want it to be size of texture,
          not rectangle in a texture atlas (which is texture size + 2).
        */
        w = content[i].tex->getSize().x;
        h = content[i].tex->getSize().y;

        sf::IntRect rect(x+1, y+1, w, h);
        content[i].spr->setTextureRect(rect);

        /*
          Border copying required for SFML texture smoothing. Avoiding texture bleeding.
        */
        textureAtlasImage.copy(content[i].img, x+1, y, sf::IntRect(0, 0, w, 1));       // ___  top
        textureAtlasImage.copy(content[i].img, x, y+1, sf::IntRect(0, 0, 1, h));       // |  left
        textureAtlasImage.copy(content[i].img, x+1+w, y+1, sf::IntRect(w-1, 0, 1, h)); // |  right
        textureAtlasImage.copy(content[i].img, x+1, y+1+h, sf::IntRect(0, h-1, w, 1)); // ___  bottom

        textureAtlasImage.setPixel(x, y, textureAtlasImage.getPixel(x+1, y));             // .  top left
        textureAtlasImage.setPixel(x+1+w, y, textureAtlasImage.getPixel(x+w, y));         // .  top right
        textureAtlasImage.setPixel(x, y+1+h, textureAtlasImage.getPixel(x+1, y+1+h));     // .  bottom left
        textureAtlasImage.setPixel(x+1+w, y+1+h, textureAtlasImage.getPixel(x+w, y+1+h)); // .  bottom right*/

        textureAtlasImage.copy(content[i].img, x+1, y+1);
    }

    if(!textureAtlasTexture.loadFromImage(textureAtlasImage)) {
        error("Could not load atlas texture from image in CTextureAtlas::pack.");
    }
    textureAtlasTexture.setSmooth(true);

    textureAtlasImage.saveToFile("atlas2.png");
}
