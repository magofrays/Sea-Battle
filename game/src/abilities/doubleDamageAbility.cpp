#include "doubleDamageAbility.h"
#include "../humanPlayer.h"
#include "../messages/textMessage.h"

abilityInfo doubleDamageAbility::info(){
    abilityInfo info;
    info.name = "DoubleDamage";
    info.need_input = false;
    return info;
}

void doubleDamageAbility::apply(humanPlayer * player){
    player->double_damage = true;
    player->Handle(textMessage("Double damage ability applied!\n", point2d(40, 40)).clone());
    player->Handle(textMessage("Now you can damage any segment twice!\n", point2d(50, 50)).clone());
}


