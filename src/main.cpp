#include <iostream>
#include "Application.h"

Application * app = nullptr;

int main(int argc, char* argv[]) {
    app = new Application();

    app->init();

    while (app->isRunning())
    {
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