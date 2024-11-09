#include "GUIInput.h"

Action GUIInput::transformKey(SDL_Keycode key){
    switch (key) {
    case SDLK_w:
        return Action::pointer_up;
    case SDLK_a:
        return Action::pointer_left;
    case SDLK_s:
        return Action::pointer_down;
    case SDLK_d:
        return Action::pointer_right;
    case SDLK_RETURN:
        return Action::main_action;
    case SDLK_e:
        return Action::extra_action;
    default:
        return Action::null;
    }
}

void GUIInput::update(){
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0){
        switch(e.type){
            case SDL_QUIT:
                return Message<Action>(Action::quit);
            case SDL_KEYDOWN:
                return Message<Action>(transformKey(e.key.keysym.sym));
        }
    }
}

template <typename T>
void GUIInput::Handle(Message<T> message){
    //different messages
}