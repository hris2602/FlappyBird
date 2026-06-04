#include "InputManager.h"
#include <cstring>

InputManager::InputManager() {
    currentKeyboardState = SDL_GetKeyboardState(&numkeys);

    previousKeyboardState.resize(numkeys, 0);
}

void InputManager::update() {
    std::memcpy(previousKeyboardState.data(), currentKeyboardState, numkeys);
}

void InputManager::BindAction(const std::string & action, SDL_Scancode key){  
    actionBinding[action] = key;
}

bool InputManager::IsActionPressed(const std::string& actionName) const {
    auto it = actionBinding.find(actionName);
    if (it != actionBinding.end()) return isKeyPressed(it->second);
    return false;
}

bool InputManager::isKeyPressed(SDL_Scancode key) const {
    return currentKeyboardState[key] == 1 && previousKeyboardState[key] == 0;
}