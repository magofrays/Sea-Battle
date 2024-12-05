#include "setupFieldState.h"
#include "../messages/keyMessage.h"
#include "../messages/textMessage.h"
#include "setupShipState.h"
#include "../messages/playFieldMessage.h"
#include "errors/errors.h"
#include "../utilities/settings.h"

setupFieldState::setupFieldState(Game * game, messageHandler * next) : gameState(game), pointer(game->pointer){
    pointer = point2d(2, 2);
    this->handler = next;
    Handle(textMessage("Create your field!", {255, 255, 0, 255}, textPosition::title).clone());//fix it
}



void setupFieldState::update(){

    try{
        playField new_field(pointer);
        play_field = new_field;
    }catch(invalidFieldSize & e){
        Handle(textMessage(e.what(), {255, 0, 0, 255}, textPosition::log).clone());
        if(pointer.x < 2){
            pointer.x = 2;
        }
        if(pointer.y < 2){
            pointer.y = 2;
        }
        if(pointer.x > seabattle::MAX_FIELD_SIZE){
            pointer.x = seabattle::MAX_FIELD_SIZE;
        }
        if(pointer.y > seabattle::MAX_FIELD_SIZE){
            pointer.y = seabattle::MAX_FIELD_SIZE;
        }
    }
    Handle(playFieldMessage("Your field", play_field, fieldPosition::center, false).clone());
    
}

void setupFieldState::main_action(){
    this->end();
}

void setupFieldState::extra_action_0(){
    int temp = pointer.x;
    pointer.x = pointer.y;
    pointer.y = temp;
}

void setupFieldState::extra_action_1(){
    pointer.x = 8;
    pointer.y = 8;
}

void setupFieldState::Handle(std::unique_ptr<Message> message){
    handler->Handle(std::move(message));
}

void setupFieldState::end(){
    game->player.setField(play_field);
    game->bot.setField(play_field);
    game->setState(new setupShipState(game, this->handler));
}

json & operator << (json & data, setupFieldState & game_state){
    data["pointer"] = game_state.pointer.toJson();
    return data;
}

json & operator >> (json & data, setupFieldState & game_state){
    game_state.pointer = point2d(data["pointer"]);
    return data;
}