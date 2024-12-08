#include "scannerAbility.h"
#include "../humanPlayer.h"
#include "../messages/textMessage.h"
#include "../errors/errors.h"

abilityInfo scannerAbility::info(){
    abilityInfo info;
    info.need_input = true;
    info.pointer_size.max_point = point2d(1, 1);
    return info;
}

void scannerAbility::apply(humanPlayer * player){
    playField & play_field = *(player->opponent_play_field);
    point2d coordinates = player->pointer;
    box2d pointer_area = player->pointer_area;
    if(!(play_field.getArea().contains(box2d(coordinates+pointer_area.min_point, coordinates+pointer_area.max_point))) ){
            throw objectOutOfBounds(coordinates);
    }
    int count = 0;
    for(int x = 0; x != pointer_area.max_point.x+1; ++x){
        for(int y = 0; y != pointer_area.max_point.y+1; ++y){
            if(play_field.getCell(coordinates.x + x, coordinates.y+y).segment){
                count += 1;
            }
        }
    }
    if(count == 0){
        player->Handle(textMessage("No segments in the area were found!", textColor::yellow, textPosition::log).clone());
    }
    else{
        if(count == 1){
            player->Handle(textMessage("1 segment in the area was found!", textColor::yellow, textPosition::log).clone());
        }
        else{
            player->Handle(textMessage("2 segments in the area were found!", textColor::yellow, textPosition::log).clone());
            }
    }
}
