#pragma once
#include "IAbility.h"

class shellingAbility : public IAbility{
    public:
        shellingAbility() = default;
        void apply(playField & play_field);
};  