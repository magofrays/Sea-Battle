#pragma once

#include "playField.h"


class Player{
    public:
        playField * opponent_play_field;
        shipManager * opponent_ship_manager;
        playField play_field;
        shipManager ship_manager;
};