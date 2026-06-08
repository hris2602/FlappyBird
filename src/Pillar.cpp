#include "Pillar.h"

Pillar::Pillar(float startX, float startY) : position(startX, startY) {
    float vertices[] = {
        0.5f, 1.0f, 0.0f,
        0.5f, -1.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,
        -0.5f, 1.0f, 0.0f 
    };

    GLuint indices[] = {
        3, 2, 1,
        0, 3, 1
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader = new Shader("src/pillarVertexShader.glsl", "src/pillarFragmentShader.glsl");
    shader->use();

    float windowWidth = 800.0f;
    float windowHeight = 600.0f;
    float aspectRatio = windowWidth / windowHeight;

    glm::mat4 projection = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
    shader->setMat4("projection", projection);
    shader->use();
    // position = glm::vec2(1.3f, -1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::scale(model, glm::vec3(0.3f, 2.0f, 1.0f));


    shader->setMat4("model", model);
}

void Pillar::render() {
    shader->use();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


Pillar::~Pillar() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Pillar::update() {
    shader->use();
    position.x -= 1.5 * 0.016f;
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::scale(model, glm::vec3(0.3f, 2.0f, 1.0f));


    shader->setMat4("model", model);
}

float Pillar::getXPosition() {
    return position.x;
}

void Pillar::recycle(float x, float y){
    position = glm::vec2(x, y);

    shader->use();
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::scale(model, glm::vec3(0.3f, 2.0f, 1.0f));


    shader->setMat4("model", model);
}
