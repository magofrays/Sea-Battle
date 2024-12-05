#include "gameController.h"
#include "../messages/textMessage.h"
#include "../states/Game.h"

template<messageHandlerDerived gameInput, messageHandlerDerived gameOutput>
gameController<gameInput, gameOutput>::gameController(Game & game){
    this->setNext(output);
    this->gameInput.setNext(this);
}

template<messageHandlerDerived gameInput, messageHandlerDerived gameOutput>
void gameController<gameInput, gameOutput>::run(){
     while(game.running){
        game.update();
        input.update();
        output.update();
    }
}

template<messageHandlerDerived gameInput, messageHandlerDerived gameOutput>
void gameController<gameInput, gameOutput>::Handle(std::unique_ptr<Message> message){
    if(typeid(*message) == typeid(keyMessage)){
        
        Message * msg = &(*message);
        keyMessage * key_msg = dynamic_cast<keyMessage*>(msg);
        switch(key_msg->info){
            case(Key::pointer_up):
                game.pointer.y += 1;
                return;
            
            case(Key::pointer_down):
                game.pointer.y -= 1;
                return;
            
            case(Key::pointer_right):
                game.pointer.x += 1;
                return;
            
            case(Key::pointer_right):
                game.pointer.x -= 1;
                return;

            case(Key::quit):
                game.running = false;
                return;
            
            case(Key::main_action):
                game.main_action();
                return;
            
            case(Key::extra_action_0):
                game.extra_action_0();
                return;

            case(Key::extra_action_1):
                game.extra_action_1();
                return;

            case(Key::save_action):
                game.save();
                handler->Handle(textMessage("You saved!", {255, 255, 0, 255}, textPosition::log).clone());
                return;
            
            case(Key::load_action):
                try{
                    game.load();
                    handler->Handle(textMessage("You loaded!", {255, 255, 0, 255}, textPosition::log).clone());
                }
                catch(std::runtime_error & e)
                { handler->Handle(textMessage(e.what(), {255, 0, 0, 255}, textPosition::log).clone()); }
                
                catch(nlohmann::json_abi_v3_11_3::detail::parse_error & e)
                { handler->Handle(textMessage("Error: Save data is corrupted! Create new save!", {255, 0, 0, 255}, textPosition::log).clone()); }
                return;
        }
            
            
    }
    handler->Handle(std::move(message));
}

template<messageHandlerDerived gameInput, messageHandlerDerived gameOutput>
void gameController<gameInput, gameOutput>::setNext(messageHandler * handler){
    this->handler = handler;
}