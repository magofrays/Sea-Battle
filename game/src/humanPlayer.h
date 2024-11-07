#include "Player.h"
#include "abilities/IAbility.h"
#include "console/input/inputManager.h"
#include "console/output/outputManager.h"
#include "abilities/abilitiesManager.h"


class humanPlayer: public Player{
    point2d pointer;
    abilitiesManager abilities_manager;
    inputManager & input_manager;
    outputManager & output_manager;
    bool double_damage;
    public:
            humanPlayer(inputManager & im, outputManager & om):input_manager(im), output_manager(om), double_damage(false){}
            void getOpponent(Player * player);
            void placeShip();
            void Attack();
            void useAbility();
            friend class Game;
            friend class doubleDamageAbility;
            friend class scannerAbility;
            friend class shellingAbility;
};