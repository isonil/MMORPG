#include "Line.hpp"

#include <cmath>

bool Line::collidesWith(const Line &line) const
{
    float x1 = start.x, x2 = end.x, x3 = line.start.x, x4 = line.end.x;
    float y1 = start.y, y2 = end.y, y3 = line.start.y, y4 = line.end.y;

    float d = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
    if(fabs(d) < 0.001f) return false;

    float pre = (x1*y2-y1*x2), post = (x3*y4-y3*x4);
    float x = (pre*(x3-x4)-(x1-x2)*post)/d;
    float y = (pre*(y3-y4)-(y1-y2)*post)/d;

    if(x < std::min(x1, x2) || x > std::max(x1, x2) ||
       x < std::min(x3, x4) || x > std::max(x3, x4)) return false;
    if(y < std::min(y1, y2) || y > std::max(y1, y2) ||
       y < std::min(y3, y4) || y > std::max(y3, y4)) return false;

    return true;
}

Line::Line()
    :   start(0.f, 0.f), end(0.f, 0.f)
{
}

Line::Line(float x1, float y1, float x2, float y2)
    :   start(x1, y1), end(x2, y2)
{
}
