#include "setupFieldState.h"
#include "../messages/keyMessage.h"
#include "../messages/textMessage.h"
#include "setupShipState.h"
#include "../messages/playFieldMessage.h"
#include "errors/errors.h"
#include "../utilities/settings.h"

void setupFieldState::execute(){

    try{
        playField new_field(size_x, size_y);
        play_field = new_field;
    }catch(invalidFieldSize & e){
        Handle(textMessage(e.what(), {255, 0, 0, 255}, textPosition::log).clone());
        if(size_x < 1){
            size_x = 1;
        }
        if(size_y < 1){
            size_y = 1;
        }
        if(size_x > seabattle::MAX_FIELD_SIZE){
            size_x = seabattle::MAX_FIELD_SIZE;
        }
        if(size_y > seabattle::MAX_FIELD_SIZE){
            size_y = seabattle::MAX_FIELD_SIZE;
        }
    }
    Handle(playFieldMessage("Your field", play_field, fieldPosition::center, false).clone());
    
}
void setupFieldState::Handle(std::unique_ptr<Message> message){
    
    if(typeid(*message) == typeid(keyMessage)){
        Message * msg = &(*message);
        keyMessage * key_msg = dynamic_cast<keyMessage*>(msg);
        int temp;
        switch(key_msg->info){
            case Key::pointer_up:
                size_y++;
                return;
            case Key::pointer_down:
                size_y--;
                return;
            case Key::pointer_right:
                size_x++;
                return;
            case Key::pointer_left:
                size_x--;
                return;
            case Key::main_action:
                this->end();
                return;
            case Key::extra_action_0:
                temp = size_x;
                size_x = size_y;
                size_y = temp;
                return;
            case Key::extra_action_1:
                size_x = 8;
                size_y = 8;
            default:
                return;
        }
    }
    else{
        handler->Handle(std::move(message));
    }
}

void setupFieldState::end(){
    game->player.setField(play_field);
    game->bot.setField(play_field);
    game->setState(new setupShipState(game, this->handler));
}

json & operator << (json & data, setupFieldState & game_state){
    data["size_x"] = game_state.size_x;
    data["size_y"] = game_state.size_y;
    return data;
}

json & operator >> (json & data, setupFieldState & game_state){
    game_state.size_x = data["size_x"];
    game_state.size_y = data["size_y"];
    return data;
}