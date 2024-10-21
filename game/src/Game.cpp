#pragma once
#include "playField.h"
#include "abilities/abilitiesManager.h"
#include "errors/indexOutOfBounds.h"
#include "errors/invalidShipLength.h"
#include "errors/objectOutOfBounds.h"
#include "errors/inputException.h"
#include "errors/invalidShipPosition.h"

void attack_field(playField playField){
    for(int i = 0; i != 5; i++){
        for(int j = 0; j != 5; j++){
            playField.Attack({j, i});
        }
    }
    playField.printField();
}

int main(){
    shipManager ship_manager;
    playField play_field(5, 5, ship_manager);
    system("clear");
    for(int i = 0; i != 3; i++){
        try{
            attack_field(play_field);
            Ship myShip;
            std::cin >> myShip;
            play_field.addShip(myShip);
        }
        catch(invalidShipPosition & e){
            system("clear");
            std::cerr << e.what();
            i--;
            continue;
        }
        system("clear");
        
    }
    
} 