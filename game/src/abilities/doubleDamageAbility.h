#pragma once
#include "IAbility.h"

class doubleDamageAbility: public IAbility{
    Player * player;
    public:
        doubleDamageAbility(): player(nullptr){}
        void apply();
        void setPlayer(Player * player);
};