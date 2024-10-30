#pragma once
#include "IAbility.h"

class scannerAbility: public IAbility{
    Player * player;
    public:
        scannerAbility(): player(nullptr){}
        void apply();
        void setPlayer(Player * player);
};