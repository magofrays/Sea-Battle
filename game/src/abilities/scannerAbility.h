#ifndef SEABATTLE_SCANNERABILITY_H
#define SEABATTLE_SCANNERABILITY_H

#include "IAbility.h"

class scannerAbility: public IAbility{
    public:
        abilityInfo info();
        void apply(humanPlayer * player);
};

#endif