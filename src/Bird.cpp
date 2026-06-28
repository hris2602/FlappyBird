#include "Bird.h"

Bird::Bird() {
    shader = new Shader("src/birdVertexShader.glsl", "src/birdFragmentShader.glsl");
    velocity = 0.0f;
    radius = 0.09f;

    float vertices[] = {
        -0.15, -0.15, 0.0,    0.0, 0.0,
        -0.15,  0.15, 0.0,    0.0, 1.0,
         0.15, -0.15, 0.0,    1.0, 0.0,
         0.15,  0.15, 0.0,    1.0, 1.0 
    };

    GLuint indices[] = {
        0,2,3,
        0,3,1
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("sprites/Bird.png", &width, &height, &nrChannels, 0);
    if(data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load image" << std::endl;
    }

    stbi_image_free(data);

    float windowWidth = 800.0f;
    float windowHeight = 600.0f;
    float aspectRatio = windowWidth / windowHeight;

    glm::mat4 projection = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);


    position = glm::vec2(0.0f, 0.0f);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));


    shader->use();

    shader->setInt("ourTexture", 0);
    shader->setMat4("projection", projection);
    shader->setMat4("model", model);
}

Bird::~Bird() {
    delete shader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);
}

void Bird::render() {
    shader->use();

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Bird::update() {
    if(InputManager::GetInstance().IsActionPressed("Jump")) {
       velocity = JUMP;
    }

    velocity += GRAVITY * DELTATIME;
    position.y += velocity * DELTATIME;

    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    shader->use();
    shader->setMat4("model", model);
}


void Bird::changeProjection(const glm::mat4 & projection) {
    shader->use();
    shader->setMat4("projection", projection);
}

glm::vec2 Bird::getPosition() {
    return position;
}

GLfloat Bird::getRadius() {
    return radius;
}

void Bird::start() {
    velocity = 0.0f;

    position = glm::vec2(0.0f, 0.0f);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    shader->use();
    shader->setMat4("model", model);
}
