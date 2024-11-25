#ifndef SEABATTLE_DOUBLEDAMAGEABILITY_H
#define SEABATTLE_DOUBLEDAMAGEABILITY_H

#include "IAbility.h"

class doubleDamageAbility: public IAbility{
    public:
        abilityInfo info();
        void apply(humanPlayer * player);
};

#endif