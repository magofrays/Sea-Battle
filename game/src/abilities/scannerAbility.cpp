#include "scannerAbility.h"
#include "../Player.h"
#include "../console/input/inputManager.h"
#include "../console/output/outputManager.h"


void scannerAbility::apply(){
    playField & play_field = player->play_field;
    inputManager & input = player->input_manager;
    outputManager & output = player->output_manager;
    point2d coordinates;
    output.drawMessage("Input coordinates for scan.Format:\nx y(coordinates)\n");
    input.inputCoordinates(coordinates);
    if(!(play_field.getArea().contains(box2d(coordinates, coordinates+point2d(1, 1)))) ){
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
        output.drawMessage("No segments in the area were found!\n");
    }
    else{
        if(count == 1){
            output.drawMessage("1 segment in the area was found!\n");
        }
        else{
            output.drawMessage("2 segments in the area were found!\n");
            }
    }
}

void scannerAbility::setPlayer(Player * player){
    this->player = player;
}