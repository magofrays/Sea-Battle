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

        void setField(playField field){
            play_field = field;
        }
        void Handle(std::unique_ptr<Message> message){
            handler->Handle(message->clone());
        }
        void setNext(messageHandler * handler){
            this->handler = handler;
        }
};