#pragma once
#include "scannerAbility.h"
#include "doubleDamageAbility.h"
#include "shellingAbility.h"

class abilitiesManager{
    std::vector <std::unique_ptr<IAbility>> abilities;
    public:
        abilitiesManager();
        void createRandomAbility();
        void applyAbility(playField & play_field, shipManager & ship_manager);
};