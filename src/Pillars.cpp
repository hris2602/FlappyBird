#include "Pillars.h"

Pillars::Pillars() : generator(std::random_device{}()), random(-0.4f, 0.4f) {
    float start = 3.3f;
    for (size_t i = 0; i < 10; i++)
    {
        float gapY = random(generator);
        PillarPair* spawn = new PillarPair(start, gapY, 0.6f);
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
    for(auto& pair :pillars) {
        pair->render();
    }
}

void Pillars::update() {
    for(auto& pair :pillars) {
        pair->update();
    }

    if (!pillars.empty() && pillars.front()->getXPosition() <= -3.0f) {
        float x = pillars.back()->getXPosition();
        pillars.front()->recycle(x + 1.7f, random(generator), 0.6f);
        PillarPair* front = pillars.front();
        pillars.pop_front();
        pillars.push_back(front);
    }
}