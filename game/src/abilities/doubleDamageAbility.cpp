#include "doubleDamageAbility.h"
#include "../humanPlayer.h"
#include "../console/output/outputManager.h"

void doubleDamageAbility::apply(humanPlayer * player){
    player->double_damage = true;
    outputManager & output = player->output_manager;
    output.drawMessage("Double damage ability applied!\n");
    output.drawMessage("Now you can damage any segment twice!\n");
}


