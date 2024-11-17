#pragma once
#include "gameState.h"
#include "Game.h"

class setupShipState: public gameState{
    int single_decks;
    int double_decks;
    int three_decks;
    int four_decks;
    bool is_vertical = true;
    playField & field;
    point2d & pointer;
    box2d pointer_area;
    int length;
    public:
        setupShipState(Game * game);
        void execute();
        bool enoughShips();
        bool shipInField(box2d area, point2d coordinates);
        void placeShip();
        void end(){}
        
        void Handle(std::unique_ptr<Message> message);
    friend Game;
};