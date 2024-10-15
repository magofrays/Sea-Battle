#include "shellingAbility.h"

void shellingAbility::apply(playField & play_field){
    std::srand(std::time(nullptr));
    shipManager & ship_manager = play_field.getShipManager();
    int ships_len = ship_manager.getLen();
    int ship_index = std::rand() % ships_len;
    Ship ship = ship_manager.getShip(ship_index);
    std::pair <int, int> coordinates = ship.getCoor();
    int ship_len = ship.getLen();
    int segment_index = std::rand() % ship_len;
    std::cout << ship_index << " " << segment_index << "\n";
    //ship_manager.Attack();
}