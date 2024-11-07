#pragma once
#include "IAbility.h"

class shellingAbility : public IAbility{
    public:
        void apply(humanPlayer * player);
};  