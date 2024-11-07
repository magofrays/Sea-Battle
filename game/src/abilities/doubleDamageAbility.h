#pragma once
#include "IAbility.h"

class doubleDamageAbility: public IAbility{
    public:
        void apply(Player * player);
};