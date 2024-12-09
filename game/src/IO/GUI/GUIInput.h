#ifndef SEABATTLE_GUIINPUT_H
#define SEABATTLE_GUIINPUT_H

#include "../../messages/messageHandler.h"
#include "../../messages/keyMessage.h"
#include "../../RW/controlReader.h"

#include <SDL2/SDL.h>
#include <map>


class GUIInput: public messageHandler{
    
    messageHandler * handler = nullptr;
    std::map<std::string, Key> controls;

    public:
        void setControls();
        void update();
        void Handle(std::unique_ptr<Message> message);
        void setNext(messageHandler * handler);
};

#endif