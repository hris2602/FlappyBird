#ifndef PILLAR_H
#define PILLAR_H

#include <glad/glad.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Pillar {
    private:
        glm::vec2 position;
        Shader* shader;
        GLuint VAO, VBO, EBO;
    public:
        void render();
        Pillar(float startX, float startY);
        ~Pillar();
        void update();
        float getXPosition();
        void recycle(float x, float y);
};

#endif