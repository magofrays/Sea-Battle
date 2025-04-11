#pragma once
#include "gameState.h"
#include "Game.h"

class setupFieldState : public gameState
{
    point2d &pointer;
    playField play_field;

public:
    setupFieldState(Game *game, messageHandler *next);

    void update();
    void main_action();
    void extra_action_0();
    void extra_action_1();

    void Handle(std::unique_ptr<Message> message);
    void end();
    friend json &operator<<(json &data, setupFieldState &game_state);
    friend json &operator>>(json &data, setupFieldState &game_state);
};