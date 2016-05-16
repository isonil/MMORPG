#ifndef LINE_HPP
#define LINE_HPP

#include <SFML/Graphics.hpp>

class Line
{
    private:
        sf::Vector2f start, end;

    public:
        bool collidesWith(const Line &line) const;
        Line();
        Line(float x1, float y1, float x2, float y2);
};

#endif
