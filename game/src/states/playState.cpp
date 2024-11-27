#include "playState.h"
#include "Game.h"
#include "endGameState.h"

playState::playState(Game * game, messageHandler * next, int round_number):gameState(game), round_number(round_number),
                        pointer(game->player.pointer), pointer_area(game->player.pointer_area){
            this->handler = next;
            pointer_area.max_point = point2d(0, 0);
            game->bot.getOpponent(&(game->player));
            game->player.getOpponent(&(game->bot));
            Handle(textMessage("ATTACK!", {255, 0, 0}, textPosition::title).clone());
            Handle(textMessage("Starting round " + std::to_string(round_number) + "!", {255, 255, 0}, textPosition::log).clone());
        }



void playState::execute(){
    if(game->player.ship_manager.allShipsDestroyed()){
        this->end(true); //lose
        return;
    }
    if(game->bot.ship_manager.allShipsDestroyed()){
        this->end(false); //win
        return;
    }

    if(input){
        this->usingAbility();
    }
    else{
        Handle(pointerMessage(pointer_area, pointer).clone());
        Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::left, false, false).clone());
        Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, true, true).clone());
    }
}

void playState::usingAbility(){
    Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::left, false, false).clone());
    Handle(pointerMessage(pointer_area, pointer).clone());
    Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, true, true).clone());
}

void playState::Handle(std::unique_ptr<Message> message){
    if(typeid(*message) == typeid(keyMessage)){
        Message * msg = &(*message);
        keyMessage * key_msg = dynamic_cast<keyMessage*>(msg);
        switch(key_msg->info){
            case Key::pointer_up:
                if(game->player.areaInField(pointer_area, pointer + point2d(0, 1)))
                    pointer += point2d(0, 1);
                    return;

            case Key::pointer_down:
                if(game->player.areaInField(pointer_area, pointer - point2d(0, 1)))
                    pointer -= point2d(0, 1);
                    return;
            case Key::pointer_right:
                if(game->player.areaInField(pointer_area, pointer + point2d(1, 0)))
                    pointer += point2d(1, 0);
                    return;
                
            case Key::pointer_left:
                if(game->player.areaInField(pointer_area, pointer - point2d(1, 0)))
                    pointer -= point2d(1, 0);
                    return;
                
            case Key::main_action:
                if(input){
                    game->player.useAbility();
                    input = false;
                    Handle(textMessage("ATTACK!", {255, 0, 0}, textPosition::title).clone());
                    return;
                }
                game->player.Attack();
                game->bot.Attack();
                return;
            case Key::extra_action_0:
            try{
                input = game->player.getAbility();
                    }
                catch(noAbilitiesException & e){
                    Handle(textMessage(e.what(), {255, 0, 0}, textPosition::log).clone());
                }
                if(input){
                    Handle(textMessage("USE ABILITY!", {255, 0, 255}, textPosition::title).clone());
                    pointer = point2d(0, 0);
                    Handle(textMessage("You need to input coordinates for ability", {0, 255, 0}, textPosition::log).clone());
                }
                break;
                
            default:
                break;
        }
    }
    handler->Handle(std::move(message));
}

void playState::end(bool lost){
    game->setState(new endGameState(game, this->handler, lost, round_number));
}

void playState::lose(){ // create new class for this
    Handle(textMessage("YOU LOSE! TOO BAD!", {255, 0, 0}, textPosition::title).clone());
    Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::left, false, true).clone());
    Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, false, true).clone());
}
void playState::win(){
    Handle(textMessage("YOU WIN! NICE!", {255, 255, 0}, textPosition::title).clone());
    Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::left, false, true).clone());
    Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, false, true).clone());
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