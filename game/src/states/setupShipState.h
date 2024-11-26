#pragma once
#include "gameState.h"
#include "Game.h"
#include "playState.h"

class setupShipState: public gameState{
    int single_decks;
    int double_decks;
    int three_decks;
    int four_decks;
    bool is_vertical = true;
    playField & field;
    point2d & pointer;
    box2d & pointer_area;
    int length;
    public:
        setupShipState(Game * game, bool bot_places_ships = true);
        void execute();
        bool enoughShips();
        void placeShip();
        void end();
        friend json & operator << (json & data, setupShipState & game_state);
        friend json & operator >> (json & data, setupShipState & game_state);
        void Handle(std::unique_ptr<Message> message);
    friend Game;
};