#ifndef PILLARS_H
#define PILLARS_H

#include <deque>
#include "Pillar.h"
#include "PillarPair.h"
#include <random>

class Pillars {
    private:
        std::mt19937 generator;
        std::uniform_real_distribution<float> random;
        std::deque<PillarPair*> pillars;

    public:
        Pillars();
        ~Pillars();
        void render();
        void update();
};

#endif