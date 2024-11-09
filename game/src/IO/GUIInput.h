#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gameInput.h"
#include "../messages/Message.h"

class GUIInput: public gameInput{
    Action transformKey(SDL_Keycode key);
    Message update();
    
    template <typename T>
    void Handle(Message<T> message);
};