#include <iostream>
#include "Application.h"

Application * app = nullptr;

int main(int argc, char* argv[]) {
    app = new Application();

    app->init();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (app->isRunning())
    {
        InputManager::GetInstance().update();
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
//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