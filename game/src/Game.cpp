#include "playField.h"
#include "abilities/abilitiesManager.h"
int main(){
    shipManager ship_manager;
    playField game(5, 5, ship_manager);
    game.addShip(3, {0, 0}, false);
    game.addShip(1, {4, 4}, false);
    game.addShip(2, {4, 0}, true);
    abilitiesManager abilities_manager;
    abilities_manager.applyAbility(game);
    abilities_manager.applyAbility(game);
    abilities_manager.applyAbility(game);
} 