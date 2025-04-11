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
    current_ability = nullptr;
    pointer_area.min_point = point2d(0, 0);
    pointer_area.max_point = point2d(0, 0);
}

void humanPlayer::Attack(){
    if(double_damage){
        opponent_play_field->Attack(pointer, false);
        double_damage = false;
        Handle(textMessage("Double damage applied!", textColor::yellow, textPosition::log).clone());
    }
    
    opponent_play_field->Attack(pointer, false);

    if(opponent_ship_manager->checkDestroyedShips()){
        Handle(textMessage("You destroyed ship, so got a new ability!", textColor::yellow, textPosition::log).clone());
        abilities_manager.createRandomAbility();
    }
}

void humanPlayer::free(){
    point2d field_size = play_field.getArea().max_point;
    ship_manager = shipManager();
    play_field = playField(field_size);
    abilities_manager = abilitiesManager();
}

bool humanPlayer::areaInField(box2d area, point2d coordinates){
    area.min_point += coordinates;
    area.max_point += coordinates;
    return play_field.getArea().contains(area);
}

json & operator << (json & data, humanPlayer & player){
    data["play_field"] = player.play_field.toJson();
    data["ship_manager"] = player.ship_manager.toJson();
    data["pointer"] = player.pointer.toJson();
    data["pointer_area"] = player.pointer_area.toJson();
    data["abilities_manager"] = player.abilities_manager.toJson();
    data["double_damage"] = player.double_damage;
    return data;
}

json & operator >> (json & data, humanPlayer & player){
    player.ship_manager = shipManager(data.at("ship_manager"));
    player.play_field = playField(data.at("play_field"));
    player.play_field.loadShips(player.ship_manager);
    player.pointer = point2d(data.at("pointer"));
    player.pointer_area = box2d(data.at("pointer_area"));
    player.abilities_manager = abilitiesManager(data.at("abilities_manager"));
    player.double_damage = data["double_damage"];
    return data;
}