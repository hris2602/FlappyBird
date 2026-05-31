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
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
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
    running = true;
}

bool Application::isRunning() {
    return running;
}

void Application::render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    bird->render();
    SDL_GL_SwapWindow(window);
}

void Application::update() {

}

void Application::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type){
            case SDL_QUIT:
                running = false;
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