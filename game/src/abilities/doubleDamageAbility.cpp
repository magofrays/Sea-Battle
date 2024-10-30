#include "doubleDamageAbility.h"
#include "../Player.h"
#include "../console/output/outputManager.h"

void doubleDamageAbility::apply(){
    player->double_damage = true;
    outputManager & output = player->output_manager;
    output.drawMessage("Double damage ability applied!\n");
    output.drawMessage("Now you can damage any segment twice!\n");
}

void doubleDamageAbility::setPlayer(Player * player){
    this->player = player;
}
