#include "Pillars.h"
#include "Collision.h"

Pillars::Pillars(Shader* shader) : generator(std::random_device{}()), random(-0.4f, 0.4f), pillarShader(shader) {
    float start = 3.3f;
    for (size_t i = 0; i < 10; i++)
    {
        float gapY = random(generator);
        PillarPair* spawn = new PillarPair(start, gapY, 0.6f, shader);
        pillars.push_back(spawn);
        start += 1.7f;
    }
}

Pillars::~Pillars() {
    for (auto& pair : pillars)
    {
        delete pair;
    }
    
}

void Pillars::render() {
    pillarShader->use();

    for(auto& pair :pillars) {
        pair->render();
    }
}

void Pillars::update() {
    for(auto& pair :pillars) {
        pair->update();
    }

    if (!pillars.empty() && pillars.front()->getBottomPosition().x <= -3.0f) {
        float x = pillars.back()->getBottomPosition().x;
        pillars.front()->recycle(x + 1.7f, random(generator), 0.6f);
        PillarPair* front = pillars.front();
        pillars.pop_front();
        pillars.push_back(front);
    }
}

bool Pillars::checkCollision(float bX, float bY, float bR) {
    float pipeWidth = 0.3f;
    float pipeHeight = 4.0f;
    for(PillarPair* pair : pillars) {
        glm::vec2 posB = pair->getBottomPosition();
        glm::vec2 posT = pair -> getTopPosition();

        float bottomRectX = posB.x - (pipeWidth / 2.0f);
        float bottomRectY = posB.y - (pipeHeight / 2.0f);


        float topRectX = posT.x - (pipeWidth / 2.0f);
        float topRectY = posT.y - (pipeHeight / 2.0f);
        if(Collision::checkCollision(bX, bY, bR, bottomRectX, bottomRectY, pipeWidth, pipeHeight) || Collision::checkCollision(bX, bY, bR, topRectX, topRectY, pipeWidth, pipeHeight))
            return true;
    }
    return false;
}