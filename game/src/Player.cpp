#include "Player.h"

void Player::getOpponent(playField * play_field, shipManager * ship_manager){
    opponent_play_field = play_field;
    opponent_ship_manager = ship_manager;
}


void Player::placeShip(){
    while(true){
        try{
            output_manager.drawMessage("Input ship. Format:\nx y l o(coordinates, length, orientation(1 vertical, 0 horizontal))\n");
            std::shared_ptr<Ship> ship = std::make_shared<Ship>();
            input_manager.inputShip(ship);
            play_field.placeShip(ship, ship_manager);
            output_manager.update();
        }
        catch(inputException & e){
            output_manager.update();
            output_manager.drawMessage(e.what());
        }
        catch(invalidShipPosition & e){
            output_manager.update();
            output_manager.drawMessage(e.what());
        }
        catch(invalidShipLength & e){
            output_manager.update();
            output_manager.drawMessage(e.what());
        }
        catch(objectOutOfBounds & e){
            output_manager.update();
            output_manager.drawMessage(e.what());
        }
        break;
    }
}

void Player::useAbility(){
    try{
        abilities_manager.applyAbility(this);
    }
    catch(inputException & e){
        output_manager.drawMessage(e.what());
    }
    catch(noAbilitiesException & e){
        output_manager.drawMessage(e.what());
    }
    
}
void Player::Attack(){
    while(true){
    try{
        point2d coordinates;
        input_manager.inputCoordinates(coordinates);
        if(double_damage){
            opponent_play_field->Attack(coordinates, true);
            double_damage = false;
        }
        
        opponent_play_field->Attack(coordinates, true);
        break;
    }
    catch(inputException & e){
        output_manager.drawMessage(e.what());
    }
    catch(objectOutOfBounds & e){
        output_manager.drawMessage(e.what());
    }
    }
    output_manager.update();
    if(opponent_ship_manager->checkDestroyedShips()){
        output_manager.drawMessage("You destroyed ship, so got a new ability!\n");
        abilities_manager.createRandomAbility();
    }
}