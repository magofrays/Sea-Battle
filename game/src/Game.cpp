#include "playField.h"
//#include "abilities/abilitiesManager.h"

#include "console/consoleDrawer.h"
//#include "console/inputManager.h"
#include "errors/invalidShipPosition.h"


int main(){
    consoleDrawer console_drawer;
    playField play_field(5, 5);
    shipManager ship_manager;
    std::shared_ptr<Ship> ship_ptr = std::make_shared<Ship>(4, std::make_pair(0, 0), true);
    
    
    try{
        play_field.placeShip(ship_ptr, ship_manager);
        ship_ptr = std::make_shared<Ship>(3, std::make_pair(2,1), false);
        play_field.placeShip(ship_ptr, ship_manager);
    
    }catch(invalidShipPosition & e){
        std::cout << e.what();
    }
    console_drawer.drawField(play_field, false);
    play_field.Attack(0, 1);
    play_field.Attack(0, 1);
    console_drawer.drawField(play_field, false);
}