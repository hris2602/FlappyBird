#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <string>
#include <glad/glad.h>
#include "Shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H

struct Charachter
{
    unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;   
};


class TextRenderer {
    private:
        std::map<char, Charachter> characters;
        Shader* shader;
        GLuint VAO, VBO, EBO;
    
    public:
        TextRenderer(float width, float height);
        ~TextRenderer();
        void load(std::string font, unsigned int fontSize);
        void renderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
        glm::vec2 getTextSize(std::string text, float scale);
};

#endif