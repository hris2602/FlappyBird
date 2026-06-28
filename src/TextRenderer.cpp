#include "TextRenderer.h"

TextRenderer::TextRenderer(float width, float height) {
    shader = new Shader("src/TextRendererVertex.glsl", "src/TextRendererFragment.glsl");
    shader->use();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    shader->setMat4("projection", projection);
    shader->setInt("text", 0);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    GLuint indices[] = {
        0, 2, 1,
        2, 3, 1
    };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
}

TextRenderer::~TextRenderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void TextRenderer::load(std::string font, unsigned int fontSize) {
    this->characters.clear();
    FT_Library ft;
    if(FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face)) 
    {
        std::cout << "ERROR::FREETYPE: Failed to load font:" << font << std::endl;
        return;
    }
    

    FT_Set_Pixel_Sizes(face, 0, fontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned char i = 0; i < 128; i++)
    {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Charachter charachter = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        characters.insert(std::pair<char, Charachter>(i, charachter));
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::renderText(std::string text, float x, float y, float scale, glm::vec3 color) {
    shader->use();
    shader->setVec3("color", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for(char c : text) {
        Charachter ch = characters[c];
        float xPos = x + ch.Bearing.x * scale;
        float yPos = y - (ch.Size.y - ch.Bearing.y) * scale;
        float width = ch.Size.x * scale;
        float height = ch.Size.y * scale;

        float vertices[] = {
            xPos, yPos + height, 0.0, 0.0f,
            xPos + width, yPos + height, 1.0f, 0.0f,
            xPos, yPos, 0.0f, 1.0f,
            xPos + width, yPos, 1.0f, 1.0f
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        x += (ch.Advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

glm::vec2 TextRenderer::getTextSize(std::string text, float scale) {
    float totalWidth = 0.0f;
    float maxHeight = 0.0f;

    for (char c : text) {
        Charachter ch = characters[c];

        totalWidth += (ch.Advance >> 6) * scale;

        float charHeight = ch.Size.y * scale;
        if (charHeight > maxHeight) {
            maxHeight = charHeight;
        }
    }

    return glm::vec2(totalWidth, maxHeight);
}
