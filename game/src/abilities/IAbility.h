#pragma once
#include "../playField.h"
#include "abilityInfo.h"

class humanPlayer;
class IAbility{
    public:
        virtual abilityInfo info() = 0;
        virtual void apply(humanPlayer * player) = 0;
        virtual ~IAbility() {}
};