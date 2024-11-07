#include "shellingAbility.h"
#include "../Player.h"
#include "../console/output/outputManager.h"

void shellingAbility::apply(Player * player){
    playField * play_field = player->opponent_play_field;
    outputManager & output = player->output_manager;
    shipManager * ship_manager = player->opponent_ship_manager;
    if(ship_manager->allShipsDestroyed()){
        output.drawMessage("All ships already destroyed\n");
        return;
    }
    output.drawMessage("Shelling ability applied!\n");
    std::mt19937 gen(std::random_device{}());
    int x = gen()%(play_field->getArea().max_point.x);
    int y = gen()%(play_field->getArea().max_point.y);
    while(!(play_field->getCell(x,y).segment) || (play_field->getCell(x, y).segment->state == Ship::Segment::destroyed)){
        x = gen()%(play_field->getArea().max_point.x);
        y = gen()%(play_field->getArea().max_point.y);
    }
    
    play_field->Attack(point2d(x, y), false);
    output.drawMessage("One of the ships was attacked!\n");
}
