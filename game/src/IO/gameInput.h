#pragma once
#include "../messages/messageHandler.h"
#include "../messages/keyMessage.h"

class gameInput: public messageHandler{
    protected:
        messageHandler * handler;
    public:
        virtual void update() = 0;
        
        virtual void Handle(std::unique_ptr<Message> message) = 0;
        void setNext(messageHandler * handler){
            this->handler = handler;
        }
};