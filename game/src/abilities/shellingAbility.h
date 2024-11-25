#ifndef SEABATTLE_SHELLINGABILITY_H
#define SEABATTLE_SHELLINGABILITY_H

#include "IAbility.h"

class shellingAbility : public IAbility{
    public:
        abilityInfo info();
        void apply(humanPlayer * player);
};

#endif