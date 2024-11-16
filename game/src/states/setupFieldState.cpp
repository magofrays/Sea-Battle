#include "setupFieldState.h"
#include "../messages/keyMessage.h"
#include "../messages/textMessage.h"
#include "setupShipState.h"
#include "../messages/playFieldMessage.h"
#include "errors/errors.h"
#include "../utilities/settings.h"

void setupFieldState::execute(){
    Handle(textMessage("Create your field!", {255, 255, 0, 255}, textPosition::title).clone());
    try{
    game->player.setField(playField(size_x, size_y));
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
    Handle(playFieldMessage("Your field", game->player.play_field, fieldPosition::center, false).clone());
    
}
void setupFieldState::Handle(std::unique_ptr<Message> message){
    
    if(typeid(*message) == typeid(keyMessage)){
        Message * msg = &(*message);
        keyMessage * key_msg = dynamic_cast<keyMessage*>(msg);
        int temp;
        switch(key_msg->info){
            case Key::pointer_up:
                size_y++;
                break;
            case Key::pointer_down:
                size_y--;
                break;
            case Key::pointer_right:
                size_x++;
                break;
            case Key::pointer_left:
                size_x--;
                break;
            case Key::main_action:
                this->end();
                break;
            case Key::extra_action:
                temp = size_x;
                size_x = size_y;
                size_y = temp;
            default:
                break;
        }
    }
    else{
        handler->Handle(std::move(message));
    }
}

void setupFieldState::end(){
    game->setState(new setupShipState(game));
}