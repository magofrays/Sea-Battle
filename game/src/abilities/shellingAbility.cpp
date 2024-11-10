#include "shellingAbility.h"
#include "../humanPlayer.h"
#include "../messages/textMessage.h"

abilityInfo shellingAbility::info(){
    abilityInfo info;
    info.name = "Shelling";
    info.need_input = false;
    return info;
}

void shellingAbility::apply(humanPlayer * player){
    playField * play_field = player->opponent_play_field;
    shipManager * ship_manager = player->opponent_ship_manager;
    if(ship_manager->allShipsDestroyed()){
        player->Handle(textMessage("All ships are already destroyed!").clone());
        return;
    }
    player->Handle(textMessage("Shelling ability applied!").clone());
    std::mt19937 gen(std::random_device{}());
    int x = gen()%(play_field->getArea().max_point.x);
    int y = gen()%(play_field->getArea().max_point.y);
    while(!(play_field->getCell(x,y).segment) || (play_field->getCell(x, y).segment->state == Ship::Segment::destroyed)){
        x = gen()%(play_field->getArea().max_point.x);
        y = gen()%(play_field->getArea().max_point.y);
    }
    
    play_field->Attack(point2d(x, y), false);
    player->Handle(textMessage("One of the ships was attacked!").clone());
}
