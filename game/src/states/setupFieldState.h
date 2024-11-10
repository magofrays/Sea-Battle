#pragma once
#include "gameState.h"
class setupFieldState: public gameState {
    int size_x;
    int size_y;
    public:
    void execute();

    void Handle(std::unique_ptr<Message> message);
    void createField();
};