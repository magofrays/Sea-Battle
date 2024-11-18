#include "setupFieldState.h"
#include "../messages/keyMessage.h"
#include "../messages/textMessage.h"
#include "setupShipState.h"
#include "../messages/playFieldMessage.h"
#include "errors/errors.h"


void setupFieldState::execute(){
    Handle(textMessage("Field size", point2d(100, 4)).clone());
    
    try{
    game->player.setField(playField(size_x, size_y));
    }catch(invalidFieldSize & e){
        Handle(textMessage(e.what(), point2d(700, 600)).clone());
        if(size_x == 0)
            size_x++;
        if(size_y == 0)
            size_y++;
    }
    Handle(playFieldMessage(game->player.play_field, fieldPosition::center).clone());
    
}
void setupFieldState::Handle(std::unique_ptr<Message> message){
    
    if(typeid(*message) == typeid(keyMessage)){
        Message * msg = &(*message);
        keyMessage * key_msg = dynamic_cast<keyMessage*>(msg);
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
                createField();
                break;
            case Key::extra_action:
                int temp = size_x;
                size_x = size_y;
                size_y = temp;
        }
    }
    else{
        handler->Handle(std::move(message));
    }
}

void setupFieldState::createField(){
    //game.setState(std::make_shared<setupShipState>();)
}