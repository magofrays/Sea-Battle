#ifndef SEABATTLE_HUMANPLAYER_H
#define SEABATTLE_HUMANPLAYER_H

#include "Player.h"
#include "abilities/IAbility.h"
#include "abilities/abilitiesManager.h"


class humanPlayer: public Player{
    abilitiesManager abilities_manager;
    bool double_damage;
    std::shared_ptr<IAbility> current_ability;
    public:
            point2d pointer;
            box2d pointer_area;
            humanPlayer(): double_damage(false){}
            void getOpponent(Player * player);
            bool areaInField(box2d area, point2d coordinates);
            void Attack();
            bool getAbility();
            void useAbility();
            json toJson();
            friend class doubleDamageAbility;
            friend class scannerAbility;
            friend class shellingAbility;
};

#endif