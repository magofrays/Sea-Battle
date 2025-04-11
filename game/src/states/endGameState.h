#ifndef SEABATTLE_ENDGAMESTATE_H
#define SEABATTLE_ENDGAMESTATE_H

#include "gameState.h"

class endGameState : public gameState
{
    bool lost;
    int round_number;

public:
    endGameState(Game *game, messageHandler *next, bool lost, int round_number);
    void update();
    void main_action();
    void extra_action_0();
    void extra_action_1();
    void Handle(std::unique_ptr<Message> message);
    void end();
    friend json &operator<<(json &data, endGameState &game_state);
    friend json &operator>>(json &data, endGameState &game_state);
};

#endif