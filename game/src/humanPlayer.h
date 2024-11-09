#include "Player.h"
#include "abilities/IAbility.h"
#include "console/input/inputManager.h"
#include "console/output/outputManager.h"
#include "abilities/abilitiesManager.h"


class humanPlayer: public Player{
    point2d pointer;
    abilitiesManager abilities_manager;
    bool double_damage;
    public:
            humanPlayer(): double_damage(false){}
            void getOpponent(Player * player);
            void placeShip();
            void Attack();
            void useAbility();
            friend class Game;
            friend class doubleDamageAbility;
            friend class scannerAbility;
            friend class shellingAbility;
};