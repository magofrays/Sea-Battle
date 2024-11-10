#include "GUIInput.h"

Key GUIInput::transformKey(SDL_Keycode key){
    switch (key) {
    case SDLK_w:
        return Key::pointer_up;
    case SDLK_a:
        return Key::pointer_left;
    case SDLK_s:
        return Key::pointer_down;
    case SDLK_d:
        return Key::pointer_right;
    case SDLK_RETURN:
        return Key::main_action;
    case SDLK_e:
        return Key::extra_action;
    default:
        return Key::null;
    }
}

void GUIInput::update(){
    SDL_Event event;
    std::unique_ptr<keyMessage> key = std::make_unique<keyMessage>();
    while (SDL_PollEvent(&event) != 0){
        switch(event.type){
            case SDL_QUIT:
                key->info = Key::quit;
                break;
            case SDL_KEYDOWN:
                key->info = transformKey(event.key.keysym.sym);
        }
    }
    Handle(key->clone());
}

void GUIInput::Handle(std::unique_ptr<Message> message){
    handler->Handle(message->clone());
}