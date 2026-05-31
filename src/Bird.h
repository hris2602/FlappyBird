#ifndef BIRD_H
#define BIRD_H

#include "Shader.h"
#include "Collision.h"

class Bird {
    private:
        Shader* shader;
        Circle collision;
        GLuint EBO, VAO, VBO; 
    public:
        Bird();
        ~Bird();
        void render();
};

#endif