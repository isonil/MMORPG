#ifndef TEXTURE_PACKER_HPP
#define TEXTURE_PACKER_HPP

#include "global.hpp"
#include <vector>
#include <set>

class CTexturePacker
{
    private:
        class CRectangle
        {
            public:
                int index;
                int x, y, w, h;

                inline bool operator < (const CRectangle &right) const
                {
                    return w+h > right.w+right.h;
                }

                inline bool operator () (const CRectangle &left, const CRectangle &right) const
                {
                    if(left.w+left.h == right.w+right.h) return left.index < right.index;
                    return left.w+left.h < right.w+right.h;
                }

                CRectangle()
                    :   index(0),
                        x(0), y(0), w(0), h(0) {
                }

                CRectangle(int newIndex, int newX, int newY, int newW, int newH)
                    :   index(newIndex),
                        x(newX), y(newY), w(newW), h(newH) {
                }
        };

        int size;
        std::set <CRectangle, CRectangle> freeZone;
        std::vector <CRectangle> texture;

    public:
        void add(int w, int h);
        void get(int index, int &x, int &y, int &w, int &h);
        void pack();

        CTexturePacker(int newSize)
            :   size(newSize) {
                _assert(size >= 0, "Size is negative in CTexturePacker constructor.");
        }
};

#endif
