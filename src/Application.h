#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include "Bird.h"
#include <iostream>


class Application {
    private:
        SDL_Window* window;
        SDL_GLContext glContext;
        bool running;
        Bird* bird;
    public:
        void init();
        bool isRunning();
        void render();
        void update();
        void handleEvents();
        void clean();
};

#endif