#include "PillarPair.h"

PillarPair::PillarPair(float x, float gapCenter_y, float gap_height, Shader* shader) {
    bottom = new Pillar(x, gapCenter_y - (gap_height / 2.0f) - 2.0f, shader);
    top = new Pillar(x, gapCenter_y + (gap_height / 2.0f) + 2.0f, shader);

    passed = false;
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

glm::vec2 PillarPair::getBottomPosition() {
    return bottom->getPosition();
}

glm::vec2 PillarPair::getTopPosition() {
    return top->getPosition();
}

void PillarPair::recycle(float x, float gapCenter_y, float gap_height) {
    bottom->recycle(x, gapCenter_y - (gap_height / 2.0f) - 2.0f);
    top->recycle(x, gapCenter_y + (gap_height / 2.0f) + 2.0f);
    passed = false;
}

bool PillarPair::isPassed() const {
    return passed;
}
void PillarPair::pass() {
    passed = true;
}