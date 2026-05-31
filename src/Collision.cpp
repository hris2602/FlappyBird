#include "Collision.h"

bool Collision::checkCollision(const Circle & circle, const Rectangle & rectangle) {
    float px = std::max(rectangle.x, std::min(circle.x, rectangle.x + rectangle.width));
    float py = std::max(rectangle.y, std::min(circle.y, rectangle.y + rectangle.height));

    float distanceX = circle.x - px;
    float distanceY = circle.y - py;

    float distance = (distanceX * distanceX) + (distanceY * distanceY);

    return distance <= circle.radius * circle.radius;
}
