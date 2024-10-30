#pragma once
#include "playField.h"

class outputManager{
    std::ostream & os;
    public:
        outputManager(std::ostream & os);
        void drawField(playField & play_field, bool fog);
        void drawMessage(std::string message);
        void update();
};