//#include "playField.h"
#include "abilities/abilitiesManager.h"

#include "console/consoleDrawer.h"
#include "console/inputManager.h"


int main(){
    inputManager input_manager;
    consoleDrawer console_drawer;
    shipManager ship_manager;
    playField play_field;
    system("clear");
    input_manager.inputPlayField(std::cin, play_field);
    system("clear");
    for(int i = 0; i != 10; i++){
        try{
            console_drawer.drawPlayerField(play_field, ship_manager);
            Ship ship;
            input_manager.inputShip(std::cin, ship);
            play_field.addShip(ship, ship_manager);
        }
        catch(invalidShipPosition & e){
            system("clear");
            std::cerr << e.what() << "\n";
            i--;
            continue;
        }
        catch(invalidShipLength & e){
            system("clear");
            std::cerr << e.what() << "\n";
            i--;
            continue;
        }
        catch(inputException & e){
            system("clear");
            std::cerr << e.what() << "\n";
            i--;
            continue;
        }
        catch(objectOutOfBounds & e){
            system("clear");
            std::cerr << e.what() << "\n";
            i--;
            continue;
        }
        system("clear");
    }
} 