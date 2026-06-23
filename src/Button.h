#ifndef BUTTON_H
#define BUTTON_H

#include "Shader.h"
#include <glad/glad.h>
#include "TextRenderer.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Button {
    private:
        TextRenderer* textRenderer;
        Shader* shader;
        GLuint VAO, VBO, EBO;
        glm::vec3 buttonColor;

        glm::vec2 position;
        glm::vec2 size;

        std::string text;
        glm::vec3 textColor;
        GLfloat scale;
    public:
        Button(TextRenderer* textRenderer, Shader* shader, const std::string& text, glm::vec2 pos, glm::vec2 size, glm::vec3 buttonColor = glm::vec3(0.3f), glm::vec3 textColor = glm::vec3(1.0f), float scale = 1.0f);
        ~Button();
        void render();
        bool isClicked(float x, float y);
};

#endif