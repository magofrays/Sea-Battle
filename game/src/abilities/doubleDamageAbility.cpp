#include "doubleDamageAbility.h"
#include "../humanPlayer.h"
#include "../messages/textMessage.h"

abilityInfo doubleDamageAbility::info(){
    abilityInfo info;
    info.need_input = false;
    return info;
}

void doubleDamageAbility::apply(humanPlayer * player){
    player->double_damage = true;
    player->Handle(textMessage("Double damage ability applied!", textColor::purple, textPosition::log).clone());
    player->Handle(textMessage("Now you can damage any segment twice!", textColor::purple, textPosition::log).clone());
}


