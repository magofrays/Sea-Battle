#include "scannerAbility.h"
#include "../humanPlayer.h"
#include "../messages/textMessage.h"

abilityInfo scannerAbility::info(){
    abilityInfo info;
    info.name = "Scanner";
    info.need_input = true;
    return info;
}

void scannerAbility::apply(humanPlayer * player){
    playField & play_field = player->play_field;
    point2d coordinates = player->pointer;
    if(!(play_field.getArea().contains(box2d(coordinates, coordinates+point2d(2, 2)))) ){
            throw objectOutOfBounds(coordinates);
    }
    int count = 0;
    for(int x = 0; x != 2; ++x){
        for(int y = 0; y != 2; ++y){
            if(play_field.getCell(coordinates.x + x, coordinates.y+y).segment){
                count += 1;
            }
        }
    }
    if(count == 0){
        player->Handle(textMessage("No segments in the area were found!\n").clone());
    }
    else{
        if(count == 1){
            player->Handle(textMessage("1 segment in the area was found!\n").clone());
        }
        else{
            player->Handle(textMessage("2 segments in the area were found!\n").clone());
            }
    }
}
