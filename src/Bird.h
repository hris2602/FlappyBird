#ifndef BIRD_H
#define BIRD_H

#include "Shader.h"
#include "Collision.h"
#include "stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include "InputManager.h"

#define GRAVITY -9.0f
#define JUMP 3.5f
#define DELTATIME 0.016f

class Bird {
    private:
        glm::vec2 position;
        Shader* shader;
        Circle collision;
        GLuint EBO, VAO, VBO; 
        GLuint texture;
        GLfloat velocity;
    public:
        Bird();
        ~Bird();
        void render();
        void update();
        void changeProjection(const glm::mat4 & projection);
};

#endif