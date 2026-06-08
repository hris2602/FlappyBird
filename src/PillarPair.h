#ifndef PILLARPAIR_H
#define PILLARPAIR_H

#include "Pillar.h"

class PillarPair {
    private:
        Pillar* bottom;
        Pillar* top;

    public:
        PillarPair(float x, float gap_y, float gap_height);
        ~PillarPair();
        void render();
        void update();
        float getXPosition();
        void recycle(float x, float gapCenter_y, float gap_height);
};

#endif