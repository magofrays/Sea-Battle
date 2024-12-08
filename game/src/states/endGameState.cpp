#include "endGameState.h"
#include "Game.h"
#include "playState.h"
#include "setupFieldState.h"
#include <string>

endGameState::endGameState(Game * game, messageHandler * next, bool lost, int round_number): gameState(game), lost(lost), round_number(round_number){
    this->handler = next;
    if(lost){
        Handle(textMessage("YOU LOST!", textColor::red, textPosition::title).clone());
        Handle(textMessage("You lost in round " + std::to_string(round_number) + "!", textColor::red, textPosition::log).clone());
        Handle(textMessage("Press ENTER to restart!", textColor::red, textPosition::log).clone());
    }
    else{
        Handle(textMessage("YOU WIN!", textColor::green, textPosition::title).clone());
        Handle(textMessage("Press ENTER to start round " + std::to_string(round_number+1) + "!", textColor::green, textPosition::log).clone());
    }
    Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::left, false, false).clone());
    Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, false, false).clone());
}

void endGameState::update(){
    
}


void endGameState::main_action(){
    this->end();
}
void endGameState::extra_action_0(){
    this->end();
}
void endGameState::extra_action_1(){
    this->end();
}

void endGameState::Handle(std::unique_ptr<Message> message){
    handler->Handle(std::move(message));     
}

void endGameState::end(){
    if(lost){
        game->player.free();
        game->bot.free();
        game->setState(new setupFieldState(game, handler));
    }
    else{
        game->bot.free();
        int ships[4];
        game->bot.callculateShips(ships);
        game->bot.placeShipsRandomly(ships);
        game->setState(new playState(game, handler, round_number+1));
    }
}

json & operator << (json & data, endGameState & game_state){
    data["round_number"] = game_state.round_number;
    data["lost"] = game_state.lost;
    return data;
}

json & operator >> (json & data, endGameState & game_state){
    game_state.round_number = data["round_number"];
    game_state.lost = data["lost"];
    return data;
}