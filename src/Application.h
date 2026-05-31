#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>

class Application {
    private:
        SDL_Window* window;
        SDL_GLContext glContext;
        bool running;

    public:
        void init();
        bool isRunning();
        void render();
        void update();
        void handleEvents();
        void clean();
};

#endif