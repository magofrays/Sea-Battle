#ifndef SEABATTLE_GUIINPUT_H
#define SEABATTLE_GUIINPUT_H

#include "../messages/messageHandler.h"
#include "../messages/keyMessage.h"
#include "gameController.h"

#include <SDL2/SDL.h>
#include <map>


class GUIInput: public messageHandler{
    
    messageHandler * handler = nullptr;
    std::map<std::string, Key> controls;

    public:
        GUIInput();
        void update();
        void Handle(std::unique_ptr<Message> message);
        void setNext(messageHandler * handler);
};

#endif