#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

class InputManager {
    private:
        InputManager();


        int numkeys;
        const Uint8 * currentKeyboardState;
        std::vector<Uint8> previousKeyboardState;
        std::unordered_map<std::string, SDL_Scancode> actionBinding; 
    public:
        static InputManager & GetInstance() {
            static InputManager instance;
            return instance;
        }

        void update();

        void BindAction(const std::string & action, SDL_Scancode key);

        bool isKeyPressed(SDL_Scancode key) const;
        
        bool IsActionPressed(const std::string& actionName) const;
};

#endif