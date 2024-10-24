//#include "playField.h"
#include "abilities/abilitiesManager.h"

#include "console/consoleDrawer.h"
#include "console/inputManager.h"


int main(){
    inputManager input_manager;
    Ship ship;
    input_manager.inputShip(std::cin, ship);
    
    /*system("clear");
    std::cout << "Input sizes of field\n";
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    int orientation = 0, x = 0, y = 0, length = 0;
    
    if (!(ss >> x >> y )|| !ss.eof()){
        throw inputException();
    }
    
    shipManager ship_manager;
    playField play_field(x, y, ship_manager);
    consoleDrawer drawer;
    system("clear");
    for(int i = 0; i != 1; i++){
        try{
            drawer.drawPlayerField(play_field);
            Ship myShip;
            std::cin >> myShip;
            play_field.addShip(myShip);
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
        
    }*/
    
} 