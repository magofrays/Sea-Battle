#include "botPlayer.h"
#include "messages/textMessage.h"
#include <random>

void botPlayer::setField(playField play_field){
    this->play_field = play_field;
}

void botPlayer::getOpponent(Player * player){
    opponent_play_field = &(player->play_field);
    opponent_ship_manager = &(player->ship_manager);
}

void botPlayer::Attack(){ //crate genius ai
    point2d size = opponent_play_field->getArea().max_point;
    std::mt19937 gen(std::random_device{}());
    int x = gen()%(size.x+1);
    int y = gen()%(size.y+1);
    opponent_play_field->Attack({x, y}, false);
    if(opponent_ship_manager->checkDestroyedShips()){
        Handle(textMessage("BOT: HAHA! I destroyed your ship!", {255, 100, 0}, textPosition::log).clone());
    }
}