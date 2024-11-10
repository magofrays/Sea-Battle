#include "humanPlayer.h"
#include "messages/textMessage.h"

void humanPlayer::getOpponent(Player * player){
    opponent_play_field = &(player->play_field);
    opponent_ship_manager = &(player->ship_manager);
}


void humanPlayer::placeShip(){
    Handle(textMessage("Place a ship!").clone());
    std::shared_ptr<Ship> ship = std::make_shared<Ship>();
    play_field.placeShip(ship, ship_manager);
}

std::shared_ptr<IAbility> humanPlayer::useAbility(){
    return abilities_manager.getAbility();
}

void humanPlayer::Attack(){
    if(double_damage){
        opponent_play_field->Attack(pointer, true);
        double_damage = false;
    }
    
    opponent_play_field->Attack(pointer, true);

    if(opponent_ship_manager->checkDestroyedShips()){
        Handle(textMessage("You destroyed ship, so got a new ability!\n").clone());
        abilities_manager.createRandomAbility();
    }
}