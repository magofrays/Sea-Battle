#pragma once
#include "playField.h"
class inputManager{
    std::istream & is;
    public:
        inputManager(std::istream & is);
        void inputCoordinates(point2d & coordinates);
        void inputShip(std::shared_ptr<Ship> ship);
        void inputAction(char & c);
};

