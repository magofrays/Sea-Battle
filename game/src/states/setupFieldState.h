#pragma once
#include "gameState.h"
#include "Game.h"

class setupFieldState: public gameState {
    int size_x;
    int size_y;
    playField play_field;
    public:
        setupFieldState() = default;
        setupFieldState(Game * game, messageHandler * next):gameState(game), size_x(2), size_y(2){
            this->handler = next;
            Handle(textMessage("Create your field!", {255, 255, 0, 255}, textPosition::title).clone());
        }
        void execute();

        void Handle(std::unique_ptr<Message> message);
        void end();
        friend json & operator << (json & data, setupFieldState & game_state);
        friend json & operator >> (json & data, setupFieldState & game_state);
    friend Game;
};