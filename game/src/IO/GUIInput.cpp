#include "GUIInput.h"
#include "../RW/fileRead.h"
#include "../utilities/settings.h"

GUIInput::GUIInput(){
    json controls_data;
    fileRead reader(seabattle::CONTROL_DIR);
    reader.read(controls_data);
    controls[controls_data["pointer_down"]] = Key::pointer_down;
    controls[controls_data["pointer_left"]] = Key::pointer_left;
    controls[controls_data["pointer_up"]] = Key::pointer_up;
    controls[controls_data["pointer_right"]] = Key::pointer_right;
    controls[controls_data["main_action"]] = Key::main_action;
    controls[controls_data["extra_action_0"]] = Key::extra_action_0;
    controls[controls_data["extra_action_1"]] = Key::extra_action_1;
    controls[controls_data["save_action"]] = Key::save_action;
    controls[controls_data["load_action"]] = Key::load_action;
    controls[controls_data["quit"]] = Key::quit;
}


void GUIInput::update(){
    SDL_Event event;
    
    while (SDL_PollEvent(&event) != 0){
        switch(event.type){
            case SDL_QUIT:
                Handle(keyMessage(Key::quit).clone());
                break;
            case SDL_KEYDOWN:
                std::string key_name = SDL_GetKeyName(event.key.keysym.sym);
                if(controls.contains(key_name)){
                    Handle(keyMessage(controls[key_name]).clone());
                }
        }
    }
}

void GUIInput::Handle(std::unique_ptr<Message> message){
    handler->Handle(std::move(message));
}

void GUIInput::setNext(messageHandler * handler){
    this->handler = handler;
}