#ifndef SEABATTLE_TUIINPUT_H
#define SEABATTLE_TUIINPUT_H

#include "../../messages/messageHandler.h"
#include "../../messages/keyMessage.h"

#include <map>


class TUIInput: public messageHandler{
    messageHandler * handler = nullptr;
    std::map<std::string, Key> controls;

    public:
        void setControls();
        void update();
        void Handle(std::unique_ptr<Message> message);
        void setNext(messageHandler * handler);
};

#endif