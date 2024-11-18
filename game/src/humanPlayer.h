#pragma once
#include "Player.h"
#include "abilities/IAbility.h"
#include "abilities/abilitiesManager.h"


class humanPlayer: public Player{
    abilitiesManager abilities_manager;
    bool double_damage;
    public:
            point2d pointer;
            humanPlayer(): double_damage(false){}
            void getOpponent(Player * player);

            void Attack();
            std::shared_ptr<IAbility> useAbility();
            friend class doubleDamageAbility;
            friend class scannerAbility;
            friend class shellingAbility;
};