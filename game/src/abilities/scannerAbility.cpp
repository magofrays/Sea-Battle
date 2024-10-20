#include "scannerAbility.h"

scannerAbility::scannerAbility(std::pair<int, int> coordinates): coordinates(coordinates){}

void scannerAbility::setCoordinates(std::pair <int, int> coordinates){
    this->coordinates = coordinates;
}

void scannerAbility::apply(playField & play_field){
    std::cout << "Scanner ability applied!\n";
    shipManager & ship_manager = play_field.getShipManager();
    int count = 0;
    std::pair<int, int> size = play_field.getSize();
    if(
        coordinates.first < 0 || size.first < coordinates.first ||
        coordinates.second < 0 || size.second < coordinates.second
        ){
            throw std::invalid_argument("COORDINATES ARE OUT OF BORDER!");
        }
    
    for(int i = 0; i != 2; i ++){
        for(int j = 0; j != 2; j++){
            if(ship_manager.checkPoint({coordinates.first+i, coordinates.second+j})){
                count++;
            }
        }
    }
    if(count == 1){
        std::cout << "DETECTED " << count << " SEGMENT OF A SHIP!\n";
    }
    else if(count > 0){
        std::cout << "DETECTED " << count << " SEGMENTS OF A SHIP!\n";
    }
    else{
        std::cout << "NO SHIPS IN AREA\n";
    }
}
