#ifndef SEABATTLE_IABILITY_H
#define SEABATTLE_IABILITY_H

#include "abilityInfo.h"

class humanPlayer;
class IAbility{
    public:
        virtual abilityInfo info() = 0;
        virtual void apply(humanPlayer * player) = 0;
        virtual ~IAbility() {}
};

#endif