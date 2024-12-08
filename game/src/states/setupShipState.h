#pragma once
#include "gameState.h"
#include "Game.h"
#include "playState.h"

class setupShipState: public gameState{
    int ships[4];
    bool is_vertical = true;
    playField & field;
    point2d & pointer;
    box2d & pointer_area;
    int length;
    public:
        setupShipState(Game * game, messageHandler * next, bool place_ships = true);
        
        void update();
        void main_action();
        void extra_action_0();
        void extra_action_1();
        
        bool enoughShips();
        void end();
        friend json & operator << (json & data, setupShipState & game_state);
        friend json & operator >> (json & data, setupShipState & game_state);
        void Handle(std::unique_ptr<Message> message);
};