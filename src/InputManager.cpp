#include "InputManager.h"
#include <cstring>

InputManager::InputManager() {
    currentKeyboardState = SDL_GetKeyboardState(&numkeys);

    previousKeyboardState.resize(numkeys, 0);

    currentMouseState = 0;
    previousMouseState = 0;
    mouseX = 0;
    mouseY = 0;
}

void InputManager::update() {
    std::memcpy(previousKeyboardState.data(), currentKeyboardState, numkeys);


    previousMouseState = currentMouseState;
    currentMouseState = SDL_GetMouseState(&mouseX, &mouseY);
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

bool InputManager::IsMouseButtonPressed(Uint8 button) const {
    return (currentMouseState & SDL_BUTTON(button)) != 0 && (previousMouseState & SDL_BUTTON(button)) == 0;
}
