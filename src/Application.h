#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include "Bird.h"
#include <iostream>
#include "Pillars.h"
#include "TextRenderer.h"
#include "Button.h"
#include "Menu.h"


class Application {
    private:
        SDL_Window* window;
        SDL_GLContext glContext;
        bool running;
        Bird* bird;
        bool end;
        TextRenderer* textRenderer;

        Shader* pillarShader;
        
        //temp
        Pillars* pillars;
        Menu* menu;
    public:
        void init();
        bool isRunning();
        void render();
        void update();
        void handleEvents();
        void clean();
};

#endif