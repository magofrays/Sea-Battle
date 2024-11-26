#ifndef SEABATTLE_ENDGAMESTATE_H
#define SEABATTLE_ENDGAMESTATE_H

#include "gameState.h"

class endGameState: public gameState{
    bool lost;
    public:
        endGameState(bool lost):lost(lost){}
        void execute();
        void Handle(std::unique_pte<Message> message);
        void end();
        friend json & operator << (json & data, endGameState & game_state);
        friend json & operator >> (json & data, endGameSt & game_state);
}

#endif