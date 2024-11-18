#pragma once
#include "IAbility.h"

class doubleDamageAbility: public IAbility{
    public:
        abilityInfo info();
        void apply(humanPlayer * player);
};