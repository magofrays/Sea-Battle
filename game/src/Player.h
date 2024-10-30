#pragma once
#include "abilities/IAbility.h"
#include "console/input/inputManager.h"
#include "console/output/outputManager.h"
#include "abilities/abilitiesManager.h"
#include "playField.h"



class Player{
        
        public:
            abilitiesManager abilities_manager;
    
            playField * opponent_play_field;
            shipManager * opponent_ship_manager;

            inputManager & input_manager;
            outputManager & output_manager;
            playField play_field;
            shipManager ship_manager;
       
            bool double_damage;
            
            Player(inputManager & im, outputManager & om):input_manager(im), output_manager(om), double_damage(false){}
            
            
            void getOpponent(playField * play_field, shipManager * ship_manager);
            void placeShip();
            void Attack();
            void useAbility();
    };