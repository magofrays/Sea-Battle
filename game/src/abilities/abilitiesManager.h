#pragma once
#include "scannerAbility.h"
#include "doubleDamageAbility.h"
#include "shellingAbility.h"
#include "errors/errors.h"
class Player;
class abilitiesManager{
    std::queue <std::shared_ptr<IAbility>> abilities;
    public:
        abilitiesManager();
        void createRandomAbility();
        void applyAbility(Player * player);
};

