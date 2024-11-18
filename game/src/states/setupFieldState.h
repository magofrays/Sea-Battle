#pragma once
#include "gameState.h"
#include "Game.h"

class setupFieldState: public gameState {
    int size_x;
    int size_y;
    public:
    setupFieldState(Game * game):gameState(game), size_x(1), size_y(1){}
    void execute();

    void Handle(std::unique_ptr<Message> message);
    void createField();
};