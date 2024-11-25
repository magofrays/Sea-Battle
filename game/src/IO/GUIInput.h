#ifndef SEABATTLE_GUIINPUT_H
#define SEABATTLE_GUIINPUT_H

#include "../messages/messageHandler.h"

#include "../messages/keyMessage.h"

#include <SDL2/SDL.h>

class GUIInput: public messageHandler{
    
    messageHandler * handler = nullptr;

    public:
    Key transformKey(SDL_Keycode key);
    void update();
    void Handle(std::unique_ptr<Message> message);

    void setNext(messageHandler * handler){
            this->handler = handler;
        }
};

#endif