#pragma once
#include "IAbility.h"

class scannerAbility: public IAbility{
    public:
        abilityInfo info();
        void apply(humanPlayer * player);
};