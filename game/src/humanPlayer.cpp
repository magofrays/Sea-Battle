#include "humanPlayer.h"
#include "messages/textMessage.h"

void humanPlayer::getOpponent(Player * player){
    opponent_play_field = &(player->play_field);
    opponent_ship_manager = &(player->ship_manager);
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
        //Handle(textMessage("You destroyed ship, so got a new ability!", point2d(70, 70)).clone());
        abilities_manager.createRandomAbility();
    }
}