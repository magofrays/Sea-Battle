#include "Game.h"

int main(){
    /*outputManager om(std::cout);
    shipManager manager;
    playField field(point2d(5, 5));
    std::shared_ptr<Ship> ship = std::make_shared<Ship>(4, std::make_pair(0, 0), false);
    field.placeShip(ship, manager);
    om.drawField(field, false);
    ship = std::make_shared<Ship>(4, std::make_pair(0, 1), false);
    
    field.placeShip(ship, manager);
    
    om.drawField(field, false);*/
    Game sea_battle;
    sea_battle.Setup();
    sea_battle.Play();
}