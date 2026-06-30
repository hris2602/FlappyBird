#include "Button.h"

Button::Button(TextRenderer* textRenderer, Shader* shader, const std::string& text,
                 glm::vec2 pos, glm::vec2 size, glm::vec3 buttonColor,
                  glm::vec3 textColor, GLfloat scale) : position(pos), textRenderer(textRenderer),
                                                                                 text(text), scale(scale), size(size), 
                                                                                 buttonColor(buttonColor), textColor(textColor), shader(shader) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    float vertices[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    shader->use();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
    shader->setMat4("projection", projection);
}



Button::~Button() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Button::render() {
    shader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f)); 

    shader->setVec3("color", buttonColor);
    shader->setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glm::vec2 textSize = textRenderer->getTextSize(this->text, scale);

    float textX = position.x + ((size.x - textSize.x) / 2);
    float textY = position.y + ((size.y - textSize.y) / 2);
    textRenderer->renderText(text, textX, textY, scale, textColor);
}

bool Button::isClicked(float x, float y) {
    y = 600.0f - y;
    float width, height;

    return (x >= position.x && x <= position.x + size.x) && (y >= position.y && y <= position.y + size.y);
}