#pragma once

#include "playField.h"
#include "messages/messageHandler.h"

class Player: public messageHandler{
    messageHandler * handler;
    public:
        playField * opponent_play_field;
        shipManager * opponent_ship_manager;
        playField play_field;
        shipManager ship_manager;
    
        template <typename T>
        void Handle(Message<T> message){
            handler->Handle(message);
        }
        void setNext(messageHandler * handler){
            this->handler = handler;
        }
};