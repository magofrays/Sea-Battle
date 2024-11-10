#include "setupFieldState.h"
#include "messages/keyMessage.h"
#include "messages/textMessage.h"
#include "setupShipState.h"

void setupFieldState::execute(){
    Handle(textMessage("Field size"))    
}
void setupFieldState::Handle(std::unique_ptr<Message> message){
    if(typeid(*message) == typeid(keyMessage)){
        switch(message->info){
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
        }
    }
    handler->Handle(message.clone());
}

void setupFieldState::createField(){
    std::make_shared<setupShipState>
}