#pragma once
#include "../playField.h"

class Player;
class IAbility{
    public:
        virtual void apply(Player * player) = 0;
        virtual ~IAbility() {}
};