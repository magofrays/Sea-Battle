#pragma once
#include "IAbility.h"

class shellingAbility : public IAbility{
    public:
        abilityInfo info();
        void apply(humanPlayer * player);
};  