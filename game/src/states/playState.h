#pragma once
#include "gameState.h"

class playState: public gameState{
    point2d & pointer;
    box2d & pointer_area;
    int round_number;
    public:
        bool input = false;
        playState() = default;
        playState(Game * game, int round_number = 0);
        void execute();
        void end(){}
        void usingAbility();
        void lose();
        void win();
        void Handle(std::unique_ptr<Message> message);
        friend json & operator << (json & data, playState & game_state);
        friend json & operator >> (json & data, playState & game_state);
};