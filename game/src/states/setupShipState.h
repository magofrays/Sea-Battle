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
    public:
        setupShipState(Game * game);
        void execute();
        void end();

        void Handle(std::unique_ptr<Message> message);
    friend Game;
};