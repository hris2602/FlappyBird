#ifndef BIRD_H
#define BIRD_H

#include "Shader.h"
#include "Collision.h"
#include "stb_image.h"
#include <glm/gtc/matrix_transform.hpp>

class Bird {
    private:
        Shader* shader;
        Circle collision;
        GLuint EBO, VAO, VBO; 
        GLuint texture;
    public:
        Bird();
        ~Bird();
        void render();
        void update();
        
};

#endif