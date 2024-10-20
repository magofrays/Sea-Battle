#include "shellingAbility.h"

void shellingAbility::apply(playField & play_field){
    std::cout << "Shelling ability applied!\n";
    std::mt19937 gen(std::random_device{}());

    shipManager & ship_manager = play_field.getShipManager();
    int ships_len = ship_manager.getLen();
    int ship_index = gen() % ships_len;
    Ship ship = ship_manager.getShip(ship_index);

    std::pair <int, int> coordinates = ship.getCoor();
    int ship_len = ship.getLen();
    int segment_index = gen() % ship_len;

    if(ship.IsVertical()){
        coordinates.second += segment_index;
    }
    else{
        coordinates.first += segment_index;
    }

    std::cout << coordinates.first << " " << coordinates.second << "\n";
    ship_manager.Attack(coordinates);
    
}