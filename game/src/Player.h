#ifndef SEABATTLE_PLAYER_H
#define SEABATTLE_PLAYER_H

#include "playField.h"
#include "shipManager.h"
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
        
        
        void Handle(std::unique_ptr<Message> message){
            handler->Handle(std::move(message));
        }

        void setNext(messageHandler * handler){
            this->handler = handler;
        }
        
        void free(){
            point2d field_size = play_field.getArea().max_point;
            ship_manager = shipManager();
            play_field = playField(field_size);
        }
        void callculateShips(int ships[4]);
        
        void placeShipsRandomly(int ships[4]);

        friend json & operator << (json & data, Player & player); //write
        friend json & operator >> (json & data, Player & player); //read
};

#endif