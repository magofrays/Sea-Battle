#pragma once
#include "../playField.h"

class humanPlayer;
class IAbility{
    public:
        virtual void apply(humanPlayer * player) = 0;
        virtual ~IAbility() {}
};