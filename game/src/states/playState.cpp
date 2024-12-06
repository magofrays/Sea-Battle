#include "playState.h"
#include "Game.h"
#include "endGameState.h"

playState::playState(Game * game, messageHandler * next, int round_number):gameState(game), round_number(round_number),
                        pointer(game->player.pointer), pointer_area(game->player.pointer_area){
            this->handler = next;
            pointer_area.max_point = point2d(0, 0);
            game->bot.getOpponent(&(game->player));
            game->player.getOpponent(&(game->bot));
            Handle(textMessage("ATTACK!", textColor::red, textPosition::title).clone());
            Handle(textMessage("Starting round " + std::to_string(round_number) + "!", textColor::yellow, textPosition::log).clone());
        }



void playState::update(){
    if(game->player.ship_manager.allShipsDestroyed()){
        this->end(true); //lose
        return;
    }
    if(game->bot.ship_manager.allShipsDestroyed()){
        this->end(false); //win
        return;
    }

    if(input){
        Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::left, false, false).clone());
        Handle(pointerMessage(pointer_area, pointer).clone());
        Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, true, true).clone());
    }
    else{
        Handle(pointerMessage(pointer_area, pointer).clone());
        Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::left, false, false).clone());
        Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, true, true).clone());
    }
}

void playState::main_action(){
    if(input){
        try{
            game->player.useAbility();
            input = false;
            Handle(textMessage("ATTACK!", textColor::red, textPosition::title).clone());
        }
        catch(objectOutOfBounds & e){
            Handle(textMessage(e.what(), textColor::red, textPosition::log).clone());  
        }
        return;
    }
    try{
    game->player.Attack();
    game->bot.Attack();}
    catch(objectOutOfBounds & e){
        Handle(textMessage(e.what(), textColor::red, textPosition::log).clone());
    }
    return;
}

void playState::extra_action_0(){
    try{
        input = game->player.getAbility();
    }catch(noAbilitiesException & e){
        Handle(textMessage(e.what(), textColor::red, textPosition::log).clone());
    }
    
    if(input){
        Handle(textMessage("USE ABILITY!", textColor::purple, textPosition::title).clone());
        pointer = point2d(0, 0);
        Handle(textMessage("You need to input coordinates for ability", textColor::purple, textPosition::log).clone());
    }
    Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::left, false, false).clone());
    Handle(pointerMessage(pointer_area, pointer).clone());
    Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, true, true).clone());
}

void playState::extra_action_1(){
    return;
}

void playState::Handle(std::unique_ptr<Message> message){
    handler->Handle(std::move(message));
}

void playState::end(bool lost){
    game->setState(new endGameState(game, this->handler, lost, round_number));
}

json & operator<<(json & data, playState & game_state){
    data["input"] = game_state.input;
    data["round_number"] = game_state.round_number;
    return data;
}

json & operator>>(json & data, playState & game_state){
    game_state.input = data["input"];
    game_state.round_number = data["round_number"];
    return data;    
}