#pragma once
#include "IAbility.h"

class doubleDamageAbility: public IAbility{
    std::pair <int, int> coordinates;
    public:
        doubleDamageAbility() = default;
        doubleDamageAbility(std::pair <int, int> coordinates);
        void setCoordinates(std::pair <int, int> coordinates);
        void apply(playField & play_field);
        ~doubleDamageAbility() = default;
};