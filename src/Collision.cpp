#include "Collision.h"

bool Collision::checkCollision(const Circle & circle, const Rectangle & rectangle) {
    float px = std::max(rectangle.x, std::min(circle.x, rectangle.x + rectangle.width));
    float py = std::max(rectangle.y, std::min(circle.y, rectangle.y + rectangle.height));

    float distanceX = circle.x - px;
    float distanceY = circle.y - py;

    float distance = (distanceX * distanceX) + (distanceY * distanceY);

    return distance <= circle.radius * circle.radius;
}

bool Collision::checkCollision(float cX, float cY, float cR, float rX, float rY, float w, float h) {
    float px = std::max(rX, std::min(cX, rX + w));
    float py = std::max(rY, std::min(cY, rY + h));

    float distanceX = cX - px;
    float distanceY = cY - py;

    float distance = (distanceX * distanceX) + (distanceY * distanceY);

    return distance <= cR * cR;
}
