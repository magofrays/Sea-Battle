#pragma once
#include "IAbility.h"

class shellingAbility : public IAbility{
    private:
        Player * player;
    public:
        shellingAbility(): player(nullptr){}
        void apply();
        void setPlayer(Player * player);
};  