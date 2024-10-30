#pragma once
#include "../playField.h"

class Player;
class IAbility{
    public:
        virtual void apply() = 0;
        virtual void setPlayer(Player * player) = 0;
        virtual ~IAbility() {}
};