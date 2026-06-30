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
        Shader* pillarShader;

        GLuint counter;

    public:
        Pillars(Shader* shader);
        ~Pillars();
        void render();
        void update();
        bool checkCollision(float bX, float bY, float bR);
        GLuint getCounter() const;
        void start();
        void setProjection(const glm::mat4& projection);
};

#endif