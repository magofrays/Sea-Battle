#include "playState.h"
#include "Game.h"

playState::playState(Game * game):gameState(game), pointer(game->player.pointer), pointer_area(game->player.pointer_area){
            pointer_area.max_point = point2d(0, 0);
            game->bot.getOpponent(&(game->player));
            game->player.getOpponent(&(game->bot));
        }



void playState::execute(){
    if(game->player.ship_manager.allShipsDestroyed()){
        this->lose();
        return;
    }
    if(game->bot.ship_manager.allShipsDestroyed()){
        this->win();
        return;
    }

    if(input){
        this->usingAbility();
    }
    else{
        Handle(textMessage("ATTACK!", {255, 0, 0}, textPosition::title).clone());
        Handle(pointerMessage(pointer_area, pointer).clone());
        Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::left, false, false).clone());
        Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, false, true).clone());
    }
}

void playState::usingAbility(){
    Handle(textMessage("USE ABILITY!", {255, 0, 255}, textPosition::title).clone());
    Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::left, false, false).clone());
    Handle(pointerMessage(pointer_area, pointer).clone());
    Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, false, true).clone());
}

void playState::Handle(std::unique_ptr<Message> message){
    if(typeid(*message) == typeid(keyMessage)){
        Message * msg = &(*message);
        keyMessage * key_msg = dynamic_cast<keyMessage*>(msg);
        switch(key_msg->info){
            case Key::pointer_up:
                if(game->player.areaInField(pointer_area, pointer + point2d(0, 1)))
                    pointer += point2d(0, 1);
                    break;

            case Key::pointer_down:
                if(game->player.areaInField(pointer_area, pointer - point2d(0, 1)))
                    pointer -= point2d(0, 1);
                    break;
            case Key::pointer_right:
                if(game->player.areaInField(pointer_area, pointer + point2d(1, 0)))
                    pointer += point2d(1, 0);
                    break;
                
            case Key::pointer_left:
                if(game->player.areaInField(pointer_area, pointer - point2d(1, 0)))
                    pointer -= point2d(1, 0);
                    break;
                
            case Key::main_action:
                if(input){
                    game->player.useAbility();
                    input = false;
                    break;
                }
                game->player.Attack();
                game->bot.Attack();
                break;
            case Key::extra_action_0:
            try{
                input = game->player.getAbility();
                    }
                catch(noAbilitiesException & e){
                    Handle(textMessage(e.what(), {255, 0, 0}, textPosition::log).clone());
                }
                if(input){
                    Handle(textMessage("You need to input coordinates for ability", {0, 255, 0}, textPosition::log).clone());
                }
                break;
                
            default:
                break;
        }
    }
    handler->Handle(std::move(message));
}

void playState::lose(){ // create new class for this
    Handle(textMessage("YOU LOSE! TOO BAD!", {255, 0, 0}, textPosition::title).clone());
    Handle(pointerMessage(pointer_area, pointer).clone());
    Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::left, false, true).clone());
    Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, false, true).clone());
}
void playState::win(){
    Handle(textMessage("YOU WIN! NICE!", {255, 255, 0}, textPosition::title).clone());
    Handle(pointerMessage(pointer_area, pointer).clone());
    Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::left, false, true).clone());
    Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, false, true).clone());
}

json & operator<<(json & data, playState & game_state){
    data["input"] = game_state.input;
    return data;
}

json & operator>>(json & data, playState & game_state){
    game_state.input = data["input"];
    return data;    
}