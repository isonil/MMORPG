#include "TexturePacker.hpp"

void CTexturePacker::add(int w, int h)
{
    int index = (int)texture.size();
    texture.push_back(CRectangle(index, 0, 0, w, h));
}

void CTexturePacker::get(int index, int &x, int &y, int &w, int &h)
{
    _assert(index >= 0 && index < (int)texture.size(),
            "Texture index out of bounds in CTexturePacker::get.");

    for(size_t i=0; i<texture.size(); ++i) {
        if(texture[i].index == index) {
            x = texture[i].x;
            y = texture[i].y;
            w = texture[i].w;
            h = texture[i].h;
        }
    }
}

void CTexturePacker::pack()
{
    int zoneIndex = 0;

    freeZone.clear();
    freeZone.insert(CRectangle(zoneIndex, 0, 0, size, size));
    ++zoneIndex;

    std::sort(texture.begin(), texture.end());
    for(size_t i=0; i<texture.size(); ++i) {
        std::set <CRectangle, CRectangle>::iterator zone = freeZone.end();
        for(std::set <CRectangle, CRectangle>::iterator it=freeZone.begin(); it!=freeZone.end(); ++it) {
            if(it->w >= texture[i].w && it->h >= texture[i].h) {
                zone = it;
                break;
            }
        }
        if(zone == freeZone.end()) error("Texture didn't fit in CTexturePacker::pack.");

        CRectangle rect = *zone;
        texture[i].x = rect.x;
        texture[i].y = rect.y;

        freeZone.erase(zone);
        freeZone.insert(CRectangle(zoneIndex, rect.x+texture[i].w, rect.y, rect.w-texture[i].w, texture[i].h));
        ++zoneIndex;
        freeZone.insert(CRectangle(zoneIndex, rect.x, rect.y+texture[i].h, rect.w, rect.h-texture[i].h));
        ++zoneIndex;
    }
}
