#include "humanPlayer.h"
#include "messages/textMessage.h"

void humanPlayer::getOpponent(Player * player){
    opponent_play_field = &(player->play_field);
    opponent_ship_manager = &(player->ship_manager);
}



bool humanPlayer::getAbility(){
    current_ability = abilities_manager.getAbility();
    abilityInfo info = current_ability->info();
    if(info.need_input){
        pointer_area = info.pointer_size;
        return true;
    }
    this->useAbility();
    return false;

}

void humanPlayer::useAbility(){
    current_ability->apply(this);
    pointer_area.min_point = point2d(0, 0);
    pointer_area.max_point = point2d(0, 0);
}

void humanPlayer::Attack(){
    if(double_damage){
        opponent_play_field->Attack(pointer, false);
        double_damage = false;
    }
    
    opponent_play_field->Attack(pointer, false);

    if(opponent_ship_manager->checkDestroyedShips()){
        Handle(textMessage("You destroyed ship, so got a new ability!", {255, 255, 0}, textPosition::log).clone());
        abilities_manager.createRandomAbility();
    }
}

bool humanPlayer::areaInField(box2d area, point2d coordinates){
    area.min_point += coordinates;
    area.max_point += coordinates;
    return play_field.getArea().contains(area);
}
/*
json & operator << (json & data, humanPlayer & player){
    data["play_field"] = player.play_field.toJson();
    data["ship_manager"] = player.ship_manager.toJson();
    data["pointer"] = player.pointer.toJson();
    data["pointer_area"] = player.pointer_area.toJson();
    return data;
}

json & operator >> (json & data, humanPlayer & player){
    player.ship_manager = shipManager(data["ship_manager"]);
    player.play_field = playField(data["play_field"]);
    player.pointer = point2d(data["pointer"]);
    player.pointer_area = box2d(data["pointer_area"]);
    return data;
}*/