#pragma once
#include "IAbility.h"

class scannerAbility: public IAbility{
    public:
        void apply(Player * player);
};