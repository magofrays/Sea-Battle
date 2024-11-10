#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gameInput.h"

class GUIInput: public gameInput{
    Key transformKey(SDL_Keycode key);
    void update();
    
    void Handle(std::unique_ptr<Message> message);
};