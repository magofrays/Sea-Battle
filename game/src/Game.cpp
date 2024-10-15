#include "playField.h"
#include "abilities/scannerAbility.h"
#include "abilities/doubleDamageAbility.h"
#include "abilities/shellingAbility.h"
int main(){
    shipManager ship_manager;
    playField game(5, 5, ship_manager);
    shipManager & other_manager = game.getShipManager();
    doubleDamageAbility double_damage;
    scannerAbility scan({0, 0});
    game.addShip(3, {0, 0}, false);
    game.addShip(1, {4, 4}, false);
    game.addShip(2, {4, 0}, true);
    double_damage.setCoordinates({0, 0});
    /*for(int i = 0; i != 5; i++){
        for(int j = 0; j != 5; j++){
            game.Attack({i, j});
        }
    }*/
    game.printField();
    scan.apply(game);
    std::cout << game.getShipManager().getShip(0).getSegment(0) << "\n";
    double_damage.apply(game);
    std::cout << game.getShipManager().getShip(0).getSegment(0) << "\n";
}