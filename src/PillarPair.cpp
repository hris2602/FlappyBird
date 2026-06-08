#include "PillarPair.h"

PillarPair::PillarPair(float x, float gapCenter_y, float gap_height) {
    bottom = new Pillar(x, gapCenter_y - (gap_height / 2.0f) - 2.0f);
    top = new Pillar(x, gapCenter_y + (gap_height / 2.0f) + 2.0f);
}

PillarPair::~PillarPair(){
    delete bottom;
    delete top;
}

void PillarPair::render(){
    bottom->render();
    top->render();
}

void PillarPair::update() {
    bottom->update();
    top->update();
}

float PillarPair::getXPosition() {
    return bottom->getXPosition();
}

void PillarPair::recycle(float x, float gapCenter_y, float gap_height) {
    bottom->recycle(x, gapCenter_y - (gap_height / 2.0f) - 2.0f);
    top->recycle(x, gapCenter_y + (gap_height / 2.0f) + 2.0f);
}
