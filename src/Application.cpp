#include "Application.h"

void Application::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize SDL2: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    window = SDL_CreateWindow(
        "Flappy Bird",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        std::cout << "Failed to create SDL Window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    glContext = SDL_GL_CreateContext(window);
    if(!glContext) {
        std::cout << "Failed to create OpenGL Context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    std::cout << "Successfully loaded OpenGL " << glGetString(GL_VERSION) << std::endl;
    bird = new Bird();
    pillars = new Pillars();
    running = true;
    end = false;
    textRenderer = new TextRenderer(800, 600);
    InputManager::GetInstance().BindAction("Jump", SDL_SCANCODE_SPACE);
    textRenderer->load("sprites/Black_Ops_One/BlackOpsOne-Regular.ttf", 20);
}

bool Application::isRunning() {
    return running;
}

void Application::render() {
    glClearColor(0.2f, 0.6f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    bird->render();
    pillars->render();
    textRenderer->renderText("0", 100.0f, 100.0f, 2.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    SDL_GL_SwapWindow(window);
}

void Application::update() {
    glm::vec2 birdPos = bird->getPosition();
    if(!pillars->checkCollision(birdPos.x, birdPos.y, bird->getRadius()) && !end) {
        bird->update();
        pillars->update();
    } else {
        end = true;
    }
}

void Application::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    float newWidth = event.window.data1;
                    float newHeight = event.window.data2;
                    
                    float aspectRatio = newWidth / newHeight;

                    glm::mat4 projection = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
                    bird->changeProjection(projection);

                    glViewport(0,0, newWidth, newHeight);
                }
                break;
            default:
                break;
        }
    }
}

void Application::clean() {
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(glContext);
    SDL_Quit();
}