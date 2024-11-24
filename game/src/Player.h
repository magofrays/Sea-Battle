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

        void placeShip(std::shared_ptr<Ship> ship){
            play_field.placeShip(ship, ship_manager);
        }

        void placeShipsRandomly(int single_decks, int double_decks, int three_decks, int four_decks);

        void Handle(std::unique_ptr<Message> message){
            handler->Handle(std::move(message));
        }
        void setNext(messageHandler * handler){
            this->handler = handler;
        }

        json toJson();
};