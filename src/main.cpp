#include <iostream>
#include "Application.h"

Application * app = nullptr;

int main(int argc, char* argv[]) {
    app = new Application();

    app->init();

    while (app->isRunning())
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        app->handleEvents();
        app->update();
        app->render();
    }
    
    app->clean();
    delete app;

    return 0;
}

// WINEDEBUG=-all wine build-win/FlappyBird.exe
// cmake --build build-win