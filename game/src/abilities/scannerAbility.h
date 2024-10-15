#pragma once
#include "IAbility.h"

class scannerAbility: public IAbility{
    std::pair<int, int> coordinates;
    public:
        scannerAbility() = default;
        scannerAbility(std::pair<int, int> coordinates);
        void setCoordinates(std::pair <int, int> coordinates);
        void apply(playField & play_field);
        ~scannerAbility() = default;
};