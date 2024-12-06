#ifndef SEABATTLE_GAMECONTROLLER_H
#define SEABATTLE_GAMECONTROLLER_H

#include <concepts>
#include <type_traits>
#include "../messages/messageHandler.h"
#include "../messages/textMessage.h"
#include "../messages/keyMessage.h"
#include "../states/Game.h"

class Game;

template<typename T>
concept messageHandlerDerived = std::is_base_of_v<messageHandler, T>;

template<messageHandlerDerived gameInput, messageHandlerDerived gameOutput>
class gameController : public messageHandler {
    
    gameInput input;
    gameOutput output;
    Game game;
    messageHandler * handler;

    public:
        gameController();
        void run();
        void Handle(std::unique_ptr<Message> message);
        void setNext(messageHandler* handler);
};

template<messageHandlerDerived gameInput, messageHandlerDerived gameOutput>
gameController<gameInput, gameOutput>::gameController() : game(&output)
    { 
    this->setNext(&output); 
    this->input.setNext(this); 
    this->run();
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
            
            case(Key::pointer_left):
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




#endif
