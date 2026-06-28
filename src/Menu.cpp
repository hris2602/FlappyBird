#include "Menu.h"

Menu::Menu(TextRenderer* textRenderer) : textRenderer(textRenderer) {
    shader = new Shader("src/menuVertexShader.glsl", "src/menuFragmentShader.glsl");
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    GLfloat verices[] = {
        -1.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, -1.0f,
        -1.0f, -1.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verices), verices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader->use();
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(400.0f, 300.0f, 0.0f));
    model = glm::scale(model, glm::vec3(200.0f, 270.0f, 1.0f));


    shader->setMat4("projection", projection);
    shader->setMat4("model", model);

    //button init
    buttonShader = new Shader("src/ButtonVertexShader.glsl", "src/ButtonFragmentShader.glsl");

    start = new Button(textRenderer, buttonShader, "START", glm::vec2(260.0f, 60.0f), glm::vec2(100.0f, 40.0f));
    exit = new Button(textRenderer, buttonShader, "EXIT", glm::vec2(440.0f, 60.0f), glm::vec2(100.0f, 40.0f));

    personalBest = "0";
    lastScore = "0";
}

Menu::~Menu() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete shader;
    delete start;
    delete exit;
    delete buttonShader;
}

void Menu::render() {
    shader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    start->render();
    exit->render();
    glm::vec2 gameoverSize = textRenderer->getTextSize("GAME OVER", 2.0f);
    textRenderer->renderText("GAME OVER", 400 - gameoverSize.x / 2, 490.0f, 2.0f);
    glm::vec2 lastScore = textRenderer->getTextSize("SCORE", 1.5f);
    textRenderer->renderText("SCORE", 260, 400.0f, 1.5f);
    glm::vec2 best = textRenderer->getTextSize("BEST", 1.5f);
    textRenderer->renderText("BEST", 540 - best.x, 400.0f, 1.5f);
    textRenderer->renderText(this->lastScore, 260 + (lastScore.x - textRenderer->getTextSize(this->lastScore, 2.5f).x) / 2, 340.0f, 2.5f);
    textRenderer->renderText(this->personalBest, (540 - best.x) + (best.x - textRenderer->getTextSize(this->personalBest, 2.5f).x) / 2, 340.0f, 2.5f);
}

void Menu::updateScore(unsigned int score) {
    lastScore = std::to_string(score);
    if(score > bestV) {
        bestV = score;
        personalBest = std::to_string(score);
    }
}

bool Menu::startButton() {
    bool one = start->isClicked(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
    bool two = InputManager::GetInstance().IsMouseButtonPressed(SDL_BUTTON_LEFT);
    // std::cout << one << " " << two << std::endl;
    return one && two;
}

