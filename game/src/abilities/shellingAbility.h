#pragma once
#include <random>
#include "IAbility.h"

class shellingAbility{
    public:
        shellingAbility() = default;
        void apply(playField & play_field);
};  