#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include "TextRenderer.h"
#include "Shader.h"
#include "InputManager.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>


#include <string>

class Menu {
    private:
        Button* start;
        Button* exit;
        TextRenderer* textRenderer;
        Shader* shader;
        Shader* buttonShader;
        GLuint VAO, VBO, EBO;

        std::string personalBest;
        unsigned int bestV;
        std::string lastScore;

        
    public:
        Menu(TextRenderer* textRenderer);
        ~Menu();
        void render();
        void updateScore(unsigned int score);
        bool startButton(int windowWidth, int windowHeight);
};

#endif