#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include "Bird.h"
#include <iostream>
#include "Pillars.h"
#include "TextRenderer.h"


class Application {
    private:
        SDL_Window* window;
        SDL_GLContext glContext;
        bool running;
        Bird* bird;
        bool end;
        TextRenderer* textRenderer;


        //temp
        Pillars* pillars;
    public:
        void init();
        bool isRunning();
        void render();
        void update();
        void handleEvents();
        void clean();
};

#endif