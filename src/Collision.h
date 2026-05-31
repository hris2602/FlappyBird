#ifndef COLLISION_H
#define COLLISION_H

#include <algorithm>

struct Rectangle
{
    float x, y;
    float width, height;
};

struct Circle
{
    float x, y;
    float radius;
};


class Collision {
    public:
        static bool checkCollision(const Circle & circle, const Rectangle & rectangle);
};

#endif