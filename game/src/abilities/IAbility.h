#pragma once
#include "../playField.h"

class IAbility{
    public:
        virtual void apply(playField & play_field) = 0;
        virtual ~IAbility() = default;
};