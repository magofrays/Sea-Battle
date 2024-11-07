#pragma once
#include "IAbility.h"

class scannerAbility: public IAbility{
    public:
        void apply(humanPlayer * player);
};